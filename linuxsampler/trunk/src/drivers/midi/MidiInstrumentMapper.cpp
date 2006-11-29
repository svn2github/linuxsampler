/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2006 Christian Schoenebeck                              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#include "MidiInstrumentMapper.h"

#include "../../common/Mutex.h"
#include "../../engines/EngineFactory.h"
#include "../../engines/Engine.h"

namespace LinuxSampler {

    // same as entry_t but without 'LoadMode'
    struct private_entry_t {
        String EngineName;
        String InstrumentFile;
        uint   InstrumentIndex;
        float  Volume;
        String Name;
    };

    // here we store all mappings (MIDI bank&prog) -> (Engine,File,Index)
    std::map<midi_prog_index_t,private_entry_t> midiMap;

    // for synchronization of midiMap
    Mutex midiMapMutex;


    void MidiInstrumentMapper::AddOrReplaceMapping(midi_prog_index_t Index, entry_t Entry, bool bInBackground) throw (Exception) {
        if (bInBackground) {
            dmsg(3,("MidiInstrumentMapper: updating mapping (%d,%d,%d) -> ('%s','%s',%d) with vol=%f, mode=%d in background\n",
                Index.midi_bank_msb,Index.midi_bank_lsb,Index.midi_prog,
                Entry.EngineName.c_str(),Entry.InstrumentFile.c_str(),Entry.InstrumentIndex,
                Entry.Volume,Entry.LoadMode)
            );
        } else {
            dmsg(3,("MidiInstrumentMapper: updating mapping (%d,%d,%d) -> ('%s','%s',%d) with vol=%f, mode=%d\n",
                Index.midi_bank_msb,Index.midi_bank_lsb,Index.midi_prog,
                Entry.EngineName.c_str(),Entry.InstrumentFile.c_str(),Entry.InstrumentIndex,
                Entry.Volume,Entry.LoadMode)
            );
        }
        if (Entry.Volume < 0.0)
            throw Exception("Volume may not be a negative value");
        Engine* pEngine = EngineFactory::Create(Entry.EngineName);
        if (!pEngine)
            throw Exception("No such engine type '"+Entry.EngineName+"'");
        Entry.EngineName = pEngine->EngineName(); // make sure to use the official engine name
        if (pEngine->GetInstrumentManager()) {
            InstrumentManager::instrument_id_t id;
            id.FileName = Entry.InstrumentFile;
            id.Index    = Entry.InstrumentIndex;
            if (Entry.LoadMode != VOID) {
                if (bInBackground)
                    pEngine->GetInstrumentManager()->SetModeInBackground(id, static_cast<InstrumentManager::mode_t>(Entry.LoadMode));
                else
                    pEngine->GetInstrumentManager()->SetMode(id, static_cast<InstrumentManager::mode_t>(Entry.LoadMode));
            }
        } else {
            dmsg(1,("WARNING: no InstrumentManager for engine '%s'\n",Entry.EngineName.c_str()));
        }
        private_entry_t privateEntry;
        privateEntry.EngineName      = Entry.EngineName;
        privateEntry.InstrumentFile  = Entry.InstrumentFile;
        privateEntry.InstrumentIndex = Entry.InstrumentIndex;
        privateEntry.Volume          = Entry.Volume;
        privateEntry.Name            = Entry.Name;
        midiMapMutex.Lock();
        midiMap[Index] = privateEntry;
        midiMapMutex.Unlock();
        EngineFactory::Destroy(pEngine);
    }

    void MidiInstrumentMapper::RemoveMapping(midi_prog_index_t Index) {
        midiMapMutex.Lock();
        midiMap.erase(Index);
        midiMapMutex.Unlock();
    }

    void MidiInstrumentMapper::RemoveAllMappings() {
        midiMapMutex.Lock();
        midiMap.clear();
        midiMapMutex.Unlock();
    }

    std::map<midi_prog_index_t,MidiInstrumentMapper::entry_t> MidiInstrumentMapper::Mappings() {
        std::map<midi_prog_index_t,entry_t> result;
        // copy the internal map first
        midiMapMutex.Lock();
        for (std::map<midi_prog_index_t,private_entry_t>::iterator iter = midiMap.begin();
             iter != midiMap.end(); iter++)
        {
            entry_t entry;
            entry.EngineName      = iter->second.EngineName;
            entry.InstrumentFile  = iter->second.InstrumentFile;
            entry.InstrumentIndex = iter->second.InstrumentIndex;
            entry.Volume          = iter->second.Volume;
            entry.Name            = iter->second.Name;
            result[iter->first] = entry;
        }
        midiMapMutex.Unlock();
        // complete it with current LoadMode of each entry
        for (std::map<midi_prog_index_t,entry_t>::iterator iter = result.begin();
             iter != result.end(); iter++)
        {
            entry_t& entry = iter->second;
            Engine* pEngine = EngineFactory::Create(entry.EngineName);
            if (!pEngine) { // invalid mapping
                RemoveMapping(iter->first);
                result.erase(iter);
                continue;
            }
            InstrumentManager* pManager = pEngine->GetInstrumentManager();
            if (pManager) { // engine provides an InstrumentManager
                InstrumentManager::instrument_id_t id;
                id.FileName = entry.InstrumentFile;
                id.Index    = entry.InstrumentIndex;
                entry.LoadMode = static_cast<mode_t>(pManager->GetMode(id));
            } else { // engine does not provide an InstrumentManager
                // use default value
                entry.LoadMode = ON_DEMAND;
            }
            EngineFactory::Destroy(pEngine);
        }
        return result;
    }

    optional<MidiInstrumentMapper::entry_t> MidiInstrumentMapper::GetEntry(midi_prog_index_t Index) {
        optional<entry_t> result;
        midiMapMutex.Lock();
        std::map<midi_prog_index_t,private_entry_t>::iterator iter = midiMap.find(Index);
        if (iter != midiMap.end()) {
            entry_t entry;
            entry.EngineName      = iter->second.EngineName;
            entry.InstrumentFile  = iter->second.InstrumentFile;
            entry.InstrumentIndex = iter->second.InstrumentIndex;
            entry.Volume          = iter->second.Volume;
            //TODO: for now we skip the LoadMode and Name entry here, since we don't need it in the MidiInputPort
            result = entry;
        }
        midiMapMutex.Unlock();
        return result;
    }

} // namespace LinuxSampler
