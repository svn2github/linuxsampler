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

#define MAX_PITCH			4  //FIXME: at the moment in octaves, should be changed into semitones
#define USE_LINEAR_INTERPOLATION	1

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
        void RenderAudio();
        void Trigger(int MIDIKey, uint8_t Velocity, gig::Instrument* Instrument);
        inline bool IsActive()                                       { return Active; }
        inline void SetOutput(float* pOutput, uint OutputBufferSize) { this->pOutput = pOutput; this->OutputBufferSize = OutputBufferSize; }
    private:
        // Types
        enum playback_state_t {
            playback_state_ram,
            playback_state_disk,
            playback_state_end
        };

        // Attributes
        float*               pOutput;           ///< Audio output buffer
        uint                 OutputBufferSize;  ///< Fragment size of the audio output buffer
        double               Pos;
        double               CurrentPitch;
        gig::Sample*         pSample;
        gig::Region*         pRegion;
        bool                 Active;
        playback_state_t     PlaybackState;     ///< When a sample will be triggered, it will be first played from RAM cache and after a couple of sample points it will switch to disk streaming and at the end of a disk stream we have to add null samples, so the interpolator can do it's work correctly
        bool                 DiskVoice;         ///< If the sample is very short it completely fits into the RAM cache and doesn't need to be streamed from disk, in that case this flag is set to false
        Stream::reference_t  DiskStreamRef;
        unsigned long        MaxRAMPos;         ///< The upper allowed limit (not actually the end) in the RAM sample cache, after that point it's not safe to chase the interpolator another time over over the current cache position, instead we switch to disk then.

        // Static Attributes
        static DiskThread*   pDiskThread;

        // Methods
        void       Interpolate(sample_t* pSrc);
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
