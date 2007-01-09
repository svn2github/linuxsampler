/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#ifndef LS_FXSEND_H
#define LS_FXSEND_H

#include "../common/global.h"
#include "../drivers/audio/AudioChannel.h"
#include "EngineChannel.h"

#include <vector>

namespace LinuxSampler {

    // just symbol prototyping
    class EngineChannel;

    /** @brief Engine Channel Effect Send
     *
     * This class is used to manage effect sends on Engine Channels. An effect
     * send is used to route sampler channel's audio signals to sampler
     * external effect processors. Each effect send entity can define an
     * arbitrary MIDI controller number which can alter the effect send's
     * send level.
     *
     * Note: effect sends cannot be routed to a different AudioOutputDevice
     * than assigned to the FxSend's EngineChannel. Also note that an effect
     * send always has as much audio channels as its EngineChannel.
     */
    class FxSend {
        public:
            /**
             * Constructor. By default all effect send channels are routed to
             * the @e last available audio channels on the EngineChannel's
             * AudioOutputDevice.
             *
             * @param pEngineChannel - engine channel on which the effect send
             *                         is added to
             * @param MidiCtrl - MIDI controller number which can alter the
             *                   effect send level
             * @param Name - (optional) name for the effect send entity
             *
             * @throws Exception - in case no free ID could be found on given EngineChannel
             */
            FxSend(EngineChannel* pEngineChannel, uint8_t MidiCtrl, String Name = "") throw (Exception);

            /**
             * Returns the audio output device's audio channel to which effect
             * send's channel \a SrcChan is currently routed to.
             */
            int DestinationChannel(int SrcChan);

            /**
             * Alters the routing of an audio channel.
             *
             * @param SrcChan - the effect send's source channel
             * @param DstChan - the audio output device's destination channel
             * @throws Exception - in case arguments out of range
             */
            void SetDestinationChannel(int SrcChan, int DstChan) throw (Exception);

            /**
             * Should be called by the engine channel whenever the amount of
             * audio channel has changed, so the FxSend object can adjust the
             * amount of channels to that new number and establish default
             * routings for new channels if needed.
             */
            void UpdateChannels();

            /**
             * The effect send's current send level ( usually a value between
             * @c 0.0f and @c 1.0f ).
             */
            float Level();

            /**
             * Alter the effect send's send level ( usually a value between
             * @c 0.0f and @c 1.0f ).
             */
            void SetLevel(float f);

            /**
             * Alter the effect send's send level by supplying the MIDI
             * controller's MIDI value. This method is usually only called
             * by the engine channel.
             */
            void SetLevel(uint8_t iMidiValue);

            /**
             * Returns the MIDI controller number which can alter the effect
             * send's send level.
             */
            uint8_t MidiController();

            /**
             * Alter the MIDI controller number which should alter the effect
             * send's send level.
             *
             * @param MidiCtrl - MIDI controller number
             * @throws Exception - if MIDI controller number is invalid
             */
            void SetMidiController(uint8_t MidiCtrl) throw (Exception);

            /**
             * Returns the (optional) name of this effect send entity.
             */
            String Name();

            /**
             * Returns the (at least sampler-channel-) unique ID of the
             * effect send instance. This is actually not used by the engine
             * at all. It is at the moment only used by the LSCP server to
             * associate an unique numerical ID with each effect send entity.
             */
            uint Id();

        protected:
            EngineChannel*   pEngineChannel;
            std::vector<int> Routing;
            uint8_t          MidiFxSendController;
            String           sName;
            uint             iId;
            float            fLevel;
    };

} // namespace LinuxSampler

#endif // LS_FXSEND_H
