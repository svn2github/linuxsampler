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

#ifndef __LS_LFO_H__
#define __LS_LFO_H__

#include "../../common/global.h"

#if DEBUG_HEADERS
# warning LFO.h included
#endif // DEBUG_HEADERS

#include "../../common/RTMath.h"
#include "Event.h"

namespace LinuxSampler {

    /**
     * Low Frequency Oscillator
     *
     * Synthesizes a triangular wave for arbitrary usage. This LFO class is a
     * generalization; it takes a class as template parameter (T_Manipulator)
     * which is actually responsible to do something with the wave levels of the
     * oscillator. The class given with T_Manipulator has to provide a
     *
     * 	void ApplyLevel(float Level, int iSample);
     *
     * method. This method will be called by the LFO whenever the level of the
     * oscillator wave changes, where parameter 'Level' is the new level of the
     * wave and 'iSample' is the index of the corresponding sample point in the
     * current audio fragment.
     */
    template<class T_Manipulator>
    class LFO {
        public:

            // *************** types ***************
            // *

            /**
             * Defines the position of the LFO wave within the given value range
             * and from which value to start when the LFO is triggered.
             */
            enum propagation_t {
                propagation_top_down,        ///< Wave level starts from given max. and grows down with growing oscillator depth.
                propagation_middle_balanced, ///< Wave level starts from the middle of the given value range and grows in both directions with growing oscillator depth.
                propagation_bottom_up        ///< Wave level starts from given min. and grows up with growing oscillator depth.
            };


            // *************** attributes ***************
            // *

            T_Manipulator* pManipulator;  ///< Instance of the specific manipulator class given by template parameter T_Manipulator.
            uint8_t        ExtController; ///< MIDI control change controller number if the LFO is controlled by an external controller, 0 otherwise.


            // *************** methods ***************
            // *

            /**
             * Constructor
             *
             * @param Min         - minimum value of the output level
             * @param Max         - maximum value of the output level
             * @param Propagation - defines from which level the wave starts and which direction it grows with growing oscillator depth
             * @param pEventPool  - reference to an event pool which will be used to allocate Event objects
             */
            LFO(float Min, float Max, propagation_t Propagation, T_Manipulator* pManipulator, RTELMemoryPool<Event>* pEventPool) {
                this->Propagation   = Propagation;
                this->pEvents       = new RTEList<Event>(pEventPool);
                this->ExtController = 0;
                this->Min           = Min;
                this->Max           = Max;
                this->Range         = Max - Min;
                this->pManipulator  = pManipulator;
            }

            ~LFO() {
                if (pEvents) delete pEvents;
            }

            /**
             * Will be called by the voice for every audio fragment to let the LFO write it's modulation changes to the synthesis parameter matrix for the current audio fragment.
             *
             * @param Samples - total number of sample points to be rendered in
             *                  this audio fragment cycle by the audio engine
             */
            void Process(uint Samples) {
                Event* pCtrlEvent = pEvents->first();
                int iSample = TriggerDelay;
                while (iSample < Samples) {
                    int process_break = Samples;
                    if (pCtrlEvent && pCtrlEvent->FragmentPos() <= process_break) process_break = pCtrlEvent->FragmentPos();

                    if (Coeff > 0.0f) { // level going up
                        while (iSample < process_break && Level <= CurrentMax) {
                            pManipulator->ApplyLevel(Level, iSample);
                            iSample++;
                            Level += Coeff;
                        }
                        if (Level > CurrentMax) {
                            Coeff = -Coeff; // invert direction
                            Level += 2.0f * Coeff;
                        }
                    }
                    else if (Coeff < 0.0f) { // level going down
                        while (iSample < process_break && Level >= CurrentMin) {
                            pManipulator->ApplyLevel(Level, iSample);
                            iSample++;
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
                            pManipulator->ApplyLevel(Level, iSample);
                            iSample++;
                        }
                    }

                    if (pCtrlEvent) {
                        RecalculateCoeff(pCtrlEvent->Param.CC.Value);
                        pCtrlEvent = pEvents->next();
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
             * @param ExtControlDepth - defines how strong the external MIDI
             *                          controller has influence on the
             *                          oscillator amplitude
             * @param ExtControlValue - current MIDI value of the external
             *                          controller for the time when the
             *                          voice was triggered
             * @param FlipPhase       - inverts the oscillator wave
             * @param SampleRate      - current sample rate of the engines
             *                          audio output signal
             * @param Delay           - number of sample points triggering
             *                          should be delayed
             */
            void Trigger(float Frequency, uint16_t InternalDepth, uint16_t ExtControlDepth, uint16_t ExtControlValue, bool FlipPhase, uint SampleRate, uint Delay) {
                this->Coeff                = 0.0f;
                this->InternalDepth        = (InternalDepth / 1200.0f) * Range;
                this->ExtControlDepthCoeff = (((float) ExtControlDepth / 1200.0f) / 127.0f) * Range;
                this->TriggerDelay         = Delay;
                this->FrequencyCoeff       = (2.0f * Frequency) / (float) SampleRate;

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
             * Will be called by the voice to inform the LFO about a change of
             * the external controller's value.
             *
             * @param pEvent - control change event of external controller
             */
            inline void SendEvent(Event* pEvent) {
                if (ExtController && pEvent->FragmentPos() >= this->TriggerDelay) pEvents->alloc_assign(*pEvent);
            }

            /**
             * Should always be called when the voice was killed.
             */
            void Reset() {
                pEvents->clear();
            }

        protected:
            RTEList<Event>* pEvents;
            propagation_t   Propagation;
            int             TriggerDelay;
            float           Min;
            float           Max;
            float           CurrentMin;
            float           CurrentMax;
            float           FrequencyCoeff;
            float           ExtControlDepthCoeff;
            float           InternalDepth;
            float           Range;
            float           Coeff;
            float           Level;

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

} // namespace LinuxSampler

#endif // __LS_LFO_H__
