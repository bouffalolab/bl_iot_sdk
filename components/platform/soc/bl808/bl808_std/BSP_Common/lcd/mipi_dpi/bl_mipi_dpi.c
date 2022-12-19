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

#include "../lcd.h"

// #define BL616

#if (LCD_INTERFACE_TYPE == LCD_INTERFACE_DPI)

#include "bflb_platform.h"
#include "bl_mipi_dpi.h"

/* Video memory used for this frame, Update in frame interrupt*/
static volatile void *screen_last = NULL;

static lcd_mipi_dpi_init_t lcd_mipi_dpi_para;

typedef void (*standard_dpi_callback)(void);
static volatile standard_dpi_callback lcd_mipi_dpi_frame_callback = NULL;
static volatile standard_dpi_callback lcd_mipi_dpi_frame_swap_callback = NULL;

#if defined(BL808)
#include "bl808_dvp_tsrc.h"
#include "bl808_spp_misc.h"
#include "bl808_dbi.h"
#include "bl808_glb.h"

static DVP_TSRC_Cfg_Type dvpTsrcCfg = {
    .dataFromSensor = DISABLE,             /* Enable: pixel data is from sensor, disable: pixel data is from AXI */
    .sensorHsyncInverse = DISABLE,         /* Enable or disable inverse signal of sensor hsync */
    .sensorVsyncInverse = DISABLE,         /* Enable or disable inverse signal of sensor vsync */
    .yuv420Enable = DISABLE,               /* Enable or disable YUV420 mode, YUV420 data is from 2 different planar buffers when enable */
    .lineType = DVP_TSRC_YUV420_LINE_EVEN, /* Select UV send in Y even lines or odd lines */
    .swapMode = ENABLE,                    /* Enable or disable swap mode */
    .swapControl = DVP_TSRC_SWAP_SOFTWARE, /* Set swap index controlled by hardware or software */
    .dvp2axi = DVP_TSRC_DVP2AXI_0,         /* Choose dvp2axi used */

    .format = DVP_TSRC_PIXEL_RGB565_16TO24BIT, /* Set pixel data format */
    .byte0 = 0,                                /* Byte 0 selection */
    .byte1 = 2,                                /* Byte 1 Selection */
    .byte2 = 1,                                /* Byte 2 Selection */

    .burst = DVP_TSRC_BURST_TYPE_INCR16, /* AXI burst length */
    .hTotalCnt = 0,                      /* Horizontal total pixel count */
    .hBlankCnt = 0,                      /* Horizontal blank stage pixel count */
    .vTotalCnt = 0,                      /* Vertical total pixel count */
    .vBlankCnt = 0,                      /* Vertical blank stage pixel count */

    .prefetch = 0,      /* Vertical prefetch start position, relativeto blank start position */
    .fifoThreshold = 0, /* FIFO threshold for each DVP line to start to output */
    .memStartY0 = 0,    /* AXI2DVP start address, Y-planar in YUV420 mode, frame 0 in swap mode */
    .memSizeY0 = 0,     /* AXI2DVP memory size of memStartY0 */
    .memStartY1 = 0,    /* AXI2DVP start address, Y-planar in YUV420 mode,  frame 1 in swap mode, don't care if not swap mode */
    .memStartUV0 = 0,   /* AXI2DVP start address, UV-planar in YUV420 mode, frame 0 in swap mode, don't care if not YUV420 mode */
    .memStartUV1 = 0,   /* AXI2DVP start address, UV-planar in YUV420 mode, frame 1 in swap mode, don't care if not YUV420 swap mode */
};

static SPP_MISC_Display_Cfg_Type displayCfg = {
    .dpiEnable = ENABLE,                               /* Enable or disable dpi function */
    .bt1120Enable = DISABLE,                           /* Enable or disable BT1120 function, BT1120 and BT656 should not be enabled at the same time */
    .inputType = SPP_MISC_DISPLAY_TSRC_RGB_OUTPUT,     /* Select display input */
    .osdType = SPP_MISC_DISPLAY_OSD_RGB2YUV422_OUTPUT, /* Select display OSD input */
    .hsyncWidth = 0,                                   /* Horizontal synchronization width */
    .hfpWidth = 0,                                     /* Horizontal front porch width */
    .vsyncWidth = 0,                                   /* Vertical synchronization width */
    .vfpWidth = 0,                                     /* Vertical front porch width */
};

static void lcd_mipi_dpi_frame_interrupt(void)
{
    uint8_t swap_flag = 0;
    void *screen_next = NULL;

    SPP_MISC_Int_Clear(SPP_MISC_INT_DISPLAY);

    screen_next = (void *)(uintptr_t)BL_RD_REG(DVP_TSRC1_BASE, DTSRC_AXI2DVP_START_ADDR_BY);

    if (screen_last != screen_next) {
        swap_flag = 1;
        screen_last = screen_next;
    }

    if (lcd_mipi_dpi_frame_callback != NULL) {
        lcd_mipi_dpi_frame_callback();
    }

    if (lcd_mipi_dpi_frame_swap_callback != 0 && swap_flag) {
        lcd_mipi_dpi_frame_swap_callback();
    }
}

int lcd_mipi_dpi_init(lcd_mipi_dpi_init_t *dpi_para)
{
    uint32_t div;

    if (dpi_para == NULL) {
        return -1;
    }

    if (dpi_para->frame_buff == NULL) {
        return -1;
    }

    lcd_mipi_dpi_para = *dpi_para;

    /* Data Configuration */
    if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565) {
        dvpTsrcCfg.memSizeY0 = 2 * lcd_mipi_dpi_para.width * lcd_mipi_dpi_para.height;
        dvpTsrcCfg.format = DVP_TSRC_PIXEL_RGB565_16TO24BIT;
        dvpTsrcCfg.byte0 = 0;
        dvpTsrcCfg.byte1 = 2;
        dvpTsrcCfg.byte2 = 1;
    } else if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888) {
        dvpTsrcCfg.memSizeY0 = 4 * lcd_mipi_dpi_para.width * lcd_mipi_dpi_para.height;
        dvpTsrcCfg.format = DVP_TSRC_PIXEL_RGBA8888_32TO24BIT;
        dvpTsrcCfg.byte0 = 0;
        dvpTsrcCfg.byte1 = 1;
        dvpTsrcCfg.byte2 = 2;
    } else {
        return -2;
    }
    dvpTsrcCfg.fifoThreshold = lcd_mipi_dpi_para.width;
    dvpTsrcCfg.memStartY0 = (uint32_t)(uintptr_t)(lcd_mipi_dpi_para.frame_buff);

    /* RGB LCD Timing config */
    dvpTsrcCfg.hTotalCnt = lcd_mipi_dpi_para.hsw + lcd_mipi_dpi_para.hbp + lcd_mipi_dpi_para.width + lcd_mipi_dpi_para.hfp - 1;
    dvpTsrcCfg.hBlankCnt = lcd_mipi_dpi_para.hsw + lcd_mipi_dpi_para.hbp + lcd_mipi_dpi_para.hfp - 1;
    dvpTsrcCfg.vTotalCnt = lcd_mipi_dpi_para.vsw + lcd_mipi_dpi_para.vbp + lcd_mipi_dpi_para.height + lcd_mipi_dpi_para.vfp - 1;
    dvpTsrcCfg.vBlankCnt = lcd_mipi_dpi_para.vsw + lcd_mipi_dpi_para.vbp + lcd_mipi_dpi_para.vfp - 1;

    displayCfg.hsyncWidth = lcd_mipi_dpi_para.hsw - 1;
    displayCfg.hfpWidth = lcd_mipi_dpi_para.hfp - 1;
    displayCfg.vsyncWidth = lcd_mipi_dpi_para.vsw - 1;
    displayCfg.vfpWidth = lcd_mipi_dpi_para.vfp - 1;

    /* MIPI clock config */
    div = 1500 * 1000 * 1000;
    div /= (dvpTsrcCfg.hTotalCnt + 1) * (dvpTsrcCfg.vTotalCnt + 1);
    div /= (lcd_mipi_dpi_para.frame_rate) ? (lcd_mipi_dpi_para.frame_rate) : 60;
    GLB_Config_MIPI_PLL(GLB_XTAL_40M, mipiPllCfg_1500M);
    GLB_Set_Display_CLK(ENABLE, GLB_DISP_CLK_MIPIPLL_1500M, div);

    /* mipi dpi init */
    DVP_TSRC_Set_Swap_Index(DVP_TSRC1_ID, 1);
    DVP_TSRC_Init(DVP_TSRC1_ID, &dvpTsrcCfg);
    SPP_MISC_Display_Init(&displayCfg);

    /* frame interrupt config */
    SPP_MISC_Int_Mask(SPP_MISC_INT_ALL, MASK);
    SPP_MISC_SEOF_Set_Source(SPP_MISC_INT_DISPLAY, SPP_MISC_SEOF_DISPLAY_OUTPUT);
    SPP_MISC_SEOF_Set_Edge(SPP_MISC_INT_DISPLAY, SPP_MISC_SEOF_VSYNC_NEGEDGE);
    SPP_MISC_Int_Callback_Install(SPP_MISC_INT_DISPLAY, &lcd_mipi_dpi_frame_interrupt);
    SPP_MISC_Int_Mask(SPP_MISC_INT_DISPLAY, UNMASK);
    CPU_Interrupt_Enable(DISPLAY_IRQn);
    System_NVIC_SetPriority(DISPLAY_IRQn, 4, 1);

    /* clear cache */
    if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565) {
        L1C_DCache_Clean_By_Addr((uintptr_t)(lcd_mipi_dpi_para.frame_buff), 2 * lcd_mipi_dpi_para.width * lcd_mipi_dpi_para.height);
    } else if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888) {
        L1C_DCache_Clean_By_Addr((uintptr_t)(lcd_mipi_dpi_para.frame_buff), 4 * lcd_mipi_dpi_para.width * lcd_mipi_dpi_para.height);
    }

    /* enable DPI, Start output data*/
    DVP_TSRC_Enable(DVP_TSRC1_ID);

    return 0;
}

int lcd_mipi_dpi_screen_switch(void *screen_buffer)
{
    if (screen_buffer == NULL) {
        return -1;
    }

    if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565) {
        L1C_DCache_Clean_By_Addr((uintptr_t)(screen_buffer), 2 * lcd_mipi_dpi_para.width * lcd_mipi_dpi_para.height);
    } else if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888) {
        L1C_DCache_Clean_By_Addr((uintptr_t)(screen_buffer), 4 * lcd_mipi_dpi_para.width * lcd_mipi_dpi_para.height);
    }

    BL_WR_REG(DVP_TSRC1_BASE, DTSRC_AXI2DVP_START_ADDR_BY, (uint32_t)(uintptr_t)screen_buffer);

    return 0;
}

void *lcd_mipi_dpi_get_screen_using(void)
{
    return (void *)screen_last;
}

int lcd_mipi_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void))
{
    if (callback_type == LCD_MIPI_DPI_FRAME_INT_TYPE_SWAP) {
        lcd_mipi_dpi_frame_swap_callback = callback;
    } else if (callback_type == LCD_MIPI_DPI_FRAME_INT_TYPE_CYCLE) {
        lcd_mipi_dpi_frame_callback = callback;
    }
    return 0;
}

#elif defined(BL616)

/* PEC simulates the RGB scheme */

#include "bl616_glb.h"
#include "bl616_pec.h"
#include "pec_instr.h"
#include "bl616_dma.h"
#include "hal_dma.h"

/* DMA linked list of PEC controls data */
static DMA_LLI_Ctrl_Type dma_lli_dpi_header, dma_dpi_lli_tail;

/* DMA linked list of display buffer */
static DMA_LLI_Ctrl_Type dma_lli_dpi_buff[DPI_PEC_DMA_LLI_CACHE_NUM][DPI_PEC_VALID_PIXEL_MAX / DMA_MAX_COUNT + 1];

/* Invalid row control parameter, Will be sent to PEC before and after the buffer */
static uint32_t pec_dpi_invalid_lin_para[(DPI_PEC_INVALID_LIN_MAX + 1) * 2];

/* dma lli cache table */
static volatile pec_dpi_dma_lli_cache_t dma_lli_cache_table[DPI_PEC_DMA_LLI_CACHE_NUM];

/* Total number of dma_transfer */
static volatile uint32_t pec_dpi_dma_lli_num;

/* next display buffer */
static volatile void *next_disp_buffer;

static int pec_dpi_dma_lli_init(lcd_mipi_dpi_init_t *dpi_para);
static int pec_dpi_dma_lli_update(void *disp_buff);
static void pec_dpi_dma_interrupt(struct device *dev, void *args, uint32_t size, uint32_t event);

int lcd_mipi_dpi_init(lcd_mipi_dpi_init_t *dpi_para)
{
    PEC_SM_CFG_Type smCfg = { 0 };
    uint8_t syncVenHen, syncVenHdis, syncVdisHen, syncVdisHdis;
    uint8_t setClklDe, setClkhDe, setClklDis, setClkhDis;
    uint32_t data32, data32_1, data32_2;
    uint32_t i;
    uint16_t pixel_width;

#if DATA_LATCH_MODE
#if DE_MODE
    uint8_t setLatLL = 0;
    uint8_t setLatLH = 4;
#else
    uint8_t setLatLL = 0;
    uint8_t setLatLH = 2;
#endif
#endif

    if (dpi_para == NULL) {
        return -1;
    }

    if (dpi_para->frame_buff == NULL) {
        return -1;
    }

    lcd_mipi_dpi_para = *dpi_para;

    if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565) {
        pixel_width = 16;
    } else if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888) {
        pixel_width = 24;
    } else {
        return -2;
    }

    /* clock config */
    data32 = (20 * 1000 * 1000);
    data32 /= (lcd_mipi_dpi_para.hsw + lcd_mipi_dpi_para.hbp + lcd_mipi_dpi_para.width + lcd_mipi_dpi_para.hfp);
    data32 /= (lcd_mipi_dpi_para.vsw + lcd_mipi_dpi_para.vbp + lcd_mipi_dpi_para.height + lcd_mipi_dpi_para.vfp);
    data32 /= (lcd_mipi_dpi_para.frame_rate) ? (lcd_mipi_dpi_para.frame_rate) : 60;

    GLB_Set_PEC_CLK(ENABLE, GLB_PEC_CLK_MCU_MUXPLL_160M, data32);

    syncVenHen = 4 | ((V_SYNC_SINGLE_POL) ? 2 : 0) | ((H_SYNC_SINGLE_POL) ? 1 : 0);
    syncVenHdis = 4 | ((V_SYNC_SINGLE_POL) ? 2 : 0) | ((H_SYNC_SINGLE_POL) ? 0 : 1);
    syncVdisHen = 4 | ((V_SYNC_SINGLE_POL) ? 0 : 2) | ((H_SYNC_SINGLE_POL) ? 1 : 0);
    syncVdisHdis = 4 | ((V_SYNC_SINGLE_POL) ? 0 : 2) | ((H_SYNC_SINGLE_POL) ? 0 : 1);
    setClklDe = (DE_SINGLE_POL) ? 2 : 0;
    setClkhDe = ((DE_SINGLE_POL) ? 2 : 0) | 1;
    setClklDis = (DE_SINGLE_POL) ? 0 : 2;
    setClkhDis = ((DE_SINGLE_POL) ? 0 : 2) | 1;

    PEC_SM_Enable(PEC_ID_USE, SM_ID_USE, DISABLE);
    smCfg.clkDivInt = 1;                       /*!< Effective frequency is sysclk/int. Value of 0 is interpreted as max possible value */
    smCfg.clkDivFrac = 0;                      /*!< Fractional part of clock divider */
    smCfg.pcOrigin = 3;                        /*!< Beginning of the program for SM */
    smCfg.sideOptionEnable = ENABLE;           /*!< Allow instructions to perform sideset optionally, rather than on every instruction */
    smCfg.sideDest = PEC_SIDE_DEST_PINVAL;     /*!< Side data is asserted to pin OEs or pin values */
    smCfg.wrapTop = 31;                        /*!< After reaching this address, execution is wrapped to wrap_bottom */
    smCfg.wrapBottom = 3;                      /*!< After reaching wrap_top, execution is wrapped to this address */
    smCfg.threshBitsPull = 32;                 /*!< Number of bits shifted out of TXSR before autopull or conditional pull, 0~32 */
    smCfg.threshFifoTx = 4 - 1;                /*!< Threshold of TX FIFO for interrupt and DMA, 0~7 */
    smCfg.osrDir = PEC_REG_SHIFT_DIR_TO_RIGHT; /*!< Shift OSR direction */
    smCfg.isrDir = PEC_REG_SHIFT_DIR_TO_RIGHT; /*!< Shift ISR direction */
    smCfg.autoPull = DISABLE;                  /*!< Pull automatically when the output shift register is emptied */
    smCfg.pinSideCount = 3;                    /*!< The number of delay bits co-opted for side-set. Inclusive of the enable bit, if present */

#if (DATA_LATCH_MODE == 0)
    smCfg.pinSetCount = 2;                     /*!< The number of pins asserted by a SET. Max of 5 */
    smCfg.pinOutCount = 16;                    /*!< The number of pins asserted by an OUT. Value of 0 to 32 pins */
#elif (DATA_LATCH_MODE == 1)
    smCfg.pinSetCount = 3; /*!< The number of pins asserted by a SET. Max of 5 */
    smCfg.pinOutCount = 8; /*!< The number of pins asserted by an OUT. Value of 0 to 32 pins */
#endif

    smCfg.pinSideBase = (PIN_HSYNC % 32);     /*!< The virtual pin corresponding to SIDESET bit 0 */
    smCfg.pinSetBase = (PIN_CLK % 32);        /*!< The virtual pin corresponding to SET bit 0 */
    smCfg.pinOutBase = (PIN_DATA_START % 32); /*!< The virtual pin corresponding to OUT bit 0 */

    // smCfg.txFifoDma = ENABLE;                /*!< Enable signal of dma_tx_req/ack interface */
    PEC_SM_Init(PEC_ID_USE, SM_ID_USE, &smCfg);
    PEC_FifoClear(PEC_ID_USE, SM_ID_USE, PEC_FIFO_DIR_RX);
    PEC_FifoClear(PEC_ID_USE, SM_ID_USE, PEC_FIFO_DIR_TX);

    /* place instruction */
    /* instruction: in region vSync and hSync all active */
    PEC_PlaceInstruction(PEC_ID_USE, 0, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClklDis, 0, 3, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 1, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClkhDis, 0, 2, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 2, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_X_WITH_DEC, 0, 0, 0, 3));
    /* instruction: pull data and jump */
    PEC_PlaceInstruction(PEC_ID_USE, 3, PEC_InstrEncodePULL(PEC_INSTR_PULL_IFE_DISABLE, PEC_INSTR_PULL_BLK_ENABLE, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 4, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_X, 16, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 5, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_EXEC, 16, 0, 0, 3));
    /* instruction: picture height, storeed in Y register */
    PEC_PlaceInstruction(PEC_ID_USE, 6, PEC_InstrEncodeMOV(PEC_INSTR_MOV_DEST_Y, PEC_INSTR_MOV_SRC_X, PEC_INSTR_MOV_OP_NONE, 0, 0, 3));
    /* instruction: ISR store Hact, hbp and hSync */
    PEC_PlaceInstruction(PEC_ID_USE, 7, PEC_InstrEncodeMOV(PEC_INSTR_MOV_DEST_OSR, PEC_INSTR_MOV_SRC_ISR, PEC_INSTR_MOV_OP_NONE, 0, 0, 3));
    /* instruction: OSR[6:0] for hSync */
    PEC_PlaceInstruction(PEC_ID_USE, 8, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_X, 7, syncVdisHen, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 9, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClklDis, 0, 3, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 10, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClkhDis, 0, 2, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 11, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_X_WITH_DEC, 9, 0, 0, 3));
    /* instruction: OSR[13:7] for hSync */
    PEC_PlaceInstruction(PEC_ID_USE, 12, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_X, 7, syncVdisHdis, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 13, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClklDis, 0, 3, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 14, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClkhDis, 0, 2, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 15, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_X_WITH_DEC, 13, 0, 0, 3));
    /* instruction: OSR[24:14] for HACT */
    PEC_PlaceInstruction(PEC_ID_USE, 16, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_X, 11, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 17, PEC_InstrEncodePULL(PEC_INSTR_PULL_IFE_DISABLE, PEC_INSTR_PULL_BLK_ENABLE, 0, 0, 3));
#if (DATA_LATCH_MODE == 0)
    PEC_PlaceInstruction(PEC_ID_USE, 18, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_PINS, 16, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 19, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClklDe, 0, 3, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 20, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClkhDe, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 21, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_OSR_NEMPTY, 18, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 22, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_X_WITH_DEC, 17, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 23, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_ALWAYS, 25, 0, 0, 3));
#elif (DATA_LATCH_MODE == 1)
    PEC_PlaceInstruction(PEC_ID_USE, 18, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClklDe | setLatLH, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 19, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_PINS, 8, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 20, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClklDe | setLatLL, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 21, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_PINS, 8, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 22, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClkhDe | setLatLL, 0, 1, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 23, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_OSR_NEMPTY, 18, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 24, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_X_WITH_DEC, 17, 0, 0, 3));
#endif
    /* instruction: OSR[31:25] for hfp */
    PEC_PlaceInstruction(PEC_ID_USE, 25, PEC_InstrEncodeMOV(PEC_INSTR_MOV_DEST_OSR, PEC_INSTR_MOV_SRC_ISR, PEC_INSTR_MOV_OP_NONE, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 26, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_NULL, 25, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 27, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_X, 7, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 28, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClklDis, 0, 3, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 29, PEC_InstrEncodeSET(PEC_INSTR_SET_DEST_PINS, setClkhDis, 0, 2, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 30, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_X_WITH_DEC, 28, 0, 0, 3));
    PEC_PlaceInstruction(PEC_ID_USE, 31, PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_Y_WITH_DEC, 7, 0, 0, 3));

    /* Configure pins */
    PEC_PadOutputValueSet(PEC_ID_USE, (PIN_HSYNC % 32), (H_SYNC_SINGLE_POL) ? 0 : 1);
    PEC_PadDirectionSet(PEC_ID_USE, (PIN_HSYNC % 32), PEC_PAD_DIRECTION_OUTPUT);
    PEC_PadOutputValueSet(PEC_ID_USE, (PIN_HSYNC % 32) + 1, (V_SYNC_SINGLE_POL) ? 0 : 1);
    PEC_PadDirectionSet(PEC_ID_USE, (PIN_HSYNC % 32) + 1, PEC_PAD_DIRECTION_OUTPUT);
    PEC_PadOutputValueSet(PEC_ID_USE, (PIN_CLK % 32), 0);
    PEC_PadDirectionSet(PEC_ID_USE, (PIN_CLK % 32), PEC_PAD_DIRECTION_OUTPUT);
#if (DATA_LATCH_MODE == 0)
    for (i = 0; i < pixel_width; i++) {
        PEC_PadOutputValueSet(PEC_ID_USE, (PIN_DATA_START % 32) + i, 0);
        PEC_PadDirectionSet(PEC_ID_USE, (PIN_DATA_START % 32) + i, PEC_PAD_DIRECTION_OUTPUT);
    }
    if (DE_MODE) {
        PEC_PadOutputValueSet(PEC_ID_USE, (PIN_CLK % 32) + 1, (DE_SINGLE_POL) ? 0 : 1);
        PEC_PadDirectionSet(PEC_ID_USE, (PIN_CLK % 32) + 1, PEC_PAD_DIRECTION_OUTPUT);
    }
#elif (DATA_LATCH_MODE == 1)
    for (i = 0; i < (pixel_width + 1) >> 1; i++) {
        PEC_PadOutputValueSet(PEC_ID_USE, (PIN_DATA_START % 32) + i, 0);
        PEC_PadDirectionSet(PEC_ID_USE, (PIN_DATA_START % 32) + i, PEC_PAD_DIRECTION_OUTPUT);
    }
    if (DE_MODE) {
        PEC_PadOutputValueSet(PEC_ID_USE, (PIN_CLK % 32), (DE_SINGLE_POL) ? 0 : 1);
        PEC_PadDirectionSet(PEC_ID_USE, (PIN_CLK % 32), PEC_PAD_DIRECTION_OUTPUT);
        PEC_PadOutputValueSet(PEC_ID_USE, (PIN_CLK % 32) + 1, 0);
        PEC_PadDirectionSet(PEC_ID_USE, (PIN_CLK % 32) + 1, PEC_PAD_DIRECTION_OUTPUT);
    } else {
        PEC_PadOutputValueSet(PEC_ID_USE, (PIN_CLK % 32), 0);
        PEC_PadDirectionSet(PEC_ID_USE, (PIN_CLK % 32), PEC_PAD_DIRECTION_OUTPUT);
    }
#endif

    /* Initialize some register */
    if (pixel_width > 16) {
        data32 = lcd_mipi_dpi_para.width;
    } else {
        data32 = lcd_mipi_dpi_para.width >> 1;
    }
    data32 = ((lcd_mipi_dpi_para.hfp - 1) << 25) | ((data32 - 1) << 14) | ((lcd_mipi_dpi_para.hbp - 1) << 7) | ((lcd_mipi_dpi_para.hsw - 1) << 0);
    PEC_TxFifoWrite(PEC_ID_USE, SM_ID_USE, data32);
    PEC_ExecInstructionImmediately(PEC_ID_USE, SM_ID_USE, PEC_InstrEncodePULL(PEC_INSTR_PULL_IFE_DISABLE, PEC_INSTR_PULL_BLK_ENABLE, 0, 0, 0), PEC_TIMEOUT_MAX);
    PEC_ExecInstructionImmediately(PEC_ID_USE, SM_ID_USE, PEC_InstrEncodeOUT(PEC_INSTR_OUT_DEST_ISR, 32, 0, 0, 0), PEC_TIMEOUT_MAX);

    /* Initialize memory data - vsw data  */
    data32_1 = PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_ALWAYS, 0, syncVenHen, 0, 3);
    data32_1 = (data32_1 << 16) | (lcd_mipi_dpi_para.hsw - 1);
    data32_2 = PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_ALWAYS, 0, syncVenHdis, 0, 3);
    data32_2 = (data32_2 << 16) | (lcd_mipi_dpi_para.hbp + lcd_mipi_dpi_para.width + lcd_mipi_dpi_para.hfp - 1);

    for (i = 0; i < (lcd_mipi_dpi_para.vsw) * 2; i += 2) {
        pec_dpi_invalid_lin_para[i] = data32_1;
        pec_dpi_invalid_lin_para[i + 1] = data32_2;
    }

    /* Initialize memory data - vbp data  */
    data32_1 = PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_ALWAYS, 0, syncVdisHen, 0, 3);
    data32_1 = (data32_1 << 16) | (lcd_mipi_dpi_para.hsw - 1);
    data32_2 = PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_ALWAYS, 0, syncVdisHdis, 0, 3);
    data32_2 = (data32_2 << 16) | (lcd_mipi_dpi_para.hbp + lcd_mipi_dpi_para.width + lcd_mipi_dpi_para.hfp - 1);

    for (i = (lcd_mipi_dpi_para.vsw) * 2; i < (lcd_mipi_dpi_para.vsw + lcd_mipi_dpi_para.vbp) * 2; i += 2) {
        pec_dpi_invalid_lin_para[i] = data32_1;
        pec_dpi_invalid_lin_para[i + 1] = data32_2;
    }

    /* Initialize memory data - display buff start date */
    data32_1 = PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_ALWAYS, 6, 0, 0, 3);
    data32_1 = (data32_1 << 16) | (lcd_mipi_dpi_para.height - 1);

    pec_dpi_invalid_lin_para[(lcd_mipi_dpi_para.vsw + lcd_mipi_dpi_para.vbp) * 2] = data32_1;

    /* Initialize memory data - vfp data  */
    data32_1 = PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_ALWAYS, 0, syncVdisHen, 0, 3);
    data32_1 = (data32_1 << 16) | (lcd_mipi_dpi_para.hsw - 1);
    data32_2 = PEC_InstrEncodeJMP(PEC_INSTR_JMP_COND_ALWAYS, 0, syncVdisHdis, 0, 3);
    data32_2 = (data32_2 << 16) | (lcd_mipi_dpi_para.hbp + lcd_mipi_dpi_para.width + lcd_mipi_dpi_para.hfp - 1);

    for (i = (lcd_mipi_dpi_para.vsw + lcd_mipi_dpi_para.vbp + 1) * 2; i < (lcd_mipi_dpi_para.vsw + lcd_mipi_dpi_para.vbp + lcd_mipi_dpi_para.vfp + 1) * 2; i += 2) {
        pec_dpi_invalid_lin_para[i] = data32_1;
        pec_dpi_invalid_lin_para[i + 1] = data32_2;
    }

    L1C_DCache_Clean_By_Addr((uintptr_t)pec_dpi_invalid_lin_para, sizeof(pec_dpi_invalid_lin_para));

    PEC_DMA_Enable(PEC_ID_USE, SM_ID_USE, PEC_FIFO_DIR_TX, ENABLE);
    PEC_SM_Enable(PEC_ID_USE, SM_ID_USE, ENABLE);

    /* dma lli init */
    pec_dpi_dma_lli_init(dpi_para);
    pec_dpi_dma_lli_update(lcd_mipi_dpi_para.frame_buff);

    /* init DMA */
    dma_register(DMA_HAL_INDEX, "dma_pce_dpi");
    struct device *dma_pce_dpi = device_find("dma_pce_dpi");

    if (dma_pce_dpi) {
        DMA_DEV(dma_pce_dpi)->direction = DMA_MEMORY_TO_PERIPH;
        DMA_DEV(dma_pce_dpi)->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(dma_pce_dpi)->src_req = DMA_REQUEST_NONE;
        DMA_DEV(dma_pce_dpi)->dst_req = DMA_REQ_PEC0_TX + SM_ID_USE;
        DMA_DEV(dma_pce_dpi)->src_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
        DMA_DEV(dma_pce_dpi)->dst_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
        DMA_DEV(dma_pce_dpi)->src_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_pce_dpi)->dst_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_pce_dpi)->src_width = DMA_TRANSFER_WIDTH_32BIT;
        DMA_DEV(dma_pce_dpi)->dst_width = DMA_TRANSFER_WIDTH_32BIT;
        device_open(dma_pce_dpi, 0);

        /* HAL DMA driver interrupt management */
        device_set_callback(dma_pce_dpi, pec_dpi_dma_interrupt);
        device_control(dma_pce_dpi, DEVICE_CTRL_SET_INT, NULL);
    }

    /* STD DMA driver lli management */
    DMA_LLI_Update(DMA_ID_USE, DMA_CHAN_USE, (uint32_t)(uintptr_t)(&dma_lli_dpi_header));
    DMA_Channel_Enable(DMA_ID_USE, DMA_CHAN_USE);

    return 0;
}

int lcd_mipi_dpi_screen_switch(void *screen_buffer)
{
    /* clean cache */
    if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565) {
        L1C_DCache_Clean_By_Addr((uintptr_t)(screen_buffer), 2 * lcd_mipi_dpi_para.width * lcd_mipi_dpi_para.height);
    } else if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888) {
        L1C_DCache_Clean_By_Addr((uintptr_t)(screen_buffer), 4 * lcd_mipi_dpi_para.width * lcd_mipi_dpi_para.height);
    }

    next_disp_buffer = screen_buffer;
    return 0;
}

void *lcd_mipi_dpi_get_screen_using(void)
{
    return (void *)screen_last;
}

static void pec_dpi_dma_interrupt(struct device *dev, void *args, uint32_t size, uint32_t event)
{
    uint8_t swap_flag = 0;

    /* update dma for frame */
    pec_dpi_dma_lli_update((void *)next_disp_buffer);

    DMA_Channel_Disable(DMA_ID_USE, DMA_CHAN_USE);
    DMA_LLI_Update(DMA_ID_USE, DMA_CHAN_USE, (uint32_t)(uintptr_t)(&dma_lli_dpi_header));
    DMA_Channel_Enable(DMA_ID_USE, DMA_CHAN_USE);

    if (screen_last != next_disp_buffer) {
        swap_flag = 1;
        screen_last = next_disp_buffer;
    }

    if (lcd_mipi_dpi_frame_callback != NULL) {
        lcd_mipi_dpi_frame_callback();
    }

    if (lcd_mipi_dpi_frame_swap_callback != 0 && swap_flag) {
        lcd_mipi_dpi_frame_swap_callback();
    }
}

int lcd_mipi_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void))
{
    if (callback_type == LCD_MIPI_DPI_FRAME_INT_TYPE_SWAP) {
        lcd_mipi_dpi_frame_swap_callback = callback;
    } else if (callback_type == LCD_MIPI_DPI_FRAME_INT_TYPE_CYCLE) {
        lcd_mipi_dpi_frame_callback = callback;
    }
    return 0;
}

static int pec_dpi_dma_lli_init(lcd_mipi_dpi_init_t *dpi_para)
{
    uint16_t i, j;
    uint32_t temp, dma_count;

    /* get total number of dma_transfer */
    if (lcd_mipi_dpi_para.pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565) {
        dma_count = (lcd_mipi_dpi_para.width * dpi_para->height) * 2 / 4;
    } else if (dpi_para->pixel_format == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888) {
        dma_count = (dpi_para->width * dpi_para->height);
    } else {
        return -1;
    }

    /* Initialize DMA and controls data lli */
    dma_lli_dpi_header.dmaCtrl.SBSize = DMA_BURST_SIZE_4;
    dma_lli_dpi_header.dmaCtrl.dst_min_mode = DISABLE;
    dma_lli_dpi_header.dmaCtrl.DBSize = DMA_BURST_SIZE_4;
    dma_lli_dpi_header.dmaCtrl.dst_add_mode = DISABLE;
    dma_lli_dpi_header.dmaCtrl.SWidth = DMA_TRNS_WIDTH_32BITS;
    dma_lli_dpi_header.dmaCtrl.DWidth = DMA_TRNS_WIDTH_32BITS;
    dma_lli_dpi_header.dmaCtrl.fix_cnt = 0;
    dma_lli_dpi_header.dmaCtrl.SI = DMA_MINC_ENABLE;
    dma_lli_dpi_header.dmaCtrl.DI = DMA_MINC_DISABLE;
    dma_lli_dpi_header.dmaCtrl.I = 0;
    dma_lli_dpi_header.destDmaAddr = PEC_BASE + PEC_TXF0_OFFSET + SM_ID_USE * 4;
    dma_lli_dpi_header.srcDmaAddr = (uint32_t)(uintptr_t)pec_dpi_invalid_lin_para;
    dma_lli_dpi_header.dmaCtrl.TransferSize = (dpi_para->vsw + dpi_para->vbp) * 2 + 1;
    dma_lli_dpi_header.nextLLI = (uint32_t)(uintptr_t)NULL;

    dma_dpi_lli_tail = dma_lli_dpi_header;
    dma_dpi_lli_tail.dmaCtrl.I = 1;
    dma_dpi_lli_tail.srcDmaAddr = (uint32_t)(uintptr_t)&pec_dpi_invalid_lin_para[(dpi_para->vsw + dpi_para->vbp + 1) * 2];
    dma_dpi_lli_tail.dmaCtrl.TransferSize = dpi_para->vfp * 2;

    L1C_DCache_Clean_By_Addr((uintptr_t)&dma_dpi_lli_tail, sizeof(DMA_LLI_Ctrl_Type));

    /* Initialize display buffer data lli, but do not load data */
    dma_lli_dpi_buff[0][0].dmaCtrl.SBSize = DMA_BURST_SIZE_4;
    dma_lli_dpi_buff[0][0].dmaCtrl.dst_min_mode = DISABLE;
    dma_lli_dpi_buff[0][0].dmaCtrl.DBSize = DMA_BURST_SIZE_4;
    dma_lli_dpi_buff[0][0].dmaCtrl.dst_add_mode = DISABLE;
    dma_lli_dpi_buff[0][0].dmaCtrl.SWidth = DMA_TRNS_WIDTH_32BITS;
    dma_lli_dpi_buff[0][0].dmaCtrl.DWidth = DMA_TRNS_WIDTH_32BITS;
    dma_lli_dpi_buff[0][0].dmaCtrl.fix_cnt = 0;
    dma_lli_dpi_buff[0][0].dmaCtrl.SI = DMA_MINC_ENABLE;
    dma_lli_dpi_buff[0][0].dmaCtrl.DI = DMA_MINC_DISABLE;
    dma_lli_dpi_buff[0][0].dmaCtrl.I = 0;
    dma_lli_dpi_buff[0][0].destDmaAddr = PEC_BASE + PEC_TXF0_OFFSET + SM_ID_USE * 4;
    dma_lli_dpi_buff[0][0].srcDmaAddr = (uint32_t)(uintptr_t)(NULL);
    dma_lli_dpi_buff[0][0].dmaCtrl.TransferSize = DMA_MAX_COUNT;
    dma_lli_dpi_buff[0][0].nextLLI = (uint32_t)(uintptr_t)NULL;

    for (i = 0; i < DPI_PEC_DMA_LLI_CACHE_NUM; i++) {
        temp = dma_count;
        for (j = 0; temp > 0; j++) {
            dma_lli_dpi_buff[i][j] = dma_lli_dpi_buff[0][0];
            dma_lli_dpi_buff[i][j].nextLLI = (uint32_t)(uintptr_t)(&dma_lli_dpi_buff[i][j + 1]);
            temp = (temp > DMA_MAX_COUNT) ? (temp - DMA_MAX_COUNT) : (0);
        }
        dma_lli_dpi_buff[i][j - 1].nextLLI = (uint32_t)(uintptr_t)(&dma_dpi_lli_tail);
        dma_lli_dpi_buff[i][j - 1].dmaCtrl.TransferSize = dma_count % DMA_MAX_COUNT;

        L1C_DCache_Clean_By_Addr((uintptr_t)dma_lli_dpi_buff[i], sizeof(DMA_LLI_Ctrl_Type) * (j + 1));
    }
    pec_dpi_dma_lli_num = j;

    for (i = 0; i < DPI_PEC_DMA_LLI_CACHE_NUM; i++) {
        dma_lli_cache_table[i].disp_buff = NULL;
        dma_lli_cache_table[i].dma_lli = dma_lli_dpi_buff[i];
        dma_lli_cache_table[i].lru_value = DPI_PEC_DMA_LLI_CACHE_NUM;
    }

    return 0;
}

static int pec_dpi_dma_lli_update(void *disp_buff)
{
    uint16_t idx, idx_oldest = 0, lru_v = 0;

    /* Looking for the cache table */
    for (idx = 0; idx < DPI_PEC_DMA_LLI_CACHE_NUM; idx++) {
        if (dma_lli_cache_table[idx].disp_buff == disp_buff) {
            lru_v = dma_lli_cache_table[idx].lru_value;
            break;
        } else if (dma_lli_cache_table[idx].lru_value > lru_v) {
            lru_v = dma_lli_cache_table[idx].lru_value;
            idx_oldest = idx;
        }
    }

    /* Not cached, Add to the cache table */
    if (idx >= DPI_PEC_DMA_LLI_CACHE_NUM) {
        idx = idx_oldest;
        /* update dma lli */
        DMA_LLI_Ctrl_Type *lli_p = dma_lli_cache_table[idx].dma_lli;
        for (uint16_t i = 0; i < pec_dpi_dma_lli_num; i++) {
            lli_p[i].srcDmaAddr = (uint32_t)(uintptr_t)(disp_buff) + (i * DMA_MAX_COUNT * 4);
        }
        L1C_DCache_Clean_By_Addr((uintptr_t)lli_p, sizeof(DMA_LLI_Ctrl_Type) * pec_dpi_dma_lli_num);

        dma_lli_cache_table[idx].disp_buff = disp_buff;
    }

    dma_lli_dpi_header.nextLLI = (uint32_t)(uintptr_t)(dma_lli_cache_table[idx].dma_lli);

    /* update cache table lru_value */
    dma_lli_cache_table[idx].lru_value = 0;
    for (idx = 0; idx < DPI_PEC_DMA_LLI_CACHE_NUM; idx++) {
        if (dma_lli_cache_table[idx].lru_value < lru_v) {
            dma_lli_cache_table[idx].lru_value++;
        }
    }

    return 0;
}

#else
#error "Devices that do not support DPI! Replace the driver port (lcd.h)"
#endif

#endif
