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

#include "MidiInputPort.h"

#include "../../Sampler.h"
#include "../../engines/EngineFactory.h"

namespace LinuxSampler {

// *************** ParameterName ***************
// *

    MidiInputPort::ParameterName::ParameterName(MidiInputPort* pPort) : DeviceRuntimeParameterString("Port " + ToString(pPort->GetPortNumber())) {
        this->pPort = pPort;
    }

    MidiInputPort::ParameterName::ParameterName(MidiInputPort* pPort, String val) : DeviceRuntimeParameterString(val) {
        this->pPort = pPort;
    }

    String MidiInputPort::ParameterName::Description() {
        return "Name for this port";
    }

    bool MidiInputPort::ParameterName::Fix() {
        return false;
    }

    std::vector<String> MidiInputPort::ParameterName::PossibilitiesAsString() {
        return std::vector<String>();
    }

    void MidiInputPort::ParameterName::OnSetValue(String s) throw (LinuxSamplerException) {
        return; /* FIXME: Nothing to do here */
    }



// *************** MidiInputPort ***************
// *

    MidiInputPort::~MidiInputPort() {
        std::map<String,DeviceRuntimeParameter*>::iterator iter = Parameters.begin();
        while (iter != Parameters.end()) {
            Parameters.erase(iter);
            delete iter->second;
            iter++;
        }
    }

    MidiInputPort::MidiInputPort(MidiInputDevice* pDevice, int portNumber) {
        this->pDevice = pDevice;
        this->portNumber = portNumber;
        Parameters["NAME"] = new ParameterName(this);
        pPreviousProgramChangeEngineChannel = NULL;
    }

    MidiInputDevice* MidiInputPort::GetDevice() {
        return pDevice;
    }

    uint MidiInputPort::GetPortNumber() {
        return portNumber;
    }

    std::map<String,DeviceRuntimeParameter*> MidiInputPort::PortParameters() {
        return Parameters;
    }

    void MidiInputPort::DispatchNoteOn(uint8_t Key, uint8_t Velocity, uint MidiChannel) {
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = MidiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = MidiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOn(Key, Velocity);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = MidiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = MidiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOn(Key, Velocity);
        }
    }

    void MidiInputPort::DispatchNoteOff(uint8_t Key, uint8_t Velocity, uint MidiChannel) {
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = MidiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = MidiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOff(Key, Velocity);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = MidiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = MidiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOff(Key, Velocity);
        }
    }

    void MidiInputPort::DispatchPitchbend(int Pitch, uint MidiChannel) {
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = MidiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = MidiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendPitchbend(Pitch);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = MidiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = MidiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendPitchbend(Pitch);
        }
    }

    void MidiInputPort::DispatchControlChange(uint8_t Controller, uint8_t Value, uint MidiChannel) {
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = MidiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = MidiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendControlChange(Controller, Value);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = MidiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = MidiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendControlChange(Controller, Value);
        }
    }

    void MidiInputPort::DispatchSysex(void* pData, uint Size) {
        // dispatch event to all engine instances
        std::set<Engine*>::iterator engineiter = EngineFactory::EngineInstances().begin();
        std::set<Engine*>::iterator end        = EngineFactory::EngineInstances().end();
        for (; engineiter != end; engineiter++) (*engineiter)->SendSysex(pData, Size);
    }

    void MidiInputPort::DispatchProgramChange(uint8_t Program, uint MidiChannel) {
        if (!pDevice || !pDevice->pSampler) {
            std::cerr << "MidiInputPort: ERROR, no sampler instance to handle program change."
                      << "This is a bug, please report it!\n" << std::flush;
            return;
        }

        Sampler*        pSampler        = (Sampler*) pDevice->pSampler;
        SamplerChannel* pSamplerChannel = pSampler->GetSamplerChannel(Program);
        if (!pSamplerChannel) return;

        EngineChannel* pEngineChannel = pSamplerChannel->GetEngineChannel();
        if (!pEngineChannel) return;

        // disconnect from the engine channel which was connected by the last PC event
        if (pPreviousProgramChangeEngineChannel)
            Disconnect(pPreviousProgramChangeEngineChannel);

        // now connect to the new engine channel and remember it
        try {
            Connect(pEngineChannel, (midi_chan_t) MidiChannel);
            pPreviousProgramChangeEngineChannel = pEngineChannel;
        }
        catch (...) { /* NOOP */ }
    }

    void MidiInputPort::Connect(EngineChannel* pEngineChannel, midi_chan_t MidiChannel) {
        if (MidiChannel < 0 || MidiChannel > 16)
            throw MidiInputException("MIDI channel index out of bounds");

        // firt check if desired connection is already established
        MidiChannelMapMutex.Lock();
        bool bAlreadyDone = MidiChannelMap[MidiChannel].count(pEngineChannel);
        MidiChannelMapMutex.Unlock();
        if (bAlreadyDone) return;

        // remove all other connections of that engine channel (if any)
        Disconnect(pEngineChannel);

        // register engine channel on the desired MIDI channel
        MidiChannelMapMutex.Lock();
        MidiChannelMap[MidiChannel].insert(pEngineChannel);
        MidiChannelMapMutex.Unlock();

        // inform engine channel about this connection
        pEngineChannel->Connect(this, MidiChannel);

        // mark engine channel as changed
        pEngineChannel->StatusChanged(true);
    }

    void MidiInputPort::Disconnect(EngineChannel* pEngineChannel) {
        if (!pEngineChannel) return;

        bool bChannelFound = false;

        // unregister engine channel from all MIDI channels
        MidiChannelMapMutex.Lock();
        try {
            for (int i = 0; i <= 16; i++) {
                bChannelFound |= MidiChannelMap[i].count(pEngineChannel);
                MidiChannelMap[i].erase(pEngineChannel);
            }
        }
        catch(...) { /* NOOP */ }
        MidiChannelMapMutex.Unlock();

        // inform engine channel about the disconnection (if there is one)
        if (bChannelFound) pEngineChannel->DisconnectMidiInputPort();

        // mark engine channel as changed
        pEngineChannel->StatusChanged(true);
    }

} // namespace LinuxSampler
