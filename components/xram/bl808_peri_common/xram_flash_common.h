/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#ifndef BL808_FLASH_COMMON_H
#define BL808_FLASH_COMMON_H

#define XRAM_ADDR_LIMIT (0x1000000)

#define FLASH_OPERATION_MAX_SIZE (256)

enum xram_flash_id {
    XRAM_FLASH_ID_0,
    XRAM_FLASH_ID_1,
    XRAM_FLASH_ID_2,
    XRAM_FLASH_ID_3,
    XRAM_FLASH_ID_4,
    XRAM_FLASH_ID_5,
    XRAM_FLASH_ID_6,
    XRAM_FLASH_ID_MAX
};

typedef enum flash_op_err {
    FLASH_OP_OK,
    FLASH_OP_ERR
} FLASH_OP_ERR_TYPE;

enum flash_operation {
    XRAM_FLASH_CREATE,
    XRAM_FLASH_DESTROY,
    XRAM_FLASH_READ,
    XRAM_FLASH_WRITE,
    XRAM_FLASH_ERASE
};

struct xram_flash_op {
    uint32_t flash_id;  /* flash id */
    uint32_t size;      /* flash size */
    uint32_t offset;    /* the offset of flash address */
    uint32_t len;       /* flash operation range */
    uint8_t op;         /* flsh operation type*/
    uint8_t data[];
};
typedef struct xram_flash_op *xram_flash_op_t;
#define XRAM_FLASH_OPERATION (sizeof(struct xram_flash_op))

#endif
