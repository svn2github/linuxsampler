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

DimRegionEdit::DimRegionEdit() :
    eEG1PreAttack("PreAttack", 0, 100, 2),
    eEG1Attack("Attack", 0, 60, 3),
    eEG1Decay1("Decay1", 0.005, 60, 3),
    eEG1Decay2("Decay2", 0, 60, 3),
    eEG1InfiniteSustain("InfiniteSustain"),
    eEG1Sustain("Sustain", 0, 100, 2),
    eEG1Release("Release", 0, 60, 3),
    eEG1Hold("Hold"),
    eEG1Controller("Controller"),
    eEG1ControllerInvert("ControllerInvert"),
    eEG1ControllerAttackInfluence("ControllerAttackInfluence", 0, 3),
    eEG1ControllerDecayInfluence("ControllerDecayInfluence", 0, 3),
    eEG1ControllerReleaseInfluence("ControllerReleaseInfluence", 0, 3),
    eLFO1Frequency("Frequency", 0.1, 10, 2),
    eLFO1InternalDepth("InternalDepth", 0, 1200),
    eLFO1ControlDepth("ControlDepth", 0, 1200),
    eLFO1Controller("Controller"),
    eLFO1FlipPhase("FlipPhase"),
    eLFO1Sync("Sync"),
    eEG2PreAttack("PreAttack", 0, 100, 2),
    eEG2Attack("Attack", 0, 60, 3),
    eEG2Decay1("Decay1", 0.005, 60, 3),
    eEG2Decay2("Decay2", 0, 60, 3),
    eEG2InfiniteSustain("InfiniteSustain"),
    eEG2Sustain("Sustain", 0, 100, 2),
    eEG2Release("Release", 0, 60, 3),
    eEG2Controller("Controller"),
    eEG2ControllerInvert("ControllerInvert"),
    eEG2ControllerAttackInfluence("ControllerAttackInfluence", 0, 3),
    eEG2ControllerDecayInfluence("ControllerDecayInfluence", 0, 3),
    eEG2ControllerReleaseInfluence("ControllerReleaseInfluence", 0, 3),
    eLFO2Frequency("Frequency", 0.1, 10, 2),
    eLFO2InternalDepth("InternalDepth", 0, 1200),
    eLFO2ControlDepth("ControlDepth", 0, 1200),
    eLFO2Controller("Controller"),
    eLFO2FlipPhase("FlipPhase"),
    eLFO2Sync("Sync"),
    eEG3Attack("Attack", 0, 10, 3),
    eEG3Depth("Depth", -1200, 1200),
    eLFO3Frequency("Frequency", 0.1, 10, 2),
    eLFO3InternalDepth("InternalDepth", 0, 1200),
    eLFO3ControlDepth("ControlDepth", 0, 1200),
    eLFO3Controller("Controller"),
    eLFO3Sync("Sync"),
    eVCFEnabled("Enabled"),
    eVCFType("Type"),
    eVCFCutoffController("CutoffController"),
    eVCFCutoffControllerInvert("CutoffControllerInvert"),
    eVCFCutoff("Cutoff"),
    eVCFVelocityCurve("VelocityCurve"),
    eVCFVelocityScale("VelocityScale"),
    eVCFVelocityDynamicRange("VelocityDynamicRange", 0, 4),
    eVCFResonance("Resonance"),
    eVCFResonanceDynamic("ResonanceDynamic"),
    eVCFResonanceController("ResonanceController"),
    eVCFKeyboardTracking("KeyboardTracking"),
    eVCFKeyboardTrackingBreakpoint("KeyboardTrackingBreakpoint"),
    eVelocityResponseCurve("VelocityResponseCurve"),
    eVelocityResponseDepth("VelocityResponseDepth", 0, 4),
    eVelocityResponseCurveScaling("VelocityResponseCurveScaling"),
    eReleaseVelocityResponseCurve("ReleaseVelocityResponseCurve"),
    eReleaseVelocityResponseDepth("ReleaseVelocityResponseDepth", 0, 4),
    eReleaseTriggerDecay("ReleaseTriggerDecay", 0, 8),
    eCrossfade_in_start("Crossfade.in_start"),
    eCrossfade_in_end("Crossfade.in_end"),
    eCrossfade_out_start("Crossfade.out_start"),
    eCrossfade_out_end("Crossfade.out_end"),
    ePitchTrack("PitchTrack"),
    eDimensionBypass("DimensionBypass"),
    ePan("Pan", -64, 63),
    eSelfMask("SelfMask"),
    eAttenuationController("AttenuationController"),
    eInvertAttenuationController("InvertAttenuationController"),
    eAttenuationControllerThreshold("AttenuationControllerThreshold"),
    eChannelOffset("ChannelOffset", 0, 9),
    eSustainDefeat("SustainDefeat"),
    eMSDecode("MSDecode"),
    eSampleStartOffset("SampleStartOffset", 0, 2000),
    eUnityNote("UnityNote"),
    eFineTune("FineTune", -49, 50),
    eGain("Gain", -96, 0, 2, -655360),
    eGainPlus6("Gain +6dB", eGain, 6 * -655360),
    eSampleLoops("SampleLoops", 0, 1)
{
    for (int i = 0 ; i < 5 ; i++) {
        table[i] = new Gtk::Table(3, 1);
        table[i]->set_col_spacings(5);
    }

    pageno = 0;
    rowno = 0;
    firstRowInBlock = 0;

    addHeader("General (mandatory):");
    addString("Sample", lSample, wSample);
    //TODO: the following would break drag&drop:   wSample->property_editable().set_value(false);  or this:    wSample->set_editable(false);
    tooltips.set_tip(*wSample, "drop a sample here");
    addProp(eUnityNote);
    addHeader("Optional Settings:");
    addProp(eSampleStartOffset);
    addProp(ePan);
    addProp(eChannelOffset);
    addHeader("Loops:");
    addProp(eSampleLoops);
    addHeader("Crossfade:");
    addProp(eCrossfade_in_start);
    addProp(eCrossfade_in_end);
    addProp(eCrossfade_out_start);
    addProp(eCrossfade_out_end);

    nextPage();

    addHeader("General Amplitude Settings:");
    addProp(eGain);
    addProp(eGainPlus6);
    addProp(eAttenuationController);
    addProp(eInvertAttenuationController);
    addProp(eAttenuationControllerThreshold);
    addHeader("EG1 (Amplitude Envelope):");
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
    addHeader("LFO1 (Amplitude Oscillator):");
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

    addHeader("General Filter Settings:");
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
    addHeader("EG2 (Filter Cutoff Envelope):");
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
    addHeader("LFO2 (Filter Cutoff Oscillator):");
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

    addHeader("General Pitch Settings:");
    addProp(eFineTune);
    addProp(ePitchTrack);
    addHeader("EG3 (Pitch Envelope):");
    addProp(eEG3Attack);
    addProp(eEG3Depth);
    addHeader("LFO3 (Pitch Oscillator):");
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
    addProp(eSelfMask);
    addProp(eSustainDefeat);
    addProp(eMSDecode);

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

    append_page(*table[0], "Sample");
    append_page(*table[1], "Amplitude");
    append_page(*table[2], "Filter");
    append_page(*table[3], "Pitch");
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
    eEG1PreAttack.set_ptr(&d->EG1PreAttack);
    eEG1Attack.set_ptr(&d->EG1Attack);
    eEG1Decay1.set_ptr(&d->EG1Decay1);
    eEG1Decay2.set_ptr(&d->EG1Decay2);
    eEG1InfiniteSustain.set_ptr(&d->EG1InfiniteSustain);
    eEG1Sustain.set_ptr(&d->EG1Sustain);
    eEG1Release.set_ptr(&d->EG1Release);
    eEG1Hold.set_ptr(&d->EG1Hold);
    eEG1Controller.set_ptr(&d->EG1Controller);
    eEG1ControllerInvert.set_ptr(&d->EG1ControllerInvert);
    eEG1ControllerAttackInfluence.set_ptr(&d->EG1ControllerAttackInfluence);
    eEG1ControllerDecayInfluence.set_ptr(&d->EG1ControllerDecayInfluence);
    eEG1ControllerReleaseInfluence.set_ptr(&d->EG1ControllerReleaseInfluence);
    eLFO1Frequency.set_ptr(&d->LFO1Frequency);
    eLFO1InternalDepth.set_ptr(&d->LFO1InternalDepth);
    eLFO1ControlDepth.set_ptr(&d->LFO1ControlDepth);
    eLFO1Controller.set_ptr(&d->LFO1Controller);
    eLFO1FlipPhase.set_ptr(&d->LFO1FlipPhase);
    eLFO1Sync.set_ptr(&d->LFO1Sync);
    eEG2PreAttack.set_ptr(&d->EG2PreAttack);
    eEG2Attack.set_ptr(&d->EG2Attack);
    eEG2Decay1.set_ptr(&d->EG2Decay1);
    eEG2Decay2.set_ptr(&d->EG2Decay2);
    eEG2InfiniteSustain.set_ptr(&d->EG2InfiniteSustain);
    eEG2Sustain.set_ptr(&d->EG2Sustain);
    eEG2Release.set_ptr(&d->EG2Release);
    eEG2Controller.set_ptr(&d->EG2Controller);
    eEG2ControllerInvert.set_ptr(&d->EG2ControllerInvert);
    eEG2ControllerAttackInfluence.set_ptr(&d->EG2ControllerAttackInfluence);
    eEG2ControllerDecayInfluence.set_ptr(&d->EG2ControllerDecayInfluence);
    eEG2ControllerReleaseInfluence.set_ptr(&d->EG2ControllerReleaseInfluence);
    eLFO2Frequency.set_ptr(&d->LFO2Frequency);
    eLFO2InternalDepth.set_ptr(&d->LFO2InternalDepth);
    eLFO2ControlDepth.set_ptr(&d->LFO2ControlDepth);
    eLFO2Controller.set_ptr(&d->LFO2Controller);
    eLFO2FlipPhase.set_ptr(&d->LFO2FlipPhase);
    eLFO2Sync.set_ptr(&d->LFO2Sync);
    eEG3Attack.set_ptr(&d->EG3Attack);
    eEG3Depth.set_ptr(&d->EG3Depth);
    eLFO3Frequency.set_ptr(&d->LFO3Frequency);
    eLFO3InternalDepth.set_ptr(&d->LFO3InternalDepth);
    eLFO3ControlDepth.set_ptr(&d->LFO3ControlDepth);
    eLFO3Controller.set_ptr(&d->LFO3Controller);
    eLFO3Sync.set_ptr(&d->LFO3Sync);
    eVCFEnabled.set_ptr(&d->VCFEnabled);
    eVCFType.set_ptr(&d->VCFType);
    eVCFCutoffController.set_ptr(&d->VCFCutoffController);
    eVCFCutoffControllerInvert.set_ptr(&d->VCFCutoffControllerInvert);
    eVCFCutoff.set_ptr(&d->VCFCutoff);
    eVCFVelocityCurve.set_ptr(&d->VCFVelocityCurve);
    eVCFVelocityScale.set_ptr(&d->VCFVelocityScale);
    eVCFVelocityDynamicRange.set_ptr(&d->VCFVelocityDynamicRange);
    eVCFResonance.set_ptr(&d->VCFResonance);
    eVCFResonanceDynamic.set_ptr(&d->VCFResonanceDynamic);
    eVCFResonanceController.set_ptr(&d->VCFResonanceController);
    eVCFKeyboardTracking.set_ptr(&d->VCFKeyboardTracking);
    eVCFKeyboardTrackingBreakpoint.set_ptr(&d->VCFKeyboardTrackingBreakpoint);
    eVelocityResponseCurve.set_ptr(&d->VelocityResponseCurve);
    eVelocityResponseDepth.set_ptr(&d->VelocityResponseDepth);
    eVelocityResponseCurveScaling.set_ptr(&d->VelocityResponseCurveScaling);
    eReleaseVelocityResponseCurve.set_ptr(&d->ReleaseVelocityResponseCurve);
    eReleaseVelocityResponseDepth.set_ptr(&d->ReleaseVelocityResponseDepth);
    eReleaseTriggerDecay.set_ptr(&d->ReleaseTriggerDecay);
    eCrossfade_in_start.set_ptr(&d->Crossfade.in_start);
    eCrossfade_in_end.set_ptr(&d->Crossfade.in_end);
    eCrossfade_out_start.set_ptr(&d->Crossfade.out_start);
    eCrossfade_out_end.set_ptr(&d->Crossfade.out_end);
    ePitchTrack.set_ptr(&d->PitchTrack);
    eDimensionBypass.set_ptr(&d->DimensionBypass);
    ePan.set_ptr(&d->Pan);
    eSelfMask.set_ptr(&d->SelfMask);
    eAttenuationController.set_ptr(&d->AttenuationController);
    eInvertAttenuationController.set_ptr(&d->InvertAttenuationController);
    eAttenuationControllerThreshold.set_ptr(&d->AttenuationControllerThreshold);
    eChannelOffset.set_ptr(&d->ChannelOffset);
    eSustainDefeat.set_ptr(&d->SustainDefeat);
    eMSDecode.set_ptr(&d->MSDecode);
    eSampleStartOffset.set_ptr(&d->SampleStartOffset);
    eUnityNote.set_ptr(&d->UnityNote);
    eFineTune.set_ptr(&d->FineTune);
    eGain.set_ptr(&d->Gain);
    eGainPlus6.set_ptr(&d->Gain);
    eSampleLoops.set_ptr(&d->SampleLoops);

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
