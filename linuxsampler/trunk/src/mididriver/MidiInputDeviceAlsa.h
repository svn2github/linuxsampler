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

#ifndef __LS_MIDIINPUTDEVICEALSA_H__
#define __LS_MIDIINPUTDEVICEALSA_H__

#include <alsa/asoundlib.h>

#include "../common/global.h"
#include "../common/Thread.h"
#include "../common/RingBuffer.h"
#include "MidiInputDevice.h"

namespace LinuxSampler {

    /** ALSA MIDI input driver
     *
     * Implements MIDI input for the Advanced Linux Sound Architecture
     * (ALSA).
     */
    class MidiInputDeviceAlsa : public MidiInputDevice, public Thread {
        public:
            MidiInputDeviceAlsa(std::map<String,String> Parameters);
            ~MidiInputDeviceAlsa();

            // derived abstract methods from class 'MidiInputDevice'
            void Listen();
            void StopListen();
	    String Driver() { return "Alsa"; };

	    static String Description();
	    static String Version();

	    class MidiInputPortAlsa : public MidiInputPort {
		    public:
			    void ConnectToAlsaMidiSource(const char* MidiSource);

			    class ParameterAlsaSeqBindings : public DeviceCreationParameterString {
				    public:
					    ParameterAlsaSeqBindings(MidiInputPortAlsa* pPort) { this->pPort = pPort; InitWithDefault();}
					    virtual String Description()                                                    { return "Bindings to other Alsa sequencer clients";   }
					    virtual bool   Fix()                                                            { return false;   }
					    virtual bool   Mandatory()                                                      { return false;   }
					    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters()         { return std::map<String,DeviceCreationParameter*>(); }
					    virtual optional<String>    Default(std::map<String,String> Parameters)         { return ""; }
					    virtual std::vector<String> PossibilitiesAsString(std::map<String,String> Parameters) { return std::vector<String>(); } //TODO
					    virtual void             OnSetValue(String s) throw (LinuxSamplerException)     { pPort->ConnectToAlsaMidiSource(s.c_str()); }
				    protected:
					    MidiInputPortAlsa* pPort;
			    };

		    protected:
			    MidiInputPortAlsa(MidiInputDeviceAlsa* pDevice, int portNumber);
			    ~MidiInputPortAlsa();
			    friend class MidiInputDeviceAlsa;
		    private:
			    MidiInputDeviceAlsa* pDevice;
	    };

	    MidiInputPortAlsa* CreateMidiPort( void );

        protected:
	    std::map<String,DeviceCreationParameter*> CreateParameters(std::map<String,String> Parameters);
            int Main(); ///< Implementation of virtual method from class Thread
        private:
	    static std::map<String,DeviceCreationParameter*> CreateAvailableParameters();
            snd_seq_t* hAlsaSeq;
            int        hAlsaSeqClient;       ///< Alsa Sequencer client ID
    };
}

#endif // __LS_MIDIINPUTDEVICEALSA_H__
