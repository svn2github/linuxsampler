/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#ifndef __LS_OPTIONAL_H__
#define __LS_OPTIONAL_H__

#include "LinuxSamplerException.h"

namespace LinuxSampler {

    class optional_base {
        public:
            class nothing_t { public: nothing_t() {} };

            static const nothing_t nothing;
    };

    template<class T>
    class optional : public optional_base {
        public:
            optional() {
                initialized = false;
            }

            optional(T data) {
                this->data  = data;
                initialized = true;
            }

            optional(nothing_t) {
                initialized = false;
            }

            template <class T_inner>
            optional(T_inner data) {
                this->data  = T(data);
                initialized = true;
            }

            const T& get() const throw (LinuxSamplerException) {
                if (!initialized) throw LinuxSamplerException("optional variable not initialized");
                return data;
            }

            T& get() throw (LinuxSamplerException) {
                if (!initialized) throw LinuxSamplerException("optional variable not initialized");
                return data;
            }

            optional& operator =(const optional& arg) throw (LinuxSamplerException) {
                if (!arg.initialized) LinuxSamplerException("optional variable not initialized");
                this->data  = arg.data;
                initialized = true;
            }

            optional& operator =(const T& arg) {
                this->data  = arg;
                initialized = true;
            }

            const T& operator *() const throw (LinuxSamplerException) { return get(); }
            T&       operator *()       throw (LinuxSamplerException) { return get(); }

            const T* operator ->() const throw (LinuxSamplerException) {
                if (!initialized) throw LinuxSamplerException("optional variable not initialized");
                return &data;
            }

            T* operator ->() throw (LinuxSamplerException) {
                if (!initialized) throw LinuxSamplerException("optional variable not initialized");
                return &data;
            }

            operator bool()   const { return initialized; }
            bool operator !() const { return !initialized; }

        protected:
            T    data;
            bool initialized;
    };

} // namespace LinuxSampler

#endif // __LS_OPTIONAL_H__
