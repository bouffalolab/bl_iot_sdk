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
