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

    struct _private_data_t {
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

    #define PTHIS ((_private_data_t*)pPrivateData)

    EngineChannel::EngineChannel() : pPrivateData(new _private_data_t) {
        PTHIS->iMute = 0;
        PTHIS->bSolo = false;
        PTHIS->uiMidiBankMsb = 0;
        PTHIS->uiMidiBankLsb = 0;
        PTHIS->uiMidiProgram = 0;
        PTHIS->bProgramChangeReceived =
        PTHIS->bMidiBankMsbReceived =
        PTHIS->bMidiBankLsbReceived = false;
        PTHIS->iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
        SetVoiceCount(0);
        SetDiskStreamCount(0);
        PTHIS->pSamplerChannel = NULL;
        ResetMidiRpnController();
    }

    EngineChannel::~EngineChannel() {
        if (PTHIS) delete PTHIS;
    }

    void EngineChannel::SetMute(int state) throw (Exception) {
        if (PTHIS->iMute == state) return;
        if (state < -1 || state > 1)
            throw Exception("Invalid Mute state: " + ToString(state));

        PTHIS->iMute = state;

        StatusChanged(true);
    }

    int EngineChannel::GetMute() {
        return PTHIS->iMute;
    }

    void EngineChannel::SetSolo(bool solo) {
        if (PTHIS->bSolo == solo) return;
        PTHIS->bSolo = solo;
        StatusChanged(true);
    }

    bool EngineChannel::GetSolo() {
        return PTHIS->bSolo;
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
        return PTHIS->uiMidiProgram; // AFAIK atomic on all systems
    }

    void EngineChannel::SetMidiProgram(uint8_t Program) {
        PTHIS->bProgramChangeReceived = true;
        PTHIS->uiMidiProgram = Program; // AFAIK atomic on all systems
    }

    uint8_t EngineChannel::GetMidiBankMsb() {
        return (PTHIS->bMidiBankMsbReceived && PTHIS->bMidiBankLsbReceived)
            ? PTHIS->uiMidiBankMsb : 0;
    }

    void EngineChannel::SetMidiBankMsb(uint8_t BankMSB) {
        if (PTHIS->bProgramChangeReceived) {
            PTHIS->bProgramChangeReceived =
            PTHIS->bMidiBankLsbReceived = false;
        }
        PTHIS->bMidiBankMsbReceived = true;
        PTHIS->uiMidiBankMsb = BankMSB; // AFAIK atomic on all systems
    }

    uint8_t EngineChannel::GetMidiBankLsb() {
        return (!PTHIS->bMidiBankMsbReceived && !PTHIS->bMidiBankLsbReceived)
                   ? 0
                   : (PTHIS->bMidiBankMsbReceived && !PTHIS->bMidiBankLsbReceived)
                         ? PTHIS->uiMidiBankMsb
                         : PTHIS->uiMidiBankLsb;
    }

    void EngineChannel::SetMidiBankLsb(uint8_t BankLSB) {
        if (PTHIS->bProgramChangeReceived) {
            PTHIS->bProgramChangeReceived =
            PTHIS->bMidiBankMsbReceived = false;
        }
        PTHIS->bMidiBankLsbReceived = true;
        PTHIS->uiMidiBankLsb = BankLSB; // AFAIK atomic on all systems
    }

    bool EngineChannel::UsesNoMidiInstrumentMap() {
        return (PTHIS->iMidiInstrumentMap == NO_MIDI_INSTRUMENT_MAP);
    }

    bool EngineChannel::UsesDefaultMidiInstrumentMap() {
        return (PTHIS->iMidiInstrumentMap == DEFAULT_MIDI_INSTRUMENT_MAP);
    }

    int EngineChannel::GetMidiInstrumentMap() throw (Exception) {
        if (UsesNoMidiInstrumentMap())
            throw Exception("EngineChannel is using no MIDI instrument map");
        if (UsesDefaultMidiInstrumentMap())
            throw Exception("EngineChannel is using default MIDI instrument map");
        // check if the stored map still exists in the MIDI instrument mapper
        std::vector<int> maps = MidiInstrumentMapper::Maps();
        if (find(maps.begin(), maps.end(), PTHIS->iMidiInstrumentMap) == maps.end()) {
            // it doesn't exist anymore, so fall back to NONE and throw an exception
            PTHIS->iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
            throw Exception("Assigned MIDI instrument map doesn't exist anymore, falling back to NONE");
        }
        return PTHIS->iMidiInstrumentMap;
    }

    void EngineChannel::SetMidiInstrumentMapToNone() {
        if (PTHIS->iMidiInstrumentMap == NO_MIDI_INSTRUMENT_MAP) return;
        PTHIS->iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
        StatusChanged(true);
    }

    void EngineChannel::SetMidiInstrumentMapToDefault() {
        if (PTHIS->iMidiInstrumentMap == DEFAULT_MIDI_INSTRUMENT_MAP) return;
        PTHIS->iMidiInstrumentMap = DEFAULT_MIDI_INSTRUMENT_MAP;
        StatusChanged(true);
    }

    void EngineChannel::SetMidiInstrumentMap(int MidiMap) throw (Exception) {
        if (PTHIS->iMidiInstrumentMap == MidiMap) return;

        // check if given map actually exists in the MIDI instrument mapper
        std::vector<int> maps = MidiInstrumentMapper::Maps();
        if (find(maps.begin(), maps.end(), MidiMap) == maps.end())
            throw Exception("MIDI instrument map doesn't exist");
        PTHIS->iMidiInstrumentMap = MidiMap; // assign the new map ID
        StatusChanged(true);
    }

    void EngineChannel::SetMidiRpnControllerMsb(uint8_t CtrlMSB) {
        PTHIS->uiMidiRpnMsb = CtrlMSB;
        PTHIS->bMidiRpnReceived = true;
    }

    void EngineChannel::SetMidiRpnControllerLsb(uint8_t CtrlLSB) {
        PTHIS->uiMidiRpnLsb = CtrlLSB;
        PTHIS->bMidiRpnReceived = true;
    }

    void EngineChannel::ResetMidiRpnController() {
        PTHIS->uiMidiRpnMsb = PTHIS->uiMidiRpnLsb = 0;
        PTHIS->bMidiRpnReceived = false;
    }

    int EngineChannel::GetMidiRpnController() {
        return (PTHIS->bMidiRpnReceived) ?
               (PTHIS->uiMidiRpnMsb << 8) | PTHIS->uiMidiRpnLsb : -1;
    }

    uint EngineChannel::GetVoiceCount() {
        return atomic_read(&PTHIS->voiceCount);
    }

    void EngineChannel::SetVoiceCount(uint Voices) {
        atomic_set(&PTHIS->voiceCount, Voices);
    }

    uint EngineChannel::GetDiskStreamCount() {
        return atomic_read(&PTHIS->diskStreamCount);
    }

    void EngineChannel::SetDiskStreamCount(uint Streams) {
        atomic_set(&PTHIS->diskStreamCount, Streams);
    }

    SamplerChannel* EngineChannel::GetSamplerChannel() {
        if (PTHIS->pSamplerChannel == NULL) {
            std::cerr << "EngineChannel::GetSamplerChannel(): pSamplerChannel is NULL, this is a bug!\n" << std::flush;
        }
        return PTHIS->pSamplerChannel;
    }

    void EngineChannel::SetSamplerChannel(SamplerChannel* pChannel) {
        PTHIS->pSamplerChannel = pChannel;
    }

    Sampler* EngineChannel::GetSampler() {
        if (GetSamplerChannel() == NULL) return NULL;
        return GetSamplerChannel()->GetSampler();
    }

    void EngineChannel::AddFxSendCountListener(FxSendCountListener* l) {
        PTHIS->llFxSendCountListeners.AddListener(l);
    }

    void EngineChannel::RemoveFxSendCountListener(FxSendCountListener* l) {
        PTHIS->llFxSendCountListeners.RemoveListener(l);
    }

    void EngineChannel::RemoveAllFxSendCountListeners() {
        PTHIS->llFxSendCountListeners.RemoveAllListeners();
    }

    void EngineChannel::fireFxSendCountChanged(int ChannelId, int NewCount) {
        for (int i = 0; i < PTHIS->llFxSendCountListeners.GetListenerCount(); i++) {
            PTHIS->llFxSendCountListeners.GetListener(i)->FxSendCountChanged(ChannelId, NewCount);
        }
    }

} // namespace LinuxSampler
