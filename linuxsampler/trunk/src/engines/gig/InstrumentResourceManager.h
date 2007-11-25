/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2007 Christian Schoenebeck                       *
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
#include "../../common/ResourceManager.h"
#include "../../drivers/audio/AudioOutputDevice.h"
#include "../InstrumentManager.h"

//namespace libgig = gig;

namespace LinuxSampler { namespace gig {

    typedef ResourceConsumer< ::gig::Instrument> InstrumentConsumer;

}} // namespace LinuxSampler::gig

#include "EngineChannel.h"
#include "Engine.h"
#include "../../plugins/InstrumentEditor.h"

namespace LinuxSampler { namespace gig {

    // just symbol prototyping
    class EngineChannel;
    class Engine;

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
    class InstrumentResourceManager : public InstrumentManager, public ResourceManager<InstrumentManager::instrument_id_t, ::gig::Instrument>, public InstrumentEditorListener {
        public:
            InstrumentResourceManager() : Gigs(this) {}
            virtual ~InstrumentResourceManager() {}
            static void OnInstrumentLoadingProgress(::gig::progress_t* pProgress);

            // implementation of derived abstract methods from 'InstrumentManager'
            virtual std::vector<instrument_id_t> Instruments();
            virtual InstrumentManager::mode_t GetMode(const instrument_id_t& ID);
            virtual void SetMode(const instrument_id_t& ID, InstrumentManager::mode_t Mode);
            virtual String GetInstrumentName(instrument_id_t ID);
            virtual String GetInstrumentDataStructureName(instrument_id_t ID);
            virtual String GetInstrumentDataStructureVersion(instrument_id_t ID);
            virtual void LaunchInstrumentEditor(instrument_id_t ID) throw (InstrumentManagerException);
            virtual std::vector<instrument_id_t> GetInstrumentFileContent(String File) throw (InstrumentManagerException);
            virtual instrument_info_t GetInstrumentInfo(instrument_id_t ID) throw (InstrumentManagerException);

            // implementation of derived abstract methods from 'InstrumentEditorListener'
            virtual void OnInstrumentEditorQuit(InstrumentEditor* pSender);
            virtual void OnSamplesToBeRemoved(std::set<void*> Samples, InstrumentEditor* pSender);
            virtual void OnSamplesRemoved(InstrumentEditor* pSender);
            virtual void OnDataStructureToBeChanged(void* pStruct, String sStructType, InstrumentEditor* pSender);
            virtual void OnDataStructureChanged(void* pStruct, String sStructType, InstrumentEditor* pSender);
            virtual void OnSampleReferenceChanged(void* pOldSample, void* pNewSample, InstrumentEditor* pSender);

            void HandBackInstrument(::gig::Instrument* pResource, InstrumentConsumer* pConsumer,
                                    ::gig::DimensionRegion** dimRegionsInUse);
            void HandBackDimReg(::gig::DimensionRegion* pDimReg);

        protected:
            // implementation of derived abstract methods from 'ResourceManager'
            virtual ::gig::Instrument* Create(instrument_id_t Key, InstrumentConsumer* pConsumer, void*& pArg);
            virtual void               Destroy(::gig::Instrument* pResource, void* pArg);
            virtual void               OnBorrow(::gig::Instrument* pResource, InstrumentConsumer* pConsumer, void*& pArg);
        private:
            typedef ResourceConsumer< ::gig::File> GigConsumer;

            class GigResourceManager : public ResourceManager<String, ::gig::File> {
                protected:
                    // implementation of derived abstract methods from 'ResourceManager'
                    virtual ::gig::File* Create(String Key, GigConsumer* pConsumer, void*& pArg);
                    virtual void         Destroy(::gig::File* pResource, void* pArg);
                    virtual void         OnBorrow(::gig::File* pResource, GigConsumer* pConsumer, void*& pArg) {} // ignore
                public:
                    GigResourceManager(InstrumentResourceManager* parent) : parent(parent) {}
                    virtual ~GigResourceManager() {}
                private:
                    InstrumentResourceManager* parent;
            } Gigs;

            void CacheInitialSamples(::gig::Sample* pSample, gig::EngineChannel* pEngineChannel);
            void CacheInitialSamples(::gig::Sample* pSample, gig::Engine* pEngine);
            void UncacheInitialSamples(::gig::Sample* pSample);
            std::vector< ::gig::Instrument*> GetInstrumentsCurrentlyUsedOf(::gig::File* pFile, bool bLock);
            std::set<gig::Engine*> GetEnginesUsing(::gig::Instrument* pFile, bool bLock);
            std::set<gig::Engine*> GetEnginesUsing(::gig::File* pFile, bool bLock);
            bool SampleReferencedByInstrument(::gig::Sample* pSample, ::gig::Instrument* pInstrument);
            void SuspendEnginesUsing(::gig::Instrument* pInstrument);
            void SuspendEnginesUsing(::gig::File* pFile);
            void ResumeAllEngines();

            struct dimreg_info_t {
                int           refCount;
                ::gig::File*  file;
                ::RIFF::File* riff;
            };
            Mutex DimRegInfoMutex; ///< protects the DimRegInfo and SampleRefCount maps from concurrent access by the instrument loader and disk threads
            std::map< ::gig::DimensionRegion*, dimreg_info_t> DimRegInfo; ///< contains dimension regions that are still in use but belong to released instrument
            std::map< ::gig::Sample*, int> SampleRefCount; ///< contains samples that are still in use but belong to a released instrument

            Mutex InstrumentEditorProxiesMutex; ///< protects the 'InstrumentEditorProxies' map
            std::map<InstrumentEditor*, InstrumentConsumer*> InstrumentEditorProxies; ///< here we store the objects that react on instrument specific notifications on behalf of the respective instrument editor
            std::set<Engine*> suspendedEngines; ///< all engines currently completely suspended
            Mutex             suspendedEnginesMutex; ///< protects 'suspendedEngines' set
    };

}} // namespace LinuxSampler::gig

#endif // __LS_GIG_INSTRUMENTRESOURCEMANAGER_H__
