/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#ifndef __RT_MATH_H__
#define __RT_MATH_H__

#include <math.h>
#include "global.h"

/// Needed for calculating frequency ratio used to pitch a sample
#define TWELVEHUNDREDTH_ROOT_OF_TWO	1.000577789506555

/** Real Time Math
 *
 * Math functions for real time operation.
 */
class RTMath {
    public:
        /**
         * Converts a double to integer type.
         */
        inline static int DoubleToInt(double f) {
            #if ARCH_X86
            int i;
            __asm__ ("fistl %0" : "=m"(i) : "st"(f - 0.5) );
            return i;
            #else
            return (int) f;
            #endif // ARCH_X86
        }

        /**
         * Calculates the frequency ratio for a pitch value given in cents
         * (assuming equal tempered scale of course, divided into 12
         * semitones per octave and 100 cents per semitone).
         *
         * Note: MAX_PITCH (defined in global.h) has to be defined to an
         * appropriate value, otherwise the behavior of this function is
         * undefined, but most probably if MAX_PITCH is too small, the
         * application will crash due to segmentation fault here.
         *
         * @param cents - pitch value in cents (+1200 cents means +1 octave)
         * @returns  frequency ratio (e.g. +2.0 for +1 octave)
         */
        inline static double CentsToFreqRatio(double Cents) {
            int   index_int   = DoubleToInt(Cents); // integer index
            float index_fract = Cents - index_int;  // fractional part of index
            return pCentsToFreqTable[index_int] + index_fract * (pCentsToFreqTable[index_int+1] - pCentsToFreqTable[index_int]);
        }

        template<class T_a, class T_b> inline static T_a Min(T_a a, T_b b) {
            return (b < a) ? b : a;
        }

        template<class T_a, class T_b> inline static T_a Max(T_a a, T_b b) {
            return (b > a) ? b : a;
        }
    private:
        static float  CentsToFreqTable[MAX_PITCH * 1200 * 2 + 1];
        static float* pCentsToFreqTable;

        static float* InitCentsToFreqTable();
};

#endif // __RT_MATH_H__
