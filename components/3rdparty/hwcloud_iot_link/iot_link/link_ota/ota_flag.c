/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/


#include <string.h>
#include <crc.h>
#include <link_log.h>
#include <ota_flag.h>

typedef struct
{
    ota_flag_t flag[EN_OTA_TYPE_LAST];
}ota_flag_cb_t;

#ifndef CONFIG_SOTA_VERSION
#define CONFIG_SOTA_VERSION  "SOTAV1.0"
#endif

#ifndef CONFIG_FOTA_VERSION
#define CONFIG_FOTA_VERSION  "FOTAV1.0"
#endif


int ota_flag_save(en_ota_type_t  otatype, ota_flag_t *flag)
{
    int ret = -1;

    if(otatype < EN_OTA_TYPE_LAST)
    {
        flag->crc = calc_crc32(0,&flag->info, sizeof(flag->info));
        ota_img_erase(otatype,EN_OTA_IMG_FLAG);
        ret = ota_img_write(otatype,EN_OTA_IMG_FLAG,0,flag,sizeof(ota_flag_t));
        ota_img_flush(otatype,EN_OTA_IMG_FLAG);
    }

    return ret;
}

int ota_flag_get(en_ota_type_t  otatype,ota_flag_t *flag)
{
    int ret = -1;
    uint32_t    crc;
    if((NULL != flag) && (otatype < EN_OTA_TYPE_LAST))
    {
        if(0 != ota_img_read(EN_OTA_TYPE_FOTA,EN_OTA_IMG_FLAG,0,flag,sizeof(ota_flag_t)))
        {
            LINK_LOG_ERROR("FLAG READ ERROR");
            goto EXIT;
        }
        crc = calc_crc32(0,&flag->info, sizeof(flag->info));
        if(crc != flag->crc)
        {
            LINK_LOG_ERROR("FLAG DESTROYED--CRC ERR");
            goto EXIT;
        }
        ret = 0;
    }
EXIT:
    return ret;
}





