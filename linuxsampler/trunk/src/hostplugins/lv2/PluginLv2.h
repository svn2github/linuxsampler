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

#ifndef LS_PLUGINLV2_H
#define LS_PLUGINLV2_H

#include <lv2.h>
#include "lv2_event.h"
#include "lv2_state.h"
#include "lv2_uri_map.h"
#include "../../drivers/Plugin.h"

namespace {

    class PluginLv2 : public LinuxSampler::Plugin {
    public:
        PluginLv2(const LV2_Descriptor* Descriptor,
                  double SampleRate, const char* BundlePath,
                  const LV2_Feature* const* Features);
        void ConnectPort(uint32_t Port, void* DataLocation);
        void Activate();
        void Run(uint32_t SampleCount);
        void Deactivate();
        void Save(LV2_State_Store_Function store, void* data);
        void Restore(LV2_State_Retrieve_Function retrieve, void* data);

	protected:
        virtual String PathToState(const String& string);
        virtual String PathFromState(const String& string);

    private:
        uint32_t uri_to_id(const char* map, const char* uri) {
	        return UriMap->uri_to_id(UriMap->callback_data, map, uri);
        }

        float* Out[2];
        LV2_Event_Buffer* MidiBuf;
        LV2_URI_Map_Feature* UriMap;
        LV2_State_Map_Path* MapPath;
        LV2_State_Make_Path* MakePath;

        String DefaultState;
    };

    class PluginInfo {
    public:
        static const LV2_Descriptor* Lv2Descriptor() {
            return &Instance.Lv2;
        }
        static const LV2_State_Interface* Lv2StateInterface() {
            return &Instance.StateInterface;
        }
    private:
        LV2_Descriptor Lv2;
        LV2_State_Interface StateInterface;

        PluginInfo();
        static PluginInfo Instance;
    };

    extern "C" {
        static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                      double sample_rate, const char* bundle_path,
                                      const LV2_Feature* const* features);
        static void connect_port(LV2_Handle instance, uint32_t port,
                                 void* data_location);
        static void activate(LV2_Handle instance);
        static void run(LV2_Handle instance, uint32_t sample_count);
        static void deactivate(LV2_Handle instance);
        static void cleanup(LV2_Handle instance);
        static const void* extension_data(const char* uri);

        static void save(LV2_Handle               handle,
                         LV2_State_Store_Function store,
                         void*                    data);

        static void restore(LV2_Handle                  handle,
                            LV2_State_Retrieve_Function retrieve,
                            void*                       data);
    }
}

#endif
