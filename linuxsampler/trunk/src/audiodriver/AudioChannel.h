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

#ifndef __LS_AUDIOCHANNEL_H__
#define __LS_AUDIOCHANNEL_H__

#include <map>
#include <vector>
#include <string.h>
#include "../common/global.h"
#include "../drivers/DeviceParameter.h"

namespace LinuxSampler {

    /** Audio Channel (always mono)
     *
     * This class is used for routing audio signals between arbitrary sources
     * and destinations. You can either create a normal channel like:
     *
     *	AudioChannel c1(512); // create unnamed channel
     *	AudioChannel c2(512, "Effect send mono channel"); // create named channel
     *
     * Or you can create a mix channel, e.g. the following would create a
     * normal channel first, and the second channel is just a copy of the
     * first channel:
     *
     *	AudioChannel mono_chan(512, "Effect send channel"); // real channel
     *	AudioChannel mix_chan(&mono_chan, "Effect send mono channel"); // mix channel
     *
     * So in the last example, when writing to 'mix_chan' the signal will
     * actually be mixed to the 'mono_chan' channel, so this is an easy way
     * to downmix a signal source which has more audio channels than the
     * signal destination can offer.
     */
    class AudioChannel {
        public:

            class ParameterName : public DeviceRuntimeParameterString {
                public:
                    ParameterName(String s) : DeviceRuntimeParameterString(s) {}
                    virtual String              Description()           { return "Arbitrary name";      }
                    virtual bool                Fix()                   { return false;                 }
                    virtual std::vector<String> PossibilitiesAsString() { return std::vector<String>(); }
                    virtual void                OnSetValue(String s)    { /* nothing to do */           }
            };

            class ParameterIsMixChannel : public DeviceRuntimeParameterBool {
                public:
                    ParameterIsMixChannel(bool b) : DeviceRuntimeParameterBool(b) {}
                    virtual String Description()                                    { return "Wether real channel or mixed to another channel"; }
                    virtual bool   Fix()                                            { return true;                                              }
                    virtual void   OnSetValue(bool b) throw (LinuxSamplerException) { /* cannot happen, as parameter is fix */                  }
            };

            class ParameterMixChannelDestination : public DeviceRuntimeParameterInt {
                public:
                    ParameterMixChannelDestination(int i) : DeviceRuntimeParameterInt(i) {}
                    virtual String           Description()                                   { return "Destination channel of this mix channel";                 }
                    virtual bool             Fix()                                           { return true;                                                      }
                    virtual optional<int>    RangeMinAsInt()                                 { return optional<int>::nothing; /*TODO: needs to be implemented */ }
                    virtual optional<int>    RangeMaxAsInt()                                 { return optional<int>::nothing; /*TODO: needs to be implemented */ }
                    virtual std::vector<int> PossibilitiesAsInt()                            { return std::vector<int>();     /*TODO: needs to be implemented */ }
                    virtual void             OnSetValue(int i) throw (LinuxSamplerException) { /*TODO: needs to be implemented */                                }
            };

            // attributes
            //String Name;  ///< Arbitrary name of this audio channel

            // constructors / destructor
#ifdef __GNUC__
            typedef std::map<String,DeviceRuntimeParameter*> DeviceRuntimeParameterMap; // nasty workaround for a GCC bug (see GCC bug #15980, #57)
            AudioChannel(uint BufferSize, String Name = "unnamed", std::map<String,DeviceRuntimeParameter*> ChannelParameters = DeviceRuntimeParameterMap());
            AudioChannel(float* pBuffer, uint BufferSize, String Name = "unnamed", std::map<String,DeviceRuntimeParameter*> ChannelParameters = DeviceRuntimeParameterMap());
            AudioChannel(AudioChannel* pMixChannel, String Name = "unnamed", std::map<String,DeviceRuntimeParameter*> ChannelParameters = DeviceRuntimeParameterMap());
#else
            AudioChannel(uint BufferSize, String Name = "unnamed", std::map<String,DeviceRuntimeParameter*> ChannelParameters = std::map<String,DeviceRuntimeParameter*>());
            AudioChannel(float* pBuffer, uint BufferSize, String Name = "unnamed", std::map<String,DeviceRuntimeParameter*> ChannelParameters = std::map<String,DeviceRuntimeParameter*>());
            AudioChannel(AudioChannel* pMixChannel, String Name = "unnamed", std::map<String,DeviceRuntimeParameter*> ChannelParameters = std::map<String,DeviceRuntimeParameter*>());
#endif // __GNUC__
            virtual ~AudioChannel();

            // methods
            inline float*        Buffer()     { return pBuffer;      } ///< Audio signal buffer
            inline AudioChannel* MixChannel() { return pMixChannel;  } ///< In case this channel is a mix channel, then it will return a pointer to the real channel this channel refers to, NULL otherwise.
            inline void          Clear()      { memset(pBuffer, 0, uiBufferSize * sizeof(float)); } ///< Reset audio buffer with silence
            std::map<String,DeviceRuntimeParameter*> ChannelParameters();
        private:
            float*        pBuffer;
            uint          uiBufferSize;
            AudioChannel* pMixChannel;
            bool          UsesExternalBuffer;
            std::map<String,DeviceRuntimeParameter*> mParameters;
    };
}

#endif // __LS_AUDIOCHANNEL_H__
