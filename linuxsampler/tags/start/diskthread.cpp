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

#include "diskthread.h"


// *********** DiskThread **************
// *


// #########################################################################
// # Foreign Thread Section
// #         (following code intended to be interface for audio thread)


/**
 * Returns -1 if command queue is full, 0 on success (will be called by audio
 * thread within the voice class).
 */
int DiskThread::OrderNewStream(Stream::reference_t* pStreamRef, gig::Sample* pSample, unsigned long SampleOffset) {
    dmsg(("Disk Thread: new stream ordered\n"));
    if (CreationQueue->write_space() < 1) return -1;

    pStreamRef->State   = Stream::state_active;
    pStreamRef->OrderID = CreateOrderID();
    pStreamRef->hStream = CreateHandle();
    pStreamRef->pStream = NULL; // a stream has to be activated by the disk thread first

    create_command_t cmd;
    cmd.pStreamRef   = pStreamRef;
    cmd.pSample      = pSample;
    cmd.SampleOffset = SampleOffset;

    CreationQueue->write(&cmd, 1);
    return 0;
}

/**
 * Returns -1 if command queue is full, 0 on success (will be called by audio
 * thread within the voice class).
 */
int DiskThread::OrderDeletionOfStream(Stream::reference_t* pStreamRef) {
    dmsg(("Disk Thread: stream deletion ordered\n"));
    if (DeletionQueue->write_space() < 1) return -1;

    delete_command_t cmd;
    cmd.pStream = pStreamRef->pStream;
    cmd.hStream = pStreamRef->hStream;
    cmd.OrderID = pStreamRef->OrderID;

    DeletionQueue->write(&cmd, 1);
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
    dmsg(("Disk Thread: been asked if stream already created, OrderID=%x ", StreamOrderID));
    Stream* pStream = pCreatedStreams[StreamOrderID];
    if (pStream) { dmsg(("(yes created)")) }
    else         { dmsg(("(no not yet created)")) }
    pCreatedStreams[StreamOrderID] = NULL; // free the slot for a new order
    return pStream;
}



// #########################################################################
// # Disk Thread Only Section
// #         (following code should only be executed by the disk thread)


DiskThread::DiskThread(uint BufferWrapElements) : Thread(false, 1, -2) {
    CreationQueue       = new RingBuffer<create_command_t>(1024);
    DeletionQueue       = new RingBuffer<delete_command_t>(1024);
    Streams             = MAX_INPUT_STREAMS;
    RefillStreamsPerRun = 4;
    for (int i = 0; i < MAX_INPUT_STREAMS; i++) {
        pStreams[i] = new Stream(131072, BufferWrapElements); // 131072 sample words
    }
    for (int i = 1; i <= MAX_INPUT_STREAMS; i++) {
        pCreatedStreams[i] = NULL;
    }
}

DiskThread::~DiskThread() {
    for (int i = 0; i < MAX_INPUT_STREAMS; i++) {
        if (pStreams[i]) delete pStreams[i];
    }
    if (CreationQueue) delete CreationQueue;
    if (DeletionQueue) delete DeletionQueue;
}

int DiskThread::Main() {
    dmsg(("Disk thread running\n"));
    while (true) {
        IsIdle = true; // will be set to false if a stream got filled

        // if there are creation commands, create new streams
        while (Stream::UnusedStreams > 0 && CreationQueue->read_space() > 0) {
            create_command_t command;
            CreationQueue->read(&command, 1);
            CreateStream(command);
        }

        // if there are deletion commands, delete those streams
        while (Stream::UnusedStreams < Streams && DeletionQueue->read_space() > 0) {
            delete_command_t command;
            DeletionQueue->read(&command, 1);
            DeleteStream(command);
        }

        RefillStreams(); // refill the most empty streams

        // if nothing was done during this iteration (eg no streambuffer
        // filled with data) then sleep for 50ms
        if (IsIdle) usleep(30000);
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
        dmsg(("No unused stream found (OrderID:%x) - report if this happens, this is a bug!\n", Command.pStreamRef->OrderID));
        return;
    }
    dmsg(("new Stream launched by disk thread (OrderID:%x,StreamHandle:%x)\n", Command.pStreamRef->OrderID, Command.pStreamRef->hStream));
    newstream->Launch(Command.pStreamRef, Command.pSample, Command.SampleOffset);
    pCreatedStreams[Command.pStreamRef->OrderID] = newstream;
}

void DiskThread::DeleteStream(delete_command_t& Command) {
    if (Command.pStream) Command.pStream->Kill();
    else { // the stream wasn't created by disk thread or picked up by audio thread yet

        // stream was created but not picked up yet
        Stream* pStream = pCreatedStreams[Command.OrderID];
        if (pStream) {
            pStream->Kill();
            pCreatedStreams[Command.OrderID] = NULL; // free slot for new order
            return;
        }

        // else we have to compare the handle with the one's of all streams
        // (this case should occur only very rarely)
        for (int i = 0; i < this->Streams; i++) {
            if (pStreams[i]->GetHandle() == Command.hStream) {
                pStreams[i]->Kill();
                return;
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
            // size to MAX_REFILL_SIZE which is by default 65536 samples = 256KBytes
            if (writespace > MAX_REFILL_SIZE) capped_writespace = MAX_REFILL_SIZE;

            // adjust the amount to read in order to ensure that the buffer wraps correctly
            int read_amount = pStreams[i]->AdjustWriteSpaceToAvoidBoundary(writespace, capped_writespace);
            // if we wasn't able to refill one of the stream buffers by more than
            // MIN_REFILL_SIZE we'll send the disk thread to sleep later
            if (pStreams[i]->ReadAhead(read_amount) > MIN_REFILL_SIZE) this->IsIdle = false;
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
    static uint32_t counter = 0;
    do {
        if (counter == MAX_INPUT_STREAMS) counter = 1; // we use '0' as 'invalid order' only, so we skip 0
        else                              counter++;
    } while (pCreatedStreams[counter]); // until empty slot found
    return counter;
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
