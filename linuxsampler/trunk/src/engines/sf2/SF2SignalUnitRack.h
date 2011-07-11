/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2011 Grigor Iliev                                       *
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

#ifndef __LS_SF2SIGNALUNITRACK_H__
#define	__LS_SF2SIGNALUNITRACK_H__

#include "../common/SignalUnitRack.h"
#include "../sfz/EGADSR.h"
#include "../common/AbstractVoice.h"

namespace LinuxSampler { namespace sf2 {
    
    class Voice;
    
    class EGUnit : public SignalUnitBase<Voice>, public ::LinuxSampler::sfz::EGADSR {
        public:
            virtual bool  Active() { return active(); }
            virtual float GetLevel() { return getLevel(); }
            virtual void  EnterReleaseStage();
            virtual void  CancelRelease();
    };

    class VolEGUnit : public EGUnit {
        public:
            virtual void  Trigger();
            virtual void  Increment();
    };

    class ModEGUnit : public EGUnit {
        public:
            virtual void  Trigger();
            virtual void  Increment();
    };

    class VibLfoUnit : public SignalUnitBase<Voice>, public LFOSigned {
        public:
            VibLfoUnit(): LFOSigned(1200.0f) { }
            virtual bool  Active() { return true; }
            virtual void  Trigger();
            virtual void  Increment();
            virtual float GetLevel() { return Level; }
    };
    
    class EndpointUnit : public EndpointSignalUnitBase<Voice> {
        public:
            EndpointUnit() { }

            virtual void Trigger();

            /** The endpoint should be active until the volume EG is active. */
            virtual bool Active();
            
            virtual float GetVolume();
            virtual float GetFilterCutoff();
            virtual float GetPitch();
            virtual float GetResonance();
    };
    
    class SF2SignalUnitRack : public SignalUnitRackBase<Voice> {
        private:
            VolEGUnit     suVolEG;
            ModEGUnit     suModEG;
            VibLfoUnit    suVibLfo;
            EndpointUnit  suEndpoint;
            

        public:
        
            /**
             * @param Voice The voice to which this rack belongs.
             */
            SF2SignalUnitRack(Voice* Voice);

            virtual void                 Trigger();
            virtual EndpointSignalUnit*  GetEndpointUnit();
    };
    
}} // namespace LinuxSampler::sf2

#endif	/* __LS_SF2SIGNALUNITRACK_H__ */

