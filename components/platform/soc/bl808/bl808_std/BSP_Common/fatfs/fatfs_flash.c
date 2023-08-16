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
#include "string.h"
#include "hal_flash.h"

#define FLASH_BLOCK_SIZE  4096

extern const char *FR_Table[];

int flash_disk_status(void)
{
    return 0;
}
int flash_disk_initialize(void)
{
    return RES_OK;
}
int flash_disk_read(BYTE *buff, LBA_t sector, UINT count)
{
    flash_read(FLASH_START_ADDR + sector * FLASH_BLOCK_SIZE, (uint8_t *)buff, count * FLASH_BLOCK_SIZE);
    return 0;
}
int flash_disk_write(const BYTE *buff, LBA_t sector, UINT count)
{
    flash_erase(FLASH_START_ADDR + sector * FLASH_BLOCK_SIZE, 4096);
    flash_write(FLASH_START_ADDR + sector * FLASH_BLOCK_SIZE, (uint8_t *)buff, count * FLASH_BLOCK_SIZE);
    return 0;
}
int flash_disk_ioctl(BYTE cmd, void *buff)
{
    int result = 0;

    switch (cmd) {
        case CTRL_SYNC:
            result = RES_OK;
            break;

        case GET_SECTOR_SIZE:
            *(WORD *)buff = FLASH_BLOCK_SIZE;
            result = RES_OK;
            break;

        case GET_BLOCK_SIZE:
            *(DWORD *)buff = 1;
            result = RES_OK;
            break;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = FLASH_BLOCK_COUNT;
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
    //MSG("%s\r\n", FR_Table[result]);
    return result;
}

void fatfs_flash_driver_register(void)
{
    FATFS_DiskioDriverTypeDef FlashDiskioDriver;

    memset(&FlashDiskioDriver, 0, sizeof(FATFS_DiskioDriverTypeDef));

    FlashDiskioDriver.FLASH_disk_status = flash_disk_status;
    FlashDiskioDriver.FLASH_disk_initialize = flash_disk_initialize;
    FlashDiskioDriver.FLASH_disk_write = flash_disk_write;
    FlashDiskioDriver.FLASH_disk_read = flash_disk_read;
    FlashDiskioDriver.FLASH_disk_ioctl = flash_disk_ioctl;
    FlashDiskioDriver.Translate_Result_Code = Translate_Result_Code;
    disk_driver_callback_init(&FlashDiskioDriver);
}
