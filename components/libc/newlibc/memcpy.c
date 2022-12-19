/*
 * memcpy.c
 */

#include <string.h>
#include <stdint.h>

void *memcpy8(void *dst, const void *src, size_t n)
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
uint32_t *memcpy32(uint32_t *dst, const uint32_t *src, size_t n)
{
    const uint32_t *p = src;
    uint32_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }

    return dst;
}

/****************************************************************************/ /**
 * @brief  Double word memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of words
 *
 * @return Destination pointer
 *
 *******************************************************************************/
uint64_t *memcpy64(uint64_t *dst, const uint64_t *src, size_t n)
{
    const uint64_t *p = src;
    uint64_t *q = dst;

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
void *memcpy(void *dst, const void *src, size_t n)
{
    uint32_t left, done, i = 0;
    uint8_t *pdst = (uint8_t *)dst;
    uint8_t *psrc = (uint8_t *)src;

#if __riscv_xlen == 64
    if (((uint64_t)(uintptr_t)pdst & 0x7) == 0 && ((uint64_t)(uintptr_t)psrc & 0x7) == 0) {
        memcpy64((uint64_t *)pdst, (const uint64_t *)psrc, n >> 3);
        left = n & 0x07;
        goto remain;
    }
#endif
    if (((uint32_t)(uintptr_t)pdst & 0x3) == 0 && ((uint32_t)(uintptr_t)psrc & 0x3) == 0) {
        memcpy32((uint32_t *)pdst, (const uint32_t *)psrc, n >> 2);
        left = n & 0x03;
#if __riscv_xlen == 64
remain:
#endif
        done = n - left;
        while (i < left) {
            pdst[done + i] = psrc[done + i];
            i++;
        }
    } else {
        memcpy8(pdst, psrc, n);
    }

    return dst;

}
