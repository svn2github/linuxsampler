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

#include <libintl.h>
#include <iostream>

#include "mainwindow.h"

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/stock.h>
#if GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 6
#define ABOUT_DIALOG
#include <gtkmm/aboutdialog.h>
#include <gtkmm/messagedialog.h>
#endif

#define _(String) gettext(String)

template<class T> inline std::string ToString(T o) {
    std::stringstream ss;
    ss << o;
    return ss.str();
}

bool update_gui;

uint8_t& access_UnityNote(gig::DimensionRegion* dimreg)
{
    return dimreg->UnityNote;
}
int16_t& access_FineTune(gig::DimensionRegion* dimreg)
{
    return dimreg->FineTune;
}
uint32_t& access_SampleLoops(gig::DimensionRegion* dimreg)
{
    return dimreg->SampleLoops;
}
uint8_t& access_Crossfade_in_start(gig::DimensionRegion* dimreg)
{
    return dimreg->Crossfade.in_start;
}
uint8_t& access_Crossfade_in_end(gig::DimensionRegion* dimreg)
{
    return dimreg->Crossfade.in_end;
}
uint8_t& access_Crossfade_out_start(gig::DimensionRegion* dimreg)
{
    return dimreg->Crossfade.out_start;
}
uint8_t& access_Crossfade_out_end(gig::DimensionRegion* dimreg)
{
    return dimreg->Crossfade.out_end;
}

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

void MainWindow::addString(char* labelText, Gtk::Label*& label,
                           Gtk::Entry*& widget)
{
    label = new Gtk::Label(Glib::ustring(labelText) + ":");
    label->set_alignment(Gtk::ALIGN_LEFT);

    table[pageno]->attach(*label, 1, 2, rowno, rowno + 1,
                          Gtk::FILL, Gtk::SHRINK);

    widget = new Gtk::Entry();

    table[pageno]->attach(*widget, 2, 3, rowno, rowno + 1,
                          Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);

    rowno++;
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
    set_value(dimreg->Gain / -655360.0);
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

BoolEntry::BoolEntry(char* labelText, bool gig::DimensionRegion::* param) :
    LabelWidget(labelText, checkbutton),
    param(param)
{
    checkbutton.signal_toggled().connect(
        sigc::mem_fun(*this, &BoolEntry::value_changed));
}

void BoolEntry::value_changed()
{
    if (dimreg && update_gui) {
        dimreg->*param = checkbutton.get_active();
    }
}

void BoolEntry::set_dimreg(gig::DimensionRegion* dimreg)
{
    this->dimreg = 0;
    checkbutton.set_active(dimreg->*param);
    this->dimreg = dimreg;
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

void MainWindow::addHeader(char* text)
{
    if (firstRowInBlock < rowno - 1)
    {
        Gtk::Label* filler = new Gtk::Label("    ");
        table[pageno]->attach(*filler, 0, 1, firstRowInBlock, rowno,
                              Gtk::FILL, Gtk::SHRINK);
    }
    Glib::ustring str = "<b>";
    str += text;
    str += "</b>";
    Gtk::Label* label = new Gtk::Label(str);
    label->set_use_markup();
    label->set_alignment(Gtk::ALIGN_LEFT);
    table[pageno]->attach(*label, 0, 3, rowno, rowno + 1,
                          Gtk::FILL, Gtk::SHRINK);
    rowno++;
    firstRowInBlock = rowno;
}

void MainWindow::nextPage()
{
    if (firstRowInBlock < rowno - 1)
    {
        Gtk::Label* filler = new Gtk::Label("    ");
        table[pageno]->attach(*filler, 0, 1, firstRowInBlock, rowno,
                              Gtk::FILL, Gtk::SHRINK);
    }
    pageno++;
    rowno = 0;
    firstRowInBlock = 0;
}

void MainWindow::addProp(LabelWidget& prop)
{
    table[pageno]->attach(prop.label, 1, 2, rowno, rowno + 1,
                          Gtk::FILL, Gtk::SHRINK);
    table[pageno]->attach(prop.widget, 2, 3, rowno, rowno + 1,
                          Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);
    rowno++;
}




MainWindow::MainWindow() :
//    eSample("Sample", wSample),
    eVelocityUpperLimit("VelocityUpperLimit",
                        &gig::DimensionRegion::VelocityUpperLimit),
    eEG1PreAttack("PreAttack", &gig::DimensionRegion::EG1PreAttack, 0, 100, 2),
    eEG1Attack("Attack", &gig::DimensionRegion::EG1Attack, 0, 60, 3),
    eEG1Decay1("Decay1", &gig::DimensionRegion::EG1Decay1, 0.005, 60, 3),
    eEG1Decay2("Decay2", &gig::DimensionRegion::EG1Decay2, 0, 60, 3),
    eEG1InfiniteSustain("InfiniteSustain",
                        &gig::DimensionRegion::EG1InfiniteSustain),
    eEG1Sustain("Sustain", &gig::DimensionRegion::EG1Sustain, 0, 100, 2),
    eEG1Release("Release", &gig::DimensionRegion::EG1Release, 0, 60, 3),
    eEG1Hold("Hold", &gig::DimensionRegion::EG1Hold),
    eEG1Controller("Controller", &gig::DimensionRegion::EG1Controller),
    eEG1ControllerInvert("ControllerInvert",
                         &gig::DimensionRegion::EG1ControllerInvert),
    eEG1ControllerAttackInfluence("ControllerAttackInfluence",
                                  &gig::DimensionRegion::EG1ControllerAttackInfluence,
                                  0, 3),
    eEG1ControllerDecayInfluence("ControllerDecayInfluence",
                                 &gig::DimensionRegion::EG1ControllerDecayInfluence,
                                 0, 3),
    eEG1ControllerReleaseInfluence("ControllerReleaseInfluence",
                                   &gig::DimensionRegion::EG1ControllerReleaseInfluence,
                                   0, 3),
    eLFO1Frequency("Frequency", &gig::DimensionRegion::LFO1Frequency,
                   0.1, 10, 2),
    eLFO1InternalDepth("InternalDepth",
                       &gig::DimensionRegion::LFO1InternalDepth, 0, 1200),
    eLFO1ControlDepth("ControlDepth", &gig::DimensionRegion::LFO1ControlDepth,
                      0, 1200),
    eLFO1Controller("Controller", &gig::DimensionRegion::LFO1Controller),
    eLFO1FlipPhase("FlipPhase", &gig::DimensionRegion::LFO1FlipPhase),
    eLFO1Sync("Sync", &gig::DimensionRegion::LFO1Sync),
    eEG2PreAttack("PreAttack", &gig::DimensionRegion::EG2PreAttack, 0, 100, 2),
    eEG2Attack("Attack", &gig::DimensionRegion::EG2Attack, 0, 60, 3),
    eEG2Decay1("Decay1", &gig::DimensionRegion::EG2Decay1, 0.005, 60, 3),
    eEG2Decay2("Decay2", &gig::DimensionRegion::EG2Decay2, 0, 60, 3),
    eEG2InfiniteSustain("InfiniteSustain",
                        &gig::DimensionRegion::EG2InfiniteSustain),
    eEG2Sustain("Sustain", &gig::DimensionRegion::EG2Sustain, 0, 100, 2),
    eEG2Release("Release", &gig::DimensionRegion::EG2Release, 0, 60, 3),
    eEG2Controller("Controller", &gig::DimensionRegion::EG2Controller),
    eEG2ControllerInvert("ControllerInvert",
                         &gig::DimensionRegion::EG2ControllerInvert),
    eEG2ControllerAttackInfluence("ControllerAttackInfluence",
                                  &gig::DimensionRegion::EG2ControllerAttackInfluence,
                                  0, 3),
    eEG2ControllerDecayInfluence("ControllerDecayInfluence",
                                 &gig::DimensionRegion::EG2ControllerDecayInfluence,
                                 0, 3),
    eEG2ControllerReleaseInfluence("ControllerReleaseInfluence",
                                   &gig::DimensionRegion::EG2ControllerReleaseInfluence,
                                   0, 3),
    eLFO2Frequency("Frequency", &gig::DimensionRegion::LFO2Frequency,
                   0.1, 10, 2),
    eLFO2InternalDepth("InternalDepth",
                       &gig::DimensionRegion::LFO2InternalDepth, 0, 1200),
    eLFO2ControlDepth("ControlDepth",
                      &gig::DimensionRegion::LFO2ControlDepth, 0, 1200),
    eLFO2Controller("Controller", &gig::DimensionRegion::LFO2Controller),
    eLFO2FlipPhase("FlipPhase", &gig::DimensionRegion::LFO2FlipPhase),
    eLFO2Sync("Sync", &gig::DimensionRegion::LFO2Sync),
    eEG3Attack("Attack", &gig::DimensionRegion::EG3Attack, 0, 10, 3),
    eEG3Depth("Depth", &gig::DimensionRegion::EG3Depth, -1200, 1200),
    eLFO3Frequency("Frequency", &gig::DimensionRegion::LFO3Frequency,
                   0.1, 10, 2),
    eLFO3InternalDepth("InternalDepth",
                       &gig::DimensionRegion::LFO3InternalDepth, 0, 1200),
    eLFO3ControlDepth("ControlDepth", &gig::DimensionRegion::LFO3ControlDepth,
                      0, 1200),
    eLFO3Controller("Controller", &gig::DimensionRegion::LFO3Controller),
    eLFO3Sync("Sync", &gig::DimensionRegion::LFO3Sync),
    eVCFEnabled("Enabled", &gig::DimensionRegion::VCFEnabled),
    eVCFType("Type", &gig::DimensionRegion::VCFType),
    eVCFCutoffController("CutoffController",
                         &gig::DimensionRegion::VCFCutoffController),
    eVCFCutoffControllerInvert("CutoffControllerInvert",
                               &gig::DimensionRegion::VCFCutoffControllerInvert),
    eVCFCutoff("Cutoff", &gig::DimensionRegion::VCFCutoff),
    eVCFVelocityCurve("VelocityCurve", &gig::DimensionRegion::VCFVelocityCurve),
    eVCFVelocityScale("VelocityScale", &gig::DimensionRegion::VCFVelocityScale),
    eVCFVelocityDynamicRange("VelocityDynamicRange",
                             &gig::DimensionRegion::VCFVelocityDynamicRange,
                             0, 4),
    eVCFResonance("Resonance", &gig::DimensionRegion::VCFResonance),
    eVCFResonanceDynamic("ResonanceDynamic",
                         &gig::DimensionRegion::VCFResonanceDynamic),
    eVCFResonanceController("ResonanceController",
                            &gig::DimensionRegion::VCFResonanceController),
    eVCFKeyboardTracking("KeyboardTracking",
                         &gig::DimensionRegion::VCFKeyboardTracking),
    eVCFKeyboardTrackingBreakpoint("KeyboardTrackingBreakpoint",
                                   &gig::DimensionRegion::VCFKeyboardTrackingBreakpoint),
    eVelocityResponseCurve("VelocityResponseCurve",
                           &gig::DimensionRegion::VelocityResponseCurve),
    eVelocityResponseDepth("VelocityResponseDepth",
                           &gig::DimensionRegion::VelocityResponseDepth, 0, 4),
    eVelocityResponseCurveScaling("VelocityResponseCurveScaling",
                                  &gig::DimensionRegion::VelocityResponseCurveScaling),
    eReleaseVelocityResponseCurve("ReleaseVelocityResponseCurve",
                                  &gig::DimensionRegion::ReleaseVelocityResponseCurve),
    eReleaseVelocityResponseDepth("ReleaseVelocityResponseDepth",
                                  &gig::DimensionRegion::ReleaseVelocityResponseDepth,
                                  0, 4),
    eReleaseTriggerDecay("ReleaseTriggerDecay",
                         &gig::DimensionRegion::ReleaseTriggerDecay, 0, 8),
    eCrossfade_in_start("Crossfade.in_start", &access_Crossfade_in_start),
    eCrossfade_in_end("Crossfade.in_end", &access_Crossfade_in_end),
    eCrossfade_out_start("Crossfade.out_start", &access_Crossfade_out_start),
    eCrossfade_out_end("Crossfade.out_end", &access_Crossfade_out_end),
    ePitchTrack("PitchTrack", &gig::DimensionRegion::PitchTrack),
    eDimensionBypass("DimensionBypass", &gig::DimensionRegion::DimensionBypass),
    ePan("Pan", &gig::DimensionRegion::Pan, -64, 63),
    eSelfMask("SelfMask", &gig::DimensionRegion::SelfMask),
    eAttenuationController("AttenuationController",
                           &gig::DimensionRegion::AttenuationController),
    eInvertAttenuationController("InvertAttenuationController",
                                 &gig::DimensionRegion::InvertAttenuationController),
    eAttenuationControllerThreshold("AttenuationControllerThreshold",
                                    &gig::DimensionRegion::AttenuationControllerThreshold),
    eChannelOffset("ChannelOffset", &gig::DimensionRegion::ChannelOffset, 0, 9),
    eSustainDefeat("SustainDefeat", &gig::DimensionRegion::SustainDefeat),
    eMSDecode("MSDecode", &gig::DimensionRegion::MSDecode),
    eSampleStartOffset("SampleStartOffset",
                       &gig::DimensionRegion::SampleStartOffset, 0, 2000),
    eUnityNote("UnityNote", &access_UnityNote),
    eFineTune("FineTune", &access_FineTune, -49, 50),
    eGain("Gain", -96, 0, 2),
    eSampleLoops("SampleLoops", &access_SampleLoops, 0, 1)
{
//    set_border_width(5);
    set_default_size(400, 200);


    add(m_VBox);

    // Handle selection
    Glib::RefPtr<Gtk::TreeSelection> tree_sel_ref = m_TreeView.get_selection();
    tree_sel_ref->signal_changed().connect(
	sigc::mem_fun(*this, &MainWindow::on_sel_change));

    m_TreeView.signal_button_press_event().connect_notify(
        sigc::mem_fun(*this, &MainWindow::on_button_release));

    // Add the TreeView tab, inside a ScrolledWindow, with the button underneath:
    m_ScrolledWindow.add(m_TreeViewNotebook);
    m_ScrolledWindow.set_size_request(400, 600);
    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    for (int i = 0 ; i < 5 ; i++) {
        table[i] = new Gtk::Table(3, 1);
        table[i]->set_col_spacings(5);
    }

    pageno = 0;
    rowno = 0;
    firstRowInBlock = 0;

    addString("Sample", lSample, wSample);
    addProp(eVelocityUpperLimit);
    addHeader("EG1");
    addProp(eEG1PreAttack);
    addProp(eEG1Attack);
    addProp(eEG1Decay1);
    addProp(eEG1Decay2);
    addProp(eEG1InfiniteSustain);
    addProp(eEG1Sustain);
    addProp(eEG1Release);
    addProp(eEG1Hold);
    addProp(eEG1Controller);
    addProp(eEG1ControllerInvert);
    addProp(eEG1ControllerAttackInfluence);
    addProp(eEG1ControllerDecayInfluence);
    addProp(eEG1ControllerReleaseInfluence);
    addHeader("LFO1");
    addProp(eLFO1Frequency);
    addProp(eLFO1InternalDepth);
    addProp(eLFO1ControlDepth);
    {
        char* choices[] = { "internal", "modwheel", "breath",
                            "internal+modwheel", "internal+breath", 0 };
        static const gig::lfo1_ctrl_t values[] = {
            gig::lfo1_ctrl_internal,
            gig::lfo1_ctrl_modwheel,
            gig::lfo1_ctrl_breath,
            gig::lfo1_ctrl_internal_modwheel,
            gig::lfo1_ctrl_internal_breath
        };
        eLFO1Controller.set_choices(choices, values);
    }
    addProp(eLFO1Controller);
    addProp(eLFO1FlipPhase);
    addProp(eLFO1Sync);

    nextPage();
    addHeader("EG2");
    addProp(eEG2PreAttack);
    addProp(eEG2Attack);
    addProp(eEG2Decay1);
    addProp(eEG2Decay2);
    addProp(eEG2InfiniteSustain);
    addProp(eEG2Sustain);
    addProp(eEG2Release);
    addProp(eEG2Controller);
    addProp(eEG2ControllerInvert);
    addProp(eEG2ControllerAttackInfluence);
    addProp(eEG2ControllerDecayInfluence);
    addProp(eEG2ControllerReleaseInfluence);
    addHeader("LFO2");
    addProp(eLFO2Frequency);
    addProp(eLFO2InternalDepth);
    addProp(eLFO2ControlDepth);
    {
        char* choices[] = { "internal", "modwheel", "foot",
                            "internal+modwheel", "internal+foot", 0 };
        static const gig::lfo2_ctrl_t values[] = {
            gig::lfo2_ctrl_internal,
            gig::lfo2_ctrl_modwheel,
            gig::lfo2_ctrl_foot,
            gig::lfo2_ctrl_internal_modwheel,
            gig::lfo2_ctrl_internal_foot
        };
        eLFO2Controller.set_choices(choices, values);
    }
    addProp(eLFO2Controller);
    addProp(eLFO2FlipPhase);
    addProp(eLFO2Sync);

    nextPage();

    addHeader("EG3");
    addProp(eEG3Attack);
    addProp(eEG3Depth);
    addHeader("LFO3");
    addProp(eLFO3Frequency);
    addProp(eLFO3InternalDepth);
    addProp(eLFO3ControlDepth);
    {
        char* choices[] = { "internal", "modwheel", "aftertouch",
                            "internal+modwheel", "internal+aftertouch", 0 };
        static const gig::lfo3_ctrl_t values[] = {
            gig::lfo3_ctrl_internal,
            gig::lfo3_ctrl_modwheel,
            gig::lfo3_ctrl_aftertouch,
            gig::lfo3_ctrl_internal_modwheel,
            gig::lfo3_ctrl_internal_aftertouch
        };
        eLFO3Controller.set_choices(choices, values);
    }
    addProp(eLFO3Controller);
    addProp(eLFO3Sync);
    addHeader("VCF");
    addProp(eVCFEnabled);
    {
        char* choices[] = { "lowpass", "lowpassturbo", "bandpass",
                            "highpass", "bandreject", 0 };
        static const gig::vcf_type_t values[] = {
            gig::vcf_type_lowpass,
            gig::vcf_type_lowpassturbo,
            gig::vcf_type_bandpass,
            gig::vcf_type_highpass,
            gig::vcf_type_bandreject
        };
        eVCFType.set_choices(choices, values);
    }
    addProp(eVCFType);
    {
        char* choices[] = { "none", "none2", "modwheel", "effect1", "effect2",
                            "breath", "foot", "sustainpedal", "softpedal",
                            "genpurpose7", "genpurpose8", "aftertouch", 0 };
        static const gig::vcf_cutoff_ctrl_t values[] = {
            gig::vcf_cutoff_ctrl_none,
            gig::vcf_cutoff_ctrl_none2,
            gig::vcf_cutoff_ctrl_modwheel,
            gig::vcf_cutoff_ctrl_effect1,
            gig::vcf_cutoff_ctrl_effect2,
            gig::vcf_cutoff_ctrl_breath,
            gig::vcf_cutoff_ctrl_foot,
            gig::vcf_cutoff_ctrl_sustainpedal,
            gig::vcf_cutoff_ctrl_softpedal,
            gig::vcf_cutoff_ctrl_genpurpose7,
            gig::vcf_cutoff_ctrl_genpurpose8,
            gig::vcf_cutoff_ctrl_aftertouch
        };
        eVCFCutoffController.set_choices(choices, values);
    }
    addProp(eVCFCutoffController);
    addProp(eVCFCutoffControllerInvert);
    addProp(eVCFCutoff);
    char* curve_type_texts[] = { "nonlinear", "linear", "special", 0 };
    static const gig::curve_type_t curve_type_values[] = {
        gig::curve_type_nonlinear,
        gig::curve_type_linear,
        gig::curve_type_special
    };
    eVCFVelocityCurve.set_choices(curve_type_texts, curve_type_values);
    addProp(eVCFVelocityCurve);
    addProp(eVCFVelocityScale);
    addProp(eVCFVelocityDynamicRange);
    addProp(eVCFResonance);
    addProp(eVCFResonanceDynamic);
    {
        char* choices[] = { "none", "genpurpose3", "genpurpose4",
                            "genpurpose5", "genpurpose6", 0 };
        static const gig::vcf_res_ctrl_t values[] = {
            gig::vcf_res_ctrl_none,
            gig::vcf_res_ctrl_genpurpose3,
            gig::vcf_res_ctrl_genpurpose4,
            gig::vcf_res_ctrl_genpurpose5,
            gig::vcf_res_ctrl_genpurpose6
        };
        eVCFResonanceController.set_choices(choices, values);
    }
    addProp(eVCFResonanceController);
    addProp(eVCFKeyboardTracking);
    addProp(eVCFKeyboardTrackingBreakpoint);

    nextPage();

    eVelocityResponseCurve.set_choices(curve_type_texts, curve_type_values);
    addProp(eVelocityResponseCurve);
    addProp(eVelocityResponseDepth);
    addProp(eVelocityResponseCurveScaling);
    eReleaseVelocityResponseCurve.set_choices(curve_type_texts,
                                              curve_type_values);
    addProp(eReleaseVelocityResponseCurve);
    addProp(eReleaseVelocityResponseDepth);
    addProp(eReleaseTriggerDecay);
    addProp(eCrossfade_in_start);
    addProp(eCrossfade_in_end);
    addProp(eCrossfade_out_start);
    addProp(eCrossfade_out_end);
    addProp(ePitchTrack);
    {
        char* choices[] = { "none", "effect4depth", "effect5depth", 0 };
        static const gig::dim_bypass_ctrl_t values[] = {
            gig::dim_bypass_ctrl_none,
            gig::dim_bypass_ctrl_94,
            gig::dim_bypass_ctrl_95
        };
        eDimensionBypass.set_choices(choices, values);
    }
    addProp(eDimensionBypass);
    addProp(ePan);
    addProp(eSelfMask);
    addProp(eAttenuationController);
    addProp(eInvertAttenuationController);
    addProp(eAttenuationControllerThreshold);
    addProp(eChannelOffset);
    addProp(eSustainDefeat);

    nextPage();
    addProp(eMSDecode);
    addProp(eSampleStartOffset);
    addProp(eUnityNote);
    addProp(eFineTune);
    addProp(eGain);
    addProp(eSampleLoops);
    nextPage();

    eEG1InfiniteSustain.signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::EG1InfiniteSustain_toggled) );
    eEG2InfiniteSustain.signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::EG2InfiniteSustain_toggled) );
    eEG1Controller.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::EG1Controller_changed) );
    eEG2Controller.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::EG2Controller_changed) );
    eLFO1Controller.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::LFO1Controller_changed) );
    eLFO2Controller.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::LFO2Controller_changed) );
    eLFO3Controller.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::LFO3Controller_changed) );
    eAttenuationController.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::AttenuationController_changed) );
    eVCFEnabled.signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::VCFEnabled_toggled) );
    eVCFCutoffController.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::VCFCutoffController_changed) );
    eVCFResonanceController.signal_changed().connect(
        sigc::mem_fun(*this, &MainWindow::VCFResonanceController_changed) );

    eCrossfade_in_start.signal_value_changed().connect(
        sigc::mem_fun(*this, &MainWindow::crossfade1_changed));
    eCrossfade_in_end.signal_value_changed().connect(
        sigc::mem_fun(*this, &MainWindow::crossfade2_changed));
    eCrossfade_out_start.signal_value_changed().connect(
        sigc::mem_fun(*this, &MainWindow::crossfade3_changed));
    eCrossfade_out_end.signal_value_changed().connect(
        sigc::mem_fun(*this, &MainWindow::crossfade4_changed));

    //m_Notebook.append_page(m_ScrolledWindow2, "Table");
    m_Notebook.append_page(*table[0], "EG1");
    m_Notebook.append_page(*table[1], "EG2");
    m_Notebook.append_page(*table[2], "EG3");
    m_Notebook.append_page(*table[3], "Velocity");
    m_Notebook.append_page(*table[4], "Misc");
    m_Notebook.set_size_request(400, 500);

    m_HPaned.add1(m_ScrolledWindow);
    m_HPaned.add2(m_Notebook);


    m_TreeViewNotebook.append_page(m_TreeViewSamples, "Samples");
    m_TreeViewNotebook.append_page(m_TreeView, "Instruments");


    actionGroup = Gtk::ActionGroup::create();

    actionGroup->add(Gtk::Action::create("MenuFile", _("_File")));
    actionGroup->add(Gtk::Action::create("New", Gtk::Stock::NEW),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_new));
    Glib::RefPtr<Gtk::Action> action =
        Gtk::Action::create("Open", Gtk::Stock::OPEN);
    action->property_label() = action->property_label() + "...";
    actionGroup->add(action,
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_open));
    actionGroup->add(Gtk::Action::create("Save", Gtk::Stock::SAVE),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_save));
    action = Gtk::Action::create("SaveAs", Gtk::Stock::SAVE_AS);
    action->property_label() = action->property_label() + "...";
    actionGroup->add(action,
                     *(new Gtk::AccelKey("<shift><control>s")),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_save_as)
        );
    actionGroup->add(Gtk::Action::create("Properties",
                                         Gtk::Stock::PROPERTIES),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_properties));
    actionGroup->add(Gtk::Action::create("InstrProperties",
                                         Gtk::Stock::PROPERTIES),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_file_properties));
    actionGroup->add(Gtk::Action::create("Quit", Gtk::Stock::QUIT),
                     sigc::mem_fun(
                         *this, &MainWindow::hide));
    actionGroup->add(Gtk::Action::create("MenuInstrument", _("_Instrument")));

    action = Gtk::Action::create("MenuHelp", Gtk::Stock::HELP);
    actionGroup->add(Gtk::Action::create("MenuHelp",
                                         action->property_label()));
#ifdef ABOUT_DIALOG
    actionGroup->add(Gtk::Action::create("About", Gtk::Stock::ABOUT),
                     sigc::mem_fun(
                         *this, &MainWindow::on_action_help_about));
#endif
    action = Gtk::Action::create("Remove", Gtk::Stock::REMOVE);
    actionGroup->add(action,
                     sigc::mem_fun(
                         *this, &MainWindow::hide));

    // sample right-click popup actions
    actionGroup->add(
        Gtk::Action::create("SampleProperties", Gtk::Stock::PROPERTIES),
        sigc::mem_fun(*this, &MainWindow::on_action_sample_properties)
    );
    actionGroup->add(
        Gtk::Action::create("AddGroup", _("Add _Group")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_group)
    );
    actionGroup->add(
        Gtk::Action::create("AddSample", _("Add _Sample")),
        sigc::mem_fun(*this, &MainWindow::on_action_add_sample)
    );
    actionGroup->add(
        Gtk::Action::create("RemoveSample", Gtk::Stock::REMOVE),
        sigc::mem_fun(*this, &MainWindow::on_action_remove_sample)
    );

    uiManager = Gtk::UIManager::create();
    uiManager->insert_action_group(actionGroup);
    // add_accel_group(uiManager->get_accel_group());

    Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='MenuFile'>"
        "      <menuitem action='New'/>"
        "      <menuitem action='Open'/>"
        "      <separator/>"
        "      <menuitem action='Save'/>"
        "      <menuitem action='SaveAs'/>"
        "      <separator/>"
        "      <menuitem action='Properties'/>"
        "      <separator/>"
        "      <menuitem action='Quit'/>"
        "    </menu>"
        "    <menu action='MenuInstrument'>"
        "    </menu>"
#ifdef ABOUT_DIALOG
        "    <menu action='MenuHelp'>"
        "      <menuitem action='About'/>"
        "    </menu>"
#endif
        "  </menubar>"
        "  <popup name='PopupMenu'>"
        "    <menuitem action='InstrProperties'/>"
        "    <menuitem action='Remove'/>"
        "  </popup>"
        "  <popup name='SamplePopupMenu'>"
        "    <menuitem action='SampleProperties'/>"
        "    <menuitem action='AddGroup'/>"
        "    <menuitem action='AddSample'/>"
        "    <separator/>"
        "    <menuitem action='RemoveSample'/>"
        "  </popup>"
        "</ui>";
    uiManager->add_ui_from_string(ui_info);

    popup_menu = dynamic_cast<Gtk::Menu*>(uiManager->get_widget("/PopupMenu"));

    Gtk::Widget* menuBar = uiManager->get_widget("/MenuBar");
    m_VBox.pack_start(*menuBar, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_HPaned);
    m_VBox.pack_start(m_RegionChooser, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_DimRegionChooser, Gtk::PACK_SHRINK);

    m_RegionChooser.signal_sel_changed().connect(
	sigc::mem_fun(*this, &MainWindow::region_changed) );
    m_DimRegionChooser.signal_sel_changed().connect(
	sigc::mem_fun(*this, &MainWindow::dimreg_changed) );


    // Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    // Add the TreeView's view columns:
    m_TreeView.append_column("Instrument", m_Columns.m_col_name);
    m_TreeView.set_headers_visible(false);

    // create samples treeview (including its data model)
    m_refSamplesTreeModel = Gtk::TreeStore::create(m_SamplesModel);
    m_TreeViewSamples.set_model(m_refSamplesTreeModel);
    m_TreeViewSamples.append_column("Samples", m_SamplesModel.m_col_name);
    m_TreeViewSamples.set_headers_visible(false);
    m_TreeViewSamples.signal_button_press_event().connect_notify(
        sigc::mem_fun(*this, &MainWindow::on_sample_treeview_button_release)
    );

    file = 0;

    show_all_children();
}

MainWindow::~MainWindow()
{
}

void MainWindow::region_changed()
{
    m_DimRegionChooser.set_region(m_RegionChooser.get_region());
}

void MainWindow::dimreg_changed()
{
    set_dim_region(m_DimRegionChooser.get_dimregion());
}

void MainWindow::on_sel_change()
{
    Glib::RefPtr<Gtk::TreeSelection> tree_sel_ref = m_TreeView.get_selection();

    Gtk::TreeModel::iterator it = tree_sel_ref->get_selected();
    if (it)
    {
	Gtk::TreeModel::Row row = *it;
	std::cout << row[m_Columns.m_col_name] << std::endl;

	if (row[m_Columns.m_col_instr])
            m_RegionChooser.set_instrument(row[m_Columns.m_col_instr]);
    }
}

void MainWindow::set_dim_region(gig::DimensionRegion* d)
{
    update_gui = false;
    wSample->set_text(d->pSample ? d->pSample->pInfo->Name.c_str() : "NULL");
    eVelocityUpperLimit.set_dimreg(d);
    eEG1PreAttack.set_dimreg(d);
    eEG1Attack.set_dimreg(d);
    eEG1Decay1.set_dimreg(d);
    eEG1Decay2.set_dimreg(d);
    eEG1InfiniteSustain.set_dimreg(d);
    eEG1Sustain.set_dimreg(d);
    eEG1Release.set_dimreg(d);
    eEG1Hold.set_dimreg(d);
    eEG1Controller.set_dimreg(d);
    eEG1ControllerInvert.set_dimreg(d);
    eEG1ControllerAttackInfluence.set_dimreg(d);
    eEG1ControllerDecayInfluence.set_dimreg(d);
    eEG1ControllerReleaseInfluence.set_dimreg(d);
    eLFO1Frequency.set_dimreg(d);
    eLFO1InternalDepth.set_dimreg(d);
    eLFO1ControlDepth.set_dimreg(d);
    eLFO1Controller.set_dimreg(d);
    eLFO1FlipPhase.set_dimreg(d);
    eLFO1Sync.set_dimreg(d);
    eEG2PreAttack.set_dimreg(d);
    eEG2Attack.set_dimreg(d);
    eEG2Decay1.set_dimreg(d);
    eEG2Decay2.set_dimreg(d);
    eEG2InfiniteSustain.set_dimreg(d);
    eEG2Sustain.set_dimreg(d);
    eEG2Release.set_dimreg(d);
    eEG2Controller.set_dimreg(d);
    eEG2ControllerInvert.set_dimreg(d);
    eEG2ControllerAttackInfluence.set_dimreg(d);
    eEG2ControllerDecayInfluence.set_dimreg(d);
    eEG2ControllerReleaseInfluence.set_dimreg(d);
    eLFO2Frequency.set_dimreg(d);
    eLFO2InternalDepth.set_dimreg(d);
    eLFO2ControlDepth.set_dimreg(d);
    eLFO2Controller.set_dimreg(d);
    eLFO2FlipPhase.set_dimreg(d);
    eLFO2Sync.set_dimreg(d);
    eEG3Attack.set_dimreg(d);
    eEG3Depth.set_dimreg(d);
    eLFO3Frequency.set_dimreg(d);
    eLFO3InternalDepth.set_dimreg(d);
    eLFO3ControlDepth.set_dimreg(d);
    eLFO3Controller.set_dimreg(d);
    eLFO3Sync.set_dimreg(d);
    eVCFEnabled.set_dimreg(d);
    eVCFType.set_dimreg(d);
    eVCFCutoffController.set_dimreg(d);
    eVCFCutoffControllerInvert.set_dimreg(d);
    eVCFCutoff.set_dimreg(d);
    eVCFVelocityCurve.set_dimreg(d);
    eVCFVelocityScale.set_dimreg(d);
    eVCFVelocityDynamicRange.set_dimreg(d);
    eVCFResonance.set_dimreg(d);
    eVCFResonanceDynamic.set_dimreg(d);
    eVCFResonanceController.set_dimreg(d);
    eVCFKeyboardTracking.set_dimreg(d);
    eVCFKeyboardTrackingBreakpoint.set_dimreg(d);
    eVelocityResponseCurve.set_dimreg(d);
    eVelocityResponseDepth.set_dimreg(d);
    eVelocityResponseCurveScaling.set_dimreg(d);
    eReleaseVelocityResponseCurve.set_dimreg(d);
    eReleaseVelocityResponseDepth.set_dimreg(d);
    eReleaseTriggerDecay.set_dimreg(d);
    eCrossfade_in_start.set_dimreg(d);
    eCrossfade_in_end.set_dimreg(d);
    eCrossfade_out_start.set_dimreg(d);
    eCrossfade_out_end.set_dimreg(d);
    ePitchTrack.set_dimreg(d);
    eDimensionBypass.set_dimreg(d);
    ePan.set_dimreg(d);
    eSelfMask.set_dimreg(d);
    eAttenuationController.set_dimreg(d);
    eInvertAttenuationController.set_dimreg(d);
    eAttenuationControllerThreshold.set_dimreg(d);
    eChannelOffset.set_dimreg(d);
    eSustainDefeat.set_dimreg(d);
    eMSDecode.set_dimreg(d);
    eSampleStartOffset.set_dimreg(d);
    eUnityNote.set_dimreg(d);
    eFineTune.set_dimreg(d);
    eGain.set_dimreg(d);
    eSampleLoops.set_dimreg(d);

    VCFEnabled_toggled();

    update_gui = true;
}

void MainWindow::VCFEnabled_toggled()
{
    bool sensitive = eVCFEnabled.get_active();
    eVCFType.set_sensitive(sensitive);
    eVCFCutoffController.set_sensitive(sensitive);
    eVCFVelocityCurve.set_sensitive(sensitive);
    eVCFVelocityScale.set_sensitive(sensitive);
    eVCFVelocityDynamicRange.set_sensitive(sensitive);
    eVCFResonance.set_sensitive(sensitive);
    eVCFResonanceController.set_sensitive(sensitive);
    eVCFKeyboardTracking.set_sensitive(sensitive);
    eVCFKeyboardTrackingBreakpoint.set_sensitive(sensitive);
    eEG2PreAttack.set_sensitive(sensitive);
    eEG2Attack.set_sensitive(sensitive);
    eEG2Decay1.set_sensitive(sensitive);
    eEG2InfiniteSustain.set_sensitive(sensitive);
    eEG2Sustain.set_sensitive(sensitive);
    eEG2Release.set_sensitive(sensitive);
    eEG2Controller.set_sensitive(sensitive);
    eEG2ControllerAttackInfluence.set_sensitive(sensitive);
    eEG2ControllerDecayInfluence.set_sensitive(sensitive);
    eEG2ControllerReleaseInfluence.set_sensitive(sensitive);
    eLFO2Frequency.set_sensitive(sensitive);
    eLFO2InternalDepth.set_sensitive(sensitive);
    eLFO2ControlDepth.set_sensitive(sensitive);
    eLFO2Controller.set_sensitive(sensitive);
    eLFO2FlipPhase.set_sensitive(sensitive);
    eLFO2Sync.set_sensitive(sensitive);
    if (sensitive) {
        VCFCutoffController_changed();
        VCFResonanceController_changed();
        EG2InfiniteSustain_toggled();
        EG2Controller_changed();
        LFO2Controller_changed();
    } else {
        eVCFCutoffControllerInvert.set_sensitive(false);
        eVCFCutoff.set_sensitive(false);
        eVCFResonanceDynamic.set_sensitive(false);
        eVCFResonance.set_sensitive(false);
        eEG2Decay2.set_sensitive(false);
        eEG2ControllerInvert.set_sensitive(false);
        eLFO2InternalDepth.set_sensitive(false);
        eLFO2ControlDepth.set_sensitive(false);
    }
}

void MainWindow::VCFCutoffController_changed()
{
    int rowno = eVCFCutoffController.get_active_row_number();
    bool hasController = rowno != 0 && rowno != 1;

    eVCFCutoffControllerInvert.set_sensitive(hasController);
    eVCFCutoff.set_sensitive(!hasController);
    eVCFResonanceDynamic.set_sensitive(!hasController);
    eVCFVelocityScale.label.set_text(hasController ? "MinimumCutoff:" :
                                     "VelocityScale:");
}

void MainWindow::VCFResonanceController_changed()
{
    bool hasController = eVCFResonanceController.get_active_row_number() != 0;
    eVCFResonance.set_sensitive(!hasController);
}

void MainWindow::EG1InfiniteSustain_toggled()
{
    bool infSus = eEG1InfiniteSustain.get_active();
    eEG1Decay2.set_sensitive(!infSus);
}

void MainWindow::EG2InfiniteSustain_toggled()
{
    bool infSus = eEG2InfiniteSustain.get_active();
    eEG2Decay2.set_sensitive(!infSus);
}

void MainWindow::EG1Controller_changed()
{
    bool hasController = eEG1Controller.get_active_row_number() != 0;
    eEG1ControllerInvert.set_sensitive(hasController);
}

void MainWindow::EG2Controller_changed()
{
    bool hasController = eEG2Controller.get_active_row_number() != 0;
    eEG2ControllerInvert.set_sensitive(hasController);
}

void MainWindow::AttenuationController_changed()
{
    bool hasController = eAttenuationController.get_active_row_number() != 0;
    eInvertAttenuationController.set_sensitive(hasController);
}

void MainWindow::LFO1Controller_changed()
{
    int rowno = eLFO1Controller.get_active_row_number();
    eLFO1ControlDepth.set_sensitive(rowno != 0);
    eLFO1InternalDepth.set_sensitive(rowno != 1 && rowno != 2);
}

void MainWindow::LFO2Controller_changed()
{
    int rowno = eLFO2Controller.get_active_row_number();
    eLFO2ControlDepth.set_sensitive(rowno != 0);
    eLFO2InternalDepth.set_sensitive(rowno != 1 && rowno != 2);
}

void MainWindow::LFO3Controller_changed()
{
    int rowno = eLFO3Controller.get_active_row_number();
    eLFO3ControlDepth.set_sensitive(rowno != 0);
    eLFO3InternalDepth.set_sensitive(rowno != 1 && rowno != 2);
}

void MainWindow::crossfade1_changed()
{
    double c1 = eCrossfade_in_start.get_value();
    double c2 = eCrossfade_in_end.get_value();
    if (c1 > c2) eCrossfade_in_end.set_value(c1);
}

void MainWindow::crossfade2_changed()
{
    double c1 = eCrossfade_in_start.get_value();
    double c2 = eCrossfade_in_end.get_value();
    double c3 = eCrossfade_out_start.get_value();

    if (c2 < c1) eCrossfade_in_start.set_value(c2);
    if (c2 > c3) eCrossfade_out_start.set_value(c2);
}

void MainWindow::crossfade3_changed()
{
    double c2 = eCrossfade_in_end.get_value();
    double c3 = eCrossfade_out_start.get_value();
    double c4 = eCrossfade_out_end.get_value();

    if (c3 < c2) eCrossfade_in_end.set_value(c3);
    if (c3 > c4) eCrossfade_out_end.set_value(c3);
}

void MainWindow::crossfade4_changed()
{
    double c3 = eCrossfade_out_start.get_value();
    double c4 = eCrossfade_out_end.get_value();

    if (c4 < c3) eCrossfade_out_start.set_value(c4);
}

void loader_progress_callback(gig::progress_t* progress)
{
    Loader* loader = static_cast<Loader*>(progress->custom);
    loader->progress_callback(progress->factor);
}

void Loader::progress_callback(float fraction)
{
    {
        Glib::Mutex::Lock lock(progressMutex);
        progress = fraction;
    }
    progress_dispatcher();
}

void Loader::thread_function()
{
    printf("thread_function self=%x\n", Glib::Thread::self());
    printf("Start %s\n", filename);
    RIFF::File* riff = new RIFF::File(filename);
    gig = new gig::File(riff);
    gig::progress_t progress;
    progress.callback = loader_progress_callback;
    progress.custom = this;

    gig->GetInstrument(0, &progress);
    printf("End\n");
    finished_dispatcher();
}

Loader::Loader(const char* filename)
    : thread(0), filename(filename)
{
}

void Loader::launch()
{
    thread = Glib::Thread::create(sigc::mem_fun(*this, &Loader::thread_function), true);
    printf("launch thread=%x\n", thread);
}

float Loader::get_progress()
{
    float res;
    {
        Glib::Mutex::Lock lock(progressMutex);
        res = progress;
    }
    return res;
}

Glib::Dispatcher& Loader::signal_progress()
{
    return progress_dispatcher;
}

Glib::Dispatcher& Loader::signal_finished()
{
    return finished_dispatcher;
}

LoadDialog::LoadDialog()
{
    get_vbox()->pack_start(progressBar);
    show_all_children();
}

void MainWindow::on_action_file_new()
{
}

void MainWindow::on_action_file_open()
{
    Gtk::FileChooserDialog dialog(*this, _("Open file"));
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    Gtk::FileFilter filter;
    filter.add_pattern("*.gig");
    dialog.set_filter(filter);
    if (dialog.run() == Gtk::RESPONSE_OK) {
        printf("filename=%s\n", dialog.get_filename().c_str());

        // remove all entries from "Instrument" menu
        Gtk::MenuItem* instrument_menu =
            dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuInstrument"));
        instrument_menu->hide();
        for (int i = 0; i < instrument_menu->get_submenu()->items().size(); i++) {
            delete &instrument_menu->get_submenu()->items()[i];
        }
        instrument_menu->get_submenu()->items().clear();

        m_refTreeModel->clear();
        m_refSamplesTreeModel->clear();
        if (file) delete file;

        // getInfo(dialog.get_filename().c_str(), *this);

        printf("on_action_file_open self=%x\n", Glib::Thread::self());
        load_dialog = new LoadDialog(); // Gtk::Dialog("Loading...", *this, true);
        load_dialog->show_all();
        loader = new Loader(strdup(dialog.get_filename().c_str()));
        loader->signal_progress().connect(
            sigc::mem_fun(*this, &MainWindow::on_loader_progress));
        loader->signal_finished().connect(
            sigc::mem_fun(*this, &MainWindow::on_loader_finished));

        loader->launch();
    }
}

void MainWindow::on_loader_progress()
{
    load_dialog->set_fraction(loader->get_progress());
}

void MainWindow::on_loader_finished()
{
    printf("Loader finished!\n");
    printf("on_loader_finished self=%x\n", Glib::Thread::self());
    load_gig(loader->gig, loader->filename);


    Glib::RefPtr<Gtk::TreeSelection> tree_sel_ref = m_TreeView.get_selection();
    tree_sel_ref->select(Gtk::TreePath("0"));

    load_dialog->hide();
}

void MainWindow::on_action_file_save()
{
}

void MainWindow::on_action_file_save_as()
{
    Gtk::FileChooserDialog dialog(*this, "Open", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
    Gtk::FileFilter filter;
    filter.add_pattern("*.gig");
    dialog.set_filter(filter);
    if (dialog.run() == Gtk::RESPONSE_OK) {
        printf("filename=%s\n", dialog.get_filename().c_str());
        file->Save(dialog.get_filename());
    }
}

void MainWindow::on_action_file_properties()
{
    propDialog.show();
    propDialog.deiconify();
}

void MainWindow::on_action_help_about()
{
#ifdef ABOUT_DIALOG
    Gtk::AboutDialog dialog;
    dialog.set_version(VERSION);
    dialog.run();
#endif
}

PropDialog::PropDialog()
    : table(2,1)
{
    table.set_col_spacings(5);
    char* propLabels[] = {
        "Name:",
        "CreationDate:",
        "Comments:", // TODO: multiline
        "Product:",
        "Copyright:",
        "Artists:",
        "Genre:",
        "Keywords:",
        "Engineer:",
        "Technician:",
        "Software:", // TODO: readonly
        "Medium:",
        "Source:",
        "SourceForm:",
        "Commissioned:",
        "Subject:"
    };
    for (int i = 0 ; i < sizeof(propLabels) / sizeof(char*) ; i++) {
        label[i].set_text(propLabels[i]);
        label[i].set_alignment(Gtk::ALIGN_LEFT);
        table.attach(label[i], 0, 1, i, i + 1, Gtk::FILL, Gtk::SHRINK);
        table.attach(entry[i], 1, 2, i, i + 1, Gtk::FILL | Gtk::EXPAND,
                     Gtk::SHRINK);
    }

    add(table);
    // add_button(Gtk::Stock::CANCEL, 0);
    // add_button(Gtk::Stock::OK, 1);
    show_all_children();
}

void PropDialog::set_info(DLS::Info* info)
{
    entry[0].set_text(info->Name);
    entry[1].set_text(info->CreationDate);
    entry[2].set_text(Glib::convert(info->Comments, "UTF-8", "ISO-8859-1"));
    entry[3].set_text(info->Product);
    entry[4].set_text(info->Copyright);
    entry[5].set_text(info->Artists);
    entry[6].set_text(info->Genre);
    entry[7].set_text(info->Keywords);
    entry[8].set_text(info->Engineer);
    entry[9].set_text(info->Technician);
    entry[10].set_text(info->Software);
    entry[11].set_text(info->Medium);
    entry[12].set_text(info->Source);
    entry[13].set_text(info->SourceForm);
    entry[14].set_text(info->Commissioned);
    entry[15].set_text(info->Subject);
}


InstrumentProps::InstrumentProps()
    : table(2,1),
      quitButton(Gtk::Stock::CLOSE)
{
    table.set_col_spacings(5);
    char* propLabels[] = {
        "Name:",
        "IsDrum:",
        "MIDIBank:",
        "MIDIProgram:",
        "Attenuation:",
        "EffectSend:",
        "FineTune:",
        "PitchbendRange:",
        "PianoReleaseMode:",
        "DimensionKeyRange:",
    };
    int entryIdx = 0, checkIdx = 0;
    for (int i = 0 ; i < sizeof(propLabels) / sizeof(char*) ; i++) {
        label[i].set_text(propLabels[i]);
        label[i].set_alignment(Gtk::ALIGN_LEFT);
        table.attach(label[i], 0, 1, i, i + 1, Gtk::FILL, Gtk::SHRINK);
        if (i == 1 || i == 8)
            table.attach(check[checkIdx++], 1, 2, i, i + 1,
                         Gtk::FILL | Gtk::EXPAND, Gtk::SHRINK);
        else
            table.attach(entry[entryIdx++], 1, 2, i, i + 1,
                         Gtk::FILL | Gtk::EXPAND, Gtk::SHRINK);
    }

    // vbox { table buttonBox { quitButton } }

    //get_vbox()->pack_start(table);
    // set_border_width(6);
    add(vbox);
    table.set_border_width(2);
    vbox.pack_start(table);
    table.show();
    vbox.pack_start(buttonBox);
    buttonBox.set_layout(Gtk::BUTTONBOX_END);
    buttonBox.set_border_width(5);
    buttonBox.show();
    buttonBox.pack_start(quitButton);
    quitButton.set_flags(Gtk::CAN_DEFAULT);
    quitButton.grab_focus();

    quitButton.signal_clicked().connect(
	sigc::mem_fun(*this, &InstrumentProps::hide));

    // quitButton.grab_default();
    quitButton.show();
    // add(table);
    vbox.show();
    show_all_children();
}


void InstrumentProps::set_instrument(gig::Instrument* instrument)
{
    char buf[100];

    int entryIdx = 0, checkIdx = 0;
    entry[entryIdx++].set_text(instrument->pInfo->Name);
    check[checkIdx++].set_active(instrument->IsDrum);
    sprintf(buf, "%d", instrument->MIDIBank);
    entry[entryIdx++].set_text(buf);
    sprintf(buf, "%d", instrument->MIDIProgram);
    entry[entryIdx++].set_text(buf);
    sprintf(buf, "%d", instrument->Attenuation);
    entry[entryIdx++].set_text(buf);
    sprintf(buf, "%d", instrument->EffectSend);
    entry[entryIdx++].set_text(buf);
    sprintf(buf, "%d", instrument->FineTune);
    entry[entryIdx++].set_text(buf);
    sprintf(buf, "%d", instrument->PitchbendRange);
    entry[entryIdx++].set_text(buf);
    check[checkIdx++].set_active(instrument->PianoReleaseMode);
    sprintf(buf, "%s%d (%d)..%s%d (%d)",
            notes[instrument->DimensionKeyRange.low % 12],
            instrument->DimensionKeyRange.low / 12 - 1,
            instrument->DimensionKeyRange.low,
            notes[instrument->DimensionKeyRange.high % 12],
            instrument->DimensionKeyRange.high / 12 - 1,
            instrument->DimensionKeyRange.high);
    entry[entryIdx].set_text(buf);
}

void MainWindow::getInfo(const char *filename)
{
    RIFF::File* riff = new RIFF::File(filename);
    gig::File* gig = new gig::File(riff);

    load_gig(gig, filename);
}

void MainWindow::load_gig(gig::File* gig, const char* filename)
{
    file = gig;

    const char *basename = strrchr(filename, '/');
    basename = basename ? basename + 1 : filename;

    set_title(basename);

    propDialog.set_info(gig->pInfo);

    Gtk::MenuItem* instrument_menu =
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/MenuBar/MenuInstrument"));

    int instrument_index = 0;
    Gtk::RadioMenuItem::Group instrument_group;
    for (gig::Instrument* instrument = gig->GetFirstInstrument() ; instrument ;
	 instrument = gig->GetNextInstrument()) {
        Gtk::TreeModel::iterator iter = m_refTreeModel->append();
	Gtk::TreeModel::Row row = *iter;
	row[m_Columns.m_col_name] = instrument->pInfo->Name.c_str();
	row[m_Columns.m_col_instr] = instrument;
        // create a menu item for this instrument
        Gtk::RadioMenuItem* item= new Gtk::RadioMenuItem(instrument_group, instrument->pInfo->Name.c_str());
        instrument_menu->get_submenu()->append(*item);
        item->signal_activate().connect(
            sigc::bind(
                sigc::mem_fun(*this, &MainWindow::on_instrument_selection_change),
                instrument_index
            )
        );
        instrument_index++;
    }
    instrument_menu->show();
    instrument_menu->get_submenu()->show_all_children();

    for (gig::Group* group = gig->GetFirstGroup(); group; group = gig->GetNextGroup()) {
        Gtk::TreeModel::iterator iterGroup = m_refSamplesTreeModel->append();
        Gtk::TreeModel::Row rowGroup = *iterGroup;
        rowGroup[m_SamplesModel.m_col_name]   = group->Name.c_str();
        rowGroup[m_SamplesModel.m_col_group]  = group;
        rowGroup[m_SamplesModel.m_col_sample] = NULL;
        for (gig::Sample* sample = group->GetFirstSample(); sample; sample = group->GetNextSample()) {
            Gtk::TreeModel::iterator iterSample = m_refSamplesTreeModel->append(rowGroup.children());
            Gtk::TreeModel::Row rowSample = *iterSample;
            rowSample[m_SamplesModel.m_col_name]   = sample->pInfo->Name.c_str();
            rowSample[m_SamplesModel.m_col_sample] = sample;
            rowSample[m_SamplesModel.m_col_group]  = NULL;
        }
    }
}

void MainWindow::on_button_release(GdkEventButton* button)
{
    if (button->type == GDK_2BUTTON_PRESS) {
        Glib::RefPtr<Gtk::TreeSelection> tree_sel_ref = m_TreeView.get_selection();
        Gtk::TreeModel::iterator it = tree_sel_ref->get_selected();
        if (it)
        {
            Gtk::TreeModel::Row row = *it;
            if (row[m_Columns.m_col_instr])
            {
                instrumentProps.set_instrument(row[m_Columns.m_col_instr]);
                instrumentProps.show();
                instrumentProps.deiconify();
            }
        }
    } else if (button->type == GDK_BUTTON_PRESS && button->button == 3) {
        popup_menu->popup(button->button, button->time);
    }
}

void MainWindow::on_instrument_selection_change(int index) {
    m_RegionChooser.set_instrument(file->GetInstrument(index));
}

void MainWindow::on_sample_treeview_button_release(GdkEventButton* button) {
    if (button->type == GDK_BUTTON_PRESS && button->button == 3) {
        Gtk::Menu* sample_popup =
            dynamic_cast<Gtk::Menu*>(uiManager->get_widget("/SamplePopupMenu"));
        // update enabled/disabled state of sample popup items
        Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewSamples.get_selection();
        Gtk::TreeModel::iterator it = sel->get_selected();
        bool group_selected  = false;
        bool sample_selected = false;
        if (it) {
            Gtk::TreeModel::Row row = *it;
            group_selected  = row[m_SamplesModel.m_col_group];
            sample_selected = row[m_SamplesModel.m_col_sample];
        }
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/SampleProperties"))->set_sensitive(group_selected || sample_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/AddSample"))->set_sensitive(group_selected || sample_selected);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/AddGroup"))->set_sensitive(file);
        dynamic_cast<Gtk::MenuItem*>(uiManager->get_widget("/SamplePopupMenu/RemoveSample"))->set_sensitive(group_selected || sample_selected);
        // show sample popup
        sample_popup->popup(button->button, button->time);
    }
}

void MainWindow::on_action_sample_properties() {
     //TODO: show a dialog where the selected sample's properties can be edited
}

void MainWindow::on_action_add_group() {
    static int __sample_indexer = 0;
    if (!file) return;
    gig::Group* group = file->AddGroup();
    group->Name = "Unnamed Group";
    if (__sample_indexer) group->Name += " " + ToString(__sample_indexer);
    __sample_indexer++;
    // update sample tree view
    Gtk::TreeModel::iterator iterGroup = m_refSamplesTreeModel->append();
    Gtk::TreeModel::Row rowGroup = *iterGroup;
    rowGroup[m_SamplesModel.m_col_name] = group->Name.c_str();
    rowGroup[m_SamplesModel.m_col_sample] = NULL;
    rowGroup[m_SamplesModel.m_col_group] = group;
}

void MainWindow::on_action_add_sample() {
    //TODO: open browse for file dialog for adding new samples
}

void MainWindow::on_action_remove_sample() {
    if (!file) return;
    Glib::RefPtr<Gtk::TreeSelection> sel = m_TreeViewSamples.get_selection();
    Gtk::TreeModel::iterator it = sel->get_selected();
    if (it) {
        Gtk::TreeModel::Row row = *it;
        gig::Group* group   = row[m_SamplesModel.m_col_group];
        gig::Sample* sample = row[m_SamplesModel.m_col_sample];
        try {
            // remove group or sample from the gig file
            if (group) {
                file->DeleteGroup(group);
            } else if (sample) {
                file->DeleteSample(sample);
            }
            // remove respective row(s) from samples tree view
            m_refSamplesTreeModel->erase(it);
        } catch (RIFF::Exception e) {
            Gtk::MessageDialog msg(*this, e.Message.c_str(), false, Gtk::MESSAGE_ERROR);
            msg.run();
        }
    }
}
