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
 */
void EG_VCA::Process(uint Samples) {
    if (Stage == stage_sustain) return; // nothing to do

    for (int to_process_total = Samples; to_process_total;) {
        int iSample = 0;
        switch (Stage) {
            case stage_attack: {
                int to_process    = Min(to_process_total, AttackStepsLeft);
                int process_end   = iSample + to_process;
                AttackStepsLeft  -= to_process;
                to_process_total -= to_process;
                for (; iSample < process_end; iSample++) {
                    Level += AttackCoeff;
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample] *= Level;
                }
                if (!AttackStepsLeft) {
                    Stage = (ReleaseSignalReceived) ? stage_release : stage_sustain;
                }
                break;
            }
            case stage_sustain: {
                return;
            }
            case stage_release: {
                int process_end = iSample + to_process_total;
                for (; iSample < process_end; iSample++) {
                    Level -= Level * ReleaseCoeff;
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample] *= Level;
                }
                if (Level <= EG_ENVELOPE_LIMIT) Stage = stage_end;
                return;
            }
            case stage_end: {
                int process_end = iSample + to_process_total;
                for (; iSample < process_end; iSample++) {
                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][iSample] *= Level;
                }
                return;
            }
        }
    }
}

/**
 * Will be called by the voice when the key / voice was triggered.
 *
 * @param PreAttack   - Preattack value for the envelope (0 - 1000 permille)
 * @param AttackTime  - Attack time for the envelope (0.000 - 60.000s)
 * @param ReleaseTIme - Release time for the envelope (0.000 - 60.000s)
 */
void EG_VCA::Trigger(uint PreAttack, double AttackTime, double ReleaseTime) {
    ReleaseSignalReceived = false;
    Stage = stage_attack;

    // calculate attack stage parameters
    AttackStepsLeft = (long) (AttackTime * ModulationSystem::GetSampleRate());
    if (AttackStepsLeft) {
        Level       = PreAttack;
        AttackCoeff = (1.0 - PreAttack) / AttackStepsLeft;
    }
    else {
        Level       = 1.0;
        AttackCoeff = 0.0;
    }

    // calcuate release stage parameters
    if (ReleaseTime < EG_MIN_RELEASE_TIME) ReleaseTime = EG_MIN_RELEASE_TIME;  // to avoid click sounds at the end of the sample playback
    ReleaseStepsLeft = (long) (ReleaseTime * ModulationSystem::GetSampleRate());
    ReleaseCoeff     = 1.0 - exp(log(EG_ENVELOPE_LIMIT) / (double) ReleaseStepsLeft);

    dmsg(4,("AttackLength=%d, ReleaseLength=%d",AttackStepsLeft,ReleaseStepsLeft));
}

/**
 * Will be called by the voice when the key / voice was released.
 */
void EG_VCA::Release() {
    // postpone release stage until sustain stage reached
    if (Stage == stage_sustain) Stage = stage_release;
    ReleaseSignalReceived = true;
}
