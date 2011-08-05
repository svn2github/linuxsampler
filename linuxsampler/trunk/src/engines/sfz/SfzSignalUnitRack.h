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
#include "../common/AbstractVoice.h"
#include "../common/PulseLFO.h"
#include "../common/SawLFO.h"
#include "../common/SineLFO.h"

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
            float  GetInfluence(ArrayList< ::sfz::CC>& cc);
    };
    
    
    class CCUnit: public CCSignalUnit {
        public:
            Voice* pVoice;

            CCUnit(SfzSignalUnitRack* rack, Listener* l = NULL);
            
            virtual void Trigger();
            
            void SetCCs(::sfz::Array<int>& pCC);
            void SetCCs(ArrayList< ::sfz::CC>& cc);
            
            inline int GetCurveCount();
            inline ::sfz::Curve* GetCurve(int idx);
    };
    
    class CurveCCUnit: public CCUnit {
        public:
            CurveCCUnit(SfzSignalUnitRack* rack, Listener* l = NULL): CCUnit(rack, l) { }
            
            virtual void Calculate() {
                Level = 0;
                for (int i = 0; i < Ctrls.size(); i++) {
                    if (Ctrls[i].Value == 0) continue;
                    if (Ctrls[i].Curve == -1) {
                        Level += (Ctrls[i].Value / 127.0f) * Ctrls[i].Influence;
                    } else {
                        Level += GetCurve(Ctrls[i].Curve)->v[Ctrls[i].Value] * Ctrls[i].Influence;
                    }
                }
            }
    };
    
    
    template <class T>
    class EGUnit: public SfzSignalUnit {
        public:
            ::sfz::EG* pEGInfo;
            T EG;

            EGUnit(SfzSignalUnitRack* rack): SfzSignalUnit(rack), pEGInfo(NULL) { }
            EGUnit(const EGUnit& Unit): SfzSignalUnit(Unit) { Copy(Unit); }
            void operator=(const EGUnit& Unit) { Copy(Unit); }
            
            void Copy(const EGUnit& Unit) {
                pEGInfo = Unit.pEGInfo;
                
                SfzSignalUnit::Copy(Unit);
            }

            virtual bool  Active() { return EG.active(); }
            virtual float GetLevel() { return DelayStage() ? 0 : EG.getLevel(); }
            
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
            int depth;
            EGv1Unit(SfzSignalUnitRack* rack): EGUnit<EGADSR>(rack), depth(0) { }
    };
    
    class EGv2Unit: public EGUnit< ::LinuxSampler::sfz::EG> {
        protected:
            ::sfz::EG egInfo;
        public:
            EGv2Unit(SfzSignalUnitRack* rack): EGUnit< ::LinuxSampler::sfz::EG>(rack) { }
            virtual void Trigger();
    };
    
    class PitchEGUnit: public EGv1Unit {
        public:
            PitchEGUnit(SfzSignalUnitRack* rack): EGv1Unit(rack) { }
            virtual void Trigger();
    };
    
    class FilEGUnit: public EGv1Unit {
        public:
            FilEGUnit(SfzSignalUnitRack* rack): EGv1Unit(rack) { }
            virtual void Trigger();
    };
    
    class AmpEGUnit: public EGv1Unit {
        public:
            AmpEGUnit(SfzSignalUnitRack* rack): EGv1Unit(rack) { }
            virtual void Trigger();
    };
    
    class AbstractLfo {
        public:
            virtual float Render() = 0;
            virtual void Update(const uint16_t& ExtControlValue) = 0;
            virtual void Trigger(float Frequency, start_level_t StartLevel, uint16_t InternalDepth, uint16_t ExtControlDepth, bool FlipPhase, unsigned int SampleRate) = 0;
            virtual void SetPhase(float phase) = 0;
            virtual void SetFrequency(float Frequency, unsigned int SampleRate) = 0;
    };
    
    template <class T>
    class LfoBase: public AbstractLfo, public T {
        public:
            LfoBase(float Max): T(Max) { }
            virtual float Render() { return T::render(); }
            
            virtual void Update(const uint16_t& ExtControlValue) { T::update(ExtControlValue); }
            
            virtual void Trigger (
                float Frequency, start_level_t StartLevel, uint16_t InternalDepth,
                uint16_t ExtControlDepth, bool FlipPhase, unsigned int SampleRate
            ) {
                T::trigger(Frequency, StartLevel, InternalDepth, ExtControlDepth, FlipPhase, SampleRate);
            }
            
            virtual void SetPhase(float phase) { T::setPhase(phase); }
            
            virtual void SetFrequency(float Frequency, unsigned int SampleRate) {
                T::setFrequency(Frequency, SampleRate);
            }
    };
    
    class LFOUnit;
    
    class FadeEGUnit: public EGUnit<EGADSR> {
        public:
            FadeEGUnit(SfzSignalUnitRack* rack): EGUnit<EGADSR>(rack) { }
            virtual void Trigger() { }
            virtual void EnterReleaseStage() { }
            virtual void CancelRelease() { }
            
            friend class LFOUnit;
    };
    
    class LFOUnit: public SfzSignalUnit, public CCSignalUnit::Listener {
        public:
            ::sfz::LFO*  pLfoInfo;
            AbstractLfo* pLFO;
            FadeEGUnit   suFadeEG;
            CCUnit       suFreqOnCC;
            
            LFOUnit(SfzSignalUnitRack* rack);
            LFOUnit(const LFOUnit& Unit);
            void operator=(const LFOUnit& Unit) { Copy(Unit); }
            
            void Copy(const LFOUnit& Unit) {
                pLfoInfo   = Unit.pLfoInfo;
                suFadeEG   = Unit.suFadeEG;
                
                SfzSignalUnit::Copy(Unit);
            }
            
            virtual bool  Active() { return pLfoInfo->freq > 0; }
            virtual void  Trigger();
            virtual void  Increment();
            virtual float GetLevel() { return Level; }
            virtual void  ValueChanged(CCSignalUnit* pUnit);
    };
    
    class LFOv1Unit: public LFOUnit {
        public:
            ::sfz::LFO lfoInfo;
            LfoBase<LFOSigned> lfo;
            
            LFOv1Unit(SfzSignalUnitRack* rack): LFOUnit(rack), lfo(1200.0f) {
                pLfoInfo = &lfoInfo; pLFO = &lfo;
            }
            
            virtual void Trigger();
    };
    
    class LFOv2Unit: public LFOUnit {
        protected:
            FixedArray<AbstractLfo*> lfos;
            LfoBase<LFOSigned>                       lfo0; // triangle
            LfoBase<SineLFO<range_signed> >          lfo1; // sine
            LfoBase<PulseLFO<range_unsigned, 750> >  lfo2; // pulse 75%
            LfoBase<SquareLFO<range_signed> >        lfo3; // square
            LfoBase<PulseLFO<range_unsigned, 250> >  lfo4; // pulse 25%
            LfoBase<PulseLFO<range_unsigned, 125> >  lfo5; // pulse 12,5%
            LfoBase<SawLFO<range_unsigned, true> >   lfo6; // saw up
            LfoBase<SawLFO<range_unsigned, false> >  lfo7; // saw down
            
            
        public:
            CCUnit suPitchOnCC;
            
            LFOv2Unit(SfzSignalUnitRack* rack);
            
            virtual void Trigger();
    };
    
    class AmpLFOUnit: public LFOv1Unit {
        public:
            AmpLFOUnit(SfzSignalUnitRack* rack): LFOv1Unit(rack) { }
            
            virtual void Trigger();
    };
    
    class PitchLFOUnit: public LFOv1Unit {
        public:
            CCUnit suDepthCC;
            
            PitchLFOUnit(SfzSignalUnitRack* rack): LFOv1Unit(rack), suDepthCC(rack) { }
            
            virtual void Trigger();
    };
    
    class FilLFOUnit: public LFOv1Unit {
        public:
            FilLFOUnit(SfzSignalUnitRack* rack): LFOv1Unit(rack) { }
            
            virtual void Trigger();
    };
    
    
    class EndpointUnit: public EndpointSignalUnit {
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
            virtual float GetPan();
            
            SfzSignalUnitRack* const GetRack();
            
            virtual float CalculateResonance(float res) {
                return GetResonance() + res;
            }
    };
    
    
    class SfzSignalUnitRack : public SignalUnitRack {
        private:
            EndpointUnit  suEndpoint;
            AmpEGUnit     suVolEG;
            FilEGUnit     suFilEG;
            PitchEGUnit   suPitchEG;
            
            AmpLFOUnit   suAmpLFO;
            PitchLFOUnit suPitchLFO;
            FilLFOUnit   suFilLFO;
            
            // SFZ v2
            
            CurveCCUnit suVolOnCC;
            
            FixedArray<EGv2Unit*> EGs;
            
            // used for optimization - contains only the ones that are modulating volume
            FixedArray<EGv2Unit*> volEGs;
            
            // used for optimization - contains only the ones that are modulating pitch
            FixedArray<EGv2Unit*> pitchEGs;
            
            
            FixedArray<LFOv2Unit*> LFOs;
            
            // used for optimization - contains only the ones that are modulating pitch
            FixedArray<LFOv2Unit*> pitchLFOs;
            
            // used for optimization - contains only the ones that are modulating filter cutoff
            FixedArray<LFOv2Unit*> filLFOs;
            
            // used for optimization - contains only the ones that are modulating resonance
            FixedArray<LFOv2Unit*> resLFOs;
            
            // used for optimization - contains only the ones that are modulating pan
            FixedArray<LFOv2Unit*> panLFOs;
            

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

