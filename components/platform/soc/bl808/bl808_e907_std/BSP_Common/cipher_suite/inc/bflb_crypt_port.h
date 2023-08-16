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
#ifndef _BFLB_AES_PORT_H
#define _BFLB_AES_PORT_H

#ifndef BFLB_CRYPT_HARDWARE
#include "mbedtls/aes.h"
#include "mbedtls/ccm.h"
#include "mbedtls/gcm.h"
#include "chacha.h"
#include "chacha20_poly1305.h"
#else
#include "bflb_bsp_driver_glue.h"
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BFLB_CRYPT_KEY_SIZE_MAX   		32
#define BFLB_CRYPT_NONCE_SIZE_MAX       16
#define BFLB_CRYPT_BLK_SIZE       		16

#ifndef BFLB_CRYPT_HARDWARE
typedef union tag_bflb_crypt_ctx_t
{
    mbedtls_aes_context ctx_aes;
    mbedtls_ccm_context ctx_ccm;
    mbedtls_gcm_context ctx_gcm;
    ChaCha              ctx_chacha;
    ChaChaPoly1305      ctx_chachapoly1305;
}bflb_crypt_ctx_t;
#endif

typedef struct tag_bflb_crypt_cfg_t
{
#ifndef BFLB_CRYPT_HARDWARE
	uint8_t key[BFLB_CRYPT_KEY_SIZE_MAX];
	//for general cipher,iv is 16 bytes, but for GCM vector test, there is a 60 bytes test
	uint8_t iv_nonce[BFLB_CRYPT_NONCE_SIZE_MAX*4];
	uint8_t stream_block[BFLB_CRYPT_BLK_SIZE];
	uint8_t key_len;
	uint8_t nonce_len;
	uint8_t dir;
#else
#endif
    uint8_t type;
}bflb_crypt_cfg_t;



#ifndef BFLB_CRYPT_HARDWARE
#define BFLB_CRYPT_DIR_ENCRYPT    MBEDTLS_AES_ENCRYPT
#define BFLB_CRYPT_DIR_DECRYPT    MBEDTLS_AES_DECRYPT
#else
#define BFLB_CRYPT_DIR_ENCRYPT    1
#define BFLB_CRYPT_DIR_DECRYPT    2
#endif

#endif
