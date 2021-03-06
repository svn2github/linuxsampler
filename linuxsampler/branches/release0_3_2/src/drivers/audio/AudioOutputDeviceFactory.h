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

#ifndef __LS_AUDIO_OUTPUT_DEVICE_FACTORY_H__
#define __LS_AUDIO_OUTPUT_DEVICE_FACTORY_H__

#include <map>
#include <vector>

#include "../../common/LinuxSamplerException.h"
#include "../DeviceParameterFactory.h"
#include "AudioOutputDevice.h"

#define REGISTER_AUDIO_OUTPUT_DRIVER(DriverClass)  static LinuxSampler::AudioOutputDeviceFactory::InnerFactoryRegistrator<DriverClass> __auto_register_audio_output_driver__##DriverClass
#define REGISTER_AUDIO_OUTPUT_DRIVER_PARAMETER(DriverClass, ParameterClass) static LinuxSampler::AudioOutputDeviceFactory::ParameterRegistrator<DriverClass, DriverClass::ParameterClass> __auto_register_audio_output_driver_parameter__##DriverClass##ParameterClass

namespace LinuxSampler {

  class AudioOutputDeviceFactory {
      public:
          class InnerFactory {
              public:
                  virtual AudioOutputDevice* Create(std::map<String,DeviceCreationParameter*> Parameters)  = 0;
                  virtual String Description() = 0;
                  virtual String Version() = 0;
          };

          template <class Driver_T>
          class InnerFactoryTemplate : public InnerFactory {
              public:
                  virtual AudioOutputDevice* Create(std::map<String,DeviceCreationParameter*> Parameters)  { return new Driver_T(Parameters); }
                  virtual String Description() { return Driver_T::Description(); }
                  virtual String Version()     { return Driver_T::Version();     }
          };

          template <class Driver_T>
          class InnerFactoryRegistrator {
              public:
                  InnerFactoryRegistrator() {
                      AudioOutputDeviceFactory::InnerFactories[Driver_T::Name()] = new AudioOutputDeviceFactory::InnerFactoryTemplate<Driver_T>;
		      AudioOutputDeviceFactory::ParameterFactories[Driver_T::Name()] = new DeviceParameterFactory();
                  }
          };

	  template <class Driver_T, class Parameter_T>
          class ParameterRegistrator {
	      public:
                  ParameterRegistrator() {
			  DeviceParameterFactory::Register<Parameter_T>(AudioOutputDeviceFactory::ParameterFactories[Driver_T::Name()]);
		  }
	  };

          static AudioOutputDevice*                        Create(String DriverName, std::map<String,String> Parameters) throw (LinuxSamplerException);
          static std::vector<String>                       AvailableDrivers();
          static String                                    AvailableDriversAsString();
          static std::map<String,DeviceCreationParameter*> GetAvailableDriverParameters(String DriverName) throw (LinuxSamplerException);
          static DeviceCreationParameter*                  GetDriverParameter(String DriverName, String ParameterName) throw (LinuxSamplerException);
          static String                                    GetDriverDescription(String DriverName) throw (LinuxSamplerException);
          static String                                    GetDriverVersion(String DriverName) throw (LinuxSamplerException);

//      protected: /* FIXME: fields below should be protected, causes errors on gcc 2.95 though */
          static std::map<String, InnerFactory*> InnerFactories;
	  static std::map<String, DeviceParameterFactory*> ParameterFactories;
  };

} // namespace LinuxSampler

#endif // __LS_AUDIO_OUTPUT_DEVICE_FACTORY_H__
