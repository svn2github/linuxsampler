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

AudioThread::AudioThread(AudioIO* pAudioIO) {
    this->pAudioIO     = pAudioIO;
    this->pDiskThread  = new DiskThread(((pAudioIO->MaxSamplesPerCycle() << MAX_PITCH) << 1) + 6); //FIXME: assuming stereo
    this->pInstrument  = NULL;
    this->Pitch        = 0;
    this->SustainPedal = 0;
    Voice::pDiskThread = this->pDiskThread;
    Voice::pEngine     = this;
    pEventQueue        = new RingBuffer<ModulationSystem::Event>(MAX_EVENTS_PER_FRAGMENT);
    pEventPool         = new RTELMemoryPool<ModulationSystem::Event>(MAX_EVENTS_PER_FRAGMENT);
    pVoicePool         = new RTELMemoryPool<Voice>(MAX_AUDIO_VOICES);
    pActiveKeys        = new RTELMemoryPool<uint>(128);
    pEvents            = new RTEList<ModulationSystem::Event>(pEventPool);
    pCCEvents          = new RTEList<ModulationSystem::Event>(pEventPool);
    for (uint i = 0; i < ModulationSystem::destination_count; i++) {
        pSynthesisEvents[i] = new RTEList<ModulationSystem::Event>(pEventPool);
    }
    for (uint i = 0; i < 128; i++) {
        pMIDIKeyInfo[i].pActiveVoices = new RTEList<Voice>(pVoicePool);
        pMIDIKeyInfo[i].KeyPressed    = false;
        pMIDIKeyInfo[i].Active        = false;
        pMIDIKeyInfo[i].pSelf         = NULL;
        pMIDIKeyInfo[i].pEvents       = new RTEList<ModulationSystem::Event>(pEventPool);
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

    pRIFF       = NULL;
    pGig        = NULL;
    pInstrument = NULL;

    // initialize modulation system
    ModulationSystem::Initialize(pAudioIO->SampleRate(), pAudioIO->MaxSamplesPerCycle());
    
    // set all MIDI controller values to zero
    memset(ControllerTable, 0x00, 128);

    SuspensionRequested = false;
    pthread_mutex_init(&__render_state_mutex, NULL);
    pthread_cond_init(&__render_exit_condition, NULL);

    dmsg(1,("Starting disk thread..."));
    pDiskThread->StartThread();
    dmsg(1,("OK\n"));
}

AudioThread::~AudioThread() {
    if (pDiskThread) {
        pDiskThread->StopThread();
        delete pDiskThread;
    }
    if (pGig)  delete pGig;
    if (pRIFF) delete pRIFF;
    ModulationSystem::Close();
    for (uint i = 0; i < 128; i++) {
        if (pMIDIKeyInfo[i].pActiveVoices) delete pMIDIKeyInfo[i].pActiveVoices;
        if (pMIDIKeyInfo[i].pEvents)       delete pMIDIKeyInfo[i].pEvents;
    }
    for (uint i = 0; i < ModulationSystem::destination_count; i++) {
        if (pSynthesisEvents[i]) delete pSynthesisEvents[i];
    }
    delete[] pSynthesisEvents;
    if (pEvents)     delete pEvents;
    if (pCCEvents)   delete pCCEvents;
    if (pEventQueue) delete pEventQueue;
    if (pEventPool)  delete pEventPool;
    if (pVoicePool)  delete pVoicePool;
    if (pActiveKeys) delete pActiveKeys;
    delete[] pAudioSumBuffer[0]; // this also frees the right channel buffer
    pthread_cond_destroy(&__render_exit_condition);
    pthread_mutex_destroy(&__render_state_mutex);
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

    // zero out the output sum buffer (left and right channel)
    memset(pAudioSumBuffer[0], 0, Samples * pAudioIO->Channels() * sizeof(float));


    // check if rendering process was requested to be interrupted (e.g. to load another instrument)
    if (SuspensionRequested) {
        pthread_cond_broadcast(&__render_exit_condition); // wake up anybody waiting for us
        return 0;
    }


    // empty the event lists for the new fragment
    pEvents->clear();
    pCCEvents->clear();
    for (uint i = 0; i < ModulationSystem::destination_count; i++) {
        pSynthesisEvents[i]->clear();
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


    // render audio from all active voices
    int active_voices = 0;
    uint* piKey = pActiveKeys->first();
    while (piKey) { // iterate through all active keys
        midi_key_info_t* pKey = &pMIDIKeyInfo[*piKey];
        pActiveKeys->set_current(piKey);
        piKey = pActiveKeys->next();

        Voice* pVoiceNext = pKey->pActiveVoices->first();
        while (pVoiceNext) { // iterate through all voices on this key
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
        pKey->pEvents->clear(); // free all events on the key
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

    // cancel release process of voices on this key if needed
    if (pKey->Active && !SustainPedal) {
        pNoteOnEvent->Type = ModulationSystem::event_type_cancel_release; // transform event type
        pEvents->move(pNoteOnEvent, pKey->pEvents); // move event to the key's own event list
    }

    // allocate a new voice for the key
    Voice* pNewVoice = pKey->pActiveVoices->alloc();
    if (pNewVoice) {
        // launch the new voice
        if (pNewVoice->Trigger(pNoteOnEvent, this->Pitch, this->pInstrument) < 0) {
            dmsg(1,("Triggering new voice failed!\n"));
            pKey->pActiveVoices->free(pNewVoice);
        }
        else if (!pKey->Active) { // mark as active key
            pKey->Active = true;
            pKey->pSelf  = pActiveKeys->alloc();
            *pKey->pSelf = pNoteOnEvent->Key;
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

    // release voices on this key if needed
    if (pKey->Active && !SustainPedal) {
        pNoteOffEvent->Type = ModulationSystem::event_type_release; // transform event type
        pEvents->move(pNoteOffEvent, pKey->pEvents); // move event to the key's own event list
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
    pEvents->move(pPitchbendEvent, pSynthesisEvents[ModulationSystem::destination_vco]);
}

/**
 *  Immediately kills the voice given with pVoice (no matter if sustain is
 *  pressed or not) and removes it from the MIDI key's list of active voice.
 *  This method will e.g. be called if a voice went inactive by itself.
 *
 *  @param pVoice - points to the voice to be killed
 */
void AudioThread::KillVoice(Voice* pVoice) {
    if (pVoice) {
        if (pVoice->IsActive()) pVoice->Kill();

        midi_key_info_t* pKey = &pMIDIKeyInfo[pVoice->MIDIKey];

        // free the voice object
        pVoicePool->free(pVoice);

        // check if there are no voices left on the MIDI key and update the key info if so
        if (pKey->pActiveVoices->is_empty()) {
            pKey->Active = false;
            pActiveKeys->free(pKey->pSelf); // remove key from list of active keys
            pKey->pSelf = NULL;
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
            if (pControlChangeEvent->Value >= 64 && !SustainPedal) {
                dmsg(4,("PEDAL DOWN\n"));
                SustainPedal = true;

                // cancel release process of voices if necessary
                uint* piKey = pActiveKeys->first();
                if (piKey) {
                    pControlChangeEvent->Type = ModulationSystem::event_type_cancel_release; // transform event type
                    while (piKey) {
                        midi_key_info_t* pKey = &pMIDIKeyInfo[*piKey];
                        pActiveKeys->set_current(piKey);
                        piKey = pActiveKeys->next();
                        if (!pKey->KeyPressed) {
                            ModulationSystem::Event* pNewEvent = pKey->pEvents->alloc();
                            if (pNewEvent) *pNewEvent = *pControlChangeEvent; // copy event to the key's own event list
                            else dmsg(1,("Event pool emtpy!\n"));
                        }
                    }
                }
            }
            if (pControlChangeEvent->Value < 64 && SustainPedal) {
                dmsg(4,("PEDAL UP\n"));
                SustainPedal = false;

                // release voices if their respective key is not pressed
                uint* piKey = pActiveKeys->first();
                if (piKey) {
                    pControlChangeEvent->Type = ModulationSystem::event_type_release; // transform event type
                    while (piKey) {
                        midi_key_info_t* pKey = &pMIDIKeyInfo[*piKey];
                        pActiveKeys->set_current(piKey);
                        piKey = pActiveKeys->next();
                        if (!pKey->KeyPressed) {
                            ModulationSystem::Event* pNewEvent = pKey->pEvents->alloc();
                            if (pNewEvent) *pNewEvent = *pControlChangeEvent; // copy event to the key's own event list
                            else dmsg(1,("Event pool emtpy!\n"));
                        }
                    }
                }
            }
            break;
        }
    }
    
    // update controller value in the engine's controller table
    ControllerTable[pControlChangeEvent->Controller] = pControlChangeEvent->Value;
    
    // move event from the unsorted event list to the control change event list
    pEvents->move(pControlChangeEvent, pCCEvents);
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

/**
 *  Load an instrument from a .gig file.
 *
 *  @param FileName   - file name of the Gigasampler instrument file
 *  @param Instrument - index of the instrument in the .gig file
 *  @returns          detailed description of the result of the method call
 */
result_t AudioThread::LoadInstrument(const char* FileName, uint Instrument) {
    result_t result;

    if (pInstrument) { // if already running
        // signal audio thread not to enter render part anymore
        SuspensionRequested = true;
        // sleep until wakened by audio thread
        pthread_mutex_lock(&__render_state_mutex);
        pthread_cond_wait(&__render_exit_condition, &__render_state_mutex);
        pthread_mutex_unlock(&__render_state_mutex);

        dmsg(1,("Freeing old instrument from memory..."));
        delete pGig;
        delete pRIFF;
        pInstrument = NULL;
        dmsg(1,("OK\n"));
    }

    // loading gig file
    try {
        dmsg(1,("Loading gig file..."));
        pRIFF       = new RIFF::File(FileName);
        pGig        = new gig::File(pRIFF);
        pInstrument = pGig->GetInstrument(Instrument);
        if (!pInstrument) {
            std::stringstream msg;
            msg << "There's no instrument with index " << Instrument << ".";
            std::cerr << msg << std::endl;
            result.type    = result_type_error;
            result.code    = LSCP_ERR_UNKNOWN;
            result.message = msg.str();
            return result;
        }
        pGig->GetFirstSample(); // just to complete instrument loading before we enter the realtime part
        dmsg(1,("OK\n"));
    }
    catch (RIFF::Exception e) {
        e.PrintMessage();
        result.type    = result_type_error;
        result.code    = LSCP_ERR_UNKNOWN;
        result.message = e.Message;
        return result;
    }
    catch (...) {
        dmsg(1,("Unknown exception while trying to parse gig file.\n"));
        result.type    = result_type_error;
        result.code    = LSCP_ERR_UNKNOWN;
        result.message = "Unknown exception while trying to parse gig file.";
        return result;
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
    dmsg(1,("OK\n"));

    ResetInternal(); // reset engine

    // signal audio thread to continue with rendering
    SuspensionRequested = false;

    // success
    result.type = result_type_success;
    return result;
}

/**
 *  Reset all voices and disk thread and clear input event queue and all
 *  control and status variables.
 */
void AudioThread::Reset() {
    if (pInstrument) { // if already running
        // signal audio thread not to enter render part anymore
        SuspensionRequested = true;
        // sleep until wakened by audio thread
        pthread_mutex_lock(&__render_state_mutex);
        pthread_cond_wait(&__render_exit_condition, &__render_state_mutex);
        pthread_mutex_unlock(&__render_state_mutex);
    }

    ResetInternal();

    // signal audio thread to continue with rendering
    SuspensionRequested = false;
}

/**
 *  Reset all voices and disk thread and clear input event queue and all
 *  control and status variables. This method is not thread safe!
 */
void AudioThread::ResetInternal() {
    this->Pitch         = 0;
    SustainPedal        = 0;
    ActiveVoiceCount    = 0;
    ActiveVoiceCountMax = 0;

    // reset key info
    for (uint i = 0; i < 128; i++) {
        pMIDIKeyInfo[i].pActiveVoices->clear();
        pMIDIKeyInfo[i].pEvents->clear();
        pMIDIKeyInfo[i].KeyPressed = false;
        pMIDIKeyInfo[i].Active     = false;
        pMIDIKeyInfo[i].pSelf      = NULL;
    }

    // reset all voices
    for (Voice* pVoice = pVoicePool->first(); pVoice; pVoice = pVoicePool->next()) {
        pVoice->Reset();
    }

    // free all active keys
    pActiveKeys->clear();

    // reset disk thread
    pDiskThread->Reset();

    // delete all input events
    pEventQueue->init();
}
