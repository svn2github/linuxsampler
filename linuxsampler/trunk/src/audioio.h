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

#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "global.h"

// just symbol prototyping
class AudioThread;

/**
 * Abstract class for audio output in LinuxSampler. This class will be
 * derived by specialized classes which implement the connection to a
 * specific audio output system (e.g. Alsa, Jack).
 */
class AudioIO {
    public:
        AudioIO();
        virtual ~AudioIO();
        virtual void  Activate() = 0;
        virtual void  Close() = 0;
        virtual void* GetInterleavedOutputBuffer() = 0;
        virtual void* GetChannelOutputBufer(uint Channel) = 0;
        inline  void  AssignEngine(AudioThread* pAudioThread) { pEngine = pAudioThread;      };
        inline  bool  Initialized()                           { return bInitialized;         };
        inline  bool  Interleaved()                           { return bInterleaved;         };
        inline  uint  Channels()                              { return uiChannels;           };
        inline  uint  SampleRate()                            { return uiSamplerate;         };
        inline  uint  MaxSamplesPerCycle()                    { return uiMaxSamplesPerCycle; };
    protected:
        bool bInitialized;
        bool bInterleaved;
        uint uiChannels;
        uint uiSamplerate;
        uint uiMaxSamplesPerCycle;   ///< in sample points
        AudioThread* pEngine;
};

#endif // __AUDIO_H__
