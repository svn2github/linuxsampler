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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "Synthesizer.h"
#include "Profiler.h"

#define SYNTHESIZE(IMPL,CHAN,FILTER,INTERPOLATE,LOOP,CONSTPITCH) \
        Synthesizer<IMPL,CHAN,FILTER,INTERPOLATE,LOOP,CONSTPITCH>::SynthesizeFragment( \
        voice, samples, pSrc, skip)
#define SYNTHESIZEP(IMPL,CHAN,FILTER,INTERPOLATE,LOOP,CONSTPITCH) \
	RTMath::time_stamp_t start = Profiler::Stamp(); \
        Synthesizer<IMPL,CHAN,FILTER,INTERPOLATE,LOOP,CONSTPITCH>::SynthesizeFragment( \
        voice, samples, pSrc, skip); \
	Profiler::Record(start, samples, skip)

namespace LinuxSampler { namespace gig {

    void SynthesizeFragment_mode01(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,0,0,1);
    }

    void SynthesizeFragment_mode02(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode03(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode04(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,1,0,0);
    }

    void SynthesizeFragment_mode05(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,1,0,1);
    }

    void SynthesizeFragment_mode06(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,1,1,0);
    }

    void SynthesizeFragment_mode07(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,1,1,1);
    }

    void SynthesizeFragment_mode08(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode09(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode0a(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode0b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode0c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,1,0,0);
    }

    void SynthesizeFragment_mode0d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,1,0,1);
    }

    void SynthesizeFragment_mode0e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,1,1,0);
    }

    void SynthesizeFragment_mode0f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,1,1,1);
    }

    void SynthesizeFragment_mode11(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,0,0,1);
    }

    void SynthesizeFragment_mode13(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,0,1,1);
    }

    void SynthesizeFragment_mode14(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,1,0,0);
    }

    void SynthesizeFragment_mode15(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,1,0,1);
    }

    void SynthesizeFragment_mode16(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,1,1,0);
    }

    void SynthesizeFragment_mode17(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,1,1,1);
    }

    void SynthesizeFragment_mode19(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,0,0,1);
    }

    void SynthesizeFragment_mode1b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,0,1,1);
    }

    void SynthesizeFragment_mode1c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,1,0,0);
    }

    void SynthesizeFragment_mode1d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,1,0,1);
    }

    void SynthesizeFragment_mode1e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,1,1,0);
    }

    void SynthesizeFragment_mode1f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,1,1,1);
    }

#if ARCH_X86

    void SynthesizeFragment_mode21(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,0,0,1);
    }

    void SynthesizeFragment_mode23(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode24(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,0,0);
    }

    void SynthesizeFragment_mode25(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,0,1);
    }

    void SynthesizeFragment_mode26(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,1,0);
    }

    void SynthesizeFragment_mode27(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,1,1);
    }

    void SynthesizeFragment_mode29(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode2b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode2c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,0,0);
    }

    void SynthesizeFragment_mode2d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,0,1);
    }

    void SynthesizeFragment_mode2e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,1,0);
    }

    void SynthesizeFragment_mode2f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,1,1);
    }

    void SynthesizeFragment_mode31(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,0,0,1);
    }

    void SynthesizeFragment_mode33(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,0,1,1);
    }

    void SynthesizeFragment_mode34(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,0,0);
    }

    void SynthesizeFragment_mode35(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,0,1);
    }

    void SynthesizeFragment_mode36(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,1,0);
    }

    void SynthesizeFragment_mode37(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,1,1);
    }

    void SynthesizeFragment_mode39(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,0,0,1);
    }

    void SynthesizeFragment_mode3b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,0,1,1);
    }

    void SynthesizeFragment_mode3c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,0,0);
    }

    void SynthesizeFragment_mode3d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,0,1);
    }

    void SynthesizeFragment_mode3e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,1,0);
    }

    void SynthesizeFragment_mode3f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,1,1);
    }

#endif // ARCH_X86

//These are the same thing but with performance monitoring
    void SynthesizeFragment_mode41(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,0,0,0,1);
    }

    void SynthesizeFragment_mode42(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode43(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode44(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,0,1,0,0);
    }

    void SynthesizeFragment_mode45(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,0,1,0,1);
    }

    void SynthesizeFragment_mode46(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,0,1,1,0);
    }

    void SynthesizeFragment_mode47(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,0,1,1,1);
    }

    void SynthesizeFragment_mode48(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode49(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode4a(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode4b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode4c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,1,1,0,0);
    }

    void SynthesizeFragment_mode4d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,1,1,0,1);
    }

    void SynthesizeFragment_mode4e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,1,1,1,0);
    }

    void SynthesizeFragment_mode4f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,MONO,1,1,1,1);
    }

    void SynthesizeFragment_mode51(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,0,0,0,1);
    }

    void SynthesizeFragment_mode53(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,0,0,1,1);
    }

    void SynthesizeFragment_mode54(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,0,1,0,0);
    }

    void SynthesizeFragment_mode55(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,0,1,0,1);
    }

    void SynthesizeFragment_mode56(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,0,1,1,0);
    }

    void SynthesizeFragment_mode57(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,0,1,1,1);
    }

    void SynthesizeFragment_mode59(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,1,0,0,1);
    }

    void SynthesizeFragment_mode5b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,1,0,1,1);
    }

    void SynthesizeFragment_mode5c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,1,1,0,0);
    }

    void SynthesizeFragment_mode5d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,1,1,0,1);
    }

    void SynthesizeFragment_mode5e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,1,1,1,0);
    }

    void SynthesizeFragment_mode5f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(CPP,STEREO,1,1,1,1);
    }

#if ARCH_X86

    void SynthesizeFragment_mode61(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,0,0,0,1);
    }

    void SynthesizeFragment_mode63(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode64(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,0,1,0,0);
    }

    void SynthesizeFragment_mode65(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,0,1,0,1);
    }

    void SynthesizeFragment_mode66(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,0,1,1,0);
    }

    void SynthesizeFragment_mode67(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,0,1,1,1);
    }

    void SynthesizeFragment_mode69(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode6b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode6c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,1,1,0,0);
    }

    void SynthesizeFragment_mode6d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,1,1,0,1);
    }

    void SynthesizeFragment_mode6e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,1,1,1,0);
    }

    void SynthesizeFragment_mode6f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,MONO,1,1,1,1);
    }

    void SynthesizeFragment_mode71(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,0,0,0,1);
    }

    void SynthesizeFragment_mode73(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,0,0,1,1);
    }

    void SynthesizeFragment_mode74(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,0,1,0,0);
    }

    void SynthesizeFragment_mode75(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,0,1,0,1);
    }

    void SynthesizeFragment_mode76(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,0,1,1,0);
    }

    void SynthesizeFragment_mode77(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,0,1,1,1);
    }

    void SynthesizeFragment_mode79(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,1,0,0,1);
    }

    void SynthesizeFragment_mode7b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,1,0,1,1);
    }

    void SynthesizeFragment_mode7c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,1,1,0,0);
    }

    void SynthesizeFragment_mode7d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,1,1,0,1);
    }

    void SynthesizeFragment_mode7e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,1,1,1,0);
    }

    void SynthesizeFragment_mode7f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZEP(ASM_X86_MMX_SSE,STEREO,1,1,1,1);
    }

#endif // ARCH_X86

    void* GetSynthesisFunction(const int SynthesisMode) {
        // Mode Bits:  IMPL,CHAN,FILT,INTERP,LOOP,CONSTPITCH
        switch (SynthesisMode) {
            case 0x00: // redundant
            case 0x01: return (void*) SynthesizeFragment_mode01;
            case 0x02: // redundant
            case 0x03: return (void*) SynthesizeFragment_mode03;
            case 0x04: return (void*) SynthesizeFragment_mode04;
            case 0x05: return (void*) SynthesizeFragment_mode05;
            case 0x06: return (void*) SynthesizeFragment_mode06;
            case 0x07: return (void*) SynthesizeFragment_mode07;
            case 0x08: // redundant
            case 0x09: return (void*) SynthesizeFragment_mode09;
            case 0x0a: // redundant
            case 0x0b: return (void*) SynthesizeFragment_mode0b;
            case 0x0c: return (void*) SynthesizeFragment_mode0c;
            case 0x0d: return (void*) SynthesizeFragment_mode0d;
            case 0x0e: return (void*) SynthesizeFragment_mode0e;
            case 0x0f: return (void*) SynthesizeFragment_mode0f;
            case 0x10: // redundant
            case 0x11: return (void*) SynthesizeFragment_mode11;
            case 0x12: // redundant
            case 0x13: return (void*) SynthesizeFragment_mode13;
            case 0x14: return (void*) SynthesizeFragment_mode14;
            case 0x15: return (void*) SynthesizeFragment_mode15;
            case 0x16: return (void*) SynthesizeFragment_mode16;
            case 0x17: return (void*) SynthesizeFragment_mode17;
            case 0x18: // redundant
            case 0x19: return (void*) SynthesizeFragment_mode19;
            case 0x1a: // redundant
            case 0x1b: return (void*) SynthesizeFragment_mode1b;
            case 0x1c: return (void*) SynthesizeFragment_mode1c;
            case 0x1d: return (void*) SynthesizeFragment_mode1d;
            case 0x1e: return (void*) SynthesizeFragment_mode1e;
            case 0x1f: return (void*) SynthesizeFragment_mode1f;
#if ARCH_X86
            case 0x20: // redundant
            case 0x21: return (void*) SynthesizeFragment_mode21;
            case 0x22: // redundant
            case 0x23: return (void*) SynthesizeFragment_mode23;
            case 0x24: return (void*) SynthesizeFragment_mode24;
            case 0x25: return (void*) SynthesizeFragment_mode25;
            case 0x26: return (void*) SynthesizeFragment_mode26;
            case 0x27: return (void*) SynthesizeFragment_mode27;
            case 0x28: // redundant
            case 0x29: return (void*) SynthesizeFragment_mode29;
            case 0x2a: // redundant
            case 0x2b: return (void*) SynthesizeFragment_mode2b;
            case 0x2c: return (void*) SynthesizeFragment_mode2c;
            case 0x2d: return (void*) SynthesizeFragment_mode2d;
            case 0x2e: return (void*) SynthesizeFragment_mode2e;
            case 0x2f: return (void*) SynthesizeFragment_mode2f;
            case 0x30: // redundant
            case 0x31: return (void*) SynthesizeFragment_mode31;
            case 0x32: // redundant
            case 0x33: return (void*) SynthesizeFragment_mode33;
            case 0x34: return (void*) SynthesizeFragment_mode34;
            case 0x35: return (void*) SynthesizeFragment_mode35;
            case 0x36: return (void*) SynthesizeFragment_mode36;
            case 0x37: return (void*) SynthesizeFragment_mode37;
            case 0x38: // redundant
            case 0x39: return (void*) SynthesizeFragment_mode39;
            case 0x3a: // redundant
            case 0x3b: return (void*) SynthesizeFragment_mode3b;
            case 0x3c: return (void*) SynthesizeFragment_mode3c;
            case 0x3d: return (void*) SynthesizeFragment_mode3d;
            case 0x3e: return (void*) SynthesizeFragment_mode3e;
            case 0x3f: return (void*) SynthesizeFragment_mode3f;
#endif // ARCH_X86

	    //these are the same with performance monitoring
            case 0x40: // redundant
            case 0x41: return (void*) SynthesizeFragment_mode41;
            case 0x42: // redundant
            case 0x43: return (void*) SynthesizeFragment_mode43;
            case 0x44: return (void*) SynthesizeFragment_mode44;
            case 0x45: return (void*) SynthesizeFragment_mode45;
            case 0x46: return (void*) SynthesizeFragment_mode46;
            case 0x47: return (void*) SynthesizeFragment_mode47;
            case 0x48: // redundant
            case 0x49: return (void*) SynthesizeFragment_mode49;
            case 0x4a: // redundant
            case 0x4b: return (void*) SynthesizeFragment_mode4b;
            case 0x4c: return (void*) SynthesizeFragment_mode4c;
            case 0x4d: return (void*) SynthesizeFragment_mode4d;
            case 0x4e: return (void*) SynthesizeFragment_mode4e;
            case 0x4f: return (void*) SynthesizeFragment_mode4f;
            case 0x50: // redundant
            case 0x51: return (void*) SynthesizeFragment_mode51;
            case 0x52: // redundant
            case 0x53: return (void*) SynthesizeFragment_mode53;
            case 0x54: return (void*) SynthesizeFragment_mode54;
            case 0x55: return (void*) SynthesizeFragment_mode55;
            case 0x56: return (void*) SynthesizeFragment_mode56;
            case 0x57: return (void*) SynthesizeFragment_mode57;
            case 0x58: // redundant
            case 0x59: return (void*) SynthesizeFragment_mode59;
            case 0x5a: // redundant
            case 0x5b: return (void*) SynthesizeFragment_mode5b;
            case 0x5c: return (void*) SynthesizeFragment_mode5c;
            case 0x5d: return (void*) SynthesizeFragment_mode5d;
            case 0x5e: return (void*) SynthesizeFragment_mode5e;
            case 0x5f: return (void*) SynthesizeFragment_mode5f;
#if ARCH_X86
            case 0x60: // redundant
            case 0x61: return (void*) SynthesizeFragment_mode61;
            case 0x62: // redundant
            case 0x63: return (void*) SynthesizeFragment_mode63;
            case 0x64: return (void*) SynthesizeFragment_mode64;
            case 0x65: return (void*) SynthesizeFragment_mode65;
            case 0x66: return (void*) SynthesizeFragment_mode66;
            case 0x67: return (void*) SynthesizeFragment_mode67;
            case 0x68: // redundant
            case 0x69: return (void*) SynthesizeFragment_mode69;
            case 0x6a: // redundant
            case 0x6b: return (void*) SynthesizeFragment_mode6b;
            case 0x6c: return (void*) SynthesizeFragment_mode6c;
            case 0x6d: return (void*) SynthesizeFragment_mode6d;
            case 0x6e: return (void*) SynthesizeFragment_mode6e;
            case 0x6f: return (void*) SynthesizeFragment_mode6f;
            case 0x70: // redundant
            case 0x71: return (void*) SynthesizeFragment_mode71;
            case 0x72: // redundant
            case 0x73: return (void*) SynthesizeFragment_mode73;
            case 0x74: return (void*) SynthesizeFragment_mode74;
            case 0x75: return (void*) SynthesizeFragment_mode75;
            case 0x76: return (void*) SynthesizeFragment_mode76;
            case 0x77: return (void*) SynthesizeFragment_mode77;
            case 0x78: // redundant
            case 0x79: return (void*) SynthesizeFragment_mode79;
            case 0x7a: // redundant
            case 0x7b: return (void*) SynthesizeFragment_mode7b;
            case 0x7c: return (void*) SynthesizeFragment_mode7c;
            case 0x7d: return (void*) SynthesizeFragment_mode7d;
            case 0x7e: return (void*) SynthesizeFragment_mode7e;
            case 0x7f: return (void*) SynthesizeFragment_mode7f;
#endif // ARCH_X86
            default: {
                printf("gig::Synthesizer: Invalid Synthesis Mode: %d\n", SynthesisMode);
                exit(-1);
            }
        }
    }

    void RunSynthesisFunction(const int SynthesisMode, VOICE& voice, uint Samples, sample_t* pSrc, uint Skip)
    {
	    SynthesizeFragment_Fn* f = (SynthesizeFragment_Fn*) GetSynthesisFunction(SynthesisMode);
	    f(voice, Samples, pSrc, Skip);
    }

}} // namespace LinuxSampler::gig
