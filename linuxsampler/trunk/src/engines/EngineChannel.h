/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
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

#include "../drivers/audio/AudioOutputDevice.h"
#include "../drivers/midi/midi.h"
#include "../drivers/midi/MidiInputDevice.h"
#include "../drivers/midi/MidiInputPort.h"
#include "Engine.h"
#include "FxSend.h"

namespace LinuxSampler {

    // just symbol prototyping
    class AudioOutputDevice;
    class MidiInputPort;
    class FxSend;


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
            virtual void    Reset() = 0;
            virtual void    SendNoteOn(uint8_t Key, uint8_t Velocity) = 0;
            virtual void    SendNoteOn(uint8_t Key, uint8_t Velocity, int32_t FragmentPos) = 0;
            virtual void    SendNoteOff(uint8_t Key, uint8_t Velocity) = 0;
            virtual void    SendNoteOff(uint8_t Key, uint8_t Velocity, int32_t FragmentPos) = 0;
            virtual void    SendPitchbend(int Pitch) = 0;
            virtual void    SendPitchbend(int Pitch, int32_t FragmentPos) = 0;
            virtual void    SendControlChange(uint8_t Controller, uint8_t Value) = 0;
            virtual void    SendControlChange(uint8_t Controller, uint8_t Value, int32_t FragmentPos) = 0;
            virtual bool    StatusChanged(bool bNewStatus = false) = 0;
            virtual float   Volume() = 0;
            virtual void    Volume(float f) = 0;
            virtual uint    Channels() = 0;
            virtual void    Connect(AudioOutputDevice* pAudioOut) = 0;
            virtual void    DisconnectAudioOutputDevice() = 0;
            virtual AudioOutputDevice* GetAudioOutputDevice() = 0;
            virtual void    SetOutputChannel(uint EngineAudioChannel, uint AudioDeviceChannel) = 0;
            virtual int     OutputChannel(uint EngineAudioChannel) = 0;
            virtual void    Connect(MidiInputPort* pMidiPort, midi_chan_t MidiChannel) = 0;
            virtual void    DisconnectMidiInputPort() = 0;
            virtual MidiInputPort* GetMidiInputPort() = 0;
            virtual midi_chan_t MidiChannel() = 0;
            virtual String  InstrumentFileName() = 0;
            virtual String  InstrumentName() = 0;
            virtual int     InstrumentIndex() = 0;
            virtual int     InstrumentStatus() = 0;
            virtual Engine* GetEngine() = 0;
            virtual String  EngineName() = 0;
            virtual FxSend* AddFxSend(uint8_t MidiCtrl, String Name = "") throw (Exception) = 0;
            virtual FxSend* GetFxSend(uint FxSendIndex) = 0;
            virtual uint    GetFxSendCount() = 0;
            virtual void    RemoveFxSend(FxSend* pFxSend) = 0;


            /////////////////////////////////////////////////////////////////
            // normal methods
            //     (usually not to be overridden by descendant)

            /**
             * Sets the mute state of this channel.
             *
             * @param state - specifies the mute state of this sampler channel.
             * @throws Exception - if state does not contain valid
             * value.
             */
            void SetMute(int state) throw (Exception);

            /**
             * Determines whether this channel is muted.
             *
             * @returns 1 if the channel is muted, 0 if the channel is not muted
             * and -1 if the channel is muted because of presence of at least
             * one solo channel.
             */
            int GetMute();

            /**
             * Sets the solo state of this channel.
             *
             * @param solo - specifies whether this is a solo channel.
             */
            void SetSolo(bool solo);

            /**
             * Determines whether this is a solo channel.
             *
             * @returns true if this is a solo channel, false otherwise.
             */
            bool GetSolo();

            /**
             * Returns current MIDI program (change) number of this
             * EngineChannel.
             */
            uint8_t GetMidiProgram();

            /**
             * Change EngineChannel's MIDI program.
             */
            void SetMidiProgram(uint8_t Program);

            /**
             * Returns current MIDI bank MSB (coarse) number of this
             * EngineChannel.
             */
            uint8_t GetMidiBankMsb();

            /**
             * Change current MIDI bank MSB (coarse) number of this
             * EngineChannel.
             */
            void SetMidiBankMsb(uint8_t BankMSB);

            /**
             * Returns current MIDI bank LSB (fine) number of this
             * EngineChannel.
             */
            uint8_t GetMidiBankLsb();

            /**
             * Change current MIDI bank LSB (fine) number of this
             * EngineChannel.
             */
            void SetMidiBankLsb(uint8_t BankLSB);

            /**
             * Returns true if this EngineChannel is using no MIDI
             * instrument map at all, that is if it will ignore all MIDI
             * program change messages.
             *
             * @see UsesDefaultMidiInstrumentMap()
             * @see GetMidiInstrumentMap()
             */
            bool UsesNoMidiInstrumentMap();

            /**
             * Returns true if this EngineChannel is using the default MIDI
             * instrument map for handling MIDI program changes.
             *
             * @see UsesNoMidiInstrumentMap()
             * @see GetMidiInstrumentMap()
             */
            bool UsesDefaultMidiInstrumentMap();

            /**
             * Returns ID of the MIDI instrument map currently used by this
             * EngineChannel to handle MIDI program changes. You should
             * always call @c UsesNoMidiInstrumentMap() and
             * @c UsesDefaultMidiInstrumentMap() before calling this method
             * to check if this EngineChannel is probably using the default
             * map or no map at all, because in these two particular cases
             * this method would throw an exception!
             *
             * @throws Exception - if EngineChannel is set to no map at all
             *                     or is set to the default map
             * @see UsesNoMidiInstrumentMap()
             * @see UsesDefaultMidiInstrumentMap()
             */
            int GetMidiInstrumentMap() throw (Exception);

            /**
             * Let this EngineChannel use no MIDI instrument map at all,
             * that is to let it ignore all MIDI program change messages.
             *
             * @see SetMidiInstrumentMapToDefault()
             * @see SetMidiInstrumentMap()
             */
            void SetMidiInstrumentMapToNone();

            /**
             * Let this EngineChannel use the default MIDI instrument map to
             * handle MIDI program changes.
             *
             * @see SetMidiInstrumentMapToNone()
             * @see SetMidiInstrumentMap()
             */
            void SetMidiInstrumentMapToDefault();

            /**
             * Set a specific MIDI instrument map this EngineChannel should
             * use to handle MIDI program changes.
             *
             * @see SetMidiInstrumentMapToNone()
             * @see SetMidiInstrumentMapToDefault()
             *
             * @throws Exception - in case given map does not exist
             */
            void SetMidiInstrumentMap(int MidiMap) throw (Exception);

            /**
             * Set MIDI Registered Parameter Number (RPN) Controller
             * (upper 8 bits / coarse).
             */
            void SetMidiRpnControllerMsb(uint8_t CtrlMSB);

            /**
             * Set MIDI Registered Parameter Number (RPN) Controller
             * (lower 8 bits / fine).
             */
            void SetMidiRpnControllerLsb(uint8_t CtrlLSB);

            /**
             * Reset to no RPN controller currently selected.
             */
            void ResetMidiRpnController();

            /**
             * Get currently selected MIDI Registered Parameter Number
             * (RPN) Controller, this method will return the already merged
             * value (MSB and LSB value).
             *
             * @e WARNING: you have to call @c ResetMidiRpnController()
             * after using this value, otherwise all subsequent MIDI CC #6
             * (Data) messages are interpreted as RPN controller value
             * messages.
             *
             * @returns currently selected RPN controller number, a negative
             *          value if no RPN controller currently selected
             */
            int GetMidiRpnController();

            int iSamplerChannelIndex; ///< FIXME: nasty hack, might be removed (should be 'virtual EngineChannel* EngineChannel() = 0;', but due to cyclic dependencies only a void* solution would be possible ATM)

        protected:
            EngineChannel();
            virtual ~EngineChannel() {}; // MUST only be destroyed by EngineChannelFactory
            friend class EngineChannelFactory;

        private:
            int     iMute;
            bool    bSolo;
            uint8_t uiMidiProgram;
            uint8_t uiMidiBankMsb;
            uint8_t uiMidiBankLsb;
            uint8_t uiMidiRpnMsb; ///< MIDI Registered Parameter Number (upper 8 bits / coarse)
            uint8_t uiMidiRpnLsb; ///< MIDI Registered Parameter Number (lower 8 bits / fine)
            bool    bMidiBankMsbReceived;
            bool    bMidiBankLsbReceived;
            bool    bProgramChangeReceived;
            bool    bMidiRpnReceived;
            int     iMidiInstrumentMap;
    };

} // namespace LinuxSampler

#endif // __LS_ENGINECHANNEL_H__
