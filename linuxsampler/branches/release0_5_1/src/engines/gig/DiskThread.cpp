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

#include <sstream>

#include "DiskThread.h"

namespace LinuxSampler { namespace gig {

    // *********** DiskThread **************
    // *


    // just a placeholder to mark a cell in the pickup array as 'reserved'
    Stream* DiskThread::SLOT_RESERVED = (Stream*) &SLOT_RESERVED;


    // #########################################################################
    // # Foreign Thread Section
    // #         (following code intended to be interface for audio thread)


    /**
     * Suspend disk thread, kill all active streams, clear all queues and the
     * pickup array and reset all streams. Call this method to bring everything
     * in the disk thread to day one. If the disk thread was running, it will be
     * respawned right after everything was reset.
     */
    void DiskThread::Reset() {
        bool running = this->IsRunning();
        if (running) this->StopThread();
        for (int i = 0; i < CONFIG_MAX_STREAMS; i++) {
            pStreams[i]->Kill();
        }
        for (int i = 1; i <= CONFIG_MAX_STREAMS; i++) {
            pCreatedStreams[i] = NULL;
        }
        GhostQueue->init();
        CreationQueue->init();
        DeletionQueue->init();
        DeletionNotificationQueue.init();
        DeleteDimregQueue->init();
        ActiveStreamCount = 0;
        ActiveStreamCountMax = 0;
        if (running) this->StartThread(); // start thread only if it was running before
    }

    String DiskThread::GetBufferFillBytes() {
        bool activestreams = false;
        std::stringstream ss;
        for (uint i = 0; i < this->Streams; i++) {
            if (pStreams[i]->GetState() == Stream::state_unused) continue;
            uint bufferfill = pStreams[i]->GetReadSpace() * sizeof(sample_t);
            uint streamid   = (uint) pStreams[i]->GetHandle();
            if (!streamid) continue;

            if (activestreams) ss << ",[" << streamid << ']' << bufferfill;
            else {
                ss << '[' << streamid << ']' << bufferfill;
                activestreams = true;
            }
        }
        return ss.str();
    }

    String DiskThread::GetBufferFillPercentage() {
        bool activestreams = false;
        std::stringstream ss;
        for (uint i = 0; i < this->Streams; i++) {
            if (pStreams[i]->GetState() == Stream::state_unused) continue;
            uint bufferfill = (uint) ((float) pStreams[i]->GetReadSpace() / (float) CONFIG_STREAM_BUFFER_SIZE * 100);
            uint streamid   = (uint) pStreams[i]->GetHandle();
            if (!streamid) continue;

            if (activestreams) ss << ",[" << streamid << ']' << bufferfill << '%';
            else {
                ss << '[' << streamid << ']' << bufferfill;
                activestreams = true;
            }
        }
        return ss.str();
    }

    /**
     * Returns -1 if command queue or pickup pool is full, 0 on success (will be
     * called by audio thread within the voice class).
     */
    int DiskThread::OrderNewStream(Stream::reference_t* pStreamRef, ::gig::DimensionRegion* pDimRgn, unsigned long SampleOffset, bool DoLoop) {
        dmsg(4,("Disk Thread: new stream ordered\n"));
        if (CreationQueue->write_space() < 1) {
            dmsg(1,("DiskThread: Order queue full!\n"));
            return -1;
        }

	const Stream::OrderID_t newOrder = CreateOrderID();
	if (!newOrder) {
		dmsg(1,("DiskThread: there was no free slot\n"));
		return -1; // there was no free slot
	}

        pStreamRef->State   = Stream::state_active;
        pStreamRef->OrderID = newOrder;
        pStreamRef->hStream = CreateHandle();
        pStreamRef->pStream = NULL; // a stream has to be activated by the disk thread first

        create_command_t cmd;
        cmd.OrderID      = pStreamRef->OrderID;
        cmd.hStream      = pStreamRef->hStream;
        cmd.pStreamRef   = pStreamRef;
        cmd.pDimRgn      = pDimRgn;
        cmd.SampleOffset = SampleOffset;
        cmd.DoLoop       = DoLoop;

        CreationQueue->push(&cmd);
        return 0;
    }

    /**
     * Request the disk thread to delete the given disk stream. This method
     * will return immediately, thus it won't block until the respective voice
     * was actually deleted. (Called by audio thread within the Voice class).
     *
     * @param pStreamRef           - stream that shall be deleted
     * @param bRequestNotification - set to true in case you want to receive a
     *                               notification once the stream has actually
     *                               been deleted
     * @returns 0 on success, -1 if command queue is full
     * @see AskForDeletedStream()
     */
    int DiskThread::OrderDeletionOfStream(Stream::reference_t* pStreamRef, bool bRequestNotification) {
        dmsg(4,("Disk Thread: stream deletion ordered\n"));
        if (DeletionQueue->write_space() < 1) {
            dmsg(1,("DiskThread: Deletion queue full!\n"));
            return -1;
        }

        delete_command_t cmd;
        cmd.pStream = pStreamRef->pStream;
        cmd.hStream = pStreamRef->hStream;
        cmd.OrderID = pStreamRef->OrderID;
        cmd.bNotify = bRequestNotification;

        DeletionQueue->push(&cmd);
        return 0;
    }

    /**
     * Tell the disk thread to release a dimension region that belongs
     * to an instrument which isn't loaded anymore. The disk thread
     * will hand back the dimension region to the instrument resource
     * manager. (OrderDeletionOfDimreg is called from the audio thread
     * when a voice dies.)
     */
    int DiskThread::OrderDeletionOfDimreg(::gig::DimensionRegion* dimreg) {
        dmsg(4,("Disk Thread: dimreg deletion ordered\n"));
        if (DeleteDimregQueue->write_space() < 1) {
            dmsg(1,("DiskThread: DeleteDimreg queue full!\n"));
            return -1;
        }
        DeleteDimregQueue->push(&dimreg);
        return 0;
    }

    /**
     * Returns the pointer to a disk stream if the ordered disk stream
     * represented by the \a StreamOrderID was already activated by the disk
     * thread, returns NULL otherwise. If the call was successful, thus if it
     * returned a valid stream pointer, the caller has to the store that pointer
     * by himself, because it's not possible to call this method again with the
     * same used order ID; this method is just intended for picking up an ordered
     * disk stream. This method will usually be called by the voice class (within
     * the audio thread).
     *
     * @param StreamOrderID - ID previously returned by OrderNewStream()
     * @returns               pointer to created stream object, NULL otherwise
     */
    Stream* DiskThread::AskForCreatedStream(Stream::OrderID_t StreamOrderID) {
        dmsg(4,("Disk Thread: been asked if stream already created, OrderID=%x ", StreamOrderID));
        Stream* pStream = pCreatedStreams[StreamOrderID];
        if (pStream && pStream != SLOT_RESERVED) {
            dmsg(4,("(yes created)\n"));
            pCreatedStreams[StreamOrderID] = NULL; // free the slot for a new order
            return pStream;
        }
        dmsg(4,("(no not yet created)\n"));
        return NULL;
    }

    /**
     * In case the original sender requested a notification with his stream
     * deletion order, he can use this method to poll if the respective stream
     * has actually been deleted.
     *
     * @returns handle / identifier of the deleted stream, or
     *          Stream::INVALID_HANDLE if no notification present
     */
    Stream::Handle DiskThread::AskForDeletedStream() {
        if (DeletionNotificationQueue.read_space()) {
            Stream::Handle hStream;
            DeletionNotificationQueue.pop(&hStream);
            return hStream;
        } else return Stream::INVALID_HANDLE; // no notification received yet
    }



    // #########################################################################
    // # Disk Thread Only Section
    // #         (following code should only be executed by the disk thread)


    DiskThread::DiskThread(uint BufferWrapElements, InstrumentResourceManager* pInstruments) :
        Thread(true, false, 1, -2),
        pInstruments(pInstruments),
        DeletionNotificationQueue(4*CONFIG_MAX_STREAMS)
    {
        DecompressionBuffer = ::gig::Sample::CreateDecompressionBuffer(CONFIG_STREAM_MAX_REFILL_SIZE);
        CreationQueue       = new RingBuffer<create_command_t,false>(4*CONFIG_MAX_STREAMS);
        DeletionQueue       = new RingBuffer<delete_command_t,false>(4*CONFIG_MAX_STREAMS);
        GhostQueue          = new RingBuffer<delete_command_t,false>(CONFIG_MAX_STREAMS);
        DeleteDimregQueue   = new RingBuffer< ::gig::DimensionRegion*,false>(4*CONFIG_MAX_STREAMS);
        Streams             = CONFIG_MAX_STREAMS;
        RefillStreamsPerRun = CONFIG_REFILL_STREAMS_PER_RUN;
        for (int i = 0; i < CONFIG_MAX_STREAMS; i++) {
            pStreams[i] = new Stream(&DecompressionBuffer, CONFIG_STREAM_BUFFER_SIZE, BufferWrapElements); // 131072 sample words
        }
        for (int i = 1; i <= CONFIG_MAX_STREAMS; i++) {
            pCreatedStreams[i] = NULL;
        }
        ActiveStreamCountMax = 0;
    }

    DiskThread::~DiskThread() {
        for (int i = 0; i < CONFIG_MAX_STREAMS; i++) {
            if (pStreams[i]) delete pStreams[i];
        }
        if (CreationQueue) delete CreationQueue;
        if (DeletionQueue) delete DeletionQueue;
        if (GhostQueue)    delete GhostQueue;
        if (DeleteDimregQueue) delete DeleteDimregQueue;
        ::gig::Sample::DestroyDecompressionBuffer(DecompressionBuffer);
    }

    int DiskThread::Main() {
        dmsg(3,("Disk thread running\n"));
        while (true) {
            #if !defined(WIN32)
            pthread_testcancel(); // mandatory for OSX
            #endif
            IsIdle = true; // will be set to false if a stream got filled

            // if there are ghost streams, delete them
            for (int i = 0; i < GhostQueue->read_space(); i++) { //FIXME: unefficient
                delete_command_t ghostStream;
                GhostQueue->pop(&ghostStream);
                bool found = false;
                for (int i = 0; i < this->Streams; i++) {
                    if (pStreams[i]->GetHandle() == ghostStream.hStream) {
                        pStreams[i]->Kill();
                        found = true;
                        // if original sender requested a notification, let him know now
                        if (ghostStream.bNotify)
                            DeletionNotificationQueue.push(&ghostStream.hStream);
                        break;
                    }
                }
                if (!found) GhostQueue->push(&ghostStream); // put ghost stream handle back to the queue
            }

            // if there are creation commands, create new streams
            while (Stream::UnusedStreams > 0 && CreationQueue->read_space() > 0) {
                create_command_t command;
                CreationQueue->pop(&command);
                CreateStream(command);
            }

            // if there are deletion commands, delete those streams
            while (Stream::UnusedStreams < Stream::TotalStreams && DeletionQueue->read_space() > 0) {
                delete_command_t command;
                DeletionQueue->pop(&command);
                DeleteStream(command);
            }

            // release DimensionRegions that belong to instruments
            // that are no longer loaded
            while (DeleteDimregQueue->read_space() > 0) {
                ::gig::DimensionRegion* dimreg;
                DeleteDimregQueue->pop(&dimreg);
                pInstruments->HandBackDimReg(dimreg);
            }

            RefillStreams(); // refill the most empty streams

            // if nothing was done during this iteration (eg no streambuffer
            // filled with data) then sleep for 30ms
            if (IsIdle) usleep(30000);

            int streamsInUsage = 0;
            for (int i = Streams - 1; i >= 0; i--) {
                if (pStreams[i]->GetState() != Stream::state_unused) streamsInUsage++;
            }
            ActiveStreamCount = streamsInUsage;
            if (streamsInUsage > ActiveStreamCountMax) ActiveStreamCountMax = streamsInUsage;
        }

        return EXIT_FAILURE;
    }

    void DiskThread::CreateStream(create_command_t& Command) {
        // search for unused stream
        Stream* newstream = NULL;
        for (int i = Streams - 1; i >= 0; i--) {
            if (pStreams[i]->GetState() == Stream::state_unused) {
                newstream = pStreams[i];
                break;
            }
        }
        if (!newstream) {
            std::cerr << "No unused stream found (OrderID:" << Command.OrderID << ") - report if this happens, this is a bug!\n" << std::flush;
            return;
        }
        newstream->Launch(Command.hStream, Command.pStreamRef, Command.pDimRgn, Command.SampleOffset, Command.DoLoop);
        dmsg(4,("new Stream launched by disk thread (OrderID:%d,StreamHandle:%d)\n", Command.OrderID, Command.hStream));
        if (pCreatedStreams[Command.OrderID] != SLOT_RESERVED) {
            std::cerr << "DiskThread: Slot " << Command.OrderID << " already occupied! Please report this!\n" << std::flush;
            newstream->Kill();
            return;
        }
        pCreatedStreams[Command.OrderID] = newstream;
    }

    void DiskThread::DeleteStream(delete_command_t& Command) {
        if (Command.pStream) Command.pStream->Kill();
        else { // the stream wasn't created by disk thread or picked up by audio thread yet

            // if stream was created but not picked up yet
            Stream* pStream = pCreatedStreams[Command.OrderID];
            if (pStream && pStream != SLOT_RESERVED) {
                pStream->Kill();
                pCreatedStreams[Command.OrderID] = NULL; // free slot for new order
                // if original sender requested a notification, let him know now
                if (Command.bNotify)
                    DeletionNotificationQueue.push(&Command.hStream);
                return;
            }

            // the stream was not created yet
            if (GhostQueue->write_space() > 0) {
                GhostQueue->push(&Command);
            } else { // error, queue full
                if (Command.bNotify) {
                    dmsg(1,("DiskThread: GhostQueue full! (might lead to dead lock with instrument editor!)\n"));
                } else {
                    dmsg(1,("DiskThread: GhostQueue full!\n"));
                }
            }
        }
    }

    void DiskThread::RefillStreams() {
        // sort the streams by most empty stream
        qsort(pStreams, Streams, sizeof(Stream*), CompareStreamWriteSpace);

        // refill the most empty streams
        for (uint i = 0; i < RefillStreamsPerRun; i++) {
            if (pStreams[i]->GetState() == Stream::state_active) {

                //float filledpercentage = (float) pStreams[i]->GetReadSpace() / 131072.0 * 100.0;
                //dmsg(("\nbuffer fill: %.1f%\n", filledpercentage));

                int writespace = pStreams[i]->GetWriteSpaceToEnd();
                if (writespace == 0) break;

                int capped_writespace = writespace;
                // if there is too much buffer space available then cut the read/write
                // size to CONFIG_STREAM_MAX_REFILL_SIZE which is by default 65536 samples = 256KBytes
                if (writespace > CONFIG_STREAM_MAX_REFILL_SIZE) capped_writespace = CONFIG_STREAM_MAX_REFILL_SIZE;

                // adjust the amount to read in order to ensure that the buffer wraps correctly
                int read_amount = pStreams[i]->AdjustWriteSpaceToAvoidBoundary(writespace, capped_writespace);
                // if we wasn't able to refill one of the stream buffers by more than
                // CONFIG_STREAM_MIN_REFILL_SIZE we'll send the disk thread to sleep later
                if (pStreams[i]->ReadAhead(read_amount) > CONFIG_STREAM_MIN_REFILL_SIZE) this->IsIdle = false;
            }
        }
    }

    /// Handle Generator
    Stream::Handle DiskThread::CreateHandle() {
        static uint32_t counter = 0;
        if (counter == 0xffffffff) counter = 1; // we use '0' as 'invalid handle' only, so we skip 0
        else                       counter++;
        return counter;
    }

    /// order ID Generator
    Stream::OrderID_t DiskThread::CreateOrderID() {
        static Stream::OrderID_t counter(0);
        for (int i = 0; i < CONFIG_MAX_STREAMS; i++) {
            if (counter == CONFIG_MAX_STREAMS) counter = 1; // we use '0' as 'invalid order' only, so we skip 0
            else                              counter++;
            if (!pCreatedStreams[counter]) {
                pCreatedStreams[counter] = SLOT_RESERVED; // mark this slot as reserved
                return counter;                           // found empty slot
            }
        }
        return 0; // no free slot
    }



    // *********** C functions **************
    // *

    /**
     * This is the comparison function the qsort algo uses to determine if a value is
     * bigger than another one or special in our case; if the writespace of a stream
     * is bigger than another one.
     */
    int CompareStreamWriteSpace(const void* A, const void* B) {
        Stream* a = *(Stream**) A;
        Stream* b = *(Stream**) B;
        return b->GetWriteSpace() - a->GetWriteSpace();
    }

}} // namespace LinuxSampler::gig
