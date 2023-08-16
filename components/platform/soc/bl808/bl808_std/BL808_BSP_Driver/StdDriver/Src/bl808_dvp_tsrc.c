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
#include <stdint.h>
#include <bl808.h>

#include <dvp_tsrc_axi_reg.h>
#include <bl808_dvp_tsrc.h>
#include "dtsrc_reg.h"

static const uint32_t DVPTSRC_BASE_ADDR_SET[] =
    {ISP_DVP_TSRC_BASE, HDMI_DVP_TSRC_BASE};

static BL_Fun_Type is_data_from_axi[2] = {DISABLE, DISABLE};

/** @defgroup  DVP_TSRC_Private_Variables
 *  @{
 */
static const uint32_t dvpTsrcAddr[DVP_TSRC_ID_MAX] = {DVP_TSRC0_BASE,DVP_TSRC1_BASE};

static int DVP_TSRC_Update_Input_Mode(ISP_DVP_TSRC_SEL_E dvp_tsrc, ISP_DVP_TSRC_INPUT_E dvp_input)
{
    dvp_tsrc_axi_reg_t *dvp_tsrc_reg = (dvp_tsrc_axi_reg_t*)DVPTSRC_BASE_ADDR_SET[dvp_tsrc];

	switch (dvp_input)
	{
        case DVP_TSRC_INPUT_SENSOR:
            dvp_tsrc_reg->config.BF.cr_snsr_en = 1;         /* pixel data is from sensor or ISP */
            is_data_from_axi[dvp_tsrc] = DISABLE;           /* pixel data is NOT from AXI */
            break;

        case DVP_TSRC_INPUT_AHB:
            dvp_tsrc_reg->config.BF.cr_snsr_en = 0;         /* pixel data is NOT from sensor or ISP */
            is_data_from_axi[dvp_tsrc] = ENABLE;            /* pixel data is from AXI */
            break;

        case DVP_TSRC_INPUT_FAKEDATA:
            dvp_tsrc_reg->config.BF.cr_snsr_en = 0;         /* pixel data is NOT from sensor or ISP */
            is_data_from_axi[dvp_tsrc] = DISABLE;           /* pixel data is NOT from AXI */
            break;

        default:
            dvp_tsrc_reg->config.BF.cr_snsr_en = 0;         /* pixel data is NOT from sensor or ISP */
            is_data_from_axi[dvp_tsrc] = DISABLE;           /* pixel data is NOT from AXI */
            BL_LOGE("DVP_TSRC_Update_Input_Mode: unregonized dvp_input %d\r\n", dvp_input);
            return -1;
    }

    return 0;
}

void ISP_DVPTSrc_SetFrameSize(ISP_DVP_TSRC_SEL_E dvp_tsrc, DVPTSrc_Frame_Size_Cfg_Type *cfg)
{
    uint32_t DVPTSRCx = DVPTSRC_BASE_ADDR_SET[dvp_tsrc];
    uint32_t tmpVal;

    CHECK_PARAM(cfg->vBlank > 4);

	tmpVal = BL_RD_REG(DVPTSRCx, DVP_TSRC_AXI_FRAME_SIZE_H);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP_TSRC_AXI_CR_TOTAL_H, cfg->width + cfg->hBlank - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP_TSRC_AXI_CR_BLANK_H, cfg->hBlank - 1);
    BL_WR_REG(DVPTSRCx, DVP_TSRC_AXI_FRAME_SIZE_H, tmpVal);

	tmpVal = BL_RD_REG(DVPTSRCx, DVP_TSRC_AXI_FRAME_SIZE_V);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP_TSRC_AXI_CR_TOTAL_V, cfg->height + cfg->vBlank - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP_TSRC_AXI_CR_BLANK_V, cfg->vBlank - 1);
    BL_WR_REG(DVPTSRCx, DVP_TSRC_AXI_FRAME_SIZE_V, tmpVal);

    /* vertical prefetch start position, at least cr_blank_v - 4, to avoid drain error at beginning */
	tmpVal = BL_RD_REG(DVPTSRCx, DVP_TSRC_AXI_AXI2DVP_PREFETCH);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP_TSRC_AXI_CR_PREFETCH_V, cfg->vBlank - 4);
    BL_WR_REG(DVPTSRCx, DVP_TSRC_AXI_AXI2DVP_PREFETCH, tmpVal);
}

int ISP_DVP_TSrc_Cfg(ISP_DVP_TSRC_SEL_E dvp_tsrc, ISP_DVP_TSRC_CFG_S *cfg)
{
    dvp_tsrc_axi_reg_t *dvp_tsrc_reg = (dvp_tsrc_axi_reg_t*)DVPTSRC_BASE_ADDR_SET[dvp_tsrc];

    DVP_TSRC_Update_Input_Mode(dvp_tsrc, cfg->dvp_input);

    if (cfg->dvp_input == DVP_TSRC_INPUT_SENSOR) {
        /* suppose vsync pulse is high. Set vsync_inv to 1 to trigger frame start from vsync neg edge,
            so we can capture the very first frame output by sensor */
#if ENABLE_DVP_RESHAPE
        dvp_tsrc_reg->config.BF.cr_snsr_vsync_inv = 0;
#else
        dvp_tsrc_reg->config.BF.cr_snsr_vsync_inv = 1;
#endif
        /* FIFO threshold for each DVP line to start to output */
        dvp_tsrc_reg->snsr2dvp_wait_pos.BF.cr_snsr_fifo_th = cfg->snsr_fifo_th;
    }
    else if (cfg->dvp_input == DVP_TSRC_INPUT_AHB) {
        //if (cfg->y_only)    pic_size >>= 1;     /* 1 byte per pixel */
        //dvp_tsrc_reg->config.BF.cr_axi2dvp_8bit_mode = cfg->y_only;   /* 8-bit per pixel (Y-only) */

        dvp_tsrc_reg->config.BF.cr_axi2dvp_swap_mode = cfg->swap_mode;        /* enable swap mode */
        dvp_tsrc_reg->config.BF.cr_axi2dvp_swap_idx_sel = cfg->swap_index;    /* swap index */
    }
    else {        /* generate fack pattern */
        /* keep high 8-bit (UV) as 128, low 8-bit (Y) gradient */
        /* MAX: {8'd128, 8'd255}, MIN: {8'd128, 8'd0} */
        dvp_tsrc_reg->pix_data_range.BF.cr_data_min = 0x8000;// 0x8000;
        dvp_tsrc_reg->pix_data_range.BF.cr_data_max = 0x80ff;//0x80ff;
        /* Data step 1 */
        dvp_tsrc_reg->pix_data_step.BF.cr_data_step = 4;
    }

#if 0 //debug isp direct hdmi
    if (DVP_TSRC_HDMI == dvp_tsrc) {
        dvp_tsrc_reg->config.BF.cr_snsr_en = 1;
        dvp_tsrc_reg->config.BF.cr_axi2dvp_en = 0;
        dvp_tsrc_reg->snsr2dvp_wait_pos.BF.cr_snsr_fifo_th = 220;
        is_data_from_axi[dvp_tsrc] = false;
    }
#endif
    return 0;
}

void ISP_DVP_TSrc_MemCfg(ISP_DVP_TSRC_SEL_E dvp_tsrc, uint32_t bufAddr, uint32_t bufSize)
{
    uint32_t DVPTSRCx = DVPTSRC_BASE_ADDR_SET[dvp_tsrc];
	uint32_t frm_buf_size;

    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

	if (dvp_tsrc == DVP_TSRC_HDMI) {
		/* Assume the buf actually contains double frame buffers */
		frm_buf_size = bufSize >> 1;
	    BL_WR_REG(DVPTSRCx, DVP_TSRC_AXI_AXI2DVP_START_ADDR, bufAddr);
	    BL_WR_REG(DVPTSRCx, DVP_TSRC_AXI_AXI2DVP_SWAP_ADDR, bufAddr + frm_buf_size);
	} else {	/* DVP_TSRC_ISP */
		/* Assume the buf actually contains only one frame buffers */
		frm_buf_size = bufSize;
	    BL_WR_REG(DVPTSRCx, DVP_TSRC_AXI_AXI2DVP_START_ADDR, bufAddr);
	    BL_WR_REG(DVPTSRCx, DVP_TSRC_AXI_AXI2DVP_SWAP_ADDR, 0);
	}
    BL_WR_REG(DVPTSRCx, DVP_TSRC_AXI_AXI2DVP_BURST_CNT, Mem_Size_To_Burst_Cnt(frm_buf_size, AXI_XLEN_INCR16));
}

int ISP_DVP_TSrc_Enable(ISP_DVP_TSRC_SEL_E dvp_tsrc)
{
    dvp_tsrc_axi_reg_t *dvp_tsrc_reg = (dvp_tsrc_axi_reg_t*)DVPTSRC_BASE_ADDR_SET[dvp_tsrc];
    BL_LOGD("DVP_TSRC[%d] status: 0x%x\r\n", dvp_tsrc, dvp_tsrc_reg->axi2dvp_status.WORD);

    dvp_tsrc_reg->config.BF.cr_axi2dvp_en = is_data_from_axi[dvp_tsrc];

#if 0   /* intend to poll until fifo full before triggering send out */
    if (is_data_from_axi[dvp_tsrc]) {
        BL_LOGI("DVP_TSRC[%d] fifo_cnt %d\r\n", dvp_tsrc, dvp_tsrc_reg->axi2dvp_status.BF.st_axi2dvp_fifo_cnt);
        while (dvp_tsrc_reg->axi2dvp_status.BF.st_axi2dvp_fifo_cnt != 0x40);
    }
#endif

    dvp_tsrc_reg->config.BF.cr_enable = 1;

    BL_LOGD("DVP_TSRC[%d] enabled.\r\n", dvp_tsrc);

    return 0;
}

int ISP_DVP_TSrc_Disable(ISP_DVP_TSRC_SEL_E dvp_tsrc)
{
    dvp_tsrc_axi_reg_t *dvp_tsrc_reg = (dvp_tsrc_axi_reg_t*)DVPTSRC_BASE_ADDR_SET[dvp_tsrc];
    BL_LOGD("DVP_TSRC[%d] status: 0x%x\r\n", dvp_tsrc, dvp_tsrc_reg->axi2dvp_status.WORD);


    dvp_tsrc_reg->config.BF.cr_enable = 0;
    dvp_tsrc_reg->config.BF.cr_axi2dvp_en = 0;    /* clear FIFO */


    while (dvp_tsrc_reg->axi2dvp_status.BF.st_axi2dvp_fifo_cnt > 0 &&
        dvp_tsrc_reg->axi2dvp_status.BF.st_axi2dvp_state_idle == 0);

    /* toggle clear bit to clear drain error */
    dvp_tsrc_reg->axi2dvp_setting.BF.cr_axi2dvp_drain_err_clr = 1;
    dvp_tsrc_reg->axi2dvp_setting.BF.cr_axi2dvp_drain_err_clr = 0;

    BL_LOGD("DVP_TSRC[%d] disabled.\r\n", dvp_tsrc);

    return 0;
}

void ISP_DVP_TSrc_Check_Status(ISP_DVP_TSRC_SEL_E dvp_tsrc)
{
    dvp_tsrc_axi_reg_t *dvp_tsrc_reg = (dvp_tsrc_axi_reg_t*)DVPTSRC_BASE_ADDR_SET[dvp_tsrc];

    if (dvp_tsrc_reg->axi2dvp_status.BF.st_axi2dvp_drain_error) {
        BL_LOGE("DVP TSrc [%d] Drain Error!\r\n", dvp_tsrc);
		BL_ABORT();
        //ISP_DVP_TSrc_Disable(dvp_tsrc);
        //ISP_DVP_TSrc_Enable(dvp_tsrc);
    }
}

/****************************************************************************//**
 * @brief  Sensor input configuration
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  threshold: FIFO threshold for each DVP line to start to output
 * @param  hsyncInv:Enable or disable inverse signal of sensor hsync
 * @param  vsyncInv:Enable or disable inverse signal of sensor vsync
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Sensor_Input_Set(DVP_TSRC_ID_Type tsrcId,uint16_t threshold,BL_Fun_Type hsyncInv,BL_Fun_Type vsyncInv)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,DTSRC_CR_SNSR_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_SNSR_HSYNC_INV,hsyncInv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_SNSR_VSYNC_INV,vsyncInv);
    BL_WR_REG(dvpTsrcX,DTSRC_CONFIG,tmpVal);

    /* Set fifo threshold for each DVP line to start to output */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_SNSR2DVP_WAIT_POS);
    BL_WR_REG(dvpTsrcX,DTSRC_SNSR2DVP_WAIT_POS,BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_SNSR_FIFO_TH,threshold));
}

/****************************************************************************//**
 * @brief  DVP_TSRC enable
 *
 * @param  tsrcId: DVP_TSRC ID type
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Enable(DVP_TSRC_ID_Type tsrcId)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX,DTSRC_CONFIG,BL_SET_REG_BIT(tmpVal,DTSRC_CR_ENABLE));
}

/****************************************************************************//**
 * @brief  DVP_TSRC disable
 *
 * @param  tsrcId: DVP_TSRC ID type
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Disable(DVP_TSRC_ID_Type tsrcId)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX,DTSRC_CONFIG,BL_CLR_REG_BIT(tmpVal,DTSRC_CR_ENABLE));
}

/****************************************************************************//**
 * @brief  DVP_TSRC init
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  dvpTsrcCfg: DVP_TSRC configuration
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DVP_TSRC_Init(DVP_TSRC_ID_Type tsrcId,DVP_TSRC_Cfg_Type *dvpTsrcCfg)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));
    CHECK_PARAM(IS_DVP_TSRC_PIXEL_FORMAT_TYPE(dvpTsrcCfg->format));
    CHECK_PARAM(IS_DVP_TSRC_DVP2AXI_TYPE(dvpTsrcCfg->dvp2axi));
    CHECK_PARAM(IS_DVP_TSRC_SWAP_CONTROL_TYPE(dvpTsrcCfg->swapControl));
    CHECK_PARAM(IS_DVP_TSRC_BURST_TYPE(dvpTsrcCfg->burst));
    CHECK_PARAM(IS_DVP_TSRC_YUV420_LINE_TYPE(dvpTsrcCfg->lineType));

    /* Enable using AXI data */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DTSRC_CR_MODE_CEA_861);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_SWAP_MODE,dvpTsrcCfg->swapMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_SWAP_IDX_SWM,dvpTsrcCfg->swapControl);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_SWAP_IDX_SEL,dvpTsrcCfg->dvp2axi);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_DVP_DATA_MODE,dvpTsrcCfg->format);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_SNSR_EN,dvpTsrcCfg->dataFromSensor);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_SNSR_HSYNC_INV,dvpTsrcCfg->sensorHsyncInverse);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_SNSR_VSYNC_INV,dvpTsrcCfg->sensorVsyncInverse);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_B0_SEL,dvpTsrcCfg->byte0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_B1_SEL,dvpTsrcCfg->byte1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_B2_SEL,dvpTsrcCfg->byte2);
    tmpVal = BL_SET_REG_BIT(tmpVal,DTSRC_CR_AXI_EN);
    BL_WR_REG(dvpTsrcX,DTSRC_CONFIG,tmpVal);

    /* Set burst length */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_AXI2DVP_SETTING);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_420_MODE,dvpTsrcCfg->yuv420Enable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_420_UD_SEL,dvpTsrcCfg->lineType);
    BL_WR_REG(dvpTsrcX,DTSRC_AXI2DVP_SETTING,BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_XLEN,dvpTsrcCfg->burst));

    /* Set horizontal pixel count */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_FRAME_SIZE_H);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_TOTAL_H,dvpTsrcCfg->hTotalCnt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_BLANK_H,dvpTsrcCfg->hBlankCnt);
    BL_WR_REG(dvpTsrcX,DTSRC_FRAME_SIZE_H,tmpVal);

    /* Set vertical pixel count */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_FRAME_SIZE_V);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_TOTAL_V,dvpTsrcCfg->vTotalCnt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_BLANK_V,dvpTsrcCfg->vBlankCnt);
    BL_WR_REG(dvpTsrcX,DTSRC_FRAME_SIZE_V,tmpVal);

    /* Set vertical prefetch start position */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_AXI2DVP_PREFETCH);
    BL_WR_REG(dvpTsrcX,DTSRC_AXI2DVP_PREFETCH,BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_PREFETCH_V,dvpTsrcCfg->prefetch));

    /* Set fifo threshold for each DVP line to start to output */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_SNSR2DVP_WAIT_POS);
    BL_WR_REG(dvpTsrcX,DTSRC_SNSR2DVP_WAIT_POS,BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_SNSR_FIFO_TH,dvpTsrcCfg->fifoThreshold));

    /* Set axi2dvp start address, Y planar in YUV420 mode, frame 0 in swap mode */
    BL_WR_REG(dvpTsrcX,DTSRC_AXI2DVP_START_ADDR_BY,dvpTsrcCfg->memStartY0);

    /* Set axi2dvp memory size in burst */
    switch(dvpTsrcCfg->burst){
        case DVP_TSRC_BURST_TYPE_SINGLE:
            tmpVal = dvpTsrcCfg->memSizeY0/8;
            break;
        case DVP_TSRC_BURST_TYPE_INCR4:
            tmpVal = dvpTsrcCfg->memSizeY0/32;
            break;
        case DVP_TSRC_BURST_TYPE_INCR8:
            tmpVal = dvpTsrcCfg->memSizeY0/64;
            break;
        case DVP_TSRC_BURST_TYPE_INCR16:
            tmpVal = dvpTsrcCfg->memSizeY0/128;
            break;
        case DVP_TSRC_BURST_TYPE_INCR32:
            tmpVal = dvpTsrcCfg->memSizeY0/256;
            break;
        case DVP_TSRC_BURST_TYPE_INCR64:
            tmpVal = dvpTsrcCfg->memSizeY0/512;
            break;
        default:
            tmpVal = 0;
            break;
    }
    BL_WR_REG(dvpTsrcX,DTSRC_AXI2DVP_BURST_CNT,tmpVal);

    /* Set axi2dvp start address, Y planar in YUV420 mode, frame 1 in swap mode */
    BL_WR_REG(dvpTsrcX,DTSRC_AXI2DVP_SWAP_ADDR_BY,dvpTsrcCfg->memStartY1);

    /* Set axi2dvp start address, UV planar in YUV420 mode, frame 0 in swap mode */
    BL_WR_REG(dvpTsrcX,DTSRC_AXI2DVP_START_ADDR_UV,dvpTsrcCfg->memStartUV0);

    /* Set axi2dvp start address, UV planar in YUV420 mode, frame 1 in swap mode */
    BL_WR_REG(dvpTsrcX,DTSRC_AXI2DVP_SWAP_ADDR_UV,dvpTsrcCfg->memStartUV1);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  DVP_TSRC set swap index in software mode
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  index: Swap index used
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Set_Swap_Index(DVP_TSRC_ID_Type tsrcId,uint8_t index)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX,DTSRC_CONFIG,BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_AXI_SWAP_IDX_SWV,index));
}

/****************************************************************************//**
 * @brief  Use fake gradient data function init
 *
 * @param  tsrcId: DVP_TSRC ID type
 * @param  dataCfg: Fake gradient data configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DVP_TSRC_Fake_Data_Init(DVP_TSRC_ID_Type tsrcId,DVP_TSRC_Fake_Data_Cfg_Type* dataCfg)
{
    uint32_t tmpVal;
    uint32_t dvpTsrcX = dvpTsrcAddr[tsrcId];

    /* Check the parameters */
    CHECK_PARAM(IS_DVP_TSRC_ID_TYPE(tsrcId));

    /* Enable using fake gradient data */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_CONFIG);
    BL_WR_REG(dvpTsrcX,DTSRC_CONFIG,BL_CLR_REG_BIT(tmpVal,DTSRC_CR_AXI_EN));

    /* Set min and max value of fake gradient data */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_PIX_DATA_RANGE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_DATA_MIN,dataCfg->minData);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_DATA_MAX,dataCfg->maxData);
    BL_WR_REG(dvpTsrcX,DTSRC_PIX_DATA_RANGE,tmpVal);

    /* Set step value for eack line of fake gradient data */
    tmpVal = BL_RD_REG(dvpTsrcX,DTSRC_PIX_DATA_STEP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DTSRC_CR_DATA_STEP,dataCfg->step);
    BL_WR_REG(dvpTsrcX,DTSRC_PIX_DATA_STEP,tmpVal);
}
