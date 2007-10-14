/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2007 Christian Schoenebeck                              *
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
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#include "InstrumentEditorFactory.h"

#include "../common/global_private.h"

#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#ifndef CONFIG_PLUGIN_DIR
# error "Configuration macro CONFIG_PLUGIN_DIR not defined!"
#endif // CONFIG_PLUGIN_DIR

namespace LinuxSampler {

    std::map<String, InstrumentEditorFactory::InnerFactory*> InstrumentEditorFactory::InnerFactories;

    bool InstrumentEditorFactory::bPluginsLoaded = false;

    std::list<void*> InstrumentEditorFactory::LoadedDLLs;

    std::vector<String> InstrumentEditorFactory::AvailableEditors() {
        // make sure plugins were loaded already
        LoadPlugins();
        // render result
        std::vector<String> result;
        std::map<String, InnerFactory*>::iterator iter = InnerFactories.begin();
        for (; iter != InnerFactories.end(); iter++)
            result.push_back(iter->first);
        return result;
    }

    std::vector<String> InstrumentEditorFactory::MatchingEditors(String sTypeName, String sTypeVersion) {
        // make sure plugins were loaded already
        LoadPlugins();
        // render result
        std::vector<String> result;
        std::map<String, InnerFactory*>::iterator iter = InnerFactories.begin();
        for (; iter != InnerFactories.end(); iter++) {
            InstrumentEditor* pEditor = iter->second->Create();
            if (pEditor->IsTypeSupported(sTypeName, sTypeVersion))
                result.push_back(iter->first);
            iter->second->Destroy(pEditor);
        }
        return result;
    }

    String InstrumentEditorFactory::AvailableEditorsAsString() {
        std::vector<String> drivers = AvailableEditors();
        String result;
        std::vector<String>::iterator iter = drivers.begin();
        for (; iter != drivers.end(); iter++) {
            if (result != "") result += ",";
            result += "'" + *iter + "'";
        }
        return result;
    }

    InstrumentEditor* InstrumentEditorFactory::Create(String InstrumentEditorName) throw (Exception) {
        if (InnerFactories.count(InstrumentEditorName)) {
            InnerFactory* pInnerFactory = InnerFactories[InstrumentEditorName];
            return pInnerFactory->Create();
        } else throw Exception("unknown instrument editor");
    }

    void InstrumentEditorFactory::Destroy(InstrumentEditor* pInstrumentEditor) throw (Exception) {
        if (InnerFactories.count(pInstrumentEditor->Name())) {
            InnerFactory* pInnerFactory = InnerFactories[pInstrumentEditor->Name()];
            return pInnerFactory->Destroy(pInstrumentEditor);
        } else throw Exception("unknown instrument editor");
    }

    void InstrumentEditorFactory::LoadPlugins() {
        if (!bPluginsLoaded) {
            dmsg(1,("Loading instrument editor plugins..."));
            DIR* hDir = opendir(CONFIG_PLUGIN_DIR);
            if (!hDir) {
                std::cerr << "Could not open instrument editor plugins directory "
                          << "(" << CONFIG_PLUGIN_DIR << "): "
                          << strerror(errno) << std::endl;
                return;
            }
            for (dirent* pEntry = readdir(hDir); pEntry; pEntry = readdir(hDir)) {
                // skip entries that are not regular files
                if (pEntry->d_type != DT_REG) continue;
                String sPath = pEntry->d_name;
                // skip files that are not .so files
                if (
                    sPath.substr(sPath.length() - 3) != ".so" &&
                    sPath.find(".so.") == String::npos
                ) continue;
                // make it a full qualified path
                sPath = CONFIG_PLUGIN_DIR + ("/" + sPath);
                // load the DLL (the plugins should register themselfes automatically)
                void* pDLL = dlopen(sPath.c_str(), RTLD_NOW);
                if (pDLL) LoadedDLLs.push_back(pDLL);
                else {
                    std::cerr << "Failed to load instrument editor plugin: "
                              << sPath << std::endl;
                }
            }
            closedir(hDir);
            bPluginsLoaded = true;
            dmsg(1,("OK\n"));
        }
    }

    void InstrumentEditorFactory::ClosePlugins() {
        if (LoadedDLLs.size()) {
            dmsg(1,("Unloading instrument editor plugins..."));
            // free all inner factories
            {
                std::map<String, InnerFactory*>::iterator iter = InnerFactories.begin();
                for (; iter != InnerFactories.end(); iter++) delete iter->second;
                InnerFactories.clear();
            }
            // free the DLLs
            {
                std::list<void*>::iterator iter = LoadedDLLs.begin();
                for (; iter != LoadedDLLs.end(); iter++) dlclose(*iter);
                LoadedDLLs.clear();
                dmsg(1,("OK\n"));
            }
        }
        bPluginsLoaded = false;
    }

} // namespace LinuxSampler
