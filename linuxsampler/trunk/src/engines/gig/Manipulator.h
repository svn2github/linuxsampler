/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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

#ifndef __LS_GIG_MANIPULATOR_H__
#define __LS_GIG_MANIPULATOR_H__

#include "../../common/global.h"
#include "Engine.h"

namespace LinuxSampler { namespace gig {

    // The following template classes are used for composition with general
    // Modulation classes like the LFO template. The modulator calls the
    // ApplyLevel() method of the respective manipulator when its level has
    // changed and the manipulator actually decides what to do with the
    // modulation signal the modulator (e.g. LFO) provides.

    /**
     * Abstract base class for all Gig manipulator classes.
     */
    class BaseManipulator {
        public:
            BaseManipulator(gig::Engine* pEngine) {
                this->pEngine = pEngine;
            }
        protected:
            gig::Engine* pEngine;
    };

    /** Amplification Manipulator
     *
     * Specialized manipulator for writing volume parameters to the synthesis
     * parameter matrix of the Gig Engine.
     */
    class VCAManipulator : public BaseManipulator {
        public:
            VCAManipulator(gig::Engine* pEngine) : BaseManipulator(pEngine) {}
            inline void ApplyLevel(float& Level, int& iSample) {
                pEngine->pSynthesisParameters[Event::destination_vca][iSample] *= Level;
            }
    };

    /** Filter Cutoff Frequency Manipulator
     *
     * Specialized manipulator for writing filter cutoff frequency parameters to
     * the synthesis parameter matrix of the Gig Engine.
     */
    class VCFCManipulator : public BaseManipulator {
        public:
            VCFCManipulator(gig::Engine* pEngine) : BaseManipulator(pEngine) {}
            inline void ApplyLevel(float& Level, int& iSample) {
                pEngine->pSynthesisParameters[Event::destination_vcfc][iSample] *= Level;
            }
    };

    /** Pitch Manipulator
     *
     * Specialized manipulator for writing pitch parameters to the synthesis
     * parameter matrix of the Gig Engine.
     */
    class VCOManipulator : public BaseManipulator {
        public:
            VCOManipulator(gig::Engine* pEngine) : BaseManipulator(pEngine) {}
            inline void ApplyLevel(float& Level, int& iSample) {
                pEngine->pSynthesisParameters[Event::destination_vco][iSample] *= RTMath::CentsToFreqRatio(Level);
            }
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_MANIPULATOR_H__
