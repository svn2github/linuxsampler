/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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

#ifndef __LS_GIG_EGDECAY_H__
#define __LS_GIG_EGDECAY_H__

#include "../../common/global.h"

#if DEBUG_HEADERS
# warning EGDecay.h included
#endif // DEBUG_HEADERS

#include "../../common/RTMath.h"
#include "../common/Event.h"
#include "Engine.h"

namespace LinuxSampler { namespace gig {

    // just symbol prototyping
    class Engine;

    /**
     * Decay Envelope Generator
     *
     * Simple Envelope Generator with only one stage: 'Decay'. We currently use
     * this specific EG only for pitch and thus it's not generalized yet, means
     * the initial envelope level (given by 'Depth') will raise / drop in
     * 'DecayTime' seconds to a level of exactly 1.0. If the initial level
     * ('Depth') is already 1.0, nothing happens. Beside that, the EG just
     * multiplies it's levels to the synthesis parameter sequence.
     */
    class EGDecay {
        public:
            EGDecay(gig::Engine* pEngine, Event::destination_t ModulationDestination);
            bool Process(uint Samples);
            void Trigger(float Depth, double DecayTime, uint Delay);
        protected:
            gig::Engine* pEngine;
            Event::destination_t ModulationDestination;
            uint  TriggerDelay;    ///< number of sample points triggering should be delayed
            float Level;
            float DecayCoeff;
            long  DecayStepsLeft;
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_EGDECAY_H__
