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

#include "MidiInputDevice.h"

namespace LinuxSampler {

    MidiInputDevice::MidiInputDevice(type_t Type) {
        MidiInputType = Type;
    }

    void MidiInputDevice::DispatchNoteOn(uint8_t Key, uint8_t Velocity, uint MidiChannel) {
        std::set<Engine*>::iterator engineiter = MidiChannelMap[MidiChannel].begin();
        std::set<Engine*>::iterator end        = MidiChannelMap[MidiChannel].end();
        for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOn(Key, Velocity);
    }

    void MidiInputDevice::DispatchNoteOff(uint8_t Key, uint8_t Velocity, uint MidiChannel) {
        std::set<Engine*>::iterator engineiter = MidiChannelMap[MidiChannel].begin();
        std::set<Engine*>::iterator end        = MidiChannelMap[MidiChannel].end();
        for (; engineiter != end; engineiter++) (*engineiter)->SendNoteOff(Key, Velocity);
    }

    void MidiInputDevice::DispatchPitchbend(int Pitch, uint MidiChannel) {
        std::set<Engine*>::iterator engineiter = MidiChannelMap[MidiChannel].begin();
        std::set<Engine*>::iterator end        = MidiChannelMap[MidiChannel].end();
        for (; engineiter != end; engineiter++) (*engineiter)->SendPitchbend(Pitch);
    }

    void MidiInputDevice::DispatchControlChange(uint8_t Controller, uint8_t Value, uint MidiChannel) {
        std::set<Engine*>::iterator engineiter = MidiChannelMap[MidiChannel].begin();
        std::set<Engine*>::iterator end        = MidiChannelMap[MidiChannel].end();
        for (; engineiter != end; engineiter++) (*engineiter)->SendControlChange(Controller, Value);
    }

    void MidiInputDevice::Connect(Engine* pEngine, midi_chan_t MidiChannel) {
        if (MidiChannel < 0 || MidiChannel > 16)
            throw MidiInputException("MIDI channel index out of bounds");
        Disconnect(pEngine);
        MidiChannelMap[MidiChannel].insert(pEngine);
    }

    void MidiInputDevice::Disconnect(Engine* pEngine) {
        try { for (int i = 0; i <= 16; i++) MidiChannelMap[i].erase(pEngine); }
        catch(...) { /* NOOP */ }
    }

    MidiInputDevice::type_t MidiInputDevice::Type() {
        return MidiInputType;
    }

} // namespace LinuxSampler
