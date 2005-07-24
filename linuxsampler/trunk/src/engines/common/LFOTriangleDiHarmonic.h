/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#ifndef __LS_LFOTRIANGLEDIHARMONIC_H__
#define __LS_LFOTRIANGLEDIHARMONIC_H__

#include "LFOBase.h"

// amplitue of 2nd harmonic (to approximate the triangular wave)
// TODO: this was just a quick head calculation, needs to be recalculated exactly (DFT)
#define AMP2	0.1f

namespace LinuxSampler {

    /** @brief Triangle LFO (di-harmonic implementation)
     *
     * This is a triangle Low Frequency Oscillator implementation which uses
     * a di-harmonic solution. This means it sums up two harmonics
     * (sinusoids) to approximate a triangular wave.
     */
    template<range_type_t RANGE>
    class LFOTriangleDiHarmonic : public LFOBase<RANGE> {
        public:

            /**
             * Constructor
             *
             * @param Max - maximum value of the output levels
             */
            LFOTriangleDiHarmonic(float Max) : LFOBase<RANGE>::LFOBase(Max) {
            }

            /**
             * Calculates exactly one sample point of the LFO wave.
             *
             * @returns next LFO level
             */
            inline float render() {
                real1 -= c1 * imag1;
                imag1 += c1 * real1;
                real2 -= c2 * imag2;
                imag2 += c2 * real2;
                if (RANGE == range_unsigned)
                    return (real1 + real2 * AMP2) * normalizer + normalizer;
                else /* signed range */
                    return (real1 + real2 * AMP2) * normalizer;
            }

            /**
             * Update LFO depth with a new external controller value.
             *
             * @param ExtControlValue - new external controller value
             */
            inline void update(const uint16_t& ExtControlValue) {
                const float max = InternalDepth + ExtControlValue * ExtControlDepthCoeff;
                if (RANGE == range_unsigned)
                    normalizer = max * 0.5f;
                else /* signed range */
                    normalizer = max;
            }

            /**
             * Will be called by the voice when the key / voice was triggered.
             *
             * @param Frequency       - frequency of the oscillator in Hz
             * @param StartLevel      - on which level the wave should start
             * @param InternalDepth   - firm, internal oscillator amplitude
             * @param ExtControlDepth - defines how strong the external MIDI
             *                          controller has influence on the
             *                          oscillator amplitude
             * @param FlipPhase       - inverts the oscillator wave
             * @param SampleRate      - current sample rate of the engines
             *                          audio output signal
             */
            void trigger(float Frequency, start_level_t StartLevel, uint16_t InternalDepth, uint16_t ExtControlDepth, bool FlipPhase, unsigned int SampleRate) {
                this->InternalDepth        = (InternalDepth / 1200.0f) * Max;
                this->ExtControlDepthCoeff = (((float) ExtControlDepth / 1200.0f) / 127.0f) * Max;

                c1 = 2.0f * M_PI * Frequency / (float) SampleRate;
                c2 = 2.0f * M_PI * Frequency / (float) SampleRate * 3.0f;

                float phi; // phase displacement
                switch (StartLevel) {
                    case start_level_max:
                        phi = 0.0f; // 0°
                        break;
                    case start_level_mid:
                        phi = (FlipPhase) ? 3.0f * M_PI : M_PI; // 270° or 90°
                        break;
                    case start_level_min:
                        phi = 2.0f * M_PI; // 180°
                        break;
                }
                real1 = real2 = cos(phi);
                imag1 = imag2 = sin(phi);
            }

        private:
            float c1;
            float c2;
            float real1;
            float imag1;
            float real2;
            float imag2;
            float normalizer;
    };

} // namespace LinuxSampler

#endif // __LS_LFOTRIANGLEDIHARMONIC_H__
