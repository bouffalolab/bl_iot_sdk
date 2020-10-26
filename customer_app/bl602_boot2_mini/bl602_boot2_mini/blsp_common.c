/*
 * Copyright (c) 2020 Bouffalolab.
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

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "blsp_port.h"
#include "bflb_platform.h"
#include "blsp_bootinfo.h"
#include "blsp_common.h"
#include "blsp_media_boot.h"

/** @addtogroup  BL606_BLSP_Boot2
 *  @{
 */

/** @addtogroup  BLSP_COMMON
 *  @{
 */

/** @defgroup  BLSP_COMMON_Private_Macros
 *  @{
 */

/*@} end of group BLSP_COMMON_Private_Macros */

/** @defgroup  BLSP_COMMON_Private_Types
 *  @{
 */

/*@} end of group BLSP_COMMON_Private_Types */

/** @defgroup  BLSP_COMMON_Private_Variables
 *  @{
 */

/*@} end of group BLSP_COMMON_Private_Variables */

/** @defgroup  BLSP_COMMON_Global_Variables
 *  @{
 */
int32_t BLSP_Boot2_Set_Encrypt(uint8_t index,Boot_Image_Config *bootImgCfg);
int32_t BLSP_Boot2_Set_Cache(uint8_t contRead,SPI_Flash_Cfg_Type *flashCfg,Boot_Image_Config *bootImgCfg);

/*@} end of group BLSP_COMMON_Global_Variables */

/** @defgroup  BLSP_COMMON_Private_Fun_Declaration
 *  @{
 */

/*@} end of group BLSP_COMMON_Private_Fun_Declaration */

/** @defgroup  BLSP_COMMON_Private_Functions_User_Define
 *  @{
 */

/*@} end of group BLSP_COMMON_Private_Functions_User_Define */

/** @defgroup  BLSP_COMMON_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Dump data
 *
 * @param  datain: Data pointer to dump
 * @param  len: Data length to dump
 *
 * @return None
 *
*******************************************************************************/
void BLSP_Dump_Data(void *datain,int len)
{
    int i=0;
    uint8_t *data=(uint8_t *)datain;
    
    for(i=0;i<len;i++){
        if(i%16==0&&i!=0){
            MSG("\r\n");
        }
        MSG("%02x ",data[i]);
    }
    MSG("\r\n");
}

/****************************************************************************//**
 * @brief  Media boot pre-jump
 *
 * @param  None
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
int32_t BLSP_MediaBoot_Pre_Jump(void)
{
    /* Sec eng deinit*/
    BLSP_Boot2_Reset_Sec_Eng();
    
    /* Platform deinit */
    bflb_platform_deinit(); 
    
    /* Jump to entry */
    BLSP_Boot2_Jump_Entry(0x00011000);
    
    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Boot2 exit with error and will stay forever
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void BLSP_Boot2_Exit(void)
{    
    uint32_t i=0;
    
    BLSP_Sboot_Finish();
    /* Prepare release Other CPUs anyway */
    /* Deal Other CPU's entry point */
    for(i=1;i<cpuCount;i++){
        BL_WR_WORD(bootCpuCfg[i].mspStoreAddr,0);
        BL_WR_WORD(bootCpuCfg[i].pcStoreAddr,0);
    }    
    /* Release other CPUs*/
    if(cpuCount!=1&&!bootImgCfg[0].haltCPU1){
        BLSP_Boot2_Releae_Other_CPU();
    }    
    /* Stay here */
    while(1){
        /* Use soft delay only */
        ARCH_Delay_MS(100);
    }
}

/****************************************************************************//**
 * @brief  Boot2 jump to entryPoint
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION BLSP_Boot2_Jump_Entry(uint32_t entry)
{
    SF_Ctrl_Set_Flash_Image_Offset(entry);
    SFlash_Cache_Flush();
    pentry_t pentry=(pentry_t)0x23000000;
    pentry();
}

/*@} end of group BLSP_COMMON_Public_Functions */

/*@} end of group BLSP_COMMON */

/*@} end of group BL606_BLSP_Boot2 */
