/*                                                         -*- c++ -*-
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

#ifndef GIGEDIT_PARAMEDIT_H
#define GIGEDIT_PARAMEDIT_H

#include <gig.h>

#include <math.h>

#include <gtkmm/adjustment.h>
#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/scale.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/tooltips.h>

class LabelWidget {
public:
    Gtk::Label label;
    Gtk::Widget& widget;

    LabelWidget(const char* labelText, Gtk::Widget& widget);
    void set_sensitive(bool sensitive = true);
    sigc::signal<void>& signal_value_changed() {
        return sig_changed;
    }
protected:
    Gtk::Tooltips tooltips;
    sigc::signal<void> sig_changed;
};

class NumEntry : public LabelWidget {
protected:
    Gtk::Adjustment adjust;
    Gtk::HScale scale;
    Gtk::SpinButton spinbutton;
    Gtk::HBox box;

    int round_to_int(double x) {
        return int(x < 0.0 ? x - 0.5 : x + 0.5);
    }
public:
    NumEntry(const char* labelText, double lower = 0, double upper = 127,
             int decimals = 0);
    void set_tip(const Glib::ustring& tip_text) {
        tooltips.set_tip(spinbutton, tip_text);
    }
    void set_upper(double upper) {
        adjust.set_upper(upper);
    }
};

class NumEntryGain : public NumEntry {
private:
    int32_t value;
    void value_changed();
    double coeff;
    bool connected;
public:
    NumEntryGain(const char* labelText,
                 double lower, double upper, int decimals, double coeff);
    int32_t get_value() const { return value; }
    void set_value(int32_t value);
};

template<typename T>
class NumEntryTemp : public NumEntry {
private:
    T value;
    void value_changed();
public:
    NumEntryTemp(const char* labelText,
                 double lower = 0, double upper = 127, int decimals = 0);
    T get_value() const { return value; }
    void set_value(T value);
};

template<typename T>
NumEntryTemp<T>::NumEntryTemp(const char* labelText,
                              double lower, double upper, int decimals) :
    NumEntry(labelText, lower, upper, decimals),
    value(0)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryTemp::value_changed));
}

template<typename T>
void NumEntryTemp<T>::value_changed()
{
    const double f = pow(10, spinbutton.get_digits());
    int new_value = round_to_int(spinbutton.get_value() * f);
    if (new_value != round_to_int(value * f)) {
        value = T(new_value / f);
        sig_changed();
    }
}

template<typename T>
void NumEntryTemp<T>::set_value(T value)
{
    if (value > adjust.get_upper()) value = T(adjust.get_upper());
    if (this->value != value) {
        this->value = value;
        const double f = pow(10, spinbutton.get_digits());
        if (round_to_int(spinbutton.get_value() * f) != round_to_int(value * f)) {
            spinbutton.set_value(value);
        }
        sig_changed();
    }
}


class NoteEntry : public NumEntryTemp<uint8_t> {
public:
    NoteEntry(const char* labelText);
private:
    int on_input(double* new_value);
    bool on_output();
};


class NumEntryPermille : public NumEntry {
private:
    uint16_t value;
    void value_changed();
public:
    NumEntryPermille(const char* labelText,
                     double lower = 0, double upper = 127, int decimals = 0);
    uint16_t get_value() const { return value; }
    void set_value(uint16_t value);
};


template<typename T>
class ChoiceEntry : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    Gtk::Alignment align;
    const T* values;
public:
    ChoiceEntry(const char* labelText);
    T get_value() const;
    void set_value(T value);
    void set_choices(const char** texts, const T* values);

    void set_tip(const Glib::ustring& tip_text) {
        tooltips.set_tip(combobox, tip_text); //FIXME: don't Gtk::ComboBoxes support tooltips ???
    }
};

template<typename T>
ChoiceEntry<T>::ChoiceEntry(const char* labelText) :
    align(0, 0, 0, 0),
    LabelWidget(labelText, align)
{
    combobox.signal_changed().connect(sig_changed.make_slot());
    align.add(combobox);
}

template<typename T>
void ChoiceEntry<T>::set_choices(const char** texts, const T* values)
{
    for (int i = 0 ; texts[i] ; i++) {
        combobox.append_text(texts[i]);
    }
    this->values = values;
}

template<typename T>
T ChoiceEntry<T>::get_value() const
{
    int rowno = combobox.get_active_row_number();
    return values[rowno];
}

template<typename T>
void ChoiceEntry<T>::set_value(T value)
{
    int row = 0;
    int nb_rows = combobox.get_model()->children().size();
    for (; row < nb_rows ; row++) {
        if (value == values[row]) break;
    }
    combobox.set_active(row == nb_rows ? -1 : row);
}


class ChoiceEntryLeverageCtrl : public LabelWidget {
private:
    gig::leverage_ctrl_t value;
    Gtk::ComboBoxText combobox;
    Gtk::Alignment align;
    void value_changed();
public:
    ChoiceEntryLeverageCtrl(const char* labelText);
    gig::leverage_ctrl_t get_value() const { return value; }
    void set_value(gig::leverage_ctrl_t value);
};


class BoolEntry : public LabelWidget {
private:
    Gtk::CheckButton checkbutton;
public:
    BoolEntry(const char* labelText);
    bool get_value() const { return checkbutton.get_active(); }
    void set_value(bool value) { checkbutton.set_active(value); }

    void set_tip(const Glib::ustring& tip_text) {
        tooltips.set_tip(checkbutton, tip_text);
    }
};


class BoolEntryPlus6 : public LabelWidget {
private:
    Gtk::CheckButton checkbutton;
    void value_changed();
    NumEntryGain& eGain;
    int32_t plus6value;
public:
    BoolEntryPlus6(const char* labelText, NumEntryGain& eGain, int32_t plus6value);
    int32_t get_value() const;
    void set_value(int32_t value);
};

class StringEntry : public LabelWidget {
private:
    Gtk::Entry entry;
    gig::String* ptr;
    void value_changed();
public:
    StringEntry(const char* labelText);
    void set_ptr(gig::String* ptr);
};


#endif
