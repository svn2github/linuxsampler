/*
    Triangle wave generator benchmark

    This is a benchmark for comparison between a integer math, table lookup
    and numeric sine wave harmonics solution.

    Copyright (C) 2005 Christian Schoenebeck <cuse@users.sf.net>
*/

#include <math.h>
#include <time.h>
#include <stdio.h>

// whether we should not show any messages on the console
#ifndef SILENT
# define SILENT 0
#endif

// set to 1 if you want to output the three calculated waves as RAW files
// you can e.g. open it as RAW file in Rezound
// (32 bit SP-FP PCM, mono, little endian, 44100kHz)
#ifndef OUTPUT_AS_RAW_WAVE
# define OUTPUT_AS_RAW_WAVE	0
#endif

// how many sample points should we calculate in one sequence
#ifndef STEPS
# define STEPS			16384
#endif

// how often should we repeat the benchmark loop of each solution
#ifndef RUNS
# define RUNS			1000
#endif

// whether the wave should have positive and negative range (signed -> 1) or just positive (unsigned -> 0)
#ifndef SIGNED
# define SIGNED			1
#endif

// pro forma
#ifndef SAMPLING_RATE
# define SAMPLING_RATE		44100.0f
#endif

// return value of this benchmark
// to indicate the best performing solution
#define INT_MATH_SOLUTION	2  /* we don't start with 1, as this is reserved for unknown errors */
#define DI_HARMONIC_SOLUTION	3
#define TABLE_LOOKUP_SOLUTION	4  /* table lookup solution is currently disabled in this benchmark, see below */
#define INVALID_RESULT		-1

// we use 32 bit single precision floating point as sample point format
typedef float sample_t;

// integer math solution
float int_math(sample_t* pDestinationBuffer, float* pAmp, const int steps, const float frequency) {
    // pro forma
    const float r = frequency / SAMPLING_RATE; // frequency alteration quotient
    unsigned int maxvalue = (unsigned int) -1; // all 0xFFFF...
    #if SIGNED
    const float normalizer = 1.0f / ((float) maxvalue / 4.0f);
    #else // unsigned
    const float normalizer = 1.0f / ((float) maxvalue / 2.0f);
    #endif
    const int c = (int) (maxvalue * r);
    const int signshifts = (sizeof(int) * 8) - 1;

    int iSign;

    clock_t stop_time;
    clock_t start_time = clock();

    for (int run = 0; run < RUNS; run++) {
        int iLevel = 0;
        for (int i = 0; i < steps; ++i) {
            iLevel += c;
            iSign  = (iLevel >> signshifts) | 1;
            #if SIGNED
            pDestinationBuffer[i] = (normalizer * (float) (iSign * iLevel) - 1.0f) * pAmp[i]; // * pAmp[i] just to simulate some memory load
            #else // unsigned
            pDestinationBuffer[i] = normalizer * (float) (iSign * iLevel) * pAmp[i]; // * pAmp[i] just to simulate some memory load
            #endif
        }
    }

    stop_time = clock();
    float elapsed_time = (stop_time - start_time) / (double(CLOCKS_PER_SEC) / 1000.0);
    #if ! SILENT
    printf("int math solution elapsed time: %1.0f ms\n", elapsed_time);
    #endif

    return elapsed_time;
}

// table lookup solution (currently disabled)
//
// This solution is not yet implemented in LinuxSampler yet and probably
// never will, I simply haven't found an architectures / system where this
// turned out to be the best solution and it introduces too many problems
// anyway. If you found an architecture where this seems to be the best
// solution, please let us know!
#if 0
float table_lookup(sample_t* pDestinationBuffer, float* pAmp, const int steps, const float frequency) {
    // pro forma
    const float r = frequency / SAMPLING_RATE; // frequency alteration quotient
    #if SIGNED
    float c = r * 4.0f;
    #else
    float c = r * 2.0f;
    #endif
    const int wl = (int) (SAMPLING_RATE / frequency); // wave length (in sample points)

    // 'volatile' to avoid the cache to fudge the benchmark result
    volatile float* pPrerenderingBuffer = new float[wl];

    // prerendering of the triangular wave
    {
        float level = 0.0f;
        for (int i = 0; i < wl; ++i) {
            level += c;
            #if SIGNED
            if (level >= 1.0f) {
                c = -c;
                level = 1.0f;
            }
            else if (level <= -1.0f) {
                c = -c;
                level = -1.0f;
            }
            #else
            if (level >= 1.0f) {
                c = -c;
                level = 1.0f;
            }
            else if (level <= 0.0f) {
                c = -c;
                level = 0.0f;
            }
            #endif
            pPrerenderingBuffer[i] = level;
        }
    }

    clock_t stop_time;
    clock_t start_time = clock();

    for (int run = 0; run < RUNS; run++) {
        for (int i = 0; i < steps; ++i) {
            pDestinationBuffer[i] = pPrerenderingBuffer[i % wl] * pAmp[i]; // * pAmp[i] just to simulate some memory load
        }
    }

    stop_time = clock();
    float elapsed_time = (stop_time - start_time) / (double(CLOCKS_PER_SEC) / 1000.0);
    #if ! SILENT
    printf("Table lookup solution elapsed time: %1.0f ms\n", elapsed_time);
    #endif

    if (pPrerenderingBuffer) delete[] pPrerenderingBuffer;

    return elapsed_time;
}
#endif

// numeric, di-harmonic solution
float numeric_di_harmonic_solution(sample_t* pDestinationBuffer, float* pAmp, const int steps, const float frequency) {
    // we approximate the triangular wave by adding 2 harmonics
    const float c1   = 2.0f * M_PI * frequency / SAMPLING_RATE;
    const float phi1 = 0.0f; // phase displacement
    const float c2   = 2.0f * M_PI * frequency / SAMPLING_RATE * 3.0f;
    const float phi2 = 0.0f; // phase displacement

    // amplitue for the 2nd harmonic (to approximate the triangular wave)
    const float amp2 = 0.1f;

    // initial values for real and imaginary part
    float real1 = cos(phi1);
    float imag1 = sin(phi1);
    float real2 = cos(phi2);
    float imag2 = sin(phi2);

    clock_t stop_time;
    clock_t start_time = clock();

    for (int run = 0; run < RUNS; run++) {
        for (int i = 0; i < steps; i++) {
            #if SIGNED
            pDestinationBuffer[i] = (real1 + real2 * amp2) * pAmp[i]; // * pAmp[i] just to simulate some memory load
            #else // unsigned
            pDestinationBuffer[i] = ((real1 + real2 * amp2) * 0.5f + 0.5f) * pAmp[i]; // * pAmp[i] just to simulate some memory load
            #endif
            real1 -= c1 * imag1;
            imag1 += c1 * real1;
            real2 -= c2 * imag2;
            imag2 += c2 * real2;
        }
    }

    stop_time = clock();
    float elapsed_time = (stop_time - start_time) / (double(CLOCKS_PER_SEC) / 1000.0);
    #if ! SILENT
    printf("Numeric harmonics solution elapsed time: %1.0f ms\n", elapsed_time);
    #endif

    return elapsed_time;
}

// output calculated values as RAW audio format (32 bit floating point, mono) file
void output_as_raw_file(const char* filename, sample_t* pOutputBuffer, int steps) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fwrite((void*) pOutputBuffer, sizeof(float), steps, file);
        fclose(file);
    } else {
        fprintf(stderr, "Could not open %s\n", filename);
    }
}

int main() {
    const int steps = STEPS;
    const int sinusoidFrequency = 100; // Hz

    #if ! SILENT
    # if SIGNED
    printf("Signed triangular wave benchmark\n");
    printf("--------------------------------\n");
    # else
    printf("Unsigned triangular wave benchmark\n");
    printf("----------------------------------\n");
    # endif
    #endif

    // output buffer for the calculated sinusoid wave
    sample_t* pOutputBuffer = new sample_t[steps];
    // just an arbitrary amplitude envelope to simulate a bit higher memory bandwidth
    float* pAmplitude  = new float[steps];

    // pro forma - an arbitary amplitude envelope
    for (int i = 0; i < steps; ++i)
        pAmplitude[i] = (float) i / (float) steps;

    // how long each solution took (in seconds)
    float int_math_result, /*table_lookup_result,*/ numeric_di_harmonic_result;

    int_math_result = int_math(pOutputBuffer, pAmplitude, steps, sinusoidFrequency);
    #if OUTPUT_AS_RAW_WAVE
      output_as_raw_file("bench_int_math.raw", pOutputBuffer, steps);
    #endif
    //table_lookup_result = table_lookup(pOutputBuffer, pAmplitude, steps, sinusoidFrequency);
    //#if OUTPUT_AS_RAW_WAVE
    //  output_as_raw_file("bench_table_lookup.raw", pOutputBuffer, steps);
    //#endif
    numeric_di_harmonic_result = numeric_di_harmonic_solution(pOutputBuffer, pAmplitude, steps, sinusoidFrequency);
    #if OUTPUT_AS_RAW_WAVE
      output_as_raw_file("bench_numeric_harmonics.raw", pOutputBuffer, steps);
    #endif

    #if ! SILENT
    printf("\nOK, 2nd try\n\n");
    #endif

    int_math_result            += int_math(pOutputBuffer, pAmplitude, steps, sinusoidFrequency);
    //table_lookup_result        += table_lookup(pOutputBuffer, pAmplitude, steps, sinusoidFrequency);
    numeric_di_harmonic_result += numeric_di_harmonic_solution(pOutputBuffer, pAmplitude, steps, sinusoidFrequency);

    if (pAmplitude)    delete[] pAmplitude;
    if (pOutputBuffer) delete[] pOutputBuffer;

    if (/*int_math_result <= table_lookup_result &&*/ int_math_result <= numeric_di_harmonic_result) return INT_MATH_SOLUTION;
    if (/*numeric_di_harmonic_result <= table_lookup_result &&*/ numeric_di_harmonic_result <= int_math_result) return DI_HARMONIC_SOLUTION;
    //if (table_lookup_result <= int_math_result && table_lookup_result <= numeric_di_harmonic_result) return TABLE_LOOKUP_SOLUTION;

    return INVALID_RESULT; // error
}
