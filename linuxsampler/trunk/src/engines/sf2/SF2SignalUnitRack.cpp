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

#include "SF2SignalUnitRack.h"
#include "Voice.h"

namespace LinuxSampler { namespace sf2 {
    
    void EGUnit::EnterReleaseStage() {
        update(EG::event_release, pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
    }
    
    void EGUnit::CancelRelease() {
        update(EG::event_cancel_release, pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
    }

    
    void VolEGUnit::Trigger() {
        // set the delay trigger
        double d = pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE;
        uiDelayTrigger = pOwner->pRegion->GetEG1PreAttackDelay(pOwner->pPresetRegion) * d;
        ////////////
            
        trigger (
            0, // should be in permille
            pOwner->pRegion->GetEG1Attack(pOwner->pPresetRegion),
            pOwner->pRegion->GetEG1Hold(pOwner->pPresetRegion),
            pOwner->pRegion->GetEG1Decay(pOwner->pPresetRegion),
            uint(pOwner->pRegion->GetEG1Sustain(pOwner->pPresetRegion)),
            pOwner->pRegion->GetEG1Release(pOwner->pPresetRegion),
            pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE
        );
    }
    
    void VolEGUnit::Increment() {
        if (DelayStage()) return;

        EGUnit::Increment();
        if (!active()) return;
        
        switch (getSegmentType()) {
            case EG::segment_lin:
                processLin();
                break;
            case EG::segment_exp:
                processExp();
                break;
            case EG::segment_end:
                getLevel();
                break; // noop
            case EG::segment_pow:
                processPow();
                break;
        }
        
        if (active()) {

            // if sample has a loop and loop start has been reached in this subfragment, send a special event to EG1 to let it finish the attack hold stage
            /*if (pOwner->SmplInfo.HasLoops && pOwner->Pos <= pOwner->SmplInfo.LoopStart && pOwner->SmplInfo.LoopStart < newPos) {
                update(EG::event_hold_end, pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            }*/
            // TODO: ^^^

            increment(1);
            if (!toStageEndLeft()) update(EG::event_stage_end, pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
         }
    }
    
    void ModEGUnit::Trigger() {
        double d = pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE;
        uiDelayTrigger = pOwner->pRegion->GetEG2PreAttackDelay(pOwner->pPresetRegion) * d;

        trigger (
            0, // should be in permille
            pOwner->pRegion->GetEG2Attack(pOwner->pPresetRegion),
            pOwner->pRegion->GetEG2Hold(pOwner->pPresetRegion),
            pOwner->pRegion->GetEG2Decay(pOwner->pPresetRegion),
            uint(pOwner->pRegion->GetEG2Sustain(pOwner->pPresetRegion)),
            pOwner->pRegion->GetEG2Release(pOwner->pPresetRegion),
            pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE
        );
    }
    
    void ModEGUnit::Increment() {
        if (DelayStage()) return;

        EGUnit::Increment();
        if (!active()) return;
        
        switch (getSegmentType()) {
            case EG::segment_lin:
                processLin();
                break;
            case EG::segment_exp:
                processExp();
                break;
            case EG::segment_end:
                getLevel();
                break; // noop
            case EG::segment_pow:
                processPow();
                break;
        }
        
        if (active()) {
            increment(1);
            if (!toStageEndLeft()) update(EG::event_stage_end, pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
         }
    }


    void VibLfoUnit::Trigger() {
        // set the delay trigger
        double samplerate = pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE;
        uiDelayTrigger = pOwner->pRegion->GetDelayVibLfo(pOwner->pPresetRegion) * samplerate;
        ////////////
            
        trigger (
            pOwner->pRegion->GetFreqVibLfo(pOwner->pPresetRegion),
            start_level_min,
            pOwner->pRegion->GetVibLfoToPitch(pOwner->pPresetRegion),
            0, false, samplerate
        );
        update(0);
    }
    void VibLfoUnit::Increment() {
        if (DelayStage()) return;
        
        SignalUnitBase<Voice>::Increment();
        
        Level = render();
    }
    

    void EndpointUnit::Trigger() {
        
    }
    
    bool EndpointUnit::Active() {
        if (Params.size() < 1) return false;
        return Params[0].pUnit->Active(); // volEGUnit
    }
    
    float EndpointUnit::GetVolume() {
        if (Params.size() < 1) return 0;
        return Params[0].pUnit->Active() ? Params[0].GetFinalValue() : 0;
    }
    
    float EndpointUnit::GetFilterCutoff() {
        return 1;
    }
    
    float EndpointUnit::GetPitch() {
        if (Params.size() < 3) return 0;
        double eg  = Params[1].pUnit->Active() ? RTMath::CentsToFreqRatio(Params[1].GetFinalValue()) : 1;
        double lfo = Params[2].pUnit->Active() ? RTMath::CentsToFreqRatio(Params[2].GetFinalValue()) : 1;
        
        return eg * lfo;
    }
    
    float EndpointUnit::GetResonance() {
        return 1;
    }
    
    SF2SignalUnitRack::SF2SignalUnitRack(Voice* pVoice): SignalUnitRackBase<Voice>(pVoice) {
        Units.add(&suVolEG);
        Units.add(&suModEG);
        Units.add(&suVibLfo);
        Units.add(&suEndpoint);
        
        // Volume envelope
        suEndpoint.Params.add(SignalUnit::Parameter(&suVolEG));
        // Modulation envelope
        suEndpoint.Params.add(SignalUnit::Parameter(&suModEG));
        // Vibrato LFO
        suEndpoint.Params.add(SignalUnit::Parameter(&suVibLfo));
    }
    
    void SF2SignalUnitRack::Trigger() {
        // The region settings are available after the voice is triggered

        // Modulation envelope
        int pitch = pOwner->pRegion->GetModEnvToPitch(pOwner->pPresetRegion);
        suEndpoint.Params[1].Coeff = pitch;
        ///////

        SignalUnitRackBase<Voice>::Trigger();
    }
    
    EndpointSignalUnit* SF2SignalUnitRack::GetEndpointUnit() {
        return static_cast<EndpointSignalUnit*> (&suEndpoint);
    }
    
}} // namespace LinuxSampler::sf2
