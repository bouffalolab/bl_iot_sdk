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
#include "usbh_core.h"
#include "usbh_msc.h"

struct usbh_msc *active_msc_class;

extern const char *FR_Table[];

int usb_disk_status(void)
{
    return 0;
}
int usb_disk_initialize(void)
{
    active_msc_class = (struct usbh_msc *)usbh_find_class_instance("/dev/sda");
    if (active_msc_class == NULL) {
        printf("do not find /dev/sda\r\n");
        return -1;
    }
    return RES_OK;
}
int usb_disk_read(BYTE *buff, LBA_t sector, UINT count)
{
    return usbh_msc_scsi_read10(active_msc_class, sector, buff, count);
}
int usb_disk_write(const BYTE *buff, LBA_t sector, UINT count)
{
    return usbh_msc_scsi_write10(active_msc_class, sector, buff, count);
}
int usb_disk_ioctl(BYTE cmd, void *buff)
{
    int result = 0;

    switch (cmd) {
        case CTRL_SYNC:
            result = RES_OK;
            break;

        case GET_SECTOR_SIZE:
            *(WORD *)buff = active_msc_class->blocksize;
            result = RES_OK;
            break;

        case GET_BLOCK_SIZE:
            *(DWORD *)buff = 1;
            result = RES_OK;
            break;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = active_msc_class->blocknum;
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

void fatfs_usbh_driver_register(void)
{
    FATFS_DiskioDriverTypeDef USBDiskioDriver;

    memset(&USBDiskioDriver, 0, sizeof(FATFS_DiskioDriverTypeDef));

    USBDiskioDriver.USB_disk_status = usb_disk_status;
    USBDiskioDriver.USB_disk_initialize = usb_disk_initialize;
    USBDiskioDriver.USB_disk_write = usb_disk_write;
    USBDiskioDriver.USB_disk_read = usb_disk_read;
    USBDiskioDriver.USB_disk_ioctl = usb_disk_ioctl;
    USBDiskioDriver.Translate_Result_Code = Translate_Result_Code;
    disk_driver_callback_init(&USBDiskioDriver);
}
