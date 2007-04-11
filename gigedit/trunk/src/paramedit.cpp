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

bool update_gui;

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

NumEntry::NumEntry(char* labelText, double lower, double upper,
                   int decimals) :
    adjust(lower, lower, upper, 1, 10),
    scale(adjust),
    spinbutton(adjust),
    LabelWidget(labelText, box)
{
    spinbutton.set_digits(decimals);
    scale.set_draw_value(false);
    box.pack_start(spinbutton, Gtk::PACK_SHRINK);
    box.add(scale);
}

NumEntryGain::NumEntryGain(char* labelText,
			   double lower, double upper,
			   int decimals, double coeff) :
    NumEntry(labelText, lower, upper, decimals),
    coeff(coeff)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryGain::value_changed));
}

void NumEntryGain::value_changed()
{
    if (ptr && update_gui) {
        *ptr = int32_t(spinbutton.get_value() * coeff);
    }
}

void NumEntryGain::set_ptr(int32_t* ptr)
{
    this->ptr = 0;
    bool plus6 = *ptr < 0;
    set_value(plus6 ? 0 : *ptr / coeff);
    set_sensitive(!plus6);
    this->ptr = ptr;
}


BoolEntryPlus6::BoolEntryPlus6(char* labelText, NumEntryGain& eGain, int32_t plus6value) :
    LabelWidget(labelText, checkbutton),
    eGain(eGain),
    plus6value(plus6value)
{
    checkbutton.signal_toggled().connect(
        sigc::mem_fun(*this, &BoolEntryPlus6::value_changed));
}

void BoolEntryPlus6::value_changed()
{
    if (ptr && update_gui) {
        bool plus6 = checkbutton.get_active();
        if (plus6) {
            eGain.set_value(0);
            *ptr = plus6value;
        } else {
            if (*ptr < 0) {
                *ptr = 0;
            }
        }
        eGain.set_sensitive(!plus6);
    }
}

void BoolEntryPlus6::set_ptr(int32_t* ptr)
{
    this->ptr = 0;
    checkbutton.set_active(*ptr < 0);
    this->ptr = ptr;
}

NumEntryPermille::NumEntryPermille(char* labelText,
                                   double lower, double upper, int decimals) :
    NumEntry(labelText, lower, upper, decimals)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryPermille::value_changed));
}

void NumEntryPermille::value_changed()
{
    if (ptr && update_gui) {
        *ptr = uint16_t(spinbutton.get_value() * 10 + 0.5);
    }
}

void NumEntryPermille::set_ptr(uint16_t* ptr)
{
    this->ptr = 0;
    set_value(*ptr / 10.0);
    this->ptr = ptr;
}


NoteEntry::NoteEntry(char* labelText) :
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
    int x = int(spinbutton.get_adjustment()->get_value());
    char buf[10];
    sprintf(buf, "%s%d", notes[x % 12], x / 12 - 1);
    spinbutton.set_text(buf);
    return true;
}

ChoiceEntryLeverageCtrl::ChoiceEntryLeverageCtrl(char* labelText) :
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
}

void ChoiceEntryLeverageCtrl::value_changed()
{
    if (ptr && update_gui) {
        int rowno = combobox.get_active_row_number();
        switch (rowno)
        {
        case -1:
            break;
        case 0:
            ptr->type = gig::leverage_ctrl_t::type_none;
            break;
        case 1:
            ptr->type = gig::leverage_ctrl_t::type_channelaftertouch;
            break;
        case 2:
            ptr->type = gig::leverage_ctrl_t::type_velocity;
            break;
        default:
            ptr->type = gig::leverage_ctrl_t::type_controlchange;
            int x = 3;
            for (int cc = 0 ; cc < 96 ; cc++) {
                if (controlChangeTexts[cc + 3]) {
                    if (rowno == x) {
                        ptr->controller_number = cc;
                        break;
                    }
                    x++;
                }
            }
            break;
        }
    }
}

void ChoiceEntryLeverageCtrl::set_ptr(gig::leverage_ctrl_t* ptr)
{
    this->ptr = 0;
    int x;
    switch (ptr->type)
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
                if (ptr->controller_number == cc) {
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
    this->ptr = ptr;
}


BoolEntry::BoolEntry(char* labelText) :
    LabelWidget(labelText, checkbutton), ptr(NULL)
{
    checkbutton.signal_toggled().connect(
        sigc::mem_fun(*this, &BoolEntry::value_changed));
}

void BoolEntry::value_changed()
{
    if (ptr && update_gui) {
        *ptr = checkbutton.get_active();
    }
}

void BoolEntry::set_ptr(bool* ptr)
{
    this->ptr = 0;
    checkbutton.set_active(*ptr);
    this->ptr = ptr;
}


StringEntry::StringEntry(char* labelText) :
    LabelWidget(labelText, entry)
{
    entry.signal_changed().connect(
        sigc::mem_fun(*this, &StringEntry::value_changed));
}

void StringEntry::value_changed()
{
    if (ptr && update_gui) {
        *ptr = entry.get_text();
    }
}

void StringEntry::set_ptr(gig::String* ptr)
{
    this->ptr = 0;
    entry.set_text(*ptr);
    this->ptr = ptr;
}
