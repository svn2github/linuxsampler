/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
 *   Copyright (C) 2006 Christian Schoenebeck and Andreas Persson          *
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

#include <gig.h>

namespace LinuxSampler { namespace gig {

    class FilterBase {
    public:
        virtual float Apply(float x) = 0;
        virtual void SetParameters(float f1, float f2, float scale) = 0;
        virtual ~FilterBase() {}

        virtual void Reset() {
            y1 = y2 = y3 = x1 = x2 = x3 = 0;
        }

    private:
        float y1, y2, y3;

    protected:
        float a1, a2, a3, x1, x2, x3;

        void KillDenormal(float& f) {
            f += 1e-18f;
            f -= 1e-18f;
        }

        float ApplyA(float x) {
            float y = x - a1 * y1 - a2 * y2 - a3 * y3;
            KillDenormal(y);
            y3 = y2;
            y2 = y1;
            y1 = y;
            return y;
        }
    };

    class LowpassFilter : public FilterBase {
    protected:
        float b0;
    public:
        float Apply(float x) {
            return ApplyA(b0 * x);
        }

        void SetParameters(float f1, float f2, float scale) {
            float f1_2 = f1 * f1;
            b0 = f1_2 * scale;
            a1 = f2;
            a2 = f1_2 - 1;
            a3 = -f2;
        }
    };

    class BandpassFilter : public FilterBase {
        float b0, b2;
    public:
        float Apply(float x) {
            float y = ApplyA(b0 * x + b2 * x2);
            x2 = x1;
            x1 = x;
            return y;
        }

        void SetParameters(float f1, float f2, float scale) {
            b0 = f1 * scale;
            b2 = -b0;
            a1 = f2;
            a2 = f1 * f1 - 1;
            a3 = -f2;
        }
    };

    class HighpassFilter : public FilterBase {
        float scale;
    public:
        float Apply(float x) {
            float y = ApplyA(-x + x1 + x2 - x3);
            x3 = x2;
            x2 = x1;
            x1 = x;
            return y * scale;
        }

        void SetParameters(float f1, float f2, float scale) {
            a1 = f2;
            a2 = f1 * f1 - 1;
            a3 = -f2;
            this->scale = scale;
        }
    };

    class BandrejectFilter : public FilterBase {
        float scale, b2;
    public:
        float Apply(float x) {
            float y = ApplyA(x - x1 + b2 * x2 + x3);
            x3 = x2;
            x2 = x1;
            x1 = x;
            return y * scale;
        }

        void SetParameters(float f1, float f2, float scale) {
            b2 = f1 * f1 - 1;
            a1 = f2;
            a2 = b2;
            a3 = -f2;
            this->scale = scale;
        }
    };

    class LowpassTurboFilter : public LowpassFilter {
        float b20, y21, y22, y23;
    public:
        float Apply(float x) {
            float y = b20 * LowpassFilter::Apply(x)
                - a1 * y21 - a2 * y22 - a3 * y23;
            KillDenormal(y);
            y23 = y22;
            y22 = y21;
            y21 = y;

            return y;
        }

        void SetParameters(float f1, float f2, float scale) {
            LowpassFilter::SetParameters(f1, f2, scale);
            b20 = b0 * 0.5;
        }

        void Reset() {
            LowpassFilter::Reset();
            y21 = y22 = y23 = 0;
        }
    };

    /**
     * These are filters similar to the ones from Gigasampler.
     */
    class Filter {
        protected:
            HighpassFilter     HPFilter;
            BandpassFilter     BPFilter;
            LowpassFilter      LPFilter;
            BandrejectFilter   BRFilter;
            LowpassTurboFilter LPTFilter;
            FilterBase*        pFilter;

        public:
            Filter() {
                // set filter type to 'lowpass' by default
                pFilter = &LPFilter;
            }

            void SetType(::gig::vcf_type_t FilterType) {
                switch (FilterType) {
                    case ::gig::vcf_type_highpass:
                        pFilter = &HPFilter;
                        break;
                    case ::gig::vcf_type_bandreject:
                        pFilter = &BRFilter;
                        break;
                    case ::gig::vcf_type_bandpass:
                        pFilter = &BPFilter;
                        break;
                    case ::gig::vcf_type_lowpassturbo:
                        pFilter = &LPTFilter;
                        break;
                    default:
                        pFilter = &LPFilter;
                }
            }

            void SetParameters(float cutoff, float resonance, float fs) {
                float f1 = cutoff * 0.0075279;
                float f2 = f1 - 1 + resonance * cutoff * (-5.5389e-5 + 1.1982e-7 * cutoff);
                float scale = resonance < 51 ? 1.0f : 1.3762f - 0.0075073f * resonance;
                pFilter->SetParameters(f1, f2, scale);
            }

            void Reset() {
                HPFilter.Reset();
                BPFilter.Reset();
                LPFilter.Reset();
                BRFilter.Reset();
                LPTFilter.Reset();
            }

            float Apply(float in) {
                return pFilter->Apply(in);
            }
    };

}} //namespace LinuxSampler::gig

#endif // __LS_GIG_FILTER_H__
