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
#ifndef __HAL_SEC_HASH__H__
#define __HAL_SEC_HASH__H__

#include "drv_device.h"
#include "hal_common.h"

enum sec_hash_index_type {
    SEC_HASH0_INDEX,
    SEC_HASH_MAX_INDEX
};

enum sec_hash_type {
    SEC_HASH_SHA1,
    SEC_HASH_SHA224,
    SEC_HASH_SHA256,
    SEC_HASH_SHA384,
    SEC_HASH_SHA512,
    SEC_HASH_UNKNOWN
};

typedef struct sec_hash_device {
    struct device parent;
    uint32_t shaBuf[64 / 4];     /*!< Data not processed but in this temp buffer */
    uint32_t shaPadding[64 / 4]; /*!< Padding data */
    uint8_t type;                /*!< Sha has feed data */
} sec_hash_device_t;

typedef struct
{
    uint32_t shaBuf[64 / 4];     /*!< Data not processed but in this temp buffer */
    uint32_t shaPadding[64 / 4]; /*!< Padding data */
    uint8_t type;                /*!< Sha has feed data */
} sec_hash_handle_t;

int sec_hash_init(sec_hash_handle_t *handle, uint8_t type);
int sec_hash_deinit(sec_hash_handle_t *handle);
int sec_hash_update(sec_hash_handle_t *handle, const void *buffer, uint32_t size);
int sec_hash_finish(sec_hash_handle_t *handle, void *buffer);
int sec_hash_sha256_register(enum sec_hash_index_type index, const char *name);
int sec_hash_sha224_register(enum sec_hash_index_type index, const char *name);

#endif