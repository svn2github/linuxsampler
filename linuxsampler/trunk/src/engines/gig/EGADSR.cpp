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

#include "EGADSR.h"

namespace LinuxSampler { namespace gig {

    EGADSR::EGADSR() {
        enterEndStage();
        Level = 0.0;
        CalculateFadeOutCoeff(CONFIG_EG_MIN_RELEASE_TIME, 44100.0); // even if the sample rate will be 192kHz it won't hurt at all
    }

    void EGADSR::CalculateFadeOutCoeff(float FadeOutTime, float SampleRate) {
        const float killSteps = FadeOutTime * SampleRate;
        FadeOutCoeff = -1.0f / killSteps;
    }

    void EGADSR::update(event_t Event, double SamplePos, float CurrentPitch, uint SampleRate) {
        switch (Stage) {
            case stage_attack:
                if (StepsLeft) {
                    PostponedEvent = Event;
                } else {
                    if (Event == event_release)
                        enterReleasePart1Stage();
                    else if (Event == event_cancel_release)
                        enterSustainStage();
                    else if (PostponedEvent == event_release)
                        enterReleasePart1Stage();
                    else if (PostponedEvent == event_cancel_release)
                        enterSustainStage();
                    else if (HoldAttack)
                        enterAttackHoldStage(SamplePos, CurrentPitch);
                    else
                        enterDecay1Part1Stage(SampleRate);
                }
                break;
            case stage_attack_hold:
                switch (Event) {
                    case event_stage_end:
                        enterDecay1Part1Stage(SampleRate);
                        break;
                    case event_release:
                        enterReleasePart1Stage();
                        break;
                    case event_cancel_release:
                        if (InfiniteSustain)
                            enterSustainStage();
                        else
                            enterDecay1Part1Stage(SampleRate);
                        break;
                }
                break;
            case stage_decay1_part1:
                switch (Event) {
                    case stage_end:
                        enterDecay1Part2Stage();
                        break;
                    case event_release:
                        enterReleasePart1Stage();
                        break;
                    case event_cancel_release:
                        if (InfiniteSustain)
                            enterSustainStage();
                        else
                            enterDecay2Stage(SampleRate);
                        break;
                }
                break;
            case stage_decay1_part2:
                switch (Event) {
                    case event_release:
                        enterReleasePart1Stage();
                        break;
                    case event_stage_end: // fall through
                    case event_cancel_release:
                        if (InfiniteSustain)
                            enterSustainStage();
                        else
                            enterDecay2Stage(SampleRate);
                        break;
                }
                break;
            case stage_decay2:
                switch (Event) {
                    case event_stage_end:
                        enterFadeOutStage();
                        break;
                    case event_release:
                        enterReleasePart1Stage();
                        break;
                }
                break;
            case stage_sustain:
                switch (Event) {
                    case event_stage_end: {// just refresh time
                        const int intMax = (unsigned int) -1 >> 1;
                        StepsLeft = intMax; // we use the highest possible value
                        break;
                    }
                    case event_release:
                        enterReleasePart1Stage();
                        break;
                }
                break;
            case stage_release_part1:
                switch (Event) {
                    case event_stage_end:
                        enterReleasePart2Stage();
                        break;
                    case event_cancel_release:
                        if (InfiniteSustain)
                            enterSustainStage();
                        else
                            enterDecay2Stage(SampleRate);
                        break;
                }
                break;
            case stage_release_part2:
                switch (Event) {
                    case event_stage_end:
                        enterFadeOutStage();
                        break;
                    case event_cancel_release:
                        if (InfiniteSustain)
                            enterSustainStage();
                        else
                            enterDecay2Stage(SampleRate);
                        break;
                }
                break;
            case stage_fadeout:
                switch (Event) {
                    case event_stage_end:
                        enterEndStage();
                        break;
                }
                break;
        }
    }

    void EGADSR::trigger(uint PreAttack, float AttackTime, bool HoldAttack, long LoopStart, float Decay1Time, double Decay2Time, bool InfiniteSustain, uint SustainLevel, float ReleaseTime, float Volume, uint SampleRate) {

        enterAttackStage(PreAttack, AttackTime, SampleRate, 0.0, 1.0f);

        if (SustainLevel) {
            this->SustainLevel = SustainLevel / 1000.0;
        } else {
            // sustain level 0 means that voice dies after decay 1
            this->SustainLevel = CONFIG_EG_BOTTOM;
            InfiniteSustain    = false;
            Decay2Time         = CONFIG_EG_MIN_RELEASE_TIME;
        }
        this->InfiniteSustain  = InfiniteSustain;
        this->HoldAttack       = HoldAttack;
        this->LoopStart        = LoopStart;

        this->Decay1Time = Decay1Time;
        this->Decay2Time = Decay2Time;

        invVolume = 1 / Volume;
        ExpOffset = (0.25 - 1 / 3.55) * invVolume;

        // calculate release stage parameters (lin+exp curve)
        if (ReleaseTime < CONFIG_EG_MIN_RELEASE_TIME) ReleaseTime = CONFIG_EG_MIN_RELEASE_TIME;  // to avoid click sounds at the end of the sample playback
        const float ReleaseStepsLeft = (long) (ReleaseTime * SampleRate);
        ReleaseSlope  = 1.365 * (0 - 1) / ReleaseStepsLeft;
        ReleaseCoeff  = ReleaseSlope * invVolume;
        ReleaseSlope  *= 3.55;
        ReleaseCoeff2 = exp(ReleaseSlope);
        ReleaseCoeff3 = ExpOffset * (1 - ReleaseCoeff2);
        ReleaseLevel2 = 0.25 * invVolume;
    }

    void EGADSR::enterAttackStage(const uint PreAttack, const float AttackTime, const uint SampleRate, const double SamplePos, const float CurrentPitch) {
        Stage   = stage_attack;
        Segment = segment_lin;
        // Measurements of GSt output shows that the real attack time
        // is about 65.5% of the value specified in the gig file.
        StepsLeft = (int) (0.655f * AttackTime * SampleRate);
        if (StepsLeft) {
            Level = (float) PreAttack / 1000.0;
            Coeff = 0.896f * (1.0f - Level) / StepsLeft; // max level is a bit lower if attack != 0
        } else { // immediately jump to the next stage
            if (HoldAttack) enterAttackHoldStage(SamplePos, CurrentPitch);
            else            enterDecay1Part1Stage(SampleRate);
        }
        PostponedEvent = (event_t) -1; // init with anything except release or cancel_release
    }

    void EGADSR::enterAttackHoldStage(const double SamplePos, const float CurrentPitch) {
        Stage     = stage_attack_hold;
        Segment   = segment_lin;
        Coeff     = 0.0f; // don't rise anymore
        StepsLeft = (int) (LoopStart - SamplePos / CurrentPitch); // FIXME: just an approximation, inaccuracy grows with higher audio fragment size, sufficient for usual fragment sizes though
    }

    void EGADSR::enterDecay1Part1Stage(const uint SampleRate) {
        // The decay1 and release stage both consist of two parts,
        // first a linear curve, f, followed by an exponential curve,
        // g:
        //
        // f(x + d) = f(x) + Coeff
        // g(x + d) = Coeff2 * g(x) + Coeff3
        //
        // (where d is 1/SampleRate). The transition from f to g is
        // done when f(x) has reached Level2 = 25% of full volume.
        StepsLeft = (int) (Decay1Time * SampleRate);
        if (StepsLeft && SustainLevel < 1.0) {
            Stage        = stage_decay1_part1;
            Segment      = segment_lin;
            Decay1Slope  = 1.365 * (SustainLevel - 1.0) / StepsLeft;
            Coeff        = Decay1Slope * invVolume;
            Decay1Level2 = 0.25 * invVolume;
            StepsLeft    = int((RTMath::Max(Decay1Level2, SustainLevel) - Level) / Coeff);
        } else {
            Level = SustainLevel;
            if (InfiniteSustain) enterSustainStage();
            else                 enterDecay2Stage(SampleRate);
        }
    }

    void EGADSR::enterDecay1Part2Stage() {
        Stage   = stage_decay1_part2;
        Segment = segment_exp;
        Decay1Slope *= 3.55;
        Coeff  = exp(Decay1Slope);
        Offset = ExpOffset * (1 - Coeff);
        Level  = Decay1Level2;
        StepsLeft = int(log((SustainLevel - ExpOffset) / (Level - ExpOffset)) / Decay1Slope);
    }

    void EGADSR::enterDecay2Stage(const uint SampleRate) {
        Stage      = stage_decay2;
        Segment    = segment_lin;
        Decay2Time = RTMath::Max(Decay2Time, CONFIG_EG_MIN_RELEASE_TIME);
        StepsLeft  = (int) (Decay2Time * SampleRate);
        Coeff      = (-1.03 / StepsLeft) * invVolume;
        //FIXME: do we really have to calculate 'StepsLeft' two times?
        StepsLeft  = int((CONFIG_EG_BOTTOM - Level) / Coeff);
    }

    void EGADSR::enterSustainStage() {
        Stage   = stage_sustain;
        Segment = segment_lin;
        Coeff   = 0.0f; // don't change the envelope level in this stage
        const int intMax = (unsigned int) -1 >> 1;
        StepsLeft = intMax; // we use the highest value possible (we refresh StepsLeft in update() in case)
    }

    void EGADSR::enterReleasePart1Stage() {
        Stage     = stage_release_part1;
        Segment   = segment_lin;
        StepsLeft = int((ReleaseLevel2 - Level) / ReleaseCoeff);
        Coeff     = ReleaseCoeff;
    }

    void EGADSR::enterReleasePart2Stage() {
        Stage     = stage_release_part2;
        Segment   = segment_exp;
        StepsLeft = int(log((CONFIG_EG_BOTTOM - ExpOffset) / (Level - ExpOffset)) / ReleaseSlope);
        Coeff     = ReleaseCoeff2;
        Offset    = ReleaseCoeff3;
    }

    void EGADSR::enterFadeOutStage() {
        Stage     = stage_fadeout;
        Segment   = segment_lin;
        StepsLeft = int(Level / (-FadeOutCoeff));
        Coeff     = FadeOutCoeff;
    }

    void EGADSR::enterEndStage() {
        Stage   = stage_end;
        Segment = segment_end;
    }

}} // namespace LinuxSampler::gig
