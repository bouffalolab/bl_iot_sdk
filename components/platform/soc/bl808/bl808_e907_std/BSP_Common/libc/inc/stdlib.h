/*
 * Copyright (c) 2016-2023 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * stdlib.h
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <extern.h>
#include <libc_compiler.h>
#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

static __inline int abs(int __n)
{
	return (__n < 0) ? -__n : __n;
}

#if __riscv_xlen == 64
#   include_next <stdio.h>
__extern long jrand48(unsigned short *);
#else
__extern int atoi(const char *);
__extern double atof(const char *);
__extern long atol(const char *);
__extern long long atoll(const char *);
static __inline long labs(long __n)
{
	return (__n < 0L) ? -__n : __n;
}

static __inline long long llabs(long long __n)
{
	return (__n < 0LL) ? -__n : __n;
}

__extern long strtol(const char *, char **, int);
__extern long long strtoll(const char *, char **, int);
__extern unsigned long strtoul(const char *, char **, int);
__extern unsigned long long strtoull(const char *, char **, int);

typedef int (*__comparefunc_t) (const void *, const void *);
__extern void *bsearch(const void *, const void *, size_t, size_t,
		       __comparefunc_t);
__extern void qsort(void *, size_t, size_t, __comparefunc_t);

__extern long jrand48(unsigned short *);
__extern long mrand48(void);
__extern long nrand48(unsigned short *);
__extern long lrand48(void);
__extern unsigned short *seed48(unsigned short *);
__extern void srand48(long);

#define RAND_MAX 0x7fffffff
__extern int rand(void);
__extern void srand(unsigned int __s);
__extern long random(void);
__extern void srandom(unsigned int __s);
#endif /* __riscv_xlen == 64 */

#endif				/* _STDLIB_H */
