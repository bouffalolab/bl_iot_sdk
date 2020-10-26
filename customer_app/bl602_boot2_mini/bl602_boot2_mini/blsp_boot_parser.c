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

#include "blsp_common.h"
#include "bflb_platform.h"
#include "blsp_bootinfo.h"
#include "blsp_boot_parser.h"
#include "softcrc.h"
#include "blsp_port.h"

/** @addtogroup  BL606_BLSP_Boot2
 *  @{
 */

/** @addtogroup  BLSP_BOOT_PARSER
 *  @{
 */

/** @defgroup  BLSP_BOOT_PARSER_Private_Macros
 *  @{
 */

/*@} end of group BLSP_BOOT_PARSER_Private_Macros */

/** @defgroup  BLSP_BOOT_PARSER_Private_Types
 *  @{
 */

/*@} end of group BLSP_BOOT_PARSER_Private_Types */

/** @defgroup  BLSP_BOOT_PARSER_Private_Variables
 *  @{
 */
static uint32_t shaTmpBuf[16] __attribute__((section(".system_ram")));
static uint32_t padding[16] __attribute__((section(".system_ram")));
SEC_Eng_SHA256_Ctx shaCtx;

/*@} end of group BLSP_BOOT_PARSER_Private_Variables */

/** @defgroup  BLSP_BOOT_PARSER_Global_Variables
 *  @{
 */

/*@} end of group BLSP_BOOT_PARSER_Global_Variables */

/** @defgroup  BLSP_BOOT_PARSER_Private_Fun_Declaration
 *  @{
 */

/*@} end of group BLSP_BOOT_PARSER_Private_Fun_Declaration */

/** @defgroup  BLSP_BOOT_PARSER_Private_Functions_User_Define
 *  @{
 */

/*@} end of group BLSP_BOOT_PARSER_Private_Functions_User_Define */

/** @defgroup  BLSP_BOOT_PARSER_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Check if the input public key is the same as  burned in the efuse
 *
 * @param  cpuType: CPU Type
 * @param  pkhash: Public key hash pointer
 *
 * @return 1 for valid and 0 for invalid
 *
*******************************************************************************/
static uint32_t BLSP_Boot_Parse_Is_PKHash_Valid(uint8_t cpuType,uint8_t *pkhash)
{    
    if(cpuType==BFLB_BOOT2_CPU_0){
        if(0==memcmp(efuseCfg.pkHashCpu0,pkhash,BFLB_BOOT2_PK_HASH_SIZE)){
            return 1;
        }
    }else if(cpuType==BFLB_BOOT2_CPU_1){
        if(0==memcmp(efuseCfg.pkHashCpu1,pkhash,BFLB_BOOT2_PK_HASH_SIZE)){
            return 1;
        }
    }
    
    return 0;
}

/*@} end of group BLSP_BOOT_PARSER_Private_Functions */

/** @defgroup  BLSP_BOOT_PARSER_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Check if the input public key is the same as  burned in the efuse
 *
 * @param  bootImgCfg: Boot image config pointer
 * @param  data: Image data pointer
 *
 * @return Boot_Error_Code type
 *
*******************************************************************************/
int32_t BLSP_Boot_Parse_BootHeader(Boot_Image_Config *bootImgCfg,uint8_t *data)
{
    Boot_Header_Config *header=(Boot_Header_Config *)data;
    uint32_t crc;
    uint32_t crcPass=0;
    uint32_t i=0;
    uint32_t *phash=(uint32_t *)header->hash;
        
    if(header->bootCfg.bval.crcIgnore==1&&header->crc32==BFLB_BOOT2_DEADBEEF_VAL){
        MSG_WAR("Crc ignored\r\n");
        crcPass=1;
    }else{
        crc=BFLB_Soft_CRC32((uint8_t *)header,sizeof(Boot_Header_Config)-sizeof(header->crc32));
        if(header->crc32==crc){
            crcPass=1;
        }
    }
    if(crcPass){
        if(header->bootCfg.bval.notLoadInBoot){
            return BFLB_BOOT2_IMG_BOOTHEADER_NOT_LOAD_ERROR;
        }
        
        /* Get which CPU's img it is*/
        for(i=0;i<BFLB_BOOT2_CPU_MAX;i++){
            if(0==memcmp((void *)&header->magicCode,BFLB_BOOT2_CPU0_MAGIC,
                sizeof(header->magicCode))){
                break;
            }else if(0==memcmp((void *)&header->magicCode,BFLB_BOOT2_CPU1_MAGIC,
                sizeof(header->magicCode))){
                break;
            }
        }
        
        if(i==BFLB_BOOT2_CPU_MAX){
            /* No cpu img magic match */
            MSG_ERR("Magic code error\r\n");
            return BFLB_BOOT2_IMG_BOOTHEADER_MAGIC_ERROR;
        }
        
        bootImgCfg->cpuType=i;        
        bootImgCfg->entryPoint=0;
        /* Set image valid 0 as default */
        bootImgCfg->imgValid=0;
        
        /* Deal with pll config */

        /* Encrypt and sign */
        bootImgCfg->encryptType=header->bootCfg.bval.encryptType;
        bootImgCfg->signType=header->bootCfg.bval.sign;
        bootImgCfg->keySel=header->bootCfg.bval.keySel;
                
        /* Xip relative */
        bootImgCfg->noSegment=header->bootCfg.bval.noSegment;
        bootImgCfg->cacheEnable=header->bootCfg.bval.cacheEnable;
        bootImgCfg->aesRegionLock=header->bootCfg.bval.aesRegionLock;
        bootImgCfg->haltCPU1=header->bootCfg.bval.haltCPU1;
        bootImgCfg->cacheWayDisable=header->bootCfg.bval.cacheWayDisable;
        bootImgCfg->hashIgnore=header->bootCfg.bval.hashIgnore;
        
        /* Firmware len*/
        bootImgCfg->imgSegmentInfo.imgLen=header->imgSegmentInfo.imgLen;
        
        /* Boot entry and flash offset */
        bootImgCfg->entryPoint=header->bootEntry; 
        bootImgCfg->imgStart.flashOffset=header->imgStart.flashOffset;

        MSG_DBG("sign %d,encrypt:%d\r\n",bootImgCfg->signType,
                            bootImgCfg->encryptType);
                            
        /* Check encrypt and sign match*/
        if(efuseCfg.encrypted[i]!=0){
            if(bootImgCfg->encryptType==0){
                MSG_ERR("Encrypt not fit\r\n");
                return BFLB_BOOT2_IMG_BOOTHEADER_ENCRYPT_NOTFIT;
            }
        }
        
        if(efuseCfg.sign[i]^bootImgCfg->signType){
            MSG_ERR("sign not fit\r\n");
            bootImgCfg->signType=efuseCfg.sign[i];
            return BFLB_BOOT2_IMG_BOOTHEADER_SIGN_NOTFIT;
        }
                
        if(psMode==BFLB_PSM_HBN && (!efuseCfg.hbnCheckSign)){
            /* In HBN Mode, if user select to ignore hash and sign*/
            bootImgCfg->hashIgnore=1;
        }else if((bootImgCfg->hashIgnore==1&& *phash!=BFLB_BOOT2_DEADBEEF_VAL)||
            efuseCfg.sign[i]!=0 ){
            /* If signed or user not really want to ignore, hash can't be ignored*/
            bootImgCfg->hashIgnore=0;
        }  

        ARCH_MemCpy_Fast(bootImgCfg->imgHash,header->hash,sizeof(header->hash));
        
        if(bootImgCfg->imgSegmentInfo.imgLen==0){
            return BFLB_BOOT2_IMG_SEGMENT_CNT_ERROR;
        }
        
        /* Start hash here*/
        Sec_Eng_SHA256_Init(&shaCtx,SEC_ENG_SHA_ID0,SEC_ENG_SHA256, shaTmpBuf,padding);
        Sec_Eng_SHA_Start(SEC_ENG_SHA_ID0);

    }else{
        MSG_ERR("bootheader crc error\r\n");
        BLSP_Dump_Data((uint8_t *)&crc,4);
        return BFLB_BOOT2_IMG_BOOTHEADER_CRC_ERROR;
    }

    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Parse public key
 *
 * @param  bootImgCfg: Boot image config pointer
 * @param  data: Public key data pointer
 * @param  own: 1 for current CPU, 0 for other(s)
 *
 * @return Boot_Error_Code type
 *
*******************************************************************************/
int32_t BLSP_Boot_Parse_PKey(Boot_Image_Config *bootImgCfg,uint8_t *data,uint8_t own)
{
    Boot_PK_Config *cfg=(Boot_PK_Config*)data;    
    uint32_t pk_hash[BFLB_BOOT2_PK_HASH_SIZE/4];
    
    if(cfg->crc32==BFLB_Soft_CRC32((uint8_t*)cfg,sizeof(Boot_PK_Config)-4)){

        /* Check public key with data info in OTP*/
        Sec_Eng_SHA256_Update(&shaCtx,SEC_ENG_SHA_ID0,data,BFLB_BOOT2_ECC_KEYXSIZE+BFLB_BOOT2_ECC_KEYYSIZE);
        Sec_Eng_SHA256_Finish(&shaCtx,SEC_ENG_SHA_ID0,(uint8_t *)pk_hash);
        
        Sec_Eng_SHA256_Init(&shaCtx,SEC_ENG_SHA_ID0,SEC_ENG_SHA256, shaTmpBuf,padding);
        Sec_Eng_SHA_Start(SEC_ENG_SHA_ID0);
        
        /* Check pk is valid */
        if(own==1){
            if(1!=BLSP_Boot_Parse_Is_PKHash_Valid(bootImgCfg->cpuType,
                                                    (uint8_t *)pk_hash)){
                MSG_ERR("PK sha error\r\n");
                return BFLB_BOOT2_IMG_PK_HASH_ERROR;
            }
        }
        if(own==1){
            ARCH_MemCpy_Fast(bootImgCfg->ecKeyX,cfg->ecKeyX,sizeof(cfg->ecKeyX));
            ARCH_MemCpy_Fast(bootImgCfg->ecKeyY,cfg->ecKeyY,sizeof(cfg->ecKeyY));
        }
     }else{
        MSG_ERR("PK crc error\r\n");
        return BFLB_BOOT2_IMG_PK_CRC_ERROR;
    }

    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Parse signature
 *
 * @param  bootImgCfg: Boot image config pointer
 * @param  data: Signature data pointer
 * @param  own: 1 for current CPU, 0 for other(s)
 *
 * @return Boot_Error_Code type
 *
*******************************************************************************/
int32_t BLSP_Boot_Parse_Signature(Boot_Image_Config *bootImgCfg,uint8_t *data,uint8_t own)
{
    Boot_Sign_Config *cfg=(Boot_Sign_Config*)data;
    uint32_t crc;
    if(cfg->sigLen>sizeof(bootImgCfg->signature)){
        return BFLB_BOOT2_IMG_SIGNATURE_LEN_ERROR;
    }
    
    /* CRC include sig_len*/
    crc=BFLB_Soft_CRC32((uint8_t *)&cfg->sigLen,cfg->sigLen+sizeof(cfg->sigLen));
    if(memcmp(&crc,&cfg->signature[cfg->sigLen],4)==0){
        if(own==1){
            ARCH_MemCpy_Fast(bootImgCfg->signature,cfg->signature,cfg->sigLen);
            bootImgCfg->sigLen=cfg->sigLen;
        }else{
            ARCH_MemCpy_Fast(bootImgCfg->signature2,cfg->signature,cfg->sigLen);
            bootImgCfg->sigLen2=cfg->sigLen;
        }
    }else{
        MSG_ERR("SIG crc error\r\n");
        return BFLB_BOOT2_IMG_SIGNATURE_CRC_ERROR;
    }

    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Parse ASE IV
 *
 * @param  bootImgCfg: Boot image config pointer
 * @param  data: AES IV data pointer
 *
 * @return Boot_Error_Code type
 *
*******************************************************************************/
int32_t BLSP_Boot_Parse_AesIv(Boot_Image_Config *bootImgCfg,uint8_t *data)
{
    Boot_AES_Config *cfg=(Boot_AES_Config *)data;

    if(cfg->crc32==BFLB_Soft_CRC32(cfg->aesIV,sizeof(cfg->aesIV))){
        memcpy(bootImgCfg->aesiv,cfg->aesIV,sizeof(Boot_AES_Config));        
        /* Update image hash */
        if(!bootImgCfg->hashIgnore){
            Sec_Eng_SHA256_Update(&shaCtx,SEC_ENG_SHA_ID0,data,sizeof(Boot_AES_Config));
        }
    }else{
        MSG_ERR("AES IV crc error\r\n");
        return BFLB_BOOT2_IMG_AES_IV_CRC_ERROR;
    }

    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Check signature is valid
 *
 * @param  bootImgCfg: Boot image config pointer
 *
 * @return Boot_Error_Code type
 *
*******************************************************************************/
int32_t BLSP_Boot_Parser_Check_Signature(Boot_Image_Config *bootImgCfg)
{
    int32_t ret=0;
    
    MSG_DBG("%d,%d\r\n",psMode,efuseCfg.hbnCheckSign);
    if(psMode==BFLB_PSM_HBN&&(!efuseCfg.hbnCheckSign)){
        return BFLB_BOOT2_SUCCESS;
    }
    if(bootImgCfg->signType){
        MSG_DBG("Check sig1\r\n");
        bflb_platform_clear_time();
        BLSP_Boot2_Init_Sec_Eng_PKA();
        ret=bflb_ecdsa_verify(0,(uint32_t *)bootImgCfg->imgHash,sizeof(bootImgCfg->imgHash),
                                (uint32_t *)bootImgCfg->ecKeyX,(uint32_t *)bootImgCfg->ecKeyY,
                                (uint32_t *)bootImgCfg->signature,(uint32_t *)&bootImgCfg->signature[32]);
        if (ret!=0) {
            MSG_ERR("verify failed\n");
            return BFLB_BOOT2_IMG_SIGN_ERROR;
        }
        MSG_DBG("Time=%d ms\r\n",bflb_platform_get_time_ms());
    }
    MSG_DBG("Success\r\n");
    return BFLB_BOOT2_SUCCESS;
}

/****************************************************************************//**
 * @brief  Check hash is valid
 *
 * @param  bootImgCfg: Boot image config pointer
 *
 * @return Boot_Error_Code type
 *
*******************************************************************************/
int32_t BLSP_Boot_Parser_Check_Hash(Boot_Image_Config *bootImgCfg)
{
    uint32_t imgHashCal[BFLB_BOOT2_HASH_SIZE/4];
    
    if(!bootImgCfg->hashIgnore){
        Sec_Eng_SHA256_Finish(&shaCtx,SEC_ENG_SHA_ID0,(uint8_t *)imgHashCal);
        if(memcmp(imgHashCal,bootImgCfg->imgHash ,
          sizeof(bootImgCfg->imgHash))!=0){
            MSG_ERR("Hash error\r\n");
            BLSP_Dump_Data(imgHashCal,BFLB_BOOT2_HASH_SIZE);
            BLSP_Dump_Data(bootImgCfg->imgHash,BFLB_BOOT2_HASH_SIZE);
            return BFLB_BOOT2_IMG_HASH_ERROR;
        }else{
            MSG_DBG("Success\r\n");
        }
    }

    return BFLB_BOOT2_SUCCESS;
}

/*@} end of group BLSP_BOOT_PARSER_Public_Functions */

/*@} end of group BLSP_BOOT_PARSER */

/*@} end of group BL606_BLSP_Boot2 */
