/*
  Copyright (C) 2003 by Benno Senoner ( benno@gardena.net )
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

template<class T>
class RTEList {
typedef struct _RTEListNode {
                 struct _RTEListNode *next;
                 struct _RTEListNode *prev;
                 struct _RTEListNode *anext;
                 struct _RTEListNode *aprev;
                 T data;
               } RTEListNode;

public:
  RTEList (void) {
    // initialize alloclist fistnode and lastnode pointers
    firstnode.aprev=&firstnode;
    firstnode.anext=&lastnode;
    lastnode.anext=&lastnode;
    lastnode.aprev=&firstnode;
    acurrentnode=firstnode.anext;
  }
  ~RTEList (void) {
  }

/* returns the first element of the alloclist
   NULL if the list is empty (no elements allocated)
 */
inline T *first(void) {
    acurrentnode=firstnode.anext;
    // if element->anext points to itself it means last element
    // return NULL to signal end of list
    if(acurrentnode->anext == acurrentnode) return(NULL);
    return(&acurrentnode->data);
}

/* returns the last element of the alloclist
   NULL if the list is empty (no elements allocated)
 */
inline T *last(void) {
    acurrentnode=lastnode.aprev;
    // if element->aprev points to itself it means first element
    // return NULL to signal begin of list
    if(acurrentnode->aprev == acurrentnode) return(NULL);
    return(&acurrentnode->data);
}

/* returns the next element of the alloclist
   NULL if we reach the end of the list
 */
inline T *next(void) {
    acurrentnode=acurrentnode->anext;
    // if element->anext points to itself it means last element
    // return NULL to signal end of list
    if(acurrentnode->anext == acurrentnode) return(NULL);
    return(&acurrentnode->data);
}

/* returns the previous element of the alloclist
   NULL if we reach the begin of the list
 */
inline T *prev(void) {
    acurrentnode=acurrentnode->aprev;
    // if element->aprev points to itself it means last element
    // return NULL to signal begin of list
    if(acurrentnode->aprev == acurrentnode) return(NULL);
    return(&acurrentnode->data);
}

  RTEListNode firstnode;
  RTEListNode lastnode;
  RTEListNode *acurrentnode;

};

template<class T>
class RTELMemoryPool
{



/*
   RTEListNode contains the next and prev pointers needed to manage
   the free element list, and anext,aprev needed to manage the list
   of allocated elements. This list is handy for the routines that make
   use of RTELMemoryPool because the list of elements can be traversed without
   building a separate list outside RTELMemoryPool
*/

typedef struct _RTEListNode { 
                 struct _RTEListNode *next;
                 struct _RTEListNode *prev;
                 struct _RTEListNode *anext; 
                 struct _RTEListNode *aprev; 
                 T data;
               } RTEListNode;

public:

inline RTELMemoryPool (int numelements) {


    // initialize freelist fistnode and lastnode pointers
    firstnode.prev=&firstnode;
    firstnode.next=&lastnode;
    lastnode.next=&lastnode;
    lastnode.prev=&firstnode;

    currentnode=&lastnode;

    // initialize alloclist fistnode and lastnode pointers
    firstnode.aprev=&firstnode;
    firstnode.anext=&lastnode;
    lastnode.anext=&lastnode;
    lastnode.aprev=&firstnode;


    memory_pool=new RTEListNode[numelements];

    for(int i=0; i < numelements; i++) {
      append(&memory_pool[i]);
    }
    /* yes ugly hack but assuming that the difference of between
       RTEListNode and RTListNode.data is constant for all
       elements of the same class seems reasonable to me
       this is needed because when calling free() the user supplies
       the pointer to the data T and not to the RTEListNode
    */
    free_offset=(int)(&firstnode.data)-(int)&firstnode;
  }
inline  ~RTELMemoryPool() {
    delete[] memory_pool;
  }

/* returns the first element of the alloclist
   NULL if the list is empty (no elements allocated)
 */
inline T *first(void) {
    acurrentnode=firstnode.anext;
    // if element->anext points to itself it means last element
    // return NULL to signal end of list
    if(acurrentnode->anext == acurrentnode) return(NULL);
    return(&acurrentnode->data);
}

/* returns the last element of the alloclist
   NULL if the list is empty (no elements allocated)
 */
inline T *last(void) {
    acurrentnode=lastnode.aprev;
    // if element->aprev points to itself it means first element
    // return NULL to signal begin of list
    if(acurrentnode->aprev == acurrentnode) return(NULL);
    return(&acurrentnode->data);
}

/* returns the next element of the alloclist
   NULL if we reach the end of the list
 */
inline T *next(void) {
    acurrentnode=acurrentnode->anext;
    // if element->anext points to itself it means last element
    // return NULL to signal end of list
    if(acurrentnode->anext == acurrentnode) return(NULL);
    return(&acurrentnode->data);
}

/* returns the previous element of the alloclist
   NULL if we reach the begin of the list
 */
inline T *prev(void) {
    acurrentnode=acurrentnode->aprev;
    // if element->aprev points to itself it means last element
    // return NULL to signal begin of list
    if(acurrentnode->aprev == acurrentnode) return(NULL);
    return(&acurrentnode->data);
}

inline  void append(RTEListNode *elem) {

    RTEListNode *last=lastnode.prev;

    last->next=elem;
    elem->next=&lastnode;
    lastnode.prev=elem;
    elem->prev=last;
    
  }

inline  void prepend(RTEListNode *elem) {

    RTEListNode *first=firstnode.next;

    elem->next=first;
    elem->prev=&firstnode;
    firstnode.next=elem;
    first->prev=elem;
  }



/* alloc_append:
   allocate one element of the memory pool
   if no elements are free return NULL
   we find the first element of the list
   remove it from the free list and then
   return the data associated to the element
*/

inline T *alloc_append(RTEList<T> *rtelist) {
    RTEListNode *prevelem;
    RTEListNode *nextelem;
    // get the first element
    currentnode=firstnode.next;
    // element->next points to itself which means last element
    // return NULL to signal end of list
    if(currentnode->next == currentnode) return(NULL);

    // now remove the element from the freelist
    prevelem=currentnode->prev;
    nextelem=currentnode->next;
    prevelem->next=nextelem;
    nextelem->prev=prevelem;

    // append the element to the external rtelist
    RTEListNode *el_lastnode=(RTEListNode *)&rtelist->lastnode;
    RTEListNode *last=el_lastnode->aprev;

    last->anext=currentnode;
    currentnode->anext=el_lastnode;
    el_lastnode->aprev=currentnode;
    currentnode->aprev=last;

    // finally return the allocated elment
//printf("alloc_append returning elem=%d\n",&currentnode->data);
    return(&currentnode->data);
}
/* same as alloc_append but the element is inserted at the 
   beginning of the list
 */
inline T *alloc_prepend(RTEList<T> *rtelist) {
    RTEListNode *prevelem;
    RTEListNode *nextelem;
    // get the first element
    currentnode=firstnode.next;
    // element->next points to itself which means last element
    // return NULL to signal end of list
    if(currentnode->next == currentnode) return(NULL);

    // now remove the element from the freelist
    prevelem=currentnode->prev;
    nextelem=currentnode->next;
    prevelem->next=nextelem;
    nextelem->prev=prevelem;

    // prepend the element to the external rtelist
    RTEListNode *el_firstnode=(RTEListNode *)&rtelist->firstnode;
    RTEListNode *first=el_firstnode->anext;

    currentnode->anext=first;
    currentnode->aprev=el_firstnode;
    el_firstnode->anext=currentnode;
    first->aprev=currentnode;

    // finally return the allocated elment
    return(&currentnode->data);
}



  // allocate one element of the memory pool
  // if no elements are free return NULL
  // we find the first element of the list
  // remove it from the free list and then
  // return the data associated to the element
inline  T *alloc(void) {

    RTEListNode *prevelem;
    RTEListNode *nextelem;
    RTEListNode *last;

    // get the first element
    currentnode=firstnode.next;
    // element->next points to itself which means last element
    // return NULL to signal end of list
    if(currentnode->next == currentnode) return(NULL);

    // now remove the element from the freelist
    prevelem=currentnode->prev;
    nextelem=currentnode->next;
    prevelem->next=nextelem;
    nextelem->prev=prevelem;

    // append the element to the alloc list
    last=lastnode.aprev;
    last->anext=currentnode;
    currentnode->anext=&lastnode;
    lastnode.aprev=currentnode;
    currentnode->aprev=last;

    // finally return the allocated elment
    return(&currentnode->data);
  }


  // free an allocated element by putting it back to the freelist
inline  void free(T *element) {
    RTEListNode *prevelem;
    RTEListNode *nextelem;
    RTEListNode *node;
    
    char *node_to_free=(char *)element;
    // calculate the offset of the RTEListNode (see free_offset calculation in the constructor)
    node_to_free -= free_offset;
    // insert the node to the beginning of the freelist
    node=(RTEListNode *)node_to_free;
    prepend(node);

    // now remove the element from the alloclist
    prevelem=node->aprev;
    nextelem=node->anext;
    prevelem->anext=nextelem;
    nextelem->aprev=prevelem;
    //printf("free returning elem=%d\n",&currentnode->data);
  }

// empty the whole list
inline void empty(void) {

    RTEListNode *nextnode;
    RTEListNode *prevelem;
    RTEListNode *nextelem;

    acurrentnode=firstnode.anext;
    if(acurrentnode->anext == acurrentnode) return;

    while(1) {
      nextnode=acurrentnode->anext;

      // prepend (insert at the beginning) the node to the freelist
      //printf("empty: putting back elem (node) %d to freelist\n",acurrentnode);
      prepend(acurrentnode);

      // now remove the element from the alloclist
      prevelem=acurrentnode->aprev;
      nextelem=acurrentnode->anext;
      prevelem->anext=nextelem;
      nextelem->aprev=prevelem;

      if(nextnode->anext == nextnode) return;
      acurrentnode=nextnode;
    }
  }


  int free_offset;


  RTEListNode firstnode;
  RTEListNode lastnode;
  RTEListNode *currentnode;

  RTEListNode *acurrentnode;

  // array that contains the elements: 
  // each list element is made of list header (prev,next) and the data
  // of type T 
  RTEListNode *memory_pool;


};


#endif
