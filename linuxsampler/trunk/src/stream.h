/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner                                   *
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

#ifndef __STREAM_H__
#define __STREAM_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <asm/page.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "global.h"
#include "ringbuffer.h"
#include "gig.h"
	
class Stream {
    public:
        // Member Types
        typedef uint32_t OrderID_t;
        typedef uint32_t Handle; ///< unique identifier of a relationship between one stream and a consumer (Voice)
        enum state_t {           ///< streams go through severe cyclic state transition (unused->active->end->unused->...)
            state_unused,        ///< stream is not in use, thus can still be launched
            state_active,        ///< stream provides data in it's buffer to be read and hasn't reached the end yet (this is the usual case)
            state_end            ///< stream end reached but still providing data in it's buffer to be read (after the client read all remaining data from the stream buffer, state will change automatically to state_unused)
        };
        struct reference_t {     ///< Defines the current relationship between the stream and a client (voice).
            OrderID_t OrderID;   ///< Unique identifier that identifies the creation order of a stream requested by a voice.
            Handle    hStream;   ///< Unique identifier of the relationship between stream and client.
            state_t   State;     ///< Current state of the stream that will be pretended to the client (the actual state of the stream might differ though, because the stream might already be in use by another client).
            Stream*   pStream;   ///< Points to the assigned and activated stream or is NULL if the disk thread hasn't launched a stream yet.
        };

        // Methods
        Stream(uint BufferSize, uint BufferWrapElements);
       ~Stream();
        int  ReadAhead(unsigned long SampleCount);
        void WriteSilence(unsigned long SilenceSampleWords);

        inline int GetReadSpace() {
            return (pRingBuffer && State == state_active) ? pRingBuffer->read_space()  : 0;
        }

        inline int GetWriteSpace() {
            return (pRingBuffer && State == state_active) ? pRingBuffer->write_space() : 0;
        }

        inline int GetWriteSpaceToEnd() {
            return (pRingBuffer && State == state_active) ? pRingBuffer->write_space_to_end_with_wrap() : 0;
        }

        // adjusts the write space to avoid buffer boundaries which would lead to the wrap space
        // within the buffer (needed for interpolation) getting filled only partially
        // for more infos see the docs in ringbuffer.h at adjust_write_space_to_avoid_boundary()
        inline int AdjustWriteSpaceToAvoidBoundary(int cnt, int capped_cnt) {
          return pRingBuffer->adjust_write_space_to_avoid_boundary(cnt, capped_cnt);
        }

        inline sample_t* GetReadPointer() {
            return pRingBuffer->get_read_ptr();
        }

        // gets the current read_ptr within the ringbuffer
        inline sample_t* GetReadPtr(void) {
            return pRingBuffer->get_read_ptr();
        }

        inline void IncrementReadPos(uint Count)  {
            uint leftspace = pRingBuffer->read_space();
            pRingBuffer->increment_read_ptr(Min(Count, leftspace));
            if (State == state_end && Count >= leftspace) {
                Reset(); // quit relation between consumer (voice) and stream and reset stream right after
            }
        }

        // Static Method
        inline static uint       GetUnusedStreams() { return UnusedStreams; }
    protected:
        // Methods
        void                     Launch(Stream::Handle hStream, reference_t* pExportReference, gig::Sample* pSample, unsigned long SampleOffset);
        inline void              Kill()      { pExportReference = NULL; Reset(); } ///< Will be called by disk thread after a 'deletion' command from the audio thread (within the voice class)
        inline Stream::Handle    GetHandle() { return hThis; }
        inline Stream::state_t   GetState()  { return State; }
        friend class DiskThread; // only the disk thread should be able to launch and most important kill a disk stream to avoid race conditions
    private:
        // Attributes
        reference_t*             pExportReference;
        state_t                  State;
        Stream::Handle           hThis;
        gig::Sample*             pSample;
        unsigned long            SampleOffset;
        RingBuffer<sample_t>*    pRingBuffer;

        // Static Attributes
        static uint              UnusedStreams; //< Reflects how many stream objects of all stream instances are currently not in use.

        // Methods
        inline void Reset() {
            pSample      = NULL;
            SampleOffset = 0;
            hThis        = 0;
            pRingBuffer->init(); // reset ringbuffer
            if (State != state_unused) {
                // we can't do 'SetPos(state_unused)' here, due to possible race conditions)
                if (pExportReference) {
                    pExportReference->State = state_unused;
                    pExportReference        = NULL;
                }
                State = state_unused;
                UnusedStreams++;
            }
        }
        inline void SetState(state_t State) {
            if (pExportReference) pExportReference->State = State;
            this->State = State;
        }
        inline long Min(long a, long b) { return (a < b) ? a : b; }
};

#endif // __STREAM_H__
