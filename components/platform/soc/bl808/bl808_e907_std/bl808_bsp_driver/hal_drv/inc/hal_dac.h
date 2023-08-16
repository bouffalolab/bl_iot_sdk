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
#ifndef __HAL_DAC__H__
#define __HAL_DAC__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

enum dac_index_type {
#ifdef BSP_USING_DAC0
    DAC0_INDEX,
#endif
    DAC_MAX_INDEX
};

#define DAC_CHANNEL_0   (1 << 0)
#define DAC_CHANNEL_1   (1 << 1)
#define DAC_CHANNEL_ALL (DAC_CHANNEL_0 | DAC_CHANNEL_1)

/* default a_rng and b_rng is 0x03*/
/*output Voltage = (1.8V-0.2V) * digital_val/1024 + 0.2V */
#define DAC_VREF_INTERNAL 0 /*0.2V~1.8V*/
/*output Voltage = (0.9vref-0.1vref) * digital_val/1024 + 0.1vref */
#define DAC_VREF_EXTERNAL 1 /*0.1vref~0.9vref,using gpio7 for GPIO_FUN_ADC*/

enum dac_sample_frequence {
    DAC_SAMPLE_FREQ_8KHZ,
    DAC_SAMPLE_FREQ_16KHZ,
    DAC_SAMPLE_FREQ_44P1KHZ,
    DAC_SAMPLE_FREQ_500KHZ,
};

typedef struct dac_device {
    struct device parent;
    enum dac_sample_frequence sample_freq;
    uint8_t channels;
    uint8_t vref;
    void *tx_dma;
} dac_device_t;

#define DAC_DEV(dev) ((adc_device_t *)dev)

int dac_register(enum dac_index_type index, const char *name);
#ifdef __cplusplus
}
#endif
#endif
