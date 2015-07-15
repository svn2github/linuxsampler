/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#ifndef LS_GIG_INSTRSCRIPTVMFUNCTIONS_H
#define LS_GIG_INSTRSCRIPTVMFUNCTIONS_H

#include "../common/InstrumentScriptVMFunctions.h"

namespace LinuxSampler { namespace gig {

    class InstrumentScriptVM;

    /**
     * Built-in script function:
     * 
     *     gig_set_dim_zone(event_id, dimension, zone)
     */
    class InstrumentScriptVMFunction_gig_set_dim_zone : public VMEmptyResultFunction {
    public:
        InstrumentScriptVMFunction_gig_set_dim_zone(InstrumentScriptVM* parent);
        int minRequiredArgs() const { return 3; }
        int maxAllowedArgs() const { return 3; }
        bool acceptsArgType(int iArg, ExprType_t type) const;
        ExprType_t argType(int iArg) const { return INT_EXPR; }
        VMFnResult* exec(VMFnArgs* args);
    protected:
        InstrumentScriptVM* m_vm;
    };

}} // namespace LinuxSampler::gig

#endif // LS_GIG_INSTRSCRIPTVMFUNCTIONS_H
