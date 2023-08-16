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
#ifndef _RF_H_
#define _RF_H_

#include "co_int.h"

/**
 ****************************************************************************************
 * @brief Radio initialization function.
 * This function is called at platform reset.
 ****************************************************************************************
 */
void rf_init(uint32_t xtalfreq_hz);

/**
 ****************************************************************************************
 * @brief Radio restore function.
 * This function is called when restore from sleep mode.
 ****************************************************************************************
 */
void rf_restore();

/**
 ****************************************************************************************
 * @brief Set RF channel and bandwidth.
 * This function is called to change LO and RBB settings of RF
 ****************************************************************************************
 */
void rf_set_channel(uint8_t bandwidth, uint16_t channel_freq);

/**
 ****************************************************************************************
 * @brief Dump RF registers.
 * This function is called when a fault is occurred
 ****************************************************************************************
 */
void rf_dump_status(void);

/**
 ****************************************************************************************
 * @brief RF interrupt service routine.
 * This function is called when a RF interrupt is asserted to the interrupt controller
 ****************************************************************************************
 */
void rf_lo_isr(void);

/**
 ****************************************************************************************
 * @brief RF interrupt service routine.
 * This function is called when a RF interrupt is asserted to the interrupt controller
 ****************************************************************************************
 */
void rf_clkpll_isr(void);

#endif /* _RF_H_ */
