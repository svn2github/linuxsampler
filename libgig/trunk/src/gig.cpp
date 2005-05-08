/***************************************************************************
 *                                                                         *
 *   libgig - C++ cross-platform Gigasampler format file loader library    *
 *                                                                         *
 *   Copyright (C) 2003-2005 by Christian Schoenebeck                      *
 *                              <cuse@users.sourceforge.net>               *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#include "gig.h"

#include <iostream>

namespace gig {

// *************** progress_t ***************
// *

    progress_t::progress_t() {
        callback    = NULL;
        custom      = NULL;
        __range_min = 0.0f;
        __range_max = 1.0f;
    }

    // private helper function to convert progress of a subprocess into the global progress
    static void __notify_progress(progress_t* pProgress, float subprogress) {
        if (pProgress && pProgress->callback) {
            const float totalrange    = pProgress->__range_max - pProgress->__range_min;
            const float totalprogress = pProgress->__range_min + subprogress * totalrange;
            pProgress->factor         = totalprogress;
            pProgress->callback(pProgress); // now actually notify about the progress
        }
    }

    // private helper function to divide a progress into subprogresses
    static void __divide_progress(progress_t* pParentProgress, progress_t* pSubProgress, float totalTasks, float currentTask) {
        if (pParentProgress && pParentProgress->callback) {
            const float totalrange    = pParentProgress->__range_max - pParentProgress->__range_min;
            pSubProgress->callback    = pParentProgress->callback;
            pSubProgress->custom      = pParentProgress->custom;
            pSubProgress->__range_min = pParentProgress->__range_min + totalrange * currentTask / totalTasks;
            pSubProgress->__range_max = pSubProgress->__range_min + totalrange / totalTasks;
        }
    }


// *************** Internal functions for sample decopmression ***************
// *

namespace {

    inline int get12lo(const unsigned char* pSrc)
    {
        const int x = pSrc[0] | (pSrc[1] & 0x0f) << 8;
        return x & 0x800 ? x - 0x1000 : x;
    }

    inline int get12hi(const unsigned char* pSrc)
    {
        const int x = pSrc[1] >> 4 | pSrc[2] << 4;
        return x & 0x800 ? x - 0x1000 : x;
    }

    inline int16_t get16(const unsigned char* pSrc)
    {
        return int16_t(pSrc[0] | pSrc[1] << 8);
    }

    inline int get24(const unsigned char* pSrc)
    {
        const int x = pSrc[0] | pSrc[1] << 8 | pSrc[2] << 16;
        return x & 0x800000 ? x - 0x1000000 : x;
    }

    void Decompress16(int compressionmode, const unsigned char* params,
                      int srcStep, int dstStep,
                      const unsigned char* pSrc, int16_t* pDst,
                      unsigned long currentframeoffset,
                      unsigned long copysamples)
    {
        switch (compressionmode) {
            case 0: // 16 bit uncompressed
                pSrc += currentframeoffset * srcStep;
                while (copysamples) {
                    *pDst = get16(pSrc);
                    pDst += dstStep;
                    pSrc += srcStep;
                    copysamples--;
                }
                break;

            case 1: // 16 bit compressed to 8 bit
                int y  = get16(params);
                int dy = get16(params + 2);
                while (currentframeoffset) {
                    dy -= int8_t(*pSrc);
                    y  -= dy;
                    pSrc += srcStep;
                    currentframeoffset--;
                }
                while (copysamples) {
                    dy -= int8_t(*pSrc);
                    y  -= dy;
                    *pDst = y;
                    pDst += dstStep;
                    pSrc += srcStep;
                    copysamples--;
                }
                break;
        }
    }

    void Decompress24(int compressionmode, const unsigned char* params,
                      int dstStep, const unsigned char* pSrc, int16_t* pDst,
                      unsigned long currentframeoffset,
                      unsigned long copysamples, int truncatedBits)
    {
        // Note: The 24 bits are truncated to 16 bits for now.

        // Note: The calculation of the initial value of y is strange
        // and not 100% correct. What should the first two parameters
        // really be used for? Why are they two? The correct value for
        // y seems to lie somewhere between the values of the first
        // two parameters.
        //
        // Strange thing #2: The formula in SKIP_ONE gives values for
        // y that are twice as high as they should be. That's why
        // COPY_ONE shifts an extra step, and also why y is
        // initialized with a sum instead of a mean value.

        int y, dy, ddy;

        const int shift = 8 - truncatedBits;
        const int shift1 = shift + 1;

#define GET_PARAMS(params)                              \
        y = (get24(params) + get24((params) + 3));      \
        dy  = get24((params) + 6);                      \
        ddy = get24((params) + 9)

#define SKIP_ONE(x)                             \
        ddy -= (x);                             \
        dy -= ddy;                              \
        y -= dy

#define COPY_ONE(x)                             \
        SKIP_ONE(x);                            \
        *pDst = y >> shift1;                    \
        pDst += dstStep

        switch (compressionmode) {
            case 2: // 24 bit uncompressed
                pSrc += currentframeoffset * 3;
                while (copysamples) {
                    *pDst = get24(pSrc) >> shift;
                    pDst += dstStep;
                    pSrc += 3;
                    copysamples--;
                }
                break;

            case 3: // 24 bit compressed to 16 bit
                GET_PARAMS(params);
                while (currentframeoffset) {
                    SKIP_ONE(get16(pSrc));
                    pSrc += 2;
                    currentframeoffset--;
                }
                while (copysamples) {
                    COPY_ONE(get16(pSrc));
                    pSrc += 2;
                    copysamples--;
                }
                break;

            case 4: // 24 bit compressed to 12 bit
                GET_PARAMS(params);
                while (currentframeoffset > 1) {
                    SKIP_ONE(get12lo(pSrc));
                    SKIP_ONE(get12hi(pSrc));
                    pSrc += 3;
                    currentframeoffset -= 2;
                }
                if (currentframeoffset) {
                    SKIP_ONE(get12lo(pSrc));
                    currentframeoffset--;
                    if (copysamples) {
                        COPY_ONE(get12hi(pSrc));
                        pSrc += 3;
                        copysamples--;
                    }
                }
                while (copysamples > 1) {
                    COPY_ONE(get12lo(pSrc));
                    COPY_ONE(get12hi(pSrc));
                    pSrc += 3;
                    copysamples -= 2;
                }
                if (copysamples) {
                    COPY_ONE(get12lo(pSrc));
                }
                break;

            case 5: // 24 bit compressed to 8 bit
                GET_PARAMS(params);
                while (currentframeoffset) {
                    SKIP_ONE(int8_t(*pSrc++));
                    currentframeoffset--;
                }
                while (copysamples) {
                    COPY_ONE(int8_t(*pSrc++));
                    copysamples--;
                }
                break;
        }
    }

    const int bytesPerFrame[] =      { 4096, 2052, 768, 524, 396, 268 };
    const int bytesPerFrameNoHdr[] = { 4096, 2048, 768, 512, 384, 256 };
    const int headerSize[] =         { 0, 4, 0, 12, 12, 12 };
    const int bitsPerSample[] =      { 16, 8, 24, 16, 12, 8 };
}


// *************** Sample ***************
// *

    unsigned int Sample::Instances = 0;
    buffer_t     Sample::InternalDecompressionBuffer;

    Sample::Sample(File* pFile, RIFF::List* waveList, unsigned long WavePoolOffset) : DLS::Sample((DLS::File*) pFile, waveList, WavePoolOffset) {
        Instances++;

        RIFF::Chunk* _3gix = waveList->GetSubChunk(CHUNK_ID_3GIX);
        if (!_3gix) throw gig::Exception("Mandatory chunks in <wave> list chunk not found.");
        SampleGroup = _3gix->ReadInt16();

        RIFF::Chunk* smpl = waveList->GetSubChunk(CHUNK_ID_SMPL);
        if (!smpl) throw gig::Exception("Mandatory chunks in <wave> list chunk not found.");
        Manufacturer      = smpl->ReadInt32();
        Product           = smpl->ReadInt32();
        SamplePeriod      = smpl->ReadInt32();
        MIDIUnityNote     = smpl->ReadInt32();
        FineTune          = smpl->ReadInt32();
        smpl->Read(&SMPTEFormat, 1, 4);
        SMPTEOffset       = smpl->ReadInt32();
        Loops             = smpl->ReadInt32();
        smpl->ReadInt32(); // manufByt
        LoopID            = smpl->ReadInt32();
        smpl->Read(&LoopType, 1, 4);
        LoopStart         = smpl->ReadInt32();
        LoopEnd           = smpl->ReadInt32();
        LoopFraction      = smpl->ReadInt32();
        LoopPlayCount     = smpl->ReadInt32();

        FrameTable                 = NULL;
        SamplePos                  = 0;
        RAMCache.Size              = 0;
        RAMCache.pStart            = NULL;
        RAMCache.NullExtensionSize = 0;

        if (BitDepth > 24) throw gig::Exception("Only samples up to 24 bit supported");

        RIFF::Chunk* ewav = waveList->GetSubChunk(CHUNK_ID_EWAV);
        Compressed        = ewav;
        Dithered          = false;
        TruncatedBits     = 0;
        if (Compressed) {
            uint32_t version = ewav->ReadInt32();
            if (version == 3 && BitDepth == 24) {
                Dithered = ewav->ReadInt32();
                ewav->SetPos(Channels == 2 ? 84 : 64);
                TruncatedBits = ewav->ReadInt32();
            }
            ScanCompressedSample();
        }

        // we use a buffer for decompression and for truncating 24 bit samples to 16 bit
        if ((Compressed || BitDepth == 24) && !InternalDecompressionBuffer.Size) {
            InternalDecompressionBuffer.pStart = new unsigned char[INITIAL_SAMPLE_BUFFER_SIZE];
            InternalDecompressionBuffer.Size   = INITIAL_SAMPLE_BUFFER_SIZE;
        }
        FrameOffset = 0; // just for streaming compressed samples

        LoopSize = LoopEnd - LoopStart;
    }

    /// Scans compressed samples for mandatory informations (e.g. actual number of total sample points).
    void Sample::ScanCompressedSample() {
        //TODO: we have to add some more scans here (e.g. determine compression rate)
        this->SamplesTotal = 0;
        std::list<unsigned long> frameOffsets;

        SamplesPerFrame = BitDepth == 24 ? 256 : 2048;
        WorstCaseFrameSize = SamplesPerFrame * FrameSize + Channels; // +Channels for compression flag

        // Scanning
        pCkData->SetPos(0);
        if (Channels == 2) { // Stereo
            for (int i = 0 ; ; i++) {
                // for 24 bit samples every 8:th frame offset is
                // stored, to save some memory
                if (BitDepth != 24 || (i & 7) == 0) frameOffsets.push_back(pCkData->GetPos());

                const int mode_l = pCkData->ReadUint8();
                const int mode_r = pCkData->ReadUint8();
                if (mode_l > 5 || mode_r > 5) throw gig::Exception("Unknown compression mode");
                const unsigned long frameSize = bytesPerFrame[mode_l] + bytesPerFrame[mode_r];

                if (pCkData->RemainingBytes() <= frameSize) {
                    SamplesInLastFrame =
                        ((pCkData->RemainingBytes() - headerSize[mode_l] - headerSize[mode_r]) << 3) /
                        (bitsPerSample[mode_l] + bitsPerSample[mode_r]);
                    SamplesTotal += SamplesInLastFrame;
                    break;
                }
                SamplesTotal += SamplesPerFrame;
                pCkData->SetPos(frameSize, RIFF::stream_curpos);
            }
        }
        else { // Mono
            for (int i = 0 ; ; i++) {
                if (BitDepth != 24 || (i & 7) == 0) frameOffsets.push_back(pCkData->GetPos());

                const int mode = pCkData->ReadUint8();
                if (mode > 5) throw gig::Exception("Unknown compression mode");
                const unsigned long frameSize = bytesPerFrame[mode];

                if (pCkData->RemainingBytes() <= frameSize) {
                    SamplesInLastFrame =
                        ((pCkData->RemainingBytes() - headerSize[mode]) << 3) / bitsPerSample[mode];
                    SamplesTotal += SamplesInLastFrame;
                    break;
                }
                SamplesTotal += SamplesPerFrame;
                pCkData->SetPos(frameSize, RIFF::stream_curpos);
            }
        }
        pCkData->SetPos(0);

        // Build the frames table (which is used for fast resolving of a frame's chunk offset)
        if (FrameTable) delete[] FrameTable;
        FrameTable = new unsigned long[frameOffsets.size()];
        std::list<unsigned long>::iterator end  = frameOffsets.end();
        std::list<unsigned long>::iterator iter = frameOffsets.begin();
        for (int i = 0; iter != end; i++, iter++) {
            FrameTable[i] = *iter;
        }
    }

    /**
     * Loads (and uncompresses if needed) the whole sample wave into RAM. Use
     * ReleaseSampleData() to free the memory if you don't need the cached
     * sample data anymore.
     *
     * @returns  buffer_t structure with start address and size of the buffer
     *           in bytes
     * @see      ReleaseSampleData(), Read(), SetPos()
     */
    buffer_t Sample::LoadSampleData() {
        return LoadSampleDataWithNullSamplesExtension(this->SamplesTotal, 0); // 0 amount of NullSamples
    }

    /**
     * Reads (uncompresses if needed) and caches the first \a SampleCount
     * numbers of SamplePoints in RAM. Use ReleaseSampleData() to free the
     * memory space if you don't need the cached samples anymore. There is no
     * guarantee that exactly \a SampleCount samples will be cached; this is
     * not an error. The size will be eventually truncated e.g. to the
     * beginning of a frame of a compressed sample. This is done for
     * efficiency reasons while streaming the wave by your sampler engine
     * later. Read the <i>Size</i> member of the <i>buffer_t</i> structure
     * that will be returned to determine the actual cached samples, but note
     * that the size is given in bytes! You get the number of actually cached
     * samples by dividing it by the frame size of the sample:
     * @code
     * 	buffer_t buf       = pSample->LoadSampleData(acquired_samples);
     * 	long cachedsamples = buf.Size / pSample->FrameSize;
     * @endcode
     *
     * @param SampleCount - number of sample points to load into RAM
     * @returns             buffer_t structure with start address and size of
     *                      the cached sample data in bytes
     * @see                 ReleaseSampleData(), Read(), SetPos()
     */
    buffer_t Sample::LoadSampleData(unsigned long SampleCount) {
        return LoadSampleDataWithNullSamplesExtension(SampleCount, 0); // 0 amount of NullSamples
    }

    /**
     * Loads (and uncompresses if needed) the whole sample wave into RAM. Use
     * ReleaseSampleData() to free the memory if you don't need the cached
     * sample data anymore.
     * The method will add \a NullSamplesCount silence samples past the
     * official buffer end (this won't affect the 'Size' member of the
     * buffer_t structure, that means 'Size' always reflects the size of the
     * actual sample data, the buffer might be bigger though). Silence
     * samples past the official buffer are needed for differential
     * algorithms that always have to take subsequent samples into account
     * (resampling/interpolation would be an important example) and avoids
     * memory access faults in such cases.
     *
     * @param NullSamplesCount - number of silence samples the buffer should
     *                           be extended past it's data end
     * @returns                  buffer_t structure with start address and
     *                           size of the buffer in bytes
     * @see                      ReleaseSampleData(), Read(), SetPos()
     */
    buffer_t Sample::LoadSampleDataWithNullSamplesExtension(uint NullSamplesCount) {
        return LoadSampleDataWithNullSamplesExtension(this->SamplesTotal, NullSamplesCount);
    }

    /**
     * Reads (uncompresses if needed) and caches the first \a SampleCount
     * numbers of SamplePoints in RAM. Use ReleaseSampleData() to free the
     * memory space if you don't need the cached samples anymore. There is no
     * guarantee that exactly \a SampleCount samples will be cached; this is
     * not an error. The size will be eventually truncated e.g. to the
     * beginning of a frame of a compressed sample. This is done for
     * efficiency reasons while streaming the wave by your sampler engine
     * later. Read the <i>Size</i> member of the <i>buffer_t</i> structure
     * that will be returned to determine the actual cached samples, but note
     * that the size is given in bytes! You get the number of actually cached
     * samples by dividing it by the frame size of the sample:
     * @code
     * 	buffer_t buf       = pSample->LoadSampleDataWithNullSamplesExtension(acquired_samples, null_samples);
     * 	long cachedsamples = buf.Size / pSample->FrameSize;
     * @endcode
     * The method will add \a NullSamplesCount silence samples past the
     * official buffer end (this won't affect the 'Size' member of the
     * buffer_t structure, that means 'Size' always reflects the size of the
     * actual sample data, the buffer might be bigger though). Silence
     * samples past the official buffer are needed for differential
     * algorithms that always have to take subsequent samples into account
     * (resampling/interpolation would be an important example) and avoids
     * memory access faults in such cases.
     *
     * @param SampleCount      - number of sample points to load into RAM
     * @param NullSamplesCount - number of silence samples the buffer should
     *                           be extended past it's data end
     * @returns                  buffer_t structure with start address and
     *                           size of the cached sample data in bytes
     * @see                      ReleaseSampleData(), Read(), SetPos()
     */
    buffer_t Sample::LoadSampleDataWithNullSamplesExtension(unsigned long SampleCount, uint NullSamplesCount) {
        if (SampleCount > this->SamplesTotal) SampleCount = this->SamplesTotal;
        if (RAMCache.pStart) delete[] (int8_t*) RAMCache.pStart;
        unsigned long allocationsize = (SampleCount + NullSamplesCount) * this->FrameSize;
        RAMCache.pStart            = new int8_t[allocationsize];
        RAMCache.Size              = Read(RAMCache.pStart, SampleCount) * this->FrameSize;
        RAMCache.NullExtensionSize = allocationsize - RAMCache.Size;
        // fill the remaining buffer space with silence samples
        memset((int8_t*)RAMCache.pStart + RAMCache.Size, 0, RAMCache.NullExtensionSize);
        return GetCache();
    }

    /**
     * Returns current cached sample points. A buffer_t structure will be
     * returned which contains address pointer to the begin of the cache and
     * the size of the cached sample data in bytes. Use
     * <i>LoadSampleData()</i> to cache a specific amount of sample points in
     * RAM.
     *
     * @returns  buffer_t structure with current cached sample points
     * @see      LoadSampleData();
     */
    buffer_t Sample::GetCache() {
        // return a copy of the buffer_t structure
        buffer_t result;
        result.Size              = this->RAMCache.Size;
        result.pStart            = this->RAMCache.pStart;
        result.NullExtensionSize = this->RAMCache.NullExtensionSize;
        return result;
    }

    /**
     * Frees the cached sample from RAM if loaded with
     * <i>LoadSampleData()</i> previously.
     *
     * @see  LoadSampleData();
     */
    void Sample::ReleaseSampleData() {
        if (RAMCache.pStart) delete[] (int8_t*) RAMCache.pStart;
        RAMCache.pStart = NULL;
        RAMCache.Size   = 0;
    }

    /**
     * Sets the position within the sample (in sample points, not in
     * bytes). Use this method and <i>Read()</i> if you don't want to load
     * the sample into RAM, thus for disk streaming.
     *
     * Although the original Gigasampler engine doesn't allow positioning
     * within compressed samples, I decided to implement it. Even though
     * the Gigasampler format doesn't allow to define loops for compressed
     * samples at the moment, positioning within compressed samples might be
     * interesting for some sampler engines though. The only drawback about
     * my decision is that it takes longer to load compressed gig Files on
     * startup, because it's neccessary to scan the samples for some
     * mandatory informations. But I think as it doesn't affect the runtime
     * efficiency, nobody will have a problem with that.
     *
     * @param SampleCount  number of sample points to jump
     * @param Whence       optional: to which relation \a SampleCount refers
     *                     to, if omited <i>RIFF::stream_start</i> is assumed
     * @returns            the new sample position
     * @see                Read()
     */
    unsigned long Sample::SetPos(unsigned long SampleCount, RIFF::stream_whence_t Whence) {
        if (Compressed) {
            switch (Whence) {
                case RIFF::stream_curpos:
                    this->SamplePos += SampleCount;
                    break;
                case RIFF::stream_end:
                    this->SamplePos = this->SamplesTotal - 1 - SampleCount;
                    break;
                case RIFF::stream_backward:
                    this->SamplePos -= SampleCount;
                    break;
                case RIFF::stream_start: default:
                    this->SamplePos = SampleCount;
                    break;
            }
            if (this->SamplePos > this->SamplesTotal) this->SamplePos = this->SamplesTotal;

            unsigned long frame = this->SamplePos / 2048; // to which frame to jump
            this->FrameOffset   = this->SamplePos % 2048; // offset (in sample points) within that frame
            pCkData->SetPos(FrameTable[frame]);           // set chunk pointer to the start of sought frame
            return this->SamplePos;
        }
        else { // not compressed
            unsigned long orderedBytes = SampleCount * this->FrameSize;
            unsigned long result = pCkData->SetPos(orderedBytes, Whence);
            return (result == orderedBytes) ? SampleCount
                                            : result / this->FrameSize;
        }
    }

    /**
     * Returns the current position in the sample (in sample points).
     */
    unsigned long Sample::GetPos() {
        if (Compressed) return SamplePos;
        else            return pCkData->GetPos() / FrameSize;
    }

    /**
     * Reads \a SampleCount number of sample points from the position stored
     * in \a pPlaybackState into the buffer pointed by \a pBuffer and moves
     * the position within the sample respectively, this method honors the
     * looping informations of the sample (if any). The sample wave stream
     * will be decompressed on the fly if using a compressed sample. Use this
     * method if you don't want to load the sample into RAM, thus for disk
     * streaming. All this methods needs to know to proceed with streaming
     * for the next time you call this method is stored in \a pPlaybackState.
     * You have to allocate and initialize the playback_state_t structure by
     * yourself before you use it to stream a sample:
     * @code
     * gig::playback_state_t playbackstate;
     * playbackstate.position         = 0;
     * playbackstate.reverse          = false;
     * playbackstate.loop_cycles_left = pSample->LoopPlayCount;
     * @endcode
     * You don't have to take care of things like if there is actually a loop
     * defined or if the current read position is located within a loop area.
     * The method already handles such cases by itself.
     *
     * <b>Caution:</b> If you are using more than one streaming thread, you
     * have to use an external decompression buffer for <b>EACH</b>
     * streaming thread to avoid race conditions and crashes!
     *
     * @param pBuffer          destination buffer
     * @param SampleCount      number of sample points to read
     * @param pPlaybackState   will be used to store and reload the playback
     *                         state for the next ReadAndLoop() call
     * @param pExternalDecompressionBuffer  (optional) external buffer to use for decompression
     * @returns                number of successfully read sample points
     * @see                    CreateDecompressionBuffer()
     */
    unsigned long Sample::ReadAndLoop(void* pBuffer, unsigned long SampleCount, playback_state_t* pPlaybackState, buffer_t* pExternalDecompressionBuffer) {
        unsigned long samplestoread = SampleCount, totalreadsamples = 0, readsamples, samplestoloopend;
        uint8_t* pDst = (uint8_t*) pBuffer;

        SetPos(pPlaybackState->position); // recover position from the last time

        if (this->Loops && GetPos() <= this->LoopEnd) { // honor looping if there are loop points defined

            switch (this->LoopType) {

                case loop_type_bidirectional: { //TODO: not tested yet!
                    do {
                        // if not endless loop check if max. number of loop cycles have been passed
                        if (this->LoopPlayCount && !pPlaybackState->loop_cycles_left) break;

                        if (!pPlaybackState->reverse) { // forward playback
                            do {
                                samplestoloopend  = this->LoopEnd - GetPos();
                                readsamples       = Read(&pDst[totalreadsamples * this->FrameSize], Min(samplestoread, samplestoloopend), pExternalDecompressionBuffer);
                                samplestoread    -= readsamples;
                                totalreadsamples += readsamples;
                                if (readsamples == samplestoloopend) {
                                    pPlaybackState->reverse = true;
                                    break;
                                }
                            } while (samplestoread && readsamples);
                        }
                        else { // backward playback

                            // as we can only read forward from disk, we have to
                            // determine the end position within the loop first,
                            // read forward from that 'end' and finally after
                            // reading, swap all sample frames so it reflects
                            // backward playback

                            unsigned long swapareastart       = totalreadsamples;
                            unsigned long loopoffset          = GetPos() - this->LoopStart;
                            unsigned long samplestoreadinloop = Min(samplestoread, loopoffset);
                            unsigned long reverseplaybackend  = GetPos() - samplestoreadinloop;

                            SetPos(reverseplaybackend);

                            // read samples for backward playback
                            do {
                                readsamples          = Read(&pDst[totalreadsamples * this->FrameSize], samplestoreadinloop, pExternalDecompressionBuffer);
                                samplestoreadinloop -= readsamples;
                                samplestoread       -= readsamples;
                                totalreadsamples    += readsamples;
                            } while (samplestoreadinloop && readsamples);

                            SetPos(reverseplaybackend); // pretend we really read backwards

                            if (reverseplaybackend == this->LoopStart) {
                                pPlaybackState->loop_cycles_left--;
                                pPlaybackState->reverse = false;
                            }

                            // reverse the sample frames for backward playback
                            SwapMemoryArea(&pDst[swapareastart * this->FrameSize], (totalreadsamples - swapareastart) * this->FrameSize, this->FrameSize);
                        }
                    } while (samplestoread && readsamples);
                    break;
                }

                case loop_type_backward: { // TODO: not tested yet!
                    // forward playback (not entered the loop yet)
                    if (!pPlaybackState->reverse) do {
                        samplestoloopend  = this->LoopEnd - GetPos();
                        readsamples       = Read(&pDst[totalreadsamples * this->FrameSize], Min(samplestoread, samplestoloopend), pExternalDecompressionBuffer);
                        samplestoread    -= readsamples;
                        totalreadsamples += readsamples;
                        if (readsamples == samplestoloopend) {
                            pPlaybackState->reverse = true;
                            break;
                        }
                    } while (samplestoread && readsamples);

                    if (!samplestoread) break;

                    // as we can only read forward from disk, we have to
                    // determine the end position within the loop first,
                    // read forward from that 'end' and finally after
                    // reading, swap all sample frames so it reflects
                    // backward playback

                    unsigned long swapareastart       = totalreadsamples;
                    unsigned long loopoffset          = GetPos() - this->LoopStart;
                    unsigned long samplestoreadinloop = (this->LoopPlayCount) ? Min(samplestoread, pPlaybackState->loop_cycles_left * LoopSize - loopoffset)
                                                                              : samplestoread;
                    unsigned long reverseplaybackend  = this->LoopStart + Abs((loopoffset - samplestoreadinloop) % this->LoopSize);

                    SetPos(reverseplaybackend);

                    // read samples for backward playback
                    do {
                        // if not endless loop check if max. number of loop cycles have been passed
                        if (this->LoopPlayCount && !pPlaybackState->loop_cycles_left) break;
                        samplestoloopend     = this->LoopEnd - GetPos();
                        readsamples          = Read(&pDst[totalreadsamples * this->FrameSize], Min(samplestoreadinloop, samplestoloopend), pExternalDecompressionBuffer);
                        samplestoreadinloop -= readsamples;
                        samplestoread       -= readsamples;
                        totalreadsamples    += readsamples;
                        if (readsamples == samplestoloopend) {
                            pPlaybackState->loop_cycles_left--;
                            SetPos(this->LoopStart);
                        }
                    } while (samplestoreadinloop && readsamples);

                    SetPos(reverseplaybackend); // pretend we really read backwards

                    // reverse the sample frames for backward playback
                    SwapMemoryArea(&pDst[swapareastart * this->FrameSize], (totalreadsamples - swapareastart) * this->FrameSize, this->FrameSize);
                    break;
                }

                default: case loop_type_normal: {
                    do {
                        // if not endless loop check if max. number of loop cycles have been passed
                        if (this->LoopPlayCount && !pPlaybackState->loop_cycles_left) break;
                        samplestoloopend  = this->LoopEnd - GetPos();
                        readsamples       = Read(&pDst[totalreadsamples * this->FrameSize], Min(samplestoread, samplestoloopend), pExternalDecompressionBuffer);
                        samplestoread    -= readsamples;
                        totalreadsamples += readsamples;
                        if (readsamples == samplestoloopend) {
                            pPlaybackState->loop_cycles_left--;
                            SetPos(this->LoopStart);
                        }
                    } while (samplestoread && readsamples);
                    break;
                }
            }
        }

        // read on without looping
        if (samplestoread) do {
            readsamples = Read(&pDst[totalreadsamples * this->FrameSize], samplestoread, pExternalDecompressionBuffer);
            samplestoread    -= readsamples;
            totalreadsamples += readsamples;
        } while (readsamples && samplestoread);

        // store current position
        pPlaybackState->position = GetPos();

        return totalreadsamples;
    }

    /**
     * Reads \a SampleCount number of sample points from the current
     * position into the buffer pointed by \a pBuffer and increments the
     * position within the sample. The sample wave stream will be
     * decompressed on the fly if using a compressed sample. Use this method
     * and <i>SetPos()</i> if you don't want to load the sample into RAM,
     * thus for disk streaming.
     *
     * <b>Caution:</b> If you are using more than one streaming thread, you
     * have to use an external decompression buffer for <b>EACH</b>
     * streaming thread to avoid race conditions and crashes!
     *
     * @param pBuffer      destination buffer
     * @param SampleCount  number of sample points to read
     * @param pExternalDecompressionBuffer  (optional) external buffer to use for decompression
     * @returns            number of successfully read sample points
     * @see                SetPos(), CreateDecompressionBuffer()
     */
    unsigned long Sample::Read(void* pBuffer, unsigned long SampleCount, buffer_t* pExternalDecompressionBuffer) {
        if (SampleCount == 0) return 0;
        if (!Compressed) {
            if (BitDepth == 24) {
                // 24 bit sample. For now just truncate to 16 bit.
                unsigned char* pSrc = (unsigned char*) ((pExternalDecompressionBuffer) ? pExternalDecompressionBuffer->pStart : this->InternalDecompressionBuffer.pStart);
                int16_t* pDst = static_cast<int16_t*>(pBuffer);
                if (Channels == 2) { // Stereo
                    unsigned long readBytes = pCkData->Read(pSrc, SampleCount * 6, 1);
                    pSrc++;
                    for (unsigned long i = readBytes ; i > 0 ; i -= 3) {
                        *pDst++ = get16(pSrc);
                        pSrc += 3;
                    }
                    return (pDst - static_cast<int16_t*>(pBuffer)) >> 1;
                }
                else { // Mono
                    unsigned long readBytes = pCkData->Read(pSrc, SampleCount * 3, 1);
                    pSrc++;
                    for (unsigned long i = readBytes ; i > 0 ; i -= 3) {
                        *pDst++ = get16(pSrc);
                        pSrc += 3;
                    }
                    return pDst - static_cast<int16_t*>(pBuffer);
                }
            }
            else { // 16 bit
                // (pCkData->Read does endian correction)
                return Channels == 2 ? pCkData->Read(pBuffer, SampleCount << 1, 2) >> 1
                                     : pCkData->Read(pBuffer, SampleCount, 2);
            }
        }
        else {
            if (this->SamplePos >= this->SamplesTotal) return 0;
            //TODO: efficiency: maybe we should test for an average compression rate
            unsigned long assumedsize      = GuessSize(SampleCount),
                          remainingbytes   = 0,           // remaining bytes in the local buffer
                          remainingsamples = SampleCount,
                          copysamples, skipsamples,
                          currentframeoffset = this->FrameOffset;  // offset in current sample frame since last Read()
            this->FrameOffset = 0;

            buffer_t* pDecompressionBuffer = (pExternalDecompressionBuffer) ? pExternalDecompressionBuffer : &InternalDecompressionBuffer;

            // if decompression buffer too small, then reduce amount of samples to read
            if (pDecompressionBuffer->Size < assumedsize) {
                std::cerr << "gig::Read(): WARNING - decompression buffer size too small!" << std::endl;
                SampleCount      = WorstCaseMaxSamples(pDecompressionBuffer);
                remainingsamples = SampleCount;
                assumedsize      = GuessSize(SampleCount);
            }

            unsigned char* pSrc = (unsigned char*) pDecompressionBuffer->pStart;
            int16_t* pDst = static_cast<int16_t*>(pBuffer);
            remainingbytes = pCkData->Read(pSrc, assumedsize, 1);

            while (remainingsamples && remainingbytes) {
                unsigned long framesamples = SamplesPerFrame;
                unsigned long framebytes, rightChannelOffset = 0, nextFrameOffset;

                int mode_l = *pSrc++, mode_r = 0;

                if (Channels == 2) {
                    mode_r = *pSrc++;
                    framebytes = bytesPerFrame[mode_l] + bytesPerFrame[mode_r] + 2;
                    rightChannelOffset = bytesPerFrameNoHdr[mode_l];
                    nextFrameOffset = rightChannelOffset + bytesPerFrameNoHdr[mode_r];
                    if (remainingbytes < framebytes) { // last frame in sample
                        framesamples = SamplesInLastFrame;
                        if (mode_l == 4 && (framesamples & 1)) {
                            rightChannelOffset = ((framesamples + 1) * bitsPerSample[mode_l]) >> 3;
                        }
                        else {
                            rightChannelOffset = (framesamples * bitsPerSample[mode_l]) >> 3;
                        }
                    }
                }
                else {
                    framebytes = bytesPerFrame[mode_l] + 1;
                    nextFrameOffset = bytesPerFrameNoHdr[mode_l];
                    if (remainingbytes < framebytes) {
                        framesamples = SamplesInLastFrame;
                    }
                }

                // determine how many samples in this frame to skip and read
                if (currentframeoffset + remainingsamples >= framesamples) {
                    if (currentframeoffset <= framesamples) {
                        copysamples = framesamples - currentframeoffset;
                        skipsamples = currentframeoffset;
                    }
                    else {
                        copysamples = 0;
                        skipsamples = framesamples;
                    }
                }
                else {
                    // This frame has enough data for pBuffer, but not
                    // all of the frame is needed. Set file position
                    // to start of this frame for next call to Read.
                    copysamples = remainingsamples;
                    skipsamples = currentframeoffset;
                    pCkData->SetPos(remainingbytes, RIFF::stream_backward);
                    this->FrameOffset = currentframeoffset + copysamples;
                }
                remainingsamples -= copysamples;

                if (remainingbytes > framebytes) {
                    remainingbytes -= framebytes;
                    if (remainingsamples == 0 &&
                        currentframeoffset + copysamples == framesamples) {
                        // This frame has enough data for pBuffer, and
                        // all of the frame is needed. Set file
                        // position to start of next frame for next
                        // call to Read. FrameOffset is 0.
                        pCkData->SetPos(remainingbytes, RIFF::stream_backward);
                    }
                }
                else remainingbytes = 0;

                currentframeoffset -= skipsamples;

                if (copysamples == 0) {
                    // skip this frame
                    pSrc += framebytes - Channels;
                }
                else {
                    const unsigned char* const param_l = pSrc;
                    if (BitDepth == 24) {
                        if (mode_l != 2) pSrc += 12;

                        if (Channels == 2) { // Stereo
                            const unsigned char* const param_r = pSrc;
                            if (mode_r != 2) pSrc += 12;

                            Decompress24(mode_l, param_l, 2, pSrc, pDst,
                                         skipsamples, copysamples, TruncatedBits);
                            Decompress24(mode_r, param_r, 2, pSrc + rightChannelOffset, pDst + 1,
                                         skipsamples, copysamples, TruncatedBits);
                            pDst += copysamples << 1;
                        }
                        else { // Mono
                            Decompress24(mode_l, param_l, 1, pSrc, pDst,
                                         skipsamples, copysamples, TruncatedBits);
                            pDst += copysamples;
                        }
                    }
                    else { // 16 bit
                        if (mode_l) pSrc += 4;

                        int step;
                        if (Channels == 2) { // Stereo
                            const unsigned char* const param_r = pSrc;
                            if (mode_r) pSrc += 4;

                            step = (2 - mode_l) + (2 - mode_r);
                            Decompress16(mode_l, param_l, step, 2, pSrc, pDst, skipsamples, copysamples);
                            Decompress16(mode_r, param_r, step, 2, pSrc + (2 - mode_l), pDst + 1,
                                         skipsamples, copysamples);
                            pDst += copysamples << 1;
                        }
                        else { // Mono
                            step = 2 - mode_l;
                            Decompress16(mode_l, param_l, step, 1, pSrc, pDst, skipsamples, copysamples);
                            pDst += copysamples;
                        }
                    }
                    pSrc += nextFrameOffset;
                }

                // reload from disk to local buffer if needed
                if (remainingsamples && remainingbytes < WorstCaseFrameSize && pCkData->GetState() == RIFF::stream_ready) {
                    assumedsize    = GuessSize(remainingsamples);
                    pCkData->SetPos(remainingbytes, RIFF::stream_backward);
                    if (pCkData->RemainingBytes() < assumedsize) assumedsize = pCkData->RemainingBytes();
                    remainingbytes = pCkData->Read(pDecompressionBuffer->pStart, assumedsize, 1);
                    pSrc = (unsigned char*) pDecompressionBuffer->pStart;
                }
            } // while

            this->SamplePos += (SampleCount - remainingsamples);
            if (this->SamplePos > this->SamplesTotal) this->SamplePos = this->SamplesTotal;
            return (SampleCount - remainingsamples);
        }
    }

    /**
     * Allocates a decompression buffer for streaming (compressed) samples
     * with Sample::Read(). If you are using more than one streaming thread
     * in your application you <b>HAVE</b> to create a decompression buffer
     * for <b>EACH</b> of your streaming threads and provide it with the
     * Sample::Read() call in order to avoid race conditions and crashes.
     *
     * You should free the memory occupied by the allocated buffer(s) once
     * you don't need one of your streaming threads anymore by calling
     * DestroyDecompressionBuffer().
     *
     * @param MaxReadSize - the maximum size (in sample points) you ever
     *                      expect to read with one Read() call
     * @returns allocated decompression buffer
     * @see DestroyDecompressionBuffer()
     */
    buffer_t Sample::CreateDecompressionBuffer(unsigned long MaxReadSize) {
        buffer_t result;
        const double worstCaseHeaderOverhead =
                (256.0 /*frame size*/ + 12.0 /*header*/ + 2.0 /*compression type flag (stereo)*/) / 256.0;
        result.Size              = (unsigned long) (double(MaxReadSize) * 3.0 /*(24 Bit)*/ * 2.0 /*stereo*/ * worstCaseHeaderOverhead);
        result.pStart            = new int8_t[result.Size];
        result.NullExtensionSize = 0;
        return result;
    }

    /**
     * Free decompression buffer, previously created with
     * CreateDecompressionBuffer().
     *
     * @param DecompressionBuffer - previously allocated decompression
     *                              buffer to free
     */
    void Sample::DestroyDecompressionBuffer(buffer_t& DecompressionBuffer) {
        if (DecompressionBuffer.Size && DecompressionBuffer.pStart) {
            delete[] (int8_t*) DecompressionBuffer.pStart;
            DecompressionBuffer.pStart = NULL;
            DecompressionBuffer.Size   = 0;
            DecompressionBuffer.NullExtensionSize = 0;
        }
    }

    Sample::~Sample() {
        Instances--;
        if (!Instances && InternalDecompressionBuffer.Size) {
            delete[] (unsigned char*) InternalDecompressionBuffer.pStart;
            InternalDecompressionBuffer.pStart = NULL;
            InternalDecompressionBuffer.Size   = 0;
        }
        if (FrameTable) delete[] FrameTable;
        if (RAMCache.pStart) delete[] (int8_t*) RAMCache.pStart;
    }



// *************** DimensionRegion ***************
// *

    uint                               DimensionRegion::Instances       = 0;
    DimensionRegion::VelocityTableMap* DimensionRegion::pVelocityTables = NULL;

    DimensionRegion::DimensionRegion(RIFF::List* _3ewl) : DLS::Sampler(_3ewl) {
        Instances++;

        memcpy(&Crossfade, &SamplerOptions, 4);
        if (!pVelocityTables) pVelocityTables = new VelocityTableMap;

        RIFF::Chunk* _3ewa = _3ewl->GetSubChunk(CHUNK_ID_3EWA);
        _3ewa->ReadInt32(); // unknown, always 0x0000008C ?
        LFO3Frequency = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        EG3Attack     = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        _3ewa->ReadInt16(); // unknown
        LFO1InternalDepth = _3ewa->ReadUint16();
        _3ewa->ReadInt16(); // unknown
        LFO3InternalDepth = _3ewa->ReadInt16();
        _3ewa->ReadInt16(); // unknown
        LFO1ControlDepth = _3ewa->ReadUint16();
        _3ewa->ReadInt16(); // unknown
        LFO3ControlDepth = _3ewa->ReadInt16();
        EG1Attack           = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        EG1Decay1           = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        _3ewa->ReadInt16(); // unknown
        EG1Sustain          = _3ewa->ReadUint16();
        EG1Release          = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        EG1Controller       = DecodeLeverageController(static_cast<_lev_ctrl_t>(_3ewa->ReadUint8()));
        uint8_t eg1ctrloptions        = _3ewa->ReadUint8();
        EG1ControllerInvert           = eg1ctrloptions & 0x01;
        EG1ControllerAttackInfluence  = GIG_EG_CTR_ATTACK_INFLUENCE_EXTRACT(eg1ctrloptions);
        EG1ControllerDecayInfluence   = GIG_EG_CTR_DECAY_INFLUENCE_EXTRACT(eg1ctrloptions);
        EG1ControllerReleaseInfluence = GIG_EG_CTR_RELEASE_INFLUENCE_EXTRACT(eg1ctrloptions);
        EG2Controller       = DecodeLeverageController(static_cast<_lev_ctrl_t>(_3ewa->ReadUint8()));
        uint8_t eg2ctrloptions        = _3ewa->ReadUint8();
        EG2ControllerInvert           = eg2ctrloptions & 0x01;
        EG2ControllerAttackInfluence  = GIG_EG_CTR_ATTACK_INFLUENCE_EXTRACT(eg2ctrloptions);
        EG2ControllerDecayInfluence   = GIG_EG_CTR_DECAY_INFLUENCE_EXTRACT(eg2ctrloptions);
        EG2ControllerReleaseInfluence = GIG_EG_CTR_RELEASE_INFLUENCE_EXTRACT(eg2ctrloptions);
        LFO1Frequency    = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        EG2Attack        = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        EG2Decay1        = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        _3ewa->ReadInt16(); // unknown
        EG2Sustain       = _3ewa->ReadUint16();
        EG2Release       = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        _3ewa->ReadInt16(); // unknown
        LFO2ControlDepth = _3ewa->ReadUint16();
        LFO2Frequency    = (double) GIG_EXP_DECODE(_3ewa->ReadInt32());
        _3ewa->ReadInt16(); // unknown
        LFO2InternalDepth = _3ewa->ReadUint16();
        int32_t eg1decay2 = _3ewa->ReadInt32();
        EG1Decay2          = (double) GIG_EXP_DECODE(eg1decay2);
        EG1InfiniteSustain = (eg1decay2 == 0x7fffffff);
        _3ewa->ReadInt16(); // unknown
        EG1PreAttack      = _3ewa->ReadUint16();
        int32_t eg2decay2 = _3ewa->ReadInt32();
        EG2Decay2         = (double) GIG_EXP_DECODE(eg2decay2);
        EG2InfiniteSustain = (eg2decay2 == 0x7fffffff);
        _3ewa->ReadInt16(); // unknown
        EG2PreAttack      = _3ewa->ReadUint16();
        uint8_t velocityresponse = _3ewa->ReadUint8();
        if (velocityresponse < 5) {
            VelocityResponseCurve = curve_type_nonlinear;
            VelocityResponseDepth = velocityresponse;
        }
        else if (velocityresponse < 10) {
            VelocityResponseCurve = curve_type_linear;
            VelocityResponseDepth = velocityresponse - 5;
        }
        else if (velocityresponse < 15) {
            VelocityResponseCurve = curve_type_special;
            VelocityResponseDepth = velocityresponse - 10;
        }
        else {
            VelocityResponseCurve = curve_type_unknown;
            VelocityResponseDepth = 0;
        }
        uint8_t releasevelocityresponse = _3ewa->ReadUint8();
        if (releasevelocityresponse < 5) {
            ReleaseVelocityResponseCurve = curve_type_nonlinear;
            ReleaseVelocityResponseDepth = releasevelocityresponse;
        }
        else if (releasevelocityresponse < 10) {
            ReleaseVelocityResponseCurve = curve_type_linear;
            ReleaseVelocityResponseDepth = releasevelocityresponse - 5;
        }
        else if (releasevelocityresponse < 15) {
            ReleaseVelocityResponseCurve = curve_type_special;
            ReleaseVelocityResponseDepth = releasevelocityresponse - 10;
        }
        else {
            ReleaseVelocityResponseCurve = curve_type_unknown;
            ReleaseVelocityResponseDepth = 0;
        }
        VelocityResponseCurveScaling = _3ewa->ReadUint8();
        AttenuationControllerThreshold = _3ewa->ReadInt8();
        _3ewa->ReadInt32(); // unknown
        SampleStartOffset = (uint16_t) _3ewa->ReadInt16();
        _3ewa->ReadInt16(); // unknown
        uint8_t pitchTrackDimensionBypass = _3ewa->ReadInt8();
        PitchTrack = GIG_PITCH_TRACK_EXTRACT(pitchTrackDimensionBypass);
        if      (pitchTrackDimensionBypass & 0x10) DimensionBypass = dim_bypass_ctrl_94;
        else if (pitchTrackDimensionBypass & 0x20) DimensionBypass = dim_bypass_ctrl_95;
        else                                       DimensionBypass = dim_bypass_ctrl_none;
        uint8_t pan = _3ewa->ReadUint8();
        Pan         = (pan < 64) ? pan : -((int)pan - 63); // signed 7 bit -> signed 8 bit
        SelfMask = _3ewa->ReadInt8() & 0x01;
        _3ewa->ReadInt8(); // unknown
        uint8_t lfo3ctrl = _3ewa->ReadUint8();
        LFO3Controller           = static_cast<lfo3_ctrl_t>(lfo3ctrl & 0x07); // lower 3 bits
        LFO3Sync                 = lfo3ctrl & 0x20; // bit 5
        InvertAttenuationController = lfo3ctrl & 0x80; // bit 7
        AttenuationController  = DecodeLeverageController(static_cast<_lev_ctrl_t>(_3ewa->ReadUint8()));
        uint8_t lfo2ctrl       = _3ewa->ReadUint8();
        LFO2Controller         = static_cast<lfo2_ctrl_t>(lfo2ctrl & 0x07); // lower 3 bits
        LFO2FlipPhase          = lfo2ctrl & 0x80; // bit 7
        LFO2Sync               = lfo2ctrl & 0x20; // bit 5
        bool extResonanceCtrl  = lfo2ctrl & 0x40; // bit 6
        uint8_t lfo1ctrl       = _3ewa->ReadUint8();
        LFO1Controller         = static_cast<lfo1_ctrl_t>(lfo1ctrl & 0x07); // lower 3 bits
        LFO1FlipPhase          = lfo1ctrl & 0x80; // bit 7
        LFO1Sync               = lfo1ctrl & 0x40; // bit 6
        VCFResonanceController = (extResonanceCtrl) ? static_cast<vcf_res_ctrl_t>(GIG_VCF_RESONANCE_CTRL_EXTRACT(lfo1ctrl))
                                                    : vcf_res_ctrl_none;
        uint16_t eg3depth = _3ewa->ReadUint16();
        EG3Depth = (eg3depth <= 1200) ? eg3depth /* positives */
                                      : (-1) * (int16_t) ((eg3depth ^ 0xffff) + 1); /* binary complementary for negatives */
        _3ewa->ReadInt16(); // unknown
        ChannelOffset = _3ewa->ReadUint8() / 4;
        uint8_t regoptions = _3ewa->ReadUint8();
        MSDecode           = regoptions & 0x01; // bit 0
        SustainDefeat      = regoptions & 0x02; // bit 1
        _3ewa->ReadInt16(); // unknown
        VelocityUpperLimit = _3ewa->ReadInt8();
        _3ewa->ReadInt8(); // unknown
        _3ewa->ReadInt16(); // unknown
        ReleaseTriggerDecay = _3ewa->ReadUint8(); // release trigger decay
        _3ewa->ReadInt8(); // unknown
        _3ewa->ReadInt8(); // unknown
        EG1Hold = _3ewa->ReadUint8() & 0x80; // bit 7
        uint8_t vcfcutoff = _3ewa->ReadUint8();
        VCFEnabled = vcfcutoff & 0x80; // bit 7
        VCFCutoff  = vcfcutoff & 0x7f; // lower 7 bits
        VCFCutoffController = static_cast<vcf_cutoff_ctrl_t>(_3ewa->ReadUint8());
        VCFVelocityScale = _3ewa->ReadUint8();
        _3ewa->ReadInt8(); // unknown
        uint8_t vcfresonance = _3ewa->ReadUint8();
        VCFResonance = vcfresonance & 0x7f; // lower 7 bits
        VCFResonanceDynamic = !(vcfresonance & 0x80); // bit 7
        uint8_t vcfbreakpoint         = _3ewa->ReadUint8();
        VCFKeyboardTracking           = vcfbreakpoint & 0x80; // bit 7
        VCFKeyboardTrackingBreakpoint = vcfbreakpoint & 0x7f; // lower 7 bits
        uint8_t vcfvelocity = _3ewa->ReadUint8();
        VCFVelocityDynamicRange = vcfvelocity % 5;
        VCFVelocityCurve        = static_cast<curve_type_t>(vcfvelocity / 5);
        VCFType = static_cast<vcf_type_t>(_3ewa->ReadUint8());
        if (VCFType == vcf_type_lowpass) {
            if (lfo3ctrl & 0x40) // bit 6
                VCFType = vcf_type_lowpassturbo;
        }

        // get the corresponding velocity->volume table from the table map or create & calculate that table if it doesn't exist yet
        uint32_t tableKey = (VelocityResponseCurve<<16) | (VelocityResponseDepth<<8) | VelocityResponseCurveScaling;
        if (pVelocityTables->count(tableKey)) { // if key exists
            pVelocityAttenuationTable = (*pVelocityTables)[tableKey];
        }
        else {
            pVelocityAttenuationTable =
                CreateVelocityTable(VelocityResponseCurve,
                                    VelocityResponseDepth,
                                    VelocityResponseCurveScaling);
            (*pVelocityTables)[tableKey] = pVelocityAttenuationTable; // put the new table into the tables map
        }

        SampleAttenuation = pow(10.0, -Gain / (20.0 * 655360));
    }

    leverage_ctrl_t DimensionRegion::DecodeLeverageController(_lev_ctrl_t EncodedController) {
        leverage_ctrl_t decodedcontroller;
        switch (EncodedController) {
            // special controller
            case _lev_ctrl_none:
                decodedcontroller.type = leverage_ctrl_t::type_none;
                decodedcontroller.controller_number = 0;
                break;
            case _lev_ctrl_velocity:
                decodedcontroller.type = leverage_ctrl_t::type_velocity;
                decodedcontroller.controller_number = 0;
                break;
            case _lev_ctrl_channelaftertouch:
                decodedcontroller.type = leverage_ctrl_t::type_channelaftertouch;
                decodedcontroller.controller_number = 0;
                break;

            // ordinary MIDI control change controller
            case _lev_ctrl_modwheel:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 1;
                break;
            case _lev_ctrl_breath:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 2;
                break;
            case _lev_ctrl_foot:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 4;
                break;
            case _lev_ctrl_effect1:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 12;
                break;
            case _lev_ctrl_effect2:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 13;
                break;
            case _lev_ctrl_genpurpose1:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 16;
                break;
            case _lev_ctrl_genpurpose2:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 17;
                break;
            case _lev_ctrl_genpurpose3:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 18;
                break;
            case _lev_ctrl_genpurpose4:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 19;
                break;
            case _lev_ctrl_portamentotime:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 5;
                break;
            case _lev_ctrl_sustainpedal:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 64;
                break;
            case _lev_ctrl_portamento:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 65;
                break;
            case _lev_ctrl_sostenutopedal:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 66;
                break;
            case _lev_ctrl_softpedal:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 67;
                break;
            case _lev_ctrl_genpurpose5:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 80;
                break;
            case _lev_ctrl_genpurpose6:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 81;
                break;
            case _lev_ctrl_genpurpose7:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 82;
                break;
            case _lev_ctrl_genpurpose8:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 83;
                break;
            case _lev_ctrl_effect1depth:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 91;
                break;
            case _lev_ctrl_effect2depth:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 92;
                break;
            case _lev_ctrl_effect3depth:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 93;
                break;
            case _lev_ctrl_effect4depth:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 94;
                break;
            case _lev_ctrl_effect5depth:
                decodedcontroller.type = leverage_ctrl_t::type_controlchange;
                decodedcontroller.controller_number = 95;
                break;

            // unknown controller type
            default:
                throw gig::Exception("Unknown leverage controller type.");
        }
        return decodedcontroller;
    }

    DimensionRegion::~DimensionRegion() {
        Instances--;
        if (!Instances) {
            // delete the velocity->volume tables
            VelocityTableMap::iterator iter;
            for (iter = pVelocityTables->begin(); iter != pVelocityTables->end(); iter++) {
                double* pTable = iter->second;
                if (pTable) delete[] pTable;
            }
            pVelocityTables->clear();
            delete pVelocityTables;
            pVelocityTables = NULL;
        }
    }

    /**
     * Returns the correct amplitude factor for the given \a MIDIKeyVelocity.
     * All involved parameters (VelocityResponseCurve, VelocityResponseDepth
     * and VelocityResponseCurveScaling) involved are taken into account to
     * calculate the amplitude factor. Use this method when a key was
     * triggered to get the volume with which the sample should be played
     * back.
     *
     * @param MIDIKeyVelocity  MIDI velocity value of the triggered key (between 0 and 127)
     * @returns                amplitude factor (between 0.0 and 1.0)
     */
    double DimensionRegion::GetVelocityAttenuation(uint8_t MIDIKeyVelocity) {
        return pVelocityAttenuationTable[MIDIKeyVelocity];
    }

    double* DimensionRegion::CreateVelocityTable(curve_type_t curveType, uint8_t depth, uint8_t scaling) {

        // line-segment approximations of the 15 velocity curves

        // linear
        const int lin0[] = { 1, 1, 127, 127 };
        const int lin1[] = { 1, 21, 127, 127 };
        const int lin2[] = { 1, 45, 127, 127 };
        const int lin3[] = { 1, 74, 127, 127 };
        const int lin4[] = { 1, 127, 127, 127 };

        // non-linear
        const int non0[] = { 1, 4, 24, 5, 57, 17, 92, 57, 122, 127, 127, 127 };
        const int non1[] = { 1, 4, 46, 9, 93, 56, 118, 106, 123, 127,
                             127, 127 };
        const int non2[] = { 1, 4, 46, 9, 57, 20, 102, 107, 107, 127,
                             127, 127 };
        const int non3[] = { 1, 15, 10, 19, 67, 73, 80, 80, 90, 98, 98, 127,
                             127, 127 };
        const int non4[] = { 1, 25, 33, 57, 82, 81, 92, 127, 127, 127 };

        // special
        const int spe0[] = { 1, 2, 76, 10, 90, 15, 95, 20, 99, 28, 103, 44,
                             113, 127, 127, 127 };
        const int spe1[] = { 1, 2, 27, 5, 67, 18, 89, 29, 95, 35, 107, 67,
                             118, 127, 127, 127 };
        const int spe2[] = { 1, 1, 33, 1, 53, 5, 61, 13, 69, 32, 79, 74,
                             85, 90, 91, 127, 127, 127 };
        const int spe3[] = { 1, 32, 28, 35, 66, 48, 89, 59, 95, 65, 99, 73,
                             117, 127, 127, 127 };
        const int spe4[] = { 1, 4, 23, 5, 49, 13, 57, 17, 92, 57, 122, 127,
                             127, 127 };

        const int* const curves[] = { non0, non1, non2, non3, non4,
                                      lin0, lin1, lin2, lin3, lin4,
                                      spe0, spe1, spe2, spe3, spe4 };

        double* const table = new double[128];

        const int* curve = curves[curveType * 5 + depth];
        const int s = scaling == 0 ? 20 : scaling; // 0 or 20 means no scaling

        table[0] = 0;
        for (int x = 1 ; x < 128 ; x++) {

            if (x > curve[2]) curve += 2;
            double y = curve[1] + (x - curve[0]) *
                (double(curve[3] - curve[1]) / (curve[2] - curve[0]));
            y = y / 127;

            // Scale up for s > 20, down for s < 20. When
            // down-scaling, the curve still ends at 1.0.
            if (s < 20 && y >= 0.5)
                y = y / ((2 - 40.0 / s) * y + 40.0 / s - 1);
            else
                y = y * (s / 20.0);
            if (y > 1) y = 1;

            table[x] = y;
        }
        return table;
    }


// *************** Region ***************
// *

    Region::Region(Instrument* pInstrument, RIFF::List* rgnList) : DLS::Region((DLS::Instrument*) pInstrument, rgnList) {
        // Initialization
        Dimensions = 0;
        for (int i = 0; i < 256; i++) {
            pDimensionRegions[i] = NULL;
        }
        Layers = 1;
        File* file = (File*) GetParent()->GetParent();
        int dimensionBits = (file->pVersion && file->pVersion->major == 3) ? 8 : 5;

        // Actual Loading

        LoadDimensionRegions(rgnList);

        RIFF::Chunk* _3lnk = rgnList->GetSubChunk(CHUNK_ID_3LNK);
        if (_3lnk) {
            DimensionRegions = _3lnk->ReadUint32();
            for (int i = 0; i < dimensionBits; i++) {
                dimension_t dimension = static_cast<dimension_t>(_3lnk->ReadUint8());
                uint8_t     bits      = _3lnk->ReadUint8();
                if (dimension == dimension_none) { // inactive dimension
                    pDimensionDefinitions[i].dimension  = dimension_none;
                    pDimensionDefinitions[i].bits       = 0;
                    pDimensionDefinitions[i].zones      = 0;
                    pDimensionDefinitions[i].split_type = split_type_bit;
                    pDimensionDefinitions[i].ranges     = NULL;
                    pDimensionDefinitions[i].zone_size  = 0;
                }
                else { // active dimension
                    pDimensionDefinitions[i].dimension = dimension;
                    pDimensionDefinitions[i].bits      = bits;
                    pDimensionDefinitions[i].zones     = 0x01 << bits; // = pow(2,bits)
                    pDimensionDefinitions[i].split_type = (dimension == dimension_layer ||
                                                           dimension == dimension_samplechannel ||
                                                           dimension == dimension_releasetrigger ||
                                                           dimension == dimension_roundrobin ||
                                                           dimension == dimension_random) ? split_type_bit
                                                                                          : split_type_normal;
                    pDimensionDefinitions[i].ranges = NULL; // it's not possible to check velocity dimensions for custom defined ranges at this point
                    pDimensionDefinitions[i].zone_size  =
                        (pDimensionDefinitions[i].split_type == split_type_normal) ? 128 / pDimensionDefinitions[i].zones
                                                                                   : 0;
                    Dimensions++;

                    // if this is a layer dimension, remember the amount of layers
                    if (dimension == dimension_layer) Layers = pDimensionDefinitions[i].zones;
                }
                _3lnk->SetPos(6, RIFF::stream_curpos); // jump forward to next dimension definition
            }

            // check velocity dimension (if there is one) for custom defined zone ranges
            for (uint i = 0; i < Dimensions; i++) {
                dimension_def_t* pDimDef = pDimensionDefinitions + i;
                if (pDimDef->dimension == dimension_velocity) {
                    if (pDimensionRegions[0]->VelocityUpperLimit == 0) {
                        // no custom defined ranges
                        pDimDef->split_type = split_type_normal;
                        pDimDef->ranges     = NULL;
                    }
                    else { // custom defined ranges
                        pDimDef->split_type = split_type_customvelocity;
                        pDimDef->ranges     = new range_t[pDimDef->zones];
                        uint8_t bits[8] = { 0 };
                        int previousUpperLimit = -1;
                        for (int velocityZone = 0; velocityZone < pDimDef->zones; velocityZone++) {
                            bits[i] = velocityZone;
                            DimensionRegion* pDimRegion = GetDimensionRegionByBit(bits);

                            pDimDef->ranges[velocityZone].low  = previousUpperLimit + 1;
                            pDimDef->ranges[velocityZone].high = pDimRegion->VelocityUpperLimit;
                            previousUpperLimit = pDimDef->ranges[velocityZone].high;
                            // fill velocity table
                            for (int i = pDimDef->ranges[velocityZone].low; i <= pDimDef->ranges[velocityZone].high; i++) {
                                VelocityTable[i] = velocityZone;
                            }
                        }
                    }
                }
            }

            // jump to start of the wave pool indices (if not already there)
            File* file = (File*) GetParent()->GetParent();
            if (file->pVersion && file->pVersion->major == 3)
                _3lnk->SetPos(68); // version 3 has a different 3lnk structure
            else
                _3lnk->SetPos(44);

            // load sample references
            for (uint i = 0; i < DimensionRegions; i++) {
                uint32_t wavepoolindex = _3lnk->ReadUint32();
                pDimensionRegions[i]->pSample = GetSampleFromWavePool(wavepoolindex);
            }
        }
        else throw gig::Exception("Mandatory <3lnk> chunk not found.");
    }

    void Region::LoadDimensionRegions(RIFF::List* rgn) {
        RIFF::List* _3prg = rgn->GetSubList(LIST_TYPE_3PRG);
        if (_3prg) {
            int dimensionRegionNr = 0;
            RIFF::List* _3ewl = _3prg->GetFirstSubList();
            while (_3ewl) {
                if (_3ewl->GetListType() == LIST_TYPE_3EWL) {
                    pDimensionRegions[dimensionRegionNr] = new DimensionRegion(_3ewl);
                    dimensionRegionNr++;
                }
                _3ewl = _3prg->GetNextSubList();
            }
            if (dimensionRegionNr == 0) throw gig::Exception("No dimension region found.");
        }
    }

    Region::~Region() {
        for (uint i = 0; i < Dimensions; i++) {
            if (pDimensionDefinitions[i].ranges) delete[] pDimensionDefinitions[i].ranges;
        }
        for (int i = 0; i < 256; i++) {
            if (pDimensionRegions[i]) delete pDimensionRegions[i];
        }
    }

    /**
     * Use this method in your audio engine to get the appropriate dimension
     * region with it's articulation data for the current situation. Just
     * call the method with the current MIDI controller values and you'll get
     * the DimensionRegion with the appropriate articulation data for the
     * current situation (for this Region of course only). To do that you'll
     * first have to look which dimensions with which controllers and in
     * which order are defined for this Region when you load the .gig file.
     * Special cases are e.g. layer or channel dimensions where you just put
     * in the index numbers instead of a MIDI controller value (means 0 for
     * left channel, 1 for right channel or 0 for layer 0, 1 for layer 1,
     * etc.).
     *
     * @param  DimValues  MIDI controller values (0-127) for dimension 0 to 7
     * @returns         adress to the DimensionRegion for the given situation
     * @see             pDimensionDefinitions
     * @see             Dimensions
     */
    DimensionRegion* Region::GetDimensionRegionByValue(const uint DimValues[8]) {
        uint8_t bits[8] = { 0 };
        for (uint i = 0; i < Dimensions; i++) {
            bits[i] = DimValues[i];
            switch (pDimensionDefinitions[i].split_type) {
                case split_type_normal:
                    bits[i] /= pDimensionDefinitions[i].zone_size;
                    break;
                case split_type_customvelocity:
                    bits[i] = VelocityTable[bits[i]];
                    break;
                case split_type_bit: // the value is already the sought dimension bit number
                    const uint8_t limiter_mask = (0xff << pDimensionDefinitions[i].bits) ^ 0xff;
                    bits[i] = bits[i] & limiter_mask; // just make sure the value don't uses more bits than allowed
                    break;
            }
        }
        return GetDimensionRegionByBit(bits);
    }

    /**
     * Returns the appropriate DimensionRegion for the given dimension bit
     * numbers (zone index). You usually use <i>GetDimensionRegionByValue</i>
     * instead of calling this method directly!
     *
     * @param DimBits  Bit numbers for dimension 0 to 7
     * @returns        adress to the DimensionRegion for the given dimension
     *                 bit numbers
     * @see            GetDimensionRegionByValue()
     */
    DimensionRegion* Region::GetDimensionRegionByBit(const uint8_t DimBits[8]) {
        return pDimensionRegions[((((((DimBits[7] << pDimensionDefinitions[6].bits | DimBits[6])
                                                  << pDimensionDefinitions[5].bits | DimBits[5])
                                                  << pDimensionDefinitions[4].bits | DimBits[4])
                                                  << pDimensionDefinitions[3].bits | DimBits[3])
                                                  << pDimensionDefinitions[2].bits | DimBits[2])
                                                  << pDimensionDefinitions[1].bits | DimBits[1])
                                                  << pDimensionDefinitions[0].bits | DimBits[0]];
    }

    /**
     * Returns pointer address to the Sample referenced with this region.
     * This is the global Sample for the entire Region (not sure if this is
     * actually used by the Gigasampler engine - I would only use the Sample
     * referenced by the appropriate DimensionRegion instead of this sample).
     *
     * @returns  address to Sample or NULL if there is no reference to a
     *           sample saved in the .gig file
     */
    Sample* Region::GetSample() {
        if (pSample) return static_cast<gig::Sample*>(pSample);
        else         return static_cast<gig::Sample*>(pSample = GetSampleFromWavePool(WavePoolTableIndex));
    }

    Sample* Region::GetSampleFromWavePool(unsigned int WavePoolTableIndex, progress_t* pProgress) {
        if ((int32_t)WavePoolTableIndex == -1) return NULL;
        File* file = (File*) GetParent()->GetParent();
        unsigned long soughtoffset = file->pWavePoolTable[WavePoolTableIndex];
        Sample* sample = file->GetFirstSample(pProgress);
        while (sample) {
            if (sample->ulWavePoolOffset == soughtoffset) return static_cast<gig::Sample*>(pSample = sample);
            sample = file->GetNextSample();
        }
        return NULL;
    }



// *************** Instrument ***************
// *

    Instrument::Instrument(File* pFile, RIFF::List* insList, progress_t* pProgress) : DLS::Instrument((DLS::File*)pFile, insList) {
        // Initialization
        for (int i = 0; i < 128; i++) RegionKeyTable[i] = NULL;
        RegionIndex = -1;

        // Loading
        RIFF::List* lart = insList->GetSubList(LIST_TYPE_LART);
        if (lart) {
            RIFF::Chunk* _3ewg = lart->GetSubChunk(CHUNK_ID_3EWG);
            if (_3ewg) {
                EffectSend             = _3ewg->ReadUint16();
                Attenuation            = _3ewg->ReadInt32();
                FineTune               = _3ewg->ReadInt16();
                PitchbendRange         = _3ewg->ReadInt16();
                uint8_t dimkeystart    = _3ewg->ReadUint8();
                PianoReleaseMode       = dimkeystart & 0x01;
                DimensionKeyRange.low  = dimkeystart >> 1;
                DimensionKeyRange.high = _3ewg->ReadUint8();
            }
            else throw gig::Exception("Mandatory <3ewg> chunk not found.");
        }
        else throw gig::Exception("Mandatory <lart> list chunk not found.");

        RIFF::List* lrgn = insList->GetSubList(LIST_TYPE_LRGN);
        if (!lrgn) throw gig::Exception("Mandatory chunks in <ins > chunk not found.");
        pRegions = new Region*[Regions];
        for (uint i = 0; i < Regions; i++) pRegions[i] = NULL;
        RIFF::List* rgn = lrgn->GetFirstSubList();
        unsigned int iRegion = 0;
        while (rgn) {
            if (rgn->GetListType() == LIST_TYPE_RGN) {
                __notify_progress(pProgress, (float) iRegion / (float) Regions);
                pRegions[iRegion] = new Region(this, rgn);
                iRegion++;
            }
            rgn = lrgn->GetNextSubList();
        }

        // Creating Region Key Table for fast lookup
        for (uint iReg = 0; iReg < Regions; iReg++) {
            for (int iKey = pRegions[iReg]->KeyRange.low; iKey <= pRegions[iReg]->KeyRange.high; iKey++) {
                RegionKeyTable[iKey] = pRegions[iReg];
            }
        }

        __notify_progress(pProgress, 1.0f); // notify done
    }

    Instrument::~Instrument() {
        for (uint i = 0; i < Regions; i++) {
            if (pRegions) {
                if (pRegions[i]) delete (pRegions[i]);
            }
        }
        if (pRegions) delete[] pRegions;
    }

    /**
     * Returns the appropriate Region for a triggered note.
     *
     * @param Key  MIDI Key number of triggered note / key (0 - 127)
     * @returns    pointer adress to the appropriate Region or NULL if there
     *             there is no Region defined for the given \a Key
     */
    Region* Instrument::GetRegion(unsigned int Key) {
        if (!pRegions || Key > 127) return NULL;
        return RegionKeyTable[Key];
        /*for (int i = 0; i < Regions; i++) {
            if (Key <= pRegions[i]->KeyRange.high &&
                Key >= pRegions[i]->KeyRange.low) return pRegions[i];
        }
        return NULL;*/
    }

    /**
     * Returns the first Region of the instrument. You have to call this
     * method once before you use GetNextRegion().
     *
     * @returns  pointer address to first region or NULL if there is none
     * @see      GetNextRegion()
     */
    Region* Instrument::GetFirstRegion() {
        if (!Regions) return NULL;
        RegionIndex = 1;
        return pRegions[0];
    }

    /**
     * Returns the next Region of the instrument. You have to call
     * GetFirstRegion() once before you can use this method. By calling this
     * method multiple times it iterates through the available Regions.
     *
     * @returns  pointer address to the next region or NULL if end reached
     * @see      GetFirstRegion()
     */
    Region* Instrument::GetNextRegion() {
        if (RegionIndex < 0 || uint32_t(RegionIndex) >= Regions) return NULL;
        return pRegions[RegionIndex++];
    }



// *************** File ***************
// *

    File::File(RIFF::File* pRIFF) : DLS::File(pRIFF) {
        pSamples     = NULL;
        pInstruments = NULL;
    }

    File::~File() {
        // free samples
        if (pSamples) {
            SamplesIterator = pSamples->begin();
            while (SamplesIterator != pSamples->end() ) {
                delete (*SamplesIterator);
                SamplesIterator++;
            }
            pSamples->clear();
            delete pSamples;

        }
        // free instruments
        if (pInstruments) {
            InstrumentsIterator = pInstruments->begin();
            while (InstrumentsIterator != pInstruments->end() ) {
                delete (*InstrumentsIterator);
                InstrumentsIterator++;
            }
            pInstruments->clear();
            delete pInstruments;
        }
    }

    Sample* File::GetFirstSample(progress_t* pProgress) {
        if (!pSamples) LoadSamples(pProgress);
        if (!pSamples) return NULL;
        SamplesIterator = pSamples->begin();
        return static_cast<gig::Sample*>( (SamplesIterator != pSamples->end()) ? *SamplesIterator : NULL );
    }

    Sample* File::GetNextSample() {
        if (!pSamples) return NULL;
        SamplesIterator++;
        return static_cast<gig::Sample*>( (SamplesIterator != pSamples->end()) ? *SamplesIterator : NULL );
    }

    void File::LoadSamples(progress_t* pProgress) {
        RIFF::List* wvpl = pRIFF->GetSubList(LIST_TYPE_WVPL);
        if (wvpl) {
            // just for progress calculation
            int iSampleIndex  = 0;
            int iTotalSamples = wvpl->CountSubLists(LIST_TYPE_WAVE);

            unsigned long wvplFileOffset = wvpl->GetFilePos();
            RIFF::List* wave = wvpl->GetFirstSubList();
            while (wave) {
                if (wave->GetListType() == LIST_TYPE_WAVE) {
                    // notify current progress
                    const float subprogress = (float) iSampleIndex / (float) iTotalSamples;
                    __notify_progress(pProgress, subprogress);

                    if (!pSamples) pSamples = new SampleList;
                    unsigned long waveFileOffset = wave->GetFilePos();
                    pSamples->push_back(new Sample(this, wave, waveFileOffset - wvplFileOffset));

                    iSampleIndex++;
                }
                wave = wvpl->GetNextSubList();
            }
            __notify_progress(pProgress, 1.0); // notify done
        }
        else throw gig::Exception("Mandatory <wvpl> chunk not found.");
    }

    Instrument* File::GetFirstInstrument() {
        if (!pInstruments) LoadInstruments();
        if (!pInstruments) return NULL;
        InstrumentsIterator = pInstruments->begin();
        return (InstrumentsIterator != pInstruments->end()) ? *InstrumentsIterator : NULL;
    }

    Instrument* File::GetNextInstrument() {
        if (!pInstruments) return NULL;
        InstrumentsIterator++;
        return (InstrumentsIterator != pInstruments->end()) ? *InstrumentsIterator : NULL;
    }

    /**
     * Returns the instrument with the given index.
     *
     * @param index     - number of the sought instrument (0..n)
     * @param pProgress - optional: callback function for progress notification
     * @returns  sought instrument or NULL if there's no such instrument
     */
    Instrument* File::GetInstrument(uint index, progress_t* pProgress) {
        if (!pInstruments) {
            // TODO: hack - we simply load ALL samples here, it would have been done in the Region constructor anyway (ATM)

            // sample loading subtask
            progress_t subprogress;
            __divide_progress(pProgress, &subprogress, 3.0f, 0.0f); // randomly schedule 33% for this subtask
            __notify_progress(&subprogress, 0.0f);
            GetFirstSample(&subprogress); // now force all samples to be loaded
            __notify_progress(&subprogress, 1.0f);

            // instrument loading subtask
            if (pProgress && pProgress->callback) {
                subprogress.__range_min = subprogress.__range_max;
                subprogress.__range_max = pProgress->__range_max; // schedule remaining percentage for this subtask
            }
            __notify_progress(&subprogress, 0.0f);
            LoadInstruments(&subprogress);
            __notify_progress(&subprogress, 1.0f);
        }
        if (!pInstruments) return NULL;
        InstrumentsIterator = pInstruments->begin();
        for (uint i = 0; InstrumentsIterator != pInstruments->end(); i++) {
            if (i == index) return *InstrumentsIterator;
            InstrumentsIterator++;
        }
        return NULL;
    }

    void File::LoadInstruments(progress_t* pProgress) {
        RIFF::List* lstInstruments = pRIFF->GetSubList(LIST_TYPE_LINS);
        if (lstInstruments) {
            int iInstrumentIndex = 0;
            RIFF::List* lstInstr = lstInstruments->GetFirstSubList();
            while (lstInstr) {
                if (lstInstr->GetListType() == LIST_TYPE_INS) {
                    // notify current progress
                    const float localProgress = (float) iInstrumentIndex / (float) Instruments;
                    __notify_progress(pProgress, localProgress);

                    // divide local progress into subprogress for loading current Instrument
                    progress_t subprogress;
                    __divide_progress(pProgress, &subprogress, Instruments, iInstrumentIndex);

                    if (!pInstruments) pInstruments = new InstrumentList;
                    pInstruments->push_back(new Instrument(this, lstInstr, &subprogress));

                    iInstrumentIndex++;
                }
                lstInstr = lstInstruments->GetNextSubList();
            }
            __notify_progress(pProgress, 1.0); // notify done
        }
        else throw gig::Exception("Mandatory <lins> list chunk not found.");
    }



// *************** Exception ***************
// *

    Exception::Exception(String Message) : DLS::Exception(Message) {
    }

    void Exception::PrintMessage() {
        std::cout << "gig::Exception: " << Message << std::endl;
    }


// *************** functions ***************
// *

    /**
     * Returns the name of this C++ library. This is usually "libgig" of
     * course. This call is equivalent to RIFF::libraryName() and
     * DLS::libraryName().
     */
    String libraryName() {
        return PACKAGE;
    }

    /**
     * Returns version of this C++ library. This call is equivalent to
     * RIFF::libraryVersion() and DLS::libraryVersion().
     */
    String libraryVersion() {
        return VERSION;
    }

} // namespace gig
