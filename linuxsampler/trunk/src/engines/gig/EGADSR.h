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

#include "../../common/global.h"
#include "../../common/RTMath.h"

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

        /**
         * Used to define what kind of segment the envelope currently is at.
         */
        enum segment_t {
            segment_end = 0, ///< final end state of envelope reached
            segment_lin = 1, ///< envelope is currently at a linear segment
            segment_exp = 2  ///< envelope is currently at a exponental segment
        };

        /**
         * Used to inform the EG about an event.
         */
        enum event_t {
            event_stage_end,
            event_release,
            event_cancel_release
        };

        /**
         * Constructor
         */
        EGADSR();

        /**
         * Change fade out time.
         */
        void CalculateFadeOutCoeff(float FadeOutTime, float SampleRate);

        /**
         * Will be called by the voice when the key / voice was triggered.
         *
         * @param PreAttack       - Preattack value for the envelope
         *                          (0 - 1000 permille)
         * @param AttackTime      - Attack time for the envelope
         *                          (0.000 - 60.000s)
         * @param HoldAttack      - if true, Decay1 will be postponed until the
         *                          sample reached the sample loop start.
         * @param LoopStart       - sample position where sample loop starts
         *                          (if any)
         * @param Decay1Time      - Decay1 time of the sample amplitude EG
         *                          (0.000 - 60.000s)
         * @param Decay2Time      - only if !InfiniteSustain: 2nd decay stage
         *                          time of the sample amplitude EG
         *                          (0.000 - 60.000s)
         * @param InfiniteSustain - if true, instead of going into Decay2
         *                          stage, Decay1 level will be hold until note
         *                          will be released
         * @param SustainLevel    - Sustain level of the sample amplitude EG
         *                          (0 - 1000 permille)
         * @param ReleaseTIme     - Release time for the envelope
         *                          (0.000 - 60.000s)
         * @param Volume          - volume the sample will be played at
         *                          (0.0 - 1.0) - used when calculating the
         *                          exponential curve parameters.
         * @param SampleRate      - sample rate of used audio output driver
         */
        void trigger(uint PreAttack, float AttackTime, bool HoldAttack, long LoopStart, float Decay1Time, double Decay2Time, bool InfiniteSustain, uint SustainLevel, float ReleaseTime, float Volume, uint SampleRate); //FIXME: we should better use 'float' for SampleRate

        /**
         * Returns true in case envelope hasn't reached its final end state yet.
         */
        inline bool active() {
            return (bool) Segment;
        }

        /**
         * Returns what kind of segment the envelope currently is at.
         */
        inline segment_t getSegmentType() {
            return Segment;
        }

        /**
         * Advance envelope by \a SamplePoints steps.
         */
        inline void increment(int SamplePoints) {
            StepsLeft = RTMath::Max(0, StepsLeft - SamplePoints);
        }

        /**
         * Returns amount of steps until the end of current envelope stage.
         */
        inline int toStageEndLeft() {
            return StepsLeft;
        }

        /**
         * Should be called to inform the EG about an external event and
         * also whenever an envelope stage is completed. This will handle
         * the envelope's transition to the respective next stage.
         *
         * @param Event        - what happened
         * @param SamplePos    - current sample playback position
         * @param CurrentPitch - current frequency alternation quotient
         */
        void update(event_t Event, double SamplePos, float CurrentPitch, uint SampleRate);

        /**
         * Calculates exactly one, the next sample point of EG
         * (linear segment). Call this if envelope is currently in a linear
         * segment.
         *
         * @returns next envelope level
         */
        inline float processLin() {
            return (Level += Coeff);
        }

        /**
         * Calculates exactly one, the next sample point of EG
         * (exponential segment). Call this if envelope is currently in an
         * exponential segment.
         *
         * @returns next envelope level
         */
        inline float processExp() {
            return (Level = Level * Coeff + Offset);
        }

        /**
         * Returns current envelope level without modifying anything. This
         * might be needed once the envelope reached its final end state,
         * because calling processLin() or processExp() at this point will
         * result in undesired behavior.
         */
        inline float getLevel() {
            return Level;
        }

    private:

        enum stage_t {
            stage_attack,
            stage_attack_hold,
            stage_decay1_part1,
            stage_decay1_part2,
            stage_decay2,
            stage_sustain,
            stage_release_part1,
            stage_release_part2,
            stage_fadeout,
            stage_end
        };

        float     Level;
        float     Coeff;
        float     Offset;
        int       StepsLeft;
        segment_t Segment;
        stage_t   Stage;
        event_t   PostponedEvent; ///< only used in Attack stage to postpone transition events until attack time is reached
        bool      HoldAttack;
        bool      InfiniteSustain;
        long      LoopStart;
        float     Decay1Time;
        float     Decay1Level2;
        float     Decay1Slope;
        float     Decay2Time;
        float     SustainLevel;
        float     ReleaseCoeff;
        float     ReleaseCoeff2;
        float     ReleaseCoeff3;
        float     ReleaseLevel2;
        float     ReleaseSlope;
        float     invVolume;
        float     ExpOffset;
        float     FadeOutCoeff; ///< very fast ramp down for e.g. voice stealing

        void enterAttackStage(const uint PreAttack, const float AttackTime, const uint SampleRate, const double SamplePos, const float CurrentPitch);
        void enterAttackHoldStage(const double SamplePos, const float CurrentPitch);
        void enterDecay1Part1Stage(const uint SampleRate);
        void enterDecay1Part2Stage(const uint SampleRate);
        void enterDecay2Stage(const uint SampleRate);
        void enterSustainStage();
        void enterReleasePart1Stage();
        void enterReleasePart2Stage();
        void enterFadeOutStage();
        void enterEndStage();
};

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_EGADSR_H__
