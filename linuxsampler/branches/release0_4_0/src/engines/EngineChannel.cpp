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

#include "EngineChannel.h"

namespace LinuxSampler {

    EngineChannel::EngineChannel() {
        iMute = 0;
        bSolo = false;
    }

    void EngineChannel::SetMute(int state) throw (Exception) {
        if(iMute == state) return;
        if(state < -1 || state > 1)
            throw Exception("Invalid Mute state: " + ToString(state));

        iMute = state;

        StatusChanged(true);
    }

    int EngineChannel::GetMute() {
        return iMute;
    }

    void EngineChannel::SetSolo(bool solo) {
        if(bSolo == solo) return;
        bSolo = solo;
        StatusChanged(true);
    }

    bool EngineChannel::GetSolo() {
        return bSolo;
    }

} // namespace LinuxSampler
