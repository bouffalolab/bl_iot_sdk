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
#ifndef _PHY_TRPC_H_
#define _PHY_TRPC_H_

#include "co_int.h"

#define PHY_TRPC_MAX_DBM    (30)

/*
 * STRUCTURES/TYPES DEFINITION
 ****************************************************************************************
 */

struct trpc_env_tag 
{
    /// RF output power capability
    int8_t power_dbm_max_rf;
    int8_t power_dbm_min_rf;
    /// Maximum power limited by regulations (SRRC/FCC/CE...)
    int8_t power_dbm_lim_reg;
    /// Current channel
    int16_t channel_freq;
    /// Current temperature
    int8_t temperature;
    int8_t temperature_compensate;
};


/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

extern struct trpc_env_tag trpc_env;


/*
 * FUNCTION PROTOTYPES
 ****************************************************************************************
 */
void trpc_init();
void trpc_update_power(int8_t txpwr_vs_rate_table[3][8]);
void trpc_power_get(int8_t power_rate_table[24]);
void trpc_update_power_11b(int8_t power_rate_table[4]);
void trpc_update_power_11g(int8_t power_rate_table[8]);
void trpc_update_power_11n(int8_t power_rate_table[8]);
int8_t trpc_get_rf_max_power();
int8_t trpc_get_rf_min_power();
uint8_t trpc_get_default_power_idx(uint8_t formatmod, uint8_t mcs);
uint8_t trpc_get_power_idx(uint8_t formatmod, uint8_t mcs, int8_t pwr_dbm);
void trpc_update_vs_channel(int8_t channel_MHz);
void trpc_update_vs_temperature(int8_t temperature);


#endif
