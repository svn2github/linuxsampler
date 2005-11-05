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

#include "RTMath.h"

float  RTMathBase::CentsToFreqTable[CONFIG_MAX_PITCH * 1200 * 2 + 1]; // +-1200 cents per octave
float* RTMathBase::pCentsToFreqTable(InitCentsToFreqTable());

#if defined(__APPLE__)
#include <mach/mach_time.h>
typedef uint64_t time_stamp_t;
static inline time_stamp_t GetMachTime() {
    return (time_stamp_t) mach_absolute_time();
}
#endif

/*
 * Creates a real time stamp for the current moment. Out of efficiency this
 * is implemented in inline assembly for each CPU independently; we currently
 * don't use a generic solution for CPUs that are not yet covered by the
 * assembly code, instead an error message is prompted on compile time, forcing
 * the user to contact us.
 */
RTMathBase::time_stamp_t RTMathBase::CreateTimeStamp() {
    #if defined(__i386__) || defined(__x86_64__)
    uint64_t t;
    __asm__ __volatile__ ("rdtsc" : "=A" (t));
    return t >> 8;
    #elif defined(__ia64__)
    time_stamp_t t;
    __asm__ __volatile__ ("mov %0=ar.itc" : "=r"(t));
    return t;
    #elif defined(__powerpc__)
    time_stamp_t t;
    __asm__ __volatile__ (
        "98:	mftb %0\n"
        "99:\n"
        ".section __ftr_fixup,\"a\"\n"
        "	.long %1\n"
        "	.long 0\n"
        "	.long 98b\n"
        "	.long 99b\n"
        ".previous"
        : "=r" (t) : "i" (0x00000100)
    );
    return t;
    #elif defined(__alpha__)
    time_stamp_t t;
    __asm__ __volatile__ ("rpcc %0" : "=r"(t));
    return t;
    #elif defined(__APPLE__)
    return GetMachTime();
    #else // we don't want to use a slow generic solution
    #  error "Sorry, LinuxSampler lacks time stamp code for your system."
    #  error "Please report this error and the CPU you are using to the LinuxSampler developers mailing list!"
    #endif
}

/**
 * Will automatically be called once to initialize the 'Cents to frequency
 * ratio' table.
 */
float* RTMathBase::InitCentsToFreqTable() {
    float* pMiddleOfTable = &CentsToFreqTable[CONFIG_MAX_PITCH * 1200];
    for (int i = -CONFIG_MAX_PITCH * 1200; i <= CONFIG_MAX_PITCH * 1200; i++) {
        pMiddleOfTable[i] = pow(TWELVEHUNDREDTH_ROOT_OF_TWO, i);
    }
    return pMiddleOfTable;
}
