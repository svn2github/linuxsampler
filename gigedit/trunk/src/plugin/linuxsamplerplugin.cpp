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

#include <gig.h>
#include <linuxsampler/engines/InstrumentEditorFactory.h>
#include "../gigedit.h"

#include <iostream>

REGISTER_INSTRUMENT_EDITOR(LinuxSamplerPlugin)

LinuxSamplerPlugin::LinuxSamplerPlugin() {
}

int LinuxSamplerPlugin::Main(void* pInstrument, String sTypeName, String sTypeVersion) {
    std::cout << "Entered Gigedit Main() loop :)\n" << std::flush;
    gig::Instrument* pGigInstr = static_cast<gig::Instrument*>(pInstrument);
    return GigEdit::run(pGigInstr);
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
