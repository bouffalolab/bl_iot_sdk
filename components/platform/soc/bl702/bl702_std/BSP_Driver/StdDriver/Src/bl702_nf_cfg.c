/**
  ******************************************************************************
  * @file    bl702_nf_cfg.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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
  *
  ******************************************************************************
  */

#include "bl702_glb.h"
#include "bl702_nf_cfg.h"
#include "bl702_sf_cfg.h"
#include "softcrc.h"
#include "bl702_xip_sflash.h"

typedef struct {
    uint32_t jedecID;
    char *name;
    const Nand_Flash_Cfg_Type *cfg;
}Flash_Info_t;



/** @defgroup  NF_CFG_Private_Variables
 *  @{
 */
static const ATTR_TCM_CONST_SECTION Nand_Flash_Cfg_Type flashCfg_XT_26G01A={
        .resetCreadCmd = 0xff,
        .resetCreadCmdSize = 1,
    //    .mid=0xef,

        .deBurstWrapCmd = 0x77,
        .deBurstWrapCmdDmyClk = 0x3,
        .deBurstWrapDataMode = SF_CTRL_DATA_4_LINES,
        .deBurstWrapData = 0xF0,

        /*reg*/
        .writeEnableCmd = 0x06,
    //    .wrEnableIndex=0x00,
    //    .wrEnableBit=0x01,
    //    .wrEnableReadRegLen=0x01,
    /*
        .qeIndex=1,
        .qeBit=0x01,
        .qeWriteRegLen=0x02,
        .qeReadRegLen=0x1,

        .busyIndex=0,
        .busyBit=0x00,
        .busyReadRegLen=0x1,
        .releasePowerDown=0xab,

        .readRegCmd[0]=0x05,
        .readRegCmd[1]=0x35,
        .writeRegCmd[0]=0x01,
        .writeRegCmd[1]=0x01,

        .fastReadQioCmd=0xeb,
        .frQioDmyClk=16/8,
        .cReadSupport=0,
        .cReadMode=0xFF,

        .burstWrapCmd=0x77,
        .burstWrapCmdDmyClk=0x3,
        .burstWrapDataMode=SF_CTRL_DATA_4_LINES,
        .burstWrapData=0x40,*/
         /*erase*/
    //    .chipEraseCmd=0xc7,
    //    .sectorEraseCmd=0x20,
        .blk128EraseCmd = 0xd8,
        
        /*write*/
        .programLoadCmd = 0x02,
        .pageProgramCmd = 0x10,
        .qpageProgramCmd = 0x32,
        .qppAddrMode = SF_CTRL_ADDR_1_LINE,

        .ioMode = SF_CTRL_NIO_MODE,
    //    .clkDelay=1,
    //    .clkInvert=0x3d,
    /*
        .resetEnCmd=0x66,
        .resetCmd=0x99,
        .cRExit=0xff,
        .wrEnableWriteRegLen=0x00,
    */
        /*get feature*/
        .getFeaturesCmd = 0x0f,

        /*set feature*/
		.setFeaturesCmd = 0x1f,

        /*id*/
        .jedecIdCmd = 0x9f,
        .jedecIdCmdDmyClk = 0,
        .qpiJedecIdCmd = 0x9f,
        .qpiJedecIdCmdDmyClk = 0x00,
    //    .sectorSize=4,
    //    .pageSize=256,

        /*read*/
        .pageReadToCacheCmd = 0x13,
        .fastReadCmd = 0x0b,
        .frDmyClk = 8 / 8,
        .qpiFastReadCmd =0x0b,
        .qpiFrDmyClk =8 / 8,
        .fastReadDoCmd = 0x3b,
        .frDoDmyClk=8 / 8,
        .fastReadDioCmd = 0xbb,
        .frDioDmyClk = 0,
        .fastReadQoCmd = 0x6b,
        .frQoDmyClk = 8 / 8,

        .qpiFastReadQioCmd = 0xeb,
        .qpiFrQioDmyClk = 16/8,
        .qpiPageProgramCmd = 0x02,
        .writeVregEnableCmd = 0x50,

        /* qpi mode */
        .enterQpi = 0x38,
        .exitQpi = 0xff,

         /*AC*/
        .timeEsector = 300,
        .timePagePgm = 5,
        .timeCe = 20 * 1000,
        .pdDelay = 3,
        .qeData = 0,
};

static const ATTR_TCM_CONST_SECTION Flash_Info_t flashInfos[]={
    {
        .jedecID=0xe10b,
        .name="XT_26G01A",
        .cfg= & flashCfg_XT_26G01A,
    },
};

/****************************************************************************//**
 * @brief  Identify one flash
 *
 * @param  callFromFlash: code run at flash or ram
 * @param  autoScan: Auto scan all GPIO pin
 * @param  flashPinCfg: Specify flash GPIO config, not auto scan
 * @param  restoreDefault: Wether restore default flash GPIO config
 * @param  pFlashCfg: Flash config pointer
 *
 * @return Flash ID
 *
*******************************************************************************/

uint32_t ATTR_TCM_SECTION NF_Cfg_Flash_Identify(uint8_t callFromFlash,
    uint32_t autoScan, uint32_t flashPinCfg, uint8_t restoreDefault, Nand_Flash_Cfg_Type *pFlashCfg)
{
    uint32_t jdecId = 0;
    uint32_t i = 0;

    BL702_MemCpy_Fast(pFlashCfg, &flashCfg_XT_26G01A, sizeof(Nand_Flash_Cfg_Type));

    if(autoScan){
        flashPinCfg = 0;
        do{
            if(flashPinCfg > 0x0f){
                jdecId = 0;
                break;
            }
            SF_Cfg_Init_Flash_Gpio(flashPinCfg, restoreDefault);
            jdecId = 0;
            NFlash_GetJedecId(pFlashCfg, (uint8_t *)&jdecId);
            jdecId = jdecId & 0xffff;
            flashPinCfg ++;
        }while((jdecId & 0xffff) == 0 || (jdecId & 0xffff) == 0 || (jdecId & 0xffff) == 0xffff || (jdecId & 0xffff) == 0xffff);
    }else{
        /* select media gpio */
        SF_Cfg_Init_Flash_Gpio(flashPinCfg, restoreDefault);
        NFlash_GetJedecId(pFlashCfg, (uint8_t *)&jdecId);
        jdecId = jdecId & 0xffff;
    }

    for(i = 0; i < sizeof(flashInfos) / sizeof(flashInfos[0]); i++){
        if(flashInfos[i].jedecID == jdecId){
            BL702_MemCpy_Fast(pFlashCfg,flashInfos[i].cfg,sizeof(Nand_Flash_Cfg_Type));
            return jdecId;
        }
    }

    return jdecId;
}

/*@} end of group NF_CFG_Public_Functions */

/*@} end of group NF_CFG */

/*@} end of group BL702_Peripheral_Driver */
