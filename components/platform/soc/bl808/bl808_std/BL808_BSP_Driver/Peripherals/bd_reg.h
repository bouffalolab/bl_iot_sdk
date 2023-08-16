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
#ifndef  __BD_REG_H__
#define  __BD_REG_H__

#include "bl808.h"

struct  bd_reg {
    /* 0x0 : BD_Config */
    union {
        struct {
            uint32_t    CS      :   1;
            uint32_t    DF      :   1;
            uint32_t    LC      :   1;
            uint32_t    RL      :   1;
            uint32_t    RTRY    :   4;
            uint32_t    UR      :   1;
            uint32_t    RSVD    :   2;
            uint32_t    CRC     :   1;
            uint32_t    PAD     :   1;
            uint32_t    WR      :   1;
            uint32_t    IRQ     :   1;
            uint32_t    RD      :   1;
            uint32_t    LEN     :   16;
        }BD_TX;
        struct {
            uint32_t    LC      :   1;
            uint32_t    CRC     :   1;
            uint32_t    SF      :   1;
            uint32_t    TL      :   1;
            uint32_t    DN      :   1;
            uint32_t    RE      :   1;
            uint32_t    OR      :   1;
            uint32_t    M       :   1;
            uint32_t    CF      :   1;
            uint32_t    RSVD    :   4;
            uint32_t    WR      :   1;
            uint32_t    IRQ     :   1;
            uint32_t    E       :   1;
            uint32_t    LEN     :   16;
        }BD_RX;
        uint32_t WORD;
    } BD_Config;

    /* 0x4 : DMA_SrcAddr */
    union {
        struct {
            uint32_t BUF_PNT    : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } BD_Buf;
};

typedef volatile struct bd_reg bd_reg_t;

#define BD_DESC_OFFSET     0x400

#endif  /* __BD_REG_H__ */
