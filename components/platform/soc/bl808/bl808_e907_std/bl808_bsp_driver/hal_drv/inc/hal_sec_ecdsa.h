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
#ifndef __HAL_SEC_ECDSA__H__
#define __HAL_SEC_ECDSA__H__

#include "hal_common.h"

typedef enum {
    ECP_SECP256R1 = 0,
    ECP_SECP256K1 = 1,
    ECP_TYPE_MAX = 2,
} sec_ecp_type;

typedef struct
{
    sec_ecp_type ecpId;
    uint32_t *privateKey;
    uint32_t *publicKeyx;
    uint32_t *publicKeyy;
} sec_ecdsa_handle_t;

typedef struct
{
    sec_ecp_type ecpId;
} sec_ecdh_handle_t;

int sec_ecdsa_init(sec_ecdsa_handle_t *handle, sec_ecp_type id);
int sec_ecdsa_deinit(sec_ecdsa_handle_t *handle);
int sec_ecdsa_sign(sec_ecdsa_handle_t *handle, const uint32_t *random_k, const uint32_t *hash, uint32_t hashLenInWord, uint32_t *r, uint32_t *s);
int sec_ecdsa_verify(sec_ecdsa_handle_t *handle, const uint32_t *hash, uint32_t hashLen, const uint32_t *r, const uint32_t *s);
int sec_ecdsa_get_private_key(sec_ecdsa_handle_t *handle, uint32_t *private_key);
int sec_ecdsa_get_public_key(sec_ecdsa_handle_t *handle, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);

int sec_ecdh_init(sec_ecdh_handle_t *handle, sec_ecp_type id);
int sec_ecdh_deinit(sec_ecdh_handle_t *handle);
int sec_ecdh_get_encrypt_key(sec_ecdh_handle_t *handle, const uint32_t *pkX, const uint32_t *pkY, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);
int sec_ecdh_get_public_key(sec_ecdh_handle_t *handle, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);
int sec_ecc_get_random_value(uint32_t *randomData, uint32_t *maxRef, uint32_t size);

#define SEC_CODEPATH_STATE_SIGN             0x48672386

#endif