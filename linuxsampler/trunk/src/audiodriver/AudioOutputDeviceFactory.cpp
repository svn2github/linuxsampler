/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#include "AudioOutputDeviceFactory.h"

namespace LinuxSampler {

    std::map<String, AudioOutputDeviceFactory::InnerFactory*> AudioOutputDeviceFactory::InnerFactories;

    AudioOutputDevice* AudioOutputDeviceFactory::Create(String DriverName, std::map<String,String>& Parameters) throw (LinuxSamplerException) {
        if (!InnerFactories.count(DriverName)) throw LinuxSamplerException("There is no audio output driver '" + DriverName + "'.");
        return InnerFactories[DriverName]->Create(Parameters);
    }

    std::vector<String> AudioOutputDeviceFactory::AvailableDrivers() {
        std::vector<String> result;
        std::map<String, InnerFactory*>::iterator iter = InnerFactories.begin();
        while (iter != InnerFactories.end()) {
            result.push_back(iter->first);
            iter++;
        }
        return result;
    }

    String AudioOutputDeviceFactory::AvailableDriversAsString() {
        std::vector<String> drivers = AvailableDrivers();
        String result;
        std::vector<String>::iterator iter = drivers.begin();
        for (; iter != drivers.end(); iter++) {
            if (result != "") result += ",";
            result += *iter;
        }
        return result;
    }

    std::map<String,DeviceCreationParameter*> AudioOutputDeviceFactory::GetAvailableDriverParameters(String DriverName) throw (LinuxSamplerException) {
        if (!InnerFactories.count(DriverName)) throw LinuxSamplerException("There is no audio output driver '" + DriverName + "'.");
        return InnerFactories[DriverName]->AvailableParameters();
    }

    DeviceCreationParameter* AudioOutputDeviceFactory::GetDriverParameter(String DriverName, String ParameterName) throw (LinuxSamplerException) {
        std::map<String,DeviceCreationParameter*> parameters = GetAvailableDriverParameters(DriverName);
        if (!parameters.count(ParameterName)) throw LinuxSamplerException("Audio output driver '" + DriverName + "' does not have a parameter '" + ParameterName + "'.");
        return parameters[ParameterName];
    }

    String AudioOutputDeviceFactory::GetDriverDescription(String DriverName) throw (LinuxSamplerException) {
        if (!InnerFactories.count(DriverName)) throw LinuxSamplerException("There is no audio output driver '" + DriverName + "'.");
        return InnerFactories[DriverName]->Description();
    }

    String AudioOutputDeviceFactory::GetDriverVersion(String DriverName) throw (LinuxSamplerException) {
        if (!InnerFactories.count(DriverName)) throw LinuxSamplerException("There is no audio output driver '" + DriverName + "'.");
        return InnerFactories[DriverName]->Version();
    }

} // namespace LinuxSampler
