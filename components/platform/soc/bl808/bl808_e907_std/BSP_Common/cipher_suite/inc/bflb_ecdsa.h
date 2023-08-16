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
#ifndef _BFLB_ECDSA_H
#define _BFLB_ECDSA_H

#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "bflb_ecdsa_port.h"
#include "bflb_platform.h"

#define BFLB_ECDSA_OK             0
#define BFLB_ECDSA_ERROR          -1
#define BFLB_ECDH_OK              0
#define BFLB_ECDH_ERROR           -1

typedef enum{
    ECP_SECP256R1=0,
}BFLB_ECP_Type;

typedef struct{
    BFLB_ECP_Type ecpId;
    uint32_t *privateKey;
    uint32_t *publicKeyx;
    uint32_t *publicKeyy;
}BFLB_ECDSA_Handle_t;

typedef struct{
    BFLB_ECP_Type ecpId;
}BFLB_ECDH_Handle_t;

int32_t bflb_ecdsa_init(BFLB_ECDSA_Handle_t * handle,BFLB_ECP_Type id);
int32_t bflb_ecdsa_deinit(BFLB_ECDSA_Handle_t * handle);
int32_t bflb_ecdsa_sign(BFLB_ECDSA_Handle_t * handle,const uint32_t *random_k,const uint32_t *hash,uint32_t hashLenInWord,uint32_t *r,uint32_t *s);
int32_t bflb_ecdsa_verify(BFLB_ECDSA_Handle_t * handle,const uint32_t *hash, uint32_t hashLen,const uint32_t *r, const uint32_t *s);
int32_t bflb_ecdsa_get_private_key(BFLB_ECDSA_Handle_t * handle,uint32_t *private_key);
int32_t bflb_ecdsa_get_public_key(BFLB_ECDSA_Handle_t * handle,const uint32_t *private_key,const uint32_t *pRx,const uint32_t *pRy);

int32_t bflb_ecdh_init(BFLB_ECDH_Handle_t * handle,BFLB_ECP_Type id);
int32_t bflb_ecdh_deinit(BFLB_ECDH_Handle_t * handle);
int32_t bflb_ecdh_get_encrypt_key(BFLB_ECDH_Handle_t *handle,const uint32_t *pkX,const uint32_t *pkY,const uint32_t *private_key,const uint32_t *pRx,const uint32_t *pRy);
int32_t bflb_ecdh_get_public_key(BFLB_ECDH_Handle_t *handle,const uint32_t *private_key,const uint32_t *pRx,const uint32_t *pRy);
int32_t bflb_ecc_get_random_value(uint32_t *randomData,uint32_t *maxRef,uint32_t size);


#endif
