/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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

#include "EngineChannel.h"

namespace LinuxSampler { namespace gig {    

    EngineChannel::EngineChannel() {
        pMIDIKeyInfo = new midi_key_info_t[128];
        pEngine      = NULL;
        pInstrument  = NULL;
        pEventQueue  = new RingBuffer<Event>(MAX_EVENTS_PER_FRAGMENT, 0);        
        pActiveKeys  = new Pool<uint>(128);
        for (uint i = 0; i < 128; i++) {
            pMIDIKeyInfo[i].pActiveVoices  = NULL; // we allocate when we retrieve the right Engine object
            pMIDIKeyInfo[i].KeyPressed     = false;
            pMIDIKeyInfo[i].Active         = false;
            pMIDIKeyInfo[i].ReleaseTrigger = false;
            pMIDIKeyInfo[i].pEvents        = NULL; // we allocate when we retrieve the right Engine object
        }
        InstrumentIdx  = -1;
        InstrumentStat = -1;
        AudioDeviceChannelLeft  = -1;
        AudioDeviceChannelRight = -1;
    }

    EngineChannel::~EngineChannel() {
        if (pInstrument) Engine::instruments.HandBack(pInstrument, this);
        for (uint i = 0; i < 128; i++) {
            if (pMIDIKeyInfo[i].pActiveVoices) {
                pMIDIKeyInfo[i].pActiveVoices->clear();
                delete pMIDIKeyInfo[i].pActiveVoices;
            }
            if (pMIDIKeyInfo[i].pEvents) {
                pMIDIKeyInfo[i].pEvents->clear();
                delete pMIDIKeyInfo[i].pEvents;
            }
        }
        if (pEventQueue) delete pEventQueue;
        if (pActiveKeys) delete pActiveKeys;
        if (pMIDIKeyInfo) delete[] pMIDIKeyInfo;
    }

    /**
     * This method is not thread safe!
     */
    void EngineChannel::ResetInternal() {
        Pitch               = 0;
        SustainPedal        = false;
        GlobalVolume        = 1.0;
        CurrentKeyDimension = 0;

        // set all MIDI controller values to zero
        memset(ControllerTable, 0x00, 128);

        // reset key info
        for (uint i = 0; i < 128; i++) {
            if (pMIDIKeyInfo[i].pActiveVoices)
                pMIDIKeyInfo[i].pActiveVoices->clear();
            if (pMIDIKeyInfo[i].pEvents)
                pMIDIKeyInfo[i].pEvents->clear();
            pMIDIKeyInfo[i].KeyPressed     = false;
            pMIDIKeyInfo[i].Active         = false;
            pMIDIKeyInfo[i].ReleaseTrigger = false;
            pMIDIKeyInfo[i].itSelf         = Pool<uint>::Iterator();
        }

        // reset all key groups
        std::map<uint,uint*>::iterator iter = ActiveKeyGroups.begin();
        for (; iter != ActiveKeyGroups.end(); iter++) iter->second = NULL;

        // free all active keys
        pActiveKeys->clear();

        // delete all input events
        pEventQueue->init();

        if (pEngine) pEngine->ResetInternal();
    }

    int EngineChannel::RenderAudio(uint Samples) {
        return (pEngine) ? pEngine->RenderAudio(this, Samples) : 0;
    }

    LinuxSampler::Engine* EngineChannel::GetEngine() {
        return pEngine;
    }

    /**
     * More or less a workaround to set the instrument name, index and load
     * status variable to zero percent immediately, that is without blocking
     * the calling thread. It might be used in future for other preparations
     * as well though.
     *
     * @param FileName   - file name of the Gigasampler instrument file
     * @param Instrument - index of the instrument in the .gig file
     * @see LoadInstrument()
     */
    void EngineChannel::PrepareLoadInstrument(const char* FileName, uint Instrument) {
        InstrumentFile = FileName;
        InstrumentIdx  = Instrument;
        InstrumentStat = 0;
    }

    /**
     * Load an instrument from a .gig file. PrepareLoadInstrument() has to
     * be called first to provide the information which instrument to load.
     * This method will then actually start to load the instrument and block
     * the calling thread until loading was completed.
     *
     * @returns detailed description of the method call result
     * @see PrepareLoadInstrument()
     */
    void EngineChannel::LoadInstrument() {

        if (pEngine) pEngine->DisableAndLock();
        
        ResetInternal();
        
        // free old instrument
        if (pInstrument) {
            // give old instrument back to instrument manager
            Engine::instruments.HandBack(pInstrument, this);
        }

        // delete all key groups
        ActiveKeyGroups.clear();

        // request gig instrument from instrument manager
        try {
            instrument_id_t instrid;
            instrid.FileName    = InstrumentFile;
            instrid.iInstrument = InstrumentIdx;
            pInstrument = Engine::instruments.Borrow(instrid, this);
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

        InstrumentIdxName = pInstrument->pInfo->Name;
        InstrumentStat = 100;

        // inform audio driver for the need of two channels
        try {
            if (pEngine && pEngine->pAudioOutputDevice)
                pEngine->pAudioOutputDevice->AcquireChannels(2); // gig Engine only stereo
        }
        catch (AudioOutputException e) {
            String msg = "Audio output device unable to provide 2 audio channels, cause: " + e.Message();
            throw LinuxSamplerException(msg);
        }

        if (pEngine) pEngine->Enable();
    }

    /**
     * Will be called by the InstrumentResourceManager when the instrument
     * we are currently using in this engine is going to be updated, so we
     * can stop playback before that happens.
     */
    void EngineChannel::ResourceToBeUpdated(::gig::Instrument* pResource, void*& pUpdateArg) {
        dmsg(3,("gig::Engine: Received instrument update message.\n"));
        if (pEngine) pEngine->DisableAndLock();
        ResetInternal();
        this->pInstrument = NULL;
    }

    /**
     * Will be called by the InstrumentResourceManager when the instrument
     * update process was completed, so we can continue with playback.
     */
    void EngineChannel::ResourceUpdated(::gig::Instrument* pOldResource, ::gig::Instrument* pNewResource, void* pUpdateArg) {
        this->pInstrument = pNewResource; //TODO: there are couple of engine parameters we should update here as well if the instrument was updated (see LoadInstrument())
        if (pEngine) pEngine->Enable();
    }

    void EngineChannel::Connect(AudioOutputDevice* pAudioOut) {        
        pEngine = Engine::AcquireEngine(this, pAudioOut);
        ResetInternal();        
        for (uint i = 0; i < 128; i++) {
            pMIDIKeyInfo[i].pActiveVoices = new RTList<Voice>(pEngine->pVoicePool);
            pMIDIKeyInfo[i].pEvents       = new RTList<Event>(pEngine->pEventPool);
        }
        AudioDeviceChannelLeft  = 0;
        AudioDeviceChannelRight = 1;
        pOutputLeft             = pAudioOut->Channel(0)->Buffer();
        pOutputRight            = pAudioOut->Channel(1)->Buffer();
    }

    void EngineChannel::DisconnectAudioOutputDevice() {
        if (pEngine) { // if clause to prevent disconnect loops
            ResetInternal();
            for (uint i = 0; i < 128; i++) {
                if (pMIDIKeyInfo[i].pActiveVoices) delete pMIDIKeyInfo[i].pActiveVoices;
                if (pMIDIKeyInfo[i].pEvents)       delete pMIDIKeyInfo[i].pEvents;
            }
            Engine* oldEngine = pEngine;
            AudioOutputDevice* oldAudioDevice = pEngine->pAudioOutputDevice;
            pEngine = NULL;
            Engine::FreeEngine(this, oldAudioDevice);
            AudioDeviceChannelLeft  = -1;
            AudioDeviceChannelRight = -1;
            oldAudioDevice->Disconnect(this);
        }
    }

    void EngineChannel::SetOutputChannel(uint EngineAudioChannel, uint AudioDeviceChannel) {
        if (!pEngine || !pEngine->pAudioOutputDevice) throw AudioOutputException("No audio output device connected yet.");
        
        AudioChannel* pChannel = pEngine->pAudioOutputDevice->Channel(AudioDeviceChannel);
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

    int EngineChannel::OutputChannel(uint EngineAudioChannel) {
        switch (EngineAudioChannel) {
            case 0: // left channel
                return AudioDeviceChannelLeft;
            case 1: // right channel
                return AudioDeviceChannelRight;
            default:
                throw AudioOutputException("Invalid engine audio channel " + ToString(EngineAudioChannel));
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to let the audio thread trigger a new
     *  voice for the given key.
     *
     *  @param Key      - MIDI key number of the triggered key
     *  @param Velocity - MIDI velocity value of the triggered key
     */
    void EngineChannel::SendNoteOn(uint8_t Key, uint8_t Velocity) {
        if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent();
            event.Type                = Event::type_note_on;
            event.Param.Note.Key      = Key;
            event.Param.Note.Velocity = Velocity;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("Engine: Input event queue full!"));
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread to release
     *  voice(s) on the given key.
     *
     *  @param Key      - MIDI key number of the released key
     *  @param Velocity - MIDI release velocity value of the released key
     */
    void EngineChannel::SendNoteOff(uint8_t Key, uint8_t Velocity) {
        if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent();
            event.Type                = Event::type_note_off;
            event.Param.Note.Key      = Key;
            event.Param.Note.Velocity = Velocity;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("Engine: Input event queue full!"));
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread to change
     *  the pitch value for all voices.
     *
     *  @param Pitch - MIDI pitch value (-8192 ... +8191)
     */
    void EngineChannel::SendPitchbend(int Pitch) {
        if (pEngine) {        
            Event event             = pEngine->pEventGenerator->CreateEvent();
            event.Type              = Event::type_pitchbend;
            event.Param.Pitch.Pitch = Pitch;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("Engine: Input event queue full!"));
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread that a
     *  continuous controller value has changed.
     *
     *  @param Controller - MIDI controller number of the occured control change
     *  @param Value      - value of the control change
     */
    void EngineChannel::SendControlChange(uint8_t Controller, uint8_t Value) {
        if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent();
            event.Type                = Event::type_control_change;
            event.Param.CC.Controller = Controller;
            event.Param.CC.Value      = Value;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("Engine: Input event queue full!"));
        }
    }

    float EngineChannel::Volume() {
        return GlobalVolume;
    }

    void EngineChannel::Volume(float f) {
        GlobalVolume = f;
    }

    uint EngineChannel::Channels() {
        return 2;
    }

    String EngineChannel::InstrumentFileName() {
        return InstrumentFile;
    }

    String EngineChannel::InstrumentName() {
        return InstrumentIdxName;
    }

    int EngineChannel::InstrumentIndex() {
        return InstrumentIdx;
    }

    int EngineChannel::InstrumentStatus() {
        return InstrumentStat;
    }    

}} // namespace LinuxSampler::gig
