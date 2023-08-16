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
#include <bl808_dvp2axi.h>
#include <dvp2axi_reg.h>

#undef  DEBUG_MODULE
#define DEBUG_MODULE 0

#define PERFORMANCE_MONITOR     0

#define DVP2AXIS_FSM_WAIT_CYCLES 0x40
#define DVP2AXI_BURST_LEN   (AXI_XLEN_INCR64)

#if PERFORMANCE_MONITOR
#define FRM_CNT_FOR_ONE_STATS     30       /* 2 sec */
static int port_intr_cnt = 0;
static TickType_t port_intr_start_time = 0;
#endif /* PERFORMANCE_MONITOR */

struct dvp2axi_shadow_settings_t {
    struct {
        uint32_t bitwiseFrmVld;
        uint32_t frmPeriodCnt;
        uint8_t  bHasData;
    } frame_skip_info;
};

void DVP2AXI_A_IRQHandler(void);
void DVP2AXI_B_IRQHandler(void);
void DVP2AXI_C_IRQHandler(void);
void DVP2AXI_D_IRQHandler(void);
void DVP2AXI_E_IRQHandler(void);
void DVP2AXI_F_IRQHandler(void);
void DVP2AXI_G_IRQHandler(void);
void DVP2AXI_H_IRQHandler(void);

static DVP2AXI_Callback_Cfg_Type *dvp2axiCallBack;
static void *dvp2axiUserData;

static const uint32_t DVP2AXI_BASE_ADDR_SET[] =
    {DVP2AXI_A_BASE, DVP2AXI_B_BASE, DVP2AXI_C_BASE, DVP2AXI_D_BASE,\
     DVP2AXI_E_BASE, DVP2AXI_F_BASE, DVP2AXI_G_BASE, DVP2AXI_H_BASE};

static const IRQn_Type DVP2AXI_ISR_NUM_SET[] =
    {DVP2AXI_A_IRQn, DVP2AXI_B_IRQn, DVP2AXI_C_IRQn, DVP2AXI_D_IRQn, \
     DVP2AXI_E_IRQn, DVP2AXI_F_IRQn, DVP2AXI_G_IRQn, DVP2AXI_H_IRQn};

static const IRQHandler_t DVP2AXI_ISR_SET[] =
    {DVP2AXI_A_IRQHandler, DVP2AXI_B_IRQHandler, DVP2AXI_C_IRQHandler, DVP2AXI_D_IRQHandler,\
     DVP2AXI_E_IRQHandler, DVP2AXI_F_IRQHandler, DVP2AXI_G_IRQHandler, DVP2AXI_H_IRQHandler};

static struct dvp2axi_shadow_settings_t dvp2axi_sw_shadow_settings[DVP2AXI_NUM];

static void DVP2AXI_IRQHandler(DVP2AXI_Port_Type port, DVP2AXI_Callback_Cfg_Type *callBack,
                                void *userData)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_DVP_STATUS_AND_ERROR);

    if (BL_IS_REG_BIT_SET(tmpVal, DVP2AXI_STS_NORMAL_INT)) {
        if (dvp2axi_sw_shadow_settings[port].frame_skip_info.bHasData != 0) {
            BL_WR_REG(DVP2AXIx, DVP2AXI_FRAME_VLD, dvp2axi_sw_shadow_settings[port].frame_skip_info.bitwiseFrmVld);
            BL_WR_REG(DVP2AXIx, DVP2AXI_FRAME_PERIOD, dvp2axi_sw_shadow_settings[port].frame_skip_info.frmPeriodCnt & 0x1F);
            dvp2axi_sw_shadow_settings[port].frame_skip_info.bHasData = 0;
        }
        if (NULL != callBack->DVP2AXI_CallBack_Data_Ready){
            callBack->DVP2AXI_CallBack_Data_Ready(port, userData);
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, DVP2AXI_STS_MEM_INT)) {
        if (NULL != callBack->DVP2AXI_CallBack_Mem_Ovwr){
            callBack->DVP2AXI_CallBack_Mem_Ovwr(port, userData);
        }
        BL_LOGD("DVP2AXI[%d] : memory overwrite!\r\n", port);
    }

    if (BL_IS_REG_BIT_SET(tmpVal, DVP2AXI_STS_FRAME_INT)) {
        if (NULL != callBack->DVP2AXI_CallBack_Frm_Ovwr){
            callBack->DVP2AXI_CallBack_Frm_Ovwr(port, userData);
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, DVP2AXI_STS_FIFO_INT)) {
        if (NULL != callBack->DVP2AXI_CallBack_Fifo_Ovfl){
            callBack->DVP2AXI_CallBack_Fifo_Ovfl(port, userData);
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, DVP2AXI_STS_HCNT_INT)) {
        if (NULL != callBack->DVP2AXI_CallBack_HCnt_Exm){
            callBack->DVP2AXI_CallBack_HCnt_Exm(port, userData);
        }
    }

    if (BL_IS_REG_BIT_SET(tmpVal, DVP2AXI_STS_VCNT_INT)) {
        if (NULL != callBack->DVP2AXI_CallBack_VCnt_Exm){
            callBack->DVP2AXI_CallBack_VCnt_Exm(port, userData);
        }
    }

    BL_LOGD("DVP2BUS[%d] vld cnt %d, addr 0x%x, size 0x%x\r\n", port,
        BL_GET_REG_BITS_VAL(tmpVal, DVP2AXI_FRAME_VALID_CNT),
        BL_RD_REG(DVP2AXIx, DVP2AXI_FRAME_START_ADDR0),
        BL_RD_REG(DVP2AXIx, DVP2AXI_FRAME_BCNT));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_DVP_FRAME_FIFO_POP);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_VCNT_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_HCNT_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_NORMAL_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_FRAME_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_MEM_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_FIFO_CLR);
    BL_WR_REG(DVP2AXIx, DVP2AXI_DVP_FRAME_FIFO_POP, tmpVal);

#if PRINT_FAST_CAP_TIMING
    //printf("DVP[%d] %d\r\n", port, xTaskGetTickCountFromISR());
#endif

#if PERFORMANCE_MONITOR
    do_frame_rate_stats("port intr", &port_intr_cnt, FRM_CNT_FOR_ONE_STATS, &port_intr_start_time);
#endif
}

void DVP2AXI_Init(DVP2AXI_Port_Type port)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_FRAM_VLD_POL, DVP2AXI_DATA_ACTIVE_HIGH);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_LINE_VLD_POL, DVP2AXI_DATA_ACTIVE_HIGH);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_XLEN, DVP2AXI_BURST_LEN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_DVP_MODE, DVP2AXI_DATA_VALID_V_AND_H);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_DVP_DATA_MODE, DVP2AXI_DATA_16_BIT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_V_SUBSAMPLE_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_V_SUBSAMPLE_POL);   /* even line masked */
    tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_HW_MODE_FWRAP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_DVP_WAIT_CYCLE, DVP2AXIS_FSM_WAIT_CYCLES);
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_DVP_STATUS_AND_ERROR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_FRAME_CNT_TRGR_INT, 1);    /* generate interrupt every frame */
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_NORMAL_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_MEM_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_FRAME_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_INT_HCNT_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_INT_VCNT_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_INT_FIFO_EN);
    BL_WR_REG(DVP2AXIx, DVP2AXI_DVP_STATUS_AND_ERROR, tmpVal);

    dvp2axi_sw_shadow_settings[port].frame_skip_info.bHasData = 0;

    Interrupt_Handler_Register(DVP2AXI_ISR_NUM_SET[port], DVP2AXI_ISR_SET[port]);
    System_NVIC_SetPriority(DVP2AXI_ISR_NUM_SET[port],7,1);
}

void DVP2AXI_Config(DVP2AXI_Port_Type port, ISP_DVP2AXI_CFG_S *cfg)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    if (DVP2AXI_DATA_8_BIT == cfg->bit_width) {
        if (DVP2AXI_SEL_HIGH_BYTE == cfg->byte_sel) {
            tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_DVP_DATA_BSEL);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_DVP_DATA_BSEL);
        }
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_DVP_DATA_MODE, cfg->bit_width);

    if (ENABLE == cfg->v_subsampl_enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_V_SUBSAMPLE_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_V_SUBSAMPLE_EN);
    }

    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);
}

void DVP2AXI_SetFrameValid(DVP2AXI_Port_Type port, ISP_DVP2AXI_DATA_POLARITY_E frm_vld)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_FRAM_VLD_POL, frm_vld);
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);
}

void DVP2AXI_Set_SW_Mode(DVP2AXI_Port_Type port, BL_Fun_Type enable)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_SW_MODE, enable);
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);
}

void DVP2AXI_SetFrameSize(DVP2AXI_Port_Type port, uint32_t frm_size)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    BL_WR_REG(DVP2AXIx, DVP2AXI_FRAME_BCNT, frm_size);
}

void DVP2AXI_MemConfig(DVP2AXI_Port_Type port, uint32_t bufAddr, uint32_t bufSize)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));
    /* check if buffer is aligned to 128 bytes boundary */
    CHECK_PARAM((bufAddr & AXI_BURST_INCR16_ALIGNMENT_MASK) == 0 );

    BL_WR_REG(DVP2AXIx, DVP2AXI_ADDR_START, bufAddr);
    BL_WR_REG(DVP2AXIx, DVP2AXI_MEM_BCNT, Mem_Size_To_Burst_Cnt(bufSize, DVP2AXI_BURST_LEN));
}

void DVP2AXI_Enable(DVP2AXI_Port_Type port)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));
    
    CPU_Interrupt_Enable(DVP2AXI_ISR_NUM_SET[port]);

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_DVP_ENABLE);
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);
}

void DVP2AXI_Disable(DVP2AXI_Port_Type port)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
	uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_DVP_ENABLE);
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);

    CPU_Interrupt_Disable(DVP2AXI_ISR_NUM_SET[port]);
}

BL_Sts_Type DVP2AXI_GetBusyStatus(DVP2AXI_Port_Type port)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_DVP_STATUS_AND_ERROR);

    return (BL_IS_REG_BIT_SET(tmpVal, DVP2AXI_ST_DVP_IDLE)) ? RESET : SET;
}

void DVP2AXI_SetFrameActive(DVP2AXI_Port_Type port, ISP_DVP2AXI_DATA_POLARITY_E frame_active)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    if (DVP2AXI_DATA_ACTIVE_HIGH == frame_active) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_FRAM_VLD_POL);
    } else if (DVP2AXI_DATA_ACTIVE_LOW == frame_active) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_FRAM_VLD_POL);
    }
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);
}

void DVP2AXI_SetLineActive(DVP2AXI_Port_Type port, ISP_DVP2AXI_DATA_POLARITY_E line_active)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    if (DVP2AXI_DATA_ACTIVE_HIGH == line_active) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_REG_LINE_VLD_POL);
    } else if (DVP2AXI_DATA_ACTIVE_LOW == line_active) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DVP2AXI_REG_LINE_VLD_POL);
    }
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);
}

void DVP2AXI_SetBitWidth(DVP2AXI_Port_Type port, ISP_DVP2AXI_DATA_MODE_E bitwidth)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_DVP_DATA_MODE, bitwidth);
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);
}

void DVP2AXI_Get_FrameBuffer(DVP2AXI_Port_Type port, uint32_t *frameAddr, uint32_t *byteCnt)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    *frameAddr = BL_RD_REG(DVP2AXIx, DVP2AXI_FRAME_START_ADDR0);

#if 1   /* TODO: workaround HW issue, first slot is not updated */
    *byteCnt = BL_RD_REG(DVP2AXIx, DVP2AXI_FRAME_BCNT);
#else
    *byteCnt = BL_RD_REG(DVP2AXIx, DVP2AXI_FRAME_BYTE_CNT0);
#endif
}

void DVP2AXI_Get_FrameFifoCount(DVP2AXI_Port_Type port, uint32_t *validFrameCnt)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_DVP_STATUS_AND_ERROR);
    *validFrameCnt = BL_GET_REG_BITS_VAL(tmpVal, DVP2AXI_FRAME_VALID_CNT);
}

void DVP2AXI_FrameFifoPop(DVP2AXI_Port_Type port)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_DVP_FRAME_FIFO_POP);
    tmpVal = BL_SET_REG_BIT(tmpVal, DVP2AXI_RFIFO_POP);
    BL_WR_REG(DVP2AXIx, DVP2AXI_DVP_FRAME_FIFO_POP, tmpVal);
}

void DVP2AXI_Set_Frame_Skip(DVP2AXI_Port_Type port, uint32_t bitwiseFrmVld, uint32_t frmPeriodCnt)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];

    if (DVP2AXI_GetBusyStatus(port)) {
        dvp2axi_sw_shadow_settings[port].frame_skip_info.bitwiseFrmVld = bitwiseFrmVld;
        dvp2axi_sw_shadow_settings[port].frame_skip_info.frmPeriodCnt = frmPeriodCnt;
        dvp2axi_sw_shadow_settings[port].frame_skip_info.bHasData = 1;
    } else {
        BL_WR_REG(DVP2AXIx, DVP2AXI_FRAME_VLD, bitwiseFrmVld);
        BL_WR_REG(DVP2AXIx, DVP2AXI_FRAME_PERIOD, frmPeriodCnt & 0x1F);
    }
}

void DVP2AXI_NoAlignBufferSync(DVP2AXI_Port_Type port)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_CONFIGUE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_HW_MODE_FWRAP, 0x0);
    BL_WR_REG(DVP2AXIx, DVP2AXI_CONFIGUE, tmpVal);
}

void DVP2AXI_Crop(DVP2AXI_Port_Type port, uint32_t h_start, int32_t h_end, uint32_t v_start, int32_t v_end)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_HSYNC_CROP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_HSYNC_ACT_START, h_start);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_HSYNC_ACT_END, h_end);
    BL_WR_REG(DVP2AXIx, DVP2AXI_HSYNC_CROP, tmpVal);

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_VSYNC_CROP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_VSYNC_ACT_START, v_start);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_VSYNC_ACT_END, v_end);
    BL_WR_REG(DVP2AXIx, DVP2AXI_VSYNC_CROP, tmpVal);
}

void DVP2AXI_Valid_Cnt_Exm(DVP2AXI_Port_Type port, uint32_t hcnt, uint32_t vcnt)
{
    uint32_t DVP2AXIx = DVP2AXI_BASE_ADDR_SET[port];
    uint32_t tmpVal;

    CHECK_PARAM(IS_DVP2AXI_ID_TYPE(port));

    tmpVal = BL_RD_REG(DVP2AXIx, DVP2AXI_FRAM_EXM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_TOTAL_HCNT, hcnt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DVP2AXI_REG_TOTAL_VCNT, vcnt);
    BL_WR_REG(DVP2AXIx, DVP2AXI_FRAM_EXM, tmpVal);
}

#if 0
void ISP_DVP2AXI_Check_Status(DVP2AXI_Port_Type port)
{
    dvp2axi_reg_t *dvp2axi_reg = (dvp2axi_reg_t*)DVP2AXI_BASE_ADDR_SET[port];

    BL_LOGD("DVP2AXI[%d] final:\r\n\t dvp_fifo_idle %d, axi_idle %d, dvp_flsh %d, dvp_wait %d, dvp_func %d, bus_idle %d\r\n",
        port, dvp2axi_reg->dvp_status_and_error.BF.st_dvp_idle, dvp2axi_reg->dvp_status_and_error.BF.axi_idle,
        dvp2axi_reg->dvp_status_and_error.BF.st_bus_flsh, dvp2axi_reg->dvp_status_and_error.BF.st_bus_wait,
        dvp2axi_reg->dvp_status_and_error.BF.st_bus_func, dvp2axi_reg->dvp_status_and_error.BF.st_bus_idle);
}
#endif

void DVP2AXI_InstallCallback(        DVP2AXI_Callback_Cfg_Type *callBack, void *userData)
{
    /* Save the callback in global variables  */
    dvp2axiCallBack = callBack;
    dvp2axiUserData = userData;
}

void DVP2AXI_A_IRQHandler(void)
{
    DVP2AXI_IRQHandler(DVP2AXI_A, dvp2axiCallBack, dvp2axiUserData);
}

void DVP2AXI_B_IRQHandler(void)
{
    DVP2AXI_IRQHandler(DVP2AXI_B, dvp2axiCallBack, dvp2axiUserData);
}

void DVP2AXI_C_IRQHandler(void)
{
    DVP2AXI_IRQHandler(DVP2AXI_C, dvp2axiCallBack, dvp2axiUserData);
}

void DVP2AXI_D_IRQHandler(void)
{
    DVP2AXI_IRQHandler(DVP2AXI_D, dvp2axiCallBack, dvp2axiUserData);
}

void DVP2AXI_E_IRQHandler(void)
{
    DVP2AXI_IRQHandler(DVP2AXI_E, dvp2axiCallBack, dvp2axiUserData);
}

void DVP2AXI_F_IRQHandler(void)
{
    DVP2AXI_IRQHandler(DVP2AXI_F, dvp2axiCallBack, dvp2axiUserData);
}

void DVP2AXI_G_IRQHandler(void)
{
    DVP2AXI_IRQHandler(DVP2AXI_G, dvp2axiCallBack, dvp2axiUserData);
}

void DVP2AXI_H_IRQHandler(void)
{
    DVP2AXI_IRQHandler(DVP2AXI_H, dvp2axiCallBack, dvp2axiUserData);
}

