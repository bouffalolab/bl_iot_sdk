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

typedef struct
{
    const ota_img_t  *ota[EN_OTA_TYPE_LAST][EN_OTA_IMG_LAST];
}ota_img_cb_t;
static ota_img_cb_t  g_img_cb_t;


int ota_img_bind(en_ota_type_t otatype, const ota_img_t *img)
{
    int ret = -1;
    if ((NULL != img)&&(otatype < EN_OTA_TYPE_LAST) && (img->type  < EN_OTA_IMG_LAST) )
    {
        g_img_cb_t.ota[otatype][img->type] = img;
        ret = 0;
    }
    return ret;
}


int ota_img_read(en_ota_type_t otatype, en_ota_img_type_t imgtype,int offset, void *buf, int len)
{
    int ret = -1;
    const ota_img_t *img;
    if((otatype < EN_OTA_TYPE_LAST) && (imgtype  < EN_OTA_IMG_LAST) && (NULL != g_img_cb_t.ota[otatype][imgtype]))
    {
        img = g_img_cb_t.ota[otatype][imgtype];
        if(NULL != img->opt.read)
        {
            ret = img->opt.read(img->arg,offset, buf, len);
        }
    }

    return ret;
}

int ota_img_write(en_ota_type_t otatype, en_ota_img_type_t imgtype,int offset,const void *buf, int len)
{
    int ret = -1;
    const ota_img_t *img;
    if((otatype < EN_OTA_TYPE_LAST) && (imgtype  < EN_OTA_IMG_LAST) && (NULL != g_img_cb_t.ota[otatype][imgtype]))
    {
        img = g_img_cb_t.ota[otatype][imgtype];
        if(NULL != img->opt.write)
        {
            ret = img->opt.write(img->arg,offset, buf, len);
        }
    }
    return ret;
}

int ota_img_erase(en_ota_type_t otatype, en_ota_img_type_t imgtype)
{
    int ret = -1;
    const ota_img_t *img;
    if((otatype < EN_OTA_TYPE_LAST) && (imgtype  < EN_OTA_IMG_LAST) && (NULL != g_img_cb_t.ota[otatype][imgtype]))
    {
        img = g_img_cb_t.ota[otatype][imgtype];
        if(NULL != img->opt.erase)
        {
            ret = img->opt.erase(img->arg,img->size);
        }
    }
    return ret;
}

int ota_img_flush(en_ota_type_t otatype, en_ota_img_type_t imgtype)
{
    int ret = -1;
    const ota_img_t *img;
    if((otatype < EN_OTA_TYPE_LAST) && (imgtype  < EN_OTA_IMG_LAST) && (NULL != g_img_cb_t.ota[otatype][imgtype]))
    {
        img = g_img_cb_t.ota[otatype][imgtype];
        if(NULL != img->opt.flush)
        {
            ret = img->opt.flush(img->arg,img->size);
        }
    }
    return ret;
}

int ota_img_size(en_ota_type_t otatype, en_ota_img_type_t imgtype, int *size)
{
    int ret = -1;
    const ota_img_t *img;
    if((otatype < EN_OTA_TYPE_LAST) && (imgtype  < EN_OTA_IMG_LAST) && (NULL != g_img_cb_t.ota[otatype][imgtype]))
    {
        img = g_img_cb_t.ota[otatype][imgtype];
        *size = img->size;
        ret = 0;
    }
    return ret;
}






