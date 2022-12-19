/*
 * Copyright (c) 2016-2022 Bouffalolab.
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

#ifdef TOUCH_I2C_GT911

#include "hal_i2c.h"
#include "gt911_i2c.h"

struct device *touch_gt911_i2c = NULL;

static int gt911_i2c_peripheral_init(void)
{
    i2c_register(I2C0_INDEX, "touch_gt911_i2c");
    touch_gt911_i2c = device_find("touch_gt911_i2c");

    if (touch_gt911_i2c) {
        I2C_DEV(touch_gt911_i2c)->mode = I2C_HW_MODE;
        I2C_DEV(touch_gt911_i2c)->phase = 1;
        device_open(touch_gt911_i2c, 0);
    } else {
        MSG("i2c register error\r\n");
        return -1;
    }
    return 0;
}

static int gt911_i2c_read_byte(uint16_t register_addr, uint8_t *data_buf, uint16_t len)
{
    static i2c_msg_t msg = {
        .slaveaddr = GT911_I2C_SLAVE_ADDR,
        .flags = SUB_ADDR_2BYTE | I2C_RD,
    };

    msg.subaddr = register_addr;
    msg.buf = data_buf;
    msg.len = len;

    return i2c_transfer(touch_gt911_i2c, &msg, 1);
}

static int gt911_i2c_write_byte(uint16_t register_addr, uint8_t *data_buf, uint16_t len)
{
    static i2c_msg_t msg = {
        .slaveaddr = GT911_I2C_SLAVE_ADDR,
        .flags = SUB_ADDR_2BYTE | I2C_WR,
    };

    msg.subaddr = register_addr;
    msg.buf = data_buf;
    msg.len = len;

    return i2c_transfer(touch_gt911_i2c, &msg, 1);
}

int gt911_i2c_get_gesture_id()
{
    uint8_t data_buf = 0;

    if (gt911_i2c_read_byte(GT911_READ_XY_REG, &data_buf, 1)) {
        return -1;
    }

    return data_buf;
}

int gt911_i2c_init(touch_coord_t *max_value)
{
    uint8_t data_buf[5] = { 0 };
    uint32_t product_id = 0;
    uint16_t x_max = 0, y_max = 0;

    gt911_i2c_peripheral_init();

    if (gt911_i2c_read_byte(GT911_PRODUCT_ID_REG, data_buf, 4)) {
        MSG("touch i2c read error\r\n");
        return -1;
    }
    product_id = BL_RDWD_FRM_BYTEP(data_buf);
    MSG("Touch Product ID: 0x%08x\r\n", product_id);

    if (product_id == GT911_PRODUCT_ID) {
#if 0
        data_buf[0] = 0;
        data_buf[1] = (uint8_t)(max_value->coord_x << 8);
        data_buf[2] = (uint8_t)(max_value->coord_x);
        data_buf[3] = (uint8_t)(max_value->coord_y << 8);
        data_buf[4] = (uint8_t)(max_value->coord_y);

        if (gt911_i2c_write_byte(GT911_CONFIG_REG, data_buf, 5)) {
            return -1;
        }

        if (gt911_i2c_write_byte(GT911_CONFIG_REG + (0x0005 << 8), (void *)g_gt911_cfg_params + 5, (sizeof(g_gt911_cfg_params) / sizeof(g_gt911_cfg_params[0]) - 5))) {
            return -1;
        }
#else
        if (gt911_i2c_write_byte(GT911_CONFIG_REG, (void *)g_gt911_cfg_params, (sizeof(g_gt911_cfg_params) / sizeof(g_gt911_cfg_params[0])))) {
            return -1;
        }
#endif

    } else {
        MSG("Touch Product ID read fail!\r\n");
        return -1;
    }

    if (gt911_i2c_read_byte(GT911_FIRMWARE_VERSION_REG, data_buf, 2)) {
        return -1;
    }
    MSG("Touch Firmware Version: 0x%04x\r\n", data_buf);

    if (gt911_i2c_read_byte(GT911_X_RESOLUTION, data_buf, 4)) {
        return -1;
    }
    x_max = (((uint16_t)data_buf[1] << 8) | data_buf[0]);
    y_max = (((uint16_t)data_buf[3] << 8) | data_buf[2]);

    MSG("Touch Resolution %dx%d \r\n", x_max, y_max);

    return 0;
}

int gt911_i2c_read(uint8_t *point_num, touch_coord_t *touch_coord, uint8_t max_num)
{
    uint8_t data_buf[8 * GT911_I2C_MAX_POINT] = { 0 };
    uint8_t read_num;

    *point_num = 0;

    if (point_num == NULL || touch_coord == NULL || max_num == 0) {
        return -1;
    }

    if (gt911_i2c_read_byte(GT911_READ_XY_REG, data_buf, 1)) {
        return -1;
    }

    /* no touch */
    if (data_buf[0] == 0) {
        return 0;
    }

    if (data_buf[0] > GT911_I2C_MAX_POINT) {
        data_buf[0] = GT911_I2C_MAX_POINT;
    }

    read_num = (data_buf[0] > max_num) ? max_num : data_buf[0];

    /* read gt911 reg */
    gt911_i2c_read_byte(GT911_READ_XY_REG, data_buf, (8 * read_num));

    /* get point coordinates */
    for (uint8_t i = 0; i < read_num; i++) {
        uint8_t *p_data = &data_buf[i * 8];
        touch_coord[i].coord_x = (uint16_t)p_data[3] << 8 | p_data[2];
        touch_coord[i].coord_y = (uint16_t)p_data[5] << 8 | p_data[4];
    }

    *point_num = read_num;

    data_buf[0] = 0;
    gt911_i2c_write_byte(GT911_READ_XY_REG, data_buf, 1);

    return 0;
}

#endif
