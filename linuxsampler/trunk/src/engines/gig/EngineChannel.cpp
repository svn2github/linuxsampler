/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003,2004 by Benno Senoner and Christian Schoenebeck    *
 *   Copyright (C) 2005-2008 Christian Schoenebeck                         *
 *   Copyright (C) 2009-2010 Christian Schoenebeck and Grigor Iliev        *
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

namespace LinuxSampler { namespace gig {
    EngineChannel::EngineChannel() {
        
    }

    EngineChannel::~EngineChannel() {
        DisconnectAudioOutputDevice();
        // In case the channel was removed before the instrument was
        // fully loaded, try to give back instrument again (see bug #113)
        InstrumentChangeCmd< ::gig::DimensionRegion, ::gig::Instrument>& cmd = ChangeInstrument(NULL);
        if (cmd.pInstrument) {
            Engine::instruments.HandBack(cmd.pInstrument, this);
        }
        ///////
    }

    AbstractEngine::Format EngineChannel::GetEngineFormat() { return AbstractEngine::GIG; }

    /** This method is not thread safe! */
    void EngineChannel::ResetInternal() {
        CurrentKeyDimension = 0;
        EngineChannelBase<Voice, ::gig::DimensionRegion, ::gig::Instrument>::ResetInternal();
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
     * Load an instrument from a .gig file. PrepareLoadInstrument() has to
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
        InstrumentChangeCmd< ::gig::DimensionRegion, ::gig::Instrument>& cmd = ChangeInstrument(0);
        if (cmd.pInstrument) {
            // give old instrument back to instrument manager, but
            // keep the dimension regions and samples that are in use
            pInstrumentManager->HandBackInstrument(cmd.pInstrument, this, cmd.pRegionsInUse);
        }
        cmd.pRegionsInUse->clear();

        // delete all key groups
        DeleteGroupEventLists();

        // request gig instrument from instrument manager
        ::gig::Instrument* newInstrument;
        try {
            InstrumentManager::instrument_id_t instrid;
            instrid.FileName  = InstrumentFile;
            instrid.Index     = InstrumentIdx;

            newInstrument = pInstrumentManager->Borrow(instrid, this);
            if (!newInstrument) {
                throw InstrumentManagerException("resource was not created");
            }
        }
        catch (RIFF::Exception e) {
            InstrumentStat = -2;
            StatusChanged(true);
            String msg = "gig::Engine error: Failed to load instrument, cause: " + e.Message;
            throw Exception(msg);
        }
        catch (InstrumentManagerException e) {
            InstrumentStat = -3;
            StatusChanged(true);
            String msg = "gig::Engine error: Failed to load instrument, cause: " + e.Message();
            throw Exception(msg);
        }
        catch (...) {
            InstrumentStat = -4;
            StatusChanged(true);
            throw Exception("gig::Engine error: Failed to load instrument, cause: Unknown exception while trying to parse gig file.");
        }

        RoundRobinIndex = 0;
        for (int i = 0 ; i < 128 ; i++) pMIDIKeyInfo[i].pRoundRobinIndex = NULL;

        // rebuild ActiveKeyGroups map with key groups of current
        // instrument and set the round robin pointers to use one
        // counter for each region
        int region = 0;
        for (::gig::Region* pRegion = newInstrument->GetFirstRegion(); pRegion; pRegion = newInstrument->GetNextRegion()) {
            AddGroup(pRegion->KeyGroup);

            RoundRobinIndexes[region] = 0;
            for (int iKey = pRegion->KeyRange.low; iKey <= pRegion->KeyRange.high; iKey++) {
                pMIDIKeyInfo[iKey].pRoundRobinIndex = &RoundRobinIndexes[region];
            }
            region++;
        }

        InstrumentIdxName = newInstrument->pInfo->Name;
        InstrumentStat = 100;

        ChangeInstrument(newInstrument);

        StatusChanged(true);
    }

    void EngineChannel::ProcessKeySwitchChange(int key) {
        // Change key dimension value if key is in keyswitching area
        {
            if (key >= pInstrument->DimensionKeyRange.low && key <= pInstrument->DimensionKeyRange.high)
                CurrentKeyDimension = float(key - pInstrument->DimensionKeyRange.low) /
                    (pInstrument->DimensionKeyRange.high - pInstrument->DimensionKeyRange.low + 1);
        }
    }

}} // namespace LinuxSampler::gig
