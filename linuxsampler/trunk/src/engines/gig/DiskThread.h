/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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

#ifndef __LS_GIG_DISKTHREAD_H__
#define __LS_GIG_DISKTHREAD_H__

#include "../../common/global.h"

#include <gig.h>

#include "../../common/Thread.h"
#include "../../common/RingBuffer.h"
#include "Stream.h"
#include "Voice.h"

namespace LinuxSampler { namespace gig {

    int CompareStreamWriteSpace(const void* a, const void* b);

    class DiskThread : public Thread {
        public:
            // Methods
            DiskThread(uint BufferWrapElements);
            virtual ~DiskThread();
            void    Reset();
            String  GetBufferFillBytes();
            String  GetBufferFillPercentage();
            int     OrderNewStream(Stream::reference_t* pStreamRef, ::gig::Sample* pSample, unsigned long SampleOffset, bool DoLoop);
            int     OrderDeletionOfStream(Stream::reference_t* pStreamRef);
            Stream* AskForCreatedStream(Stream::OrderID_t StreamOrderID);

            // the number of streams currently in usage
            // printed on the console the main thread (along with the active voice count)
            int ActiveStreamCount;
            int ActiveStreamCountMax;

        protected:
            ::gig::buffer_t DecompressionBuffer; ///< Used for thread safe streaming.

            int Main(); ///< Implementation of virtual method from class Thread

            friend class Stream;
        private:
            // Private Types
            struct create_command_t {
                Stream::OrderID_t    OrderID;
                Stream::Handle       hStream;
                Stream::reference_t* pStreamRef;
                ::gig::Sample*       pSample;
                unsigned long        SampleOffset;
                bool                 DoLoop;
            };
            struct delete_command_t {
                Stream*           pStream;
                Stream::Handle    hStream;
                Stream::OrderID_t OrderID;
            };

            // Attributes
            bool                           IsIdle;
            uint                           Streams;
            RingBuffer<create_command_t>*  CreationQueue;                          ///< Contains commands to create streams
            RingBuffer<delete_command_t>*  DeletionQueue;                          ///< Contains commands to delete streams
            RingBuffer<Stream::Handle>*    GhostQueue;                             ///< Contains handles to streams that are not used anymore and weren't deletable immediately
            unsigned int                   RefillStreamsPerRun;                    ///< How many streams should be refilled in each loop run
            Stream*                        pStreams[CONFIG_MAX_STREAMS];            ///< Contains all disk streams (wether used or unused)
            Stream*                        pCreatedStreams[CONFIG_MAX_STREAMS + 1]; ///< This is where the voice (audio thread) picks up it's meanwhile hopefully created disk stream.
            static Stream*                 SLOT_RESERVED;                          ///< This value is used to mark an entry in pCreatedStreams[] as reserved.

            // Methods
            void                           CreateStream(create_command_t& Command);
            void                           DeleteStream(delete_command_t& Command);
            void                           RefillStreams();
            Stream::Handle                 CreateHandle();
            Stream::OrderID_t              CreateOrderID();
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_DISKTHREAD_H__
