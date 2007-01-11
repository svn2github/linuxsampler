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

#include "FxSend.h"

#include "../drivers/audio/AudioOutputDevice.h"
#include "../common/RTMath.h"

#include <map>

namespace LinuxSampler {

    FxSend::FxSend(EngineChannel* pEngineChannel, uint8_t MidiCtrl, String Name) throw (Exception) {
        this->pEngineChannel = pEngineChannel;
        AudioOutputDevice* pDevice = pEngineChannel->GetAudioOutputDevice();
        const int iChanOffset = (pDevice) ? pDevice->ChannelCount() - pEngineChannel->Channels() : 0;
        for (int i = 0; i < pEngineChannel->Channels(); i++) {
            const int iDestination = iChanOffset + i;
            Routing.push_back(iDestination);
        }
        MidiFxSendController = MidiCtrl;
        sName = Name;

        // create an EngineChannel unique ID for this FxSend instance
        if (!pEngineChannel->GetFxSendCount()) iId = 0;
        else {
            // get the highest existing map ID
            uint highestIndex = 0;
            for (uint i = 0; i < pEngineChannel->GetFxSendCount(); i++)
                highestIndex = RTMath::Max(highestIndex, pEngineChannel->GetFxSend(i)->Id());
            // check if we reached the index limit
            if (highestIndex + 1 < highestIndex) {
                // search for an unoccupied map ID starting from 0
                for (uint i = 0; i < highestIndex; i++) {
                    bool bOccupied = false;
                    for (uint j = 0; j < pEngineChannel->GetFxSendCount(); j++) {
                        if (pEngineChannel->GetFxSend(j)->Id() == i) {
                            bOccupied = true;
                            break;
                        }
                    }
                    if (!bOccupied) {
                        iId = i;
                        goto __done;
                    }
                }
                throw Exception("Internal error: could not find unoccupied FxSend ID.");
            }
            iId = highestIndex + 1;
        }
        __done:

        fLevel = 0.3f; // default FX send level
    }

    int FxSend::DestinationChannel(int SrcChan) {
        if (SrcChan >= pEngineChannel->Channels()) return -1;
        return Routing[SrcChan];
    }

    void FxSend::SetDestinationChannel(int SrcChan, int DstChan) throw (Exception) {
        if (SrcChan < 0 || SrcChan >= pEngineChannel->Channels())
            throw Exception("Cannot alter FxSend routing, source channel out of bounds");
        AudioOutputDevice* pDevice = pEngineChannel->GetAudioOutputDevice();
        if (pDevice) {
            if (DstChan < 0 || DstChan >= pDevice->ChannelCount())
                throw Exception("Cannot alter FxSend routing, destination channel out of bounds");
        } else { // no audio device assigned yet
            if (DstChan < 0 || DstChan >= pEngineChannel->Channels())
                throw Exception(
                    "there is no audio device yet, so you cannot set a "
                    "FxSend destination channel higher than the engine "
                    "channel's amount of channels"
                );
        }
        Routing[SrcChan] = DstChan;
    }

    void FxSend::UpdateChannels() {
        if (Routing.size() > pEngineChannel->Channels()) {
            // add routings with default destinations
            AudioOutputDevice* pDevice = pEngineChannel->GetAudioOutputDevice();
            const int iChanOffset = (pDevice) ? pDevice->ChannelCount() - pEngineChannel->Channels() : 0;
            for (int i = Routing.size(); i < pEngineChannel->Channels(); i++) {
                const int iDestination = iChanOffset + i;
                Routing.push_back(iDestination);
            }
        } else if (Routing.size() < pEngineChannel->Channels()) {
            // shrink routing vector
            Routing.resize(pEngineChannel->Channels());
        }
    }

    float FxSend::Level() {
        return fLevel;
    }

    void FxSend::SetLevel(float f) {
        fLevel = f;
    }

    void FxSend::SetLevel(uint8_t iMidiValue) {
        fLevel = float(iMidiValue & 0x7f) / 127.0f;
    }

    uint8_t FxSend::MidiController() {
        return MidiFxSendController;
    }

    void FxSend::SetMidiController(uint8_t MidiCtrl) throw (Exception) {
        if (MidiCtrl & 0x7f)
            throw Exception("Invalid MIDI controller");
        MidiFxSendController = MidiCtrl;
    }

    String FxSend::Name() {
        return sName;
    }

    uint FxSend::Id() {
        return iId;
    }

} // namespace LinuxSampler