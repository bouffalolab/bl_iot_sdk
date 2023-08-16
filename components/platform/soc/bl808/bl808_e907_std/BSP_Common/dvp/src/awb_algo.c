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
#include <string.h>
#include "awb_algo.h"
#include "awb1_algo.h"
#include "awb2_algo.h"

static awb_func_t awb_func;

int awb_init(AWB_ALGO algo)
{
    ISP_RGB_Gain_Type rgb_gain;
    rgb_gain.r_gain = 4096;
    rgb_gain.g_gain = 4096;
    rgb_gain.b_gain = 4096;
    
    ISP_Set_AWB_Gain(&rgb_gain);
    ISP_Set_AWB2_Gain(&rgb_gain);
    ISP_Set_AWB2_State(DISABLE);
    ISP_Set_AWB_State(DISABLE);
    ISP_Set_AWB2_Gain_State(DISABLE);

    memset(&awb_func, 0, sizeof(awb_func_t));

    if (AWB_ALGO_1 == algo) {
        awb1_init(&awb_func);
    }
    else if (AWB_ALGO_2 == algo) {
        awb2_init(&awb_func);
    }
    else {
        MSG("awb algo %d not support!\r\n", (int)algo);
        return -1;
    }

    return 0;
}

int awb_config(awb_config_t *config, bool is_virtual_sensor)
{
    if ( NULL == awb_func.config) {
        return -1;
    }

    return awb_func.config(config, is_virtual_sensor);
}

int awb_control(void)
{
    if ( NULL == awb_func.control) {
        return -1;
    }

    return awb_func.control();
}

int awb_get_info(awb_info_t **awb_info)
{
    if ( NULL == awb_func.get_info) {
        return -1;
    }

    return awb_func.get_info(awb_info);
}

int awb_set_mode(AWB_MODE mode)
{
    if ( NULL == awb_func.set_mode) {
        return -1;
    }

    return awb_func.set_mode(mode);
}

int awb_get_mode(AWB_MODE *mode)
{
    if ( NULL == awb_func.get_mode) {
        return -1;
    }

    return awb_func.get_mode(mode);
}

int awb_set_gain(ISP_RGB_Gain_Type *rgb_gain)
{
    if ( NULL == awb_func.set_gain) {
        return -1;
    }

    return awb_func.set_gain(rgb_gain);
}

int awb_get_gain(ISP_RGB_Gain_Type *rgb_gain)
{
    if ( NULL == awb_func.get_gain) {
        return -1;
    }

    return awb_func.get_gain(rgb_gain);
}

int awb_set_color_temp(BL_COLOR_TEMP color_temp)
{
    if ( NULL == awb_func.set_color_temp) {
        return -1;
    }

    return awb_func.set_color_temp(color_temp);
}

int awb_get_color_temp(BL_COLOR_TEMP *color_temp)
{
    if ( NULL == awb_func.get_color_temp) {
        return -1;
    }

    return awb_func.get_color_temp(color_temp);
}




