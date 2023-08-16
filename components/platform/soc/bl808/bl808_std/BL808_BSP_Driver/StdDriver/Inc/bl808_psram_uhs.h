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
#ifndef __BL808_PSRAM_UHS_H__
#define __BL808_PSRAM_UHS_H__

#include "psram_uhs_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PSRAM_UHS
 *  @{
 */

/** @defgroup  PSRAM_UHS_Public_Types
 *  @{
 */

/**
 *  @brief Psram UHS Size
 */
typedef enum {
    PSRAM_MEM_SIZE_4MB=0x03,                 /*!< PSRAM Memory Size 4M */
    PSRAM_MEM_SIZE_8MB=0x07,                 /*!< PSRAM Memory Size 8M */
    PSRAM_MEM_SIZE_16MB=0x0f,                /*!< PSRAM Memory Size 16M */
    PSRAM_MEM_SIZE_32MB=0x1f,                /*!< PSRAM Memory Size 32M */
}PSRAM_UHS_Mem_Size_Type;

/**
 *  @brief Psram UHS Page Type
 */
typedef enum {
    PSRAM_PAGE_SIZE_2KB=0x0B,                /*!< PSRAM Page Size 2KB */
    PSRAM_PAGE_SIZE_4KB=0x16,                /*!< PSRAM Page Size 4KB */
}PSRAM_UHS_Page_Size_Type;

/**
 *  @brief Psram UHS Burst Size
 */
typedef enum {
    PSRAM_UHS_Warp_Burst_64,                 /*!< PSRAM Warp Burst Size 64 */
    PSRAM_UHS_Warp_Burst_32,                 /*!< PSRAM Warp Burst Size 32 */
    PSRAM_UHS_Warp_Burst_16,                 /*!< PSRAM Warp Burst Size 16 */
}PSRAM_UHS_Warp_Burst_Type;

/**
 *  @brief Psram UHS Driver Strength
 */
typedef enum {
    PSRAM_UHS_Driver_ST_34P3_PUPU,           /*!< 34.3Ω PD/PU */
    PSRAM_UHS_Driver_ST_40_PUPU,             /*!< 40Ω PD/PU */
    PSRAM_UHS_Driver_ST_48_PUPU,             /*!< 48Ω PD/PU */
    PSRAM_UHS_Driver_ST_60_PUPU,             /*!< 60Ω PD/PU */
    PSRAM_UHS_Driver_ST_80_PUPU,             /*!< 80Ω PD/PU */
    PSRAM_UHS_Driver_ST_34P3_PD_40_PU,       /*!< 34.3Ω PD & 40Ω PU */
    PSRAM_UHS_Driver_ST_40_PD_48_PU,         /*!< 40Ω PD & 48Ω PU */
    PSRAM_UHS_Driver_ST_34P3_PD_48_PU,       /*!< 34.3Ω PD & 48Ω PU */
}PSRAM_UHS_Driver_ST_Type;

/**
 *  @brief Psram UHS Latency
 */
typedef enum {
    PSRAM_UHS_Latency_W10_R20_Max_Fre_533_MHZ,    /*!< Max freq. = 533 MHz / Write latency=10 / Read latency=20 */
    PSRAM_UHS_Latency_W14_R29_Max_Fre_800_MHZ,    /*!< Max freq. = 800 MHz / Write latency=14 / Read latency=29 */
    PSRAM_UHS_Latency_W16_R33_Max_Fre_933_MHZ,    /*!< Max freq. = 933 MHz / Write latency=16 / Read latency=33 */
    PSRAM_UHS_Latency_W18_R37_Max_Fre_1066_MHZ,    /*!< Max freq. = 1066 MHz / Write latency=18 / Read latency=37 */
    PSRAM_UHS_Latency_W6_R16_Max_Fre_400_MHZ,    /*!< Max freq. = 400 MHz / Write latency=6 / Read latency=16 */
    PSRAM_UHS_Latency_W5_R13_Max_Fre_333_MHZ,    /*!< Max freq. = 333 MHz / Write latency=5 / Read latency=13 */
    PSRAM_UHS_Latency_W5_R9_Max_Fre_200_MHZ, /*!< Max freq. = 200 MHz / Write latency=5 / Read latency=9 */
}PSRAM_UHS_Latency_Type;

/**
 *  @brief PSRAM_UHS_Cfg_Type
 */
typedef struct {
    uint32_t pck_freq;                       /*!< pck frequency unit is MHZ */
    PSRAM_UHS_Mem_Size_Type psramMemSize;    /*!< psram uhm memory size */
    PSRAM_UHS_Page_Size_Type psramPageSize;  /*!< psram uhm page size */
    uint8_t  isHighTem;                      /*!< auto refresh work temperature */
}PSRAM_UHS_Cfg_Type;

/**
 *  @brief PSRAM_UHS_Write_Reg_Cfg_Type
 */
typedef struct {
    PSRAM_UHS_Driver_ST_Type driver_st;      /*!< driver strength */
    PSRAM_UHS_Warp_Burst_Type burst_size;    /*!< burst size */
    PSRAM_UHS_Latency_Type lentency;         /*!< lentency */
}PSRAM_UHS_Write_Reg_Cfg_Type;

/*@} end of group PSRAM_UHS_Public_Types */

/** @defgroup  PSRAM_UHS_Public_Constants
 *  @{
 */

/** @defgroup  PSRAM_UHS_MEM_SIZE_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_MEM_SIZE_TYPE(type)                 (((type) == PSRAM_MEM_SIZE_4MB) || \
                                                          ((type) == PSRAM_MEM_SIZE_8MB) || \
                                                          ((type) == PSRAM_MEM_SIZE_16MB) || \
                                                          ((type) == PSRAM_MEM_SIZE_32MB))

/** @defgroup  PSRAM_UHS_PAGE_SIZE_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_PAGE_SIZE_TYPE(type)                (((type) == PSRAM_PAGE_SIZE_2KB) || \
                                                          ((type) == PSRAM_PAGE_SIZE_4KB))

/** @defgroup  PSRAM_UHS_WARP_BURST_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_WARP_BURST_TYPE(type)               (((type) == PSRAM_UHS_Warp_Burst_64) || \
                                                          ((type) == PSRAM_UHS_Warp_Burst_32) || \
                                                          ((type) == PSRAM_UHS_Warp_Burst_16))

/** @defgroup  PSRAM_UHS_DRIVER_ST_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_DRIVER_ST_TYPE(type)                (((type) == PSRAM_UHS_Driver_ST_34P3_PUPU) || \
                                                          ((type) == PSRAM_UHS_Driver_ST_40_PUPU) || \
                                                          ((type) == PSRAM_UHS_Driver_ST_48_PUPU) || \
                                                          ((type) == PSRAM_UHS_Driver_ST_60_PUPU) || \
                                                          ((type) == PSRAM_UHS_Driver_ST_80_PUPU) || \
                                                          ((type) == PSRAM_UHS_Driver_ST_34P3_PD_40_PU) || \
                                                          ((type) == PSRAM_UHS_Driver_ST_40_PD_48_PU) || \
                                                          ((type) == PSRAM_UHS_Driver_ST_34P3_PD_48_PU))

/** @defgroup  PSRAM_UHS_LATENCY_TYPE
 *  @{
 */
#define IS_PSRAM_UHS_LATENCY_TYPE(type)                  (((type) == PSRAM_UHS_Latency_W10_R20_Max_Fre_533_MHZ) || \
                                                          ((type) == PSRAM_UHS_Latency_W14_R29_Max_Fre_800_MHZ) || \
                                                          ((type) == PSRAM_UHS_Latency_W16_R33_Max_Fre_933_MHZ) || \
                                                          ((type) == PSRAM_UHS_Latency_W18_R37_Max_Fre_1066_MHZ) || \
                                                          ((type) == PSRAM_UHS_Latency_W6_R16_Max_Fre_400_MHZ) || \
                                                          ((type) == PSRAM_UHS_Latency_W5_R13_Max_Fre_333_MHZ) || \
                                                          ((type) == PSRAM_UHS_Latency_W5_R9_Max_Fre_200_MHZ))

/*@} end of group PSRAM_UHS_Public_Constants */

/** @defgroup  PSRAM_UHS_Public_Macros
 *  @{
 */

/*@} end of group PSRAM_UHS_Public_Macros */

/** @defgroup  PSRAM_UHS_Public_Functions
 *  @{
 */

/*@} end of group PSRAM_UHS_Public_Functions */

/*@} end of group PSRAM_UHS */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_PSRAM_UHS_H__ */
