/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "common.h"

namespace LinuxSampler {

    VMIntExpr* VMExpr::asInt() const {
        return const_cast<VMIntExpr*>( dynamic_cast<const VMIntExpr*>(this) );
    }

    VMStringExpr* VMExpr::asString() const {
        return const_cast<VMStringExpr*>( dynamic_cast<const VMStringExpr*>(this) );
    }

} // namespace LinuxSampler
