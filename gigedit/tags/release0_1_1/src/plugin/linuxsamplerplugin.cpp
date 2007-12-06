/*
 * Copyright (C) 2007 Andreas Persson
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

#include <iostream>
#include <sigc++/bind.h>

REGISTER_INSTRUMENT_EDITOR(LinuxSamplerPlugin)

LinuxSamplerPlugin::LinuxSamplerPlugin() {
}

int LinuxSamplerPlugin::Main(void* pInstrument, String sTypeName, String sTypeVersion) {
    std::cout << "Entered Gigedit Main() loop :)\n" << std::flush;
    gig::Instrument* pGigInstr = static_cast<gig::Instrument*>(pInstrument);
    GigEdit app;
    // connect notification signals
    app.signal_file_structure_to_be_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureToBeChanged
            ),
            "gig::File"
        )
    );
    app.signal_file_structure_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureChanged
            ),
            "gig::File"
        )
    );
    app.signal_samples_to_be_removed().connect(
        sigc::mem_fun(*this, &LinuxSamplerPlugin::__onSamplesToBeRemoved)
    );
    app.signal_samples_removed().connect(
        sigc::mem_fun(*this, &LinuxSamplerPlugin::NotifySamplesRemoved)
    );
    app.signal_region_to_be_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureToBeChanged
            ),
            "gig::Region"
        )
    );
    app.signal_region_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureChanged
            ),
            "gig::Region"
        )
    );
    app.signal_dimreg_to_be_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureToBeChanged
            ),
            "gig::DimensionRegion"
        )
    );
    app.signal_dimreg_changed().connect(
        sigc::bind(
            sigc::mem_fun(
                *this, &LinuxSamplerPlugin::NotifyDataStructureChanged
            ),
            "gig::DimensionRegion"
        )
    );
    app.signal_sample_ref_changed().connect(
        sigc::mem_fun(*this, &LinuxSamplerPlugin::NotifySampleReferenceChanged)
    );
    // run gigedit application
    return app.run(pGigInstr);
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
