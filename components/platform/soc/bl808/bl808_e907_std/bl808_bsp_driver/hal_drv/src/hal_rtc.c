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
#include "hal_rtc.h"
#include "bl808_hbn.h"
static uint64_t current_timestamp = 0;

/**
 * @brief rtc init withc sleep time
 *
 * @param sleep_time
 */
void rtc_init(uint64_t sleep_time)
{
    uint32_t tmpVal;
    uint32_t comp_l, comp_h;

    /* Clear & Disable RTC counter */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Clear RTC control bit0 */
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal & 0xfffffff0);

    /* Get current RTC timer */
    /* Tigger RTC val read */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);

    /* Read RTC val */
    comp_l = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_L);
    comp_h = (BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H) & 0xff);

    /* calculate RTC Comp time */
    comp_l += (uint32_t)((sleep_time * 32768) & 0xFFFFFFFF);
    comp_h += (uint32_t)(((sleep_time * 32768) >> 32) & 0xFFFFFFFF);

    /* Set RTC Comp time  */
    BL_WR_REG(HBN_BASE, HBN_TIME_L, comp_l);
    BL_WR_REG(HBN_BASE, HBN_TIME_H, comp_h & 0xff);

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Set interrupt delay option */
    tmpVal =
        BL_SET_REG_BITS_VAL(tmpVal, HBN_RTC_DLY_OPTION, HBN_RTC_INT_DELAY_0T);
    /* Set RTC compare mode */
    tmpVal |= (HBN_RTC_COMP_BIT0_39 << 1);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Enable RTC Counter */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Set RTC control bit0 */
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal | 0x01);
}

void rtc_set_timestamp(uint64_t time_stamp)
{
    current_timestamp = time_stamp;
}
/**
 * @bref Get rtc value
 *
 */
uint64_t rtc_get_timestamp(void)
{
    uint32_t tmpVal;
    uint64_t time_l;
    uint64_t time_h;

    /* Tigger RTC val read */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);

    /* Read RTC val */
    time_l = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_L);
    time_h = (BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H) & 0xff);

    return (((time_h << 32 | time_l) >> 15) + current_timestamp);
}
