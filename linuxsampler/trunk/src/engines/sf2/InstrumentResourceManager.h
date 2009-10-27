/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2009 Christian Schoenebeck                       *
 *   Copyright (C) 2009 Grigor Iliev                                       *
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

#ifndef __LS_SF2_INSTRUMENTRESOURCEMANAGER_H__
#define __LS_SF2_INSTRUMENTRESOURCEMANAGER_H__

#include "../../common/global.h"

#include <SF.h>

#include "../../common/global.h"
#include "../../common/Pool.h"
#include "../../common/ResourceManager.h"
#include "../../drivers/audio/AudioOutputDevice.h"
#include "../InstrumentManagerBase.h"
#include "../../common/ArrayList.h"

namespace LinuxSampler { namespace sf2 {

    typedef ResourceConsumer< ::sf2::InstrumentBase> InstrumentConsumer;

}} // namespace LinuxSampler::sf2

#include "../../plugins/InstrumentEditor.h"

namespace LinuxSampler { namespace sf2 {
    class Engine;
    class EngineChannel;

    /** @brief sf2 instrument manager
     *
     * Manager to share sf2 instruments between multiple sf2
     * engine channels. The engine channels Borrow() instruments when they
     * need them and HandBack() when they don't need them anymore. The
     * InstrumentResourceManager loads the corresponding sf2 file and sf2
     * instrument if needed, if it's already in use by another engine
     * channel, then it just returns the same resource, if a sf2
     * instrument / file is not needed anymore, then it will be freed from
     * memory.
     */
    class InstrumentResourceManager : public InstrumentManagerDefaultImpl< ::sf2::File, ::sf2::InstrumentBase, ::sf2::Region, ::sf2::Sample> {
        public:
            InstrumentResourceManager() : Sf2s(this) {}
            virtual ~InstrumentResourceManager() {}

            // implementation of derived abstract methods from 'InstrumentManager'
            virtual std::vector<instrument_id_t> Instruments();
            virtual String GetInstrumentName(instrument_id_t ID);
            virtual std::vector<instrument_id_t> GetInstrumentFileContent(String File) throw (InstrumentManagerException);
            virtual instrument_info_t GetInstrumentInfo(instrument_id_t ID) throw (InstrumentManagerException);

        protected:
            // implementation of derived abstract methods from 'ResourceManager'
            virtual ::sf2::InstrumentBase*  Create(instrument_id_t Key, InstrumentConsumer* pConsumer, void*& pArg);
            virtual void   Destroy(::sf2::InstrumentBase* pResource, void* pArg);
            virtual void   OnBorrow(::sf2::InstrumentBase* pResource, InstrumentConsumer* pConsumer, void*& pArg);
            virtual void   DeleteRegionIfNotUsed(::sf2::Region* pRegion, region_info_t* pRegInfo);
            virtual void   DeleteSampleIfNotUsed(::sf2::Sample* pSample, region_info_t* pRegInfo);
        private:
            typedef ResourceConsumer< ::sf2::File> Sf2Consumer;

            class Sf2ResourceManager : public ResourceManager<String, ::sf2::File> {
                protected:
                    // implementation of derived abstract methods from 'ResourceManager'
                    virtual ::sf2::File* Create(String Key, Sf2Consumer* pConsumer, void*& pArg);
                    virtual void         Destroy(::sf2::File* pResource, void* pArg);
                    virtual void         OnBorrow(::sf2::File* pResource, Sf2Consumer* pConsumer, void*& pArg) {} // ignore
                public:
                    Sf2ResourceManager(InstrumentResourceManager* parent) : parent(parent) {}
                    virtual ~Sf2ResourceManager() {}
                    friend class InstrumentResourceManager;
                private:
                    InstrumentResourceManager* parent;
            } Sf2s;

            int                     GetSfInstrumentCount(::sf2::File* pFile);
            ::sf2::InstrumentBase*  GetSfInstrument(::sf2::File* pFile, int idx);
    };

}} // namespace LinuxSampler::sf2

#endif // __LS_SF2_INSTRUMENTRESOURCEMANAGER_H__
