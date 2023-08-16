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
#include "misc.h"

#ifndef BFLB_USE_ROM_DRIVER
/****************************************************************************/ /**
 * @brief  Char memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of char
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ void *ATTR_TCM_SECTION arch_memcpy(void *dst, const void *src, uint32_t n)
{
    const uint8_t *p = src;
    uint8_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  Word memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of words
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ uint32_t *ATTR_TCM_SECTION arch_memcpy4(uint32_t *dst, const uint32_t *src, uint32_t n)
{
    const uint32_t *p = src;
    uint32_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  Fast memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of bytes
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ void *ATTR_TCM_SECTION arch_memcpy_fast(void *pdst, const void *psrc, uint32_t n)
{
    uint32_t left, done, i = 0;
    uint8_t *dst = (uint8_t *)pdst;
    uint8_t *src = (uint8_t *)psrc;

    if (((uint32_t)(uintptr_t)dst & 0x3) == 0 && ((uint32_t)(uintptr_t)src & 0x3) == 0) {
        arch_memcpy4((uint32_t *)dst, (const uint32_t *)src, n >> 2);
        left = n % 4;
        done = n - left;

        while (i < left) {
            dst[done + i] = src[done + i];
            i++;
        }
    } else {
        arch_memcpy(dst, src, n);
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  char memset
 *
 * @param  dst: Destination
 * @param  val: Value to set
 * @param  n: Count of char
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ void *ATTR_TCM_SECTION arch_memset(void *s, uint8_t c, uint32_t n)
{
    uint8_t *p = (uint8_t *)s;

    while (n > 0) {
        *p++ = (uint8_t)c;
        --n;
    }

    return s;
}
/****************************************************************************/ /**
 * @brief  Word memset
 *
 * @param  dst: Destination
 * @param  val: Value to set
 * @param  n: Count of words
 *
 * @return Destination pointer
 *
 *******************************************************************************/
__WEAK__ uint32_t *ATTR_TCM_SECTION arch_memset4(uint32_t *dst, const uint32_t val, uint32_t n)
{
    uint32_t *q = dst;

    while (n--) {
        *q++ = val;
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  string compare
 *
 * @param  s1: string 1
 * @param  s2: string 2
 * @param  n: Count of chars
 *
 * @return compare result
 *
 *******************************************************************************/
__WEAK__ int ATTR_TCM_SECTION arch_memcmp(const void *s1, const void *s2, uint32_t n)
{
    const unsigned char *c1 = s1, *c2 = s2;
    int d = 0;

    while (n--) {
        d = (int)*c1++ - (int)*c2++;

        if (d) {
            break;
        }
    }

    return d;
}
#endif

void memcopy_to_fifo(void *fifo_addr, uint8_t *data, uint32_t length)
{
    uint8_t *p = (uint8_t *)fifo_addr;
    uint8_t *q = data;

    while (length--) {
        *p = *q++;
    }
}

void fifocopy_to_mem(void *fifo_addr, uint8_t *data, uint32_t length)
{
    uint8_t *p = (uint8_t *)fifo_addr;
    uint8_t *q = data;

    while (length--) {
        *q++ = *p;
    }
}

/****************************************************************************/ /**
 * @brief  get u64 first number 1 from right to left
 *
 * @param  val: target value
 * @param  bit: first 1 in bit
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
int arch_ffsll(uint64_t *val, uint32_t *bit)
{
    if (!*val) {
        return ERROR;
    }

    *bit = __builtin_ffsll(*val) - 1;
    *val &= ~((1ULL) << (*bit));
    return 0;
}

int arch_ctzll(uint64_t *val, uint32_t *bit)
{
    if (!*val)
        return -1;

    *bit = __builtin_ctzll(*val);
    *val &= ~((1ULL) << (*bit));
    return 0;
}

int arch_clzll(uint64_t *val, uint32_t *bit)
{
    if (!*val)
        return -1;

    *bit = __builtin_clzll(*val);
    *val &= ~((1ULL) << (*bit));
    return 0;
}

#ifdef DEBUG
/*******************************************************************************
* @brief  Reports the name of the source file and the source line number
*         where the CHECK_PARAM error has occurred.

* @param  file: Pointer to the source file name
* @param  line: assert_param error line source number

* @return None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
    /* Infinite loop */
    while (1)
        ;
}
#endif /* DEBUG */

/*@} end of group DRIVER_Public_Functions */

/*@} end of group DRIVER_COMMON */

/*@} end of group BL602_Periph_Driver */
