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

#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include <set>
#include <map>

/**
 * Interface class for consumer classes which use a resource managed
 * by the ResourceManager class.
 */
template<class T_res>
class ResourceConsumer {
    public:
        /**
         * Will be called by the ResourceManager to inform the
         * consumer that a resource currently used by him is going
         * to be updated. The consumer can then react by stopping
         * usage until resource is updated. The ResourceManager will
         * not update the resource until this method returns. This
         * method needs to be implemented by the consumer.
         *
         * @param pResource  - resource going to be updated
         * @param pUpdateArg - pointer the consumer might use to store
         *                     informations he might need when update
         *                     process was completed
         */
        virtual void ResourceToBeUpdated(T_res* pResource, void*& pUpdateArg) = 0;

        /**
         * Will be called by the ResourceManager to inform the
         * consumer that resource update was completed. This method
         * needs to be implemented by the consumer.
         *
         * @param pOldResource - (now invalid) pointer to the old
         *                       resource
         * @param pNewResource - (valid) pointer to the updated
         *                       resource
         * @param pUpdateArg   - pointer the consumer might have used when
         *                       ResourceToBeUpdated() was called
         */
        virtual void ResourceUpdated(T_res* pOldResource, T_res* pNewResource, void* pUpdateArg) = 0;
};

/**
 * Abstract base class for sharing resources between multiple consumers.
 * A consumer can borrow a resource from the ResourceManager, if the
 * resource doesn't exist yet it will be created. Other consumers will
 * just be given the same pointer to the resource then. When all consumers
 * gave back their pointer to the resource, the resource will be destroyed.
 * Descendants of this base class have to implement the (protected)
 * Create() and Destroy() methods to create and destroy a resource.
 */
template<class T_key, class T_res>
class ResourceManager {
    private:
        typedef std::set<ResourceConsumer<T_res>*> ConsumerSet;
        struct resource_entry_t {
            T_key       key;
            T_res*      resource;  ///< pointer to the resource
            ConsumerSet consumers; ///< list of all consumers who currently use the resource
            void*       arg;       ///< optional pointer the descendant might use to store informations about the resource
        };
        typedef std::map<T_key, resource_entry_t> ResourceMap;
        ResourceMap ResourceEntries;

    public:
        /**
         * Borrow a resource identified by \a Key. The ResourceManager will
         * mark the resource as in usage by the consumer given with
         * \a pConsumer. If the Resource doesn't exist yet it will be
         * created.
         *
         * @param Key       - resource identifier
         * @param pConsumer - identifier of the consumer who borrows it
         * @returns  pointer to resource
         */
        T_res* Borrow(T_key Key, ResourceConsumer<T_res>* pConsumer) {
            typename ResourceMap::iterator iterEntry = ResourceEntries.find(Key);
            if (iterEntry == ResourceEntries.end()) {
                resource_entry_t entry;
                entry.key      = Key;
                entry.resource = Create(Key, pConsumer, entry.arg);
                entry.consumers.insert(pConsumer);
                OnBorrow(entry.resource, pConsumer, entry.arg);
                ResourceEntries[Key] = entry;
                return entry.resource;
            }
            resource_entry_t& entry = iterEntry->second;
            entry.consumers.insert(pConsumer);
            OnBorrow(entry.resource, pConsumer, entry.arg);
            return entry.resource;
        }

        /**
         * Give back a resource. This tells the ResourceManager that the
         * consumer given by \a pConsumer doesn't need the resource anymore.
         * If the resource is not needed by any consumer anymore then the
         * resource will be destroyed.
         *
         * @param pResource - pointer to resource
         * @param pConsumer - identifier of the consumer who borrowed the
         *                    resource
         */
        void HandBack(T_res* pResource, ResourceConsumer<T_res>* pConsumer) {
            typename ResourceMap::iterator iter = ResourceEntries.begin();
            typename ResourceMap::iterator end  = ResourceEntries.end();
            for (; iter != end; iter++) {
                if (iter->second.resource == pResource) {
                    resource_entry_t& entry = iter->second;
                    entry.consumers.erase(pConsumer);
                    if (entry.consumers.empty()) {
                        ResourceEntries.erase(iter);
                        Destroy(entry.resource, entry.arg);
                    }
                    return;
                }
            }
        }

        /**
         * Request update of a resource.
         *
         * @param pResource - resource to be updated
         * @param pConsumer - consumer who requested the update
         */
        void Update(T_res* pResource, ResourceConsumer<T_res>* pConsumer) {
            typename ResourceMap::iterator iter = ResourceEntries.begin();
            typename ResourceMap::iterator end  = ResourceEntries.end();
            for (; iter != end; iter++) {
                if (iter->second.resource == pResource) {
                    resource_entry_t& entry = iter->second;
                    // inform all consumers about pending update
                    std::map<ResourceConsumer<T_res>*,void*> updateargs;
                    typename ConsumerSet::iterator iterCons = entry.consumers.begin();
                    typename ConsumerSet::iterator endCons  = entry.consumers.end();
                    for (; iterCons != endCons; iterCons++) {
                        if (*iterCons == pConsumer) continue;
                        void* updatearg = NULL;
                        (*iterCons)->ResourceToBeUpdated(entry.resource, updatearg);
                        if (updatearg) updateargs[*iterCons] = updatearg;
                    }
                    // update resource
                    T_res* pOldResource = entry.resource;
                    Destroy(entry.resource, entry.arg);
                    entry.resource = Create(entry.key, pConsumer, entry.arg);
                    // inform all consumers about update completed
                    iterCons = entry.consumers.begin();
                    endCons  = entry.consumers.end();
                    for (; iterCons != endCons; iterCons++) {
                        if (*iterCons == pConsumer) continue;
                        typename std::map<ResourceConsumer<T_res>*,void*>::iterator iterArg = updateargs.find(*iterCons);
                        void* updatearg = (iterArg != updateargs.end()) ? iterArg->second : NULL;
                        (*iterCons)->ResourceUpdated(pOldResource, entry.resource, updatearg);
                    }
                    return;
                }
            }
        }

    protected:
        /**
         * Has to be implemented by the descendant to create (allocate) a
         * resource identified by \a Key.
         *
         * @param Key       - identifier of the resource
         * @param pConsumer - identifier of the consumer who borrows the
         *                    resource
         * @param pArg      - pointer the descendant can use to store
         *                    informations he might need for destruction of
         *                    the resource
         * @returns  pointer to new resource
         */
        virtual T_res* Create(T_key Key, ResourceConsumer<T_res>* pConsumer, void*& pArg) = 0;

        /**
         * Has to be implemented by the descendant to destroy (free) a
         * resource pointed by \a pResource.
         *
         * @param pResource - pointer to the resource
         * @param pArg      - pointer the descendant might have used when
         *                    Create() was called to store informations
         *                    about the resource
         */
        virtual void Destroy(T_res* pResource, void* pArg) = 0;

        /**
         * Has to be implemented by the descendant to react when a consumer
         * borrows a resource (no matter if freshly created or an already
         * created one). Of course reacting is optional, but the descendant
         * at least has to provide a method with empty body.
         *
         * @param pResource - pointer to the resource
         * @param pConsumer - identifier of the consumer who borrows the
         *                    resource
         * @param pArg      - pointer the descendant might have used when
         *                    Create() was called to store informations
         *                    about the resource, this information can be
         *                    updated by the descendant here
         */
        virtual void OnBorrow(T_res* pResource, ResourceConsumer<T_res>* pConsumer, void*& pArg) = 0;
};

#endif // __RESOURCE_MANAGER__
