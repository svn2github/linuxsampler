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

#include "AudioOutputDeviceAlsa.h"
#include "AudioOutputDeviceFactory.h"

namespace LinuxSampler {

    REGISTER_AUDIO_OUTPUT_DRIVER(AudioOutputDeviceAlsa);

    /* Common parameters for now they'll have to be registered here. */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterActive);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterSampleRate);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterChannels);

    /* Driver specific parameters */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterCard);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterFragments);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterFragmentSize);

    /**
     * Create and initialize Alsa audio output device with given parameters.
     *
     * @param Parameters - optional parameters
     * @throws AudioOutputException  if output device cannot be opened
     */
    AudioOutputDeviceAlsa::AudioOutputDeviceAlsa(std::map<String,DeviceCreationParameter*> Parameters) : AudioOutputDevice(Parameters), Thread(true, 1, 0) {
        pcm_handle           = NULL;
        stream               = SND_PCM_STREAM_PLAYBACK;
        this->uiAlsaChannels = ((DeviceCreationParameterInt*)Parameters["channels"])->ValueAsInt();
        this->uiSamplerate   = ((DeviceCreationParameterInt*)Parameters["samplerate"])->ValueAsInt();
        this->FragmentSize   = ((DeviceCreationParameterInt*)Parameters["fragmentsize"])->ValueAsInt();
        uint Fragments       = ((DeviceCreationParameterInt*)Parameters["fragments"])->ValueAsInt();
        String Card          = Parameters["card"]->Value();

        dmsg(1,("Checking if hw parameters supported...\n"));
        if (HardwareParametersSupported(Card, uiAlsaChannels, uiSamplerate, Fragments, FragmentSize)) {
            pcm_name = "hw:" + Card;
        }
        else {
            printf("Warning: your soundcard doesn't support chosen hardware parameters; ");
            printf("trying to compensate support lack with plughw...");
            fflush(stdout);
            pcm_name = "plughw:" + Card;
        }
	dmsg(1,("HW check completed.\n"));

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
            throw AudioOutputException(String("Error opening PCM device ") + pcm_name + ": " + snd_strerror(err));
        }

        if ((err = snd_pcm_hw_params_any(pcm_handle, hwparams)) < 0) {
            throw AudioOutputException(String("Error, cannot initialize hardware parameter structure: ") + snd_strerror(err));
        }

        /* Set access type. This can be either    */
        /* SND_PCM_ACCESS_RW_INTERLEAVED or       */
        /* SND_PCM_ACCESS_RW_NONINTERLEAVED.      */
        if ((err = snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
            throw AudioOutputException(String("Error snd_pcm_hw_params_set_access: ") + snd_strerror(err));
        }

        /* Set sample format */
        #if WORDS_BIGENDIAN
        if ((err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_BE)) < 0)
        #else // little endian
        if ((err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE)) < 0)
        #endif
        {
            throw AudioOutputException(String("Error setting sample format: ") + snd_strerror(err));
        }

        int dir = 0;

        /* Set sample rate. If the exact rate is not supported */
        /* by the hardware, use nearest possible rate.         */
        #if ALSA_MAJOR > 0
        if((err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &uiSamplerate, &dir)) < 0)
        #else
        if((err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, uiSamplerate, &dir)) < 0)
        #endif
        {
            throw AudioOutputException(String("Error setting sample rate: ") + snd_strerror(err));
        }

        if ((err = snd_pcm_hw_params_set_channels(pcm_handle, hwparams, uiAlsaChannels)) < 0) {
            throw AudioOutputException(String("Error setting number of channels: ") + snd_strerror(err));
        }

        /* Set number of periods. Periods used to be called fragments. */
        if ((err = snd_pcm_hw_params_set_periods(pcm_handle, hwparams, Fragments, dir)) < 0) {
            throw AudioOutputException(String("Error setting number of periods: ") + snd_strerror(err));
        }

        /* Set buffer size (in frames). The resulting latency is given by */
        /* latency = periodsize * periods / (rate * bytes_per_frame)     */
        if ((err = snd_pcm_hw_params_set_buffer_size(pcm_handle, hwparams, (FragmentSize * Fragments))) < 0) {
            throw AudioOutputException(String("Error setting buffersize: ") + snd_strerror(err));
        }

        /* Apply HW parameter settings to */
        /* PCM device and prepare device  */
        if ((err = snd_pcm_hw_params(pcm_handle, hwparams)) < 0) {
            throw AudioOutputException(String("Error setting HW params: ") + snd_strerror(err));
        }

        if (snd_pcm_sw_params_malloc(&swparams) != 0) {
            throw AudioOutputException(String("Error in snd_pcm_sw_params_malloc: ") + snd_strerror(err));
        }

        if (snd_pcm_sw_params_current(pcm_handle, swparams) != 0) {
            throw AudioOutputException(String("Error in snd_pcm_sw_params_current: ") + snd_strerror(err));
        }

        if (snd_pcm_sw_params_set_stop_threshold(pcm_handle, swparams, 0xffffffff) != 0) {
            throw AudioOutputException(String("Error in snd_pcm_sw_params_set_stop_threshold: ") + snd_strerror(err));
        }

        if (snd_pcm_sw_params(pcm_handle, swparams) != 0) {
            throw AudioOutputException(String("Error in snd_pcm_sw_params: ") + snd_strerror(err));
        }

        if ((err = snd_pcm_prepare(pcm_handle)) < 0) {
            throw AudioOutputException(String("Error snd_pcm_prepare: ") + snd_strerror(err));
        }

        // allocate Alsa output buffer
        pAlsaOutputBuffer = new int16_t[uiAlsaChannels * FragmentSize];

        // create audio channels for this audio device to which the sampler engines can write to
        for (int i = 0; i < uiAlsaChannels; i++) this->Channels.push_back(new AudioChannel(FragmentSize));

	if (((DeviceCreationParameterBool*)Parameters["active"])->ValueAsBool()) {
		Play();
	}
    }

    AudioOutputDeviceAlsa::~AudioOutputDeviceAlsa() {
        //dmsg(0,("Stopping Alsa Thread..."));
        //StopThread();  //FIXME: commented out due to a bug in thread.cpp (StopThread() doesn't return at all)
        //dmsg(0,("OK\n"));

        //FIXME: currently commented out due to segfault
        //snd_pcm_close(pcm_handle);

        // destroy all audio channels
        for (int c = 0; c < Channels.size(); c++) delete Channels[c];

        if (pAlsaOutputBuffer) {
            //FIXME: currently commented out due to segfault
            //delete[] pOutputBuffer;
        }
    }

    /**
     *  Checks if sound card supports the chosen parameters.
     *
     *  @returns  true if hardware supports it
     */
    bool AudioOutputDeviceAlsa::HardwareParametersSupported(String card, uint channels, int samplerate, uint numfragments, uint fragmentsize) {
        pcm_name = "hw:" + card;
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
        if (snd_pcm_hw_params_test_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_BE) < 0)
        #else // little endian
        if (snd_pcm_hw_params_test_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE) < 0)
        #endif
        {
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

    void AudioOutputDeviceAlsa::Play() {
        StartThread();
    }

    bool AudioOutputDeviceAlsa::IsPlaying() {
        return IsRunning(); // if Thread is running
    }

    void AudioOutputDeviceAlsa::Stop() {
        StopThread();
    }

    void AudioOutputDeviceAlsa::AcquireChannels(uint Channels) {
        if (Channels > uiAlsaChannels) {
            // just create mix channel(s)
            for (int i = uiAlsaChannels; i < Channels; i++) {
                AudioChannel* pNewChannel = new AudioChannel(this->Channels[i % uiAlsaChannels]);
                this->Channels.push_back(pNewChannel);
            }
        }
    }

    uint AudioOutputDeviceAlsa::MaxSamplesPerCycle() {
        return FragmentSize;
    }

    uint AudioOutputDeviceAlsa::SampleRate() {
        return uiSamplerate;
    }

    String AudioOutputDeviceAlsa::Name() {
        return "Alsa";
    }

    String AudioOutputDeviceAlsa::Driver() {
        return Name();
    }

    String AudioOutputDeviceAlsa::Description() {
        return "Advanced Linux Sound Architecture";
    }

    String AudioOutputDeviceAlsa::Version() {
       String s = "$Revision: 1.10 $";
       return s.substr(11, s.size() - 13); // cut dollar signs, spaces and CVS macro keyword
    }

    /**
     * Entry point for the thread.
     */
    int AudioOutputDeviceAlsa::Main() {
        while (true) {

            // let all connected engines render 'FragmentSize' sample points
            RenderAudio(FragmentSize);

            // convert from DSP value range (-1.0..+1.0) to 16 bit integer value
            // range (-32768..+32767), check clipping  and copy to Alsa output buffer
            // (note: we use interleaved output method to Alsa)
            for (int c = 0; c < uiAlsaChannels; c++) {
                float* in  = Channels[c]->Buffer();
                for (int i = 0, o = c; i < FragmentSize; i++ , o += uiAlsaChannels) {
                    float sample_point = in[i] * 32768.0f;
                    if (sample_point < -32768.0) sample_point = -32768.0;
                    if (sample_point >  32767.0) sample_point =  32767.0;
                    pAlsaOutputBuffer[o] = (int16_t) sample_point;
                }
            }

            // output sound
            int res = Output();
            if (res < 0) {
                fprintf(stderr, "Alsa: Audio output error, exiting.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    /**
     *  Will be called after every audio fragment cycle, to output the audio data
     *  of the current fragment to the soundcard.
     *
     *  @returns  0 on success, a value < 0 on error
     */
    int AudioOutputDeviceAlsa::Output() {
        int err = snd_pcm_writei(pcm_handle, pAlsaOutputBuffer, FragmentSize);
        if (err < 0) {
            fprintf(stderr, "Error snd_pcm_writei failed: %s\n", snd_strerror(err));
            return -1;
        }
        return 0;
    }

} // namespace LinuxSampler

