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

#ifndef __LS_GIG_STREAM_H__
#define __LS_GIG_STREAM_H__

#include "../../common/global.h"

#include <gig.h>

#include "../../common/RingBuffer.h"

namespace LinuxSampler { namespace gig {

    /** @brief Buffered Disk Stream
     *
     * This encapsulation of a disk stream uses a ring buffer to allow
     * thread safe refilling the stream's buffer with one thread (disk
     * thread) and actual use / extraction of the audio data from the
     * stream's buffer with another thread (audio thread).
     */
    class Stream {
        public:
            // Member Types
            typedef uint32_t OrderID_t;
            typedef uint32_t Handle; ///< unique identifier of a relationship between one stream and a consumer (Voice)
            enum { INVALID_HANDLE = 0 };
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
            Stream( ::gig::buffer_t* pDecompressionBuffer, uint BufferSize, uint BufferWrapElements);
            virtual ~Stream();
            int  ReadAhead(unsigned long SampleCount);
            void WriteSilence(unsigned long SilenceSampleWords);

            inline int GetReadSpace() {
                return (pRingBuffer && State != state_unused) ? pRingBuffer->read_space() / BytesPerSample : 0;
            }

            inline int GetWriteSpace() {
                return (pRingBuffer && State == state_active) ? pRingBuffer->write_space() / BytesPerSample : 0;
            }

            inline int GetWriteSpaceToEnd() {
                return (pRingBuffer && State == state_active) ? pRingBuffer->write_space_to_end_with_wrap() / BytesPerSample : 0;
            }

            // adjusts the write space to avoid buffer boundaries which would lead to the wrap space
            // within the buffer (needed for interpolation) getting filled only partially
            // for more infos see the docs in ringbuffer.h at adjust_write_space_to_avoid_boundary()
            inline int AdjustWriteSpaceToAvoidBoundary(int cnt, int capped_cnt) {
              return pRingBuffer->adjust_write_space_to_avoid_boundary(cnt * BytesPerSample, capped_cnt * BytesPerSample) / BytesPerSample;
            }

            // gets the current read_ptr within the ringbuffer
            inline uint8_t* GetReadPtr(void) {
                return pRingBuffer->get_read_ptr();
            }

            inline void IncrementReadPos(uint Count)  {
                Count *= BytesPerSample;
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
            void                     Launch(Stream::Handle hStream, reference_t* pExportReference, ::gig::DimensionRegion* pDimRgn, unsigned long SampleOffset, bool DoLoop);
            inline void              Kill()      { pExportReference = NULL; Reset(); } ///< Will be called by disk thread after a 'deletion' command from the audio thread (within the voice class)
            inline Stream::Handle    GetHandle() { return hThis; }
            inline Stream::state_t   GetState()  { return State; }
            friend class DiskThread; // only the disk thread should be able to launch and most important kill a disk stream to avoid race conditions
        private:
            // Attributes
            reference_t*             pExportReference;
            state_t                  State;
            Stream::Handle           hThis;
            unsigned long            SampleOffset;
            ::gig::DimensionRegion*  pDimRgn;
            ::gig::playback_state_t  PlaybackState;
            RingBuffer<uint8_t,false>* pRingBuffer;
            bool                     DoLoop;
            ::gig::buffer_t*         pDecompressionBuffer;
            int                      BytesPerSample;

            // Static Attributes
            static uint              UnusedStreams; //< Reflects how many stream objects of all stream instances are currently not in use.
            static uint              TotalStreams; //< Reflects how many stream objects currently exist.

            // Methods
            inline void Reset() {
                SampleOffset                   = 0;
                pDimRgn                        = NULL;
                PlaybackState.position         = 0;
                PlaybackState.reverse          = false;
                hThis                          = 0;
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

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_STREAM_H__
