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

#ifndef __LS_GIG_SYNTHESIZER_H__
#define __LS_GIG_SYNTHESIZER_H__

#include "../../common/global.h"
#include "../../common/RTMath.h"
#include "../common/Resampler.h"
#include "../common/BiquadFilter.h"
#include "Filter.h"
#include "Voice.h"

#define SYNTHESIS_MODE_SET_CONSTPITCH(iMode,bVal)       if (bVal) iMode |= 0x01; else iMode &= ~0x01   /* (un)set mode bit 0 */
#define SYNTHESIS_MODE_SET_LOOP(iMode,bVal)             if (bVal) iMode |= 0x02; else iMode &= ~0x02   /* (un)set mode bit 1 */
#define SYNTHESIS_MODE_SET_INTERPOLATE(iMode,bVal)      if (bVal) iMode |= 0x04; else iMode &= ~0x04   /* (un)set mode bit 2 */
#define SYNTHESIS_MODE_SET_FILTER(iMode,bVal)           if (bVal) iMode |= 0x08; else iMode &= ~0x08   /* (un)set mode bit 3 */
#define SYNTHESIS_MODE_SET_CHANNELS(iMode,bVal)         if (bVal) iMode |= 0x10; else iMode &= ~0x10   /* (un)set mode bit 4 */
#define SYNTHESIS_MODE_SET_IMPLEMENTATION(iMode,bVal)   if (bVal) iMode |= 0x20; else iMode &= ~0x20   /* (un)set mode bit 5 */
#define SYNTHESIS_MODE_SET_PROFILING(iMode,bVal)   	if (bVal) iMode |= 0x40; else iMode &= ~0x40   /* (un)set mode bit 6 */

#define SYNTHESIS_MODE_GET_CONSTPITCH(iMode)            iMode & 0x01
#define SYNTHESIS_MODE_GET_LOOP(iMode)                  iMode & 0x02
#define SYNTHESIS_MODE_GET_INTERPOLATE(iMode)           iMode & 0x04
#define SYNTHESIS_MODE_GET_FILTER(iMode)                iMode & 0x08
#define SYNTHESIS_MODE_GET_CHANNELS(iMode)              iMode & 0x10
#define SYNTHESIS_MODE_GET_IMPLEMENTATION(iMode)        iMode & 0x20

// that's usually gig::Voice of course, but we make it a macro so we can
// include this code for our synthesis benchmark which uses fake data
// structures
#ifndef VOICE
# define VOICE Voice
#endif // VOICE

namespace LinuxSampler { namespace gig {

    typedef void SynthesizeFragment_Fn(VOICE&, uint, sample_t*, uint);

    void* GetSynthesisFunction(const int SynthesisMode);
    void RunSynthesisFunction(const int SynthesisMode, VOICE& voice, uint Samples, sample_t* pSrc, uint Skip);

    enum channels_t {
        MONO,
        STEREO
    };

    template<implementation_t IMPLEMENTATION, channels_t CHANNELS, bool USEFILTER, bool INTERPOLATE, bool DOLOOP, bool CONSTPITCH>
    class Synthesizer : public __RTMath<IMPLEMENTATION>, public LinuxSampler::Resampler<INTERPOLATE> {
        public:
            template<typename VOICE_T>
            inline static void SynthesizeFragment(VOICE_T& Voice, uint Samples, sample_t* pSrc, uint i) {
                if (IMPLEMENTATION == ASM_X86_MMX_SSE) {
                    float fPos = (float) Voice.Pos;
                    SynthesizeFragment(Voice, Samples, pSrc, i, Voice.pSample->LoopPlayCount,
                                       Voice.pSample->LoopStart,
                                       Voice.pSample->LoopEnd,
                                       Voice.pSample->LoopSize,
                                       Voice.LoopCyclesLeft,
                                       (void *)&fPos,
                                       Voice.PitchBase,
                                       Voice.PitchBend);
                    if (INTERPOLATE) EMMS;
                    Voice.Pos = (double) fPos;
                } else {
                    SynthesizeFragment(Voice, Samples, pSrc, i, Voice.pSample->LoopPlayCount,
                                       Voice.pSample->LoopStart,
                                       Voice.pSample->LoopEnd,
                                       Voice.pSample->LoopSize,
                                       Voice.LoopCyclesLeft,
                                       (void *)&Voice.Pos,
                                       Voice.PitchBase,
                                       Voice.PitchBend);
                }
            }

        //protected:

            template<typename VOICE_T>
            inline static void SynthesizeFragment(VOICE_T& Voice, uint Samples, sample_t* pSrc, uint& i, uint& LoopPlayCount, uint LoopStart, uint LoopEnd, uint LoopSize, uint& LoopCyclesLeft, void* Pos, float& PitchBase, float& PitchBend) {
                const float loopEnd = Float(LoopEnd);
                const float PBbyPB = Mul(PitchBase, PitchBend);
                const float f_LoopStart = Float(LoopStart);
                const float f_LoopSize = Float(LoopSize);
                if (DOLOOP) {
                    if (LoopPlayCount) {
                        // render loop (loop count limited)
                        while (i < Samples && LoopCyclesLeft) {
                            if (CONSTPITCH) {
                                const uint processEnd = Min(Samples, i + DiffToLoopEnd(loopEnd,Pos, PBbyPB) + 1); //TODO: instead of +1 we could also round up
                                while (i < processEnd) Synthesize(Voice, Pos, pSrc, i);
                            }
                            else Synthesize(Voice, Pos, pSrc, i);
                            if (WrapLoop(f_LoopStart, f_LoopSize, loopEnd, Pos)) LoopCyclesLeft--;
                        }
                        // render on without loop
                        while (i < Samples) Synthesize(Voice, Pos, pSrc, i);
                    }
                    else { // render loop (endless loop)
                        while (i < Samples) {
                            if (CONSTPITCH) {
                                const uint processEnd = Min(Samples, i + DiffToLoopEnd(loopEnd, Pos, PBbyPB) + 1); //TODO: instead of +1 we could also round up
                                while (i < processEnd) Synthesize(Voice, Pos, pSrc, i);
                            }
                            else Synthesize(Voice, Pos, pSrc, i);
                            WrapLoop(f_LoopStart, f_LoopSize, loopEnd, Pos);
                        }
                    }
                }
                else { // no looping
                    while (i < Samples) { Synthesize(Voice, Pos, pSrc, i);}
                }
            }

            template<typename VOICE_T>
            inline static void Synthesize(VOICE_T& Voice, void* Pos, sample_t* pSrc, uint& i) {
                Synthesize(pSrc, Pos,
                           Voice.pEngine->pSynthesisParameters[Event::destination_vco][i],
                           Voice.pEngine->pOutputLeft,
                           Voice.pEngine->pOutputRight,
                           i,
                           Voice.pEngine->pSynthesisParameters[Event::destination_vca],
                           &Voice.PanLeft,
                           &Voice.PanRight,
                           Voice.FilterLeft,
                           Voice.FilterRight,
                           Voice.pEngine->pBasicFilterParameters[i],
                           Voice.pEngine->pMainFilterParameters[i]);
            }

            inline static int DiffToLoopEnd(const float& LoopEnd, const void* Pos, const float& Pitch) {
                switch (IMPLEMENTATION) {
                    // pure C++ implementation (thus platform independent)
                    case CPP: {
                        return uint((LoopEnd - *((double *)Pos)) / Pitch);
                    }
                    #if ARCH_X86
                    case ASM_X86_MMX_SSE: {
                        int result;
                        __asm__ __volatile__ (
                            "movss    (%1), %%xmm0  #read loopend\n\t"
                            "subss    (%2), %%xmm0  #sub  pos\n\t"
                            "divss    (%3), %%xmm0  #div  by pitch\n\t"
                            "cvtss2si %%xmm0, %0    #convert to int\n\t"
                            : "=r" (result)   /* %0 */
                            : "r" (&LoopEnd), /* %1 */
                              "r" (Pos),      /* %2 */
                              "r" (&Pitch)    /* %3 */
                        );
                        return result;
                    }
                    #endif // ARCH_X86
                }
            }

            inline static int WrapLoop(const float& LoopStart, const float& LoopSize, const float& LoopEnd, void* vPos) {
                switch (IMPLEMENTATION) {
                    // pure C++ implementation (thus platform independent)
                    case CPP: {
                        double * Pos = (double *)vPos;
                        if (*Pos < LoopEnd) return 0;
                        *Pos = fmod(*Pos - LoopEnd, LoopSize) + LoopStart;
                        return 1;
                    }
                    #if ARCH_X86
                    case ASM_X86_MMX_SSE: {
                        int result;
                        __asm__ __volatile__ (
                            "movss  (%2), %%xmm0          # load LoopEnd\n\t"
                            "movss  (%1), %%xmm1          # load Pos\n\t"
                            "comiss %%xmm0, %%xmm1      # LoopEnd <> Pos\n\t"
                            "movl    $0,%%eax            # result = 0\n\t"
                            "jb     1f                  # jump if no work needs to be done\n\t"
                            "movss    (%3), %%xmm2        # load LoopSize\n\t"
                            "subss    %%xmm0, %%xmm1    # Pos - LoopEnd\n\t"
                            //now the fmodf
                            "movss    %%xmm1, %%xmm3    # xmm3 = (Pos - LoopEnd)\n\t"
                            "divss    %%xmm2, %%xmm1    # (Pos - LoopEnd) / LoopSize\n\t"
                            "cvttss2si %%xmm1, %%eax    # convert to int\n\t"
                            "cvtsi2ss  %%eax, %%xmm1    # convert back to float\n\t"
                            "movss    (%4), %%xmm0      # load LoopStart\n\t"
                            "mulss    %%xmm2, %%xmm1    # LoopSize * int((Pos-LoopEnd)/LoopSize)\n\t"
                            "subss    %%xmm1, %%xmm3    # xmm2 = fmodf(Pos - LoopEnd, LoopSize)\n\t"
                            //done with fmodf
                            "addss    %%xmm0, %%xmm3      # add LoopStart\n\t"
                            "movss    %%xmm3, (%1)        # update Pos\n\t"
                            "movl    $1,%%eax            # result = 1\n\t"
                            ".balign 16 \n\t"
                            "1:\n\t"
                            : "=a" (result)     /* %0 */
                            : "r"  (vPos),      /* %1 */
                              "r"  (&LoopEnd),  /* %2 */
                              "r"  (&LoopSize), /* %3 */
                              "r"  (&LoopStart) /* %4 */
                        );
                        return result;
                    }
                    #endif // ARCH_X86
                }
            }

            inline static void Synthesize(sample_t* pSrc, void* Pos, float& Pitch, float* pOutL, float* pOutR, uint& i, float* Volume, float* PanL, float* PanR, Filter& FilterL, Filter& FilterR, biquad_param_t& bqBase, biquad_param_t& bqMain) {
                switch (IMPLEMENTATION) {
                    // pure C++ implementation (thus platform independent)
                    case CPP: {
                        switch (CHANNELS) {
                            case MONO: {
                                float samplePoint = GetNextSampleMonoCPP(pSrc, (double *)Pos, Pitch);
                                if (USEFILTER) samplePoint = FilterL.Apply(&bqBase, &bqMain, samplePoint);
                                pOutL[i] += samplePoint * Volume[i] * *PanL;
                                pOutR[i] += samplePoint * Volume[i] * *PanR;
                                i++;
                                break;
                            }
                            case STEREO: {
                                stereo_sample_t samplePoint = GetNextSampleStereoCPP(pSrc, (double *)Pos, Pitch);
                                if (USEFILTER) {
                                    samplePoint.left  = FilterL.Apply(&bqBase, &bqMain, samplePoint.left);
                                    samplePoint.right = FilterR.Apply(&bqBase, &bqMain, samplePoint.right);
                                }
                                pOutL[i] += samplePoint.left  * Volume[i] * *PanL;
                                pOutR[i] += samplePoint.right * Volume[i] * *PanR;
                                i++;
                                break;
                            }
                        }
                        break;
                    }
                    #if ARCH_X86
                    // Assembly optimization using the MMX & SSE(1) instruction set (thus only for x86)
                    case ASM_X86_MMX_SSE: {
                        const int ii = i & 0xfffffffc;
                        i += 4;
                        switch (CHANNELS) {
                            case MONO: {
                                GetNext4SamplesMonoMMXSSE(pSrc, (float *)Pos, Pitch); // outputs samples in xmm2
                                if (USEFILTER) {
                                    /* prepare filter input */
                                    __asm__ __volatile__ (
                                        "movaps %xmm2,%xmm0"
                                    );
                                    FilterL.Apply4StepsSSE(&bqBase, &bqMain); // xmm0 input, xmm7 output
                                    __asm__ __volatile__ (
                                        "movaps %xmm7,%xmm2       # mono filter result -> xmm2"
                                    );
                                }
                                /* apply panorama and volume factors */
                                __asm__ __volatile__ (
                                    "movss    (%1),%%xmm0             # load pan left\n\t"
                                    "movss    (%2),%%xmm1             # load pan right\n\t"
                                    "movaps   (%0),%%xmm4             # load vca\n\t"
                                    "shufps   $0x00,%%xmm0,%%xmm0     # copy pan left to the other 3 cells\n\t"
                                    "shufps   $0x00,%%xmm1,%%xmm1     # copy pan right to the other 3 cells\n\t"
                                    "mulps    %%xmm2,%%xmm0           # left  = sample * pan_left\n\t"
                                    "mulps    %%xmm2,%%xmm1           # right = sample * pan_right\n\t"
                                    "mulps    %%xmm4,%%xmm0           # left  = vca * (sample * pan_left)\n\t"
                                    "mulps    %%xmm4,%%xmm1           # right = vca * (sample * pan_right)\n\t"
                                    : /* no output */
                                    : "r" (&Volume[ii]), /* %0 */
                                      "r" (PanL),   /* %1 */
                                      "r" (PanR)    /* %2 */
                                    : "xmm0", /* holds final left  sample (for the 4 samples) at the end */
                                      "xmm1"  /* holds final right sample (for the 4 samples) at the end */
                                );
                                break;
                            }
                            case STEREO: {
                                GetNext4SamplesStereoMMXSSE(pSrc, (float *)Pos, Pitch); // outputs samples in xmm2 (left channel) and xmm3 (right channel)
                                if (USEFILTER) {
                                    __asm__ __volatile__ (
                                        "movaps %xmm2,%xmm0     # prepare left channel for filter\n\t"
                                        "movaps %xmm3,%xmm1     # save right channel not to get overwritten by filter algorithms\n\t"
                                    );
                                    FilterL.Apply4StepsSSE(&bqBase, &bqMain); // xmm0 input, xmm7 output
                                    __asm__ __volatile__ (
                                        "movaps %xmm1,%xmm0     # prepare right channel for filter\n\t"
                                        "movaps %xmm7,%xmm1     # save filter output for left channel\n\t"
                                    );
                                    FilterR.Apply4StepsSSE(&bqBase, &bqMain); // xmm0 input, xmm7 output
                                    __asm__ __volatile__ (
                                        "movaps %xmm1,%xmm2     # result left channel -> xmm2\n\t"
                                        "movaps %xmm7,%xmm3     # result right channel -> xmm3\n\t"
                                    );
                                }
                                /* apply panorama and volume factors */
                                __asm__ __volatile__ (
                                    "movss    (%1),%%xmm0             # load pan left\n\t"
                                    "movss    (%2),%%xmm1             # load pan right\n\t"
                                    "movaps   (%0),%%xmm4             # load vca\n\t"
                                    "shufps   $0x00,%%xmm0,%%xmm0     # copy pan left to the other 3 cells\n\t"
                                    "shufps   $0x00,%%xmm1,%%xmm1     # copy pan right to the other 3 cells\n\t"
                                    "mulps    %%xmm2,%%xmm0           # left  = sample_left  * pan_left\n\t"
                                    "mulps    %%xmm3,%%xmm1           # right = sample_right * pan_right\n\t"
                                    "mulps    %%xmm4,%%xmm0           # left  = vca * (sample_left  * pan_left)\n\t"
                                    "mulps    %%xmm4,%%xmm1           # right = vca * (sample_right * pan_right)\n\t"
                                    : /* no output */
                                    : "r" (&Volume[ii]), /* %0 */
                                      "r" (PanL),   /* %1 */
                                      "r" (PanR)    /* %2 */
                                );
                                break;
                            }
                        }
                        /* mix the 4 samples to the output channels */
                        __asm__ __volatile__ (
                            "addps  (%0),%%xmm0       # mix calculated sample(s) to output left\n\t"
                            "movaps %%xmm0,(%0)       # output to left channel\n\t"
                            "addps  (%1),%%xmm1       # mix calculated sample(s) to output right\n\t"
                            "movaps %%xmm1,(%1)       # output to right channel\n\t"
                            : /* no output */
                            : "r" (&pOutL[ii]), /* %0 - must be 16 byte aligned ! */
                              "r" (&pOutR[ii])  /* %1 - must be 16 byte aligned ! */
                        );
                    }
                    #endif // ARCH_X86
                }
            }
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_SYNTHESIZER_H__
