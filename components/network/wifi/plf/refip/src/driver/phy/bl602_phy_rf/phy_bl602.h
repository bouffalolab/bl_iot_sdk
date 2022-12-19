#ifndef _PHY_BL602_H_
#define _PHY_BL602_H_

#include <stdint.h>

/// Maximum output power TODO
#define PHY_BL602_MAX_PWR_24G   		(20)
/// Minimum output power TODO
#define PHY_BL602_MIN_PWR_24G   		(-6)
/// MAC core clock frequency in MHz
#define PHY_BL602_MACCORE_FREQ_MHZ  	(40)
/// AGC memory address and size
#define PHY_BL602_AGC_MEM_ADDR 			(0x54c0a000)
#define PHY_BL602_AGC_MEM_SIZE 			(2048)
#define PHY_BL602_AGC_MEM_USED          (1280)

void phy_config_rxgain(int offset);
void phy_get_rf_gain_idx_vs_mode(uint8_t mode, int8_t *power, uint8_t *idx);

#endif
