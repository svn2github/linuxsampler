/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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
        const float killSteps  = EG_MIN_RELEASE_TIME * sampleRate;
        return 1.0f / killSteps;
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
     * @param pTriggerEvent - event that caused triggering of the voice (only if
     *                        the voice was triggered in the current audio
     *                        fragment, NULL otherwise)
     * @param SamplePos     - current playback position
     * @param CurrentPitch  - current pitch value for playback
     * @param pKillEvent    - (optional) event which caused this voice to be killed
     */
    void EGADSR::Process(uint TotalSamples, RTEList<Event>* pEvents, Event* pTriggerEvent, double SamplePos, double CurrentPitch, Event* pKillEvent) {
        Event* pTransitionEvent;
        if (pTriggerEvent) { // skip all events which occured before this voice was triggered
            pEvents->set_current(pTriggerEvent);
            pTransitionEvent = pEvents->next();
        }
        else {
            pTransitionEvent = pEvents->first();
        }

        // if the voice was killed in this fragment we only process the time before this kill event, then switch to 'stage_fadeout'
        int Samples = (pKillEvent) ? pKillEvent->FragmentPos() : (int) TotalSamples;

        int iSample = TriggerDelay;
        while (iSample < TotalSamples) {

            // if the voice was killed in this fragment and we already processed the time before this kill event
            if (pKillEvent && iSample >= Samples) Stage = stage_fadeout;

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
                    if (iSample == TotalSamples) { // postpone last transition event for the next audio fragment
                        Event* pLastEvent = pEvents->last();
                        if (pLastEvent) ReleasePostponed = (pLastEvent->Type == Event::type_release);
                    }
                    if (!AttackStepsLeft) Stage = (ReleasePostponed) ? stage_release : (HoldAttack) ? stage_attack_hold : stage_decay1;
                    break;
                }
                case stage_attack_hold: {
                    if (SamplePos >= LoopStart) {
                        Stage = stage_decay1;
                        break;
                    }
                    int holdstepsleft = (int) (LoopStart - SamplePos / CurrentPitch); // FIXME: just an approximation, inaccuracy grows with higher audio fragment size, sufficient for usual fragment sizes though
                    int to_process    = RTMath::Min(holdstepsleft, Samples - iSample);
                    int process_end   = iSample + to_process;
                    if (pTransitionEvent && pTransitionEvent->FragmentPos() <= process_end) {
                        process_end      = pTransitionEvent->FragmentPos();
                        Stage            = (pTransitionEvent->Type == Event::type_release) ? stage_release : (InfiniteSustain) ? stage_sustain : stage_decay2;
                        pTransitionEvent = pEvents->next();
                    }
                    else if (to_process == holdstepsleft) Stage = stage_decay1;
                    while (iSample < process_end) {
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_decay1: {
                    int to_process   = RTMath::Min(Samples - iSample, Decay1StepsLeft);
                    int process_end  = iSample + to_process;
                    if (pTransitionEvent && pTransitionEvent->FragmentPos() <= process_end) {
                        process_end      = pTransitionEvent->FragmentPos();
                        Stage            = (pTransitionEvent->Type == Event::type_release) ? stage_release : (InfiniteSustain) ? stage_sustain : stage_decay2;
                        pTransitionEvent = pEvents->next();
                    }
                    else {
                        Decay1StepsLeft -= to_process;
                        if (!Decay1StepsLeft) Stage = (InfiniteSustain) ? stage_sustain : stage_decay2;
                    }
                    while (iSample < process_end) {
                        Level += Level * Decay1Coeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_decay2: {
                    int process_end;
                    if (pTransitionEvent && pTransitionEvent->Type == Event::type_release && pTransitionEvent->FragmentPos() <= Samples) {
                        process_end      = pTransitionEvent->FragmentPos();
                        pTransitionEvent = pEvents->next();
                        Stage            = stage_release; // switch to release stage soon
                    }
                    else process_end = Samples;
                    while (iSample < process_end) {
                        Level += Level * Decay2Coeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    if (Level <= EG_ENVELOPE_LIMIT) Stage = stage_fadeout;
                    break;
                }
                case stage_sustain: {
                    int process_end;
                    if (pTransitionEvent && pTransitionEvent->Type == Event::type_release && pTransitionEvent->FragmentPos() <= Samples) {
                        process_end      = pTransitionEvent->FragmentPos();
                        pTransitionEvent = pEvents->next();
                        Stage            = stage_release; // switch to release stage soon
                    }
                    else process_end = Samples;
                    while (iSample < process_end) {
                       pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    break;
                }
                case stage_release: {
                    int process_end;
                    if (pTransitionEvent && pTransitionEvent->Type == Event::type_cancel_release && pTransitionEvent->FragmentPos() <= Samples) {
                        process_end      = pTransitionEvent->FragmentPos();
                        pTransitionEvent = pEvents->next();
                        Stage            = (InfiniteSustain) ? stage_sustain : stage_decay2; // switch back to sustain / decay2 stage soon
                    }
                    else process_end = Samples;
                    while (iSample < process_end) {
                        Level += Level * ReleaseCoeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    if (Level <= EG_ENVELOPE_LIMIT) Stage = stage_fadeout;
                    break;
                }
                case stage_fadeout: {
                    int to_process   = RTMath::Min(int(Level / (-FadeOutCoeff)), TotalSamples - iSample);
                    int process_end  = iSample + to_process;
                    while (iSample < process_end) {
                        Level += FadeOutCoeff;
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] *= Level;
                    }
                    if (Level <= FadeOutCoeff) Stage = stage_end;
                    break;
                }
                case stage_end: {
                    while (iSample < TotalSamples) {
                        pEngine->pSynthesisParameters[ModulationDestination][iSample++] = 0.0f;
                    }
                    break;
                }
            }
        }
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
     */
    void EGADSR::Trigger(uint PreAttack, double AttackTime, bool HoldAttack, long LoopStart, double Decay1Time, double Decay2Time, bool InfiniteSustain, uint SustainLevel, double ReleaseTime, uint Delay) {
        this->TriggerDelay     = Delay;
        this->Stage            = stage_attack;
        this->SustainLevel     = (SustainLevel) ? (SustainLevel > EG_ENVELOPE_LIMIT) ? (float) SustainLevel / 1000.0 : EG_ENVELOPE_LIMIT : 1.0;
        this->InfiniteSustain  = InfiniteSustain;
        this->HoldAttack       = HoldAttack;
        this->LoopStart        = LoopStart;
        this->ReleasePostponed = false;

        // calculate attack stage parameters (lin. curve)
        AttackStepsLeft = (long) (AttackTime * pEngine->pAudioOutputDevice->SampleRate());
        if (AttackStepsLeft) {
            Level       = (float) PreAttack / 1000.0;
            AttackCoeff = (1.0 - Level) / AttackStepsLeft;
        }
        else {
            Level       = 1.0;
            AttackCoeff = 0.0;
        }

        // calculate decay1 stage parameters (exp. curve)
        Decay1StepsLeft = (long) (Decay1Time * pEngine->pAudioOutputDevice->SampleRate());
        Decay1Coeff     = (Decay1StepsLeft) ? exp(log(this->SustainLevel) / (double) Decay1StepsLeft) - 1.0
                                            : 0.0;

        // calculate decay2 stage parameters (exp. curve)
        if (!InfiniteSustain) {
            if (Decay2Time < EG_MIN_RELEASE_TIME) Decay2Time = EG_MIN_RELEASE_TIME;
            long Decay2Steps = (long) (Decay2Time * pEngine->pAudioOutputDevice->SampleRate());
            Decay2Coeff      = (Decay2Steps) ? exp((log(EG_ENVELOPE_LIMIT) - log(this->SustainLevel)) / Decay2Steps + log(this->SustainLevel)) - this->SustainLevel
                                             : 0.0;
        }

        // calculate release stage parameters (exp. curve)
        if (ReleaseTime < EG_MIN_RELEASE_TIME) ReleaseTime = EG_MIN_RELEASE_TIME;  // to avoid click sounds at the end of the sample playback
        ReleaseStepsLeft = (long) (ReleaseTime * pEngine->pAudioOutputDevice->SampleRate());
        ReleaseCoeff     = exp((log(EG_ENVELOPE_LIMIT) - log(this->SustainLevel)) / ReleaseStepsLeft + log(this->SustainLevel)) - this->SustainLevel;

        dmsg(4,("PreAttack=%d, AttackLength=%d, AttackCoeff=%f, Decay1Coeff=%f, Decay2Coeff=%f, ReleaseLength=%d, ReleaseCoeff=%f\n",
                PreAttack, AttackStepsLeft, AttackCoeff, Decay1Coeff, Decay2Coeff, ReleaseStepsLeft, ReleaseCoeff));
    }

}} // namespace LinuxSampler::gig
