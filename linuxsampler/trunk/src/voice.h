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

#ifndef __VOICE_H__
#define __VOICE_H__

#include "global.h"
#include "diskthread.h"
#include "ringbuffer.h"
#include "stream.h"
#include "gig.h"
#include "eg_vca.h"

#define MAX_PITCH			4  //FIXME: at the moment in octaves, should be changed into semitones
#define USE_LINEAR_INTERPOLATION	1  ///< set to 0 if you prefer cubic interpolation (slower, better quality)

class Voice {
    public:
        // Attributes
        int      MIDIKey;          ///< MIDI key number of the key that triggered the voice
        Voice**  pSelfPtr;         ///< FIXME: hack to be able to remove the voice from the active voices list within the audio thread, ugly but fast
        uint     ReleaseVelocity;  ///< Reflects the release velocity value if a note-off command arrived for the voice.

        // Methods
        Voice(DiskThread* pDiskThread);
       ~Voice();
        void Kill();
        void Release();
        void Render(uint Samples);
        int  Trigger(int MIDIKey, uint8_t Velocity, gig::Instrument* Instrument);
        inline bool IsActive()                                              { return Active; }
        inline void SetOutputLeft(float* pOutput, uint MaxSamplesPerCycle)  { this->pOutputLeft  = pOutput; this->MaxSamplesPerCycle = MaxSamplesPerCycle; }
        inline void SetOutputRight(float* pOutput, uint MaxSamplesPerCycle) { this->pOutputRight = pOutput; this->MaxSamplesPerCycle = MaxSamplesPerCycle; }
    private:
        // Types
        enum playback_state_t {
            playback_state_ram,
            playback_state_disk,
            playback_state_end
        };

        // Attributes
        float                Volume;             ///< Volume level of the voice
        float*               pOutputLeft;        ///< Audio output buffer (left channel)
        float*               pOutputRight;       ///< Audio output buffer (right channel)
        uint                 MaxSamplesPerCycle; ///< Size of each audio output buffer
        double               Pos;                ///< Current playback position in sample
        double               CurrentPitch;       ///< Current pitch depth (number of sample points to move on with each render step)
        gig::Sample*         pSample;            ///< Pointer to the sample to be played back
        gig::Region*         pRegion;            ///< Pointer to the articulation information of the respective keyboard region of this voice
        bool                 Active;             ///< If this voice object is currently in usage
        playback_state_t     PlaybackState;      ///< When a sample will be triggered, it will be first played from RAM cache and after a couple of sample points it will switch to disk streaming and at the end of a disk stream we have to add null samples, so the interpolator can do it's work correctly
        bool                 DiskVoice;          ///< If the sample is very short it completely fits into the RAM cache and doesn't need to be streamed from disk, in that case this flag is set to false
        Stream::reference_t  DiskStreamRef;      ///< Reference / link to the disk stream
        unsigned long        MaxRAMPos;          ///< The upper allowed limit (not actually the end) in the RAM sample cache, after that point it's not safe to chase the interpolator another time over over the current cache position, instead we switch to disk then.
        bool                 RAMLoop;            ///< If this voice has a loop defined which completely fits into the cached RAM part of the sample, in this case we handle the looping within the voice class, else if the loop is located in the disk stream part, we let the disk stream handle the looping
        int                  LoopCyclesLeft;     ///< In case there is a RAMLoop and it's not an endless loop; reflects number of loop cycles left to be passed
        EG_VCA               EG1;

        // Static Attributes
        static DiskThread*   pDiskThread;        ///< Pointer to the disk thread, to be able to order a disk stream and later to delete the stream again

        // Methods
        void        Interpolate(uint Samples, sample_t* pSrc);
        void        InterpolateAndLoop(uint Samples, sample_t* pSrc);
        inline void InterpolateOneStep_Stereo(sample_t* pSrc, int& i, float& effective_volume) {
            int   pos_int   = double_to_int(this->Pos);  // integer position
            float pos_fract = this->Pos - pos_int;       // fractional part of position
            pos_int <<= 1;

            #if USE_LINEAR_INTERPOLATION
                // left channel
                this->pOutputLeft[i]    += effective_volume * (pSrc[pos_int]   + pos_fract * (pSrc[pos_int+2] - pSrc[pos_int]));
                // right channel
                this->pOutputRight[i++] += effective_volume * (pSrc[pos_int+1] + pos_fract * (pSrc[pos_int+3] - pSrc[pos_int+1]));
            #else // polynomial interpolation
                // calculate left channel
                float xm1 = pSrc[pos_int];
                float x0  = pSrc[pos_int+2];
                float x1  = pSrc[pos_int+4];
                float x2  = pSrc[pos_int+6];
                float a   = (3 * (x0 - x1) - xm1 + x2) / 2;
                float b   = 2 * x1 + xm1 - (5 * x0 + x2) / 2;
                float c   = (x1 - xm1) / 2;
                this->pOutputLeft[i] += effective_volume * ((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0);

                //calculate right channel
                xm1 = pSrc[pos_int+1];
                x0  = pSrc[pos_int+3];
                x1  = pSrc[pos_int+5];
                x2  = pSrc[pos_int+7];
                a   = (3 * (x0 - x1) - xm1 + x2) / 2;
                b   = 2 * x1 + xm1 - (5 * x0 + x2) / 2;
                c   = (x1 - xm1) / 2;
                this->pOutputRight[i++] += effective_volume * ((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0);
            #endif // USE_LINEAR_INTERPOLATION

            this->Pos += this->CurrentPitch;
        }
        inline void InterpolateOneStep_Mono(sample_t* pSrc, int& i, float& effective_volume) {
            int   pos_int   = double_to_int(this->Pos);  // integer position
            float pos_fract = this->Pos - pos_int;       // fractional part of position

            #if USE_LINEAR_INTERPOLATION
                float sample_point  = effective_volume * (pSrc[pos_int] + pos_fract * (pSrc[pos_int+1] - pSrc[pos_int]));
            #else // polynomial interpolation
                float xm1 = pSrc[pos_int];
                float x0  = pSrc[pos_int+1];
                float x1  = pSrc[pos_int+2];
                float x2  = pSrc[pos_int+3];
                float a   = (3 * (x0 - x1) - xm1 + x2) / 2;
                float b   = 2 * x1 + xm1 - (5 * x0 + x2) / 2;
                float c   = (x1 - xm1) / 2;
                float sample_point = effective_volume * ((((a * pos_fract) + b) * pos_fract + c) * pos_fract + x0);
            #endif // USE_LINEAR_INTERPOLATION

            this->pOutputLeft[i]    += sample_point;
            this->pOutputRight[i++] += sample_point;

            this->Pos += this->CurrentPitch;
        }
        inline int double_to_int(double f) {
            #if ARCH_X86
            int i;
            __asm__ ("fistl %0" : "=m"(i) : "st"(f - 0.5) );
            return i;
            #else
            return (int) f;
            #endif // ARCH_X86
        }
};

#endif // __VOICE_H__
