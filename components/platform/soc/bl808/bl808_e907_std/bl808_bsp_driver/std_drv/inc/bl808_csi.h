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
#ifndef __BL808_CSI_H__
#define __BL808_CSI_H__

#include "csi_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CSI
 *  @{
 */

/** @defgroup  CSI_Public_Types
 *  @{
 */

/**
 *  @brief CSI port type definition
 */
typedef enum {
    CSI0_ID = 0, /*!< CSI0 port define */
    CSI_ID_MAX,  /*!< CSI max ID define */
} CSI_ID_Type;

/**
 *  @brief CSI lane number type definition
 */
typedef enum {
    CSI_LANE_NUMBER_1, /*!< 1-lane RX */
    CSI_LANE_NUMBER_2, /*!< 2-lane RX */
} CSI_Lane_Number_Type;

/**
 *  @brief CSI interrupt type definition
 */
typedef enum {
    CSI_INT_GENERIC_PACKET = 0x01,      /*!< CSI generic packet interrupt */
    CSI_INT_LANE_MERGE_ERR = 0x02,      /*!< CSI lane merging error interrupt */
    CSI_INT_ECC_ERR = 0x04,             /*!< CSI ECC error interrupt */
    CSI_INT_CRC_ERR = 0x08,             /*!< CSI CRC error interrupt */
    CSI_INT_PHY_HS_SOT_ERR = 0x10,      /*!< CSI PHY HS SoT error interrupt */
    CSI_INT_PHY_HS_SOT_SYNC_ERR = 0x20, /*!< CSI PHY HS SoT sync error interrupt */
    CSI_INT_ALL = 0x3F,                 /*!< CSI all interrupt */
    CSI_INT_COUNT = 0x06,               /*!< CSI interrupt count */
} CSI_INT_Type;

/**
 *  @brief CSI configuration struct definition
 */
typedef struct
{
    uint8_t dvp0VirtualChan;       /*!< Virtual channel number for dvp port 0 */
    CSI_Lane_Number_Type laneNum;  /*!< CSI lane number */
    BL_Fun_Type dataUnpackEn;      /*!< 0: disable data-unpack function, dvp output is 8-bit valid(byte-in-byte-out) 
                                        1: enable data-unpack function, dvp output format depends on packet data type(RAW 8/10/12/14) */
    BL_Fun_Type syncShortPacketEn; /*!< Enable or disable sync short packets(FS/FE/LS/LE) to be received into generic packet buffer */
    BL_Fun_Type dataBitInverseEn;  /*!< Enable or disable PPI I/F data byte bit inverse, which should be set to little-endian */
    BL_Fun_Type laneInverseEn;     /*!< Enable or disable lane0 and lane1 inverse */
} CSI_CFG_Type;

/*@} end of group CSI_Public_Types */

/** @defgroup  CSI_Public_Constants
 *  @{
 */

/** @defgroup  CSI_ID_TYPE
 *  @{
 */
#define IS_CSI_ID_TYPE(type) (((type) == CSI0_ID) || \
                              ((type) == CSI_ID_MAX))

/** @defgroup  CSI_LANE_NUMBER_TYPE
 *  @{
 */
#define IS_CSI_LANE_NUMBER_TYPE(type) (((type) == CSI_LANE_NUMBER_1) || \
                                       ((type) == CSI_LANE_NUMBER_2))

/** @defgroup  CSI_INT_TYPE
 *  @{
 */
#define IS_CSI_INT_TYPE(type) (((type) == CSI_INT_GENERIC_PACKET) || \
                               ((type) == CSI_INT_LANE_MERGE_ERR) || \
                               ((type) == CSI_INT_ECC_ERR) || \
                               ((type) == CSI_INT_CRC_ERR) || \
                               ((type) == CSI_INT_PHY_HS_SOT_ERR) || \
                               ((type) == CSI_INT_PHY_HS_SOT_SYNC_ERR) || \
                               ((type) == CSI_INT_ALL) || \
                               ((type) == CSI_INT_COUNT))

/*@} end of group CSI_Public_Constants */

/** @defgroup  CSI_Public_Macros
 *  @{
 */

/*@} end of group CSI_Public_Macros */

/** @defgroup  CSI_Public_Functions
 *  @{
 */

/**
 *  @brief CSI Functions
 */
#ifndef BFLB_USE_HAL_DRIVER
void CSI_IRQHandler(void);
#endif
void CSI_Init(CSI_ID_Type csiId, CSI_CFG_Type *cfg);
void CSI_Deinit(CSI_ID_Type csiId);
void CSI_Enable(CSI_ID_Type csiId);
void CSI_Disable(CSI_ID_Type csiId);
void CSI_IntMask(CSI_ID_Type csiId, CSI_INT_Type intType, BL_Mask_Type intMask);
void CSI_IntClear(CSI_ID_Type csiId, CSI_INT_Type intType);
void CSI_Int_Callback_Install(CSI_ID_Type csiId, CSI_INT_Type intType, intCallback_Type *cbFun);
void CSI_PHY_Reset(CSI_ID_Type csiId);
void CSI_PHY_Config(CSI_ID_Type csiId, uint32_t txClkEsc, uint32_t dataRate);
void CSI_PHY_Enable_Lanes(CSI_ID_Type csiId, CSI_Lane_Number_Type lanes);
void CSI_PHY_Disable_Lanes(CSI_ID_Type csiId);

/*@} end of group CSI_Public_Functions */

/*@} end of group CSI */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_CSI_H__ */
