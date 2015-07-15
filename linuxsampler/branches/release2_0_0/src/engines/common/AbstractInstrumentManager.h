/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#ifndef LS_ABSTRACTINSTRUMENTMANAGER_H
#define LS_ABSTRACTINSTRUMENTMANAGER_H

#include "../InstrumentManager.h"
#include "../../common/ResourceManager.h"
#include "../../common/global_private.h"
#include "InstrumentScriptVM.h"

namespace LinuxSampler {

    typedef ResourceConsumer<VMParserContext> InstrumentScriptConsumer;

    class AbstractInstrumentManager : public InstrumentManager {
    public:
        AbstractInstrumentManager() { }
        virtual ~AbstractInstrumentManager() { }

        class ScriptResourceManager : public ResourceManager<String, VMParserContext> {
        public:
            ScriptResourceManager() {}
            virtual ~ScriptResourceManager() {}
        protected:
            // implementation of derived abstract methods from 'ResourceManager'
            virtual VMParserContext* Create(String Key, InstrumentScriptConsumer* pConsumer, void*& pArg);
            virtual void Destroy(VMParserContext* pResource, void* pArg);
            virtual void OnBorrow(VMParserContext* pResource, InstrumentScriptConsumer* pConsumer, void*& pArg) {} // ignore
        } scripts;
    };
    
} // namespace LinuxSampler

#endif // LS_ABSTRACTINSTRUMENTMANAGER_H
