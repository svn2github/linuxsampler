/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2008 Christian Schoenebeck                       *
 *   Copyright (C) 2009 - 2011 Christian Schoenebeck and Grigor Iliev      *
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

#include "Voice.h"

#include "Engine.h"
#include "EngineChannel.h"

namespace LinuxSampler { namespace sf2 {

    Voice::Voice() {
        pEngine = NULL;
        pEG1 = &EG1;
        pEG2 = &EG2;
    }

    Voice::~Voice() {

    }

    EngineChannel* Voice::GetSf2EngineChannel() {
        return static_cast<EngineChannel*>(pEngineChannel);
    }

    void Voice::SetEngine(LinuxSampler::Engine* pEngine) {
        Engine* engine = static_cast<Engine*>(pEngine);
        this->pEngine     = engine;
        this->pDiskThread = engine->pDiskThread;
        dmsg(6,("Voice::SetEngine()\n"));
    }

    Voice::SampleInfo Voice::GetSampleInfo() {
        SampleInfo si;
        si.SampleRate       = pSample->SampleRate;
        si.ChannelCount     = pSample->GetChannelCount();
        si.FrameSize        = pSample->GetFrameSize();
        si.BitDepth         = (pSample->GetFrameSize() / pSample->GetChannelCount()) * 8;
        si.TotalFrameCount  = pSample->GetTotalFrameCount();

        si.HasLoops       = pRegion->HasLoop;
        si.LoopStart      = (si.HasLoops) ? pRegion->LoopStart : 0;
        si.LoopLength     = (si.HasLoops) ? ((pRegion->LoopEnd) - pRegion->LoopStart): 0;
        si.LoopPlayCount  = 0; // TODO:
        si.Unpitched      = pSample->IsUnpitched();

        return si;
    }

    Voice::RegionInfo Voice::GetRegionInfo() {
        ::sf2::Region* reg = NULL;
        ::sf2::Preset* preset = GetSf2EngineChannel()->pInstrument;
        for (int i = 0; i < preset->GetRegionCount(); i++) { // TODO: some optimization?
            if (preset->GetRegion(i)->pInstrument == pRegion->GetParentInstrument()) {
                reg = preset->GetRegion(i); // TODO: Can the instrument belong to more than one preset region?
                break;
            }
        }
        pPresetRegion = reg;

        RegionInfo ri;
        ri.UnityNote = pRegion->GetUnityNote();
        ri.FineTune  = pRegion->GetFineTune(reg) + (pRegion->GetCoarseTune(reg) * 100);
        ri.Pan       = pRegion->GetPan(reg);
        ri.SampleStartOffset = pRegion->startAddrsOffset + pRegion->startAddrsCoarseOffset;

        // filter cutoff frequency
        ri.EG2PreAttack        = 1000;
        ri.EG2Attack           = pRegion->GetEG2Attack(reg);
        //ri.EG2Hold             = pRegion->EG2Hold; // TODO:
        ri.EG2Decay1           = pRegion->GetEG2Decay(reg);
        ri.EG2Decay2           = pRegion->GetEG2Decay(reg);
        ri.EG2Sustain          = pRegion->GetEG2Sustain(reg);
        ri.EG2InfiniteSustain  = true;
        ri.EG2Release          = pRegion->GetEG2Release(reg);

        // sample pitch
        ri.EG3Attack     = 0; // TODO:
        ri.EG3Depth      = 0; // TODO:
        ri.VCFEnabled    = false; // TODO:
        ri.VCFType       = Filter::vcf_type_2p_lowpass; // TODO:
        ri.VCFResonance  = 0; // TODO:

        ri.ReleaseTriggerDecay = 0; // TODO:

        return ri;
    }

    Voice::InstrumentInfo Voice::GetInstrumentInfo() {
        InstrumentInfo ii;
        ii.FineTune = 0; // TODO: 
        ii.PitchbendRange = 2; // TODO: 

        return ii;
    }

    double Voice::GetSampleAttenuation() {
        return 1.0; // TODO: 
    }

    double Voice::GetVelocityAttenuation(uint8_t MIDIKeyVelocity) {
        return double(MIDIKeyVelocity) / 127.0f; // TODO: 
    }

    double Voice::GetVelocityRelease(uint8_t MIDIKeyVelocity) {
        return 0.9; // TODO:
    }

    void Voice::ProcessCCEvent(RTList<Event>::Iterator& itEvent) {
        /*if (itEvent->Type == Event::type_control_change && itEvent->Param.CC.Controller) { // if (valid) MIDI control change event
            if (pRegion->AttenuationController.type == ::gig::attenuation_ctrl_t::type_controlchange &&
                itEvent->Param.CC.Controller == pRegion->AttenuationController.controller_number) {
                CrossfadeSmoother.update(AbstractEngine::CrossfadeCurve[CrossfadeAttenuation(itEvent->Param.CC.Value)]);
            }
        }*/ // TODO: ^^^
    }

    void Voice::ProcessCutoffEvent(RTList<Event>::Iterator& itEvent) {
        /*int ccvalue = itEvent->Param.CC.Value;
        if (VCFCutoffCtrl.value == ccvalue) return;
        VCFCutoffCtrl.value == ccvalue;
        if (pRegion->VCFCutoffControllerInvert)  ccvalue = 127 - ccvalue;
        if (ccvalue < pRegion->VCFVelocityScale) ccvalue = pRegion->VCFVelocityScale;
        float cutoff = CutoffBase * float(ccvalue);
        if (cutoff > 127.0f) cutoff = 127.0f;

        VCFCutoffCtrl.fvalue = cutoff; // needed for initialization of fFinalCutoff next time
        fFinalCutoff = cutoff;*/ // TODO: ^^^
    }

    double Voice::CalculateCrossfadeVolume(uint8_t MIDIKeyVelocity) {
        /*float crossfadeVolume;
        switch (pRegion->AttenuationController.type) {
            case ::gig::attenuation_ctrl_t::type_channelaftertouch:
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(GetSf2EngineChannel()->ControllerTable[128])];
                break;
            case ::gig::attenuation_ctrl_t::type_velocity:
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(MIDIKeyVelocity)];
                break;
            case ::gig::attenuation_ctrl_t::type_controlchange: //FIXME: currently not sample accurate
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(GetSf2EngineChannel()->ControllerTable[pRegion->AttenuationController.controller_number])];
                break;
            case ::gig::attenuation_ctrl_t::type_none: // no crossfade defined
            default:
                crossfadeVolume = 1.0f;
        }

        return crossfadeVolume;*/ // TODO: ^^^
        return 1.0f;
    }

    double Voice::GetEG1ControllerValue(uint8_t MIDIKeyVelocity) {
        /*double eg1controllervalue = 0;
        switch (pRegion->EG1Controller.type) {
            case ::gig::eg1_ctrl_t::type_none: // no controller defined
                eg1controllervalue = 0;
                break;
            case ::gig::eg1_ctrl_t::type_channelaftertouch:
                eg1controllervalue = GetSf2EngineChannel()->ControllerTable[128];
                break;
            case ::gig::eg1_ctrl_t::type_velocity:
                eg1controllervalue = MIDIKeyVelocity;
                break;
            case ::gig::eg1_ctrl_t::type_controlchange: // MIDI control change controller
                eg1controllervalue = GetSf2EngineChannel()->ControllerTable[pRegion->EG1Controller.controller_number];
                break;
        }
        if (pRegion->EG1ControllerInvert) eg1controllervalue = 127 - eg1controllervalue;

        return eg1controllervalue;*/ // TODO: ^^^
        return 0;
    }

    Voice::EGInfo Voice::CalculateEG1ControllerInfluence(double eg1ControllerValue) {
        /*EGInfo eg;
        // (eg1attack is different from the others)
        eg.Attack  = (pRegion->EG1ControllerAttackInfluence)  ?
            1 + 0.031 * (double) (pRegion->EG1ControllerAttackInfluence == 1 ?
                                  1 : 1 << pRegion->EG1ControllerAttackInfluence) * eg1ControllerValue : 1.0;
        eg.Decay   = (pRegion->EG1ControllerDecayInfluence)   ? 1 + 0.00775 * (double) (1 << pRegion->EG1ControllerDecayInfluence)   * eg1ControllerValue : 1.0;
        eg.Release = (pRegion->EG1ControllerReleaseInfluence) ? 1 + 0.00775 * (double) (1 << pRegion->EG1ControllerReleaseInfluence) * eg1ControllerValue : 1.0;

        return eg;*/ // TODO: ^^^
        EGInfo eg;
        eg.Attack = 1.0;
        eg.Decay = 1.0;
        eg.Release = 1.0;
        return eg;
    }

    void Voice::TriggerEG1(const EGInfo& egInfo, double velrelease, double velocityAttenuation, uint sampleRate, uint8_t velocity) {
        EG1.trigger(0,
                    pRegion->GetEG1Attack(pPresetRegion),
                    pRegion->GetEG1Hold(pPresetRegion),
                    pRegion->GetEG1Decay(pPresetRegion),
                    uint(pRegion->GetEG1Sustain(pPresetRegion)),
                    pRegion->GetEG1Release(pPresetRegion),
                    sampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
    }

    double Voice::GetEG2ControllerValue(uint8_t MIDIKeyVelocity) {
        /*double eg2controllervalue = 0;
        switch (pRegion->EG2Controller.type) {
            case ::gig::eg2_ctrl_t::type_none: // no controller defined
                eg2controllervalue = 0;
                break;
            case ::gig::eg2_ctrl_t::type_channelaftertouch:
                eg2controllervalue = GetSf2EngineChannel()->ControllerTable[128];
                break;
            case ::gig::eg2_ctrl_t::type_velocity:
                eg2controllervalue = MIDIKeyVelocity;
                break;
            case ::gig::eg2_ctrl_t::type_controlchange: // MIDI control change controller
                eg2controllervalue = GetSf2EngineChannel()->ControllerTable[pRegion->EG2Controller.controller_number];
                break;
        }
        if (pRegion->EG2ControllerInvert) eg2controllervalue = 127 - eg2controllervalue;

        return eg2controllervalue;*/ // TODO: ^^^
        return 0;
    }

    Voice::EGInfo Voice::CalculateEG2ControllerInfluence(double eg2ControllerValue) {
        /*EGInfo eg;
        eg.Attack  = (pRegion->EG2ControllerAttackInfluence)  ? 1 + 0.00775 * (double) (1 << pRegion->EG2ControllerAttackInfluence)  * eg2ControllerValue : 1.0;
        eg.Decay   = (pRegion->EG2ControllerDecayInfluence)   ? 1 + 0.00775 * (double) (1 << pRegion->EG2ControllerDecayInfluence)   * eg2ControllerValue : 1.0;
        eg.Release = (pRegion->EG2ControllerReleaseInfluence) ? 1 + 0.00775 * (double) (1 << pRegion->EG2ControllerReleaseInfluence) * eg2ControllerValue : 1.0;

        return eg;*/ // TODO: ^^^
        EGInfo eg;
        eg.Attack = 1.0;
        eg.Decay = 1.0;
        eg.Release = 1.0;
        return eg;
    }

    void Voice::TriggerEG2(const EGInfo& egInfo, double velrelease, double velocityAttenuation, uint sampleRate, uint8_t velocity) {
        EG2.trigger(uint(RgnInfo.EG2PreAttack),
                    RgnInfo.EG2Attack * egInfo.Attack,
                    false,
                    RgnInfo.EG2Decay1 * egInfo.Decay * velrelease,
                    RgnInfo.EG2Decay2 * egInfo.Decay * velrelease,
                    RgnInfo.EG2InfiniteSustain,
                    uint(RgnInfo.EG2Sustain),
                    RgnInfo.EG2Release * egInfo.Release * velrelease,
                    velocityAttenuation,
                    sampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
    }

    void Voice::InitLFO1() {
        /*uint16_t lfo1_internal_depth;
        switch (pRegion->LFO1Controller) {
            case ::gig::lfo1_ctrl_internal:
                lfo1_internal_depth  = pRegion->LFO1InternalDepth;
                pLFO1->ExtController = 0; // no external controller
                bLFO1Enabled         = (lfo1_internal_depth > 0);
                break;
            case ::gig::lfo1_ctrl_modwheel:
                lfo1_internal_depth  = 0;
                pLFO1->ExtController = 1; // MIDI controller 1
                bLFO1Enabled         = (pRegion->LFO1ControlDepth > 0);
                break;
            case ::gig::lfo1_ctrl_breath:
                lfo1_internal_depth  = 0;
                pLFO1->ExtController = 2; // MIDI controller 2
                bLFO1Enabled         = (pRegion->LFO1ControlDepth > 0);
                break;
            case ::gig::lfo1_ctrl_internal_modwheel:
                lfo1_internal_depth  = pRegion->LFO1InternalDepth;
                pLFO1->ExtController = 1; // MIDI controller 1
                bLFO1Enabled         = (lfo1_internal_depth > 0 || pRegion->LFO1ControlDepth > 0);
                break;
            case ::gig::lfo1_ctrl_internal_breath:
                lfo1_internal_depth  = pRegion->LFO1InternalDepth;
                pLFO1->ExtController = 2; // MIDI controller 2
                bLFO1Enabled         = (lfo1_internal_depth > 0 || pRegion->LFO1ControlDepth > 0);
                break;
            default:
                lfo1_internal_depth  = 0;
                pLFO1->ExtController = 0; // no external controller
                bLFO1Enabled         = false;
        }
        if (bLFO1Enabled) {
            pLFO1->trigger(pRegion->LFO1Frequency,
                           start_level_min,
                           lfo1_internal_depth,
                           pRegion->LFO1ControlDepth,
                           pRegion->LFO1FlipPhase,
                           pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            pLFO1->update(pLFO1->ExtController ? GetSf2EngineChannel()->ControllerTable[pLFO1->ExtController] : 0);
        }*/ // TODO: ^^^
        bLFO1Enabled = false;
    }

    void Voice::InitLFO2() {
        /*uint16_t lfo2_internal_depth;
        switch (pRegion->LFO2Controller) {
            case ::gig::lfo2_ctrl_internal:
                lfo2_internal_depth  = pRegion->LFO2InternalDepth;
                pLFO2->ExtController = 0; // no external controller
                bLFO2Enabled         = (lfo2_internal_depth > 0);
                break;
            case ::gig::lfo2_ctrl_modwheel:
                lfo2_internal_depth  = 0;
                pLFO2->ExtController = 1; // MIDI controller 1
                bLFO2Enabled         = (pRegion->LFO2ControlDepth > 0);
                break;
            case ::gig::lfo2_ctrl_foot:
                lfo2_internal_depth  = 0;
                pLFO2->ExtController = 4; // MIDI controller 4
                bLFO2Enabled         = (pRegion->LFO2ControlDepth > 0);
                break;
            case ::gig::lfo2_ctrl_internal_modwheel:
                lfo2_internal_depth  = pRegion->LFO2InternalDepth;
                pLFO2->ExtController = 1; // MIDI controller 1
                bLFO2Enabled         = (lfo2_internal_depth > 0 || pRegion->LFO2ControlDepth > 0);
                break;
            case ::gig::lfo2_ctrl_internal_foot:
                lfo2_internal_depth  = pRegion->LFO2InternalDepth;
                pLFO2->ExtController = 4; // MIDI controller 4
                bLFO2Enabled         = (lfo2_internal_depth > 0 || pRegion->LFO2ControlDepth > 0);
                break;
            default:
                lfo2_internal_depth  = 0;
                pLFO2->ExtController = 0; // no external controller
                bLFO2Enabled         = false;
        }
        if (bLFO2Enabled) {
            pLFO2->trigger(pRegion->LFO2Frequency,
                           start_level_max,
                           lfo2_internal_depth,
                           pRegion->LFO2ControlDepth,
                           pRegion->LFO2FlipPhase,
                           pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            pLFO2->update(pLFO2->ExtController ? GetSf2EngineChannel()->ControllerTable[pLFO2->ExtController] : 0);
        }*/ // TODO: ^^^
         bLFO2Enabled = false;
    }

    void Voice::InitLFO3() {
        /*uint16_t lfo3_internal_depth;
        switch (pRegion->LFO3Controller) {
            case ::gig::lfo3_ctrl_internal:
                lfo3_internal_depth  = pRegion->LFO3InternalDepth;
                pLFO3->ExtController = 0; // no external controller
                bLFO3Enabled         = (lfo3_internal_depth > 0);
                break;
            case ::gig::lfo3_ctrl_modwheel:
                lfo3_internal_depth  = 0;
                pLFO3->ExtController = 1; // MIDI controller 1
                bLFO3Enabled         = (pRegion->LFO3ControlDepth > 0);
                break;
            case ::gig::lfo3_ctrl_aftertouch:
                lfo3_internal_depth  = 0;
                pLFO3->ExtController = 128;
                bLFO3Enabled         = true;
                break;
            case ::gig::lfo3_ctrl_internal_modwheel:
                lfo3_internal_depth  = pRegion->LFO3InternalDepth;
                pLFO3->ExtController = 1; // MIDI controller 1
                bLFO3Enabled         = (lfo3_internal_depth > 0 || pRegion->LFO3ControlDepth > 0);
                break;
            case ::gig::lfo3_ctrl_internal_aftertouch:
                lfo3_internal_depth  = pRegion->LFO3InternalDepth;
                pLFO1->ExtController = 128;
                bLFO3Enabled         = (lfo3_internal_depth > 0 || pRegion->LFO3ControlDepth > 0);
                break;
            default:
                lfo3_internal_depth  = 0;
                pLFO3->ExtController = 0; // no external controller
                bLFO3Enabled         = false;
        }
        if (bLFO3Enabled) {
            pLFO3->trigger(pRegion->LFO3Frequency,
                           start_level_mid,
                           lfo3_internal_depth,
                           pRegion->LFO3ControlDepth,
                           false,
                           pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            pLFO3->update(pLFO3->ExtController ? GetSf2EngineChannel()->ControllerTable[pLFO3->ExtController] : 0);
        }*/ // TODO: ^^^
         bLFO3Enabled = false;
    }

    float Voice::CalculateCutoffBase(uint8_t MIDIKeyVelocity) {
        /*float cutoff = pRegion->GetVelocityCutoff(MIDIKeyVelocity);
        if (pRegion->VCFKeyboardTracking) {
            cutoff *= RTMath::CentsToFreqRatioUnlimited((MIDIKey - pRegion->VCFKeyboardTrackingBreakpoint) * 100);
        }
        return cutoff;*/ // TODO: ^^^
        return 1.0f;
    }

    float Voice::CalculateFinalCutoff(float cutoffBase) {
        /*int cvalue;
        if (VCFCutoffCtrl.controller) {
            cvalue = GetSf2EngineChannel()->ControllerTable[VCFCutoffCtrl.controller];
            if (pRegion->VCFCutoffControllerInvert) cvalue = 127 - cvalue;
            // VCFVelocityScale in this case means Minimum cutoff
            if (cvalue < pRegion->VCFVelocityScale) cvalue = pRegion->VCFVelocityScale;
        }
        else {
            cvalue = pRegion->VCFCutoff;
        }
        float fco = cutoffBase * float(cvalue);
        if (fco > 127.0f) fco = 127.0f;

        return fco;*/ // TODO: ^^^
        return 0.0f;
    }

    uint8_t Voice::GetVCFCutoffCtrl() {
        /*uint8_t ctrl;
        switch (pRegion->VCFCutoffController) {
            case ::gig::vcf_cutoff_ctrl_modwheel:
                ctrl = 1;
                break;
            case ::gig::vcf_cutoff_ctrl_effect1:
                ctrl = 12;
                break;
            case ::gig::vcf_cutoff_ctrl_effect2:
                ctrl = 13;
                break;
            case ::gig::vcf_cutoff_ctrl_breath:
                ctrl = 2;
                break;
            case ::gig::vcf_cutoff_ctrl_foot:
                ctrl = 4;
                break;
            case ::gig::vcf_cutoff_ctrl_sustainpedal:
                ctrl = 64;
                break;
            case ::gig::vcf_cutoff_ctrl_softpedal:
                ctrl = 67;
                break;
            case ::gig::vcf_cutoff_ctrl_genpurpose7:
                ctrl = 82;
                break;
            case ::gig::vcf_cutoff_ctrl_genpurpose8:
                ctrl = 83;
                break;
            case ::gig::vcf_cutoff_ctrl_aftertouch:
                ctrl = 128;
                break;
            case ::gig::vcf_cutoff_ctrl_none:
            default:
                ctrl = 0;
                break;
        }

        return ctrl;*/ // TODO: ^^^
        return 0;
    }

    uint8_t Voice::GetVCFResonanceCtrl() {
        /*uint8_t ctrl;
        switch (pRegion->VCFResonanceController) {
            case ::gig::vcf_res_ctrl_genpurpose3:
                ctrl = 18;
                break;
            case ::gig::vcf_res_ctrl_genpurpose4:
                ctrl = 19;
                break;
            case ::gig::vcf_res_ctrl_genpurpose5:
                ctrl = 80;
                break;
            case ::gig::vcf_res_ctrl_genpurpose6:
                ctrl = 81;
                break;
            case ::gig::vcf_res_ctrl_none:
            default:
                ctrl = 0;
        }

        return ctrl;*/ // TODO: ^^^
        return 0;
    }

    void Voice::ProcessGroupEvent(RTList<Event>::Iterator& itEvent) {
        if (itEvent->Param.Note.Key != MIDIKey) {
            // kill the voice fast
            pEG1->enterFadeOutStage();
        }
    }

}} // namespace LinuxSampler::sf2
