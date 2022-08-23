#ifndef __BL_HBN_H__
#define __BL_HBN_H__
#include <stdint.h>

typedef struct _hbn_type {
    uint8_t buflen;
    uint8_t active;
    uint8_t buf[1];
} hbn_type_t;

int bl_hbn_enter(hbn_type_t *hbn, uint32_t *time);

#endif

