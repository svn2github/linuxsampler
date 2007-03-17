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

template<typename T2>
class NumEntry : public LabelWidget {
protected:
    Gtk::Adjustment adjust;
    Gtk::HScale scale;
    Gtk::SpinButton spinbutton;
    Gtk::HBox box;
    T2* dimreg;
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

template<typename T2>
NumEntry<T2>::NumEntry(char* labelText, double lower, double upper,
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

class NumEntryGain : public NumEntry<gig::DimensionRegion> {
private:
    void value_changed();
public:
    NumEntryGain(char* labelText,
		 double lower, double upper, int decimals);
    void set_dimreg(gig::DimensionRegion* dimreg);
};

template<typename T>
class NumEntryX : public NumEntry<gig::DimensionRegion> {
private:
    T& (*access)(gig::DimensionRegion*);
    void value_changed();
public:
    NumEntryX(char* labelText, T& (*access)(gig::DimensionRegion*),
              double lower = 0, double upper = 127, int decimals = 0);
    void set_dimreg(gig::DimensionRegion* dimreg);
};

template<typename T>
NumEntryX<T>::NumEntryX(char* labelText, T& (*access)(gig::DimensionRegion*),
			double lower, double upper, int decimals) :
    NumEntry<gig::DimensionRegion>(labelText, lower, upper, decimals),
    access(access)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryX::value_changed));
}

template<typename T>
void NumEntryX<T>::value_changed()
{
    if (dimreg && update_gui) {
        access(dimreg) = T(spinbutton.get_value());
    }
}

template<typename T>
void NumEntryX<T>::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    set_value(access(dimreg));
    this->dimreg = dimreg;
}


class NoteEntry : public NumEntryX<uint8_t> {
public:
    NoteEntry(char* labelText, uint8_t& (*access)(gig::DimensionRegion*));
private:
    int on_input(double* new_value);
    bool on_output();
};


template<typename T, typename T2 = gig::DimensionRegion>
class NumEntryTemp : public NumEntry<T2> {
    using NumEntry<T2>::spinbutton;
    using NumEntry<T2>::dimreg;
private:
    T T2::* param;
    void value_changed();
public:
    NumEntryTemp(char* labelText, T T2::* param,
                 double lower = 0, double upper = 127, int decimals = 0);
    void set_dimreg(gig::DimensionRegion* dimreg);
};

template<typename T, typename T2>
NumEntryTemp<T, T2>::NumEntryTemp(char* labelText, T T2::* param,
                                  double lower, double upper, int decimals) :
    NumEntry<T2>(labelText, lower, upper, decimals),
    param(param)
{
    spinbutton.signal_value_changed().connect(
        sigc::mem_fun(*this, &NumEntryTemp<T, T2>::value_changed));
}

template<typename T, typename T2>
void NumEntryTemp<T, T2>::value_changed()
{
    if (dimreg && update_gui) {
        dimreg->*param = T(spinbutton.get_value());
    }
}

template<typename T, typename T2>
void NumEntryTemp<T, T2>::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    set_value(dimreg->*param);
    this->dimreg = dimreg;
}



class NumEntryPermille : public NumEntry<gig::DimensionRegion> {
private:
    uint16_t gig::DimensionRegion::* param;
    void value_changed();
public:
    NumEntryPermille(char* labelText, uint16_t gig::DimensionRegion::* param,
                     double lower = 0, double upper = 127, int decimals = 0);
    void set_dimreg(gig::DimensionRegion* dimreg);
};


template<typename T>
class ChoiceEntry : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    Gtk::Alignment align;
    T gig::DimensionRegion::* param;
    gig::DimensionRegion* dimreg;
    void value_changed();
    const T* values;
public:
    ChoiceEntry(char* labelText,
                T gig::DimensionRegion::* param);
    void set_choices(char** texts, const T* values);
    void set_dimreg(gig::DimensionRegion* dimreg);
    int get_active_row_number() { return combobox.get_active_row_number(); }
    Glib::SignalProxy0<void> signal_changed() {
        return combobox.signal_changed();
    }
};

template<typename T>
ChoiceEntry<T>::ChoiceEntry(char* labelText,
                            T gig::DimensionRegion::* param) :
    align(0, 0, 0, 0),
    LabelWidget(labelText, align),
    param(param)
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
    if (dimreg && update_gui) {
        int rowno = combobox.get_active_row_number();
        if (rowno != -1) dimreg->*param = values[rowno];
    }
}

template<typename T>
void ChoiceEntry<T>::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    T value = dimreg->*param;
    int row = 0;
    int nb_rows = combobox.get_model()->children().size();
    for (; row < nb_rows ; row++) {
        if (value == values[row]) break;
    }
    combobox.set_active(row == nb_rows ? -1 : row);
    this->dimreg = dimreg;
}


class ChoiceEntryLeverageCtrl : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    Gtk::Alignment align;
    gig::leverage_ctrl_t gig::DimensionRegion::* param;
    gig::DimensionRegion* dimreg;
    void value_changed();
public:
    ChoiceEntryLeverageCtrl(char* labelText,
                            gig::leverage_ctrl_t gig::DimensionRegion::* param);
    void set_dimreg(gig::DimensionRegion* dimreg);
    int get_active_row_number() { return combobox.get_active_row_number(); }
    Glib::SignalProxy0<void> signal_changed() {
        return combobox.signal_changed();
    }
};


class BoolEntry : public LabelWidget {
private:
    Gtk::CheckButton checkbutton;
    bool gig::DimensionRegion::* param;
    gig::DimensionRegion* dimreg;
    void value_changed();
public:
    BoolEntry(char* labelText, bool gig::DimensionRegion::* param);
    void set_dimreg(gig::DimensionRegion* dimreg);
    bool get_active() { return checkbutton.get_active(); }
    Glib::SignalProxy0<void> signal_toggled() {
        return checkbutton.signal_toggled();
    }
};

#endif
