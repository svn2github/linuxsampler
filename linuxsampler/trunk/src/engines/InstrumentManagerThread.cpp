/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
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

#include "InstrumentManagerThread.h"

namespace LinuxSampler {

    InstrumentManagerThread::InstrumentManagerThread() : Thread(true, false, 0, -4) {
    }

    InstrumentManagerThread::~InstrumentManagerThread() {
    }

    /**
     * @brief Order loading of a new instrument.
     *
     * The request will go into a queue waiting to be processed by the
     * class internal task thread. This method will immediately return and
     * the instrument will be loaded in the background.
     *
     * @param Filename - file name of the instrument
     * @param uiInstrumentIndex - index of the instrument within the file
     * @param pEngineChannel - engine channel on which the instrument should be loaded
     */
    void InstrumentManagerThread::StartNewLoad(String Filename, uint uiInstrumentIndex, EngineChannel* pEngineChannel) {
        dmsg(1,("Scheduling '%s' (Index=%d) to be loaded in background (if not loaded yet).\n",Filename.c_str(),uiInstrumentIndex));
        // already tell the engine which instrument to load
        pEngineChannel->PrepareLoadInstrument(Filename.c_str(), uiInstrumentIndex);

        command_t cmd;
        cmd.type           = command_t::DIRECT_LOAD;
        cmd.pEngineChannel = pEngineChannel;

        mutex.Lock();
        queue.push_back(cmd);
        mutex.Unlock();

        StartThread(); // ensure thread is running
        conditionJobsLeft.Set(true); // wake up thread
    }

    /**
     * @brief Order changing the life-time strategy of an instrument.
     *
     * The request will go into a queue waiting to be processed by the
     * class internal task thread. This method will immediately return and
     * in case the instrument has to be loaded due to a mode change to
     * PERSISTENT, it will be loaded in the background.
     *
     * @param pManager - InstrumentManager which manages the instrument
     * @param ID       - unique ID of the instrument
     * @param Mode     - life-time strategy to set for this instrument
     */
    void InstrumentManagerThread::StartSettingMode(InstrumentManager* pManager, const InstrumentManager::instrument_id_t& ID, InstrumentManager::mode_t Mode) {
        command_t cmd;
        cmd.type         = command_t::INSTR_MODE;
        cmd.pManager     = pManager;
        cmd.instrumentId = ID;
        cmd.mode         = Mode;

        mutex.Lock();
        queue.push_back(cmd);
        mutex.Unlock();

        StartThread(); // ensure thread is running
        conditionJobsLeft.Set(true); // wake up thread
    }

    // Entry point for the task thread.
    int InstrumentManagerThread::Main() {
        while (true) {
            while (!queue.empty()) {
                command_t cmd;

                // grab a new command from the queue
                mutex.Lock();
                cmd = queue.front();
                mutex.Unlock();

                try {
                    switch (cmd.type) {
                        case command_t::DIRECT_LOAD:
                            cmd.pEngineChannel->LoadInstrument();
                            break;
                        case command_t::INSTR_MODE:
                            cmd.pManager->SetMode(cmd.instrumentId, cmd.mode);
                            break;
                        default:
                            std::cerr << "InstrumentManagerThread: unknown command - BUG!\n" << std::flush;
                    }
                } catch (Exception e) {
                    e.PrintMessage();
                } catch (...) {
                    std::cerr << "InstrumentManagerThread: some exception occured, could not finish task\n" << std::flush;
                }

                // remove processed command from queue
                mutex.Lock();
                queue.pop_front();
                mutex.Unlock();
            }

            // nothing left to do, sleep until new jobs arrive
            conditionJobsLeft.WaitIf(false);
            // reset flag
            conditionJobsLeft.Set(false);
            // unlock condition object so it can be turned again by other thread
            conditionJobsLeft.Unlock();
        }
    }

} // namespace LinuxSampler
