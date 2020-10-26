/*****************************************************************************************
*
* @file utils.c
*
* @brief entry
*
* Copyright (C) Bouffalo Lab 2019
*
* History: 2019-11 crealted by Lanlan Gong @ Shanghai
*
*****************************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

void reverse_bytearray(uint8_t *src, uint8_t *result, int array_size)
{
    for(int i=0; i < array_size;i++){
        result[array_size - i -1] = src[i];
    }
}

unsigned int find_msb_set(uint32_t data)
{
    uint32_t count = 0;
    uint32_t mask = 0x80000000;

    if (!data) {
        return 0;
    }
    while ((data & mask) == 0) {
        count += 1u;
        mask = mask >> 1u;
    }
    return (32 - count);
}

unsigned int find_lsb_set(uint32_t data)
{
    uint32_t count = 0;
    uint32_t mask = 0x00000001;

    if (!data) {
        return 0;
    }
    while ((data & mask) == 0) {
        count += 1u;
        mask = mask << 1u;
    }
    return (1 + count);
}
