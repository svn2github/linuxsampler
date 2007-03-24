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

#include "dimregionedit.h"

bool update_gui;

namespace {
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
}

DimRegionEdit::DimRegionEdit() :
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
    eGainPlus6("Gain +6dB", eGain),
    eSampleLoops("SampleLoops", &access_SampleLoops, 0, 1)
{
    for (int i = 0 ; i < 5 ; i++) {
        table[i] = new Gtk::Table(3, 1);
        table[i]->set_col_spacings(5);
    }

    pageno = 0;
    rowno = 0;
    firstRowInBlock = 0;

    addString("Sample", lSample, wSample);
    //TODO: the following would break drag&drop:   wSample->property_editable().set_value(false);  or this:    wSample->set_editable(false);
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
    addProp(eGainPlus6);
    addProp(eSampleLoops);
    nextPage();

    eEG1InfiniteSustain.signal_toggled().connect(
        sigc::mem_fun(*this, &DimRegionEdit::EG1InfiniteSustain_toggled) );
    eEG2InfiniteSustain.signal_toggled().connect(
        sigc::mem_fun(*this, &DimRegionEdit::EG2InfiniteSustain_toggled) );
    eEG1Controller.signal_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::EG1Controller_changed) );
    eEG2Controller.signal_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::EG2Controller_changed) );
    eLFO1Controller.signal_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::LFO1Controller_changed) );
    eLFO2Controller.signal_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::LFO2Controller_changed) );
    eLFO3Controller.signal_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::LFO3Controller_changed) );
    eAttenuationController.signal_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::AttenuationController_changed) );
    eVCFEnabled.signal_toggled().connect(
        sigc::mem_fun(*this, &DimRegionEdit::VCFEnabled_toggled) );
    eVCFCutoffController.signal_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::VCFCutoffController_changed) );
    eVCFResonanceController.signal_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::VCFResonanceController_changed) );

    eCrossfade_in_start.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::crossfade1_changed));
    eCrossfade_in_end.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::crossfade2_changed));
    eCrossfade_out_start.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::crossfade3_changed));
    eCrossfade_out_end.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::crossfade4_changed));

    append_page(*table[0], "EG1");
    append_page(*table[1], "EG2");
    append_page(*table[2], "EG3");
    append_page(*table[3], "Velocity");
    append_page(*table[4], "Misc");
}

DimRegionEdit::~DimRegionEdit()
{
}

void DimRegionEdit::addString(char* labelText, Gtk::Label*& label,
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

void DimRegionEdit::addHeader(char* text)
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

void DimRegionEdit::nextPage()
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

void DimRegionEdit::addProp(LabelWidget& prop)
{
    table[pageno]->attach(prop.label, 1, 2, rowno, rowno + 1,
                          Gtk::FILL, Gtk::SHRINK);
    table[pageno]->attach(prop.widget, 2, 3, rowno, rowno + 1,
                          Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);
    rowno++;
}


void DimRegionEdit::set_dim_region(gig::DimensionRegion* d)
{
    set_sensitive(d);
    if (!d) return;

    update_gui = false;
    wSample->set_text(d->pSample ? d->pSample->pInfo->Name.c_str() : "NULL");
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
    eGainPlus6.set_dimreg(d);
    eSampleLoops.set_dimreg(d);

    VCFEnabled_toggled();

    update_gui = true;
}

void DimRegionEdit::VCFEnabled_toggled()
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

void DimRegionEdit::VCFCutoffController_changed()
{
    int rowno = eVCFCutoffController.get_active_row_number();
    bool hasController = rowno != 0 && rowno != 1;

    eVCFCutoffControllerInvert.set_sensitive(hasController);
    eVCFCutoff.set_sensitive(!hasController);
    eVCFResonanceDynamic.set_sensitive(!hasController);
    eVCFVelocityScale.label.set_text(hasController ? "MinimumCutoff:" :
                                     "VelocityScale:");
}

void DimRegionEdit::VCFResonanceController_changed()
{
    bool hasController = eVCFResonanceController.get_active_row_number() != 0;
    eVCFResonance.set_sensitive(!hasController);
}

void DimRegionEdit::EG1InfiniteSustain_toggled()
{
    bool infSus = eEG1InfiniteSustain.get_active();
    eEG1Decay2.set_sensitive(!infSus);
}

void DimRegionEdit::EG2InfiniteSustain_toggled()
{
    bool infSus = eEG2InfiniteSustain.get_active();
    eEG2Decay2.set_sensitive(!infSus);
}

void DimRegionEdit::EG1Controller_changed()
{
    bool hasController = eEG1Controller.get_active_row_number() != 0;
    eEG1ControllerInvert.set_sensitive(hasController);
}

void DimRegionEdit::EG2Controller_changed()
{
    bool hasController = eEG2Controller.get_active_row_number() != 0;
    eEG2ControllerInvert.set_sensitive(hasController);
}

void DimRegionEdit::AttenuationController_changed()
{
    bool hasController = eAttenuationController.get_active_row_number() != 0;
    eInvertAttenuationController.set_sensitive(hasController);
}

void DimRegionEdit::LFO1Controller_changed()
{
    int rowno = eLFO1Controller.get_active_row_number();
    eLFO1ControlDepth.set_sensitive(rowno != 0);
    eLFO1InternalDepth.set_sensitive(rowno != 1 && rowno != 2);
}

void DimRegionEdit::LFO2Controller_changed()
{
    int rowno = eLFO2Controller.get_active_row_number();
    eLFO2ControlDepth.set_sensitive(rowno != 0);
    eLFO2InternalDepth.set_sensitive(rowno != 1 && rowno != 2);
}

void DimRegionEdit::LFO3Controller_changed()
{
    int rowno = eLFO3Controller.get_active_row_number();
    eLFO3ControlDepth.set_sensitive(rowno != 0);
    eLFO3InternalDepth.set_sensitive(rowno != 1 && rowno != 2);
}

void DimRegionEdit::crossfade1_changed()
{
    double c1 = eCrossfade_in_start.get_value();
    double c2 = eCrossfade_in_end.get_value();
    if (c1 > c2) eCrossfade_in_end.set_value(c1);
}

void DimRegionEdit::crossfade2_changed()
{
    double c1 = eCrossfade_in_start.get_value();
    double c2 = eCrossfade_in_end.get_value();
    double c3 = eCrossfade_out_start.get_value();

    if (c2 < c1) eCrossfade_in_start.set_value(c2);
    if (c2 > c3) eCrossfade_out_start.set_value(c2);
}

void DimRegionEdit::crossfade3_changed()
{
    double c2 = eCrossfade_in_end.get_value();
    double c3 = eCrossfade_out_start.get_value();
    double c4 = eCrossfade_out_end.get_value();

    if (c3 < c2) eCrossfade_in_end.set_value(c3);
    if (c3 > c4) eCrossfade_out_end.set_value(c3);
}

void DimRegionEdit::crossfade4_changed()
{
    double c3 = eCrossfade_out_start.get_value();
    double c4 = eCrossfade_out_end.get_value();

    if (c4 < c3) eCrossfade_out_start.set_value(c4);
}
