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
    this->pAudioIO    = pAudioIO;
    this->pDiskThread = pDiskThread;
    this->pInstrument = pInstrument;
    pCommandQueue     = new RingBuffer<command_t>(1024);
    pVoices           = new Voice*[MAX_AUDIO_VOICES];
    // allocate the ActiveVoicePool (for each midi key there is a variable size linked list
    // of pointers to Voice objects)
    ActiveVoicePool = new RTELMemoryPool<Voice*>(MAX_AUDIO_VOICES);
    for (uint i = 0; i < MAX_AUDIO_VOICES; i++) {
        pVoices[i] = new Voice(pDiskThread);
    }
    for (uint i = 0; i < 128; i++) {
        pMIDIKeyInfo[i].pActiveVoices    = new RTEList<Voice*>;
        pMIDIKeyInfo[i].hSustainPtr      = NULL;
        pMIDIKeyInfo[i].Sustained        = false;
        pMIDIKeyInfo[i].KeyPressed       = false;
        pMIDIKeyInfo[i].pSustainPoolNode = NULL;
    }
    SustainedKeyPool = new RTELMemoryPool<uint>(128);

    // FIXME: assuming stereo output
    pAudioSumBuffer[0] = new float[pAudioIO->MaxSamplesPerCycle() * pAudioIO->Channels()];
    pAudioSumBuffer[1] = &pAudioSumBuffer[0][pAudioIO->MaxSamplesPerCycle()];

    // set all voice outputs to the AudioSumBuffer
    for (int i = 0; i < MAX_AUDIO_VOICES; i++) { //FIXME: assuming stereo
        pVoices[i]->SetOutputLeft(pAudioSumBuffer[0],  pAudioIO->MaxSamplesPerCycle());
        pVoices[i]->SetOutputRight(pAudioSumBuffer[1], pAudioIO->MaxSamplesPerCycle());
    }

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
    if (pCommandQueue) delete pCommandQueue;
    if (pVoices) {
        for (uint i = 0; i < MAX_AUDIO_VOICES; i++) {
            if (pVoices[i]) delete pVoices[i];
        }
    }
    delete[] pVoices;
    delete[] pAudioSumBuffer[0]; // this also frees the right channel buffer
}

int AudioThread::RenderAudio(uint Samples) {

    // read and process commands from the queue
    while (true) {
        command_t command;
        if (!pCommandQueue->pop(&command)) break;

        switch (command.type) {
            case command_type_note_on:
                dmsg(5,("Audio Thread: Note on received\n"));
                ProcessNoteOn(command.pitch, command.velocity);
                break;
            case command_type_note_off:
                dmsg(5,("Audio Thread: Note off received\n"));
                ProcessNoteOff(command.pitch, command.velocity);
                break;
            case command_type_continuous_controller:
                dmsg(5,("Audio Thread: MIDI CC received\n"));
                ProcessControlChange(command.channel, command.number, command.value);
                break;
        }
    }


    // zero out the output sum buffer (left and right channel)
    memset(pAudioSumBuffer[0], 0, Samples * pAudioIO->Channels() * sizeof(float));


    // render audio from all active voices
    int active_voices = 0;
    for (uint i = 0; i < MAX_AUDIO_VOICES; i++) {
        if (pVoices[i]->IsActive()) {
            pVoices[i]->Render(Samples);
            if (pVoices[i]->IsActive()) active_voices++; // still active
            else { // voice reached end, is now inactive
                KillVoice(pVoices[i]); // remove voice from the list of active voices
            }
        }
    }
    // write that to the disk thread class so that it can print it
    // on the console for debugging purposes
    ActiveVoiceCount = active_voices;
    if (ActiveVoiceCount > ActiveVoiceCountMax) ActiveVoiceCountMax = ActiveVoiceCount;


    return 0;
}

/// Will be called by the MIDIIn Thread to let the audio thread trigger a new voice.
void AudioThread::SendNoteOn(uint8_t Pitch, uint8_t Velocity) {
    command_t cmd;
    cmd.type     = command_type_note_on;
    cmd.pitch    = Pitch;
    cmd.velocity = Velocity;
    if (this->pCommandQueue->write_space() > 0) this->pCommandQueue->push(&cmd);
    else dmsg(1,("AudioThread: Command queue full!"));
}

/// Will be called by the MIDIIn Thread to signal the audio thread to release voice(s).
void AudioThread::SendNoteOff(uint8_t Pitch, uint8_t Velocity) {
    command_t cmd;
    cmd.type     = command_type_note_off;
    cmd.pitch    = Pitch;
    cmd.velocity = Velocity;
    if (this->pCommandQueue->write_space() > 0) this->pCommandQueue->push(&cmd);
    else dmsg(1,("AudioThread: Command queue full!"));
}

// Will be called by the MIDIIn Thread to signal the audio thread that a continuous controller value has changed.
void AudioThread::SendControlChange(uint8_t Channel, uint8_t Number, uint8_t Value) {
    command_t cmd;
    cmd.type     = command_type_continuous_controller;
    cmd.channel  = Channel;
    cmd.number   = Number;
    cmd.value    = Value;
    if (this->pCommandQueue->write_space() > 0) this->pCommandQueue->push(&cmd);
    else dmsg(1,("AudioThread: Command queue full!"));
}

/**
 *  Assigns and triggers a new voice for the respective MIDI key.
 */
void AudioThread::ProcessNoteOn(uint8_t MIDIKey, uint8_t Velocity) {
    pMIDIKeyInfo[MIDIKey].KeyPressed = true; // the MIDI key was currently pressed down
    for (int i = 0; i < MAX_AUDIO_VOICES; i++) {
        if (pVoices[i]->IsActive()) continue; // search for a free voice

        // launch the new voice
        if (pVoices[i]->Trigger(MIDIKey, Velocity, this->pInstrument) < 0) {
            return; // failed to trigger the new voice
        }

        // add (append) a new voice to the corresponding MIDIKey active voices list
        Voice** new_voice_ptr = ActiveVoicePool->alloc_append(pMIDIKeyInfo[MIDIKey].pActiveVoices);
        *new_voice_ptr = pVoices[i];
        pVoices[i]->pSelfPtr = new_voice_ptr; // FIXME: hack to allow fast deallocation

        // update key info
        if (!pMIDIKeyInfo[MIDIKey].hSustainPtr) {
            dmsg(4,("ActivateVoice(uint,uint): hSustainPtr == null, setting release pointer to the last voice on the key...\n"));
            pMIDIKeyInfo[MIDIKey].pActiveVoices->last();
            pMIDIKeyInfo[MIDIKey].hSustainPtr = pMIDIKeyInfo[MIDIKey].pActiveVoices->current();
        }
        return;
    }
    std::cerr << "No free voice!" << std::endl << std::flush;
}

/**
 *  Releases the voices on the given key if sustain pedal is not pressed.
 *  If sustain is pressed, the release of the note will be postponed until
 *  sustain pedal will be released or voice turned inactive by itself (e.g.
 *  due to completion of sample playback).
 */
void AudioThread::ProcessNoteOff(uint8_t MIDIKey, uint8_t Velocity) {
    pMIDIKeyInfo[MIDIKey].KeyPressed = false; // the MIDI key was currently released
    midi_key_info_t* pmidikey = &pMIDIKeyInfo[MIDIKey];
    if (SustainPedal) { // if sustain pedal is pressed postpone the Note-Off
        if (pmidikey->hSustainPtr) {
            // stick the note-off information to the respective voice
            Voice** pVoiceToRelease = pmidikey->pActiveVoices->set_current(pmidikey->hSustainPtr);
            if (pVoiceToRelease) {
                (*pVoiceToRelease)->ReleaseVelocity = Velocity;
                // now increment the sustain pointer
                pmidikey->pActiveVoices->next();
                pmidikey->hSustainPtr = pmidikey->pActiveVoices->current();
                // if the key was not sustained yet, add it's MIDI key number to the sustained key pool
                if (!pmidikey->Sustained) {
                    uint* sustainedmidikey     = SustainedKeyPool->alloc();
                    *sustainedmidikey          = MIDIKey;
                    pmidikey->pSustainPoolNode = sustainedmidikey;
                    pmidikey->Sustained        = true;
                }
            }
            else dmsg(3,("Ignoring NOTE OFF --> pVoiceToRelease == null!\n"));
        }
        else dmsg(3,("Ignoring NOTE OFF, seems like more Note-Offs than Note-Ons or no free voices available?\n"));
    }
    else {
        // release all active voices on the midi key
        Voice** pVoicePtr = pmidikey->pActiveVoices->first();
        while (pVoicePtr) {
            Voice** pVoicePtrNext = pMIDIKeyInfo[MIDIKey].pActiveVoices->next();
            (*pVoicePtr)->Release();
            pVoicePtr = pVoicePtrNext;
        }
    }
}

/**
 *  Immediately kills the voice given with pVoice (no matter if sustain is
 *  pressed or not) and removes it from the MIDI key's list of active voice.
 *  This method will e.g. be called if a voice went inactive by itself. If
 *  sustain pedal is pressed the method takes care to free those sustain
 *  informations of the voice.
 */
void AudioThread::KillVoice(Voice* pVoice) {
    if (pVoice) {
        if (pVoice->IsActive()) pVoice->Kill();

        if (pMIDIKeyInfo[pVoice->MIDIKey].Sustained) {
            // check if the sustain pointer has to be moved, now that we kill the voice
            RTEList<Voice*>::NodeHandle hSustainPtr = pMIDIKeyInfo[pVoice->MIDIKey].hSustainPtr;
            if (hSustainPtr) {
                Voice** pVoicePtr = pMIDIKeyInfo[pVoice->MIDIKey].pActiveVoices->set_current(hSustainPtr);
                if (pVoicePtr) {
                    if (*pVoicePtr == pVoice) { // move sustain pointer to the next sustained voice
                        dmsg(3,("Correcting sustain pointer\n"));
                        pMIDIKeyInfo[pVoice->MIDIKey].pActiveVoices->next();
                        pMIDIKeyInfo[pVoice->MIDIKey].hSustainPtr = pMIDIKeyInfo[pVoice->MIDIKey].pActiveVoices->current();
                    }
                    else dmsg(4,("ReleaseVoice(Voice*): *hSustain != pVoice\n"));
                }
                else dmsg(3,("ReleaseVoice(Voice*): pVoicePtr == null\n"));
            }
            else dmsg(3,("ReleaseVoice(Voice*): hSustainPtr == null\n"));
        }

        // remove the voice from the list associated with this MIDI key
        ActiveVoicePool->free(pVoice->pSelfPtr);

        // check if there are no voices left on the MIDI key and update the key info if so
        if (pMIDIKeyInfo[pVoice->MIDIKey].pActiveVoices->is_empty()) {
            pMIDIKeyInfo[pVoice->MIDIKey].hSustainPtr = NULL;
            if (pMIDIKeyInfo[pVoice->MIDIKey].Sustained) {
                SustainedKeyPool->free(pMIDIKeyInfo[pVoice->MIDIKey].pSustainPoolNode);
                pMIDIKeyInfo[pVoice->MIDIKey].pSustainPoolNode = NULL;
                pMIDIKeyInfo[pVoice->MIDIKey].Sustained        = false;
            }
            dmsg(3,("Key has no more voices now\n"));
        }
    }
    else std::cerr << "Couldn't release voice! (pVoice == NULL)\n" << std::flush;
}

void AudioThread::ProcessControlChange(uint8_t Channel, uint8_t Number, uint8_t Value) {
    dmsg(4,("AudioThread::ContinuousController c=%d n=%d v=%d\n", Channel, Number, Value));
    if (Number == 64) {
        if (Value >= 64 && PrevHoldCCValue < 64) {
            dmsg(4,("PEDAL DOWN\n"));
            SustainPedal = true;
        }
        if (Value < 64 && PrevHoldCCValue >= 64) {
            dmsg(4,("PEDAL UP\n"));
            SustainPedal = false;
            // iterate through all keys that are currently sustained
            for (uint* key = SustainedKeyPool->first(); key; key = SustainedKeyPool->next()) {
                if (!pMIDIKeyInfo[*key].KeyPressed) { // release the voices on the key, if the key is not pressed anymore
                    // release all active voices on the midi key
                    Voice** pVoicePtr = pMIDIKeyInfo[*key].pActiveVoices->first();
                    while (pVoicePtr) {
                        Voice** pVoicePtrNext = pMIDIKeyInfo[*key].pActiveVoices->next();
                        dmsg(3,("Sustain CC: releasing voice on midi key %d\n", *key));
                        (*pVoicePtr)->Release();
                        pVoicePtr = pVoicePtrNext;
                    }
                    SustainedKeyPool->free(pMIDIKeyInfo[*key].pSustainPoolNode);
                    pMIDIKeyInfo[*key].pSustainPoolNode = NULL;
                    pMIDIKeyInfo[*key].Sustained        = false;
                    pMIDIKeyInfo[*key].hSustainPtr      = NULL;
                }
            }
            //SustainedKeyPool->empty();
        }
        PrevHoldCCValue = Value;
    }
}

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
