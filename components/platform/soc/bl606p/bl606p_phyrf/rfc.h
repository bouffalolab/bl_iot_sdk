#ifndef _BL606P_RFC_H_
#define _BL606P_RFC_H_

#include "co_int.h"
#include "co_bool.h"

void rfc_init(uint32_t xtalfreq, uint8_t cold);
void rfc_config_channel(uint32_t channel_freq);
void rfc_bbmode_force(uint32_t force_enable, uint32_t bbmode);

// TODO: remove in BL606P
bool rfc_config_power_ble(int32_t pwr_dbm);
uint32_t rfc_get_power_level(uint32_t mode, int32_t power);
void rfc_apply_tx_power_offset(uint8_t channel,int8_t power_offset[14]);

#endif
