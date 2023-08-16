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
#ifndef __DRV_DEVICE_H__
#define __DRV_DEVICE_H__

#include "drv_list.h"
#include "stdio.h"

#define DEVICE_NAME_MAX 20 /* max device name*/

#define DEVICE_OFLAG_DEFAULT   0x000 /* open with default  */
#define DEVICE_OFLAG_STREAM_TX 0x001 /* open with poll tx */
#define DEVICE_OFLAG_STREAM_RX 0x002 /* open with poll rx */
#define DEVICE_OFLAG_INT_TX    0x004 /* open with interrupt tx */
#define DEVICE_OFLAG_INT_RX    0x008 /* open with interrupt rx */
#define DEVICE_OFLAG_DMA_TX    0x010 /* open with dma tx */
#define DEVICE_OFLAG_DMA_RX    0x020 /* open with dma rx */

#define DEVICE_CTRL_SET_INT        0x01 /* set interrupt */
#define DEVICE_CTRL_CLR_INT        0x02 /* clear interrupt */
#define DEVICE_CTRL_GET_INT        0x03 /* get interrupt status*/
#define DEVICE_CTRL_RESUME         0x04 /* resume device */
#define DEVICE_CTRL_SUSPEND        0x05 /* suspend device */
#define DEVICE_CTRL_CONFIG         0x06 /* config device */
#define DEVICE_CTRL_GET_CONFIG     0x07 /* get device configuration */
#define DEVICE_CTRL_ATTACH_TX_DMA  0x08 /* deivce link tx dma */
#define DEVICE_CTRL_ATTACH_RX_DMA  0x09 /* deivce link rx dma */
#define DEVICE_CTRL_TX_DMA_SUSPEND 0x0a /* deivce suspend tx dma */
#define DEVICE_CTRL_RX_DMA_SUSPEND 0x0b /* deivce suspend rx dma */
#define DEVICE_CTRL_TX_DMA_RESUME  0x0c /* deivce resume tx dma */
#define DEVICE_CTRL_RX_DMA_RESUME  0x0d /* deivce resume rx dma */
#define DEVICE_CTRL_RESVD1         0x0E
#define DEVICE_CTRL_RESVD2         0x0F

/*
 * POSIX Error codes
 */

#define DEVICE_EOK      0
#define DEVICE_EFAULT   14 /* Bad address */
#define DEVICE_EEXIST   17 /* device exists */
#define DEVICE_ENODEV   19 /* No such device */
#define DEVICE_EINVAL   22 /* Invalid argument */
#define DEVICE_ENOSPACE 23 /* No more Device for Allocate */

#define __ASSERT_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)

#define __ASSERT_LOC(test)                          \
    __ASSERT_PRINT("ASSERTION FAIL [%s] @ %s:%d\n", \
                   #test,                           \
                   __FILE__, __LINE__)

#define DEVICE_ASSERT(test, fmt, ...)           \
    do {                                        \
        if (!(test)) {                          \
            __ASSERT_LOC(test);                 \
            __ASSERT_PRINT(fmt, ##__VA_ARGS__); \
        }                                       \
    } while (0)

enum device_class_type {
    DEVICE_CLASS_NONE = 0,
    DEVICE_CLASS_GPIO,
    DEVICE_CLASS_UART,
    DEVICE_CLASS_SPI,
    DEVICE_CLASS_I2C,
    DEVICE_CLASS_ADC,
    DEVICE_CLASS_DAC,
    DEVICE_CLASS_DMA,
    DEVICE_CLASS_TIMER,
    DEVICE_CLASS_PWM,
    DEVICE_CLASS_QDEC,
    DEVICE_CLASS_SDIO,
    DEVICE_CLASS_USB,
    DEVICE_CLASS_RMII,
    DEVICE_CLASS_I2S,
    DEVICE_CLASS_CAMERA,
    DEVICE_CLASS_SEC_HASH,
    DEVICE_CLASS_KEYSCAN,
};

enum device_status_type {
    DEVICE_UNREGISTER = 0,
    DEVICE_REGISTERED,
    DEVICE_OPENED,
    DEVICE_CLOSED
};

struct device {
    char name[DEVICE_NAME_MAX];     /*name of device */
    dlist_t list;                   /*list node of device */
    enum device_status_type status; /*status of device */
    enum device_class_type type;    /*type of device */
    uint16_t oflag;                 /*oflag of device */

    int (*open)(struct device *dev, uint16_t oflag);
    int (*close)(struct device *dev);
    int (*control)(struct device *dev, int cmd, void *args);
    int (*write)(struct device *dev, uint32_t pos, const void *buffer, uint32_t size);
    int (*read)(struct device *dev, uint32_t pos, void *buffer, uint32_t size);
    void (*callback)(struct device *dev, void *args, uint32_t size, uint32_t event);
    void *handle;
};

int device_register(struct device *dev, const char *name);
int device_unregister(const char *name);
struct device *device_find(const char *name);
int device_open(struct device *dev, uint16_t oflag);
int device_close(struct device *dev);
int device_control(struct device *dev, int cmd, void *args);
int device_write(struct device *dev, uint32_t pos, const void *buffer, uint32_t size);
int device_read(struct device *dev, uint32_t pos, void *buffer, uint32_t size);
int device_set_callback(struct device *dev, void (*callback)(struct device *dev, void *args, uint32_t size, uint32_t event));
dlist_t *device_get_list_header(void);
#endif