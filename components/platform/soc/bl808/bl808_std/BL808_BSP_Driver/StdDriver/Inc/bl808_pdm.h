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
#ifndef __BL808_PDM_H__
#define __BL808_PDM_H__

#include "pdm_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL60x_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PDM
 *  @{
 */

/** @defgroup  PDM_Public_Types
 *  @{
 */

/**
 *  @brief PDM FS type definition
 */
typedef enum {
    PDM_FS_64,                              /*!< PDM FS 64 */
    PDM_FS_128,                             /*!< PDM FS 128 */
}PDM_FS_Type;

/**
 *  @brief PDM Channel config type definition
 */
typedef enum {
    PDM_CHAN_LEFT,                          /*!< PDM left channel only */
    PDM_CHAN_RIGHT,                         /*!< PDM right channel only */
    PDM_CHAN_LEFT_RIGHT,                    /*!< PDM left and right channel */
}PDM_Chan_Type;

/**
 *  @brief PDM data format type definition
 */
typedef enum {
    PDM_DATA_FORMAT_STEREO = 0,             /*!< 32 bits stereo,{L0}, {R0}, {L1}, {R1}, {L2}, {R2}...(2CH) */
    PDM_DATA_FORMAT_LEFT,                   /*!< 32 bits left channel,{L0}, {L1}, {L2}, {L3}... (1CH) */
    PDM_DATA_FORMAT_LEFT_MERGE,             /*!< 16 bit merge left channel,{L1,L0}, {L3,L2}, {L5,L4}...(1CH) */
    PDM_DATA_FORMAT_STEREO_MERGE,           /*!< 16 bits merge stereo{R0,L0}, {R1,L1}, {R2,L2}...(2CH) */
    PDM_DATA_FORMAT_DSD_MERGE,              /*!< DSD merge format,{R1,L1,R0,L0}, {R3,L3,R2,L2}...(DSD format) */
    PDM_DATA_FORMAT_DSF_MERGE,              /*!< DSF merge format,{L3,L2,L1,L0}, {L7,L6,L5,L4}...(DSF format){R3,R2,R1,R0}, 
                                                 {R7,R6,R5,R4}...(second DMA) */
}PDM_Data_Format_Type;

/**
 *  @brief PDM configuration type definition
 */
typedef struct {
    PDM_FS_Type rxFs;                       /*!< PDM rx FS type */
    PDM_FS_Type txFs;                       /*!< PDM tx FS type */
    PDM_Chan_Type chanType;                 /*!< PDM channel type */
    BL_Fun_Type dsdSwap;                    /*!< Swap DSD high and low 16 bits data */
    BL_Fun_Type outClkInv;                  /*!< Output clock invert */
    uint8_t outClkDly;                      /*!< Output clock delay count */
    uint8_t outDataDly;                     /*!< Output data delay count */
}PDM_CFG_Type;

/**
 *  @brief PDM FIFO configuration type definition
 */
typedef struct {
    uint16_t txDataRShift;                  /*!< PDM tx data right shift */
    PDM_Data_Format_Type txFmt;             /*!< PDM tx data format */
    BL_Fun_Type txDMAEn;                    /*!< Enable tx DMA function */
    PDM_Data_Format_Type rxFmt;             /*!< PDM rx data format */
    BL_Fun_Type rxDMAEn;                    /*!< Enable rx DMA function */
}PDM_FIFO_CFG_Type;

/*@} end of group PDM_Public_Types */

/** @defgroup  PDM_Public_Constants
 *  @{
 */

/** @defgroup  PDM_FS_TYPE
 *  @{
 */
#define IS_PDM_FS_TYPE(type)                             (((type) == PDM_FS_64) || \
                                                          ((type) == PDM_FS_128))

/** @defgroup  PDM_CHAN_TYPE
 *  @{
 */
#define IS_PDM_CHAN_TYPE(type)                           (((type) == PDM_CHAN_LEFT) || \
                                                          ((type) == PDM_CHAN_RIGHT) || \
                                                          ((type) == PDM_CHAN_LEFT_RIGHT))

/** @defgroup  PDM_DATA_FORMAT_TYPE
 *  @{
 */
#define IS_PDM_DATA_FORMAT_TYPE(type)                    (((type) == PDM_DATA_FORMAT_STEREO ) || \
                                                          ((type) == PDM_DATA_FORMAT_LEFT) || \
                                                          ((type) == PDM_DATA_FORMAT_LEFT_MERGE) || \
                                                          ((type) == PDM_DATA_FORMAT_STEREO_MERGE) || \
                                                          ((type) == PDM_DATA_FORMAT_DSD_MERGE) || \
                                                          ((type) == PDM_DATA_FORMAT_DSF_MERGE))

/*@} end of group PDM_Public_Constants */

/** @defgroup  PDM_Public_Macros
 *  @{
 */

/*@} end of group PDM_Public_Macros */

/** @defgroup  PDM_Public_Functions
 *  @{
 */
void PDM_Init(PDM_CFG_Type *cfg);
void PDM_FIFO_Init(PDM_FIFO_CFG_Type *cfg);
void PDM_Enable(void);
void PDM_Disable(void);
uint32_t PDM_Read(void);
void PDM_Write1(uint32_t data);
void PDM_Write2(uint32_t data);

/*@} end of group PDM_Public_Functions */

/*@} end of group PDM */

/*@} end of group BL60x_Peripheral_Driver */

#endif /* __BL808_PDM_H__ */
