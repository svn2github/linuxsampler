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
     * This is a filter similar to the ones from Gigasampler.
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
        public:
            bool Enabled;

            inline Filter() {
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
                        Type = ::gig::vcf_type_bandpass;
                    case ::gig::vcf_type_bandpass:
                        pFilter = &BPFilter;
                        break;
                    case ::gig::vcf_type_lowpassturbo: //TODO: not implemented yet
                    default:
                        Type = ::gig::vcf_type_lowpass;
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

            inline bq_t Apply(const bq_t in) {
                return (Enabled) ? pFilter->Apply(in) * this->scale +
                                  BasicBPFilter.ApplyFB(in, this->resonance * LSF_FB) * this->resonance
                                : in;
            }
    };

}} //namespace LinuxSampler::gig

#endif // __LS_GIG_FILTER_H__
