/*
 * Copyright (c) 2020 Bouffalolab.
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
#ifndef __AES_TEST_H__
#define __AES_TEST_H__

#include <stddef.h>
#include <stdint.h>

#include "malloc_hw.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AES_ENCRYPT     1
#define AES_DECRYPT     0

typedef struct aes_gcm_hw {
    uint8_t *p_key;
    uint16_t key_bitlen;
    uint64_t len;                         /*!< The total length of the encrypted data. */
    uint64_t add_len;                     /*!< The total length of the additional data. */
    unsigned char base_ectr[16];          /*!< The first ECTR for tag. */
    unsigned char y[16];                  /*!< The Y working value. */
    unsigned char buf[16];                /*!< The buf working value. */
    int mode;                             /*!< The operation to perform:
                                               #MBEDTLS_GCM_ENCRYPT or
                                               #MBEDTLS_GCM_DECRYPT. */
} aes_gcm_hw_t;

typedef enum {
    AES_TEST_KEY_128 = 1,
    AES_TEST_KEY_192,
    AES_TEST_KEY_256,
    AES_TEST_DOUBLE_KEY_128,
} aes_key_t;

typedef enum {
    AES_ECB_MODE,                         /*!< AES mode type:ECB */
    AES_CTR_MODE,                         /*!< AES mode type:CTR */
    AES_CBC_MODE,                         /*!< AES mode type:CBC */
}AES_Type;

void aes_ecb_test(uint32_t length, uint32_t count,
                  aes_key_t keytype, uint8_t is_soft, ram_type_t ram_type);

void aes_cbc_test(uint32_t length, uint32_t count,
                  aes_key_t keytype, uint8_t is_soft, ram_type_t ram_type);

void aes_ctr_test(uint32_t length, uint32_t count,
                  aes_key_t keytype, uint8_t is_soft, ram_type_t ram_type);

void aes_gcm_test(uint32_t length, uint32_t count,
                  aes_key_t keytype, uint8_t is_soft, ram_type_t ram_type);

#ifdef __cplusplus
}
#endif

#endif
