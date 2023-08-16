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
 * limits.h
 */

#ifndef _LIMITS_H
#define _LIMITS_H

#define CHAR_BIT	8
#define SHRT_BIT	16
#define INT_BIT		32
#define LONGLONG_BIT	64

#define SCHAR_MIN	(-128)
#define SCHAR_MAX	127
#define UCHAR_MAX	255

#ifdef __CHAR_UNSIGNED__
# define CHAR_MIN 0
# define CHAR_MAX UCHAR_MAX
#else
# define CHAR_MIN SCHAR_MIN
# define CHAR_MAX SCHAR_MAX
#endif

#define SHRT_MIN	(-32768)
#define SHRT_MAX	32767
#define USHRT_MAX	65535


#define INT_MIN		(-2147483647-1)
#define INT_MAX		2147483647
#define UINT_MAX	4294967295U

#if __riscv_xlen == 64
# define LONG_BIT	64

# define LONG_MIN	(-9223372036854775807LL-1)
# define LONG_MAX	9223372036854775807LL
# define ULONG_MAX	18446744073709551615ULL
#else
# define LONG_BIT	32

# define LONG_MIN	(-2147483647L-1)
# define LONG_MAX	2147483647L
# define ULONG_MAX	4294967295UL
#endif

#define LONGLONG_MIN	(-9223372036854775807LL-1)
#define LONGLONG_MAX	9223372036854775807LL
#define ULONGLONG_MAX	18446744073709551615ULL


#endif				/* _LIMITS_H */
