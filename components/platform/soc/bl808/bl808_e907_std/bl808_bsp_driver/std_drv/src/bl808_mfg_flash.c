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
#include "bl808_mfg_flash.h"
#include "softcrc.h"

static rf_para_flash_t  rf_para;
static uint32_t rf_para_addr=0;
static SPI_Flash_Cfg_Type *pFlashCfg;

//#define RF_PARA_MAGIC_FLAG      0x41504652
#define RF_PARA_MAGIC_FLAG      0x41
#define RF_PARA_VALID_FLAG      0x5A
#define RF_PARA_PART_NAME       "rf_para"


//PtTable_Stuff_Config ptTableStuff[2];
//PtTable_Entry_Config ptEntry={0};


static BL_Err_Type PtTable_Flash_Read (uint32_t addr,uint8_t *data, uint32_t len)
{
    //XIP_SFlash_Read_Need_Lock_Ext(pFlashCfg,addr,data,len);
    return SUCCESS;
}

int8_t mfg_flash_init( SPI_Flash_Cfg_Type *flashCfg)
{
#if 0
    PtTable_ID_Type activeID;
    PtTable_Error_Type ret;

    pFlashCfg=flashCfg;
    if(pFlashCfg!=NULL){
        PtTable_Set_Flash_Operation(NULL,NULL,PtTable_Flash_Read);
        activeID=PtTable_Get_Active_Partition_Need_Lock(ptTableStuff);
        if(PT_TABLE_ID_INVALID==activeID){
            //mfg_print("No valid PT\r\n");
            return -1;
        }
        ret=PtTable_Get_Active_Entries_By_Name(&ptTableStuff[activeID],(uint8_t*)RF_PARA_PART_NAME,&ptEntry);
        if(PT_ERROR_SUCCESS==ret){
            rf_para_addr=ptEntry.Address[0];
            //mfg_print("RF para flash address=%08x\r\n",(unsigned int)rf_para_addr);
            return 0;
        }else{
            //mfg_print("Not found "RF_PARA_PART_NAME"\r\n");
            return -1;
        }
    }
#endif    
    return -1;
}

static int8_t mfg_flash_program(void)
{
#if 0
    BL_Err_Type ret;

    //mfg_print("mfg_flash_write\r\n");

     ret=XIP_SFlash_Erase_Need_Lock_Ext(pFlashCfg,rf_para_addr,rf_para_addr+15);
     if(ret!=SUCCESS){
         //mfg_print("Flash erase error\r\n");
         return -1;
     }

     ret=XIP_SFlash_Write_Need_Lock_Ext(pFlashCfg,rf_para_addr,(uint8_t *)&rf_para,sizeof(rf_para));
     if(ret!=SUCCESS){
         //mfg_print("Flash write error\r\n");
         return -1;
     }
#endif
     return 0;
}

static int8_t mfg_flash_read(void)
{
#if 0
    BL_Err_Type ret;

    //mfg_print("mfg_flash_read\r\n");

     ret=XIP_SFlash_Read_Need_Lock_Ext(pFlashCfg,rf_para_addr,(uint8_t *)&rf_para,sizeof(rf_para));
     if(ret!=SUCCESS){
         //mfg_print("Flash write error\r\n");
         return -1;
     }
#endif
     return 0;
}

int8_t mfg_flash_write_xtal_capcode_pre(uint8_t capcode,uint8_t program)
{
#if 0
    rf_para.magic=RF_PARA_MAGIC_FLAG;
    rf_para.capcode_valid=RF_PARA_VALID_FLAG;
    rf_para.capcode=capcode;
    rf_para.crc32=BFLB_Soft_CRC32(&rf_para.capcode_valid,sizeof(rf_para)-8);

    if(program){
        return mfg_flash_program();
    }else{
        return 0;
    }
#endif
    return 0;
}

void mfg_flash_write_xtal_capcode(void)
{
    //mfg_flash_program();
}

int8_t mfg_flash_read_xtal_capcode(uint8_t *capcode,uint8_t reload)
{  
#if 0
    if((reload!=0)&&(mfg_flash_read()!=0)){
        return -1;
    }
    if(rf_para.magic==RF_PARA_MAGIC_FLAG){
        if(rf_para.crc32==(BFLB_Soft_CRC32(&rf_para.capcode_valid,sizeof(rf_para)-8))){
            if(rf_para.capcode_valid==RF_PARA_VALID_FLAG){
                *capcode=rf_para.capcode;
                return 0;
            }
        }
    }
#endif    
    return -1;
}

int8_t mfg_flash_write_poweroffset_pre(int8_t pwrOffset[14],uint8_t program)
{
#if 0
    rf_para.magic=RF_PARA_MAGIC_FLAG;
    rf_para.poweroffset_valid=RF_PARA_VALID_FLAG;
    rf_para.poweroffset[0]=pwrOffset[0];
    rf_para.poweroffset[1]=pwrOffset[6];
    rf_para.poweroffset[2]=pwrOffset[12];
    rf_para.crc32=BFLB_Soft_CRC32(&rf_para.capcode_valid,sizeof(rf_para)-8);

    if(program){
        return mfg_flash_program();
    }else{
        return 0;
    }
#endif 
    return 0;
}

void mfg_flash_write_poweroffset(void)
{
    //mfg_flash_program();
}

int8_t mfg_flash_read_poweroffset(int8_t pwrOffset[14],uint8_t reload)
{
#if 0
    int8_t pwrOffsetTmp[3];
    int32_t step=0;

    if((reload!=0)&&(mfg_flash_read()!=0)){
        return -1;
    }
    if(rf_para.magic==RF_PARA_MAGIC_FLAG){
        if(rf_para.crc32==(BFLB_Soft_CRC32(&rf_para.capcode_valid,sizeof(rf_para)-8))){
            if(rf_para.poweroffset_valid==RF_PARA_VALID_FLAG){
                memset(pwrOffset,0,14);
                pwrOffsetTmp[0]=rf_para.poweroffset[0];
                pwrOffsetTmp[1]=rf_para.poweroffset[1];
                pwrOffsetTmp[2]=rf_para.poweroffset[2];

                pwrOffset[0]=pwrOffsetTmp[0];

                step=(pwrOffsetTmp[1]-pwrOffsetTmp[0])*100/6;
                pwrOffset[1]=(step+50)/100+pwrOffsetTmp[0];
                pwrOffset[2]=(step*2+50)/100+pwrOffsetTmp[0];
                pwrOffset[3]=(step*3+50)/100+pwrOffsetTmp[0];
                pwrOffset[4]=(step*4+50)/100+pwrOffsetTmp[0];
                pwrOffset[5]=(step*5+50)/100+pwrOffsetTmp[0];

                pwrOffset[6]=pwrOffsetTmp[1];

                step=(pwrOffsetTmp[2]-pwrOffsetTmp[1])*100/6;
                pwrOffset[7]=(step+50)/100+pwrOffsetTmp[1];
                pwrOffset[8]=(step*2+50)/100+pwrOffsetTmp[1];
                pwrOffset[9]=(step*3+50)/100+pwrOffsetTmp[1];
                pwrOffset[10]=(step*4+50)/100+pwrOffsetTmp[1];
                pwrOffset[11]=(step*5+50)/100+pwrOffsetTmp[1];

                pwrOffset[12]=pwrOffsetTmp[2];

                pwrOffset[13]=(step*7+50)/100+pwrOffsetTmp[1];
                return 0;
            }
        }
    }
#endif    
    return -1;
    
}

int8_t mfg_flash_write_macaddr_pre(uint8_t mac[6],uint8_t program)
{
#if 0
    rf_para.magic=RF_PARA_MAGIC_FLAG;
    rf_para.mac_valid=RF_PARA_VALID_FLAG;
    memcpy(rf_para.mac,mac,6);
    rf_para.crc32=BFLB_Soft_CRC32(&rf_para.capcode_valid,sizeof(rf_para)-8);

    if(program){
        return mfg_flash_program();
    }else{
        return 0;
    }
#endif
    return 0;
}

void mfg_flash_write_macaddr(void)
{
    //mfg_flash_program();
}

int8_t mfg_flash_read_macaddr(uint8_t mac[6],uint8_t reload)
{
#if 0
    if((reload!=0)&&(mfg_flash_read()!=0)){
        //mfg_print("mfg_flash_read fail\r\n");
        return -1;
    }
    if(rf_para.magic==RF_PARA_MAGIC_FLAG){
        if(rf_para.crc32==(BFLB_Soft_CRC32(&rf_para.capcode_valid,sizeof(rf_para)-8))){
            if(rf_para.mac_valid==RF_PARA_VALID_FLAG){
                memcpy(mac,rf_para.mac,6);
                return 0;
            }
        }
    }
#endif    
    return -1;
}

