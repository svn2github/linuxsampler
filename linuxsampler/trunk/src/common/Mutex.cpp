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

#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1 /* so _XOPEN_SOURCE will be defined by features.h */
#endif

#include <features.h>

#if !defined(_XOPEN_SOURCE) || _XOPEN_SOURCE < 500
# undef _XOPEN_SOURCE
# define _XOPEN_SOURCE 500 /* to define PTHREAD_MUTEX_ERRORCHECK */
# warning "Seems you don't have a UNIX98 compatible system."
# warning "Please run LinuxSampler's selftest to make sure this won't be a problem!"
# warning "(compile tests with 'make tests', run them with 'src/testcases/linuxsamplertest')"
#endif

#include <iostream>
#include <errno.h>
#include <stdlib.h> /* for exit(int) */

#include "Mutex.h"

Mutex::Mutex() {
    // the following function call only works on UNIX98 compatible systems
    if (pthread_mutexattr_settype(&__posix_mutexattr, PTHREAD_MUTEX_ERRORCHECK)) {
        std::cout << "Mutex Constructor: Fatal error - unable to pthread_mutexattr_settype(PTHREAD_MUTEX_ERRORCHECK)\n" << std::flush;
        exit(-1);
    }
    pthread_mutex_init(&__posix_mutex, &__posix_mutexattr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&__posix_mutex);
}

void Mutex::Lock() {
    pthread_mutex_lock(&__posix_mutex);
}

bool Mutex::Trylock() {
    if (pthread_mutex_trylock(&__posix_mutex) == EBUSY)
	    return false;
    return true;
}

void Mutex::Unlock() {
    pthread_mutex_unlock(&__posix_mutex);
}
