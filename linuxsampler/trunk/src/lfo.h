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

#ifndef __LFO_H__
#define __LFO_H__

#include "global.h"
#include "rtelmemorypool.h"
#include "modulationsystem.h"
#include "gig.h"

/**
 * Low Frequency Oscillator
 *
 * Synthesizes a triangular wave for modulating arbitrary synthesis
 * parameters.
 */
class LFO {
    public:
        /**
         * Defines how the LFO applies it's values to the synthesis
         * parameter matrix.
         */
        enum manipulation_type_t {
            manipulation_type_add,      ///< Add LFO's values to the synthesis paramter matrix.
            manipulation_type_multiply  ///< Multiply LFO's values with the ones from the synthesis parameter matrix.
        };
        /**
         * Defines the position of the LFO wave within the given value range
         * and from which value to start when the LFO is triggered.
         */
        enum propagation_t {
            propagation_top_down,        ///< Wave level starts from given max. and grows down with growing oscillator depth.
            propagation_middle_balanced, ///< Wave level starts from the middle of the given value range and grows in both directions with growing oscillator depth.
            propagation_bottom_up        ///< Wave level starts from given min. and grows up with growing oscillator depth.
        };

        uint8_t ExtController; ///< MIDI control change controller number if the LFO is controlled by an external controller, 0 otherwise.

        LFO(ModulationSystem::destination_t ModulationDestination, manipulation_type_t ManipulationType, float Min, float Max, propagation_t Propagation, RTELMemoryPool<ModulationSystem::Event>* pEventPool);
        void Process(uint Samples);
        void Trigger(float Frequency, uint16_t InternalDepth, uint16_t ExtControlDepth, uint16_t ExtControlValue, bool FlipPhase, uint Delay);
        void Reset();
        /**
         * Will be called by the voice to inform the LFO about a change of
         * the external controller's value.
         *
         * @param pEvent - control change event of external controller
         */
        inline void SendEvent(ModulationSystem::Event* pEvent) {
            if (ExtController && pEvent->FragmentPos() >= this->TriggerDelay) pEvents->alloc_assign(*pEvent);
        }
        ~LFO();
    protected:
        RTEList<ModulationSystem::Event>* pEvents;
        ModulationSystem::destination_t   ModulationDestination;
        manipulation_type_t               ManipulationType;
        propagation_t                     Propagation;
        int                               TriggerDelay;
        float                             Min;
        float                             Max;
        float                             CurrentMin;
        float                             CurrentMax;
        float                             FrequencyCoeff;
        float                             ExtControlDepthCoeff;
        float                             InternalDepth;
        float                             Range;
        float                             Coeff;
        float                             Level;

        inline void RecalculateCoeff(uint16_t ExtControlValue) {
            float currentrange = InternalDepth + ExtControlValue * ExtControlDepthCoeff;
            if (currentrange > Range) currentrange = Range;
            Coeff = (Coeff < 0) ? -(currentrange * FrequencyCoeff)
                                :   currentrange * FrequencyCoeff;
            switch (Propagation) {
                case propagation_top_down: {
                    CurrentMax = Max;
                    CurrentMin = Max - currentrange;
                    break;
                }
                case propagation_middle_balanced: {
                    float rangediff = (Range - currentrange) * 0.5f;
                    CurrentMax = Max - rangediff;
                    CurrentMin = Min + rangediff;
                    break;
                }
                case propagation_bottom_up: {
                    CurrentMax = Max - currentrange;
                    CurrentMin = Min;
                    break;
                }
            }
        }
};

#endif // __LFO_H__
