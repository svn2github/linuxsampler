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

        // GetEG1Sustain gets the decrease in level in centibels
        uint sustain = ::sf2::ToRatio(-1 * pOwner->pRegion->GetEG1Sustain(pOwner->pPresetRegion)) * 1000; // in permille
        
        trigger (
            0, // should be in permille
            pOwner->pRegion->GetEG1Attack(pOwner->pPresetRegion),
            pOwner->pRegion->GetEG1Hold(pOwner->pPresetRegion),
            pOwner->pRegion->GetEG1Decay(pOwner->pPresetRegion),
            sustain,
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
            uint(1000 - pOwner->pRegion->GetEG2Sustain(pOwner->pPresetRegion)),
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


    void ModLfoUnit::Trigger() {
        //reset
        Level = 0;
        
        // set the delay trigger
        double samplerate = pOwner->GetSampleRate() / CONFIG_DEFAULT_SUBFRAGMENT_SIZE;
        uiDelayTrigger = pOwner->pRegion->GetDelayModLfo(pOwner->pPresetRegion) * samplerate;
        ////////////
            
        trigger (
            pOwner->pRegion->GetFreqModLfo(pOwner->pPresetRegion),
            start_level_min,
            1, 0, false, samplerate
        );
        update(0);
    }

    void ModLfoUnit::Increment() {
        if (DelayStage()) return;
        
        SignalUnitBase<Voice>::Increment();
        
        Level = render();
    }


    void VibLfoUnit::Trigger() {
        //reset
        Level = 0;

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


    EndpointUnit::EndpointUnit() {
        
    }

    void EndpointUnit::Trigger() {
        prmModEgPitch->Coeff = pOwner->pRegion->GetModEnvToPitch(pOwner->pPresetRegion);
        if (prmModEgPitch->Coeff == ::sf2::NONE) prmModEgPitch->Coeff = 0;

        prmModEgCutoff->Coeff = pOwner->pRegion->GetModEnvToFilterFc(pOwner->pPresetRegion); // cents
        if (prmModEgCutoff->Coeff == ::sf2::NONE) prmModEgCutoff->Coeff = 0;

        prmModLfoVol->Coeff = pOwner->pRegion->GetModLfoToVolume(pOwner->pPresetRegion); // centibels
        if (prmModLfoVol->Coeff == ::sf2::NONE) prmModLfoVol->Coeff = 0;

        prmModLfoCutoff->Coeff = pOwner->pRegion->GetModLfoToFilterFc(pOwner->pPresetRegion);
        if (prmModLfoCutoff->Coeff == ::sf2::NONE) prmModLfoCutoff->Coeff = 0;

        prmModLfoPitch->Coeff = pOwner->pRegion->GetModLfoToPitch(pOwner->pPresetRegion);
        if (prmModLfoPitch->Coeff == ::sf2::NONE) prmModLfoPitch->Coeff = 0;
    }
    
    bool EndpointUnit::Active() {
        if (Params.size() < 1) return false;
        return prmVolEg->pUnit->Active(); // volEGUnit
    }
    
    float EndpointUnit::GetVolume() {
        if (!prmVolEg->pUnit->Active()) return 0;
        return prmVolEg->GetValue() * 
               ::sf2::ToRatio(prmModLfoVol->GetValue() /*logarithmically modified */);
    }
    
    float EndpointUnit::GetFilterCutoff() {
        double modEg, modLfo;
        modEg = prmModEgCutoff->pUnit->Active() ? prmModEgCutoff->GetValue() : 0;
        modEg = RTMath::CentsToFreqRatioUnlimited(modEg);
        
        modLfo = prmModLfoCutoff->pUnit->Active() ? prmModLfoCutoff->GetValue() : 0;
        modLfo = RTMath::CentsToFreqRatioUnlimited(modLfo);
        
        return modEg * modLfo;
    }
    
    float EndpointUnit::GetPitch() {
        double modEg, modLfo, vibLfo;
        modEg  = prmModEgPitch->pUnit->Active() ? RTMath::CentsToFreqRatioUnlimited(prmModEgPitch->GetValue()) : 1;
        modLfo = prmModLfoPitch->pUnit->Active() ? RTMath::CentsToFreqRatioUnlimited(prmModLfoPitch->GetValue()) : 1;
        vibLfo = prmVibLfo->pUnit->Active() ? RTMath::CentsToFreqRatioUnlimited(prmVibLfo->GetValue()) : 1;
        
        return modEg * modLfo * vibLfo;
    }
    
    float EndpointUnit::GetResonance() {
        return 1;
    }
    
    SF2SignalUnitRack::SF2SignalUnitRack(Voice* pVoice): SignalUnitRackBase<Voice>(pVoice) {
        Units.add(&suVolEG);
        Units.add(&suModEG);
        Units.add(&suModLfo);
        Units.add(&suVibLfo);
        Units.add(&suEndpoint);
        
        // Volume envelope
        suEndpoint.Params.add(SignalUnit::Parameter(&suVolEG)); // Volume
        // Modulation envelope
        suEndpoint.Params.add(SignalUnit::Parameter(&suModEG)); // Pitch
        suEndpoint.Params.add(SignalUnit::Parameter(&suModEG)); // Filter cutoff
        // Modulation LFO
        suEndpoint.Params.add(SignalUnit::Parameter(&suModLfo)); // Volume
        suEndpoint.Params.add(SignalUnit::Parameter(&suModLfo)); // Pitch
        suEndpoint.Params.add(SignalUnit::Parameter(&suModLfo)); // Filter cutoff
        // Vibrato LFO
        suEndpoint.Params.add(SignalUnit::Parameter(&suVibLfo)); // Pitch

        /* This should be done at the end because when a parameter is added to
           ArrayList a new copy is made for all parameters */
        suEndpoint.prmVolEg = &suEndpoint.Params[0];
        suEndpoint.prmModEgPitch = &suEndpoint.Params[1];
        suEndpoint.prmModEgCutoff = &suEndpoint.Params[2];
        suEndpoint.prmModLfoVol = &suEndpoint.Params[3];
        suEndpoint.prmModLfoPitch = &suEndpoint.Params[4];
        suEndpoint.prmModLfoCutoff = &suEndpoint.Params[5];
        suEndpoint.prmVibLfo = &suEndpoint.Params[6];
    }
    
    void SF2SignalUnitRack::Trigger() {
        // The region settings are available after the voice is triggered

        SignalUnitRackBase<Voice>::Trigger();
    }
    
    EndpointSignalUnit* SF2SignalUnitRack::GetEndpointUnit() {
        return static_cast<EndpointSignalUnit*> (&suEndpoint);
    }
    
}} // namespace LinuxSampler::sf2
