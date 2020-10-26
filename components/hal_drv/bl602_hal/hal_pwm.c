/*
 * Copyright (c) 2020 Bouffalolab.
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
#include "hal_pwm.h"

#include <device/vfs_pwm.h>
#include <vfs_err.h>
#include <vfs_register.h>
#include <hal/soc/pwm.h>
#include <aos/kernel.h>

#include <bl_pwm.h>
#include <libfdt.h>

#include <utils_log.h>

#include <looprt.h>
#include <loopset_pwm.h>

#define _HAL_PWM_DUTY_ACCURACY  100
#define _HAL_PWM_DUTY_UNIT_MS   1
#define _HAL_PWM_CHAN_NUMS      5

static uint8_t __g_init_flag = 0;
static hal_pwm_dev_t __g_pwm_dev[_HAL_PWM_CHAN_NUMS] = {0};

typedef struct pwm_priv_data {
    aos_mutex_t    mutex;
} pwm_priv_data_t;

static int8_t inited;
static pwm_dev_t *dev_pwm0 = NULL;
static pwm_dev_t *dev_pwm1 = NULL;
static pwm_dev_t *dev_pwm2 = NULL;
static pwm_dev_t *dev_pwm3 = NULL;
static pwm_dev_t *dev_pwm4 = NULL;

static int pwm_dev_malloc(pwm_dev_t **pdev)
{
    if (*pdev) {
        log_error("arg err.\r\n");
        return -1;
    }

    *pdev = pvPortMalloc(sizeof(pwm_dev_t));
    if (*pdev == 0) {
        log_error("mem err.\r\n");
        return -1;
    }

    (*pdev)->priv = NULL;
    (*pdev)->priv = pvPortMalloc(sizeof(pwm_priv_data_t));
    if ((*pdev)->priv == NULL) {
        log_error("mem err.\r\n");
        return -1;
    }

    return 0;
}

static void pwm_dev_setdef(pwm_dev_t **pdev, uint8_t id)
{
    if (*pdev == NULL) {
        log_error("mem err.\r\n");
        return;
    }

    (*pdev)->port = id;
}

static int dev_pwm_init(uint8_t id, const char *path)
{
    pwm_dev_t **pdev = NULL;
    int ret;

    if ((id >= 3) || (path == 0)) {
        log_error("arg err.\r\n");
        return -1;
    }

    switch (id) {
        case 0:
        {
            pdev = &dev_pwm0;
        } break;
        case 1:
        {
            pdev = &dev_pwm1;
        } break;
        case 2:
        {
            pdev = &dev_pwm2;
        } break;
        case 3:
        {
            pdev = &dev_pwm3;
        } break;
        case 4:
        {
            pdev = &dev_pwm4;
        } break;
        default:
        {
            log_error("err.\r\n");
            return -1;
        } break;
    }

    if (pwm_dev_malloc(pdev) != 0) {
        return -1;
    }

    pwm_dev_setdef(pdev, id);
    ret = aos_register_driver(path, &pwm_ops, *pdev);
    if (ret != VFS_SUCCESS) {
        return ret;
    }

    return 0;
}

int32_t hal_pwm_init_bydev(pwm_dev_t *pwm)
{
    pwm_priv_data_t *data;

    data = pwm->priv;
    if (aos_mutex_new(&(data->mutex))) {
        /*we should assert here?*/
        return -1;
    }
    return 0;
}

int32_t hal_pwm_finalize_bydev(pwm_dev_t *pwm)
{
    pwm_priv_data_t *data;

    data = pwm->priv;
    aos_mutex_free(&(data->mutex));

    return 0;
}

#define BL_FDT32_TO_U8(addr, byte_offset)   ((uint8_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))
#define BL_FDT32_TO_U16(addr, byte_offset)  ((uint16_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))
#define BL_FDT32_TO_U32(addr, byte_offset)  ((uint32_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))
static void fdt_pwm_module_init(const void *fdt, int pwm_offset)
{
    #define PWM_MODULE_MAX 5
    //const char *path = "/dev/pwm0";
    int offset1 = 0;

    const uint32_t *addr_prop = 0;
    int lentmp = 0;
    const char *result = 0;
    int countindex = 0;
    int i;

    uint8_t id;
    char *path = NULL;
    uint8_t pin;
    uint32_t freq;

    const char *pwm_node[PWM_MODULE_MAX] = {
        "pwm@4000A420",
        "pwm@4000A440",
        "pwm@4000A460",
        "pwm@4000A480",
        "pwm@4000A4A0",
    };

    for (i = 0; i < PWM_MODULE_MAX; i++) {
        offset1 = fdt_subnode_offset(fdt, pwm_offset, pwm_node[i]);
        if (0 >= offset1) {
            log_info("pwm[%d] %s NULL.\r\n", i, pwm_node[i]);
            continue;
        }
        countindex = fdt_stringlist_count(fdt, offset1, "status");
        if (countindex != 1) {
            log_info("pwm[%d] status_countindex = %d NULL.\r\n", i, countindex);
            continue;
        }
        result = fdt_stringlist_get(fdt, offset1, "status", 0, &lentmp);
        if ((lentmp != 4) || (memcmp("okay", result, 4) != 0)) {
            log_info("pwm[%d] status = %s\r\n", i, result);
            continue;
        }

        /* set path */
        countindex = fdt_stringlist_count(fdt, offset1, "path");
        if (countindex != 1) {
            log_info("pwm[%d] path_countindex = %d NULL.\r\n", i, countindex);
            continue;
        }
        result = fdt_stringlist_get(fdt, offset1, "path", 0, &lentmp);
        if ((lentmp < 0) || (lentmp > 32))
        {
            log_info("pwm[%d] path lentmp = %d\r\n", i, lentmp);
        }
        path = (char *)result;

        /* set id */
        addr_prop = fdt_getprop(fdt, offset1, "id", &lentmp);
        if (addr_prop == NULL) {
            log_info("pwm[%d] id NULL.\r\n", i);
            continue;
        }
        id = BL_FDT32_TO_U8(addr_prop, 0);

        /* set pin */
        addr_prop = fdt_getprop(fdt, offset1, "pin", &lentmp);
        if (addr_prop == NULL) {
            log_info("pwm[%d] pin NULL.\r\n", i);
            continue;
        }
        pin = BL_FDT32_TO_U8(addr_prop, 0);

        /* set freq */
        addr_prop = fdt_getprop(fdt, offset1, "freq", &lentmp);
        if (addr_prop == NULL) {
            log_info("pwm[%d] freq NULL.\r\n", i);
            continue;
        }
        freq = BL_FDT32_TO_U32(addr_prop, 0);

        log_info("path = %s, id = %d, pin = %d, freq = %ld\r\n",
                path, id, pin, freq);
        bl_pwm_init(id, pin, freq);
        if (dev_pwm_init(id, (const char *)path) != 0) {
            log_error("dev_pwm_init err.\r\n");
        }
    }
}

int32_t vfs_pwm_init(uint32_t fdt, uint32_t dtb_pwm_offset)
{
    if (inited == 1) {
        return VFS_SUCCESS;
    }

    fdt_pwm_module_init((const void *)fdt, (int)dtb_pwm_offset);

    inited = 1;

    return VFS_SUCCESS;
}

int32_t hal_pwm_start_bydev(pwm_dev_t *pwm)
{
    bl_pwm_start(pwm->port);
    return 0;
}

int32_t hal_pwm_stop_bydev(pwm_dev_t *pwm)
{
    bl_pwm_stop(pwm->port);
    return 0;
}

int32_t hal_pwm_para_chg_bydev(pwm_dev_t *pwm, pwm_config_t para)
{
    return 0;
}

int32_t hal_pwm_set_duty_bydev(pwm_dev_t *pwm, float duty)
{
    //log_info("set duty %d, %ld\r\n", pwm->port, (uint16_t)duty);
    bl_pwm_set_duty(pwm->port, duty);
    return 0;
}

int32_t hal_pwm_set_freq_bydev(pwm_dev_t *pwm, uint32_t freq)
{
    log_error("not support.\r\n");
    bl_pwm_set_freq(pwm->port, freq);
    return 0;
}

static void __pwm_duty_adjust (int id)
{
    hal_pwm_dev_t *p_dev = &__g_pwm_dev[id];
    hal_pwm_ev_t *p_ev;

    if (p_dev->p_now_ev == NULL) {
        p_dev->p_now_ev = (hal_pwm_ev_t *)utils_list_pop_front(&p_dev->list_head);
    }
    if ((p_ev = p_dev->p_now_ev) == NULL) {
        return;
    }

    if (p_ev->remain_ms) {
        p_ev->remain_ms--;
        p_dev->now_duty = p_dev->now_duty + p_ev->adjust_duty;

        bl_pwm_set_duty(id, p_dev->now_duty);

        if (p_ev->remain_ms == 0) {
            if (p_dev->now_duty != p_ev->duty) {
                p_ev->remain_ms++;
                p_ev->adjust_duty = p_ev->duty - p_dev->now_duty;
            } else {
                if (p_ev->cb) {
                    p_ev->cb(p_ev->p_arg);
                }
                /* next event */
                p_dev->p_now_ev = (hal_pwm_ev_t *)utils_list_pop_front(&p_dev->list_head);
            }
        }
    }
}

static void __loop_pwm_trigger (void *p_arg)
{
    int id;
    uint8_t stop = 1;

    taskENTER_CRITICAL();
    for (id = 0; id < _HAL_PWM_CHAN_NUMS; id++) {
        if (__g_pwm_dev[id].active) {
            __pwm_duty_adjust(id);
        }
        if (__g_pwm_dev[id].p_now_ev != NULL) {
            stop = 0;
        }
    }
    if (stop) {
        loopset_pwm_trigger_stop();
    }
    taskEXIT_CRITICAL();
}

static void __ev_complete (void *p_arg)
{
    hal_pwm_ev_t *p_ev = (hal_pwm_ev_t *)p_arg;
    printf("pwm_duty_set finish duty %f\r\n", p_ev->duty);
    vPortFree(p_ev);
}

int hal_pwm_start(uint8_t id)
{
    if (id >= _HAL_PWM_CHAN_NUMS) {
        return -1;
    }

    bl_pwm_start(id);
    return 0;
}

int hal_pwm_stop(uint8_t id)
{
    if (id >= _HAL_PWM_CHAN_NUMS) {
        return -1;
    }

    bl_pwm_stop(id);
    return 0;
}

static struct utils_list_hdr * __list_last (struct utils_list *list)
{
    if (utils_list_is_empty(list)) {
        return NULL;
    }
    return list->last;
}

int hal_pwm_duty_set(uint8_t id, uint32_t duty, uint32_t duration_ms)
{
    float now_duty, adjust_duty;
    hal_pwm_dev_t *p_dev;
    hal_pwm_ev_t  *p_ev, *p_temp_ev;

    if (id >= _HAL_PWM_CHAN_NUMS || duty > (100 * _HAL_PWM_DUTY_ACCURACY)) {
        return -1;
    }

    p_dev = &__g_pwm_dev[id];

    if (duration_ms == 0) {
        p_dev->now_duty = (float)duty / _HAL_PWM_DUTY_ACCURACY;
        bl_pwm_set_duty(id, p_dev->now_duty);
        return 0;
    }

    p_ev = pvPortMalloc(sizeof(hal_pwm_ev_t));
    if (NULL == p_ev) {
        return -1;
    }
    memset(p_ev, 0, sizeof(hal_pwm_ev_t));

    if (p_dev->p_now_ev) {
        if (!(p_temp_ev = (hal_pwm_ev_t *)__list_last(&p_dev->list_head))) {
            p_temp_ev = p_dev->p_now_ev;
        }
        now_duty = p_temp_ev->duty;
    } else {
        bl_pwm_get_duty(id, &now_duty);
    }

    adjust_duty = (float)duty / _HAL_PWM_DUTY_ACCURACY - now_duty;
    adjust_duty = adjust_duty / duration_ms;
    if (adjust_duty == 0.0) {
        return 0;
    }

    p_ev->cb = __ev_complete;
    p_ev->p_arg = p_ev;

    taskENTER_CRITICAL();
    p_ev->duty = (float)duty / _HAL_PWM_DUTY_ACCURACY;
    p_ev->remain_ms = duration_ms;
    p_ev->adjust_duty = adjust_duty;
    utils_list_push_back(&p_dev->list_head, &p_ev->item);
    taskEXIT_CRITICAL();

    loopset_pwm_trigger_start();

    printf("now_duty %f, adjust_duty %f\r\n", now_duty, adjust_duty);

    return 0;
}

int hal_pwm_duty_get(uint8_t id, uint32_t *p_duty)
{
    float duty;
    if (id >= _HAL_PWM_CHAN_NUMS || NULL == p_duty) {
        return -1;
    }
    bl_pwm_get_duty(id, &duty);
    *p_duty = duty * _HAL_PWM_DUTY_ACCURACY;
    return 0;
}

int hal_pwm_freq_get(uint8_t id, uint32_t *p_freq)
{
    if (id >= _HAL_PWM_CHAN_NUMS || NULL == p_freq) {
        return -1;
    }
    *p_freq = __g_pwm_dev[id].freq;
    int32_t bl_pwm_get_duty(uint8_t id, float *p_duty);
    return 0;
}

int hal_pwm_freq_update(uint8_t id, uint32_t freq)
{
    if (id >= _HAL_PWM_CHAN_NUMS) {
        return -1;
    }
    if (freq <= (BL_PWM_CLK / (1UL << 16)) || freq > (BL_PWM_CLK / 100)) {
        return -1;
    }
    __g_pwm_dev[id].freq = freq;
    bl_pwm_set_freq(id, freq);
    bl_pwm_set_duty(id, __g_pwm_dev[id].now_duty);
    return 0;
}

int hal_pwm_init(uint8_t id, int pin)
{
    if (id >= _HAL_PWM_CHAN_NUMS) {
        return -1;
    }

    memset(&__g_pwm_dev[id], 0, sizeof(hal_pwm_dev_t));

    __g_pwm_dev[id].active = 1;
    __g_pwm_dev[id].freq = 2000;

    utils_list_init(&__g_pwm_dev[id].list_head);
    bl_pwm_init(id, pin, __g_pwm_dev[id].freq);

    if (!__g_init_flag) {
        __g_init_flag = 1;
        loopset_pwm_hook_on_looprt();
        loopset_pwm_trigger_on(_HAL_PWM_DUTY_UNIT_MS, __loop_pwm_trigger, NULL);
    }

    return 0;
}

int hal_pwm_deinit(uint8_t id)
{
    if (id >= _HAL_PWM_CHAN_NUMS) {
        return -1;
    }
    hal_pwm_stop(id);
    memset(__g_pwm_dev, 0, sizeof(__g_pwm_dev));
    __g_init_flag = 0;

    loopset_pwm_trigger_off();
    loopset_pwm_hook_off_looprt();

    return 0;
}


