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

    // internal map type (MIDI bank&prog) -> (Engine,File,Index)
    class MidiInstrumentMap : public std::map<midi_prog_index_t,private_entry_t> {
        public:
            String name;
    };

    // here we store all maps
    std::map<int,MidiInstrumentMap> midiMaps;

    // for synchronization of midiMaps
    Mutex midiMapsMutex;


    void MidiInstrumentMapper::AddOrReplaceEntry(int Map, midi_prog_index_t Index, entry_t Entry, bool bInBackground) throw (Exception) {
        if (bInBackground) {
            dmsg(3,("MidiInstrumentMapper: updating mapping %d (%d,%d,%d) -> ('%s','%s',%d) with vol=%f, mode=%d in background\n",
                Map,
                Index.midi_bank_msb,Index.midi_bank_lsb,Index.midi_prog,
                Entry.EngineName.c_str(),Entry.InstrumentFile.c_str(),Entry.InstrumentIndex,
                Entry.Volume,Entry.LoadMode)
            );
        } else {
            dmsg(3,("MidiInstrumentMapper: updating mapping %d (%d,%d,%d) -> ('%s','%s',%d) with vol=%f, mode=%d\n",
                Map,
                Index.midi_bank_msb,Index.midi_bank_lsb,Index.midi_prog,
                Entry.EngineName.c_str(),Entry.InstrumentFile.c_str(),Entry.InstrumentIndex,
                Entry.Volume,Entry.LoadMode)
            );
        }
        midiMapsMutex.Lock();
        if (midiMaps.empty()) {
            midiMapsMutex.Unlock();
            throw Exception("There is no MIDI instrument map, you have to add one first.");
        }
        midiMapsMutex.Unlock();
        if (!Entry.InstrumentFile.size())
            throw Exception("No instrument file name given");
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
        midiMapsMutex.Lock();
        std::map<int,MidiInstrumentMap>::iterator iterMap = midiMaps.find(Map);
        if (iterMap != midiMaps.end()) { // map found
            iterMap->second[Index] = privateEntry;
        } else { // no such map
            midiMapsMutex.Unlock();
            EngineFactory::Destroy(pEngine);
            throw Exception("There is no MIDI instrument map " + ToString(Map));
        }
        midiMapsMutex.Unlock();
        EngineFactory::Destroy(pEngine);
    }

    void MidiInstrumentMapper::RemoveEntry(int Map, midi_prog_index_t Index) {
        midiMapsMutex.Lock();
        std::map<int,MidiInstrumentMap>::iterator iterMap = midiMaps.find(Map);
        if (iterMap != midiMaps.end()) { // map found
            iterMap->second.erase(Index); // remove entry
        }
        midiMapsMutex.Unlock();
    }

    void MidiInstrumentMapper::RemoveAllEntries(int Map) {
        midiMapsMutex.Lock();
        std::map<int,MidiInstrumentMap>::iterator iterMap = midiMaps.find(Map);
        if (iterMap != midiMaps.end()) { // map found
            iterMap->second.clear(); // clear that map
        }
        midiMapsMutex.Unlock();
    }

    std::map<midi_prog_index_t,MidiInstrumentMapper::entry_t> MidiInstrumentMapper::Entries(int Map) throw (Exception) {
        std::map<midi_prog_index_t,entry_t> result;

        // copy the internal map first
        midiMapsMutex.Lock();
        std::map<int,MidiInstrumentMap>::iterator iterMap = midiMaps.find(Map);
        if (iterMap == midiMaps.end()) { // no such map
            midiMapsMutex.Unlock();
            throw Exception("There is no MIDI instrument map " + ToString(Map));
        }
        for (std::map<midi_prog_index_t,private_entry_t>::iterator iterEntry = iterMap->second.begin();
             iterEntry != iterMap->second.end(); iterEntry++)
        {
            entry_t entry;
            entry.EngineName      = iterEntry->second.EngineName;
            entry.InstrumentFile  = iterEntry->second.InstrumentFile;
            entry.InstrumentIndex = iterEntry->second.InstrumentIndex;
            entry.Volume          = iterEntry->second.Volume;
            entry.Name            = iterEntry->second.Name;
            result[iterEntry->first] = entry;
        }
        midiMapsMutex.Unlock();

        // complete it with current LoadMode of each entry
        for (std::map<midi_prog_index_t,entry_t>::iterator iter = result.begin();
             iter != result.end(); iter++)
        {
            entry_t& entry = iter->second;
            Engine* pEngine = EngineFactory::Create(entry.EngineName);
            if (!pEngine) { // invalid mapping
                RemoveEntry(Map, iter->first);
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

    std::vector<int> MidiInstrumentMapper::Maps() {
        std::vector<int> result;
        midiMapsMutex.Lock();
        for (std::map<int,MidiInstrumentMap>::iterator iterMap = midiMaps.begin();
             iterMap != midiMaps.end(); iterMap++)
        {
            result.push_back(iterMap->first);
        }
        midiMapsMutex.Unlock();
        return result;
    }

    int MidiInstrumentMapper::AddMap(String MapName) throw (Exception) {
        int ID;
        midiMapsMutex.Lock();
        if (midiMaps.empty()) ID = 0;
        else {
            // get the highest existing map ID
            uint lastIndex = (--(midiMaps.end()))->first;
            // check if we reached the index limit
            if (lastIndex + 1 < lastIndex) {
                // search for an unoccupied map ID starting from 0
                for (uint i = 0; i < lastIndex; i++) {
                    if (midiMaps.find(i) != midiMaps.end()) continue;
                    // we found an unused ID, so insert the new map there
                    ID = i;
                    goto __create_map;
                }
                throw Exception("Internal error: could not find unoccupied MIDI instrument map ID.");
            }
            ID = lastIndex;
        }
        __create_map:
        midiMaps[ID].name = MapName;
        midiMapsMutex.Unlock();
        return ID;
    }

    String MidiInstrumentMapper::MapName(int Map) throw (Exception) {
        String result;
        midiMapsMutex.Lock();
        std::map<int,MidiInstrumentMap>::iterator iterMap = midiMaps.find(Map);
        if (iterMap == midiMaps.end()) {
            midiMapsMutex.Unlock();
            throw Exception("There is no MIDI instrument map " + ToString(Map));
        }
        result = iterMap->second.name;
        midiMapsMutex.Unlock();
        return result;
    }

    void MidiInstrumentMapper::RenameMap(int Map, String NewName) throw (Exception) {
        midiMapsMutex.Lock();
        std::map<int,MidiInstrumentMap>::iterator iterMap = midiMaps.find(Map);
        if (iterMap == midiMaps.end()) {
            midiMapsMutex.Unlock();
            throw Exception("There is no MIDI instrument map " + ToString(Map));
        }
        iterMap->second.name = NewName;
        midiMapsMutex.Unlock();
    }

    void MidiInstrumentMapper::RemoveMap(int Map) {
        midiMapsMutex.Lock();
        midiMaps.erase(Map);
        midiMapsMutex.Unlock();
    }

    void MidiInstrumentMapper::RemoveAllMaps() {
        midiMapsMutex.Lock();
        midiMaps.clear();
        midiMapsMutex.Unlock();
    }

    optional<MidiInstrumentMapper::entry_t> MidiInstrumentMapper::GetEntry(int Map, midi_prog_index_t Index) {
        optional<entry_t> result;
        midiMapsMutex.Lock();
        std::map<int,MidiInstrumentMap>::iterator iterMap = midiMaps.find(Map);
        if (iterMap != midiMaps.end()) { // map found
            std::map<midi_prog_index_t,private_entry_t>::iterator iterEntry = iterMap->second.find(Index);
            if (iterEntry != iterMap->second.end()) {
                entry_t entry;
                entry.EngineName      = iterEntry->second.EngineName;
                entry.InstrumentFile  = iterEntry->second.InstrumentFile;
                entry.InstrumentIndex = iterEntry->second.InstrumentIndex;
                entry.Volume          = iterEntry->second.Volume;
                //TODO: for now we skip the LoadMode and Name entry here, since we don't need it in the MidiInputPort
                result = entry;
            }
        }
        midiMapsMutex.Unlock();
        return result;
    }

} // namespace LinuxSampler
