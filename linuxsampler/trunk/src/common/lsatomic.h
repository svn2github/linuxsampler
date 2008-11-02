/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 Andreas Persson                                    *
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

#ifndef LSATOMIC_H
#define LSATOMIC_H

/*
 * Implementation of a small subset of the C++0x atomic operations
 * (cstdatomic).
 *
 * The supported operations are:
 *
 * - fences (acquire, release and full)
 *
 * - load and store of atomic<int> with relaxed, acquire/release or
 *   seq_cst memory ordering
 *
 * The supported architectures are x86 and powerpc.
 */
namespace LinuxSampler {
    enum memory_order {
        memory_order_relaxed, memory_order_acquire,
        memory_order_release, memory_order_seq_cst
    };

    inline void atomic_thread_fence(memory_order order) {
        switch (order) {
        case memory_order_relaxed:
            break;

        case memory_order_acquire:
        case memory_order_release:
#ifdef _ARCH_PPC64
            asm volatile("lwsync" : : : "memory");
#elif defined(__powerpc__)
            asm volatile("sync" : : : "memory");
#else
            asm volatile("" : : : "memory");
#endif
            break;

        case memory_order_seq_cst:
#ifdef __powerpc__
            asm volatile("sync" : : : "memory");
#elif defined(__i386__) || defined(__x86_64__)
            asm volatile("lock; addl $0,0(%%esp)" : : : "memory");
#else
            asm volatile("" : : : "memory");
#endif
            break;
        }
    }

    template<typename T> class atomic {
    public:
        atomic() { }
        atomic(T m) : f(m) { }
        T load(memory_order order = memory_order_seq_cst) const volatile {
            T m;
            switch (order) {
            case memory_order_relaxed:
                m = f;
                break;

            case memory_order_seq_cst:
            case memory_order_release: // (invalid)
                atomic_thread_fence(memory_order_seq_cst);
                // fall-through

            case memory_order_acquire:
#ifdef __powerpc__
                // PPC load-acquire: artificial dependency + isync
                asm volatile(
#ifdef _ARCH_PPC64
                    "ld %0,%1\n\t"
#else
                    "lwz%U1%X1 %0,%1\n\t"
#endif
                    "cmpw %0,%0\n\t"
                    "bne- 1f\n\t"
                    "1: isync"
                    : "=r" (m)
                    : "m"  (f)
                    : "memory", "cc");
#else
                m = f;
                asm volatile("" : : : "memory");
#endif
                break;
            }
            return m;
        }

        void store(T m, memory_order order = memory_order_seq_cst) volatile {
            switch (order) {
            case memory_order_relaxed:
                f = m;
                break;

            case memory_order_release:
                atomic_thread_fence(memory_order_release);
                f = m;
                asm volatile("" : : : "memory");
                break;

            case memory_order_seq_cst:
            case memory_order_acquire: // (invalid)
                atomic_thread_fence(memory_order_release);
                f = m;
                atomic_thread_fence(memory_order_seq_cst);
                break;
            }
        }
    private:
        T f;
    };
}
#endif
