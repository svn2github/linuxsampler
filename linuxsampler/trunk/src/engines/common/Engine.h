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

#ifndef __LS_ENGINE_H__
#define __LS_ENGINE_H__

#include "../../common/global.h"
#include "../../drivers/audio/AudioOutputDevice.h"

namespace LinuxSampler {

    // just symbol prototyping
    class AudioOutputDevice;

    /** LinuxSampler Sampler Engine
     *
     * Abstract base class for all LinuxSampler engines.
     */
    class Engine {
        public:

	    virtual ~Engine() {};

            /////////////////////////////////////////////////////////////////
            // type definitions

            /**
             * List with all currently implemented sampler engines.
             */
            enum type_t {
                type_gig
            };



            /////////////////////////////////////////////////////////////////
            // abstract methods
            //     (these have to be implemented by the descendant)

            virtual void   LoadInstrument(const char* FileName, uint Instrument) = 0;
            virtual void   Reset() = 0;
            virtual void   Enable() = 0;
            virtual void   Disable() = 0;
            virtual void   SendNoteOn(uint8_t Key, uint8_t Velocity) = 0;
            virtual void   SendNoteOff(uint8_t Key, uint8_t Velocity) = 0;
            virtual void   SendPitchbend(int Pitch) = 0;
            virtual void   SendControlChange(uint8_t Controller, uint8_t Value) = 0;
            virtual void   SendSysex(void* pData, uint Size) = 0;
            virtual float  Volume() = 0;
            virtual void   Volume(float f) = 0;
            virtual uint   Channels() = 0;
            virtual void   Connect(AudioOutputDevice* pAudioOut) = 0;
            virtual void   DisconnectAudioOutputDevice() = 0;
            virtual void   SetOutputChannel(uint EngineAudioChannel, uint AudioDeviceChannel) = 0;
            virtual int    OutputChannel(uint EngineAudioChannel) = 0;
            virtual int    RenderAudio(uint Samples) = 0;
            virtual uint   VoiceCount() = 0;
            virtual uint   VoiceCountMax() = 0;
            virtual bool   DiskStreamSupported() = 0;
            virtual uint   DiskStreamCount() = 0;
            virtual uint   DiskStreamCountMax() = 0;
            virtual String DiskStreamBufferFillBytes() = 0;
            virtual String DiskStreamBufferFillPercentage() = 0;
            virtual String Description() = 0;
            virtual String Version() = 0;
            virtual String EngineName() = 0;
            virtual String InstrumentFileName() = 0;
            virtual String InstrumentName() = 0;
            virtual int    InstrumentIndex() = 0;
            virtual int    InstrumentStatus() = 0;
    };
}

#endif // __LS_ENGINE_H__
