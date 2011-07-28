/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2011 Grigor Iliev                                       *
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

#ifndef __LS_SIGNALUNIT_H__
#define	__LS_SIGNALUNIT_H__

#include "../../common/ArrayList.h"


namespace LinuxSampler {

    class SignalUnitRack;

    /**
     * A signal unit consist of internal signal generator (like envelope generator,
     * low frequency oscillator, etc) with a number of generator parameters which
     * influence/modulate/dynamically change the generator's signal in some manner.
     * Each generator parameter (also called signal unit parameter) can receive
     * signal from another signal unit and use this signal to dynamically change the
     * behavior of the signal generator. In turn, the signal of this unit can be fed
     * to another unit(s) and influence its parameters.
     */
    class SignalUnit {
        public:

        /**
         * This class represents a parameter which will influence the signal
         * unit to which it belongs in certain way.
         * For example, let's say the signal unit is a low frequency oscillator
         * with frequency 1Hz. If we want to modulate the LFO to start with 1Hz
         * and increment its frequency to 5Hz in 1 second, we can add
         * a parameter which signal source is an envelope
         * generator with attack time of 1 second and coefficient 4. Thus, the
         * normalized level of the EG will move from 0 to 1 in one second.
         * On every time step (sample point) the normalized level
         * will be multiplied by 4 (the parameter coefficient) and added to the
         * LFO's frequency.
         * So, after 1 second, the LFO frequency will be 1x4 + 1 = 5Hz.
         * We can also add another parameter for modulating the LFO's pitch depth
         * and so on.
         */
        class Parameter {
            public:
                SignalUnit* pUnit; /* The source unit whose output signal 
                                    * will modulate the parameter.
                                    */
                
                float Coeff; // The modulation coefficient
                
                
                Parameter() : Coeff(1), pUnit(NULL) { }

                /**
                 * @param unit The source unit used to influence this parameter.
                 * @param coeff The coefficient by which the normalized signal
                 * received from the source unit should be multiplied when a
                 * default transformation is done.
                 */
                Parameter(SignalUnit* unit, float coeff = 1) {
                    pUnit = unit;
                    Coeff = coeff;
                }

                Parameter(const Parameter& Prm) { Copy(Prm); }
                void operator=(const Parameter& Prm) { Copy(Prm); }
            
                void Copy(const Parameter& Prm) {
                    if (this == &Prm) return;

                    pUnit = Prm.pUnit;
                    Coeff = Prm.Coeff;
                }
                
                
                /**
                 * Calculates the transformation for this parameter
                 * which should be applied to the parameter's value
                 * and multiplies by Coeff.
                 * This implementation of the method just multiplies by Coeff.
                 */
                virtual float Transform(float val) {
                    return val * Coeff;
                }
                
                /**
                 * Gets the current value of the parameter.
                 * This implementation returns the current signal level of the
                 * source unit with applied transformation if the source unit is
                 * active, otherwise returns 1.
                 * Note that this method assume that pUnit is not NULL.
                 */
                virtual float GetValue() {
                    return pUnit->Active() ? Transform(pUnit->GetLevel()) : 1.0f;
                }
        };


        public:
            ArrayList<SignalUnit::Parameter> Params; // The list of parameters which are modulating the signal unit
            
            SignalUnit(SignalUnitRack* rack): pRack(rack), bActive(false), Level(0.0f), bCalculating(false), uiDelayTrigger(0) { }
            SignalUnit(const SignalUnit& Unit): pRack(Unit.pRack) { Copy(Unit); }
            void operator=(const SignalUnit& Unit) { Copy(Unit); }
            
            void Copy(const SignalUnit& Unit) {
                if (this == &Unit) return;

                bActive = Unit.bActive;
                Level   = Unit.Level;
                Params  = Unit.Params;
                uiDelayTrigger = Unit.uiDelayTrigger;
                bCalculating = false;
            }
                
            /*
             * Determines whether the unit is active.
             * If the unit is not active, its level should be ignored.
             * For endpoint unit this method determines whether
             * the rendering should be stopped.
             */
            virtual bool Active() { return bActive; }
            
            /**
             * Override this method to process the current control change events.
             * @param itEvent - iterator pointing to the event to be processed.
             */
            virtual void ProcessCCEvent(uint8_t Controller, uint8_t Value) { }
            
            virtual void EnterReleaseStage() { }
            
            virtual void CancelRelease() { }
        
            /**
             * Gets the normalized level of the unit for the current
             * time step (sample point). The level is calculated if it's not
             * calculated for the current step yet. Because the level depends on
             * the parameters, their levels are calculated too.
             */
            virtual float GetLevel() {
                if (!bRecalculate) return Level;

                if (bCalculating) {
                    std::cerr << "SignalUnit: Loop detected. Aborted!";
                    return Level;
                }

                bCalculating = true;
                
                for(int i = 0; i < Params.size(); i++) {
                    Params[i].GetValue();
                }
                
                bRecalculate = bCalculating = false;
                return Level;
            }
        
            /**
             * Will be called to increment the time with one sample point.
             * The unit should recalculate or prepare for recalculation
             * its current level on every call of this function.
             * Note that it is not known whether all source signal unit's levels
             * are recalculated before the call of this method. So, the calculations
             * that depends on the unit's parameters should be postponed to
             * the call of GetLevel().
             */
            virtual void Increment() { bRecalculate = true; }

            /**
             * Initializes and triggers the unit.
             * Note that when a voice is the owner of a unit rack, all settings
             * should be reset when this method is called, because the sampler
             * is reusing the voice objects.
             */
            virtual void Trigger() = 0;
            
            /**
             * When the signal unit rack is triggered, it triggers all signal
             * units it holds. If for some reason the triggering of a unit
             * should be delayed, this method can be set to return non-zero value
             * specifying the delay in time steps.
             * Note that this is only a helper method and the implementation
             * should be done manually.
             */
            virtual uint DelayTrigger() { return uiDelayTrigger; }
            
            /**
             * A helper method which checks whether the delay
             * stage is finished.
             */
            bool DelayStage();
            
        protected:
            SignalUnitRack* const pRack;

            bool   bActive; /* Don't use it to check the active state of the unit!!!
                             * Use Active() instead! */
            float  Level;
            bool   bRecalculate; /* Determines whether the unit's level should be recalculated. */
            bool   bCalculating; /* Determines whether the unit is in process of calculating
                                  * its level. Used for preventing infinite loops.
                                  */

            uint   uiDelayTrigger; /* in time steps */
        
    };
    
    class EndpointSignalUnit: public SignalUnit {
        public:
            EndpointSignalUnit(SignalUnitRack* rack): SignalUnit(rack) { }

            /**
             * Gets the volume modulation value
             * for the current time step (sample point).
             */
            virtual float GetVolume() = 0;

            /**
             * Gets the filter cutoff frequency modulation value
             * for the current time step (sample point).
             */
            virtual float GetFilterCutoff() = 0;

            /**
             * Gets the pitch modulation value
             * for the current time step (sample point).
             */
            virtual float GetPitch() = 0;

            /**
             * Gets the resonance modulation value
             * for the current time step (sample point).
             */
            virtual float GetResonance() = 0;
            
            /** Should return value in the range [-100, 100] (L <-> R) */
            virtual float GetPan() = 0;
            
            virtual float CalculateFilterCutoff(float cutoff) {
                cutoff *= GetFilterCutoff();
                return cutoff > 13500 ? 13500 : cutoff;
            }
            
            virtual float CalculatePitch(float pitch) {
                return GetPitch() * pitch;
            }
            
            virtual float CalculateResonance(float res) {
                return GetResonance() * res;
            }
            
            /** Should return value in the range [0, 127] (L <-> R) */
            virtual uint8_t CaluclatePan(uint8_t pan) {
                int p = pan + GetPan() * 0.63;
                if (p < 0) return 0;
                if (p > 127) return 127;
                return p;
            }
    };
    
    /**
     * Continuous controller signal unit.
     * The level of this unit corresponds to the controller changes
     * and is normalized to be in the range from -1 to +1.
     */
    class CCSignalUnit: public SignalUnit {
        private:
            uint8_t Ctrl; // The number of the MIDI controller which modulates this signal unit.

        public:
            CCSignalUnit(SignalUnitRack* rack, uint8_t Controller): SignalUnit(rack) {
                Ctrl = Controller;
            }
            
            CCSignalUnit(const CCSignalUnit& Unit): SignalUnit(Unit.pRack) { Copy(Unit); }
            void operator=(const CCSignalUnit& Unit) { Copy(Unit); }
            
            void Copy(const CCSignalUnit& Unit) {
                Ctrl = Unit.Ctrl;
                SignalUnit::Copy(Unit);
            }
            
            virtual void Increment() { }
            
            virtual void ProcessCCEvent(uint8_t Controller, uint8_t Value) {
                if (Controller != Ctrl) return;
                
                // Normalize the value so it belongs to the interval [-1, +1]
                Level = 2 * Value;
                Level = Level/127.0f - 1.0f;
                
                if (!bActive) bActive = true;
            }
    };
    
} // namespace LinuxSampler

#endif	/* __LS_SIGNALUNIT_H__ */
