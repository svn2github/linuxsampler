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

#include "lfo.h"

LFO::LFO(ModulationSystem::destination_t ModulationDestination, manipulation_type_t ManipulationType, float Min, float Max, propagation_t Propagation, RTELMemoryPool<ModulationSystem::Event>* pEventPool) {
    this->ModulationDestination = ModulationDestination;
    this->ManipulationType      = ManipulationType;
    this->Propagation           = Propagation;
    this->pEvents               = new RTEList<ModulationSystem::Event>(pEventPool);
    this->ExtController         = 0;
    this->Min                   = Min;
    this->Max                   = Max;
    this->Range                 = Max - Min;
}

LFO::~LFO() {
    if (pEvents) delete pEvents;
}

/**
 * Will be called by the voice for every audio fragment to let the LFO write
 * it's modulation changes to the synthesis parameter matrix for the current
 * audio fragment.
 *
 * @param Samples - total number of sample points to be rendered in this
 *                  audio fragment cycle by the audio engine
 */
void LFO::Process(uint Samples) {
    ModulationSystem::Event* pCtrlEvent = pEvents->first();

    int iSample = TriggerDelay;
    switch (ManipulationType) {
        case manipulation_type_add: {
            while (iSample < Samples) {
                int process_break = Samples;
                if (pCtrlEvent && pCtrlEvent->FragmentPos() <= process_break) process_break = pCtrlEvent->FragmentPos();

                if (Coeff > 0.0f) { // level going up
                    while (iSample < process_break && Level <= CurrentMax) {
                        ModulationSystem::pDestinationParameter[ModulationDestination][iSample++] += Level;
                        Level += Coeff;
                    }
                    if (Level > CurrentMax) {
                        Coeff = -Coeff; // invert direction
                        Level += 2.0f * Coeff;
                    }
                }
                else if (Coeff < 0.0f) { // level going down
                    while (iSample < process_break && Level >= CurrentMin) {
                        ModulationSystem::pDestinationParameter[ModulationDestination][iSample++] += Level;
                        Level += Coeff;
                    }
                    if (Level < CurrentMin) {
                        Coeff = -Coeff; // invert direction
                        Level += 2.0f * Coeff;
                    }
                }
                else { // no modulation at all (Coeff = 0.0)
                    switch (Propagation) {
                        case propagation_top_down:
                            Level = Max;
                            break;
                        case propagation_middle_balanced:
                            Level = Min + 0.5f * Range;
                            break;
                        case propagation_bottom_up:
                            Level = Min;
                            break;
                    }
                    while (iSample < process_break) {
                        ModulationSystem::pDestinationParameter[ModulationDestination][iSample++] += Level;
                    }
                }

                if (pCtrlEvent) {
                    RecalculateCoeff(pCtrlEvent->Value);
                    pCtrlEvent = pEvents->next();
                }
            }
            break;
        }
        case manipulation_type_multiply: {
            while (iSample < Samples) {
                int process_break = Samples;
                if (pCtrlEvent && pCtrlEvent->FragmentPos() <= process_break) process_break = pCtrlEvent->FragmentPos();

                if (Coeff > 0.0f) { // level going up
                    while (iSample < process_break && Level <= CurrentMax) {
                        ModulationSystem::pDestinationParameter[ModulationDestination][iSample++] *= Level;
                        Level += Coeff;
                    }
                    if (Level > CurrentMax) {
                        Coeff = -Coeff; // invert direction
                        Level += 2.0f * Coeff;
                    }
                }
                else if (Coeff < 0.0f) { // level going down
                    while (iSample < process_break && Level >= CurrentMin) {
                        ModulationSystem::pDestinationParameter[ModulationDestination][iSample++] *= Level;
                        Level += Coeff;
                    }
                    if (Level < CurrentMin) {
                        Coeff = -Coeff; // invert direction
                        Level += 2.0f * Coeff;
                    }
                }
                else { // no modulation at all (Coeff = 0.0)
                    switch (Propagation) {
                        case propagation_top_down:
                            Level = Max;
                            break;
                        case propagation_middle_balanced:
                            Level = Min + 0.5f * Range;
                            break;
                        case propagation_bottom_up:
                            Level = Min;
                            break;
                    }
                    while (iSample < process_break) {
                        ModulationSystem::pDestinationParameter[ModulationDestination][iSample++] *= Level;
                    }
                }

                if (pCtrlEvent) {
                    RecalculateCoeff(pCtrlEvent->Value);
                    pCtrlEvent = pEvents->next();
                }
            }
            break;
        }
    }
    TriggerDelay = 0;
    pEvents->clear();
}

/**
 * Will be called by the voice when the key / voice was triggered.
 *
 * @param Frequency       - frequency of the oscillator in Hz
 * @param InternalDepth   - firm, internal oscillator amplitude
 * @param ExtControlDepth - defines how strong the external MIDI controller
 *                          has influence on the oscillator amplitude
 * @param ExtControlValue - current MIDI value of the external controller
 *                          for the time when the voice was triggered
 * @param FlipPhase       - inverts the oscillator wave
 * @param Delay           - number of sample points triggering should be
 *                          delayed
 */
void LFO::Trigger(float Frequency, uint16_t InternalDepth, uint16_t ExtControlDepth, uint16_t ExtControlValue, bool FlipPhase, uint Delay) {
    this->Coeff                = 0.0f;
    this->InternalDepth        = (InternalDepth / 1200.0f) * Range;
    this->ExtControlDepthCoeff = (((float) ExtControlDepth / 1200.0f) / 127.0f) * Range;
    this->TriggerDelay         = Delay;
    this->FrequencyCoeff       = (2.0f * Frequency) / (float) ModulationSystem::SampleRate();

    if (ExtController) RecalculateCoeff(ExtControlValue);
    else               RecalculateCoeff(0);

    switch (Propagation) {
        case propagation_top_down: {
            if (FlipPhase) {
                Level = CurrentMin;
            }
            else { // normal case
                Level = Max;
                Coeff = -Coeff; // level starts at max. thus has to go down now
            }
            break;
        }
        case propagation_middle_balanced: {
            Level = Min + 0.5f * Range;
            if (FlipPhase) Coeff = -Coeff; // invert direction (going down)
            break;
        }
        case propagation_bottom_up: {
            if (FlipPhase) {
                Level = CurrentMax;
                Coeff = -Coeff; // level starts at max. thus has to go down now
            }
            else { // normal case
                Level = Min;
            }
            break;
        }
    }
}

/**
 * Should always be called when the voice was killed.
 */
void LFO::Reset() {
    pEvents->clear();
}
