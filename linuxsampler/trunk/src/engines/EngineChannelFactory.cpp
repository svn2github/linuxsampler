/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2005, 2006 Christian Schoenebeck                        *
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

#include "EngineChannelFactory.h"

#include <strings.h>

#include "gig/EngineChannel.h"

#if HAVE_SF2
#include "sf2/EngineChannel.h"
#endif

#include "sfz/EngineChannel.h"

namespace LinuxSampler {
    class LockedChannel {
        public:
            const EngineChannel* pChannel;
            bool bDestroyed;

            LockedChannel(const EngineChannel* pChannel)  {
                this->pChannel = pChannel;
                bDestroyed = false;
            }
    };

    class LockedChannelList {
        public:
            void Add(const EngineChannel* pChannel) {
                vChannelList.push_back(LockedChannel(pChannel));
            }

            bool IsDestroyed(const EngineChannel* pChannel) {
                LockedChannel* pLockedChannel = get(pChannel);
                if (pLockedChannel == NULL) return false;
                return pLockedChannel->bDestroyed;
            }

            void SetDestroyed(const EngineChannel* pChannel, bool bDestroyed = true) {
                LockedChannel* pLockedChannel = get(pChannel);
                if (pLockedChannel == NULL) return;
                pLockedChannel->bDestroyed = bDestroyed;
            }

            void Remove(const EngineChannel* pChannel) {
                std::vector<LockedChannel>::iterator it = vChannelList.begin();
                for (; it != vChannelList.end(); it++) {
                    if ((*it).pChannel == pChannel) {
                        vChannelList.erase(it);
                        return;
                    }
                }
            }

            bool Contains(const EngineChannel* pChannel) {
                return get(pChannel) != NULL;
            }

        private:
            std::vector<LockedChannel> vChannelList;

            LockedChannel* get(const EngineChannel* pChannel) {
                for (int i = 0; i < vChannelList.size(); i++) {
                    if (vChannelList[i].pChannel == pChannel) {
                        return &vChannelList[i];
                    }
                }

                return NULL;
            }
    } lockedChannels;

    Mutex EngineChannelFactory::LockedChannelsMutex;

    void EngineChannelFactory::SetDeleteEnabled(const EngineChannel* pEngineChannel, bool enable) {
        LockedChannelsMutex.Lock();
        if (!enable) {
            if (!lockedChannels.Contains(pEngineChannel)) lockedChannels.Add(pEngineChannel);
            LockedChannelsMutex.Unlock();
        } else {
            bool b = lockedChannels.IsDestroyed(pEngineChannel);
            lockedChannels.Remove(pEngineChannel);
            LockedChannelsMutex.Unlock();

            if (b) delete pEngineChannel;
        }
    }

    // all currently existing engine channel instances
    static std::set<LinuxSampler::EngineChannel*> engineChannels;

    LinuxSampler::EngineChannel* EngineChannelFactory::Create(String EngineType) throw (Exception) {
        if (!strcasecmp(EngineType.c_str(),"GigEngine") || !strcasecmp(EngineType.c_str(),"gig")) {
            LinuxSampler::EngineChannel* pEngineChannel = new gig::EngineChannel;
            engineChannels.insert(pEngineChannel);
            return pEngineChannel;
        } else if (!strcasecmp(EngineType.c_str(),"sf2")) {
        #if HAVE_SF2
            LinuxSampler::EngineChannel* pEngineChannel = new sf2::EngineChannel;
            engineChannels.insert(pEngineChannel);
            return pEngineChannel;
        #else
            throw Exception("LinuxSampler is not compiled with SF2 support");
        #endif
        } else if (!strcasecmp(EngineType.c_str(),"sfz")) {
            LinuxSampler::EngineChannel* pEngineChannel = new sfz::EngineChannel;
            engineChannels.insert(pEngineChannel);
            return pEngineChannel;
        }
        throw Exception("Unknown engine type");
    }

    void EngineChannelFactory::Destroy(LinuxSampler::EngineChannel* pEngineChannel) {
        pEngineChannel->RemoveAllFxSendCountListeners();
        engineChannels.erase(pEngineChannel);

        // Postpone the deletion of the specified EngineChannel if needed (bug #113)
        LockedChannelsMutex.Lock();
        if (lockedChannels.Contains(pEngineChannel)) {
            lockedChannels.SetDestroyed(pEngineChannel);
            pEngineChannel->SetSamplerChannel(NULL);
            LockedChannelsMutex.Unlock();
            return;
        }
        LockedChannelsMutex.Unlock();
        ///////

        delete pEngineChannel;
    }

    const std::set<LinuxSampler::EngineChannel*>& EngineChannelFactory::EngineChannelInstances() {
        return engineChannels;
    }

} // namespace LinuxSampler
