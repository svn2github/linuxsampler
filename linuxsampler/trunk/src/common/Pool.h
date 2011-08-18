/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *   Copyright (C) 2005 - 2008 Christian Schoenebeck                       *
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

#ifndef __LS_POOL_H__
#define __LS_POOL_H__

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

// we just use exceptions for debugging, better not in the final realtime thread !
#ifndef CONFIG_RT_EXCEPTIONS
# define CONFIG_RT_EXCEPTIONS 0
#endif

#if CONFIG_RT_EXCEPTIONS
# include <stdexcept>
# include <string>
#endif // CONFIG_RT_EXCEPTIONS

#if CONFIG_DEVMODE
# include <string>
# include <iostream>
const std::string __err_msg_iterator_invalidated = "Pool/RTList iterator invalidated";
#endif // CONFIG_DEVMODE

const std::string __err_msg_resize_while_in_use = "Pool::resizePool() ERROR: elements still in use!";

// just symbol prototyping
template<typename T> class Pool;
template<typename T> class RTList;

template<typename T>
class RTListBase {
    protected:
        template<typename T1>
        struct _Node {
            _Node<T1>* next;
            _Node<T1>* prev;
            T1* data;
            #if CONFIG_DEVMODE
            RTListBase<T1>* list; // list to which this node currently belongs to
            #endif // CONFIG_DEVMODE

            _Node() {
                next = NULL;
                prev = NULL;
                data = NULL;
                #if CONFIG_DEVMODE
                list = NULL;
                #endif // CONFIG_DEVMODE
            }
        };
        typedef _Node<T> Node;

    public:
        template<typename T1>
        class _Iterator {
            public:
                _Iterator() {
                    current  = NULL;
                    fallback = NULL;
                    #if CONFIG_DEVMODE
                    list = NULL;
                    #endif // CONFIG_DEVMODE
                }

                /// prefix increment op.
                inline _Iterator& operator++() {
                    #if CONFIG_DEVMODE
                    if (!isValid()) {
                        #if CONFIG_RT_EXCEPTIONS
                        throw std::runtime_error(__err_msg_iterator_invalidated);
                        #else
                        std::cerr << __err_msg_iterator_invalidated << std::endl << std::flush;
                        return *(_Iterator*)NULL; // force segfault if iterator became invalidated
                        #endif // CONFIG_RT_EXCEPTIONS
                    }
                    #endif // CONFIG_DEVMODE
                    fallback = current;
                    current  = current->next;
                    return *this;
                }

                /// postfix increment op.
                inline _Iterator operator++(int) {
                    _Iterator preval = *this;
                    ++*this; // use prefix operator implementation
                    return preval;
                }

                /// prefix decrement op.
                inline _Iterator& operator--() {
                    #if CONFIG_DEVMODE
                    if (!isValid()) {
                        #if CONFIG_RT_EXCEPTIONS
                        throw std::runtime_error(__err_msg_iterator_invalidated);
                        #else
                        std::cerr << __err_msg_iterator_invalidated << std::endl << std::flush;
                        return *(_Iterator*)NULL; // force segfault if iterator became invalidated
                        #endif // CONFIG_RT_EXCEPTIONS
                    }
                    #endif // CONFIG_DEVMODE
                    fallback = current;
                    current  = current->prev;
                    return *this;
                }

                /// postfix decrement op.
                inline _Iterator operator--(int) {
                    _Iterator preval = *this;
                    --*this; // use prefix operator implementation
                    return preval;
                }

                inline T1& operator*() {
                    #if CONFIG_DEVMODE
                    if (!isValid()) { // if iterator became invalidated
                        #if CONFIG_RT_EXCEPTIONS
                        throw std::runtime_error(__err_msg_iterator_invalidated);
                        #else
                        std::cerr << __err_msg_iterator_invalidated << std::endl << std::flush;
                        return *((T1*)NULL); // force segfault if iterator became invalidated
                        #endif // CONFIG_RT_EXCEPTIONS
                    }
                    #endif // CONFIG_DEVMODE
                    return *current->data;

                }

                inline T1* operator->() {
                    #if CONFIG_DEVMODE
                    if (!isValid()) { // if iterator became invalidated
                        #if CONFIG_RT_EXCEPTIONS
                        throw std::runtime_error(__err_msg_iterator_invalidated);
                        #else
                        std::cerr << __err_msg_iterator_invalidated << std::endl << std::flush;
                        return (T1*)NULL; // force segfault if iterator became invalidated
                        #endif // CONFIG_RT_EXCEPTIONS
                    }
                    #endif // CONFIG_DEVMODE
                    return current->data;
                }

                inline bool operator==(const _Iterator<T1> other) {
                    return current == other.current;
                }

                inline bool operator!=(const _Iterator<T1> other) {
                    return current != other.current;
                }

                inline operator bool() const {
                    return current && current->data;
                }

                inline bool operator!() const {
                    return !(current && current->data);
                }

                inline _Iterator moveToEndOf(RTListBase<T1>* pDstList) {
                    detach();
                    pDstList->append(*this);
                    _Iterator iterOnDstList = _Iterator(current);
                    current = fallback;
                    return iterOnDstList;
                }

                inline _Iterator moveToBeginOf(RTListBase<T1>* pDstList) {
                    detach();
                    pDstList->prepend(*this);
                    _Iterator iterOnDstList = _Iterator(current);
                    current = fallback;
                    return iterOnDstList;
                }

                #if CONFIG_DEVMODE
                inline bool isValid() {
                    return current->list == list;
                }
                #endif // CONFIG_DEVMODE

            protected:
                Node* current;
                Node* fallback;
                enum dir_t {
                    dir_forward,
                    dir_backward
                };
                #if CONFIG_DEVMODE
                RTListBase<T1>* list;
                #endif // CONFIG_DEVMODE

                _Iterator(Node* pNode, dir_t direction = dir_forward) {
                    current  = pNode;
                    fallback = (direction == dir_forward) ? pNode->prev : pNode->next;
                    #if CONFIG_DEVMODE
                    list = pNode->list;
                    #endif // CONFIG_DEVMODE
                }

                inline Node* node() {
                    #if CONFIG_DEVMODE
                    #if CONFIG_RT_EXCEPTIONS
                    if (isValid()) return current;
                    else throw std::runtime_error(__err_msg_iterator_invalidated);
                    #else
                    return (isValid()) ? current : (Node*)NULL; // force segfault if iterator became invalidated
                    #endif // CONFIG_RT_EXCEPTIONS
                    #else
                    return current;
                    #endif // CONFIG_DEVMODE
                }

                inline void detach() {
                    RTListBase<T1>::detach(*this);
                }

                friend class RTListBase<T1>;
                friend class RTList<T1>;
                friend class Pool<T1>;
        };
        typedef _Iterator<T> Iterator;

        inline Iterator first() {
            return Iterator(_begin.next, Iterator::dir_forward);
        }

        inline Iterator last() {
            return Iterator(_end.prev, Iterator::dir_backward);
        }

        inline Iterator begin() {
            return Iterator(&_begin, Iterator::dir_forward);
        }

        inline Iterator end() {
            return Iterator(&_end, Iterator::dir_backward);
        }

        inline bool isEmpty() {
            return _begin.next == &_end;
        }

        inline int count() {
            int elements = 0;
            for (Iterator it = first(); it != end(); ++it) ++elements;
            return elements;
        }

    protected:
        Node _begin; // fake node (without data) which represents the begin of the list - not the first element!
        Node _end;   // fake node (without data) which represents the end of the list - not the last element!

        RTListBase() {
            init();
        }

        void init() {
            // initialize boundary nodes
            _begin.prev = &_begin;
            _begin.next = &_end;
            _begin.data = NULL;
            _end.next = &_end;
            _end.prev = &_begin;
            _end.data = NULL;
            #if CONFIG_DEVMODE
            _begin.list = this;
            _end.list   = this;
            #endif // CONFIG_DEVMODE
        }

        inline void append(Iterator itElement) {
            Node* pNode = itElement.current;
            Node* last  = _end.prev;
            last->next  = pNode;
            pNode->prev = last; // if a segfault happens here, then because 'itElement' Iterator became invalidated
            pNode->next = &_end;
            _end.prev   = pNode;
            #if CONFIG_DEVMODE
            pNode->list = this;
            #endif // CONFIG_DEVMODE
        }

        inline void append(Iterator itFirst, Iterator itLast) {
            Node* pFirst = itFirst.current;
            Node* pLast  = itLast.current;
            Node* last   = _end.prev;
            last->next   = pFirst;
            pFirst->prev = last;  // if a segfault happens here, then because 'itFirst' Iterator became invalidated
            pLast->next  = &_end; // if a segfault happens here, then because 'itLast' Iterator became invalidated
            _end.prev    = pLast;
            #if CONFIG_DEVMODE
            for (Node* pNode = pFirst; true; pNode = pNode->next) {
                pNode->list = this;
                if (pNode == pLast) break;
            }
            #endif // CONFIG_DEVMODE
        }

        inline void prepend(Iterator itElement) {
            Node* pNode = itElement.current;
            Node* first = _begin.next;
            _begin.next = pNode;
            pNode->prev = &_begin; // if a segfault happens here, then because 'itElement' Iterator became invalidated
            pNode->next = first;
            first->prev = pNode;
            #if CONFIG_DEVMODE
            pNode->list = this;
            #endif // CONFIG_DEVMODE
        }

        inline void prepend(Iterator itFirst, Iterator itLast) {
            Node* pFirst = itFirst.current;
            Node* pLast  = itLast.current;
            Node* first  = _begin.next;
            _begin.next  = pFirst;
            pFirst->prev = &_begin; // if a segfault happens here, then because 'itFirst' Iterator became invalidated
            pLast->next  = first;   // if a segfault happens here, then because 'itLast' Iterator became invalidated
            first->prev  = pLast;
            #if CONFIG_DEVMODE
            for (Node* pNode = pFirst; true; pNode = pNode->next) {
                pNode->list = this;
                if (pNode == pLast) break;
            }
            #endif // CONFIG_DEVMODE
        }

        static inline void detach(Iterator itElement) {
            Node* pNode = itElement.node();
            Node* prev = pNode->prev; // if a segfault happens here, then because 'itElement' Iterator became invalidated
            Node* next = pNode->next;
            prev->next = next;
            next->prev = prev;
        }

        static inline void detach(Iterator itFirst, Iterator itLast) {
            Node* prev = itFirst.node()->prev; // if a segfault happens here, then because 'itFirst' Iterator became invalidated
            Node* next = itLast.node()->next;  // if a segfault happens here, then because 'itLast' Iterator became invalidated
            prev->next = next;
            next->prev = prev;
        }

        friend class _Iterator<T>;
        friend class RTList<T>;
        friend class Pool<T>;
};

template<typename T>
class RTList : public RTListBase<T> {
    public:
        typedef typename RTListBase<T>::Node     Node;
        typedef typename RTListBase<T>::Iterator Iterator;

        /**
         * Constructor
         *
         * @param pPool - pool this list uses for allocation and
         *                deallocation of elements
         */
        RTList(Pool<T>* pPool) : RTListBase<T>::RTListBase() {
            this->pPool = pPool;
        }
        
        /**
         * Copy constructor
         */
        RTList(RTList<T>& list) : RTListBase<T>::RTListBase() {
            this->pPool = list.pPool;
            RTList<T>::Iterator it = list.first();
            RTList<T>::Iterator end = list.end();
            for(; it != end; ++it) {
                if (poolIsEmpty()) break;
                *(allocAppend()) = *it;
            }
        }

        virtual ~RTList() {
            clear();
        }

        inline bool poolIsEmpty() {
            return pPool->poolIsEmpty();
        }

        inline Iterator allocAppend() {
            if (pPool->poolIsEmpty()) return RTListBase<T>::begin();
            Iterator element = pPool->alloc();
            append(element);
            #if CONFIG_DEVMODE
            element.list = this;
            #endif // CONFIG_DEVMODE
            return element;
        }

        inline Iterator allocPrepend() {
            if (pPool->poolIsEmpty()) return RTListBase<T>::end();
            Iterator element = pPool->alloc();
            prepend(element);
            #if CONFIG_DEVMODE
            element.list = this;
            #endif // CONFIG_DEVMODE
            return element;
        }

        inline void free(Iterator& itElement) {
            itElement.detach();
            pPool->freeToPool(itElement);
            itElement.current = itElement.fallback;
        }

        inline void clear() {
            if (!RTListBase<T>::isEmpty()) {
                Node* first = RTListBase<T>::_begin.next;
                Node* last  = RTListBase<T>::_end.prev;
                RTListBase<T>::detach(first, last);
                pPool->freeToPool(first, last);
            }
        }

    protected:
        Pool<T>* pPool;
};

template<typename T>
class Pool : public RTList<T> {
    public:
        typedef typename RTList<T>::Node     Node;
        typedef typename RTList<T>::Iterator Iterator;

        Node*         nodes;
        T*            data;
        RTListBase<T> freelist; // not yet allocated elements
        int           poolsize;

        Pool(int Elements) : RTList<T>::RTList(this) {
            _init(Elements);
        }

        virtual ~Pool() {
            if (nodes) delete[] nodes;
            if (data)  delete[] data;
        }

        inline bool poolIsEmpty() {
            return freelist.isEmpty();
        }

        /**
         * Returns the current size of the pool, that is the amount of
         * pre-allocated elements from the operating system. It equals the
         * amount of elements given to the constructor unless resizePool()
         * is called.
         *
         * @see resizePool()
         */
        int poolSize() const {
            return poolsize;
        }

        /**
         * Alters the amount of elements to be pre-allocated from the
         * operating system for this pool object.
         *
         * @e CAUTION: you MUST free all elements in use before calling this
         * method ( e.g. by calling clear() )! Also make sure that no
         * references of elements before this call will still be used after this
         * call, since all elements will be reallocated and their old memory
         * addresses become invalid!
         *
         * @see poolSize()
         */
        void resizePool(int Elements) {
            if (freelist.count() != poolsize) {
                #if CONFIG_DEVMODE
                throw std::runtime_error(__err_msg_resize_while_in_use);
                #else
                std::cerr << __err_msg_resize_while_in_use << std::endl << std::flush;
                // if we're here something's terribly wrong, but we try to do the best
                RTList<T>::clear();
                #endif
            }
            if (nodes) delete[] nodes;
            if (data)  delete[] data;
            freelist.init();
            RTListBase<T>::init();
            _init(Elements);
        }

    protected:
        // caution: assumes pool (that is freelist) is not empty!
        inline Iterator alloc() {
            Iterator element = freelist.last();
            element.detach();
            return element;
        }

        inline void freeToPool(Iterator itElement) {
            freelist.append(itElement);
        }

        inline void freeToPool(Iterator itFirst, Iterator itLast) {
            freelist.append(itFirst, itLast);
        }

        friend class RTList<T>;

    private:
        void _init(int Elements) {
            data  = new T[Elements];
            nodes = new Node[Elements];
            for (int i = 0; i < Elements; i++) {
                nodes[i].data = &data[i];
                freelist.append(&nodes[i]);
            }
            poolsize = Elements;
        }
};

#endif // __LS_POOL_H__
