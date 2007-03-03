/* -*- C++ -*- */

#include <gig.h>

#include <gtkmm/alignment.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>


class ConverterPermille {
public:
    uint16_t convert1(double x);
    double convert2(uint16_t x);
};

template<typename T>
class ConverterNum {
public:
    T convert1(double x) { return T(x); }
    double convert2(T x) { return x; }
};

template<typename T>
class ConverterChoice {
private:
    const T* values;
public:
    T convert1(int x);
    int convert2(T x);
};

class ConverterChoiceLevCtrl {
public:
    gig::leverage_ctrl_t convert1(int x);
    int convert2(gig::leverage_ctrl_t x);
};

class ConverterBool {
public:
    bool convert1(bool x) { return x; }
    bool convert2(bool x) { return x; }
};


template<typename T>
class Tjosan : public ConverterNum<T> {
    using ConverterNum<T>::convert1;
private:
    T* var;
public:
    void value_changed();
};


template<typename T>
void Tjosan<T>::value_changed() {
    var = convert1(4.2);
};

// -------------------------------------------------------------------------
class LabelWidget {
public:
    Gtk::Label label;
    Gtk::Widget& widget;

    LabelWidget(char* labelText, Gtk::Widget& widget);
    void set_sensitive(bool sensitive = true);
};

// -------------------------------------------------------------------------
template<typename T2>
class NumEntry : public LabelWidget {
protected:
    Gtk::SpinButton spinbutton;
    Gtk::Alignment align;
    T2* dimreg;
public:
    NumEntry(char* labelText, double lower = 0, double upper = 127,
             int decimals = 0);
};

// -------------------------------------------------------------------------
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


// -------------------------------------------------------------------------
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


// -------------------------------------------------------------------------
class NumEntryPermille : public NumEntry<gig::DimensionRegion> {
private:
    uint16_t gig::DimensionRegion::* param;
    void value_changed();
public:
    NumEntryPermille(char* labelText, uint16_t gig::DimensionRegion::* param,
                     double lower = 0, double upper = 127, int decimals = 0);
    void set_dimreg(gig::DimensionRegion* dimreg);
};


// -------------------------------------------------------------------------
template<typename T>
class ChoiceEntry : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    T gig::DimensionRegion::* param;
    gig::DimensionRegion* dimreg;
    void value_changed();
    const T* values;
public:
    ChoiceEntry(char* labelText,
                T gig::DimensionRegion::* param);
    void set_choices(char** texts, const T* values);
    void set_dimreg(gig::DimensionRegion* dimreg);
    bool get_active_row_number() { return combobox.get_active_row_number(); }
    Glib::SignalProxy0<void> signal_changed() {
        return combobox.signal_changed();
    }
};


// -------------------------------------------------------------------------
class ChoiceEntryLeverageCtrl : public LabelWidget {
private:
    Gtk::ComboBoxText combobox;
    gig::leverage_ctrl_t gig::DimensionRegion::* param;
    gig::DimensionRegion* dimreg;
    void value_changed();
public:
    ChoiceEntryLeverageCtrl(char* labelText,
                            gig::leverage_ctrl_t gig::DimensionRegion::* param);
    void set_dimreg(gig::DimensionRegion* dimreg);
    bool get_active_row_number() { return combobox.get_active_row_number(); }
    Glib::SignalProxy0<void> signal_changed() {
        return combobox.signal_changed();
    }
};



// -------------------------------------------------------------------------
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



// -------------------------------------------------------------------------
// Implementation of template functions


// -------------------------------------------------------------------------
template<typename T2>
NumEntry<T2>::NumEntry(char* labelText, double lower, double upper,
                       int decimals) :
    align(0, 0, 0, 0),
    LabelWidget(labelText, align)
{
    spinbutton.set_range(lower, upper);
    spinbutton.set_increments(1, 10);
    spinbutton.set_digits(decimals);

    align.add(spinbutton);
}


// -------------------------------------------------------------------------
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
    if (dimreg) {
        access(dimreg) = T(spinbutton.get_value());
    }
}

template<typename T>
void NumEntryX<T>::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    spinbutton.set_value(access(dimreg));
    this->dimreg = dimreg;
}


// -------------------------------------------------------------------------
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
    if (dimreg) {
        dimreg->*param = T(spinbutton.get_value());
    }
}

template<typename T, typename T2>
void NumEntryTemp<T, T2>::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    spinbutton.set_value(dimreg->*param);
    this->dimreg = dimreg;
}


// -------------------------------------------------------------------------
template<typename T>
ChoiceEntry<T>::ChoiceEntry(char* labelText,
                            T gig::DimensionRegion::* param) :
    LabelWidget(labelText, combobox),
    param(param)
{
    combobox.signal_changed().connect(
        sigc::mem_fun(*this, &ChoiceEntry::value_changed));
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
    if (dimreg) {
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

