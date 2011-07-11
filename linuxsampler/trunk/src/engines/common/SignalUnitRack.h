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

#ifndef __LS_SIGNALUNITRACK_H__
#define	__LS_SIGNALUNITRACK_H__

#include "Event.h"
#include "SignalUnit.h"
#include "../../common/Pool.h"


namespace LinuxSampler {
    class SignalUnitRack {
        protected:
            uint CurrentStep; // The current time step

        public:
            SignalUnitRack(): CurrentStep(0) { }
            uint GetCurrentStep() { return CurrentStep; }

            /**
             * Will be called to increment the time with one sample point.
             * Each unit should recalculate its current level on every call of this function.
             */
            virtual void Increment() = 0;
            
            virtual void ProcessCCEvent(RTList<Event>::Iterator& itEvent) = 0;
            
            /** Initializes and triggers the rack. */
            virtual void Trigger() = 0;
            
            /**
             * When the rack belongs to a voice, this method is
             * called when the voice enter the release stage.
             */
            virtual void EnterReleaseStage() = 0;
            
            /**
             * When the rack belongs to a voice, this method is
             * called when the voice is of type which ignore note off.
             */
            virtual void CancelRelease() = 0;
            
            virtual EndpointSignalUnit* GetEndpointUnit() = 0;
    };
    
    template <class O /* The signal unit rack's owner */>
    class SignalUnitRackBase: public SignalUnitRack {
        protected:
            O* pOwner; // The owner to which this rack belongs.

        public:
            ArrayList<SignalUnitBase<O>*> Units; // A list of all signal units in this rack
            
            SignalUnitRackBase(O* Owner) {
                pOwner = Owner;
            }
            
            /**
             * Will be called to increment the time with one sample point.
             * Each unit should recalculate its current level on every call of this function.
             */
            virtual void Increment() {
                CurrentStep++;

                for (int i = 0; i < Units.size(); i++) {
                    Units[i]->Increment();
                }
            }
            
            virtual void ProcessCCEvent(RTList<Event>::Iterator& itEvent) {
                if ( !(itEvent->Type == Event::type_control_change && itEvent->Param.CC.Controller) ) return;
                for (int i = 0; i < Units.size(); i++) {
                    Units[i]->ProcessCCEvent(itEvent->Param.CC.Controller, itEvent->Param.CC.Value);
                }
            }
            
            /** Initializes and triggers the rack. */
            virtual void Trigger() {
                CurrentStep = 0;
                for (int i = 0; i < Units.size(); i++) {
                    Units[i]->SetOwner(pOwner);
                    Units[i]->Trigger();
                }
            }
            
            virtual void EnterReleaseStage() {
                for (int i = 0; i < Units.size(); i++) {
                    Units[i]->EnterReleaseStage();
                }
            }
            
            virtual void CancelRelease() {
                for (int i = 0; i < Units.size(); i++) {
                    Units[i]->CancelRelease();
                }
            }
    };
} // namespace LinuxSampler

#endif	/* __LS_SIGNALUNITRACK_H__ */
