/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#include "EGADSR.h"
#include "Manipulator.h"
#include "../../common/Features.h"
#include "Synthesizer.h"

#include "Voice.h"

namespace LinuxSampler { namespace gig {

    const float Voice::FILTER_CUTOFF_COEFF(CalculateFilterCutoffCoeff());

    const int Voice::FILTER_UPDATE_MASK(CalculateFilterUpdateMask());

    float Voice::CalculateFilterCutoffCoeff() {
        return log(FILTER_CUTOFF_MIN / FILTER_CUTOFF_MAX);
    }

    int Voice::CalculateFilterUpdateMask() {
        if (FILTER_UPDATE_PERIOD <= 0) return 0;
        int power_of_two;
        for (power_of_two = 0; 1<<power_of_two < FILTER_UPDATE_PERIOD; power_of_two++);
        return (1 << power_of_two) - 1;
    }

    Voice::Voice() {
        pEngine     = NULL;
        pDiskThread = NULL;
        PlaybackState = playback_state_end;
        pEG1   = NULL;
        pEG2   = NULL;
        pEG3   = NULL;
        pVCAManipulator  = NULL;
        pVCFCManipulator = NULL;
        pVCOManipulator  = NULL;
        pLFO1  = NULL;
        pLFO2  = NULL;
        pLFO3  = NULL;
        KeyGroup = 0;
	SynthesisMode = 0; //Set all mode bits to 0 first

        // select synthesis implementation (currently either pure C++ or MMX+SSE(1))
        SYNTHESIS_MODE_SET_IMPLEMENTATION(SynthesisMode, Features::supportsMMX() && Features::supportsSSE());
        SYNTHESIS_MODE_SET_PROFILING(SynthesisMode, true);
    }

    Voice::~Voice() {
        if (pEG1)  delete pEG1;
        if (pEG2)  delete pEG2;
        if (pEG3)  delete pEG3;
        if (pLFO1) delete pLFO1;
        if (pLFO2) delete pLFO2;
        if (pLFO3) delete pLFO3;
        if (pVCAManipulator)  delete pVCAManipulator;
        if (pVCFCManipulator) delete pVCFCManipulator;
        if (pVCOManipulator)  delete pVCOManipulator;
    }

    void Voice::SetEngine(Engine* pEngine) {
        this->pEngine = pEngine;

        // delete old objects
        if (pEG1) delete pEG1;
        if (pEG2) delete pEG2;
        if (pEG3) delete pEG3;
        if (pVCAManipulator)  delete pVCAManipulator;
        if (pVCFCManipulator) delete pVCFCManipulator;
        if (pVCOManipulator)  delete pVCOManipulator;
        if (pLFO1) delete pLFO1;
        if (pLFO2) delete pLFO2;
        if (pLFO3) delete pLFO3;

        // create new ones
        pEG1   = new EGADSR(pEngine, Event::destination_vca);
        pEG2   = new EGADSR(pEngine, Event::destination_vcfc);
        pEG3   = new EGDecay(pEngine, Event::destination_vco);
        pVCAManipulator  = new VCAManipulator(pEngine);
        pVCFCManipulator = new VCFCManipulator(pEngine);
        pVCOManipulator  = new VCOManipulator(pEngine);
        pLFO1  = new LFO<gig::VCAManipulator>(0.0f, 1.0f, LFO<VCAManipulator>::propagation_top_down, pVCAManipulator, pEngine->pEventPool);
        pLFO2  = new LFO<gig::VCFCManipulator>(0.0f, 1.0f, LFO<VCFCManipulator>::propagation_top_down, pVCFCManipulator, pEngine->pEventPool);
        pLFO3  = new LFO<gig::VCOManipulator>(-1200.0f, 1200.0f, LFO<VCOManipulator>::propagation_middle_balanced, pVCOManipulator, pEngine->pEventPool); // +-1 octave (+-1200 cents) max.

        this->pDiskThread = pEngine->pDiskThread;
        dmsg(6,("Voice::SetEngine()\n"));
    }

    /**
     *  Initializes and triggers the voice, a disk stream will be launched if
     *  needed.
     *
     *  @param itNoteOnEvent       - event that caused triggering of this voice
     *  @param PitchBend           - MIDI detune factor (-8192 ... +8191)
     *  @param pInstrument         - points to the loaded instrument which provides sample wave(s) and articulation data
     *  @param iLayer              - layer number this voice refers to (only if this is a layered sound of course)
     *  @param ReleaseTriggerVoice - if this new voice is a release trigger voice (optional, default = false)
     *  @param VoiceStealing       - wether the voice is allowed to steal voices for further subvoices
     *  @returns 0 on success, a value < 0 if the voice wasn't triggered
     *           (either due to an error or e.g. because no region is
     *           defined for the given key)
     */
    int Voice::Trigger(Pool<Event>::Iterator& itNoteOnEvent, int PitchBend, ::gig::Instrument* pInstrument, int iLayer, bool ReleaseTriggerVoice, bool VoiceStealing) {
        if (!pInstrument) {
           dmsg(1,("voice::trigger: !pInstrument\n"));
           exit(EXIT_FAILURE);
        }
        if (itNoteOnEvent->FragmentPos() > pEngine->MaxSamplesPerCycle) { // FIXME: should be removed before the final release (purpose: just a sanity check for debugging)
            dmsg(1,("Voice::Trigger(): ERROR, TriggerDelay > Totalsamples\n"));
        }

        Type            = type_normal;
        MIDIKey         = itNoteOnEvent->Param.Note.Key;
        pRegion         = pInstrument->GetRegion(MIDIKey);
        PlaybackState   = playback_state_ram; // we always start playback from RAM cache and switch then to disk if needed
        Delay           = itNoteOnEvent->FragmentPos();
        itTriggerEvent  = itNoteOnEvent;
        itKillEvent     = Pool<Event>::Iterator();
        itChildVoice    = Pool<Voice>::Iterator();

        if (!pRegion) {
            dmsg(4, ("gig::Voice: No Region defined for MIDI key %d\n", MIDIKey));
            return -1;
        }

        KeyGroup = pRegion->KeyGroup;

        // get current dimension values to select the right dimension region
        //FIXME: controller values for selecting the dimension region here are currently not sample accurate
        uint DimValues[8] = { 0 };
        for (int i = pRegion->Dimensions - 1; i >= 0; i--) {
            switch (pRegion->pDimensionDefinitions[i].dimension) {
                case ::gig::dimension_samplechannel:
                    DimValues[i] = 0; //TODO: we currently ignore this dimension
                    break;
                case ::gig::dimension_layer:
                    DimValues[i] = iLayer;
                    // if this is the 1st layer then spawn further voices for all the other layers
                    if (iLayer == 0)
                        for (int iNewLayer = 1; iNewLayer < pRegion->pDimensionDefinitions[i].zones; iNewLayer++)
                            itChildVoice = pEngine->LaunchVoice(itNoteOnEvent, iNewLayer, ReleaseTriggerVoice, VoiceStealing);
                    break;
                case ::gig::dimension_velocity:
                    DimValues[i] = itNoteOnEvent->Param.Note.Velocity;
                    break;
                case ::gig::dimension_channelaftertouch:
                    DimValues[i] = 0; //TODO: we currently ignore this dimension
                    break;
                case ::gig::dimension_releasetrigger:
                    Type = (ReleaseTriggerVoice) ? type_release_trigger : (!iLayer) ? type_release_trigger_required : type_normal;
                    DimValues[i] = (uint) ReleaseTriggerVoice;
                    break;
                case ::gig::dimension_keyboard:
                    DimValues[i] = (uint) pEngine->CurrentKeyDimension;
                    break;
                case ::gig::dimension_modwheel:
                    DimValues[i] = pEngine->ControllerTable[1];
                    break;
                case ::gig::dimension_breath:
                    DimValues[i] = pEngine->ControllerTable[2];
                    break;
                case ::gig::dimension_foot:
                    DimValues[i] = pEngine->ControllerTable[4];
                    break;
                case ::gig::dimension_portamentotime:
                    DimValues[i] = pEngine->ControllerTable[5];
                    break;
                case ::gig::dimension_effect1:
                    DimValues[i] = pEngine->ControllerTable[12];
                    break;
                case ::gig::dimension_effect2:
                    DimValues[i] = pEngine->ControllerTable[13];
                    break;
                case ::gig::dimension_genpurpose1:
                    DimValues[i] = pEngine->ControllerTable[16];
                    break;
                case ::gig::dimension_genpurpose2:
                    DimValues[i] = pEngine->ControllerTable[17];
                    break;
                case ::gig::dimension_genpurpose3:
                    DimValues[i] = pEngine->ControllerTable[18];
                    break;
                case ::gig::dimension_genpurpose4:
                    DimValues[i] = pEngine->ControllerTable[19];
                    break;
                case ::gig::dimension_sustainpedal:
                    DimValues[i] = pEngine->ControllerTable[64];
                    break;
                case ::gig::dimension_portamento:
                    DimValues[i] = pEngine->ControllerTable[65];
                    break;
                case ::gig::dimension_sostenutopedal:
                    DimValues[i] = pEngine->ControllerTable[66];
                    break;
                case ::gig::dimension_softpedal:
                    DimValues[i] = pEngine->ControllerTable[67];
                    break;
                case ::gig::dimension_genpurpose5:
                    DimValues[i] = pEngine->ControllerTable[80];
                    break;
                case ::gig::dimension_genpurpose6:
                    DimValues[i] = pEngine->ControllerTable[81];
                    break;
                case ::gig::dimension_genpurpose7:
                    DimValues[i] = pEngine->ControllerTable[82];
                    break;
                case ::gig::dimension_genpurpose8:
                    DimValues[i] = pEngine->ControllerTable[83];
                    break;
                case ::gig::dimension_effect1depth:
                    DimValues[i] = pEngine->ControllerTable[91];
                    break;
                case ::gig::dimension_effect2depth:
                    DimValues[i] = pEngine->ControllerTable[92];
                    break;
                case ::gig::dimension_effect3depth:
                    DimValues[i] = pEngine->ControllerTable[93];
                    break;
                case ::gig::dimension_effect4depth:
                    DimValues[i] = pEngine->ControllerTable[94];
                    break;
                case ::gig::dimension_effect5depth:
                    DimValues[i] = pEngine->ControllerTable[95];
                    break;
                case ::gig::dimension_none:
                    std::cerr << "gig::Voice::Trigger() Error: dimension=none\n" << std::flush;
                    break;
                default:
                    std::cerr << "gig::Voice::Trigger() Error: Unknown dimension\n" << std::flush;
            }
        }
        pDimRgn = pRegion->GetDimensionRegionByValue(DimValues);

        pSample = pDimRgn->pSample; // sample won't change until the voice is finished
        if (!pSample || !pSample->SamplesTotal) return -1; // no need to continue if sample is silent

        // select channel mode (mono or stereo)
        SYNTHESIS_MODE_SET_CHANNELS(SynthesisMode, pSample->Channels == 2);

        // get starting crossfade volume level
        switch (pDimRgn->AttenuationController.type) {
            case ::gig::attenuation_ctrl_t::type_channelaftertouch:
                CrossfadeVolume = 1.0f; //TODO: aftertouch not supported yet
                break;
            case ::gig::attenuation_ctrl_t::type_velocity:
                CrossfadeVolume = CrossfadeAttenuation(itNoteOnEvent->Param.Note.Velocity);
                break;
            case ::gig::attenuation_ctrl_t::type_controlchange: //FIXME: currently not sample accurate
                CrossfadeVolume = CrossfadeAttenuation(pEngine->ControllerTable[pDimRgn->AttenuationController.controller_number]);
                break;
            case ::gig::attenuation_ctrl_t::type_none: // no crossfade defined
            default:
                CrossfadeVolume = 1.0f;
        }

        PanLeft  = 1.0f - float(RTMath::Max(pDimRgn->Pan, 0)) /  63.0f;
        PanRight = 1.0f - float(RTMath::Min(pDimRgn->Pan, 0)) / -64.0f;

        Pos = pDimRgn->SampleStartOffset; // offset where we should start playback of sample (0 - 2000 sample points)

        // Check if the sample needs disk streaming or is too short for that
        long cachedsamples = pSample->GetCache().Size / pSample->FrameSize;
        DiskVoice          = cachedsamples < pSample->SamplesTotal;

        if (DiskVoice) { // voice to be streamed from disk
            MaxRAMPos = cachedsamples - (pEngine->MaxSamplesPerCycle << MAX_PITCH) / pSample->Channels; //TODO: this calculation is too pessimistic and may better be moved to Render() method, so it calculates MaxRAMPos dependent to the current demand of sample points to be rendered (e.g. in case of JACK)

            // check if there's a loop defined which completely fits into the cached (RAM) part of the sample
            if (pSample->Loops && pSample->LoopEnd <= MaxRAMPos) {
                RAMLoop        = true;
                LoopCyclesLeft = pSample->LoopPlayCount;
            }
            else RAMLoop = false;

            if (pDiskThread->OrderNewStream(&DiskStreamRef, pSample, MaxRAMPos, !RAMLoop) < 0) {
                dmsg(1,("Disk stream order failed!\n"));
                KillImmediately();
                return -1;
            }
            dmsg(4,("Disk voice launched (cached samples: %d, total Samples: %d, MaxRAMPos: %d, RAMLooping: %s)\n", cachedsamples, pSample->SamplesTotal, MaxRAMPos, (RAMLoop) ? "yes" : "no"));
        }
        else { // RAM only voice
            MaxRAMPos = cachedsamples;
            if (pSample->Loops) {
                RAMLoop        = true;
                LoopCyclesLeft = pSample->LoopPlayCount;
            }
            else RAMLoop = false;
            dmsg(4,("RAM only voice launched (Looping: %s)\n", (RAMLoop) ? "yes" : "no"));
        }


        // calculate initial pitch value
        {
            double pitchbasecents = pDimRgn->FineTune + (int) pEngine->ScaleTuning[MIDIKey % 12];
            if (pDimRgn->PitchTrack) pitchbasecents += (MIDIKey - (int) pDimRgn->UnityNote) * 100;
            this->PitchBase = RTMath::CentsToFreqRatio(pitchbasecents) * (double(pSample->SamplesPerSecond) / double(pEngine->pAudioOutputDevice->SampleRate()));
            this->PitchBend = RTMath::CentsToFreqRatio(((double) PitchBend / 8192.0) * 200.0); // pitchbend wheel +-2 semitones = 200 cents
        }

        Volume = pDimRgn->GetVelocityAttenuation(itNoteOnEvent->Param.Note.Velocity) / 32768.0f; // we downscale by 32768 to convert from int16 value range to DSP value range (which is -1.0..1.0)

        // setup EG 1 (VCA EG)
        {
            // get current value of EG1 controller
            double eg1controllervalue;
            switch (pDimRgn->EG1Controller.type) {
                case ::gig::eg1_ctrl_t::type_none: // no controller defined
                    eg1controllervalue = 0;
                    break;
                case ::gig::eg1_ctrl_t::type_channelaftertouch:
                    eg1controllervalue = 0; // TODO: aftertouch not yet supported
                    break;
                case ::gig::eg1_ctrl_t::type_velocity:
                    eg1controllervalue = itNoteOnEvent->Param.Note.Velocity;
                    break;
                case ::gig::eg1_ctrl_t::type_controlchange: // MIDI control change controller
                    eg1controllervalue = pEngine->ControllerTable[pDimRgn->EG1Controller.controller_number];
                    break;
            }
            if (pDimRgn->EG1ControllerInvert) eg1controllervalue = 127 - eg1controllervalue;

            // calculate influence of EG1 controller on EG1's parameters (TODO: needs to be fine tuned)
            double eg1attack  = (pDimRgn->EG1ControllerAttackInfluence)  ? 0.0001 * (double) (1 << pDimRgn->EG1ControllerAttackInfluence)  * eg1controllervalue : 0.0;
            double eg1decay   = (pDimRgn->EG1ControllerDecayInfluence)   ? 0.0001 * (double) (1 << pDimRgn->EG1ControllerDecayInfluence)   * eg1controllervalue : 0.0;
            double eg1release = (pDimRgn->EG1ControllerReleaseInfluence) ? 0.0001 * (double) (1 << pDimRgn->EG1ControllerReleaseInfluence) * eg1controllervalue : 0.0;

            pEG1->Trigger(pDimRgn->EG1PreAttack,
                          pDimRgn->EG1Attack + eg1attack,
                          pDimRgn->EG1Hold,
                          pSample->LoopStart,
                          pDimRgn->EG1Decay1 + eg1decay,
                          pDimRgn->EG1Decay2 + eg1decay,
                          pDimRgn->EG1InfiniteSustain,
                          pDimRgn->EG1Sustain,
                          pDimRgn->EG1Release + eg1release,
                          Delay);
        }


        // setup EG 2 (VCF Cutoff EG)
        {
            // get current value of EG2 controller
            double eg2controllervalue;
            switch (pDimRgn->EG2Controller.type) {
                case ::gig::eg2_ctrl_t::type_none: // no controller defined
                    eg2controllervalue = 0;
                    break;
                case ::gig::eg2_ctrl_t::type_channelaftertouch:
                    eg2controllervalue = 0; // TODO: aftertouch not yet supported
                    break;
                case ::gig::eg2_ctrl_t::type_velocity:
                    eg2controllervalue = itNoteOnEvent->Param.Note.Velocity;
                    break;
                case ::gig::eg2_ctrl_t::type_controlchange: // MIDI control change controller
                    eg2controllervalue = pEngine->ControllerTable[pDimRgn->EG2Controller.controller_number];
                    break;
            }
            if (pDimRgn->EG2ControllerInvert) eg2controllervalue = 127 - eg2controllervalue;

            // calculate influence of EG2 controller on EG2's parameters (TODO: needs to be fine tuned)
            double eg2attack  = (pDimRgn->EG2ControllerAttackInfluence)  ? 0.0001 * (double) (1 << pDimRgn->EG2ControllerAttackInfluence)  * eg2controllervalue : 0.0;
            double eg2decay   = (pDimRgn->EG2ControllerDecayInfluence)   ? 0.0001 * (double) (1 << pDimRgn->EG2ControllerDecayInfluence)   * eg2controllervalue : 0.0;
            double eg2release = (pDimRgn->EG2ControllerReleaseInfluence) ? 0.0001 * (double) (1 << pDimRgn->EG2ControllerReleaseInfluence) * eg2controllervalue : 0.0;

            pEG2->Trigger(pDimRgn->EG2PreAttack,
                          pDimRgn->EG2Attack + eg2attack,
                          false,
                          pSample->LoopStart,
                          pDimRgn->EG2Decay1 + eg2decay,
                          pDimRgn->EG2Decay2 + eg2decay,
                          pDimRgn->EG2InfiniteSustain,
                          pDimRgn->EG2Sustain,
                          pDimRgn->EG2Release + eg2release,
                          Delay);
        }


        // setup EG 3 (VCO EG)
        {
          double eg3depth = RTMath::CentsToFreqRatio(pDimRgn->EG3Depth);
          pEG3->Trigger(eg3depth, pDimRgn->EG3Attack, Delay);
        }


        // setup LFO 1 (VCA LFO)
        {
            uint16_t lfo1_internal_depth;
            switch (pDimRgn->LFO1Controller) {
                case ::gig::lfo1_ctrl_internal:
                    lfo1_internal_depth  = pDimRgn->LFO1InternalDepth;
                    pLFO1->ExtController = 0; // no external controller
                    break;
                case ::gig::lfo1_ctrl_modwheel:
                    lfo1_internal_depth  = 0;
                    pLFO1->ExtController = 1; // MIDI controller 1
                    break;
                case ::gig::lfo1_ctrl_breath:
                    lfo1_internal_depth  = 0;
                    pLFO1->ExtController = 2; // MIDI controller 2
                    break;
                case ::gig::lfo1_ctrl_internal_modwheel:
                    lfo1_internal_depth  = pDimRgn->LFO1InternalDepth;
                    pLFO1->ExtController = 1; // MIDI controller 1
                    break;
                case ::gig::lfo1_ctrl_internal_breath:
                    lfo1_internal_depth  = pDimRgn->LFO1InternalDepth;
                    pLFO1->ExtController = 2; // MIDI controller 2
                    break;
                default:
                    lfo1_internal_depth  = 0;
                    pLFO1->ExtController = 0; // no external controller
            }
            pLFO1->Trigger(pDimRgn->LFO1Frequency,
                          lfo1_internal_depth,
                          pDimRgn->LFO1ControlDepth,
                          pEngine->ControllerTable[pLFO1->ExtController],
                          pDimRgn->LFO1FlipPhase,
                          pEngine->SampleRate,
                          Delay);
        }


        // setup LFO 2 (VCF Cutoff LFO)
        {
            uint16_t lfo2_internal_depth;
            switch (pDimRgn->LFO2Controller) {
                case ::gig::lfo2_ctrl_internal:
                    lfo2_internal_depth  = pDimRgn->LFO2InternalDepth;
                    pLFO2->ExtController = 0; // no external controller
                    break;
                case ::gig::lfo2_ctrl_modwheel:
                    lfo2_internal_depth  = 0;
                    pLFO2->ExtController = 1; // MIDI controller 1
                    break;
                case ::gig::lfo2_ctrl_foot:
                    lfo2_internal_depth  = 0;
                    pLFO2->ExtController = 4; // MIDI controller 4
                    break;
                case ::gig::lfo2_ctrl_internal_modwheel:
                    lfo2_internal_depth  = pDimRgn->LFO2InternalDepth;
                    pLFO2->ExtController = 1; // MIDI controller 1
                    break;
                case ::gig::lfo2_ctrl_internal_foot:
                    lfo2_internal_depth  = pDimRgn->LFO2InternalDepth;
                    pLFO2->ExtController = 4; // MIDI controller 4
                    break;
                default:
                    lfo2_internal_depth  = 0;
                    pLFO2->ExtController = 0; // no external controller
            }
            pLFO2->Trigger(pDimRgn->LFO2Frequency,
                          lfo2_internal_depth,
                          pDimRgn->LFO2ControlDepth,
                          pEngine->ControllerTable[pLFO2->ExtController],
                          pDimRgn->LFO2FlipPhase,
                          pEngine->SampleRate,
                          Delay);
        }


        // setup LFO 3 (VCO LFO)
        {
            uint16_t lfo3_internal_depth;
            switch (pDimRgn->LFO3Controller) {
                case ::gig::lfo3_ctrl_internal:
                    lfo3_internal_depth  = pDimRgn->LFO3InternalDepth;
                    pLFO3->ExtController = 0; // no external controller
                    break;
                case ::gig::lfo3_ctrl_modwheel:
                    lfo3_internal_depth  = 0;
                    pLFO3->ExtController = 1; // MIDI controller 1
                    break;
                case ::gig::lfo3_ctrl_aftertouch:
                    lfo3_internal_depth  = 0;
                    pLFO3->ExtController = 0; // TODO: aftertouch not implemented yet
                    break;
                case ::gig::lfo3_ctrl_internal_modwheel:
                    lfo3_internal_depth  = pDimRgn->LFO3InternalDepth;
                    pLFO3->ExtController = 1; // MIDI controller 1
                    break;
                case ::gig::lfo3_ctrl_internal_aftertouch:
                    lfo3_internal_depth  = pDimRgn->LFO3InternalDepth;
                    pLFO1->ExtController = 0; // TODO: aftertouch not implemented yet
                    break;
                default:
                    lfo3_internal_depth  = 0;
                    pLFO3->ExtController = 0; // no external controller
            }
            pLFO3->Trigger(pDimRgn->LFO3Frequency,
                          lfo3_internal_depth,
                          pDimRgn->LFO3ControlDepth,
                          pEngine->ControllerTable[pLFO3->ExtController],
                          false,
                          pEngine->SampleRate,
                          Delay);
        }


        #if FORCE_FILTER_USAGE
        SYNTHESIS_MODE_SET_FILTER(SynthesisMode, true);
        #else // use filter only if instrument file told so
        SYNTHESIS_MODE_SET_FILTER(SynthesisMode, pDimRgn->VCFEnabled);
        #endif // FORCE_FILTER_USAGE
        if (pDimRgn->VCFEnabled) {
            #ifdef OVERRIDE_FILTER_CUTOFF_CTRL
            VCFCutoffCtrl.controller = OVERRIDE_FILTER_CUTOFF_CTRL;
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
                case ::gig::vcf_cutoff_ctrl_aftertouch: //TODO: not implemented yet
                case ::gig::vcf_cutoff_ctrl_none:
                default:
                    VCFCutoffCtrl.controller = 0;
                    break;
            }
            #endif // OVERRIDE_FILTER_CUTOFF_CTRL

            #ifdef OVERRIDE_FILTER_RES_CTRL
            VCFResonanceCtrl.controller = OVERRIDE_FILTER_RES_CTRL;
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
            #endif // OVERRIDE_FILTER_RES_CTRL

            #ifndef OVERRIDE_FILTER_TYPE
            FilterLeft.SetType(pDimRgn->VCFType);
            FilterRight.SetType(pDimRgn->VCFType);
            #else // override filter type
            FilterLeft.SetType(OVERRIDE_FILTER_TYPE);
            FilterRight.SetType(OVERRIDE_FILTER_TYPE);
            #endif // OVERRIDE_FILTER_TYPE

            VCFCutoffCtrl.value    = pEngine->ControllerTable[VCFCutoffCtrl.controller];
            VCFResonanceCtrl.value = pEngine->ControllerTable[VCFResonanceCtrl.controller];

            // calculate cutoff frequency
            float cutoff = (!VCFCutoffCtrl.controller)
                ? exp((float) (127 - itNoteOnEvent->Param.Note.Velocity) * (float) pDimRgn->VCFVelocityScale * 6.2E-5f * FILTER_CUTOFF_COEFF) * FILTER_CUTOFF_MAX
                : exp((float) VCFCutoffCtrl.value * 0.00787402f * FILTER_CUTOFF_COEFF) * FILTER_CUTOFF_MAX;

            // calculate resonance
            float resonance = (float) VCFResonanceCtrl.value * 0.00787f;   // 0.0..1.0
            if (pDimRgn->VCFKeyboardTracking) {
                resonance += (float) (itNoteOnEvent->Param.Note.Key - pDimRgn->VCFKeyboardTrackingBreakpoint) * 0.00787f;
            }
            Constrain(resonance, 0.0, 1.0); // correct resonance if outside allowed value range (0.0..1.0)

            VCFCutoffCtrl.fvalue    = cutoff - FILTER_CUTOFF_MIN;
            VCFResonanceCtrl.fvalue = resonance;

            FilterUpdateCounter = -1;
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
        SYNTHESIS_MODE_SET_INTERPOLATE(SynthesisMode, (PitchBase * PitchBend) != 1.0f);
        SYNTHESIS_MODE_SET_CONSTPITCH(SynthesisMode, true);
        SYNTHESIS_MODE_SET_LOOP(SynthesisMode, false);

        // Reset the synthesis parameter matrix

        pEngine->ResetSynthesisParameters(Event::destination_vca, this->Volume * this->CrossfadeVolume * pEngine->GlobalVolume);
        pEngine->ResetSynthesisParameters(Event::destination_vco, this->PitchBase);
        pEngine->ResetSynthesisParameters(Event::destination_vcfc, VCFCutoffCtrl.fvalue);
        pEngine->ResetSynthesisParameters(Event::destination_vcfr, VCFResonanceCtrl.fvalue);

        // Apply events to the synthesis parameter matrix
        ProcessEvents(Samples);

        // Let all modulators write their parameter changes to the synthesis parameter matrix for the current audio fragment
        pEG1->Process(Samples, pEngine->pMIDIKeyInfo[MIDIKey].pEvents, itTriggerEvent, this->Pos, this->PitchBase * this->PitchBend, itKillEvent);
        pEG2->Process(Samples, pEngine->pMIDIKeyInfo[MIDIKey].pEvents, itTriggerEvent, this->Pos, this->PitchBase * this->PitchBend);
        if (pEG3->Process(Samples)) { // if pitch EG is active
            SYNTHESIS_MODE_SET_INTERPOLATE(SynthesisMode, true);
            SYNTHESIS_MODE_SET_CONSTPITCH(SynthesisMode, false);
        }
        pLFO1->Process(Samples);
        pLFO2->Process(Samples);
        if (pLFO3->Process(Samples)) { // if pitch LFO modulation is active
            SYNTHESIS_MODE_SET_INTERPOLATE(SynthesisMode, true);
            SYNTHESIS_MODE_SET_CONSTPITCH(SynthesisMode, false);
        }

        if (SYNTHESIS_MODE_GET_FILTER(SynthesisMode))
        	CalculateBiquadParameters(Samples); // calculate the final biquad filter parameters

        switch (this->PlaybackState) {

            case playback_state_ram: {
                    if (RAMLoop) SYNTHESIS_MODE_SET_LOOP(SynthesisMode, true); // enable looping

                    // render current fragment
                    Synthesize(Samples, (sample_t*) pSample->GetCache().pStart, Delay);

                    if (DiskVoice) {
                        // check if we reached the allowed limit of the sample RAM cache
                        if (Pos > MaxRAMPos) {
                            dmsg(5,("Voice: switching to disk playback (Pos=%f)\n", Pos));
                            this->PlaybackState = playback_state_disk;
                        }
                    }
                    else if (Pos >= pSample->GetCache().Size / pSample->FrameSize) {
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
                        DiskStreamRef.pStream->IncrementReadPos(pSample->Channels * (int(Pos) - MaxRAMPos));
                        Pos -= int(Pos);
                        RealSampleWordsLeftToRead = -1; // -1 means no silence has been added yet
                    }

                    const int sampleWordsLeftToRead = DiskStreamRef.pStream->GetReadSpace();

                    // add silence sample at the end if we reached the end of the stream (for the interpolator)
                    if (DiskStreamRef.State == Stream::state_end) {
                        const int maxSampleWordsPerCycle = (pEngine->MaxSamplesPerCycle << MAX_PITCH) * pSample->Channels + 6; // +6 for the interpolator algorithm
                        if (sampleWordsLeftToRead <= maxSampleWordsPerCycle) {
                            // remember how many sample words there are before any silence has been added
                            if (RealSampleWordsLeftToRead < 0) RealSampleWordsLeftToRead = sampleWordsLeftToRead;
                            DiskStreamRef.pStream->WriteSilence(maxSampleWordsPerCycle - sampleWordsLeftToRead);
                        }
                    }

                    sample_t* ptr = DiskStreamRef.pStream->GetReadPtr(); // get the current read_ptr within the ringbuffer where we read the samples from

                    // render current audio fragment
                    Synthesize(Samples, ptr, Delay);

                    const int iPos = (int) Pos;
                    const int readSampleWords = iPos * pSample->Channels; // amount of sample words actually been read
                    DiskStreamRef.pStream->IncrementReadPos(readSampleWords);
                    Pos -= iPos; // just keep fractional part of Pos

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

        // Reset synthesis event lists (except VCO, as VCO events apply channel wide currently)
        pEngine->pSynthesisEvents[Event::destination_vca]->clear();
        pEngine->pSynthesisEvents[Event::destination_vcfc]->clear();
        pEngine->pSynthesisEvents[Event::destination_vcfr]->clear();

        // Reset delay
        Delay = 0;

        itTriggerEvent = Pool<Event>::Iterator();

        // If sample stream or release stage finished, kill the voice
        if (PlaybackState == playback_state_end || pEG1->GetStage() == EGADSR::stage_end) KillImmediately();
    }

    /**
     *  Resets voice variables. Should only be called if rendering process is
     *  suspended / not running.
     */
    void Voice::Reset() {
        pLFO1->Reset();
        pLFO2->Reset();
        pLFO3->Reset();
        FilterLeft.Reset();
        FilterRight.Reset();
        DiskStreamRef.pStream = NULL;
        DiskStreamRef.hStream = 0;
        DiskStreamRef.State   = Stream::state_unused;
        DiskStreamRef.OrderID = 0;
        PlaybackState = playback_state_end;
        itTriggerEvent = Pool<Event>::Iterator();
        itKillEvent    = Pool<Event>::Iterator();
    }

    /**
     *  Process the control change event lists of the engine for the current
     *  audio fragment. Event values will be applied to the synthesis parameter
     *  matrix.
     *
     *  @param Samples - number of samples to be rendered in this audio fragment cycle
     */
    void Voice::ProcessEvents(uint Samples) {

        // dispatch control change events
        RTList<Event>::Iterator itCCEvent = pEngine->pCCEvents->first();
        if (Delay) { // skip events that happened before this voice was triggered
            while (itCCEvent && itCCEvent->FragmentPos() <= Delay) ++itCCEvent;
        }
        while (itCCEvent) {
            if (itCCEvent->Param.CC.Controller) { // if valid MIDI controller
                if (itCCEvent->Param.CC.Controller == VCFCutoffCtrl.controller) {
                    *pEngine->pSynthesisEvents[Event::destination_vcfc]->allocAppend() = *itCCEvent;
                }
                if (itCCEvent->Param.CC.Controller == VCFResonanceCtrl.controller) {
                    *pEngine->pSynthesisEvents[Event::destination_vcfr]->allocAppend() = *itCCEvent;
                }
                if (itCCEvent->Param.CC.Controller == pLFO1->ExtController) {
                    pLFO1->SendEvent(itCCEvent);
                }
                if (itCCEvent->Param.CC.Controller == pLFO2->ExtController) {
                    pLFO2->SendEvent(itCCEvent);
                }
                if (itCCEvent->Param.CC.Controller == pLFO3->ExtController) {
                    pLFO3->SendEvent(itCCEvent);
                }
                if (pDimRgn->AttenuationController.type == ::gig::attenuation_ctrl_t::type_controlchange &&
                    itCCEvent->Param.CC.Controller == pDimRgn->AttenuationController.controller_number) { // if crossfade event
                    *pEngine->pSynthesisEvents[Event::destination_vca]->allocAppend() = *itCCEvent;
                }
            }

            ++itCCEvent;
        }


        // process pitch events
        {
            RTList<Event>* pVCOEventList = pEngine->pSynthesisEvents[Event::destination_vco];
            RTList<Event>::Iterator itVCOEvent = pVCOEventList->first();
            if (Delay) { // skip events that happened before this voice was triggered
                while (itVCOEvent && itVCOEvent->FragmentPos() <= Delay) ++itVCOEvent;
            }
            // apply old pitchbend value until first pitch event occurs
            if (this->PitchBend != 1.0) {
                uint end = (itVCOEvent) ? itVCOEvent->FragmentPos() : Samples;
                for (uint i = Delay; i < end; i++) {
                    pEngine->pSynthesisParameters[Event::destination_vco][i] *= this->PitchBend;
                }
            }
            float pitch;
            while (itVCOEvent) {
                RTList<Event>::Iterator itNextVCOEvent = itVCOEvent;
                ++itNextVCOEvent;

                // calculate the influence length of this event (in sample points)
                uint end = (itNextVCOEvent) ? itNextVCOEvent->FragmentPos() : Samples;

                pitch = RTMath::CentsToFreqRatio(((double) itVCOEvent->Param.Pitch.Pitch / 8192.0) * 200.0); // +-two semitones = +-200 cents

                // apply pitch value to the pitch parameter sequence
                for (uint i = itVCOEvent->FragmentPos(); i < end; i++) {
                    pEngine->pSynthesisParameters[Event::destination_vco][i] *= pitch;
                }

                itVCOEvent = itNextVCOEvent;
            }
            if (!pVCOEventList->isEmpty()) {
                this->PitchBend = pitch;
                SYNTHESIS_MODE_SET_INTERPOLATE(SynthesisMode, true);
                SYNTHESIS_MODE_SET_CONSTPITCH(SynthesisMode, false);
            }
        }

        // process volume / attenuation events (TODO: we only handle and _expect_ crossfade events here ATM !)
        {
            RTList<Event>* pVCAEventList = pEngine->pSynthesisEvents[Event::destination_vca];
            RTList<Event>::Iterator itVCAEvent = pVCAEventList->first();
            if (Delay) { // skip events that happened before this voice was triggered
                while (itVCAEvent && itVCAEvent->FragmentPos() <= Delay) ++itVCAEvent;
            }
            float crossfadevolume;
            while (itVCAEvent) {
                RTList<Event>::Iterator itNextVCAEvent = itVCAEvent;
                ++itNextVCAEvent;

                // calculate the influence length of this event (in sample points)
                uint end = (itNextVCAEvent) ? itNextVCAEvent->FragmentPos() : Samples;

                crossfadevolume = CrossfadeAttenuation(itVCAEvent->Param.CC.Value);

                float effective_volume = crossfadevolume * this->Volume * pEngine->GlobalVolume;

                // apply volume value to the volume parameter sequence
                for (uint i = itVCAEvent->FragmentPos(); i < end; i++) {
                    pEngine->pSynthesisParameters[Event::destination_vca][i] = effective_volume;
                }

                itVCAEvent = itNextVCAEvent;
            }
            if (!pVCAEventList->isEmpty()) this->CrossfadeVolume = crossfadevolume;
        }

        // process filter cutoff events
        {
            RTList<Event>* pCutoffEventList = pEngine->pSynthesisEvents[Event::destination_vcfc];
            RTList<Event>::Iterator itCutoffEvent = pCutoffEventList->first();
            if (Delay) { // skip events that happened before this voice was triggered
                while (itCutoffEvent && itCutoffEvent->FragmentPos() <= Delay) ++itCutoffEvent;
            }
            float cutoff;
            while (itCutoffEvent) {
                RTList<Event>::Iterator itNextCutoffEvent = itCutoffEvent;
                ++itNextCutoffEvent;

                // calculate the influence length of this event (in sample points)
                uint end = (itNextCutoffEvent) ? itNextCutoffEvent->FragmentPos() : Samples;

                cutoff = exp((float) itCutoffEvent->Param.CC.Value * 0.00787402f * FILTER_CUTOFF_COEFF) * FILTER_CUTOFF_MAX - FILTER_CUTOFF_MIN;

                // apply cutoff frequency to the cutoff parameter sequence
                for (uint i = itCutoffEvent->FragmentPos(); i < end; i++) {
                    pEngine->pSynthesisParameters[Event::destination_vcfc][i] = cutoff;
                }

                itCutoffEvent = itNextCutoffEvent;
            }
            if (!pCutoffEventList->isEmpty()) VCFCutoffCtrl.fvalue = cutoff; // needed for initialization of parameter matrix next time
        }

        // process filter resonance events
        {
            RTList<Event>* pResonanceEventList = pEngine->pSynthesisEvents[Event::destination_vcfr];
            RTList<Event>::Iterator itResonanceEvent = pResonanceEventList->first();
            if (Delay) { // skip events that happened before this voice was triggered
                while (itResonanceEvent && itResonanceEvent->FragmentPos() <= Delay) ++itResonanceEvent;
            }
            while (itResonanceEvent) {
                RTList<Event>::Iterator itNextResonanceEvent = itResonanceEvent;
                ++itNextResonanceEvent;

                // calculate the influence length of this event (in sample points)
                uint end = (itNextResonanceEvent) ? itNextResonanceEvent->FragmentPos() : Samples;

                // convert absolute controller value to differential
                int ctrldelta = itResonanceEvent->Param.CC.Value - VCFResonanceCtrl.value;
                VCFResonanceCtrl.value = itResonanceEvent->Param.CC.Value;

                float resonancedelta = (float) ctrldelta * 0.00787f; // 0.0..1.0

                // apply cutoff frequency to the cutoff parameter sequence
                for (uint i = itResonanceEvent->FragmentPos(); i < end; i++) {
                    pEngine->pSynthesisParameters[Event::destination_vcfr][i] += resonancedelta;
                }

                itResonanceEvent = itNextResonanceEvent;
            }
            if (!pResonanceEventList->isEmpty()) VCFResonanceCtrl.fvalue = pResonanceEventList->last()->Param.CC.Value * 0.00787f; // needed for initialization of parameter matrix next time
        }
    }

    /**
     * Calculate all necessary, final biquad filter parameters.
     *
     * @param Samples - number of samples to be rendered in this audio fragment cycle
     */
    void Voice::CalculateBiquadParameters(uint Samples) {
        biquad_param_t bqbase;
        biquad_param_t bqmain;
        float prev_cutoff = pEngine->pSynthesisParameters[Event::destination_vcfc][0];
        float prev_res    = pEngine->pSynthesisParameters[Event::destination_vcfr][0];
        FilterLeft.SetParameters(&bqbase, &bqmain, prev_cutoff, prev_res, pEngine->SampleRate);
        FilterRight.SetParameters(&bqbase, &bqmain, prev_cutoff, prev_res, pEngine->SampleRate);
        pEngine->pBasicFilterParameters[0] = bqbase;
        pEngine->pMainFilterParameters[0]  = bqmain;

        float* bq;
        for (int i = 1; i < Samples; i++) {
            // recalculate biquad parameters if cutoff or resonance differ from previous sample point
            if (!(i & FILTER_UPDATE_MASK)) {
                if (pEngine->pSynthesisParameters[Event::destination_vcfr][i] != prev_res ||
                    pEngine->pSynthesisParameters[Event::destination_vcfc][i] != prev_cutoff)
                {
                    prev_cutoff = pEngine->pSynthesisParameters[Event::destination_vcfc][i];
                    prev_res    = pEngine->pSynthesisParameters[Event::destination_vcfr][i];
                    FilterLeft.SetParameters(&bqbase, &bqmain, prev_cutoff, prev_res, pEngine->SampleRate);
                    FilterRight.SetParameters(&bqbase, &bqmain, prev_cutoff, prev_res, pEngine->SampleRate);
                }
            }

            //same as 'pEngine->pBasicFilterParameters[i] = bqbase;'
            bq    = (float*) &pEngine->pBasicFilterParameters[i];
            bq[0] = bqbase.b0;
            bq[1] = bqbase.b1;
            bq[2] = bqbase.b2;
            bq[3] = bqbase.a1;
            bq[4] = bqbase.a2;

            // same as 'pEngine->pMainFilterParameters[i] = bqmain;'
            bq    = (float*) &pEngine->pMainFilterParameters[i];
            bq[0] = bqmain.b0;
            bq[1] = bqmain.b1;
            bq[2] = bqmain.b2;
            bq[3] = bqmain.a1;
            bq[4] = bqmain.a2;
        }
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
        RunSynthesisFunction(SynthesisMode, *this, Samples, pSrc, Skip);
    }

    /**
     *  Immediately kill the voice. This method should not be used to kill
     *  a normal, active voice, because it doesn't take care of things like
     *  fading down the volume level to avoid clicks and regular processing
     *  until the kill event actually occured!
     *
     *  @see Kill()
     */
    void Voice::KillImmediately() {
        if (DiskVoice && DiskStreamRef.State != Stream::state_unused) {
            pDiskThread->OrderDeletionOfStream(&DiskStreamRef);
        }
        Reset();
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
        //FIXME: just two sanity checks for debugging, can be removed
        if (!itKillEvent) dmsg(1,("gig::Voice::Kill(): ERROR, !itKillEvent !!!\n"));
        if (itKillEvent && !itKillEvent.isValid()) dmsg(1,("gig::Voice::Kill(): ERROR, itKillEvent invalid !!!\n"));

        if (itTriggerEvent && itKillEvent->FragmentPos() <= itTriggerEvent->FragmentPos()) return;
        this->itKillEvent = itKillEvent;
    }

}} // namespace LinuxSampler::gig
