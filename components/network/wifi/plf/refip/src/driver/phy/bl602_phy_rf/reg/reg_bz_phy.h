#ifndef _REG_BZ_PHY_H_
#define _REG_BZ_PHY_H_

#include "co_int.h"
#include "arch.h"
#include "_reg_access.h"

static inline uint32_t bz_phy_dfe_txdfe_4s_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void bz_phy_dfe_txdfe_4s_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_dfe_rxdfe_4s_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void bz_phy_dfe_rxdfe_4s_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_adc_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void bz_phy_adc_clk_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_dfe_clk_force_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void bz_phy_dfe_clk_force_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_dfe_txmode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x000000c0)) >> 6);
}

static inline void bz_phy_dfe_txmode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x000000c0);
    localVal |= (x << 6)&((uint32_t)0x000000c0);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_dfe_txmode_force_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void bz_phy_dfe_txmode_force_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_txdfe_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void bz_phy_txdfe_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_dfe_rxmode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void bz_phy_dfe_rxmode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_dfe_rxmode_force_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void bz_phy_dfe_rxmode_force_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_rxdfe_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void bz_phy_rxdfe_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002800);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40002800,localVal);
}

static inline uint32_t bz_phy_tx_pll_bw_switch_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    return ((localVal & ((uint32_t)0xffc00000)) >> 22);
}

static inline void bz_phy_tx_pll_bw_switch_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    localVal &= ~((uint32_t)0xffc00000);
    localVal |= (x << 22)&((uint32_t)0xffc00000);
    REG_PL_WR(0x40002804,localVal);
}

static inline uint32_t bz_phy_tx_dfe_psf_zig_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void bz_phy_tx_dfe_psf_zig_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x40002804,localVal);
}

static inline uint32_t bz_phy_tx_dfe_psf_ble2m_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    return ((localVal & ((uint32_t)0x000c0000)) >> 18);
}

static inline void bz_phy_tx_dfe_psf_ble2m_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    localVal &= ~((uint32_t)0x000c0000);
    localVal |= (x << 18)&((uint32_t)0x000c0000);
    REG_PL_WR(0x40002804,localVal);
}

static inline uint32_t bz_phy_tx_dfe_psf_ble1m_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void bz_phy_tx_dfe_psf_ble1m_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x40002804,localVal);
}

static inline uint32_t bz_phy_tx_dfe_iq_if_freq_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void bz_phy_tx_dfe_iq_if_freq_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002804);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x40002804,localVal);
}

static inline uint32_t bz_phy_tx_rampup_time_us_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void bz_phy_tx_rampup_time_us_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40002808,localVal);
}

static inline uint32_t bz_phy_tx_rampup_fm_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void bz_phy_tx_rampup_fm_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x40002808,localVal);
}

static inline uint32_t bz_phy_tx_rampup_am_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void bz_phy_tx_rampup_am_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x40002808,localVal);
}

static inline uint32_t bz_phy_tx_rampup_am_step_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    return ((localVal & ((uint32_t)0x003fc000)) >> 14);
}

static inline void bz_phy_tx_rampup_am_step_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    localVal &= ~((uint32_t)0x003fc000);
    localVal |= (x << 14)&((uint32_t)0x003fc000);
    REG_PL_WR(0x40002808,localVal);
}

static inline uint32_t bz_phy_tx_pa_pwr_code_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    return ((localVal & ((uint32_t)0x00003e00)) >> 9);
}

static inline void bz_phy_tx_pa_pwr_code_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002808);
    localVal &= ~((uint32_t)0x00003e00);
    localVal |= (x << 9)&((uint32_t)0x00003e00);
    REG_PL_WR(0x40002808,localVal);
}

static inline uint32_t bz_phy_tx_rampdn_time_us_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void bz_phy_tx_rampdn_time_us_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x4000280c,localVal);
}

static inline uint32_t bz_phy_tx_rampdn_fm_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void bz_phy_tx_rampdn_fm_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x4000280c,localVal);
}

static inline uint32_t bz_phy_tx_rampdn_am_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void bz_phy_tx_rampdn_am_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x4000280c,localVal);
}

static inline uint32_t bz_phy_tx_rampdn_am_step_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    return ((localVal & ((uint32_t)0x003fc000)) >> 14);
}

static inline void bz_phy_tx_rampdn_am_step_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    localVal &= ~((uint32_t)0x003fc000);
    localVal |= (x << 14)&((uint32_t)0x003fc000);
    REG_PL_WR(0x4000280c,localVal);
}

static inline uint32_t bz_phy_tx_rampdn_am_start_dly_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void bz_phy_tx_rampdn_am_start_dly_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x4000280c,localVal);
}

static inline uint32_t bz_phy_tx_rampdn_pad0_time_us_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_phy_tx_rampdn_pad0_time_us_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000280c);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x4000280c,localVal);
}

static inline uint32_t bz_phy_rx_dfe_dccan_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void bz_phy_rx_dfe_dccan_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_loop_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void bz_phy_rx_dfe_loop_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_nsr_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void bz_phy_rx_dfe_nsr_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_diffosr_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void bz_phy_rx_dfe_diffosr_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_dga_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void bz_phy_rx_dfe_dga_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_cs_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void bz_phy_rx_dfe_cs_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_ddc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void bz_phy_rx_dfe_ddc_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_toc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void bz_phy_rx_dfe_toc_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_notch_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void bz_phy_rx_dfe_notch_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002810);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40002810,localVal);
}

static inline uint32_t bz_phy_rx_dfe_freq_trk_force_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002814);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void bz_phy_rx_dfe_freq_trk_force_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002814);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40002814,localVal);
}

static inline uint32_t bz_phy_rx_dfe_freq_trk_val_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002814);
    return ((localVal & ((uint32_t)0x00001fff)) >> 0);
}

static inline void bz_phy_rx_dfe_freq_trk_val_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002814);
    localVal &= ~((uint32_t)0x00001fff);
    localVal |= (x << 0)&((uint32_t)0x00001fff);
    REG_PL_WR(0x40002814,localVal);
}

static inline uint32_t bz_phy_rx_dfe_dccan_alpha_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    return ((localVal & ((uint32_t)0x01800000)) >> 23);
}

static inline void bz_phy_rx_dfe_dccan_alpha_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    localVal &= ~((uint32_t)0x01800000);
    localVal |= (x << 23)&((uint32_t)0x01800000);
    REG_PL_WR(0x40002818,localVal);
}

static inline uint32_t bz_phy_rx_dfe_notch_force_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void bz_phy_rx_dfe_notch_force_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x40002818,localVal);
}

static inline uint32_t bz_phy_rx_dfe_notch_alpha_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void bz_phy_rx_dfe_notch_alpha_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x40002818,localVal);
}

static inline uint32_t bz_phy_rx_dfe_notch_rot_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    return ((localVal & ((uint32_t)0x000ffc00)) >> 10);
}

static inline void bz_phy_rx_dfe_notch_rot_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    localVal &= ~((uint32_t)0x000ffc00);
    localVal |= (x << 10)&((uint32_t)0x000ffc00);
    REG_PL_WR(0x40002818,localVal);
}

static inline uint32_t bz_phy_rx_dfe_notch_rot_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_rx_dfe_notch_rot_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002818);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002818,localVal);
}

static inline uint32_t bz_phy_rx_dfe_toc_fac_force_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000281c);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void bz_phy_rx_dfe_toc_fac_force_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000281c);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x4000281c,localVal);
}

static inline uint32_t bz_phy_rx_dfe_toc_fac_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000281c);
    return ((localVal & ((uint32_t)0x00000fff)) >> 0);
}

static inline void bz_phy_rx_dfe_toc_fac_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000281c);
    localVal &= ~((uint32_t)0x00000fff);
    localVal |= (x << 0)&((uint32_t)0x00000fff);
    REG_PL_WR(0x4000281c,localVal);
}

static inline uint32_t bz_phy_phy_sw_ed_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_phy_sw_ed_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_phy_sw_cca_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void bz_phy_phy_sw_cca_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_phy_cca_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

static inline void bz_phy_phy_cca_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x20000000);
    localVal |= (x << 29)&((uint32_t)0x20000000);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_phy_cca_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x18000000)) >> 27);
}

static inline void bz_phy_phy_cca_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x18000000);
    localVal |= (x << 27)&((uint32_t)0x18000000);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_phy_cca_dur_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void bz_phy_phy_cca_dur_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_phy_cca_found_src_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void bz_phy_phy_cca_found_src_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_phy_cca_ed_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x007f0000)) >> 16);
}

static inline void bz_phy_phy_cca_ed_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x007f0000);
    localVal |= (x << 16)&((uint32_t)0x007f0000);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_phy_sw_cca_en_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void bz_phy_phy_sw_cca_en_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_cca_st_ed_meas_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00007f00)) >> 8);
}

static inline uint32_t bz_phy_cca_st_cca_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline uint32_t bz_phy_cca_st_ed_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline uint32_t bz_phy_cca_st_cs_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline uint32_t bz_phy_cca_st_dm_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline uint32_t bz_phy_cca_st_int_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline uint32_t bz_phy_cca_st_int_clr_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void bz_phy_cca_st_int_clr_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_cca_st_int_set_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void bz_phy_cca_st_int_set_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002834);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40002834,localVal);
}

static inline uint32_t bz_phy_ble_aa_offset_coef_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    return ((localVal & ((uint32_t)0x07c00000)) >> 22);
}

static inline void bz_phy_ble_aa_offset_coef_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    localVal &= ~((uint32_t)0x07c00000);
    localVal |= (x << 22)&((uint32_t)0x07c00000);
    REG_PL_WR(0x40002838,localVal);
}

static inline uint32_t bz_phy_ble_cfoe_avg_l_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    return ((localVal & ((uint32_t)0x003c0000)) >> 18);
}

static inline void bz_phy_ble_cfoe_avg_l_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    localVal &= ~((uint32_t)0x003c0000);
    localVal |= (x << 18)&((uint32_t)0x003c0000);
    REG_PL_WR(0x40002838,localVal);
}

static inline uint32_t bz_phy_ble_sync_corr_avg_l_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    return ((localVal & ((uint32_t)0x0003e000)) >> 13);
}

static inline void bz_phy_ble_sync_corr_avg_l_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    localVal &= ~((uint32_t)0x0003e000);
    localVal |= (x << 13)&((uint32_t)0x0003e000);
    REG_PL_WR(0x40002838,localVal);
}

static inline uint32_t bz_phy_blec_cfoe_alpha_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    return ((localVal & ((uint32_t)0x00001c00)) >> 10);
}

static inline void bz_phy_blec_cfoe_alpha_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    localVal &= ~((uint32_t)0x00001c00);
    localVal |= (x << 10)&((uint32_t)0x00001c00);
    REG_PL_WR(0x40002838,localVal);
}

static inline uint32_t bz_phy_t2f_mag_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    return ((localVal & ((uint32_t)0x000001ff)) >> 0);
}

static inline void bz_phy_t2f_mag_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002838);
    localVal &= ~((uint32_t)0x000001ff);
    localVal |= (x << 0)&((uint32_t)0x000001ff);
    REG_PL_WR(0x40002838,localVal);
}

static inline uint32_t bz_phy_t2f_filter_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000283c);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void bz_phy_t2f_filter_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000283c);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x4000283c,localVal);
}

static inline uint32_t bz_phy_t2f_filter_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000283c);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

static inline void bz_phy_t2f_filter_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000283c);
    localVal &= ~((uint32_t)0x08000000);
    localVal |= (x << 27)&((uint32_t)0x08000000);
    REG_PL_WR(0x4000283c,localVal);
}

static inline uint32_t bz_phy_t2f_impulse_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000283c);
    return ((localVal & ((uint32_t)0x07ffe000)) >> 13);
}

static inline void bz_phy_t2f_impulse_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000283c);
    localVal &= ~((uint32_t)0x07ffe000);
    localVal |= (x << 13)&((uint32_t)0x07ffe000);
    REG_PL_WR(0x4000283c,localVal);
}

static inline uint32_t bz_phy_t2f_limite_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000283c);
    return ((localVal & ((uint32_t)0x00001fff)) >> 0);
}

static inline void bz_phy_t2f_limite_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000283c);
    localVal &= ~((uint32_t)0x00001fff);
    localVal |= (x << 0)&((uint32_t)0x00001fff);
    REG_PL_WR(0x4000283c,localVal);
}

static inline uint32_t bz_phy_phy_reserved_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002840);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void bz_phy_phy_reserved_0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002840);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40002840,localVal);
}

static inline uint32_t bz_phy_phy_reserved_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002844);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void bz_phy_phy_reserved_1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002844);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40002844,localVal);
}

static inline uint32_t bz_phy_ff_coef_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002848);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void bz_phy_ff_coef_0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002848);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40002848,localVal);
}

static inline uint32_t bz_phy_ff_coef_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002848);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void bz_phy_ff_coef_1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002848);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x40002848,localVal);
}

static inline uint32_t bz_phy_ff_coef_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002848);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_phy_ff_coef_2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002848);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002848,localVal);
}

static inline uint32_t bz_phy_fb_coef_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002848);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_phy_fb_coef_0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002848);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002848,localVal);
}

static inline uint32_t bz_phy_ble_search_offset_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000284c);
    return ((localVal & ((uint32_t)0x0001f000)) >> 12);
}

static inline void bz_phy_ble_search_offset_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000284c);
    localVal &= ~((uint32_t)0x0001f000);
    localVal |= (x << 12)&((uint32_t)0x0001f000);
    REG_PL_WR(0x4000284c,localVal);
}

static inline uint32_t bz_phy_ble_aa_corr_thres_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000284c);
    return ((localVal & ((uint32_t)0x00000fff)) >> 0);
}

static inline void bz_phy_ble_aa_corr_thres_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000284c);
    localVal &= ~((uint32_t)0x00000fff);
    localVal |= (x << 0)&((uint32_t)0x00000fff);
    REG_PL_WR(0x4000284c,localVal);
}

static inline uint32_t bz_phy_ble_fsm_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_ble_fsm_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002850,localVal);
}

static inline uint32_t bz_phy_ble_fsm_cg_4s_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void bz_phy_ble_fsm_cg_4s_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40002850,localVal);
}

static inline uint32_t bz_phy_ble_demod_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_ble_demod_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002850,localVal);
}

static inline uint32_t bz_phy_ble_fsm_cfo_peak_dly_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    return ((localVal & ((uint32_t)0x0f000000)) >> 24);
}

static inline void bz_phy_ble_fsm_cfo_peak_dly_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    localVal &= ~((uint32_t)0x0f000000);
    localVal |= (x << 24)&((uint32_t)0x0f000000);
    REG_PL_WR(0x40002850,localVal);
}

static inline uint32_t bz_phy_ble_fsm_rx_dmtime_1m_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void bz_phy_ble_fsm_rx_dmtime_1m_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x40002850,localVal);
}

static inline uint32_t bz_phy_ble_fsm_rx_dmtime_2m_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_phy_ble_fsm_rx_dmtime_2m_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002850,localVal);
}

static inline uint32_t bz_phy_ble_rx_cfo_adj_symb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_phy_ble_rx_cfo_adj_symb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002850);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002850,localVal);
}

static inline uint32_t bz_phy_rx_proc_time_direct_us_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002854);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void bz_phy_rx_proc_time_direct_us_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002854);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40002854,localVal);
}

static inline uint32_t bz_phy_rx_proc_time_eq_us_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002854);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void bz_phy_rx_proc_time_eq_us_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002854);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x40002854,localVal);
}

static inline uint32_t bz_phy_rx_proc_time_mlsd_us_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002854);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_phy_rx_proc_time_mlsd_us_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002854);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002854,localVal);
}

static inline uint32_t bz_phy_rx_proc_time_viterbi_us_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002854);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_phy_rx_proc_time_viterbi_us_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002854);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002854,localVal);
}

static inline uint32_t bz_phy_phy_testbus_read_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002858);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t bz_phy_phy_testbus_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000285c);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_phy_phy_testbus_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000285c);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x4000285c,localVal);
}

static inline uint32_t bz_phy_sts_agc_clear_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002860);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_sts_agc_clear_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002860);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002860,localVal);
}

static inline uint32_t bz_phy_sts_agc_rf_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002860);
    return ((localVal & ((uint32_t)0x00e00000)) >> 21);
}

static inline uint32_t bz_phy_sts_agc_rf_rbb_ind_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002860);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline uint32_t bz_phy_sts_agc_agc_rssi_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002860);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline uint32_t bz_phy_sts_agc_fe_dg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002860);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline uint32_t bz_phy_sts_ble_clear_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000287c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_sts_ble_clear_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000287c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000287c,localVal);
}

static inline uint32_t bz_phy_sts_ble_frtk_out_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000287c);
    return ((localVal & ((uint32_t)0x001fff00)) >> 8);
}

static inline uint32_t bz_phy_sts_ble_cfo_out_peak_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000287c);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline uint32_t bz_phy_sts_ble_aa_confirm_bits_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002880);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t bz_phy_sts_ble_aa_error_cnt_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002884);
    return ((localVal & ((uint32_t)0x03f00000)) >> 20);
}

static inline uint32_t bz_phy_sts_ble_corr_out_max_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002884);
    return ((localVal & ((uint32_t)0x000fff00)) >> 8);
}

static inline uint32_t bz_phy_sts_ble_done_cfo_out_peak_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002884);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline uint32_t bz_phy_zb_dm_phy_len_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002888);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline uint32_t bz_phy_zb_dm_sfd_found_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002888);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline uint32_t bz_phy_zb_ts_cs_found_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002888);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline uint32_t bz_phy_zb_fsm_dbg_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002888);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void bz_phy_zb_fsm_dbg_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002888);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40002888,localVal);
}

static inline uint32_t bz_phy_zb_fsm_err_sts_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002888);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline uint32_t bz_phy_blec_pk_start_thres_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    return ((localVal & ((uint32_t)0xff800000)) >> 23);
}

static inline void bz_phy_blec_pk_start_thres_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    localVal &= ~((uint32_t)0xff800000);
    localVal |= (x << 23)&((uint32_t)0xff800000);
    REG_PL_WR(0x4000288c,localVal);
}

static inline uint32_t bz_phy_blec_pk_thres_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    return ((localVal & ((uint32_t)0x007fc000)) >> 14);
}

static inline void bz_phy_blec_pk_thres_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    localVal &= ~((uint32_t)0x007fc000);
    localVal |= (x << 14)&((uint32_t)0x007fc000);
    REG_PL_WR(0x4000288c,localVal);
}

static inline uint32_t bz_phy_blec_pk_timing_diff_thres_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    return ((localVal & ((uint32_t)0x00003800)) >> 11);
}

static inline void bz_phy_blec_pk_timing_diff_thres_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    localVal &= ~((uint32_t)0x00003800);
    localVal |= (x << 11)&((uint32_t)0x00003800);
    REG_PL_WR(0x4000288c,localVal);
}

static inline uint32_t bz_phy_blec_pk_jump_thres_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    return ((localVal & ((uint32_t)0x000007e0)) >> 5);
}

static inline void bz_phy_blec_pk_jump_thres_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    localVal &= ~((uint32_t)0x000007e0);
    localVal |= (x << 5)&((uint32_t)0x000007e0);
    REG_PL_WR(0x4000288c,localVal);
}

static inline uint32_t bz_phy_blec_aa_search_start_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void bz_phy_blec_aa_search_start_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000288c);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x4000288c,localVal);
}

static inline uint32_t bz_phy_blec_aa_search_stop_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    return ((localVal & ((uint32_t)0xfe000000)) >> 25);
}

static inline void bz_phy_blec_aa_search_stop_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    localVal &= ~((uint32_t)0xfe000000);
    localVal |= (x << 25)&((uint32_t)0xfe000000);
    REG_PL_WR(0x40002890,localVal);
}

static inline uint32_t bz_phy_blec_aa_corr_thres_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    return ((localVal & ((uint32_t)0x01fe0000)) >> 17);
}

static inline void bz_phy_blec_aa_corr_thres_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    localVal &= ~((uint32_t)0x01fe0000);
    localVal |= (x << 17)&((uint32_t)0x01fe0000);
    REG_PL_WR(0x40002890,localVal);
}

static inline uint32_t bz_phy_blec_timing_adj_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    return ((localVal & ((uint32_t)0x0001f000)) >> 12);
}

static inline void bz_phy_blec_timing_adj_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    localVal &= ~((uint32_t)0x0001f000);
    localVal |= (x << 12)&((uint32_t)0x0001f000);
    REG_PL_WR(0x40002890,localVal);
}

static inline uint32_t bz_phy_blec_rst_thres_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    return ((localVal & ((uint32_t)0x00000f00)) >> 8);
}

static inline void bz_phy_blec_rst_thres_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    localVal &= ~((uint32_t)0x00000f00);
    localVal |= (x << 8)&((uint32_t)0x00000f00);
    REG_PL_WR(0x40002890,localVal);
}

static inline uint32_t bz_phy_ble_fsm_rx_dmtime_cd_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_phy_ble_fsm_rx_dmtime_cd_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002890);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002890,localVal);
}

static inline uint32_t bz_phy_ble_frtk_th1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002894);
    return ((localVal & ((uint32_t)0x7f000000)) >> 24);
}

static inline void bz_phy_ble_frtk_th1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002894);
    localVal &= ~((uint32_t)0x7f000000);
    localVal |= (x << 24)&((uint32_t)0x7f000000);
    REG_PL_WR(0x40002894,localVal);
}

static inline uint32_t bz_phy_ble_frtk_th2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002894);
    return ((localVal & ((uint32_t)0x007f0000)) >> 16);
}

static inline void bz_phy_ble_frtk_th2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002894);
    localVal &= ~((uint32_t)0x007f0000);
    localVal |= (x << 16)&((uint32_t)0x007f0000);
    REG_PL_WR(0x40002894,localVal);
}

static inline uint32_t bz_phy_ble_frtk_th3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002894);
    return ((localVal & ((uint32_t)0x00007f00)) >> 8);
}

static inline void bz_phy_ble_frtk_th3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002894);
    localVal &= ~((uint32_t)0x00007f00);
    localVal |= (x << 8)&((uint32_t)0x00007f00);
    REG_PL_WR(0x40002894,localVal);
}

static inline uint32_t bz_phy_ble_frtk_max_step_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002894);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void bz_phy_ble_frtk_max_step_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002894);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40002894,localVal);
}

static inline uint32_t bz_phy_ble_frtk_coeff_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002898);
    return ((localVal & ((uint32_t)0x000003fe)) >> 1);
}

static inline void bz_phy_ble_frtk_coeff_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002898);
    localVal &= ~((uint32_t)0x000003fe);
    localVal |= (x << 1)&((uint32_t)0x000003fe);
    REG_PL_WR(0x40002898,localVal);
}

static inline uint32_t bz_phy_ble_frtk_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002898);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void bz_phy_ble_frtk_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002898);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40002898,localVal);
}

static inline uint32_t bz_phy_notch_en_2402_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002900);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2402_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002900);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002900,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2402_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002900);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2402_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002900);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002900,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2402_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002900);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2402_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002900);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002900,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2402_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002900);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2402_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002900);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002900,localVal);
}

static inline uint32_t bz_phy_notch_en_2404_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002904);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2404_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002904);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002904,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2404_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002904);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2404_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002904);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002904,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2404_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002904);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2404_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002904);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002904,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2404_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002904);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2404_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002904);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002904,localVal);
}

static inline uint32_t bz_phy_notch_en_2406_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002908);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2406_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002908);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002908,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2406_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002908);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2406_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002908);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002908,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2406_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002908);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2406_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002908);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002908,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2406_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002908);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2406_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002908);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002908,localVal);
}

static inline uint32_t bz_phy_notch_en_2408_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000290c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2408_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000290c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000290c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2408_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000290c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2408_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000290c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000290c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2408_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000290c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2408_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000290c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000290c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2408_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000290c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2408_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000290c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000290c,localVal);
}

static inline uint32_t bz_phy_notch_en_2410_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002910);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2410_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002910);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002910,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2410_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002910);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2410_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002910);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002910,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2410_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002910);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2410_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002910);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002910,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2410_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002910);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2410_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002910);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002910,localVal);
}

static inline uint32_t bz_phy_notch_en_2412_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002914);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2412_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002914);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002914,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2412_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002914);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2412_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002914);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002914,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2412_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002914);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2412_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002914);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002914,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2412_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002914);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2412_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002914);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002914,localVal);
}

static inline uint32_t bz_phy_notch_en_2414_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002918);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2414_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002918);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002918,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2414_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002918);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2414_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002918);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002918,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2414_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002918);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2414_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002918);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002918,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2414_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002918);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2414_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002918);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002918,localVal);
}

static inline uint32_t bz_phy_notch_en_2416_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000291c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2416_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000291c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000291c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2416_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000291c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2416_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000291c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000291c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2416_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000291c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2416_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000291c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000291c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2416_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000291c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2416_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000291c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000291c,localVal);
}

static inline uint32_t bz_phy_notch_en_2418_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002920);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2418_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002920);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002920,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2418_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002920);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2418_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002920);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002920,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2418_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002920);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2418_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002920);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002920,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2418_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002920);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2418_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002920);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002920,localVal);
}

static inline uint32_t bz_phy_notch_en_2420_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002924);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2420_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002924);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002924,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2420_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002924);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2420_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002924);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002924,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2420_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002924);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2420_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002924);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002924,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2420_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002924);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2420_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002924);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002924,localVal);
}

static inline uint32_t bz_phy_notch_en_2422_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002928);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2422_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002928);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002928,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2422_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002928);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2422_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002928);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002928,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2422_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002928);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2422_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002928);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002928,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2422_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002928);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2422_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002928);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002928,localVal);
}

static inline uint32_t bz_phy_notch_en_2424_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000292c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2424_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000292c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000292c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2424_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000292c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2424_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000292c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000292c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2424_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000292c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2424_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000292c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000292c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2424_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000292c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2424_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000292c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000292c,localVal);
}

static inline uint32_t bz_phy_notch_en_2426_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002930);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2426_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002930);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002930,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2426_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002930);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2426_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002930);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002930,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2426_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002930);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2426_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002930);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002930,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2426_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002930);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2426_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002930);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002930,localVal);
}

static inline uint32_t bz_phy_notch_en_2428_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002934);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2428_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002934);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002934,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2428_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002934);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2428_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002934);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002934,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2428_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002934);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2428_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002934);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002934,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2428_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002934);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2428_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002934);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002934,localVal);
}

static inline uint32_t bz_phy_notch_en_2430_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002938);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2430_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002938);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002938,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2430_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002938);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2430_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002938);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002938,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2430_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002938);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2430_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002938);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002938,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2430_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002938);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2430_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002938);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002938,localVal);
}

static inline uint32_t bz_phy_notch_en_2432_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000293c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2432_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000293c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000293c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2432_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000293c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2432_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000293c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000293c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2432_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000293c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2432_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000293c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000293c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2432_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000293c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2432_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000293c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000293c,localVal);
}

static inline uint32_t bz_phy_notch_en_2434_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002940);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2434_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002940);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002940,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2434_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002940);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2434_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002940);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002940,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2434_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002940);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2434_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002940);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002940,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2434_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002940);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2434_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002940);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002940,localVal);
}

static inline uint32_t bz_phy_notch_en_2436_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002944);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2436_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002944);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002944,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2436_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002944);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2436_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002944);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002944,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2436_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002944);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2436_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002944);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002944,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2436_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002944);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2436_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002944);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002944,localVal);
}

static inline uint32_t bz_phy_notch_en_2438_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002948);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2438_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002948);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002948,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2438_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002948);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2438_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002948);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002948,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2438_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002948);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2438_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002948);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002948,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2438_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002948);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2438_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002948);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002948,localVal);
}

static inline uint32_t bz_phy_notch_en_2440_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000294c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2440_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000294c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000294c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2440_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000294c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2440_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000294c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000294c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2440_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000294c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2440_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000294c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000294c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2440_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000294c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2440_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000294c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000294c,localVal);
}

static inline uint32_t bz_phy_notch_en_2442_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002950);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2442_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002950);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002950,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2442_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002950);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2442_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002950);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002950,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2442_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002950);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2442_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002950);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002950,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2442_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002950);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2442_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002950);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002950,localVal);
}

static inline uint32_t bz_phy_notch_en_2444_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002954);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2444_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002954);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002954,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2444_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002954);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2444_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002954);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002954,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2444_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002954);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2444_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002954);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002954,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2444_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002954);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2444_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002954);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002954,localVal);
}

static inline uint32_t bz_phy_notch_en_2446_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002958);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2446_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002958);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002958,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2446_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002958);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2446_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002958);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002958,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2446_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002958);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2446_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002958);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002958,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2446_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002958);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2446_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002958);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002958,localVal);
}

static inline uint32_t bz_phy_notch_en_2448_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000295c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2448_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000295c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000295c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2448_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000295c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2448_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000295c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000295c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2448_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000295c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2448_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000295c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000295c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2448_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000295c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2448_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000295c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000295c,localVal);
}

static inline uint32_t bz_phy_notch_en_2450_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002960);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2450_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002960);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002960,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2450_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002960);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2450_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002960);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002960,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2450_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002960);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2450_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002960);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002960,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2450_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002960);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2450_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002960);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002960,localVal);
}

static inline uint32_t bz_phy_notch_en_2452_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002964);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2452_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002964);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002964,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2452_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002964);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2452_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002964);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002964,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2452_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002964);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2452_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002964);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002964,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2452_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002964);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2452_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002964);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002964,localVal);
}

static inline uint32_t bz_phy_notch_en_2454_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002968);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2454_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002968);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002968,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2454_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002968);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2454_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002968);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002968,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2454_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002968);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2454_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002968);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002968,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2454_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002968);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2454_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002968);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002968,localVal);
}

static inline uint32_t bz_phy_notch_en_2456_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000296c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2456_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000296c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000296c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2456_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000296c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2456_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000296c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000296c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2456_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000296c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2456_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000296c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000296c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2456_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000296c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2456_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000296c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000296c,localVal);
}

static inline uint32_t bz_phy_notch_en_2458_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002970);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2458_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002970);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002970,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2458_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002970);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2458_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002970);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002970,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2458_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002970);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2458_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002970);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002970,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2458_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002970);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2458_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002970);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002970,localVal);
}

static inline uint32_t bz_phy_notch_en_2460_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002974);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2460_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002974);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002974,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2460_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002974);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2460_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002974);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002974,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2460_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002974);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2460_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002974);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002974,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2460_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002974);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2460_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002974);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002974,localVal);
}

static inline uint32_t bz_phy_notch_en_2462_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002978);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2462_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002978);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002978,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2462_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002978);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2462_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002978);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002978,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2462_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002978);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2462_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002978);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002978,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2462_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002978);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2462_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002978);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002978,localVal);
}

static inline uint32_t bz_phy_notch_en_2464_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000297c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2464_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000297c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000297c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2464_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000297c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2464_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000297c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000297c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2464_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000297c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2464_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000297c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000297c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2464_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000297c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2464_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000297c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000297c,localVal);
}

static inline uint32_t bz_phy_notch_en_2466_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002980);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2466_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002980);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002980,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2466_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002980);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2466_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002980);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002980,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2466_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002980);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2466_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002980);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002980,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2466_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002980);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2466_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002980);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002980,localVal);
}

static inline uint32_t bz_phy_notch_en_2468_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002984);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2468_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002984);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002984,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2468_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002984);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2468_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002984);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002984,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2468_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002984);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2468_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002984);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002984,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2468_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002984);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2468_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002984);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002984,localVal);
}

static inline uint32_t bz_phy_notch_en_2470_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002988);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2470_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002988);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002988,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2470_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002988);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2470_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002988);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002988,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2470_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002988);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2470_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002988);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002988,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2470_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002988);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2470_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002988);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002988,localVal);
}

static inline uint32_t bz_phy_notch_en_2472_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000298c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2472_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000298c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000298c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2472_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000298c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2472_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000298c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000298c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2472_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000298c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2472_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000298c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000298c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2472_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000298c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2472_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000298c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000298c,localVal);
}

static inline uint32_t bz_phy_notch_en_2474_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002990);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2474_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002990);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002990,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2474_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002990);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2474_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002990);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002990,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2474_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002990);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2474_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002990);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002990,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2474_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002990);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2474_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002990);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002990,localVal);
}

static inline uint32_t bz_phy_notch_en_2476_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002994);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2476_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002994);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002994,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2476_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002994);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2476_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002994);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002994,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2476_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002994);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2476_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002994);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002994,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2476_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002994);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2476_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002994);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002994,localVal);
}

static inline uint32_t bz_phy_notch_en_2478_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002998);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2478_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002998);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002998,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2478_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002998);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2478_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002998);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40002998,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2478_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002998);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2478_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002998);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40002998,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2478_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002998);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2478_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002998);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002998,localVal);
}

static inline uint32_t bz_phy_notch_en_2480_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000299c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2480_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000299c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000299c,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2480_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000299c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2480_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000299c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000299c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2480_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000299c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2480_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000299c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000299c,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2480_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000299c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2480_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000299c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000299c,localVal);
}

static inline uint32_t bz_phy_notch_en_2405_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a0);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2405_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a0);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x400029a0,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2405_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a0);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2405_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a0);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400029a0,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2405_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a0);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2405_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a0);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x400029a0,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2405_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a0);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2405_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a0);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400029a0,localVal);
}

static inline uint32_t bz_phy_notch_en_2415_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a4);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2415_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a4);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x400029a4,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2415_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a4);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2415_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a4);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400029a4,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2415_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a4);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2415_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a4);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x400029a4,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2415_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a4);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2415_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a4);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400029a4,localVal);
}

static inline uint32_t bz_phy_notch_en_2425_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a8);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2425_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a8);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x400029a8,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2425_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a8);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2425_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a8);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400029a8,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2425_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a8);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2425_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a8);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x400029a8,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2425_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029a8);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2425_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029a8);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400029a8,localVal);
}

static inline uint32_t bz_phy_notch_en_2435_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029ac);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2435_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029ac);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x400029ac,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2435_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029ac);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2435_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029ac);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400029ac,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2435_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029ac);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2435_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029ac);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x400029ac,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2435_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029ac);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2435_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029ac);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400029ac,localVal);
}

static inline uint32_t bz_phy_notch_en_2445_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b0);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2445_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b0);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x400029b0,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2445_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b0);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2445_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b0);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400029b0,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2445_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b0);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2445_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b0);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x400029b0,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2445_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b0);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2445_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b0);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400029b0,localVal);
}

static inline uint32_t bz_phy_notch_en_2455_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b4);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2455_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b4);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x400029b4,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2455_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b4);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2455_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b4);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400029b4,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2455_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b4);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2455_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b4);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x400029b4,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2455_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b4);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2455_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b4);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400029b4,localVal);
}

static inline uint32_t bz_phy_notch_en_2465_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b8);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2465_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b8);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x400029b8,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2465_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b8);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2465_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b8);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400029b8,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2465_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b8);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2465_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b8);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x400029b8,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2465_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029b8);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2465_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029b8);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400029b8,localVal);
}

static inline uint32_t bz_phy_notch_en_2475_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029bc);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_phy_notch_en_2475_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029bc);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x400029bc,localVal);
}

static inline uint32_t bz_phy_notch_alpha_2475_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029bc);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void bz_phy_notch_alpha_2475_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029bc);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400029bc,localVal);
}

static inline uint32_t bz_phy_notch_coeff_re_2475_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029bc);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void bz_phy_notch_coeff_re_2475_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029bc);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x400029bc,localVal);
}

static inline uint32_t bz_phy_notch_coeff_im_2475_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400029bc);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_notch_coeff_im_2475_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400029bc);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400029bc,localVal);
}

static inline uint32_t bz_phy_fpga_dig_gain_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    return ((localVal & ((uint32_t)0xfc000000)) >> 26);
}

static inline void bz_phy_fpga_dig_gain_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    localVal &= ~((uint32_t)0xfc000000);
    localVal |= (x << 26)&((uint32_t)0xfc000000);
    REG_PL_WR(0x40002a00,localVal);
}

static inline uint32_t bz_phy_pf_en_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void bz_phy_pf_en_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40002a00,localVal);
}

static inline uint32_t bz_phy_pf_en_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void bz_phy_pf_en_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40002a00,localVal);
}

static inline uint32_t bz_phy_pf_th1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    return ((localVal & ((uint32_t)0x000ffc00)) >> 10);
}

static inline void bz_phy_pf_th1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    localVal &= ~((uint32_t)0x000ffc00);
    localVal |= (x << 10)&((uint32_t)0x000ffc00);
    REG_PL_WR(0x40002a00,localVal);
}

static inline uint32_t bz_phy_pf_th2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_phy_pf_th2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002a00);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002a00,localVal);
}

#endif