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

#ifndef LITEOS_LAB_IOT_LINK_LINK_OTA_OTA_IMG_H_
#define LITEOS_LAB_IOT_LINK_LINK_OTA_OTA_IMG_H_

#include <stdint.h>
#include <stddef.h>
#include <link_log.h>

typedef enum
{
    EN_OTA_IMG_RUNNING = 0,
    EN_OTA_IMG_DOWNLOAD,
    EN_OTA_IMG_BACKUP,
    EN_OTA_IMG_FLAG,
    EN_OTA_IMG_LAST,
}en_ota_img_type_t;

///< these functions return 0 for success or -1 failed
///< arg, registed in the ota_img_t
///< offset, from where to read or set
///< buf, data to write fromr or read to
///< len, how much data to read or write
typedef int (*fn_ota_imgwrite) (uintptr_t arg,int offset, const void *buf, int len);  ///< call this function will write the new bin to the storage
typedef int (*fn_ota_imgread) (uintptr_t arg, int offset, void *buf, int len);         ///< call this function will read the new bin from the storage
typedef int (*fn_ota_imgerase)(uintptr_t arg, int imgsize);   ///< erase the file, we only call this function once before we write the img, we means erase the whole img
typedef int (*fn_ota_imgflush)(uintptr_t arg, int imgsize);   ///< after the write, we call this function to flush all the data to the file

typedef struct
{
    fn_ota_imgwrite  write;
    fn_ota_imgread   read;
    fn_ota_imgerase  erase;
    fn_ota_imgflush  flush;
}ota_img_opts_t;;

typedef struct
{
    const char        *name;
    int                size;    ///< the imge could storage how much data
    en_ota_img_type_t  type;    ///< defined as en_ota_img_type_t
    uintptr_t          arg;     ///< you could use this in the read write erase function, defined as the img
    ota_img_opts_t     opt;     ///< the img operator
}ota_img_t;

typedef enum
{
    EN_OTA_TYPE_FOTA = 0,
    EN_OTA_TYPE_SOTA,
    EN_OTA_TYPE_LAST,
}en_ota_type_t;

///< the bsp developer should call this function in the ota_img_imp function, and
///< ota_img_imp is a weak function ,which will called by the ota modules
int ota_img_bind(en_ota_type_t otatype, const ota_img_t *img);
///< this is a weak function , and the user should develop this function
int ota_img_init();
///< the ota components will call the following functions to read.write the data to the images
int ota_img_read(en_ota_type_t otatype, en_ota_img_type_t imgtype,int offset, void *buf, int len);
int ota_img_write(en_ota_type_t otatype, en_ota_img_type_t imgtype,int offset, const void *buf, int len);
int ota_img_erase(en_ota_type_t otatype, en_ota_img_type_t imgtype);
int ota_img_flush(en_ota_type_t otatype, en_ota_img_type_t imgtype);
int ota_img_size(en_ota_type_t otatype, en_ota_img_type_t imgtype, int *size);





#endif /* LITEOS_LAB_IOT_LINK_LINK_OTA_OTA_IMG_H_ */
