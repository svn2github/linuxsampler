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
#include "../../common/RTELMemoryPool.h"
#include "../../drivers/audio/AudioOutputDevice.h"
#include "../../lib/fileloader/libgig/gig.h"
#include "../common/BiquadFilter.h"
#include "Engine.h"
#include "Stream.h"
#include "DiskThread.h"

#include "EGDecay.h"
#include "Filter.h"
#include "../common/LFO.h"

#define USE_LINEAR_INTERPOLATION	0  ///< set to 0 if you prefer cubic interpolation (slower, better quality)
#define ENABLE_FILTER			1  ///< if set to 0 then filter (VCF) code is ignored on compile time
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
            // Attributes
            int          MIDIKey;      ///< MIDI key number of the key that triggered the voice
            DiskThread*  pDiskThread;  ///< Pointer to the disk thread, to be able to order a disk stream and later to delete the stream again

            // Methods
            Voice();
           ~Voice();
            void Kill();
            void Render(uint Samples);
            void Reset();
            void SetOutput(AudioOutputDevice* pAudioOutputDevice);
            void SetEngine(Engine* pEngine);
            int  Trigger(Event* pNoteOnEvent, int PitchBend, ::gig::Instrument* pInstrument, int iLayer = 0);
            inline bool IsActive() { return Active; }
        private:
            // Types
            enum playback_state_t {
                playback_state_ram,
                playback_state_disk,
                playback_state_end
            };

            // Attributes
            gig::Engine*                pEngine;            ///< Pointer to the sampler engine, to be able to access the event lists.
            float                       Volume;             ///< Volume level of the voice
            float                       CrossfadeVolume;    ///< Current attenuation level caused by a crossfade (only if a crossfade is defined of course)
            double                      Pos;                ///< Current playback position in sample
            double                      PitchBase;          ///< Basic pitch depth, stays the same for the whole life time of the voice
            double                      PitchBend;          ///< Current pitch value of the pitchbend wheel
            ::gig::Sample*              pSample;            ///< Pointer to the sample to be played back
            ::gig::Region*              pRegion;            ///< Pointer to the articulation information of the respective keyboard region of this voice
            ::gig::DimensionRegion*     pDimRgn;            ///< Pointer to the articulation information of current dimension region of this voice
            bool                        Active;             ///< If this voice object is currently in usage
            playback_state_t            PlaybackState;      ///< When a sample will be triggered, it will be first played from RAM cache and after a couple of sample points it will switch to disk streaming and at the end of a disk stream we have to add null samples, so the interpolator can do it's work correctly
            bool                        DiskVoice;          ///< If the sample is very short it completely fits into the RAM cache and doesn't need to be streamed from disk, in that case this flag is set to false
            Stream::reference_t         DiskStreamRef;      ///< Reference / link to the disk stream
            unsigned long               MaxRAMPos;          ///< The upper allowed limit (not actually the end) in the RAM sample cache, after that point it's not safe to chase the interpolator another time over over the current cache position, instead we switch to disk then.
            bool                        RAMLoop;            ///< If this voice has a loop defined which completely fits into the cached RAM part of the sample, in this case we handle the looping within the voice class, else if the loop is located in the disk stream part, we let the disk stream handle the looping
            int                         LoopCyclesLeft;     ///< In case there is a RAMLoop and it's not an endless loop; reflects number of loop cycles left to be passed
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
            Event*                      pTriggerEvent;      ///< First event on the key's list the voice should process (only needed for the first audio fragment in which voice was triggered, after that it will be set to NULL).

            // Static Methods
            static float CalculateFilterCutoffCoeff();
            static int   CalculateFilterUpdateMask();

            // Methods
            void        ProcessEvents(uint Samples);
            #if ENABLE_FILTER
            void        CalculateBiquadParameters(uint Samples);
            #endif // ENABLE_FILTER
            void        Interpolate(uint Samples, sample_t* pSrc, uint Skip);
            void        InterpolateAndLoop(uint Samples, sample_t* pSrc, uint Skip);
            inline void InterpolateOneStep_Stereo(sample_t* pSrc, int& i, float& effective_volume, float& pitch, biquad_param_t& bq_base, biquad_param_t& bq_main) {
                int   pos_int   = RTMath::DoubleToInt(this->Pos);  // integer position
                float pos_fract = this->Pos - pos_int;             // fractional part of position
                pos_int <<= 1;

                #if USE_LINEAR_INTERPOLATION
                    #if ENABLE_FILTER
                        // left channel
                        pEngine->pOutputLeft[i]    += this->FilterLeft.Apply(&bq_base, &bq_main, effective_volume * (pSrc[pos_int]   + pos_fract * (pSrc[pos_int+2] - pSrc[pos_int])));
                        // right channel
                        pEngine->pOutputRight[i++] += this->FilterRight.Apply(&bq_base, &bq_main, effective_volume * (pSrc[pos_int+1] + pos_fract * (pSrc[pos_int+3] - pSrc[pos_int+1])));
                    #else // no filter
                        // left channel
                        pEngine->pOutputLeft[i]    += effective_volume * (pSrc[pos_int]   + pos_fract * (pSrc[pos_int+2] - pSrc[pos_int]));
                        // right channel
                        pEngine->pOutputRight[i++] += effective_volume * (pSrc[pos_int+1] + pos_fract * (pSrc[pos_int+3] - pSrc[pos_int+1]));
                    #endif // ENABLE_FILTER
                #else // polynomial interpolation
                    // calculate left channel
                    float xm1 = pSrc[pos_int];
                    float x0  = pSrc[pos_int+2];
                    float x1  = pSrc[pos_int+4];
                    float x2  = pSrc[pos_int+6];
                    float a   = (3.0f * (x0 - x1) - xm1 + x2) * 0.5f;
                    float b   = 2.0f * x1 + xm1 - (5.0f * x0 + x2) * 0.5f;
                    float c   = (x1 - xm1) * 0.5f;
                    #if ENABLE_FILTER
                        pEngine->pOutputLeft[i] += this->FilterLeft.Apply(&bq_base, &bq_main, effective_volume * ((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0));
                    #else // no filter
                        pEngine->pOutputLeft[i] += effective_volume * ((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0);
                    #endif // ENABLE_FILTER

                    //calculate right channel
                    xm1 = pSrc[pos_int+1];
                    x0  = pSrc[pos_int+3];
                    x1  = pSrc[pos_int+5];
                    x2  = pSrc[pos_int+7];
                    a   = (3.0f * (x0 - x1) - xm1 + x2) * 0.5f;
                    b   = 2.0f * x1 + xm1 - (5.0f * x0 + x2) * 0.5f;
                    c   = (x1 - xm1) * 0.5f;
                    #if ENABLE_FILTER
                        pEngine->pOutputRight[i++] += this->FilterRight.Apply(&bq_base, &bq_main, effective_volume * ((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0));
                    #else // no filter
                        pEngine->pOutputRight[i++] += effective_volume * ((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0);
                    #endif // ENABLE_FILTER
                #endif // USE_LINEAR_INTERPOLATION

                this->Pos += pitch;
            }

            inline void InterpolateOneStep_Mono(sample_t* pSrc, int& i, float& effective_volume, float& pitch,  biquad_param_t& bq_base, biquad_param_t& bq_main) {
                int   pos_int   = RTMath::DoubleToInt(this->Pos);  // integer position
                float pos_fract = this->Pos - pos_int;             // fractional part of position

                #if USE_LINEAR_INTERPOLATION
                    float sample_point  = effective_volume * (pSrc[pos_int] + pos_fract * (pSrc[pos_int+1] - pSrc[pos_int]));
                #else // polynomial interpolation
                    float xm1 = pSrc[pos_int];
                    float x0  = pSrc[pos_int+1];
                    float x1  = pSrc[pos_int+2];
                    float x2  = pSrc[pos_int+3];
                    float a   = (3.0f * (x0 - x1) - xm1 + x2) * 0.5f;
                    float b   = 2.0f * x1 + xm1 - (5.0f * x0 + x2) * 0.5f;
                    float c   = (x1 - xm1) * 0.5f;
                    float sample_point = effective_volume * ((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0);
                #endif // USE_LINEAR_INTERPOLATION

                #if ENABLE_FILTER
                    sample_point = this->FilterLeft.Apply(&bq_base, &bq_main, sample_point);
                #endif // ENABLE_FILTER

                pEngine->pOutputLeft[i]    += sample_point;
                pEngine->pOutputRight[i++] += sample_point;

                this->Pos += pitch;
            }

            inline float CrossfadeAttenuation(uint8_t& CrossfadeControllerValue) {
                return (CrossfadeControllerValue <= pDimRgn->Crossfade.in_start)  ? 0.0f
                     : (CrossfadeControllerValue < pDimRgn->Crossfade.in_end)     ? float(CrossfadeControllerValue - pDimRgn->Crossfade.in_start) / float(pDimRgn->Crossfade.in_end - pDimRgn->Crossfade.in_start)
                     : (CrossfadeControllerValue <= pDimRgn->Crossfade.out_start) ? 1.0f
                     : (CrossfadeControllerValue < pDimRgn->Crossfade.out_end)    ? float(CrossfadeControllerValue - pDimRgn->Crossfade.out_start) / float(pDimRgn->Crossfade.out_end - pDimRgn->Crossfade.out_start)
                     : 0.0f;
            }

            inline float Constrain(float ValueToCheck, float Min, float Max) {
                if      (ValueToCheck > Max) ValueToCheck = Max;
                else if (ValueToCheck < Min) ValueToCheck = Min;
                return ValueToCheck;
            }
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_VOICE_H__
