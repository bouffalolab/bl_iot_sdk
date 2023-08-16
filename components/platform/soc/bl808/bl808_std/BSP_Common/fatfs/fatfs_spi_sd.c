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

#include "diskio.h"
#include "bsp_spi_sd.h"
#include "string.h"

extern const char *FR_Table[];

int sd_disk_status(void)
{
    return 0;
}
int sd_disk_initialize(void)
{
    return SD_Init(&SD_CardInfo);
}
int sd_disk_read(BYTE *buff, LBA_t sector, UINT count)
{
    return SD_ReadBlock(sector, buff, count);
}
int sd_disk_write(const BYTE *buff, LBA_t sector, UINT count)
{
    return SD_WriteBlock(sector, (BYTE *)buff, count);
}
int sd_disk_ioctl(BYTE cmd, void *buff)
{
    int result = 0;

    switch (cmd) {
        case CTRL_SYNC:
            result = RES_OK;
            break;

        case GET_SECTOR_SIZE:
            *(WORD *)buff = SD_CardInfo.CardBlockSize;
            result = RES_OK;
            break;

        case GET_BLOCK_SIZE:
            *(DWORD *)buff = SD_CardInfo.CardBlockSize;
            result = RES_OK;
            break;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = SD_CardInfo.CardCapacity / SD_CardInfo.CardBlockSize;
            result = RES_OK;
            break;

        default:
            result = RES_PARERR;
            break;
    }

    return result;
}

DSTATUS Translate_Result_Code(int result)
{
    // MSG("%s\r\n",FR_Table[result]);
    return result;
}

void fatfs_sd_driver_register(void)
{
    FATFS_DiskioDriverTypeDef sdDiskioDriver;

    memset(&sdDiskioDriver, 0, sizeof(FATFS_DiskioDriverTypeDef));

    sdDiskioDriver.MMC_disk_status = sd_disk_status;
    sdDiskioDriver.MMC_disk_initialize = sd_disk_initialize;
    sdDiskioDriver.MMC_disk_write = sd_disk_write;
    sdDiskioDriver.MMC_disk_read = sd_disk_read;
    sdDiskioDriver.MMC_disk_ioctl = sd_disk_ioctl;
    sdDiskioDriver.Translate_Result_Code = Translate_Result_Code;
    disk_driver_callback_init(&sdDiskioDriver);
}