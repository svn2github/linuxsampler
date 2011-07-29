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
    

    void LFOUnit::Increment() {
        if (DelayStage()) return;
        
        SignalUnit::Increment();
        
        Level = pLFO->Render();
    }
    
    void LFOUnit::Trigger() {
        //reset
        Level = 0;
        
        // set the delay trigger
        uiDelayTrigger = pLfoInfo->delay * GetSampleRate();
    }
    
    void LFOv1Unit::Trigger() {
        LFOUnit::Trigger();
        
        lfo.trigger (
            pLfoInfo->freq,
            start_level_mid,
            1, 0, false, GetSampleRate()
        );
        lfo.update(0);
    }
    
    
    LFOv2Unit::LFOv2Unit(SfzSignalUnitRack* rack)
        : LFOUnit(rack), lfos(8), lfo0(1200.0f), lfo1(1200.0f), lfo2(1200.0f),
          lfo3(1200.0f), lfo4(1200.0f), lfo5(1200.0f), lfo6(1200.0f), lfo7(1200.0f)
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
            pLfoInfo->freq,
            start_level_mid,
            1, 0, false, GetSampleRate()
        );
        pLFO->Update(0);
    }
    
    void AmpLFOUnit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        pLfoInfo->delay = pRegion->amplfo_delay;
        pLfoInfo->freq = pRegion->amplfo_freq;
        pLfoInfo->volume = pRegion->amplfo_depth;
        
        LFOv1Unit::Trigger();
    }
    
    void PitchLFOUnit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        pLfoInfo->delay = pRegion->pitchlfo_delay;
        pLfoInfo->freq = pRegion->pitchlfo_freq;
        pLfoInfo->pitch = pRegion->pitchlfo_depth;
        
        LFOv1Unit::Trigger();
    }
    
    void FilLFOUnit::Trigger() {
        ::sfz::Region* const pRegion = pVoice->pRegion;
        pLfoInfo->delay = pRegion->fillfo_delay;
        pLfoInfo->freq = pRegion->fillfo_freq;
        pLfoInfo->cutoff = pRegion->fillfo_depth;
        
        LFOv1Unit::Trigger();
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
        p *= u2->Active() ? RTMath::CentsToFreqRatioUnlimited(u2->GetLevel() * u2->pLfoInfo->pitch) : 1;
        
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
        LFOs(maxLfoCount), filLFOs(maxLfoCount), resLFOs(maxLfoCount), panLFOs(maxLfoCount)
    {
        suEndpoint.pVoice = suVolEG.pVoice = suFilEG.pVoice = suPitchEG.pVoice = voice;
        suAmpLFO.pVoice = suPitchLFO.pVoice = suFilLFO.pVoice = voice;
        
        for (int i = 0; i < EGs.capacity(); i++) {
            EGs[i] = new EGv2Unit(this);
            EGs[i]->pVoice = voice;
        }
        
        for (int i = 0; i < LFOs.capacity(); i++) {
            LFOs[i] = new LFOv2Unit(this);
            LFOs[i]->pVoice = voice;
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
            } else { std::cerr << "Maximum number of LFOs reached!" << std::endl; break; }
            
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
        
        Units.clear();
        
        Units.add(&suVolEG);
        Units.add(&suFilEG);
        Units.add(&suPitchEG);
        Units.add(&suPitchLFO);
        Units.add(&suAmpLFO);
        Units.add(&suFilLFO);
        
        for (int i = 0; i < EGs.size(); i++) {
            Units.add(EGs[i]);
        }
        
        for (int i = 0; i < LFOs.size(); i++) {
            Units.add(LFOs[i]);
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
