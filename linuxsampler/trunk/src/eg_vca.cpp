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

#include "eg_vca.h"

EG_VCA::EG_VCA() {
    Stage = stage_end;
    Level = 0.0;
}

/**
 * Will be called by the voice for every audio fragment to let the EG
 * queue it's modulation changes for the current audio fragment.
 *
 * @param Samples       - total number of sample points to be rendered in this
 *                        audio fragment cycle by the audio engine
 * @param pEvents       - event list with "release" and "cancel release" events
 * @param pTriggerEvent - event that caused triggering of the voice (only if
 *                        the voices was triggered in the current audio
 *                        fragment, NULL otherwise)
 * @param SamplePos     - current playback position
 * @param CurrentPitch  - current pitch value for playback
 */
void EG_VCA::Process(uint Samples, RTEList<ModulationSystem::Event>* pEvents, ModulationSystem::Event* pTriggerEvent, double SamplePos, double CurrentPitch) {
    ModulationSystem::Event* pReleaseTransitionEvent;
    if (pTriggerEvent) {
        pEvents->set_current(pTriggerEvent);
        pReleaseTransitionEvent = pEvents->next();
    }
    else {
        pReleaseTransitionEvent = pEvents->first();
    }

    int iSample = TriggerDelay;
    while (iSample < Samples) {
        switch (Stage) {
            case stage_attack: {
                int to_process   = Min(Samples - iSample, AttackStepsLeft);
                int process_end  = iSample + to_process;
                AttackStepsLeft -= to_process;
                while (iSample < process_end) {
                    Level += AttackCoeff;
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample++] *= Level;
                }
                TriggerDelay = 0;
                if (!AttackStepsLeft) Stage = (HoldAttack) ? stage_attack_hold : stage_decay1;
                if (iSample == Samples) { // postpone last transition event for the next audio fragment
                    ModulationSystem::Event* pLastEvent = pEvents->last();
                    if (pLastEvent) ReleasePostponed = (pLastEvent->Type == ModulationSystem::event_type_release);
                }
                break;
            }
            case stage_attack_hold: {
                if (SamplePos >= LoopStart) {
                    Stage = stage_decay1;
                    break;
                }
                int holdstepsleft = (int) (LoopStart - SamplePos / CurrentPitch); // FIXME: just an approximation, inaccuracy grows with higher audio fragment size, sufficient for usual fragment sizes though
                int to_process    = Min(Samples - iSample, holdstepsleft);
                int process_end   = iSample + to_process;
                while (iSample < process_end) {
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample++] *= Level;
                }
                if (to_process == holdstepsleft) Stage = stage_decay1;
                if (iSample == Samples) { // postpone last transition event for the next audio fragment
                    ModulationSystem::Event* pLastEvent = pEvents->last();
                    if (pLastEvent) ReleasePostponed = (pLastEvent->Type == ModulationSystem::event_type_release);
                }
                break;
            }
            case stage_decay1: {
                int to_process   = Min(Samples - iSample, Decay1StepsLeft);
                int process_end  = iSample + to_process;
                Decay1StepsLeft -= to_process;
                while (iSample < process_end) {
                    Level += Decay1Coeff;
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample++] *= Level;
                }
                if (iSample == Samples) { // postpone last transition event for the next audio fragment
                    ModulationSystem::Event* pLastEvent = pEvents->last();
                    if (pLastEvent) ReleasePostponed = (pLastEvent->Type == ModulationSystem::event_type_release);
                }
                if (!Decay1StepsLeft) {
                    Stage = (ReleasePostponed) ? stage_release
                                               : (InfiniteSustain) ? stage_sustain
                                                                   : stage_decay2;
                }
                break;
            }
            case stage_decay2: {
                int process_end;
                if (pReleaseTransitionEvent && pReleaseTransitionEvent->Type == ModulationSystem::event_type_release) {
                    process_end             = pReleaseTransitionEvent->FragmentPos();
                    pReleaseTransitionEvent = pEvents->next();
                    Stage                   = stage_release; // switch to release stage soon
                }
                else process_end = Samples;
                while (iSample < process_end) {
                    Level += Level * Decay2Coeff;
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample++] *= Level;
                }
                if (Level <= EG_ENVELOPE_LIMIT) Stage = stage_end;
                break;
            }
            case stage_sustain: {
                int process_end;
                if (pReleaseTransitionEvent && pReleaseTransitionEvent->Type == ModulationSystem::event_type_release) {
                    process_end             = pReleaseTransitionEvent->FragmentPos();
                    pReleaseTransitionEvent = pEvents->next();
                    Stage                   = stage_release; // switch to release stage soon
                }
                else process_end = Samples;
                while (iSample < process_end) {
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample++] *= Level;
                }
                break;
            }
            case stage_release: {
                int process_end;
                if (pReleaseTransitionEvent && pReleaseTransitionEvent->Type == ModulationSystem::event_type_cancel_release) {
                    process_end             = pReleaseTransitionEvent->FragmentPos();
                    pReleaseTransitionEvent = pEvents->next();
                    Stage                   = (InfiniteSustain) ? stage_sustain : stage_decay2; // switch back to sustain / decay2 stage soon
                }
                else process_end = Samples;
                while (iSample < process_end) {
                    Level += Level * ReleaseCoeff;
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample++] *= Level;
                }
                if (Level <= EG_ENVELOPE_LIMIT) Stage = stage_end;
                break;
            }
            case stage_end: {
                while (iSample < Samples) {
                    Level += Level * ReleaseCoeff;
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample++] *= Level;
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
void EG_VCA::Trigger(uint PreAttack, double AttackTime, bool HoldAttack, long LoopStart, double Decay1Time, double Decay2Time, bool InfiniteSustain, uint SustainLevel, double ReleaseTime, uint Delay) {
    this->TriggerDelay     = Delay;
    this->Stage            = stage_attack;
    this->SustainLevel     = (SustainLevel) ? (SustainLevel > EG_ENVELOPE_LIMIT) ? (float) SustainLevel / 1000.0 : EG_ENVELOPE_LIMIT : 1.0;
    this->InfiniteSustain  = InfiniteSustain;
    this->HoldAttack       = HoldAttack;
    this->LoopStart        = LoopStart;
    this->ReleasePostponed = false;

    // calculate attack stage parameters (lin. curve)
    AttackStepsLeft = (long) (AttackTime * ModulationSystem::SampleRate());
    if (AttackStepsLeft) {
        Level       = (float) PreAttack / 1000.0;
        AttackCoeff = (1.0 - Level) / AttackStepsLeft;
    }
    else {
        Level       = 1.0;
        AttackCoeff = 0.0;
    }

    // calculate decay1 stage parameters (lin. curve)
    Decay1StepsLeft = (long) (Decay1Time * ModulationSystem::SampleRate());
    Decay1Coeff     = (Decay1StepsLeft) ? (this->SustainLevel - 1.0) / Decay1StepsLeft : 0.0;

    // calculate decay2 stage parameters (exp. curve)
    if (!InfiniteSustain) {
        if (Decay2Time < EG_MIN_RELEASE_TIME) Decay2Time = EG_MIN_RELEASE_TIME;
        long Decay2Steps = (long) (Decay2Time * ModulationSystem::SampleRate());
        Decay2Coeff      = (Decay2Steps) ? exp((log(EG_ENVELOPE_LIMIT) - log(this->SustainLevel)) / Decay2Steps + log(this->SustainLevel)) - this->SustainLevel
                                         : 0.0;
    }

    // calcuate release stage parameters (exp. curve)
    if (ReleaseTime < EG_MIN_RELEASE_TIME) ReleaseTime = EG_MIN_RELEASE_TIME;  // to avoid click sounds at the end of the sample playback
    ReleaseStepsLeft = (long) (ReleaseTime * ModulationSystem::SampleRate());
    //ReleaseCoeff     = exp(log(EG_ENVELOPE_LIMIT) / (double) ReleaseStepsLeft) - 1.0; // <- this is only accurate for a curve start level of exactly 1.0, otherwise we have to use the following calculation for the coefficient...
    ReleaseCoeff     = exp((log(EG_ENVELOPE_LIMIT) - log(this->SustainLevel)) / ReleaseStepsLeft + log(this->SustainLevel)) - this->SustainLevel;

    dmsg(4,("PreAttack=%d, AttackLength=%d, AttackCoeff=%f, Decay1Coeff=%f, Decay2Coeff=%f, ReleaseLength=%d, ReleaseCoeff=%f\n",
            PreAttack, AttackStepsLeft, AttackCoeff, Decay1Coeff, Decay2Coeff, ReleaseStepsLeft, ReleaseCoeff));
}
