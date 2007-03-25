/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#include "EngineChannel.h"

#include <algorithm>

#include "../drivers/midi/MidiInstrumentMapper.h"

#define NO_MIDI_INSTRUMENT_MAP		-1
#define DEFAULT_MIDI_INSTRUMENT_MAP	-2

namespace LinuxSampler {

    EngineChannel::EngineChannel() {
        iMute = 0;
        bSolo = false;
        uiMidiBankMsb = 0;
        uiMidiBankLsb = 0;
        uiMidiProgram = 0;
        bProgramChangeReceived = bMidiBankMsbReceived = bMidiBankLsbReceived = false;
        iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
        ResetMidiRpnController();
    }

    void EngineChannel::SetMute(int state) throw (Exception) {
        if(iMute == state) return;
        if(state < -1 || state > 1)
            throw Exception("Invalid Mute state: " + ToString(state));

        iMute = state;

        StatusChanged(true);
    }

    int EngineChannel::GetMute() {
        return iMute;
    }

    void EngineChannel::SetSolo(bool solo) {
        if(bSolo == solo) return;
        bSolo = solo;
        StatusChanged(true);
    }

    bool EngineChannel::GetSolo() {
        return bSolo;
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
        return uiMidiProgram; // AFAIK atomic on all systems
    }

    void EngineChannel::SetMidiProgram(uint8_t Program) {
        bProgramChangeReceived = true;
        uiMidiProgram = Program; // AFAIK atomic on all systems
    }

    uint8_t EngineChannel::GetMidiBankMsb() {
        return (bMidiBankMsbReceived && bMidiBankLsbReceived) ? uiMidiBankMsb : 0;
    }

    void EngineChannel::SetMidiBankMsb(uint8_t BankMSB) {
        if (bProgramChangeReceived)
            bProgramChangeReceived = bMidiBankLsbReceived = false;
        bMidiBankMsbReceived = true;
        uiMidiBankMsb = BankMSB; // AFAIK atomic on all systems
    }

    uint8_t EngineChannel::GetMidiBankLsb() {
        return (!bMidiBankMsbReceived && !bMidiBankLsbReceived)
                   ? 0
                   : (bMidiBankMsbReceived && !bMidiBankLsbReceived)
                         ? uiMidiBankMsb
                         : uiMidiBankLsb;
    }

    void EngineChannel::SetMidiBankLsb(uint8_t BankLSB) {
        if (bProgramChangeReceived)
            bProgramChangeReceived = bMidiBankMsbReceived = false;
        bMidiBankLsbReceived = true;
        uiMidiBankLsb = BankLSB; // AFAIK atomic on all systems
    }

    bool EngineChannel::UsesNoMidiInstrumentMap() {
        return (iMidiInstrumentMap == NO_MIDI_INSTRUMENT_MAP);
    }

    bool EngineChannel::UsesDefaultMidiInstrumentMap() {
        return (iMidiInstrumentMap == DEFAULT_MIDI_INSTRUMENT_MAP);
    }

    int EngineChannel::GetMidiInstrumentMap() throw (Exception) {
        if (UsesNoMidiInstrumentMap())
            throw Exception("EngineChannel is using no MIDI instrument map");
        if (UsesDefaultMidiInstrumentMap())
            throw Exception("EngineChannel is using default MIDI instrument map");
        // check if the stored map still exists in the MIDI instrument mapper
        std::vector<int> maps = MidiInstrumentMapper::Maps();
        if (find(maps.begin(), maps.end(), iMidiInstrumentMap) == maps.end()) {
            // it doesn't exist anymore, so fall back to NONE and throw an exception
            iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
            throw Exception("Assigned MIDI instrument map doesn't exist anymore, falling back to NONE");
        }
        return iMidiInstrumentMap;
    }

    void EngineChannel::SetMidiInstrumentMapToNone() {
        iMidiInstrumentMap = NO_MIDI_INSTRUMENT_MAP;
    }

    void EngineChannel::SetMidiInstrumentMapToDefault() {
        iMidiInstrumentMap = DEFAULT_MIDI_INSTRUMENT_MAP;
    }

    void EngineChannel::SetMidiInstrumentMap(int MidiMap) throw (Exception) {
        // check if given map actually exists in the MIDI instrument mapper
        std::vector<int> maps = MidiInstrumentMapper::Maps();
        if (find(maps.begin(), maps.end(), MidiMap) == maps.end())
            throw Exception("MIDI instrument map doesn't exist");
        iMidiInstrumentMap = MidiMap; // assign the new map ID
    }

    void EngineChannel::SetMidiRpnControllerMsb(uint8_t CtrlMSB) {
        uiMidiRpnMsb = CtrlMSB;
        bMidiRpnReceived = true;
    }

    void EngineChannel::SetMidiRpnControllerLsb(uint8_t CtrlLSB) {
        uiMidiRpnLsb = CtrlLSB;
        bMidiRpnReceived = true;
    }

    void EngineChannel::ResetMidiRpnController() {
        uiMidiRpnMsb = uiMidiRpnLsb = 0;
        bMidiRpnReceived = false;
    }

    int EngineChannel::GetMidiRpnController() {
        return (bMidiRpnReceived) ? (uiMidiRpnMsb << 8) | uiMidiRpnLsb : -1;
    }

    void EngineChannel::AddFxSendCountListener(FxSendCountListener* l) {
        llFxSendCountListeners.AddListener(l);
    }

    void EngineChannel::RemoveFxSendCountListener(FxSendCountListener* l) {
        llFxSendCountListeners.RemoveListener(l);
    }

    void EngineChannel::RemoveAllFxSendCountListeners() {
        llFxSendCountListeners.RemoveAllListeners();
    }

    void EngineChannel::fireFxSendCountChanged(int ChannelId, int NewCount) {
        for (int i = 0; i < llFxSendCountListeners.GetListenerCount(); i++) {
            llFxSendCountListeners.GetListener(i)->FxSendCountChanged(ChannelId, NewCount);
        }
    }

} // namespace LinuxSampler
