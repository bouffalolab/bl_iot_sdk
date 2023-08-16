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
#ifndef __HAL_I2C__H__
#define __HAL_I2C__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

enum i2c_index_type {
#ifdef BSP_USING_I2C0
    I2C0_INDEX,
#endif
#ifdef BSP_USING_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_I2C2
    I2C2_INDEX,
#endif
#ifdef BSP_USING_I2C3
    I2C3_INDEX,
#endif
    I2C_MAX_INDEX
};

#define I2C_WR      0x0000
#define I2C_RD      0x0001
#define I2C_RW_MASK 0x0001

#define SUB_ADDR_0BYTE 0x0010
#define SUB_ADDR_1BYTE 0x0020
#define SUB_ADDR_2BYTE 0x0040

#define I2C_HW_MODE 0
#define I2C_SW_MODE 1

typedef struct i2c_msg {
    uint8_t slaveaddr;
    uint32_t subaddr;
    uint16_t flags;
    uint16_t len;
    uint8_t *buf;
} i2c_msg_t;

typedef struct i2c_device {
    struct device parent;
    uint8_t id;
    uint8_t mode;
    uint32_t phase;
} i2c_device_t;

#define I2C_DEV(dev) ((i2c_device_t *)dev)

int i2c_register(enum i2c_index_type index, const char *name);
int i2c_transfer(struct device *dev, i2c_msg_t msgs[], uint32_t num);

#endif