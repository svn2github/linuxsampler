/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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

#include "lscpinstrumentloader.h"

LSCPInstrumentLoader::LSCPInstrumentLoader() : Thread(false, 0, -4) {
    pQueue = new RingBuffer<command_t>(INSTRUMENT_LOADER_QUEUE_SIZE);
}

LSCPInstrumentLoader::~LSCPInstrumentLoader() {
    if (pQueue) delete pQueue;
}

/**
 * @brief Order loading of a new instrument.
 * The request will go into a queue waiting to be processed by the loader
 * thread. This method will immediately return and the instrument will be
 * loaded in the background.
 *
 * @param Filename - file name of the instrument
 * @param uiInstrumentIndex - index of the instrument within the file
 * @param pEngine - engine on which the instrument should be loaded
 */
void LSCPInstrumentLoader::StartNewLoad(String Filename, uint uiInstrumentIndex, Engine* pEngine) {
    command_t cmd;
    cmd.pFilename         = new String(Filename);
    cmd.uiInstrumentIndex = uiInstrumentIndex;
    cmd.pEngine           = pEngine;
    pQueue->push(&cmd);
    StartThread(); // ensure thread is running
    conditionJobsLeft.Set(true); // wake up thread
}

// Entry point for the InstrumentLoader Thread.
int LSCPInstrumentLoader::Main() {
    while (true) {
        while (pQueue->read_space()) {
            command_t cmd;
            pQueue->pop(&cmd);
            try {
                cmd.pEngine->LoadInstrument(cmd.pFilename->c_str(), cmd.uiInstrumentIndex);
            }
            catch (LinuxSamplerException e) {
                e.PrintMessage();
            }
            delete cmd.pFilename;
            // Always re-enable the engine.
            cmd.pEngine->Enable();
        }

        // nothing left to do, sleep until new jobs arrive
        conditionJobsLeft.WaitIf(false);
        // reset flag
        conditionJobsLeft.Set(false);
        // unlock condition object so it can be turned again by other thread
        conditionJobsLeft.Unlock();
    }
}
