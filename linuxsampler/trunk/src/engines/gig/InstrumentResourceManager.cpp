/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 Christian Schoenebeck                              *
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

#include <sstream>

#include "InstrumentResourceManager.h"

// We need to know the maximum number of sample points which are going to
// be processed for each render cycle of the audio output driver, to know
// how much initial sample points we need to cache into RAM. If the given
// sampler channel does not have an audio output device assigned yet
// though, we simply use this default value.
#define GIG_RESOURCE_MANAGER_DEFAULT_MAX_SAMPLES_PER_CYCLE     128

namespace LinuxSampler { namespace gig {

    ::gig::Instrument* InstrumentResourceManager::Create(instrument_id_t Key, InstrumentConsumer* pConsumer, void*& pArg) {
        // get gig file from inernal gig file manager
        ::gig::File* pGig = Gigs.Borrow(Key.FileName, (GigConsumer*) Key.iInstrument); // conversion kinda hackish :/

        dmsg(1,("Loading gig instrument..."));
        ::gig::Instrument* pInstrument = pGig->GetInstrument(Key.iInstrument);
        if (!pInstrument) {
            std::stringstream msg;
            msg << "There's no instrument with index " << Key.iInstrument << ".";
            throw InstrumentResourceManagerException(msg.str());
        }
        pGig->GetFirstSample(); // just to force complete instrument loading
        dmsg(1,("OK\n"));

        // cache initial samples points (for actually needed samples)
        dmsg(1,("Caching initial samples..."));
        ::gig::Region* pRgn = pInstrument->GetFirstRegion();
        while (pRgn) {
            if (pRgn->GetSample() && !pRgn->GetSample()->GetCache().Size) {
                dmsg(2,("C"));
                CacheInitialSamples(pRgn->GetSample(), dynamic_cast<gig::EngineChannel*>(pConsumer));
            }
            for (uint i = 0; i < pRgn->DimensionRegions; i++) {
                CacheInitialSamples(pRgn->pDimensionRegions[i]->pSample, dynamic_cast<gig::EngineChannel*>(pConsumer));
            }

            pRgn = pInstrument->GetNextRegion();
        }
        dmsg(1,("OK\n"));

        // we need the following for destruction later
        instr_entry_t* pEntry = new instr_entry_t;
        pEntry->iInstrument   = Key.iInstrument;
        pEntry->pGig          = pGig;
        
        gig::EngineChannel* pEngineChannel = dynamic_cast<gig::EngineChannel*>(pConsumer);
        // and we save this to check if we need to reallocate for a engine with higher value of 'MaxSamplesPerSecond'
        pEntry->MaxSamplesPerCycle =
            (pEngineChannel->GetEngine()) ? dynamic_cast<gig::Engine*>(pEngineChannel->GetEngine())->pAudioOutputDevice->MaxSamplesPerCycle()
                                          : GIG_RESOURCE_MANAGER_DEFAULT_MAX_SAMPLES_PER_CYCLE;
        pArg = pEntry;

        return pInstrument;
    }

    void InstrumentResourceManager::Destroy( ::gig::Instrument* pResource, void* pArg) {
        instr_entry_t* pEntry = (instr_entry_t*) pArg;
        Gigs.HandBack(pEntry->pGig, (GigConsumer*) pEntry->iInstrument); // conversion kinda hackish :/
        delete pEntry;
    }

    void InstrumentResourceManager::OnBorrow(::gig::Instrument* pResource, InstrumentConsumer* pConsumer, void*& pArg) {
        instr_entry_t* pEntry = (instr_entry_t*) pArg;
        gig::EngineChannel* pEngineChannel = dynamic_cast<gig::EngineChannel*>(pConsumer);
        uint maxSamplesPerCycle =
            (pEngineChannel->GetEngine()) ? dynamic_cast<gig::Engine*>(pEngineChannel->GetEngine())->pAudioOutputDevice->MaxSamplesPerCycle()
                                          : GIG_RESOURCE_MANAGER_DEFAULT_MAX_SAMPLES_PER_CYCLE;
        if (pEntry->MaxSamplesPerCycle < maxSamplesPerCycle) {
            Update(pResource, pConsumer);
        }
    }

    /**
     *  Caches a certain size at the beginning of the given sample in RAM. If the
     *  sample is very short, the whole sample will be loaded into RAM and thus
     *  no disk streaming is needed for this sample. Caching an initial part of
     *  samples is needed to compensate disk reading latency.
     *
     *  @param pSample - points to the sample to be cached
     *  @param pEngineChannel - pointer to Gig Engine Channel which caused this call
     */
    void InstrumentResourceManager::CacheInitialSamples(::gig::Sample* pSample, gig::EngineChannel* pEngineChannel) {
        if (!pSample || pSample->GetCache().Size || !pSample->SamplesTotal) return;
        if (pSample->SamplesTotal <= NUM_RAM_PRELOAD_SAMPLES) {
            // Sample is too short for disk streaming, so we load the whole
            // sample into RAM and place 'pAudioIO->FragmentSize << MAX_PITCH'
            // number of '0' samples (silence samples) behind the official buffer
            // border, to allow the interpolator do it's work even at the end of
            // the sample.
            dmsg(3,("Caching whole sample (sample name: \"%s\", sample size: %d)\n", pSample->pInfo->Name.c_str(), pSample->SamplesTotal));
            const uint maxSamplesPerCycle =
                (pEngineChannel->GetEngine()) ? dynamic_cast<gig::Engine*>(pEngineChannel->GetEngine())->pAudioOutputDevice->MaxSamplesPerCycle()
                                              : GIG_RESOURCE_MANAGER_DEFAULT_MAX_SAMPLES_PER_CYCLE;
            const uint silenceSamples = (maxSamplesPerCycle << MAX_PITCH) + 3;
            ::gig::buffer_t buf = pSample->LoadSampleDataWithNullSamplesExtension(silenceSamples);
            dmsg(4,("Cached %d Bytes, %d silence bytes.\n", buf.Size, buf.NullExtensionSize));
        }
        else { // we only cache NUM_RAM_PRELOAD_SAMPLES and stream the other sample points from disk
            pSample->LoadSampleData(NUM_RAM_PRELOAD_SAMPLES);
        }

        if (!pSample->GetCache().Size) std::cerr << "Unable to cache sample - maybe memory full!" << std::endl << std::flush;
    }



    // internal gig file manager

    ::gig::File* InstrumentResourceManager::GigResourceManager::Create(String Key, GigConsumer* pConsumer, void*& pArg) {
        dmsg(1,("Loading gig file \'%s\'...", Key.c_str()));
        ::RIFF::File* pRIFF = new ::RIFF::File(Key);
        ::gig::File* pGig   = new ::gig::File(pRIFF);
        pArg                = pRIFF;
        dmsg(1,("OK\n"));
        return pGig;
    }

    void InstrumentResourceManager::GigResourceManager::Destroy(::gig::File* pResource, void* pArg) {
        dmsg(1,("Freeing gig file from memory..."));
        delete pResource;
        delete (::RIFF::File*) pArg;
        dmsg(1,("OK\n"));
    }

}} // namespace LinuxSampler::gig
