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

#include "bflb_platform.h"
#include "blsp_port.h"
#include "blsp_bootinfo.h"
#include "blsp_media_boot.h"
#include "partition.h"
#include "blsp_boot_decompress.h"
#include "blsp_common.h"
#include "softcrc.h"

/** @addtogroup  BL606_BLSP_Boot2
 *  @{
 */

/** @addtogroup  BLSP_BOOT2
 *  @{
 */

/** @defgroup  BLSP_BOOT2_Private_Macros
 *  @{
 */

/*@} end of group BLSP_BOOT2_Private_Macros */

/** @defgroup  BLSP_BOOT2_Private_Types
 *  @{
 */

/*@} end of group BLSP_BOOT2_Private_Types */

/** @defgroup  BLSP_BOOT2_Private_Variables
 *  @{
 */

/*@} end of group BLSP_BOOT2_Private_Variables */

/** @defgroup  BLSP_BOOT2_Global_Variables
 *  @{
 */
uint8_t boot2ReadBuf[BFLB_BOOT2_READBUF_SIZE] __attribute__((section(".system_ram")));
Boot_Image_Config   bootImgCfg[2];
Boot_CPU_Config     bootCpuCfg[2]=
{
    /*CPU0 boot cfg*/
    {
        .mspStoreAddr=0,
        .pcStoreAddr=0,
        .defaultXIPAddr=0x23000000,
    },
    /*CPU1 boot cfg*/
    {
        .mspStoreAddr=BFLB_BOOT2_CPU1_APP_MSP_ADDR,
        .pcStoreAddr=BFLB_BOOT2_CPU1_APP_PC_ADDR,
        .defaultXIPAddr=0x23000000,
    }
};
Boot_Efuse_HW_Config efuseCfg;
SPI_Flash_Cfg_Type flashCfg;
uint8_t psMode=BFLB_PSM_ACTIVE;
uint8_t cpuCount;
int32_t BLSP_Boot2_Get_Clk_Cfg(Boot_Clk_Config *cfg);
void BLSP_Boot2_Get_Efuse_Cfg(Boot_Efuse_HW_Config *efuseCfg);

/*@} end of group BLSP_BOOT2_Global_Variables */

/** @defgroup  BLSP_BOOT2_Private_Fun_Declaration
 *  @{
 */

/*@} end of group BLSP_BOOT2_Private_Fun_Declaration */

/** @defgroup  BLSP_BOOT2_Private_Functions_User_Define
 *  @{
 */

/*@} end of group BLSP_BOOT2_Private_Functions_User_Define */

/** @defgroup  BLSP_BOOT2_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Partition table erase flash function pointer
 *
 * @param  startaddr: Start address to erase
 * @param  endaddr: End address to erase
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
static BL_Err_Type PtTable_Flash_Erase (uint32_t startaddr,uint32_t endaddr)
{
    XIP_SFlash_Erase_Need_Lock(&flashCfg,startaddr,endaddr);
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Partition table write flash function pointer
 *
 * @param  addr: Start address to write
 * @param  data: Data pointer to write
 * @param  len: Data length to write
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
static BL_Err_Type PtTable_Flash_Write (uint32_t addr,uint8_t *data, uint32_t len)
{
    XIP_SFlash_Write_Need_Lock(&flashCfg,addr,data,len);
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Partition table read flash function pointer
 *
 * @param  addr: Start address to read
 * @param  data: Data pointer to read
 * @param  len: Data length to read
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
static BL_Err_Type PtTable_Flash_Read (uint32_t addr,uint8_t *data, uint32_t len)
{
    XIP_SFlash_Read_Need_Lock(&flashCfg,addr,data,len);
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Boot2 runs error call back function
 *
 * @param  log: Log to print
 *
 * @return None
 *
*******************************************************************************/
static void BLSP_Boot2_On_Error(void *log)
{
    while(1){
        MSG_ERR("%s\r\n",(char*)log);
        ARCH_Delay_MS(500);
    }
}

/****************************************************************************//**
 * @brief  Boot2 Dump partition entry
 *
 * @param  ptEntry: Partition entry pointer to dump
 *
 * @return None
 *
*******************************************************************************/
static void BLSP_Dump_PtEntry(PtTable_Entry_Config *ptEntry)
{
    MSG("Name=%s\r\n",ptEntry->name);
    MSG("Age=%d\r\n",(unsigned int)ptEntry->age);
    MSG("active Index=%d\r\n",(unsigned int)ptEntry->activeIndex);
    MSG("active Address=%08x\r\n",(unsigned int)ptEntry->Address[ptEntry->activeIndex]);
}

/****************************************************************************//**
 * @brief  Boot2 check XZ FW and do decompression
 *
 * @param  activeID: Active partition table ID
 * @param  ptStuff: Pointer of partition table stuff
 * @param  ptEntry: Pointer of active entry
 *
 * @return 1 for find XZ FW and decompress success, 0 for other cases
 *
*******************************************************************************/
static int BLSP_Boot2_Check_XZ_FW(PtTable_ID_Type activeID,PtTable_Stuff_Config *ptStuff,PtTable_Entry_Config *ptEntry)
{
    uint8_t buf[6];

    if(BFLB_BOOT2_SUCCESS!=BLSP_MediaBoot_Read(ptEntry->Address[ptEntry->activeIndex],buf,sizeof(buf))){
        MSG_ERR("Read fw fail\r\n");
        return 0;
    }
    if(BLSP_Boot2_Dump_Critical_Flag()){
        BLSP_Dump_Data(buf,sizeof(buf));
    }
    if(BLSP_Boot2_Verify_XZ_Header(buf)==1){
        MSG_DBG("XZ image\r\n");
        if(BFLB_BOOT2_SUCCESS==BLSP_Boot2_Update_Fw(activeID,ptStuff,ptEntry)){
            return 1;
        }else{
            MSG_ERR("Img decompress fail\r\n");
            /* Set flag to make it not boot */
            ptEntry->activeIndex=0;
            ptEntry->Address[0]=0;
            return 0;
        }
    }
    return 0;
}

/****************************************************************************//**
 * @brief  Boot2 copy firmware from OTA region to normal region
 *
 * @param  activeID: Active partition table ID
 * @param  ptStuff: Pointer of partition table stuff
 * @param  ptEntry: Pointer of active entry
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
static int BLSP_Boot2_Do_FW_Copy(PtTable_ID_Type activeID,PtTable_Stuff_Config *ptStuff,PtTable_Entry_Config *ptEntry)
{
    uint8_t activeIndex=ptEntry->activeIndex;
    uint32_t srcAddress=ptEntry->Address[activeIndex&0x01];
    uint32_t destAddress=ptEntry->Address[!(activeIndex&0x01)];
    uint32_t destMaxSize= ptEntry->maxLen[!(activeIndex&0x01)];
    uint32_t totalLen=ptEntry->len;
    uint32_t dealLen=0;
    uint32_t curLen=0;

    if(SUCCESS!=XIP_SFlash_Erase_Need_Lock(&flashCfg,destAddress,destAddress+destMaxSize-1)){
        MSG_ERR("Erase flash fail");
        return BFLB_BOOT2_FLASH_ERASE_ERROR;
    }

    while(dealLen<totalLen){
        curLen=totalLen-dealLen;
        if(curLen>sizeof(boot2ReadBuf)){
            curLen=sizeof(boot2ReadBuf);
        }
        if(BFLB_BOOT2_SUCCESS!=BLSP_MediaBoot_Read(srcAddress,boot2ReadBuf,curLen)){
            MSG_ERR("Read FW fail when copy\r\n");
            return BFLB_BOOT2_FLASH_READ_ERROR;
        }
        if(SUCCESS!=XIP_SFlash_Write_Need_Lock(&flashCfg,destAddress,boot2ReadBuf,curLen)){
            MSG_ERR("Write flash fail");
            return BFLB_BOOT2_FLASH_WRITE_ERROR;
        }
        srcAddress+=curLen;
        destAddress+=curLen;
        dealLen+=curLen;
    }
    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Boot2 deal with one firmware
 *
 * @param  activeID: Active partition table ID
 * @param  ptStuff: Pointer of partition table stuff
 * @param  ptEntry: Pointer of active entry
 * @param  fwName: Firmware name pointer
 * @param  type: Firmware name ID
 *
 * @return 0 for partition table changed,need re-parse,1 for partition table or entry parsed successfully
 *
*******************************************************************************/
static int BLSP_Boot2_Deal_One_FW(PtTable_ID_Type activeID,PtTable_Stuff_Config *ptStuff,
                                    PtTable_Entry_Config *ptEntry,uint8_t *fwName,
                                    PtTable_Entry_Type type)
{
    uint32_t ret;

    if(fwName!=NULL){
        MSG_DBG("Get FW:%s\r\n",fwName);
        ret=PtTable_Get_Active_Entries_By_Name(ptStuff,fwName,ptEntry);
    }else{
        MSG_DBG("Get FW ID:%d\r\n",type);
        ret=PtTable_Get_Active_Entries_By_ID(ptStuff,type,ptEntry);
    }

    if(PT_ERROR_SUCCESS!=ret){
        MSG_ERR("Entry not found\r\n");
    }else{
        BLSP_Dump_PtEntry(ptEntry);
        MSG_DBG("Check Img\r\n");
        if(BLSP_Boot2_Check_XZ_FW(activeID,ptStuff,ptEntry)==1){
            return 0;
        }
        /* Check if this partition need copy */
        if(ptEntry->activeIndex>=2){
            if(BFLB_BOOT2_SUCCESS==BLSP_Boot2_Do_FW_Copy(activeID,ptStuff,ptEntry)){
                return 0;
            }
        }
    }
    return 1;
}

/****************************************************************************//**
 * @brief  Boot2 Roll back pt entry
 *
 * @param  activeID: Active partition table ID
 * @param  ptStuff: Pointer of partition table stuff
 * @param  ptEntry: Pointer of active entry
 *
 * @return Boot_Error_Code
 *
*******************************************************************************/
#ifdef BLSP_BOOT2_ROLLBACK
static int32_t BLSP_Boot2_Rollback_PtEntry(PtTable_ID_Type activeID,PtTable_Stuff_Config *ptStuff,PtTable_Entry_Config *ptEntry)
{
    int32_t ret;

    ptEntry->activeIndex=!(ptEntry->activeIndex&0x01);
    ptEntry->age++;
    ret=PtTable_Update_Entry((PtTable_ID_Type)(!activeID),ptStuff,ptEntry);
    if(ret!=PT_ERROR_SUCCESS){
        MSG_ERR("Update PT entry fail\r\n");
        return BFLB_BOOT2_FAIL;
    }
    return BFLB_BOOT2_SUCCESS;
}
#endif

/****************************************************************************//**
 * @brief  Boot2 get mfg start up request
 *
 * @param  activeID: Active partition table ID
 * @param  ptStuff: Pointer of partition table stuff
 * @param  ptEntry: Pointer of active entry
 *
 * @return 0 for partition table changed,need re-parse,1 for partition table or entry parsed successfully
 *
*******************************************************************************/
static void BLSP_Boot2_Get_MFG_StartReq(PtTable_ID_Type activeID,PtTable_Stuff_Config *ptStuff,PtTable_Entry_Config *ptEntry,uint8_t *userFwName)
{
    uint32_t ret;
    uint32_t len=0;
    uint8_t tmp[16+1]={0};

    ret=PtTable_Get_Active_Entries_By_Name(ptStuff,(uint8_t*)"mfg",ptEntry);

    if(PT_ERROR_SUCCESS==ret){
        MSG_DBG("XIP_SFlash_Read_Need_Lock");
        XIP_SFlash_Read_Need_Lock(&flashCfg,ptEntry->Address[0]+MFG_START_REQUEST_OFFSET,tmp,sizeof(tmp)-1);
        MSG_DBG("%s",tmp);
        if(tmp[0]=='0'||tmp[0]=='1'){
            len=strlen((char*)tmp);
            if(len<9){
                ARCH_MemCpy_Fast(userFwName,tmp,len);
                MSG_DBG("%s",tmp);
            }
        }
    }else{
        MSG_DBG("MFG not found");
    }
}

/*@} end of group BLSP_BOOT2_Private_Functions */

/** @defgroup  BLSP_BOOT2_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Boot2 main function
 *
 * @param  None
 *
 * @return Return value
 *
*******************************************************************************/
int main(void)
{
    uint32_t ret=0,i=0;
    PtTable_Stuff_Config ptTableStuff[2];
    PtTable_ID_Type activeID;
    /* Init to zero incase only one cpu boot up*/
    PtTable_Entry_Config ptEntry[BFLB_BOOT2_CPU_MAX]={0};
    uint32_t bootHeaderAddr[BFLB_BOOT2_CPU_MAX]={0};
    uint8_t bootRollback[BFLB_BOOT2_CPU_MAX]={0};
    uint8_t ptParsed=1;
    uint8_t userFwName[9]={0};
#ifdef BLSP_BOOT2_ROLLBACK
    uint8_t rollBacked=0;
#endif
    uint8_t tempMode=0;
    Boot_Clk_Config clkCfg;
    uint8_t flashCfgBuf[4+sizeof(SPI_Flash_Cfg_Type)+4]={0};

    /* It's better not enable interrupt */
    //BLSP_Boot2_Init_Timer();

    /* Set RAM Max size */
    BLSP_Boot2_Disable_Other_Cache();

    /* Flush cache to get parameter */
    BLSP_Boot2_Flush_XIP_Cache();
    ret=BLSP_Boot2_Get_Clk_Cfg(&clkCfg);
    ret|=SF_Cfg_Get_Flash_Cfg_Need_Lock(0,&flashCfg);
    BLSP_Boot2_Flush_XIP_Cache();

    bflb_platform_print_set(BLSP_Boot2_Get_Log_Disable_Flag());
    bflb_platform_init(BLSP_Boot2_Get_Baudrate());
    bflb_platform_deinit_time();
    if(BLSP_Boot2_Get_Feature_Flag()==BLSP_BOOT2_CP_FLAG){
        MSG_DBG("BLSP_Boot2_CP:%s,%s\r\n",__DATE__,__TIME__);
    }else  if(BLSP_Boot2_Get_Feature_Flag()==BLSP_BOOT2_MP_FLAG){
        MSG_DBG("BLSP_Boot2_MC:%s,%s\r\n",__DATE__,__TIME__);
    }else{
        MSG_DBG("BLSP_Boot2_SP:%s,%s\r\n",__DATE__,__TIME__);
    }
#ifdef BL_SDK_VER
    MSG_DBG("SDK:%s\r\n",BL_SDK_VER);
#else
    MSG_DBG("MCU SDK:%s\r\n",MCU_SDK_VERSION);
    MSG_DBG("BSP:%s\r\n",BSP_VERSION);
#endif
	if(BLSP_Boot2_Dump_Critical_Flag()){
        BLSP_Dump_Data(&clkCfg,16);
		BLSP_Dump_Data(&flashCfg,16);
    }

    MSG_DBG("Get efuse config\r\n");
    BLSP_Boot2_Get_Efuse_Cfg(&efuseCfg);

    /* Reset Sec_Eng for using */
    BLSP_Boot2_Reset_Sec_Eng();

    if(BLSP_Boot2_Get_Feature_Flag()!=BLSP_BOOT2_SP_FLAG){
        /* Get cpu count info */
        cpuCount=BLSP_Boot2_Get_CPU_Count();
    }else{
        cpuCount=1;
    }

    /* Get power save mode */
    psMode=BLSP_Read_Power_Save_Mode();

    /* Get User specified FW */
    ARCH_MemCpy_Fast(userFwName,BLSP_Get_User_Specified_Fw(),4);
    if(BLSP_Boot2_8M_Support_Flag()){
        /* Set flash operation function, read via sbus */
        PtTable_Set_Flash_Operation(PtTable_Flash_Erase,PtTable_Flash_Write,PtTable_Flash_Read);
    }else{
        /* Set flash operation function, read via xip */
        PtTable_Set_Flash_Operation(PtTable_Flash_Erase,PtTable_Flash_Write,PtTable_Flash_Read);
    }
    while(1){
        tempMode=0;
        do{
            activeID=PtTable_Get_Active_Partition_Need_Lock(ptTableStuff);
            if(PT_TABLE_ID_INVALID==activeID){
                BLSP_Boot2_On_Error("No valid PT\r\n");
            }
            MSG_DBG("Active PT:%d,%d\r\n",activeID,ptTableStuff[activeID].ptTable.age);

            BLSP_Boot2_Get_MFG_StartReq(activeID,&ptTableStuff[activeID],&ptEntry[0],userFwName);
            /* Get entry and boot */
            if (userFwName[0]=='0'){
                ptParsed=BLSP_Boot2_Deal_One_FW(activeID,&ptTableStuff[activeID],&ptEntry[0],&userFwName[1],PT_ENTRY_FW_CPU0);
                if(ptParsed==0){
                    continue;
                }else{
                    BLSP_Clr_User_Specified_Fw();
                }
                tempMode=1;
                userFwName[0]=0;
            }else if (userFwName[0]=='1' && cpuCount>1){
                ptParsed=BLSP_Boot2_Deal_One_FW(activeID,&ptTableStuff[activeID],&ptEntry[1],&userFwName[1],PT_ENTRY_FW_CPU1);
                if(ptParsed==0){
                    continue;
                }else{
                    BLSP_Clr_User_Specified_Fw();
                }
                tempMode=1;
                userFwName[0]=0;
            }else{
                ptParsed=BLSP_Boot2_Deal_One_FW(activeID,&ptTableStuff[activeID],&ptEntry[0],NULL,PT_ENTRY_FW_CPU0);
                if(ptParsed==0){
                    continue;
                }
                if(cpuCount>1){
                    ptParsed=BLSP_Boot2_Deal_One_FW(activeID,&ptTableStuff[activeID],&ptEntry[1],NULL,PT_ENTRY_FW_CPU1);
                    if(ptParsed==0){
                        continue;
                    }
                }
            }
            ptParsed=1;
        }while(ptParsed==0);

        /* Pass data to App*/
        BLSP_Boot2_Pass_Parameter(NULL,0);
        /* Pass active partition table ID */
        BLSP_Boot2_Pass_Parameter(&activeID,4);
        /* Pass active partition table content: table header+ entries +crc32 */
        BLSP_Boot2_Pass_Parameter(&ptTableStuff[activeID],sizeof(PtTable_Config)+4+
                                    ptTableStuff[activeID].ptTable.entryCnt*sizeof(PtTable_Entry_Config));
        /* Pass flash config */
        if(ptEntry[0].Address[ptEntry[0].activeIndex]!=0){
            XIP_SFlash_Read_Via_Cache_Need_Lock(BLSP_BOOT2_XIP_BASE+ptEntry[0].Address[ptEntry[0].activeIndex]+8,flashCfgBuf,sizeof(flashCfgBuf));
            /* Include magic and CRC32 */
            BLSP_Boot2_Pass_Parameter(flashCfgBuf,sizeof(flashCfgBuf));
        }

        MSG_DBG("Boot start\r\n");
        for(i=0;i<cpuCount;i++){
            bootHeaderAddr[i]=ptEntry[i].Address[ptEntry[i].activeIndex];
        }
#ifdef BLSP_BOOT2_ROLLBACK
        /* Test mode is not need roll back */
        if(rollBacked==0 && tempMode==0){
            ret=BLSP_MediaBoot_Main(bootHeaderAddr,bootRollback,1);
        }else{
            ret=BLSP_MediaBoot_Main(bootHeaderAddr,bootRollback,0);
        }
#else
        ret=BLSP_MediaBoot_Main(bootHeaderAddr,bootRollback,0);
#endif
        /* Fail in temp mode,continue to boot normal image */
        if(tempMode==1){
            continue;
        }
#ifdef BLSP_BOOT2_ROLLBACK
        /* If rollback is done, we still fail, break */
        if(rollBacked){
            break;
        }
        MSG_DBG("Boot return %d\r\n",ret);
        MSG_WAR("Check Rollback\r\n");
        for(i=0;i<cpuCount;i++){
            if(bootRollback[i]!=0){
                MSG_WAR("Rollback %d\r\n",i);
                if(BFLB_BOOT2_SUCCESS==BLSP_Boot2_Rollback_PtEntry(activeID,&ptTableStuff[activeID],&ptEntry[i])){
                    rollBacked=1;
                }
            }
        }
        /* If need no rollback, boot fail due to other reseaon instead of imgae issue,break */
        if(rollBacked==0){
            break;
        }
#else
        break;
#endif
    }

    /* We should never get here unless boot fail */
    MSG_ERR("Media boot return %d\r\n",ret);
    while(1){
        MSG_ERR("BLSP boot2 fail\r\n");
        ARCH_Delay_MS(500);
    }
}

void bfl_main()
{
    main();
}

/*@} end of group BLSP_BOOT2_Public_Functions */

/*@} end of group BLSP_BOOT2 */

/*@} end of group BL606_BLSP_Boot2 */
