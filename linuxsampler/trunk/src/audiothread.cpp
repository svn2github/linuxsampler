/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#include "audiothread.h"

AudioThread::AudioThread(AudioIO* pAudioIO, DiskThread* pDiskThread, gig::Instrument* pInstrument) {
    this->pAudioIO     = pAudioIO;
    this->pDiskThread  = pDiskThread;
    this->pInstrument  = pInstrument;
    this->Pitch        = 0;
    Voice::pDiskThread = pDiskThread;
    Voice::pEngine     = this;
    pEventQueue        = new RingBuffer<ModulationSystem::Event>(MAX_EVENTS_PER_FRAGMENT);
    pEventPool         = new RTELMemoryPool<ModulationSystem::Event>(MAX_EVENTS_PER_FRAGMENT);
    pVoicePool         = new RTELMemoryPool<Voice>(MAX_AUDIO_VOICES);
    pSustainedKeyPool  = new RTELMemoryPool<uint>(128);
    pEvents            = new RTEList<ModulationSystem::Event>(pEventPool);
    for (uint i = 0; i < ModulationSystem::destination_count; i++) {
        pCCEvents[i] = new RTEList<ModulationSystem::Event>(pEventPool);
    }
    for (uint i = 0; i < 128; i++) {
        pMIDIKeyInfo[i].pActiveVoices    = new RTEList<Voice>(pVoicePool);
        pMIDIKeyInfo[i].pSustainPtr      = NULL;
        pMIDIKeyInfo[i].Sustained        = false;
        pMIDIKeyInfo[i].KeyPressed       = false;
        pMIDIKeyInfo[i].pSustainPoolNode = NULL;
    }

    // FIXME: assuming stereo output
    pAudioSumBuffer[0] = new float[pAudioIO->MaxSamplesPerCycle() * pAudioIO->Channels()];
    pAudioSumBuffer[1] = &pAudioSumBuffer[0][pAudioIO->MaxSamplesPerCycle()];

    // set all voice outputs to the AudioSumBuffer
    for (Voice* pVoice = pVoicePool->alloc(); pVoice; pVoice = pVoicePool->alloc()) { //FIXME: assuming stereo
        pVoice->SetOutputLeft(pAudioSumBuffer[0],  pAudioIO->MaxSamplesPerCycle());
        pVoice->SetOutputRight(pAudioSumBuffer[1], pAudioIO->MaxSamplesPerCycle());
    }
    pVoicePool->clear();

    // cache initial samples points (for actually needed samples)
    dmsg(1,("Caching initial samples..."));
    gig::Region* pRgn = this->pInstrument->GetFirstRegion();
    while (pRgn) {
        if (!pRgn->GetSample()->GetCache().Size) {
            dmsg(2,("C"));
            CacheInitialSamples(pRgn->GetSample());
        }
        for (uint i = 0; i < pRgn->DimensionRegions; i++) {
            CacheInitialSamples(pRgn->pDimensionRegions[i]->pSample);
        }

        pRgn = this->pInstrument->GetNextRegion();
    }

    // initialize modulation system
    ModulationSystem::Initialize(pAudioIO->SampleRate(), pAudioIO->MaxSamplesPerCycle());

    // sustain pedal value
    PrevHoldCCValue = 0;
    SustainPedal    = 0;

    dmsg(1,("OK\n"));
}

AudioThread::~AudioThread() {
    ModulationSystem::Close();
    for (uint i = 0; i < 128; i++) {
        if (pMIDIKeyInfo[i].pActiveVoices) delete pMIDIKeyInfo[i].pActiveVoices;
    }
    for (uint i = 0; i < ModulationSystem::destination_count; i++) {
        if (pCCEvents[i]) delete pCCEvents[i];
    }
    delete[] pCCEvents;
    if (pEvents)           delete pEvents;
    if (pEventQueue)       delete pEventQueue;
    if (pEventPool)        delete pEventPool;
    if (pVoicePool)        delete pVoicePool;
    if (pSustainedKeyPool) delete pSustainedKeyPool;
    delete[] pAudioSumBuffer[0]; // this also frees the right channel buffer
}

/**
 *  Let this engine proceed to render the given amount of sample points. The
 *  calculated audio data of all voices of this engine will be placed into
 *  the engine's audio sum buffer which has to be copied and eventually be
 *  converted to the appropriate value range by the audio output class (e.g.
 *  AlsaIO or JackIO) right after.
 *
 *  @param Samples - number of sample points to be rendered
 *  @returns       0 on success
 */
int AudioThread::RenderAudio(uint Samples) {

    // empty the event lists for the new fragment
    pEvents->clear();
    for (uint i = 0; i < ModulationSystem::destination_count; i++) {
        pCCEvents[i]->clear();
    }

    // read and copy events from input queue
    ModulationSystem::Event Event;
    while (true) {
        if (!pEventQueue->pop(&Event)) break;
        pEvents->alloc_assign(Event);
    }


    // update time of start and end of this audio fragment (as events' time stamps relate to this)
    ModulationSystem::UpdateFragmentTime();


    // process events
    ModulationSystem::Event* pNextEvent = pEvents->first();
    while (pNextEvent) {
        ModulationSystem::Event* pEvent = pNextEvent;
        pEvents->set_current(pEvent);
        pNextEvent = pEvents->next();
        switch (pEvent->Type) {
            case ModulationSystem::event_type_note_on:
                dmsg(5,("Audio Thread: Note on received\n"));
                ProcessNoteOn(pEvent);
                break;
            case ModulationSystem::event_type_note_off:
                dmsg(5,("Audio Thread: Note off received\n"));
                ProcessNoteOff(pEvent);
                break;
            case ModulationSystem::event_type_control_change:
                dmsg(5,("Audio Thread: MIDI CC received\n"));
                ProcessControlChange(pEvent);
                break;
            case ModulationSystem::event_type_pitchbend:
                dmsg(5,("Audio Thread: Pitchbend received\n"));
                ProcessPitchbend(pEvent);
                break;
        }
    }


    // zero out the output sum buffer (left and right channel)
    memset(pAudioSumBuffer[0], 0, Samples * pAudioIO->Channels() * sizeof(float));


    // render audio from all active voices
    int active_voices = 0;
    for (uint i = 0; i < 128; i++) {
        midi_key_info_t* pKey = &pMIDIKeyInfo[i];
        Voice* pVoiceNext = pKey->pActiveVoices->first();
        while (pVoiceNext) {
            // already get next voice on key
            Voice* pVoice = pVoiceNext;
            pKey->pActiveVoices->set_current(pVoice);
            pVoiceNext = pKey->pActiveVoices->next();

            // now render current voice
            pVoice->Render(Samples);
            if (pVoice->IsActive()) active_voices++; // still active
            else { // voice reached end, is now inactive
                KillVoice(pVoice); // remove voice from the list of active voices
            }
        }
    }

    // write that to the disk thread class so that it can print it
    // on the console for debugging purposes
    ActiveVoiceCount = active_voices;
    if (ActiveVoiceCount > ActiveVoiceCountMax) ActiveVoiceCountMax = ActiveVoiceCount;


    return 0;
}

/**
 *  Will be called by the MIDIIn Thread to let the audio thread trigger a new
 *  voice for the given key.
 *
 *  @param Key      - MIDI key number of the triggered key
 *  @param Velocity - MIDI velocity value of the triggered key
 */
void AudioThread::SendNoteOn(uint8_t Key, uint8_t Velocity) {
    ModulationSystem::Event Event;
    Event.Type       = ModulationSystem::event_type_note_on;
    Event.Key        = Key;
    Event.Velocity   = Velocity;
    if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&Event);
    else dmsg(1,("AudioThread: Input event queue full!"));
}

/**
 *  Will be called by the MIDIIn Thread to signal the audio thread to release
 *  voice(s) on the given key.
 *
 *  @param Key      - MIDI key number of the released key
 *  @param Velocity - MIDI release velocity value of the released key
 */
void AudioThread::SendNoteOff(uint8_t Key, uint8_t Velocity) {
    ModulationSystem::Event Event;
    Event.Type       = ModulationSystem::event_type_note_off;
    Event.Key        = Key;
    Event.Velocity   = Velocity;
    if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&Event);
    else dmsg(1,("AudioThread: Input event queue full!"));
}

/**
 *  Will be called by the MIDIIn Thread to signal the audio thread to change
 *  the pitch value for all voices.
 *
 *  @param Pitch - MIDI pitch value (-8192 ... +8191)
 */
void AudioThread::SendPitchbend(int Pitch) {
    ModulationSystem::Event Event;
    Event.Type  = ModulationSystem::event_type_pitchbend;
    Event.Pitch = Pitch;
    if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&Event);
    else dmsg(1,("AudioThread: Input event queue full!"));
}

/**
 *  Will be called by the MIDIIn Thread to signal the audio thread that a
 *  continuous controller value has changed.
 *
 *  @param Controller - MIDI controller number of the occured control change
 *  @param Value      - value of the control change
 */
void AudioThread::SendControlChange(uint8_t Controller, uint8_t Value) {
    ModulationSystem::Event Event;
    Event.Type       = ModulationSystem::event_type_control_change;
    Event.Controller = Controller;
    Event.Value      = Value;
    if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&Event);
    else dmsg(1,("AudioThread: Input event queue full!"));
}

/**
 *  Assigns and triggers a new voice for the respective MIDI key.
 *
 *  @param pNoteOnEvent - key, velocity and time stamp of the event
 */
void AudioThread::ProcessNoteOn(ModulationSystem::Event* pNoteOnEvent) {
    midi_key_info_t* pKey = &pMIDIKeyInfo[pNoteOnEvent->Key];

    pKey->KeyPressed = true; // the MIDI key was now pressed down
    Voice* pNewVoice = pKey->pActiveVoices->alloc(); // allocate a new voice for the key
    if (pNewVoice) {
        // launch the new voice
        if (pNewVoice->Trigger(pNoteOnEvent->Key, pNoteOnEvent->Velocity, this->Pitch, this->pInstrument, pNoteOnEvent->FragmentPos()) < 0) {
            return; // failed to trigger the new voice
        }

        // update key info
        if (!pKey->pSustainPtr) {
            dmsg(4,("ProcessNoteOn(): pSustainPtr == null, setting release pointer to the last voice on the key...\n"));
            pKey->pSustainPtr = pKey->pActiveVoices->last();
        }
    }
    else std::cerr << "No free voice!" << std::endl << std::flush;
}

/**
 *  Releases the voices on the given key if sustain pedal is not pressed.
 *  If sustain is pressed, the release of the note will be postponed until
 *  sustain pedal will be released or voice turned inactive by itself (e.g.
 *  due to completion of sample playback).
 *
 *  @param pNoteOffEvent - key, velocity and time stamp of the event
 */
void AudioThread::ProcessNoteOff(ModulationSystem::Event* pNoteOffEvent) {
    midi_key_info_t* pKey = &pMIDIKeyInfo[pNoteOffEvent->Key];

    pKey->KeyPressed = false; // the MIDI key was now released
    if (SustainPedal) { // if sustain pedal is pressed postpone the Note-Off
        if (pKey->pSustainPtr) {
            // stick the note-off information to the respective voice
            Voice* pVoiceToRelease = pKey->pSustainPtr;
            pVoiceToRelease->ReleaseVelocity = pNoteOffEvent->Velocity;

            // now increment the sustain pointer
            pKey->pActiveVoices->set_current(pVoiceToRelease);
            pKey->pSustainPtr = pKey->pActiveVoices->next();

            // if the key was not marked as sustained yet, add it's MIDI key number to the sustained key pool
            if (!pKey->Sustained) {
                uint* puiSustainedKey  = pSustainedKeyPool->alloc();
                *puiSustainedKey       = pNoteOffEvent->Key;
                pKey->pSustainPoolNode = puiSustainedKey;
                pKey->Sustained        = true;
            }
        }
        else dmsg(3,("Ignoring NOTE OFF, seems like more Note-Offs than Note-Ons or no free voices available?\n"));
    }
    else {
        // release all active voices on the midi key
        Voice* pVoiceNext = pKey->pActiveVoices->first();
        while (pVoiceNext) {
            Voice* pVoiceToRelease = pVoiceNext;
            pKey->pActiveVoices->set_current(pVoiceToRelease);
            pVoiceNext = pKey->pActiveVoices->next();
            pVoiceToRelease->Release(pNoteOffEvent->FragmentPos());
        }
    }
}

/**
 *  Moves pitchbend event from the general (input) event list to the pitch
 *  event list and converts absolute pitch value to delta pitch value.
 *
 *  @param pPitchbendEvent - absolute pitch value and time stamp of the event
 */
void AudioThread::ProcessPitchbend(ModulationSystem::Event* pPitchbendEvent) {
    int currentPitch        = pPitchbendEvent->Pitch;
    pPitchbendEvent->Pitch -= this->Pitch;  // convert to delta
    this->Pitch             = currentPitch; // store current absolute pitch value
    pEvents->move(pPitchbendEvent, pCCEvents[ModulationSystem::destination_vco]);
}

/**
 *  Immediately kills the voice given with pVoice (no matter if sustain is
 *  pressed or not) and removes it from the MIDI key's list of active voice.
 *  This method will e.g. be called if a voice went inactive by itself. If
 *  sustain pedal is pressed the method takes care to free those sustain
 *  informations of the voice.
 *
 *  @param pVoice - points to the voice to be killed
 */
void AudioThread::KillVoice(Voice* pVoice) {
    if (pVoice) {
        if (pVoice->IsActive()) pVoice->Kill();

        midi_key_info_t* pKey = &pMIDIKeyInfo[pVoice->MIDIKey];

        if (pKey->Sustained) {
            // check if the sustain pointer has to be moved, now that we kill the voice
            if (pKey->pSustainPtr) {
                if (pKey->pSustainPtr == pVoice) {
                    // move sustain pointer to the next sustained voice
                    dmsg(3,("Correcting sustain pointer\n"));
                    pKey->pActiveVoices->set_current(pVoice);
                    pKey->pSustainPtr = pKey->pActiveVoices->next();
                }
                else dmsg(4,("KillVoice(Voice*): pSustainPtr != pVoice\n"));
            }
            else dmsg(3,("KillVoice(Voice*): pSustainPtr == null\n"));
        }

        // free the voice object
        pVoicePool->free(pVoice);

        // check if there are no voices left on the MIDI key and update the key info if so
        if (pKey->pActiveVoices->is_empty()) {
            pKey->pSustainPtr = NULL;
            if (pKey->Sustained) {
                pSustainedKeyPool->free(pKey->pSustainPoolNode);
                pKey->pSustainPoolNode = NULL;
                pKey->Sustained        = false;
            }
            dmsg(3,("Key has no more voices now\n"));
        }
    }
    else std::cerr << "Couldn't release voice! (pVoice == NULL)\n" << std::flush;
}

/**
 *  Reacts on supported control change commands (e.g. pitch bend wheel,
 *  modulation wheel, aftertouch).
 *
 *  @param pControlChangeEvent - controller, value and time stamp of the event
 */
void AudioThread::ProcessControlChange(ModulationSystem::Event* pControlChangeEvent) {
    dmsg(4,("AudioThread::ContinuousController cc=%d v=%d\n", pControlChangeEvent->Controller, pControlChangeEvent->Value));

    switch (pControlChangeEvent->Controller) {
        case 64: {
            if (pControlChangeEvent->Value >= 64 && PrevHoldCCValue < 64) {
                dmsg(4,("PEDAL DOWN\n"));
                SustainPedal = true;
            }
            if (pControlChangeEvent->Value < 64 && PrevHoldCCValue >= 64) {
                dmsg(4,("PEDAL UP\n"));
                SustainPedal = false;
                // iterate through all keys that are currently sustained
                for (uint* key = pSustainedKeyPool->first(); key; key = pSustainedKeyPool->next()) {
                    if (!pMIDIKeyInfo[*key].KeyPressed) { // release the voices on the key, if the key is not pressed anymore
                        // release all active voices on the midi key
                        Voice* pNextVoice = pMIDIKeyInfo[*key].pActiveVoices->first();
                        while (pNextVoice) {
                            Voice* pVoiceToRelease = pNextVoice;
                            pMIDIKeyInfo[*key].pActiveVoices->set_current(pVoiceToRelease);
                            pNextVoice = pMIDIKeyInfo[*key].pActiveVoices->next();
                            dmsg(3,("Sustain CC: releasing voice on midi key %d\n", *key));
                            pVoiceToRelease->Release(pControlChangeEvent->FragmentPos());
                        }
                        pSustainedKeyPool->free(pMIDIKeyInfo[*key].pSustainPoolNode);
                        pMIDIKeyInfo[*key].pSustainPoolNode = NULL;
                        pMIDIKeyInfo[*key].Sustained        = false;
                        pMIDIKeyInfo[*key].pSustainPtr      = NULL;
                    }
                }
                //SustainedKeyPool->empty();
            }
            PrevHoldCCValue = pControlChangeEvent->Value;
            break;
        }
    }
}

/**
 *  Caches a certain size at the beginning of the given sample in RAM. If the
 *  sample is very short, the whole sample will be loaded into RAM and thus
 *  no disk streaming is needed for this sample. Caching an initial part of
 *  samples is needed to compensate disk reading latency.
 *
 *  @param pSample - points to the sample to be cached
 */
void AudioThread::CacheInitialSamples(gig::Sample* pSample) {
    if (!pSample || pSample->GetCache().Size) return;
    if (pSample->SamplesTotal <= NUM_RAM_PRELOAD_SAMPLES) {
        // Sample is too short for disk streaming, so we load the whole
        // sample into RAM and place 'pAudioIO->FragmentSize << MAX_PITCH'
        // number of '0' samples (silence samples) behind the official buffer
        // border, to allow the interpolator do it's work even at the end of
        // the sample.
        gig::buffer_t buf = pSample->LoadSampleDataWithNullSamplesExtension((pAudioIO->MaxSamplesPerCycle() << MAX_PITCH) + 3);
        dmsg(4,("Cached %d Bytes, %d silence bytes.\n", buf.Size, buf.NullExtensionSize));
    }
    else { // we only cache NUM_RAM_PRELOAD_SAMPLES and stream the other sample points from disk
        pSample->LoadSampleData(NUM_RAM_PRELOAD_SAMPLES);
    }

    if (!pSample->GetCache().Size) std::cerr << "Unable to cache sample - maybe memory full!" << std::endl << std::flush;
}
