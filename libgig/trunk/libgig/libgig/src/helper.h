/***************************************************************************
 *                                                                         *
 *   libgig - C++ cross-platform Gigasampler format file access library    *
 *                                                                         *
 *   Copyright (C) 2003-2014 by Christian Schoenebeck                      *
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

#ifndef __LIBGIG_HELPER_H__
#define __LIBGIG_HELPER_H__

#include <string.h>
#include <string>
#include <sstream>

#if defined(WIN32) && !HAVE_CONFIG_H
# include "../win32/libgig_private.h" // like config.h, automatically generated by Dev-C++
# define PACKAGE "libgig"
# define VERSION VER_STRING // VER_STRING defined in libgig_private.h
#endif // WIN32

#include "RIFF.h"

// *************** Helper Functions **************
// *

template<class T> inline std::string ToString(T o) {
    std::stringstream ss;
    ss << o;
    return ss.str();
}

inline long Min(long A, long B) {
    return (A > B) ? B : A;
}

inline long Abs(long val) {
    return (val > 0) ? val : -val;
}

inline void swapBytes_16(void* Word) {
    uint8_t byteCache = *((uint8_t*) Word);
    *((uint8_t*) Word)     = *((uint8_t*) Word + 1);
    *((uint8_t*) Word + 1) = byteCache;
}

inline void swapBytes_32(void* Word) {
    uint8_t byteCache = *((uint8_t*) Word);
    *((uint8_t*) Word)     = *((uint8_t*) Word + 3);
    *((uint8_t*) Word + 3) = byteCache;
    byteCache = *((uint8_t*) Word + 1);
    *((uint8_t*) Word + 1) = *((uint8_t*) Word + 2);
    *((uint8_t*) Word + 2) = byteCache;
}

inline void swapBytes_64(void* Word) {
    uint8_t byteCache = ((uint8_t*)Word)[0];
    ((uint8_t*)Word)[0] = ((uint8_t*)Word)[7];
    ((uint8_t*)Word)[7] = byteCache;
    byteCache = ((uint8_t*)Word)[1];
    ((uint8_t*)Word)[1] = ((uint8_t*)Word)[6];
    ((uint8_t*)Word)[6] = byteCache;
    byteCache = ((uint8_t*)Word)[2];
    ((uint8_t*)Word)[2] = ((uint8_t*)Word)[5];
    ((uint8_t*)Word)[5] = byteCache;
    byteCache = ((uint8_t*)Word)[3];
    ((uint8_t*)Word)[3] = ((uint8_t*)Word)[4];
    ((uint8_t*)Word)[4] = byteCache;
}

inline void swapBytes(void* Word, uint64_t WordSize) {
    uint8_t byteCache;
    uint64_t lo = 0, hi = WordSize - 1;
    for (; lo < hi; hi--, lo++) {
        byteCache = *((uint8_t*) Word + lo);
        *((uint8_t*) Word + lo) = *((uint8_t*) Word + hi);
        *((uint8_t*) Word + hi) = byteCache;
    }
}

/**
 * Stores a 16 bit integer in memory using little-endian format.
 *
 * @param pData - memory pointer
 * @param data  - integer to be stored
 */
inline void store16(uint8_t* pData, uint16_t data) {
    pData[0] = data;
    pData[1] = data >> 8;
}

/**
 * Stores a 32 bit integer in memory using little-endian format.
 *
 * @param pData - memory pointer
 * @param data  - integer to be stored
 */
inline void store32(uint8_t* pData, uint32_t data) {
    pData[0] = data;
    pData[1] = data >> 8;
    pData[2] = data >> 16;
    pData[3] = data >> 24;
}

/**
 * Loads a 32 bit integer in memory using little-endian format.
 *
 * @param pData - memory pointer
 * @returns 32 bit data word
 */
inline uint32_t load32(uint8_t* pData) {
    return uint32_t(pData[0])       |
           uint32_t(pData[1]) << 8  |
           uint32_t(pData[2]) << 16 |
           uint32_t(pData[3]) << 24;
}

/**
 * Swaps the order of the data words in the given memory area
 * with a granularity given by \a WordSize.
 *
 * @param pData    - pointer to the memory area to be swapped
 * @param AreaSize - size of the memory area to be swapped (in bytes)
 * @param WordSize - size of the data words (in bytes)
 */
inline void SwapMemoryArea(void* pData, unsigned long AreaSize, uint WordSize) {
    if (!AreaSize) return; // AreaSize==0 would cause a segfault here
    switch (WordSize) { // TODO: unefficient
        case 1: {
            uint8_t* pDst = (uint8_t*) pData;
            uint8_t  cache;
            unsigned long lo = 0, hi = AreaSize - 1;
            for (; lo < hi; hi--, lo++) {
                cache    = pDst[lo];
                pDst[lo] = pDst[hi];
                pDst[hi] = cache;
            }
            break;
        }
        case 2: {
            uint16_t* pDst = (uint16_t*) pData;
            uint16_t  cache;
            unsigned long lo = 0, hi = (AreaSize >> 1) - 1;
            for (; lo < hi; hi--, lo++) {
                cache    = pDst[lo];
                pDst[lo] = pDst[hi];
                pDst[hi] = cache;
            }
            break;
        }
        case 4: {
            uint32_t* pDst = (uint32_t*) pData;
            uint32_t  cache;
            unsigned long lo = 0, hi = (AreaSize >> 2) - 1;
            for (; lo < hi; hi--, lo++) {
                cache    = pDst[lo];
                pDst[lo] = pDst[hi];
                pDst[hi] = cache;
            }
            break;
        }
        default: {
            uint8_t* pCache = new uint8_t[WordSize]; // TODO: unefficient
            unsigned long lo = 0, hi = AreaSize - WordSize;
            for (; lo < hi; hi -= WordSize, lo += WordSize) {
                memcpy(pCache, (uint8_t*) pData + lo, WordSize);
                memcpy((uint8_t*) pData + lo, (uint8_t*) pData + hi, WordSize);
                memcpy((uint8_t*) pData + hi, pCache, WordSize);
            }
            if (pCache) delete[] pCache;
            break;
        }
    }
}

/** @brief Load given info field (string).
 *
 * Load info field string from given info chunk (\a ck) and save value to \a s.
 */
inline void LoadString(RIFF::Chunk* ck, std::string& s) {
    if (ck) {
        const char* str = (char*)ck->LoadChunkData();
        int size = (int) ck->GetSize();
        int len;
        for (len = 0 ; len < size ; len++)
            if (str[len] == '\0') break;
        s.assign(str, len);
        ck->ReleaseChunkData();
    }
}

/** @brief Apply given INFO field to the respective chunk.
 *
 * Apply given info value string to given info chunk, which is a
 * subchunk of INFO list chunk \a lstINFO. If the given chunk already
 * exists, value \a s will be applied. Otherwise if it doesn't exist yet
 * and either \a s or \a sDefault is not an empty string, such a chunk
 * will be created and either \a s or \a sDefault will be applied
 * (depending on which one is not an empty string, if both are not an
 * empty string \a s will be preferred).
 *
 * @param ChunkID  - 32 bit RIFF chunk ID of INFO subchunk (only used in case \a ck is NULL)
 * @param ck       - INFO (sub)chunk where string should be stored to
 * @param lstINFO  - parent (INFO) RIFF list chunk
 * @param s        - current value of info field
 * @param sDefault - default value
 * @param bUseFixedLengthStrings - should a specific string size be forced in the chunk?
 * @param size     - wanted size of the INFO chunk. This is ignored if bUseFixedLengthStrings is false.
 */
inline void SaveString(uint32_t ChunkID, RIFF::Chunk* ck, RIFF::List* lstINFO, const std::string& s, const std::string& sDefault, bool bUseFixedLengthStrings, int size) {
    if (ck) { // if chunk exists already, use 's' as value
        if (!bUseFixedLengthStrings) size = (int) s.size() + 1;
        ck->Resize(size);
        char* pData = (char*) ck->LoadChunkData();
        strncpy(pData, s.c_str(), size);
    } else if (s != "" || sDefault != "" || bUseFixedLengthStrings) { // create chunk
        const std::string& sToSave = (s != "") ? s : sDefault;
        if (!bUseFixedLengthStrings) size = (int) sToSave.size() + 1;
        ck = lstINFO->AddSubChunk(ChunkID, size);
        char* pData = (char*) ck->LoadChunkData();
        strncpy(pData, sToSave.c_str(), size);
    }
}

// private helper function to convert progress of a subprocess into the global progress
inline void __notify_progress(RIFF::progress_t* pProgress, float subprogress) {
    if (pProgress && pProgress->callback) {
        const float totalrange    = pProgress->__range_max - pProgress->__range_min;
        const float totalprogress = pProgress->__range_min + subprogress * totalrange;
        pProgress->factor         = totalprogress;
        pProgress->callback(pProgress); // now actually notify about the progress
    }
}

// private helper function to divide a progress into subprogresses
inline void __divide_progress(RIFF::progress_t* pParentProgress, RIFF::progress_t* pSubProgress, float totalTasks, float currentTask) {
    if (pParentProgress && pParentProgress->callback) {
        const float totalrange    = pParentProgress->__range_max - pParentProgress->__range_min;
        pSubProgress->callback    = pParentProgress->callback;
        pSubProgress->custom      = pParentProgress->custom;
        pSubProgress->__range_min = pParentProgress->__range_min + totalrange * currentTask / totalTasks;
        pSubProgress->__range_max = pSubProgress->__range_min + totalrange / totalTasks;
    }
}

#endif // __LIBGIG_HELPER_H__
