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
#include "misc.h"

#define PSRAM_BLOCK_SIZE 512

extern const char *FR_Table[];

int ram_disk_status(void)
{
    return 0;
}
int ram_disk_initialize(void)
{
    return RES_OK;
}
int ram_disk_read(BYTE *buff, LBA_t sector, UINT count)
{
    arch_memcpy_fast((void *)buff, (uint32_t *)(PSRAM_START_ADDR + sector * PSRAM_BLOCK_SIZE), count * PSRAM_BLOCK_SIZE);

    return 0;
}
int ram_disk_write(const BYTE *buff, LBA_t sector, UINT count)
{
    arch_memcpy_fast((uint32_t *)(PSRAM_START_ADDR + sector * PSRAM_BLOCK_SIZE), (void *)buff, count * PSRAM_BLOCK_SIZE);
    return 0;
}
int ram_disk_ioctl(BYTE cmd, void *buff)
{
    int result = 0;

    switch (cmd) {
        case CTRL_SYNC:
            result = RES_OK;
            break;

        case GET_SECTOR_SIZE:
            *(WORD *)buff = PSRAM_BLOCK_SIZE;
            result = RES_OK;
            break;

        case GET_BLOCK_SIZE:
            *(DWORD *)buff = 1;
            result = RES_OK;
            break;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = PSRAM_BLOCK_COUNT;
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

void fatfs_psram_driver_register(void)
{
    FATFS_DiskioDriverTypeDef RamDiskioDriver;

    memset(&RamDiskioDriver, 0, sizeof(FATFS_DiskioDriverTypeDef));

    RamDiskioDriver.RAM_disk_status = ram_disk_status;
    RamDiskioDriver.RAM_disk_initialize = ram_disk_initialize;
    RamDiskioDriver.RAM_disk_write = ram_disk_write;
    RamDiskioDriver.RAM_disk_read = ram_disk_read;
    RamDiskioDriver.RAM_disk_ioctl = ram_disk_ioctl;
    RamDiskioDriver.Translate_Result_Code = Translate_Result_Code;
    disk_driver_callback_init(&RamDiskioDriver);
}
