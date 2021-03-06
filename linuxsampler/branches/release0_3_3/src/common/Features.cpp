/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
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

#include "Features.h"

#if CONFIG_ASM && ARCH_X86
bool Features::bMMX(false);
bool Features::bSSE(false);
bool Features::bSSE2(false);

unsigned int edx = 0;
unsigned int eax_temp = 0;
unsigned int ebx_temp = 0;
unsigned int ecx_temp = 0;
unsigned int edx_temp = 0;

void Features::detect() {
    // we store and restore all registers modified by 'cpuid' the old fashioned way
    __asm__ __volatile__ (
        "mov %eax,eax_temp\n\t"
        "mov %ebx,ebx_temp\n\t"
        "mov %ecx,ecx_temp\n\t"
        "mov %edx,edx_temp\n\t"
        "mov $1,%eax\n\t"
        "cpuid\n\t"
        "mov %edx,edx\n\t"
        "mov eax_temp,%eax\n\t"
        "mov ebx_temp,%ebx\n\t"
        "mov ecx_temp,%ecx\n\t"
        "mov edx_temp,%edx\n\t"
    );
    bMMX = (edx & 0x00800000);
    bSSE = (edx & 0x02000000);
    bSSE2 = (edx & 0x04000000);
}
#else
void Features::detect() {}
#endif // CONFIG_ASM && ARCH_X86

void Features::enableDenormalsAreZeroMode() {
    #if CONFIG_ASM && ARCH_X86
    if (supportsSSE2()) {
        int x;
        __asm__ __volatile__ (
            "stmxcsr %0\n\t"
            "movl    %0, %%eax\n\t"
            "orl     $0x40, %%eax\n\t"
            "movl    %%eax, %0\n\t"
            "ldmxcsr %0\n\t"
            :: "m" (x)
            : "%eax"
        );
    }
    #endif // CONFIG_ASM && ARCH_X86
}

String Features::featuresAsString() {
    String sFeatures = "none";
    #if CONFIG_ASM && ARCH_X86    
    if (supportsMMX())  sFeatures  =  "MMX";
    if (supportsSSE())  sFeatures += " SSE";
    if (supportsSSE2()) sFeatures += " SSE2";
    #else
    sFeatures = "disabled at compile time";
    #endif // CONFIG_ASM && ARCH_X86
    return sFeatures;
}
