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
#include <bl808_common.h>
#include "bl_comm_sns.h"


#undef  DEBUG_MODULE
#define DEBUG_MODULE 0

bool is_param_valid(int value, int min, int max)
{
    if (value > max || value < min) {
        return false;
    }
    return true;
}

void clip_param_range(int *value, int min, int max)
{
    if (*value > max) *value = max;
    if (*value < min) *value = min;
}

intpl_point_t create_intpl_point(int position, int value)
{
    intpl_point_t intpl_point;
    intpl_point.position = position;
    intpl_point.value = value;

    return intpl_point;
}

int linear_interpolate(intpl_point_t *point_L, intpl_point_t *point_H, int pos, int *value)
{
    if (point_H->position <= point_L->position) {
        MSG("linear_interpolate: invalid param!\r\n");
        return -1;
    }

    if (pos <= point_L->position) {
        *value = point_L->value;
    } else if (pos >= point_H->position) {
        *value = point_H->value;
    } else {
        *value = DIV_ROUND_SIGNED(
                (point_H->position - pos) * point_L->value +
                (pos - point_L->position) * point_H->value,
                point_H->position - point_L->position);
    }

    MSG("linear_interpolate: (%d, %d) ~ (%d, %d) -> (%d, %d)\r\n", point_L->position, point_L->value,
        point_H->position, point_H->value, pos, *value);

    return 0;
}

