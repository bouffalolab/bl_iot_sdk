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
#ifndef __BLSP_BOOTINFO_H__
#define __BLSP_BOOTINFO_H__

#include "stdint.h"
#include "blsp_port.h"

/** @addtogroup  BL606_BLSP_Boot2
 *  @{
 */

/** @addtogroup  BLSP_BOOTINFO
 *  @{
 */

/** @defgroup  BLSP_BOOTINFO_Public_Macros
 *  @{
 */
#define BFLB_BOOT2_CPU0_MAGIC                   "BFNP"
#define BFLB_BOOT2_CPU1_MAGIC                   "BFAP"
#define BFLB_BOOT2_FLASH_CFG_MAGIC              "FCFG"
#define BFLB_BOOT2_PLL_CFG_MAGICCODE            "PCFG"
#define BFLB_BOOT2_FLASH_TZC_MAGIC              "TCFG"
#define BFLB_BOOT2_DEADBEEF_VAL                 0xdeadbeef

#define BFLB_BOOT2_READBUF_SIZE                 4*1024
#define BFLB_FW_IMG_OFFSET_AFTER_HEADER         4*1024

/* Image owner type */
#define BFLB_BOOT2_CPU_0                        0
#define BFLB_BOOT2_CPU_1                        1
#define BFLB_BOOT2_CPU_MAX                      2
    
/* Public key hash size */  
#define BFLB_BOOT2_PK_HASH_SIZE                 256/8
#define BFLB_BOOT2_HASH_SIZE                    256/8
/* Public key type */       
#define BFLB_BOOT2_ECC_KEYXSIZE                 256/8
#define BFLB_BOOT2_ECC_KEYYSIZE                 256/8
#define BFLB_BOOT2_SIGN_MAXSIZE                 2048/8
    
/* Power save define */ 
#define BFLB_PSM_ACTIVE                         0
#define BFLB_PSM_HBN                            1

/*@} end of group BLSP_BOOTINFO_Public_Macros */

/** @defgroup  BLSP_BOOTINFO_Public_Types
 *  @{
 */
typedef  enum {
    BFLB_BOOT2_SUCCESS=0x00,

    /* Flash*/
    BFLB_BOOT2_FLASH_INIT_ERROR=0x0001,
    BFLB_BOOT2_FLASH_ERASE_PARA_ERROR=0x0002,
    BFLB_BOOT2_FLASH_ERASE_ERROR=0x0003,
    BFLB_BOOT2_FLASH_WRITE_PARA_ERROR=0x0004,
    BFLB_BOOT2_FLASH_WRITE_ADDR_ERROR=0x0005,
    BFLB_BOOT2_FLASH_WRITE_ERROR=0x0006,
    BFLB_BOOT2_FLASH_BOOT_PARA=0x0007,
    BFLB_BOOT2_FLASH_READ_ERROR=0x0008,

    /* Image*/
    BFLB_BOOT2_IMG_BOOTHEADER_LEN_ERROR=0x0201,
    BFLB_BOOT2_IMG_BOOTHEADER_NOT_LOAD_ERROR=0x0202,
    BFLB_BOOT2_IMG_BOOTHEADER_MAGIC_ERROR=0x0203,
    BFLB_BOOT2_IMG_BOOTHEADER_CRC_ERROR=0x0204,
    BFLB_BOOT2_IMG_BOOTHEADER_ENCRYPT_NOTFIT=0x0205,
    BFLB_BOOT2_IMG_BOOTHEADER_SIGN_NOTFIT=0x0206,
    BFLB_BOOT2_IMG_SEGMENT_CNT_ERROR=0x0207,
    BFLB_BOOT2_IMG_AES_IV_LEN_ERROR=0x0208,
    BFLB_BOOT2_IMG_AES_IV_CRC_ERROR=0x0209,
    BFLB_BOOT2_IMG_PK_LEN_ERROR=0x020a,
    BFLB_BOOT2_IMG_PK_CRC_ERROR=0x020b,
    BFLB_BOOT2_IMG_PK_HASH_ERROR=0x020c,
    BFLB_BOOT2_IMG_SIGNATURE_LEN_ERROR=0x020d,
    BFLB_BOOT2_IMG_SIGNATURE_CRC_ERROR=0x020e,
    BFLB_BOOT2_IMG_SECTIONHEADER_LEN_ERROR=0x020f,
    BFLB_BOOT2_IMG_SECTIONHEADER_CRC_ERROR=0x0210,
    BFLB_BOOT2_IMG_SECTIONHEADER_DST_ERROR=0x0211,
    BFLB_BOOT2_IMG_SECTIONDATA_LEN_ERROR=0x0212,
    BFLB_BOOT2_IMG_SECTIONDATA_DEC_ERROR=0x0213,
    BFLB_BOOT2_IMG_SECTIONDATA_TLEN_ERROR=0x0214,
    BFLB_BOOT2_IMG_SECTIONDATA_CRC_ERROR=0x0215,
    BFLB_BOOT2_IMG_HALFBAKED_ERROR=0x0216,
    BFLB_BOOT2_IMG_HASH_ERROR=0x0217,
    BFLB_BOOT2_IMG_SIGN_PARSE_ERROR=0x0218,
    BFLB_BOOT2_IMG_SIGN_ERROR=0x0219,
    BFLB_BOOT2_IMG_DEC_ERROR=0x021a,
    BFLB_BOOT2_IMG_ALL_INVALID_ERROR=0x021b,
    BFLB_BOOT2_IMG_Roll_Back=0x021c,

    /* MISC*/
    BFLB_BOOT2_MEM_ERROR=0xfffb,
    BFLB_BOOT2_PLL_ERROR=0xfffc,
    BFLB_BOOT2_INVASION_ERROR=0xfffd,
    BFLB_BOOT2_POLLING=0xfffe,
    BFLB_BOOT2_FAIL=0xffff,

}Boot_Error_Code;

typedef struct {
    uint8_t encrypted[BFLB_BOOT2_CPU_MAX];
    uint8_t sign[BFLB_BOOT2_CPU_MAX];
    uint8_t hbnCheckSign;
    uint8_t rsvd[3];
    uint8_t chipID[8];
    uint8_t pkHashCpu0[BFLB_BOOT2_PK_HASH_SIZE];
    uint8_t pkHashCpu1[BFLB_BOOT2_PK_HASH_SIZE];
}Boot_Efuse_HW_Config;

typedef struct {
    uint32_t magicCode;       /*'FCFG'*/
    SPI_Flash_Cfg_Type cfg;
    uint32_t crc32;
}Boot_Flash_Config;

typedef struct {
    uint8_t xtalType;
    uint8_t pllClk;
    uint8_t hclkDiv;
    uint8_t bclkDiv;
    
    uint8_t flashClkType;
    uint8_t flashClkDiv;
    uint8_t rsvd[2];
}Boot_Sys_Clk_Config;

typedef struct {
    uint32_t magicCode;       /*'PCFG'*/
    Boot_Sys_Clk_Config cfg;
    uint32_t crc32;
}Boot_Clk_Config;

typedef struct {
    uint32_t magicCode;                   /*'BFXP'*/
    uint32_t rivison; 
    Boot_Flash_Config flashCfg;       
    Boot_Clk_Config   clkCfg;
    __PACKED_UNION {
        __PACKED_STRUCT {
          uint32_t sign              :  2;   /* [1: 0]      for sign*/
          uint32_t encryptType       :  2;   /* [3: 2]      for encrypt */
          uint32_t keySel            :  2;   /* [5: 4]      for key sel in boot interface*/
          uint32_t rsvd6_7           :  2;   /* [7: 6]      for encrypt*/
          uint32_t noSegment         :  1;   /* [8]         no segment info */
          uint32_t cacheEnable       :  1;   /* [9]         for cache */
          uint32_t notLoadInBoot     :  1;   /* [10]        not load this img in bootrom */
          uint32_t aesRegionLock     :  1;   /* [11]        aes region lock */
          uint32_t cacheWayDisable   :  4;   /* [15: 12]    cache way disable info*/
          uint32_t crcIgnore         :  1;   /* [16]        ignore crc */
          uint32_t hashIgnore        :  1;   /* [17]        hash crc */
          uint32_t haltCPU1          :  1;   /* [18]        halt ap */
          uint32_t rsvd19_31         :  13;  /* [31:19]     rsvd */
        } bval;
        uint32_t wval;
    }bootCfg ;
    
    __PACKED_UNION {
        uint32_t segmentCnt;
        uint32_t imgLen;
    }imgSegmentInfo;
    
    uint32_t bootEntry;      /* entry point of the image*/
    __PACKED_UNION {
        uint32_t ramAddr;
        uint32_t flashOffset;
    }imgStart;

    uint8_t hash[BFLB_BOOT2_HASH_SIZE];    /*hash of the image*/

    uint32_t rsv1;
    uint32_t rsv2;
    uint32_t crc32;
}Boot_Header_Config;

typedef struct {
    uint8_t aesIV[16];
    uint32_t crc32;
}Boot_AES_Config;

typedef struct {
    uint8_t ecKeyX[BFLB_BOOT2_ECC_KEYXSIZE];        //ec key in boot header
    uint8_t ecKeyY[BFLB_BOOT2_ECC_KEYYSIZE];        //ec key in boot header
    uint32_t crc32;
}Boot_PK_Config;

typedef struct {
    uint32_t sigLen;
    uint8_t signature[BFLB_BOOT2_SIGN_MAXSIZE];
    uint32_t crc32;
}Boot_Sign_Config;

typedef struct {
    uint8_t encryptType;
    uint8_t signType;
    uint8_t keySel;
    uint8_t imgValid;
    
    uint8_t noSegment;
    uint8_t cacheEnable;
    uint8_t cacheWayDisable;
    uint8_t hashIgnore;
    
    uint8_t aesRegionLock;
    uint8_t haltCPU1;
    uint8_t cpuType;
    uint8_t r[1];

    __PACKED_UNION {
        uint32_t segmentCnt;
        uint32_t imgLen;
    }imgSegmentInfo;
    
    uint32_t mspVal; 
    uint32_t entryPoint;
    __PACKED_UNION {
        uint32_t ramAddr;
        uint32_t flashOffset;
    }imgStart;
    uint32_t sigLen;
    uint32_t sigLen2;

    uint32_t dealLen;
    uint32_t maxInputLen;

    uint8_t imgHash[BFLB_BOOT2_HASH_SIZE];            //hash of the whole (all)images
    uint8_t aesiv[16+4];                                //iv in boot header

    uint8_t ecKeyX[BFLB_BOOT2_ECC_KEYXSIZE];          //ec key in boot header
    uint8_t ecKeyY[BFLB_BOOT2_ECC_KEYYSIZE];          //ec key in boot header    
    uint8_t ecKeyX2[BFLB_BOOT2_ECC_KEYXSIZE];         //ec key in boot header
    uint8_t ecKeyY2[BFLB_BOOT2_ECC_KEYYSIZE];         //ec key in boot header

    uint8_t signature[BFLB_BOOT2_SIGN_MAXSIZE];       //signature in boot header
    uint8_t signature2[BFLB_BOOT2_SIGN_MAXSIZE];      //signature in boot header

}Boot_Image_Config;

typedef struct {
    uint32_t mspStoreAddr;
    uint32_t pcStoreAddr;
    uint32_t defaultXIPAddr;
}Boot_CPU_Config;

typedef  void (*pentry_t)(void );

extern Boot_CPU_Config     bootCpuCfg[2];
extern Boot_Image_Config   bootImgCfg[2];
extern Boot_Efuse_HW_Config efuseCfg;
extern SPI_Flash_Cfg_Type flashCfg;
extern uint8_t psMode;
extern uint8_t cpuCount;
extern uint8_t boot2ReadBuf[BFLB_BOOT2_READBUF_SIZE];

/*@} end of group BLSP_BOOTINFO_Public_Types */

/** @defgroup  BLSP_BOOTINFO_Public_Constants
 *  @{
 */

/*@} end of group BLSP_BOOTINFO_Public_Constants */

/** @defgroup  BLSP_BOOTINFO_Public_Functions
 *  @{
 */

/*@} end of group BLSP_BOOTINFO_Public_Functions */

/*@} end of group BLSP_BOOTINFO */

/*@} end of group BL606_BLSP_Boot2 */

#endif /* __BLSP_BOOTINFO_H__ */
