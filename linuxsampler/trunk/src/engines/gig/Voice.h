/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
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

#ifndef __LS_GIG_VOICE_H__
#define __LS_GIG_VOICE_H__

#include "../../common/global.h"

#include <gig.h>

#include "../../common/RTMath.h"
#include "../../common/RingBuffer.h"
#include "../../common/Pool.h"
#include "../../drivers/audio/AudioOutputDevice.h"
#include "../common/BiquadFilter.h"
#include "Engine.h"
#include "EngineChannel.h"
#include "Stream.h"
#include "DiskThread.h"
#include "EGADSR.h"
#include "EGDecay.h"
#include "Filter.h"
#include "../common/LFOBase.h"
#include "SynthesisParam.h"
#include "SmoothVolume.h"

// include the appropriate (unsigned) triangle LFO implementation
#if CONFIG_UNSIGNED_TRIANG_ALGO == INT_MATH_SOLUTION
# include "../common/LFOTriangleIntMath.h"
#elif CONFIG_UNSIGNED_TRIANG_ALGO == INT_ABS_MATH_SOLUTION
# include "../common/LFOTriangleIntAbsMath.h"
#elif CONFIG_UNSIGNED_TRIANG_ALGO == DI_HARMONIC_SOLUTION
# include "../common/LFOTriangleDiHarmonic.h"
#else
# error "Unknown or no (unsigned) triangle LFO implementation selected!"
#endif

// include the appropriate (signed) triangle LFO implementation
#if CONFIG_SIGNED_TRIANG_ALGO == INT_MATH_SOLUTION
# include "../common/LFOTriangleIntMath.h"
#elif CONFIG_SIGNED_TRIANG_ALGO == INT_ABS_MATH_SOLUTION
# include "../common/LFOTriangleIntAbsMath.h"
#elif CONFIG_SIGNED_TRIANG_ALGO == DI_HARMONIC_SOLUTION
# include "../common/LFOTriangleDiHarmonic.h"
#else
# error "Unknown or no (signed) triangle LFO implementation selected!"
#endif

namespace LinuxSampler { namespace gig {

    class Engine;

    /// Reflects a MIDI controller
    struct midi_ctrl {
        uint8_t controller; ///< MIDI control change controller number
        uint8_t value;      ///< Current MIDI controller value
        float   fvalue;     ///< Transformed / effective value (e.g. volume level or filter cutoff frequency)
    };

    #if CONFIG_UNSIGNED_TRIANG_ALGO == INT_MATH_SOLUTION
    typedef LFOTriangleIntMath<range_unsigned> LFOUnsigned;
    #elif CONFIG_UNSIGNED_TRIANG_ALGO == INT_ABS_MATH_SOLUTION
    typedef LFOTriangleIntAbsMath<range_unsigned> LFOUnsigned;
    #elif CONFIG_UNSIGNED_TRIANG_ALGO == DI_HARMONIC_SOLUTION
    typedef LFOTriangleDiHarmonic<range_unsigned> LFOUnsigned;
    #endif

    #if CONFIG_SIGNED_TRIANG_ALGO == INT_MATH_SOLUTION
    typedef LFOTriangleIntMath<range_signed> LFOSigned;
    #elif CONFIG_SIGNED_TRIANG_ALGO == INT_ABS_MATH_SOLUTION
    typedef LFOTriangleIntAbsMath<range_signed> LFOSigned;
    #elif CONFIG_SIGNED_TRIANG_ALGO == DI_HARMONIC_SOLUTION
    typedef LFOTriangleDiHarmonic<range_signed> LFOSigned;
    #endif

    /** Gig Voice
     *
     * Renders a voice for the Gigasampler format.
     */
    class Voice {
        public:
            // Types
            enum type_t {
                type_normal,
                type_release_trigger_required,  ///< If the key of this voice will be released, it causes a release triggered voice to be spawned
                type_release_trigger            ///< Release triggered voice which cannot be killed by releasing its key
            };

            // Attributes
            type_t       Type;         ///< Voice Type
            int          MIDIKey;      ///< MIDI key number of the key that triggered the voice
            uint         KeyGroup;
            DiskThread*  pDiskThread;  ///< Pointer to the disk thread, to be able to order a disk stream and later to delete the stream again

            // Methods
            Voice();
            virtual ~Voice();
            void Kill(Pool<Event>::Iterator& itKillEvent);
            void Render(uint Samples);
            void Reset();
            void SetOutput(AudioOutputDevice* pAudioOutputDevice);
            void SetEngine(Engine* pEngine);
            int  Trigger(EngineChannel* pEngineChannel, Pool<Event>::Iterator& itNoteOnEvent, int PitchBend, ::gig::DimensionRegion* pDimRgn, type_t VoiceType, int iKeyGroup);
            inline bool IsActive() { return PlaybackState; }
            inline bool IsStealable() { return !itKillEvent && PlaybackState >= playback_state_ram; }
            void UpdatePortamentoPos(Pool<Event>::Iterator& itNoteOffEvent);

        //private:
            // Types
            enum playback_state_t {
                playback_state_end  = 0,
                playback_state_init = 1,
                playback_state_ram  = 2,
                playback_state_disk = 3
            };

            // Attributes
            EngineChannel*              pEngineChannel;
            Engine*                     pEngine;            ///< Pointer to the sampler engine, to be able to access the event lists.
            float                       VolumeLeft;         ///< Left channel volume. This factor is calculated when the voice is triggered and doesn't change after that.
            float                       VolumeRight;        ///< Right channel volume. This factor is calculated when the voice is triggered and doesn't change after that.
            SmoothVolume                CrossfadeSmoother;  ///< Crossfade volume, updated by crossfade CC events
            SmoothVolume                VolumeSmoother;     ///< Volume, updated by CC 7 (volume) events
            SmoothVolume                PanLeftSmoother;    ///< Left channel volume, updated by CC 10 (pan) events
            SmoothVolume                PanRightSmoother;   ///< Right channel volume, updated by CC 10 (pan) events
            double                      Pos;                ///< Current playback position in sample
            float                       PitchBase;          ///< Basic pitch depth, stays the same for the whole life time of the voice
            float                       PitchBend;          ///< Current pitch value of the pitchbend wheel
            float                       CutoffBase;         ///< Cutoff frequency before control change, EG and LFO are applied
            ::gig::Sample*              pSample;            ///< Pointer to the sample to be played back
            ::gig::DimensionRegion*     pDimRgn;            ///< Pointer to the articulation information of current dimension region of this voice
            playback_state_t            PlaybackState;      ///< When a sample will be triggered, it will be first played from RAM cache and after a couple of sample points it will switch to disk streaming and at the end of a disk stream we have to add null samples, so the interpolator can do it's work correctly
            bool                        DiskVoice;          ///< If the sample is very short it completely fits into the RAM cache and doesn't need to be streamed from disk, in that case this flag is set to false
            Stream::reference_t         DiskStreamRef;      ///< Reference / link to the disk stream
            int                         RealSampleWordsLeftToRead; ///< Number of samples left to read, not including the silence added for the interpolator
            unsigned long               MaxRAMPos;          ///< The upper allowed limit (not actually the end) in the RAM sample cache, after that point it's not safe to chase the interpolator another time over over the current cache position, instead we switch to disk then.
            bool                        RAMLoop;            ///< If this voice has a loop defined which completely fits into the cached RAM part of the sample, in this case we handle the looping within the voice class, else if the loop is located in the disk stream part, we let the disk stream handle the looping
            //uint                        LoopCyclesLeft;     ///< In case there is a RAMLoop and it's not an endless loop; reflects number of loop cycles left to be passed
            uint                        Delay;              ///< Number of sample points the rendering process of this voice should be delayed (jitter correction), will be set to 0 after the first audio fragment cycle
            EGADSR                      EG1;                ///< Envelope Generator 1 (Amplification)
            EGADSR                      EG2;                ///< Envelope Generator 2 (Filter cutoff frequency)
            EGDecay                     EG3;                ///< Envelope Generator 3 (Pitch)
            midi_ctrl                   VCFCutoffCtrl;
            midi_ctrl                   VCFResonanceCtrl;
            static const float          FILTER_CUTOFF_COEFF;
            LFOUnsigned*                pLFO1;               ///< Low Frequency Oscillator 1 (Amplification)
            LFOUnsigned*                pLFO2;               ///< Low Frequency Oscillator 2 (Filter cutoff frequency)
            LFOSigned*                  pLFO3;               ///< Low Frequency Oscillator 3 (Pitch)
            bool                        bLFO1Enabled;        ///< Should we use the Amplitude LFO for this voice?
            bool                        bLFO2Enabled;        ///< Should we use the Filter Cutoff LFO for this voice?
            bool                        bLFO3Enabled;        ///< Should we use the Pitch LFO for this voice?
            Pool<Event>::Iterator       itTriggerEvent;      ///< First event on the key's list the voice should process (only needed for the first audio fragment in which voice was triggered, after that it will be set to NULL).
        //public: // FIXME: just made public for debugging (sanity check in Engine::RenderAudio()), should be changed to private before the final release
            Pool<Event>::Iterator       itKillEvent;         ///< Event which caused this voice to be killed
        //private:
            int                         SynthesisMode;
            float                       fFinalCutoff;
            float                       fFinalResonance;
            SynthesisParam              finalSynthesisParameters;
            Loop                        loop;

            // Static Methods
            static float CalculateFilterCutoffCoeff();

            // Methods
            void KillImmediately();
            void ProcessEvents(uint Samples);
            void Synthesize(uint Samples, sample_t* pSrc, uint Skip);
            void processTransitionEvents(RTList<Event>::Iterator& itEvent, uint End);
            void processCCEvents(RTList<Event>::Iterator& itEvent, uint End);
            void processPitchEvent(RTList<Event>::Iterator& itEvent);
            void processCrossFadeEvent(RTList<Event>::Iterator& itEvent);
            void processCutoffEvent(RTList<Event>::Iterator& itEvent);
            void processResonanceEvent(RTList<Event>::Iterator& itEvent);

            inline uint8_t CrossfadeAttenuation(uint8_t& CrossfadeControllerValue) {
                uint8_t c = std::max(CrossfadeControllerValue, pDimRgn->AttenuationControllerThreshold);
                c = (!pDimRgn->Crossfade.out_end) ? c /* 0,0,0,0 means no crossfade defined */
                          : (c < pDimRgn->Crossfade.in_end) ?
                                ((c <= pDimRgn->Crossfade.in_start) ? 0
                                : 127 * (c - pDimRgn->Crossfade.in_start) / (pDimRgn->Crossfade.in_end - pDimRgn->Crossfade.in_start))
                          : (c <= pDimRgn->Crossfade.out_start) ? 127
                          : (c < pDimRgn->Crossfade.out_end) ? 127 * (pDimRgn->Crossfade.out_end - c) / (pDimRgn->Crossfade.out_end - pDimRgn->Crossfade.out_start)
                          : 0;
                return pDimRgn->InvertAttenuationController ? 127 - c : c;
            }

            inline float Constrain(float ValueToCheck, float Min, float Max) {
                if      (ValueToCheck > Max) ValueToCheck = Max;
                else if (ValueToCheck < Min) ValueToCheck = Min;
                return ValueToCheck;
            }
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_VOICE_H__
