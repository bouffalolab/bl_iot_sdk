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
#include <stdio.h>
#include <bl808_common.h>
#include <bl808_glb.h>
#include <bl808_i2s.h>
#include <bl808_dma.h>
#include "bl_dma.h"
#include "bl_i2s.h"

#include "utils_log.h"

//TODO use unified DMA interface with hal DMA
//TODO use unified I2S interface

#define I2S_FIFO_ADDR_TX           (I2S1_BASE + 0x10)
#define I2S_FIFO_ADDR_RX           (I2S1_BASE + 0x14)

static DMA_LLI_Ctrl_Type (*lli_tx)[2];
static DMA_LLI_Ctrl_Type (*lli_rx)[2];
static uint8_t *lli_tx_buffer;
static uint8_t *lli_rx_buffer;
static int lli_tx_buffer_size;
static int lli_rx_buffer_size;
static bl_audio_callback_tx_ready_t cb_tx;
static bl_audio_callback_rx_ready_t cb_rx;
static void *usrdata_tx;
static void *usrdata_rx;
const static I2S_ID_Type i2sID = I2S1_ID;
static DMA_Chan_Type dmaCh = DMA_CH0;

void dump_hex(void* any, int length)
{
    int i;
    uint8_t *start = (uint8_t*)any;

    printf("\r\n");
    for(i=0; i< length; i++){
        printf("%x ", start[i]);
    }
    printf("\r\n");
}

static I2S_CFG_Type i2sCfg =
{
    I2S_DATA_ENDIAN_MSB,       /*!< I2S msb first */
    I2S_MODE_I2S_LEFT,         /*!< I2S left justified */
    24.576*1000000,            /*!< Audio PLL 24.576M */
    48*1000,                   /*!< Sample Rate 48K */
    DISABLE,                   /*!< I2S bclk invert disable */
    I2S_SIZE_FRAME_8,          /*!< I2S frame size 8 */
    DISABLE,                   /*!< I2S frame select invert disable */
    I2S_FS_MODE_EVEN,          /*!< I2S frame mode even */
    I2S_FS_CHANNELS_2,         /*!< I2S frame cis 2 hannels */
    1,                         /*!< I2S data output offset is 0 */
    I2S_SIZE_DATA_8,           /*!< I2S data size 8 */
    DISABLE,                   /*!< I2S mono mode disabled */
};
static I2S_FifoCfg_Type fifoCfg =
{
    DISABLE,                 /*!< I2S FIFO packed enable */
    DISABLE,                /*!< I2S exchange disable */
    ENABLE,                /*!< Disable I2S tx fifo dma function. */
    ENABLE,                /*!< Disable I2S rx fifo dma function. */
    8,                      /*!< I2S receive fifo interrupt trigger level */
    8,                      /*!< I2S transmit fifo interrupt trigger level */
};
static DMA_LLI_Cfg_Type lliCfg =
{
    DMA_TRNS_M2P,
    DMA_REQ_NONE,
    DMA_REQ_I2S1_TX,
};
static struct DMA_Control_Reg dmaCtrlRegVal =
{
    .TransferSize=0,
    .SBSize=DMA_BURST_SIZE_4,
    .DBSize=DMA_BURST_SIZE_4,
    .SWidth=DMA_TRNS_WIDTH_32BITS,
    .DWidth=DMA_TRNS_WIDTH_32BITS,
    .SI=DMA_MINC_ENABLE,
    .DI=DMA_PINC_DISABLE,
    .I=1,
};

/*USE DMA0 channel 0 as Default*/
void bl_i2s_dma_int_handler_tx(void)
{
    int size, trans, count;

    if (cb_tx) {
retry:
        //FIXME use std driver to access DMA channel0
        trans = (*(volatile uint32_t*)0x4000710C) & 0xFFF;
        count = ((*(volatile uint32_t*)0x40007110) & (0x3FF << 20)) >> 20;
        if (0 == trans) {
            goto retry;
        }
        size = (lli_tx_buffer_size >> 1);
        if (0 == (count & 0x1)) {
            /*start with 1, we use the send half buffer*/
            cb_tx(usrdata_tx, lli_tx_buffer + size, size, 0);
        } else {
            /*start with 0, we use the first buffer*/
            cb_tx(usrdata_tx, lli_tx_buffer, size, 0);
        }
    }
    bl_dma_int_clear(DMA_CH0);
}

/*USE DMA0 channel 1 as Default*/
void bl_i2s_dma_int_handler_rx(void)
{
    int size, trans, count;

    if (cb_rx) {
retry:
        //FIXME use std driver to access DMA channel0
        trans = (*(volatile uint32_t*)0x4000720C) & 0xFFF;
        count = ((*(volatile uint32_t*)0x40007210) & (0x3FF << 20)) >> 20;
        if (0 == trans) {
            goto retry;
        }
        size = (lli_rx_buffer_size >> 1);
        if (0 == (count & 0x1)) {
            /*start with 1, we use the send half buffer*/
            cb_rx(usrdata_rx, lli_rx_buffer + size, size, 0);
        } else {
            /*start with 0, we use the first buffer*/
            cb_rx(usrdata_rx, lli_rx_buffer, size, 0);
        }
    }
    bl_dma_int_clear(DMA_CH1);
}

int bl_i2s_tx_buffer_config(int size, void **ptr_mem, void *(*malloc_dma_ptr)(size_t size))
{
    int i;
    uint16_t *ptr_u16;

    lli_tx_buffer = malloc_dma_ptr(size);
    if (NULL == lli_tx_buffer) {
        return -1;
    }
    *ptr_mem = lli_tx_buffer;
    lli_tx_buffer_size = size;
    ptr_u16 = (uint16_t*)lli_tx_buffer;
    for (i = 0; i < (size >> 1); i++) {
        ptr_u16[i] = i;
    }

    return 0;
}

int bl_i2s_rx_buffer_config(int size, void **ptr_mem, void *(*malloc_dma_ptr)(size_t size))
{
    lli_rx_buffer  = malloc_dma_ptr(size);
    if (NULL == lli_rx_buffer) {
        return -1;
    }
    *ptr_mem = lli_rx_buffer;
    lli_rx_buffer_size = size;

    return 0;
}

int bl_i2s_init(int tx_enable, int rx_enable, void *(*malloc_dma_ptr)(size_t size), void (*free_dma_ptr)(void*ptr))
{
    //i2sCfg.fsChannel = I2S_FS_CHANNELS_2;
    //i2sCfg.modeType = I2S_MODE_I2S_LEFT;
    //i2sCfg.dataOffset = 1;
    //i2sCfg.fsInvert = DISABLE;
    //i2sCfg.fsMode = I2S_FS_MODE_EVEN;
    //i2sCfg.monoMode = DISABLE;

    if (tx_enable) {
        lli_tx = malloc_dma_ptr(sizeof(*lli_tx));
        if (NULL == lli_tx) {
            goto failed;
        }
    }

    if (rx_enable) {
        lli_rx = malloc_dma_ptr(sizeof(*lli_rx));
        if (NULL == lli_rx) {
            goto failed;
        }
    }
    return 0;

failed:
    if (tx_enable && lli_tx) {
        free_dma_ptr(lli_tx);
    }
    if (rx_enable && lli_rx) {
        free_dma_ptr(lli_rx);
    }
    return -1;
}

int bl_i2s_unint(void (*free_dma_ptr)(void* ptr))
{
    if (lli_tx) {
        free_dma_ptr(lli_tx);
        lli_tx = NULL;
    }
    if (lli_rx) {
        free_dma_ptr(lli_rx);
        lli_rx = NULL;
    }
    //FIXME use API for std driver, and also critiale region protect
    uint32_t val;
    val = *(volatile uint32_t*)0x40000010;
    val |= 0x80;
    //hold reset
    *(volatile uint32_t*)0x40000010 = val;
    val &= 0xFFFFFF7F;
    //clear reset
    *(volatile uint32_t*)0x40000010 = val;
    if (lli_tx_buffer) {
        free_dma_ptr(lli_tx_buffer);
        lli_tx_buffer = NULL;
    }
    if  (lli_rx_buffer) {
        free_dma_ptr(lli_rx_buffer);
        lli_rx_buffer = NULL;
    }

    return 0;
}

int bl_i2s_sample_rate_config(BL_I2S_SAMPLE_RATE_T config)
{
    switch (config) {
        case BL_I2S_SAMPLE_RATE_8K:
        {
            i2sCfg.sampleFreqHz = 8000;
        }
        break;
        case BL_I2S_SAMPLE_RATE_11P025K:
        {
            i2sCfg.sampleFreqHz = 11025;
        }
        break;
        case BL_I2S_SAMPLE_RATE_12K:
        {
            i2sCfg.sampleFreqHz = 12000;
        }
        break;
        case BL_I2S_SAMPLE_RATE_16K:
        {
            i2sCfg.sampleFreqHz = 16000;
        }
        break;
        case BL_I2S_SAMPLE_RATE_22P05K:
        {
            i2sCfg.sampleFreqHz = 22050;
        }
        break;
        case BL_I2S_SAMPLE_RATE_24K:
        {
            i2sCfg.sampleFreqHz = 24000;
        }
        break;
        case BL_I2S_SAMPLE_RATE_32K:
        {
            i2sCfg.sampleFreqHz = 32000;
        }
        break;
        case BL_I2S_SAMPLE_RATE_44P1K:
        {
            i2sCfg.sampleFreqHz = 44100;
        }
        break;
        case BL_I2S_SAMPLE_RATE_48K:
        {
            i2sCfg.sampleFreqHz = 48000;
        }
        break;
        case BL_I2S_SAMPLE_RATE_96K:
        {
            i2sCfg.sampleFreqHz = 96000;
        }
        break;
        case BL_I2S_SAMPLE_RATE_192K:
        {
            i2sCfg.sampleFreqHz = 192000;
        }
        break;
        default:
        {
            /*Error now*/
            return -1;
        }
    }

    return 0;
}

int bl_i2s_start(void)
{
    uint8_t clkDiv = 0;
    (void) clkDiv;

#if 0
    if ((i2sCfg.sampleFreqHz == 11025) || (i2sCfg.sampleFreqHz == 22050) || (i2sCfg.sampleFreqHz == 44100)){
        Mixed_Power_On_Audio_PLL(PLL_XTAL_38P4M, AUPLL_CLK_5P6448M, 11289600/i2sCfg.audioFreqHz);
    } else {
        Mixed_Power_On_Audio_PLL(PLL_XTAL_38P4M, AUPLL_CLK_24P576M, 24576000/i2sCfg.audioFreqHz);
    }
#endif

    /*Enabel I2S*/
    I2S_Disable(I2S0_ID);
    I2S_Init(I2S0_ID, &i2sCfg);
    I2S_FifoConfig(I2S0_ID, &fifoCfg);
    I2S_Enable(I2S0_ID, I2S_ROLE_MASTER);

    I2S_Disable(i2sID);
    I2S_Init(i2sID, &i2sCfg);
    I2S_FifoConfig(i2sID, &fifoCfg);
    I2S_Enable(i2sID, I2S_ROLE_MASTER);

    DMA_Enable();

    dmaCh = DMA_CH0;
    DMA_IntMask(dmaCh, DMA_INT_ALL, MASK);
    DMA_IntMask(dmaCh, DMA_INT_TCOMPLETED, UNMASK);
    DMA_IntMask(dmaCh, DMA_INT_ERR, UNMASK);
    /*Enabel DMA*/
    lliCfg.dir = DMA_TRNS_M2P;
    lliCfg.srcPeriph = DMA_REQ_NONE;
    lliCfg.dstPeriph = DMA_REQ_I2S1_TX;
    DMA_LLI_Init(dmaCh, &lliCfg);
    DMA_LLI_Update(dmaCh, (uint32_t)lli_tx);
    DMA_Channel_Enable(dmaCh);
    System_NVIC_SetPriority(DMA0_CH0_IRQn, 7, 1);
    CPU_Interrupt_Enable(DMA0_CH0_IRQn);

    dmaCh = DMA_CH1;
    DMA_IntMask(dmaCh, DMA_INT_ALL, MASK);
    DMA_IntMask(dmaCh, DMA_INT_TCOMPLETED, UNMASK);
    DMA_IntMask(dmaCh, DMA_INT_ERR, UNMASK);
    /*Enabel DMA*/
    lliCfg.dir = DMA_TRNS_P2M;
    lliCfg.srcPeriph = DMA_REQ_I2S1_RX;
    lliCfg.dstPeriph = DMA_REQ_NONE;
    DMA_LLI_Init(dmaCh, &lliCfg);
    DMA_LLI_Update(dmaCh, (uint32_t)lli_rx);
    DMA_Channel_Enable(dmaCh);
    System_NVIC_SetPriority(DMA0_CH1_IRQn, 7, 1);
    CPU_Interrupt_Enable(DMA0_CH1_IRQn);

    log_info("i2sCfg :\r\n");
    log_buf((uint8_t *)&i2sCfg, sizeof(i2sCfg));
    dump_hex(&i2sCfg, sizeof(i2sCfg));

    log_info("fifoCfg :\r\n");
    log_buf((uint8_t *)&fifoCfg, sizeof(fifoCfg));
    dump_hex(&fifoCfg, sizeof(fifoCfg));

    log_info("lliCfg :\r\n");
    log_buf((uint8_t *)&lliCfg, sizeof(lliCfg));
    dump_hex(&lliCfg, sizeof(lliCfg));

    clkDiv = (i2sCfg.audioFreqHz/(i2sCfg.sampleFreqHz*128))-1;
    GLB_Set_I2S_CLK(0, ENABLE, 0,
            0,//0/* Out clk div */
            ENABLE/*Out clk enable */
    );
    GLB_Set_I2S_CLK(1, ENABLE,0/* pll clk div */,
                    0,
                    DISABLE/*Out clk DISABLE */
    );

    return 0;
}

int bl_i2s_configure(BL_AUDIO_FORMAT_T format)
{
    switch (format) {
        case BL_AUDIO_FORMAT_DATA16BIT_WIDTH16BIT_MONO:
        {
        }
        break;
        case BL_AUDIO_FORMAT_DATA16BIT_WIDTH16BIT_STERO:
        {
            printf("[HAL] Audio data 16bit, width 16bit, stero\r\n");
            /*normal mode*/
            i2sCfg.modeType = I2S_MODE_I2S_LEFT;
            i2sCfg.dataOffset = 1;
            i2sCfg.fsInvert = DISABLE;
            i2sCfg.fsMode = I2S_FS_MODE_EVEN;
            i2sCfg.fsChannel = I2S_FS_CHANNELS_2;

            /*format config*/
            i2sCfg.monoMode = DISABLE;
            i2sCfg.frameSize = I2S_SIZE_FRAME_16;
            //i2sCfg.sampleFreqHz = 48*1000;//sampleFreqHz should be set in sample rate API
            i2sCfg.dataSize = I2S_SIZE_DATA_16;

            /*fifo config*/
            fifoCfg.lRMerge = DISABLE;

            /*config LLI LIST TX*/
            if (lli_tx_buffer_size) {
                /*ping-pong buffer, one buffer is split into two*/
                lli_tx[0][0].srcDmaAddr = (uint32_t)lli_tx_buffer;
                lli_tx[0][0].destDmaAddr = I2S_FIFO_ADDR_TX;
                lli_tx[0][0].nextLLI=(uint32_t)(&lli_tx[0][1]);
                dmaCtrlRegVal.I = 1;
                dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.TransferSize = (lli_tx_buffer_size >> 1) >> 1;
                dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.SI = DMA_MINC_ENABLE,
                dmaCtrlRegVal.DI = DMA_PINC_DISABLE,
                lli_tx[0][0].dmaCtrl= dmaCtrlRegVal;
                printf("[HAL] TX Configuring LLI[0] @%p, copy from %p, count %d\r\n",
                        &(lli_tx[0][0]),
                        (void*)lli_tx[0][0].srcDmaAddr,
                        (unsigned int)(dmaCtrlRegVal.TransferSize)
                );

                lli_tx[0][1].srcDmaAddr = ((uint32_t)lli_tx_buffer) + 1 * (lli_tx_buffer_size >> 1);
                lli_tx[0][1].destDmaAddr = I2S_FIFO_ADDR_TX;
                lli_tx[0][1].nextLLI=(uint32_t)(&lli_tx[0][0]);
                dmaCtrlRegVal.I = 1;//generate INT
                dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.TransferSize = (lli_tx_buffer_size >> 1) >> 1;
                dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.SI = DMA_MINC_ENABLE,
                dmaCtrlRegVal.DI = DMA_PINC_DISABLE,
                lli_tx[0][1].dmaCtrl= dmaCtrlRegVal;
                printf("[HAL] TX Configuring LLI[1] @%p, copy from %p, count %d\r\n",
                        &(lli_tx[0][1]),
                        (void*)lli_tx[0][1].srcDmaAddr,
                        (unsigned int)(dmaCtrlRegVal.TransferSize)
                );
            }

            if (lli_rx_buffer_size) {
                /*ping-pong buffer, one buffer is split into two*/
                lli_rx[0][0].srcDmaAddr = I2S_FIFO_ADDR_RX;
                lli_rx[0][0].destDmaAddr = (uint32_t)lli_rx_buffer;
                lli_rx[0][0].nextLLI=(uint32_t)(&lli_rx[0][1]);
                dmaCtrlRegVal.I = 1;
                dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.TransferSize = (lli_rx_buffer_size >> 1) >> 1;
                dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.SI = DMA_PINC_DISABLE,
                dmaCtrlRegVal.DI = DMA_MINC_ENABLE,
                lli_rx[0][0].dmaCtrl= dmaCtrlRegVal;
                printf("[HAL] RX Configuring LLI[0] @%p, copy to %p, count %d\r\n",
                        &(lli_rx[0][0]),
                        (void*)lli_rx[0][0].destDmaAddr,
                        (unsigned int)(dmaCtrlRegVal.TransferSize)
                );

                lli_rx[0][1].srcDmaAddr = I2S_FIFO_ADDR_RX;
                lli_rx[0][1].destDmaAddr = ((uint32_t)lli_rx_buffer) + 1 * (lli_rx_buffer_size >> 1);
                lli_rx[0][1].nextLLI=(uint32_t)(&lli_rx[0][0]);
                dmaCtrlRegVal.I = 1;//generate INT
                dmaCtrlRegVal.SWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.DWidth = DMA_TRNS_WIDTH_16BITS;
                dmaCtrlRegVal.TransferSize = (lli_rx_buffer_size >> 1) >> 1;
                dmaCtrlRegVal.SBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.DBSize = DMA_BURST_SIZE_4;
                dmaCtrlRegVal.SI = DMA_PINC_DISABLE,
                dmaCtrlRegVal.DI = DMA_MINC_ENABLE,
                lli_rx[0][1].dmaCtrl= dmaCtrlRegVal;
                printf("[HAL] RX Configuring LLI[1] @%p, copy to %p, count %d\r\n",
                        &(lli_rx[0][1]),
                        (void*)lli_rx[0][1].destDmaAddr,
                        (unsigned int)(dmaCtrlRegVal.TransferSize)
                );
            }
        }
        break;
        case BL_AUDIO_FORMAT_DATA16BIT_WIDTH32BIT_MONO:
        {
            /*TODO*/
        }
        break;
        case BL_AUDIO_FORMAT_DATA16BIT_WIDTH32BIT_STERO:
        {
            /*TODO*/
        }
        break;
        case BL_AUDIO_FORMAT_DATA24BIT_WIDTH32BIT_MONO:
        {
            /*TODO*/
        }
        break;
        case BL_AUDIO_FORMAT_DATA24BIT_WIDTH32BIT_STERO:
        {
            /*TODO*/
        }
        break;
        case BL_AUDIO_FORMAT_DATA32BIT_WIDTH32BIT_MONO:
        {
            /*TODO*/
        }
        break;
        case BL_AUDIO_FORMAT_DATA32BIT_WIDTH32BIT_STERO:
        {
            /*TODO*/
        }
        break;
        default:
        {
            return -1;
        }
    }

    return 0;
}

int bl_i2s_set_mclk(uint32_t mclk)
{
    i2sCfg.audioFreqHz = mclk;

    return 0;
}

int bl_i2s_stop(void)
{
    /*Disable I2S function*/

    /*Disable DMA*/

    /*Disable INT*/
    CPU_Interrupt_Disable(DMA0_CH0_IRQn);
    CPU_Interrupt_Disable(DMA0_CH0_IRQn);

    return 0;
}

int bl_i2s_tx_ready_config(bl_audio_callback_tx_ready_t cb, void *usrdata)
{
    cb_tx = cb;
    usrdata_tx = usrdata;

    return 0;
}

int bl_i2s_rx_ready_config(bl_audio_callback_rx_ready_t cb, void *usrdata)
{
    cb_rx = cb;
    usrdata_rx = usrdata;

    return 0;
}
