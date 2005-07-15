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

#ifndef __LS_GIG_EGADSR_H__
#define __LS_GIG_EGADSR_H__

#include <math.h>

#include "../../common/global.h"
#include "../../common/RTMath.h"
#include "../../common/Pool.h"
#include "../common/Event.h"
#include "Manipulator.h"
#include "Engine.h"

namespace LinuxSampler { namespace gig {

/**
 * ADSR Envelope Generator
 *
 * Envelope Generator with stage 'Attack', 'Attack_Hold', 'Decay_1',
 * 'Decay_2', 'Sustain' and 'Release' for modulating arbitrary synthesis
 * parameters.
 */
class EGADSR {
    public:
        enum stage_t {
            stage_attack,
            stage_attack_hold,
            stage_decay1_init,
            stage_decay1,
            stage_decay1_part2_init,
            stage_decay1_part2,
            stage_decay2_init,
            stage_decay2,
            stage_sustain,
            stage_release_init,
            stage_release,
            stage_release_part2_init,
            stage_release_part2,
            stage_fadeout,
            stage_end
        };

        EGADSR(gig::Engine* pEngine, Event::destination_t ModulationDestination);
        void Process(uint TotalSamples, RTList<Event>* pEvents, RTList<Event>::Iterator itTriggerEvent, double SamplePos, double CurrentPitch, RTList<Event>::Iterator itKillEvent = RTList<Event>::Iterator());
        void Trigger(uint PreAttack, double AttackTime, bool HoldAttack, long LoopStart, double Decay1Time, double Decay2Time, bool InfiniteSustain, uint SustainLevel, double ReleaseTime, uint Delay, float Volume);
        void CalculateFadeOutCoeff(float FadeOutTime, float SampleRate);
        inline EGADSR::stage_t GetStage() { return Stage; }
    protected:
        gig::Engine* pEngine;
        Event::destination_t ModulationDestination;
        uint    TriggerDelay;      ///< number of sample points triggering should be delayed
        float   Level;
        stage_t Stage;
        float   AttackCoeff;
        long    AttackStepsLeft;   ///< number of sample points til end of attack stage
        bool    HoldAttack;
        long    LoopStart;
        float   Decay1Coeff;
        float   Decay1Coeff2;
        float   Decay1Coeff3;
        float   Decay1Level2;
        float   Decay1Slope;
        long    Decay1StepsLeft;   ///< number of sample points in Decay1 stage
        float   Decay2Coeff;
        long    Decay2StepsLeft;
        bool	InfiniteSustain;
        float   SustainLevel;
        float   ReleaseCoeff;
        float   ReleaseCoeff2;
        float   ReleaseCoeff3;
        float   ReleaseLevel2;
        float   ReleaseSlope;
        long    ReleaseStepsLeft;  ///< number of sample points til end of release stage
        bool    ReleasePostponed;  ///< If a "release" event occured in the previous audio fragment, but wasn't processed yet.
        float   ExpOffset;
        float   FadeOutCoeff;      ///< very fast ramp down for e.g. voice stealing
};

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_EGADSR_H__
