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
#ifndef __BL808_L1C_H__
#define __BL808_L1C_H__

#include "pds_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  L1C
 *  @{
 */

/** @defgroup  L1C_Public_Types
 *  @{
 */

/**
 *  @brief L1C configuration structure type definition
 */
typedef struct {
    uint8_t cacheEn;
    uint8_t wayDis;
    uint8_t wa;
    uint8_t wb;
    uint8_t wt;
    uint8_t rsvd[3];
    uint32_t cacheRangeL;
    uint32_t cacheRangeH;
}L1C_CACHE_Cfg_Type;

/**
 *  @brief L1C BMX arb mode type definition
 */
typedef enum {
    L1C_BMX_ARB_FIX,                        /*!< 0->fix */
    L1C_BMX_ARB_ROUND_ROBIN,                /*!< 2->round-robin */
    L1C_BMX_ARB_RANDOM,                     /*!< 3->random */
}L1C_BMX_ARB_Type;

/**
 *  @brief L1C BMX configuration structure type definition
 */
typedef struct {
    uint8_t timeoutEn;                      /*!< Bus timeout enable: detect slave no reaponse in 1024 cycles */
    BL_Fun_Type errEn;                      /*!< Bus error response enable */
    L1C_BMX_ARB_Type arbMod;                /*!< 0->fix, 2->round-robin, 3->random */
}L1C_BMX_Cfg_Type;

/**
 *  @brief L1C BMX bus err type definition
 */
typedef enum {
    L1C_BMX_BUS_ERR_TRUSTZONE_DECODE,       /*!< Bus trustzone decode error */
    L1C_BMX_BUS_ERR_ADDR_DECODE,            /*!< Bus addr decode error */
}L1C_BMX_BUS_ERR_Type;

/**
 *  @brief L1C BMX bus err interrupt type definition
 */
typedef enum {
    L1C_BMX_ERR_INT_ERR,                    /*!< L1C BMX bus err interrupt */
    L1C_BMX_ERR_INT_ALL,                    /*!< L1C BMX bus err interrupt max num */
}L1C_BMX_ERR_INT_Type;

/**
 *  @brief L1C BMX time out interrupt type definition
 */
typedef enum {
    L1C_BMX_TO_INT_TIMEOUT,                 /*!< L1C_BMX timeout interrupt */
    L1C_BMX_TO_INT_ALL,                     /*!< L1C_BMX timeout interrupt max num */
}L1C_BMX_TO_INT_Type;

/*@} end of group L1C_Public_Types */

/** @defgroup  L1C_Public_Constants
 *  @{
 */

/** @defgroup  L1C_BMX_ARB_TYPE
 *  @{
 */
#define IS_L1C_BMX_ARB_TYPE(type)                        (((type) == L1C_BMX_ARB_FIX) || \
                                                          ((type) == L1C_BMX_ARB_ROUND_ROBIN) || \
                                                          ((type) == L1C_BMX_ARB_RANDOM))

/** @defgroup  L1C_BMX_BUS_ERR_TYPE
 *  @{
 */
#define IS_L1C_BMX_BUS_ERR_TYPE(type)                    (((type) == L1C_BMX_BUS_ERR_TRUSTZONE_DECODE) || \
                                                          ((type) == L1C_BMX_BUS_ERR_ADDR_DECODE))

/** @defgroup  L1C_BMX_ERR_INT_TYPE
 *  @{
 */
#define IS_L1C_BMX_ERR_INT_TYPE(type)                    (((type) == L1C_BMX_ERR_INT_ERR) || \
                                                          ((type) == L1C_BMX_ERR_INT_ALL))

/** @defgroup  L1C_BMX_TO_INT_TYPE
 *  @{
 */
#define IS_L1C_BMX_TO_INT_TYPE(type)                     (((type) == L1C_BMX_TO_INT_TIMEOUT) || \
                                                          ((type) == L1C_BMX_TO_INT_ALL))

/*@} end of group L1C_Public_Constants */

/** @defgroup  L1C_Public_Macros
 *  @{
 */
#define L1C_WAY_DISABLE_NONE                     0x00
#define L1C_WAY_DISABLE_ONE                      0x01
#define L1C_WAY_DISABLE_TWO                      0x03
#define L1C_WAY_DISABLE_ALL                      0x03
#define L1C_WAY_DISABLE_NOT_CAHNGE               0xFF
#if 1
/*NP config address */
#define L1C_CONF_REG                             (L1C_BASE+0x00)
#define L1C_HIT_CNT_LSB_REG                      (L1C_BASE+0x04)
#define L1C_HIT_CNT_MSB_REG                      (L1C_BASE+0x08)
#define L1C_MISS_CNT_REG                         (L1C_BASE+0x0C)
/* Get miss and hit count */
#define L1C_Get_Miss_Cnt()                       BL808_REG_RD(L1C_MISS_CNT_REG)
#define L1C_Get_Hit_Cnt_LSB()                    BL808_REG_RD(L1C_HIT_CNT_LSB_REG)
#define L1C_Get_Hit_Cnt_MSB()                    BL808_REG_RD(L1C_HIT_CNT_MSB_REG)
#endif

/*@} end of group L1C_Public_Macros */

/** @defgroup  L1C_Public_Functions
 *  @{
 */

/*----------*/
BL_Err_Type L1C_ICache_Enable(uint8_t wayDsiable);
BL_Err_Type L1C_DCache_Enable(uint8_t wayDsiable);
BL_Err_Type L1C_ICache_Disable(void);
BL_Err_Type L1C_DCache_Disable(void);
void L1C_DCache_Write_Set(BL_Fun_Type wtEn, BL_Fun_Type wbEn, BL_Fun_Type waEn);
BL_Err_Type L1C_DCache_Clean_All(void);
BL_Err_Type L1C_DCache_Clean_Invalid_All(void);
BL_Err_Type L1C_ICache_Invalid_All(void);
BL_Err_Type L1C_DCache_Invalid_All(void);
BL_Err_Type L1C_DCache_Clean_By_Addr(uintptr_t addr,uint32_t len);
BL_Err_Type L1C_DCache_Clean_Invalid_By_Addr(uintptr_t addr,uint32_t len);
BL_Err_Type L1C_ICache_Invalid_By_Addr(uintptr_t addr,uint32_t len);
BL_Err_Type L1C_DCache_Invalid_By_Addr(uintptr_t addr,uint32_t len);
/*----------*/
BL_Err_Type L1C_Set_Wrap(uint8_t en);
BL_Err_Type L1C_Set_LP_Cache_Setting(L1C_CACHE_Cfg_Type *cacheSetting);
BL_Err_Type L1C_Set_Cache_Setting_By_ID(uint8_t core,L1C_CACHE_Cfg_Type *cacheSetting);
/*----------*/

/*@} end of group L1C_Public_Functions */

/*@} end of group L1C */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_L1C_H__ */
