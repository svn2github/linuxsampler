/***************************************************************************
 *                                                                         *
 *   libgig - C++ cross-platform Gigasampler format file loader library    *
 *                                                                         *
 *   Copyright (C) 2003 by Christian Schoenebeck                           *
 *                         <cuse@users.sourceforge.net>                    *
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

namespace gig {

// *************** Sample ***************
// *

    unsigned int  Sample::Instances               = 0;
    void*         Sample::pDecompressionBuffer    = NULL;
    unsigned long Sample::DecompressionBufferSize = 0;

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
        uint32_t manufByt = smpl->ReadInt32();
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

        Compressed = (waveList->GetSubChunk(CHUNK_ID_EWAV));
        if (Compressed) {
            ScanCompressedSample();
            if (!pDecompressionBuffer) {
                pDecompressionBuffer    = new int8_t[INITIAL_SAMPLE_BUFFER_SIZE];
                DecompressionBufferSize = INITIAL_SAMPLE_BUFFER_SIZE;
            }
        }
	FrameOffset = 0; // just for streaming compressed samples

        LoopSize = LoopEnd - LoopStart;
    }

    /// Scans compressed samples for mandatory informations (e.g. actual number of total sample points).
    void Sample::ScanCompressedSample() {
        //TODO: we have to add some more scans here (e.g. determine compression rate)
        this->SamplesTotal = 0;
        std::list<unsigned long> frameOffsets;

        // Scanning
        pCkData->SetPos(0);
        while (pCkData->GetState() == RIFF::stream_ready) {
            frameOffsets.push_back(pCkData->GetPos());
            int16_t compressionmode = pCkData->ReadInt16();
            this->SamplesTotal += 2048;
            switch (compressionmode) {
                case 1:   // left channel compressed
                case 256: // right channel compressed
                    pCkData->SetPos(6148, RIFF::stream_curpos);
                    break;
                case 257: // both channels compressed
                    pCkData->SetPos(4104, RIFF::stream_curpos);
                    break;
                default: // both channels uncompressed
                    pCkData->SetPos(8192, RIFF::stream_curpos);
            }
        }
        pCkData->SetPos(0);

        //FIXME: only seen compressed samples with 16 bit stereo so far
        this->FrameSize = 4;
        this->BitDepth  = 16;

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
     *
     * 	buffer_t buf       = pSample->LoadSampleData(acquired_samples);
     * 	long cachedsamples = buf.Size / pSample->FrameSize;
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
     *
     * 	buffer_t buf       = pSample->LoadSampleDataWithNullSamplesExtension(acquired_samples, null_samples);
     * 	long cachedsamples = buf.Size / pSample->FrameSize;
     *
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
     *
     * <i>
     * gig::playback_state_t playbackstate;                           <br>
     * playbackstate.position         = 0;                            <br>
     * playbackstate.reverse          = false;                        <br>
     * playbackstate.loop_cycles_left = pSample->LoopPlayCount;       <br>
     * </i>
     *
     * You don't have to take care of things like if there is actually a loop
     * defined or if the current read position is located within a loop area.
     * The method already handles such cases by itself.
     *
     * @param pBuffer          destination buffer
     * @param SampleCount      number of sample points to read
     * @param pPlaybackState   will be used to store and reload the playback
     *                         state for the next ReadAndLoop() call
     * @returns                number of successfully read sample points
     */
    unsigned long Sample::ReadAndLoop(void* pBuffer, unsigned long SampleCount, playback_state_t* pPlaybackState) {
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
                                readsamples       = Read(&pDst[totalreadsamples * this->FrameSize], Min(samplestoread, samplestoloopend));
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
                                readsamples          = Read(&pDst[totalreadsamples * this->FrameSize], samplestoreadinloop);
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
                        readsamples       = Read(&pDst[totalreadsamples * this->FrameSize], Min(samplestoread, samplestoloopend));
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
                        readsamples          = Read(&pDst[totalreadsamples * this->FrameSize], Min(samplestoreadinloop, samplestoloopend));
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
                        readsamples       = Read(&pDst[totalreadsamples * this->FrameSize], Min(samplestoread, samplestoloopend));
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
            readsamples = Read(&pDst[totalreadsamples * this->FrameSize], samplestoread);
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
     * @param pBuffer      destination buffer
     * @param SampleCount  number of sample points to read
     * @returns            number of successfully read sample points
     * @see                SetPos()
     */
    unsigned long Sample::Read(void* pBuffer, unsigned long SampleCount) {
        if (SampleCount == 0) return 0;
        if (!Compressed) return pCkData->Read(pBuffer, SampleCount, FrameSize); //FIXME: channel inversion due to endian correction?
        else { //FIXME: no support for mono compressed samples yet, are there any?
            if (this->SamplePos >= this->SamplesTotal) return 0;
            //TODO: efficiency: we simply assume here that all frames are compressed, maybe we should test for an average compression rate
            // best case needed buffer size (all frames compressed)
            unsigned long assumedsize      = (SampleCount << 1)  + // *2 (16 Bit, stereo, but assume all frames compressed)
                                             (SampleCount >> 10) + // 10 bytes header per 2048 sample points
                                             8194,                 // at least one worst case sample frame
                          remainingbytes   = 0,           // remaining bytes in the local buffer
                          remainingsamples = SampleCount,
                          copysamples;
            int currentframeoffset = this->FrameOffset;   // offset in current sample frame since last Read()
            this->FrameOffset = 0;

            if (assumedsize > this->DecompressionBufferSize) {
                // local buffer reallocation - hope this won't happen
                if (this->pDecompressionBuffer) delete[] (int8_t*) this->pDecompressionBuffer;
                this->pDecompressionBuffer    = new int8_t[assumedsize << 1]; // double of current needed size
                this->DecompressionBufferSize = assumedsize;
            }

            int16_t  compressionmode, left, dleft, right, dright;
            int8_t*  pSrc = (int8_t*)  this->pDecompressionBuffer;
            int16_t* pDst = (int16_t*) pBuffer;
            remainingbytes = pCkData->Read(pSrc, assumedsize, 1);

            while (remainingsamples) {

                // reload from disk to local buffer if needed
                if (remainingbytes < 8194) {
                    if (pCkData->GetState() != RIFF::stream_ready) {
                        this->SamplePos = this->SamplesTotal;
                        return (SampleCount - remainingsamples);
                    }
                    assumedsize    = remainingsamples;
                    assumedsize    = (assumedsize << 1)  + // *2 (16 Bit, stereo, but assume all frames compressed)
                                     (assumedsize >> 10) + // 10 bytes header per 2048 sample points
                                     8194;                 // at least one worst case sample frame
                    pCkData->SetPos(remainingbytes, RIFF::stream_backward);
                    if (pCkData->RemainingBytes() < assumedsize) assumedsize = pCkData->RemainingBytes();
                    remainingbytes = pCkData->Read(this->pDecompressionBuffer, assumedsize, 1);
                    pSrc = (int8_t*) this->pDecompressionBuffer;
                }

                // determine how many samples in this frame to skip and read
                if (remainingsamples >= 2048) {
                    copysamples       = 2048 - currentframeoffset;
                    remainingsamples -= copysamples;
                }
                else {
                    copysamples = remainingsamples;
                    if (currentframeoffset + copysamples > 2048) {
                        copysamples = 2048 - currentframeoffset;
                        remainingsamples -= copysamples;
                    }
                    else {
                        pCkData->SetPos(remainingbytes, RIFF::stream_backward);
                        remainingsamples = 0;
                        this->FrameOffset = currentframeoffset + copysamples;
                    }
                }

                // decompress and copy current frame from local buffer to destination buffer
                compressionmode = *(int16_t*)pSrc; pSrc+=2;
                switch (compressionmode) {
                    case 1: // left channel compressed
                        remainingbytes -= 6150; // (left 8 bit, right 16 bit, +6 byte header)
                        if (!remainingsamples && copysamples == 2048)
                            pCkData->SetPos(remainingbytes, RIFF::stream_backward);

                        left  = *(int16_t*)pSrc; pSrc+=2;
                        dleft = *(int16_t*)pSrc; pSrc+=2;
                        while (currentframeoffset) {
                            dleft -= *pSrc;
                            left  -= dleft;
                            pSrc+=3; // 8 bit left channel, skip uncompressed right channel (16 bit)
                            currentframeoffset--;
                        }
                        while (copysamples) {
                            dleft -= *pSrc; pSrc++;
                            left  -= dleft;
                            *pDst = left; pDst++;
                            *pDst = *(int16_t*)pSrc; pDst++; pSrc+=2;
                            copysamples--;
                        }
                        break;
                    case 256: // right channel compressed
                        remainingbytes -= 6150; // (left 16 bit, right 8 bit, +6 byte header)
                        if (!remainingsamples && copysamples == 2048)
                            pCkData->SetPos(remainingbytes, RIFF::stream_backward);

                        right  = *(int16_t*)pSrc; pSrc+=2;
                        dright = *(int16_t*)pSrc; pSrc+=2;
                        if (currentframeoffset) {
                            pSrc+=2; // skip uncompressed left channel, now we can increment by 3
                            while (currentframeoffset) {
                                dright -= *pSrc;
                                right  -= dright;
                                pSrc+=3; // 8 bit right channel, skip uncompressed left channel (16 bit)
                                currentframeoffset--;
                            }
                            pSrc-=2; // back aligned to left channel
                        }
                        while (copysamples) {
                            *pDst = *(int16_t*)pSrc; pDst++; pSrc+=2;
                            dright -= *pSrc; pSrc++;
                            right  -= dright;
                            *pDst = right; pDst++;
                            copysamples--;
                        }
                        break;
                    case 257: // both channels compressed
                        remainingbytes -= 4106; // (left 8 bit, right 8 bit, +10 byte header)
                        if (!remainingsamples && copysamples == 2048)
                            pCkData->SetPos(remainingbytes, RIFF::stream_backward);

                        left   = *(int16_t*)pSrc; pSrc+=2;
                        dleft  = *(int16_t*)pSrc; pSrc+=2;
                        right  = *(int16_t*)pSrc; pSrc+=2;
                        dright = *(int16_t*)pSrc; pSrc+=2;
                        while (currentframeoffset) {
                            dleft  -= *pSrc; pSrc++;
                            left   -= dleft;
                            dright -= *pSrc; pSrc++;
                            right  -= dright;
                            currentframeoffset--;
                        }
                        while (copysamples) {
                            dleft  -= *pSrc; pSrc++;
                            left   -= dleft;
                            dright -= *pSrc; pSrc++;
                            right  -= dright;
                            *pDst = left;  pDst++;
                            *pDst = right; pDst++;
                            copysamples--;
                        }
                        break;
                    default: // both channels uncompressed
                        remainingbytes -= 8194; // (left 16 bit, right 16 bit, +2 byte header)
                        if (!remainingsamples && copysamples == 2048)
                            pCkData->SetPos(remainingbytes, RIFF::stream_backward);

                        pSrc += currentframeoffset << 2;
                        currentframeoffset = 0;
                        memcpy(pDst, pSrc, copysamples << 2);
                        pDst += copysamples << 1;
                        pSrc += copysamples << 2;
                        break;
                }
            }
            this->SamplePos += (SampleCount - remainingsamples);
            if (this->SamplePos > this->SamplesTotal) this->SamplePos = this->SamplesTotal;
            return (SampleCount - remainingsamples);
        }
    }

    Sample::~Sample() {
        Instances--;
        if (!Instances && pDecompressionBuffer) delete[] (int8_t*) pDecompressionBuffer;
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
        _3ewa->ReadInt32(); // unknown, allways 0x0000008C ?
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
        EG1Controller       = static_cast<eg1_ctrl_t>(_3ewa->ReadUint8());
        uint8_t eg1ctrloptions        = _3ewa->ReadUint8();
        EG1ControllerInvert           = eg1ctrloptions & 0x01;
        EG1ControllerAttackInfluence  = GIG_EG_CTR_ATTACK_INFLUENCE_EXTRACT(eg1ctrloptions);
        EG1ControllerDecayInfluence   = GIG_EG_CTR_DECAY_INFLUENCE_EXTRACT(eg1ctrloptions);
        EG1ControllerReleaseInfluence = GIG_EG_CTR_RELEASE_INFLUENCE_EXTRACT(eg1ctrloptions);
        EG2Controller       = static_cast<eg2_ctrl_t>(_3ewa->ReadUint8());
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
        AttenuationControlTreshold   = _3ewa->ReadInt8();
        _3ewa->ReadInt32(); // unknown
        SampleStartOffset = (uint16_t) _3ewa->ReadInt16();
        _3ewa->ReadInt16(); // unknown
        uint8_t pitchTrackDimensionBypass = _3ewa->ReadInt8();
        PitchTrack = GIG_PITCH_TRACK_EXTRACT(pitchTrackDimensionBypass);
        if      (pitchTrackDimensionBypass & 0x10) DimensionBypass = dim_bypass_ctrl_94;
        else if (pitchTrackDimensionBypass & 0x20) DimensionBypass = dim_bypass_ctrl_95;
        else                                       DimensionBypass = dim_bypass_ctrl_none;
        uint8_t pan = _3ewa->ReadUint8();
        Pan         = (pan < 64) ? pan : (-1) * (int8_t)pan - 63;
        SelfMask = _3ewa->ReadInt8() & 0x01;
        _3ewa->ReadInt8(); // unknown
        uint8_t lfo3ctrl = _3ewa->ReadUint8();
        LFO3Controller           = static_cast<lfo3_ctrl_t>(lfo3ctrl & 0x07); // lower 3 bits
        LFO3Sync                 = lfo3ctrl & 0x20; // bit 5
        InvertAttenuationControl = lfo3ctrl & 0x80; // bit 7
        if (VCFType == vcf_type_lowpass) {
            if (lfo3ctrl & 0x40) // bit 6
                VCFType = vcf_type_lowpassturbo;
        }
        AttenuationControl = static_cast<attenuation_ctrl_t>(_3ewa->ReadUint8());
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

        // get the corresponding velocity->volume table from the table map or create & calculate that table if it doesn't exist yet
        uint32_t tableKey = (VelocityResponseCurve<<16) | (VelocityResponseDepth<<8) | VelocityResponseCurveScaling;
        if (pVelocityTables->count(tableKey)) { // if key exists
            pVelocityAttenuationTable = (*pVelocityTables)[tableKey];
        }
        else {
            pVelocityAttenuationTable = new double[128];
            switch (VelocityResponseCurve) { // calculate the new table
                case curve_type_nonlinear:
                    for (int velocity = 0; velocity < 128; velocity++) {
                        pVelocityAttenuationTable[velocity] =
                            GIG_VELOCITY_TRANSFORM_NONLINEAR((double)(velocity+1),(double)(VelocityResponseDepth+1),(double)VelocityResponseCurveScaling);
                        if      (pVelocityAttenuationTable[velocity] > 1.0) pVelocityAttenuationTable[velocity] = 1.0;
                        else if (pVelocityAttenuationTable[velocity] < 0.0) pVelocityAttenuationTable[velocity] = 0.0;
                     }
                     break;
                case curve_type_linear:
                    for (int velocity = 0; velocity < 128; velocity++) {
                        pVelocityAttenuationTable[velocity] =
                            GIG_VELOCITY_TRANSFORM_LINEAR((double)velocity,(double)(VelocityResponseDepth+1),(double)VelocityResponseCurveScaling);
                        if      (pVelocityAttenuationTable[velocity] > 1.0) pVelocityAttenuationTable[velocity] = 1.0;
                        else if (pVelocityAttenuationTable[velocity] < 0.0) pVelocityAttenuationTable[velocity] = 0.0;
                    }
                    break;
                case curve_type_special:
                    for (int velocity = 0; velocity < 128; velocity++) {
                        pVelocityAttenuationTable[velocity] =
                            GIG_VELOCITY_TRANSFORM_SPECIAL((double)(velocity+1),(double)(VelocityResponseDepth+1),(double)VelocityResponseCurveScaling);
                        if      (pVelocityAttenuationTable[velocity] > 1.0) pVelocityAttenuationTable[velocity] = 1.0;
                        else if (pVelocityAttenuationTable[velocity] < 0.0) pVelocityAttenuationTable[velocity] = 0.0;
                    }
                    break;
                case curve_type_unknown:
                default:
                    throw gig::Exception("Unknown transform curve type.");
            }
            (*pVelocityTables)[tableKey] = pVelocityAttenuationTable; // put the new table into the tables map
        }
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
     * @param    MIDI velocity value of the triggered key (between 0 and 127)
     * @returns  amplitude factor (between 0.0 and 1.0)
     */
    double DimensionRegion::GetVelocityAttenuation(uint8_t MIDIKeyVelocity) {
        return pVelocityAttenuationTable[MIDIKeyVelocity];
    }



// *************** Region ***************
// *

    Region::Region(Instrument* pInstrument, RIFF::List* rgnList) : DLS::Region((DLS::Instrument*) pInstrument, rgnList) {
        // Initialization
        Dimensions = 0;
        for (int i = 0; i < 32; i++) {
            pDimensionRegions[i] = NULL;
        }

        // Actual Loading

        LoadDimensionRegions(rgnList);

        RIFF::Chunk* _3lnk = rgnList->GetSubChunk(CHUNK_ID_3LNK);
        if (_3lnk) {
            DimensionRegions = _3lnk->ReadUint32();
            for (int i = 0; i < 5; i++) {
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
                                                           dimension == dimension_samplechannel) ? split_type_bit
                                                                                                 : split_type_normal;
                    pDimensionDefinitions[i].ranges = NULL; // it's not possible to check velocity dimensions for custom defined ranges at this point
                    pDimensionDefinitions[i].zone_size  =
                        (pDimensionDefinitions[i].split_type == split_type_normal) ? 128 / pDimensionDefinitions[i].zones
                                                                                   : 0;
                    Dimensions++;
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
                        unsigned int bits[5] = {0,0,0,0,0};
                        int previousUpperLimit = -1;
                        for (int velocityZone = 0; velocityZone < pDimDef->zones; velocityZone++) {
                            bits[i] = velocityZone;
                            DimensionRegion* pDimRegion = GetDimensionRegionByBit(bits[4],bits[3],bits[2],bits[1],bits[0]);

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

            // load sample references
            _3lnk->SetPos(44); // jump to start of the wave pool indices (if not already there)
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
        for (int i = 0; i < 32; i++) {
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
     * @param  Dim4Val  MIDI controller value (0-127) for dimension 4
     * @param  Dim3Val  MIDI controller value (0-127) for dimension 3
     * @param  Dim2Val  MIDI controller value (0-127) for dimension 2
     * @param  Dim1Val  MIDI controller value (0-127) for dimension 1
     * @param  Dim0Val  MIDI controller value (0-127) for dimension 0
     * @returns         adress to the DimensionRegion for the given situation
     * @see             pDimensionDefinitions
     * @see             Dimensions
     */
    DimensionRegion* Region::GetDimensionRegionByValue(uint Dim4Val, uint Dim3Val, uint Dim2Val, uint Dim1Val, uint Dim0Val) {
        unsigned int bits[5] = {Dim0Val,Dim1Val,Dim2Val,Dim3Val,Dim4Val};
        for (uint i = 0; i < Dimensions; i++) {
            switch (pDimensionDefinitions[i].split_type) {
                case split_type_normal:
                    bits[i] /= pDimensionDefinitions[i].zone_size;
                    break;
                case split_type_customvelocity:
                    bits[i] = VelocityTable[bits[i]];
                    break;
                // else the value is already the sought dimension bit number
            }
        }
        return GetDimensionRegionByBit(bits[4],bits[3],bits[2],bits[1],bits[0]);
    }

    /**
     * Returns the appropriate DimensionRegion for the given dimension bit
     * numbers (zone index). You usually use <i>GetDimensionRegionByValue</i>
     * instead of calling this method directly!
     *
     * @param Dim4Bit  Bit number for dimension 4
     * @param Dim3Bit  Bit number for dimension 3
     * @param Dim2Bit  Bit number for dimension 2
     * @param Dim1Bit  Bit number for dimension 1
     * @param Dim0Bit  Bit number for dimension 0
     * @returns        adress to the DimensionRegion for the given dimension
     *                 bit numbers
     * @see            GetDimensionRegionByValue()
     */
    DimensionRegion* Region::GetDimensionRegionByBit(uint8_t Dim4Bit, uint8_t Dim3Bit, uint8_t Dim2Bit, uint8_t Dim1Bit, uint8_t Dim0Bit) {
        return *(pDimensionRegions + ((((((((Dim4Bit << pDimensionDefinitions[3].bits) | Dim3Bit)
                                                     << pDimensionDefinitions[2].bits) | Dim2Bit)
                                                     << pDimensionDefinitions[1].bits) | Dim1Bit)
                                                     << pDimensionDefinitions[0].bits) | Dim0Bit) );
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

    Sample* Region::GetSampleFromWavePool(unsigned int WavePoolTableIndex) {
        File* file = (File*) GetParent()->GetParent();
        unsigned long soughtoffset = file->pWavePoolTable[WavePoolTableIndex];
        Sample* sample = file->GetFirstSample();
        while (sample) {
            if (sample->ulWavePoolOffset == soughtoffset) return static_cast<gig::Sample*>(pSample = sample);
            sample = file->GetNextSample();
        }
        return NULL;
    }



// *************** Instrument ***************
// *

    Instrument::Instrument(File* pFile, RIFF::List* insList) : DLS::Instrument((DLS::File*)pFile, insList) {
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
        RIFF::List* rgn = lrgn->GetFirstSubList();
        unsigned int iRegion = 0;
        while (rgn) {
            if (rgn->GetListType() == LIST_TYPE_RGN) {
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
    }

    Instrument::~Instrument() {
        for (uint i = 0; i < Regions; i++) {
            if (pRegions) {
                if (pRegions[i]) delete (pRegions[i]);
            }
            delete[] pRegions;
        }
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
        if (RegionIndex < 0 || RegionIndex >= Regions) return NULL;
        return pRegions[RegionIndex++];
    }



// *************** File ***************
// *

    File::File(RIFF::File* pRIFF) : DLS::File(pRIFF) {
        pSamples     = NULL;
        pInstruments = NULL;
    }

    Sample* File::GetFirstSample() {
        if (!pSamples) LoadSamples();
        if (!pSamples) return NULL;
        SamplesIterator = pSamples->begin();
        return static_cast<gig::Sample*>( (SamplesIterator != pSamples->end()) ? *SamplesIterator : NULL );
    }

    Sample* File::GetNextSample() {
        if (!pSamples) return NULL;
        SamplesIterator++;
        return static_cast<gig::Sample*>( (SamplesIterator != pSamples->end()) ? *SamplesIterator : NULL );
    }

    void File::LoadSamples() {
        RIFF::List* wvpl = pRIFF->GetSubList(LIST_TYPE_WVPL);
        if (wvpl) {
            unsigned long wvplFileOffset = wvpl->GetFilePos();
            RIFF::List* wave = wvpl->GetFirstSubList();
            while (wave) {
                if (wave->GetListType() == LIST_TYPE_WAVE) {
                    if (!pSamples) pSamples = new SampleList;
                    unsigned long waveFileOffset = wave->GetFilePos();
                    pSamples->push_back(new Sample(this, wave, waveFileOffset - wvplFileOffset));
                }
                wave = wvpl->GetNextSubList();
            }
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
     * @returns  sought instrument or NULL if there's no such instrument
     */
    Instrument* File::GetInstrument(uint index) {
        if (!pInstruments) LoadInstruments();
        if (!pInstruments) return NULL;
        InstrumentsIterator = pInstruments->begin();
        for (uint i = 0; InstrumentsIterator != pInstruments->end(); i++) {
            if (i == index) return *InstrumentsIterator;
            InstrumentsIterator++;
        }
        return NULL;
    }

    void File::LoadInstruments() {
        RIFF::List* lstInstruments = pRIFF->GetSubList(LIST_TYPE_LINS);
        if (lstInstruments) {
            RIFF::List* lstInstr = lstInstruments->GetFirstSubList();
            while (lstInstr) {
                if (lstInstr->GetListType() == LIST_TYPE_INS) {
                    if (!pInstruments) pInstruments = new InstrumentList;
                    pInstruments->push_back(new Instrument(this, lstInstr));
                }
                lstInstr = lstInstruments->GetNextSubList();
            }
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

} // namespace gig
