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

#ifndef __LIBGIG_HELPER_H__
#define __LIBGIG_HELPER_H__

#include <string.h>
#include <string>
#include <sstream>

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

/**
 * Swaps the order of the data words in the given memory area
 * with a granularity given by \a WordSize.
 *
 * @param pData    - pointer to the memory area to be swapped
 * @param AreaSize - size of the memory area to be swapped (in bytes)
 * @param WordSize - size of the data words (in bytes)
 */
inline void SwapMemoryArea(void* pData, unsigned long AreaSize, uint WordSize) {
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
            delete[] pCache;
            break;
        }
    }
}

#endif // __LIBGIG_HELPER_H__
