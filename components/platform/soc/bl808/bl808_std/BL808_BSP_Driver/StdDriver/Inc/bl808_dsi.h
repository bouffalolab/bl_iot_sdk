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
#ifndef __BL808_DSI_H__
#define __BL808_DSI_H__

#include "dsi_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSI
 *  @{
 */

/** @defgroup  DSI_Public_Types
 *  @{
 */

/**
 *  @brief DSI port type definition
 */
typedef enum {
    DSI0_ID,                                 /*!< DSI0 port define */
    DSI_ID_MAX,                              /*!< DSI max ID define */
}DSI_ID_Type;

/**
 *  @brief DSI interrupt type definition
 */
typedef enum {   
    DSI_INT_DATA_OVERRUN_ERR=0x01,                /*!< DSI data overrun error interrupt */
    DSI_INT_DATA_DISCONT_ERR=0x02,                /*!< DSI data dis-continous error interrupt */
    DSI_INT_DATA_LEN_ERR=0x04,                    /*!< DSI data length error interrupt */
    DSI_INT_ALL=0x07,                             /*!< All interrupt */
    DSI_INT_COUNT=0x03,                           /*!< Interrupt count */
}DSI_INT_Type;

/**
 *  @brief DSI interrupt type definition
 */
typedef enum {   
    DSI_LANE_DATA0=0x01,                    /*!< Data0 */
    DSI_LANE_DATA1=0x02,                    /*!< Data1 */
    DSI_LANE_DATA2=0x04,                    /*!< Data2 */
    DSI_LANE_DATA3=0x08,                    /*!< Data3 */
    DSI_LANE_CLOCK=0x010,                   /*!< Clcok */
}DSI_Lane_Type;

/**
 *  @brief DSI interrupt type definition
 */
typedef enum {   
    DSI_LANE_STAT_NORMAL=0x00,                /*!< Status normal */
    DSI_LANE_STAT_ULP=0x01,                   /*!< Status low power */
    DSI_LANE_STAT_STOP=0x02,                  /*!< Status stop */
}DSI_Lane_State_Type;

/**
 *  @brief DSI interrupt type definition
 */
typedef enum {
    DSI_CLOCK_LANE_OPT_ULP_ENTER=0x01,             /*!< low power enter */
    DSI_CLOCK_LANE_OPT_ULP_EXIT=0x02,              /*!< low power exit */
    DSI_CLOCK_LANE_OPT_HS_REQ=0x04,                /*!< hs request */
}DSI_Clock_Lane_Opt_Type;

/**
 *  @brief DSI data type definition
 */
typedef enum {
    DSI_DATA_TYPE_565,                /*!< DSI data length error interrupt */
    DSI_DATA_TYPE_888,                /*!< DSI data dis-continous error interrupt */
}DSI_Data_Type;

/**
 *  @brief DSI configuration strcut definition
 */
typedef struct {
    uint8_t virtualChans;            /*!< DSI virtual channels */
    uint8_t lsePktEn;               /*!< DSI LS/LE packet enable */
    uint8_t laneNum;                 /*!< DSI lane numbers */
    DSI_Data_Type dataType;          /*!< DSI data type */
}DSI_CFG_Type;

/*@} end of group DSI_Public_Types */

/** @defgroup  DSI_Public_Constants
 *  @{
 */

/** @defgroup  DSI_ID_TYPE
 *  @{
 */
#define IS_DSI_ID_TYPE(type)                             (((type) == DSI0_ID) || \
                                                          ((type) == DSI_ID_MAX))

/*@} end of group DSI_Public_Constants */

/** @defgroup  DSI_Public_Macros
 *  @{
 */

/*@} end of group DSI_Public_Macros */

/** @defgroup  DSI_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void DSI0_IRQHandler(void);
#endif
void DSI_Init(DSI_ID_Type disId,DSI_CFG_Type *cfg);
void DSI_Deinit(DSI_ID_Type disId);
void DSI_Enable(DSI_ID_Type disId);
void DSI_Disable(DSI_ID_Type disId);
void DSI_IntMask(DSI_ID_Type dsiId,DSI_INT_Type intType, BL_Mask_Type intMask);
void DSI_IntClear(DSI_ID_Type dsiId,DSI_INT_Type intType);
void DSI_IntEnable(DSI_ID_Type dsiId,DSI_INT_Type intType);
DSI_INT_Type DSI_IntGet(DSI_ID_Type dsiId);
void DSI_Set_Frame_Num(DSI_ID_Type dsiId,uint32_t num);
void DSI_PHY_Reset(DSI_ID_Type dsiId);
void DSI_PHY_Reinit_Data_Lanes(DSI_ID_Type dsiId,DSI_Lane_Type lanes);
void DSI_PHY_Enable_Lanes(DSI_ID_Type dsiId,DSI_Lane_Type lanes);
void DSI_PHY_Disable_Lanes(DSI_ID_Type dsiId,DSI_Lane_Type lanes);
void DSI_PHY_Stop_Data_Lanes(DSI_ID_Type dsiId,DSI_Lane_Type lanes);
void DSI_PHY_Get_Lanes_State(DSI_ID_Type dsiId,DSI_Lane_Type lane,DSI_Lane_State_Type *state);
void DSI_PHY_Set_Clock_Lane(DSI_ID_Type dsiId,DSI_Clock_Lane_Opt_Type opt);

/*@} end of group DSI_Public_Functions */

/*@} end of group DSI */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DSI_H__ */
