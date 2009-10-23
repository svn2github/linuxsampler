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

#include "EngineChannel.h"
#include "Engine.h"

namespace LinuxSampler { namespace sfz {
    EngineChannel::EngineChannel() {
        for(int i = 0; i < 128; i++) PressedKeys[i] = false;
        LastKey = LastKeySwitch = -1;
        AddMidiKeyboardListener(this);
    }

    EngineChannel::~EngineChannel() {
        DisconnectAudioOutputDevice();
        RemoveMidiKeyboardListener(this);
        // In case the channel was removed before the instrument was
        // fully loaded, try to give back instrument again (see bug #113)
        InstrumentChangeCmd< ::sfz::Region, ::sfz::Instrument>& cmd = ChangeInstrument(NULL);
        if (cmd.pInstrument) {
                InstrumentResourceManager* instrs = dynamic_cast<InstrumentResourceManager*>(pEngine->GetInstrumentManager());
                instrs->HandBack(cmd.pInstrument, this);
        }
        ///////
    }

    AbstractEngine::Format EngineChannel::GetEngineFormat() { return AbstractEngine::SFZ; }

    /** This method is not thread safe! */
    void EngineChannel::ResetInternal() {
        CurrentKeyDimension = 0;
        EngineChannelBase<Voice, ::sfz::Region, ::sfz::Instrument>::ResetInternal();
        for(int i = 0; i < 128; i++) PressedKeys[i] = false;
    }

    /**
     *  Will be called by the MIDIIn Thread to signal that a program
     *  change should be performed. As a program change isn't
     *  real-time safe, the actual change is performed by the disk
     *  thread.
     *
     *  @param Program     - MIDI program change number
     */
    void EngineChannel::SendProgramChange(uint8_t Program) {
        Engine* engine = dynamic_cast<Engine*>(pEngine);
        if(engine == NULL) return;

        if(engine->GetDiskThread()) {
            engine->GetDiskThread()->OrderProgramChange(Program, this);
        } else {
            // TODO: 
        }
    }

    /**
     * Load an instrument from a .sfz file. PrepareLoadInstrument() has to
     * be called first to provide the information which instrument to load.
     * This method will then actually start to load the instrument and block
     * the calling thread until loading was completed.
     *
     * @see PrepareLoadInstrument()
     */
    void EngineChannel::LoadInstrument() {
        InstrumentResourceManager* pInstrumentManager = dynamic_cast<InstrumentResourceManager*>(pEngine->GetInstrumentManager());

        // make sure we don't trigger any new notes with an old
        // instrument
        InstrumentChangeCmd< ::sfz::Region, ::sfz::Instrument>& cmd = ChangeInstrument(0);
        if (cmd.pInstrument) {
            // give old instrument back to instrument manager, but
            // keep the dimension regions and samples that are in use
            pInstrumentManager->HandBackInstrument(cmd.pInstrument, this, cmd.pRegionsInUse);
        }
        cmd.pRegionsInUse->clear();

        // delete all key groups
        ActiveKeyGroups.clear();

        // request sfz instrument from instrument manager
        ::sfz::Instrument* newInstrument;
        try {
            InstrumentManager::instrument_id_t instrid;
            instrid.FileName  = InstrumentFile;
            instrid.Index     = InstrumentIdx;

            newInstrument = pInstrumentManager->Borrow(instrid, this);
            if (!newInstrument) {
                throw InstrumentManagerException("resource was not created");
            }
        }
        catch (InstrumentManagerException e) {
            InstrumentStat = -3;
            StatusChanged(true);
            String msg = "sfz::Engine error: Failed to load instrument, cause: " + e.Message();
            throw Exception(msg);
        }
        catch (::sfz::Exception e) {
            InstrumentStat = -3;
            StatusChanged(true);
            String msg = "sfz::Engine error: Failed to load instrument, cause: " + e.Message();
            throw Exception(msg);
        }
        catch (::std::runtime_error e) {
            InstrumentStat = -3;
            StatusChanged(true);
            String msg = "sfz::Engine error: Failed to load instrument, cause: ";
            msg += e.what();
            throw Exception(msg);
        }
        catch (...) {
            InstrumentStat = -4;
            StatusChanged(true);
            throw Exception("sfz::Engine error: Failed to load instrument, cause: Unknown exception while trying to parse sfz file.");
        }

        // rebuild ActiveKeyGroups map with key groups of current instrument
        //for (::gig::Region* pRegion = newInstrument->GetFirstRegion(); pRegion; pRegion = newInstrument->GetNextRegion())
        //    if (pRegion->KeyGroup) ActiveKeyGroups[pRegion->KeyGroup] = NULL;
        // TODO: ^^^

        InstrumentIdxName = newInstrument->GetName();
        InstrumentStat = 100;

        ChangeInstrument(newInstrument);

        StatusChanged(true);
    }

    void EngineChannel::ProcessKeySwitchChange(int key) { }

    void EngineChannel::PreProcessNoteOn(uint8_t key, uint8_t velocity) {
        LastKey = key;
        if(pInstrument != NULL && pInstrument->HasKeySwitchBinding(key)) LastKeySwitch = key;
        PressedKeys[key] = true;
    }

    void EngineChannel::PreProcessNoteOff(uint8_t key, uint8_t velocity) {
        PressedKeys[key] = false;
    }

}} // namespace LinuxSampler::sfz
