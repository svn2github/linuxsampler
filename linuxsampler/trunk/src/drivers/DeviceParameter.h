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

#ifndef __LS_DEVICE_PARAMETER_H__
#define __LS_DEVICE_PARAMETER_H__

#include <map>
#include <vector>

#include "../common/global.h"
#include "../common/optional.h"
#include "../common/LinuxSamplerException.h"
#include "InputOutputDevice.h"

namespace LinuxSampler {

    // TODO: All plurar parameter classes (except for String) have to be added (namely DeviceRuntimeParameterBools, DeviceRuntimeParameterInts, DeviceRuntimeParameterFloats, DeviceCreationParameterBools, DeviceCreationParameterInts, DeviceCreationParameterFloats), I ignored them for the moment, because they were not that necessary.

    class DeviceRuntimeParameter {
        public:
            virtual String           Type()          = 0;
            virtual String           Description()   = 0;
            virtual bool             Fix()           = 0;
            virtual bool             Multiplicity()  = 0;
            virtual optional<String> RangeMin()      = 0;
            virtual optional<String> RangeMax()      = 0;
            virtual optional<String> Possibilities() = 0;
            virtual String           Value()         = 0;
            virtual void             SetValue(String val) throw (LinuxSamplerException) = 0;
    };

    class DeviceRuntimeParameterBool : public DeviceRuntimeParameter {
        public:
            DeviceRuntimeParameterBool(bool bVal);
            virtual String           Type();
            virtual bool             Multiplicity();
            virtual optional<String> RangeMin();
            virtual optional<String> RangeMax();
            virtual optional<String> Possibilities();
            virtual String           Value();
            virtual void             SetValue(String val) throw (LinuxSamplerException);

            virtual bool ValueAsBool();
            virtual void SetValue(bool b);

            virtual void OnSetValue(bool b) throw (LinuxSamplerException) = 0;
        protected:
            bool bVal;
    };

    class DeviceRuntimeParameterInt : public DeviceRuntimeParameter {
        public:
            DeviceRuntimeParameterInt(int iVal);
            virtual String           Type();
            virtual bool             Multiplicity();
            virtual optional<String> RangeMin();
            virtual optional<String> RangeMax();
            virtual optional<String> Possibilities();
            virtual String           Value();
            virtual void             SetValue(String val) throw (LinuxSamplerException);

            virtual int  ValueAsInt();
            virtual void SetValue(int i);

            virtual optional<int>    RangeMinAsInt()      = 0;
            virtual optional<int>    RangeMaxAsInt()      = 0;
            virtual std::vector<int> PossibilitiesAsInt() = 0;
            virtual void             OnSetValue(int i) throw (LinuxSamplerException) = 0;
        protected:
            int iVal;
    };

    class DeviceRuntimeParameterFloat : public DeviceRuntimeParameter {
        public:
            DeviceRuntimeParameterFloat(float fVal);
            virtual String           Type();
            virtual bool             Multiplicity();
            virtual optional<String> RangeMin();
            virtual optional<String> RangeMax();
            virtual optional<String> Possibilities();
            virtual String           Value();
            virtual void             SetValue(String val) throw (LinuxSamplerException);

            virtual float ValueAsFloat();
            virtual void  SetValue(float f);

            virtual optional<float>     RangeMinAsFloat()      = 0;
            virtual optional<float>     RangeMaxAsFloat()      = 0;
            virtual std::vector<float>  PossibilitiesAsFloat() = 0;
            virtual void                OnSetValue(float f) = 0;
        protected:
            float fVal;
    };

    class DeviceRuntimeParameterString : public DeviceRuntimeParameter {
        public:
            DeviceRuntimeParameterString(String sVal);
            virtual String           Type();
            virtual bool             Multiplicity();
            virtual optional<String> RangeMin();
            virtual optional<String> RangeMax();
            virtual optional<String> Possibilities();
            virtual String           Value();
            virtual void             SetValue(String val) throw (LinuxSamplerException);

            virtual std::vector<String> PossibilitiesAsString() = 0;
            virtual void                OnSetValue(String s)    = 0;
        protected:
            String sVal;
    };

    class DeviceRuntimeParameterStrings : public DeviceRuntimeParameter {
        public:
            DeviceRuntimeParameterStrings(std::vector<String> vS);
            virtual String           Type();
            virtual bool             Multiplicity();
            virtual optional<String> RangeMin();
            virtual optional<String> RangeMax();
            virtual optional<String> Possibilities();
            virtual String           Value();
            virtual void             SetValue(String val) throw (LinuxSamplerException);

            virtual std::vector<String> ValueAsStrings();
            virtual void                SetValue(std::vector<String> vS);

            virtual std::vector<String> PossibilitiesAsString()            = 0;
            virtual void                OnSetValue(std::vector<String> vS) = 0;
        protected:
            std::vector<String> sVals;
    };



    class DeviceCreationParameter : public DeviceRuntimeParameter {
        public:
	    DeviceCreationParameter ( void )                  { pDevice = NULL; }
            virtual bool                                      Mandatory() = 0;
            virtual optional<String>                          Depends();
            virtual std::map<String,DeviceCreationParameter*> DependsAsParameters() = 0;
            virtual optional<String>                          Default();
            virtual optional<String>                          Default(std::map<String,String> Parameters) = 0;
            virtual optional<String>                          RangeMin();
            virtual optional<String>                          RangeMin(std::map<String,String> Parameters) = 0;
            virtual optional<String>                          RangeMax();
            virtual optional<String>                          RangeMax(std::map<String,String> Parameters) = 0;
            virtual optional<String>                          Possibilities();
            virtual optional<String>                          Possibilities(std::map<String,String> Parameters) = 0;
	    void                                              Attach(InputOutputDevice* pDevice) { this->pDevice = pDevice; }
	protected:
	    InputOutputDevice*       pDevice;
    };

    class DeviceCreationParameterBool : public DeviceCreationParameter {
        public:
            DeviceCreationParameterBool(bool bVal = false);
            DeviceCreationParameterBool(String val) throw (LinuxSamplerException);
            virtual String Type();
            virtual bool   Multiplicity();
            virtual optional<String> Default(std::map<String,String> Parameters);
            virtual optional<String> RangeMin(std::map<String,String> Parameters);
            virtual optional<String> RangeMax(std::map<String,String> Parameters);
            virtual optional<String> Possibilities(std::map<String,String> Parameters);
            virtual String Value();
            virtual void   SetValue(String val) throw (LinuxSamplerException);

            virtual bool ValueAsBool();
            virtual void SetValue(bool b);

            virtual optional<bool> DefaultAsBool(std::map<String,String> Parameters) = 0;
            virtual void OnSetValue(bool b) throw (LinuxSamplerException)  = 0;
        protected:
            bool bVal;
            void InitWithDefault();
        private:
    };

    class DeviceCreationParameterInt : public DeviceCreationParameter {
        public:
            DeviceCreationParameterInt(int iVal = 0);
            DeviceCreationParameterInt(String val) throw (LinuxSamplerException);
            virtual String Type();
            virtual bool   Multiplicity();
            virtual optional<String> Default(std::map<String,String> Parameters);
            virtual optional<String> RangeMin(std::map<String,String> Parameters);
            virtual optional<String> RangeMax(std::map<String,String> Parameters);
            virtual optional<String> Possibilities(std::map<String,String> Parameters);
            virtual String Value();
            virtual void   SetValue(String val) throw (LinuxSamplerException);

            virtual int  ValueAsInt();
            virtual void SetValue(int i);

            virtual optional<int>    DefaultAsInt(std::map<String,String> Parameters)  = 0;
            virtual optional<int>    RangeMinAsInt(std::map<String,String> Parameters) = 0;
            virtual optional<int>    RangeMaxAsInt(std::map<String,String> Parameters) = 0;
            virtual std::vector<int> PossibilitiesAsInt(std::map<String,String> Parameters) = 0;
            virtual void             OnSetValue(int i) throw (LinuxSamplerException)  = 0;
        protected:
            int iVal;
            void InitWithDefault();
        private:
    };

    class DeviceCreationParameterFloat : public DeviceCreationParameter {
        public:
            DeviceCreationParameterFloat(float fVal = 0.0);
            DeviceCreationParameterFloat(String val) throw (LinuxSamplerException);
            virtual String Type();
            virtual bool   Multiplicity();
            virtual optional<String> Default(std::map<String,String> Parameters);
            virtual optional<String> RangeMin(std::map<String,String> Parameters);
            virtual optional<String> RangeMax(std::map<String,String> Parameters);
            virtual optional<String> Possibilities(std::map<String,String> Parameters);
            virtual String Value();
            virtual void   SetValue(String val) throw (LinuxSamplerException);

            virtual float ValueAsFloat();
            virtual void  SetValue(float f);

            virtual optional<float>    DefaultAsFloat(std::map<String,String> Parameters)  = 0;
            virtual optional<float>    RangeMinAsFloat(std::map<String,String> Parameters) = 0;
            virtual optional<float>    RangeMaxAsFloat(std::map<String,String> Parameters) = 0;
            virtual std::vector<float> PossibilitiesAsFloat(std::map<String,String> Parameters) = 0;
            virtual void OnSetValue(float f) throw (LinuxSamplerException)  = 0;
        protected:
            float fVal;
            void InitWithDefault();
        private:
    };

    class DeviceCreationParameterString : public DeviceCreationParameter {
        public:
            DeviceCreationParameterString(String sVal = String());
            virtual String Type();
            virtual bool   Multiplicity();
            virtual optional<String> RangeMin(std::map<String,String> Parameters);
            virtual optional<String> RangeMax(std::map<String,String> Parameters);
            virtual optional<String> Possibilities(std::map<String,String> Parameters);
            virtual String Value();
            virtual void   SetValue(String val) throw (LinuxSamplerException);

            virtual std::vector<String> PossibilitiesAsString(std::map<String,String> Parameters) = 0;
            virtual void OnSetValue(String s) throw (LinuxSamplerException) = 0;
        protected:
            String sVal;
            void InitWithDefault();
        private:
    };

    class DeviceCreationParameterStrings : public DeviceCreationParameter {
        public:
            DeviceCreationParameterStrings();
            DeviceCreationParameterStrings(std::vector<String> sVals);
            DeviceCreationParameterStrings(String val) throw (LinuxSamplerException);
            virtual String Type();
            virtual bool   Multiplicity();
            virtual optional<String> RangeMin(std::map<String,String> Parameters);
            virtual optional<String> RangeMax(std::map<String,String> Parameters);
            virtual optional<String> Possibilities(std::map<String,String> Parameters);
            virtual String Value();
            virtual void   SetValue(String val) throw (LinuxSamplerException);

            virtual std::vector<String> ValueAsStrings();
            virtual void                SetValue(std::vector<String> vS);

            virtual optional<std::vector<String> > DefaultAsStrings(std::map<String,String> Parameters) = 0;
            virtual std::vector<String> PossibilitiesAsString(std::map<String,String> Parameters) = 0;
            virtual void OnSetValue(std::vector<String> vS) throw (LinuxSamplerException) = 0;
        protected:
            std::vector<String> sVals;
            void InitWithDefault();
        private:
    };

} // namespace LinuxSampler

#endif // __LS_DEVICE_PARAMETER_H__
