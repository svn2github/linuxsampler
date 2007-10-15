/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
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

#include "InstrumentManager.h"

#include "InstrumentManagerThread.h"
#include "../common/Mutex.h"

namespace LinuxSampler {

    // the thread which actually loads the instruments one by one
    InstrumentManagerThread thread;

    // used to prevent multiple threads writing to the instrumentLoader at the same time
    Mutex loaderMutex;

    void InstrumentManager::LoadInstrumentInBackground(InstrumentManager::instrument_id_t ID, EngineChannel* pEngineChannel) {
        loaderMutex.Lock();
        thread.StartNewLoad(ID.FileName, ID.Index, pEngineChannel);
        loaderMutex.Unlock();
    }

    void InstrumentManager::SetModeInBackground(const instrument_id_t& ID, mode_t Mode) {
        loaderMutex.Lock();
        thread.StartSettingMode(this, ID, Mode);
        loaderMutex.Unlock();
    }

} // namespace LinuxSampler
