/*
  Copyright (C) 2003, 2004 by Benno Senoner ( benno@gardena.net )
  http://www.linuxaudiodev.org

  For questions, suggestions, improvements contact me via E-Mail.

  LICENSE:

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  DESCRIPTION:

  This C++ class is an fast Real Time memory allocator suitable
  for elements of constant size.
  This is often needed in real time audio applications and I wrote
  this allocator because of my frustration of still seeing
  real time audio applications that call new,delete malloc() and free()
  within the real time loop !

  The allocappend(), allocprepend() and free() methods take only a few machine cycles providing
  deterministic execution times.

  the class is designed to provide element allocation which can
  be put in an external list ( RTEList<T>) which can be traversed
  forwards and backwards using
  for(elem=rtelist->first(); elem; elem=rtelist->next() ) { .... }
  or: for(elem=rtelist->last(); elem; elem=rtelist->prev() ) { .... }


  USAGE:

  //TODO: update usage documentation here to the new interface, means things below don't work anymore!

  creation of the memory pool:

  RTELMemoryPool *mypool=RTLMemoryPool<my_datatype>(number_of_elements);

  the above constructor creates a memory pool which contains
  number_of_elements elements that can be allocated and freed
  efficienty without calling system functions like new, delete malloc(),free()
  which cause non-deterministic behaviour in Real Time applications that
  need deterministic execution time.

  allocation of an element:

  RTEList<T> *rtelist;
  rtelist=new RTEList<T>;
  my_datatype *element;
  // append the allocated element to rtelist
  element=mypool->allocappend(rtelist);
  // prepend (insert at first position) the allocated element to rtelist
  element=mypool->allocprepend(rtelist);

  if there is no space left in the array alloc() returns NULL

  freeing of an element:

  mypool->free(element);


  THAT'S ALL FOLKS !


*/


#ifndef RTELMEMORYPOOL_H
#define RTELMEMORYPOOL_H

template<class T> class RTELMemoryPool;

/**
 * RTEList::Node contains the next and prev pointers needed to manage
 * the free element list, and anext, aprev needed to manage the list
 * of allocated elements. This list is handy for the routines that make
 * use of RTELMemoryPool because the list of elements can be traversed without
 * building a separate list outside RTELMemoryPool
 */
template<class T>
class RTELNode {
	public:
		RTELNode<T>* next;
		RTELNode<T>* prev;
		RTELNode<T>* anext;
		RTELNode<T>* aprev;
		T data;
		RTELNode() {}
};

template<class T>
class RTEList {
    protected:
        RTELNode<T>  firstnode;
        RTELNode<T>  lastnode;
        RTELNode<T>* acurrentnode;
        int   free_offset;
        RTELMemoryPool<T>* pPool;

        inline void move(RTELNode<T>* pNode, RTEList<T>* pDstList) {
            // remove element from this list
            RTELNode<T>* prev = pNode->aprev;
            RTELNode<T>* next = pNode->anext;
            prev->anext = next;
            next->aprev = prev;

            // add element to destination list
            RTELNode<T>* last         = pDstList->lastnode.aprev;
            last->anext              = pNode;
            pNode->anext             = &pDstList->lastnode;
            pDstList->lastnode.aprev = pNode;
            pNode->aprev             = last;
        }

        friend class RTELMemoryPool<T>;

    public:
        /**
         * Constructor
         *
         * @param pPool - the allocation pool this external list belongs to
         */
        RTEList(RTELMemoryPool<T>* pPool) {
            this->pPool = pPool;
            // initialize alloclist fistnode and lastnode pointers
            firstnode.aprev = &firstnode;
            firstnode.anext = &lastnode;
            lastnode.anext  = &lastnode;
            lastnode.aprev  = &firstnode;
            acurrentnode    = firstnode.anext;

            /* yes ugly hack but assuming that the difference of between
               RTEList::Node and RTList::Node.data is constant for all
               elements of the same class seems reasonable to me
               this is needed because when calling free() the user supplies
               the pointer to the data T and not to the RTEListNode
             */
            free_offset = (int)(&firstnode.data) - (int)&firstnode;
        }

        ~RTEList() {}

        /**
         * Returns the first element of the alloclist
         * NULL if the list is empty (no elements allocated)
         */
        inline T* first() {
            acurrentnode = firstnode.anext;
            // if element->anext points to itself it means last element
            // return NULL to signal end of list
            if (acurrentnode->anext == acurrentnode) return NULL;
            return &acurrentnode->data;
        }

        /**
         * Returns the last element of the alloclist
         * NULL if the list is empty (no elements allocated)
         */
        inline T* last() {
            acurrentnode = lastnode.aprev;
            // if element->aprev points to itself it means first element
            // return NULL to signal begin of list
            if (acurrentnode->aprev == acurrentnode) return NULL;
            return &acurrentnode->data;
        }

        /**
         * Returns the next element of the alloclist
         * NULL if we reach the end of the list
         */
        inline T* next() {
            acurrentnode = acurrentnode->anext;
            // if element->anext points to itself it means last element
            // return NULL to signal end of list
            if (acurrentnode->anext == acurrentnode) return NULL;
            return &acurrentnode->data;
        }

        /**
         * Returns the previous element of the alloclist
         * NULL if we reach the begin of the list
         */
        inline T* prev() {
            acurrentnode = acurrentnode->aprev;
            // if element->aprev points to itself it means last element
            // return NULL to signal begin of list
            if (acurrentnode->aprev == acurrentnode) return NULL;
            return &acurrentnode->data;
        }

        /**
         * Selects the node in the list respective to the given element;
         * mandatory for subsequent operations like prev() or next().
         *
         * @param element - element to be selected in the list
         */
        inline void set_current(T* element) {
            char* node = (char*) element;
            // calculate the offset of the RTEListNode (see free_offset calculation in the constructor)
            node -= free_offset;
            // select the node
            acurrentnode = (RTELNode<T>*) node;
        }

        /**
         * Moves current selected element from this list to another list.
         * The element will be appended to the destination list.
         *
         * @param pDstList - destination list
         * @returns          the moved element or NULL on error
         */
        inline T* move(RTEList<T>* pDstList) {
            // if there's a valid element selected
            if (acurrentnode != &firstnode && acurrentnode != &lastnode) {
                RTELNode<T>* pNode = acurrentnode;
                acurrentnode      = acurrentnode->aprev; // select previous element
                move(pNode, pDstList); // move element's node
                return &pNode->data;
            }
            return NULL;
        }

        /**
         * Moves the given element from this list to another list.
         * The element will be appended to the destination list.
         *
         * @param pElement - element to be moved
         * @param pDstList - destination list
         */
        inline void move(T* pElement, RTEList<T>* pDstList) {
            char* cNode = (char*) pElement;
            // calculate the offset of the RTEListNode (see free_offset calculation in the constructor)
            cNode -= free_offset;
            RTELNode<T>* pNode = (RTELNode<T>*) cNode;

            // if the node is selected, select previous element
            if (acurrentnode == pNode) acurrentnode = acurrentnode->aprev;

            // move the element's node
            move(pNode, pDstList);
        }

        /**
         * Returns true if no more element can be allocated from the pool.
         */
        inline bool pool_is_empty() {
            return pPool->pool_is_empty();
        }

        /**
         * Allocate one element from the pool and append it to this list.
         *
         * @returns allocated element
         */
        inline T* alloc() {
            return pPool->alloc_append(this);
        }

        /**
         * Allocate one element from the pool, assign given value and
         * append element to this list.
         *
         * @returns allocated element with already assigned value
         */
        inline T* alloc_assign(T data) {
            T* pData = alloc();
            if (pData) *pData = data;
            return pData;
        }

        /**
         * Free the given (allocated) element from this list. The element
         * will be readded to the pool's list of free elements.
         */
        inline void free(T* element) {
            pPool->free(element);
        }

        /**
         * Returns true if the list is empty.
         */
        inline bool is_empty() {
            return !first();
        }

        /**
         * Free all allocated elements in the list. All elements of this list
         * will be readded to the pool's internal list of free nodes.
         *
         * @returns number of freed elements
         */
        inline int clear() {
            int count = 0;
            acurrentnode = firstnode.anext;
            while (acurrentnode != acurrentnode->anext) {
                pPool->free(&acurrentnode->data); count++;
                acurrentnode = firstnode.anext;
            }
            return count;
        }
};

template<class T>
class RTELMemoryPool : public RTEList<T> {
    protected:
        RTELNode<T>* currentnode;

        // array that contains the elements:
        // each list element is made of list header (prev,next) and the data
        // of type T
        RTELNode<T>* memory_pool;

        /**
         * Allocate one element of the memory pool
         * if no elements are free return NULL
         * we find the first element of the list
         * remove it from the free list and then
         * return the data associated to the element
         */
        inline T* alloc_append(RTEList<T>* rtelist) {
            // get the first element
            currentnode = this->firstnode.next;
            // element->next points to itself which means last element
            // return NULL to signal end of list
            if (currentnode->next == currentnode) return NULL;

            // now remove the element from the freelist
            RTELNode<T>* prevelem = currentnode->prev;
            RTELNode<T>* nextelem = currentnode->next;
            prevelem->next = nextelem;
            nextelem->prev = prevelem;

            // append the element to the external rtelist
            RTELNode<T>* el_lastnode = (RTELNode<T>*) &rtelist->lastnode;
            RTELNode<T>* last        = el_lastnode->aprev;

            last->anext        = currentnode;
            currentnode->anext = el_lastnode;
            el_lastnode->aprev = currentnode;
            currentnode->aprev = last;

            // finally return the allocated elment
            //printf("alloc_append returning elem=%d\n",&currentnode->data);
            return &currentnode->data;
        }

        /**
         * same as alloc_append but the element is inserted at the
         * beginning of the list
         */
        inline T* alloc_prepend(RTEList<T>* rtelist) {
            RTELNode<T>* prevelem;
            RTELNode<T>* nextelem;
            // get the first element
            currentnode = this->firstnode.next;
            // element->next points to itself which means last element
            // return NULL to signal end of list
            if (currentnode->next == currentnode) return NULL;

            // now remove the element from the freelist
            prevelem       = currentnode->prev;
            nextelem       = currentnode->next;
            prevelem->next = nextelem;
            nextelem->prev = prevelem;

            // prepend the element to the external rtelist
            RTELNode<T>* el_firstnode = (RTELNode<T>*) &rtelist->firstnode;
            RTELNode<T>* first        = el_firstnode->anext;

            currentnode->anext  = first;
            currentnode->aprev  = el_firstnode;
            el_firstnode->anext = currentnode;
            first->aprev        = currentnode;

            // finally return the allocated elment
            return &currentnode->data;
        }

        inline void append(RTELNode<T>* elem) {
            RTELNode<T>* last = this->lastnode.prev;

            last->next    = elem;
            elem->next    = &(this->lastnode);
            this->lastnode.prev = elem;
            elem->prev    = last;
        }

        inline void prepend(RTELNode<T>* elem) {
            RTELNode<T>* first = this->firstnode.next;

            elem->next     = first;
            elem->prev     = &(this->firstnode);
            this->firstnode.next = elem;
            first->prev    = elem;
        }

        friend class RTEList<T>;

    public:
        /**
         * Constructor
         *
         * @param numelements - number of elements this pool should offer
         */
        RTELMemoryPool(int numelements) : RTEList<T>::RTEList(this) {
            // initialize freelist listnode and lastnode pointers
            this->firstnode.prev = &(this->firstnode);
            this->firstnode.next = &(this->lastnode);
            this->lastnode.next  = &(this->lastnode);
            this->lastnode.prev  = &(this->firstnode);

            currentnode = &(this->lastnode);

            // initialize alloclist listnode and lastnode pointers
            this->firstnode.aprev = &(this->firstnode);
            this->firstnode.anext = &(this->lastnode);
            this->lastnode.anext  = &(this->lastnode);
            this->lastnode.aprev  = &(this->firstnode);


            memory_pool = new RTELNode<T>[numelements];

            for (int i = 0; i < numelements; i++) {
                append(&memory_pool[i]);
            }
        }

        inline ~RTELMemoryPool() {
            if (memory_pool) delete[] memory_pool;
        }

        /**
         * Returns true if no more element can be allocated.
         */
        inline bool pool_is_empty() {
            RTELNode<T>* nextnode = this->firstnode.next;
            return (nextnode->next == nextnode);
        }

        /**
         * Allocate one element of the memory pool
         * if no elements are free return NULL
         * we find the first element of the list
         * remove it from the free list and then
         * return the data associated to the element
         */
        inline T* alloc() {
            // get the first element
            currentnode = this->firstnode.next;
            // element->next points to itself which means last element
            // return NULL to signal end of list
            if (currentnode->next == currentnode) return NULL;

            // now remove the element from the freelist
            RTELNode<T>* prevelem = currentnode->prev;
            RTELNode<T>* nextelem = currentnode->next;
            prevelem->next = nextelem;
            nextelem->prev = prevelem;

            // append the element to the alloc list
            RTELNode<T>* last = this->lastnode.aprev;
            last->anext        = currentnode;
            currentnode->anext = &(this->lastnode);
            this->lastnode.aprev = currentnode;
            currentnode->aprev = last;

            // finally return the allocated elment
            return &currentnode->data;
        }

        /**
         * Free an allocated element by putting it back to the freelist.
         */
        inline void free(T* element) {
            RTELNode<T>* prevelem;
            RTELNode<T>* nextelem;
            RTELNode<T>* node;

            char* node_to_free = (char*) element;
            // calculate the offset of the RTEListNode (see free_offset calculation in the constructor)
            node_to_free -= this->free_offset;
            // insert the node to the beginning of the freelist
            node = (RTELNode<T>*) node_to_free;
            prepend(node);

            // now remove the element from the alloclist
            prevelem        = node->aprev;
            nextelem        = node->anext;
            prevelem->anext = nextelem;
            nextelem->aprev = prevelem;
            //printf("free returning elem=%d\n",&currentnode->data);
        }

        /**
         * Frees all allocated elements in the internal allocation list.
         * This method does not free elements allocated for external lists!
         * For freeing elements allocated for external lists, use the empty()
         * method of the respective RTEList object.
         *
         * @returns number of freed elements
         */
        inline int clear() {
            RTELNode<T>* nextnode;
            RTELNode<T>* prevelem;
            RTELNode<T>* nextelem;

            int count = 0;

            this->acurrentnode = this->firstnode.anext;
            if (this->acurrentnode->anext == this->acurrentnode) return 0;

            while (true) {
                nextnode = this->acurrentnode->anext;

                // prepend (insert at the beginning) the node to the freelist
                //printf("empty: putting back elem (node) %d to freelist\n",acurrentnode);
                prepend(this->acurrentnode); count++;

                // now remove the element from the alloclist
                prevelem        = this->acurrentnode->aprev;
                nextelem        = this->acurrentnode->anext;
                prevelem->anext = nextelem;
                nextelem->aprev = prevelem;

                if (nextnode->anext == nextnode) return count;
                this->acurrentnode = nextnode;
            }
        }
};


#endif
