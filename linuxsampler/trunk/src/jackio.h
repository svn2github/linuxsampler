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

#ifndef __JACKIO_H__
#define __JACKIO_H__

#include "global.h"
#include "audioio.h"
#include "audiothread.h"

#if HAVE_JACK

#include <jack/jack.h>

//TODO: only stereo (2 ports / channels) at the moment

// Callback functions for the libjack API
int  __libjack_process_callback(jack_nframes_t nframes, void* arg);
void __libjack_shutdown_callback(void* arg);

class JackIO : public AudioIO {
    public:
        JackIO();
        int   Initialize(uint Channels);
        void  Activate();
        void  Close();
        void* GetInterleavedOutputBuffer();
        void* GetChannelOutputBufer(uint Channel);
        int   Process(uint Samples);  // FIXME: should be private
    private:
        typedef std::string String;

        jack_client_t* Client;
        jack_port_t*   Ports[2];
        uint           PendingSamples;
};

#endif // HAVE_JACK
#endif // __JACKIO_H__
