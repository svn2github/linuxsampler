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

#ifndef __LS_AUDIOOUTPUTDEVICEALSA_H__
#define __LS_AUDIOOUTPUTDEVICEALSA_H__

#include <string.h>
#include <alsa/asoundlib.h>

#include "../common/global.h"
#include "../common/Thread.h"
#include "AudioOutputDevice.h"
#include "AudioChannel.h"
#include "../drivers/DeviceParameter.h"

namespace LinuxSampler {

    /** ALSA audio output driver
     *
     * Implements audio output to the Advanced Linux Sound Architecture (ALSA).
     */
    class AudioOutputDeviceAlsa : public AudioOutputDevice, protected Thread {
        public:
            AudioOutputDeviceAlsa(std::map<String,DeviceCreationParameter*> Parameters);
            ~AudioOutputDeviceAlsa();

            // derived abstract methods from class 'AudioOutputDevice'
            virtual void Play();
            virtual bool IsPlaying();
            virtual void Stop();
            virtual void AcquireChannels(uint Channels);
            virtual uint MaxSamplesPerCycle();
            virtual uint SampleRate();

            virtual String Driver();

	    static String Name();

            static String Description();
            static String Version();

            class ParameterCard : public DeviceCreationParameterString {
                public:
                    ParameterCard( void ) : DeviceCreationParameterString ()                              { InitWithDefault();                                             }
                    ParameterCard( String s ) : DeviceCreationParameterString (s)                         {}
                    virtual String Description()                                                          { return "Sound card to be used";                                }
                    virtual bool   Fix()                                                                  { return true;                                                   }
                    virtual bool   Mandatory()                                                            { return false;                                                  }
                    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters()               { return std::map<String,DeviceCreationParameter*>();            }
                    virtual optional<String>    Default(std::map<String,String> Parameters)               { return "0,0"; /* first card by default */                      }
                    virtual std::vector<String> PossibilitiesAsString(std::map<String,String> Parameters) { return std::vector<String>(); /*TODO: return possible cards*/  }
                    virtual void                OnSetValue(String s) throw (LinuxSamplerException)        { /* not posssible, as parameter is fix */                       }
		    static String Name( void ) { return "card"; }
            };

            class ParameterFragments : public DeviceCreationParameterInt {
                public:
                    ParameterFragments( void ) : DeviceCreationParameterInt ()                      { InitWithDefault();                                  }
                    ParameterFragments( String s ) : DeviceCreationParameterInt (s)                 {}
                    virtual String Description()                                                    { return "Number of buffer fragments";                }
                    virtual bool   Fix()                                                            { return true;                                        }
                    virtual bool   Mandatory()                                                      { return false;                                       }
                    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters()         { return std::map<String,DeviceCreationParameter*>(); } //TODO: should return dependency to CARD
                    virtual optional<int>    DefaultAsInt(std::map<String,String> Parameters)       { return 2; /* until done */                          }
                    virtual optional<int>    RangeMinAsInt(std::map<String,String> Parameters)      { return optional<int>::nothing;                      }
                    virtual optional<int>    RangeMaxAsInt(std::map<String,String> Parameters)      { return optional<int>::nothing;                      }
                    virtual std::vector<int> PossibilitiesAsInt(std::map<String,String> Parameters) { return std::vector<int>();                          }
                    virtual void             OnSetValue(int i) throw (LinuxSamplerException)        { /* not posssible, as parameter is fix */            }
		    static String Name( void ) { return "fragments"; }
            };

            class ParameterFragmentSize : public DeviceCreationParameterInt {
                public:
                    ParameterFragmentSize( void ) : DeviceCreationParameterInt ()                   { InitWithDefault();                                  }
                    ParameterFragmentSize( String s ) : DeviceCreationParameterInt (s)              {}
                    virtual String Description()                                                    { return "Size of each buffer fragment";              }
                    virtual bool   Fix()                                                            { return true;                                        }
                    virtual bool   Mandatory()                                                      { return false;                                       }
                    virtual std::map<String,DeviceCreationParameter*> DependsAsParameters()         { return std::map<String,DeviceCreationParameter*>(); } //TODO: should return dependency to CARD
                    virtual optional<int>    DefaultAsInt(std::map<String,String> Parameters)       { return 128; /* until done */                        }
                    virtual optional<int>    RangeMinAsInt(std::map<String,String> Parameters)      { return optional<int>::nothing;                      }
                    virtual optional<int>    RangeMaxAsInt(std::map<String,String> Parameters)      { return optional<int>::nothing;                      }
                    virtual std::vector<int> PossibilitiesAsInt(std::map<String,String> Parameters) { return std::vector<int>();                          }
                    virtual void             OnSetValue(int i) throw (LinuxSamplerException)        { /* not posssible, as parameter is fix */            }
		    static String Name( void ) { return "fragmentsize"; }
            };

        protected:
            int Main();  ///< Implementation of virtual method from class Thread

        private:
            uint                 uiAlsaChannels;
            uint                 uiSamplerate;
            uint                 FragmentSize;
            int16_t*             pAlsaOutputBuffer; ///< This is the buffer where the final mix will be copied to and send to the sound card
            String               pcm_name;          ///< Name of the PCM device, like plughw:0,0 the first number is the number of the soundcard, the second number is the number of the device.
            snd_pcm_t*           pcm_handle;        ///< Handle for the PCM device
            snd_pcm_stream_t     stream;
            snd_pcm_hw_params_t* hwparams;          ///< This structure contains information about the hardware and can be used to specify the configuration to be used for the PCM stream.
            snd_pcm_sw_params_t* swparams;

            int  Output();
            bool HardwareParametersSupported(String card, uint channels, int samplerate, uint numfragments, uint fragmentsize);
    };
}

#endif // __LS_AUDIOOUTPUTDEVICEALSA_H__
