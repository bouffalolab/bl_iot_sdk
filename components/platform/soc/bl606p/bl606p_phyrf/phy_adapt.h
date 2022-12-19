#ifndef _PHY_ADAPT_H_
#define _PHY_ADAPT_H_

#include "hal_desc.h"

void pa_init();
int8_t pa_alloc(uint32_t vif_addr);
void pa_input(uint8_t id, struct rx_hd *rhd);
void pa_adapt(uint8_t id);
int8_t phy_utils_calc_ppm(struct rx_hd *rhd);

#endif
