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

#include "SfzSignalUnitRack.h"
#include "Voice.h"
#include <SF.h>

namespace LinuxSampler { namespace sfz {
    
    SfzSignalUnit::SfzSignalUnit(SfzSignalUnitRack* rack): SignalUnit(rack), pVoice(rack->pVoice) {
        
    }
    
    double SfzSignalUnit::GetSampleRate() {
        return pVoice->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE;
    }
    
    
    void EGv1Unit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        
        // the length of the decay and release curves are dependent on the velocity
        const double velrelease = 1 / pVoice->GetVelocityRelease(pVoice->MIDIVelocity);

        // set the delay trigger
        uiDelayTrigger = (pRegion->ampeg_delay + pRegion->ampeg_vel2delay * velrelease) * GetSampleRate();
        
        EG.trigger(uint(pRegion->ampeg_start * 10),
                   std::max(0.0, pRegion->ampeg_attack + pRegion->ampeg_vel2attack * velrelease),
                   std::max(0.0, pRegion->ampeg_hold + pRegion->ampeg_vel2hold * velrelease),
                   std::max(0.0, pRegion->ampeg_decay + pRegion->ampeg_vel2decay * velrelease),
                   uint(std::min(std::max(0.0, 10 * (pRegion->ampeg_sustain + pRegion->ampeg_vel2sustain * velrelease)), 1000.0)),
                   std::max(0.0, pRegion->ampeg_release + pRegion->ampeg_vel2release * velrelease),
                   GetSampleRate());
    }
    
    
    void EGv2Unit::Trigger() {
        EG.trigger(*pEGInfo, GetSampleRate(), pVoice->MIDIVelocity);
    }
    
    
    void PitchEGUnit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        depth = pRegion->pitcheg_depth;
        
        // the length of the decay and release curves are dependent on the velocity
        const double velrelease = 1 / pVoice->GetVelocityRelease(pVoice->MIDIVelocity);

        // set the delay trigger
        uiDelayTrigger = (pRegion->pitcheg_delay + pRegion->pitcheg_vel2delay * velrelease) * GetSampleRate();
        
        EG.trigger(uint(pRegion->pitcheg_start * 10),
                   std::max(0.0, pRegion->pitcheg_attack + pRegion->pitcheg_vel2attack * velrelease),
                   std::max(0.0, pRegion->pitcheg_hold + pRegion->pitcheg_vel2hold * velrelease),
                   std::max(0.0, pRegion->pitcheg_decay + pRegion->pitcheg_vel2decay * velrelease),
                   uint(std::min(std::max(0.0, 10 * (pRegion->pitcheg_sustain + pRegion->pitcheg_vel2sustain * velrelease)), 1000.0)),
                   std::max(0.0, pRegion->pitcheg_release + pRegion->pitcheg_vel2release * velrelease),
                   GetSampleRate());
    }
    
    
    void FilEGUnit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        depth = pRegion->fileg_depth;
        
        // the length of the decay and release curves are dependent on the velocity
        const double velrelease = 1 / pVoice->GetVelocityRelease(pVoice->MIDIVelocity);

        // set the delay trigger
        uiDelayTrigger = (pRegion->fileg_delay + pRegion->fileg_vel2delay * velrelease) * GetSampleRate();
        
        EG.trigger(uint(pRegion->fileg_start * 10),
                   std::max(0.0, pRegion->fileg_attack + pRegion->fileg_vel2attack * velrelease),
                   std::max(0.0, pRegion->fileg_hold + pRegion->fileg_vel2hold * velrelease),
                   std::max(0.0, pRegion->fileg_decay + pRegion->fileg_vel2decay * velrelease),
                   uint(std::min(std::max(0.0, 10 * (pRegion->fileg_sustain + pRegion->fileg_vel2sustain * velrelease)), 1000.0)),
                   std::max(0.0, pRegion->fileg_release + pRegion->fileg_vel2release * velrelease),
                   GetSampleRate());
    }
    
    
    LFOUnit::LFOUnit(SfzSignalUnitRack* rack)
        : SfzSignalUnit(rack), pLfoInfo(NULL), pLFO(NULL),
          suFadeEG(rack), suFreqOnCC(rack, this)
    { }
    
    LFOUnit::LFOUnit(const LFOUnit& Unit)
        : SfzSignalUnit(Unit), suFadeEG(static_cast<SfzSignalUnitRack*>(Unit.pRack)),
          suFreqOnCC(static_cast<SfzSignalUnitRack*>(Unit.pRack), this)
    {
        Copy(Unit);
    }

    void LFOUnit::Increment() {
        if (DelayStage()) return;
        
        SignalUnit::Increment();
        
        Level = pLFO->Render();
        if (suFadeEG.Active()) Level *= suFadeEG.GetLevel();
    }
    
    void LFOUnit::Trigger() {
        //reset
        Level = 0;
        
        // set the delay trigger
        uiDelayTrigger = pLfoInfo->delay * GetSampleRate();
        if(pLfoInfo->fade != 0 || !pLfoInfo->fade_oncc.empty()) {
            float f = pLfoInfo->fade;
            for (int i = 0; i < pLfoInfo->fade_oncc.size(); i++) {
                int val = pVoice->GetControllerValue(pLfoInfo->fade_oncc[i].Controller);
                f += (val / 127.0f) * pLfoInfo->fade_oncc[i].Influence;
            }
            
            if (f != 0) {
                suFadeEG.uiDelayTrigger = pLfoInfo->delay * GetSampleRate();
                suFadeEG.EG.trigger(0, f, 0, 0, 1000, 0, GetSampleRate());
            }
        }
    }
    
    void LFOUnit::ValueChanged(CCSignalUnit* pUnit) {
        pLFO->SetFrequency(suFreqOnCC.GetLevel() + pLfoInfo->freq, GetSampleRate());
    }
    
    
    void LFOv1Unit::Trigger() {
        LFOUnit::Trigger();
        
        lfo.trigger (
            pLfoInfo->freq + suFreqOnCC.GetLevel(),
            start_level_mid,
            1, 0, false, GetSampleRate()
        );
        lfo.update(0);
    }
    
    
    LFOv2Unit::LFOv2Unit(SfzSignalUnitRack* rack)
        : LFOUnit(rack), lfos(8), lfo0(1200.0f), lfo1(1200.0f), lfo2(1200.0f),
          lfo3(1200.0f), lfo4(1200.0f), lfo5(1200.0f), lfo6(1200.0f), lfo7(1200.0f),
          suPitchOnCC(rack)
    {
        lfos.add(&lfo0);
        lfos.add(&lfo1);
        lfos.add(&lfo2);
        lfos.add(&lfo3);
        lfos.add(&lfo4);
        lfos.add(&lfo5);
        lfos.add(&lfo6);
        lfos.add(&lfo7);
    }
    
    void LFOv2Unit::Trigger() {
        LFOUnit::Trigger();
        
        if (pLfoInfo->wave < 0 || pLfoInfo->wave >= lfos.size()) pLFO = &lfo0;
        else pLFO = lfos[pLfoInfo->wave];
        
        pLFO->Trigger (
            pLfoInfo->freq + suFreqOnCC.GetLevel(),
            start_level_mid,
            1, 0, false, GetSampleRate()
        );
        pLFO->Update(0);
        
        float phase = pLfoInfo->phase;
        for (int i = 0; i < pLfoInfo->phase_oncc.size(); i++) {
            int val = pVoice->GetControllerValue(pLfoInfo->phase_oncc[i].Controller);
            phase += (val / 127.0f) * pLfoInfo->phase_oncc[i].Influence;
        }
        if (phase != 0) pLFO->SetPhase(phase);
    }
    
    void AmpLFOUnit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        pLfoInfo->delay  = pRegion->amplfo_delay;
        pLfoInfo->freq   = pRegion->amplfo_freq;
        pLfoInfo->fade   = pRegion->amplfo_fade;
        pLfoInfo->volume = pRegion->amplfo_depth;
        
        LFOv1Unit::Trigger();
    }
    
    void PitchLFOUnit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        pLfoInfo->delay = pRegion->pitchlfo_delay;
        pLfoInfo->freq  = pRegion->pitchlfo_freq;
        pLfoInfo->fade  = pRegion->pitchlfo_fade;
        pLfoInfo->pitch = pRegion->pitchlfo_depth;
        
        LFOv1Unit::Trigger();
    }
    
    void FilLFOUnit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        pLfoInfo->delay  = pRegion->fillfo_delay;
        pLfoInfo->freq   = pRegion->fillfo_freq;
        pLfoInfo->fade   = pRegion->fillfo_fade;
        pLfoInfo->cutoff = pRegion->fillfo_depth;
        
        LFOv1Unit::Trigger();
    }
    
    CCUnit::CCUnit(SfzSignalUnitRack* rack, Listener* l): CCSignalUnit(rack, l) {
        pVoice = NULL;
    }
    
    void CCUnit::Trigger() {
        for (int i = 0; i < Ctrls.size(); i++) {
            Ctrls[i].Value = pVoice->GetControllerValue(Ctrls[i].Controller);
        }
        CCSignalUnit::Trigger();
    }
    
     void CCUnit::SetCCs(::sfz::Array<int>& cc) {
         RemoveAllCCs();
         for (int i = 0; i < 128; i++) {
             if (cc[i] != 0) AddCC(i, cc[i]);
         }
     }
    
     void CCUnit::SetCCs(ArrayList< ::sfz::CC>& cc) {
         RemoveAllCCs();
         for (int i = 0; i < cc.size(); i++) {
             if (cc[i].Influence != 0) AddCC(cc[i].Controller, cc[i].Influence);
         }
     }


    EndpointUnit::EndpointUnit(SfzSignalUnitRack* rack): EndpointSignalUnit(rack) {
        
    }
    
    SfzSignalUnitRack* const EndpointUnit::GetRack() {
        return static_cast<SfzSignalUnitRack* const>(pRack);
    }
    
    void EndpointUnit::Trigger() {
        
    }
    
    bool EndpointUnit::Active() {
        if (GetRack()->suVolEG.Active()) return true;
        
        bool b = false;
        for (int i = 0; i < GetRack()->volEGs.size(); i++) {
            if (GetRack()->volEGs[i]->Active()) { b = true; break; }
        }
        
        return b;
    }
    
    float EndpointUnit::GetVolume() {
        float vol = GetRack()->suVolEG.Active() ? GetRack()->suVolEG.GetLevel() : 0;
        
        for (int i = 0; i < GetRack()->volEGs.size(); i++) {
            EGv2Unit* eg = GetRack()->volEGs[i];
            if (!eg->Active()) continue;
            vol += eg->GetLevel() * (eg->pEGInfo->amplitude / 100.0f);
        }
        
        AmpLFOUnit* u = &(GetRack()->suAmpLFO);
        vol *= u->Active() ? ::sf2::ToRatio((u->GetLevel() * u->pLfoInfo->volume) * 10.0) : 1;
        
        return vol;
    }
    
    float EndpointUnit::GetFilterCutoff() {
        float val;
        
        FilLFOUnit* u = &(GetRack()->suFilLFO);
        val = u->Active() ? RTMath::CentsToFreqRatioUnlimited(u->GetLevel() * u->pLfoInfo->cutoff) : 1;
        
        FilEGUnit* u2 = &(GetRack()->suFilEG);
        val *= u2->Active() ? RTMath::CentsToFreqRatioUnlimited(u2->GetLevel() * u2->depth) : 1;
        
        for (int i = 0; i < GetRack()->filLFOs.size(); i++) {
            LFOv2Unit* lfo = GetRack()->filLFOs[i];
            if (!lfo->Active()) continue;
            
            float f = lfo->GetLevel() * lfo->pLfoInfo->cutoff;
            val *= RTMath::CentsToFreqRatioUnlimited(f);
        }
        
        return val;
    }
    
    float EndpointUnit::GetPitch() {
        double p;
        EGv1Unit* u = &(GetRack()->suPitchEG);
        p = u->Active() ? RTMath::CentsToFreqRatioUnlimited(u->GetLevel() * u->depth) : 1;
        
        PitchLFOUnit* u2 = &(GetRack()->suPitchLFO);
        CCSignalUnit* u3 = &(GetRack()->suPitchLFO.suDepthCC);
        float f = u3->Active() ? u3->GetLevel() : 0;
        p *= u2->Active() ? RTMath::CentsToFreqRatioUnlimited(u2->GetLevel() * (u2->pLfoInfo->pitch + f)) : 1;
        
        for (int i = 0; i < GetRack()->pitchLFOs.size(); i++) {
            LFOv2Unit* lfo = GetRack()->pitchLFOs[i];
            if (!lfo->Active()) continue;
            
            float f = lfo->suPitchOnCC.Active() ? lfo->suPitchOnCC.GetLevel() : 0;
            p *= RTMath::CentsToFreqRatioUnlimited(lfo->GetLevel() * (lfo->pLfoInfo->pitch + f));
        }
        
        return p;
    }
    
    float EndpointUnit::GetResonance() {
         float val = 0;
        
        for (int i = 0; i < GetRack()->resLFOs.size(); i++) {
            LFOv2Unit* lfo = GetRack()->resLFOs[i];
            if (!lfo->Active()) continue;
            
            val += lfo->GetLevel() * lfo->pLfoInfo->resonance;
        }
        
        return val;
    }
    
    float EndpointUnit::GetPan() {
        float pan = 0;
        
        for (int i = 0; i < GetRack()->panLFOs.size(); i++) {
            LFOv2Unit* lfo = GetRack()->panLFOs[i];
            if (!lfo->Active()) continue;
            
            pan += lfo->GetLevel() * lfo->pLfoInfo->pan;
        }
        
        if(pan < -100) return -100;
        if(pan >  100) return  100;
        
        return pan;
    }
    
    
    SfzSignalUnitRack::SfzSignalUnitRack(Voice* voice)
        : SignalUnitRack(MaxUnitCount), pVoice(voice), suEndpoint(this), suVolEG(this), suFilEG(this), suPitchEG(this),
        EGs(maxEgCount), volEGs(maxEgCount), pitchEGs(maxEgCount),
        suAmpLFO(this), suPitchLFO(this), suFilLFO(this),
        LFOs(maxLfoCount), pitchLFOs(maxLfoCount), filLFOs(maxLfoCount), resLFOs(maxLfoCount), panLFOs(maxLfoCount)
    {
        suEndpoint.pVoice = suVolEG.pVoice = suFilEG.pVoice = suPitchEG.pVoice = voice;
        suAmpLFO.pVoice = suPitchLFO.pVoice = suFilLFO.pVoice = voice;
        suPitchLFO.suDepthCC.pVoice = suPitchLFO.suFadeEG.pVoice = suPitchLFO.suFreqOnCC.pVoice = voice;
        suFilLFO.suFadeEG.pVoice = suFilLFO.suFreqOnCC.pVoice = voice;
        suAmpLFO.suFadeEG.pVoice = suAmpLFO.suFreqOnCC.pVoice = voice;
        
        for (int i = 0; i < EGs.capacity(); i++) {
            EGs[i] = new EGv2Unit(this);
            EGs[i]->pVoice = voice;
        }
        
        for (int i = 0; i < LFOs.capacity(); i++) {
            LFOs[i] = new LFOv2Unit(this);
            LFOs[i]->pVoice = voice;
            LFOs[i]->suFadeEG.pVoice = voice;
            LFOs[i]->suPitchOnCC.pVoice = voice;
            LFOs[i]->suFreqOnCC.pVoice = voice;
        }
    }
    
    SfzSignalUnitRack::~SfzSignalUnitRack() {
        for (int i = 0; i < EGs.capacity(); i++) {
            delete EGs[i]; EGs[i] = NULL;
        }
        
        for (int i = 0; i < LFOs.capacity(); i++) {
            delete LFOs[i]; LFOs[i] = NULL;
        }
    }
    
    void SfzSignalUnitRack::Trigger() {
        EGs.clear();
        volEGs.clear();
        pitchEGs.clear();
        
        LFOs.clear();
        pitchLFOs.clear();
        filLFOs.clear();
        resLFOs.clear();
        panLFOs.clear();
        
        ::sfz::Region* const pRegion = pVoice->pRegion;
        
        for (int i = 0; i < pRegion->eg.size(); i++) {
            if (pRegion->eg[i].node.size() == 0) continue;
            
            if(EGs.size() < EGs.capacity()) {
                EGv2Unit eg(this);
                eg.pEGInfo = &(pRegion->eg[i]);
                EGs.increment()->Copy(eg);
            } else { std::cerr << "Maximum number of EGs reached!" << std::endl; break; }
            
            if (pRegion->eg[i].amplitude > 0) {
                if(volEGs.size() < volEGs.capacity()) volEGs.add(EGs[EGs.size() - 1]);
                else std::cerr << "Maximum number of EGs reached!" << std::endl;
            }
        }
        
        if (pRegion->ampeg_sustain == -1) {
            if (volEGs.size() > 0) pRegion->ampeg_sustain = 0;
            else pRegion->ampeg_sustain = 100;
        }
        
        // LFO
        for (int i = 0; i < pRegion->lfos.size(); i++) {
            if (pRegion->lfos[i].freq == -1) continue; // Not initialized
            
            if(LFOs.size() < LFOs.capacity()) {
                LFOv2Unit lfo(this);
                lfo.pLfoInfo = &(pRegion->lfos[i]);
                LFOs.increment()->Copy(lfo);
                LFOs[LFOs.size() - 1]->suPitchOnCC.SetCCs(pRegion->lfos[i].pitch_oncc);
                LFOs[LFOs.size() - 1]->suFreqOnCC.SetCCs(pRegion->lfos[i].freq_oncc);
            } else { std::cerr << "Maximum number of LFOs reached!" << std::endl; break; }
            
            if (pRegion->lfos[i].pitch != 0 || !pRegion->lfos[i].pitch_oncc.empty()) {
                if(pitchLFOs.size() < pitchLFOs.capacity()) pitchLFOs.add(LFOs[LFOs.size() - 1]);
                else std::cerr << "Maximum number of LFOs reached!" << std::endl;
            }
            
            if (pRegion->lfos[i].cutoff != 0) {
                if(filLFOs.size() < filLFOs.capacity()) filLFOs.add(LFOs[LFOs.size() - 1]);
                else std::cerr << "Maximum number of LFOs reached!" << std::endl;
            }
            
            if (pRegion->lfos[i].resonance != 0) {
                if(resLFOs.size() < resLFOs.capacity()) resLFOs.add(LFOs[LFOs.size() - 1]);
                else std::cerr << "Maximum number of LFOs reached!" << std::endl;
            }
            
            if (pRegion->lfos[i].pan != 0) {
                if(panLFOs.size() < panLFOs.capacity()) panLFOs.add(LFOs[LFOs.size() - 1]);
                else std::cerr << "Maximum number of LFOs reached!" << std::endl;
            }
        }
        
        suPitchLFO.suDepthCC.SetCCs(pRegion->pitchlfo_depthcc);
        suPitchLFO.suFreqOnCC.SetCCs(pRegion->pitchlfo_freqcc);
        
        suFilLFO.suFreqOnCC.SetCCs(pRegion->fillfo_freqcc);
        
        suAmpLFO.suFreqOnCC.SetCCs(pRegion->amplfo_freqcc);
        
        Units.clear();
        
        Units.add(&suVolEG);
        Units.add(&suFilEG);
        Units.add(&suPitchEG);
        
        Units.add(&suPitchLFO.suFreqOnCC); // Don't change order! (should be triggered before the LFO)
        Units.add(&suPitchLFO);
        Units.add(&suPitchLFO.suDepthCC);
        Units.add(&suPitchLFO.suFadeEG);
        
        Units.add(&suAmpLFO.suFreqOnCC); // Don't change order! (should be triggered before the LFO)
        Units.add(&suAmpLFO);
        Units.add(&suAmpLFO.suFadeEG);
        
        Units.add(&suFilLFO.suFreqOnCC); // Don't change order! (should be triggered before the LFO)
        Units.add(&suFilLFO);
        Units.add(&suFilLFO.suFadeEG);
        
        for (int i = 0; i < EGs.size(); i++) {
            Units.add(EGs[i]);
        }
        
        for (int i = 0; i < LFOs.size(); i++) {
            Units.add(&(LFOs[i]->suFreqOnCC)); // Don't change order! (should be triggered before the LFO)
            Units.add(LFOs[i]);
            Units.add(&(LFOs[i]->suFadeEG));
            Units.add(&(LFOs[i]->suPitchOnCC));
        }
        
        Units.add(&suEndpoint);
        
        SignalUnitRack::Trigger();
    }
    
    EndpointSignalUnit* SfzSignalUnitRack::GetEndpointUnit() {
        return &suEndpoint;
    }
    
    void SfzSignalUnitRack::EnterFadeOutStage() {
        suVolEG.EG.enterFadeOutStage();
        
        for (int i = 0; i < volEGs.size(); i++) {
            volEGs[i]->EG.enterFadeOutStage();
        }
    }
    
}} // namespace LinuxSampler::sfz
