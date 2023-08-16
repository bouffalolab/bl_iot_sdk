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
#ifndef _BFLB_RSA_H
#define _BFLB_RSA_H

#include "bflb_rsa_port.h"
#include "bflb_platform.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define bflb_rsa_printf     bflb_platform_printf
#define bflb_rsa_printe     bflb_platform_printf
#define bflb_rsa_printd     bflb_platform_printf
#define bflb_rsa_printw     bflb_platform_printf


#define BFLB_RSA_OK             0
#define BFLB_RSA_ERROR          -1

enum BFLB_RSA_PARA
{
    BFLB_RSA_PARA_N,
    BFLB_RSA_PARA_E,
    BFLB_RSA_PARA_D,
    BFLB_RSA_PARA_P,
    BFLB_RSA_PARA_Q,
    BFLB_RSA_PARA_DP,
    BFLB_RSA_PARA_DQ,
    BFLB_RSA_PARA_QP,
};
   
typedef struct tag_bflb_rsa_handle_t
{
    bflb_rsa_ctx_t rsa_ctx;
}bflb_rsa_handle_t;

int32_t bflb_rsa_init(bflb_rsa_handle_t *rsa_handle,int padding,int hashtype );
int32_t bflb_rsa_set_parameter(bflb_rsa_handle_t *rsa_handle,int type,uint8_t *value,
                                uint32_t len );
int32_t bflb_rsa_check_private(bflb_rsa_handle_t *rsa_handle);
int32_t bflb_rsa_sign( bflb_rsa_handle_t *rsa_handle,const uint8_t *hash,
                            uint8_t hashlen,uint8_t hashtype,uint8_t *sig,uint32_t *slen);
int32_t bflb_rsa_verify( bflb_rsa_handle_t *rsa_handle,const uint8_t *hash,
                            uint8_t hashlen,uint8_t hashtype,const uint8_t *sig,uint32_t slen);
                            
int32_t bflb_rsa_deinit( bflb_rsa_handle_t *rsa_handle);

#endif
