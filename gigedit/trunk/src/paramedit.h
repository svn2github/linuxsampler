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

#include <gtkmm/adjustment.h>
#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/scale.h>
#include <gtkmm/spinbutton.h>

extern bool update_gui;

class LabelWidget {
public:
    Gtk::Label label;
    Gtk::Widget& widget;

    LabelWidget(char* labelText, Gtk::Widget& widget);
    void set_sensitive(bool sensitive = true);
};

class NumEntry : public LabelWidget {
protected:
    Gtk::Adjustment adjust;
    Gtk::HScale scale;
    Gtk::SpinButton spinbutton;
    Gtk::HBox box;
public:
    NumEntry(char* labelText, double lower = 0, double upper = 127,
             int decimals = 0);
    void set_value(double value) {
        spinbutton.set_value(value);
    }
    Glib::SignalProxy0<void> signal_value_changed() {
        return spinbutton.signal_value_changed();
    }
    double get_value() const {
        return spinbutton.get_value();
    }
};

class NumEntryGain : public NumEntry {
private:
    void value_changed();
    int32_t* ptr;
    double coeff;
public:
    NumEntryGain(char* labelText,
                 double lower, double upper, int decimals, double coeff);
    void set_ptr(int32_t* ptr);
};

template<typename T>
class NumEntryTemp : public NumEntry {
private:
    T* ptr;
    void value_changed();
public:
    NumEntryTemp(char* labelText,
                 double lower = 0, double upper = 127, int decimals = 0);
    void set_ptr(T* ptr);
};

template<typename T>
NumEntryTemp<T>::NumEntryTemp(char* labelText,
                              double lower, double upper, int decimals) :
    NumEntry(labelText, lower, upper, decimals)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryTemp::value_changed));
}

template<typename T>
void NumEntryTemp<T>::value_changed()
{
    if (ptr && update_gui) {
        *ptr = T(spinbutton.get_value());
    }
}

template<typename T>
void NumEntryTemp<T>::set_ptr(T* ptr)
{
    this->ptr = 0;
    set_value(*ptr);
    this->ptr = ptr;
}


class NoteEntry : public NumEntryTemp<uint8_t> {
public:
    NoteEntry(char* labelText);
private:
    int on_input(double* new_value);
    bool on_output();
};


class NumEntryPermille : public NumEntry {
private:
    uint16_t* ptr;
    void value_changed();
public:
    NumEntryPermille(char* labelText,
                     double lower = 0, double upper = 127, int decimals = 0);
    void set_ptr(uint16_t* ptr);
};


template<typename T>
class ChoiceEntry : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    Gtk::Alignment align;
    T* ptr;
    void value_changed();
    const T* values;
public:
    ChoiceEntry(char* labelText);
    void set_choices(char** texts, const T* values);
    void set_ptr(T* ptr);
    int get_active_row_number() { return combobox.get_active_row_number(); }
    Glib::SignalProxy0<void> signal_changed() {
        return combobox.signal_changed();
    }
};

template<typename T>
ChoiceEntry<T>::ChoiceEntry(char* labelText) :
    align(0, 0, 0, 0),
    LabelWidget(labelText, align)
{
    combobox.signal_changed().connect(
        sigc::mem_fun(*this, &ChoiceEntry::value_changed));
    align.add(combobox);
}

template<typename T>
void ChoiceEntry<T>::set_choices(char** texts, const T* values)
{
    for (int i = 0 ; texts[i] ; i++) {
        combobox.append_text(texts[i]);
    }
    this->values = values;
}

template<typename T>
void ChoiceEntry<T>::value_changed()
{
    if (ptr && update_gui) {
        int rowno = combobox.get_active_row_number();
        if (rowno != -1) *ptr = values[rowno];
    }
}

template<typename T>
void ChoiceEntry<T>::set_ptr(T* ptr)
{
    this->ptr = 0;
    T value = *ptr;
    int row = 0;
    int nb_rows = combobox.get_model()->children().size();
    for (; row < nb_rows ; row++) {
        if (value == values[row]) break;
    }
    combobox.set_active(row == nb_rows ? -1 : row);
    this->ptr = ptr;
}


class ChoiceEntryLeverageCtrl : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    Gtk::Alignment align;
    gig::leverage_ctrl_t* ptr;
    void value_changed();
public:
    ChoiceEntryLeverageCtrl(char* labelText);
    void set_ptr(gig::leverage_ctrl_t* ptr);
    int get_active_row_number() { return combobox.get_active_row_number(); }
    Glib::SignalProxy0<void> signal_changed() {
        return combobox.signal_changed();
    }
};


class BoolEntry : public LabelWidget {
private:
    Gtk::CheckButton checkbutton;
    bool* ptr;
    void value_changed();
public:
    BoolEntry(char* labelText);
    bool get_active() { return checkbutton.get_active(); }
    Glib::SignalProxy0<void> signal_toggled() {
        return checkbutton.signal_toggled();
    }
    void set_ptr(bool* ptr);
};


class BoolEntryPlus6 : public LabelWidget {
private:
    Gtk::CheckButton checkbutton;
    int32_t* ptr;
    void value_changed();
    NumEntryGain& eGain;
    int32_t plus6value;
public:
    BoolEntryPlus6(char* labelText, NumEntryGain& eGain, int32_t plus6value);
    void set_ptr(int32_t* ptr);
    bool get_active() { return checkbutton.get_active(); }
    Glib::SignalProxy0<void> signal_toggled() {
        return checkbutton.signal_toggled();
    }
};

class StringEntry : public LabelWidget {
private:
    Gtk::Entry entry;
    gig::String* ptr;
    void value_changed();
public:
    StringEntry(char* labelText);
    void set_ptr(gig::String* ptr);
};


#endif
