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

#ifndef __DISKTHREAD_H__
#define __DISKTHREAD_H__

#define REFILL_STREAMS_PER_RUN		4       ///< number of streams that should be refilled with each disk thread cycle
#define MIN_REFILL_SIZE			1024    ///< if no buffer was filled up more than this bottom limit, the disk thread will go to sleep
#define MAX_REFILL_SIZE			65536   ///< maximum of samples a buffer should be refilled in one cycle (256kB, as 16 bit stereo)
#define STREAM_BUFFER_SIZE		131072  ///< the diskstream ringbuffer size (256kB as sample_t is 16bit)
#define MAX_INPUT_STREAMS		100     ///< number of streams that should be allocated

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "global.h"
#include "thread.h"
#include "voice.h"
#include "ringbuffer.h"
#include "stream.h"

int CompareStreamWriteSpace(const void* a, const void* b);

class DiskThread : public Thread {
    public:
        // Methods
        DiskThread(uint BufferWrapElements);
       ~DiskThread();
        int     OrderNewStream(Stream::reference_t* pStreamRef, gig::Sample* pSample, unsigned long SampleOffset, bool DoLoop);
        int     OrderDeletionOfStream(Stream::reference_t* pStreamRef);
        Stream* AskForCreatedStream(Stream::OrderID_t StreamOrderID);

        // the number of streams currently in usage
        // printed on the console the main thread (along with the active voice count)
        int ActiveStreamCount;
        int ActiveStreamCountMax;

    protected:
        int Main(); ///< Implementation of virtual method from class Thread
    private:
        // Private Types
        struct create_command_t {
            Stream::OrderID_t    OrderID;
            Stream::Handle       hStream;
            Stream::reference_t* pStreamRef;
            gig::Sample*         pSample;
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
        Stream*                        pStreams[MAX_INPUT_STREAMS];            ///< Contains all disk streams (wether used or unused)
        Stream*                        pCreatedStreams[MAX_INPUT_STREAMS + 1]; ///< This is where the voice (audio thread) picks up it's meanwhile hopefully created disk stream.
        static Stream*                 SLOT_RESERVED;                          ///< This value is used to mark an entry in pCreatedStreams[] as reserved.

        // Methods
        void                           CreateStream(create_command_t& Command);
        void                           DeleteStream(delete_command_t& Command);
        void                           RefillStreams();
        Stream::Handle                 CreateHandle();
        Stream::OrderID_t              CreateOrderID();
};

#endif // __DISKTHREAD_H__
