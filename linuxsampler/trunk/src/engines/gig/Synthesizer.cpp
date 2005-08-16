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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "Synthesizer.h"
#include "Profiler.h"

#define SYNTHESIZE(IMPL,CHAN,LOOP,FILTER,INTERPOLATE) \
        Synthesizer<IMPL,CHAN,LOOP,FILTER,INTERPOLATE>::SynthesizeSubFragment( \
        voice, samples, pSrc, skip)
#define SYNTHESIZEP(IMPL,CHAN,FILTER,INTERPOLATE,LOOP,CONSTPITCH) \
	RTMath::time_stamp_t start = Profiler::Stamp(); \
        Synthesizer<IMPL,CHAN,FILTER,INTERPOLATE,LOOP,CONSTPITCH>::SynthesizeFragment( \
        voice, samples, pSrc, skip); \
	Profiler::Record(start, samples, skip)

namespace LinuxSampler { namespace gig {

    void SynthesizeFragment_mode00(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,0,0);
    }

    void SynthesizeFragment_mode01(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,0,1);
    }

    void SynthesizeFragment_mode02(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,1,0);
    }

    void SynthesizeFragment_mode03(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,0,1,1);
    }

    void SynthesizeFragment_mode04(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,0,0);
    }

    void SynthesizeFragment_mode05(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,0,1);
    }

    void SynthesizeFragment_mode06(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,1,0);
    }

    void SynthesizeFragment_mode07(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,MONO,1,1,1);
    }

    void SynthesizeFragment_mode08(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,0,0);
    }

    void SynthesizeFragment_mode09(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,0,1);
    }

    void SynthesizeFragment_mode0a(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,1,0);
    }

    void SynthesizeFragment_mode0b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,0,1,1);
    }

    void SynthesizeFragment_mode0c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,0,0);
    }

    void SynthesizeFragment_mode0d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,0,1);
    }

    void SynthesizeFragment_mode0e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,1,0);
    }

    void SynthesizeFragment_mode0f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(CPP,STEREO,1,1,1);
    }

#if CONFIG_ASM && ARCH_X86

    void SynthesizeFragment_mode10(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,0,0);
    }

    void SynthesizeFragment_mode11(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,0,1);
    }

    void SynthesizeFragment_mode12(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,0);
    }

    void SynthesizeFragment_mode13(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,1);
    }

    void SynthesizeFragment_mode14(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,0,0);
    }

    void SynthesizeFragment_mode15(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,0,1);
    }

    void SynthesizeFragment_mode16(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,0);
    }

    void SynthesizeFragment_mode17(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,1);
    }

    void SynthesizeFragment_mode18(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,0,0);
    }

    void SynthesizeFragment_mode19(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,0,1);
    }

    void SynthesizeFragment_mode1a(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,0);
    }

    void SynthesizeFragment_mode1b(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,1);
    }

    void SynthesizeFragment_mode1c(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,0,0);
    }

    void SynthesizeFragment_mode1d(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,0,1);
    }

    void SynthesizeFragment_mode1e(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,0);
    }

    void SynthesizeFragment_mode1f(VOICE &voice, uint samples, sample_t* pSrc, uint skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,1);
    }

#endif // CONFIG_ASM && ARCH_X86

    void* GetSynthesisFunction(int SynthesisMode) {
        // Mode Bits: IMPL,CHAN,LOOP,FILT,INTERP
        SynthesisMode &= 0x1f;
        switch (SynthesisMode) {
            case 0x00: return (void*) SynthesizeFragment_mode00;
            case 0x01: return (void*) SynthesizeFragment_mode01;
            case 0x02: return (void*) SynthesizeFragment_mode02;
            case 0x03: return (void*) SynthesizeFragment_mode03;
            case 0x04: return (void*) SynthesizeFragment_mode04;
            case 0x05: return (void*) SynthesizeFragment_mode05;
            case 0x06: return (void*) SynthesizeFragment_mode06;
            case 0x07: return (void*) SynthesizeFragment_mode07;
            case 0x08: return (void*) SynthesizeFragment_mode08;
            case 0x09: return (void*) SynthesizeFragment_mode09;
            case 0x0a: return (void*) SynthesizeFragment_mode0a;
            case 0x0b: return (void*) SynthesizeFragment_mode0b;
            case 0x0c: return (void*) SynthesizeFragment_mode0c;
            case 0x0d: return (void*) SynthesizeFragment_mode0d;
            case 0x0e: return (void*) SynthesizeFragment_mode0e;
            case 0x0f: return (void*) SynthesizeFragment_mode0f;
#if CONFIG_ASM && ARCH_X86
            case 0x10: return (void*) SynthesizeFragment_mode10;
            case 0x11: return (void*) SynthesizeFragment_mode11;
            case 0x12: return (void*) SynthesizeFragment_mode12;
            case 0x13: return (void*) SynthesizeFragment_mode13;
            case 0x14: return (void*) SynthesizeFragment_mode14;
            case 0x15: return (void*) SynthesizeFragment_mode15;
            case 0x16: return (void*) SynthesizeFragment_mode16;
            case 0x17: return (void*) SynthesizeFragment_mode17;
            case 0x18: return (void*) SynthesizeFragment_mode18;
            case 0x19: return (void*) SynthesizeFragment_mode19;
            case 0x1a: return (void*) SynthesizeFragment_mode1a;
            case 0x1b: return (void*) SynthesizeFragment_mode1b;
            case 0x1c: return (void*) SynthesizeFragment_mode1c;
            case 0x1d: return (void*) SynthesizeFragment_mode1d;
            case 0x1e: return (void*) SynthesizeFragment_mode1e;
            case 0x1f: return (void*) SynthesizeFragment_mode1f;
#endif // CONFIG_ASM && ARCH_X86
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
