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

#ifndef __LS_GIG_VOICE_H__
#define __LS_GIG_VOICE_H__

#include "../../common/global.h"

#if DEBUG_HEADERS
# warning Voice.h included
#endif // DEBUG_HEADERS

#include "../../common/RTMath.h"
#include "../../common/RingBuffer.h"
#include "../../common/Pool.h"
#include "../../drivers/audio/AudioOutputDevice.h"
#include "../../lib/fileloader/libgig/gig.h"
#include "../common/BiquadFilter.h"
#include "Engine.h"
#include "Stream.h"
#include "DiskThread.h"

#include "EGDecay.h"
#include "Filter.h"
#include "../common/LFO.h"

#define FILTER_UPDATE_PERIOD		64 ///< amount of sample points after which filter parameters (cutoff, resonance) are going to be updated (higher value means less CPU load, but also worse parameter resolution, this value will be aligned to a power of two)
#define FORCE_FILTER_USAGE		0  ///< if set to 1 then filter is always used, if set to 0 filter is used only in case the instrument file defined one
#define FILTER_CUTOFF_MAX		10000.0f ///< maximum cutoff frequency (10kHz)
#define FILTER_CUTOFF_MIN		100.0f   ///< minimum cutoff frequency (100Hz)

// Uncomment following line to override external cutoff controller
//#define OVERRIDE_FILTER_CUTOFF_CTRL	1  ///< set to an arbitrary MIDI control change controller (e.g. 1 for 'modulation wheel')

// Uncomment following line to override external resonance controller
//#define OVERRIDE_FILTER_RES_CTRL	91  ///< set to an arbitrary MIDI control change controller (e.g. 91 for 'effect 1 depth')

// Uncomment following line to override filter type
//#define OVERRIDE_FILTER_TYPE		::gig::vcf_type_lowpass  ///< either ::gig::vcf_type_lowpass, ::gig::vcf_type_bandpass or ::gig::vcf_type_highpass

namespace LinuxSampler { namespace gig {

    class Engine;
    class EGADSR;
    class VCAManipulator;
    class VCFCManipulator;
    class VCOManipulator;

    /// Reflects a MIDI controller
    struct midi_ctrl {
        uint8_t controller; ///< MIDI control change controller number
        uint8_t value;      ///< Current MIDI controller value
        float   fvalue;     ///< Transformed / effective value (e.g. volume level or filter cutoff frequency)
    };

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
            RTList<Voice>::Iterator itChildVoice; ///< Points to the next layer voice (if any). This field is currently only used by the voice stealing algorithm.

            // Methods
            Voice();
           ~Voice();
            void Kill(Pool<Event>::Iterator& itKillEvent);
            void Render(uint Samples);
            void Reset();
            void SetOutput(AudioOutputDevice* pAudioOutputDevice);
            void SetEngine(Engine* pEngine);
            int  Trigger(Pool<Event>::Iterator& itNoteOnEvent, int PitchBend, ::gig::Instrument* pInstrument, int iLayer, bool ReleaseTriggerVoice, bool VoiceStealing);
            inline bool IsActive() { return PlaybackState; }
        //private:
            // Types
            enum playback_state_t {
                playback_state_end  = 0,
                playback_state_ram  = 1,
                playback_state_disk = 2
            };

            // Attributes
            gig::Engine*                pEngine;            ///< Pointer to the sampler engine, to be able to access the event lists.
            float                       Volume;             ///< Volume level of the voice
            float                       PanLeft;
            float                       PanRight;
            float                       CrossfadeVolume;    ///< Current attenuation level caused by a crossfade (only if a crossfade is defined of course)
            double                      Pos;                ///< Current playback position in sample
            float                       PitchBase;          ///< Basic pitch depth, stays the same for the whole life time of the voice
            float                       PitchBend;          ///< Current pitch value of the pitchbend wheel
            ::gig::Sample*              pSample;            ///< Pointer to the sample to be played back
            ::gig::Region*              pRegion;            ///< Pointer to the articulation information of the respective keyboard region of this voice
            ::gig::DimensionRegion*     pDimRgn;            ///< Pointer to the articulation information of current dimension region of this voice
            playback_state_t            PlaybackState;      ///< When a sample will be triggered, it will be first played from RAM cache and after a couple of sample points it will switch to disk streaming and at the end of a disk stream we have to add null samples, so the interpolator can do it's work correctly
            bool                        DiskVoice;          ///< If the sample is very short it completely fits into the RAM cache and doesn't need to be streamed from disk, in that case this flag is set to false
            Stream::reference_t         DiskStreamRef;      ///< Reference / link to the disk stream
            int                         RealSampleWordsLeftToRead; ///< Number of samples left to read, not including the silence added for the interpolator
            unsigned long               MaxRAMPos;          ///< The upper allowed limit (not actually the end) in the RAM sample cache, after that point it's not safe to chase the interpolator another time over over the current cache position, instead we switch to disk then.
            bool                        RAMLoop;            ///< If this voice has a loop defined which completely fits into the cached RAM part of the sample, in this case we handle the looping within the voice class, else if the loop is located in the disk stream part, we let the disk stream handle the looping
            uint                        LoopCyclesLeft;     ///< In case there is a RAMLoop and it's not an endless loop; reflects number of loop cycles left to be passed
            uint                        Delay;              ///< Number of sample points the rendering process of this voice should be delayed (jitter correction), will be set to 0 after the first audio fragment cycle
            EGADSR*                     pEG1;               ///< Envelope Generator 1 (Amplification)
            EGADSR*                     pEG2;               ///< Envelope Generator 2 (Filter cutoff frequency)
            EGDecay*                    pEG3;               ///< Envelope Generator 3 (Pitch)
            Filter                      FilterLeft;
            Filter                      FilterRight;
            midi_ctrl                   VCFCutoffCtrl;
            midi_ctrl                   VCFResonanceCtrl;
            int                         FilterUpdateCounter; ///< Used to update filter parameters all FILTER_UPDATE_PERIOD samples
            static const float          FILTER_CUTOFF_COEFF;
            static const int            FILTER_UPDATE_MASK;
            VCAManipulator*             pVCAManipulator;
            VCFCManipulator*            pVCFCManipulator;
            VCOManipulator*             pVCOManipulator;
            LFO<gig::VCAManipulator>*   pLFO1;              ///< Low Frequency Oscillator 1 (Amplification)
            LFO<gig::VCFCManipulator>*  pLFO2;             ///< Low Frequency Oscillator 2 (Filter cutoff frequency)
            LFO<gig::VCOManipulator>*   pLFO3;              ///< Low Frequency Oscillator 3 (Pitch)
            Pool<Event>::Iterator       itTriggerEvent;      ///< First event on the key's list the voice should process (only needed for the first audio fragment in which voice was triggered, after that it will be set to NULL).
        //public: // FIXME: just made public for debugging (sanity check in Engine::RenderAudio()), should be changed to private before the final release
            Pool<Event>::Iterator       itKillEvent;         ///< Event which caused this voice to be killed
        //private:
            int                         SynthesisMode;

            // Static Methods
            static float CalculateFilterCutoffCoeff();
            static int   CalculateFilterUpdateMask();

            // Methods
            void KillImmediately();
            void ProcessEvents(uint Samples);
            void CalculateBiquadParameters(uint Samples);
            void Synthesize(uint Samples, sample_t* pSrc, uint Skip);

            inline float CrossfadeAttenuation(uint8_t& CrossfadeControllerValue) {
                float att = (!pDimRgn->Crossfade.out_end) ? CrossfadeControllerValue / 127.0f /* 0,0,0,0 means no crossfade defined */
                          : (CrossfadeControllerValue < pDimRgn->Crossfade.in_end) ?
                                ((CrossfadeControllerValue <= pDimRgn->Crossfade.in_start) ? 0.0f
                                : float(CrossfadeControllerValue - pDimRgn->Crossfade.in_start) / float(pDimRgn->Crossfade.in_end - pDimRgn->Crossfade.in_start))
                          : (CrossfadeControllerValue <= pDimRgn->Crossfade.out_start) ? 1.0f
                          : (CrossfadeControllerValue < pDimRgn->Crossfade.out_end) ? float(pDimRgn->Crossfade.out_end - CrossfadeControllerValue) / float(pDimRgn->Crossfade.out_end - pDimRgn->Crossfade.out_start)
                          : 0.0f;
                return pDimRgn->InvertAttenuationController ? 1 - att : att;
            }

            inline float Constrain(float ValueToCheck, float Min, float Max) {
                if      (ValueToCheck > Max) ValueToCheck = Max;
                else if (ValueToCheck < Min) ValueToCheck = Min;
                return ValueToCheck;
            }
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_VOICE_H__
