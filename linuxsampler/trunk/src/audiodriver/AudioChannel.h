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

#ifndef __LS_AUDIOCHANNEL_H__
#define __LS_AUDIOCHANNEL_H__

#include <string.h>
#include "../common/global.h"

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
            // attributes
            String Name;  ///< Arbitrary name of this audio channel

            // constructors / destructor
            AudioChannel(uint BufferSize, String Name = "unnamed");
            AudioChannel(float* pBuffer, uint BufferSize, String Name = "unnamed");
            AudioChannel(AudioChannel* pMixChannel, String Name = "unnamed");
            ~AudioChannel();

            // methods
            inline float*        Buffer()     { return pBuffer;      } ///< Audio signal buffer
            inline AudioChannel* MixChannel() { return pMixChannel;  } ///< In case this channel is a mix channel, then it will return a pointer to the real channel this channel refers to, NULL otherwise.
            inline void          Clear()      { memset(pBuffer, 0, uiBufferSize * sizeof(float)); } ///< Reset audio buffer with silence
        private:
            float*        pBuffer;
            uint          uiBufferSize;
            AudioChannel* pMixChannel;
            bool          UsesExternalBuffer;
    };
}

#endif // __LS_AUDIOCHANNEL_H__
