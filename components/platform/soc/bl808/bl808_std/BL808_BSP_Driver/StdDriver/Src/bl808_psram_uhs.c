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

#include "bl808_psram_uhs.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PSRAM_UHS
 *  @{
 */

/** @defgroup  PSRAM_UHS_Private_Macros
 *  @{
 */
#define PSRAM_UHM_RW_TIMEOUT                             0xffffffff

/*@} end of group PSRAM_UHS_Private_Macros */

/** @defgroup  PSRAM_UHS_Private_Types
 *  @{
 */

/*@} end of group PSRAM_UHS_Private_Types */

/** @defgroup  PSRAM_UHS_Private_Variables
 *  @{
 */

/*@} end of group PSRAM_UHS_Private_Variables */

/** @defgroup  PSRAM_UHS_Global_Variables
 *  @{
 */

/*@} end of group PSRAM_UHS_Global_Variables */

/** @defgroup  PSRAM_UHS_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PSRAM_UHS_Private_Fun_Declaration */

/** @defgroup  PSRAM_UHS_Private_Functions
 *  @{
 */

/*@} end of group PSRAM_UHS_Private_Functions */

/** @defgroup  PSRAM_UHS_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Init Psram UHS ,set auto refresh cycle
 *
 * @param  cfg: pck frequency unit is MHZ
 *
 * @return None
 *
*******************************************************************************/
void Psram_UHS_Init(PSRAM_UHS_Cfg_Type * cfg){

    /* pck period unit is ps */
    uint32_t tmpVal = 0;
    uint32_t pck_perid = 0;
    uint32_t refresh_window = 0;
    uint32_t reg_win_cycle = 0;
    uint32_t auto_refresh_cycle_time = 90 * 1000;
    uint32_t reg_burst_cycle=0;


    CHECK_PARAM(IS_PSRAM_UHS_MEM_SIZE_TYPE(cfg->psramMemSize));
    CHECK_PARAM(IS_PSRAM_UHS_PAGE_SIZE_TYPE(cfg->psramPageSize));

    /* Wait 150 us */
    ARCH_Delay_US(150);

    /* set refresh paramater */

    /* 1. calculate pck period unit is ps ,pck_freq unit is Mhz*/
    pck_perid =  ((1000 * 1000) / cfg->pck_freq);

    /* 2. calculate refresh windows cycle count 
     * reg_win_cycle = refresh_window / Tpck_y
     * 
     * refresh_window unit is ms
     * when refresh tempotory > 85 
     *      refresh_window = 16 
     * else 
     *      refresh_window = 32
     */

    if(cfg->isHighTem){
        refresh_window = 16;
    }else{
        refresh_window = 32;
    }

    reg_win_cycle = (refresh_window * 1000 * 1000 * 1000) / pck_perid;

    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_1,reg_win_cycle); 

    /* 3 & 4. calculate refresh count in a windows fixed value 4096 in v0.1
     * calculate Average cycle between two auto-refresh 
     * reg_refi_cycle = reg_win_cycle / reg_win_ref_cnt
     * */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_2);  

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_WIN_REF_CNT,4096);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_REFI_CYCLE,reg_win_cycle/4096);

    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_2,tmpVal);     

    /* 5 calculate single auto refresh time */

    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_4);  

    if(auto_refresh_cycle_time % pck_perid == 0)
        reg_burst_cycle = auto_refresh_cycle_time / pck_perid;
    else
        reg_burst_cycle = auto_refresh_cycle_time / pck_perid + 1;

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_BUST_CYCLE,reg_burst_cycle);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_AUTO_FRESH_4,tmpVal); 

    /* 6 auto-refesh enable */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);  
    tmpVal = BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_AF_EN);  

    /* 7&8 . set psram memory size and page size */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_ADDRMB_MSK,cfg->psramMemSize);  
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_LINEAR_BND_B,cfg->psramPageSize);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);   

    /* 9. psram enable initial */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);  
    tmpVal = BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_INIT_EN);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal); 
}


/****************************************************************************//**
 * @brief  Read register for uhs
 *
 * @param  reg_addr: read addr
 * @param  regVal: regVal
 *
 * @return success or not
 *
*******************************************************************************/
int PSram_UHS_Read_Reg(uint32_t reg_addr,uint8_t *regVal)
{
    uint32_t tmpVal = 0;
    uint32_t cnt=0;

    /* 1 set mode reg */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);  
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_MODE_REG,reg_addr);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal); 

    /* 2 generate requeset and wait authorization*/
    tmpVal=BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);     
    tmpVal=BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_CONFIG_REQ);        
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);  
 
    do{   
        tmpVal=BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC); 
        cnt ++;
        if(cnt > PSRAM_UHM_RW_TIMEOUT)
            return -1;
    }while(!BL_IS_REG_BIT_SET(tmpVal,PSRAM_UHS_REG_CONFIG_GNT));

    /* 3 enable controller Rx*/
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);  
    tmpVal = BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_REGR_PULSE);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal); 

    cnt = 0;

    /* 4 wait read done */
    do{   
        tmpVal=BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC); 
        cnt ++;
        if(cnt > PSRAM_UHM_RW_TIMEOUT)
            return -1;
    }while(!BL_IS_REG_BIT_SET(tmpVal,PSRAM_UHS_STS_REGR_DONE));
    
    /* 5 steup up read data */
    tmpVal=BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD); 

    *regVal = (uint8_t)(BL_GET_REG_BITS_VAL(tmpVal,PSRAM_UHS_STS_CONFIG_READ));

    return 0;
}


/****************************************************************************//**
 * @brief  write register for winbond PSRAM
 *
 * @param  reg_addr: reg_addr
 * @param  regCfg: wirte reg data
 *
 * @return None
 *
*******************************************************************************/
int PSram_UHS_Write_Reg(uint32_t reg_addr,PSRAM_UHS_Write_Reg_Cfg_Type *regCfg)
{
    uint32_t tmpVal = 0;
    uint32_t cnt=0;

    /* 1 set mode reg */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);  
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_MODE_REG,reg_addr);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal); 

    /* 2 congfi write reg*/
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_PSRAM_CONFIGURE);  

    switch(regCfg->burst_size){
        case PSRAM_UHS_Warp_Burst_64: tmpVal = BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_UHS_BL_64);break;
        case PSRAM_UHS_Warp_Burst_32: tmpVal = BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_UHS_BL_32);break;
        case PSRAM_UHS_Warp_Burst_16: tmpVal = BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_UHS_BL_16);break;
        default: return -1;
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_DRIVE_ST,regCfg->driver_st);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PSRAM_UHS_REG_UHS_LATENCY,regCfg->lentency);

    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_PSRAM_CONFIGURE,tmpVal); 


    /* 3 generate requeset and wait authorization*/
    tmpVal=BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC);     
    tmpVal=BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_CONFIG_REQ);        
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC,tmpVal);  
 
    do{   
        tmpVal=BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC); 
        cnt ++;
        if(cnt > PSRAM_UHM_RW_TIMEOUT)
            return -1;
    }while(!BL_IS_REG_BIT_SET(tmpVal,PSRAM_UHS_REG_CONFIG_GNT));

    /* 4 enable controller */
    tmpVal = BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD);  
    tmpVal = BL_SET_REG_BIT(tmpVal,PSRAM_UHS_REG_REGW_PULSE);
    BL_WR_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_CMD,tmpVal); 

    cnt = 0;

    /* 5 wait write done */
    do{   
        tmpVal=BL_RD_REG(PSRAM_UHS_BASE,PSRAM_UHS_UHS_BASIC); 
        cnt ++;
        if(cnt > PSRAM_UHM_RW_TIMEOUT)
            return -1;
    }while(!BL_IS_REG_BIT_SET(tmpVal,PSRAM_UHS_STS_REGW_DONE));
    
    return 0;
}

/*@} end of group PSRAM_UHS_Public_Functions */

/*@} end of group PSRAM_UHS */

/*@} end of group BL808_Peripheral_Driver */
