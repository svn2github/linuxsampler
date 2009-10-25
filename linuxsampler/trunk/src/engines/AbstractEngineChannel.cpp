/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003,2004 by Benno Senoner and Christian Schoenebeck    *
 *   Copyright (C) 2005-2009 Christian Schoenebeck                         *
 *   Copyright (C) 2009 Grigor Iliev                                       *
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

#include "AbstractEngineChannel.h"
#include "../common/global_private.h"
#include "../Sampler.h"

namespace LinuxSampler {

    AbstractEngineChannel::AbstractEngineChannel() :
        virtualMidiDevicesReader_AudioThread(virtualMidiDevices),
        virtualMidiDevicesReader_MidiThread(virtualMidiDevices)
    {
        pEngine      = NULL;
        pEvents      = NULL; // we allocate when we retrieve the right Engine object
        pEventQueue  = new RingBuffer<Event,false>(CONFIG_MAX_EVENTS_PER_FRAGMENT, 0);
        InstrumentIdx  = -1;
        InstrumentStat = -1;
        pChannelLeft  = NULL;
        pChannelRight = NULL;
        AudioDeviceChannelLeft  = -1;
        AudioDeviceChannelRight = -1;
        pMidiInputPort = NULL;
        midiChannel = midi_chan_all;
        ResetControllers();
        PortamentoMode = false;
        PortamentoTime = CONFIG_PORTAMENTO_TIME_DEFAULT;
    }

    AbstractEngineChannel::~AbstractEngineChannel() {
        
        if (pEventQueue) delete pEventQueue;
        RemoveAllFxSends();
    }

    Engine* AbstractEngineChannel::GetEngine() {
        return pEngine;
    }

    uint AbstractEngineChannel::Channels() {
        return 2;
    }

    /**
     * More or less a workaround to set the instrument name, index and load
     * status variable to zero percent immediately, that is without blocking
     * the calling thread. It might be used in future for other preparations
     * as well though.
     *
     * @param FileName   - file name of the instrument file
     * @param Instrument - index of the instrument in the file
     * @see LoadInstrument()
     */
    void AbstractEngineChannel::PrepareLoadInstrument(const char* FileName, uint Instrument) {
        InstrumentFile = FileName;
        InstrumentIdx  = Instrument;
        InstrumentStat = 0;
    }

    String AbstractEngineChannel::InstrumentFileName() {
        return InstrumentFile;
    }

    String AbstractEngineChannel::InstrumentName() {
        return InstrumentIdxName;
    }

    int AbstractEngineChannel::InstrumentIndex() {
        return InstrumentIdx;
    }

    int AbstractEngineChannel::InstrumentStatus() {
        return InstrumentStat;
    }

    String AbstractEngineChannel::EngineName() {
        return AbstractEngine::GetFormatString(GetEngineFormat());
    }

    void AbstractEngineChannel::Reset() {
        if (pEngine) pEngine->DisableAndLock();
        ResetInternal();
        ResetControllers();
        if (pEngine) {
            pEngine->Enable();
            pEngine->Reset();
        }
    }

    void AbstractEngineChannel::ResetControllers() {
        Pitch          = 0;
        GlobalVolume   = 1.0f;
        MidiVolume     = 1.0;
        GlobalPanLeft  = 1.0f;
        GlobalPanRight = 1.0f;
        iLastPanRequest = 64;
        GlobalTranspose = 0;
        // set all MIDI controller values to zero
        memset(ControllerTable, 0x00, 129);
        // reset all FX Send levels
        for (
            std::vector<FxSend*>::iterator iter = fxSends.begin();
            iter != fxSends.end(); iter++
        ) {
            (*iter)->Reset();
        }
    }

    /**
     * This method is not thread safe!
     */
    void AbstractEngineChannel::ResetInternal() {
        CurrentKeyDimension = 0;
        PortamentoPos = -1.0f; // no portamento active yet

        // delete all input events
        pEventQueue->init();

        if (pEngine) pEngine->ResetInternal();

        // status of engine channel has changed, so set notify flag
        bStatusChanged = true;
    }

    /**
     * Implementation of virtual method from abstract EngineChannel interface.
     * This method will periodically be polled (e.g. by the LSCP server) to
     * check if some engine channel parameter has changed since the last
     * StatusChanged() call.
     *
     * This method can also be used to mark the engine channel as changed
     * from outside, e.g. by a MIDI input device. The optional argument
     * \a nNewStatus can be used for this.
     *
     * TODO: This "poll method" is just a lazy solution and might be
     *       replaced in future.
     * @param bNewStatus - (optional, default: false) sets the new status flag
     * @returns true if engine channel status has changed since last
     *          StatusChanged() call
     */
    bool AbstractEngineChannel::StatusChanged(bool bNewStatus) {
        bool b = bStatusChanged;
        bStatusChanged = bNewStatus;
        return b;
    }

    float AbstractEngineChannel::Volume() {
        return GlobalVolume;
    }

    void AbstractEngineChannel::Volume(float f) {
        GlobalVolume = f;
        bStatusChanged = true; // status of engine channel has changed, so set notify flag
    }

    float AbstractEngineChannel::Pan() {
        return float(iLastPanRequest - 64) / 64.0f;
    }

    void AbstractEngineChannel::Pan(float f) {
        int iMidiPan = int(f * 64.0f) + 64;
        if (iMidiPan > 127) iMidiPan = 127;
        else if (iMidiPan < 0) iMidiPan = 0;
        GlobalPanLeft  = AbstractEngine::PanCurve[128 - iMidiPan];
        GlobalPanRight = AbstractEngine::PanCurve[iMidiPan];
        iLastPanRequest = iMidiPan;
    }

    AudioOutputDevice* AbstractEngineChannel::GetAudioOutputDevice() {
        return (pEngine) ? pEngine->pAudioOutputDevice : NULL;
    }

    void AbstractEngineChannel::SetOutputChannel(uint EngineAudioChannel, uint AudioDeviceChannel) {
        if (!pEngine || !pEngine->pAudioOutputDevice) throw AudioOutputException("No audio output device connected yet.");

        AudioChannel* pChannel = pEngine->pAudioOutputDevice->Channel(AudioDeviceChannel);
        if (!pChannel) throw AudioOutputException("Invalid audio output device channel " + ToString(AudioDeviceChannel));
        switch (EngineAudioChannel) {
            case 0: // left output channel
                if (fxSends.empty()) pChannelLeft = pChannel;
                AudioDeviceChannelLeft = AudioDeviceChannel;
                break;
            case 1: // right output channel
                if (fxSends.empty()) pChannelRight = pChannel;
                AudioDeviceChannelRight = AudioDeviceChannel;
                break;
            default:
                throw AudioOutputException("Invalid engine audio channel " + ToString(EngineAudioChannel));
        }

        bStatusChanged = true;
    }

    int AbstractEngineChannel::OutputChannel(uint EngineAudioChannel) {
        switch (EngineAudioChannel) {
            case 0: // left channel
                return AudioDeviceChannelLeft;
            case 1: // right channel
                return AudioDeviceChannelRight;
            default:
                throw AudioOutputException("Invalid engine audio channel " + ToString(EngineAudioChannel));
        }
    }

    void AbstractEngineChannel::Connect(MidiInputPort* pMidiPort, midi_chan_t MidiChannel) {
        if (!pMidiPort || pMidiPort == this->pMidiInputPort) return;
        DisconnectMidiInputPort();
        this->pMidiInputPort = pMidiPort;
        this->midiChannel    = MidiChannel;
        pMidiPort->Connect(this, MidiChannel);
    }

    void AbstractEngineChannel::DisconnectMidiInputPort() {
        MidiInputPort* pOldPort = this->pMidiInputPort;
        this->pMidiInputPort = NULL;
        if (pOldPort) pOldPort->Disconnect(this);
    }

    MidiInputPort* AbstractEngineChannel::GetMidiInputPort() {
        return pMidiInputPort;
    }

    midi_chan_t AbstractEngineChannel::MidiChannel() {
        return midiChannel;
    }

    void AbstractEngineChannel::Connect(VirtualMidiDevice* pDevice) {
        // double buffer ... double work ...
        {
            ArrayList<VirtualMidiDevice*>& devices = virtualMidiDevices.GetConfigForUpdate();
            devices.add(pDevice);
        }
        {
            ArrayList<VirtualMidiDevice*>& devices = virtualMidiDevices.SwitchConfig();
            devices.add(pDevice);
        }
    }

    void AbstractEngineChannel::Disconnect(VirtualMidiDevice* pDevice) {
        // double buffer ... double work ...
        {
            ArrayList<VirtualMidiDevice*>& devices = virtualMidiDevices.GetConfigForUpdate();
            devices.remove(pDevice);
        }
        {
            ArrayList<VirtualMidiDevice*>& devices = virtualMidiDevices.SwitchConfig();
            devices.remove(pDevice);
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to let the audio thread trigger a new
     *  voice for the given key. This method is meant for real time rendering,
     *  that is an event will immediately be created with the current system
     *  time as time stamp.
     *
     *  @param Key      - MIDI key number of the triggered key
     *  @param Velocity - MIDI velocity value of the triggered key
     */
    void AbstractEngineChannel::SendNoteOn(uint8_t Key, uint8_t Velocity) {
        if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent();
            event.Type                = Event::type_note_on;
            event.Param.Note.Key      = Key;
            event.Param.Note.Velocity = Velocity;
            event.pEngineChannel      = this;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("EngineChannel: Input event queue full!"));
            // inform connected virtual MIDI devices if any ...
            // (e.g. virtual MIDI keyboard in instrument editor(s))
            ArrayList<VirtualMidiDevice*>& devices =
                const_cast<ArrayList<VirtualMidiDevice*>&>(
                    virtualMidiDevicesReader_MidiThread.Lock()
                );
            for (int i = 0; i < devices.size(); i++) {
                devices[i]->SendNoteOnToDevice(Key, Velocity);
            }
            virtualMidiDevicesReader_MidiThread.Unlock();
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to let the audio thread trigger a new
     *  voice for the given key. This method is meant for offline rendering
     *  and / or for cases where the exact position of the event in the current
     *  audio fragment is already known.
     *
     *  @param Key         - MIDI key number of the triggered key
     *  @param Velocity    - MIDI velocity value of the triggered key
     *  @param FragmentPos - sample point position in the current audio
     *                       fragment to which this event belongs to
     */
    void AbstractEngineChannel::SendNoteOn(uint8_t Key, uint8_t Velocity, int32_t FragmentPos) {
        if (FragmentPos < 0) {
            dmsg(1,("EngineChannel::SendNoteOn(): negative FragmentPos! Seems MIDI driver is buggy!"));
        }
        else if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent(FragmentPos);
            event.Type                = Event::type_note_on;
            event.Param.Note.Key      = Key;
            event.Param.Note.Velocity = Velocity;
            event.pEngineChannel      = this;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("EngineChannel: Input event queue full!"));
            // inform connected virtual MIDI devices if any ...
            // (e.g. virtual MIDI keyboard in instrument editor(s))
            ArrayList<VirtualMidiDevice*>& devices =
                const_cast<ArrayList<VirtualMidiDevice*>&>(
                    virtualMidiDevicesReader_MidiThread.Lock()
                );
            for (int i = 0; i < devices.size(); i++) {
                devices[i]->SendNoteOnToDevice(Key, Velocity);
            }
            virtualMidiDevicesReader_MidiThread.Unlock();
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread to release
     *  voice(s) on the given key. This method is meant for real time rendering,
     *  that is an event will immediately be created with the current system
     *  time as time stamp.
     *
     *  @param Key      - MIDI key number of the released key
     *  @param Velocity - MIDI release velocity value of the released key
     */
    void AbstractEngineChannel::SendNoteOff(uint8_t Key, uint8_t Velocity) {
        if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent();
            event.Type                = Event::type_note_off;
            event.Param.Note.Key      = Key;
            event.Param.Note.Velocity = Velocity;
            event.pEngineChannel      = this;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("EngineChannel: Input event queue full!"));
            // inform connected virtual MIDI devices if any ...
            // (e.g. virtual MIDI keyboard in instrument editor(s))
            ArrayList<VirtualMidiDevice*>& devices =
                const_cast<ArrayList<VirtualMidiDevice*>&>(
                    virtualMidiDevicesReader_MidiThread.Lock()
                );
            for (int i = 0; i < devices.size(); i++) {
                devices[i]->SendNoteOffToDevice(Key, Velocity);
            }
            virtualMidiDevicesReader_MidiThread.Unlock();
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread to release
     *  voice(s) on the given key. This method is meant for offline rendering
     *  and / or for cases where the exact position of the event in the current
     *  audio fragment is already known.
     *
     *  @param Key         - MIDI key number of the released key
     *  @param Velocity    - MIDI release velocity value of the released key
     *  @param FragmentPos - sample point position in the current audio
     *                       fragment to which this event belongs to
     */
    void AbstractEngineChannel::SendNoteOff(uint8_t Key, uint8_t Velocity, int32_t FragmentPos) {
        if (FragmentPos < 0) {
            dmsg(1,("EngineChannel::SendNoteOff(): negative FragmentPos! Seems MIDI driver is buggy!"));
        }
        else if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent(FragmentPos);
            event.Type                = Event::type_note_off;
            event.Param.Note.Key      = Key;
            event.Param.Note.Velocity = Velocity;
            event.pEngineChannel      = this;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("EngineChannel: Input event queue full!"));
            // inform connected virtual MIDI devices if any ...
            // (e.g. virtual MIDI keyboard in instrument editor(s))
            ArrayList<VirtualMidiDevice*>& devices =
                const_cast<ArrayList<VirtualMidiDevice*>&>(
                    virtualMidiDevicesReader_MidiThread.Lock()
                );
            for (int i = 0; i < devices.size(); i++) {
                devices[i]->SendNoteOffToDevice(Key, Velocity);
            }
            virtualMidiDevicesReader_MidiThread.Unlock();
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread to change
     *  the pitch value for all voices. This method is meant for real time
     *  rendering, that is an event will immediately be created with the
     *  current system time as time stamp.
     *
     *  @param Pitch - MIDI pitch value (-8192 ... +8191)
     */
    void AbstractEngineChannel::SendPitchbend(int Pitch) {
        if (pEngine) {
            Event event             = pEngine->pEventGenerator->CreateEvent();
            event.Type              = Event::type_pitchbend;
            event.Param.Pitch.Pitch = Pitch;
            event.pEngineChannel    = this;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("EngineChannel: Input event queue full!"));
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread to change
     *  the pitch value for all voices. This method is meant for offline
     *  rendering and / or for cases where the exact position of the event in
     *  the current audio fragment is already known.
     *
     *  @param Pitch       - MIDI pitch value (-8192 ... +8191)
     *  @param FragmentPos - sample point position in the current audio
     *                       fragment to which this event belongs to
     */
    void AbstractEngineChannel::SendPitchbend(int Pitch, int32_t FragmentPos) {
        if (FragmentPos < 0) {
            dmsg(1,("AbstractEngineChannel::SendPitchBend(): negative FragmentPos! Seems MIDI driver is buggy!"));
        }
        else if (pEngine) {
            Event event             = pEngine->pEventGenerator->CreateEvent(FragmentPos);
            event.Type              = Event::type_pitchbend;
            event.Param.Pitch.Pitch = Pitch;
            event.pEngineChannel    = this;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("AbstractEngineChannel: Input event queue full!"));
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread that a
     *  continuous controller value has changed. This method is meant for real
     *  time rendering, that is an event will immediately be created with the
     *  current system time as time stamp.
     *
     *  @param Controller - MIDI controller number of the occured control change
     *  @param Value      - value of the control change
     */
    void AbstractEngineChannel::SendControlChange(uint8_t Controller, uint8_t Value) {
        if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent();
            event.Type                = Event::type_control_change;
            event.Param.CC.Controller = Controller;
            event.Param.CC.Value      = Value;
            event.pEngineChannel      = this;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("AbstractEngineChannel: Input event queue full!"));
        }
    }

    /**
     *  Will be called by the MIDIIn Thread to signal the audio thread that a
     *  continuous controller value has changed. This method is meant for
     *  offline rendering and / or for cases where the exact position of the
     *  event in the current audio fragment is already known.
     *
     *  @param Controller  - MIDI controller number of the occured control change
     *  @param Value       - value of the control change
     *  @param FragmentPos - sample point position in the current audio
     *                       fragment to which this event belongs to
     */
    void AbstractEngineChannel::SendControlChange(uint8_t Controller, uint8_t Value, int32_t FragmentPos) {
        if (FragmentPos < 0) {
            dmsg(1,("AbstractEngineChannel::SendControlChange(): negative FragmentPos! Seems MIDI driver is buggy!"));
        }
        else if (pEngine) {
            Event event               = pEngine->pEventGenerator->CreateEvent(FragmentPos);
            event.Type                = Event::type_control_change;
            event.Param.CC.Controller = Controller;
            event.Param.CC.Value      = Value;
            event.pEngineChannel      = this;
            if (this->pEventQueue->write_space() > 0) this->pEventQueue->push(&event);
            else dmsg(1,("AbstractEngineChannel: Input event queue full!"));
        }
    }

    /**
     * Copy all events from the engine channel's input event queue buffer to
     * the internal event list. This will be done at the beginning of each
     * audio cycle (that is each RenderAudio() call) to distinguish all
     * events which have to be processed in the current audio cycle. Each
     * EngineChannel has it's own input event queue for the common channel
     * specific events (like NoteOn, NoteOff and ControlChange events).
     * Beside that, the engine also has a input event queue for global
     * events (usually SysEx messages).
     *
     * @param Samples - number of sample points to be processed in the
     *                  current audio cycle
     */
    void AbstractEngineChannel::ImportEvents(uint Samples) {
        // import events from pure software MIDI "devices"
        // (e.g. virtual keyboard in instrument editor)
        {
            const int FragmentPos = 0; // randomly chosen, we don't care about jitter for virtual MIDI devices
            Event event = pEngine->pEventGenerator->CreateEvent(FragmentPos);
            VirtualMidiDevice::event_t devEvent; // the event format we get from the virtual MIDI device
            // as we're going to (carefully) write some status to the
            // synchronized struct, we cast away the const
            ArrayList<VirtualMidiDevice*>& devices =
                const_cast<ArrayList<VirtualMidiDevice*>&>(virtualMidiDevicesReader_AudioThread.Lock());
            // iterate through all virtual MIDI devices
            for (int i = 0; i < devices.size(); i++) {
                VirtualMidiDevice* pDev = devices[i];
                // I think we can simply flush the whole FIFO(s), the user shouldn't be so fast ;-)
                while (pDev->GetMidiEventFromDevice(devEvent)) {
                    event.Type =
                        (devEvent.Type == VirtualMidiDevice::EVENT_TYPE_NOTEON) ?
                            Event::type_note_on : Event::type_note_off;
                    event.Param.Note.Key      = devEvent.Key;
                    event.Param.Note.Velocity = devEvent.Velocity;
                    event.pEngineChannel      = this;
                    // copy event to internal event list
                    if (pEvents->poolIsEmpty()) {
                        dmsg(1,("Event pool emtpy!\n"));
                        goto exitVirtualDevicesLoop;
                    }
                    *pEvents->allocAppend() = event;
                }
            }
        }
        exitVirtualDevicesLoop:
        virtualMidiDevicesReader_AudioThread.Unlock();

        // import events from the regular MIDI devices
        RingBuffer<Event,false>::NonVolatileReader eventQueueReader = pEventQueue->get_non_volatile_reader();
        Event* pEvent;
        while (true) {
            // get next event from input event queue
            if (!(pEvent = eventQueueReader.pop())) break;
            // if younger event reached, ignore that and all subsequent ones for now
            if (pEvent->FragmentPos() >= Samples) {
                eventQueueReader--;
                dmsg(2,("Younger Event, pos=%d ,Samples=%d!\n",pEvent->FragmentPos(),Samples));
                pEvent->ResetFragmentPos();
                break;
            }
            // copy event to internal event list
            if (pEvents->poolIsEmpty()) {
                dmsg(1,("Event pool emtpy!\n"));
                break;
            }
            *pEvents->allocAppend() = *pEvent;
        }
        eventQueueReader.free(); // free all copied events from input queue
    }

    FxSend* AbstractEngineChannel::AddFxSend(uint8_t MidiCtrl, String Name) throw (Exception) {
        if (pEngine) pEngine->DisableAndLock();
        FxSend* pFxSend = new FxSend(this, MidiCtrl, Name);
        if (fxSends.empty()) {
            if (pEngine && pEngine->pAudioOutputDevice) {
                AudioOutputDevice* pDevice = pEngine->pAudioOutputDevice;
                // create local render buffers
                pChannelLeft  = new AudioChannel(0, pDevice->MaxSamplesPerCycle());
                pChannelRight = new AudioChannel(1, pDevice->MaxSamplesPerCycle());
            } else {
                // postpone local render buffer creation until audio device is assigned
                pChannelLeft  = NULL;
                pChannelRight = NULL;
            }
        }
        fxSends.push_back(pFxSend);
        if (pEngine) pEngine->Enable();
        fireFxSendCountChanged(GetSamplerChannel()->Index(), GetFxSendCount());

        return pFxSend;
    }

    FxSend* AbstractEngineChannel::GetFxSend(uint FxSendIndex) {
        return (FxSendIndex < fxSends.size()) ? fxSends[FxSendIndex] : NULL;
    }

    uint AbstractEngineChannel::GetFxSendCount() {
        return fxSends.size();
    }

    void AbstractEngineChannel::RemoveFxSend(FxSend* pFxSend) {
        if (pEngine) pEngine->DisableAndLock();
        for (
            std::vector<FxSend*>::iterator iter = fxSends.begin();
            iter != fxSends.end(); iter++
        ) {
            if (*iter == pFxSend) {
                delete pFxSend;
                fxSends.erase(iter);
                if (fxSends.empty()) {
                    // destroy local render buffers
                    if (pChannelLeft)  delete pChannelLeft;
                    if (pChannelRight) delete pChannelRight;
                    // fallback to render directly into AudioOutputDevice's buffers
                    if (pEngine && pEngine->pAudioOutputDevice) {
                        pChannelLeft  = pEngine->pAudioOutputDevice->Channel(AudioDeviceChannelLeft);
                        pChannelRight = pEngine->pAudioOutputDevice->Channel(AudioDeviceChannelRight);
                    } else { // we update the pointers later
                        pChannelLeft  = NULL;
                        pChannelRight = NULL;
                    }
                }
                break;
            }
        }
        if (pEngine) pEngine->Enable();
        fireFxSendCountChanged(GetSamplerChannel()->Index(), GetFxSendCount());
    }

    void AbstractEngineChannel::RemoveAllFxSends() {
        if (pEngine) pEngine->DisableAndLock();
        if (!fxSends.empty()) { // free local render buffers
            if (pChannelLeft) {
                delete pChannelLeft;
                if (pEngine && pEngine->pAudioOutputDevice) {
                    // fallback to render directly to the AudioOutputDevice's buffer
                    pChannelLeft = pEngine->pAudioOutputDevice->Channel(AudioDeviceChannelLeft);
                } else pChannelLeft = NULL;
            }
            if (pChannelRight) {
                delete pChannelRight;
                if (pEngine && pEngine->pAudioOutputDevice) {
                    // fallback to render directly to the AudioOutputDevice's buffer
                    pChannelRight = pEngine->pAudioOutputDevice->Channel(AudioDeviceChannelRight);
                } else pChannelRight = NULL;
            }
        }
        for (int i = 0; i < fxSends.size(); i++) delete fxSends[i];
        fxSends.clear();
        if (pEngine) pEngine->Enable();
    }

} // namespace LinuxSampler