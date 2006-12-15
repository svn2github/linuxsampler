/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
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

#include "MidiInstrumentMapper.h"
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

    void MidiInputPort::ParameterName::OnSetValue(String s) throw (Exception) {
        return; /* FIXME: Nothing to do here */
    }



// *************** MidiInputPort ***************
// *

    MidiInputPort::~MidiInputPort() {
        std::map<String,DeviceRuntimeParameter*>::iterator iter = Parameters.begin();
        while (iter != Parameters.end()) {
            delete iter->second;
            iter++;
        }
        Parameters.clear();
    }

    MidiInputPort::MidiInputPort(MidiInputDevice* pDevice, int portNumber)
        : MidiChannelMapReader(MidiChannelMap),
          SysexListenersReader(SysexListeners) {
        this->pDevice = pDevice;
        this->portNumber = portNumber;
        Parameters["NAME"] = new ParameterName(this);
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
        if (Key > 127 || Velocity > 127 || MidiChannel > 16) return;
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOn(Key, Velocity);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOn(Key, Velocity);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchNoteOn(uint8_t Key, uint8_t Velocity, uint MidiChannel, int32_t FragmentPos) {
        if (Key > 127 || Velocity > 127 || MidiChannel > 16) return;
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOn(Key, Velocity, FragmentPos);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOn(Key, Velocity, FragmentPos);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchNoteOff(uint8_t Key, uint8_t Velocity, uint MidiChannel) {
        if (Key > 127 || Velocity > 127 || MidiChannel > 16) return;
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOff(Key, Velocity);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOff(Key, Velocity);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchNoteOff(uint8_t Key, uint8_t Velocity, uint MidiChannel, int32_t FragmentPos) {
        if (Key > 127 || Velocity > 127 || MidiChannel > 16) return;
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOff(Key, Velocity, FragmentPos);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOff(Key, Velocity, FragmentPos);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchPitchbend(int Pitch, uint MidiChannel) {
        if (Pitch < -8192 || Pitch > 8191 || MidiChannel > 16) return;
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendPitchbend(Pitch);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendPitchbend(Pitch);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchPitchbend(int Pitch, uint MidiChannel, int32_t FragmentPos) {
        if (Pitch < -8192 || Pitch > 8191 || MidiChannel > 16) return;
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendPitchbend(Pitch, FragmentPos);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendPitchbend(Pitch, FragmentPos);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchControlChange(uint8_t Controller, uint8_t Value, uint MidiChannel) {
        if (Controller > 128 || Value > 127 || MidiChannel > 16) return;
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendControlChange(Controller, Value);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendControlChange(Controller, Value);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchControlChange(uint8_t Controller, uint8_t Value, uint MidiChannel, int32_t FragmentPos) {
        if (Controller > 128 || Value > 127 || MidiChannel > 16) return;
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendControlChange(Controller, Value, FragmentPos);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) (*engineiter)->SendControlChange(Controller, Value, FragmentPos);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchSysex(void* pData, uint Size) {
        const std::set<Engine*> allEngines = SysexListenersReader.Lock();
        // dispatch event to all engine instances
        std::set<Engine*>::iterator engineiter = allEngines.begin();
        std::set<Engine*>::iterator end        = allEngines.end();
        for (; engineiter != end; engineiter++) (*engineiter)->SendSysex(pData, Size);
        SysexListenersReader.Unlock();
    }

    void MidiInputPort::DispatchProgramChange(uint8_t Program, uint MidiChannel) {
        dmsg(1,("Received MIDI program change (prog=%d,ch=%d)\n",Program,MidiChannel));
        if (Program > 127 || MidiChannel > 16) return;
        if (!pDevice || !pDevice->pSampler) {
            std::cerr << "MidiInputPort: ERROR, no sampler instance to handle program change."
                      << "This is a bug, please report it!\n" << std::flush;
            return;
        }
        std::vector<int> maps = MidiInstrumentMapper::Maps();
        if (maps.empty()) return;

        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            for (; engineiter != end; engineiter++) {
                (*engineiter)->SetMidiProgram(Program);
                if ((*engineiter)->UsesNoMidiInstrumentMap()) continue;
                // retrieve the MIDI instrument map this engine channel is assigned to
                int iMapID = ((*engineiter)->UsesDefaultMidiInstrumentMap())
                    ? maps[0] /*default*/ : (*engineiter)->GetMidiInstrumentMap();
                // is there an entry for this MIDI bank&prog pair in that map?
                midi_prog_index_t midiIndex;
                midiIndex.midi_bank_msb = (*engineiter)->GetMidiBankMsb();
                midiIndex.midi_bank_lsb = (*engineiter)->GetMidiBankLsb();
                midiIndex.midi_prog     = (*engineiter)->GetMidiProgram();
                optional<MidiInstrumentMapper::entry_t> mapping =
                    MidiInstrumentMapper::GetEntry(iMapID, midiIndex);
                if (mapping) { // if mapping exists ...
                    InstrumentManager::instrument_id_t id;
                    id.FileName = mapping->InstrumentFile;
                    id.Index    = mapping->InstrumentIndex;
                    //TODO: we should switch the engine type here
                    InstrumentManager::LoadInstrumentInBackground(id, *engineiter);
                    (*engineiter)->Volume(mapping->Volume);
                }
            }
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            for (; engineiter != end; engineiter++) {
                (*engineiter)->SetMidiProgram(Program);
                if ((*engineiter)->UsesNoMidiInstrumentMap()) continue;
                // retrieve the MIDI instrument map this engine channel is assigned to
                int iMapID = ((*engineiter)->UsesDefaultMidiInstrumentMap())
                    ? maps[0] /*default*/ : (*engineiter)->GetMidiInstrumentMap();
                // is there an entry for this MIDI bank&prog pair in that map?
                midi_prog_index_t midiIndex;
                midiIndex.midi_bank_msb = (*engineiter)->GetMidiBankMsb();
                midiIndex.midi_bank_lsb = (*engineiter)->GetMidiBankLsb();
                midiIndex.midi_prog     = (*engineiter)->GetMidiProgram();
                optional<MidiInstrumentMapper::entry_t> mapping =
                    MidiInstrumentMapper::GetEntry(iMapID, midiIndex);
                if (mapping) { // if mapping exists ...
                    InstrumentManager::instrument_id_t id;
                    id.FileName = mapping->InstrumentFile;
                    id.Index    = mapping->InstrumentIndex;
                    //TODO: we should switch the engine type here
                    InstrumentManager::LoadInstrumentInBackground(id, *engineiter);
                    (*engineiter)->Volume(mapping->Volume);
                }
            }
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchBankSelectMsb(uint8_t BankMSB, uint MidiChannel) {
        if (BankMSB > 127 || MidiChannel > 16) return;
        if (!pDevice || !pDevice->pSampler) {
            std::cerr << "MidiInputPort: ERROR, no sampler instance to handle bank select MSB."
                      << "This is a bug, please report it!\n" << std::flush;
            return;
        }
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            // according to the MIDI specs, a bank select should not alter the patch
            for (; engineiter != end; engineiter++) (*engineiter)->SetMidiBankMsb(BankMSB);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            // according to the MIDI specs, a bank select should not alter the patch
            for (; engineiter != end; engineiter++) (*engineiter)->SetMidiBankMsb(BankMSB);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::DispatchBankSelectLsb(uint8_t BankLSB, uint MidiChannel) {
        if (BankLSB > 127 || MidiChannel > 16) return;
        if (!pDevice || !pDevice->pSampler) {
            std::cerr << "MidiInputPort: ERROR, no sampler instance to handle bank select LSB."
                      << "This is a bug, please report it!\n" << std::flush;
            return;
        }
        const MidiChannelMap_t& midiChannelMap = MidiChannelMapReader.Lock();
        // dispatch event for engines listening to the same MIDI channel
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[MidiChannel].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[MidiChannel].end();
            // according to the MIDI specs, a bank select should not alter the patch
            for (; engineiter != end; engineiter++) (*engineiter)->SetMidiBankLsb(BankLSB);
        }
        // dispatch event for engines listening to ALL MIDI channels
        {
            std::set<EngineChannel*>::iterator engineiter = midiChannelMap[midi_chan_all].begin();
            std::set<EngineChannel*>::iterator end        = midiChannelMap[midi_chan_all].end();
            // according to the MIDI specs, a bank select should not alter the patch
            for (; engineiter != end; engineiter++) (*engineiter)->SetMidiBankLsb(BankLSB);
        }
        MidiChannelMapReader.Unlock();
    }

    void MidiInputPort::Connect(EngineChannel* pEngineChannel, midi_chan_t MidiChannel) {
        if (MidiChannel < 0 || MidiChannel > 16)
            throw MidiInputException("MIDI channel index out of bounds");

        // first check if desired connection is already established
        MidiChannelMapMutex.Lock();
        MidiChannelMap_t& midiChannelMap = MidiChannelMap.GetConfigForUpdate();
        bool bAlreadyDone = midiChannelMap[MidiChannel].count(pEngineChannel);
        MidiChannelMapMutex.Unlock();
        if (bAlreadyDone) return;

        // remove all other connections of that engine channel (if any)
        Disconnect(pEngineChannel);

        // register engine channel on the desired MIDI channel
        MidiChannelMapMutex.Lock();
        MidiChannelMap.GetConfigForUpdate()[MidiChannel].insert(pEngineChannel);
        MidiChannelMap.SwitchConfig()[MidiChannel].insert(pEngineChannel);
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
            {
                MidiChannelMap_t& midiChannelMap = MidiChannelMap.GetConfigForUpdate();
                for (int i = 0; i <= 16; i++) {
                    bChannelFound |= midiChannelMap[i].count(pEngineChannel);
                    midiChannelMap[i].erase(pEngineChannel);
                }
            }
            // do the same update again, after switching to the other config
            {
                MidiChannelMap_t& midiChannelMap = MidiChannelMap.SwitchConfig();
                for (int i = 0; i <= 16; i++) {
                    bChannelFound |= midiChannelMap[i].count(pEngineChannel);
                    midiChannelMap[i].erase(pEngineChannel);
                }
            }
        }
        catch(...) { /* NOOP */ }
        MidiChannelMapMutex.Unlock();

        // inform engine channel about the disconnection (if there is one)
        if (bChannelFound) pEngineChannel->DisconnectMidiInputPort();

        // mark engine channel as changed
        pEngineChannel->StatusChanged(true);
    }

    SynchronizedConfig<std::set<LinuxSampler::Engine*> > MidiInputPort::SysexListeners;

    void MidiInputPort::AddSysexListener(Engine* engine) {
        std::pair<std::set<Engine*>::iterator, bool> p = SysexListeners.GetConfigForUpdate().insert(engine);
        if (p.second) SysexListeners.SwitchConfig().insert(engine);
    }

    bool MidiInputPort::RemoveSysexListener(Engine* engine) {
        int count = SysexListeners.GetConfigForUpdate().erase(engine);
        if (count) SysexListeners.SwitchConfig().erase(engine);
        return count;
    }

} // namespace LinuxSampler
