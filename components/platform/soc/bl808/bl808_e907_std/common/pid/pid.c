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

#include "pid.h"

void pid_init(pid_alg_t *pid)
{
    pid->set_val = 0.0f;
    pid->out_val = 0.0f;

    pid->last_error = 0.0f;
    pid->prev_error = 0.0f;

    pid->kp = 3.0f;
    pid->ki = 0.0f;
    pid->kd = 0.0f;

    pid->i_error = 0.0f;
    pid->sum_error = 0.0f;

    pid->max_val = 32;
    pid->min_val = -32;
}

// standard pid
float standard_pid_cal(pid_alg_t *pid, float next_val)
{
    pid->set_val = next_val;
    pid->i_error = pid->set_val - pid->out_val;
    pid->sum_error += pid->i_error;
    pid->out_val = pid->kp * pid->i_error + pid->ki * pid->sum_error + pid->kd * (pid->i_error - pid->last_error);
    pid->last_error = pid->i_error;

    return pid->out_val;
}

// increment pid
float increment_pid_cal(pid_alg_t *pid, float next_val)
{
    pid->set_val = next_val;
    pid->i_error = pid->set_val - pid->out_val;
    float increment = pid->kp * (pid->i_error - pid->prev_error) + pid->ki * pid->i_error + pid->kd * (pid->i_error - 2 * pid->prev_error + pid->last_error);
    pid->out_val += increment;
    pid->last_error = pid->prev_error;
    pid->prev_error = pid->i_error;

    return pid->out_val;
}
