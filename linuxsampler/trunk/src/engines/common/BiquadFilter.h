/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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

#ifndef __LS_BIQUADFILTER_H__
#define __LS_BIQUADFILTER_H__

/// ln(2) / 2
#define LN_2_2			0.34657359f

#ifndef LIMIT
# define LIMIT(v,l,u)		(v < l ? l : (v > u ? u : v))
#endif

namespace LinuxSampler {

    typedef float bq_t;

    /**
    * Bi-quadratic filter
    * (adapted from lisp code by Eli Brandt, http://www.cs.cmu.edu/~eli/)
    */
    class BiquadFilter {
        protected:
            bq_t a1;
            bq_t a2;
            bq_t b0;
            bq_t b1;
            bq_t b2;
            bq_t x1;
            bq_t x2;
            bq_t y1;
            bq_t y2;

            /**
            * Prevent \a f from going into denormal mode which would slow down
            * subsequent floating point calculations, we achieve that by setting
            * \a f to zero when it falls under the denormal threshold value.
            */
            inline void KillDenormal(float& f) {
                // TODO: this is a generic solution for 32bit floats, should be replaced by CPU specific asm code
                f += 1e-18f;
                f -= 1e-18f;
            }
        public:
            inline BiquadFilter() {
                x1 = 0.0f;
                x2 = 0.0f;
                y1 = 0.0f;
                y2 = 0.0f;
            }

            inline bq_t Apply(const bq_t x) {
                bq_t y;

                y = this->b0 * x + this->b1 * this->x1 + this->b2 * this->x2 +
                    this->a1 * this->y1 + this->a2 * this->y2;
                KillDenormal(y);
                this->x2 = this->x1;
                this->x1 = x;
                this->y2 = this->y1;
                this->y1 = y;

                return y;
            }

            inline bq_t ApplyFB(bq_t x, const bq_t fb) {
                bq_t y;

                x += this->y1 * fb * 0.98;
                y = this->b0 * x + this->b1 * this->x1 + this->b2 * this->x2 +
                    this->a1 * this->y1 + this->a2 * this->y2;
                KillDenormal(y);
                this->x2 = this->x1;
                this->x1 = x;
                this->y2 = this->y1;
                this->y1 = y;

                return y;
            }
    };

    class LowpassFilter : public BiquadFilter {
        public:
            inline LowpassFilter() : BiquadFilter() {}

            inline void SetParameters(bq_t fc, bq_t bw, bq_t fs) {
                bq_t omega = 2.0 * M_PI * fc / fs;
                bq_t sn    = sin(omega);
                bq_t cs    = cos(omega);
                bq_t alpha = sn * sinh(M_LN2 / 2.0 * bw * omega / sn);

                const float a0r = 1.0 / (1.0 + alpha);
                this->b0 = a0r * (1.0 - cs) * 0.5;
                this->b1 = a0r * (1.0 - cs);
                this->b2 = a0r * (1.0 - cs) * 0.5;
                this->a1 = a0r * (2.0 * cs);
                this->a2 = a0r * (alpha - 1.0);
            }
    };

    class BandpassFilter : public BiquadFilter {
        public:
            inline BandpassFilter() : BiquadFilter() {}

            inline void SetParameters(bq_t fc, bq_t bw, bq_t fs) {
                bq_t omega = 2.0 * M_PI * fc / fs;
                bq_t sn    = sin(omega);
                bq_t cs    = cos(omega);
                bq_t alpha = sn * sinh(M_LN2 / 2.0 * bw * omega / sn);

                const float a0r = 1.0 / (1.0 + alpha);
                this->b0 = a0r * alpha;
                this->b1 = 0.0;
                this->b2 = a0r * -alpha;
                this->a1 = a0r * (2.0 * cs);
                this->a2 = a0r * (alpha - 1.0);
            }
    };

    class HighpassFilter : public BiquadFilter {
        public:
            inline HighpassFilter() : BiquadFilter() {}

            inline void SetParameters(bq_t fc, bq_t bw, bq_t fs) {
                bq_t omega = 2.0 * M_PI * fc / fs;
                bq_t sn    = sin(omega);
                bq_t cs    = cos(omega);
                bq_t alpha = sn * sinh(M_LN2 / 2.0 * bw * omega / sn);

                const float a0r = 1.0 / (1.0 + alpha);
                this->b0 = a0r * (1.0 + cs) * 0.5;
                this->b1 = a0r * -(1.0 + cs);
                this->b2 = a0r * (1.0 + cs) * 0.5;
                this->a1 = a0r * (2.0 * cs);
                this->a2 = a0r * (alpha - 1.0);
            }
    };

} // namespace LinuxSampler

#endif // __LS_BIQUADFILTER_H__
