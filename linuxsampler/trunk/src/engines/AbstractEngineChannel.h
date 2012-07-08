/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003,2004 by Benno Senoner and Christian Schoenebeck    *
 *   Copyright (C) 2005-2008 Christian Schoenebeck                         *
 *   Copyright (C) 2009-2012 Christian Schoenebeck and Grigor Iliev        *
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

#ifndef __LS_ABSTRACTENGINECHANNEL_H__
#define __LS_ABSTRACTENGINECHANNEL_H__

#include "EngineChannel.h"
#include "AbstractEngine.h"

#include "../common/Pool.h"
#include "../common/RingBuffer.h"

namespace LinuxSampler {

    class AbstractEngineChannel: public EngineChannel {
        public:
            // implementation of abstract methods derived from interface class 'LinuxSampler::EngineChannel'
            virtual void    PrepareLoadInstrument(const char* FileName, uint Instrument);
            virtual void    Reset();
            virtual void    SendNoteOn(uint8_t Key, uint8_t Velocity, uint8_t MidiChannel);
            virtual void    SendNoteOn(uint8_t Key, uint8_t Velocity, uint8_t MidiChannel, int32_t FragmentPos);
            virtual void    SendNoteOff(uint8_t Key, uint8_t Velocity, uint8_t MidiChannel);
            virtual void    SendNoteOff(uint8_t Key, uint8_t Velocity, uint8_t MidiChannel, int32_t FragmentPos);
            virtual void    SendPitchbend(int Pitch, uint8_t MidiChannel);
            virtual void    SendPitchbend(int Pitch, uint8_t MidiChannel, int32_t FragmentPos);
            virtual void    SendControlChange(uint8_t Controller, uint8_t Value, uint8_t MidiChannel);
            virtual void    SendControlChange(uint8_t Controller, uint8_t Value, uint8_t MidiChannel, int32_t FragmentPos);
            virtual bool    StatusChanged(bool bNewStatus = false);
            virtual float   Volume();
            virtual void    Volume(float f);
            virtual float   Pan();
            virtual void    Pan(float f);
            virtual uint    Channels();
            virtual AudioOutputDevice* GetAudioOutputDevice();
            virtual void    SetOutputChannel(uint EngineAudioChannel, uint AudioDeviceChannel);
            virtual int     OutputChannel(uint EngineAudioChannel);
            virtual void    Connect(MidiInputPort* pMidiPort, midi_chan_t MidiChannel);
            virtual void    DisconnectMidiInputPort();
            virtual MidiInputPort* GetMidiInputPort();
            virtual midi_chan_t MidiChannel();
            virtual String  InstrumentFileName();
            virtual String  InstrumentName();
            virtual int     InstrumentIndex();
            virtual int     InstrumentStatus();
            virtual Engine* GetEngine();
            virtual String  EngineName();
            virtual FxSend* AddFxSend(uint8_t MidiCtrl, String Name = "") throw (Exception);
            virtual FxSend* GetFxSend(uint FxSendIndex);
            virtual uint    GetFxSendCount();
            virtual void    RemoveFxSend(FxSend* pFxSend);
            virtual void    Connect(VirtualMidiDevice* pDevice);
            virtual void    Disconnect(VirtualMidiDevice* pDevice);


            virtual AbstractEngine::Format GetEngineFormat() = 0;

            AudioOutputDevice* GetAudioOutputDeviceSafe();

            friend class AbstractVoice;
            friend class AbstractEngine;
            template<class TV, class TRR, class TR, class TD, class TIM, class TI> friend class EngineBase;
            template<class EC, class R, class S, class D> friend class VoiceBase;

        protected:
            AbstractEngineChannel();
            virtual ~AbstractEngineChannel();

            AbstractEngine*           pEngine;
            Mutex                     EngineMutex; ///< protects the Engine from access by the instrument loader thread when lscp is disconnecting

        protected:
            AudioChannel*             pChannelLeft;             ///< encapsulates the audio rendering buffer (left)
            AudioChannel*             pChannelRight;            ///< encapsulates the audio rendering buffer (right)
            int                       AudioDeviceChannelLeft;   ///< audio device channel number to which the left channel is connected to
            int                       AudioDeviceChannelRight;  ///< audio device channel number to which the right channel is connected to
            MidiInputPort*            pMidiInputPort;           ///< Points to the connected MIDI input port or NULL if none assigned.
            midi_chan_t               midiChannel;              ///< MIDI channel(s) on which this engine channel listens to.
            RingBuffer<Event,false>*  pEventQueue;              ///< Input event queue.
            RTList<Event>*            pEvents;                  ///< All engine channel specific events for the current audio fragment.
            uint8_t                   ControllerTable[129];     ///< Reflects the current values (0-127) of all MIDI controllers for this engine / sampler channel. Number 128 is for channel pressure (mono aftertouch).
            String                    InstrumentFile;
            int                       InstrumentIdx;
            String                    InstrumentIdxName;
            int                       InstrumentStat;
            double                    GlobalVolume;             ///< Master volume factor set through the C++ API / LSCP (a value < 1.0 means attenuation, a value > 1.0 means amplification)
            double                    MidiVolume;               ///< Volume factor altered by MIDI CC#7 (a value < 1.0 means attenuation, a value > 1.0 means amplification)
            float                     GlobalPanLeft;
            float                     GlobalPanRight;
            int                       Pitch;                    ///< Current (absolute) MIDI pitch value.
            float                     CurrentKeyDimension;      ///< Current value (0-1.0) for the keyboard dimension, altered by pressing a keyswitching key.
            bool                      PortamentoMode;           ///< in Portamento Mode we slide the pitch from the last note to the current note.
            float                     PortamentoTime;           ///< How long it will take to glide from the previous note to the current (in seconds)
            float                     PortamentoPos;            ///< Current position on the keyboard, that is integer and fractional part (only used if PortamentoMode is on)
            std::vector<FxSend*>      fxSends;
            int                       GlobalTranspose;          ///< amount of semi tones all notes should be transposed
            int                       iLastPanRequest;          ///< just for the return value of Pan(), so we don't have to make an injective function
            int                       iEngineIndexSelf;         ///< Reflects the index of this EngineChannel in the Engine's ArrayList.
            bool                      bStatusChanged;           ///< true in case an engine parameter has changed (e.g. new instrument, another volumet)
            uint32_t                  RoundRobinIndex;          ///< counter for round robin sample selection, incremented for each note on

            SynchronizedConfig< ArrayList<VirtualMidiDevice*> > virtualMidiDevices;
            SynchronizedConfig< ArrayList<VirtualMidiDevice*> >::Reader virtualMidiDevicesReader_AudioThread;
            SynchronizedConfig< ArrayList<VirtualMidiDevice*> >::Reader virtualMidiDevicesReader_MidiThread;

            // specialization of RTList that doesn't require the pool
            // to be provided at construction time
            template<typename T>
            class LazyList : public RTList<T> {
            public:
                using RTList<T>::allocAppend;
                using RTList<T>::pPool;

                LazyList() : RTList<T>(0) { }
                typename RTList<T>::Iterator allocAppend(Pool<T>* pool) {
                    pPool = pool;
                    return allocAppend();
                }
            };
            
            typedef std::map<uint, LazyList<Event>*> ActiveKeyGroupMap;
            ActiveKeyGroupMap ActiveKeyGroups;      ///< Contains event queues for key groups, ordered by key group ID.

            virtual void ResetControllers();
            virtual void ResetInternal();
            virtual void RemoveAllFxSends();

            void ImportEvents(uint Samples);

            void AddGroup(uint group);
            void HandleKeyGroupConflicts(uint KeyGroup, Pool<Event>::Iterator& itNoteOnEvent);
            void ClearGroupEventLists();
            void DeleteGroupEventLists();
    };

} // namespace LinuxSampler

#endif  /* __LS_ABSTRACTENGINECHANNEL_H__ */

