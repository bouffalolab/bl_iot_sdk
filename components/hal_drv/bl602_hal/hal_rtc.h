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
#ifndef __HAL_RTC_H__
#define __HAL_RTC_H__

/** @addtogroup hal_rtc RTC
 *  rtc hal API.
 *
 *  @{
 */

#include <stdint.h>

/* Decode format list */
#define HAL_RTC_FORMAT_DEC 1
#define HAL_RTC_FORMAT_BCD 2

typedef struct {
    uint8_t format; /**< time formart DEC or BCD */
} rtc_config_t;

typedef struct {
    uint8_t       port;   /**< rtc port */
    rtc_config_t  config; /**< rtc config */
    void         *priv;   /**< priv data */
} rtc_dev_t;

/*
 * RTC time
 */
typedef struct {
    uint8_t sec;     /**< DEC format:value range from 0 to 59, BCD format:value range from 0x00 to 0x59 */
    uint8_t min;     /**< DEC format:value range from 0 to 59, BCD format:value range from 0x00 to 0x59 */
    uint8_t hr;      /**< DEC format:value range from 0 to 23, BCD format:value range from 0x00 to 0x23 */
    uint8_t weekday; /**< DEC format:value range from 1 to  7, BCD format:value range from 0x01 to 0x07 */
    uint8_t date;    /**< DEC format:value range from 1 to 31, BCD format:value range from 0x01 to 0x31 */
    uint8_t month;   /**< DEC format:value range from 1 to 12, BCD format:value range from 0x01 to 0x12 */
    uint16_t year;   /**< DEC format:value range from 0 to 9999, BCD format:value range from 0x0000 to 0x9999 */
} rtc_time_t;

/**
 * This function will initialize the on board CPU real time clock
 *
 *
 * @param[in]  rtc  rtc device
 *
 * @return  0 : on success,  otherwise is error
 */
int32_t hal_rtc_init(rtc_dev_t *rtc);

/**
 * This function will return the value of time read from the on board CPU real time clock.
 *
 * @param[in]   rtc   rtc device
 * @param[out]  time  pointer to a time structure
 *
 * @return  0 : on success,  otherwise is error
 */
int32_t hal_rtc_get_time(rtc_dev_t *rtc, rtc_time_t *time);

/**
 * This function will set MCU RTC time to a new value.
 *
 * @param[in]   rtc   rtc device
 * @param[in]   time  pointer to a time structure
 *
 * @return  0 : on success,  otherwise is error
 */
int32_t hal_rtc_set_time(rtc_dev_t *rtc, const rtc_time_t *time);

/**
 * De-initialises an RTC interface, Turns off an RTC hardware interface
 *
 * @param[in]  RTC  the interface which should be de-initialised
 *
 * @return  0 : on success,  otherwise is error
 */
int32_t hal_rtc_finalize(rtc_dev_t *rtc);

/** @} */

#endif /* HAL_RTC_H */

