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

    const float EGADSR::FadeOutCoeff(CalculateFadeOutCoeff());

    float EGADSR::CalculateFadeOutCoeff() {
        const float sampleRate = 44100.0; // even if the sample rate will be 192kHz it won't hurt at all
        const float killSteps  = CONFIG_EG_MIN_RELEASE_TIME * sampleRate;
        return -1.0f / killSteps;
    }

    EGADSR::EGADSR(gig::Engine* pEngine, Event::destination_t ModulationDestination) {
        this->pEngine = pEngine;
        this->ModulationDestination = ModulationDestination;
        Stage = stage_end;
        Level = 0.0;
    }

    /**
     * Will be called by the voice for every audio fragment to let the EG
     * queue it's modulation changes for the current audio fragment.
     *
     * @param TotalSamples  - total number of sample points to be rendered in this
     *                        audio fragment cycle by the audio engine
     * @param pEvents       - event list with "release" and "cancel release" events
     * @param itTriggerEvent - event that caused triggering of the voice (only if
     *                        the voice was triggered in the current audio
     *                        fragment, NULL otherwise)
     * @param SamplePos     - current playback position
     * @param CurrentPitch  - current pitch value for playback
     * @param itKillEvent   - (optional) event which caused this voice to be killed
     */
    void EGADSR::Process(uint TotalSamples, RTList<Event>* pEvents, RTList<Event>::Iterator itTriggerEvent, double SamplePos, double CurrentPitch, RTList<Event>::Iterator itKillEvent) {
        // skip all events which occured before this voice was triggered
        RTList<Event>::Iterator itTransitionEvent = (itTriggerEvent) ? ++itTriggerEvent : pEvents->first();

        // if the voice was killed in this fragment we only process the time before this kill event, then switch to 'stage_fadeout'
        int Samples = (itKillEvent) ? RTMath::Min(itKillEvent->FragmentPos(), pEngine->MaxFadeOutPos) : (int) TotalSamples;

        int iSample = TriggerDelay;

        #if CONFIG_DEVMODE
        if (TriggerDelay > TotalSamples) { // just a sanity check for debugging
            dmsg(1,("EGADSR: ERROR, TriggerDelay > Totalsamples\n"));
            int* i = NULL;
            (*i)++; // force a segfault
        }
        #endif // CONFIG_DEVMODE

        while (iSample < TotalSamples) {

            // if the voice was killed in this fragment and we already processed the time before this kill event
            if (itKillEvent && iSample >= Samples) Stage = stage_fadeout;

            switch (Stage) {
                case stage_attack: {
                    TriggerDelay = 0;
                    int to_process   = RTMath::Min(AttackStepsLeft, Samples - iSample);
                    int process_end  = iSample + to_process;
                    AttackStepsLeft -= to_process;
                    while (iSample < process_end) {
                        Level += AttackCoeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    if (iSample == TotalSamples && itTransitionEvent) { // postpone last transition event for the next audio fragment
                        RTList<Event>::Iterator itLastEvent = pEvents->last();
                        if (itLastEvent) ReleasePostponed = (itLastEvent->Type == Event::type_release);
                    }
                    if (!AttackStepsLeft) Stage = (ReleasePostponed) ? stage_release_init : (HoldAttack) ? stage_attack_hold : stage_decay1_init;
                    break;
                }
                case stage_attack_hold: {
                    if (SamplePos >= LoopStart) {
                        Stage = stage_decay1_init;
                        break;
                    }
                    int holdstepsleft = (int) (LoopStart - SamplePos / CurrentPitch); // FIXME: just an approximation, inaccuracy grows with higher audio fragment size, sufficient for usual fragment sizes though
                    int to_process    = RTMath::Min(holdstepsleft, Samples - iSample);
                    int process_end   = iSample + to_process;
                    if (itTransitionEvent && itTransitionEvent->FragmentPos() <= process_end) {
                        process_end       = itTransitionEvent->FragmentPos();
                        Stage             = (itTransitionEvent->Type == Event::type_release) ? stage_release_init : (InfiniteSustain) ? stage_sustain : stage_decay2_init;
                        ++itTransitionEvent;
                    }
                    else if (to_process == holdstepsleft) Stage = stage_decay1_init;
                    while (iSample < process_end) {
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_decay1_init: {
                    if (Decay1StepsLeft) {
                        if (SustainLevel < 1.0) {
                            Decay1StepsLeft = int((RTMath::Max(Decay1Level2, SustainLevel) - Level) / Decay1Coeff);
                        } else {
                            Stage = (InfiniteSustain) ? stage_sustain : stage_decay2_init;
                            break;
                        }
                    } else {
                        Level = SustainLevel;
                        Stage = (InfiniteSustain) ? stage_sustain : stage_decay2_init;
                        break;
                    }
                    Stage = stage_decay1;
                }
                case stage_decay1: {
                    int to_process   = RTMath::Min(Samples - iSample, Decay1StepsLeft);
                    int process_end  = iSample + to_process;
                    if (itTransitionEvent && itTransitionEvent->FragmentPos() <= process_end) {
                        process_end       = itTransitionEvent->FragmentPos();
                        Stage             = (itTransitionEvent->Type == Event::type_release) ? stage_release_init : (InfiniteSustain) ? stage_sustain : stage_decay2_init;
                        ++itTransitionEvent;
                    }
                    else {
                        Decay1StepsLeft -= to_process;
                        if (!Decay1StepsLeft) Stage = stage_decay1_part2_init;
                    }
                    while (iSample < process_end) {
                        Level += Decay1Coeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_decay1_part2_init:
                    Decay1StepsLeft = int(log((SustainLevel - ExpOffset) / (Level - ExpOffset)) / Decay1Slope);
                    Stage = stage_decay1_part2;
                case stage_decay1_part2: {
                    int to_process   = RTMath::Min(Samples - iSample, Decay1StepsLeft);
                    int process_end  = iSample + to_process;
                    if (itTransitionEvent && itTransitionEvent->FragmentPos() <= process_end) {
                        process_end       = itTransitionEvent->FragmentPos();
                        Stage             = (itTransitionEvent->Type == Event::type_release) ? stage_release_init : (InfiniteSustain) ? stage_sustain : stage_decay2_init;
                        ++itTransitionEvent;
                    }
                    else {
                        Decay1StepsLeft -= to_process;
                        if (!Decay1StepsLeft) Stage = (InfiniteSustain) ? stage_sustain : stage_decay2_init;
                    }
                    while (iSample < process_end) {
                        Level = Level * Decay1Coeff2 + Decay1Coeff3;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_decay2_init:
                    Decay2StepsLeft = int((CONFIG_EG_BOTTOM - Level) / Decay2Coeff);
                    Stage = stage_decay2;
                case stage_decay2: {
                    int to_process   = RTMath::Min(Samples - iSample, Decay2StepsLeft);
                    int process_end  = iSample + to_process;
                    if (itTransitionEvent && itTransitionEvent->Type == Event::type_release && itTransitionEvent->FragmentPos() <= process_end) {
                        process_end       = itTransitionEvent->FragmentPos();
                        ++itTransitionEvent;
                        Stage             = stage_release_init; // switch to release stage soon
                    }
                    else {
                        Decay2StepsLeft -= to_process;
                        if (!Decay2StepsLeft) Stage = stage_fadeout;
                    }
                    while (iSample < process_end) {
                        Level += Decay2Coeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_sustain: {
                    int process_end;
                    if (itTransitionEvent && itTransitionEvent->Type == Event::type_release && itTransitionEvent->FragmentPos() <= Samples) {
                        process_end       = itTransitionEvent->FragmentPos();
                        ++itTransitionEvent;
                        Stage             = stage_release_init; // switch to release stage soon
                    }
                    else process_end = Samples;
                    while (iSample < process_end) {
                       pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_release_init:
                    ReleaseStepsLeft = int((ReleaseLevel2 - Level) / ReleaseCoeff);
                    Stage = stage_release;
                case stage_release: {
                    int to_process   = RTMath::Min(Samples - iSample, ReleaseStepsLeft);
                    int process_end  = iSample + to_process;
                    if (itTransitionEvent && itTransitionEvent->Type == Event::type_cancel_release && itTransitionEvent->FragmentPos() <= process_end) {
                        process_end       = itTransitionEvent->FragmentPos();
                        ++itTransitionEvent;
                        Stage             = (InfiniteSustain) ? stage_sustain : stage_decay2_init; // switch back to sustain / decay2 stage soon
                    }
                    else {
                        ReleaseStepsLeft -= to_process;
                        if (!ReleaseStepsLeft) Stage = stage_release_part2_init;
                    }
                    while (iSample < process_end) {
                        Level += ReleaseCoeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_release_part2_init:
                    ReleaseStepsLeft = int(log((CONFIG_EG_BOTTOM - ExpOffset) / (Level - ExpOffset)) / ReleaseSlope);
                    Stage = stage_release_part2;
                case stage_release_part2: {
                    int to_process   = RTMath::Min(Samples - iSample, ReleaseStepsLeft);
                    int process_end  = iSample + to_process;
                    if (itTransitionEvent && itTransitionEvent->Type == Event::type_cancel_release && itTransitionEvent->FragmentPos() <= process_end) {
                        process_end       = itTransitionEvent->FragmentPos();
                        ++itTransitionEvent;
                        Stage             = (InfiniteSustain) ? stage_sustain : stage_decay2_init; // switch back to sustain / decay2 stage soon
                    }
                    else {
                        ReleaseStepsLeft -= to_process;
                        if (!ReleaseStepsLeft) Stage = stage_fadeout;
                    }
                    while (iSample < process_end) {
                        Level = Level * ReleaseCoeff2 + ReleaseCoeff3;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_fadeout: {
                    int to_process   = RTMath::Min(int(Level / (-FadeOutCoeff)), TotalSamples - iSample);
                    int process_end  = iSample + to_process;
                    while (iSample < process_end) {
                        Level += FadeOutCoeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    Stage = stage_end;
                    if (Level > -FadeOutCoeff) dmsg(1,("EGADSR: Warning, final fade out level too high, may result in click sound!\n"));
                } //Fall through here instead of breaking otherwise we can get back into stage_fadeout and loop forever!
                case stage_end: {
                    while (iSample < TotalSamples) {
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] = 0.0f;
                    }
                    break;
                }
            }
        }

        #if CONFIG_DEVMODE
        if (itKillEvent && Stage != stage_end) { // just a sanity check for debugging
            dmsg(1,("EGADSR: ERROR, voice killing not completed !!!\n"));
            dmsg(1,("EGADSR: Stage=%d,iSample=%d,Samples=%d, TotalSamples=%d, MaxFadoutPos=%d\n",Stage,iSample,Samples,TotalSamples,pEngine->MaxFadeOutPos));
        }
        #endif // CONFIG_DEVMODE
    }

    /**
     * Will be called by the voice when the key / voice was triggered.
     *
     * @param PreAttack       - Preattack value for the envelope (0 - 1000 permille)
     * @param AttackTime      - Attack time for the envelope (0.000 - 60.000s)
     * @param HoldAttack      - If true, Decay1 will be postponed until the sample reached the sample loop start.
     * @param LoopStart       - Sample position where sample loop starts (if any)
     * @param Decay1Time      - Decay1 time of the sample amplitude EG (0.000 - 60.000s).
     * @param Decay2Time      - Only if !InfiniteSustain: 2nd decay stage time of the sample amplitude EG (0.000 - 60.000s).
     * @param InfiniteSustain - If true, instead of going into Decay2 phase, Decay1 level will be hold until note will be released.
     * @param SustainLevel    - Sustain level of the sample amplitude EG (0 - 1000 permille).
     * @param ReleaseTIme     - Release time for the envelope (0.000 - 60.000s)
     * @param Delay           - Number of sample points triggering should be delayed.
     * @param Volume          - Volume the sample will be played at (0.0 - 1.0). Used when calculating the exponential curve parameters.
     */
    void EGADSR::Trigger(uint PreAttack, double AttackTime, bool HoldAttack, long LoopStart, double Decay1Time, double Decay2Time, bool InfiniteSustain, uint SustainLevel, double ReleaseTime, uint Delay, float Volume) {
        this->TriggerDelay     = Delay;
        this->Stage            = stage_attack;
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
        this->ReleasePostponed = false;

        // calculate attack stage parameters (lin. curve)

        // Measurements of GSt output shows that the real attack time
        // is about 65.5% of the value specified in the gig file.
        AttackStepsLeft = (long) (0.655 * AttackTime * pEngine->pAudioOutputDevice->SampleRate());
        if (AttackStepsLeft) {
            Level       = (float) PreAttack / 1000.0;
            AttackCoeff = 0.896 * (1.0 - Level) / AttackStepsLeft; // max level is a bit lower if attack != 0
        }
        else {
            Level       = 1.0;
            AttackCoeff = 0.0;
        }

        const float invVolume = 1 / Volume;
        ExpOffset = (0.25 - 1 / 3.55) * invVolume;

        // The decay1 and release stage both consist of two parts,
        // first a linear curve, f, followed by an exponential curve,
        // g:
        //
        // f(x + d) = f(x) + Coeff
        // g(x + d) = Coeff2 * g(x) + Coeff3
        //
        // (where d is 1/SampleRate). The transition from f to g is
        // done when f(x) has reached Level2 = 25% of full volume.

        // calculate decay1 stage parameters (lin+exp curve)
        Decay1StepsLeft = (long) (Decay1Time * pEngine->pAudioOutputDevice->SampleRate());
        if (Decay1StepsLeft) {
            Decay1Slope  = 1.365 * (this->SustainLevel - 1.0) / Decay1StepsLeft;
            Decay1Coeff  = Decay1Slope * invVolume;
            Decay1Slope  *= 3.55;
            Decay1Coeff2 = exp(Decay1Slope);
            Decay1Coeff3 = ExpOffset * (1 - Decay1Coeff2);
            Decay1Level2 = 0.25 * invVolume;
        }

        // calculate decay2 stage parameters (lin. curve)
        if (!InfiniteSustain) {
            if (Decay2Time < CONFIG_EG_MIN_RELEASE_TIME) Decay2Time = CONFIG_EG_MIN_RELEASE_TIME;
            long Decay2Steps = (long) (Decay2Time * pEngine->pAudioOutputDevice->SampleRate());
            Decay2Coeff = (-1.03 / Decay2Steps) * invVolume;
        }

        // calculate release stage parameters (lin+exp curve)
        if (ReleaseTime < CONFIG_EG_MIN_RELEASE_TIME) ReleaseTime = CONFIG_EG_MIN_RELEASE_TIME;  // to avoid click sounds at the end of the sample playback
        ReleaseStepsLeft = (long) (ReleaseTime * pEngine->pAudioOutputDevice->SampleRate());
        ReleaseSlope  = 1.365 * (0 - 1) / ReleaseStepsLeft;
        ReleaseCoeff  = ReleaseSlope * invVolume;
        ReleaseSlope  *= 3.55;
        ReleaseCoeff2 = exp(ReleaseSlope);
        ReleaseCoeff3 = ExpOffset * (1 - ReleaseCoeff2);
        ReleaseLevel2 = 0.25 * invVolume;

        dmsg(4,("PreAttack=%d, AttackLength=%d, AttackCoeff=%f, Decay1Coeff=%f, Decay2Coeff=%f, ReleaseLength=%d, ReleaseCoeff=%f\n",
                PreAttack, AttackStepsLeft, AttackCoeff, Decay1Coeff, Decay2Coeff, ReleaseStepsLeft, ReleaseCoeff));
    }

}} // namespace LinuxSampler::gig
