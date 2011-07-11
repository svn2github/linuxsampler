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

    /**
     * A signal unit consist of internal signal generator (like envelope generator,
     * low frequency oscillator, etc) with a number of generator parameters which
     * influence/modulate/dynamically change the generator's signal in some manner.
     * The generators' parameters (also called signal unit parameters) can receive
     * the signal of one or more signal units (through modulators if need)
     * and use the (modulated) signals of those units to dynamically change the
     * behavior of the signal generator. In turn, the signal of those unit can be fed
     * to another unit(s) and influence its parameters.
     */
    class SignalUnit {
        public:

        /**
         * Used as an intermediate link between a source signal unit and
         * a destination unit parameter. Modulates the received signal from the
         * source unit and feed it to the unit parameter to which it is connected.
         */
        class Modulator {
            public:
                SignalUnit* pUnit; /* The signal source which will be used for modulation.
                                    * If pUnit is NULL the level is considered to be 1!
                                    */
                float Coeff; // The modulation coefficient
                
                Modulator() : pUnit(NULL) { }
                Modulator(SignalUnit* Unit) { pUnit = Unit; }
                Modulator(const Modulator& Mod) { Copy(Mod); }
                void operator=(const Modulator& Mod) { Copy(Mod); }
            
                virtual void Copy(const Modulator& Mod) {
                    if (this == &Mod) return;

                    pUnit = Mod.pUnit;
                    Coeff = Mod.Coeff;
                }
                
                /**
                 * Gets the normalized level of the signal source for the current
                 * time step (sample point). Returns 1 if source unit is NULL or
                 * if the source unit is inactive.
                 */
                virtual float GetLevel() {
                    if (pUnit == NULL) return 1.0f;
                    return pUnit->Active() ? pUnit->GetLevel() : 1.0f;
                }
                
                /**
                 * Gets the modulated level of the source signal
                 * for the current time step (sample point).
                 */
                virtual float GetValue() {
                    return Transform(GetLevel());
                }
                
                /**
                 * Calculates the transformation that should be applied
                 * to the signal of the source unit and multiplies by Coeff.
                 * This implementation of the method just multiplies by Coeff,
                 * or returns 1 if the source unit is inactive.
                 */
                virtual float Transform(float val) {
                    if (pUnit != NULL && !pUnit->Active()) return 1;
                    return val * Coeff;
                }
        };
        
        /**
         * This class represents a parameter which will influence the signal
         * unit to which it belongs in certain way.
         * For example, let's say the signal unit is a low frequency oscillator
         * with frequency 1Hz. If we want to modulate the LFO to start with 1Hz
         * and increment its frequency to 5Hz in 1 second, we can add
         * a parameter with one modulator which signal source is an envelope
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
                ArrayList<Modulator> Modulators; // A list of signal units which will modulate this parameter
                
                SignalUnit* pUnit; /* If pUnit is not NULL, the modulators are ignored and
                                    * this unit is used as only source.
                                    * This is done for efficiency reasons.
                                    */
                
                float Coeff; // The global modulation coefficient
                
                
                Parameter() : Coeff(1), pUnit(NULL) { }

                /**
                 * Most often we just need to directly feed the signal of single unit
                 * to a unit parameter without any additional modulation.
                 * This constructor creates a parameter with only a single source
                 * unit without additional modulation, optimized for efficiency.
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
            
                virtual void Copy(const Parameter& Prm) {
                    if (this == &Prm) return;

                    Modulators = Prm.Modulators;
                    pUnit = Prm.pUnit;
                    Coeff = Prm.Coeff;
                }
                
                
                /**
                 * Calculates the global transformation for this parameter
                 * which should be applied to the parameter's value
                 * and multiplies by Coeff.
                 * This implementation of the method just multiplies by Coeff.
                 */
                virtual float Transform(float val) {
                    return val * Coeff;
                }
                
                /**
                 * Gets the current value of the parameter (without transformation).
                 * This implementation just sum the modulators values.
                 * If only a single unit is used without additional modulation
                 * returns the source unit's level or 1 if the unit is not active.
                 */
                virtual float GetValue() {
                    if (pUnit != NULL) {
                        return pUnit->Active() ? pUnit->GetLevel() : 1.0f;
                    }

                    float val = 0;
                    for(int i = 0; i < Modulators.size(); i++) {
                        val += Modulators[i].GetValue();
                    }
                    
                    return val;
                }
                
                /** Gets the final value - with applied transformation. */
                virtual float GetFinalValue() {
                    return Transform(GetValue());
                }
        };


        public:
            ArrayList<SignalUnit::Parameter> Params; // The list of parameters which are modulating the signal unit
            
            SignalUnit() : bActive(false), Level(0.0f), bCalculating(false), uiDelayTrigger(0) { }
            SignalUnit(const SignalUnit& Unit) { Copy(Unit); }
            void operator=(const SignalUnit& Unit) { Copy(Unit); }
            
            virtual void Copy(const SignalUnit& Unit) {
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

            /** Initializes and triggers the unit. */
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
            
        protected:
            bool   bActive; /* Don't use it to check the active state of the unit!!!
                             * Use Active() instead! */
            float  Level;
            bool   bRecalculate; /* Determines whether the unit's level should be recalculated. */
            bool   bCalculating; /* Determines whether the unit is in process of calculating
                                  * its level. Used for preventing infinite loops.
                                  */

            uint   uiDelayTrigger; /* in time steps */
        
    };
    
    class EndpointSignalUnit: virtual public SignalUnit {
        public:
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
            
            virtual float CalculateFilterCutoff(float cutoff) = 0;
            
            virtual float CalculatePitch(float pitch) = 0;
            
            virtual float CalculateResonance(float res) = 0;
    };
    

    class SignalUnitRack;

    template <class O /* The signal unit's owner */>
    class SignalUnitBase: virtual public SignalUnit {
        public:
            SignalUnitBase() : pOwner(NULL) { }
            SignalUnitBase(const SignalUnitBase& Unit) { Copy(Unit); }
            void operator=(const SignalUnitBase& Unit) { Copy(Unit); }
            
            virtual void Copy(const SignalUnitBase& Unit) {
                if (this == &Unit) return;

                pOwner = Unit.pOwner;
                SignalUnit::Copy(Unit);
            }

        protected:
            O* pOwner; // The owner to which this rack belongs.
            
            SignalUnitRack* GetSignalUnitRack() { return pOwner->GetSignalUnitRack(); }
        
        public:
            
            
            /**
             * The owner of the unit is set by the rack
             * just before the call to the unit's trigger method.
             */
            void SetOwner(O* Owner) { pOwner = Owner; }
            
            /**
             * A helper method which checks whether the delay
             * stage is finished.
             */
            bool DelayStage() {
                return (DelayTrigger() >= GetSignalUnitRack()->GetCurrentStep());
            }
    };
    
    /**
     * Continuous controller signal unit.
     * The level of this unit corresponds to the controller changes
     * and is normalized to be in the range from -1 to +1.
     */
    template<class O>
    class CCSignalUnit: public SignalUnitBase<O> {
        private:
            uint8_t Ctrl; // The number of the MIDI controller which modulates this signal unit.

        public:
            CCSignalUnit(uint8_t Controller) {
                Ctrl = Controller;
            }
            
            CCSignalUnit(const CCSignalUnit& Unit) { Copy(Unit); }
            void operator=(const CCSignalUnit& Unit) { Copy(Unit); }
            
            virtual void Copy(const CCSignalUnit& Unit) {
                SignalUnitBase<O>::Copy(Unit);
                Ctrl = Unit.Ctrl;
            }
            
            virtual void Increment() { }
            
            virtual void ProcessCCEvent(uint8_t Controller, uint8_t Value) {
                if (Controller != Ctrl) return;
                
                // Normalize the value so it belongs to the interval [-1, +1]
                SignalUnitBase<O>::Level = 2 * Value;
                SignalUnitBase<O>::Level = SignalUnitBase<O>::Level/127.0f - 1.0f;
                
                if (!SignalUnitBase<O>::bActive) SignalUnitBase<O>::bActive = true;
            }
    };

    /**
     * Endpoint signal unit.
     */
    template<class O>
    class EndpointSignalUnitBase : public SignalUnitBase<O>, public EndpointSignalUnit {
        public:

            virtual float CalculateFilterCutoff(float cutoff) {
                return GetFilterCutoff() * cutoff;
            }
            
            virtual float CalculatePitch(float pitch) {
                return GetPitch() * pitch;
            }
            
            virtual float CalculateResonance(float res) {
                return GetResonance() * res;
            }
    };
    
} // namespace LinuxSampler

#endif	/* __LS_SIGNALUNIT_H__ */
