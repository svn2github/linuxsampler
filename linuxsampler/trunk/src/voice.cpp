/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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

#include "voice.h"

// FIXME: no support for layers (nor crossfades) yet

DiskThread*  Voice::pDiskThread = NULL;
AudioThread* Voice::pEngine     = NULL;
const float  Voice::FILTER_CUTOFF_COEFF(CalculateFilterCutoffCoeff());

float Voice::CalculateFilterCutoffCoeff() {
    return log(FILTER_CUTOFF_MIN / FILTER_CUTOFF_MAX);
}

Voice::Voice() {
    Active = false;
    pEG1   = new EG_VCA(ModulationSystem::destination_vca);
    pEG2   = new EG_VCA(ModulationSystem::destination_vcfc);
    pEG3   = new EG_D(ModulationSystem::destination_vco);
    pLFO1  = new LFO<VCAManipulator>(0.0f, 1.0f, LFO<VCAManipulator>::propagation_top_down, pEngine->pEventPool);
    pLFO2  = new LFO<VCFCManipulator>(0.0f, 1.0f, LFO<VCFCManipulator>::propagation_top_down, pEngine->pEventPool);
    pLFO3  = new LFO<VCOManipulator>(-1200.0f, 1200.0f, LFO<VCOManipulator>::propagation_middle_balanced, pEngine->pEventPool); // +-1 octave (+-1200 cents) max.
}

Voice::~Voice() {
    if (pEG1)  delete pEG1;
    if (pEG2)  delete pEG2;
    if (pEG3)  delete pEG3;
    if (pLFO1) delete pLFO1;
    if (pLFO2) delete pLFO2;
    if (pLFO3) delete pLFO3;
}

/**
 *  Initializes and triggers the voice, a disk stream will be launched if
 *  needed.
 *
 *  @param pNoteOnEvent - event that caused triggering of this voice
 *  @param PitchBend    - MIDI detune factor (-8192 ... +8191)
 *  @param pInstrument  - points to the loaded instrument which provides sample wave(s) and articulation data
 *  @returns            0 on success, a value < 0 if something failed
 */
int Voice::Trigger(ModulationSystem::Event* pNoteOnEvent, int PitchBend, gig::Instrument* pInstrument) {
    Active          = true;
    MIDIKey         = pNoteOnEvent->Key;
    pRegion         = pInstrument->GetRegion(MIDIKey);
    PlaybackState   = playback_state_ram; // we always start playback from RAM cache and switch then to disk if needed
    Pos             = 0;
    ReleaseVelocity = 127; // default release velocity value
    Delay           = pNoteOnEvent->FragmentPos();
    pTriggerEvent   = pNoteOnEvent;

    if (!pRegion) {
        std::cerr << "Audio Thread: No Region defined for MIDI key " << MIDIKey << std::endl << std::flush;
        Kill();
        return -1;
    }

    //TODO: current MIDI controller values are not taken into account yet
    gig::DimensionRegion* pDimRgn = NULL;
    for (int i = pRegion->Dimensions - 1; i >= 0; i--) { // Check if instrument has a velocity split
        if (pRegion->pDimensionDefinitions[i].dimension == gig::dimension_velocity) {
            uint DimValues[5] = {0,0,0,0,0};
                 DimValues[i] = pNoteOnEvent->Velocity;
            pDimRgn = pRegion->GetDimensionRegionByValue(DimValues[4],DimValues[3],DimValues[2],DimValues[1],DimValues[0]);
            break;
        }
    }
    if (!pDimRgn) { // if there was no velocity split
        pDimRgn = pRegion->GetDimensionRegionByValue(0,0,0,0,0);
    }

    pSample = pDimRgn->pSample; // sample won't change until the voice is finished

    // Check if the sample needs disk streaming or is too short for that
    long cachedsamples = pSample->GetCache().Size / pSample->FrameSize;
    DiskVoice          = cachedsamples < pSample->SamplesTotal;

    if (DiskVoice) { // voice to be streamed from disk
        MaxRAMPos = cachedsamples - (MaxSamplesPerCycle << MAX_PITCH) / pSample->Channels; //TODO: this calculation is too pessimistic and may better be moved to Render() method, so it calculates MaxRAMPos dependent to the current demand of sample points to be rendered (e.g. in case of JACK)

        // check if there's a loop defined which completely fits into the cached (RAM) part of the sample
        if (pSample->Loops && pSample->LoopEnd <= MaxRAMPos) {
            RAMLoop        = true;
            LoopCyclesLeft = pSample->LoopPlayCount;
        }
        else RAMLoop = false;

        if (pDiskThread->OrderNewStream(&DiskStreamRef, pSample, MaxRAMPos, !RAMLoop) < 0) {
            dmsg(1,("Disk stream order failed!\n"));
            Kill();
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
        double pitchbasecents = pDimRgn->FineTune * 10;
        if (pDimRgn->PitchTrack) pitchbasecents += (MIDIKey - (int) pDimRgn->UnityNote) * 100;
        this->PitchBase = RTMath::CentsToFreqRatio(pitchbasecents);
        this->PitchBend = RTMath::CentsToFreqRatio(((double) PitchBend / 8192.0) * 200.0); // pitchbend wheel +-2 semitones = 200 cents
    }


    Volume = pDimRgn->GetVelocityAttenuation(pNoteOnEvent->Velocity);


    // setup EG 1 (VCA EG)
    {
        // get current value of EG1 controller
        double eg1controllervalue;
        switch (pDimRgn->EG1Controller.type) {
            case gig::eg1_ctrl_t::type_none: // no controller defined
                eg1controllervalue = 0;
                break;
            case gig::eg1_ctrl_t::type_channelaftertouch:
                eg1controllervalue = 0; // TODO: aftertouch not yet supported
                break;
            case gig::eg1_ctrl_t::type_velocity:
                eg1controllervalue = pNoteOnEvent->Velocity;
                break;
            case gig::eg1_ctrl_t::type_controlchange: // MIDI control change controller
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


#if ENABLE_FILTER
    // setup EG 2 (VCF Cutoff EG)
    {
        // get current value of EG2 controller
        double eg2controllervalue;
        switch (pDimRgn->EG2Controller.type) {
            case gig::eg2_ctrl_t::type_none: // no controller defined
                eg2controllervalue = 0;
                break;
            case gig::eg2_ctrl_t::type_channelaftertouch:
                eg2controllervalue = 0; // TODO: aftertouch not yet supported
                break;
            case gig::eg2_ctrl_t::type_velocity:
                eg2controllervalue = pNoteOnEvent->Velocity;
                break;
            case gig::eg2_ctrl_t::type_controlchange: // MIDI control change controller
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
#endif // ENABLE_FILTER


    // setup EG 3 (VCO EG)
    {
       double eg3depth = RTMath::CentsToFreqRatio(pDimRgn->EG3Depth);
       pEG3->Trigger(eg3depth, pDimRgn->EG3Attack, Delay);
    }


    // setup LFO 1 (VCA LFO)
    {
        uint16_t lfo1_internal_depth;
        switch (pDimRgn->LFO1Controller) {
            case gig::lfo1_ctrl_internal:
                lfo1_internal_depth  = pDimRgn->LFO1InternalDepth;
                pLFO1->ExtController = 0; // no external controller
                break;
            case gig::lfo1_ctrl_modwheel:
                lfo1_internal_depth  = 0;
                pLFO1->ExtController = 1; // MIDI controller 1
                break;
            case gig::lfo1_ctrl_breath:
                lfo1_internal_depth  = 0;
                pLFO1->ExtController = 2; // MIDI controller 2
                break;
            case gig::lfo1_ctrl_internal_modwheel:
                lfo1_internal_depth  = pDimRgn->LFO1InternalDepth;
                pLFO1->ExtController = 1; // MIDI controller 1
                break;
            case gig::lfo1_ctrl_internal_breath:
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
                       Delay);
    }

#if ENABLE_FILTER
    // setup LFO 2 (VCF Cutoff LFO)
    {
        uint16_t lfo2_internal_depth;
        switch (pDimRgn->LFO2Controller) {
            case gig::lfo2_ctrl_internal:
                lfo2_internal_depth  = pDimRgn->LFO2InternalDepth;
                pLFO2->ExtController = 0; // no external controller
                break;
            case gig::lfo2_ctrl_modwheel:
                lfo2_internal_depth  = 0;
                pLFO2->ExtController = 1; // MIDI controller 1
                break;
            case gig::lfo2_ctrl_foot:
                lfo2_internal_depth  = 0;
                pLFO2->ExtController = 4; // MIDI controller 4
                break;
            case gig::lfo2_ctrl_internal_modwheel:
                lfo2_internal_depth  = pDimRgn->LFO2InternalDepth;
                pLFO2->ExtController = 1; // MIDI controller 1
                break;
            case gig::lfo2_ctrl_internal_foot:
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
                       Delay);
    }
#endif // ENABLE_FILTER

    // setup LFO 3 (VCO LFO)
    {
        uint16_t lfo3_internal_depth;
        switch (pDimRgn->LFO3Controller) {
            case gig::lfo3_ctrl_internal:
                lfo3_internal_depth  = pDimRgn->LFO3InternalDepth;
                pLFO3->ExtController = 0; // no external controller
                break;
            case gig::lfo3_ctrl_modwheel:
                lfo3_internal_depth  = 0;
                pLFO3->ExtController = 1; // MIDI controller 1
                break;
            case gig::lfo3_ctrl_aftertouch:
                lfo3_internal_depth  = 0;
                pLFO3->ExtController = 0; // TODO: aftertouch not implemented yet
                break;
            case gig::lfo3_ctrl_internal_modwheel:
                lfo3_internal_depth  = pDimRgn->LFO3InternalDepth;
                pLFO3->ExtController = 1; // MIDI controller 1
                break;
            case gig::lfo3_ctrl_internal_aftertouch:
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
                       Delay);
    }

#if ENABLE_FILTER
    #if FORCE_FILTER_USAGE
    FilterLeft.Enabled = FilterRight.Enabled = true;
    #else // use filter only if instrument file told so
    FilterLeft.Enabled = FilterRight.Enabled = pDimRgn->VCFEnabled;
    #endif // FORCE_FILTER_USAGE
    if (pDimRgn->VCFEnabled) {
        #ifdef OVERRIDE_FILTER_CUTOFF_CTRL
        VCFCutoffCtrl.controller = OVERRIDE_FILTER_CUTOFF_CTRL;
        #else // use the one defined in the instrument file
        switch (pDimRgn->VCFCutoffController) {
            case gig::vcf_cutoff_ctrl_modwheel:
                VCFCutoffCtrl.controller = 1;
                break;
            case gig::vcf_cutoff_ctrl_effect1:
                VCFCutoffCtrl.controller = 12;
                break;
            case gig::vcf_cutoff_ctrl_effect2:
                VCFCutoffCtrl.controller = 13;
                break;
            case gig::vcf_cutoff_ctrl_breath:
                VCFCutoffCtrl.controller = 2;
                break;
            case gig::vcf_cutoff_ctrl_foot:
                VCFCutoffCtrl.controller = 4;
                break;
            case gig::vcf_cutoff_ctrl_sustainpedal:
                VCFCutoffCtrl.controller = 64;
                break;
            case gig::vcf_cutoff_ctrl_softpedal:
                VCFCutoffCtrl.controller = 67;
                break;
            case gig::vcf_cutoff_ctrl_genpurpose7:
                VCFCutoffCtrl.controller = 82;
                break;
            case gig::vcf_cutoff_ctrl_genpurpose8:
                VCFCutoffCtrl.controller = 83;
                break;
            case gig::vcf_cutoff_ctrl_aftertouch: //TODO: not implemented yet
            case gig::vcf_cutoff_ctrl_none:
            default:
                VCFCutoffCtrl.controller = 0;
                break;
        }
        #endif // OVERRIDE_FILTER_CUTOFF_CTRL

        #ifdef OVERRIDE_FILTER_RES_CTRL
        VCFResonanceCtrl.controller = OVERRIDE_FILTER_RES_CTRL;
        #else // use the one defined in the instrument file
        switch (pDimRgn->VCFResonanceController) {
            case gig::vcf_res_ctrl_genpurpose3:
                VCFResonanceCtrl.controller = 18;
                break;
            case gig::vcf_res_ctrl_genpurpose4:
                VCFResonanceCtrl.controller = 19;
                break;
            case gig::vcf_res_ctrl_genpurpose5:
                VCFResonanceCtrl.controller = 80;
                break;
            case gig::vcf_res_ctrl_genpurpose6:
                VCFResonanceCtrl.controller = 81;
                break;
            case gig::vcf_res_ctrl_none:
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
            ? exp((float) (127 - pNoteOnEvent->Velocity) * (float) pDimRgn->VCFVelocityScale * 6.2E-5f * FILTER_CUTOFF_COEFF) * FILTER_CUTOFF_MAX
            : exp((float) VCFCutoffCtrl.value * 0.00787402f * FILTER_CUTOFF_COEFF) * FILTER_CUTOFF_MAX;

        // calculate resonance
        float resonance = (float) VCFResonanceCtrl.value * 0.00787f;   // 0.0..1.0
        if (pDimRgn->VCFKeyboardTracking) {
            resonance += (float) (pNoteOnEvent->Key - pDimRgn->VCFKeyboardTrackingBreakpoint) * 0.00787f;
        }
        Constrain(resonance, 0.0, 1.0); // correct resonance if outside allowed value range (0.0..1.0)

        VCFCutoffCtrl.fvalue    = cutoff - FILTER_CUTOFF_MIN;
        VCFResonanceCtrl.fvalue = resonance;

        FilterLeft.SetParameters(cutoff,  resonance, ModulationSystem::SampleRate());
        FilterRight.SetParameters(cutoff, resonance, ModulationSystem::SampleRate());

        FilterUpdateCounter = -1;
    }
    else {
        VCFCutoffCtrl.controller    = 0;
        VCFResonanceCtrl.controller = 0;
    }
#endif // ENABLE_FILTER

    // ************************************************
    // TODO: ARTICULATION DATA HANDLING IS MISSING HERE
    // ************************************************

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

    // Reset the synthesis parameter matrix
    ModulationSystem::ResetDestinationParameter(ModulationSystem::destination_vca, this->Volume);
    ModulationSystem::ResetDestinationParameter(ModulationSystem::destination_vco, this->PitchBase);
#if ENABLE_FILTER
    ModulationSystem::ResetDestinationParameter(ModulationSystem::destination_vcfc, VCFCutoffCtrl.fvalue);
    ModulationSystem::ResetDestinationParameter(ModulationSystem::destination_vcfr, VCFResonanceCtrl.fvalue);
#endif // ENABLE_FILTER


    // Apply events to the synthesis parameter matrix
    ProcessEvents(Samples);


    // Let all modulators write their parameter changes to the synthesis parameter matrix for the current audio fragment
    pEG1->Process(Samples, pEngine->pMIDIKeyInfo[MIDIKey].pEvents, pTriggerEvent, this->Pos, this->PitchBase * this->PitchBend);
#if ENABLE_FILTER
    pEG2->Process(Samples, pEngine->pMIDIKeyInfo[MIDIKey].pEvents, pTriggerEvent, this->Pos, this->PitchBase * this->PitchBend);
#endif // ENABLE_FILTER
    pEG3->Process(Samples);
    pLFO1->Process(Samples);
#if ENABLE_FILTER
    pLFO2->Process(Samples);
#endif // ENABLE_FILTER
    pLFO3->Process(Samples);


    switch (this->PlaybackState) {

        case playback_state_ram: {
                if (RAMLoop) InterpolateAndLoop(Samples, (sample_t*) pSample->GetCache().pStart, Delay);
                else         Interpolate(Samples, (sample_t*) pSample->GetCache().pStart, Delay);
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
                        Kill();
                        return;
                    }
                    DiskStreamRef.pStream->IncrementReadPos(pSample->Channels * (RTMath::DoubleToInt(Pos) - MaxRAMPos));
                    Pos -= RTMath::DoubleToInt(Pos);
                }

                // add silence sample at the end if we reached the end of the stream (for the interpolator)
                if (DiskStreamRef.State == Stream::state_end && DiskStreamRef.pStream->GetReadSpace() < (MaxSamplesPerCycle << MAX_PITCH) / pSample->Channels) {
                    DiskStreamRef.pStream->WriteSilence((MaxSamplesPerCycle << MAX_PITCH) / pSample->Channels);
                    this->PlaybackState = playback_state_end;
                }

                sample_t* ptr = DiskStreamRef.pStream->GetReadPtr(); // get the current read_ptr within the ringbuffer where we read the samples from
                Interpolate(Samples, ptr, Delay);
                DiskStreamRef.pStream->IncrementReadPos(RTMath::DoubleToInt(Pos) * pSample->Channels);
                Pos -= RTMath::DoubleToInt(Pos);
            }
            break;

        case playback_state_end:
            Kill(); // free voice
            break;
    }


#if ENABLE_FILTER
    // Reset synthesis event lists (except VCO, as VCO events apply channel wide currently)
    pEngine->pSynthesisEvents[ModulationSystem::destination_vcfc]->clear();
    pEngine->pSynthesisEvents[ModulationSystem::destination_vcfr]->clear();
#endif // ENABLE_FILTER

    // Reset delay
    Delay = 0;

    pTriggerEvent = NULL;

    // If release stage finished, let the voice be killed
    if (pEG1->GetStage() == EG_VCA::stage_end) this->PlaybackState = playback_state_end;
}

/**
 *  Resets voice variables. Should only be called if rendering process is
 *  suspended / not running.
 */
void Voice::Reset() {
    pLFO1->Reset();
    pLFO2->Reset();
    pLFO3->Reset();
    DiskStreamRef.pStream = NULL;
    DiskStreamRef.hStream = 0;
    DiskStreamRef.State   = Stream::state_unused;
    DiskStreamRef.OrderID = 0;
    Active = false;
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
    ModulationSystem::Event* pCCEvent = pEngine->pCCEvents->first();
    if (Delay) { // skip events that happened before this voice was triggered
        while (pCCEvent && pCCEvent->FragmentPos() <= Delay) pCCEvent = pEngine->pCCEvents->next();
    }
    while (pCCEvent) {
        if (pCCEvent->Controller) { // if valid MIDI controller
            #if ENABLE_FILTER
            if (pCCEvent->Controller == VCFCutoffCtrl.controller) {
                pEngine->pSynthesisEvents[ModulationSystem::destination_vcfc]->alloc_assign(*pCCEvent);
            }
            if (pCCEvent->Controller == VCFResonanceCtrl.controller) {
                pEngine->pSynthesisEvents[ModulationSystem::destination_vcfr]->alloc_assign(*pCCEvent);
            }
            #endif // ENABLE_FILTER
            if (pCCEvent->Controller == pLFO1->ExtController) {
                pLFO1->SendEvent(pCCEvent);
            }
            #if ENABLE_FILTER
            if (pCCEvent->Controller == pLFO2->ExtController) {
                pLFO2->SendEvent(pCCEvent);
            }
            #endif // ENABLE_FILTER
            if (pCCEvent->Controller == pLFO3->ExtController) {
                pLFO3->SendEvent(pCCEvent);
            }
        }

        pCCEvent = pEngine->pCCEvents->next();
    }


    // process pitch events
    {
        RTEList<ModulationSystem::Event>* pVCOEventList = pEngine->pSynthesisEvents[ModulationSystem::destination_vco];
        ModulationSystem::Event* pVCOEvent = pVCOEventList->first();
        if (Delay) { // skip events that happened before this voice was triggered
            while (pVCOEvent && pVCOEvent->FragmentPos() <= Delay) pVCOEvent = pVCOEventList->next();
        }
        // apply old pitchbend value until first pitch event occurs
        if (this->PitchBend != 1.0) {
            uint end = (pVCOEvent) ? pVCOEvent->FragmentPos() : Samples;
            for (uint i = Delay; i < end; i++) {
                ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i] *= this->PitchBend;
            }
        }
        float pitch;
        while (pVCOEvent) {
            ModulationSystem::Event* pNextVCOEvent = pVCOEventList->next();

            // calculate the influence length of this event (in sample points)
            uint end = (pNextVCOEvent) ? pNextVCOEvent->FragmentPos() : Samples;

            pitch = RTMath::CentsToFreqRatio(((double) pVCOEvent->Pitch / 8192.0) * 200.0); // +-two semitones = +-200 cents

            // apply pitch value to the pitch parameter sequence
            for (uint i = pVCOEvent->FragmentPos(); i < end; i++) {
                ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i] *= pitch;
            }

            pVCOEvent = pNextVCOEvent;
        }
        if (pVCOEventList->last()) this->PitchBend = pitch;
    }


#if ENABLE_FILTER
    // process filter cutoff events
    {
        RTEList<ModulationSystem::Event>* pCutoffEventList = pEngine->pSynthesisEvents[ModulationSystem::destination_vcfc];
        ModulationSystem::Event* pCutoffEvent = pCutoffEventList->first();
        if (Delay) { // skip events that happened before this voice was triggered
            while (pCutoffEvent && pCutoffEvent->FragmentPos() <= Delay) pCutoffEvent = pCutoffEventList->next();
        }
        float cutoff;
        while (pCutoffEvent) {
            ModulationSystem::Event* pNextCutoffEvent = pCutoffEventList->next();

            // calculate the influence length of this event (in sample points)
            uint end = (pNextCutoffEvent) ? pNextCutoffEvent->FragmentPos() : Samples;

            cutoff = exp((float) pCutoffEvent->Value * 0.00787402f * FILTER_CUTOFF_COEFF) * FILTER_CUTOFF_MAX - FILTER_CUTOFF_MIN;

            // apply cutoff frequency to the cutoff parameter sequence
            for (uint i = pCutoffEvent->FragmentPos(); i < end; i++) {
                ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i] = cutoff;
            }

            pCutoffEvent = pNextCutoffEvent;
        }
        if (pCutoffEventList->last()) VCFCutoffCtrl.fvalue = cutoff; // needed for initialization of parameter matrix next time
    }

    // process filter resonance events
    {
        RTEList<ModulationSystem::Event>* pResonanceEventList = pEngine->pSynthesisEvents[ModulationSystem::destination_vcfr];
        ModulationSystem::Event* pResonanceEvent = pResonanceEventList->first();
        if (Delay) { // skip events that happened before this voice was triggered
            while (pResonanceEvent && pResonanceEvent->FragmentPos() <= Delay) pResonanceEvent = pResonanceEventList->next();
        }
        while (pResonanceEvent) {
            ModulationSystem::Event* pNextResonanceEvent = pResonanceEventList->next();

            // calculate the influence length of this event (in sample points)
            uint end = (pNextResonanceEvent) ? pNextResonanceEvent->FragmentPos() : Samples;

            // convert absolute controller value to differential
            int ctrldelta = pResonanceEvent->Value - VCFResonanceCtrl.value;
            VCFResonanceCtrl.value = pResonanceEvent->Value;

            float resonancedelta = (float) ctrldelta * 0.00787f; // 0.0..1.0

            // apply cutoff frequency to the cutoff parameter sequence
            for (uint i = pResonanceEvent->FragmentPos(); i < end; i++) {
                ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i] += resonancedelta;
            }

            pResonanceEvent = pNextResonanceEvent;
        }
        if (pResonanceEventList->last()) VCFResonanceCtrl.fvalue = pResonanceEventList->last()->Value * 0.00787f; // needed for initialization of parameter matrix next time
    }
#endif // ENABLE_FILTER
}

/**
 *  Interpolates the input audio data (no loop).
 *
 *  @param Samples - number of sample points to be rendered in this audio
 *                   fragment cycle
 *  @param pSrc    - pointer to input sample data
 *  @param Skip    - number of sample points to skip in output buffer
 */
void Voice::Interpolate(uint Samples, sample_t* pSrc, uint Skip) {
    int i = Skip;

    // FIXME: assuming either mono or stereo
    if (this->pSample->Channels == 2) { // Stereo Sample
        while (i < Samples) {
            InterpolateOneStep_Stereo(pSrc, i,
                                      ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i],
                                      ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i],
                                      ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i],
                                      ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i]);
        }
    }
    else { // Mono Sample
        while (i < Samples) {
            InterpolateOneStep_Mono(pSrc, i,
                                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i],
                                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i],
                                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i],
                                    ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i]);
        }
    }
}

/**
 *  Interpolates the input audio data, this method honors looping.
 *
 *  @param Samples - number of sample points to be rendered in this audio
 *                   fragment cycle
 *  @param pSrc    - pointer to input sample data
 *  @param Skip    - number of sample points to skip in output buffer
 */
void Voice::InterpolateAndLoop(uint Samples, sample_t* pSrc, uint Skip) {
    int i = Skip;

    // FIXME: assuming either mono or stereo
    if (pSample->Channels == 2) { // Stereo Sample
        if (pSample->LoopPlayCount) {
            // render loop (loop count limited)
            while (i < Samples && LoopCyclesLeft) {
                InterpolateOneStep_Stereo(pSrc, i,
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i]);
                if (Pos > pSample->LoopEnd) {
                    Pos = pSample->LoopStart + fmod(Pos - pSample->LoopEnd, pSample->LoopSize);;
                    LoopCyclesLeft--;
                }
            }
            // render on without loop
            while (i < Samples) {
                InterpolateOneStep_Stereo(pSrc, i,
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i]);
            }
        }
        else { // render loop (endless loop)
            while (i < Samples) {
                InterpolateOneStep_Stereo(pSrc, i,
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i],
                                          ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i]);
                if (Pos > pSample->LoopEnd) {
                    Pos = pSample->LoopStart + fmod(Pos - pSample->LoopEnd, pSample->LoopSize);
                }
            }
        }
    }
    else { // Mono Sample
        if (pSample->LoopPlayCount) {
            // render loop (loop count limited)
            while (i < Samples && LoopCyclesLeft) {
                InterpolateOneStep_Mono(pSrc, i,
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i]);
                if (Pos > pSample->LoopEnd) {
                    Pos = pSample->LoopStart + fmod(Pos - pSample->LoopEnd, pSample->LoopSize);;
                    LoopCyclesLeft--;
                }
            }
            // render on without loop
            while (i < Samples) {
                InterpolateOneStep_Mono(pSrc, i,
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i]);
            }
        }
        else { // render loop (endless loop)
            while (i < Samples) {
                InterpolateOneStep_Mono(pSrc, i,
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vca][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vco][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfc][i],
                                        ModulationSystem::pDestinationParameter[ModulationSystem::destination_vcfr][i]);
                if (Pos > pSample->LoopEnd) {
                    Pos = pSample->LoopStart + fmod(Pos - pSample->LoopEnd, pSample->LoopSize);;
                }
            }
        }
    }
}

/**
 *  Immediately kill the voice.
 */
void Voice::Kill() {
    if (DiskVoice && DiskStreamRef.State != Stream::state_unused) {
        pDiskThread->OrderDeletionOfStream(&DiskStreamRef);
    }
    Reset();
}
