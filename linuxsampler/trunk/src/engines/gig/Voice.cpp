/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
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

#include "../../common/Features.h"
#include "Synthesizer.h"
#include "Profiler.h"

#include "Voice.h"

namespace LinuxSampler { namespace gig {

    Voice::Voice() {
        pEngine     = NULL;
        pDiskThread = NULL;
        PlaybackState = playback_state_end;
        pLFO1 = new LFOUnsigned(1.0f);  // amplitude EG (0..1 range)
        pLFO2 = new LFOUnsigned(1.0f);  // filter EG (0..1 range)
        pLFO3 = new LFOSigned(1200.0f); // pitch EG (-1200..+1200 range)
        KeyGroup = 0;
        SynthesisMode = 0; // set all mode bits to 0 first
        // select synthesis implementation (asm core is not supported ATM)
        #if 0 // CONFIG_ASM && ARCH_X86
        SYNTHESIS_MODE_SET_IMPLEMENTATION(SynthesisMode, Features::supportsMMX() && Features::supportsSSE());
        #else
        SYNTHESIS_MODE_SET_IMPLEMENTATION(SynthesisMode, false);
        #endif
        SYNTHESIS_MODE_SET_PROFILING(SynthesisMode, Profiler::isEnabled());

        finalSynthesisParameters.filterLeft.Reset();
        finalSynthesisParameters.filterRight.Reset();
    }

    Voice::~Voice() {
        if (pLFO1) delete pLFO1;
        if (pLFO2) delete pLFO2;
        if (pLFO3) delete pLFO3;
    }

    void Voice::SetEngine(Engine* pEngine) {
        this->pEngine     = pEngine;
        this->pDiskThread = pEngine->pDiskThread;
        dmsg(6,("Voice::SetEngine()\n"));
    }

    /**
     *  Initializes and triggers the voice, a disk stream will be launched if
     *  needed.
     *
     *  @param pEngineChannel - engine channel on which this voice was ordered
     *  @param itNoteOnEvent  - event that caused triggering of this voice
     *  @param PitchBend      - MIDI detune factor (-8192 ... +8191)
     *  @param pDimRgn        - points to the dimension region which provides sample wave(s) and articulation data
     *  @param VoiceType      - type of this voice
     *  @param iKeyGroup      - a value > 0 defines a key group in which this voice is member of
     *  @returns 0 on success, a value < 0 if the voice wasn't triggered
     *           (either due to an error or e.g. because no region is
     *           defined for the given key)
     */
    int Voice::Trigger(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itNoteOnEvent, int PitchBend, ::gig::DimensionRegion* pDimRgn, type_t VoiceType, int iKeyGroup) {
        this->pEngineChannel = pEngineChannel;
        this->pDimRgn        = pDimRgn;
        Orphan = false;

        #if CONFIG_DEVMODE
        if (itNoteOnEvent->FragmentPos() > pEngine->MaxSamplesPerCycle) { // just a sanity check for debugging
            dmsg(1,("Voice::Trigger(): ERROR, TriggerDelay > Totalsamples\n"));
        }
        #endif // CONFIG_DEVMODE

        Type            = VoiceType;
        MIDIKey         = itNoteOnEvent->Param.Note.Key;
        PlaybackState   = playback_state_init; // mark voice as triggered, but no audio rendered yet
        Delay           = itNoteOnEvent->FragmentPos();
        itTriggerEvent  = itNoteOnEvent;
        itKillEvent     = Pool<Event>::Iterator();
        KeyGroup        = iKeyGroup;
        pSample         = pDimRgn->pSample; // sample won't change until the voice is finished

        // calculate volume
        const double velocityAttenuation = pDimRgn->GetVelocityAttenuation(itNoteOnEvent->Param.Note.Velocity);

        // For 16 bit samples, we downscale by 32768 to convert from
        // int16 value range to DSP value range (which is
        // -1.0..1.0). For 24 bit, we downscale from int32.
        float volume = velocityAttenuation / (pSample->BitDepth == 16 ? 32768.0f : 32768.0f * 65536.0f);

        volume *= pDimRgn->SampleAttenuation * pEngineChannel->GlobalVolume * GLOBAL_VOLUME;

        // the volume of release triggered samples depends on note length
        if (Type == type_release_trigger) {
            float noteLength = float(pEngine->FrameTime + Delay -
                                     pEngineChannel->pMIDIKeyInfo[MIDIKey].NoteOnTime) / pEngine->SampleRate;
            float attenuation = 1 - 0.01053 * (256 >> pDimRgn->ReleaseTriggerDecay) * noteLength;
            if (attenuation <= 0) return -1;
            volume *= attenuation;
        }

        // select channel mode (mono or stereo)
        SYNTHESIS_MODE_SET_CHANNELS(SynthesisMode, pSample->Channels == 2);
        // select bit depth (16 or 24)
        SYNTHESIS_MODE_SET_BITDEPTH24(SynthesisMode, pSample->BitDepth == 24);

        // get starting crossfade volume level
        float crossfadeVolume;
        switch (pDimRgn->AttenuationController.type) {
            case ::gig::attenuation_ctrl_t::type_channelaftertouch:
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(pEngineChannel->ControllerTable[128])];
                break;
            case ::gig::attenuation_ctrl_t::type_velocity:
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(itNoteOnEvent->Param.Note.Velocity)];
                break;
            case ::gig::attenuation_ctrl_t::type_controlchange: //FIXME: currently not sample accurate
                crossfadeVolume = Engine::CrossfadeCurve[CrossfadeAttenuation(pEngineChannel->ControllerTable[pDimRgn->AttenuationController.controller_number])];
                break;
            case ::gig::attenuation_ctrl_t::type_none: // no crossfade defined
            default:
                crossfadeVolume = 1.0f;
        }

        VolumeLeft  = volume * Engine::PanCurve[64 - pDimRgn->Pan];
        VolumeRight = volume * Engine::PanCurve[64 + pDimRgn->Pan];

        float subfragmentRate = pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE;
        CrossfadeSmoother.trigger(crossfadeVolume, subfragmentRate);
        VolumeSmoother.trigger(pEngineChannel->MidiVolume, subfragmentRate);
        PanLeftSmoother.trigger(pEngineChannel->GlobalPanLeft, subfragmentRate);
        PanRightSmoother.trigger(pEngineChannel->GlobalPanRight, subfragmentRate);

        finalSynthesisParameters.dPos = pDimRgn->SampleStartOffset; // offset where we should start playback of sample (0 - 2000 sample points)
        Pos = pDimRgn->SampleStartOffset;

        // Check if the sample needs disk streaming or is too short for that
        long cachedsamples = pSample->GetCache().Size / pSample->FrameSize;
        DiskVoice          = cachedsamples < pSample->SamplesTotal;

        const DLS::sample_loop_t& loopinfo = pDimRgn->pSampleLoops[0];

        if (DiskVoice) { // voice to be streamed from disk
            MaxRAMPos = cachedsamples - (pEngine->MaxSamplesPerCycle << CONFIG_MAX_PITCH) / pSample->Channels; //TODO: this calculation is too pessimistic and may better be moved to Render() method, so it calculates MaxRAMPos dependent to the current demand of sample points to be rendered (e.g. in case of JACK)

            // check if there's a loop defined which completely fits into the cached (RAM) part of the sample
            RAMLoop = (pDimRgn->SampleLoops && (loopinfo.LoopStart + loopinfo.LoopLength) <= MaxRAMPos);

            if (pDiskThread->OrderNewStream(&DiskStreamRef, pDimRgn, MaxRAMPos, !RAMLoop) < 0) {
                dmsg(1,("Disk stream order failed!\n"));
                KillImmediately();
                return -1;
            }
            dmsg(4,("Disk voice launched (cached samples: %d, total Samples: %d, MaxRAMPos: %d, RAMLooping: %s)\n", cachedsamples, pSample->SamplesTotal, MaxRAMPos, (RAMLoop) ? "yes" : "no"));
        }
        else { // RAM only voice
            MaxRAMPos = cachedsamples;
            RAMLoop = (pDimRgn->SampleLoops != 0);
            dmsg(4,("RAM only voice launched (Looping: %s)\n", (RAMLoop) ? "yes" : "no"));
        }
        if (RAMLoop) {
            loop.uiTotalCycles = pSample->LoopPlayCount;
            loop.uiCyclesLeft  = pSample->LoopPlayCount;
            loop.uiStart       = loopinfo.LoopStart;
            loop.uiEnd         = loopinfo.LoopStart + loopinfo.LoopLength;
            loop.uiSize        = loopinfo.LoopLength;
        }

        // calculate initial pitch value
        {
            double pitchbasecents = pDimRgn->FineTune + (int) pEngine->ScaleTuning[MIDIKey % 12];

            // GSt behaviour: maximum transpose up is 40 semitones. If
            // MIDI key is more than 40 semitones above unity note,
            // the transpose is not done.
            if (pDimRgn->PitchTrack && (MIDIKey - (int) pDimRgn->UnityNote) < 40) pitchbasecents += (MIDIKey - (int) pDimRgn->UnityNote) * 100;

            this->PitchBase = RTMath::CentsToFreqRatio(pitchbasecents) * (double(pSample->SamplesPerSecond) / double(pEngine->SampleRate));
            this->PitchBend = RTMath::CentsToFreqRatio(((double) PitchBend / 8192.0) * 200.0); // pitchbend wheel +-2 semitones = 200 cents
        }

        // the length of the decay and release curves are dependent on the velocity
        const double velrelease = 1 / pDimRgn->GetVelocityRelease(itNoteOnEvent->Param.Note.Velocity);

        // setup EG 1 (VCA EG)
        {
            // get current value of EG1 controller
            double eg1controllervalue;
            switch (pDimRgn->EG1Controller.type) {
                case ::gig::eg1_ctrl_t::type_none: // no controller defined
                    eg1controllervalue = 0;
                    break;
                case ::gig::eg1_ctrl_t::type_channelaftertouch:
                    eg1controllervalue = pEngineChannel->ControllerTable[128];
                    break;
                case ::gig::eg1_ctrl_t::type_velocity:
                    eg1controllervalue = itNoteOnEvent->Param.Note.Velocity;
                    break;
                case ::gig::eg1_ctrl_t::type_controlchange: // MIDI control change controller
                    eg1controllervalue = pEngineChannel->ControllerTable[pDimRgn->EG1Controller.controller_number];
                    break;
            }
            if (pDimRgn->EG1ControllerInvert) eg1controllervalue = 127 - eg1controllervalue;

            // calculate influence of EG1 controller on EG1's parameters
            // (eg1attack is different from the others)
            double eg1attack  = (pDimRgn->EG1ControllerAttackInfluence)  ?
                1 + 0.031 * (double) (pDimRgn->EG1ControllerAttackInfluence == 1 ?
                                      1 : 1 << pDimRgn->EG1ControllerAttackInfluence) * eg1controllervalue : 1.0;
            double eg1decay   = (pDimRgn->EG1ControllerDecayInfluence)   ? 1 + 0.00775 * (double) (1 << pDimRgn->EG1ControllerDecayInfluence)   * eg1controllervalue : 1.0;
            double eg1release = (pDimRgn->EG1ControllerReleaseInfluence) ? 1 + 0.00775 * (double) (1 << pDimRgn->EG1ControllerReleaseInfluence) * eg1controllervalue : 1.0;

            EG1.trigger(pDimRgn->EG1PreAttack,
                        pDimRgn->EG1Attack * eg1attack,
                        pDimRgn->EG1Hold,
                        pDimRgn->EG1Decay1 * eg1decay * velrelease,
                        pDimRgn->EG1Decay2 * eg1decay * velrelease,
                        pDimRgn->EG1InfiniteSustain,
                        pDimRgn->EG1Sustain,
                        pDimRgn->EG1Release * eg1release * velrelease,
                        velocityAttenuation,
                        pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
        }

#ifdef CONFIG_INTERPOLATE_VOLUME
        // setup initial volume in synthesis parameters
#ifdef CONFIG_PROCESS_MUTED_CHANNELS
        if (pEngineChannel->GetMute()) {
            finalSynthesisParameters.fFinalVolumeLeft  = 0;
            finalSynthesisParameters.fFinalVolumeRight = 0;
        }
        else
#else
        {
            float finalVolume = pEngineChannel->MidiVolume * crossfadeVolume * EG1.getLevel();

            finalSynthesisParameters.fFinalVolumeLeft  = finalVolume * VolumeLeft  * pEngineChannel->GlobalPanLeft;
            finalSynthesisParameters.fFinalVolumeRight = finalVolume * VolumeRight * pEngineChannel->GlobalPanRight;
        }
#endif
#endif

        // setup EG 2 (VCF Cutoff EG)
        {
            // get current value of EG2 controller
            double eg2controllervalue;
            switch (pDimRgn->EG2Controller.type) {
                case ::gig::eg2_ctrl_t::type_none: // no controller defined
                    eg2controllervalue = 0;
                    break;
                case ::gig::eg2_ctrl_t::type_channelaftertouch:
                    eg2controllervalue = pEngineChannel->ControllerTable[128];
                    break;
                case ::gig::eg2_ctrl_t::type_velocity:
                    eg2controllervalue = itNoteOnEvent->Param.Note.Velocity;
                    break;
                case ::gig::eg2_ctrl_t::type_controlchange: // MIDI control change controller
                    eg2controllervalue = pEngineChannel->ControllerTable[pDimRgn->EG2Controller.controller_number];
                    break;
            }
            if (pDimRgn->EG2ControllerInvert) eg2controllervalue = 127 - eg2controllervalue;

            // calculate influence of EG2 controller on EG2's parameters
            double eg2attack  = (pDimRgn->EG2ControllerAttackInfluence)  ? 1 + 0.00775 * (double) (1 << pDimRgn->EG2ControllerAttackInfluence)  * eg2controllervalue : 1.0;
            double eg2decay   = (pDimRgn->EG2ControllerDecayInfluence)   ? 1 + 0.00775 * (double) (1 << pDimRgn->EG2ControllerDecayInfluence)   * eg2controllervalue : 1.0;
            double eg2release = (pDimRgn->EG2ControllerReleaseInfluence) ? 1 + 0.00775 * (double) (1 << pDimRgn->EG2ControllerReleaseInfluence) * eg2controllervalue : 1.0;

            EG2.trigger(pDimRgn->EG2PreAttack,
                        pDimRgn->EG2Attack * eg2attack,
                        false,
                        pDimRgn->EG2Decay1 * eg2decay * velrelease,
                        pDimRgn->EG2Decay2 * eg2decay * velrelease,
                        pDimRgn->EG2InfiniteSustain,
                        pDimRgn->EG2Sustain,
                        pDimRgn->EG2Release * eg2release * velrelease,
                        velocityAttenuation,
                        pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
        }


        // setup EG 3 (VCO EG)
        {
            // if portamento mode is on, we dedicate EG3 purely for portamento, otherwise if portamento is off we do as told by the patch
            bool  bPortamento = pEngineChannel->PortamentoMode && pEngineChannel->PortamentoPos >= 0.0f;
            float eg3depth = (bPortamento)
                                 ? RTMath::CentsToFreqRatio((pEngineChannel->PortamentoPos - (float) MIDIKey) * 100)
                                 : RTMath::CentsToFreqRatio(pDimRgn->EG3Depth);
            float eg3time = (bPortamento)
                                ? pEngineChannel->PortamentoTime
                                : pDimRgn->EG3Attack;
            EG3.trigger(eg3depth, eg3time, pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            dmsg(5,("PortamentoPos=%f, depth=%f, time=%f\n", pEngineChannel->PortamentoPos, eg3depth, eg3time));
        }


        // setup LFO 1 (VCA LFO)
        {
            uint16_t lfo1_internal_depth;
            switch (pDimRgn->LFO1Controller) {
                case ::gig::lfo1_ctrl_internal:
                    lfo1_internal_depth  = pDimRgn->LFO1InternalDepth;
                    pLFO1->ExtController = 0; // no external controller
                    bLFO1Enabled         = (lfo1_internal_depth > 0);
                    break;
                case ::gig::lfo1_ctrl_modwheel:
                    lfo1_internal_depth  = 0;
                    pLFO1->ExtController = 1; // MIDI controller 1
                    bLFO1Enabled         = (pDimRgn->LFO1ControlDepth > 0);
                    break;
                case ::gig::lfo1_ctrl_breath:
                    lfo1_internal_depth  = 0;
                    pLFO1->ExtController = 2; // MIDI controller 2
                    bLFO1Enabled         = (pDimRgn->LFO1ControlDepth > 0);
                    break;
                case ::gig::lfo1_ctrl_internal_modwheel:
                    lfo1_internal_depth  = pDimRgn->LFO1InternalDepth;
                    pLFO1->ExtController = 1; // MIDI controller 1
                    bLFO1Enabled         = (lfo1_internal_depth > 0 || pDimRgn->LFO1ControlDepth > 0);
                    break;
                case ::gig::lfo1_ctrl_internal_breath:
                    lfo1_internal_depth  = pDimRgn->LFO1InternalDepth;
                    pLFO1->ExtController = 2; // MIDI controller 2
                    bLFO1Enabled         = (lfo1_internal_depth > 0 || pDimRgn->LFO1ControlDepth > 0);
                    break;
                default:
                    lfo1_internal_depth  = 0;
                    pLFO1->ExtController = 0; // no external controller
                    bLFO1Enabled         = false;
            }
            if (bLFO1Enabled) {
                pLFO1->trigger(pDimRgn->LFO1Frequency,
                               start_level_min,
                               lfo1_internal_depth,
                               pDimRgn->LFO1ControlDepth,
                               pDimRgn->LFO1FlipPhase,
                               pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                pLFO1->update(pLFO1->ExtController ? pEngineChannel->ControllerTable[pLFO1->ExtController] : 0);
            }
        }


        // setup LFO 2 (VCF Cutoff LFO)
        {
            uint16_t lfo2_internal_depth;
            switch (pDimRgn->LFO2Controller) {
                case ::gig::lfo2_ctrl_internal:
                    lfo2_internal_depth  = pDimRgn->LFO2InternalDepth;
                    pLFO2->ExtController = 0; // no external controller
                    bLFO2Enabled         = (lfo2_internal_depth > 0);
                    break;
                case ::gig::lfo2_ctrl_modwheel:
                    lfo2_internal_depth  = 0;
                    pLFO2->ExtController = 1; // MIDI controller 1
                    bLFO2Enabled         = (pDimRgn->LFO2ControlDepth > 0);
                    break;
                case ::gig::lfo2_ctrl_foot:
                    lfo2_internal_depth  = 0;
                    pLFO2->ExtController = 4; // MIDI controller 4
                    bLFO2Enabled         = (pDimRgn->LFO2ControlDepth > 0);
                    break;
                case ::gig::lfo2_ctrl_internal_modwheel:
                    lfo2_internal_depth  = pDimRgn->LFO2InternalDepth;
                    pLFO2->ExtController = 1; // MIDI controller 1
                    bLFO2Enabled         = (lfo2_internal_depth > 0 || pDimRgn->LFO2ControlDepth > 0);
                    break;
                case ::gig::lfo2_ctrl_internal_foot:
                    lfo2_internal_depth  = pDimRgn->LFO2InternalDepth;
                    pLFO2->ExtController = 4; // MIDI controller 4
                    bLFO2Enabled         = (lfo2_internal_depth > 0 || pDimRgn->LFO2ControlDepth > 0);
                    break;
                default:
                    lfo2_internal_depth  = 0;
                    pLFO2->ExtController = 0; // no external controller
                    bLFO2Enabled         = false;
            }
            if (bLFO2Enabled) {
                pLFO2->trigger(pDimRgn->LFO2Frequency,
                               start_level_max,
                               lfo2_internal_depth,
                               pDimRgn->LFO2ControlDepth,
                               pDimRgn->LFO2FlipPhase,
                               pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                pLFO2->update(pLFO2->ExtController ? pEngineChannel->ControllerTable[pLFO2->ExtController] : 0);
            }
        }


        // setup LFO 3 (VCO LFO)
        {
            uint16_t lfo3_internal_depth;
            switch (pDimRgn->LFO3Controller) {
                case ::gig::lfo3_ctrl_internal:
                    lfo3_internal_depth  = pDimRgn->LFO3InternalDepth;
                    pLFO3->ExtController = 0; // no external controller
                    bLFO3Enabled         = (lfo3_internal_depth > 0);
                    break;
                case ::gig::lfo3_ctrl_modwheel:
                    lfo3_internal_depth  = 0;
                    pLFO3->ExtController = 1; // MIDI controller 1
                    bLFO3Enabled         = (pDimRgn->LFO3ControlDepth > 0);
                    break;
                case ::gig::lfo3_ctrl_aftertouch:
                    lfo3_internal_depth  = 0;
                    pLFO3->ExtController = 128;
                    bLFO3Enabled         = true;
                    break;
                case ::gig::lfo3_ctrl_internal_modwheel:
                    lfo3_internal_depth  = pDimRgn->LFO3InternalDepth;
                    pLFO3->ExtController = 1; // MIDI controller 1
                    bLFO3Enabled         = (lfo3_internal_depth > 0 || pDimRgn->LFO3ControlDepth > 0);
                    break;
                case ::gig::lfo3_ctrl_internal_aftertouch:
                    lfo3_internal_depth  = pDimRgn->LFO3InternalDepth;
                    pLFO1->ExtController = 128;
                    bLFO3Enabled         = (lfo3_internal_depth > 0 || pDimRgn->LFO3ControlDepth > 0);
                    break;
                default:
                    lfo3_internal_depth  = 0;
                    pLFO3->ExtController = 0; // no external controller
                    bLFO3Enabled         = false;
            }
            if (bLFO3Enabled) {
                pLFO3->trigger(pDimRgn->LFO3Frequency,
                               start_level_mid,
                               lfo3_internal_depth,
                               pDimRgn->LFO3ControlDepth,
                               false,
                               pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                pLFO3->update(pLFO3->ExtController ? pEngineChannel->ControllerTable[pLFO3->ExtController] : 0);
            }
        }


        #if CONFIG_FORCE_FILTER
        const bool bUseFilter = true;
        #else // use filter only if instrument file told so
        const bool bUseFilter = pDimRgn->VCFEnabled;
        #endif // CONFIG_FORCE_FILTER
        SYNTHESIS_MODE_SET_FILTER(SynthesisMode, bUseFilter);
        if (bUseFilter) {
            #ifdef CONFIG_OVERRIDE_CUTOFF_CTRL
            VCFCutoffCtrl.controller = CONFIG_OVERRIDE_CUTOFF_CTRL;
            #else // use the one defined in the instrument file
            switch (pDimRgn->VCFCutoffController) {
                case ::gig::vcf_cutoff_ctrl_modwheel:
                    VCFCutoffCtrl.controller = 1;
                    break;
                case ::gig::vcf_cutoff_ctrl_effect1:
                    VCFCutoffCtrl.controller = 12;
                    break;
                case ::gig::vcf_cutoff_ctrl_effect2:
                    VCFCutoffCtrl.controller = 13;
                    break;
                case ::gig::vcf_cutoff_ctrl_breath:
                    VCFCutoffCtrl.controller = 2;
                    break;
                case ::gig::vcf_cutoff_ctrl_foot:
                    VCFCutoffCtrl.controller = 4;
                    break;
                case ::gig::vcf_cutoff_ctrl_sustainpedal:
                    VCFCutoffCtrl.controller = 64;
                    break;
                case ::gig::vcf_cutoff_ctrl_softpedal:
                    VCFCutoffCtrl.controller = 67;
                    break;
                case ::gig::vcf_cutoff_ctrl_genpurpose7:
                    VCFCutoffCtrl.controller = 82;
                    break;
                case ::gig::vcf_cutoff_ctrl_genpurpose8:
                    VCFCutoffCtrl.controller = 83;
                    break;
                case ::gig::vcf_cutoff_ctrl_aftertouch:
                    VCFCutoffCtrl.controller = 128;
                    break;
                case ::gig::vcf_cutoff_ctrl_none:
                default:
                    VCFCutoffCtrl.controller = 0;
                    break;
            }
            #endif // CONFIG_OVERRIDE_CUTOFF_CTRL

            #ifdef CONFIG_OVERRIDE_RESONANCE_CTRL
            VCFResonanceCtrl.controller = CONFIG_OVERRIDE_RESONANCE_CTRL;
            #else // use the one defined in the instrument file
            switch (pDimRgn->VCFResonanceController) {
                case ::gig::vcf_res_ctrl_genpurpose3:
                    VCFResonanceCtrl.controller = 18;
                    break;
                case ::gig::vcf_res_ctrl_genpurpose4:
                    VCFResonanceCtrl.controller = 19;
                    break;
                case ::gig::vcf_res_ctrl_genpurpose5:
                    VCFResonanceCtrl.controller = 80;
                    break;
                case ::gig::vcf_res_ctrl_genpurpose6:
                    VCFResonanceCtrl.controller = 81;
                    break;
                case ::gig::vcf_res_ctrl_none:
                default:
                    VCFResonanceCtrl.controller = 0;
            }
            #endif // CONFIG_OVERRIDE_RESONANCE_CTRL

            #ifndef CONFIG_OVERRIDE_FILTER_TYPE
            finalSynthesisParameters.filterLeft.SetType(pDimRgn->VCFType);
            finalSynthesisParameters.filterRight.SetType(pDimRgn->VCFType);
            #else // override filter type
            finalSynthesisParameters.filterLeft.SetType(CONFIG_OVERRIDE_FILTER_TYPE);
            finalSynthesisParameters.filterRight.SetType(CONFIG_OVERRIDE_FILTER_TYPE);
            #endif // CONFIG_OVERRIDE_FILTER_TYPE

            VCFCutoffCtrl.value    = pEngineChannel->ControllerTable[VCFCutoffCtrl.controller];
            VCFResonanceCtrl.value = pEngineChannel->ControllerTable[VCFResonanceCtrl.controller];

            // calculate cutoff frequency
            float cutoff = pDimRgn->GetVelocityCutoff(itNoteOnEvent->Param.Note.Velocity);
            if (pDimRgn->VCFKeyboardTracking) {
                cutoff *= exp((itNoteOnEvent->Param.Note.Key - pDimRgn->VCFKeyboardTrackingBreakpoint) * 0.057762265f); // (ln(2) / 12)
            }
            CutoffBase = cutoff;

            int cvalue;
            if (VCFCutoffCtrl.controller) {
                cvalue = pEngineChannel->ControllerTable[VCFCutoffCtrl.controller];
                if (pDimRgn->VCFCutoffControllerInvert) cvalue = 127 - cvalue;
                // VCFVelocityScale in this case means Minimum cutoff
                if (cvalue < pDimRgn->VCFVelocityScale) cvalue = pDimRgn->VCFVelocityScale;
            }
            else {
                cvalue = pDimRgn->VCFCutoff;
            }
            cutoff *= float(cvalue);
            if (cutoff > 127.0f) cutoff = 127.0f;

            // calculate resonance
            float resonance = (float) (VCFResonanceCtrl.controller ? VCFResonanceCtrl.value : pDimRgn->VCFResonance);

            VCFCutoffCtrl.fvalue    = cutoff;
            VCFResonanceCtrl.fvalue = resonance;
        }
        else {
            VCFCutoffCtrl.controller    = 0;
            VCFResonanceCtrl.controller = 0;
        }

        return 0; // success
    }

    /**
     *  Renders the audio data for this voice for the current audio fragment.
     *  The sample input data can either come from RAM (cached sample or sample
     *  part) or directly from disk. The output signal will be rendered by
     *  resampling / interpolation. If this voice is a disk streaming voice and
     *  the voice completely played back the cached RAM part of the sample, it
     *  will automatically switch to disk playback for the next RenderAudio()
     *  call.
     *
     *  @param Samples - number of samples to be rendered in this audio fragment cycle
     */
    void Voice::Render(uint Samples) {

        // select default values for synthesis mode bits
        SYNTHESIS_MODE_SET_LOOP(SynthesisMode, false);

        switch (this->PlaybackState) {

            case playback_state_init:
                this->PlaybackState = playback_state_ram; // we always start playback from RAM cache and switch then to disk if needed
                // no break - continue with playback_state_ram

            case playback_state_ram: {
                    if (RAMLoop) SYNTHESIS_MODE_SET_LOOP(SynthesisMode, true); // enable looping

                    // render current fragment
                    Synthesize(Samples, (sample_t*) pSample->GetCache().pStart, Delay);

                    if (DiskVoice) {
                        // check if we reached the allowed limit of the sample RAM cache
                        if (finalSynthesisParameters.dPos > MaxRAMPos) {
                            dmsg(5,("Voice: switching to disk playback (Pos=%f)\n", finalSynthesisParameters.dPos));
                            this->PlaybackState = playback_state_disk;
                        }
                    } else if (finalSynthesisParameters.dPos >= pSample->GetCache().Size / pSample->FrameSize) {
                        this->PlaybackState = playback_state_end;
                    }
                }
                break;

            case playback_state_disk: {
                    if (!DiskStreamRef.pStream) {
                        // check if the disk thread created our ordered disk stream in the meantime
                        DiskStreamRef.pStream = pDiskThread->AskForCreatedStream(DiskStreamRef.OrderID);
                        if (!DiskStreamRef.pStream) {
                            std::cout << stderr << "Disk stream not available in time!" << std::endl << std::flush;
                            KillImmediately();
                            return;
                        }
                        DiskStreamRef.pStream->IncrementReadPos(pSample->Channels * (int(finalSynthesisParameters.dPos) - MaxRAMPos));
                        finalSynthesisParameters.dPos -= int(finalSynthesisParameters.dPos);
                        RealSampleWordsLeftToRead = -1; // -1 means no silence has been added yet
                    }

                    const int sampleWordsLeftToRead = DiskStreamRef.pStream->GetReadSpace();

                    // add silence sample at the end if we reached the end of the stream (for the interpolator)
                    if (DiskStreamRef.State == Stream::state_end) {
                        const int maxSampleWordsPerCycle = (pEngine->MaxSamplesPerCycle << CONFIG_MAX_PITCH) * pSample->Channels + 6; // +6 for the interpolator algorithm
                        if (sampleWordsLeftToRead <= maxSampleWordsPerCycle) {
                            // remember how many sample words there are before any silence has been added
                            if (RealSampleWordsLeftToRead < 0) RealSampleWordsLeftToRead = sampleWordsLeftToRead;
                            DiskStreamRef.pStream->WriteSilence(maxSampleWordsPerCycle - sampleWordsLeftToRead);
                        }
                    }

                    sample_t* ptr = (sample_t*)DiskStreamRef.pStream->GetReadPtr(); // get the current read_ptr within the ringbuffer where we read the samples from

                    // render current audio fragment
                    Synthesize(Samples, ptr, Delay);

                    const int iPos = (int) finalSynthesisParameters.dPos;
                    const int readSampleWords = iPos * pSample->Channels; // amount of sample words actually been read
                    DiskStreamRef.pStream->IncrementReadPos(readSampleWords);
                    finalSynthesisParameters.dPos -= iPos; // just keep fractional part of playback position

                    // change state of voice to 'end' if we really reached the end of the sample data
                    if (RealSampleWordsLeftToRead >= 0) {
                        RealSampleWordsLeftToRead -= readSampleWords;
                        if (RealSampleWordsLeftToRead <= 0) this->PlaybackState = playback_state_end;
                    }
                }
                break;

            case playback_state_end:
                std::cerr << "gig::Voice::Render(): entered with playback_state_end, this is a bug!\n" << std::flush;
                break;
        }

        // Reset delay
        Delay = 0;

        itTriggerEvent = Pool<Event>::Iterator();

        // If sample stream or release stage finished, kill the voice
        if (PlaybackState == playback_state_end || EG1.getSegmentType() == EGADSR::segment_end) KillImmediately();
    }

    /**
     *  Resets voice variables. Should only be called if rendering process is
     *  suspended / not running.
     */
    void Voice::Reset() {
        finalSynthesisParameters.filterLeft.Reset();
        finalSynthesisParameters.filterRight.Reset();
        DiskStreamRef.pStream = NULL;
        DiskStreamRef.hStream = 0;
        DiskStreamRef.State   = Stream::state_unused;
        DiskStreamRef.OrderID = 0;
        PlaybackState = playback_state_end;
        itTriggerEvent = Pool<Event>::Iterator();
        itKillEvent    = Pool<Event>::Iterator();
    }

    /**
     * Process given list of MIDI note on, note off and sustain pedal events
     * for the given time.
     *
     * @param itEvent - iterator pointing to the next event to be processed
     * @param End     - youngest time stamp where processing should be stopped
     */
    void Voice::processTransitionEvents(RTList<Event>::Iterator& itEvent, uint End) {
        for (; itEvent && itEvent->FragmentPos() <= End; ++itEvent) {
            if (itEvent->Type == Event::type_release) {
                EG1.update(EGADSR::event_release, pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                EG2.update(EGADSR::event_release, pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            } else if (itEvent->Type == Event::type_cancel_release) {
                EG1.update(EGADSR::event_cancel_release, pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                EG2.update(EGADSR::event_cancel_release, pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            }
        }
    }

    /**
     * Process given list of MIDI control change and pitch bend events for
     * the given time.
     *
     * @param itEvent - iterator pointing to the next event to be processed
     * @param End     - youngest time stamp where processing should be stopped
     */
    void Voice::processCCEvents(RTList<Event>::Iterator& itEvent, uint End) {
        for (; itEvent && itEvent->FragmentPos() <= End; ++itEvent) {
            if (itEvent->Type == Event::type_control_change &&
                itEvent->Param.CC.Controller) { // if (valid) MIDI control change event
                if (itEvent->Param.CC.Controller == VCFCutoffCtrl.controller) {
                    processCutoffEvent(itEvent);
                }
                if (itEvent->Param.CC.Controller == VCFResonanceCtrl.controller) {
                    processResonanceEvent(itEvent);
                }
                if (itEvent->Param.CC.Controller == pLFO1->ExtController) {
                    pLFO1->update(itEvent->Param.CC.Value);
                }
                if (itEvent->Param.CC.Controller == pLFO2->ExtController) {
                    pLFO2->update(itEvent->Param.CC.Value);
                }
                if (itEvent->Param.CC.Controller == pLFO3->ExtController) {
                    pLFO3->update(itEvent->Param.CC.Value);
                }
                if (pDimRgn->AttenuationController.type == ::gig::attenuation_ctrl_t::type_controlchange &&
                    itEvent->Param.CC.Controller == pDimRgn->AttenuationController.controller_number) {
                    CrossfadeSmoother.update(Engine::CrossfadeCurve[CrossfadeAttenuation(itEvent->Param.CC.Value)]);
                }
                if (itEvent->Param.CC.Controller == 7) { // volume
                    VolumeSmoother.update(Engine::VolumeCurve[itEvent->Param.CC.Value]);
                } else if (itEvent->Param.CC.Controller == 10) { // panpot
                    PanLeftSmoother.update(Engine::PanCurve[128 - itEvent->Param.CC.Value]);
                    PanRightSmoother.update(Engine::PanCurve[itEvent->Param.CC.Value]);
                }
            } else if (itEvent->Type == Event::type_pitchbend) { // if pitch bend event
                processPitchEvent(itEvent);
            }
        }
    }

    void Voice::processPitchEvent(RTList<Event>::Iterator& itEvent) {
        const float pitch = RTMath::CentsToFreqRatio(((double) itEvent->Param.Pitch.Pitch / 8192.0) * 200.0); // +-two semitones = +-200 cents
        finalSynthesisParameters.fFinalPitch *= pitch;
        PitchBend = pitch;
    }

    void Voice::processCutoffEvent(RTList<Event>::Iterator& itEvent) {
        int ccvalue = itEvent->Param.CC.Value;
        if (VCFCutoffCtrl.value == ccvalue) return;
        VCFCutoffCtrl.value == ccvalue;
        if (pDimRgn->VCFCutoffControllerInvert)  ccvalue = 127 - ccvalue;
        if (ccvalue < pDimRgn->VCFVelocityScale) ccvalue = pDimRgn->VCFVelocityScale;
        float cutoff = CutoffBase * float(ccvalue);
        if (cutoff > 127.0f) cutoff = 127.0f;

        VCFCutoffCtrl.fvalue = cutoff; // needed for initialization of fFinalCutoff next time
        fFinalCutoff = cutoff;
    }

    void Voice::processResonanceEvent(RTList<Event>::Iterator& itEvent) {
        // convert absolute controller value to differential
        const int ctrldelta = itEvent->Param.CC.Value - VCFResonanceCtrl.value;
        VCFResonanceCtrl.value = itEvent->Param.CC.Value;
        const float resonancedelta = (float) ctrldelta;
        fFinalResonance += resonancedelta;
        // needed for initialization of parameter
        VCFResonanceCtrl.fvalue = itEvent->Param.CC.Value;
    }

    /**
     *  Synthesizes the current audio fragment for this voice.
     *
     *  @param Samples - number of sample points to be rendered in this audio
     *                   fragment cycle
     *  @param pSrc    - pointer to input sample data
     *  @param Skip    - number of sample points to skip in output buffer
     */
    void Voice::Synthesize(uint Samples, sample_t* pSrc, uint Skip) {
        finalSynthesisParameters.pOutLeft  = &pEngineChannel->pChannelLeft->Buffer()[Skip];
        finalSynthesisParameters.pOutRight = &pEngineChannel->pChannelRight->Buffer()[Skip];
        finalSynthesisParameters.pSrc      = pSrc;

        RTList<Event>::Iterator itCCEvent = pEngineChannel->pEvents->first();
        RTList<Event>::Iterator itNoteEvent = pEngineChannel->pMIDIKeyInfo[MIDIKey].pEvents->first();

        if (itTriggerEvent) { // skip events that happened before this voice was triggered
            while (itCCEvent && itCCEvent->FragmentPos() <= Skip) ++itCCEvent;
            while (itNoteEvent && itNoteEvent->FragmentPos() <= Skip) ++itNoteEvent;
        }

        uint killPos;
        if (itKillEvent) {
            int maxFadeOutPos = Samples - pEngine->MinFadeOutSamples;
            if (maxFadeOutPos < 0) {
                // There's not enough space in buffer to do a fade out
                // from max volume (this can only happen for audio
                // drivers that use Samples < MaxSamplesPerCycle).
                // End the EG1 here, at pos 0, with a shorter max fade
                // out time.
                EG1.enterFadeOutStage(Samples / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                itKillEvent = Pool<Event>::Iterator();
            } else {
                killPos = RTMath::Min(itKillEvent->FragmentPos(), maxFadeOutPos);
            }
        }

        uint i = Skip;
        while (i < Samples) {
            int iSubFragmentEnd = RTMath::Min(i + CONFIG_DEFAULT_SUBFRAGMENT_SIZE, Samples);

            // initialize all final synthesis parameters
            finalSynthesisParameters.fFinalPitch = PitchBase * PitchBend;
            fFinalCutoff    = VCFCutoffCtrl.fvalue;
            fFinalResonance = VCFResonanceCtrl.fvalue;

            // process MIDI control change and pitchbend events for this subfragment
            processCCEvents(itCCEvent, iSubFragmentEnd);

            float fFinalVolume = VolumeSmoother.render() * CrossfadeSmoother.render();
#ifdef CONFIG_PROCESS_MUTED_CHANNELS
            if (pEngineChannel->GetMute()) fFinalVolume = 0;
#endif

            // process transition events (note on, note off & sustain pedal)
            processTransitionEvents(itNoteEvent, iSubFragmentEnd);

            // if the voice was killed in this subfragment, or if the
            // filter EG is finished, switch EG1 to fade out stage
            if ((itKillEvent && killPos <= iSubFragmentEnd) ||
                (SYNTHESIS_MODE_GET_FILTER(SynthesisMode) &&
                 EG2.getSegmentType() == EGADSR::segment_end)) {
                EG1.enterFadeOutStage();
                itKillEvent = Pool<Event>::Iterator();
            }

            // process envelope generators
            switch (EG1.getSegmentType()) {
                case EGADSR::segment_lin:
                    fFinalVolume *= EG1.processLin();
                    break;
                case EGADSR::segment_exp:
                    fFinalVolume *= EG1.processExp();
                    break;
                case EGADSR::segment_end:
                    fFinalVolume *= EG1.getLevel();
                    break; // noop
            }
            switch (EG2.getSegmentType()) {
                case EGADSR::segment_lin:
                    fFinalCutoff *= EG2.processLin();
                    break;
                case EGADSR::segment_exp:
                    fFinalCutoff *= EG2.processExp();
                    break;
                case EGADSR::segment_end:
                    fFinalCutoff *= EG2.getLevel();
                    break; // noop
            }
            if (EG3.active()) finalSynthesisParameters.fFinalPitch *= EG3.render();

            // process low frequency oscillators
            if (bLFO1Enabled) fFinalVolume *= (1.0f - pLFO1->render());
            if (bLFO2Enabled) fFinalCutoff *= pLFO2->render();
            if (bLFO3Enabled) finalSynthesisParameters.fFinalPitch *= RTMath::CentsToFreqRatio(pLFO3->render());

            // if filter enabled then update filter coefficients
            if (SYNTHESIS_MODE_GET_FILTER(SynthesisMode)) {
                finalSynthesisParameters.filterLeft.SetParameters(fFinalCutoff, fFinalResonance, pEngine->SampleRate);
                finalSynthesisParameters.filterRight.SetParameters(fFinalCutoff, fFinalResonance, pEngine->SampleRate);
            }

            // do we need resampling?
            const float __PLUS_ONE_CENT  = 1.000577789506554859250142541782224725466f;
            const float __MINUS_ONE_CENT = 0.9994225441413807496009516495583113737666f;
            const bool bResamplingRequired = !(finalSynthesisParameters.fFinalPitch <= __PLUS_ONE_CENT &&
                                               finalSynthesisParameters.fFinalPitch >= __MINUS_ONE_CENT);
            SYNTHESIS_MODE_SET_INTERPOLATE(SynthesisMode, bResamplingRequired);

            // prepare final synthesis parameters structure
            finalSynthesisParameters.uiToGo            = iSubFragmentEnd - i;
#ifdef CONFIG_INTERPOLATE_VOLUME
            finalSynthesisParameters.fFinalVolumeDeltaLeft  =
                (fFinalVolume * VolumeLeft  * PanLeftSmoother.render() -
                 finalSynthesisParameters.fFinalVolumeLeft) / finalSynthesisParameters.uiToGo;
            finalSynthesisParameters.fFinalVolumeDeltaRight =
                (fFinalVolume * VolumeRight * PanRightSmoother.render() -
                 finalSynthesisParameters.fFinalVolumeRight) / finalSynthesisParameters.uiToGo;
#else
            finalSynthesisParameters.fFinalVolumeLeft  =
                fFinalVolume * VolumeLeft  * PanLeftSmoother.render();
            finalSynthesisParameters.fFinalVolumeRight =
                fFinalVolume * VolumeRight * PanRightSmoother.render();
#endif
            // render audio for one subfragment
            RunSynthesisFunction(SynthesisMode, &finalSynthesisParameters, &loop);

            // stop the rendering if volume EG is finished
            if (EG1.getSegmentType() == EGADSR::segment_end) break;

            const double newPos = Pos + (iSubFragmentEnd - i) * finalSynthesisParameters.fFinalPitch;

            // increment envelopes' positions
            if (EG1.active()) {

                // if sample has a loop and loop start has been reached in this subfragment, send a special event to EG1 to let it finish the attack hold stage
                if (pDimRgn->SampleLoops && Pos <= pDimRgn->pSampleLoops[0].LoopStart && pDimRgn->pSampleLoops[0].LoopStart < newPos) {
                    EG1.update(EGADSR::event_hold_end, pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                }

                EG1.increment(1);
                if (!EG1.toStageEndLeft()) EG1.update(EGADSR::event_stage_end, pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            }
            if (EG2.active()) {
                EG2.increment(1);
                if (!EG2.toStageEndLeft()) EG2.update(EGADSR::event_stage_end, pEngine->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            }
            EG3.increment(1);
            if (!EG3.toEndLeft()) EG3.update(); // neutralize envelope coefficient if end reached

            Pos = newPos;
            i = iSubFragmentEnd;
        }
    }

    /** @brief Update current portamento position.
     *
     * Will be called when portamento mode is enabled to get the final
     * portamento position of this active voice from where the next voice(s)
     * might continue to slide on.
     *
     * @param itNoteOffEvent - event which causes this voice to die soon
     */
    void Voice::UpdatePortamentoPos(Pool<Event>::Iterator& itNoteOffEvent) {
        const float fFinalEG3Level = EG3.level(itNoteOffEvent->FragmentPos());
        pEngineChannel->PortamentoPos = (float) MIDIKey + RTMath::FreqRatioToCents(fFinalEG3Level) * 0.01f;
    }

    /**
     *  Immediately kill the voice. This method should not be used to kill
     *  a normal, active voice, because it doesn't take care of things like
     *  fading down the volume level to avoid clicks and regular processing
     *  until the kill event actually occured!
     *
     * If it's necessary to know when the voice's disk stream was actually
     * deleted, then one can set the optional @a bRequestNotification
     * parameter and this method will then return the handle of the disk
     * stream (unique identifier) and one can use this handle to poll the
     * disk thread if this stream has been deleted. In any case this method
     * will return immediately and will not block until the stream actually
     * was deleted.
     *
     * @param bRequestNotification - (optional) whether the disk thread shall
     *                                provide a notification once it deleted
     *                               the respective disk stream
     *                               (default=false)
     * @returns handle to the voice's disk stream or @c Stream::INVALID_HANDLE
     *          if the voice did not use a disk stream at all
     * @see Kill()
     */
    Stream::Handle Voice::KillImmediately(bool bRequestNotification) {
        Stream::Handle hStream = Stream::INVALID_HANDLE;
        if (DiskVoice && DiskStreamRef.State != Stream::state_unused) {
            pDiskThread->OrderDeletionOfStream(&DiskStreamRef, bRequestNotification);
            hStream = DiskStreamRef.hStream;
        }
        Reset();
        return hStream;
    }

    /**
     *  Kill the voice in regular sense. Let the voice render audio until
     *  the kill event actually occured and then fade down the volume level
     *  very quickly and let the voice die finally. Unlike a normal release
     *  of a voice, a kill process cannot be cancalled and is therefore
     *  usually used for voice stealing and key group conflicts.
     *
     *  @param itKillEvent - event which caused the voice to be killed
     */
    void Voice::Kill(Pool<Event>::Iterator& itKillEvent) {
        #if CONFIG_DEVMODE
        if (!itKillEvent) dmsg(1,("gig::Voice::Kill(): ERROR, !itKillEvent !!!\n"));
        if (itKillEvent && !itKillEvent.isValid()) dmsg(1,("gig::Voice::Kill(): ERROR, itKillEvent invalid !!!\n"));
        #endif // CONFIG_DEVMODE

        if (itTriggerEvent && itKillEvent->FragmentPos() <= itTriggerEvent->FragmentPos()) return;
        this->itKillEvent = itKillEvent;
    }

}} // namespace LinuxSampler::gig
