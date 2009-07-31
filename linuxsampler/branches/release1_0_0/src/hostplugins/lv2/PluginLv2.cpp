/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 Andreas Persson                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,                *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

#include "PluginLv2.h"

namespace {

    PluginLv2::PluginLv2(const LV2_Descriptor* Descriptor,
                         double SampleRate, const char* BundlePath,
                         const LV2_Feature* const* Features) {
        Out[0] = 0;
        Out[1] = 0;
        for (int i = 0 ; Features[i] ; i++) {
            dmsg(2, ("linuxsampler: host feature: %s\n", Features[i]->URI));
        }

        Init(SampleRate, 128);

        InitState();
    }

    void PluginLv2::ConnectPort(uint32_t Port, void* DataLocation) {
        if (Port == 2) {
            MidiBuf = static_cast<LV2_Event_Buffer*>(DataLocation);
        } else if (Port < 2) {
            Out[Port] = static_cast<float*>(DataLocation);
        }
    }

    void PluginLv2::Activate() {
        dmsg(2, ("linuxsampler: Activate\n"));
    }

    void PluginLv2::Run(uint32_t SampleCount) {
        int samplePos = 0;
        uint8_t* events = MidiBuf->data;
        int eventCount = MidiBuf->event_count;
        while (SampleCount) {
            int samples = std::min(SampleCount, 128U);

            for ( ; eventCount ; eventCount--) {
                LV2_Event* event = reinterpret_cast<LV2_Event*>(events);

                int time = event->frames - samplePos;
                if (time >= samples) break;

                uint8_t* data = events + sizeof(LV2_Event);
                events += (sizeof(LV2_Event) + event->size + 7) & ~7;

                pMidiDevice->Port()->DispatchRaw(data, time);
            }
            pAudioDevice->Channel(0)->SetBuffer(Out[0] + samplePos);
            pAudioDevice->Channel(1)->SetBuffer(Out[1] + samplePos);
            pAudioDevice->Render(samples);

            samplePos += samples;
            SampleCount -= samples;
        }
    }

    void PluginLv2::Deactivate() {
        dmsg(2, ("linuxsampler: Deactivate\n"));
    }

    char* PluginLv2::Save(const char* Directory, LV2SR_File*** Files) {
        dmsg(2, ("linuxsampler: Save Directory=%s\n", Directory));

        String filename(Directory);
        filename += "/linuxsampler";
        dmsg(2, ("saving to %s\n", filename.c_str()));
        std::ofstream out(filename.c_str());
        out << GetState();
        out.close();

        LV2SR_File** filearr = static_cast<LV2SR_File**>(malloc(sizeof(LV2SR_File*) * 2));

        LV2SR_File* file = static_cast<LV2SR_File*>(malloc(sizeof(LV2SR_File)));
        file->name = strdup("linuxsampler");
        file->path = strdup(filename.c_str());
        file->must_copy = 0;

        filearr[0] = file;
        filearr[1] = 0;

        *Files = filearr;

        dmsg(2, ("saving done\n"));
        return 0;
    }

    char* PluginLv2::Restore(const LV2SR_File** Files) {
        dmsg(2, ("linuxsampler: restore\n"));
        for (int i = 0 ; Files[i] ; i++) {
            dmsg(2, ("  name=%s path=%s\n", Files[i]->name, Files[i]->path));
            if (strcmp(Files[i]->name, "linuxsampler") == 0) {
                std::ifstream in(Files[0]->path);
                String state;
                std::getline(in, state, '\0');
                SetState(state);
            }
        }
        return 0;
    }

    LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                           double sample_rate, const char* bundle_path,
                           const LV2_Feature* const* features) {
        return new PluginLv2(descriptor, sample_rate, bundle_path, features);
    }

    void connect_port(LV2_Handle instance, uint32_t port, void* data_location) {
        static_cast<PluginLv2*>(instance)->ConnectPort(port, data_location);
    }

    void activate(LV2_Handle instance) {
        static_cast<PluginLv2*>(instance)->Activate();
    }

    void run(LV2_Handle instance, uint32_t sample_count) {
        static_cast<PluginLv2*>(instance)->Run(sample_count);
    }

    void deactivate(LV2_Handle instance) {
        static_cast<PluginLv2*>(instance)->Deactivate();
    }

    void cleanup(LV2_Handle instance) {
        delete static_cast<PluginLv2*>(instance);
    }

    char* save(LV2_Handle handle, const char* directory, LV2SR_File*** files) {
        return static_cast<PluginLv2*>(handle)->Save(directory, files);
    }

    char* restore(LV2_Handle handle, const LV2SR_File** files) {
        return static_cast<PluginLv2*>(handle)->Restore(files);
    }

    PluginInfo PluginInfo::Instance;

    PluginInfo::PluginInfo() {
        Lv2.URI = "http://linuxsampler.org/plugins/linuxsampler";
        Lv2.activate = activate;
        Lv2.cleanup = cleanup;
        Lv2.connect_port = connect_port;
        Lv2.deactivate = deactivate;
        Lv2.instantiate = instantiate;
        Lv2.run = run;
        Lv2.extension_data = extension_data;
        Lv2sr.save = save;
        Lv2sr.restore = restore;
    }


    const void* extension_data(const char* uri) {
        dmsg(2, ("linuxsampler: extension_data %s\n", uri));
        if (strcmp(uri, LV2_SAVERESTORE_URI) == 0) {
            return PluginInfo::Lv2srDescriptor();
        }
        return 0;
    }
}


extern "C" {
    LV2_SYMBOL_EXPORT
    const LV2_Descriptor* lv2_descriptor(uint32_t index) {
        return index == 0 ? PluginInfo::Lv2Descriptor() : 0;
    }
}
