/*                                                         -*- c++ -*-
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

#ifndef GIGEDIT_PARAMEDIT_H
#define GIGEDIT_PARAMEDIT_H

#include <gig.h>

#include <cmath>

#include <glibmm/convert.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/scale.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/table.h>
#include <gtkmm/textview.h>

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 12) || GTKMM_MAJOR_VERSION < 2
#define OLD_TOOLTIPS
#include <gtkmm/tooltips.h>
#endif


Glib::ustring gig_to_utf8(const gig::String& gig_string);
gig::String gig_from_utf8(const Glib::ustring& utf8_string);

int note_value(const Glib::ustring& note);
Glib::ustring note_str(int note);

void spin_button_show_notes(Gtk::SpinButton& spin_button);

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
#ifdef OLD_TOOLTIPS
    Gtk::Tooltips tooltips;
#endif
    sigc::signal<void> sig_changed;
};

class NumEntry : public LabelWidget {
protected:
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    Gtk::Adjustment adjust;
#else
    Glib::RefPtr<Gtk::Adjustment> adjust;
#endif
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
#ifdef OLD_TOOLTIPS
        tooltips.set_tip(spinbutton, tip_text);
#else
        spinbutton.set_tooltip_text(tip_text);
#endif
    }
    void set_upper(double upper) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
        adjust.set_upper(upper);
#else
        adjust->set_upper(upper);
#endif
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
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
    if (value > adjust.get_upper()) value = T(adjust.get_upper());
#else
    if (value > adjust->get_upper()) value = T(adjust->get_upper());
#endif
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
#ifdef OLD_TOOLTIPS
        tooltips.set_tip(combobox, tip_text);
#else
        combobox.set_tooltip_text(tip_text);
#endif
    }
};

template<typename T>
ChoiceEntry<T>::ChoiceEntry(const char* labelText) :
    LabelWidget(labelText, align),
    align(0, 0, 0, 0),
    values(0)
{
    combobox.signal_changed().connect(sig_changed.make_slot());
    align.add(combobox);
}

template<typename T>
void ChoiceEntry<T>::set_choices(const char** texts, const T* values)
{
    for (int i = 0 ; texts[i] ; i++) {
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 24) || GTKMM_MAJOR_VERSION < 2
        combobox.append_text(texts[i]);
#else
        combobox.append(texts[i]);
#endif
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
#ifdef OLD_TOOLTIPS
        tooltips.set_tip(checkbutton, tip_text);
#else
        checkbutton.set_tooltip_text(tip_text);
#endif
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
public:
    StringEntry(const char* labelText);
    gig::String get_value() const;
    void set_value(const gig::String& value);
    void set_width_chars(int n_chars) { entry.set_width_chars(n_chars); }
};

class StringEntryMultiLine : public LabelWidget {
private:
    Gtk::TextView text_view;
    Glib::RefPtr<Gtk::TextBuffer> text_buffer;
    Gtk::Frame frame;
public:
    StringEntryMultiLine(const char* labelText);
    gig::String get_value() const;
    void set_value(const gig::String& value);
};


/**
 * Container widget for LabelWidgets.
 */
class Table : public Gtk::Table
{
public:
    Table(int x, int y);
    void add(BoolEntry& boolentry);
    void add(BoolEntryPlus6& boolentry);
    void add(LabelWidget& labelwidget);
private:
    int rowno;
};


/**
 * Base class for editor components that use LabelWidgets to edit
 * member variables of the same class. By connecting the widgets to
 * members of the model class, the model is automatically kept
 * updated.
 */
template<class M>
class PropEditor {
public:
    sigc::signal<void>& signal_changed() {
        return sig_changed;
    }
protected:
    M* m;
    int update_model; // to prevent infinite update loops
    PropEditor() : m(0), update_model(0) { }
    sigc::signal<void> sig_changed;

    template<class C, typename T>
    void connect(C& widget, T M::* member) {
        // gcc 4.1.2 needs this temporary variable to resolve the
        // address
        void (PropEditor::*f)(const C* w, T M::* member) =
            &PropEditor::set_member;
        widget.signal_value_changed().connect(
            sigc::bind(sigc::mem_fun(*this, f), &widget, member));

        void (PropEditor::*g)(C* w, T M::* member) =
            &PropEditor::get_member;
        sig.connect(
            sigc::bind(sigc::mem_fun(*this, g), &widget, member));
    }

    template<class C, class S, typename T>
    void connect(C& widget, void (S::*setter)(T)) {
        void (PropEditor::*f)(const C* w, void (S::*setter)(T)) =
            &PropEditor<M>::call_setter;
        widget.signal_value_changed().connect(
            sigc::bind(sigc::mem_fun(*this, f), &widget, setter));
    }

    void connect(NoteEntry& eKeyRangeLow, NoteEntry& eKeyRangeHigh,
                 gig::range_t M::* range) {
        eKeyRangeLow.signal_value_changed().connect(
            sigc::bind(
                sigc::mem_fun(*this, &PropEditor::key_range_low_changed),
                &eKeyRangeLow, &eKeyRangeHigh, range));
        eKeyRangeHigh.signal_value_changed().connect(
            sigc::bind(
                sigc::mem_fun(*this, &PropEditor::key_range_high_changed),
                &eKeyRangeLow, &eKeyRangeHigh, range));
        sig.connect(
            sigc::bind(sigc::mem_fun(*this, &PropEditor::get_key_range),
                       &eKeyRangeLow, &eKeyRangeHigh, range));
    }

    void update(M* m) {
        update_model++;
        this->m = m;
        sig.emit();
        update_model--;
    }

private:
    sigc::signal<void> sig;

    void key_range_low_changed(NoteEntry* eKeyRangeLow,
                               NoteEntry* eKeyRangeHigh,
                               gig::range_t M::* range) {
        if (update_model == 0) {
            uint8_t value = eKeyRangeLow->get_value();
            (m->*range).low = value;
            if (value > (m->*range).high) {
                eKeyRangeHigh->set_value(value);
            }
            sig_changed();
        }
    }

    void key_range_high_changed(NoteEntry* eKeyRangeLow,
                                NoteEntry* eKeyRangeHigh,
                                gig::range_t M::* range) {
        if (update_model == 0) {
            uint8_t value = eKeyRangeHigh->get_value();
            (m->*range).high = value;
            if (value < (m->*range).low) {
                eKeyRangeLow->set_value(value);
            }
            sig_changed();
        }
    }

    template<class C, typename T>
    void set_member(const C* w, T M::* member) {
        if (update_model == 0) {
            m->*member = w->get_value();
            sig_changed();
        }
    }

    template<class C, typename T>
    void get_member(C* w, T M::* member) {
        w->set_value(m->*member);
    }

    void get_key_range(NoteEntry* eKeyRangeLow,
                       NoteEntry* eKeyRangeHigh,
                       gig::range_t M::* range) {
        eKeyRangeLow->set_value((m->*range).low);
        eKeyRangeHigh->set_value((m->*range).high);
    }

    template<class C, class S, typename T>
    void call_setter(const C* w, void (S::*setter)(T)) {
        if (update_model == 0) {
            (static_cast<S*>(this)->*setter)(w->get_value());
            sig_changed();
        }
    }
};

#endif
