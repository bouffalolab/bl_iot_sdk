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

#ifndef LITEOS_LAB_IOT_LINK_LINK_OTA_LOADER_OTA_UPGRADE_H_
#define LITEOS_LAB_IOT_LINK_LINK_OTA_LOADER_OTA_UPGRADE_H_

#include <ota_img.h>

typedef enum _en_ota_err_t
{
    EN_OTA_SUCCESS = 0,

    EN_OTA_ERR_UNKNOWN = 0X80,

    EN_OTA_ERR_DOWNLOADREAD,
    EN_OTA_ERR_DOWNLOADWRITE,
    EN_OTA_ERR_DOWNLOADERRASE,
    EN_OTA_ERR_DOWNLOADFLUSH,
    EN_OTA_ERR_NODOWNLOADIMG,
    EN_OTA_ERR_DOWNLOADIMGSIZE,

    EN_OTA_ERR_BACKUPREAD,
    EN_OTA_ERR_BACKUPWRITE,
    EN_OTA_ERR_BACKUPERASE,
    EN_OTA_ERR_BACKUPFLUSH,
    EN_OTA_ERR_NOBACKUPIMG,
    EN_OTA_ERR_BACKUPIMGSIZE,

    EN_OTA_ERR_RUNNNINGREAD,
    EN_OTA_ERR_RUNNINGWRITE,
    EN_OTA_ERR_RUNNINGERASE,
    EN_OTA_ERR_RUNNINGFLUSH,
    EN_OTA_ERR_NORUNNINGIMG,
    EN_OTA_ERR_RUNNINGIMGSIZE,

    EN_OTA_ERR_DECOMPRESSMETHOD,
    EN_OTA_ERR_PATCHHEAD,
    EN_OTA_ERR_PATCH,
}en_ota_err_t;


en_ota_err_t ota_patch(en_ota_type_t otatype, int download_filesize);
en_ota_err_t ota_backup(en_ota_type_t  otatype);
en_ota_err_t ota_recover(en_ota_type_t  otatype);


#endif /* LITEOS_LAB_IOT_LINK_LINK_OTA_LOADER_OTA_UPGRADE_H_ */
