/*
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

#include "dimregionedit.h"

#include "global.h"
#include "compat.h"

VelocityCurve::VelocityCurve(double (gig::DimensionRegion::*getter)(uint8_t)) :
    getter(getter), dimreg(0) {
    set_size_request(80, 80);
}

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
bool VelocityCurve::on_expose_event(GdkEventExpose* e) {
    const Cairo::RefPtr<Cairo::Context>& cr =
        get_window()->create_cairo_context();
#if 0
}
#endif
#else
bool VelocityCurve::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
#endif
    if (dimreg) {
        int w = get_width();
        int h = get_height();

        for (int pass = 0 ; pass < 2 ; pass++) {
            for (double x = 0 ; x <= w ; x++) {
                int vel = int(x * (127 - 1e-10) / w + 1);
                double y = (1 - (dimreg->*getter)(vel)) * (h - 3) + 1.5;

                if (x < 1e-10) {
                    cr->move_to(x, y);
                } else {
                    cr->line_to(x, y);
                }
            }
            if (pass == 0) {
                cr->line_to(w, h);
                cr->line_to(0, h);
                cr->set_source_rgba(0.5, 0.44, 1.0, is_sensitive() ? 0.2 : 0.1);
                cr->fill();
            } else {
                cr->set_line_width(3);
                cr->set_source_rgba(0.5, 0.44, 1.0, is_sensitive() ? 1.0 : 0.3);
                cr->stroke();
            }
        }
    }
    return true;
}


CrossfadeCurve::CrossfadeCurve() : dimreg(0) {
    set_size_request(280, 80);
}

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION < 90) || GTKMM_MAJOR_VERSION < 2
bool CrossfadeCurve::on_expose_event(GdkEventExpose* e) {
    const Cairo::RefPtr<Cairo::Context>& cr =
        get_window()->create_cairo_context();
#if 0
}
#endif
#else
bool CrossfadeCurve::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
#endif
    if (dimreg) {
        cr->translate(1.5, 0);

        // first, draw curves for the other layers
        gig::Region* region = dimreg->GetParent();
        int dimregno;
        for (dimregno = 0 ; dimregno < region->DimensionRegions ; dimregno++) {
            if (region->pDimensionRegions[dimregno] == dimreg) {
                break;
            }
        }
        int bitcount = 0;
        for (int dim = 0 ; dim < region->Dimensions ; dim++) {
            if (region->pDimensionDefinitions[dim].dimension ==
                gig::dimension_layer) {
                int mask =
                    ~(((1 << region->pDimensionDefinitions[dim].bits) - 1) <<
                      bitcount);
                int c = dimregno & mask; // mask away the layer dimension

                for (int i = 0 ; i < region->pDimensionDefinitions[dim].zones ;
                     i++) {
                    gig::DimensionRegion* d =
                        region->pDimensionRegions[c + (i << bitcount)];
                    if (d != dimreg) {
                        draw_one_curve(cr, d, false);
                    }
                }
                break;
            }
            bitcount += region->pDimensionDefinitions[dim].bits;
        }

        // then, draw the currently selected layer
        draw_one_curve(cr, dimreg, is_sensitive());
    }
    return true;
}

void CrossfadeCurve::draw_one_curve(const Cairo::RefPtr<Cairo::Context>& cr,
                                    const gig::DimensionRegion* d,
                                    bool sensitive) {
    int w = get_width();
    int h = get_height();

    if (d->Crossfade.out_end) {
        for (int pass = 0 ; pass < 2 ; pass++) {
            cr->move_to(d->Crossfade.in_start / 127.0 * (w - 3), h);
            cr->line_to(d->Crossfade.in_end / 127.0 * (w - 3), 1.5);
            cr->line_to(d->Crossfade.out_start / 127.0 * (w - 3), 1.5);
            cr->line_to(d->Crossfade.out_end / 127.0 * (w - 3), h);

            if (pass == 0) {
                cr->set_source_rgba(0.5, 0.44, 1.0, sensitive ? 0.2 : 0.1);
                cr->fill();
            } else {
                cr->set_line_width(3);
                cr->set_source_rgba(0.5, 0.44, 1.0, sensitive ? 1.0 : 0.3);
                cr->stroke();
            }
        }
    }
}


DimRegionEdit::DimRegionEdit() :
    velocity_curve(&gig::DimensionRegion::GetVelocityAttenuation),
    release_curve(&gig::DimensionRegion::GetVelocityRelease),
    cutoff_curve(&gig::DimensionRegion::GetVelocityCutoff),
    eEG1PreAttack(_("Pre-attack Level (%)"), 0, 100, 2),
    eEG1Attack(_("Attack Time (seconds)"), 0, 60, 3),
    eEG1Decay1(_("Decay 1 Time (seconds)"), 0.005, 60, 3),
    eEG1Decay2(_("Decay 2 Time (seconds)"), 0, 60, 3),
    eEG1InfiniteSustain(_("Infinite sustain")),
    eEG1Sustain(_("Sustain Level (%)"), 0, 100, 2),
    eEG1Release(_("Release Time (seconds)"), 0, 60, 3),
    eEG1Hold(_("Hold Attack Stage until Loop End")),
    eEG1Controller(_("Controller")),
    eEG1ControllerInvert(_("Controller invert")),
    eEG1ControllerAttackInfluence(_("Controller attack influence"), 0, 3),
    eEG1ControllerDecayInfluence(_("Controller decay influence"), 0, 3),
    eEG1ControllerReleaseInfluence(_("Controller release influence"), 0, 3),
    eLFO1Frequency(_("Frequency"), 0.1, 10, 2),
    eLFO1InternalDepth(_("Internal depth"), 0, 1200),
    eLFO1ControlDepth(_("Control depth"), 0, 1200),
    eLFO1Controller(_("Controller")),
    eLFO1FlipPhase(_("Flip phase")),
    eLFO1Sync(_("Sync")),
    eEG2PreAttack(_("Pre-attack Level (%)"), 0, 100, 2),
    eEG2Attack(_("Attack Time (seconds)"), 0, 60, 3),
    eEG2Decay1(_("Decay 1 Time (seconds)"), 0.005, 60, 3),
    eEG2Decay2(_("Decay 2 Time (seconds)"), 0, 60, 3),
    eEG2InfiniteSustain(_("Infinite sustain")),
    eEG2Sustain(_("Sustain Level (%)"), 0, 100, 2),
    eEG2Release(_("Release Time (seconds)"), 0, 60, 3),
    eEG2Controller(_("Controller")),
    eEG2ControllerInvert(_("Controller invert")),
    eEG2ControllerAttackInfluence(_("Controller attack influence"), 0, 3),
    eEG2ControllerDecayInfluence(_("Controller decay influence"), 0, 3),
    eEG2ControllerReleaseInfluence(_("Controller release influence"), 0, 3),
    eLFO2Frequency(_("Frequency"), 0.1, 10, 2),
    eLFO2InternalDepth(_("Internal depth"), 0, 1200),
    eLFO2ControlDepth(_("Control depth"), 0, 1200),
    eLFO2Controller(_("Controller")),
    eLFO2FlipPhase(_("Flip phase")),
    eLFO2Sync(_("Sync")),
    eEG3Attack(_("Attack"), 0, 10, 3),
    eEG3Depth(_("Depth"), -1200, 1200),
    eLFO3Frequency(_("Frequency"), 0.1, 10, 2),
    eLFO3InternalDepth(_("Internal depth"), 0, 1200),
    eLFO3ControlDepth(_("Control depth"), 0, 1200),
    eLFO3Controller(_("Controller")),
    eLFO3Sync(_("Sync")),
    eVCFEnabled(_("Enabled")),
    eVCFType(_("Type")),
    eVCFCutoffController(_("Cutoff controller")),
    eVCFCutoffControllerInvert(_("Cutoff controller invert")),
    eVCFCutoff(_("Cutoff")),
    eVCFVelocityCurve(_("Velocity curve")),
    eVCFVelocityScale(_("Velocity scale")),
    eVCFVelocityDynamicRange(_("Velocity dynamic range"), 0, 4),
    eVCFResonance(_("Resonance")),
    eVCFResonanceDynamic(_("Resonance dynamic")),
    eVCFResonanceController(_("Resonance controller")),
    eVCFKeyboardTracking(_("Keyboard tracking")),
    eVCFKeyboardTrackingBreakpoint(_("Keyboard tracking breakpoint")),
    eVelocityResponseCurve(_("Velocity response curve")),
    eVelocityResponseDepth(_("Velocity response depth"), 0, 4),
    eVelocityResponseCurveScaling(_("Velocity response curve scaling")),
    eReleaseVelocityResponseCurve(_("Release velocity response curve")),
    eReleaseVelocityResponseDepth(_("Release velocity response depth"), 0, 4),
    eReleaseTriggerDecay(_("Release trigger decay"), 0, 8),
    eCrossfade_in_start(_("Crossfade-in start")),
    eCrossfade_in_end(_("Crossfade-in end")),
    eCrossfade_out_start(_("Crossfade-out start")),
    eCrossfade_out_end(_("Crossfade-out end")),
    ePitchTrack(_("Pitch track")),
    eDimensionBypass(_("Dimension bypass")),
    ePan(_("Pan"), -64, 63),
    eSelfMask(_("Kill lower velocity voices (a.k.a \"Self mask\")")),
    eAttenuationController(_("Attenuation controller")),
    eInvertAttenuationController(_("Invert attenuation controller")),
    eAttenuationControllerThreshold(_("Attenuation controller threshold")),
    eChannelOffset(_("Channel offset"), 0, 9),
    eSustainDefeat(_("Ignore Hold Pedal (a.k.a. \"Sustain defeat\")")),
    eMSDecode(_("Decode Mid/Side Recordings")),
    eSampleStartOffset(_("Sample start offset"), 0, 2000),
    eUnityNote(_("Unity note")),
    eFineTune(_("Fine tune"), -49, 50),
    eGain(_("Gain"), -96, 0, 2, -655360),
    eGainPlus6(_("Gain +6dB"), eGain, 6 * -655360),
    eSampleLoopEnabled(_("Enabled")),
    eSampleLoopStart(_("Loop start positon")),
    eSampleLoopLength(_("Loop size")),
    eSampleLoopType(_("Loop type")),
    eSampleLoopInfinite(_("Infinite loop")),
    eSampleLoopPlayCount(_("Playback count"), 1),
    update_model(0)
{
    connect(eEG1PreAttack, &gig::DimensionRegion::EG1PreAttack);
    connect(eEG1Attack, &gig::DimensionRegion::EG1Attack);
    connect(eEG1Decay1, &gig::DimensionRegion::EG1Decay1);
    connect(eEG1Decay2, &gig::DimensionRegion::EG1Decay2);
    connect(eEG1InfiniteSustain, &gig::DimensionRegion::EG1InfiniteSustain);
    connect(eEG1Sustain, &gig::DimensionRegion::EG1Sustain);
    connect(eEG1Release, &gig::DimensionRegion::EG1Release);
    connect(eEG1Hold, &gig::DimensionRegion::EG1Hold);
    connect(eEG1Controller, &gig::DimensionRegion::EG1Controller);
    connect(eEG1ControllerInvert, &gig::DimensionRegion::EG1ControllerInvert);
    connect(eEG1ControllerAttackInfluence,
            &gig::DimensionRegion::EG1ControllerAttackInfluence);
    connect(eEG1ControllerDecayInfluence,
            &gig::DimensionRegion::EG1ControllerDecayInfluence);
    connect(eEG1ControllerReleaseInfluence,
            &gig::DimensionRegion::EG1ControllerReleaseInfluence);
    connect(eLFO1Frequency, &gig::DimensionRegion::LFO1Frequency);
    connect(eLFO1InternalDepth, &gig::DimensionRegion::LFO1InternalDepth);
    connect(eLFO1ControlDepth, &gig::DimensionRegion::LFO1ControlDepth);
    connect(eLFO1Controller, &gig::DimensionRegion::LFO1Controller);
    connect(eLFO1FlipPhase, &gig::DimensionRegion::LFO1FlipPhase);
    connect(eLFO1Sync, &gig::DimensionRegion::LFO1Sync);
    connect(eEG2PreAttack, &gig::DimensionRegion::EG2PreAttack);
    connect(eEG2Attack, &gig::DimensionRegion::EG2Attack);
    connect(eEG2Decay1, &gig::DimensionRegion::EG2Decay1);
    connect(eEG2Decay2, &gig::DimensionRegion::EG2Decay2);
    connect(eEG2InfiniteSustain, &gig::DimensionRegion::EG2InfiniteSustain);
    connect(eEG2Sustain, &gig::DimensionRegion::EG2Sustain);
    connect(eEG2Release, &gig::DimensionRegion::EG2Release);
    connect(eEG2Controller, &gig::DimensionRegion::EG2Controller);
    connect(eEG2ControllerInvert, &gig::DimensionRegion::EG2ControllerInvert);
    connect(eEG2ControllerAttackInfluence,
            &gig::DimensionRegion::EG2ControllerAttackInfluence);
    connect(eEG2ControllerDecayInfluence,
            &gig::DimensionRegion::EG2ControllerDecayInfluence);
    connect(eEG2ControllerReleaseInfluence,
            &gig::DimensionRegion::EG2ControllerReleaseInfluence);
    connect(eLFO2Frequency, &gig::DimensionRegion::LFO2Frequency);
    connect(eLFO2InternalDepth, &gig::DimensionRegion::LFO2InternalDepth);
    connect(eLFO2ControlDepth, &gig::DimensionRegion::LFO2ControlDepth);
    connect(eLFO2Controller, &gig::DimensionRegion::LFO2Controller);
    connect(eLFO2FlipPhase, &gig::DimensionRegion::LFO2FlipPhase);
    connect(eLFO2Sync, &gig::DimensionRegion::LFO2Sync);
    connect(eEG3Attack, &gig::DimensionRegion::EG3Attack);
    connect(eEG3Depth, &gig::DimensionRegion::EG3Depth);
    connect(eLFO3Frequency, &gig::DimensionRegion::LFO3Frequency);
    connect(eLFO3InternalDepth, &gig::DimensionRegion::LFO3InternalDepth);
    connect(eLFO3ControlDepth, &gig::DimensionRegion::LFO3ControlDepth);
    connect(eLFO3Controller, &gig::DimensionRegion::LFO3Controller);
    connect(eLFO3Sync, &gig::DimensionRegion::LFO3Sync);
    connect(eVCFEnabled, &gig::DimensionRegion::VCFEnabled);
    connect(eVCFType, &gig::DimensionRegion::VCFType);
    connect(eVCFCutoffController,
            &gig::DimensionRegion::SetVCFCutoffController);
    connect(eVCFCutoffControllerInvert,
            &gig::DimensionRegion::VCFCutoffControllerInvert);
    connect(eVCFCutoff, &gig::DimensionRegion::VCFCutoff);
    connect(eVCFVelocityCurve, &gig::DimensionRegion::SetVCFVelocityCurve);
    connect(eVCFVelocityScale, &gig::DimensionRegion::SetVCFVelocityScale);
    connect(eVCFVelocityDynamicRange,
            &gig::DimensionRegion::SetVCFVelocityDynamicRange);
    connect(eVCFResonance, &gig::DimensionRegion::VCFResonance);
    connect(eVCFResonanceDynamic, &gig::DimensionRegion::VCFResonanceDynamic);
    connect(eVCFResonanceController,
            &gig::DimensionRegion::VCFResonanceController);
    connect(eVCFKeyboardTracking, &gig::DimensionRegion::VCFKeyboardTracking);
    connect(eVCFKeyboardTrackingBreakpoint,
            &gig::DimensionRegion::VCFKeyboardTrackingBreakpoint);
    connect(eVelocityResponseCurve,
            &gig::DimensionRegion::SetVelocityResponseCurve);
    connect(eVelocityResponseDepth,
            &gig::DimensionRegion::SetVelocityResponseDepth);
    connect(eVelocityResponseCurveScaling,
            &gig::DimensionRegion::SetVelocityResponseCurveScaling);
    connect(eReleaseVelocityResponseCurve,
            &gig::DimensionRegion::SetReleaseVelocityResponseCurve);
    connect(eReleaseVelocityResponseDepth,
            &gig::DimensionRegion::SetReleaseVelocityResponseDepth);
    connect(eReleaseTriggerDecay, &gig::DimensionRegion::ReleaseTriggerDecay);
    connect(eCrossfade_in_start, &DimRegionEdit::set_Crossfade_in_start);
    connect(eCrossfade_in_end, &DimRegionEdit::set_Crossfade_in_end);
    connect(eCrossfade_out_start, &DimRegionEdit::set_Crossfade_out_start);
    connect(eCrossfade_out_end, &DimRegionEdit::set_Crossfade_out_end);
    connect(ePitchTrack, &gig::DimensionRegion::PitchTrack);
    connect(eDimensionBypass, &gig::DimensionRegion::DimensionBypass);
    connect(ePan, &gig::DimensionRegion::Pan);
    connect(eSelfMask, &gig::DimensionRegion::SelfMask);
    connect(eAttenuationController,
            &gig::DimensionRegion::AttenuationController);
    connect(eInvertAttenuationController,
            &gig::DimensionRegion::InvertAttenuationController);
    connect(eAttenuationControllerThreshold,
            &gig::DimensionRegion::AttenuationControllerThreshold);
    connect(eChannelOffset, &gig::DimensionRegion::ChannelOffset);
    connect(eSustainDefeat, &gig::DimensionRegion::SustainDefeat);
    connect(eMSDecode, &gig::DimensionRegion::MSDecode);
    connect(eSampleStartOffset, &gig::DimensionRegion::SampleStartOffset);
    connect(eUnityNote, &DimRegionEdit::set_UnityNote);
    connect(eFineTune, &DimRegionEdit::set_FineTune);
    connect(eGain, &DimRegionEdit::set_Gain);
    connect(eGainPlus6, &DimRegionEdit::set_Gain);
    connect(eSampleLoopEnabled, &DimRegionEdit::set_LoopEnabled);
    connect(eSampleLoopType, &DimRegionEdit::set_LoopType);
    connect(eSampleLoopStart, &DimRegionEdit::set_LoopStart);
    connect(eSampleLoopLength, &DimRegionEdit::set_LoopLength);
    connect(eSampleLoopInfinite, &DimRegionEdit::set_LoopInfinite);
    connect(eSampleLoopPlayCount, &DimRegionEdit::set_LoopPlayCount);

    for (int i = 0 ; i < 7 ; i++) {
        table[i] = new Gtk::Table(3, 1);
        table[i]->set_col_spacings(7);
    }

    // set tooltips
    eUnityNote.set_tip(
        _("Note this sample is associated with (a.k.a. 'root note')")
    );
    eSampleStartOffset.set_tip(_("Sample position at which playback should be started"));
    ePan.set_tip(_("Stereo balance (left/right)"));
    eChannelOffset.set_tip(
        _("Output channel where the audio signal should be routed to (0 - 9)")
    );
    ePitchTrack.set_tip(
        _("If true: sample will be pitched according to the key position "
          "(this would be disabled for drums for example)")
    );
    eSampleLoopEnabled.set_tip(_("If enabled: repeats to playback the sample"));
    eSampleLoopStart.set_tip(
        _("Start position within the sample (in sample points) of the area to "
          "be looped")
    );
    eSampleLoopLength.set_tip(
        _("Duration (in sample points) of the area to be looped")
    );
    eSampleLoopType.set_tip(
        _("Direction in which the loop area in the sample should be played back")
    );
    eSampleLoopInfinite.set_tip(
        _("Whether the loop area should be played back forever\n"
          "Caution: this setting is stored on Sample side, thus is shared "
          "among all dimension regions that use this sample!")
    );
    eSampleLoopPlayCount.set_tip(
        _("How many times the loop area should be played back\n"
          "Caution: this setting is stored on Sample side, thus is shared "
          "among all dimension regions that use this sample!")
    );
    
    eEG1PreAttack.set_tip(
        "Very first level this EG starts with. It rises then in Attack Time "
        "seconds from this initial level to 100%."
    );
    eEG1Attack.set_tip(
        "Duration of the EG's Attack stage, which raises its level from "
        "Pre-Attack Level to 100%."
    );
    eEG1Hold.set_tip(
       "On looped sounds, enabling this will cause the Decay 1 stage not to "
       "enter before the loop has been passed one time."
    );
    eAttenuationController.set_tip(_(
        "If you are not using the 'Layer' dimension, then this controller "
        "simply alters the volume. If you are using the 'Layer' dimension, "
        "then this controller is controlling the crossfade between Layers in "
        "real-time."
    ));

    eLFO1Sync.set_tip(
        "If not checked, every voice will use its own LFO instance, which "
        "causes voices triggered at different points in time to have different "
        "LFO levels. By enabling 'Sync' here the voices will instead use and "
        "share one single LFO, causing all voices to have the same LFO level, "
        "no matter when the individual notes have been triggered."
    );
    eLFO2Sync.set_tip(
        "If not checked, every voice will use its own LFO instance, which "
        "causes voices triggered at different points in time to have different "
        "LFO levels. By enabling 'Sync' here the voices will instead use and "
        "share one single LFO, causing all voices to have the same LFO level, "
        "no matter when the individual notes have been triggered."
    );
    eLFO3Sync.set_tip(
        "If not checked, every voice will use its own LFO instance, which "
        "causes voices triggered at different points in time to have different "
        "LFO levels. By enabling 'Sync' here the voices will instead use and "
        "share one single LFO, causing all voices to have the same LFO level, "
        "no matter when the individual notes have been triggered."
    );
    eLFO1FlipPhase.set_tip(
       "Inverts the LFO's generated wave vertically."
    );
    eLFO2FlipPhase.set_tip(
       "Inverts the LFO's generated wave vertically."
    );

    pageno = 0;
    rowno = 0;
    firstRowInBlock = 0;

    addHeader(_("Mandatory Settings"));
    addString(_("Sample"), lSample, wSample);
    //TODO: the following would break drag&drop:   wSample->property_editable().set_value(false);  or this:    wSample->set_editable(false);
#ifdef OLD_TOOLTIPS
    tooltips.set_tip(*wSample, _("Drag & drop a sample here"));
#else
    wSample->set_tooltip_text(_("Drag & drop a sample here"));
#endif
    addProp(eUnityNote);
    addHeader(_("Optional Settings"));
    addProp(eSampleStartOffset);
    addProp(eChannelOffset);
    addHeader(_("Loops"));
    addProp(eSampleLoopEnabled);
    addProp(eSampleLoopStart);
    addProp(eSampleLoopLength);
    {
        const char* choices[] = { _("normal"), _("bidirectional"), _("backward"), 0 };
        static const uint32_t values[] = {
            gig::loop_type_normal,
            gig::loop_type_bidirectional,
            gig::loop_type_backward
        };
        eSampleLoopType.set_choices(choices, values);
    }
    addProp(eSampleLoopType);
    addProp(eSampleLoopInfinite);
    addProp(eSampleLoopPlayCount);

    nextPage();

    addHeader(_("General Amplitude Settings"));
    addProp(eGain);
    addProp(eGainPlus6);
    addProp(ePan);
    addHeader(_("Amplitude Envelope (EG1)"));
    addProp(eEG1PreAttack);
    addProp(eEG1Attack);
    addProp(eEG1Hold);
    addProp(eEG1Decay1);
    addProp(eEG1Decay2);
    addProp(eEG1InfiniteSustain);
    addProp(eEG1Sustain);
    addProp(eEG1Release);
    addProp(eEG1Controller);
    addProp(eEG1ControllerInvert);
    addProp(eEG1ControllerAttackInfluence);
    addProp(eEG1ControllerDecayInfluence);
    addProp(eEG1ControllerReleaseInfluence);

    nextPage();

    addHeader(_("Amplitude Oscillator (LFO1)"));
    addProp(eLFO1Frequency);
    addProp(eLFO1InternalDepth);
    addProp(eLFO1ControlDepth);
    {
        const char* choices[] = { _("internal"), _("modwheel"), _("breath"),
                                  _("internal+modwheel"), _("internal+breath"), 0 };
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
    addHeader(_("Crossfade"));
    addProp(eAttenuationController);
    addProp(eInvertAttenuationController);
    addProp(eAttenuationControllerThreshold);
    addProp(eCrossfade_in_start);
    addProp(eCrossfade_in_end);
    addProp(eCrossfade_out_start);
    addProp(eCrossfade_out_end);

    Gtk::Frame* frame = new Gtk::Frame;
    frame->add(crossfade_curve);
    table[pageno]->attach(*frame, 1, 3, rowno, rowno + 1,
                          Gtk::SHRINK, Gtk::SHRINK);
    rowno++;

    eCrossfade_in_start.signal_value_changed().connect(
        sigc::mem_fun(crossfade_curve, &CrossfadeCurve::queue_draw));
    eCrossfade_in_end.signal_value_changed().connect(
        sigc::mem_fun(crossfade_curve, &CrossfadeCurve::queue_draw));
    eCrossfade_out_start.signal_value_changed().connect(
        sigc::mem_fun(crossfade_curve, &CrossfadeCurve::queue_draw));
    eCrossfade_out_end.signal_value_changed().connect(
        sigc::mem_fun(crossfade_curve, &CrossfadeCurve::queue_draw));

    nextPage();

    addHeader(_("General Filter Settings"));
    addProp(eVCFEnabled);
    {
        const char* choices[] = { _("lowpass"), _("lowpassturbo"), _("bandpass"),
                                  _("highpass"), _("bandreject"), 0 };
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
        const char* choices[] = { _("none"), _("none2"), _("modwheel"), _("effect1"), _("effect2"),
                                  _("breath"), _("foot"), _("sustainpedal"), _("softpedal"),
                                  _("genpurpose7"), _("genpurpose8"), _("aftertouch"), 0 };
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
    const char* curve_type_texts[] = { _("nonlinear"), _("linear"), _("special"), 0 };
    static const gig::curve_type_t curve_type_values[] = {
        gig::curve_type_nonlinear,
        gig::curve_type_linear,
        gig::curve_type_special
    };
    eVCFVelocityCurve.set_choices(curve_type_texts, curve_type_values);
    addProp(eVCFVelocityCurve);
    addProp(eVCFVelocityScale);
    addProp(eVCFVelocityDynamicRange);

    eVCFCutoffController.signal_value_changed().connect(
        sigc::mem_fun(cutoff_curve, &VelocityCurve::queue_draw));
    eVCFVelocityCurve.signal_value_changed().connect(
        sigc::mem_fun(cutoff_curve, &VelocityCurve::queue_draw));
    eVCFVelocityScale.signal_value_changed().connect(
        sigc::mem_fun(cutoff_curve, &VelocityCurve::queue_draw));
    eVCFVelocityDynamicRange.signal_value_changed().connect(
        sigc::mem_fun(cutoff_curve, &VelocityCurve::queue_draw));

    frame = new Gtk::Frame;
    frame->add(cutoff_curve);
    table[pageno]->attach(*frame, 1, 3, rowno, rowno + 1,
                          Gtk::SHRINK, Gtk::SHRINK);
    rowno++;

    addProp(eVCFResonance);
    addProp(eVCFResonanceDynamic);
    {
        const char* choices[] = { _("none"), _("genpurpose3"), _("genpurpose4"),
                                  _("genpurpose5"), _("genpurpose6"), 0 };
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

    lEG2 = addHeader(_("Filter Cutoff Envelope (EG2)"));
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
    lLFO2 = addHeader(_("Filter Cutoff Oscillator (LFO2)"));
    addProp(eLFO2Frequency);
    addProp(eLFO2InternalDepth);
    addProp(eLFO2ControlDepth);
    {
        const char* choices[] = { _("internal"), _("modwheel"), _("foot"),
                                  _("internal+modwheel"), _("internal+foot"), 0 };
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

    addHeader(_("General Pitch Settings"));
    addProp(eFineTune);
    addProp(ePitchTrack);
    addHeader(_("Pitch Envelope (EG3)"));
    addProp(eEG3Attack);
    addProp(eEG3Depth);
    addHeader(_("Pitch Oscillator (LFO3)"));
    addProp(eLFO3Frequency);
    addProp(eLFO3InternalDepth);
    addProp(eLFO3ControlDepth);
    {
        const char* choices[] = { _("internal"), _("modwheel"), _("aftertouch"),
                                  _("internal+modwheel"), _("internal+aftertouch"), 0 };
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

    addHeader(_("Velocity Response"));
    eVelocityResponseCurve.set_choices(curve_type_texts, curve_type_values);
    addProp(eVelocityResponseCurve);
    addProp(eVelocityResponseDepth);
    addProp(eVelocityResponseCurveScaling);

    eVelocityResponseCurve.signal_value_changed().connect(
        sigc::mem_fun(velocity_curve, &VelocityCurve::queue_draw));
    eVelocityResponseDepth.signal_value_changed().connect(
        sigc::mem_fun(velocity_curve, &VelocityCurve::queue_draw));
    eVelocityResponseCurveScaling.signal_value_changed().connect(
        sigc::mem_fun(velocity_curve, &VelocityCurve::queue_draw));

    frame = new Gtk::Frame;
    frame->add(velocity_curve);
    table[pageno]->attach(*frame, 1, 3, rowno, rowno + 1,
                          Gtk::SHRINK, Gtk::SHRINK);
    rowno++;

    addHeader(_("Release Velocity Response"));
    eReleaseVelocityResponseCurve.set_choices(curve_type_texts,
                                              curve_type_values);
    addProp(eReleaseVelocityResponseCurve);
    addProp(eReleaseVelocityResponseDepth);

    eReleaseVelocityResponseCurve.signal_value_changed().connect(
        sigc::mem_fun(release_curve, &VelocityCurve::queue_draw));
    eReleaseVelocityResponseDepth.signal_value_changed().connect(
        sigc::mem_fun(release_curve, &VelocityCurve::queue_draw));
    frame = new Gtk::Frame;
    frame->add(release_curve);
    table[pageno]->attach(*frame, 1, 3, rowno, rowno + 1,
                          Gtk::SHRINK, Gtk::SHRINK);
    rowno++;

    addProp(eReleaseTriggerDecay);
    {
        const char* choices[] = { _("none"), _("effect4depth"), _("effect5depth"), 0 };
        static const gig::dim_bypass_ctrl_t values[] = {
            gig::dim_bypass_ctrl_none,
            gig::dim_bypass_ctrl_94,
            gig::dim_bypass_ctrl_95
        };
        eDimensionBypass.set_choices(choices, values);
    }
    addProp(eDimensionBypass);
    eSelfMask.widget.set_tooltip_text(_(
        "If enabled: new notes with higher velocity value will stop older "
        "notes with lower velocity values, that way you can save voices that "
        "would barely be audible. This is also useful for certain drum sounds."
    ));
    addProp(eSelfMask);
    eSustainDefeat.widget.set_tooltip_text(_(
        "If enabled: sustain pedal will not hold a note. This way you can use "
        "the sustain pedal for other purposes, for example to switch among "
        "dimension regions."
    ));
    addProp(eSustainDefeat);
    eMSDecode.widget.set_tooltip_text(_(
        "Defines if Mid/Side Recordings should be decoded. Mid/Side Recordings "
        "are an alternative way to record sounds in stereo. The sampler needs "
        "to decode such samples to actually make use of them. Note: this "
        "feature is currently not supported by LinuxSampler."
    ));
    addProp(eMSDecode);

    nextPage();


    eEG1InfiniteSustain.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::EG1InfiniteSustain_toggled));
    eEG2InfiniteSustain.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::EG2InfiniteSustain_toggled));
    eEG1Controller.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::EG1Controller_changed));
    eEG2Controller.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::EG2Controller_changed));
    eLFO1Controller.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::LFO1Controller_changed));
    eLFO2Controller.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::LFO2Controller_changed));
    eLFO3Controller.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::LFO3Controller_changed));
    eAttenuationController.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::AttenuationController_changed));
    eVCFEnabled.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::VCFEnabled_toggled));
    eVCFCutoffController.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::VCFCutoffController_changed));
    eVCFResonanceController.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::VCFResonanceController_changed));

    eCrossfade_in_start.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::crossfade1_changed));
    eCrossfade_in_end.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::crossfade2_changed));
    eCrossfade_out_start.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::crossfade3_changed));
    eCrossfade_out_end.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::crossfade4_changed));

    eSampleLoopEnabled.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::update_loop_elements));
    eSampleLoopStart.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::loop_start_changed));
    eSampleLoopLength.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::loop_length_changed));
    eSampleLoopInfinite.signal_value_changed().connect(
        sigc::mem_fun(*this, &DimRegionEdit::loop_infinite_toggled));

    append_page(*table[0], _("Sample"));
    append_page(*table[1], _("Amplitude (1)"));
    append_page(*table[2], _("Amplitude (2)"));
    append_page(*table[3], _("Filter (1)"));
    append_page(*table[4], _("Filter (2)"));
    append_page(*table[5], _("Pitch"));
    append_page(*table[6], _("Misc"));
}

DimRegionEdit::~DimRegionEdit()
{
}

void DimRegionEdit::addString(const char* labelText, Gtk::Label*& label,
                              Gtk::Entry*& widget)
{
    label = new Gtk::Label(Glib::ustring(labelText) + ":");
    label->set_alignment(Gtk::ALIGN_START);

    table[pageno]->attach(*label, 1, 2, rowno, rowno + 1,
                          Gtk::FILL, Gtk::SHRINK);

    widget = new Gtk::Entry();

    table[pageno]->attach(*widget, 2, 3, rowno, rowno + 1,
                          Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);

    rowno++;
}

Gtk::Label* DimRegionEdit::addHeader(const char* text)
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
    label->set_alignment(Gtk::ALIGN_START);
    table[pageno]->attach(*label, 0, 3, rowno, rowno + 1,
                          Gtk::FILL, Gtk::SHRINK);
    rowno++;
    firstRowInBlock = rowno;
    return label;
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

void DimRegionEdit::addProp(BoolEntry& boolentry)
{
    table[pageno]->attach(boolentry.widget, 1, 3, rowno, rowno + 1,
                          Gtk::FILL, Gtk::SHRINK);
    rowno++;
}

void DimRegionEdit::addProp(BoolEntryPlus6& boolentry)
{
    table[pageno]->attach(boolentry.widget, 1, 3, rowno, rowno + 1,
                          Gtk::FILL, Gtk::SHRINK);
    rowno++;
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
    dimregion = d;
    velocity_curve.set_dim_region(d);
    release_curve.set_dim_region(d);
    cutoff_curve.set_dim_region(d);
    crossfade_curve.set_dim_region(d);

    set_sensitive(d);
    if (!d) return;

    update_model++;
    eEG1PreAttack.set_value(d->EG1PreAttack);
    eEG1Attack.set_value(d->EG1Attack);
    eEG1Decay1.set_value(d->EG1Decay1);
    eEG1Decay2.set_value(d->EG1Decay2);
    eEG1InfiniteSustain.set_value(d->EG1InfiniteSustain);
    eEG1Sustain.set_value(d->EG1Sustain);
    eEG1Release.set_value(d->EG1Release);
    eEG1Hold.set_value(d->EG1Hold);
    eEG1Controller.set_value(d->EG1Controller);
    eEG1ControllerInvert.set_value(d->EG1ControllerInvert);
    eEG1ControllerAttackInfluence.set_value(d->EG1ControllerAttackInfluence);
    eEG1ControllerDecayInfluence.set_value(d->EG1ControllerDecayInfluence);
    eEG1ControllerReleaseInfluence.set_value(d->EG1ControllerReleaseInfluence);
    eLFO1Frequency.set_value(d->LFO1Frequency);
    eLFO1InternalDepth.set_value(d->LFO1InternalDepth);
    eLFO1ControlDepth.set_value(d->LFO1ControlDepth);
    eLFO1Controller.set_value(d->LFO1Controller);
    eLFO1FlipPhase.set_value(d->LFO1FlipPhase);
    eLFO1Sync.set_value(d->LFO1Sync);
    eEG2PreAttack.set_value(d->EG2PreAttack);
    eEG2Attack.set_value(d->EG2Attack);
    eEG2Decay1.set_value(d->EG2Decay1);
    eEG2Decay2.set_value(d->EG2Decay2);
    eEG2InfiniteSustain.set_value(d->EG2InfiniteSustain);
    eEG2Sustain.set_value(d->EG2Sustain);
    eEG2Release.set_value(d->EG2Release);
    eEG2Controller.set_value(d->EG2Controller);
    eEG2ControllerInvert.set_value(d->EG2ControllerInvert);
    eEG2ControllerAttackInfluence.set_value(d->EG2ControllerAttackInfluence);
    eEG2ControllerDecayInfluence.set_value(d->EG2ControllerDecayInfluence);
    eEG2ControllerReleaseInfluence.set_value(d->EG2ControllerReleaseInfluence);
    eLFO2Frequency.set_value(d->LFO2Frequency);
    eLFO2InternalDepth.set_value(d->LFO2InternalDepth);
    eLFO2ControlDepth.set_value(d->LFO2ControlDepth);
    eLFO2Controller.set_value(d->LFO2Controller);
    eLFO2FlipPhase.set_value(d->LFO2FlipPhase);
    eLFO2Sync.set_value(d->LFO2Sync);
    eEG3Attack.set_value(d->EG3Attack);
    eEG3Depth.set_value(d->EG3Depth);
    eLFO3Frequency.set_value(d->LFO3Frequency);
    eLFO3InternalDepth.set_value(d->LFO3InternalDepth);
    eLFO3ControlDepth.set_value(d->LFO3ControlDepth);
    eLFO3Controller.set_value(d->LFO3Controller);
    eLFO3Sync.set_value(d->LFO3Sync);
    eVCFEnabled.set_value(d->VCFEnabled);
    eVCFType.set_value(d->VCFType);
    eVCFCutoffController.set_value(d->VCFCutoffController);
    eVCFCutoffControllerInvert.set_value(d->VCFCutoffControllerInvert);
    eVCFCutoff.set_value(d->VCFCutoff);
    eVCFVelocityCurve.set_value(d->VCFVelocityCurve);
    eVCFVelocityScale.set_value(d->VCFVelocityScale);
    eVCFVelocityDynamicRange.set_value(d->VCFVelocityDynamicRange);
    eVCFResonance.set_value(d->VCFResonance);
    eVCFResonanceDynamic.set_value(d->VCFResonanceDynamic);
    eVCFResonanceController.set_value(d->VCFResonanceController);
    eVCFKeyboardTracking.set_value(d->VCFKeyboardTracking);
    eVCFKeyboardTrackingBreakpoint.set_value(d->VCFKeyboardTrackingBreakpoint);
    eVelocityResponseCurve.set_value(d->VelocityResponseCurve);
    eVelocityResponseDepth.set_value(d->VelocityResponseDepth);
    eVelocityResponseCurveScaling.set_value(d->VelocityResponseCurveScaling);
    eReleaseVelocityResponseCurve.set_value(d->ReleaseVelocityResponseCurve);
    eReleaseVelocityResponseDepth.set_value(d->ReleaseVelocityResponseDepth);
    eReleaseTriggerDecay.set_value(d->ReleaseTriggerDecay);
    eCrossfade_in_start.set_value(d->Crossfade.in_start);
    eCrossfade_in_end.set_value(d->Crossfade.in_end);
    eCrossfade_out_start.set_value(d->Crossfade.out_start);
    eCrossfade_out_end.set_value(d->Crossfade.out_end);
    ePitchTrack.set_value(d->PitchTrack);
    eDimensionBypass.set_value(d->DimensionBypass);
    ePan.set_value(d->Pan);
    eSelfMask.set_value(d->SelfMask);
    eAttenuationController.set_value(d->AttenuationController);
    eInvertAttenuationController.set_value(d->InvertAttenuationController);
    eAttenuationControllerThreshold.set_value(d->AttenuationControllerThreshold);
    eChannelOffset.set_value(d->ChannelOffset);
    eSustainDefeat.set_value(d->SustainDefeat);
    eMSDecode.set_value(d->MSDecode);
    eSampleStartOffset.set_value(d->SampleStartOffset);
    eUnityNote.set_value(d->UnityNote);
    eFineTune.set_value(d->FineTune);
    eGain.set_value(d->Gain);
    eGainPlus6.set_value(d->Gain);
    eSampleLoopEnabled.set_value(d->SampleLoops);
    eSampleLoopType.set_value(
        d->SampleLoops ? d->pSampleLoops[0].LoopType : 0);
    eSampleLoopStart.set_value(
        d->SampleLoops ? d->pSampleLoops[0].LoopStart : 0);
    eSampleLoopLength.set_value(
        d->SampleLoops ? d->pSampleLoops[0].LoopLength : 0);
    eSampleLoopInfinite.set_value(
        d->pSample && d->pSample->LoopPlayCount == 0);
    eSampleLoopPlayCount.set_value(
        d->pSample ? d->pSample->LoopPlayCount : 0);
    update_model--;

    wSample->set_text(d->pSample ? gig_to_utf8(d->pSample->pInfo->Name) :
                      _("NULL"));

    update_loop_elements();
    VCFEnabled_toggled();
}


void DimRegionEdit::VCFEnabled_toggled()
{
    bool sensitive = eVCFEnabled.get_value();
    eVCFType.set_sensitive(sensitive);
    eVCFCutoffController.set_sensitive(sensitive);
    eVCFVelocityCurve.set_sensitive(sensitive);
    eVCFVelocityScale.set_sensitive(sensitive);
    eVCFVelocityDynamicRange.set_sensitive(sensitive);
    cutoff_curve.set_sensitive(sensitive);
    eVCFResonance.set_sensitive(sensitive);
    eVCFResonanceController.set_sensitive(sensitive);
    eVCFKeyboardTracking.set_sensitive(sensitive);
    eVCFKeyboardTrackingBreakpoint.set_sensitive(sensitive);
    lEG2->set_sensitive(sensitive);
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
    lLFO2->set_sensitive(sensitive);
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
    gig::vcf_cutoff_ctrl_t ctrl = eVCFCutoffController.get_value();
    bool hasController = ctrl != gig::vcf_cutoff_ctrl_none && ctrl != gig::vcf_cutoff_ctrl_none2;

    eVCFCutoffControllerInvert.set_sensitive(hasController);
    eVCFCutoff.set_sensitive(!hasController);
    eVCFResonanceDynamic.set_sensitive(!hasController);
    eVCFVelocityScale.label.set_text(hasController ? _("Minimum cutoff:") :
                                     _("Velocity scale:"));
}

void DimRegionEdit::VCFResonanceController_changed()
{
    bool hasController = eVCFResonanceController.get_value() != gig::vcf_res_ctrl_none;
    eVCFResonance.set_sensitive(!hasController);
}

void DimRegionEdit::EG1InfiniteSustain_toggled()
{
    bool infSus = eEG1InfiniteSustain.get_value();
    eEG1Decay2.set_sensitive(!infSus);
}

void DimRegionEdit::EG2InfiniteSustain_toggled()
{
    bool infSus = eEG2InfiniteSustain.get_value();
    eEG2Decay2.set_sensitive(!infSus);
}

void DimRegionEdit::EG1Controller_changed()
{
    bool hasController = eEG1Controller.get_value().type != gig::leverage_ctrl_t::type_none;
    eEG1ControllerInvert.set_sensitive(hasController);
}

void DimRegionEdit::EG2Controller_changed()
{
    bool hasController = eEG2Controller.get_value().type != gig::leverage_ctrl_t::type_none;
    eEG2ControllerInvert.set_sensitive(hasController);
}

void DimRegionEdit::AttenuationController_changed()
{
    bool hasController =
        eAttenuationController.get_value().type != gig::leverage_ctrl_t::type_none;
    eInvertAttenuationController.set_sensitive(hasController);
    eAttenuationControllerThreshold.set_sensitive(hasController);
    eCrossfade_in_start.set_sensitive(hasController);
    eCrossfade_in_end.set_sensitive(hasController);
    eCrossfade_out_start.set_sensitive(hasController);
    eCrossfade_out_end.set_sensitive(hasController);
    crossfade_curve.set_sensitive(hasController);
}

void DimRegionEdit::LFO1Controller_changed()
{
    gig::lfo1_ctrl_t ctrl = eLFO1Controller.get_value();
    eLFO1ControlDepth.set_sensitive(ctrl != gig::lfo1_ctrl_internal);
    eLFO1InternalDepth.set_sensitive(ctrl != gig::lfo1_ctrl_modwheel &&
                                     ctrl != gig::lfo1_ctrl_breath);
}

void DimRegionEdit::LFO2Controller_changed()
{
    gig::lfo2_ctrl_t ctrl = eLFO2Controller.get_value();
    eLFO2ControlDepth.set_sensitive(ctrl != gig::lfo2_ctrl_internal);
    eLFO2InternalDepth.set_sensitive(ctrl != gig::lfo2_ctrl_modwheel &&
                                     ctrl != gig::lfo2_ctrl_foot);
}

void DimRegionEdit::LFO3Controller_changed()
{
    gig::lfo3_ctrl_t ctrl = eLFO3Controller.get_value();
    eLFO3ControlDepth.set_sensitive(ctrl != gig::lfo3_ctrl_internal);
    eLFO3InternalDepth.set_sensitive(ctrl != gig::lfo3_ctrl_modwheel &&
                                     ctrl != gig::lfo3_ctrl_aftertouch);
}

void DimRegionEdit::crossfade1_changed()
{
    update_model++;
    eCrossfade_in_end.set_value(dimregion->Crossfade.in_end);
    eCrossfade_out_start.set_value(dimregion->Crossfade.out_start);
    eCrossfade_out_end.set_value(dimregion->Crossfade.out_end);
    update_model--;
}

void DimRegionEdit::crossfade2_changed()
{
    update_model++;
    eCrossfade_in_start.set_value(dimregion->Crossfade.in_start);
    eCrossfade_out_start.set_value(dimregion->Crossfade.out_start);
    eCrossfade_out_end.set_value(dimregion->Crossfade.out_end);
    update_model--;
}

void DimRegionEdit::crossfade3_changed()
{
    update_model++;
    eCrossfade_in_start.set_value(dimregion->Crossfade.in_start);
    eCrossfade_in_end.set_value(dimregion->Crossfade.in_end);
    eCrossfade_out_end.set_value(dimregion->Crossfade.out_end);
    update_model--;
}

void DimRegionEdit::crossfade4_changed()
{
    update_model++;
    eCrossfade_in_start.set_value(dimregion->Crossfade.in_start);
    eCrossfade_in_end.set_value(dimregion->Crossfade.in_end);
    eCrossfade_out_start.set_value(dimregion->Crossfade.out_start);
    update_model--;
}

void DimRegionEdit::update_loop_elements()
{
    update_model++;
    const bool active = eSampleLoopEnabled.get_value();
    eSampleLoopStart.set_sensitive(active);
    eSampleLoopLength.set_sensitive(active);
    eSampleLoopType.set_sensitive(active);
    eSampleLoopInfinite.set_sensitive(active && dimregion && dimregion->pSample);
    // sample loop shall never be longer than the actual sample size
    loop_start_changed();
    loop_length_changed();
    eSampleLoopStart.set_value(
        dimregion->SampleLoops ? dimregion->pSampleLoops[0].LoopStart : 0);
    eSampleLoopLength.set_value(
        dimregion->SampleLoops ? dimregion->pSampleLoops[0].LoopLength : 0);

    eSampleLoopInfinite.set_value(
        dimregion->pSample && dimregion->pSample->LoopPlayCount == 0);

    loop_infinite_toggled();
    update_model--;
}

void DimRegionEdit::loop_start_changed() {
    if (dimregion && dimregion->SampleLoops) {
        eSampleLoopLength.set_upper(dimregion->pSample ?
                                    dimregion->pSample->SamplesTotal -
                                    dimregion->pSampleLoops[0].LoopStart : 0);
    }
}

void DimRegionEdit::loop_length_changed() {
    if (dimregion && dimregion->SampleLoops) {
        eSampleLoopStart.set_upper(dimregion->pSample ?
                                   dimregion->pSample->SamplesTotal -
                                   dimregion->pSampleLoops[0].LoopLength : 0);
    }
}

void DimRegionEdit::loop_infinite_toggled() {
    eSampleLoopPlayCount.set_sensitive(
        dimregion && dimregion->pSample &&
        !eSampleLoopInfinite.get_value() &&
        eSampleLoopEnabled.get_value()
    );
    update_model++;
    eSampleLoopPlayCount.set_value(
        dimregion->pSample ? dimregion->pSample->LoopPlayCount : 0);
    update_model--;
}

bool DimRegionEdit::set_sample(gig::Sample* sample, bool copy_sample_unity, bool copy_sample_tune, bool copy_sample_loop)
{
    if (dimregion) {
        //TODO: we should better move the code from MainWindow::on_sample_label_drop_drag_data_received() here

        // currently commented because we're sending a similar signal in MainWindow::on_sample_label_drop_drag_data_received()
        //dimreg_to_be_changed_signal.emit(dimregion);

        // make sure stereo samples always are the same in both
        // dimregs in the samplechannel dimension
        int nbDimregs = 1;
        gig::DimensionRegion* d[2] = { dimregion, 0 };
        if (sample->Channels == 2) {
            gig::Region* region = dimregion->GetParent();

            int bitcount = 0;
            int stereo_bit = 0;
            for (int dim = 0 ; dim < region->Dimensions ; dim++) {
                if (region->pDimensionDefinitions[dim].dimension == gig::dimension_samplechannel) {
                    stereo_bit = 1 << bitcount;
                    break;
                }
                bitcount += region->pDimensionDefinitions[dim].bits;
            }

            if (stereo_bit) {
                int dimregno;
                for (dimregno = 0 ; dimregno < region->DimensionRegions ; dimregno++) {
                    if (region->pDimensionRegions[dimregno] == dimregion) {
                        break;
                    }
                }
                d[0] = region->pDimensionRegions[dimregno & ~stereo_bit];
                d[1] = region->pDimensionRegions[dimregno | stereo_bit];
                nbDimregs = 2;
            }
        }

        gig::Sample* oldref = dimregion->pSample;

        for (int i = 0 ; i < nbDimregs ; i++) {
            d[i]->pSample = sample;

            // copy sample information from Sample to DimensionRegion
            if (copy_sample_unity)
                d[i]->UnityNote = sample->MIDIUnityNote;
            if (copy_sample_tune)
                d[i]->FineTune = sample->FineTune;
            if (copy_sample_loop) {
                int loops = sample->Loops ? 1 : 0;
                while (d[i]->SampleLoops > loops) {
                    d[i]->DeleteSampleLoop(&d[i]->pSampleLoops[0]);
                }
                while (d[i]->SampleLoops < sample->Loops) {
                    DLS::sample_loop_t loop;
                    d[i]->AddSampleLoop(&loop);
                }
                if (loops) {
                    d[i]->pSampleLoops[0].Size = sizeof(DLS::sample_loop_t);
                    d[i]->pSampleLoops[0].LoopType = sample->LoopType;
                    d[i]->pSampleLoops[0].LoopStart = sample->LoopStart;
                    d[i]->pSampleLoops[0].LoopLength = sample->LoopEnd - sample->LoopStart + 1;
                }
            }
        }

        // update ui
        update_model++;
        wSample->set_text(gig_to_utf8(dimregion->pSample->pInfo->Name));
        eUnityNote.set_value(dimregion->UnityNote);
        eFineTune.set_value(dimregion->FineTune);
        eSampleLoopEnabled.set_value(dimregion->SampleLoops);
        update_loop_elements();
        update_model--;

        sample_ref_changed_signal.emit(oldref, sample);
        // currently commented because we're sending a similar signal in MainWindow::on_sample_label_drop_drag_data_received()
        //dimreg_changed_signal.emit(dimregion);
        return true;
    }
    return false;
}

sigc::signal<void, gig::DimensionRegion*>& DimRegionEdit::signal_dimreg_to_be_changed() {
    return dimreg_to_be_changed_signal;
}

sigc::signal<void, gig::DimensionRegion*>& DimRegionEdit::signal_dimreg_changed() {
    return dimreg_changed_signal;
}

sigc::signal<void, gig::Sample*/*old*/, gig::Sample*/*new*/>& DimRegionEdit::signal_sample_ref_changed() {
    return sample_ref_changed_signal;
}


void DimRegionEdit::set_UnityNote(gig::DimensionRegion* d, uint8_t value)
{
    d->UnityNote = value;
}

void DimRegionEdit::set_FineTune(gig::DimensionRegion* d, int16_t value)
{
    d->FineTune = value;
}

void DimRegionEdit::set_Crossfade_in_start(gig::DimensionRegion* d,
                                           uint8_t value)
{
    d->Crossfade.in_start = value;
    if (d->Crossfade.in_end < value) set_Crossfade_in_end(d, value);
}

void DimRegionEdit::set_Crossfade_in_end(gig::DimensionRegion* d,
                                         uint8_t value)
{
    d->Crossfade.in_end = value;
    if (value < d->Crossfade.in_start) set_Crossfade_in_start(d, value);
    if (value > d->Crossfade.out_start) set_Crossfade_out_start(d, value);
}

void DimRegionEdit::set_Crossfade_out_start(gig::DimensionRegion* d,
                                            uint8_t value)
{
    d->Crossfade.out_start = value;
    if (value < d->Crossfade.in_end) set_Crossfade_in_end(d, value);
    if (value > d->Crossfade.out_end) set_Crossfade_out_end(d, value);
}

void DimRegionEdit::set_Crossfade_out_end(gig::DimensionRegion* d,
                                          uint8_t value)
{
    d->Crossfade.out_end = value;
    if (value < d->Crossfade.out_start) set_Crossfade_out_start(d, value);
}

void DimRegionEdit::set_Gain(gig::DimensionRegion* d, int32_t value)
{
    d->SetGain(value);
}

void DimRegionEdit::set_LoopEnabled(gig::DimensionRegion* d, bool value)
{
    if (value) {
        // create a new sample loop in case there is none yet
        if (!d->SampleLoops) {
            DLS::sample_loop_t loop;
            loop.LoopType = gig::loop_type_normal;
            // loop the whole sample by default
            loop.LoopStart  = 0;
            loop.LoopLength =
                (d->pSample) ? d->pSample->SamplesTotal : 0;
            dimreg_to_be_changed_signal.emit(d);
            d->AddSampleLoop(&loop);
            dimreg_changed_signal.emit(d);
        }
    } else {
        if (d->SampleLoops) {
            dimreg_to_be_changed_signal.emit(d);
            // delete ALL existing sample loops
            while (d->SampleLoops) {
                d->DeleteSampleLoop(&d->pSampleLoops[0]);
            }
            dimreg_changed_signal.emit(d);
        }
    }
}

void DimRegionEdit::set_LoopType(gig::DimensionRegion* d, uint32_t value)
{
    if (d->SampleLoops) d->pSampleLoops[0].LoopType = value;
}

void DimRegionEdit::set_LoopStart(gig::DimensionRegion* d, uint32_t value)
{
    if (d->SampleLoops) {
        d->pSampleLoops[0].LoopStart =
            d->pSample ?
            std::min(value, uint32_t(d->pSample->SamplesTotal -
                                     d->pSampleLoops[0].LoopLength)) :
            0;
    }
}

void DimRegionEdit::set_LoopLength(gig::DimensionRegion* d, uint32_t value)
{
    if (d->SampleLoops) {
        d->pSampleLoops[0].LoopLength =
            d->pSample ?
            std::min(value, uint32_t(d->pSample->SamplesTotal -
                                     d->pSampleLoops[0].LoopStart)) :
            0;
    }
}

void DimRegionEdit::set_LoopInfinite(gig::DimensionRegion* d, bool value)
{
    if (d->pSample) {
        if (value) d->pSample->LoopPlayCount = 0;
        else if (d->pSample->LoopPlayCount == 0) d->pSample->LoopPlayCount = 1;
    }
}

void DimRegionEdit::set_LoopPlayCount(gig::DimensionRegion* d, uint32_t value)
{
    if (d->pSample) d->pSample->LoopPlayCount = value;
}
