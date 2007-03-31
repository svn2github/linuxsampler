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

#ifndef GIGEDIT_DIMREGIONEDIT_H
#define GIGEDIT_DIMREGIONEDIT_H

#include <gig.h>

#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/notebook.h>
#include <gtkmm/table.h>
#include <gtkmm/tooltips.h>

#include "paramedit.h"

class DimRegionEdit : public Gtk::Notebook
{
public:
    DimRegionEdit();
    virtual ~DimRegionEdit();
    void set_dim_region(gig::DimensionRegion* d);
    Gtk::Entry* wSample;

protected:
    Gtk::Tooltips tooltips;

    Gtk::Table* table[5];

    Gtk::Label* lSample;

    NumEntryPermille eEG1PreAttack;
    NumEntryTemp<double> eEG1Attack;
    NumEntryTemp<double> eEG1Decay1;
    NumEntryTemp<double> eEG1Decay2;
    BoolEntry eEG1InfiniteSustain;
    NumEntryPermille eEG1Sustain;
    NumEntryTemp<double> eEG1Release;
    BoolEntry eEG1Hold;
    ChoiceEntryLeverageCtrl eEG1Controller;
    BoolEntry eEG1ControllerInvert;
    NumEntryTemp<uint8_t> eEG1ControllerAttackInfluence;
    NumEntryTemp<uint8_t> eEG1ControllerDecayInfluence;
    NumEntryTemp<uint8_t> eEG1ControllerReleaseInfluence;
    NumEntryTemp<double> eLFO1Frequency;
    NumEntryTemp<uint16_t> eLFO1InternalDepth;
    NumEntryTemp<uint16_t> eLFO1ControlDepth;
    ChoiceEntry<gig::lfo1_ctrl_t> eLFO1Controller;
    BoolEntry eLFO1FlipPhase;
    BoolEntry eLFO1Sync;
    NumEntryPermille eEG2PreAttack;
    NumEntryTemp<double> eEG2Attack;
    NumEntryTemp<double> eEG2Decay1;
    NumEntryTemp<double> eEG2Decay2;
    BoolEntry eEG2InfiniteSustain;
    NumEntryPermille eEG2Sustain;
    NumEntryTemp<double> eEG2Release;
    ChoiceEntryLeverageCtrl eEG2Controller;
    BoolEntry eEG2ControllerInvert;
    NumEntryTemp<uint8_t> eEG2ControllerAttackInfluence;
    NumEntryTemp<uint8_t> eEG2ControllerDecayInfluence;
    NumEntryTemp<uint8_t> eEG2ControllerReleaseInfluence;
    NumEntryTemp<double> eLFO2Frequency;
    NumEntryTemp<uint16_t> eLFO2InternalDepth;
    NumEntryTemp<uint16_t> eLFO2ControlDepth;
    ChoiceEntry<gig::lfo2_ctrl_t> eLFO2Controller;
    BoolEntry eLFO2FlipPhase;
    BoolEntry eLFO2Sync;
    NumEntryTemp<double> eEG3Attack;
    NumEntryTemp<int16_t> eEG3Depth;
    NumEntryTemp<double> eLFO3Frequency;
    NumEntryTemp<int16_t> eLFO3InternalDepth;
    NumEntryTemp<int16_t> eLFO3ControlDepth;
    ChoiceEntry<gig::lfo3_ctrl_t> eLFO3Controller;
    BoolEntry eLFO3Sync;
    BoolEntry eVCFEnabled;
    ChoiceEntry<gig::vcf_type_t> eVCFType;
    ChoiceEntry<gig::vcf_cutoff_ctrl_t> eVCFCutoffController;
    BoolEntry eVCFCutoffControllerInvert;
    NumEntryTemp<uint8_t> eVCFCutoff;
    ChoiceEntry<gig::curve_type_t> eVCFVelocityCurve;
    NumEntryTemp<uint8_t> eVCFVelocityScale;
    NumEntryTemp<uint8_t> eVCFVelocityDynamicRange;
    NumEntryTemp<uint8_t> eVCFResonance;
    BoolEntry eVCFResonanceDynamic;
    ChoiceEntry<gig::vcf_res_ctrl_t> eVCFResonanceController;
    BoolEntry eVCFKeyboardTracking;
    NumEntryTemp<uint8_t> eVCFKeyboardTrackingBreakpoint;
    ChoiceEntry<gig::curve_type_t> eVelocityResponseCurve;
    NumEntryTemp<uint8_t> eVelocityResponseDepth;
    NumEntryTemp<uint8_t> eVelocityResponseCurveScaling;
    ChoiceEntry<gig::curve_type_t> eReleaseVelocityResponseCurve;
    NumEntryTemp<uint8_t> eReleaseVelocityResponseDepth;
    NumEntryTemp<uint8_t> eReleaseTriggerDecay;
    NumEntryTemp<uint8_t> eCrossfade_in_start;
    NumEntryTemp<uint8_t> eCrossfade_in_end;
    NumEntryTemp<uint8_t> eCrossfade_out_start;
    NumEntryTemp<uint8_t> eCrossfade_out_end;
    BoolEntry ePitchTrack;
    ChoiceEntry<gig::dim_bypass_ctrl_t> eDimensionBypass;
    NumEntryTemp<int8_t> ePan;
    BoolEntry eSelfMask;
    ChoiceEntryLeverageCtrl eAttenuationController;
    BoolEntry eInvertAttenuationController;
    NumEntryTemp<uint8_t> eAttenuationControllerThreshold;
    NumEntryTemp<uint8_t> eChannelOffset;
    BoolEntry eSustainDefeat;
    BoolEntry eMSDecode;
    NumEntryTemp<uint16_t> eSampleStartOffset;
    NoteEntry eUnityNote;
    NumEntryTemp<int16_t> eFineTune;
    NumEntryGain eGain;
    BoolEntryPlus6 eGainPlus6;
    NumEntryTemp<uint32_t> eSampleLoops;

    int rowno;
    int pageno;
    int firstRowInBlock;


    void addProp(LabelWidget& labelwidget);
    void addString(char* labelText, Gtk::Label*& label,
                   Gtk::Entry*& widget);
    void addHeader(char* text);
    void nextPage();

    void VCFEnabled_toggled();
    void VCFCutoffController_changed();
    void VCFResonanceController_changed();
    void EG1InfiniteSustain_toggled();
    void EG2InfiniteSustain_toggled();
    void EG1Controller_changed();
    void EG2Controller_changed();
    void AttenuationController_changed();
    void LFO1Controller_changed();
    void LFO2Controller_changed();
    void LFO3Controller_changed();
    void crossfade1_changed();
    void crossfade2_changed();
    void crossfade3_changed();
    void crossfade4_changed();

};

#endif
