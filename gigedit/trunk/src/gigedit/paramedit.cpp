/*
 * Copyright (C) 2006-2014 Andreas Persson
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

#include <cstring>

#include "paramedit.h"

#include "global.h"
#include "compat.h"
#include "Settings.h"

#include <gtkmm/messagedialog.h>

std::string gig_encoding("CP1252");

Glib::ustring gig_to_utf8(const gig::String& gig_string) {
    return Glib::convert_with_fallback(gig_string, "UTF-8", gig_encoding, "?");
}

gig::String gig_from_utf8(const Glib::ustring& utf8_string) {
    return Glib::convert_with_fallback(utf8_string, gig_encoding, "UTF-8", "?");
}


namespace {
    struct CCText {
        const char* const txt;
        bool isExtension; ///< True if this is a controller only supported by LinuxSampler, but not supperted by Gigasampler/GigaStudio.
    };
    static const CCText controlChangeTexts[] = {
        // 3 special ones (not being CCs)
        { _("none") }, { _("channelaftertouch") }, { _("velocity") },
        {0}, // bank select MSB (hard coded in sampler, so discouraged to be used here, even though considerable)
        { _("modwheel") }, // "Modulation Wheel or Lever",
        { _("breath") }, // "Breath Controller",
        { _("undefined"), true },
        { _("foot") }, // "Foot Controller",
        { _("portamentotime") }, // "Portamento Time",
        { _("data entry MSB"), true },
        { _("volume"), true },
        { _("balance"), true },
        { _("undefined"), true },
        { _("pan"), true },
        { _("expression"), true },
        { _("effect1") }, // "Effect Control 1",
        { _("effect2") }, // "Effect Control 2",
        { _("undefined"), true },
        { _("undefined"), true },
        { _("genpurpose1") }, // "General Purpose Controller 1",
        { _("genpurpose2") }, // "General Purpose Controller 2",
        { _("genpurpose3") }, // "General Purpose Controller 3",
        { _("genpurpose4") }, // "General Purpose Controller 4",
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        
        // LSB variant of the various controllers above
        // (so discouraged to be used here for now)
        {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
        {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
        {0}, {0}, {0}, {0},
        
        { _("sustainpedal") }, // "Damper Pedal on/off (Sustain)",
        { _("portamento") }, // "Portamento On/Off",
        { _("sostenuto") }, // "Sustenuto On/Off",
        { _("softpedal") }, // "Soft Pedal On/Off",
        { _("legato"), true },
        { _("hold2"), true },
        { _("soundvariation"), true },
        { _("timbre"), true },
        { _("releasetime"), true },
        { _("attacktime"), true },
        { _("brightness"), true },
        { _("decaytime"), true },
        { _("vibratorate"), true },
        { _("vibratodepth"), true },
        { _("vibratodelay"), true },
        { _("undefined"), true },
        { _("genpurpose5") }, // "General Purpose Controller 5",
        { _("genpurpose6") }, // "General Purpose Controller 6",
        { _("genpurpose7") }, // "General Purpose Controller 7",
        { _("genpurpose8") }, // "General Purpose Controller 8",
        { _("portamentoctrl"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        {0}, // high resolution velocity prefix (so discouraged to be used here)
        { _("undefined"), true },
        { _("undefined"), true },
        { _("effect1depth") }, // "Effects 1 Depth",
        { _("effect2depth") }, // "Effects 2 Depth",
        { _("effect3depth") }, // "Effects 3 Depth",
        { _("effect4depth") }, // "Effects 4 Depth",
        { _("effect5depth") }, // "Effects 5 Depth"
        { _("dataincrement"), true },
        { _("datadecrement"), true },
        {0}, // NRPN LSB (so discouraged to be used here)
        {0}, // NRPN MSB (so discouraged to be used here)
        {0}, // RPN LSB (so discouraged to be used here)
        {0}, // RPN MSB (so discouraged to be used here)
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true },
        { _("undefined"), true } // CC 119
        // (all other ones that follow [CC 120- CC 127] are hard coded channel
        // mode messages, so those are discouraged to be used here)
    };
}

#define controlChangeTextsSize  (sizeof(controlChangeTexts) / sizeof(CCText))

LabelWidget::LabelWidget(const char* labelText, Gtk::Widget& widget) :
    label(Glib::ustring(labelText) + ":"),
    widget(widget)
{
    label.set_alignment(Gtk::ALIGN_START);
}

void LabelWidget::set_sensitive(bool sensitive)
{
    label.set_sensitive(sensitive);
    widget.set_sensitive(sensitive);
}

NumEntry::NumEntry(const char* labelText, double lower, double upper,
                   int decimals) :
    LabelWidget(labelText, box),
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    adjust(lower, lower, upper, 1, 10),
#else
    adjust(Gtk::Adjustment::create(lower, lower, upper, 1, 10)),
#endif
    scale(adjust),
    spinbutton(adjust)
{
    scale.set_size_request(70);
    spinbutton.set_digits(decimals);
    spinbutton.set_value(0);
    spinbutton.set_numeric();
    scale.set_draw_value(false);
    box.pack_start(spinbutton, Gtk::PACK_SHRINK);
    box.add(scale);
}

NumEntryGain::NumEntryGain(const char* labelText,
			   double lower, double upper,
			   int decimals, double coeff) :
    NumEntry(labelText, lower, upper, decimals),
    value(0),
    coeff(coeff),
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
    spin_button_show_notes(spinbutton);
}

namespace {
    const char* notes[] = {
        _("C"), _("C#"), _("D"), _("D#"), _("E"), _("F"),_("F#"),
        _("G"), _("G#"), _("A"), _("A#"), _("B")
    };

    int note_value(const Glib::ustring& note, double* value)
    {
        const char* str = note.c_str();

        int i;
        for (i = 11 ; i >= 0 ; i--) {
            if (strncasecmp(str, notes[i], strlen(notes[i])) == 0) break;
        }
        if (i >= 0) {
            char* endptr;
            long x = strtol(str + strlen(notes[i]), &endptr, 10);
            if (endptr != str + strlen(notes[i])) {
                *value = std::max(0L, std::min(i + (x + 1) * 12, 127L));
                return true;
            }
        } else {
            char* endptr;
            long x = strtol(str, &endptr, 10);
            if (endptr != str) {
                *value = std::max(0L, std::min(x, 127L));
                return true;
            }
        }
        return Gtk::INPUT_ERROR;
    }
}

int note_value(const Glib::ustring& note)
{
    double value = 0;
    note_value(note, &value);
    return value;
}

Glib::ustring note_str(int note)
{
    char buf[10];
    sprintf(buf, "%s%d", notes[note % 12], note / 12 - 1);
    return buf;
}

namespace {
    // Convert the Entry text to a number
    int on_input(double* new_value, Gtk::SpinButton* spinbutton) {
        return note_value(spinbutton->get_text(), new_value);
    }

    // Convert the Adjustment position to text
    bool on_output(Gtk::SpinButton* spinbutton) {
        spinbutton->set_text(
            note_str(spinbutton->get_adjustment()->get_value() + 0.5));
        return true;
    }
}

// Make a SpinButton show notes instead of numbers
void spin_button_show_notes(Gtk::SpinButton& spin_button)
{
    spin_button.set_numeric(false);
    spin_button.set_width_chars(4);
    spin_button.signal_input().connect(
        sigc::bind(sigc::ptr_fun(&on_input), &spin_button));
    spin_button.signal_output().connect(
        sigc::bind(sigc::ptr_fun(&on_output), &spin_button));
}

ChoiceEntryLeverageCtrl::ChoiceEntryLeverageCtrl(const char* labelText) :
    LabelWidget(labelText, align),
    align(0, 0, 0, 0)
{
    for (int i = 0 ; i < controlChangeTextsSize ; i++) {
        if (controlChangeTexts[i].txt) {
            const int cc = i - 3;
            Glib::ustring s = (i < 3)
                ? controlChangeTexts[i].txt
                : Glib::ustring::compose("CC%1: %2%3", cc, controlChangeTexts[i].txt, controlChangeTexts[i].isExtension ? " [EXT]" : "");
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 24) || GTKMM_MAJOR_VERSION < 2
            combobox.append_text(s);
#else
            combobox.append(s);
#endif
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
        for (uint cc = 0 ; cc < controlChangeTextsSize - 3 ; cc++) {
            if (controlChangeTexts[cc + 3].txt) {
                if (rowno == x) {
                    value.controller_number = cc;
                    if (controlChangeTexts[cc + 3].isExtension &&
                        Settings::singleton()->warnUserOnExtensions)
                    {
                        Glib::ustring txt = _("<b>Format Extension</b>\n\nAll controllers marked with \"<b>[EXT]</b>\" are an extension to the original gig sound format. They will only work with LinuxSampler, but they will <b>not work</b> with Gigasampler/GigaStudio!\n\n(You may disable this warning in the <i>Settings</i> menu.)");
                        Gtk::MessageDialog msg(
                            txt, true, Gtk::MESSAGE_WARNING
                        );
                        msg.run();
                    }
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
    int comboIndex;
    switch (value.type)
    {
    case gig::leverage_ctrl_t::type_none:
        comboIndex = 0;
        break;
    case gig::leverage_ctrl_t::type_channelaftertouch:
        comboIndex = 1;
        break;
    case gig::leverage_ctrl_t::type_velocity:
        comboIndex = 2;
        break;
    case gig::leverage_ctrl_t::type_controlchange: {
        comboIndex = -1;
        int x = 3;
        for (uint cc = 0 ; cc < controlChangeTextsSize - 3 ; cc++) {
            if (controlChangeTexts[cc + 3].txt) {
                if (value.controller_number == cc) {
                    comboIndex = x;
                    break;
                }
                x++;
            }
        }
        break;
    }
    default:
        comboIndex = -1;
        break;
    }
    combobox.set_active(comboIndex);
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
    entry.signal_changed().connect(sig_changed.make_slot());
}

gig::String StringEntry::get_value() const
{
    return gig_from_utf8(entry.get_text());
}

void StringEntry::set_value(const gig::String& value) {
    entry.set_text(gig_to_utf8(value));
}


StringEntryMultiLine::StringEntryMultiLine(const char* labelText) :
    LabelWidget(labelText, frame)
{
    text_buffer = text_view.get_buffer();
    frame.set_shadow_type(Gtk::SHADOW_IN);
    frame.add(text_view);
    text_buffer->signal_changed().connect(sig_changed.make_slot());
}

gig::String StringEntryMultiLine::get_value() const
{
    Glib::ustring value = text_buffer->get_text();
    for (int i = 0 ; (i = value.find("\x0a", i)) >= 0 ; i += 2)
        value.replace(i, 1, "\x0d\x0a");
    return gig_from_utf8(value);
}

void StringEntryMultiLine::set_value(const gig::String& value)
{
    Glib::ustring text = gig_to_utf8(value);
    for (int i = 0 ; (i = text.find("\x0d\x0a", i, 2)) >= 0 ; i++)
        text.replace(i, 2, "\x0a");
    text_buffer->set_text(text);
}


Table::Table(int x, int y) : Gtk::Table(x, y), rowno(0) {  }

void Table::add(BoolEntry& boolentry)
{
    attach(boolentry.widget, 0, 2, rowno, rowno + 1,
           Gtk::FILL, Gtk::SHRINK);
    rowno++;
}

void Table::add(BoolEntryPlus6& boolentry)
{
    attach(boolentry.widget, 0, 2, rowno, rowno + 1,
           Gtk::FILL, Gtk::SHRINK);
    rowno++;
}

void Table::add(LabelWidget& prop)
{
    attach(prop.label, 1, 2, rowno, rowno + 1,
           Gtk::FILL, Gtk::SHRINK);
    attach(prop.widget, 2, 3, rowno, rowno + 1,
           Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);
    rowno++;
}
