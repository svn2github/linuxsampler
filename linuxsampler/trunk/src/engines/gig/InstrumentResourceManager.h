/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
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

#ifndef __LS_GIG_INSTRUMENTRESOURCEMANAGER_H__
#define __LS_GIG_INSTRUMENTRESOURCEMANAGER_H__

#include "../../common/global.h"

#include <gig.h>

#include "../../common/global.h"
#include "../../common/Exception.h"
#include "../../common/ResourceManager.h"
#include "../../drivers/audio/AudioOutputDevice.h"
#include "../InstrumentManager.h"

//namespace libgig = gig;

namespace LinuxSampler { namespace gig {

    typedef ResourceConsumer< ::gig::Instrument> InstrumentConsumer;

}} // namespace LinuxSampler::gig

#include "EngineChannel.h"
#include "Engine.h"

namespace LinuxSampler { namespace gig {

    // just symbol prototyping
    class EngineChannel;

    /** @brief Gig instrument manager
     *
     * Manager to share gig instruments between multiple Gigasampler
     * engine channels. The engine channels Borrow() instruments when they
     * need them and HandBack() when they don't need them anymore. The
     * InstrumentResourceManager loads the corresponding gig file and gig
     * instrument if needed, if it's already in use by another engine
     * channel, then it just returns the same resource, if an gig
     * instrument / file is not needed anymore, then it will be freed from
     * memory.
     */
    class InstrumentResourceManager : public InstrumentManager, public ResourceManager<InstrumentManager::instrument_id_t, ::gig::Instrument> {
        public:
            virtual ~InstrumentResourceManager() {}
            static void OnInstrumentLoadingProgress(::gig::progress_t* pProgress);

            // implementation of derived abstract methods from 'InstrumentManager'
            virtual std::vector<instrument_id_t> Instruments();
            virtual InstrumentManager::mode_t GetMode(const instrument_id_t& ID);
            virtual void SetMode(const instrument_id_t& ID, InstrumentManager::mode_t Mode);
            virtual String GetInstrumentName(instrument_id_t ID);
        protected:
            virtual ::gig::Instrument* Create(instrument_id_t Key, InstrumentConsumer* pConsumer, void*& pArg);
            virtual void               Destroy(::gig::Instrument* pResource, void* pArg);
            virtual void               OnBorrow(::gig::Instrument* pResource, InstrumentConsumer* pConsumer, void*& pArg);
        private:
            typedef ResourceConsumer< ::gig::File> GigConsumer;

            class GigResourceManager : public ResourceManager<String, ::gig::File> {
                protected:
                    virtual ::gig::File* Create(String Key, GigConsumer* pConsumer, void*& pArg);
                    virtual void         Destroy(::gig::File* pResource, void* pArg);
                    virtual void         OnBorrow(::gig::File* pResource, GigConsumer* pConsumer, void*& pArg) {} // ignore
                public:
                    virtual ~GigResourceManager() {}
            } Gigs;

            void CacheInitialSamples(::gig::Sample* pSample, gig::EngineChannel* pEngineChannel);
    };

    /**
     * Will be thrown by the InstrumentResourceManager on errors.
     */
    class InstrumentResourceManagerException : public Exception {
        public:
            InstrumentResourceManagerException(String msg) : Exception(msg) {}
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_INSTRUMENTRESOURCEMANAGER_H__
