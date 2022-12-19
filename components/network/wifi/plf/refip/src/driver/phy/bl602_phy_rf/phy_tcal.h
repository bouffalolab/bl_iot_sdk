#ifndef _PHY_TCAL_H_
#define _PHY_TCAL_H_

#include <stdint.h>

#define PHY_TCAL_INTERVAL_US   (1000000)

struct tcal_sim_tag
{
    int16_t rxgain_temperature;
    int8_t rxgain_vpeak_dbv;
    int16_t txpwr_temperature;
    int8_t txpwr_offset_db;
};

void phy_tcal_reset();
void phy_tcal_start();
void phy_tcal_stop();
void phy_tcal_callback(int16_t temperature);

#endif
