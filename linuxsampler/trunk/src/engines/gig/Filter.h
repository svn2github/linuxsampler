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

#ifndef __LS_GIG_FILTER_H__
#define __LS_GIG_FILTER_H__

#include "../../common/global.h"

#if DEBUG_HEADERS
# warning Filter.h included
#endif // DEBUG_HEADERS

#include "../common/BiquadFilter.h"

// TODO: Gigasampler's "Turbo Lowpass" and "Bandreject" filters not implemented yet

#include "../../lib/fileloader/libgig/gig.h"

#define LSF_BW 0.9
#define LSF_FB 0.9f

namespace LinuxSampler { namespace gig {

    /**
     * These are filters similar to the ones from Gigasampler.
     */
    class Filter {
        protected:
            BandpassFilter    BasicBPFilter;
            HighpassFilter    HPFilter;
            BandpassFilter    BPFilter;
            LowpassFilter     LPFilter;
            BiquadFilter*     pFilter;
            bq_t              scale;
            bq_t              resonance;
            bq_t              cutoff;
            ::gig::vcf_type_t Type;
            static const float fFB = LSF_FB;
        public:

            Filter() {
                // set filter type to 'lowpass' by default
                pFilter = &LPFilter;
                Type    = ::gig::vcf_type_lowpass;
            }

            inline bq_t Cutoff()     { return cutoff; }

            inline bq_t Resonance()  { return resonance; }

            inline void SetType(::gig::vcf_type_t FilterType) {
                switch (FilterType) {
                    case ::gig::vcf_type_highpass:
                        pFilter = &HPFilter;
                        break;
                    case ::gig::vcf_type_bandreject: //TODO: not implemented yet
                        FilterType = ::gig::vcf_type_bandpass;
                    case ::gig::vcf_type_bandpass:
                        pFilter = &BPFilter;
                        break;
                    case ::gig::vcf_type_lowpassturbo: //TODO: not implemented yet
                    default:
                        FilterType = ::gig::vcf_type_lowpass;
                    case ::gig::vcf_type_lowpass:
                        pFilter = &LPFilter;

                }
                Type = FilterType;
            }

            inline void SetParameters(bq_t cutoff, bq_t resonance, bq_t fs) {
                BasicBPFilter.SetParameters(cutoff, 0.7, fs);
                switch (Type) {
                    case ::gig::vcf_type_highpass:
                        HPFilter.SetParameters(cutoff, 1.0 - resonance * LSF_BW, fs);
                        break;
                    case ::gig::vcf_type_bandpass:
                        BPFilter.SetParameters(cutoff, 1.0 - resonance * LSF_BW, fs);
                        break;
                    case ::gig::vcf_type_lowpass:
                        LPFilter.SetParameters(cutoff, 1.0 - resonance * LSF_BW, fs);
                        break;
                }
                this->scale     = 1.0f - resonance * 0.7f;
                this->resonance = resonance;
                this->cutoff    = cutoff;
            }

            inline void SetParameters(biquad_param_t* base, biquad_param_t* main, bq_t cutoff, bq_t resonance, bq_t fs) {
                BasicBPFilter.SetParameters(base, cutoff, 0.7, fs);
                switch (Type) {
                    case ::gig::vcf_type_highpass:
                        HPFilter.SetParameters(main, cutoff, 1.0 - resonance * LSF_BW, fs);
                        break;
                    case ::gig::vcf_type_bandpass:
                        BPFilter.SetParameters(main, cutoff, 1.0 - resonance * LSF_BW, fs);
                        break;
                    case ::gig::vcf_type_lowpass:
                        LPFilter.SetParameters(main, cutoff, 1.0 - resonance * LSF_BW, fs);
                        break;
                }
                this->scale     = 1.0f - resonance * 0.7f;
                this->resonance = resonance;
                this->cutoff    = cutoff;
            }

            void Reset() {
                BasicBPFilter.Reset();
                HPFilter.Reset();
                BPFilter.Reset();
                LPFilter.Reset();
            }

            inline bq_t Apply(const bq_t in) {
                return pFilter->Apply(in) * this->scale +
                        BasicBPFilter.ApplyFB(in, this->resonance * LSF_FB) * this->resonance;
            }

            inline bq_t Apply(biquad_param_t* base, biquad_param_t* main, const bq_t in) {
                return pFilter->Apply(main, in) * this->scale +
                        BasicBPFilter.ApplyFB(base, in, this->resonance * LSF_FB) * this->resonance;
            }

#if ARCH_X86
            // expects to find input in xmm0 and leaves output in xmm7
            inline void Apply4StepsSSE(biquad_param_t* base, biquad_param_t* main) {
                float fb;
                __asm__ __volatile__ (
                    "movss %0, %%xmm4\n\t"
                    "mulss %1, %%xmm4      # this->resonance * LSF_FB\n\t"
                    "movss %%xmm4, %2\n\t"
                    :: "m" (fFB),       /* %0 */
                       "m" (resonance), /* %1 */
                       "m" (fb)         /* %2 */
                );
                BasicBPFilter.ApplyFB4StepsSSE(base, fb); // leaves output in xmm7
                __asm__ __volatile__ (
                    "movss  %0, %%xmm4\n\t"
                    "shufps $0, %%xmm4, %%xmm4     # copy to other 3 cells\n\t"
                    "mulps  %%xmm4, %%xmm7         # ApplyFB() * this->resonance\n\t"
                    :: "m" (resonance) /* %0 */
                );
                pFilter->Apply4StepsSSE(main); // leaves output in xmm6
                __asm__ __volatile__ (
                    "movss  %0, %%xmm5\n\t"
                    "shufps $0, %%xmm5, %%xmm5     # copy to other 3 cells\n\t"
                    "mulps  %%xmm5, %%xmm6         # Apply() * this->scale\n\t"
                    "addps  %%xmm6, %%xmm7         # xmm7 = result\n\t"
                    :: "m" (scale) /* %0 */
                );
            }
#endif // ARCH_X86

    };

}} //namespace LinuxSampler::gig

#endif // __LS_GIG_FILTER_H__
