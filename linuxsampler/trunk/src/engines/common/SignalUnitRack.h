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
    
    template<typename T>
    class FixedArray {
        public:
            FixedArray(int capacity) {
                iSize = 0;
                iCapacity = capacity;
                pData = new T[iCapacity];
            }
            
            ~FixedArray() {
                delete pData;
                pData = NULL;
            }
            
            inline int size() { return iSize; }
            inline int capacity() { return iCapacity; }
            
            void add(T element) {
                if (iSize >= iCapacity) throw Exception("Array out of bounds");
                pData[iSize++] = element;
            }
            
            
            T increment() {
                if (iSize >= iCapacity) throw Exception("Array out of bounds");
                return pData[iSize++];
            }
            
            void clear() { iSize = 0; }
            
            inline T& operator[](int idx) {
                return pData[idx];
            }
            
        private:
            T*   pData;
            int  iSize;
            int  iCapacity;
    };
    
    class SignalUnitRack {
        protected:
            uint CurrentStep; // The current time step

        public:
            FixedArray<SignalUnit*> Units; // A list of all signal units in this rack

            /**
             * @param maxUnitCount We are using fixed size array because of the real-time safe requirements.
             */
            SignalUnitRack(int maxUnitCount): CurrentStep(0), Units(maxUnitCount) { }
            
            uint GetCurrentStep() { return CurrentStep; }

            virtual EndpointSignalUnit* GetEndpointUnit() = 0;
            
            virtual void EnterFadeOutStage() = 0;
            
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
                    Units[i]->Trigger();
                }
            }
            
            /**
             * When the rack belongs to a voice, this method is
             * called when the voice enter the release stage.
             */
            virtual void EnterReleaseStage() {
                for (int i = 0; i < Units.size(); i++) {
                    Units[i]->EnterReleaseStage();
                }
            }
            
            /**
             * When the rack belongs to a voice, this method is
             * called when the voice is of type which ignore note off.
             */
            virtual void CancelRelease() {
                for (int i = 0; i < Units.size(); i++) {
                    Units[i]->CancelRelease();
                }
            }
    };
} // namespace LinuxSampler

#endif	/* __LS_SIGNALUNITRACK_H__ */
