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

#include "bl808_l1c.h"
#include "bl808_common.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  L1C
 *  @{
 */

/** @defgroup  L1C_Private_Macros
 *  @{
 */

/*@} end of group L1C_Private_Macros */

/** @defgroup  L1C_Private_Types
 *  @{
 */

/*@} end of group L1C_Private_Types */

/** @defgroup  L1C_Private_Variables
 *  @{
 */

/*@} end of group L1C_Private_Variables */

/** @defgroup  L1C_Global_Variables
 *  @{
 */

/*@} end of group L1C_Global_Variables */

/** @defgroup  L1C_Private_Fun_Declaration
 *  @{
 */

/*@} end of group L1C_Private_Fun_Declaration */

/** @defgroup  L1C_Private_Functions
 *  @{
 */

/*@} end of group L1C_Private_Functions */

/** @defgroup  L1C_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Enable I-Cache
 *
 * @param  wayDsiable: cache way disable config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_ICache_Enable(uint8_t wayDsiable)
{
#ifndef __riscv_32e
    csi_icache_enable();
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Enable D-Cache
 *
 * @param  wayDsiable: cache way disable config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Enable(uint8_t wayDsiable)
{
#ifndef __riscv_32e
    csi_dcache_enable();
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Disable I-Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_ICache_Disable(void)
{
#ifndef __riscv_32e
    csi_icache_disable();
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Disable D-Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Disable(void)
{
#ifndef __riscv_32e
    csi_dcache_disable();
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  L1C D-Cache write set
 *
 * @param  wtEn: L1C write through enable
 * @param  wbEn: L1C write back enable
 * @param  waEn: L1C write allocate enable
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION L1C_DCache_Write_Set(BL_Fun_Type wtEn, BL_Fun_Type wbEn, BL_Fun_Type waEn)
{
    return ;
}

/****************************************************************************//**
 * @brief  Clean all D_Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Clean_All(void)
{
#ifndef __riscv_32e
    csi_dcache_clean();
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Clean and invalid all D_Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Clean_Invalid_All(void)
{
#ifndef __riscv_32e
    csi_dcache_clean_invalid();
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Invalid all I-Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_ICache_Invalid_All(void)
{
#ifndef __riscv_32e
    csi_icache_invalid();
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Invalid all D_Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Invalid_All(void)
{
#ifndef __riscv_32e
    csi_dcache_invalid();
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Clean D-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Clean_By_Addr(uintptr_t addr,uint32_t len)
{
#ifndef __riscv_32e
    csi_dcache_clean_range((uintptr_t *)addr,len);
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Clean and invalid D-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Clean_Invalid_By_Addr(uintptr_t addr,uint32_t len)
{
#ifndef __riscv_32e
    csi_dcache_clean_invalid_range((uintptr_t *)addr,len);
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Invalid I-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_ICache_Invalid_By_Addr(uintptr_t addr,uint32_t len)
{
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Invalid D-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Invalid_By_Addr(uintptr_t addr,uint32_t len)
{
#ifndef __riscv_32e
    csi_dcache_invalid_range((uintptr_t *)addr,len);
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  cache wrap
 *
 * @param  en: wrap enable or disable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION L1C_Set_Wrap(uint8_t en)
{
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  cache setting
 *
 * @param  cacheSetting: cache setting
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_Set_LP_Cache_Setting(L1C_CACHE_Cfg_Type *cacheSetting)
{
    uint32_t tmpVal;
    uint32_t cnt=0;
    uint8_t finWayDisable=0;
    
    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_BYPASS);
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_EARLY_RESP_DIS);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CNT_EN);
    finWayDisable=BL_GET_REG_BITS_VAL(tmpVal,PDS_L1C_WAY_DIS);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    /*Set Tag RAM to zero */
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_INVALID_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_INVALID_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    /* Polling for invalid done */
    do{
        ARCH_Delay_US(1);
        cnt++;
        tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    }while(!BL_IS_REG_BIT_SET(tmpVal,PDS_L1C_INVALID_DONE)&&cnt<100);

    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_INVALID_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    /* data flush */
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_FLUSH_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_FLUSH_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    /* Polling for flush done */
    do{
        ARCH_Delay_US(1);
        cnt++;
        tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    }while(!BL_IS_REG_BIT_SET(tmpVal,PDS_L1C_FLUSH_DONE)&&cnt<100);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_FLUSH_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_BYPASS);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_BYPASS);
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_CNT_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    if(cacheSetting->wayDis!=L1C_WAY_DISABLE_NOT_CAHNGE){
        finWayDisable=cacheSetting->wayDis;
    }

    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_WAY_DIS);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_L1C_WA_EN,cacheSetting->wa);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_L1C_WB_EN,cacheSetting->wb);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_L1C_WT_EN,cacheSetting->wt);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    tmpVal|=(finWayDisable<<PDS_L1C_WAY_DIS_POS);
    /* If way disable is 0x0f, cacheable can't be set */
    if(finWayDisable!=L1C_WAY_DISABLE_ALL){
       tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    }else{
       tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    }
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    /* Set cache range */
    *(volatile uint32_t *)(PDS_BASE + 0x104)  = cacheSetting->cacheRangeL;
    *(volatile uint32_t *)(PDS_BASE + 0x100)  = cacheSetting->cacheRangeH;

    return SUCCESS;
}

BL_Err_Type ATTR_TCM_SECTION L1C_Set_Cache_Setting_By_ID(uint8_t core,L1C_CACHE_Cfg_Type *cacheSetting)
{
    if(GLB_CORE_ID_LP==core){
        L1C_Set_LP_Cache_Setting(cacheSetting);
    }
    return SUCCESS;
}

/*@} end of group L1C_Public_Functions */

/*@} end of group L1C */

/*@} end of group BL808_Peripheral_Driver */
