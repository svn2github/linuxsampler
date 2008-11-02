/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2006-2008 Andreas Persson                               *
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
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,                *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#ifndef SYNCHRONIZEDCONFIG_H
#define SYNCHRONIZEDCONFIG_H

#include <set>
#include <unistd.h>
#include "lsatomic.h"

namespace LinuxSampler {

    /**
     * Thread safe management of configuration data, where the data is
     * updated by a single non real time thread and read by a number
     * of real time threads.
     *
     * The synchronization is achieved by using two instances of the
     * configuration data. The non real time thread gets access to the
     * instance not currently in use by the real time threads by
     * calling GetConfigForUpdate(). After the data is updated, the
     * non real time thread must call SwitchConfig() and redo the
     * update on the other instance. SwitchConfig() blocks until it is
     * safe to modify the other instance.
     *
     * The real time threads need one Reader object each to access the
     * configuration data. This object must be created outside the
     * real time thread. The Lock() function returns a reference to
     * the data to be read, and Unlock() must be called when finished
     * reading the data. (Neither Lock nor Unlock will block the real
     * time thread, or use any system calls.)
     */
    template<class T>
    class SynchronizedConfig {
        public:
            SynchronizedConfig();

            // methods for the real time thread

            class Reader {
                public:
                    /**
                     * Gets the configuration object for use by the
                     * real time thread. The object is safe to use
                     * (read only) until Unlock() is called.
                     *
                     * @returns a reference to the configuration
                     *          object to be read by the real time
                     *          thread
                     */
                    const T& Lock() {
                        lock.store(1, memory_order_relaxed);
                        atomic_thread_fence(memory_order_seq_cst);
                        return parent.config[parent.indexAtomic.load(
                                memory_order_acquire)];
                    }

                    /**
                     * Unlock the configuration object. Unlock() must
                     * be called by the real time thread after it has
                     * finished reading the configuration object. If
                     * the non real time thread is waiting in
                     * SwitchConfig() it will be awaken when no real
                     * time threads are locked anymore.
                     */
                    void Unlock() {
                        atomic_thread_fence(memory_order_release);
                        lock.store(0, memory_order_relaxed);
                        flag.store(0, memory_order_relaxed);
                    }

                    Reader(SynchronizedConfig& config);
                    ~Reader();
                private:
                    friend class SynchronizedConfig;
                    SynchronizedConfig& parent;
                    atomic<int> lock;
                    atomic<int> flag;
                    Reader *next; // only used locally in SwitchConfig
            };


            // methods for the non real time thread

            /**
             * Gets the configuration object for use by the non real
             * time thread. The object returned is not in use by the
             * real time thread, so it can safely be updated. After
             * the update is done, the non real time thread must call
             * SwitchConfig() and the same update must be done again.
             *
             * @returns a reference to the configuration object to be
             *          updated by the non real time thread
             */
            T& GetConfigForUpdate();

            /**
             * Atomically switch the newly updated configuration
             * object with the one used by the real time thread, then
             * wait for the real time thread to finish working with
             * the old object before returning the old object.
             * SwitchConfig() must be called by the non real time
             * thread after an update has been done, and the object
             * returned must be updated in the same way as the first.
             *
             * @returns a reference to the configuration object to be
             *          updated by the non real time thread
             */
            T& SwitchConfig();

        private:
            atomic<int> indexAtomic;
            int updateIndex;
            T config[2];
            std::set<Reader*> readers;
    };

    template<class T> SynchronizedConfig<T>::SynchronizedConfig() :
        indexAtomic(0) {
        updateIndex = 1;
    }

    template<class T> T& SynchronizedConfig<T>::GetConfigForUpdate() {
        return config[updateIndex];
    }

    template<class T> T& SynchronizedConfig<T>::SwitchConfig() {
        indexAtomic.store(updateIndex, memory_order_release);
        atomic_thread_fence(memory_order_seq_cst);

        // first put all locking readers in a linked list
        Reader* lockingReaders = 0;
        for (typename std::set<Reader*>::iterator iter = readers.begin() ;
             iter != readers.end() ;
             iter++) {
            (*iter)->flag.store(1, memory_order_relaxed);
            if ((*iter)->lock.load(memory_order_acquire) &&
                (*iter)->flag.load(memory_order_acquire)) {
                (*iter)->next = lockingReaders;
                lockingReaders = *iter;
            }
        }

        // wait until there are no locking readers left
        while (lockingReaders) {
            usleep(50000);
            Reader** prev = &lockingReaders;
            for (Reader* p = lockingReaders ; p ; p = p->next) {
               if (p->lock.load(memory_order_acquire) &&
                   p->flag.load(memory_order_acquire)) prev = &p->next;
                else *prev = p->next; // unlink
            }
        }

        updateIndex ^= 1;
        return config[updateIndex];
    }


    // ----- Reader ----

    template <class T>
    SynchronizedConfig<T>::Reader::Reader(SynchronizedConfig& config) :
        parent(config), lock(0), flag(0) {
        parent.readers.insert(this);
    }

    template <class T>
    SynchronizedConfig<T>::Reader::~Reader() {
        parent.readers.erase(this);
    }

} // namespace LinuxSampler

#endif
