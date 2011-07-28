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

#ifndef __LS_SFZSIGNALUNITRACK_H__
#define	__LS_SFZSIGNALUNITRACK_H__

#include "../common/SignalUnitRack.h"
#include "EG.h"
#include "EGADSR.h"

namespace LinuxSampler { namespace sfz {
    const int MaxUnitCount = 1000;
    const int maxEgCount = 100; // Maximum number of v2 envelope generators
    const int maxLfoCount = 100; // Maximum number of v2 LFOs
    
    class Voice;
    class SfzSignalUnitRack;
    
    class SfzSignalUnit: public SignalUnit {
        public:
            Voice* pVoice;

            SfzSignalUnit(SfzSignalUnitRack* rack);
            SfzSignalUnit(const SfzSignalUnit& Unit): SignalUnit(Unit.pRack) { Copy(Unit); }
            
            void Copy(const SfzSignalUnit& Unit) {
                pVoice = Unit.pVoice;
                
                SignalUnit::Copy(Unit);
            }
            
            double GetSampleRate();
    };
    
    template <class T>
    class EGUnit : public SfzSignalUnit {
        public:
            ::sfz::EG* pEGInfo;
            T EG;

            EGUnit(SfzSignalUnitRack* rack): SfzSignalUnit(rack), pEGInfo(NULL) { }
            EGUnit(const EGUnit& Unit): SfzSignalUnit(Unit.pRack) { Copy(Unit); }
            void operator=(const EGUnit& Unit) { Copy(Unit); }
            
            void Copy(const EGUnit& Unit) {
                pEGInfo = Unit.pEGInfo;
                
                SfzSignalUnit::Copy(Unit);
            }

            virtual bool  Active() { return EG.active(); }
            virtual float GetLevel() { return EG.getLevel(); }
            
            virtual void EnterReleaseStage() { EG.update(EG::event_release, GetSampleRate()); }
            virtual void CancelRelease() { EG.update(EG::event_cancel_release, GetSampleRate()); }
            
            virtual void Increment() {
                if (DelayStage()) return;

                SfzSignalUnit::Increment();
                if (!EG.active()) return;
        
                switch (EG.getSegmentType()) {
                    case EG::segment_lin:
                        EG.processLin();
                        break;
                    case EG::segment_exp:
                        EG.processExp();
                        break;
                    case EG::segment_end:
                        EG.getLevel();
                        break; // noop
                    case EG::segment_pow:
                        EG.processPow();
                        break;
                }
        
                if (EG.active()) {
                    EG.increment(1);
                    if (!EG.toStageEndLeft()) EG.update(EG::event_stage_end, GetSampleRate());
                }
            }
    };
    
    class EGv1Unit: public EGUnit<EGADSR> {
        public:
            EGv1Unit(SfzSignalUnitRack* rack): EGUnit<EGADSR>(rack) { }
            virtual void Trigger();
    };
    
    class EGv2Unit: public EGUnit< ::LinuxSampler::sfz::EG> {
        public:
            EGv2Unit(SfzSignalUnitRack* rack): EGUnit< ::LinuxSampler::sfz::EG>(rack) { }
            virtual void Trigger();
    };
    
    
    
    class EndpointUnit : public EndpointSignalUnit {
        public:
            Voice* pVoice;

            EndpointUnit(SfzSignalUnitRack* rack);

            virtual void Trigger();

            /** The endpoint should be active until the volume EG is active. */
            virtual bool Active();
            
            virtual float GetVolume();
            virtual float GetFilterCutoff();
            virtual float GetPitch();
            virtual float GetResonance();
            
            SfzSignalUnitRack* const GetRack();
    };
    
    
    class SfzSignalUnitRack : public SignalUnitRack {
        private:
            EndpointUnit  suEndpoint;
            EGv1Unit      suVolEG;
            
            FixedArray<EGv2Unit*> EGs;
            
            // used for optimization - contains only the ones that are modulating volume
            FixedArray<EGv2Unit*> volEGs;
            
            // used for optimization - contains only the ones that are modulating pitch
            FixedArray<EGv2Unit*> pitchEGs;
            

        public:
            Voice* const pVoice;
        
            /**
             * @param Voice The voice to which this rack belongs.
             */
            SfzSignalUnitRack(Voice* voice);
            ~SfzSignalUnitRack();

            virtual EndpointSignalUnit* GetEndpointUnit();
            
            virtual void Trigger();
            virtual void EnterFadeOutStage();
            
            friend class EndpointUnit;
    };
}} // namespace LinuxSampler::sfz

#endif	/* __LS_SFZSIGNALUNITRACK_H__ */

