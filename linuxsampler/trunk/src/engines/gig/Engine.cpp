/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#include <sstream>
#include "DiskThread.h"
#include "Voice.h"

#include "Engine.h"

namespace LinuxSampler { namespace gig {

    InstrumentResourceManager Engine::Instruments;

    Engine::Engine() {
        pRIFF              = NULL;
        pGig               = NULL;
        pInstrument        = NULL;
        pAudioOutputDevice = NULL;
        pDiskThread        = NULL;
        pEventGenerator    = NULL;
        pSysexBuffer       = new RingBuffer<uint8_t>(SYSEX_BUFFER_SIZE, 0);
        pEventQueue        = new RingBuffer<Event>(MAX_EVENTS_PER_FRAGMENT, 0);
        pEventPool         = new RTELMemoryPool<Event>(MAX_EVENTS_PER_FRAGMENT);
        pVoicePool         = new RTELMemoryPool<Voice>(MAX_AUDIO_VOICES);
        pActiveKeys        = new RTELMemoryPool<uint>(128);
        pEvents            = new RTEList<Event>(pEventPool);
        pCCEvents          = new RTEList<Event>(pEventPool);
        for (uint i = 0; i < Event::destination_count; i++) {
            pSynthesisEvents[i] = new RTEList<Event>(pEventPool);
        }
        for (uint i = 0; i < 128; i++) {
            pMIDIKeyInfo[i].pActiveVoices  = new RTEList<Voice>(pVoicePool);
            pMIDIKeyInfo[i].KeyPressed     = false;
            pMIDIKeyInfo[i].Active         = false;
            pMIDIKeyInfo[i].ReleaseTrigger = false;
            pMIDIKeyInfo[i].pSelf          = NULL;
            pMIDIKeyInfo[i].pEvents        = new RTEList<Event>(pEventPool);
        }
        for (Voice* pVoice = pVoicePool->alloc(); pVoice; pVoice = pVoicePool->alloc()) {
            pVoice->SetEngine(this);
        }
        pVoicePool->clear();

        pSynthesisParameters[0] = NULL; // we allocate when an audio device is connected
        pBasicFilterParameters  = NULL;
        pMainFilterParameters   = NULL;

	InstrumentIdx = -1;
	InstrumentStat = -1;

        AudioDeviceChannelLeft  = -1;
        AudioDeviceChannelRight = -1;

        ResetInternal();
    }

    Engine::~Engine() {
        if (pDiskThread) {
            pDiskThread->StopThread();
            delete pDiskThread;
        }
        if (pGig)  delete pGig;
        if (pRIFF) delete pRIFF;
        for (uint i = 0; i < 128; i++) {
            if (pMIDIKeyInfo[i].pActiveVoices) delete pMIDIKeyInfo[i].pActiveVoices;
            if (pMIDIKeyInfo[i].pEvents)       delete pMIDIKeyInfo[i].pEvents;
        }
        for (uint i = 0; i < Event::destination_count; i++) {
            if (pSynthesisEvents[i]) delete pSynthesisEvents[i];
        }
        delete[] pSynthesisEvents;
        if (pEvents)     delete pEvents;
        if (pCCEvents)   delete pCCEvents;
        if (pEventQueue) delete pEventQueue;
        if (pEventPool)  delete pEventPool;
        if (pVoicePool)  delete pVoicePool;
        if (pActiveKeys) delete pActiveKeys;
        if (pSysexBuffer) delete pSysexBuffer;
        if (pEventGenerator) delete pEventGenerator;
        if (pMainFilterParameters) delete[] pMainFilterParameters;
        if (pBasicFilterParameters) delete[] pBasicFilterParameters;
        if (pSynthesisParameters[0]) delete[] pSynthesisParameters[0];
    }

    void Engine::Enable() {
        dmsg(3,("gig::Engine: enabling\n"));
        EngineDisabled.PushAndUnlock(false, 2); // set condition object 'EngineDisabled' to false (wait max. 2s)
        dmsg(3,("gig::Engine: enabled (val=%d)\n", EngineDisabled.GetUnsafe()));
    }

    void Engine::Disable() {
        dmsg(3,("gig::Engine: disabling\n"));
        bool* pWasDisabled = EngineDisabled.PushAndUnlock(true, 2); // wait max. 2s
        if (!pWasDisabled) dmsg(3,("gig::Engine warning: Timeout waiting to disable engine.\n"));
    }

    void Engine::DisableAndLock() {
        dmsg(3,("gig::Engine: disabling\n"));
        bool* pWasDisabled = EngineDisabled.Push(true, 2); // wait max. 2s
        if (!pWasDisabled) dmsg(3,("gig::Engine warning: Timeout waiting to disable engine.\n"));
    }

    /**
     *  Reset all voices and disk thread and clear input event queue and all
     *  control and status variables.
     */
    void Engine::Reset() {
        DisableAndLock();

        //if (pAudioOutputDevice->IsPlaying()) { // if already running
            /*
            // signal audio thread not to enter render part anymore
            SuspensionRequested = true;
            // sleep until wakened by audio thread
            pthread_mutex_lock(&__render_state_mutex);
            pthread_cond_wait(&__render_exit_condition, &__render_state_mutex);
            pthread_mutex_unlock(&__render_state_mutex);
            */
        //}

        //if (wasplaying) pAudioOutputDevice->Stop();

        ResetInternal();

        // signal audio thread to continue with rendering
        //SuspensionRequested = false;
        Enable();
    }

    /**
     *  Reset all voices and disk thread and clear input event queue and all
     *  control and status variables. This method is not thread safe!
     */
    void Engine::ResetInternal() {
        Pitch               = 0;
        SustainPedal        = false;
        ActiveVoiceCount    = 0;
        ActiveVoiceCountMax = 0;
        GlobalVolume        = 1.0;

        // reset to normal chromatic scale (means equal temper)
        memset(&ScaleTuning[0], 0x00, 12);

        // set all MIDI controller values to zero
        memset(ControllerTable, 0x00, 128);

        // reset key info
        for (uint i = 0; i < 128; i++) {
            pMIDIKeyInfo[i].pActiveVoices->clear();
            pMIDIKeyInfo[i].pEvents->clear();
            pMIDIKeyInfo[i].KeyPressed     = false;
            pMIDIKeyInfo[i].Active         = false;
            pMIDIKeyInfo[i].ReleaseTrigger = false;
            pMIDIKeyInfo[i].pSelf          = NULL;
        }

        // reset all key groups
        map<uint,uint*>::iterator iter = ActiveKeyGroups.begin();
        for (; iter != ActiveKeyGroups.end(); iter++) iter->second = NULL;

        // reset all voices
        for (Voice* pVoice = pVoicePool->alloc(); pVoice; pVoice = pVoicePool->alloc()) {
            pVoice->Reset();
        }
        pVoicePool->clear();

        // free all active keys
        pActiveKeys->clear();

        // reset disk thread
        if (pDiskThread) pDiskThread->Reset();

        // delete all input events
        pEventQueue->init();
    }

    /**
     *  Load an instrument from a .gig file.
     *
     *  @param FileName   - file name of the Gigasampler instrument file
     *  @param Instrument - index of the instrument in the .gig file
     *  @throws LinuxSamplerException  on error
     *  @returns          detailed description of the method call result
     */
    void Engine::LoadInstrument(const char* FileName, uint Instrument) {

        DisableAndLock();

        ResetInternal(); // reset engine

        // free old instrument
        if (pInstrument) {
            // give old instrument back to instrument manager
            Instruments.HandBack(pInstrument, this);
        }

	InstrumentFile = FileName;
	InstrumentIdx = Instrument;
	InstrumentStat = 0;

        // delete all key groups
        ActiveKeyGroups.clear();

        // request gig instrument from instrument manager
        try {
            instrument_id_t instrid;
            instrid.FileName    = FileName;
            instrid.iInstrument = Instrument;
            pInstrument = Instruments.Borrow(instrid, this);
            if (!pInstrument) {
                InstrumentStat = -1;
                dmsg(1,("no instrument loaded!!!\n"));
                exit(EXIT_FAILURE);
            }
        }
        catch (RIFF::Exception e) {
            InstrumentStat = -2;
            String msg = "gig::Engine error: Failed to load instrument, cause: " + e.Message;
            throw LinuxSamplerException(msg);
        }
        catch (InstrumentResourceManagerException e) {
            InstrumentStat = -3;
            String msg = "gig::Engine error: Failed to load instrument, cause: " + e.Message();
            throw LinuxSamplerException(msg);
        }
        catch (...) {
            InstrumentStat = -4;
            throw LinuxSamplerException("gig::Engine error: Failed to load instrument, cause: Unknown exception while trying to parse gig file.");
        }

        // rebuild ActiveKeyGroups map with key groups of current instrument
        for (::gig::Region* pRegion = pInstrument->GetFirstRegion(); pRegion; pRegion = pInstrument->GetNextRegion())
            if (pRegion->KeyGroup) ActiveKeyGroups[pRegion->KeyGroup] = NULL;

	InstrumentStat = 100;

        // inform audio driver for the need of two channels
        try {
            if (pAudioOutputDevice) pAudioOutputDevice->AcquireChannels(2); // gig Engine only stereo
        }
        catch (AudioOutputException e) {
            String msg = "Audio output device unable to provide 2 audio channels, cause: " + e.Message();
            throw LinuxSamplerException(msg);
        }

        Enable();
    }

    /**
     * Will be called by the InstrumentResourceManager when the instrument
     * we are currently using in this engine is going to be updated, so we
     * can stop playback before that happens.
     */
    void Engine::ResourceToBeUpdated(::gig::Instrument* pResource, void*& pUpdateArg) {
        dmsg(3,("gig::Engine: Received instrument update message.\n"));
        DisableAndLock();
        ResetInternal();
        this->pInstrument = NULL;
    }

    /**
     * Will be called by the InstrumentResourceManager when the instrument
     * update process was completed, so we can continue with playback.
     */
    void Engine::ResourceUpdated(::gig::Instrument* pOldResource, ::gig::Instrument* pNewResource, void* pUpdateArg) {
        this->pInstrument = pNewResource; //TODO: there are couple of engine parameters we should update here as well if the instrument was updated (see LoadInstrument())
        Enable();
    }

    void Engine::Connect(AudioOutputDevice* pAudioOut) {
        pAudioOutputDevice = pAudioOut;

        ResetInternal();

        // inform audio driver for the need of two channels
        try {
            pAudioOutputDevice->AcquireChannels(2); // gig engine only stereo
        }
        catch (AudioOutputException e) {
            String msg = "Audio output device unable to provide 2 audio channels, cause: " + e.Message();
            throw LinuxSamplerException(msg);
        }

        this->AudioDeviceChannelLeft  = 0;
        this->AudioDeviceChannelRight = 1;
        this->pOutputLeft             = pAudioOutputDevice->Channel(0)->Buffer();
        this->pOutputRight            = pAudioOutputDevice->Channel(1)->Buffer();
        this->MaxSamplesPerCycle      = pAudioOutputDevice->MaxSamplesPerCycle();
        this->SampleRate              = pAudioOutputDevice->SampleRate();

        // (re)create disk thread
        if (this->pDiskThread) {
            this->pDiskThread->StopThread();
            delete this->pDiskThread;
        }
        this->pDiskThread = new DiskThread(((pAudioOut->MaxSamplesPerCycle() << MAX_PITCH) << 1) + 6); //FIXME: assuming stereo
        if (!pDiskThread) {
            dmsg(0,("gig::Engine  new diskthread = NULL\n"));
            exit(EXIT_FAILURE);
        }

        for (Voice* pVoice = pVoicePool->alloc(); pVoice; pVoice = pVoicePool->alloc()) {
            pVoice->pDiskThread = this->pDiskThread;
            dmsg(3,("d"));
        }
        pVoicePool->clear();

        // (re)create event generator
        if (pEventGenerator) delete pEventGenerator;
        pEventGenerator = new EventGenerator(pAudioOut->SampleRate());

        // (re)allocate synthesis parameter matrix
        if (pSynthesisParameters[0]) delete[] pSynthesisParameters[0];
        pSynthesisParameters[0] = new float[Event::destination_count * pAudioOut->MaxSamplesPerCycle()];
        for (int dst = 1; dst < Event::destination_count; dst++)
            pSynthesisParameters[dst] = pSynthesisParameters[dst - 1] + pAudioOut->MaxSamplesPerCycle();

        // (re)allocate biquad filter parameter sequence
        if (pBasicFilterParameters) delete[] pBasicFilterParameters;
        if (pMainFilterParameters)  delete[] pMainFilterParameters;
        pBasicFilterParameters = new biquad_param_t[pAudioOut->MaxSamplesPerCycle()];
        pMainFilterParameters  = new biquad_param_t[pAudioOut->MaxSamplesPerCycle()];

        dmsg(1,("Starting disk thread..."));
        pDiskThread->StartThread();
        dmsg(1,("OK\n"));

        for (Voice* pVoice = pVoicePool->first(); pVoice; pVoice = pVoicePool->next()) {
            if (!pVoice->pDiskThread) {
                dmsg(0,("Engine -> voice::trigger: !pDiskThread\n"));
                exit(EXIT_FAILURE);
            }
        }
    }

    void Engine::DisconnectAudioOutputDevice() {
        if (pAudioOutputDevice) { // if clause to prevent disconnect loops
            AudioOutputDevice* olddevice = pAudioOutputDevice;
            pAudioOutputDevice = NULL;
            olddevice->Disconnect(this);
            AudioDeviceChannelLeft  = -1;
            AudioDeviceChannelRight = -1;
        }
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
    int Engine::RenderAudio(uint Samples) {
        dmsg(5,("RenderAudio(Samples=%d)\n", Samples));

        // return if no instrument loaded or engine disabled
        if (EngineDisabled.Pop()) {
            dmsg(5,("gig::Engine: engine disabled (val=%d)\n",EngineDisabled.GetUnsafe()));
            return 0;
        }
        if (!pInstrument) {
            dmsg(5,("gig::Engine: no instrument loaded\n"));
            return 0;
        }


        // empty the event lists for the new fragment
        pEvents->clear();
        pCCEvents->clear();
        for (uint i = 0; i < Event::destination_count; i++) {
            pSynthesisEvents[i]->clear();
        }

        // read and copy events from input queue
        Event event = pEventGenerator->CreateEvent();
        while (true) {
            if (!pEventQueue->pop(&event)) break;
            pEvents->alloc_assign(event);
        }


        // update time of start and end of this audio fragment (as events' time stamps relate to this)
        pEventGenerator->UpdateFragmentTime(Samples);


        // process events
        Event* pNextEvent = pEvents->first();
        while (pNextEvent) {
            Event* pEvent = pNextEvent;
            pEvents->set_current(pEvent);
            pNextEvent = pEvents->next();
            switch (pEvent->Type) {
                case Event::type_note_on:
                    dmsg(5,("Engine: Note on received\n"));
                    ProcessNoteOn(pEvent);
                    break;
                case Event::type_note_off:
                    dmsg(5,("Engine: Note off received\n"));
                    ProcessNoteOff(pEvent);
                    break;
                case Event::type_control_change:
                    dmsg(5,("Engine: MIDI CC received\n"));
                    ProcessControlChange(pEvent);
                    break;
                case Event::type_pitchbend:
                    dmsg(5,("Engine: Pitchbend received\n"));
                    ProcessPitchbend(pEvent);
                    break;
                case Event::type_sysex:
                    dmsg(5,("Engine: Sysex received\n"));
                    ProcessSysex(pEvent);
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
                    KillVoiceImmediately(pVoice); // remove voice from the list of active voices
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
    void Engine::SendNoteOn(uint8_t Key, uint8_t Velocity) {
        Event event    = pEventGenerator->CreateEvent();
        event.Type     = Event::type_note_on;
        event.Key      = Key;
        event.Velocity = Velocity;
        if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
        else dmsg(1,("Engine: Input event queue full!"));
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread to release
     *  voice(s) on the given key.
     *
     *  @param Key      - MIDI key number of the released key
     *  @param Velocity - MIDI release velocity value of the released key
     */
    void Engine::SendNoteOff(uint8_t Key, uint8_t Velocity) {
        Event event    = pEventGenerator->CreateEvent();
        event.Type     = Event::type_note_off;
        event.Key      = Key;
        event.Velocity = Velocity;
        if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
        else dmsg(1,("Engine: Input event queue full!"));
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread to change
     *  the pitch value for all voices.
     *
     *  @param Pitch - MIDI pitch value (-8192 ... +8191)
     */
    void Engine::SendPitchbend(int Pitch) {
        Event event = pEventGenerator->CreateEvent();
        event.Type  = Event::type_pitchbend;
        event.Pitch = Pitch;
        if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
        else dmsg(1,("Engine: Input event queue full!"));
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread that a
     *  continuous controller value has changed.
     *
     *  @param Controller - MIDI controller number of the occured control change
     *  @param Value      - value of the control change
     */
    void Engine::SendControlChange(uint8_t Controller, uint8_t Value) {
        Event event      = pEventGenerator->CreateEvent();
        event.Type       = Event::type_control_change;
        event.Controller = Controller;
        event.Value      = Value;
        if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
        else dmsg(1,("Engine: Input event queue full!"));
    }

    /**
     *  Will be called by the MIDI input device whenever a MIDI system
     *  exclusive message has arrived.
     *
     *  @param pData - pointer to sysex data
     *  @param Size  - lenght of sysex data (in bytes)
     */
    void Engine::SendSysex(void* pData, uint Size) {
        Event event = pEventGenerator->CreateEvent();
        event.Type  = Event::type_sysex;
        event.Size  = Size;
        if (pEventQueue->write_space() > 0) {
            if (pSysexBuffer->write_space() >= Size) {
                // copy sysex data to input buffer
                uint toWrite = Size;
                uint8_t* pPos = (uint8_t*) pData;
                while (toWrite) {
                    const uint writeNow = RTMath::Min(toWrite, pSysexBuffer->write_space_to_end());
                    pSysexBuffer->write(pPos, writeNow);
                    toWrite -= writeNow;
                    pPos    += writeNow;

                }
                // finally place sysex event into input event queue
                pEventQueue->push(&event);
            }
            else dmsg(1,("Engine: Sysex message too large (%d byte) for input buffer (%d byte)!",Size,SYSEX_BUFFER_SIZE));
        }
        else dmsg(1,("Engine: Input event queue full!"));
    }

    /**
     *  Assigns and triggers a new voice for the respective MIDI key.
     *
     *  @param pNoteOnEvent - key, velocity and time stamp of the event
     */
    void Engine::ProcessNoteOn(Event* pNoteOnEvent) {
        midi_key_info_t* pKey = &pMIDIKeyInfo[pNoteOnEvent->Key];

        pKey->KeyPressed = true; // the MIDI key was now pressed down

        // cancel release process of voices on this key if needed
        if (pKey->Active && !SustainPedal) {
            Event* pCancelReleaseEvent = pKey->pEvents->alloc();
            if (pCancelReleaseEvent) {
                *pCancelReleaseEvent = *pNoteOnEvent;
                pCancelReleaseEvent->Type = Event::type_cancel_release; // transform event type
            }
            else dmsg(1,("Event pool emtpy!\n"));
        }

        // allocate and trigger a new voice for the key
        LaunchVoice(pNoteOnEvent);

        // finally move note on event to the key's own event list
        pEvents->move(pNoteOnEvent, pKey->pEvents);
    }

    /**
     *  Releases the voices on the given key if sustain pedal is not pressed.
     *  If sustain is pressed, the release of the note will be postponed until
     *  sustain pedal will be released or voice turned inactive by itself (e.g.
     *  due to completion of sample playback).
     *
     *  @param pNoteOffEvent - key, velocity and time stamp of the event
     */
    void Engine::ProcessNoteOff(Event* pNoteOffEvent) {
        midi_key_info_t* pKey = &pMIDIKeyInfo[pNoteOffEvent->Key];

        pKey->KeyPressed = false; // the MIDI key was now released

        // release voices on this key if needed
        if (pKey->Active && !SustainPedal) {
            pNoteOffEvent->Type = Event::type_release; // transform event type
        }

        // spawn release triggered voice(s) if needed
        if (pKey->ReleaseTrigger) {
            LaunchVoice(pNoteOffEvent, 0, true);
            pKey->ReleaseTrigger = false;
        }

        // move event to the key's own event list
        pEvents->move(pNoteOffEvent, pKey->pEvents);
    }

    /**
     *  Moves pitchbend event from the general (input) event list to the pitch
     *  event list.
     *
     *  @param pPitchbendEvent - absolute pitch value and time stamp of the event
     */
    void Engine::ProcessPitchbend(Event* pPitchbendEvent) {
        this->Pitch = pPitchbendEvent->Pitch; // store current pitch value
        pEvents->move(pPitchbendEvent, pSynthesisEvents[Event::destination_vco]);
    }

    /**
     *  Allocates and triggers a new voice. This method will usually be
     *  called by the ProcessNoteOn() method and by the voices itself
     *  (e.g. to spawn further voices on the same key for layered sounds).
     *
     *  @param pNoteOnEvent        - key, velocity and time stamp of the event
     *  @param iLayer              - layer index for the new voice (optional - only
     *                               in case of layered sounds of course)
     *  @param ReleaseTriggerVoice - if new voice is a release triggered voice
     *                               (optional, default = false)
     */
    void Engine::LaunchVoice(Event* pNoteOnEvent, int iLayer, bool ReleaseTriggerVoice) {
        midi_key_info_t* pKey = &pMIDIKeyInfo[pNoteOnEvent->Key];

        // allocate a new voice for the key
        Voice* pNewVoice = pKey->pActiveVoices->alloc();
        if (pNewVoice) {
            // launch the new voice
            if (pNewVoice->Trigger(pNoteOnEvent, this->Pitch, this->pInstrument, iLayer, ReleaseTriggerVoice) < 0) {
                dmsg(1,("Triggering new voice failed!\n"));
                pKey->pActiveVoices->free(pNewVoice);
            }
            else { // on success
                uint** ppKeyGroup = NULL;
                if (pNewVoice->KeyGroup) { // if this voice / key belongs to a key group
                    ppKeyGroup = &ActiveKeyGroups[pNewVoice->KeyGroup];
                    if (*ppKeyGroup) { // if there's already an active key in that key group
                        midi_key_info_t* pOtherKey = &pMIDIKeyInfo[**ppKeyGroup];
                        // kill all voices on the (other) key
                        Voice* pVoiceToBeKilled = pOtherKey->pActiveVoices->first();
                        while (pVoiceToBeKilled) {
                            Voice* pVoiceToBeKilledNext = pOtherKey->pActiveVoices->next();
                            if (pVoiceToBeKilled->Type != Voice::type_release_trigger) pVoiceToBeKilled->Kill(pNoteOnEvent);
                            pOtherKey->pActiveVoices->set_current(pVoiceToBeKilled);
                            pVoiceToBeKilled = pVoiceToBeKilledNext;
                        }
                    }
                }
                if (!pKey->Active) { // mark as active key
                    pKey->Active = true;
                    pKey->pSelf  = pActiveKeys->alloc();
                    *pKey->pSelf = pNoteOnEvent->Key;
                }
                if (pNewVoice->KeyGroup) {
                    *ppKeyGroup = pKey->pSelf; // put key as the (new) active key to its key group
                }
                if (pNewVoice->Type == Voice::type_release_trigger_required) pKey->ReleaseTrigger = true; // mark key for the need of release triggered voice(s)
            }
        }
        else std::cerr << "No free voice!" << std::endl << std::flush;
    }

    /**
     *  Immediately kills the voice given with pVoice (no matter if sustain is
     *  pressed or not) and removes it from the MIDI key's list of active voice.
     *  This method will e.g. be called if a voice went inactive by itself.
     *
     *  @param pVoice - points to the voice to be killed
     */
    void Engine::KillVoiceImmediately(Voice* pVoice) {
        if (pVoice) {
            if (pVoice->IsActive()) pVoice->KillImmediately();

            midi_key_info_t* pKey = &pMIDIKeyInfo[pVoice->MIDIKey];

            // free the voice object
            pVoicePool->free(pVoice);

            // check if there are no voices left on the MIDI key and update the key info if so
            if (pKey->pActiveVoices->is_empty()) {
                if (pVoice->KeyGroup) { // if voice / key belongs to a key group
                    uint** ppKeyGroup = &ActiveKeyGroups[pVoice->KeyGroup];
                    if (*ppKeyGroup == pKey->pSelf) *ppKeyGroup = NULL; // remove key from key group
                }
                pKey->Active = false;
                pActiveKeys->free(pKey->pSelf); // remove key from list of active keys
                pKey->pSelf = NULL;
                pKey->ReleaseTrigger = false;
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
    void Engine::ProcessControlChange(Event* pControlChangeEvent) {
        dmsg(4,("Engine::ContinuousController cc=%d v=%d\n", pControlChangeEvent->Controller, pControlChangeEvent->Value));

        switch (pControlChangeEvent->Controller) {
            case 64: {
                if (pControlChangeEvent->Value >= 64 && !SustainPedal) {
                    dmsg(4,("PEDAL DOWN\n"));
                    SustainPedal = true;

                    // cancel release process of voices if necessary
                    uint* piKey = pActiveKeys->first();
                    if (piKey) {
                        pControlChangeEvent->Type = Event::type_cancel_release; // transform event type
                        while (piKey) {
                            midi_key_info_t* pKey = &pMIDIKeyInfo[*piKey];
                            pActiveKeys->set_current(piKey);
                            piKey = pActiveKeys->next();
                            if (!pKey->KeyPressed) {
                                Event* pNewEvent = pKey->pEvents->alloc();
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
                        pControlChangeEvent->Type = Event::type_release; // transform event type
                        while (piKey) {
                            midi_key_info_t* pKey = &pMIDIKeyInfo[*piKey];
                            pActiveKeys->set_current(piKey);
                            piKey = pActiveKeys->next();
                            if (!pKey->KeyPressed) {
                                Event* pNewEvent = pKey->pEvents->alloc();
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
     *  Reacts on MIDI system exclusive messages.
     *
     *  @param pSysexEvent - sysex data size and time stamp of the sysex event
     */
    void Engine::ProcessSysex(Event* pSysexEvent) {
        RingBuffer<uint8_t>::NonVolatileReader reader = pSysexBuffer->get_non_volatile_reader();

        uint8_t exclusive_status, id;
        if (!reader.pop(&exclusive_status)) goto free_sysex_data;
        if (!reader.pop(&id))               goto free_sysex_data;
        if (exclusive_status != 0xF0)       goto free_sysex_data;

        switch (id) {
            case 0x41: { // Roland
                uint8_t device_id, model_id, cmd_id;
                if (!reader.pop(&device_id)) goto free_sysex_data;
                if (!reader.pop(&model_id))  goto free_sysex_data;
                if (!reader.pop(&cmd_id))    goto free_sysex_data;
                if (model_id != 0x42 /*GS*/) goto free_sysex_data;
                if (cmd_id != 0x12 /*DT1*/)  goto free_sysex_data;

                // command address
                uint8_t addr[3]; // 2 byte addr MSB, followed by 1 byte addr LSB)
                const RingBuffer<uint8_t>::NonVolatileReader checksum_reader = reader; // so we can calculate the check sum later
                if (reader.read(&addr[0], 3) != 3) goto free_sysex_data;
                if (addr[0] == 0x40 && addr[1] == 0x00) { // System Parameters
                }
                else if (addr[0] == 0x40 && addr[1] == 0x01) { // Common Parameters
                }
                else if (addr[0] == 0x40 && (addr[1] & 0xf0) == 0x10) { // Part Parameters (1)
                    switch (addr[3]) {
                        case 0x40: { // scale tuning
                            uint8_t scale_tunes[12]; // detuning of all 12 semitones of an octave
                            if (reader.read(&scale_tunes[0], 12) != 12) goto free_sysex_data;
                            uint8_t checksum;
                            if (!reader.pop(&checksum))                      goto free_sysex_data;
                            if (GSCheckSum(checksum_reader, 12) != checksum) goto free_sysex_data;
                            for (int i = 0; i < 12; i++) scale_tunes[i] -= 64;
                            AdjustScale((int8_t*) scale_tunes);
                            break;
                        }
                    }
                }
                else if (addr[0] == 0x40 && (addr[1] & 0xf0) == 0x20) { // Part Parameters (2)
                }
                else if (addr[0] == 0x41) { // Drum Setup Parameters
                }
                break;
            }
        }

        free_sysex_data: // finally free sysex data
        pSysexBuffer->increment_read_ptr(pSysexEvent->Size);
    }

    /**
     * Calculates the Roland GS sysex check sum.
     *
     * @param AddrReader - reader which currently points to the first GS
     *                     command address byte of the GS sysex message in
     *                     question
     * @param DataSize   - size of the GS message data (in bytes)
     */
    uint8_t Engine::GSCheckSum(const RingBuffer<uint8_t>::NonVolatileReader AddrReader, uint DataSize) {
        RingBuffer<uint8_t>::NonVolatileReader reader = AddrReader;
        uint bytes = 3 /*addr*/ + DataSize;
        uint8_t addr_and_data[bytes];
        reader.read(&addr_and_data[0], bytes);
        uint8_t sum = 0;
        for (uint i = 0; i < bytes; i++) sum += addr_and_data[i];
        return 128 - sum % 128;
    }

    /**
     * Allows to tune each of the twelve semitones of an octave.
     *
     * @param ScaleTunes - detuning of all twelve semitones (in cents)
     */
    void Engine::AdjustScale(int8_t ScaleTunes[12]) {
        memcpy(&this->ScaleTuning[0], &ScaleTunes[0], 12); //TODO: currently not sample accurate
    }

    /**
     * Initialize the parameter sequence for the modulation destination given by
     * by 'dst' with the constant value given by val.
     */
    void Engine::ResetSynthesisParameters(Event::destination_t dst, float val) {
        int maxsamples = pAudioOutputDevice->MaxSamplesPerCycle();
        float* m = &pSynthesisParameters[dst][0];
        for (int i = 0; i < maxsamples; i += 4) {
           m[i]   = val;
           m[i+1] = val;
           m[i+2] = val;
           m[i+3] = val;
        }
    }

    float Engine::Volume() {
        return GlobalVolume;
    }

    void Engine::Volume(float f) {
        GlobalVolume = f;
    }

    uint Engine::Channels() {
        return 2;
    }

    void Engine::SetOutputChannel(uint EngineAudioChannel, uint AudioDeviceChannel) {
        AudioChannel* pChannel = pAudioOutputDevice->Channel(AudioDeviceChannel);
        if (!pChannel) throw AudioOutputException("Invalid audio output device channel " + ToString(AudioDeviceChannel));
        switch (EngineAudioChannel) {
            case 0: // left output channel
                pOutputLeft = pChannel->Buffer();
                AudioDeviceChannelLeft = AudioDeviceChannel;
                break;
            case 1: // right output channel
                pOutputRight = pChannel->Buffer();
                AudioDeviceChannelRight = AudioDeviceChannel;
                break;
            default:
                throw AudioOutputException("Invalid engine audio channel " + ToString(EngineAudioChannel));
        }
    }

    int Engine::OutputChannel(uint EngineAudioChannel) {
        switch (EngineAudioChannel) {
            case 0: // left channel
                return AudioDeviceChannelLeft;
            case 1: // right channel
                return AudioDeviceChannelRight;
            default:
                throw AudioOutputException("Invalid engine audio channel " + ToString(EngineAudioChannel));
        }
    }

    uint Engine::VoiceCount() {
        return ActiveVoiceCount;
    }

    uint Engine::VoiceCountMax() {
        return ActiveVoiceCountMax;
    }

    bool Engine::DiskStreamSupported() {
        return true;
    }

    uint Engine::DiskStreamCount() {
        return (pDiskThread) ? pDiskThread->ActiveStreamCount : 0;
    }

    uint Engine::DiskStreamCountMax() {
        return (pDiskThread) ? pDiskThread->ActiveStreamCountMax : 0;
    }

    String Engine::DiskStreamBufferFillBytes() {
        return pDiskThread->GetBufferFillBytes();
    }

    String Engine::DiskStreamBufferFillPercentage() {
        return pDiskThread->GetBufferFillPercentage();
    }

    String Engine::EngineName() {
        return "GigEngine";
    }

    String Engine::InstrumentFileName() {
        return InstrumentFile;
    }

    int Engine::InstrumentIndex() {
        return InstrumentIdx;
    }

    int Engine::InstrumentStatus() {
        return InstrumentStat;
    }

    String Engine::Description() {
        return "Gigasampler Engine";
    }

    String Engine::Version() {
        String s = "$Revision: 1.12 $";
        return s.substr(11, s.size() - 13); // cut dollar signs, spaces and CVS macro keyword
    }

}} // namespace LinuxSampler::gig
