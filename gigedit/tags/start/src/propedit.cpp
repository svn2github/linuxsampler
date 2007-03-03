#include "propedit.h"

/*

  NumEntryX         access(dimreg) = T(spinbutton.get_value())
  NumEntryTemp      dimreg->*param = T(spinbutton.get_value())
  NumEntryPermille  dimreg->*param = uint16_t(spinbutton.get_value() * 10 + 0.5)

  ChoiceEntry       int rowno = combobox.get_active_row_number();
                    if (rowno != -1) dimreg->*param = values[rowno];

  ChoiceEntryLC     int rowno = combobox.get_active_row_number();
                    ...
                    (dimreg->*param).type ...

  BoolEntry         dimreg->*param = checkbutton.get_active();



 */

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

// -------------------------------------------------------------------------
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

// -------------------------------------------------------------------------
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
    if (dimreg) {
        dimreg->*param = uint16_t(spinbutton.get_value() * 10 + 0.5);
    }
}

void NumEntryPermille::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    spinbutton.set_value(dimreg->*param / 10.0);
    this->dimreg = dimreg;
}



// -------------------------------------------------------------------------
BoolEntry::BoolEntry(char* labelText, bool gig::DimensionRegion::* param) :
    LabelWidget(labelText, checkbutton),
    param(param)
{
    checkbutton.signal_toggled().connect(
        sigc::mem_fun(*this, &BoolEntry::value_changed));
}

void BoolEntry::value_changed()
{
    if (dimreg) {
        dimreg->*param = checkbutton.get_active();
    }
}

void BoolEntry::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    checkbutton.set_active(dimreg->*param);
    this->dimreg = dimreg;
}

// -------------------------------------------------------------------------
ChoiceEntryLeverageCtrl::ChoiceEntryLeverageCtrl(
    char* labelText,
    gig::leverage_ctrl_t gig::DimensionRegion::* param) :
    LabelWidget(labelText, combobox),
    param(param)
{
    for (int i = 0 ; i < 99 ; i++) {
        if (controlChangeTexts[i]) {
            combobox.append_text(controlChangeTexts[i]);
        }
    }
    combobox.signal_changed().connect(
        sigc::mem_fun(*this, &ChoiceEntryLeverageCtrl::value_changed));
}

void ChoiceEntryLeverageCtrl::value_changed()
{
    if (dimreg) {
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
