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

#include "audioio.h"

AudioIO::AudioIO() {
    pcm_handle    = NULL;
    pOutputBuffer = NULL;
    Initialized   = false;
    stream        = SND_PCM_STREAM_PLAYBACK;
}

AudioIO::~AudioIO() {
    Close();
}

int AudioIO::Initialize(uint channels, uint samplerate, uint numfragments, uint fragmentsize) {
    this->Channels     = channels;
    this->Samplerate   = samplerate;
    this->Fragments    = numfragments;
    this->FragmentSize = fragmentsize;

    if (HardwareParametersSupported(channels, samplerate, numfragments, fragmentsize)) {
        pcm_name = "hw:0,0";
    }
    else {
        printf("Warning: your soundcard doesn't support chosen hardware parameters; ");
        printf("trying to compensate support lack with plughw...");
        fflush(stdout);
        pcm_name = "plughw:0,0";
    }

    int err;

    snd_pcm_hw_params_alloca(&hwparams);  // Allocate the snd_pcm_hw_params_t structure on the stack.

    /* Open PCM. The last parameter of this function is the mode. */
    /* If this is set to 0, the standard mode is used. Possible   */
    /* other values are SND_PCM_NONBLOCK and SND_PCM_ASYNC.       */
    /* If SND_PCM_NONBLOCK is used, read / write access to the    */
    /* PCM device will return immediately. If SND_PCM_ASYNC is    */
    /* specified, SIGIO will be emitted whenever a period has     */
    /* been completely processed by the soundcard.                */
    if ((err = snd_pcm_open(&pcm_handle, pcm_name.c_str(), stream, 0)) < 0) {
        fprintf(stderr, "Error opening PCM device %s: %s\n", pcm_name.c_str(), snd_strerror(err));
        return EXIT_FAILURE;
    }

    if ((err = snd_pcm_hw_params_any(pcm_handle, hwparams)) < 0) {
        fprintf(stderr, "Error, cannot initialize hardware parameter structure: %s.\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    /* Set access type. This can be either    */
    /* SND_PCM_ACCESS_RW_INTERLEAVED or       */
    /* SND_PCM_ACCESS_RW_NONINTERLEAVED.      */
    if ((err = snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_access: %s.\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    /* Set sample format */
    #if WORDS_BIGENDIAN
    if ((err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_BE)) < 0) {
    #else // little endian
    if ((err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE)) < 0) {
    #endif
        fprintf(stderr, "Error setting sample format. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    int dir = 0;

    /* Set sample rate. If the exact rate is not supported */
    /* by the hardware, use nearest possible rate.         */
    #if ALSA_MAJOR > 0
    if((err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &samplerate, &dir)) < 0) {
    #else
    if((err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, samplerate, &dir)) < 0) {
    #endif
        fprintf(stderr, "Error setting sample rate. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    if ((err = snd_pcm_hw_params_set_channels(pcm_handle, hwparams, channels)) < 0) {
        fprintf(stderr, "Error setting number of channels. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    /* Set number of periods. Periods used to be called fragments. */
    if ((err = snd_pcm_hw_params_set_periods(pcm_handle, hwparams, numfragments, dir)) < 0) {
        fprintf(stderr, "Error setting number of periods. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    /* Set buffer size (in frames). The resulting latency is given by */
    /* latency = periodsize * periods / (rate * bytes_per_frame)     */
    if ((err = snd_pcm_hw_params_set_buffer_size(pcm_handle, hwparams, (fragmentsize * numfragments))) < 0) {
        fprintf(stderr, "Error setting buffersize. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    /* Apply HW parameter settings to */
    /* PCM device and prepare device  */
    if ((err = snd_pcm_hw_params(pcm_handle, hwparams)) < 0) {
        fprintf(stderr, "Error setting HW params. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    if (snd_pcm_sw_params_malloc(&swparams) != 0) {
        fprintf(stderr, "Error in snd_pcm_sw_params_malloc. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    if (snd_pcm_sw_params_current(pcm_handle, swparams) != 0) {
        fprintf(stderr, "Error in snd_pcm_sw_params_current. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    if (snd_pcm_sw_params_set_stop_threshold(pcm_handle, swparams, 0xffffffff) != 0) {
        fprintf(stderr, "Error in snd_pcm_sw_params_set_stop_threshold. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    if (snd_pcm_sw_params(pcm_handle, swparams) != 0) {
        fprintf(stderr, "Error in snd_pcm_sw_params. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    if ((err = snd_pcm_prepare(pcm_handle)) < 0) {
        fprintf(stderr, "Error snd_pcm_prepare : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    // allocate the audio output buffer
    pOutputBuffer = new int16_t[channels * fragmentsize];
    
    this->Initialized = true;

    return EXIT_SUCCESS;
}

/**
 *  Checks if sound card supports the chosen parameters.
 *
 *  @returns  true if hardware supports it
 */
bool AudioIO::HardwareParametersSupported(uint channels, int samplerate, uint numfragments, uint fragmentsize) {
    pcm_name = "hw:0,0";
    if (snd_pcm_open(&pcm_handle, pcm_name.c_str(), stream, 0) < 0) return false;
    snd_pcm_hw_params_alloca(&hwparams);
    if (snd_pcm_hw_params_any(pcm_handle, hwparams) < 0) {
        snd_pcm_close(pcm_handle);
        return false;
    }
    if (snd_pcm_hw_params_test_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
        snd_pcm_close(pcm_handle);
        return false;
    }
    #if WORDS_BIGENDIAN
    if (snd_pcm_hw_params_test_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_BE) < 0) {
    #else // little endian
    if (snd_pcm_hw_params_test_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE) < 0) {
    #endif
        snd_pcm_close(pcm_handle);
        return false;
    }
    int dir = 0;
    if (snd_pcm_hw_params_test_rate(pcm_handle, hwparams, samplerate, dir) < 0) {
        snd_pcm_close(pcm_handle);
        return false;
    }
    if (snd_pcm_hw_params_test_channels(pcm_handle, hwparams, channels) < 0) {
        snd_pcm_close(pcm_handle);
        return false;
    }
    if (snd_pcm_hw_params_test_periods(pcm_handle, hwparams, numfragments, dir) < 0) {
        snd_pcm_close(pcm_handle);
        return false;
    }
    if (snd_pcm_hw_params_test_buffer_size(pcm_handle, hwparams, (fragmentsize * numfragments)) < 0) {
        snd_pcm_close(pcm_handle);
        return false;
    }

    snd_pcm_close(pcm_handle);
    return true;
}

/**
 *  Will be called by the audio engine after every audio fragment cycle, to
 *  output the audio data of the current fragment to the soundcard.
 *
 *  @returns  0 on success
 */
int AudioIO::Output() {
    int err = snd_pcm_writei(pcm_handle, pOutputBuffer, FragmentSize);
    if (err < 0) {
        fprintf(stderr, "Error snd_pcm_writei failed. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void AudioIO::Close(void) {
    if (Initialized) {
        if (pcm_handle) {
            //FIXME: currently commented out due to segfault
            //snd_pcm_close(pcm_handle);
            pcm_handle = NULL;
        }
        if (pOutputBuffer) {
            //FIXME: currently commented out due to segfault
            //delete[] pOutputBuffer;
            pOutputBuffer = NULL;
        }
        Initialized = false;
    }
}
