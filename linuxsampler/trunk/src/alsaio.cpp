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

#include "alsaio.h"

AlsaIO::AlsaIO() : AudioIO(), Thread(true, 1, 0) {
    pcm_handle    = NULL;
    pOutputBuffer = NULL;
    stream        = SND_PCM_STREAM_PLAYBACK;
}

int AlsaIO::Initialize(uint Channels, uint Samplerate, uint Fragments, uint FragmentSize) {
    this->uiChannels           = Channels;
    this->uiSamplerate         = Samplerate;
    this->uiMaxSamplesPerCycle = FragmentSize;
    this->bInterleaved         = true;

    if (HardwareParametersSupported(Channels, Samplerate, Fragments, FragmentSize)) {
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
        return -1;
    }

    if ((err = snd_pcm_hw_params_any(pcm_handle, hwparams)) < 0) {
        fprintf(stderr, "Error, cannot initialize hardware parameter structure: %s.\n", snd_strerror(err));
        return -1;
    }

    /* Set access type. This can be either    */
    /* SND_PCM_ACCESS_RW_INTERLEAVED or       */
    /* SND_PCM_ACCESS_RW_NONINTERLEAVED.      */
    if ((err = snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_access: %s.\n", snd_strerror(err));
        return -1;
    }

    /* Set sample format */
    #if WORDS_BIGENDIAN
    if ((err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_BE)) < 0) {
    #else // little endian
    if ((err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE)) < 0) {
    #endif
        fprintf(stderr, "Error setting sample format. : %s\n", snd_strerror(err));
        return -1;
    }

    int dir = 0;

    /* Set sample rate. If the exact rate is not supported */
    /* by the hardware, use nearest possible rate.         */
    #if ALSA_MAJOR > 0
    if((err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &Samplerate, &dir)) < 0) {
    #else
    if((err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, Samplerate, &dir)) < 0) {
    #endif
        fprintf(stderr, "Error setting sample rate. : %s\n", snd_strerror(err));
        return -1;
    }

    if ((err = snd_pcm_hw_params_set_channels(pcm_handle, hwparams, Channels)) < 0) {
        fprintf(stderr, "Error setting number of channels. : %s\n", snd_strerror(err));
        return -1;
    }

    /* Set number of periods. Periods used to be called fragments. */
    if ((err = snd_pcm_hw_params_set_periods(pcm_handle, hwparams, Fragments, dir)) < 0) {
        fprintf(stderr, "Error setting number of periods. : %s\n", snd_strerror(err));
        return -1;
    }

    /* Set buffer size (in frames). The resulting latency is given by */
    /* latency = periodsize * periods / (rate * bytes_per_frame)     */
    if ((err = snd_pcm_hw_params_set_buffer_size(pcm_handle, hwparams, (FragmentSize * Fragments))) < 0) {
        fprintf(stderr, "Error setting buffersize. : %s\n", snd_strerror(err));
        return -1;
    }

    /* Apply HW parameter settings to */
    /* PCM device and prepare device  */
    if ((err = snd_pcm_hw_params(pcm_handle, hwparams)) < 0) {
        fprintf(stderr, "Error setting HW params. : %s\n", snd_strerror(err));
        return -1;
    }

    if (snd_pcm_sw_params_malloc(&swparams) != 0) {
        fprintf(stderr, "Error in snd_pcm_sw_params_malloc. : %s\n", snd_strerror(err));
        return -1;
    }

    if (snd_pcm_sw_params_current(pcm_handle, swparams) != 0) {
        fprintf(stderr, "Error in snd_pcm_sw_params_current. : %s\n", snd_strerror(err));
        return -1;
    }

    if (snd_pcm_sw_params_set_stop_threshold(pcm_handle, swparams, 0xffffffff) != 0) {
        fprintf(stderr, "Error in snd_pcm_sw_params_set_stop_threshold. : %s\n", snd_strerror(err));
        return -1;
    }

    if (snd_pcm_sw_params(pcm_handle, swparams) != 0) {
        fprintf(stderr, "Error in snd_pcm_sw_params. : %s\n", snd_strerror(err));
        return -1;
    }

    if ((err = snd_pcm_prepare(pcm_handle)) < 0) {
        fprintf(stderr, "Error snd_pcm_prepare : %s\n", snd_strerror(err));
        return -1;
    }

    // allocate the audio output buffer
    pOutputBuffer = new int16_t[Channels * FragmentSize];
    
    this->bInitialized = true;

    return 0;
}

/**
 *  Checks if sound card supports the chosen parameters.
 *
 *  @returns  true if hardware supports it
 */
bool AlsaIO::HardwareParametersSupported(uint channels, int samplerate, uint numfragments, uint fragmentsize) {
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

void AlsaIO::Activate() {
    this->StartThread();
}

int AlsaIO::Main() {
    if (!pEngine) {
        fprintf(stderr, "AlsaIO: No Sampler Engine assigned, exiting.\n");
        exit(EXIT_FAILURE);
    }
    if (!bInitialized) {
        fprintf(stderr, "AlsaIO: Not yet intitialized, exiting.\n");
        exit(EXIT_FAILURE);
    }

    while (true) {

        // let the engine render audio for the current audio fragment
        pEngine->RenderAudio(uiMaxSamplesPerCycle);


        // check clipping in the audio sum, convert to sample_type
        // (from 32bit to 16bit sample) and copy to output buffer
        float sample_point; uint o = 0;
        for (uint s = 0; s < uiMaxSamplesPerCycle; s++) {
            for (uint c = 0; c < uiChannels; c++) {
                sample_point = pEngine->GetAudioSumBuffer(c)[s] * pEngine->Volume;
                if (sample_point < -32768.0) sample_point = -32768.0;
                if (sample_point >  32767.0) sample_point =  32767.0;
                this->pOutputBuffer[o++] = (int32_t) sample_point;
            }
        }


        // output sound
        int res = Output();
        if (res < 0) {
            fprintf(stderr, "AlsaIO: Audio output error, exiting.\n");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 *  Will be called after every audio fragment cycle, to output the audio data
 *  of the current fragment to the soundcard.
 *
 *  @returns  0 on success
 */
int AlsaIO::Output() {
    int err = snd_pcm_writei(pcm_handle, pOutputBuffer, uiMaxSamplesPerCycle);
    if (err < 0) {
        fprintf(stderr, "Error snd_pcm_writei failed. : %s\n", snd_strerror(err));
        return -1;
    }
    return 0;
}

void AlsaIO::Close() {
    if (bInitialized) {
        //dmsg(0,("Stopping Alsa Thread..."));
        //StopThread();  //FIXME: commented out due to a bug in thread.cpp (StopThread() doesn't return at all)
        //dmsg(0,("OK\n"));
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
        bInitialized = false;
    }
}

void* AlsaIO::GetInterleavedOutputBuffer() {
    return pOutputBuffer;
}

void* AlsaIO::GetChannelOutputBufer(uint Channel) {
    fprintf(stderr, "AlsaIO::GetChannelOutputBufer(): Only interleaved access allowed so far, exiting.\n");
    exit(EXIT_FAILURE);
    // just to avoid compiler warnings
    return NULL;
}
