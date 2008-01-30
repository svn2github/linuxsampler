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

#ifndef GIGEDIT_LINUXSAMPLER_PLUGIN_H
#define GIGEDIT_LINUXSAMPLER_PLUGIN_H

#include <config.h>

#include <linuxsampler/plugins/InstrumentEditor.h>
#include "../gigedit/gigedit.h"

#include <gig.h>

class LinuxSamplerPlugin : public LinuxSampler::InstrumentEditor, public GigEditJob {
    public:
        LinuxSamplerPlugin();
        virtual int Main(void* pInstrument, String sTypeName, String sTypeVersion);
        virtual bool IsTypeSupported(String sTypeName, String sTypeVersion);
        virtual String Name();
        virtual String Version();
        virtual String Description();
        virtual ~LinuxSamplerPlugin();

        virtual bool runGigEditJob();

    private:
        void* pApp;

        void __onSamplesToBeRemoved(std::list<gig::Sample*> lSamples);
};

#endif // GIGEDIT_LINUXSAMPLER_PLUGIN_H
