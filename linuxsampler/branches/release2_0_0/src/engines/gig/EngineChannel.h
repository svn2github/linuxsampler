/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2008 Christian Schoenebeck                       *
 *   Copyright (C) 2009 - 2013 Christian Schoenebeck and Grigor Iliev      *
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

#ifndef __LS_GIG_ENGINECHANNEL_H__
#define	__LS_GIG_ENGINECHANNEL_H__

#include "../AbstractEngine.h"
#include "../EngineChannelBase.h"
#include "../EngineChannelFactory.h"
#include "Voice.h"
#include <gig.h>

namespace LinuxSampler { namespace gig {
    class Voice;

    class EngineChannel: public LinuxSampler::EngineChannelBase<Voice, ::gig::DimensionRegion, ::gig::Instrument> {
        public:
            virtual void SendProgramChange(uint8_t Program);
            virtual void LoadInstrument();
            virtual void ResetInternal();
            virtual String InstrumentFileName();
            virtual String InstrumentFileName(int index);

            virtual AbstractEngine::Format GetEngineFormat();

            friend class Voice;
            friend class Engine;
            friend class LinuxSampler::EngineChannelFactory;

        protected:
            EngineChannel();
            virtual ~EngineChannel();

            float CurrentKeyDimension;      ///< Current value (0-1.0) for the keyboard dimension, altered by pressing a keyswitching key.

            virtual void ProcessKeySwitchChange(int key);

    };

}} // namespace LinuxSampler::gig

#endif	/* __LS_GIG_ENGINECHANNEL_H__ */
