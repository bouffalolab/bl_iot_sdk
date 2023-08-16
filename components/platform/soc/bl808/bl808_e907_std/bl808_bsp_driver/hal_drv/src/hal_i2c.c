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
#include "hal_i2c.h"
#include "hal_gpio.h"
#include "bl808_i2c.h"
#include "bl808_glb.h"

static i2c_device_t i2cx_device[I2C_MAX_INDEX] = {
#ifdef BSP_USING_I2C0
    I2C0_CONFIG,
#endif
#ifdef BSP_USING_I2C1
    I2C1_CONFIG,
#endif
#ifdef BSP_USING_I2C2
    I2C2_CONFIG,
#endif
#ifdef BSP_USING_I2C3
    I2C3_CONFIG,
#endif
};
/**
 * @brief
 *
 * @param dev
 * @param oflag
 * @return int
 */
int i2c_open(struct device *dev, uint16_t oflag)
{
    i2c_device_t *i2c_device = (i2c_device_t *)dev;

    if (i2c_device->mode == I2C_HW_MODE) {
        I2C_SetPrd(i2c_device->id, i2c_device->phase);
    }

    return 0;
}

/**
 * @brief
 *
 * @param index
 * @param name
 * @param flag
 * @return int
 */
int i2c_register(enum i2c_index_type index, const char *name)
{
    struct device *dev;

    if (I2C_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(i2cx_device[index].parent);

    dev->open = i2c_open;
    dev->close = NULL;
    dev->control = NULL;
    dev->write = NULL;
    dev->read = NULL;

    dev->type = DEVICE_CLASS_I2C;
    dev->handle = NULL;

    return device_register(dev, name);
}
/**
 * @brief
 *
 * @param dev
 * @param msgs
 * @param num
 * @return uint32_t
 */
int i2c_transfer(struct device *dev, i2c_msg_t msgs[], uint32_t num)
{
    i2c_msg_t *msg;
    I2C_Transfer_Cfg i2cCfg = { 0 };

    i2c_device_t *i2c_device = (i2c_device_t *)dev;

    if (i2c_device->mode == I2C_HW_MODE) {
        for (uint32_t i = 0; i < num; i++) {
            msg = &msgs[i];
            i2cCfg.slaveAddr = msg->slaveaddr;
            i2cCfg.stopEveryByte = DISABLE;
            i2cCfg.subAddr = msg->subaddr;
            i2cCfg.dataSize = msg->len;
            i2cCfg.data = msg->buf;

            if (msg->flags & SUB_ADDR_0BYTE) {
                i2cCfg.subAddrSize = 0;
            } else if (msg->flags & SUB_ADDR_1BYTE) {
                i2cCfg.subAddrSize = 1;
            } else if (msg->flags & SUB_ADDR_2BYTE) {
                i2cCfg.subAddrSize = 2;
            }

            if ((msg->flags & I2C_RW_MASK) == I2C_WR) {
                return I2C_MasterSendBlocking(i2c_device->id, &i2cCfg);
            } else if ((msg->flags & I2C_RW_MASK) == I2C_RD) {
                return I2C_MasterReceiveBlocking(i2c_device->id, &i2cCfg);
            }
        }
    } else {
    }

    return 0;
}