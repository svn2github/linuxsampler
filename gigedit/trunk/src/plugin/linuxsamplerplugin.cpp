/*
 * Copyright (C) 2007, 2008 Andreas Persson
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

#include "linuxsamplerplugin.h"

#include <linuxsampler/plugins/InstrumentEditorFactory.h>
#include "../gigedit/gigedit.h"
#include "../gigedit/global.h"

#include <iostream>
#include <sigc++/bind.h>
#include <glibmm/main.h>

REGISTER_INSTRUMENT_EDITOR(LinuxSamplerPlugin)

LinuxSamplerPlugin::LinuxSamplerPlugin() {
    pApp = new GigEdit;
}

LinuxSamplerPlugin::~LinuxSamplerPlugin() {
    if (pApp) delete (GigEdit*) pApp;
}

int LinuxSamplerPlugin::Main(void* pInstrument, String sTypeName, String sTypeVersion) {
    std::cout << "Entered Gigedit Main() loop :)\n" << std::flush;
    gig::Instrument* pGigInstr = static_cast<gig::Instrument*>(pInstrument);
    GigEdit* app = (GigEdit*) pApp;

    // connect notification signals
    app->signal_file_structure_to_be_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureToBeChanged
            ),
            "gig::File"
        )
    );
    app->signal_file_structure_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureChanged
            ),
            "gig::File"
        )
    );
    app->signal_samples_to_be_removed().connect(
        sigc::mem_fun(*this, &LinuxSamplerPlugin::__onSamplesToBeRemoved)
    );
    app->signal_samples_removed().connect(
        sigc::mem_fun(*this, &LinuxSamplerPlugin::NotifySamplesRemoved)
    );
    app->signal_region_to_be_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureToBeChanged
            ),
            "gig::Region"
        )
    );
    app->signal_region_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureChanged
            ),
            "gig::Region"
        )
    );
    app->signal_dimreg_to_be_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureToBeChanged
            ),
            "gig::DimensionRegion"
        )
    );
    app->signal_dimreg_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureChanged
            ),
            "gig::DimensionRegion"
        )
    );
    app->signal_sample_ref_changed().connect(
        sigc::mem_fun(*this, &LinuxSamplerPlugin::NotifySampleReferenceChanged)
    );

    app->signal_keyboard_key_hit().connect(
        sigc::mem_fun(*this, &LinuxSamplerPlugin::__onVirtualKeyboardKeyHit)
    );
    app->signal_keyboard_key_released().connect(
        sigc::mem_fun(*this, &LinuxSamplerPlugin::__onVirtualKeyboardKeyReleased)
    );

    // register a timeout job to gigedit's main loop, so we can poll the
    // the sampler periodically for MIDI events (I HOPE it works on all
    // archs, because gigedit is actually running in another thread than
    // the one that is calling this timeout handler register code)
    const Glib::RefPtr<Glib::TimeoutSource> timeout_source =
        Glib::TimeoutSource::create(100); // poll every 100ms
    timeout_source->connect(
        sigc::mem_fun(this, &LinuxSamplerPlugin::__onPollPeriod)
    );
    timeout_source->attach(Glib::MainContext::get_default());

    // run gigedit application
    return app->run(pGigInstr);
}

bool LinuxSamplerPlugin::__onPollPeriod() {
    #if HAVE_LINUXSAMPLER_VIRTUAL_MIDI_DEVICE
    GigEdit* app = (GigEdit*) pApp;
    if (!NotesChanged()) return true;
    for (int iKey = 0; iKey < 128; iKey++)
        if (NoteChanged(iKey))
            NoteIsActive(iKey) ?
                app->on_note_on_event(iKey, NoteOnVelocity(iKey)) :
                app->on_note_off_event(iKey, NoteOffVelocity(iKey));
    return true;
    #else
    return false;
    #endif
}

void LinuxSamplerPlugin::__onSamplesToBeRemoved(std::list<gig::Sample*> lSamples) {
    // we have to convert the gig::Sample* list to a void* list first
    std::set<void*> samples;
    for (
        std::list<gig::Sample*>::iterator iter = lSamples.begin();
        iter != lSamples.end(); iter++
    ) samples.insert((void*)*iter);
    // finally send notification to sampler
    NotifySamplesToBeRemoved(samples);
}

void LinuxSamplerPlugin::__onVirtualKeyboardKeyHit(int Key, int Velocity) {
    #if HAVE_LINUXSAMPLER_VIRTUAL_MIDI_DEVICE
    SendNoteOnToSampler(Key, Velocity);
    #endif
}

void LinuxSamplerPlugin::__onVirtualKeyboardKeyReleased(int Key, int Velocity) {
    #if HAVE_LINUXSAMPLER_VIRTUAL_MIDI_DEVICE
    SendNoteOffToSampler(Key, Velocity);
    #endif
}

bool LinuxSamplerPlugin::IsTypeSupported(String sTypeName, String sTypeVersion) {
    return sTypeName == gig::libraryName() &&
           sTypeVersion == gig::libraryVersion();
}

String LinuxSamplerPlugin::Name() {
    return "gigedit";
}

String LinuxSamplerPlugin::Version() {
    return VERSION; // gigedit's version
}

String LinuxSamplerPlugin::Description() {
    return "Gigedit is an instrument editor for gig files.";
}
