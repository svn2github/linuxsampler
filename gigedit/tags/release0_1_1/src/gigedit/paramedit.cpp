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

LabelWidget::LabelWidget(const char* labelText, Gtk::Widget& widget) :
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

NumEntry::NumEntry(const char* labelText, double lower, double upper,
                   int decimals) :
    adjust(lower, lower, upper, 1, 10),
    scale(adjust),
    spinbutton(adjust),
    LabelWidget(labelText, box)
{
    spinbutton.set_digits(decimals);
    spinbutton.set_value(0);
    scale.set_draw_value(false);
    box.pack_start(spinbutton, Gtk::PACK_SHRINK);
    box.add(scale);
}

NumEntryGain::NumEntryGain(const char* labelText,
			   double lower, double upper,
			   int decimals, double coeff) :
    NumEntry(labelText, lower, upper, decimals),
    coeff(coeff),
    value(0),
    connected(true)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryGain::value_changed));
}

void NumEntryGain::value_changed()
{
    if (!connected) return;

    const double f = pow(10, spinbutton.get_digits());
    int new_value = round_to_int(spinbutton.get_value() * f);
    if (new_value != round_to_int(value / coeff * f)) {
        value = round_to_int(new_value / f * coeff);
        sig_changed();
    }
}

void NumEntryGain::set_value(int32_t value)
{
    if (value != this->value) {
        this->value = value;

        connected = false;
        bool plus6 = value < 0;
        spinbutton.set_value(plus6 ? 0 : value / coeff);
        set_sensitive(!plus6);
        connected = true;

        sig_changed();
    }
}


BoolEntryPlus6::BoolEntryPlus6(const char* labelText, NumEntryGain& eGain, int32_t plus6value) :
    LabelWidget(labelText, checkbutton),
    checkbutton(labelText),
    eGain(eGain),
    plus6value(plus6value)
{
    checkbutton.signal_toggled().connect(
        sigc::mem_fun(*this, &BoolEntryPlus6::value_changed));
}

void BoolEntryPlus6::value_changed()
{
    if (checkbutton.get_active()) eGain.set_value(plus6value);
    else if (eGain.get_value() < 0) eGain.set_value(0);
}

int32_t BoolEntryPlus6::get_value() const
{
    return eGain.get_value();
}

void BoolEntryPlus6::set_value(int32_t value)
{
    checkbutton.set_active(value < 0);
}

NumEntryPermille::NumEntryPermille(const char* labelText,
                                   double lower, double upper, int decimals) :
    NumEntry(labelText, lower, upper, decimals),
    value(0)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryPermille::value_changed));
}

void NumEntryPermille::value_changed()
{
    uint16_t new_value = uint16_t(spinbutton.get_value() * 10 + 0.5);
    if (new_value != value) {
        value = uint16_t(spinbutton.get_value() * 10 + 0.5);
        sig_changed();
    }
}

void NumEntryPermille::set_value(uint16_t value)
{
    if (value != this->value) {
        spinbutton.set_value(value / 10.0);
    }
}


NoteEntry::NoteEntry(const char* labelText) :
    NumEntryTemp<uint8_t>(labelText)
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
    int x = int(spinbutton.get_adjustment()->get_value() + 0.5);
    char buf[10];
    sprintf(buf, "%s%d", notes[x % 12], x / 12 - 1);
    spinbutton.set_text(buf);
    return true;
}

ChoiceEntryLeverageCtrl::ChoiceEntryLeverageCtrl(const char* labelText) :
    align(0, 0, 0, 0),
    LabelWidget(labelText, align)
{
    for (int i = 0 ; i < 99 ; i++) {
        if (controlChangeTexts[i]) {
            combobox.append_text(controlChangeTexts[i]);
        }
    }
    combobox.signal_changed().connect(
        sigc::mem_fun(*this, &ChoiceEntryLeverageCtrl::value_changed));
    align.add(combobox);
    value.type = gig::leverage_ctrl_t::type_none;
    value.controller_number = 0;
}

void ChoiceEntryLeverageCtrl::value_changed()
{
    int rowno = combobox.get_active_row_number();
    switch (rowno)
    {
    case -1:
        break;
    case 0:
        value.type = gig::leverage_ctrl_t::type_none;
        break;
    case 1:
        value.type = gig::leverage_ctrl_t::type_channelaftertouch;
        break;
    case 2:
        value.type = gig::leverage_ctrl_t::type_velocity;
        break;
    default:
        value.type = gig::leverage_ctrl_t::type_controlchange;
        int x = 3;
        for (int cc = 0 ; cc < 96 ; cc++) {
            if (controlChangeTexts[cc + 3]) {
                if (rowno == x) {
                    value.controller_number = cc;
                    break;
                }
                x++;
            }
        }
        break;
    }
    if (rowno >= 0) sig_changed();
}

void ChoiceEntryLeverageCtrl::set_value(gig::leverage_ctrl_t value)
{
    int x;
    switch (value.type)
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
                if (value.controller_number == cc) {
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
}


BoolEntry::BoolEntry(const char* labelText) :
    LabelWidget(labelText, checkbutton),
    checkbutton(labelText)
{
    checkbutton.signal_toggled().connect(sig_changed.make_slot());
}


StringEntry::StringEntry(const char* labelText) :
    LabelWidget(labelText, entry)
{
    entry.signal_changed().connect(
        sigc::mem_fun(*this, &StringEntry::value_changed));
}

void StringEntry::value_changed()
{
    if (ptr) {
        *ptr = entry.get_text();
        sig_changed();
    }
}

void StringEntry::set_ptr(gig::String* ptr)
{
    this->ptr = 0;
    entry.set_text(*ptr);
    this->ptr = ptr;
}
