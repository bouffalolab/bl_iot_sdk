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
#ifndef __BL808_DVP2AXI_H__
#define __BL808_DVP2AXI_H__

#include <bl808_common.h>
#include <bl808_comm_mm.h>



typedef enum {
    DVP2AXI_A = 0,
    DVP2AXI_B = 1,
    DVP2AXI_C = 2,
    DVP2AXI_D = 3,
    DVP2AXI_E = 4,
    DVP2AXI_F = 5,
    DVP2AXI_G = 6,
    DVP2AXI_H = 7,
    DVP2AXI_NUM ,
} DVP2AXI_Port_Type;

typedef enum {
    DVP2AXI_DATA_ACTIVE_LOW = 0,
    DVP2AXI_DATA_ACTIVE_HIGH = 1,
} ISP_DVP2AXI_DATA_POLARITY_E;

typedef enum {
    DVP2AXI_DATA_VALID_V_AND_H = 0,
    DVP2AXI_DATA_VALID_V_OR_H = 1,
    DVP2AXI_DATA_VALID_V = 2,
    DVP2AXI_DATA_VALID_H = 3,
} ISP_DVP2AXI_DATA_VALID_E;

typedef enum {
    DVP2AXI_DATA_16_BIT = 0,
    DVP2AXI_DATA_24_BIT = 1,
    DVP2AXI_DATA_24_COMP_16BIT = 2,
    DVP2AXI_DATA_24_EXP_32BIT = 3,
    DVP2AXI_DATA_8_BIT = 4,
} ISP_DVP2AXI_DATA_MODE_E;

typedef enum {
    DVP2AXI_SEL_LOW_BYTE = 0,
    DVP2AXI_SEL_HIGH_BYTE = 1,
} ISP_DVP2AXI_BYTE_SEL_E;

typedef enum {
    DVP2AXI_ODD_LINE_MASKED = 0,
    DVP2AXI_EVEN_LINE_MASKED = 1,
} ISP_DVP2AXI_LINE_MASK_E;

typedef struct blISP_DVP2AXI_CFG_S {
	ISP_DVP2AXI_DATA_MODE_E bit_width;
    ISP_DVP2AXI_BYTE_SEL_E byte_sel;
    BL_Fun_Type v_subsampl_enable;
} ISP_DVP2AXI_CFG_S;


typedef struct {
    void (*DVP2AXI_CallBack_Data_Ready)(DVP2AXI_Port_Type port, void *userData);
    void (*DVP2AXI_CallBack_Mem_Ovwr)(DVP2AXI_Port_Type port, void *userData);
    void (*DVP2AXI_CallBack_Frm_Ovwr)(DVP2AXI_Port_Type port, void *userData);
    void (*DVP2AXI_CallBack_Fifo_Ovfl)(DVP2AXI_Port_Type port, void *userData);
    void (*DVP2AXI_CallBack_VCnt_Exm)(DVP2AXI_Port_Type port, void *userData);
    void (*DVP2AXI_CallBack_HCnt_Exm)(DVP2AXI_Port_Type port, void *userData);
} DVP2AXI_Callback_Cfg_Type;


#define IS_DVP2AXI_ID_TYPE(type)                          (((type) == DVP2AXI_A) || \
                                                          ((type)  == DVP2AXI_B) || \
                                                          ((type)  == DVP2AXI_C) || \
                                                          ((type)  == DVP2AXI_D) || \
                                                          ((type)  == DVP2AXI_E) || \
                                                          ((type)  == DVP2AXI_F) || \
                                                          ((type)  == DVP2AXI_G) || \
                                                          ((type)  == DVP2AXI_H))


void DVP2AXI_Init(DVP2AXI_Port_Type port);
void DVP2AXI_Config(DVP2AXI_Port_Type port, ISP_DVP2AXI_CFG_S* BL_ISP_SetDVP2AXI_Cfg);
void DVP2AXI_InstallCallback(        DVP2AXI_Callback_Cfg_Type *callBack, void *userData);

void DVP2AXI_SetFrameValid(DVP2AXI_Port_Type port, ISP_DVP2AXI_DATA_POLARITY_E frm_vld);
void DVP2AXI_Set_SW_Mode(DVP2AXI_Port_Type port, BL_Fun_Type enable);
void DVP2AXI_SetFrameSize(DVP2AXI_Port_Type port, uint32_t frm_size);
void DVP2AXI_MemConfig(DVP2AXI_Port_Type port, uint32_t bufAddr, uint32_t bufSize);
void DVP2AXI_Enable(DVP2AXI_Port_Type port);
void DVP2AXI_Disable(DVP2AXI_Port_Type port);
BL_Sts_Type DVP2AXI_GetBusyStatus(DVP2AXI_Port_Type port);
void DVP2AXI_SetFrameActive(DVP2AXI_Port_Type port, ISP_DVP2AXI_DATA_POLARITY_E frame_active);
void DVP2AXI_SetLineActive(DVP2AXI_Port_Type port, ISP_DVP2AXI_DATA_POLARITY_E line_active);
void DVP2AXI_SetBitWidth(DVP2AXI_Port_Type port, ISP_DVP2AXI_DATA_MODE_E bitwidth);
void DVP2AXI_Get_FrameBuffer(DVP2AXI_Port_Type port, uint32_t *frameAddr, uint32_t *byteCnt);
void DVP2AXI_Get_FrameFifoCount(DVP2AXI_Port_Type port, uint32_t *validFrameCnt);
void DVP2AXI_FrameFifoPop(DVP2AXI_Port_Type port);
void ISP_DVP2AXI_Check_Status(DVP2AXI_Port_Type port);

void DVP2AXI_Crop(DVP2AXI_Port_Type port, uint32_t h_start, int32_t h_end, uint32_t v_start, int32_t v_end);
void DVP2AXI_Set_Frame_Skip(DVP2AXI_Port_Type port, uint32_t bitwiseFrmVld, uint32_t frmPeriodCnt);
void DVP2AXI_NoAlignBufferSync(DVP2AXI_Port_Type port);
void DVP2AXI_Valid_Cnt_Exm(DVP2AXI_Port_Type port, uint32_t hcnt, uint32_t vcnt);


#endif /* __BL808_DVP2AXI_H__ */
