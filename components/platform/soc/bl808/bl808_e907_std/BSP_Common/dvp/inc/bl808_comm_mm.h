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
#ifndef __BL808_COMM_MM_H__
#define __BL808_COMM_MM_H__

#include <bl808_common.h>

/*----------------------------------------------*
 * const defination                             *
 *----------------------------------------------*/

#define ISP_INVALID_ADDR        0xDEADBEAF
#define ENC_END_FRAME_ADDR      0xDEADBEAF

#define INTR_MASK(x)        (!x)

#define RGB_GAIN_1X         4096

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define FAST_CAPTURE_MODE   0

/***************************** Value manipulation ************************************/

/* To avoid divide-0 exception in code. */
#define DIV_0_TO_1(a)   ( (0 == (a)) ? 1 : (a) )

/* Divide operation */
#define DIV_ROUND(divident, divider)    (((divident)+((divider)>>1)) / (divider))
#define DIV_ROUNDUP(divident, divider)    (((divident)+((divider)-1)) / (divider))
#define DIV_ROUND_SIGNED(divident, divider) \
    ((((divident) < 0) ^ ((divider) < 0)) ? \
    (((divident) - (divider)/2)/(divider)) : (((divident) + (divider)/2)/(divider))) \

#define FLOAT_TO_INT(x)         ((int)((float)(x) + 0.5))

#define SIGN_EXTEND(x, num_bits)    ((((int)(x)) & ((1 << num_bits) - 1)) << (32 - num_bits) >> (32 - num_bits))

#define ALIGN_TO_AXI_BURST_INCR16(x)    ((x) & 0xFFFFFF80)
#define AXI_BURST_INCR16_ALIGNMENT_MASK     ( 0x7F )
#define ROUNDUP_TO_AXI_BURST_INCR16(x)    (((x) + AXI_BURST_INCR16_ALIGNMENT_MASK)  & 0xFFFFFF80)
#define ROUNDUP_TO_16(x)    (((x) + 0xF)  & 0xFFFFFFF0)
#define ROUNDUP_TO_8(x)    (((x) + 0x7)  & 0xFFFFFFF8)
#define BLK_CNT_16X16(x)    (ROUNDUP_TO_16(x) >> 4)
#define BLK_CNT_8X8(x)    (ROUNDUP_TO_8(x) >> 3)
#define IS_MULTIPULE_OF_16(x)    (((x) & 0xF) == 0)
#define IS_MULTIPULE_OF_8(x)    (((x) & 0x7) == 0)
#define IS_MB_ALIGNED(x)    (((x) & 0xF) == 0)

#define ENC_HEIGHT(x)    (x)


/***************************** Type defines ************************************/
typedef int BL_GAIN_DB;                            /* gain value in dB */

typedef enum {
    INTR_DISABLE  = 0,
    INTR_ENABLE   = 1,
} ISP_INTR_MASK_E;

typedef enum {
    AXI_XLEN_SINGLE = 0,
    AXI_XLEN_INCR4 = 1,
    AXI_XLEN_INCR8 = 2,
    AXI_XLEN_INCR16 = 3,
    AXI_XLEN_INCR32 = 4,
} AXI_XLEN_E;


/***************************** Functions ************************************/

int Mem_Size_To_Burst_Cnt(uint32_t mem_size, AXI_XLEN_E xlen);

#endif /* __BL808_MM_COMM_H__ */

