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
}

AudioIO::~AudioIO() {
    Close();
}

int AudioIO::Initialize(uint channels, uint samplerate, uint numfragments, uint fragmentsize) {
    this->Channels         = channels;
    this->Samplerate       = samplerate;
    this->Fragments        = numfragments;
    this->FragmentSize     = fragmentsize;

    /* Playback stream */
    snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;

    /* This structure contains information about    */
    /* the hardware and can be used to specify the  */
    /* configuration to be used for the PCM stream. */
    snd_pcm_hw_params_t* hwparams;

    snd_pcm_sw_params_t* swparams;

    /* Name of the PCM device, like plughw:0,0          */
    /* The first number is the number of the soundcard, */
    /* the second number is the number of the device.   */
    char* pcm_name;

    /* Init pcm_name. Of course, later you */

    int err;

    pcm_name = strdup("hw:0,0");

    /* Allocate the snd_pcm_hw_params_t structure on the stack. */
    snd_pcm_hw_params_alloca(&hwparams);

    /* Open PCM. The last parameter of this function is the mode. */
    /* If this is set to 0, the standard mode is used. Possible   */
    /* other values are SND_PCM_NONBLOCK and SND_PCM_ASYNC.       */
    /* If SND_PCM_NONBLOCK is used, read / write access to the    */
    /* PCM device will return immediately. If SND_PCM_ASYNC is    */
    /* specified, SIGIO will be emitted whenever a period has     */
    /* been completely processed by the soundcard.                */
    if ((err = snd_pcm_open(&pcm_handle, pcm_name, stream, 0)) < 0) {
        fprintf(stderr, "Error opening PCM device %s: %s\n", pcm_name, snd_strerror(err));
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
    if ((err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE)) < 0) {
        fprintf(stderr, "Error setting sample format. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    /* Set sample rate. If the exact rate is not supported */
    /* by the hardware, use nearest possible rate.         */
    if((err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, samplerate, 0)) < 0) {
        fprintf(stderr, "Error setting sample rate. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    if ((err = snd_pcm_hw_params_set_channels(pcm_handle, hwparams, channels)) < 0) {
        fprintf(stderr, "Error setting number of channels. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }

    /* Set number of periods. Periods used to be called fragments. */
    if ((err = snd_pcm_hw_params_set_periods(pcm_handle, hwparams, numfragments, 0)) < 0) {
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

    return EXIT_SUCCESS;
}

int AudioIO::Output() {
    int err = snd_pcm_writei(pcm_handle, pOutputBuffer, FragmentSize);
    if (err < 0) {
        fprintf(stderr, "Error snd_pcm_writei failed. : %s\n", snd_strerror(err));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void AudioIO::Close(void) {
    if (pcm_handle) {
        snd_pcm_close(pcm_handle);
        pcm_handle = NULL;
    }
    if (pOutputBuffer) {
        delete[] pOutputBuffer;
        pOutputBuffer = NULL;
    }
}
