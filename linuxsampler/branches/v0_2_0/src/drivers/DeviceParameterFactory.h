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

#ifndef __LS_DEVICE_PARAMETER_FACTORY_H__
#define __LS_DEVICE_PARAMETER_FACTORY_H__

#include <map>
#include <vector>

#include "../common/global.h"
#include "../common/optional.h"
#include "../common/LinuxSamplerException.h"
#include "DeviceParameter.h"

namespace LinuxSampler {

	class DeviceParameterFactory {
		public:
			class InnerFactory {
				public:
					virtual DeviceCreationParameter* Create() = 0;
					virtual DeviceCreationParameter* Create(String val) = 0;
			};
			
			template <class Parameter_T>
			class InnerFactoryTemplate : public InnerFactory {
				public:
					virtual DeviceCreationParameter* Create() { return new Parameter_T(); }
					virtual DeviceCreationParameter* Create(String val) { return new Parameter_T(val); }
			};

			template <class Parameter_T>
			static void Register(DeviceParameterFactory* factory) {
				factory->InnerFactories[Parameter_T::Name()] = new InnerFactoryTemplate<Parameter_T>;
			}

			std::map<String,DeviceCreationParameter*> CreateAllParams ( std::map<String,String> Parameters );
			std::map<String,DeviceCreationParameter*> CreateAllParams ();

			DeviceCreationParameter* Create(String ParameterName) throw (LinuxSamplerException);
			DeviceCreationParameter* Create(String ParameterName, String val) throw (LinuxSamplerException);

		protected:
			std::map<String, InnerFactory*> InnerFactories;
	};

} // namespace LinuxSampler

#endif // __LS_DEVICE_PARAMETER_FACTORY_H__
