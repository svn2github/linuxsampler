/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003,2004 by Benno Senoner and Christian Schoenebeck    *
 *   Copyright (C) 2005-2008 Christian Schoenebeck                         *
 *   Copyright (C) 2009-2010 Christian Schoenebeck and Grigor Iliev        *
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

#include "AbstractVoice.h"

namespace LinuxSampler {

    AbstractVoice::AbstractVoice() {
        pEngineChannel = NULL;
        pLFO1 = new LFOUnsigned(1.0f);  // amplitude EG (0..1 range)
        pLFO2 = new LFOUnsigned(1.0f);  // filter EG (0..1 range)
        pLFO3 = new LFOSigned(1200.0f); // pitch EG (-1200..+1200 range)
        PlaybackState = playback_state_end;
        SynthesisMode = 0; // set all mode bits to 0 first
        // select synthesis implementation (asm core is not supported ATM)
        #if 0 // CONFIG_ASM && ARCH_X86
        SYNTHESIS_MODE_SET_IMPLEMENTATION(SynthesisMode, Features::supportsMMX() && Features::supportsSSE());
        #else
        SYNTHESIS_MODE_SET_IMPLEMENTATION(SynthesisMode, false);
        #endif
        SYNTHESIS_MODE_SET_PROFILING(SynthesisMode, gig::Profiler::isEnabled());

        finalSynthesisParameters.filterLeft.Reset();
        finalSynthesisParameters.filterRight.Reset();
    }

    AbstractVoice::~AbstractVoice() {
        if (pLFO1) delete pLFO1;
        if (pLFO2) delete pLFO2;
        if (pLFO3) delete pLFO3;
    }

    /**
     *  Resets voice variables. Should only be called if rendering process is
     *  suspended / not running.
     */
    void AbstractVoice::Reset() {
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
     *  Initializes and triggers the voice, a disk stream will be launched if
     *  needed.
     *
     *  @param pEngineChannel - engine channel on which this voice was ordered
     *  @param itNoteOnEvent  - event that caused triggering of this voice
     *  @param PitchBend      - MIDI detune factor (-8192 ... +8191)
     *  @param pRegion- points to the region which provides sample wave(s) and articulation data
     *  @param VoiceType      - type of this voice
     *  @param iKeyGroup      - a value > 0 defines a key group in which this voice is member of
     *  @returns 0 on success, a value < 0 if the voice wasn't triggered
     *           (either due to an error or e.g. because no region is
     *           defined for the given key)
     */
    int AbstractVoice::Trigger (
        AbstractEngineChannel*  pEngineChannel,
        Pool<Event>::Iterator&  itNoteOnEvent,
        int                     PitchBend,
        type_t                  VoiceType,
        int                     iKeyGroup
    ) {
        this->pEngineChannel = pEngineChannel;
        Orphan = false;

        #if CONFIG_DEVMODE
        if (itNoteOnEvent->FragmentPos() > GetEngine()->MaxSamplesPerCycle) { // just a sanity check for debugging
            dmsg(1,("Voice::Trigger(): ERROR, TriggerDelay > Totalsamples\n"));
        }
        #endif // CONFIG_DEVMODE

        Type            = VoiceType;
        MIDIKey         = itNoteOnEvent->Param.Note.Key;
        PlaybackState   = playback_state_init; // mark voice as triggered, but no audio rendered yet
        Delay           = itNoteOnEvent->FragmentPos();
        itTriggerEvent  = itNoteOnEvent;
        itKillEvent     = Pool<Event>::Iterator();

        pGroupEvents = iKeyGroup ? pEngineChannel->ActiveKeyGroups[iKeyGroup] : 0;

        SmplInfo   = GetSampleInfo();
        RgnInfo    = GetRegionInfo();
        InstrInfo  = GetInstrumentInfo();

        // calculate volume
        const double velocityAttenuation = GetVelocityAttenuation(itNoteOnEvent->Param.Note.Velocity);
        float volume = CalculateVolume(velocityAttenuation);
        if (volume <= 0) return -1;

        // select channel mode (mono or stereo)
        SYNTHESIS_MODE_SET_CHANNELS(SynthesisMode, SmplInfo.ChannelCount == 2);
        // select bit depth (16 or 24)
        SYNTHESIS_MODE_SET_BITDEPTH24(SynthesisMode, SmplInfo.BitDepth == 24);

        // get starting crossfade volume level
        float crossfadeVolume = CalculateCrossfadeVolume(itNoteOnEvent->Param.Note.Velocity);

        VolumeLeft  = volume * AbstractEngine::PanCurve[64 - RgnInfo.Pan];
        VolumeRight = volume * AbstractEngine::PanCurve[64 + RgnInfo.Pan];

        float subfragmentRate = GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE;
        CrossfadeSmoother.trigger(crossfadeVolume, subfragmentRate);
        VolumeSmoother.trigger(pEngineChannel->MidiVolume, subfragmentRate);
        PanLeftSmoother.trigger(pEngineChannel->GlobalPanLeft, subfragmentRate);
        PanRightSmoother.trigger(pEngineChannel->GlobalPanRight, subfragmentRate);

        finalSynthesisParameters.dPos = RgnInfo.SampleStartOffset; // offset where we should start playback of sample (0 - 2000 sample points)
        Pos = RgnInfo.SampleStartOffset;

        // Check if the sample needs disk streaming or is too short for that
        long cachedsamples = GetSampleCacheSize() / SmplInfo.FrameSize;
        DiskVoice          = cachedsamples < SmplInfo.TotalFrameCount;

        if (DiskVoice) { // voice to be streamed from disk
            if (cachedsamples > (GetEngine()->MaxSamplesPerCycle << CONFIG_MAX_PITCH)) {
                MaxRAMPos = cachedsamples - (GetEngine()->MaxSamplesPerCycle << CONFIG_MAX_PITCH) / SmplInfo.ChannelCount; //TODO: this calculation is too pessimistic and may better be moved to Render() method, so it calculates MaxRAMPos dependent to the current demand of sample points to be rendered (e.g. in case of JACK)
            } else {
                // The cache is too small to fit a max sample buffer.
                // Setting MaxRAMPos to 0 will probably cause a click
                // in the audio, but it's better than not handling
                // this case at all, which would have caused the
                // unsigned MaxRAMPos to be set to a negative number.
                MaxRAMPos = 0;
            }

            // check if there's a loop defined which completely fits into the cached (RAM) part of the sample
            RAMLoop = (SmplInfo.HasLoops && (SmplInfo.LoopStart + SmplInfo.LoopLength) <= MaxRAMPos);

            if (OrderNewStream()) return -1;
            dmsg(4,("Disk voice launched (cached samples: %d, total Samples: %d, MaxRAMPos: %d, RAMLooping: %s)\n", cachedsamples, SmplInfo.TotalFrameCount, MaxRAMPos, (RAMLoop) ? "yes" : "no"));
        }
        else { // RAM only voice
            MaxRAMPos = cachedsamples;
            RAMLoop = (SmplInfo.HasLoops);
            dmsg(4,("RAM only voice launched (Looping: %s)\n", (RAMLoop) ? "yes" : "no"));
        }
        if (RAMLoop) {
            loop.uiTotalCycles = SmplInfo.LoopPlayCount;
            loop.uiCyclesLeft  = SmplInfo.LoopPlayCount;
            loop.uiStart       = SmplInfo.LoopStart;
            loop.uiEnd         = SmplInfo.LoopStart + SmplInfo.LoopLength;
            loop.uiSize        = SmplInfo.LoopLength;
        }

        Pitch = CalculatePitchInfo(PitchBend);

        // the length of the decay and release curves are dependent on the velocity
        const double velrelease = 1 / GetVelocityRelease(itNoteOnEvent->Param.Note.Velocity);

        // setup EG 1 (VCA EG)
        {
            // get current value of EG1 controller
            double eg1controllervalue = GetEG1ControllerValue(itNoteOnEvent->Param.Note.Velocity);

            // calculate influence of EG1 controller on EG1's parameters
            EGInfo egInfo = CalculateEG1ControllerInfluence(eg1controllervalue);

            TriggerEG1(egInfo, velrelease, velocityAttenuation, GetEngine()->SampleRate, itNoteOnEvent->Param.Note.Velocity);
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
            float finalVolume = pEngineChannel->MidiVolume * crossfadeVolume * pEG1->getLevel();

            finalSynthesisParameters.fFinalVolumeLeft  = finalVolume * VolumeLeft  * pEngineChannel->GlobalPanLeft;
            finalSynthesisParameters.fFinalVolumeRight = finalVolume * VolumeRight * pEngineChannel->GlobalPanRight;
        }
    #endif
#endif

        // setup EG 2 (VCF Cutoff EG)
        {
            // get current value of EG2 controller
            double eg2controllervalue = GetEG2ControllerValue(itNoteOnEvent->Param.Note.Velocity);

            // calculate influence of EG2 controller on EG2's parameters
            EGInfo egInfo = CalculateEG2ControllerInfluence(eg2controllervalue);

            EG2.trigger (
                uint(RgnInfo.EG2PreAttack),
                RgnInfo.EG2Attack * egInfo.Attack,
                false,
                RgnInfo.EG2Decay1 * egInfo.Decay * velrelease,
                RgnInfo.EG2Decay2 * egInfo.Decay * velrelease,
                RgnInfo.EG2InfiniteSustain,
                uint(RgnInfo.EG2Sustain),
                RgnInfo.EG2Release * egInfo.Release * velrelease,
                velocityAttenuation,
                GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE
            );
        }


        // setup EG 3 (VCO EG)
        {
            // if portamento mode is on, we dedicate EG3 purely for portamento, otherwise if portamento is off we do as told by the patch
            bool  bPortamento = pEngineChannel->PortamentoMode && pEngineChannel->PortamentoPos >= 0.0f;
            float eg3depth = (bPortamento)
                         ? RTMath::CentsToFreqRatio((pEngineChannel->PortamentoPos - (float) MIDIKey) * 100)
                         : RTMath::CentsToFreqRatio(RgnInfo.EG3Depth);
            float eg3time = (bPortamento)
                        ? pEngineChannel->PortamentoTime
                        : RgnInfo.EG3Attack;
            EG3.trigger(eg3depth, eg3time, GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            dmsg(5,("PortamentoPos=%f, depth=%f, time=%f\n", pEngineChannel->PortamentoPos, eg3depth, eg3time));
        }


        // setup LFO 1 (VCA LFO)
        InitLFO1();
        // setup LFO 2 (VCF Cutoff LFO)
        InitLFO2();
        // setup LFO 3 (VCO LFO)
        InitLFO3();


        #if CONFIG_FORCE_FILTER
        const bool bUseFilter = true;
        #else // use filter only if instrument file told so
        const bool bUseFilter = RgnInfo.VCFEnabled;
        #endif // CONFIG_FORCE_FILTER
        SYNTHESIS_MODE_SET_FILTER(SynthesisMode, bUseFilter);
        if (bUseFilter) {
            #ifdef CONFIG_OVERRIDE_CUTOFF_CTRL
            VCFCutoffCtrl.controller = CONFIG_OVERRIDE_CUTOFF_CTRL;
            #else // use the one defined in the instrument file
            VCFCutoffCtrl.controller = GetVCFCutoffCtrl();
            #endif // CONFIG_OVERRIDE_CUTOFF_CTRL

            #ifdef CONFIG_OVERRIDE_RESONANCE_CTRL
            VCFResonanceCtrl.controller = CONFIG_OVERRIDE_RESONANCE_CTRL;
            #else // use the one defined in the instrument file
            VCFResonanceCtrl.controller = GetVCFResonanceCtrl();
            #endif // CONFIG_OVERRIDE_RESONANCE_CTRL

            #ifndef CONFIG_OVERRIDE_FILTER_TYPE
            finalSynthesisParameters.filterLeft.SetType(RgnInfo.VCFType);
            finalSynthesisParameters.filterRight.SetType(RgnInfo.VCFType);
            #else // override filter type
            finalSynthesisParameters.filterLeft.SetType(CONFIG_OVERRIDE_FILTER_TYPE);
            finalSynthesisParameters.filterRight.SetType(CONFIG_OVERRIDE_FILTER_TYPE);
            #endif // CONFIG_OVERRIDE_FILTER_TYPE

            VCFCutoffCtrl.value    = pEngineChannel->ControllerTable[VCFCutoffCtrl.controller];
            VCFResonanceCtrl.value = pEngineChannel->ControllerTable[VCFResonanceCtrl.controller];

            // calculate cutoff frequency
            CutoffBase = CalculateCutoffBase(itNoteOnEvent->Param.Note.Velocity);

            VCFCutoffCtrl.fvalue = CalculateFinalCutoff(CutoffBase);

            // calculate resonance
            float resonance = (float) (VCFResonanceCtrl.controller ? VCFResonanceCtrl.value : RgnInfo.VCFResonance);
            VCFResonanceCtrl.fvalue = resonance;
        } else {
            VCFCutoffCtrl.controller    = 0;
            VCFResonanceCtrl.controller = 0;
        }

        return 0; // success
    }

    /**
     *  Synthesizes the current audio fragment for this voice.
     *
     *  @param Samples - number of sample points to be rendered in this audio
     *                   fragment cycle
     *  @param pSrc    - pointer to input sample data
     *  @param Skip    - number of sample points to skip in output buffer
     */
    void AbstractVoice::Synthesize(uint Samples, sample_t* pSrc, uint Skip) {
        AbstractEngineChannel* pChannel = pEngineChannel;
        finalSynthesisParameters.pOutLeft  = &pChannel->pChannelLeft->Buffer()[Skip];
        finalSynthesisParameters.pOutRight = &pChannel->pChannelRight->Buffer()[Skip];
        finalSynthesisParameters.pSrc      = pSrc;

        RTList<Event>::Iterator itCCEvent = pChannel->pEvents->first();
        RTList<Event>::Iterator itNoteEvent;
        GetFirstEventOnKey(MIDIKey, itNoteEvent);

        RTList<Event>::Iterator itGroupEvent;
        if (pGroupEvents) itGroupEvent = pGroupEvents->first();

        if (itTriggerEvent) { // skip events that happened before this voice was triggered
            while (itCCEvent && itCCEvent->FragmentPos() <= Skip) ++itCCEvent;
            while (itGroupEvent && itGroupEvent->FragmentPos() <= Skip) ++itGroupEvent;

            // we can't simply compare the timestamp here, because note events
            // might happen on the same time stamp, so we have to deal on the
            // actual sequence the note events arrived instead (see bug #112)
            for (; itNoteEvent; ++itNoteEvent) {
                if (itTriggerEvent == itNoteEvent) {
                    ++itNoteEvent;
                    break;
                }
            }
        }

        uint killPos;
        if (itKillEvent) {
            int maxFadeOutPos = Samples - GetEngine()->GetMinFadeOutSamples();
            if (maxFadeOutPos < 0) {
                // There's not enough space in buffer to do a fade out
                // from max volume (this can only happen for audio
                // drivers that use Samples < MaxSamplesPerCycle).
                // End the EG1 here, at pos 0, with a shorter max fade
                // out time.
                pEG1->enterFadeOutStage(Samples / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                itKillEvent = Pool<Event>::Iterator();
            } else {
                killPos = RTMath::Min(itKillEvent->FragmentPos(), maxFadeOutPos);
            }
        }

        uint i = Skip;
        while (i < Samples) {
            int iSubFragmentEnd = RTMath::Min(i + CONFIG_DEFAULT_SUBFRAGMENT_SIZE, Samples);

            // initialize all final synthesis parameters
            fFinalCutoff    = VCFCutoffCtrl.fvalue;
            fFinalResonance = VCFResonanceCtrl.fvalue;

            // process MIDI control change and pitchbend events for this subfragment
            processCCEvents(itCCEvent, iSubFragmentEnd);

            finalSynthesisParameters.fFinalPitch = Pitch.PitchBase * Pitch.PitchBend;
            float fFinalVolume = VolumeSmoother.render() * CrossfadeSmoother.render();
#ifdef CONFIG_PROCESS_MUTED_CHANNELS
            if (pChannel->GetMute()) fFinalVolume = 0;
#endif

            // process transition events (note on, note off & sustain pedal)
            processTransitionEvents(itNoteEvent, iSubFragmentEnd);
            processGroupEvents(itGroupEvent, iSubFragmentEnd);

            // if the voice was killed in this subfragment, or if the
            // filter EG is finished, switch EG1 to fade out stage
            if ((itKillEvent && killPos <= iSubFragmentEnd) ||
                (SYNTHESIS_MODE_GET_FILTER(SynthesisMode) &&
                 EG2.getSegmentType() == gig::EGADSR::segment_end)) {
                pEG1->enterFadeOutStage();
                itKillEvent = Pool<Event>::Iterator();
            }

            // process envelope generators
            switch (pEG1->getSegmentType()) {
                case EG::segment_lin:
                    fFinalVolume *= pEG1->processLin();
                    break;
                case EG::segment_exp:
                    fFinalVolume *= pEG1->processExp();
                    break;
                case EG::segment_end:
                    fFinalVolume *= pEG1->getLevel();
                    break; // noop
                case EG::segment_pow:
                    fFinalVolume *= pEG1->processPow();
                    break;
            }
            switch (EG2.getSegmentType()) {
                case gig::EGADSR::segment_lin:
                    fFinalCutoff *= EG2.processLin();
                    break;
                case gig::EGADSR::segment_exp:
                    fFinalCutoff *= EG2.processExp();
                    break;
                case gig::EGADSR::segment_end:
                    fFinalCutoff *= EG2.getLevel();
                    break; // noop
            }
            if (EG3.active()) finalSynthesisParameters.fFinalPitch *= EG3.render();

            // process low frequency oscillators
            if (bLFO1Enabled) fFinalVolume *= (1.0f - pLFO1->render());
            if (bLFO2Enabled) fFinalCutoff *= pLFO2->render();
            if (bLFO3Enabled) finalSynthesisParameters.fFinalPitch *= RTMath::CentsToFreqRatio(pLFO3->render());

            // limit the pitch so we don't read outside the buffer
            finalSynthesisParameters.fFinalPitch = RTMath::Min(finalSynthesisParameters.fFinalPitch, float(1 << CONFIG_MAX_PITCH));

            // if filter enabled then update filter coefficients
            if (SYNTHESIS_MODE_GET_FILTER(SynthesisMode)) {
                finalSynthesisParameters.filterLeft.SetParameters(fFinalCutoff, fFinalResonance, GetEngine()->SampleRate);
                finalSynthesisParameters.filterRight.SetParameters(fFinalCutoff, fFinalResonance, GetEngine()->SampleRate);
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
            if (pEG1->getSegmentType() == EG::segment_end) break;

            const double newPos = Pos + (iSubFragmentEnd - i) * finalSynthesisParameters.fFinalPitch;

            // increment envelopes' positions
            if (pEG1->active()) {

                // if sample has a loop and loop start has been reached in this subfragment, send a special event to EG1 to let it finish the attack hold stage
                if (SmplInfo.HasLoops && Pos <= SmplInfo.LoopStart && SmplInfo.LoopStart < newPos) {
                    pEG1->update(EG::event_hold_end, GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                }

                pEG1->increment(1);
                if (!pEG1->toStageEndLeft()) pEG1->update(EG::event_stage_end, GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            }
            if (EG2.active()) {
                EG2.increment(1);
                if (!EG2.toStageEndLeft()) EG2.update(gig::EGADSR::event_stage_end, GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
            }
            EG3.increment(1);
            if (!EG3.toEndLeft()) EG3.update(); // neutralize envelope coefficient if end reached

            Pos = newPos;
            i = iSubFragmentEnd;
        }
    }

    /**
     * Process given list of MIDI control change and pitch bend events for
     * the given time.
     *
     * @param itEvent - iterator pointing to the next event to be processed
     * @param End     - youngest time stamp where processing should be stopped
     */
    void AbstractVoice::processCCEvents(RTList<Event>::Iterator& itEvent, uint End) {
        for (; itEvent && itEvent->FragmentPos() <= End; ++itEvent) {
            if (itEvent->Type == Event::type_control_change && itEvent->Param.CC.Controller) { // if (valid) MIDI control change event
                if (itEvent->Param.CC.Controller == VCFCutoffCtrl.controller) {
                    ProcessCutoffEvent(itEvent);
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
                if (itEvent->Param.CC.Controller == 7) { // volume
                    VolumeSmoother.update(AbstractEngine::VolumeCurve[itEvent->Param.CC.Value]);
                } else if (itEvent->Param.CC.Controller == 10) { // panpot
                    PanLeftSmoother.update(AbstractEngine::PanCurve[128 - itEvent->Param.CC.Value]);
                    PanRightSmoother.update(AbstractEngine::PanCurve[itEvent->Param.CC.Value]);
                }
            } else if (itEvent->Type == Event::type_pitchbend) { // if pitch bend event
                processPitchEvent(itEvent);
            }

            ProcessCCEvent(itEvent);
        }
    }

    void AbstractVoice::processPitchEvent(RTList<Event>::Iterator& itEvent) {
        Pitch.PitchBend = RTMath::CentsToFreqRatio(itEvent->Param.Pitch.Pitch * Pitch.PitchBendRange);
    }

    void AbstractVoice::processResonanceEvent(RTList<Event>::Iterator& itEvent) {
        // convert absolute controller value to differential
        const int ctrldelta = itEvent->Param.CC.Value - VCFResonanceCtrl.value;
        VCFResonanceCtrl.value = itEvent->Param.CC.Value;
        const float resonancedelta = (float) ctrldelta;
        fFinalResonance += resonancedelta;
        // needed for initialization of parameter
        VCFResonanceCtrl.fvalue = itEvent->Param.CC.Value;
    }

    /**
     * Process given list of MIDI note on, note off and sustain pedal events
     * for the given time.
     *
     * @param itEvent - iterator pointing to the next event to be processed
     * @param End     - youngest time stamp where processing should be stopped
     */
    void AbstractVoice::processTransitionEvents(RTList<Event>::Iterator& itEvent, uint End) {
        for (; itEvent && itEvent->FragmentPos() <= End; ++itEvent) {
            if (Type != Voice::type_release_trigger) {

                if (itEvent->Type == Event::type_release) {
                    EnterReleaseStage();
                } else if (itEvent->Type == Event::type_cancel_release) {
                    pEG1->update(EG::event_cancel_release, GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                    EG2.update(gig::EGADSR::event_cancel_release, GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
                }
            }
        }
    }

    /**
     * Process given list of events aimed at all voices in a key group.
     *
     * @param itEvent - iterator pointing to the next event to be processed
     * @param End     - youngest time stamp where processing should be stopped
     */
    void AbstractVoice::processGroupEvents(RTList<Event>::Iterator& itEvent, uint End) {
        for (; itEvent && itEvent->FragmentPos() <= End; ++itEvent) {
            ProcessGroupEvent(itEvent);
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
    void AbstractVoice::UpdatePortamentoPos(Pool<Event>::Iterator& itNoteOffEvent) {
        const float fFinalEG3Level = EG3.level(itNoteOffEvent->FragmentPos());
        pEngineChannel->PortamentoPos = (float) MIDIKey + RTMath::FreqRatioToCents(fFinalEG3Level) * 0.01f;
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
    void AbstractVoice::Kill(Pool<Event>::Iterator& itKillEvent) {
        #if CONFIG_DEVMODE
        if (!itKillEvent) dmsg(1,("AbstractVoice::Kill(): ERROR, !itKillEvent !!!\n"));
        if (itKillEvent && !itKillEvent.isValid()) dmsg(1,("AbstractVoice::Kill(): ERROR, itKillEvent invalid !!!\n"));
        #endif // CONFIG_DEVMODE

        if (itTriggerEvent && itKillEvent->FragmentPos() <= itTriggerEvent->FragmentPos()) return;
        this->itKillEvent = itKillEvent;
    }

    Voice::PitchInfo AbstractVoice::CalculatePitchInfo(int PitchBend) {
        PitchInfo pitch;
        double pitchbasecents = InstrInfo.FineTune + RgnInfo.FineTune + GetEngine()->ScaleTuning[MIDIKey % 12];

        // GSt behaviour: maximum transpose up is 40 semitones. If
        // MIDI key is more than 40 semitones above unity note,
        // the transpose is not done.
        if (!SmplInfo.Unpitched && (MIDIKey - (int) RgnInfo.UnityNote) < 40) pitchbasecents += (MIDIKey - (int) RgnInfo.UnityNote) * 100;

        pitch.PitchBase = RTMath::CentsToFreqRatioUnlimited(pitchbasecents) * (double(SmplInfo.SampleRate) / double(GetEngine()->SampleRate));
        pitch.PitchBendRange = 1.0 / 8192.0 * 100.0 * InstrInfo.PitchbendRange;
        pitch.PitchBend = RTMath::CentsToFreqRatio(PitchBend * pitch.PitchBendRange);

        return pitch;
    }

    double AbstractVoice::CalculateVolume(double velocityAttenuation) {
        // For 16 bit samples, we downscale by 32768 to convert from
        // int16 value range to DSP value range (which is
        // -1.0..1.0). For 24 bit, we downscale from int32.
        float volume = velocityAttenuation / (SmplInfo.BitDepth == 16 ? 32768.0f : 32768.0f * 65536.0f);

        volume *= GetSampleAttenuation() * pEngineChannel->GlobalVolume * GLOBAL_VOLUME;

        // the volume of release triggered samples depends on note length
        if (Type == Voice::type_release_trigger) {
            float noteLength = float(GetEngine()->FrameTime + Delay -
                GetNoteOnTime(MIDIKey) ) / GetEngine()->SampleRate;

            volume *= GetReleaseTriggerAttenuation(noteLength);
        }

        return volume;
    }

    float AbstractVoice::GetReleaseTriggerAttenuation(float noteLength) {
        return 1 - RgnInfo.ReleaseTriggerDecay * noteLength;
    }

    void AbstractVoice::EnterReleaseStage() {
        pEG1->update(EG::event_release, GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
        EG2.update(gig::EGADSR::event_release, GetEngine()->SampleRate / CONFIG_DEFAULT_SUBFRAGMENT_SIZE);
    }

} // namespace LinuxSampler
