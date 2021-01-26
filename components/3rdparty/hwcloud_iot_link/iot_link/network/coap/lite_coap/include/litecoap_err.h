/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of CHN and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/
 
#ifndef _LITECOAP_ERR_H
#define _LITECOAP_ERR_H

#define LITECOAP_OK                 0
#define LITECOAP_NG                 -1

#define LITECOAP_PARAM_NULL         -1
#define LITECOAP_BUF_LEN_TOO_SMALL  -2

#define LITECOAP_VER_ERR            -3
#define LITECOAP_TOKEN_LEN_ERR      -4
#define LITECOAP_OPTION_DELTA_ERR   -5
#define LITECOAP_OPTION_LEN_ERR     -6
#define LITECOAP_OPTION_OVERRUN_ERR -7
#define LITECOAP_OPTION_POSTION_ERR -8
#define LITECOAP_CONTEX_BUF_NULL    -9
#define LITECOAP_SND_LEN_TOO_BIG    -10

#define LITECOAP_ENCODE_PKG_SIZE_ERR -11

#define LITECOAP_HEADER_ERR         -12
#define LITECOAP_TOKEN_ERR          -13
#define LITECOAP_OPTION_ERR         -14

#define LITECOAP_MALLOC_FAILED      -12

#define LITECOAP_STATACK_INIT_FAILED    -13
#define LITECOAP_SOCKET_HANDLER_ERR     -14
#define LITECOAP_SOCKET_READ_ERR        -15
#define LITECOAP_SOCKET_NETWORK_ERR     -16
#define LITECOAP_SOCKET_SETOPT_ERR      -17
#define LITECOAP_SOCKET_ADDRCHK_ERR     -19
#endif
