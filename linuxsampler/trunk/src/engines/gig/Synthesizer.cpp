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

#define SYNTHESIZE(IMPL,CHAN,FILTER,INTERPOLATE,LOOP,CONSTPITCH) \
        Synthesizer<IMPL,CHAN,FILTER,INTERPOLATE,LOOP,CONSTPITCH>::SynthesizeFragment( \
        voice, samples, pSrc, skip)

namespace LinuxSampler { namespace gig {

    void SynthesizeFragment_mode1(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,0,0,0,1);
    }

    void SynthesizeFragment_mode2(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode3(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode4(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,0,1,0,0);
    }

    void SynthesizeFragment_mode5(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,0,1,0,1);
    }

    void SynthesizeFragment_mode6(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,0,1,1,0);
    }

    void SynthesizeFragment_mode7(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,0,1,1,1);
    }

    void SynthesizeFragment_mode8(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode9(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode10(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode11(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode12(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,1,1,0,0);
    }

    void SynthesizeFragment_mode13(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,1,1,0,1);
    }

    void SynthesizeFragment_mode14(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,1,1,1,0);
    }

    void SynthesizeFragment_mode15(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,MONO,1,1,1,1);
    }

    void SynthesizeFragment_mode16(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,0,0,0,1);
    }

    void SynthesizeFragment_mode17(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,0,0,0,1);
    }

    void SynthesizeFragment_mode18(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,0,0,1,1);
    }

    void SynthesizeFragment_mode19(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,0,0,1,1);
    }

    void SynthesizeFragment_mode20(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,0,1,0,0);
    }

    void SynthesizeFragment_mode21(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,0,1,0,1);
    }

    void SynthesizeFragment_mode22(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,0,1,1,0);
    }

    void SynthesizeFragment_mode23(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,0,1,1,1);
    }

    void SynthesizeFragment_mode24(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,1,0,0,1);
    }

    void SynthesizeFragment_mode25(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,1,0,0,1);
    }

    void SynthesizeFragment_mode26(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,1,0,1,1);
    }

    void SynthesizeFragment_mode27(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,1,0,1,1);
    }

    void SynthesizeFragment_mode28(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,1,1,0,0);
    }

    void SynthesizeFragment_mode29(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,1,1,0,1);
    }

    void SynthesizeFragment_mode30(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,1,1,1,0);
    }

    void SynthesizeFragment_mode31(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(CPP,STEREO,1,1,1,1);
    }

    void SynthesizeFragment_mode32(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,0,0,1);
    }

    void SynthesizeFragment_mode33(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,0,0,1);
    }

    void SynthesizeFragment_mode34(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode35(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,0,1,1);
    }

    void SynthesizeFragment_mode36(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,0,0);
    }

    void SynthesizeFragment_mode37(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,0,1);
    }

    void SynthesizeFragment_mode38(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,1,0);
    }

    void SynthesizeFragment_mode39(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,0,1,1,1);
    }

    void SynthesizeFragment_mode40(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode41(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,0,0,1);
    }

    void SynthesizeFragment_mode42(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode43(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,0,1,1);
    }

    void SynthesizeFragment_mode44(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,0,0);
    }

    void SynthesizeFragment_mode45(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,0,1);
    }

    void SynthesizeFragment_mode46(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,1,0);
    }

    void SynthesizeFragment_mode47(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,MONO,1,1,1,1);
    }

    void SynthesizeFragment_mode48(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,0,0,1);
    }

    void SynthesizeFragment_mode49(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,0,0,1);
    }

    void SynthesizeFragment_mode50(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,0,1,1);
    }

    void SynthesizeFragment_mode51(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,0,1,1);
    }

    void SynthesizeFragment_mode52(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,0,0);
    }

    void SynthesizeFragment_mode53(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,0,1);
    }

    void SynthesizeFragment_mode54(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,1,0);
    }

    void SynthesizeFragment_mode55(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,0,1,1,1);
    }

    void SynthesizeFragment_mode56(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,0,0,1);
    }

    void SynthesizeFragment_mode57(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,0,0,1);
    }

    void SynthesizeFragment_mode58(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,0,1,1);
    }

    void SynthesizeFragment_mode59(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,0,1,1);
    }

    void SynthesizeFragment_mode60(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,0,0);
    }

    void SynthesizeFragment_mode61(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,0,1);
    }

    void SynthesizeFragment_mode62(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,1,0);
    }

    void SynthesizeFragment_mode63(VOICE &voice, uint samples, sample_t* pSrc, int skip) {
        SYNTHESIZE(ASM_X86_MMX_SSE,STEREO,1,1,1,1);
    }

    void* GetSynthesisFunction(const int SynthesisMode) {
        // Mode Bits:  IMPL,CHAN,FILT,INTERP,LOOP,CONSTPITCH
        switch (SynthesisMode) {
            case 0:  // redundant
            case 1:  return (void*) SynthesizeFragment_mode1;
#if 1
            case 2:  // redundant
            case 3:  return (void*) SynthesizeFragment_mode3;
            case 4:  return (void*) SynthesizeFragment_mode4;
            case 5:  return (void*) SynthesizeFragment_mode5;
            case 6:  return (void*) SynthesizeFragment_mode6;
            case 7:  return (void*) SynthesizeFragment_mode7;
            case 8:  // redundant
            case 9:  return (void*) SynthesizeFragment_mode9;
            case 10: // redundant
            case 11: return (void*) SynthesizeFragment_mode11;
            case 12: return (void*) SynthesizeFragment_mode12;
            case 13: return (void*) SynthesizeFragment_mode13;
            case 14: return (void*) SynthesizeFragment_mode14;
            case 15: return (void*) SynthesizeFragment_mode15;
            case 16: // redundant
            case 17: return (void*) SynthesizeFragment_mode17;
            case 18: // redundant
            case 19: return (void*) SynthesizeFragment_mode19;
            case 20: return (void*) SynthesizeFragment_mode20;
            case 21: return (void*) SynthesizeFragment_mode21;
            case 22: return (void*) SynthesizeFragment_mode22;
            case 23: return (void*) SynthesizeFragment_mode23;
            case 24: // redundant
            case 25: return (void*) SynthesizeFragment_mode25;
            case 26: // redundant
            case 27: return (void*) SynthesizeFragment_mode27;
            case 28: return (void*) SynthesizeFragment_mode28;
            case 29: return (void*) SynthesizeFragment_mode29;
            case 30: return (void*) SynthesizeFragment_mode30;
            case 31: return (void*) SynthesizeFragment_mode31;
            case 32: // redundant
            case 33: return (void*) SynthesizeFragment_mode33;
            case 34: // redundant
            case 35: return (void*) SynthesizeFragment_mode35;
            case 36: return (void*) SynthesizeFragment_mode36;
            case 37: return (void*) SynthesizeFragment_mode37;
            case 38: return (void*) SynthesizeFragment_mode38;
            case 39: return (void*) SynthesizeFragment_mode39;
            case 40: // redundant
            case 41: return (void*) SynthesizeFragment_mode41;
            case 42: // redundant
            case 43: return (void*) SynthesizeFragment_mode43;
            case 44: return (void*) SynthesizeFragment_mode44;
            case 45: return (void*) SynthesizeFragment_mode45;
            case 46: return (void*) SynthesizeFragment_mode46;
            case 47: return (void*) SynthesizeFragment_mode47;
            case 48: // redundant
            case 49: return (void*) SynthesizeFragment_mode49;
            case 50: // redundant
            case 51: return (void*) SynthesizeFragment_mode51;
            case 52: return (void*) SynthesizeFragment_mode52;
            case 53: return (void*) SynthesizeFragment_mode53;
            case 54: return (void*) SynthesizeFragment_mode54;
            case 55: return (void*) SynthesizeFragment_mode55;
            case 56: // redundant
            case 57: return (void*) SynthesizeFragment_mode57;
            case 58: // redundant
            case 59: return (void*) SynthesizeFragment_mode59;
            case 60: return (void*) SynthesizeFragment_mode60;
            case 61: return (void*) SynthesizeFragment_mode61;
            case 62: return (void*) SynthesizeFragment_mode62;
            case 63: return (void*) SynthesizeFragment_mode63;
#endif
            default: {
                printf("gig::Synthesizer: Invalid Synthesis Mode: %d\n", SynthesisMode);
                exit(-1);
            }
        }
    }


}} // namespace LinuxSampler::gig
