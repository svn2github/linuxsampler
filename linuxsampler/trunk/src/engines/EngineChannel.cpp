/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2009 Christian Schoenebeck                       *
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

#include "EngineChannel.h"

#include <algorithm>

#include "../Sampler.h"
#include "../common/global_private.h"
#include "../drivers/midi/MidiInstrumentMapper.h"
#include "../common/atomic.h"

#define NO_MIDI_INSTRUMENT_MAP		-1
#define DEFAULT_MIDI_INSTRUMENT_MAP	-2

namespace LinuxSampler {

    struct EngineChannel::private_data_t {
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
        atomic_t voiceCount;
        atomic_t diskStreamCount;
        SamplerChannel* pSamplerChannel;
        ListenerList<FxSendCountListener*> llFxSendCountListeners;
    };

    EngineChannel::EngineChannel() : p(new private_data_t) {
        p->iMute = 0;
        p->bSolo = false;
        p->uiMidiBankMsb = 0;
        p->uiMidiBankLsb = 0;
        p->uiMidiProgram = 0;
        p->bProgramChangeReceived =
        p->bMidiBankMsbReceived =
        p->bMidiBankLsbReceived = false;
        p->iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
        SetVoiceCount(0);
        SetDiskStreamCount(0);
        p->pSamplerChannel = NULL;
        ResetMidiRpnController();
    }

    EngineChannel::~EngineChannel() {
        delete p;
    }

    void EngineChannel::SetMute(int state) throw (Exception) {
        if (p->iMute == state) return;
        if (state < -1 || state > 1)
            throw Exception("Invalid Mute state: " + ToString(state));

        p->iMute = state;

        StatusChanged(true);
    }

    int EngineChannel::GetMute() {
        return p->iMute;
    }

    void EngineChannel::SetSolo(bool solo) {
        if (p->bSolo == solo) return;
        p->bSolo = solo;
        StatusChanged(true);
    }

    bool EngineChannel::GetSolo() {
        return p->bSolo;
    }

    /*
       We use a workaround for MIDI devices (i.e. old keyboards) which either
       only send bank select MSB or only bank select LSB messages. Bank
       selects will be modified according to the following table:

       MIDI Sequence received:            -> GetMidiBankMsb()= | GetMidiBankLsb()=
       ---------------------------------------------------------------------------
       program change                     ->        0          |        0
       bank LSB, program change           ->        0          |     LSB value
       bank MSB, program change           ->        0          |     MSB value
       bank LSB, bank MSB, program change ->     MSB value     |     LSB value
       bank MSB, bank LSB, program change ->     MSB value     |     LSB value
       ---------------------------------------------------------------------------

       That way we ensure those limited devices always to switch between the
       following set of MIDI instrument banks:  { 0, 1, 2, ..., 127 }
    */

    uint8_t EngineChannel::GetMidiProgram() {
        return p->uiMidiProgram; // AFAIK atomic on all systems
    }

    void EngineChannel::SetMidiProgram(uint8_t Program) {
        p->bProgramChangeReceived = true;
        p->uiMidiProgram = Program; // AFAIK atomic on all systems
    }

    uint8_t EngineChannel::GetMidiBankMsb() {
        return (p->bMidiBankMsbReceived && p->bMidiBankLsbReceived)
            ? p->uiMidiBankMsb : 0;
    }

    void EngineChannel::SetMidiBankMsb(uint8_t BankMSB) {
        if (p->bProgramChangeReceived) {
            p->bProgramChangeReceived =
            p->bMidiBankLsbReceived = false;
        }
        p->bMidiBankMsbReceived = true;
        p->uiMidiBankMsb = BankMSB; // AFAIK atomic on all systems
    }

    uint8_t EngineChannel::GetMidiBankLsb() {
        return (!p->bMidiBankMsbReceived && !p->bMidiBankLsbReceived)
                   ? 0
                   : (p->bMidiBankMsbReceived && !p->bMidiBankLsbReceived)
                         ? p->uiMidiBankMsb
                         : p->uiMidiBankLsb;
    }

    void EngineChannel::SetMidiBankLsb(uint8_t BankLSB) {
        if (p->bProgramChangeReceived) {
            p->bProgramChangeReceived =
            p->bMidiBankMsbReceived = false;
        }
        p->bMidiBankLsbReceived = true;
        p->uiMidiBankLsb = BankLSB; // AFAIK atomic on all systems
    }

    bool EngineChannel::UsesNoMidiInstrumentMap() {
        return (p->iMidiInstrumentMap == NO_MIDI_INSTRUMENT_MAP);
    }

    bool EngineChannel::UsesDefaultMidiInstrumentMap() {
        return (p->iMidiInstrumentMap == DEFAULT_MIDI_INSTRUMENT_MAP);
    }

    int EngineChannel::GetMidiInstrumentMap() throw (Exception) {
        if (UsesNoMidiInstrumentMap())
            throw Exception("EngineChannel is using no MIDI instrument map");
        if (UsesDefaultMidiInstrumentMap())
            throw Exception("EngineChannel is using default MIDI instrument map");
        // check if the stored map still exists in the MIDI instrument mapper
        std::vector<int> maps = MidiInstrumentMapper::Maps();
        if (find(maps.begin(), maps.end(), p->iMidiInstrumentMap) == maps.end()) {
            // it doesn't exist anymore, so fall back to NONE and throw an exception
            p->iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
            throw Exception("Assigned MIDI instrument map doesn't exist anymore, falling back to NONE");
        }
        return p->iMidiInstrumentMap;
    }

    void EngineChannel::SetMidiInstrumentMapToNone() {
        if (p->iMidiInstrumentMap == NO_MIDI_INSTRUMENT_MAP) return;
        p->iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
        StatusChanged(true);
    }

    void EngineChannel::SetMidiInstrumentMapToDefault() {
        if (p->iMidiInstrumentMap == DEFAULT_MIDI_INSTRUMENT_MAP) return;
        p->iMidiInstrumentMap = DEFAULT_MIDI_INSTRUMENT_MAP;
        StatusChanged(true);
    }

    void EngineChannel::SetMidiInstrumentMap(int MidiMap) throw (Exception) {
        if (p->iMidiInstrumentMap == MidiMap) return;

        // check if given map actually exists in the MIDI instrument mapper
        std::vector<int> maps = MidiInstrumentMapper::Maps();
        if (find(maps.begin(), maps.end(), MidiMap) == maps.end())
            throw Exception("MIDI instrument map doesn't exist");
        p->iMidiInstrumentMap = MidiMap; // assign the new map ID
        StatusChanged(true);
    }

    void EngineChannel::SetMidiRpnControllerMsb(uint8_t CtrlMSB) {
        p->uiMidiRpnMsb = CtrlMSB;
        p->bMidiRpnReceived = true;
    }

    void EngineChannel::SetMidiRpnControllerLsb(uint8_t CtrlLSB) {
        p->uiMidiRpnLsb = CtrlLSB;
        p->bMidiRpnReceived = true;
    }

    void EngineChannel::ResetMidiRpnController() {
        p->uiMidiRpnMsb = p->uiMidiRpnLsb = 0;
        p->bMidiRpnReceived = false;
    }

    int EngineChannel::GetMidiRpnController() {
        return (p->bMidiRpnReceived) ?
               (p->uiMidiRpnMsb << 8) | p->uiMidiRpnLsb : -1;
    }

    uint EngineChannel::GetVoiceCount() {
        return atomic_read(&p->voiceCount);
    }

    void EngineChannel::SetVoiceCount(uint Voices) {
        atomic_set(&p->voiceCount, Voices);
    }

    uint EngineChannel::GetDiskStreamCount() {
        return atomic_read(&p->diskStreamCount);
    }

    void EngineChannel::SetDiskStreamCount(uint Streams) {
        atomic_set(&p->diskStreamCount, Streams);
    }

    SamplerChannel* EngineChannel::GetSamplerChannel() {
        if (p->pSamplerChannel == NULL) {
            std::cerr << "EngineChannel::GetSamplerChannel(): pSamplerChannel is NULL, this is a bug!\n" << std::flush;
        }
        return p->pSamplerChannel;
    }

    void EngineChannel::SetSamplerChannel(SamplerChannel* pChannel) {
        p->pSamplerChannel = pChannel;
    }

    Sampler* EngineChannel::GetSampler() {
        if (GetSamplerChannel() == NULL) return NULL;
        return GetSamplerChannel()->GetSampler();
    }

    void EngineChannel::AddFxSendCountListener(FxSendCountListener* l) {
        p->llFxSendCountListeners.AddListener(l);
    }

    void EngineChannel::RemoveFxSendCountListener(FxSendCountListener* l) {
        p->llFxSendCountListeners.RemoveListener(l);
    }

    void EngineChannel::RemoveAllFxSendCountListeners() {
        p->llFxSendCountListeners.RemoveAllListeners();
    }

    void EngineChannel::fireFxSendCountChanged(int ChannelId, int NewCount) {
        for (int i = 0; i < p->llFxSendCountListeners.GetListenerCount(); i++) {
            p->llFxSendCountListeners.GetListener(i)->FxSendCountChanged(ChannelId, NewCount);
        }
    }

} // namespace LinuxSampler
