/*
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * http://www.linuxsampler.org
 *
 * This file is part of LinuxSampler and released under the same terms.
 * See README file for details.
 */

#include "common.h"
#include <iostream>

namespace LinuxSampler {

    VMIntExpr* VMExpr::asInt() const {
        return const_cast<VMIntExpr*>( dynamic_cast<const VMIntExpr*>(this) );
    }

    VMStringExpr* VMExpr::asString() const {
        return const_cast<VMStringExpr*>( dynamic_cast<const VMStringExpr*>(this) );
    }

    void VMFunction::wrnMsg(const String& txt) {
        std::cout << "[ScriptVM] " << txt << std::endl;
    }

    void VMFunction::errMsg(const String& txt) {
        std::cerr << "[ScriptVM] " << txt << std::endl;
    }

} // namespace LinuxSampler
