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

#include "touch.h"

#ifdef TOUCH_CONTROLLER_FT6X36

#include "hal_i2c.h"
#include "hal_gpio.h"
#include "ft6x36_i2c.h"

struct device *touch_ft6x36_i2c = NULL;

static int ft6x06_i2c_init(void)
{
    i2c_register(I2C0_INDEX, "touch_ft6x36_i2c");
    touch_ft6x36_i2c = device_find("touch_ft6x36_i2c");

    if (touch_ft6x36_i2c) {
        I2C_DEV(touch_ft6x36_i2c)->mode = I2C_HW_MODE;
        I2C_DEV(touch_ft6x36_i2c)->phase = 1;
        device_open(touch_ft6x36_i2c, 0);
    } else {
        MSG("i2c register error\r\n");
        return -1;
    }
    return 0;
}

static int ft6x06_i2c_read(uint8_t register_addr, uint8_t *data_buf, uint16_t len)
{
    static i2c_msg_t msg = {
        .slaveaddr = FT6236_I2C_SLAVE_ADDR,
        .flags = SUB_ADDR_1BYTE | I2C_RD,
    };

    msg.subaddr = register_addr;
    msg.buf = data_buf;
    msg.len = len;

    return i2c_transfer(touch_ft6x36_i2c, &msg, 1);
}

int ft6x36_get_gesture_id()
{
    uint8_t data_buf = FT6X36_GEST_ID_NO_GESTURE;

    if (ft6x06_i2c_read(FT6X36_GEST_ID_REG, &data_buf, 1)) {
        return -1;
    }

    return data_buf;
}

int ft6x06_init(void)
{
    uint8_t data_buf;

    ft6x06_i2c_init();

    if (ft6x06_i2c_read(FT6X36_PANEL_ID_REG, &data_buf, 1)) {
        return -1;
    }
    MSG("Touch Device ID: 0x%02x\r\n", data_buf);

    if (ft6x06_i2c_read(FT6X36_CHIPSELECT_REG, &data_buf, 1)) {
        return -1;
    }
    MSG("Touch Chip ID: 0x%02x\r\n", data_buf);

    if (ft6x06_i2c_read(FT6X36_DEV_MODE_REG, &data_buf, 1)) {
        return -1;
    }
    MSG("Touch Device mode: 0x%02x\r\n", data_buf);

    if (ft6x06_i2c_read(FT6X36_FIRMWARE_ID_REG, &data_buf, 1)) {
        return -1;
    }
    MSG("Touch Firmware ID: 0x%02x\r\n", data_buf);

    if (ft6x06_i2c_read(FT6X36_RELEASECODE_REG, &data_buf, 1)) {
        return -1;
    }
    MSG("Touch Release code: 0x%02x\r\n", data_buf);

    return 0;
}

int ft6x36_read(uint8_t *point_num, touch_coord_t *touch_coord, uint8_t max_num)
{
    uint8_t data_buf[5];
    *point_num = 0;

    if (point_num == NULL || touch_coord == NULL || max_num == 0) {
        return -1;
    }

    if (ft6x06_i2c_read(FT6X36_TD_STAT_REG, &data_buf[0], 1)) {
        return -1;
    }
    data_buf[0] &= FT6X36_TD_STAT_MASK;

    /* no touch or err */
    if (data_buf[0] == 0 || data_buf[0] > 2) {
        if (data_buf[0] > 2) {
            return -2;
        } else {
            return 0;
        }
    }

    /* Get the first point */
    ft6x06_i2c_read(FT6X36_P1_XH_REG, &data_buf[1], 4);
    touch_coord[0].coord_x = (data_buf[1] & FT6X36_MSB_MASK) << 8 | (data_buf[2] & FT6X36_LSB_MASK);
    touch_coord[0].coord_y = (data_buf[3] & FT6X36_MSB_MASK) << 8 | (data_buf[4] & FT6X36_LSB_MASK);
    *point_num = 1;

    /* Get the second point */
    if (data_buf[0] > 1 && max_num > 1) {
        ft6x06_i2c_read(FT6X36_P2_XH_REG, &data_buf[1], 4);
        touch_coord[1].coord_x = (data_buf[1] & FT6X36_MSB_MASK) << 8 | (data_buf[2] & FT6X36_LSB_MASK);
        touch_coord[1].coord_y = (data_buf[3] & FT6X36_MSB_MASK) << 8 | (data_buf[4] & FT6X36_LSB_MASK);
        *point_num = 2;
    }
    return 0;
}

#endif
