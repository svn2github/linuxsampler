/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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

#ifndef __LS_ENGINECHANNEL_H__
#define __LS_ENGINECHANNEL_H__

#include "../../drivers/audio/AudioOutputDevice.h"
#include "Engine.h"

namespace LinuxSampler {

    // just symbol prototyping
    class AudioOutputDevice;

    /** @brief Channel Interface for LinuxSampler Sampler Engines
     *
     * Every sampler engine can be used on several sampler channels and
     * usually the same Engine instance is used on multiple sampler
     * channels. For this every sampler engine must also implement a class
     * which handles all channel dependant parameters and channel
     * dependant execution code.
     *
     * This abstract base interface class defines all mandatory methods
     * which have to be implemented by all engine channel implementations.
     */
    class EngineChannel {
        public:
    
            /////////////////////////////////////////////////////////////////
            // abstract methods
            //     (these have to be implemented by the descendant)
            
            virtual void    PrepareLoadInstrument(const char* FileName, uint Instrument) = 0;
            virtual void    LoadInstrument() = 0;
            virtual void    SendNoteOn(uint8_t Key, uint8_t Velocity) = 0;
            virtual void    SendNoteOff(uint8_t Key, uint8_t Velocity) = 0;
            virtual void    SendPitchbend(int Pitch) = 0;
            virtual void    SendControlChange(uint8_t Controller, uint8_t Value) = 0;            
            virtual float   Volume() = 0;
            virtual void    Volume(float f) = 0;
            virtual uint    Channels() = 0;            
            virtual void    Connect(AudioOutputDevice* pAudioOut) = 0;
            virtual void    DisconnectAudioOutputDevice() = 0;
            virtual void    SetOutputChannel(uint EngineAudioChannel, uint AudioDeviceChannel) = 0;
            virtual int     OutputChannel(uint EngineAudioChannel) = 0;            
            virtual String  InstrumentFileName() = 0;
            virtual String  InstrumentName() = 0;
            virtual int     InstrumentIndex() = 0;
            virtual int     InstrumentStatus() = 0;
            virtual Engine* GetEngine() = 0;

            virtual ~EngineChannel() {};
    };
    
} // namespace LinuxSampler
 
#endif // __LS_ENGINECHANNEL_H__
