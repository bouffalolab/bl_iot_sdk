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

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <bl_flash.h>
#include <xram_peripheral.h>
#include <xram_peri_pwm.h>
#include <xram_peri_common.h>
#include <xram_pwm_common.h>
#include <bl808_common.h>
#include <xram.h>
#include "hosal_pwm.h"

static int xram_pwm_int(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_init(&pwm) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int xram_pwm_finalize(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_finalize(&pwm) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int xram_pwm_start(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_start(&pwm) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int xram_pwm_stop(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_stop(&pwm) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

static int xram_pwm_set_duty(struct xram_pwm_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = PWM_OP_OK;

    hosal_pwm_dev_t pwm;
    pwm.port = op->port;
    pwm.config.pin = op->pin;
    pwm.config.duty_cycle = op->duty_cycle;
    pwm.config.freq = op->freq;
    if (hosal_pwm_duty_set(&pwm, op->duty_cycle) != 0)
        operation_ret = PWM_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_PWM;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return PWM_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return PWM_OP_ERR;
    }
}

void xram_pwm_operation_handle(uint32_t len)
{
    struct xram_pwm_op pwm_op;
    uint32_t bytes;

    bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &pwm_op, len);
    if (bytes == sizeof(struct xram_pwm_op)) {
        switch (pwm_op.op){
            case XRAM_PWM_INIT: {
                xram_pwm_int(&pwm_op);
                break;
               }
            case XRAM_PWM_FINALIZE: {
                xram_pwm_finalize(&pwm_op);
                break;
            }
            case XRAM_PWM_START: {
                xram_pwm_start(&pwm_op);
                break;
            }
            case XRAM_PWM_STOP: {
                xram_pwm_stop(&pwm_op);
                break;
            }
            case XRAM_PWM_SET_DUTY: {
                xram_pwm_set_duty(&pwm_op);
                break;
            }
            default: {
                printf("xram pwm operate type err.\r\n");
                break;
            }
        }
    }
}

