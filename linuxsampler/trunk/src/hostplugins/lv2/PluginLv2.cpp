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
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

#include "PluginLv2.h"

#define NS_ATOM "http://lv2plug.in/ns/ext/atom#"
#define NS_LS   "http://linuxsampler.org/schema#"

namespace {

    PluginLv2::PluginLv2(const LV2_Descriptor* Descriptor,
                         double SampleRate, const char* BundlePath,
                         const LV2_Feature* const* Features) {
        Out[0] = 0;
        Out[1] = 0;
        UriMap = 0;
        MapPath = 0;
        MakePath = 0;
        for (int i = 0 ; Features[i] ; i++) {
            dmsg(2, ("linuxsampler: host feature: %s\n", Features[i]->URI));
            if (!strcmp(Features[i]->URI, LV2_URI_MAP_URI)) {
                UriMap = (LV2_URI_Map_Feature*)Features[i]->data;
            } else if (!strcmp(Features[i]->URI, LV2_STATE_MAP_PATH_URI)) {
                MapPath = (LV2_State_Map_Path*)Features[i]->data;
            } else if (!strcmp(Features[i]->URI, LV2_STATE_MAKE_PATH_URI)) {
                MakePath = (LV2_State_Make_Path*)Features[i]->data;
            }
        }

        Init(SampleRate, 128);

        InitState();

        DefaultState = GetState();
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

    String PluginLv2::PathToState(const String& path) {
        if (MapPath) {
	        char* cstr = MapPath->abstract_path(MapPath->handle,
                                                path.c_str());
            const String abstract_path(cstr);
            free(cstr);
            return abstract_path;
        }
        return path;
    }

    String PluginLv2::PathFromState(const String& path) {
        if (MapPath) {
	        char* cstr = MapPath->absolute_path(MapPath->handle,
                                                path.c_str());
            const String abstract_path(cstr);
            free(cstr);
            return abstract_path;
        }
        return path;
    }

    void PluginLv2::Save(LV2_State_Store_Function store, LV2_State_Handle handle) {
        if (MakePath) {
	        char* path = MakePath->path(MapPath->handle,
	                                    "linuxsampler");
            dmsg(2, ("saving to file %s\n", path));

            std::ofstream out(path);
            out << GetState();

            store(handle,
                  uri_to_id(NULL, NS_LS "state-file"),
                  path,
                  strlen(path) + 1,
                  uri_to_id(NULL, LV2_STATE_PATH_URI),
                  LV2_STATE_IS_PORTABLE);
        } else {
            dmsg(2, ("saving to string\n"));

            std::ostringstream out;
            out << GetState();

            store(handle,
                  uri_to_id(NULL, NS_LS "state-string"),
                  out.str().c_str(),
                  out.str().length() + 1,
                  uri_to_id(NULL, NS_ATOM "String"),
                  LV2_STATE_IS_POD | LV2_STATE_IS_PORTABLE);
        }
        dmsg(2, ("saving done\n"));
    }

    void PluginLv2::Restore(LV2_State_Retrieve_Function retrieve, LV2_State_Handle handle) {
        size_t   size;
        uint32_t type;
        uint32_t flags;

        // Attempt to restore from state-file
        const void* value = retrieve(
            handle,
            uri_to_id(NULL, NS_LS "state-file"),
            &size, &type, &flags);
        if (value) {
            assert(type == uri_to_id(NULL, LV2_STATE_PATH_URI));
            const String path((const char*)value);
            dmsg(2, ("linuxsampler: restoring from file %s\n", path.c_str()));
            std::ifstream in(path.c_str());
            String state;
            std::getline(in, state, '\0');
            SetState(state);
            return;
        }

        // Attempt to restore from state-string
        value = retrieve(
                handle,
                uri_to_id(NULL, NS_LS "state-string"),
                &size, &type, &flags);
        if (value) {
            dmsg(2, ("linuxsampler: restoring from string\n"));
            assert(type == uri_to_id(NULL, NS_ATOM "String"));
            String state((const char*)value);
            SetState(state);
            return;
        }

        // No valid state found, reset to default state
        dmsg(2, ("linuxsampler: restoring default state\n"));
        SetState(DefaultState);
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

    void save(LV2_Handle handle, LV2_State_Store_Function store, LV2_State_Handle state,
              uint32_t flags, const LV2_Feature* const* features) {
        return static_cast<PluginLv2*>(handle)->Save(store, state);
    }

    void restore(LV2_Handle handle, LV2_State_Retrieve_Function retrieve, LV2_State_Handle state,
                 uint32_t flags, const LV2_Feature* const* features) {
        return static_cast<PluginLv2*>(handle)->Restore(retrieve, state);
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
        StateInterface.save = save;
        StateInterface.restore = restore;
    }


    const void* extension_data(const char* uri) {
        dmsg(2, ("linuxsampler: extension_data %s\n", uri));
        if (strcmp(uri, LV2_STATE_URI "#Interface") == 0) {
            return PluginInfo::Lv2StateInterface();
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
