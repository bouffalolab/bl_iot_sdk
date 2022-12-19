/*
 * Copyright (c) 2016-2022 Bouffalolab.
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

#include <stdint.h>
#include <bl808_dma.h>

#include "bl_dma.h"

#define DMA_CHANNEL_OFFSET              0x100
#define DMA_Get_Channel(ch)             (DMA0_BASE+DMA_CHANNEL_OFFSET+(ch)*0x100)

int bl_dma_int_clear(int ch)
{
    uint32_t tmpVal;
    uint32_t intClr;
    /* Get DMA register */
    uint32_t DMAChs = DMA2_BASE;

    tmpVal = BL_RD_REG(DMAChs, DMA_INTTCSTATUS);
    if((BL_GET_REG_BITS_VAL(tmpVal, DMA_INTTCSTATUS) & (1 << ch)) != 0) {
        /* Clear interrupt */
        tmpVal = BL_RD_REG(DMAChs, DMA_INTTCCLEAR);
        intClr = BL_GET_REG_BITS_VAL(tmpVal, DMA_INTTCCLEAR);
        intClr |= (1 << ch);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_INTTCCLEAR, intClr);
        BL_WR_REG(DMAChs, DMA_INTTCCLEAR, tmpVal);
    }

    tmpVal = BL_RD_REG(DMAChs, DMA_INTERRORSTATUS);
    if((BL_GET_REG_BITS_VAL(tmpVal, DMA_INTERRORSTATUS) & (1 << ch)) != 0) {
        /*Clear interrupt */
        tmpVal = BL_RD_REG(DMAChs, DMA_INTERRCLR);
        intClr = BL_GET_REG_BITS_VAL(tmpVal, DMA_INTERRCLR);
        intClr |= (1 << ch);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_INTERRCLR, intClr);
        BL_WR_REG(DMAChs, DMA_INTERRCLR, tmpVal);
    }

    return 0;
}

#if 0
void bl_dma_update_memsrc(uint8_t ch, uint32_t src, uint32_t len)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMAChs = DMA_Get_Channel(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA_CHAN_TYPE(ch));

    /* config channel config*/
    BL_WR_REG(DMAChs, DMA_SRCADDR, src);

    tmpVal = BL_RD_REG(DMAChs, DMA_CONTROL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_TRANSFERSIZE, len);
    BL_WR_REG(DMAChs, DMA_CONTROL, tmpVal);
}

void bl_dma_update_memdst(uint8_t ch, uint32_t dst, uint32_t len)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t DMAChs = DMA_Get_Channel(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_DMA_CHAN_TYPE(ch));

    /* config channel config*/
    BL_WR_REG(DMAChs, DMA_DSTADDR, dst);

    tmpVal = BL_RD_REG(DMAChs, DMA_CONTROL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DMA_TRANSFERSIZE, len);
    BL_WR_REG(DMAChs, DMA_CONTROL, tmpVal);
}
#endif
