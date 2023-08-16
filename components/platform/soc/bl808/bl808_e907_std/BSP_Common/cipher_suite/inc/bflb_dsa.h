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
#ifndef _BFLB_DSA_H
#define _BFLB_DSA_H

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "bflb_ecdsa_port.h"
#include "bflb_platform.h"

#define BFLB_DSA_OK                     0
#define BFLB_DSA_ERROR                  -1

typedef struct tag_bflb_dsa_crt_cfg
{
    uint32_t *dP;
    uint32_t *dQ;
    uint32_t *qInv;
    uint32_t *p;
    uint32_t *invR_p;
    uint32_t *primeN_p;
    uint32_t *q;
    uint32_t *invR_q;
    uint32_t *primeN_q;
}bflb_dsa_crt_cfg;

typedef struct{
    uint32_t size;
    uint32_t crtSize;
    uint32_t *n;
    uint32_t *e;
    uint32_t *d;
    bflb_dsa_crt_cfg crtCfg;
}BFLB_DSA_Handle_t;

int32_t bflb_dsa_init(BFLB_DSA_Handle_t * handle,uint32_t size);
int32_t bflb_dsa_mexp_binary(uint32_t size,const uint32_t *a,const uint32_t *b,const uint32_t *c,uint32_t *r);
int32_t bflb_dsa_mexp_mont(uint32_t size,uint32_t *a,uint32_t *b,uint32_t *c,uint32_t *invR_c,uint32_t *primeN_c,uint32_t *r);
int32_t bflb_dsa_decrypt_crt(uint32_t size,uint32_t *c,bflb_dsa_crt_cfg *crtCfg,uint32_t *d,uint32_t *r);
int32_t bflb_dsa_sign(BFLB_DSA_Handle_t * handle,const uint32_t *hash,uint32_t hashLenInWord,uint32_t *s);
int32_t bflb_dsa_verify(BFLB_DSA_Handle_t * handle,const uint32_t *hash,uint32_t hashLenInWord,const uint32_t *s);

#endif
