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

#include "jackio.h"

#if HAVE_JACK

JackIO::JackIO() : AudioIO() {
    PendingSamples = 0;
}

int JackIO::Initialize(uint Channels, String OutputPorts[2]) {
    this->uiChannels   = Channels;
    this->bInterleaved = false;

    if ((Client = jack_client_new("LinuxSampler")) == 0) {
        fprintf (stderr, "Seems Jack server not running.\n");
        return -1;
    }

    jack_set_process_callback(Client, __libjack_process_callback, this);
    jack_on_shutdown(Client, __libjack_shutdown_callback, this);

    this->uiMaxSamplesPerCycle = jack_get_buffer_size(Client);
    this->uiSamplerate         = jack_get_sample_rate(Client);
    this->bInitialized         = true;

    // Acquire given output ports
    if(OutputPorts[0] != "")
        if ((this->playback_port[0] = jack_port_by_name(Client, OutputPorts[0].c_str())) == 0)
            fprintf (stderr, "JackIO: Invalid playback port %s.\n", OutputPorts[0].c_str());
    if(OutputPorts[1] != "")
        if ((this->playback_port[1] = jack_port_by_name(Client, OutputPorts[1].c_str())) == 0)
            fprintf (stderr, "JackIO: Invalid playback port %s.\n", OutputPorts[1].c_str());

    return 0;
}

void JackIO::Activate() {
    if (jack_activate(Client)) {
        fprintf (stderr, "JackIO: Cannot activate Jack client, exiting.\n");
        exit(EXIT_FAILURE);
    }

    if ((Ports[0] = jack_port_register(Client, "LinuxSampler:1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0)) == 0) {
        fprintf (stderr, "JackIO: Cannot register Jack output port, exiting.\n");
        Close();
        exit(-1);
    }

    if ((Ports[1] = jack_port_register(Client, "LinuxSampler:2", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0)) == 0) {
        fprintf (stderr, "JackIO: Cannot register Jack output port, exiting.\n");
        Close();
        exit(-1);
    }

    // Connect to given output ports
    if (playback_port[0])
        if (jack_connect(Client, jack_port_name(Ports[0]), jack_port_name(playback_port[0])))
            fprintf (stderr, "JackIO: Cannot connect port 0.\n");
    if (playback_port[1])
        if (jack_connect(Client, jack_port_name(Ports[1]), jack_port_name(playback_port[1])))
            fprintf (stderr, "JackIO: Cannot connect port 1.\n");
}

int JackIO::Process(uint Samples) {
    if (!pEngine) {
        fprintf(stderr, "JackIO: No Sampler Engine assigned, exiting.\n");
        exit(EXIT_FAILURE);
    }
    PendingSamples = Samples;


    // let the engine render audio for the current fragment
    int res = pEngine->RenderAudio(Samples);


    // check clipping (16 bit) in the audio sum and copy to output buffer
    float sample_point;
    for (uint c = 0; c < uiChannels; c++) {
        float* psumbuffer = pEngine->GetAudioSumBuffer(c);
        float* poutput    = (float*) GetChannelOutputBufer(c);
        for (uint s = 0; s < Samples; s++) {
            sample_point = psumbuffer[s] * pEngine->Volume;
            if (sample_point < -32768.0) sample_point = -32768.0;
            if (sample_point >  32767.0) sample_point =  32767.0;
            poutput[s] = sample_point / 32768.0;
        }
    }


    return res;
}

void JackIO::Close() {
    if (bInitialized) {
        jack_client_close (Client);
        bInitialized = false;
    }
}

void* JackIO::GetInterleavedOutputBuffer() {
    fprintf(stderr, "JackIO::GetInterleavedOutputBuffer(): No interleaved access allowed, exiting.\n");
    exit(EXIT_FAILURE);
    // just to avoid compiler warnings
    return NULL;
}

void* JackIO::GetChannelOutputBufer(uint Channel) {
    return (jack_default_audio_sample_t *) jack_port_get_buffer(Ports[Channel], PendingSamples);
}

int __libjack_process_callback(jack_nframes_t nframes, void* arg) {
    JackIO* pJackIO = (JackIO*) arg;
    return pJackIO->Process(nframes);
}

void __libjack_shutdown_callback(void* arg) {
    JackIO* pJackIO = (JackIO*) arg;
    pJackIO->Close();
    fprintf(stderr, "JackIO: Jack server shutdown, exiting.\n");
    exit(EXIT_FAILURE);
}

#endif // HAVE_JACK
