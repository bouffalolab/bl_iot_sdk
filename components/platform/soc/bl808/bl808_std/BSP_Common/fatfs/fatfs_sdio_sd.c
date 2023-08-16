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

/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"     /* Obtains integer types */
#include "diskio.h" /* Declarations of disk functions */
#include "bsp_sdio_sdcard.h"

static sd_card_t gSDCardInfo;
extern const char *FR_Table[];

int MMC_disk_status()
{
    return 0;
}

int MMC_disk_initialize()
{
    static uint8_t inited = 0;

    if (inited == 0) {
        if (SDH_Init(SDH_DATA_BUS_WIDTH_4BITS, &gSDCardInfo) == SD_OK) {
            inited = 1;
            return 0;
        } else {
            return -1;
        }
    }

    return 0;
}

int MMC_disk_read(BYTE *buff, LBA_t sector, UINT count)
{
    if (SD_OK == SDH_ReadMultiBlocks(buff, sector, gSDCardInfo.blockSize, count)) {
        return 0;
    } else {
        return -1;
    }
}

int MMC_disk_write(const BYTE *buff, LBA_t sector, UINT count)
{
    if (SD_OK == SDH_WriteMultiBlocks((uint8_t *)buff, sector, gSDCardInfo.blockSize, count)) {
        return 0;
    } else {
        return -1;
    }
}

int MMC_disk_ioctl(BYTE cmd, void *buff)
{
    switch (cmd) {
        // Get R/W sector size (WORD)
        case GET_SECTOR_SIZE:
            *(WORD *)buff = gSDCardInfo.blockSize;
            break;

        // Get erase block size in unit of sector (DWORD)
        case GET_BLOCK_SIZE:
            *(DWORD *)buff = 1;
            break;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = gSDCardInfo.blockCount;
            break;

        case CTRL_SYNC:
            break;

        default:
            break;
    }

    return 0;
}

DWORD get_fattime(void)
{
    return ((DWORD)(2015 - 1980) << 25) /* Year 2015 */
           | ((DWORD)1 << 21)           /* Month 1 */
           | ((DWORD)1 << 16)           /* Mday 1 */
           | ((DWORD)0 << 11)           /* Hour 0 */
           | ((DWORD)0 << 5)            /* Min 0 */
           | ((DWORD)0 >> 1);           /* Sec 0 */
}

DSTATUS Translate_Result_Code(int result)
{
    // MSG("%s\r\n",FR_Table[result]);
    return result;
}

void fatfs_sdio_driver_register(void)
{
    FATFS_DiskioDriverTypeDef pNewDiskioDriver;

    memset(&pNewDiskioDriver, 0, sizeof(FATFS_DiskioDriverTypeDef));

    pNewDiskioDriver.MMC_disk_status = MMC_disk_status;
    pNewDiskioDriver.MMC_disk_initialize = MMC_disk_initialize;
    pNewDiskioDriver.MMC_disk_write = MMC_disk_write;
    pNewDiskioDriver.MMC_disk_read = MMC_disk_read;
    pNewDiskioDriver.MMC_disk_ioctl = MMC_disk_ioctl;
    pNewDiskioDriver.Translate_Result_Code = Translate_Result_Code;
    disk_driver_callback_init(&pNewDiskioDriver);
}
