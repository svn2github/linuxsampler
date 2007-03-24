/*
 * Copyright (C) 2006, 2007 Andreas Persson
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with program; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#include "paramedit.h"

namespace {
    const char* const controlChangeTexts[] = {
        "none", "channelaftertouch", "velocity",
        0,
        "modwheel", // "Modulation Wheel or Lever",
        "breath", // "Breath Controller",
        0,
        "foot", // "Foot Controller",
        "portamentotime", // "Portamento Time",
        0, 0, 0, 0, 0, 0,
        "effect1", // "Effect Control 1",
        "effect2", // "Effect Control 2",
        0, 0,
        "genpurpose1", // "General Purpose Controller 1",
        "genpurpose2", // "General Purpose Controller 2",
        "genpurpose3", // "General Purpose Controller 3",
        "genpurpose4", // "General Purpose Controller 4",
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        "sustainpedal", // "Damper Pedal on/off (Sustain)",
        "portamento", // "Portamento On/Off",
        "sostenuto", // "Sustenuto On/Off",
        "softpedal", // "Soft Pedal On/Off",
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        "genpurpose5", // "General Purpose Controller 5",
        "genpurpose6", // "General Purpose Controller 6",
        "genpurpose7", // "General Purpose Controller 7",
        "genpurpose8", // "General Purpose Controller 8",
        0, 0, 0, 0, 0, 0, 0,
        "effect1depth", // "Effects 1 Depth",
        "effect2depth", // "Effects 2 Depth",
        "effect3depth", // "Effects 3 Depth",
        "effect4depth", // "Effects 4 Depth",
        "effect5depth", // "Effects 5 Depth"
    };
}

LabelWidget::LabelWidget(char* labelText, Gtk::Widget& widget) :
    label(Glib::ustring(labelText) + ":"),
    widget(widget)
{
    label.set_alignment(Gtk::ALIGN_LEFT);
}

void LabelWidget::set_sensitive(bool sensitive)
{
    label.set_sensitive(sensitive);
    widget.set_sensitive(sensitive);
}

NumEntryGain::NumEntryGain(char* labelText,
			   double lower = 0, double upper = 127,
			   int decimals = 0) :
    NumEntry<gig::DimensionRegion>(labelText, lower, upper, decimals)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryGain::value_changed));
}

void NumEntryGain::value_changed()
{
    if (dimreg && update_gui) {
      dimreg->Gain = int32_t(spinbutton.get_value() * -655360.0);
    }
}

void NumEntryGain::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    bool plus6 = dimreg->Gain < 0;
    set_value(plus6 ? 0 : dimreg->Gain / -655360.0);
    set_sensitive(!plus6);
    this->dimreg = dimreg;
}


BoolEntryPlus6::BoolEntryPlus6(char* labelText, NumEntryGain& eGain) :
    LabelWidget(labelText, checkbutton),
    eGain(eGain)
{
    checkbutton.signal_toggled().connect(
        sigc::mem_fun(*this, &BoolEntryPlus6::value_changed));
}

void BoolEntryPlus6::value_changed()
{
    if (dimreg && update_gui) {
        bool plus6 = checkbutton.get_active();
        if (plus6) {
            eGain.set_value(0);
            dimreg->Gain = 6 * -655360;
        } else {
            if (dimreg->Gain < 0) {
                dimreg->Gain = 0;
            }
        }
        eGain.set_sensitive(!plus6);
    }
}

void BoolEntryPlus6::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    checkbutton.set_active(dimreg->Gain < 0);
    this->dimreg = dimreg;
}

NumEntryPermille::NumEntryPermille(char* labelText,
                                   uint16_t gig::DimensionRegion::* param,
                                   double lower, double upper, int decimals) :
    NumEntry<gig::DimensionRegion>(labelText, lower, upper, decimals),
    param(param)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryPermille::value_changed));
}

void NumEntryPermille::value_changed()
{
    if (dimreg && update_gui) {
        dimreg->*param = uint16_t(spinbutton.get_value() * 10 + 0.5);
    }
}

void NumEntryPermille::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    set_value(dimreg->*param / 10.0);
    this->dimreg = dimreg;
}


NoteEntry::NoteEntry(char* labelText, uint8_t& (*access)(gig::DimensionRegion*)) :
    NumEntryX<uint8_t>(labelText, access)
{
    spinbutton.signal_input().connect(
        sigc::mem_fun(*this, &NoteEntry::on_input));
    spinbutton.signal_output().connect(
        sigc::mem_fun(*this, &NoteEntry::on_output));
}

const char* notes[] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};


// Convert the Entry text to a number
int NoteEntry::on_input(double* new_value)
{
    const char* str = spinbutton.get_text().c_str();

    int i;
    for (i = 11 ; i >= 0 ; i--) {
        if (strncmp(str, notes[i], strlen(notes[i])) == 0) break;
    }
    if (i >= 0) {
        char* endptr;
        long x = strtol(str + strlen(notes[i]), &endptr, 10);
        if (endptr != str + strlen(notes[i])) {
            *new_value = i + (x + 1) * 12;
            return true;
        }
    }
    return Gtk::INPUT_ERROR;
}

// Convert the Adjustment position to text
bool NoteEntry::on_output()
{
    int x = int(spinbutton.get_adjustment()->get_value());
    char buf[10];
    sprintf(buf, "%s%d", notes[x % 12], x / 12 - 1);
    spinbutton.set_text(buf);
    return true;
}

ChoiceEntryLeverageCtrl::ChoiceEntryLeverageCtrl(
    char* labelText,
    gig::leverage_ctrl_t gig::DimensionRegion::* param) :
    align(0, 0, 0, 0),
    LabelWidget(labelText, align),
    param(param)
{
    for (int i = 0 ; i < 99 ; i++) {
        if (controlChangeTexts[i]) {
            combobox.append_text(controlChangeTexts[i]);
        }
    }
    combobox.signal_changed().connect(
        sigc::mem_fun(*this, &ChoiceEntryLeverageCtrl::value_changed));
    align.add(combobox);
}

void ChoiceEntryLeverageCtrl::value_changed()
{
    if (dimreg && update_gui) {
        int rowno = combobox.get_active_row_number();
        switch (rowno)
        {
        case -1:
            break;
        case 0:
            (dimreg->*param).type = gig::leverage_ctrl_t::type_none;
            break;
        case 1:
            (dimreg->*param).type =
                gig::leverage_ctrl_t::type_channelaftertouch;
            break;
        case 2:
            (dimreg->*param).type = gig::leverage_ctrl_t::type_velocity;
            break;
        default:
            (dimreg->*param).type = gig::leverage_ctrl_t::type_controlchange;
            int x = 3;
            for (int cc = 0 ; cc < 96 ; cc++) {
                if (controlChangeTexts[cc + 3]) {
                    if (rowno == x) {
                        (dimreg->*param).controller_number = cc;
                        break;
                    }
                    x++;
                }
            }
            break;
        }
    }
}

void ChoiceEntryLeverageCtrl::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    gig::leverage_ctrl_t c = dimreg->*param;
    int x;
    switch (c.type)
    {
    case gig::leverage_ctrl_t::type_none:
        x = 0;
        break;
    case gig::leverage_ctrl_t::type_channelaftertouch:
        x = 1;
        break;
    case gig::leverage_ctrl_t::type_velocity:
        x = 2;
        break;
    case gig::leverage_ctrl_t::type_controlchange:
        x = -1;
        for (int cc = 0 ; cc < 96 ; cc++) {
            if (controlChangeTexts[cc + 3]) {
                x++;
                if (c.controller_number == cc) {
                    x += 3;
                    break;
                }
            }
        }
        break;
    default:
        x = -1;
        break;
    }
    combobox.set_active(x);
    this->dimreg = dimreg;
}
