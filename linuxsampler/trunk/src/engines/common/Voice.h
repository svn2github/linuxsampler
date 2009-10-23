/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003,2004 by Benno Senoner and Christian Schoenebeck    *
 *   Copyright (C) 2005-2009 Christian Schoenebeck                         *
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

#ifndef __LS_VOICE_H__
#define	__LS_VOICE_H__

#include "Event.h"
#include "../../common/Pool.h"

namespace LinuxSampler {

    class Voice {
        public:
            enum playback_state_t {
                playback_state_end  = 0,
                playback_state_init = 1,
                playback_state_ram  = 2,
                playback_state_disk = 3
            };

            // Types
            enum type_t {
                type_normal,
                type_release_trigger_required,  ///< If the key of this voice will be released, it causes a release triggered voice to be spawned
                type_release_trigger            ///< Release triggered voice which cannot be killed by releasing its key
            };
    };
} // namespace LinuxSampler

#endif	/* __LS_VOICE_H__ */

