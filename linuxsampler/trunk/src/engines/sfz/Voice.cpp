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

#define LN_10_DIV_20 0.115129254649702

namespace LinuxSampler { namespace sfz {

    typedef LinuxSampler::VoiceBase<EngineChannel, ::sfz::Region, Sample, DiskThread> SfzVoice;
    Voice::Voice(): SignalRack(this), SfzVoice(&SignalRack) {
        pEngine     = NULL;
    }

    Voice::~Voice() {

    }

    EngineChannel* Voice::GetSfzEngineChannel() {
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
        si.SampleRate       = pSample->GetSampleRate();
        si.ChannelCount     = pSample->GetChannelCount();
        si.FrameSize        = pSample->GetFrameSize();
        si.BitDepth         = (pSample->GetFrameSize() / pSample->GetChannelCount()) * 8;
        si.TotalFrameCount  = pSample->GetTotalFrameCount();

        si.HasLoops       = pRegion->HasLoop();
        si.LoopStart      = pRegion->GetLoopStart();
        si.LoopLength     = pRegion->GetLoopEnd() - pRegion->GetLoopStart();
        si.LoopPlayCount  = pRegion->GetLoopCount();
        si.Unpitched      = pRegion->pitch_keytrack == 0;
        return si;
    }

    Voice::RegionInfo Voice::GetRegionInfo() {
        RegionInfo ri;
        ri.UnityNote = pRegion->pitch_keycenter;
        ri.FineTune  = pRegion->tune + pRegion->transpose * 100;
        ri.Pan       = int(pRegion->pan * 0.63); // convert from -100..100 to -64..63
        ri.SampleStartOffset = pRegion->offset ? *(pRegion->offset) : 0;

        ri.EG2PreAttack        = pRegion->fileg_start * 10;
        ri.EG2Attack           = pRegion->fileg_attack;
        //ri.EG2Hold             = pRegion->fileg_hold; // TODO: 
        ri.EG2Decay1           = pRegion->fileg_decay;
        ri.EG2Decay2           = pRegion->fileg_decay;
        ri.EG2Sustain          = pRegion->fileg_sustain * 10;
        ri.EG2InfiniteSustain  = true;
        ri.EG2Release          = pRegion->fileg_release;

        ri.EG3Attack     = pRegion->pitcheg_attack;
        ri.EG3Depth      = 0; // TODO:
        ri.VCFEnabled    = pRegion->cutoff;
        switch (pRegion->fil_type) {
        case ::sfz::LPF_1P:
            ri.VCFType = Filter::vcf_type_1p_lowpass;
            break;
        case ::sfz::LPF_2P:
            ri.VCFType = Filter::vcf_type_2p_lowpass;
            break;
        case ::sfz::LPF_4P:
            ri.VCFType = Filter::vcf_type_4p_lowpass;
            break;
        case ::sfz::LPF_6P:
            ri.VCFType = Filter::vcf_type_6p_lowpass;
            break;
        case ::sfz::HPF_1P:
            ri.VCFType = Filter::vcf_type_1p_highpass;
            break;
        case ::sfz::HPF_2P:
            ri.VCFType = Filter::vcf_type_2p_highpass;
            break;
        case ::sfz::HPF_4P:
            ri.VCFType = Filter::vcf_type_4p_highpass;
            break;
        case ::sfz::HPF_6P:
            ri.VCFType = Filter::vcf_type_6p_highpass;
            break;
        case ::sfz::BPF_1P:
        case ::sfz::BPF_2P:
            ri.VCFType = Filter::vcf_type_2p_bandpass;
            break;
        case ::sfz::BRF_1P:
        case ::sfz::BRF_2P:
            ri.VCFType = Filter::vcf_type_2p_bandreject;
            break;
        case ::sfz::APF_1P:
        case ::sfz::PKF_2P:
        default:
            ri.VCFEnabled = false;
            break;
        }

        ri.VCFResonance  = pRegion->resonance;

        // rt_decay is in dB. Precalculate a suitable value for exp in
        // GetReleaseTriggerAttenuation: -ln(10) / 20 * rt_decay
        ri.ReleaseTriggerDecay = -LN_10_DIV_20 * pRegion->rt_decay;

        return ri;
    }

    Voice::InstrumentInfo Voice::GetInstrumentInfo() {
        InstrumentInfo ii;
        ii.FineTune = 0; // TODO: 
        ii.PitchbendRange = 2; // TODO: 

        return ii;
    }

    double Voice::GetSampleAttenuation() {
        return exp(LN_10_DIV_20 * pRegion->volume);
    }

    double Voice::GetVelocityAttenuation(uint8_t MIDIKeyVelocity) {
        return pRegion->amp_velcurve[MIDIKeyVelocity];
    }

    double Voice::GetVelocityRelease(uint8_t MIDIKeyVelocity) {
        return 127.0 / MIDIKeyVelocity;
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
        int ccvalue = itEvent->Param.CC.Value;
        if (VCFCutoffCtrl.value == ccvalue) return;
        VCFCutoffCtrl.value = ccvalue;

        float cutoff = CutoffBase * RTMath::CentsToFreqRatioUnlimited(
            ccvalue / 127.0f * pRegion->cutoff_oncc[VCFCutoffCtrl.controller]);
        if (cutoff > 0.49 * pEngine->SampleRate) cutoff = 0.49 * pEngine->SampleRate;

        VCFCutoffCtrl.fvalue = cutoff; // needed for initialization of fFinalCutoff next time
        fFinalCutoff = cutoff;
    }

    double Voice::CalculateCrossfadeVolume(uint8_t MIDIKeyVelocity) {
        /*float crossfadeVolume;
        switch (pRegion->AttenuationController.type) {
            case ::gig::attenuation_ctrl_t::type_channelaftertouch:
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(GetSfzEngineChannel()->ControllerTable[128])];
                break;
            case ::gig::attenuation_ctrl_t::type_velocity:
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(MIDIKeyVelocity)];
                break;
            case ::gig::attenuation_ctrl_t::type_controlchange: //FIXME: currently not sample accurate
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(GetSfzEngineChannel()->ControllerTable[pRegion->AttenuationController.controller_number])];
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
                eg1controllervalue = GetSfzEngineChannel()->ControllerTable[128];
                break;
            case ::gig::eg1_ctrl_t::type_velocity:
                eg1controllervalue = MIDIKeyVelocity;
                break;
            case ::gig::eg1_ctrl_t::type_controlchange: // MIDI control change controller
                eg1controllervalue = GetSfzEngineChannel()->ControllerTable[pRegion->EG1Controller.controller_number];
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

        // TODO: controller modulation

        // first check if there is a v2 EG for amplitude
        for (int i = 0 ; i < pRegion->eg.size() ; i++) {
            if (pRegion->eg[i].amplitude > 0) {
                // TODO: actually use the value of the amplitude parameter
                pEG1 = &EG1;
                EG1.trigger(pRegion->eg[i], sampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE, velocity);
                return;
            }
        }

        // otherwise use the v1 EGADSR
        pEG1 = &EGADSR1;
        EGADSR1.trigger(uint(pRegion->ampeg_start * 10),
                        std::max(0.0, pRegion->ampeg_attack + pRegion->ampeg_vel2attack * velrelease),
                        std::max(0.0, pRegion->ampeg_hold + pRegion->ampeg_vel2hold * velrelease),
                        std::max(0.0, pRegion->ampeg_decay + pRegion->ampeg_vel2decay * velrelease),
                        uint(std::min(std::max(0.0, 10 * (pRegion->ampeg_sustain + pRegion->ampeg_vel2sustain * velrelease)), 1000.0)),
                        std::max(0.0, pRegion->ampeg_release + pRegion->ampeg_vel2release * velrelease),
                        sampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
    }

    double Voice::GetEG2ControllerValue(uint8_t MIDIKeyVelocity) {
        /*double eg2controllervalue = 0;
        switch (pRegion->EG2Controller.type) {
            case ::gig::eg2_ctrl_t::type_none: // no controller defined
                eg2controllervalue = 0;
                break;
            case ::gig::eg2_ctrl_t::type_channelaftertouch:
                eg2controllervalue = GetSfzEngineChannel()->ControllerTable[128];
                break;
            case ::gig::eg2_ctrl_t::type_velocity:
                eg2controllervalue = MIDIKeyVelocity;
                break;
            case ::gig::eg2_ctrl_t::type_controlchange: // MIDI control change controller
                eg2controllervalue = GetSfzEngineChannel()->ControllerTable[pRegion->EG2Controller.controller_number];
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

        // TODO: the sfz filter EG should modulate cents, not hertz,
        // so we can't use the EG or EGADSR as it is. Disable for now.

        pEG2 = &EGADSR2;
        EGADSR2.trigger(0,
                        0,
                        false,
                        0,
                        1000,
                        0,
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
            pLFO1->update(pLFO1->ExtController ? GetSfzEngineChannel()->ControllerTable[pLFO1->ExtController] : 0);
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
            pLFO2->update(pLFO2->ExtController ? GetSfzEngineChannel()->ControllerTable[pLFO2->ExtController] : 0);
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
            pLFO3->update(pLFO3->ExtController ? GetSfzEngineChannel()->ControllerTable[pLFO3->ExtController] : 0);
        }*/ // TODO: ^^^
        bLFO3Enabled = false;
    }

    float Voice::CalculateCutoffBase(uint8_t MIDIKeyVelocity) {
        float cutoff = *pRegion->cutoff;
        cutoff *= RTMath::CentsToFreqRatioUnlimited(
            MIDIKeyVelocity / 127.0f * pRegion->fil_veltrack +
            (MIDIKey - pRegion->fil_keycenter) * pRegion->fil_keytrack);
        return cutoff;
    }

    float Voice::CalculateFinalCutoff(float cutoffBase) {
        float cutoff;
        if (VCFCutoffCtrl.controller) {
            int ccvalue = GetSfzEngineChannel()->ControllerTable[VCFCutoffCtrl.controller];
            cutoff = CutoffBase * RTMath::CentsToFreqRatioUnlimited(
                ccvalue / 127.0f * pRegion->cutoff_oncc[VCFCutoffCtrl.controller]);
        } else {
            cutoff = cutoffBase;
        }
        if (cutoff > 0.49 * pEngine->SampleRate) cutoff = 0.49 * pEngine->SampleRate;
        return cutoff;
    }

    uint8_t Voice::GetVCFCutoffCtrl() {
        // TODO: the sfz format allows several CC for the same
        // modulation destination. The Voice interface needs to be
        // changed to support that.
        if (pRegion->cutoff_cc) return pRegion->cutoff_cc;
        else if (pRegion->cutoff_chanaft) return 128;
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

    float Voice::GetReleaseTriggerAttenuation(float noteLength) {
        // pow(10, -rt_decay * noteLength / 20):
        return expf(RgnInfo.ReleaseTriggerDecay * noteLength);
    }

    void Voice::ProcessGroupEvent(RTList<Event>::Iterator& itEvent) {
        dmsg(4,("Voice %x processGroupEvents event type=%d", this, itEvent->Type));
        if (itEvent->Type == Event::type_control_change ||
            (Type & Voice::type_controller_triggered) ||
            itEvent->Param.Note.Key != MIDIKey) {
            dmsg(4,("Voice %x - kill", this));
            if (pRegion->off_mode == ::sfz::OFF_NORMAL) {
                // turn off the voice by entering release envelope stage
                EnterReleaseStage();
            } else {
                // kill the voice fast
                SignalRack.EnterFadeOutStage();
            }
        }
    }
    
    void Voice::SetSampleStartOffset() {
        if (DiskVoice && RgnInfo.SampleStartOffset > pSample->MaxOffset) {
            // The offset is applied to the RAM buffer
            finalSynthesisParameters.dPos = 0;
            Pos = 0;
        } else {
            finalSynthesisParameters.dPos = RgnInfo.SampleStartOffset; // offset where we should start playback of sample
            Pos = RgnInfo.SampleStartOffset;
        }
    }

}} // namespace LinuxSampler::sfz
