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



#include <ota_img.h>

static int imgerase_func(uintptr_t  arg, int imgsize)
{
    LINK_LOG_DEBUG("TEST IMG EARASE:img:%s imgsize:%d",(char *)arg, imgsize);
    return 0;
}

static int imgflush_func(uintptr_t  arg, int imgsize)
{
    LINK_LOG_DEBUG("TEST IMG FLUSH:img:%s imgsize:%d",(char *)arg, imgsize);
    return 0;
}



static int imgread_func(uintptr_t  arg, int offset, void *buf, int len)
{
    LINK_LOG_DEBUG("TEST IMG READ:img:%s offset:%d len:%d",(char *)arg, offset, len);
    return 0;
}


static int imgwrite_func(uintptr_t  arg, int offset,const void *buf, int len)
{
    LINK_LOG_DEBUG("TEST IMG WRITE:img:%s offset:%d len:%d",(char *)arg, offset, len);
    return 0;
}

static const ota_img_t  g_otaimg_flag = {
    .name = "FLAG",
    .type = EN_OTA_IMG_FLAG,
    .arg = (uintptr_t)"FLAGIMG",
    {
       .write = imgwrite_func,
       .read = imgread_func,
       .erase = imgerase_func,
       .erase = imgflush_func,
    },
};

static const ota_img_t  g_otaimg_running = {
    .name = "RUNIMG",
    .type = EN_OTA_IMG_RUNNING,
    .arg = (uintptr_t)"RUNNINGIMG",
    {
        .write = imgwrite_func,
        .read = imgread_func,
        .erase = imgerase_func,
        .flush = imgflush_func,
    },
};

static const ota_img_t  g_otaimg_backup = {
    .name =  "BACKUP",
    .type =  EN_OTA_IMG_BACKUP,
    .arg =  (uintptr_t)"BACKUPIMG",
    {
        .write = imgwrite_func,
        .read = imgread_func,
        .erase = imgerase_func,
        .flush = imgflush_func,
    },
};

static const ota_img_t  g_otaimg_download = {
    .name = "DOWNLOAD",
    .type = EN_OTA_IMG_DOWNLOAD,
    .arg = (uintptr_t)"DOWNLOADIMG",
    {
        .write = imgwrite_func,
        .read = imgread_func,
        .erase = imgerase_func,
        .flush = imgflush_func,
    },
};

__attribute__((weak)) int ota_img_init()
{
    ota_img_bind(EN_OTA_TYPE_FOTA,&g_otaimg_flag);
    ota_img_bind(EN_OTA_TYPE_SOTA,&g_otaimg_flag);

    ota_img_bind(EN_OTA_TYPE_FOTA,&g_otaimg_backup);
    ota_img_bind(EN_OTA_TYPE_SOTA,&g_otaimg_backup);

    ota_img_bind(EN_OTA_TYPE_FOTA,&g_otaimg_running);
    ota_img_bind(EN_OTA_TYPE_SOTA,&g_otaimg_running);

    ota_img_bind(EN_OTA_TYPE_FOTA,&g_otaimg_download);
    ota_img_bind(EN_OTA_TYPE_SOTA,&g_otaimg_download);

    return 0;
}

