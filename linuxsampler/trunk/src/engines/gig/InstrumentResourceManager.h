/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 by Benno Senoner and Christian Schoenebeck         *
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

#if DEBUG_HEADERS
# warning InstrumentResourceManager.h included
#endif // DEBUG_HEADERS

#include "../../common/global.h"
#include "../../common/LinuxSamplerException.h"
#include "../../common/ResourceManager.h"
#include "../../audiodriver/AudioOutputDevice.h"
#include "../../lib/fileloader/libgig/gig.h"

// preload 64k samples = 128kB of data in RAM for 16 bit mono samples
#define NUM_RAM_PRELOAD_SAMPLES 32768

//namespace libgig = gig;

namespace LinuxSampler { namespace gig {

    typedef ResourceConsumer< ::gig::Instrument> InstrumentConsumer;

}} // namespace LinuxSampler::gig

#include "Engine.h"

namespace LinuxSampler { namespace gig {

    // just symbol prototyping
    class Engine;

    /**
     * Explicitly identifies a Gigasampler instrument.
     */
    struct instrument_id_t {
        String FileName;    ///< name of the file which contains the instrument
        uint   iInstrument; ///< index of the instrument in the instrument file

        // TODO: we should extend operator<() so it will be able to detect that file x and file y are actually the same files, e.g. because one of them is a symlink / share the same inode
        bool operator<(const instrument_id_t& o) const {
            return (iInstrument < o.iInstrument || (iInstrument == o.iInstrument && FileName < o.FileName));
        }
    };

    /** Gig instrument manager
     *
     * Manager to share gig instruments between multiple Gigasampler
     * engines. The engines Borrow() instruments when they need them and
     * HandBack() when they don't need them anymore. The
     * InstrumentResourceManager loads the corresponding gig file and gig
     * instrument if needed, if it's already in use by another engine, then
     * it just returns the same resource, if an gig instrument / file is not
     * in use by any engine anymore, then it will be freed from memory.
     */
    class InstrumentResourceManager : public ResourceManager<instrument_id_t, ::gig::Instrument> {
        protected:
            virtual ::gig::Instrument* Create(instrument_id_t Key, InstrumentConsumer* pConsumer, void*& pArg);
            virtual void               Destroy(::gig::Instrument* pResource, void* pArg);
            virtual void               OnBorrow(::gig::Instrument* pResource, InstrumentConsumer* pConsumer, void*& pArg);
        private:
            struct instr_entry_t {
                ::gig::File* pGig;
                uint         iInstrument;
                uint         MaxSamplesPerCycle; ///< if some engine requests an already allocated instrument with a higher value, we have to reallocate the instrument
            };

            typedef ResourceConsumer< ::gig::File> GigConsumer;

            class GigResourceManager : public ResourceManager<String, ::gig::File> {
                protected:
                    virtual ::gig::File* Create(String Key, GigConsumer* pConsumer, void*& pArg);
                    virtual void         Destroy(::gig::File* pResource, void* pArg);
                    virtual void         OnBorrow(::gig::File* pResource, GigConsumer* pConsumer, void*& pArg) {} // ignore
            } Gigs;

            void CacheInitialSamples(::gig::Sample* pSample, gig::Engine* pEngine);
    };

    /**
     * Will be thrown by the InstrumentResourceManager on errors.
     */
    class InstrumentResourceManagerException : public LinuxSamplerException {
        public:
            InstrumentResourceManagerException(String msg) : LinuxSamplerException(msg) {}
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_INSTRUMENTRESOURCEMANAGER_H__
