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

#ifndef __LS_AUDIOOUTPUTDEVICEJACK_H__
#define __LS_AUDIOOUTPUTDEVICEJACK_H__

#include "../common/global.h"

#if HAVE_JACK

#include <vector>
#include <sstream>
#include <jack/jack.h>

#include "AudioOutputDevice.h"
#include "../common/ConditionServer.h"

namespace LinuxSampler {

    /** JACK audio output driver
     *
     * Implements audio output to the JACK Audio Connection Kit (JACK).
     */
    class AudioOutputDeviceJack : public AudioOutputDevice {
        public:
            AudioOutputDeviceJack(std::map<String,DeviceCreationParameter*> Parameters);
            ~AudioOutputDeviceJack();

            // Audio channel parameter to connect to other Jack clients
            class ParameterJackBindings : public DeviceRuntimeParameterStrings {
                public:
                    ParameterJackBindings(AudioChannel* pChannel, std::vector<String> InitialBindings) : DeviceRuntimeParameterStrings(InitialBindings) { this->pChannel = pChannel; }
                    virtual String              Description()                      { return "Bindings to other JACK clients";                     }
                    virtual bool                Fix()                              { return false;                                                }
                    virtual std::vector<String> PossibilitiesAsString()            { return std::vector<String>(); /* TODO: to be implemented */  }
                    virtual void                OnSetValue(std::vector<String> vS) { /* TODO: code to connect to other jack clients */            }
                protected:
                    AudioChannel* pChannel;
            };

            // derived abstract methods from class 'AudioOutputDevice'
            virtual void Play();
            virtual bool IsPlaying();
            virtual void Stop();
            virtual void AcquireChannels(uint uiChannels);
            virtual uint MaxSamplesPerCycle();
            virtual uint SampleRate();

	    static String Name();

            virtual String Driver();

            static String Description();
            static String Version();
            static std::map<String,DeviceCreationParameter*> AvailableParameters();

            int Process(uint Samples);  // FIXME: should be private
        protected:
            AudioOutputDeviceJack(String* AutoConnectPortIDs = NULL, uint AutoConnectPorts = 0);
        private:
            ConditionServer           csIsPlaying;
            uint                      uiMaxSamplesPerCycle;
            jack_client_t*            hJackClient;
            std::vector<jack_port_t*> hJackPorts;
    };

    // Callback functions for the libjack API
    int  __libjack_process_callback(jack_nframes_t nframes, void* arg);
    void __libjack_shutdown_callback(void* arg);
}

#endif // HAVE_JACK
#endif // __LS_AUDIOOUTPUTDEVICEJACK_H__
