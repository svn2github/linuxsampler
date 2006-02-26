/***************************************************************************
 *                                                                         *
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

#ifndef __LS_ENGINECHANNELFACTORY_H__
#define __LS_ENGINECHANNELFACTORY_H__

#include <set>

#include "common/EngineChannel.h"

namespace LinuxSampler {

    class EngineChannelFactory {
        public:
            static EngineChannel* Create(String EngineType) throw (LinuxSamplerException);
            static void Destroy(EngineChannel* pEngineChannel);
            static const std::set<EngineChannel*>& EngineChannelInstances();
    };

} // namespace LinuxSampler

#endif // __LS_ENGINECHANNELFACTORY_H__
