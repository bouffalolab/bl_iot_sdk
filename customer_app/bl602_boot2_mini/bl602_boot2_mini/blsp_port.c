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

/** @addtogroup  BLSP_PORT
 *  @{
 */

/** @defgroup  BLSP_PORT_Private_Macros
 *  @{
 */

/*@} end of group BLSP_PORT_Private_Macros */

/** @defgroup  BLSP_PORT_Private_Types
 *  @{
 */

/*@} end of group BLSP_PORT_Private_Types */

/** @defgroup  BLSP_PORT_Private_Variables
 *  @{
 */

/*@} end of group BLSP_PORT_Private_Variables */

/** @defgroup  BLSP_PORT_Global_Variables
 *  @{
 */

/*@} end of group BLSP_PORT_Global_Variables */

/** @defgroup  BLSP_PORT_Private_Fun_Declaration
 *  @{
 */

/*@} end of group BLSP_PORT_Private_Fun_Declaration */

/** @defgroup  BLSP_PORT_Private_Functions_User_Define
 *  @{
 */

/*@} end of group BLSP_PORT_Private_Functions_User_Define */

/** @defgroup  BLSP_PORT_Private_Functions
 *  @{
 */

/*@} end of group BLSP_PORT_Private_Functions */

/** @defgroup  BLSP_PORT_Public_Functions
 *  @{
 */
/****************************************************************************//**
 * @brief  Boot2 init timer for cal boot time
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void BLSP_Boot2_Init_Timer(void)
{
    TIMER_CFG_Type timerCfg = {
                                TIMER_CH0,                           /* timer channel 0 */
                                TIMER_CLKSRC_FCLK,                   /* timer clock source:bus clock */
                                TIMER_PRELOAD_TRIG_NONE,            /* reaload on comaparator 2  */
                                TIMER_COUNT_FREERUN,                 /* preload when match occur */
                                159,                                 /* clock divider */
                                0xfffffffe,                          /* match value 0  */
                                0xfffffffe,                          /* match value 1 */
                                0xfffffffe,                          /* match value 2 */
                                0,                                   /* preload value */
                           };

    /* Disable all interrupt */
    TIMER_IntMask(timerCfg.timerCh, TIMER_INT_ALL, MASK);

    /* Disable timer before config */
    TIMER_Disable(timerCfg.timerCh);

    /* Timer init with default configuration */
    TIMER_Init(&timerCfg);

    /* Enable timer */
    TIMER_Enable(timerCfg.timerCh);
}

/****************************************************************************//**
* @brief  Boot2 Disable other CPU cache
*
* @param  None
*
* @return None
*
*******************************************************************************/
void BLSP_Boot2_Disable_Other_Cache(void)
{

}

/****************************************************************************//**
* @brief  Boot2 Flash Boot2 cache
*
* @param  None
*
* @return None
*
*******************************************************************************/
void BLSP_Boot2_Flush_XIP_Cache()
{
    SFlash_Cache_Flush();
}

/****************************************************************************//**
 * @brief  Boot2 Get fw clock config
 *
 * @param  cfg: Clock config pointer
 *
 * @return Boot_Error_Code
 *
*******************************************************************************/
int32_t ATTR_TCM_SECTION BLSP_Boot2_Get_Clk_Cfg(Boot_Clk_Config *cfg)
{

    XIP_SFlash_Read_Via_Cache_Need_Lock(8+sizeof(Boot_Flash_Config)+BLSP_BOOT2_XIP_BASE,
    (uint8_t *)cfg,sizeof(Boot_Clk_Config));

    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
* @brief  Boot2 show timer for cal boot time
*
* @param  None
*
* @return None
*
*******************************************************************************/
void BLSP_Boot2_Show_Timer(void)
{
    MSG("Counter value=%d,%d\n",TIMER_GetCounterValue(TIMER_CH0));
}

/****************************************************************************//**
* @brief  Boot2 get efuse config security
*
* @param  None
*
* @return None
*
*******************************************************************************/
void ATTR_TCM_SECTION BLSP_Boot2_Get_Efuse_Cfg(Boot_Efuse_HW_Config *efuseCfg)
{
    uint32_t tmp;

    HBN_Set_ROOT_CLK_Sel(GLB_ROOT_CLK_XTAL);

    /* Get sign and aes type*/
    EF_Ctrl_Read_Secure_Boot((EF_Ctrl_Sign_Type*)efuseCfg->sign, (EF_Ctrl_SF_AES_Type*)efuseCfg->encrypted);
    /* Get hash:aes key slot 0 and slot1*/
    EF_Ctrl_Read_AES_Key(0,(uint32_t *)efuseCfg->pkHashCpu0,8);
    EF_Ctrl_Read_Chip_ID(efuseCfg->chipID);
    /* Get HBN check sign config */
    EF_Ctrl_Read_Sw_Usage(0,&tmp);
    efuseCfg->hbnCheckSign=(tmp>>22)&0x01;

    GLB_Set_System_CLK_Div(0,1);
    HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_PLL);
}

/****************************************************************************//**
* @brief  Boot2 reset sec_eng module
*
* @param  None
*
* @return None
*
*******************************************************************************/
void BLSP_Boot2_Reset_Sec_Eng(void)
{
    GLB_AHB_Slave1_Reset(BL_AHB_SLAVE1_SEC);
}

/****************************************************************************//**
* @brief  Boot2 init sec_eng PKA module
*
* @param  None
*
* @return None
*
*******************************************************************************/
void BLSP_Boot2_Init_Sec_Eng_PKA(void)
{
    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();
}


/****************************************************************************//**
* @brief  Boot2 get cpu count info
*
* @param  None
*
* @return None
*
*******************************************************************************/
uint32_t BLSP_Boot2_Get_CPU_Count(void)
{
    return 1;
}

/****************************************************************************//**
 * @brief  Read power save mode
 *
 * @param  None
 *
 * @return BFLB_PSM_ACTIVE or BFLB_PSM_HBN
 *
*******************************************************************************/
uint8_t BLSP_Read_Power_Save_Mode(void)
{
    if(HBN_Get_Status_Flag()==HBN_STATUS_WAKEUP_FLAG){
        return BFLB_PSM_HBN;
    }else{
        return BFLB_PSM_ACTIVE;
    }
}

/****************************************************************************//**
 * @brief  Boot2 Pass parameter to FW
 *
 * @param  data: Data pointer to pass
 * @param  len: Data length
 *
 * @return None
 *
*******************************************************************************/
void BLSP_Boot2_Pass_Parameter(void *data,uint32_t len)
{
    static uint8_t *pParameter=NULL;
    if(len==0){
    	GLB_Set_EM_Sel(0);
        pParameter=(uint8_t *)(0x42030000+103*1024);
        return;
    }
    ARCH_MemCpy_Fast(pParameter,data,len);
    pParameter+=len;
}

/****************************************************************************//**
 * @brief  Boot2 Get XIP offset
 *
 * @param  None
 *
 * @return XIP offset
 *
*******************************************************************************/
uint32_t BLSP_Boot2_Get_XIP_Offset(void)
{
    return SF_Ctrl_Get_Flash_Image_Offset();
}

/****************************************************************************//**
 * @brief  Get User specified firmware to boot up
 *
 * @param  None
 *
 * @return User specified firmware name
 *
*******************************************************************************/
uint8_t* BLSP_Get_User_Specified_Fw(void)
{
    return (uint8_t*)(HBN_BASE+HBN_RSV0_OFFSET);
}

/****************************************************************************//**
 * @brief  Clear User specified firmware to boot up
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void BLSP_Clr_User_Specified_Fw(void)
{
    uint32_t *p=(uint32_t*)(HBN_BASE+HBN_RSV0_OFFSET);

    *p=0;
}

/****************************************************************************//**
 * @brief  Release other CPU
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION BLSP_Boot2_Releae_Other_CPU(void)
{

}

/****************************************************************************//**
   * @brief  Boot2 update fw clock config
   *
   * @param  clkCfg: Clock config pointer
   * @param  flashCfg: flash config pointer
   *
   * @return Boot_Error_Code
   *
*******************************************************************************/
void ATTR_TCM_SECTION BLSP_Boot2_Update_System_Flash_Clk(Boot_Clk_Config *clkCfg,SPI_Flash_Cfg_Type *flashCfg)
{
#if 0
      SF_Ctrl_Cfg_Type sfCtrlCfg={
          .owner=SF_CTRL_OWNER_IAHB,
          .clkDelay=0,
          .clkInvert=1,
          .rxClkInvert=1,
          .doDelay=0,
          .diDelay=0,
          .oeDelay=0,
      };

      GLB_Set_System_CLK((MIXED_PLL_XTAL_Type)(clkCfg->cfg.xtalType-1),
                          (GLB_PLL_CLK_Type)clkCfg->cfg.pllClk);
      GLB_Set_Flash_CLK((GLB_SFLASH_CLK_Type)clkCfg->cfg.flashClkType,0);
      /* update SF CTRL on success */
      /* bit0-3 for clk delay,not my willing, but for setting PLL and flash config in Boot2
         , otherwise getting from FW is not easy */
      sfCtrlCfg.clkDelay=(flashCfg->rsvd1&0x01);
      /* bit0 for clk invert */
      sfCtrlCfg.clkInvert=(flashCfg->rsvd1>>1)&0x01;
      /* bit1 for rx clk invert */
      sfCtrlCfg.rxClkInvert=(flashCfg->rsvd1>>2)&0x01;

      sfCtrlCfg.doDelay=((flashCfg->rsvd1>>3)&0x01)*128;
      sfCtrlCfg.diDelay=((flashCfg->rsvd1>>4)&0x01)*128;
      sfCtrlCfg.oeDelay=((flashCfg->rsvd1>>5)&0x01)*128;

      SFlash_Init(&sfCtrlCfg,flashCfg);
#endif
}

/****************************************************************************//**
 * @brief  Set encryption config
 *
 * @param  index: Region index
 * @param  bootImgCfg: Boot image config pointer to hold parsed information
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
int32_t ATTR_TCM_SECTION BLSP_Boot2_Set_Encrypt(uint8_t index,Boot_Image_Config *bootImgCfg)
{
    uint32_t aesEnabled=0;
    uint32_t len=0;

    /* FIXME:,1:lock, should be 1??*/
    if(bootImgCfg->encryptType!=0){
        len=bootImgCfg->imgSegmentInfo.imgLen;
        if(len!=0){
            SF_Ctrl_AES_Set_Key_BE(index,NULL,(SF_Ctrl_AES_Key_Type)(bootImgCfg->encryptType-1));
            SF_Ctrl_AES_Set_IV_BE(index,bootImgCfg->aesiv,bootImgCfg->imgStart.flashOffset);

            SF_Ctrl_AES_Set_Region(index,1/*enable this region*/,1/*hardware key*/,
                                    bootImgCfg->imgStart.flashOffset,
                                    bootImgCfg->imgStart.flashOffset+len-1,
                                    bootImgCfg->aesRegionLock/*lock*/);
            aesEnabled=1;
        }
    }

    if(aesEnabled){
        SF_Ctrl_AES_Enable_BE();
        SF_Ctrl_AES_Enable();
    }

    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Media boot set cache according to image config
 *
 * @param  None
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
int32_t ATTR_TCM_SECTION BLSP_Boot2_Set_Cache(uint8_t contRead,SPI_Flash_Cfg_Type *flashCfg,Boot_Image_Config *bootImgCfg)
{
    uint32_t tmp[1];
    uint32_t stat;

    /* To make it simple, exit cont read anyway */
    SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);
    SFlash_Reset_Continue_Read(flashCfg);
    if(contRead==1){
        stat=SFlash_Read(flashCfg,SF_CTRL_QIO_MODE,1,0x00000000,(uint8_t *)tmp, sizeof(tmp));
        if(SUCCESS!=stat){
            return BFLB_BOOT2_FAIL;
        }
    }
    /* Set default value */
    SFlash_Cache_Enable_Set(0xf);
    //SFlash_Cache16K_Enable_Set(0xf);
    //SFlash_Cache32K_Enable_Set(0xf);

    if(bootImgCfg[0].cacheEnable){
        if((bootImgCfg[0].entryPoint&0xFF000000)==BLSP_BOOT2_XIP_BASE){
            SF_Ctrl_Set_Flash_Image_Offset(bootImgCfg[0].imgStart.flashOffset);
            SFlash_Cache_Read_Enable(flashCfg,SF_CTRL_QIO_MODE,contRead,bootImgCfg[0].cacheWayDisable);
            //SF_Ctrl_Set_Other_Flash_Image_Offset(bootImgCfg[0].imgStart.flashOffset);
        }else{
            //SF_Ctrl_Set_Other_Flash_Image_Offset(bootImgCfg[0].imgStart.flashOffset);
            //SFlash_Other_Cache_Read_Enable(flashCfg,SF_CTRL_QIO_MODE,contRead,bootImgCfg[0].cacheWayDisable);
            //SF_Ctrl_Set_Other_Flash_Image_Offset(bootImgCfg[0].imgStart.flashOffset);
        }
    }
    if(BLSP_Boot2_Get_Feature_Flag()==BLSP_BOOT2_CP_FLAG){
        /* For ACP case, cpu0 and cpu1 use the same entrypoint,just set
           The other one waydisable=0x0f*/
        if(bootImgCfg[1].cacheEnable){
            if((bootImgCfg[1].entryPoint&0xFF000000)==BLSP_BOOT2_XIP_BASE){
                //SFlash_Other_Cache_Read_Enable(flashCfg,SF_CTRL_QIO_MODE,contRead,bootImgCfg[1].cacheWayDisable);
            }else{
                //SFlash_Cache_Read_Enable(flashCfg,SF_CTRL_QIO_MODE,contRead,bootImgCfg[1].cacheWayDisable);
            }
        }
    }else{
        /* For normal case, just judge as cpu0 */
        if(bootImgCfg[1].cacheEnable){
            if((bootImgCfg[1].entryPoint&0xFF000000)==BLSP_BOOT2_XIP_BASE){
                //SF_Ctrl_Set_Other_Flash_Image_Offset(bootImgCfg[1].imgStart.flashOffset);
                //SFlash_Other_Cache_Read_Enable(flashCfg,SF_CTRL_QIO_MODE,contRead,bootImgCfg[1].cacheWayDisable);
            }else{
                //SF_Ctrl_Set_Flash_Image_Offset(bootImgCfg[1].imgStart.flashOffset);
                //SFlash_Cache_Read_Enable(flashCfg,SF_CTRL_QIO_MODE,contRead,bootImgCfg[1].cacheWayDisable);
            }
        }
    }

    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Check if MSP is valid
 *
 * @param  mspVal: MSP value
 *
 * @return 1 for valid and 0 for invalid
 *
*******************************************************************************/
int32_t BLSP_Is_MSP_Valid(uint32_t mspVal)
{
    if(mspVal>BL602_WRAM_BASE&&mspVal<=BL602_WRAM_END){
        return 1;
    }else if(mspVal>BL602_WRAM_REMAP0_BASE&&mspVal<=BL602_WRAM_REMAP0_END){
        return 1;
    }else if(mspVal>BL602_WRAM_REMAP1_BASE&&mspVal<=BL602_WRAM_REMAP1_END){
        return 1;
    }else if(mspVal>BL602_WRAM_REMAP2_BASE&&mspVal<=BL602_WRAM_REMAP2_END){
        return 1;
    }else if(mspVal>BL602_TCM_BASE&&mspVal<=BL602_TCM_END){
        return 1;
    }else if(mspVal>BL602_TCM_REMAP0_BASE&&mspVal<=BL602_TCM_REMAP0_END){
        return 1;
    }else if(mspVal>BL602_TCM_REMAP1_BASE&&mspVal<=BL602_TCM_REMAP1_END){
        return 1;
    }else if(mspVal>BL602_TCM_REMAP2_BASE&&mspVal<=BL602_TCM_REMAP2_END){
        return 1;
    }

    return 0;
}

/****************************************************************************//**
 * @brief  Check if PC is valid
 *
 * @param  pcVal: PC value
 *
 * @return 1 for valid and 0 for invalid
 *
*******************************************************************************/
int32_t BLSP_Is_PC_Valid(uint32_t pcVal)
{
    /* Check XIP memory */
    if(pcVal>=BL602_FLASH_XIP_BASE&&pcVal<BL602_FLASH_XIP_END){
        return 1;
    }else if(pcVal>=BL602_FLASH_XIP_REMAP0_BASE&&pcVal<BL602_FLASH_XIP_REMAP0_END){
        return 1;
    }else if(pcVal>=BL602_FLASH_XIP_REMAP1_BASE&&pcVal<BL602_FLASH_XIP_REMAP1_END){
        return 1;
    }else if(pcVal>=BL602_FLASH_XIP_REMAP2_BASE&&pcVal<BL602_FLASH_XIP_REMAP2_END){
        return 1;
    }

    /* Check RAM memory */
    if(pcVal>=BL602_WRAM_BASE&&pcVal<BL602_WRAM_END){
        return 1;
    }else if(pcVal>=BL602_WRAM_REMAP0_BASE&&pcVal<BL602_WRAM_REMAP0_END){
        return 1;
    }else if(pcVal>=BL602_WRAM_REMAP1_BASE&&pcVal<BL602_WRAM_REMAP1_END){
        return 1;
    }else if(pcVal>=BL602_WRAM_REMAP2_BASE&&pcVal<BL602_WRAM_REMAP2_END){
        return 1;
    }else if(pcVal>=BL602_TCM_BASE&&pcVal<BL602_TCM_END){
        return 1;
    }else if(pcVal>=BL602_TCM_REMAP0_BASE&&pcVal<BL602_TCM_REMAP0_END){
        return 1;
    }else if(pcVal>=BL602_TCM_REMAP1_BASE&&pcVal<BL602_TCM_REMAP1_END){
        return 1;
    }else if(pcVal>=BL602_TCM_REMAP2_BASE&&pcVal<BL602_TCM_REMAP2_END){
        return 1;
    }

    return 0;
}

/****************************************************************************//**
 * @brief  Security boot finished
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION BLSP_Sboot_Finish(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(TZC_SEC_BASE,TZC_SEC_TZC_ROM_CTRL);

    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,TZC_SEC_TZC_SBOOT_DONE,0xf);

    BL_WR_REG(TZC_SEC_BASE,TZC_SEC_TZC_ROM_CTRL,tmpVal);
}

/****************************************************************************//**
 * @brief  Fix MSP and PC,if they are invalid
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void BLSP_Fix_Invalid_MSP_PC(void)
{
    uint32_t i=0;
    
    for(i=0;i<BFLB_BOOT2_CPU_MAX;i++){
        if(!BLSP_Is_MSP_Valid(bootImgCfg[i].mspVal)){
            bootImgCfg[i].mspVal=0;
        }
        if(!BLSP_Is_PC_Valid(bootImgCfg[i].entryPoint)){
            bootImgCfg[i].entryPoint=0;
        }
    }
}

typedef void( *pFunc )( void );
extern pFunc __Vectors[];
/****************************************************************************//**
 * @brief  Boot2 Get log tx GPIO
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint8_t  ATTR_TCM_SECTION BLSP_Boot2_Get_TX_GPIO(void)
{
    uint8_t *p=((uint8_t *)&__Vectors[9]+1);

    return *p;
}

/****************************************************************************//**
 * @brief  Boot2 Get Feature Flag
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint8_t  ATTR_TCM_SECTION BLSP_Boot2_Get_Feature_Flag(void)
{
    static uint8_t boot2Flag=0xff;
    uint8_t *p=((uint8_t *)&__Vectors[10]+0);
    
    if(boot2Flag==0xff){
        boot2Flag=*p;
    }
    return boot2Flag;
}

/****************************************************************************//**
 * @brief  Boot2 Get log disable Flag
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint8_t ATTR_TCM_SECTION BLSP_Boot2_Get_Log_Disable_Flag(void)
{
    uint8_t *p=((uint8_t *)&__Vectors[10]+1);
    
    return *p;
}

/****************************************************************************//**
 * @brief  Boot2 Get 8M Flash support Flag
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint8_t ATTR_TCM_SECTION BLSP_Boot2_8M_Support_Flag(void)
{
    uint8_t *p=((uint8_t *)&__Vectors[10]+2);
    
    return *p;
}

/****************************************************************************//**
 * @brief  Boot2 Get dump critical data flag
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint8_t ATTR_TCM_SECTION BLSP_Boot2_Dump_Critical_Flag(void)
{
    uint8_t *p=((uint8_t *)&__Vectors[10]+3);

    return *p;
}

/****************************************************************************//**
 * @brief  Boot2 Get Baudrate
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint32_t ATTR_TCM_SECTION BLSP_Boot2_Get_Baudrate(void)
{
    uint32_t *p=((uint32_t *)&__Vectors[13]);

    return *p;
}

/****************************************************************************//**
 * @brief  Boot2 re-implement platform uart init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifdef _HSF_BOOT_
void bflb_platform_init_uart_debug_gpio_delete()
#else
void bflb_platform_init_uart_debug_gpio()
#endif
{
	GLB_GPIO_Cfg_Type cfg;
    
    uint8_t gpio=BLSP_Boot2_Get_TX_GPIO();

	cfg.drive=0;
	cfg.smtCtrl=1;

	/*set GPIO as UART0 TX */
	cfg.gpioPin=GLB_GPIO_PIN_0+(GLB_GPIO_Type)(gpio);
	cfg.gpioFun=7;
	cfg.gpioMode=GPIO_MODE_OUTPUT;
	cfg.pullType=GPIO_PULL_UP;
	GLB_GPIO_Init(&cfg);

	/* select uart gpio function */
	GLB_UART_Fun_Sel((GLB_UART_SIG_Type)(GLB_UART_SIG_0+(gpio%8)),GLB_UART_SIG_FUN_UART0_TXD);
}

/****************************************************************************//**
 * @brief  Boot2 re-implement platform uart deinit
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void bflb_platform_deinit_uart_debug_gpio()
{
	GLB_GPIO_Cfg_Type cfg;
    uint8_t gpio=BLSP_Boot2_Get_TX_GPIO();

	cfg.gpioMode=GPIO_MODE_INPUT;
	cfg.pullType=GPIO_PULL_NONE;
	cfg.drive=0;
	cfg.smtCtrl=1;

	/*set GPIO as input */
	cfg.gpioPin=GLB_GPIO_PIN_0+(GLB_GPIO_Type)(gpio);
	cfg.gpioFun=11;
	GLB_GPIO_Init(&cfg);

	/* restore uart function sel*/
	GLB_UART_Fun_Sel((GLB_UART_SIG_Type)(GLB_UART_SIG_0+(gpio%8)),
                    (GLB_UART_SIG_FUN_Type)(GLB_UART_SIG_0+(GLB_UART_SIG_Type)(gpio%12)));
}

/*@} end of group BLSP_PORT_Public_Functions */

/*@} end of group BLSP_PORT */

/*@} end of group BL606_BLSP_Boot2 */
