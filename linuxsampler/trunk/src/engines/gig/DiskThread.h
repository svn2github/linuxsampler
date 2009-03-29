/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2009 Christian Schoenebeck                       *
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

#include "../../common/global_private.h"

#include <gig.h>

#include "../../common/Thread.h"
#include "../../common/RingBuffer.h"
#include "../../common/atomic.h"
#include "Stream.h"
#include "Voice.h"

namespace LinuxSampler { namespace gig {

    int CompareStreamWriteSpace(const void* a, const void* b);

    /** @brief Disk Reader Thread
     *
     * The disk reader thread is responsible for periodically refilling
     * disk streams in parallel to the audio thread's rendering process.
     *
     * There is also a function for releasing parts of instruments not
     * in use anymore (as this is not real time safe, the audio thread
     * cannot do it directly).
     */
    class DiskThread : public Thread {
        public:
            // Methods
            DiskThread(int MaxStreams, uint BufferWrapElements, InstrumentResourceManager* pInstruments);
            virtual ~DiskThread();
            void    Reset();
            String  GetBufferFillBytes();
            String  GetBufferFillPercentage();
            int     OrderNewStream(Stream::reference_t* pStreamRef, ::gig::DimensionRegion* pDimRgn, unsigned long SampleOffset, bool DoLoop);
            int     OrderDeletionOfStream(Stream::reference_t* pStreamRef, bool bRequestNotification = false);
            int     OrderDeletionOfDimreg(::gig::DimensionRegion* dimreg);
            Stream* AskForCreatedStream(Stream::OrderID_t StreamOrderID);
            Stream::Handle AskForDeletedStream();

            // the number of streams currently in usage
            // printed on the console the main thread (along with the active voice count)
            uint GetActiveStreamCount() { return atomic_read(&ActiveStreamCount); }
            void SetActiveStreamCount(uint Streams) { atomic_set(&ActiveStreamCount, Streams); }
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
                ::gig::DimensionRegion* pDimRgn;
                unsigned long        SampleOffset;
                bool                 DoLoop;
            };
            struct delete_command_t {
                Stream*           pStream;
                Stream::Handle    hStream;
                Stream::OrderID_t OrderID;
                bool              bNotify;
            };

            // Attributes
            bool                           IsIdle;
            uint                           Streams;
            RingBuffer<create_command_t,false>* CreationQueue;                      ///< Contains commands to create streams
            RingBuffer<delete_command_t,false>* DeletionQueue;                      ///< Contains commands to delete streams
            RingBuffer<delete_command_t,false>* GhostQueue;                         ///< Contains handles to streams that are not used anymore and weren't deletable immediately
            RingBuffer<Stream::Handle,false>    DeletionNotificationQueue;          ///< In case the original sender requested a notification for its stream deletion order, this queue will receive the handle of the respective stream once actually be deleted by the disk thread.
            RingBuffer< ::gig::DimensionRegion*,false>* DeleteDimregQueue;          ///< Contains dimension regions that are not used anymore and should be handed back to the instrument resource manager
            unsigned int                   RefillStreamsPerRun;                    ///< How many streams should be refilled in each loop run
            Stream**                       pStreams; ///< Contains all disk streams (whether used or unused)
            Stream**                       pCreatedStreams; ///< This is where the voice (audio thread) picks up it's meanwhile hopefully created disk stream.
            static Stream*                 SLOT_RESERVED;                          ///< This value is used to mark an entry in pCreatedStreams[] as reserved.
            InstrumentResourceManager*     pInstruments;                           ///< The instrument resource manager of the engine that is using this disk thread. Used by the dimension region deletion feature.

            // Methods
            void                           CreateStream(create_command_t& Command);
            void                           DeleteStream(delete_command_t& Command);
            void                           RefillStreams();
            Stream::Handle                 CreateHandle();
            Stream::OrderID_t              CreateOrderID();

            atomic_t ActiveStreamCount;
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_DISKTHREAD_H__
