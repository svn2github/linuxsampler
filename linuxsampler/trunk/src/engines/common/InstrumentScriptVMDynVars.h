/*
 * Copyright (c) 2016 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#ifndef LS_INSTRSCRIPTVMDYNVARS_H
#define LS_INSTRSCRIPTVMDYNVARS_H

#include "../../common/global.h"
#include "../../scriptvm/CoreVMDynVars.h"

namespace LinuxSampler {

    class InstrumentScriptVM;

    /**
     * Implements the built-in $ENGINE_UPTIME script variable.
     */
    class InstrumentScriptVMDynVar_ENGINE_UPTIME : public VMDynIntVar {
    public:
        InstrumentScriptVMDynVar_ENGINE_UPTIME(InstrumentScriptVM* parent) : m_vm(parent) {}
        bool isAssignable() const OVERRIDE { return false; }
        int evalInt() OVERRIDE;
    protected:
        InstrumentScriptVM* m_vm;
    };

} // namespace LinuxSampler

#endif // LS_INSTRSCRIPTVMDYNVARS_H
