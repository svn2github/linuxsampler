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

#ifndef __LS_POOL_H__
#define __LS_POOL_H__

#ifndef DEVMODE
# include "global.h" // just to check if we should compile in 'DEVMODE'
#endif

// we just use exceptions for debugging, better not in the final realtime thread !
#ifndef USE_EXCEPTIONS
# define USE_EXCEPTIONS 0
#endif

#if USE_EXCEPTIONS
# include <stdexcept>
# include <string>
const std::string __err_msg_iterator_invalidated = "Pool/RTList iterator invalidated";
#endif // USE_EXCEPTIONS

// just symbol prototyping
template<typename T> class Pool;
template<typename T> class RTList;

template<typename T>
class RTListBase {
    protected:
        template<typename _T>
        struct _Node {
            _Node<_T>* next;
            _Node<_T>* prev;
            _T* data;
            #if DEVMODE
            RTListBase<_T>* list; // list to which this node currently belongs to
            #endif // DEVMODE

            _Node() {
                next = NULL;
                prev = NULL;
                data = NULL;
                #if DEVMODE
                list = NULL;
                #endif // DEVMODE
            }
        };
        typedef _Node<T> Node;

    public:
        template<typename _T>
        class _Iterator {
            public:
                _Iterator() {
                    current  = NULL;
                    fallback = NULL;
                    #if DEVMODE
                    list = NULL;
                    #endif // DEVMODE
                }

                /// prefix increment op.
                inline _Iterator& operator++() {
                    #if DEVMODE
                    #if USE_EXCEPTIONS
                    if (!isValid()) throw std::runtime_error(__err_msg_iterator_invalidated);
                    #else
                    if (!isValid()) return *(_Iterator*)NULL; // force segfault if iterator became invalidated
                    #endif // USE_EXCEPTIONS
                    #endif // DEVMODE
                    fallback = current;
                    current  = current->next;
                    return *this;
                }

                /// postfix increment op.
                inline _Iterator operator++(int) {
                    _Iterator preval = *this;
                    ++*this;
                    return preval;
                }

                /// prefix decrement op.
                inline _Iterator& operator--() {
                    #if DEVMODE
                    #if USE_EXCEPTIONS
                    if (!isValid()) throw std::runtime_error(__err_msg_iterator_invalidated);
                    #else
                    if (!isValid()) return *(_Iterator*)NULL; // force segfault if iterator became invalidated
                    #endif // USE_EXCEPTIONS
                    #endif // DEVMODE
                    fallback = current;
                    current  = current->prev;
                    return *this;
                }

                /// postfix decrement op.
                inline _Iterator operator--(int) {
                    _Iterator preval = *this;
                    --*this;
                    return preval;
                }

                inline _T& operator*() {
                    #if DEVMODE
                    #if USE_EXCEPTIONS
                    if (isValid()) return *current->data;
                    else throw std::runtime_error(__err_msg_iterator_invalidated);
                    #else
                    return *(isValid() ? current->data : (_T*)NULL); // force segfault if iterator became invalidated
                    #endif // USE_EXCEPTIONS
                    #else
                    return *current->data;
                    #endif // DEVMODE
                }

                inline _T* operator->() {
                    #if DEVMODE
                    #if USE_EXCEPTIONS
                    if (isValid()) return current->data;
                    else throw std::runtime_error(__err_msg_iterator_invalidated);
                    #else
                    return isValid() ? current->data : (_T*)NULL; // force segfault if iterator became invalidated
                    #endif // USE_EXCEPTIONS
                    #else
                    return current->data;
                    #endif // DEVMODE
                }

                inline bool operator==(const _Iterator<_T> other) {
                    return current == other.current;
                }

                inline bool operator!=(const _Iterator<_T> other) {
                    return current != other.current;
                }

                inline operator bool() const {
                    return current && current->data;
                }

                inline bool operator!() const {
                    return !(current && current->data);
                }

                inline _Iterator moveToEndOf(RTListBase<_T>* pDstList) {
                    detach();
                    pDstList->append(*this);
                    _Iterator iterOnDstList = _Iterator(current);
                    current = fallback;
                    return iterOnDstList;
                }

                inline _Iterator moveToBeginOf(RTListBase<_T>* pDstList) {
                    detach();
                    pDstList->prepend(*this);
                    _Iterator iterOnDstList = _Iterator(current);
                    current = fallback;
                    return iterOnDstList;
                }

                #if DEVMODE
                inline bool isValid() {
                    return current->list == list;
                }
                #endif // DEVMODE

            protected:
                Node* current;
                Node* fallback;
                enum dir_t {
                    dir_forward,
                    dir_backward
                };
                #if DEVMODE
                RTListBase<_T>* list;
                #endif // DEVMODE

                _Iterator(Node* pNode, dir_t direction = dir_forward) {
                    current  = pNode;
                    fallback = (direction == dir_forward) ? pNode->prev : pNode->next;
                    #if DEVMODE
                    list = pNode->list;
                    #endif // DEVMODE
                }

                inline Node* node() {
                    #if DEVMODE
                    #if USE_EXCEPTIONS
                    if (isValid()) return current;
                    else throw std::runtime_error(__err_msg_iterator_invalidated);
                    #else
                    return (isValid()) ? current : (Node*)NULL; // force segfault if iterator became invalidated
                    #endif // USE_EXCEPTIONS
                    #else
                    return current;
                    #endif // DEVMODE
                }

                inline void detach() {
                    RTListBase<_T>::detach(*this);
                }

                friend class RTListBase<_T>;
                friend class RTList<_T>;
                friend class Pool<_T>;
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

    protected:
        Node _begin; // fake node (without data) which represents the begin of the list - not the first element!
        Node _end;   // fake node (without data) which represents the end of the list - not the last element!

        RTListBase() {
            // initialize boundary nodes
            _begin.prev = &_begin;
            _begin.next = &_end;
            _begin.data = NULL;
            _end.next = &_end;
            _end.prev = &_begin;
            _end.data = NULL;
            #if DEVMODE
            _begin.list = this;
            _end.list   = this;
            #endif // DEVMODE
        }

        inline void append(Iterator itElement) {
            Node* pNode = itElement.current;
            Node* last  = _end.prev;
            last->next  = pNode;
            pNode->prev = last; // if a segfault happens here, then because 'itElement' Iterator became invalidated
            pNode->next = &_end;
            _end.prev   = pNode;
            #if DEVMODE
            pNode->list = this;
            #endif // DEVMODE
        }

        inline void append(Iterator itFirst, Iterator itLast) {
            Node* pFirst = itFirst.current;
            Node* pLast  = itLast.current;
            Node* last   = _end.prev;
            last->next   = pFirst;
            pFirst->prev = last;  // if a segfault happens here, then because 'itFirst' Iterator became invalidated
            pLast->next  = &_end; // if a segfault happens here, then because 'itLast' Iterator became invalidated
            _end.prev    = pLast;
            #if DEVMODE
            for (Node* pNode = pFirst; true; pNode = pNode->next) {
                pNode->list = this;
                if (pNode == pLast) break;
            }
            #endif // DEVMODE
        }

        inline void prepend(Iterator itElement) {
            Node* pNode = itElement.current;
            Node* first = _begin.next;
            _begin.next = pNode;
            pNode->prev = &_begin; // if a segfault happens here, then because 'itElement' Iterator became invalidated
            pNode->next = first;
            first->prev = pNode;
            #if DEVMODE
            pNode->list = this;
            #endif // DEVMODE
        }

        inline void prepend(Iterator itFirst, Iterator itLast) {
            Node* pFirst = itFirst.current;
            Node* pLast  = itLast.current;
            Node* first  = _begin.next;
            _begin.next  = pFirst;
            pFirst->prev = &_begin; // if a segfault happens here, then because 'itFirst' Iterator became invalidated
            pLast->next  = first;   // if a segfault happens here, then because 'itLast' Iterator became invalidated
            first->prev  = pLast;
            #if DEVMODE
            for (Node* pNode = pFirst; true; pNode = pNode->next) {
                pNode->list = this;
                if (pNode == pLast) break;
            }
            #endif // DEVMODE
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
            #if DEVMODE
            element.list = this;
            #endif // DEVMODE
            return element;
        }

        inline Iterator allocPrepend() {
            if (pPool->poolIsEmpty()) return RTListBase<T>::end();
            Iterator element = pPool->alloc();
            prepend(element);
            #if DEVMODE
            element.list = this;
            #endif // DEVMODE
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

        Pool(int Elements) : RTList<T>::RTList(this) {
            data  = new T[Elements];
            nodes = new Node[Elements];
            for (int i = 0; i < Elements; i++) {
                nodes[i].data = &data[i];
                freelist.append(&nodes[i]);
            }
        }

        virtual ~Pool() {
            if (nodes) delete[] nodes;
            if (data)  delete[] data;
        }

        inline bool poolIsEmpty() {
            return freelist.isEmpty();
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
};

#endif // __LS_POOL_H__
