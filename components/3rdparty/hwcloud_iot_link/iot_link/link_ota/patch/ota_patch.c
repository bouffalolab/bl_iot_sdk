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

/**
 * @brief: we will do the img upgraded including the diff or full mode
 *         we hope you could do the img binded first
 * */
#include <stdio.h>
#include <osal.h>
#include <ota_img.h>
#include <ota_flag.h>
#include <ota_patch.h>
#include "libHDiffPatch/HPatch/patch.h"
#include "decompress_plugin_demo.h"

#define CONFIG_IMGDOWNLOAD_OFFSET 32
static hpatch_BOOL stream_downloadread(const hpatch_TStreamInput *stream, hpatch_StreamPos_t read_pos,
        uint8_t * data, uint8_t * data_end)
{
    if(ota_img_read((en_ota_type_t)(uintptr_t)stream->streamImport,EN_OTA_IMG_DOWNLOAD,(int) read_pos+CONFIG_IMGDOWNLOAD_OFFSET,data, (int)(uintptr_t) (data_end - data)) == 0)
    {
        return hpatch_TRUE;
    }
    else
    {
        return hpatch_FALSE;
    }
}

static void stream_downloadinit(hpatch_TStreamInput *stream , int size, en_ota_type_t otatype)
{
    stream->streamSize = (hpatch_StreamPos_t)size;
    stream->read = stream_downloadread;
    stream->streamImport = (void*)(uintptr_t)(otatype);

}

static hpatch_BOOL stream_backupread(const hpatch_TStreamInput *stream, hpatch_StreamPos_t read_pos,
        uint8_t * data, uint8_t * data_end)
{
    if(ota_img_read((en_ota_type_t)(uintptr_t)stream->streamImport,EN_OTA_IMG_BACKUP,(int) read_pos,data, (int)(uintptr_t) (data_end - data)) == 0)
    {
        return hpatch_TRUE;
    }
    else
    {
        return hpatch_FALSE;
    }
}

static void stream_backupinit(hpatch_TStreamInput *stream, int size,en_ota_type_t otatype)
{
    stream->streamSize = (hpatch_StreamPos_t)size;
    stream->read = stream_backupread;
    stream->streamImport = (void*)(uintptr_t)(otatype);
}


static hpatch_BOOL stream_runningwrite(const hpatch_TStreamOutput *stream, hpatch_StreamPos_t write_pos,
        const unsigned char* data, const unsigned char* data_end)
{
    if(ota_img_write((en_ota_type_t)(uintptr_t)stream->streamImport,EN_OTA_IMG_RUNNING,(int) write_pos,(const void *)data, (int)(uintptr_t) (data_end - data)) == 0)
    {
        return hpatch_TRUE;
    }
    else
    {
        return hpatch_FALSE;
    }
}

static hpatch_BOOL stream_runningread(const hpatch_TStreamOutput *stream, hpatch_StreamPos_t read_pos,
        uint8_t * data, uint8_t * data_end)
{
    if(0 == ota_img_read((en_ota_type_t)(uintptr_t)stream->streamImport,EN_OTA_IMG_RUNNING,(int) read_pos,data, (int)(uintptr_t) (data_end - data)))
    {
        return hpatch_TRUE;
    }
    else
    {
        return hpatch_FALSE;
    }
}

static void stream_runninginit(hpatch_TStreamOutput *stream, int size,en_ota_type_t otatype)
{
    stream->streamSize = (hpatch_StreamPos_t)size;
    stream->read_writed = stream_runningread;
    stream->write = stream_runningwrite;
    stream->streamImport = (void*)(uintptr_t)(otatype);
}

hpatch_BOOL getDecompressPlugin(const hpatch_compressedDiffInfo* diffInfo,
                                       hpatch_TDecompress** out_decompressPlugin)
{
    hpatch_TDecompress*  decompressPlugin=0;
    if (strlen(diffInfo->compressType)>0){
        if ((!decompressPlugin)&&lzmaDecompressPlugin.is_can_open(diffInfo->compressType))
            decompressPlugin=&lzmaDecompressPlugin;

        if (!decompressPlugin){
            if (diffInfo->compressedCount>0){
                return hpatch_FALSE; //error
            }else{
                if (strlen(diffInfo->compressType)>0)
                    printf("  diffFile added useless compress tag \"%s\"\n",diffInfo->compressType);
                decompressPlugin=0;
            }
        }else{
            printf("hpatchz run with decompress plugin: \"%s\" (need decompress %d)\n",
            diffInfo->compressType,diffInfo->compressedCount);
        }
    }
    *out_decompressPlugin=decompressPlugin;
    return hpatch_TRUE;
}

#define CN_OTACACHE_SIZE  (hpatch_kStreamCacheSize * 4)
static uint8_t  g_otacache_mem[CN_OTACACHE_SIZE];

en_ota_err_t ota_patch(en_ota_type_t otatype, int download_filesize)
{
    en_ota_err_t ret = EN_OTA_ERR_UNKNOWN;
    int  img_size;
    hpatch_compressedDiffInfo diff_info;
    hpatch_TDecompress*  decompress_plugin = 0;
    hpatch_TStreamInput  download_img_stream;
    hpatch_TStreamInput  backup_img_stream;
    hpatch_TStreamOutput running_img_stream;

    if (0 != ota_img_read(otatype,EN_OTA_IMG_DOWNLOAD,CONFIG_IMGDOWNLOAD_OFFSET,g_otacache_mem,CN_OTACACHE_SIZE))
    {
        ret = EN_OTA_ERR_NODOWNLOADIMG;
        goto EXIT;
    }

    if(hpatch_TRUE != getCompressedDiffInfo_mem(&diff_info, g_otacache_mem , g_otacache_mem + CN_OTACACHE_SIZE))
    {
        ret = EN_OTA_ERR_PATCHHEAD;
        goto EXIT;
    }

    LINK_LOG_DEBUG("new img size:%d, old img size:%d\n", (int)diff_info.newDataSize, (int)diff_info.oldDataSize);
    if(hpatch_TRUE != getDecompressPlugin(&diff_info, &decompress_plugin))
    {
        ret = EN_OTA_ERR_DECOMPRESSMETHOD;
        goto EXIT;
    }
    ///< check if the data size matched
    if((0 != ota_img_size(otatype, EN_OTA_IMG_BACKUP,&img_size)) || ((int)diff_info.oldDataSize >  img_size))
    {
        ret = EN_OTA_ERR_BACKUPIMGSIZE;
        goto EXIT;
    }

    if((0 != ota_img_size(otatype, EN_OTA_IMG_DOWNLOAD,&img_size)) || ((int)diff_info.newDataSize >  img_size))
    {
        ret = EN_OTA_ERR_DOWNLOADIMGSIZE;
        goto EXIT;
    }

    if((0 != ota_img_size(otatype, EN_OTA_IMG_RUNNING,&img_size)) || ((int)diff_info.newDataSize >  img_size))
    {
        ret = EN_OTA_ERR_RUNNINGIMGSIZE;
        goto EXIT;
    }

    ///< now we do the running erase
    if ( 0 != ota_img_erase(otatype, EN_OTA_IMG_RUNNING))
    {
        ret = EN_OTA_ERR_RUNNINGERASE;
        goto EXIT;
    }
    ///< now do th stream initialize
    stream_runninginit(&running_img_stream,(int)diff_info.newDataSize, otatype);
    stream_backupinit(&backup_img_stream,(int)diff_info.oldDataSize, otatype);
    stream_downloadinit(&download_img_stream,download_filesize -CONFIG_IMGDOWNLOAD_OFFSET, otatype);

    if (patch_decompress_with_cache(&running_img_stream, &backup_img_stream, &download_img_stream,
            decompress_plugin,  g_otacache_mem , g_otacache_mem + CN_OTACACHE_SIZE) != hpatch_TRUE)
    {
        ret = EN_OTA_ERR_PATCH;
        goto EXIT;
    }
    ret = EN_OTA_SUCCESS;

EXIT:
    return ret;
}

///< which you could use this function to do a img backUP:move the running to the backup
en_ota_err_t ota_backup(en_ota_type_t  otatype)
{
    en_ota_err_t ret = EN_OTA_ERR_UNKNOWN;
    int size_left;
    int movelen;
    int offset = 0;

    if(0 != ota_img_size(otatype, EN_OTA_IMG_RUNNING, &size_left))
    {
        ret = EN_OTA_ERR_NORUNNINGIMG;
        goto EXIT;
    }

    if(0 != ota_img_erase(otatype, EN_OTA_IMG_BACKUP))
    {
        ret = EN_OTA_ERR_RUNNINGERASE;
        goto EXIT;
    }

    while(size_left > 0)
    {
        movelen = size_left > CN_OTACACHE_SIZE ?CN_OTACACHE_SIZE:size_left;
        if(ota_img_read(otatype,EN_OTA_IMG_RUNNING,offset,g_otacache_mem, movelen) != 0)
        {
            ret = EN_OTA_ERR_RUNNNINGREAD;
            goto EXIT;
        }
        if(ota_img_write(otatype,EN_OTA_IMG_BACKUP,offset,g_otacache_mem, movelen) != 0)
        {
            ret = EN_OTA_ERR_BACKUPWRITE;
            goto EXIT;
        }
        offset += movelen;
        size_left -= movelen;
    }

    if( 0 != ota_img_flush(otatype,EN_OTA_IMG_BACKUP))
    {
        ret = EN_OTA_ERR_BACKUPFLUSH;
        goto EXIT;
    }
    ret = EN_OTA_SUCCESS;
EXIT:
    return ret;
}

///< which you could use this fucntion to do a img recover
en_ota_err_t ota_recover(en_ota_type_t  otatype)
{
    en_ota_err_t ret = EN_OTA_ERR_UNKNOWN;
    int size_left;
    int movelen;
    int offset = 0;

    if(0 != ota_img_size(otatype, EN_OTA_IMG_RUNNING, &size_left))
    {
        ret = EN_OTA_ERR_NORUNNINGIMG;
        goto EXIT;
    }

    if(0 != ota_img_erase(otatype, EN_OTA_IMG_RUNNING))
    {
        ret = EN_OTA_ERR_RUNNINGERASE;
        goto EXIT;
    }

    while(size_left > 0)
    {
        movelen = size_left > CN_OTACACHE_SIZE ?CN_OTACACHE_SIZE:size_left;
        if(ota_img_read(otatype,EN_OTA_IMG_BACKUP,offset,g_otacache_mem, movelen) != 0)
        {
            ret = EN_OTA_ERR_BACKUPREAD;
            goto EXIT;
        }
        if(ota_img_write(otatype,EN_OTA_IMG_RUNNING,offset,g_otacache_mem, movelen) != 0)
        {
            ret = EN_OTA_ERR_RUNNINGWRITE;
            goto EXIT;
        }
        offset += movelen;
        size_left -= movelen;
    }

    if( 0 != ota_img_flush(otatype,EN_OTA_IMG_RUNNING))
    {
        ret = EN_OTA_ERR_RUNNINGFLUSH;
        goto EXIT;
    }
    ret = EN_OTA_SUCCESS;
EXIT:
    return ret;
}

