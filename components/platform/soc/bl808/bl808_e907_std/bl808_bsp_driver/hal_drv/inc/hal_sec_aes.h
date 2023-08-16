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
#ifndef __HAL_SEC_AES__H__
#define __HAL_SEC_AES__H__

#include "hal_common.h"

typedef enum {
    SEC_AES_CBC,
    SEC_AES_CTR,
    SEC_AES_XTS,
    SEC_AES_ECB
} sec_aes_type;

typedef enum {
    SEC_AES_KEY_128,
    SEC_AES_KEY_256,
    SEC_AES_KEY_192
} sec_aes_key_type;

typedef struct sec_aes_handle_t {
    sec_aes_type aes_type;
    sec_aes_key_type key_type;
} sec_aes_handle_t;

typedef enum {
    SEC_AES_DIR_ENCRYPT,
    SEC_AES_DIR_DECRYPT
} sec_aes_dir_type;

int sec_aes_init(sec_aes_handle_t *handle, sec_aes_type aes_tye, sec_aes_key_type key_type);
int sec_aes_setkey(sec_aes_handle_t *handle, const uint8_t *key, uint8_t key_len, const uint8_t *nonce, uint8_t dir);
int sec_aes_encrypt(sec_aes_handle_t *handle, const uint8_t *in, uint32_t len, size_t offset, uint8_t *out);
int sec_aes_decrypt(sec_aes_handle_t *handle, const uint8_t *in, uint32_t len, size_t offset, uint8_t *out);
int sec_aes_deinit(sec_aes_handle_t *handle);

#endif