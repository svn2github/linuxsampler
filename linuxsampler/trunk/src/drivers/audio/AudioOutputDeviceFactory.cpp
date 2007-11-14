/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#include "AudioOutputDeviceFactory.h"

#include "../../common/global_private.h"

#if HAVE_ALSA
# include "AudioOutputDeviceAlsa.h"
#endif // HAVE_ALSA

#if HAVE_JACK
# include "AudioOutputDeviceJack.h"
#endif // HAVE_JACK

#if HAVE_ARTS
# include "AudioOutputDeviceArts.h"
#endif // HAVE_ARTS

#if HAVE_ASIO
# include "AudioOutputDeviceAsio.h"
#endif // HAVE_ASIO
namespace LinuxSampler {

    std::map<String, AudioOutputDeviceFactory::InnerFactory*> AudioOutputDeviceFactory::InnerFactories;
    std::map<String, DeviceParameterFactory*> AudioOutputDeviceFactory::ParameterFactories;

#if HAVE_ALSA
    REGISTER_AUDIO_OUTPUT_DRIVER(AudioOutputDeviceAlsa);
    /* Common parameters for now they'll have to be registered here. */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterActive);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterSampleRate);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterChannels);
    /* Driver specific parameters */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterCard);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterFragments);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAlsa, ParameterFragmentSize);
#endif // HAVE_ALSA

#if HAVE_JACK
    REGISTER_AUDIO_OUTPUT_DRIVER(AudioOutputDeviceJack);
    /* Common parameters for now they'll have to be registered here. */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceJack, ParameterActive);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceJack, ParameterChannels);
    /* Driver specific parameters */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceJack, ParameterName);
#endif // HAVE_JACK

#if HAVE_ARTS
    REGISTER_AUDIO_OUTPUT_DRIVER(AudioOutputDeviceArts);
    /* Common parameters for now they'll have to be registered here. */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceArts, ParameterActive);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceArts, ParameterSampleRate);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceArts, ParameterChannels);
    /* Driver specific parameters */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceArts, ParameterName);
#endif // HAVE_ARTS

#if HAVE_ASIO
    REGISTER_AUDIO_OUTPUT_DRIVER(AudioOutputDeviceAsio);
    /* Common parameters for now they'll have to be registered here. */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAsio, ParameterActive);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAsio, ParameterSampleRate);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAsio, ParameterChannels);
    /* Driver specific parameters */
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAsio, ParameterCard);
    REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(AudioOutputDeviceAsio, ParameterFragmentSize);
#endif // HAVE_ASIO

    AudioOutputDevice* AudioOutputDeviceFactory::Create(String DriverName, std::map<String,String> Parameters) throw (Exception) {
        if (!InnerFactories.count(DriverName)) throw Exception("There is no audio output driver '" + DriverName + "'.");
	//Let's see if we need to create parameters
	std::map<String,DeviceCreationParameter*> thisDeviceParams;
	DeviceParameterFactory* pParamFactory = ParameterFactories[DriverName];
	if (pParamFactory) {
		thisDeviceParams = pParamFactory->CreateAllParams(Parameters);
	} else {
	       	//No parameters are registered by the driver. Throw if any parameters were specified.
		if (Parameters.size() != 0) throw Exception("Driver '" + DriverName + "' does not have any parameters.");
	}
	//Now create the device using those parameters
        AudioOutputDevice* pDevice = InnerFactories[DriverName]->Create(thisDeviceParams);
	//Now attach all parameters to the newely created device.
	for (std::map<String,DeviceCreationParameter*>::iterator iter = thisDeviceParams.begin(); iter != thisDeviceParams.end(); iter++) {
		iter->second->Attach(pDevice);
	}
	return pDevice;
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

    std::map<String,DeviceCreationParameter*> AudioOutputDeviceFactory::GetAvailableDriverParameters(String DriverName) throw (Exception) {
        if (!InnerFactories.count(DriverName)) throw Exception("There is no audio output driver '" + DriverName + "'.");
	std::map<String,DeviceCreationParameter*> thisDeviceParams;
	DeviceParameterFactory* pParamFactory = ParameterFactories[DriverName];
	if (pParamFactory) {
		thisDeviceParams = pParamFactory->CreateAllParams();
	}
        return thisDeviceParams;
    }

    DeviceCreationParameter* AudioOutputDeviceFactory::GetDriverParameter(String DriverName, String ParameterName) throw (Exception) {
        std::map<String,DeviceCreationParameter*> parameters = GetAvailableDriverParameters(DriverName);
        if (!parameters.count(ParameterName)) throw Exception("Audio output driver '" + DriverName + "' does not have a parameter '" + ParameterName + "'.");
        return parameters[ParameterName];
    }

    String AudioOutputDeviceFactory::GetDriverDescription(String DriverName) throw (Exception) {
        if (!InnerFactories.count(DriverName)) throw Exception("There is no audio output driver '" + DriverName + "'.");
        return InnerFactories[DriverName]->Description();
    }

    String AudioOutputDeviceFactory::GetDriverVersion(String DriverName) throw (Exception) {
        if (!InnerFactories.count(DriverName)) throw Exception("There is no audio output driver '" + DriverName + "'.");
        return InnerFactories[DriverName]->Version();
    }

} // namespace LinuxSampler
