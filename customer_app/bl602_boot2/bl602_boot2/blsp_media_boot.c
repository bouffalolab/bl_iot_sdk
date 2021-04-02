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

#include "stdint.h"
#include "string.h"
#include "blsp_port.h"
#include "bflb_platform.h"
#include "blsp_bootinfo.h"
#include "blsp_common.h"
#include "blsp_boot_parser.h"
#include "blsp_media_boot.h"
#include "softcrc.h"

/** @addtogroup  BL606_BLSP_Boot2
 *  @{
 */

/** @addtogroup  BLSP_MEDIA_BOOT
 *  @{
 */

/** @defgroup  BLSP_MEDIA_BOOT_Private_Macros
 *  @{
 */

/*@} end of group BLSP_MEDIA_BOOT_Private_Macros */

/** @defgroup  BLSP_MEDIA_BOOT_Private_Types
 *  @{
 */

/*@} end of group BLSP_MEDIA_BOOT_Private_Types */

/** @defgroup  BLSP_MEDIA_BOOT_Private_Variables
 *  @{
 */

/*@} end of group BLSP_MEDIA_BOOT_Private_Variables */

/** @defgroup  BLSP_MEDIA_BOOT_Global_Variables
 *  @{
 */
extern SEC_Eng_SHA256_Ctx shaCtx;

/*@} end of group BLSP_MEDIA_BOOT_Global_Variables */

/** @defgroup  BLSP_MEDIA_BOOT_Private_Fun_Declaration
 *  @{
 */

/*@} end of group BLSP_MEDIA_BOOT_Private_Fun_Declaration */

/** @defgroup  BLSP_MEDIA_BOOT_Private_Functions_User_Define
 *  @{
 */

/*@} end of group BLSP_MEDIA_BOOT_Private_Functions_User_Define */

/** @defgroup  BLSP_MEDIA_BOOT_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Media boot calculate hash
 *
 * @param  startAddr: Start address to calculate
 * @param  totalLen: Data length to calculate
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
static int32_t BLSP_MediaBot_Cal_Hash(uint32_t startAddr,uint32_t totalLen)
{
    int32_t dealLen=0;
    int32_t readLen=0;
    uint32_t addr=startAddr;
    int32_t ret;
    uint32_t dumpCnt=0;
    
    while(dealLen<totalLen){

        readLen=totalLen-dealLen;
        if(readLen>BFLB_BOOT2_READBUF_SIZE){
            readLen=BFLB_BOOT2_READBUF_SIZE;
        }
        
        ret=BLSP_MediaBoot_Read(addr,boot2ReadBuf,readLen);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
        if(dumpCnt==0){
            if(BLSP_Boot2_Dump_Critical_Flag()){
                BLSP_Dump_Data(boot2ReadBuf,readLen);
            }
            dumpCnt=1;
        }
        /* Update hash*/
        Sec_Eng_SHA256_Update(&shaCtx,SEC_ENG_SHA_ID0,(uint8_t *)boot2ReadBuf,readLen);
        //BLSP_Dump_Data((uint8_t *)boot2ReadBuf,readLen);
        
        addr+=readLen;
        dealLen+=readLen;
    }
    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Media boot read signature
 *
 * @param  addr: Start address to read signature
 * @param  len: Signature length pointer
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
static int32_t BLSP_MediaBoot_Read_Signaure(uint32_t addr,uint32_t *len)
{
    int32_t ret=BFLB_BOOT2_SUCCESS;
    uint32_t sig_len;
    uint8_t *ptmp;
    
    /* Read signature*/
    ret=BLSP_MediaBoot_Read(addr,(uint8_t*)&sig_len,sizeof(sig_len));
    if(ret!=BFLB_BOOT2_SUCCESS){
        return ret;
    }
    addr+=sizeof(sig_len);
    if(sig_len>BFLB_BOOT2_SIGN_MAXSIZE){
        return BFLB_BOOT2_IMG_SIGNATURE_LEN_ERROR;
    }
    /* Tail 4 bytes for crc */
    ptmp=((uint8_t *)boot2ReadBuf);
    ret=BLSP_MediaBoot_Read(addr,(uint8_t *)(ptmp+sizeof(sig_len)),sig_len+4);
    if(ret!=BFLB_BOOT2_SUCCESS){
        return ret;
    }
    ARCH_MemCpy_Fast(boot2ReadBuf,&sig_len,sizeof(sig_len));
    addr+=(sig_len+4);
    *len=sig_len;
    
    return ret;
}

/****************************************************************************//**
 * @brief  Media boot parse one firmware
 *
 * @param  bootImgCfg: Boot image config pointer to hold parsed information
 * @param  bootheaderAddr: Bootheader start address
 * @param  imgAddr: Image start address
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
static int32_t BLSP_MediaBoot_Parse_One_FW(Boot_Image_Config *bootImgCfg,uint32_t bootheaderAddr,uint32_t imgAddr)
{
    uint32_t addr=bootheaderAddr;
    int32_t ret;
    uint32_t sig_len;
    
    /* Read boot header*/
    MSG_DBG("R header from %08x\r\n",addr);
    ret=BLSP_MediaBoot_Read(addr,boot2ReadBuf,sizeof(Boot_Header_Config));
    if(ret!=BFLB_BOOT2_SUCCESS){
        return ret;
    }
    if(BLSP_Boot2_Dump_Critical_Flag()){
        BLSP_Dump_Data(boot2ReadBuf,sizeof(Boot_Header_Config));
    }
    
    addr+=sizeof(Boot_Header_Config);
    ret=BLSP_Boot_Parse_BootHeader(bootImgCfg,(uint8_t *)boot2ReadBuf);
    if(ret!=BFLB_BOOT2_SUCCESS){
        return ret;
    }
    /* Due to OTA, the flashOffset is changed, so copy from partition info */
    bootImgCfg->imgStart.flashOffset=imgAddr;
    
    /* If sign enable,get pk key and signature*/
    if(bootImgCfg->signType){
        /* Read public key */
        MSG_DBG("R PK\r\n");
        ret=BLSP_MediaBoot_Read(addr,boot2ReadBuf,sizeof(Boot_PK_Config));
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
        if(BLSP_Boot2_Dump_Critical_Flag()){
            BLSP_Dump_Data(boot2ReadBuf,sizeof(Boot_PK_Config));
        }
        addr+=sizeof(Boot_PK_Config);
        ret=BLSP_Boot_Parse_PKey(bootImgCfg,(uint8_t *)boot2ReadBuf,1);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }     
        /* Read public key 2*/
        MSG_DBG("R PK2\r\n");
        ret=BLSP_MediaBoot_Read(addr,boot2ReadBuf,sizeof(Boot_PK_Config));
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
        if(BLSP_Boot2_Dump_Critical_Flag()){
            BLSP_Dump_Data(boot2ReadBuf,sizeof(Boot_PK_Config));
        }
        addr+=sizeof(Boot_PK_Config);
        ret=BLSP_Boot_Parse_PKey(bootImgCfg,(uint8_t *)boot2ReadBuf,0);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
        /* Read signature*/
        MSG_DBG("R SIG1\r\n");
        BLSP_MediaBoot_Read_Signaure(addr,&sig_len);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
        if(BLSP_Boot2_Dump_Critical_Flag()){
            BLSP_Dump_Data(boot2ReadBuf,sig_len);
        }
        /*len+data+crc*/
        addr+=sizeof(sig_len);
        addr+=(sig_len+4);
        ret=BLSP_Boot_Parse_Signature(bootImgCfg,(uint8_t *)boot2ReadBuf,1);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
        
        /* Read signature2*/
        MSG_DBG("R SIG2\r\n");
        BLSP_MediaBoot_Read_Signaure(addr,&sig_len);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
        if(BLSP_Boot2_Dump_Critical_Flag()){
            BLSP_Dump_Data(boot2ReadBuf,sig_len);
        }
        /*len+data+crc*/
        addr+=sizeof(sig_len);
        addr+=(sig_len+4);
        ret=BLSP_Boot_Parse_Signature(bootImgCfg,(uint8_t *)boot2ReadBuf,0);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
    }
    
    /* If encrypt enable,get AES key*/
    if(bootImgCfg->encryptType){
        /* Read aes iv*/
        MSG_DBG("R IV\r\n");
        ret=BLSP_MediaBoot_Read(addr,boot2ReadBuf,sizeof(Boot_AES_Config));
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }        
        if(BLSP_Boot2_Dump_Critical_Flag()){
            BLSP_Dump_Data(boot2ReadBuf,sizeof(Boot_AES_Config));
        }
        addr+=sizeof(Boot_AES_Config);
        ret=BLSP_Boot_Parse_AesIv(bootImgCfg,(uint8_t *)boot2ReadBuf);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }
    }
    
    if(bootImgCfg->noSegment){
        /* Flash image */
        if(!bootImgCfg->hashIgnore){
            MSG_DBG("Cal hash\r\n");
            ret= BLSP_MediaBot_Cal_Hash(imgAddr,
                                        bootImgCfg->imgSegmentInfo.imgLen);
            if(ret!=BFLB_BOOT2_SUCCESS){
                return ret;
            }
            ret= BLSP_Boot_Parser_Check_Hash(bootImgCfg);
            if(ret!=BFLB_BOOT2_SUCCESS){
                return ret;
            }
        }
        ret=BLSP_Boot_Parser_Check_Signature(bootImgCfg);
        if(ret!=BFLB_BOOT2_SUCCESS){
            return ret;
        }               
        bootImgCfg->imgValid=1;
    }else{
        bootImgCfg->imgValid=0;
    } 
    
    return ret;
}

/*@} end of group BLSP_MEDIA_BOOT_Private_Functions */

/** @defgroup  BLSP_MEDIA_BOOT_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Media boot read data
 *
 * @param  addr: Start address to read
 * @param  data: Data buffer to hold read data
 * @param  len: Data length to read
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
int32_t ATTR_TCM_SECTION BLSP_MediaBoot_Read(uint32_t addr,uint8_t *data, uint32_t len)
{
    XIP_SFlash_Read_Via_Cache_Need_Lock(BLSP_BOOT2_XIP_BASE+addr,data,len);

    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Media boot main process
 *
 * @param  cpuBootheaderAddr[BFLB_BOOT2_CPU_MAX]: CPU bootheader address list
 * @param  cpuRollBack[BFLB_BOOT2_CPU_MAX]: CPU need roll back flag hold list
 * @param  rollBack: 1 for rollback when imge error occurs, 0 for not rollback when imge error occurs
 *
 * @return BL_Err_Type
 *
*******************************************************************************/
int32_t BLSP_MediaBoot_Main(uint32_t cpuBootheaderAddr[BFLB_BOOT2_CPU_MAX],uint8_t cpuRollBack[BFLB_BOOT2_CPU_MAX],uint8_t rollBack)
{
    int32_t ret;
    uint32_t i=0;
    uint32_t validImgFound=0;
    uint32_t bootHeaderAddr[BFLB_BOOT2_CPU_MAX];
    
    MSG_DBG("Media boot main\r\n");
    
    /* Reset some parameters*/
    for(i=0;i<BFLB_BOOT2_CPU_MAX;i++){
        memset(&bootImgCfg[i],0,sizeof(bootImgCfg[i]));
        bootHeaderAddr[i]=cpuBootheaderAddr[i];
        cpuRollBack[i]=0;
    }
    bootImgCfg[0].haltCPU1=0;
    
    /* Try to boot from flash */
    for(i=0;i<cpuCount;i++){
        if(bootHeaderAddr[i]==0){
            MSG_ERR("CPU %d not boot\r\n",i);
            continue;
        }
        ret=BLSP_MediaBoot_Parse_One_FW(&bootImgCfg[i],bootHeaderAddr[i],
                                        bootHeaderAddr[i]+BFLB_FW_IMG_OFFSET_AFTER_HEADER);
        if(ret!=BFLB_BOOT2_SUCCESS){
            MSG_ERR("CPU %d boot fail\r\n",i);
            cpuRollBack[i]=1;
        }else{
            validImgFound++;
        }
    }
    if(validImgFound!=cpuCount && 1==rollBack){
        /* For CP and DP, found CPU0 image is taken as correct when the other not found, others as wrong and try to rollback */
        if(bootHeaderAddr[1]==0 && validImgFound==1){
            MSG_DBG("Found One img Only\r\n");            
        }else{
            MSG_ERR("Image roll back\r\n");
            return BFLB_BOOT2_IMG_Roll_Back;
        }
    }
    if(validImgFound==0){
        MSG_ERR("no valid img found\r\n");
        return BFLB_BOOT2_IMG_ALL_INVALID_ERROR;
    }
    

    /* Get msp and pc value */
    for(i=0;i<cpuCount;i++){
        if(bootImgCfg[i].imgValid){
            if(bootImgCfg[i].entryPoint==0){
#ifdef    ARCH_ARM
                BLSP_MediaBoot_Read(bootImgCfg[i].imgStart.flashOffset,
                                        (uint8_t *)&bootImgCfg[i].mspVal,4);
                BLSP_MediaBoot_Read(bootImgCfg[i].imgStart.flashOffset+4,
                                        (uint8_t *)&bootImgCfg[i].entryPoint,4);
#endif
#ifdef    ARCH_RISCV
                bootImgCfg[i].entryPoint=bootCpuCfg[i].defaultXIPAddr;
#endif
            }
        }
    }
    if(BLSP_Boot2_Get_Feature_Flag()==BLSP_BOOT2_CP_FLAG){
        /*co-processor*/
        bootImgCfg[1].imgStart.flashOffset=bootImgCfg[0].imgStart.flashOffset;
        bootImgCfg[1].mspVal=bootImgCfg[0].mspVal;
        bootImgCfg[1].entryPoint=bootImgCfg[0].entryPoint;
        bootImgCfg[1].cacheEnable=bootImgCfg[0].cacheEnable;
        bootImgCfg[1].imgValid=1;
        bootImgCfg[1].cacheWayDisable=0xf;
    }
    MSG_DBG("%08x,%08x\r\n",bootImgCfg[0].mspVal,bootImgCfg[0].entryPoint);
    MSG_DBG("%08x,%08x\r\n",bootImgCfg[1].mspVal,bootImgCfg[1].entryPoint);
    MSG_DBG("%08x,%08x\r\n",bootImgCfg[0].imgStart.flashOffset,bootImgCfg[0].cacheWayDisable);
    MSG_DBG("%08x,%08x\r\n",bootImgCfg[1].imgStart.flashOffset,bootImgCfg[1].cacheWayDisable);
    MSG_DBG("CPU Count %d,%d\r\n",cpuCount,bootImgCfg[0].haltCPU1);
    BLSP_Boot2_Show_Timer();
    
    /* Fix invalid pc and msp */
    BLSP_Fix_Invalid_MSP_PC();   
       
    /* Prepare jump to entry*/
    BLSP_MediaBoot_Pre_Jump();
    
    /* We should never get here unless something is wrong */
    return BFLB_BOOT2_FAIL;
}

/*@} end of group BLSP_MEDIA_BOOT_Public_Functions */

/*@} end of group BLSP_MEDIA_BOOT */

/*@} end of group BL606_BLSP_Boot2 */
