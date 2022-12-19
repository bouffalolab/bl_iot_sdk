#ifndef _REG_BZ_PHY_AGC_H_
#define _REG_BZ_PHY_AGC_H_

#include "co_int.h"
#include "arch.h"
#include "_reg_access.h"

static inline uint32_t bz_agc_force_pip_flag_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

static inline void bz_agc_force_pip_flag_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x04000000);
    localVal |= (x << 26)&((uint32_t)0x04000000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_pip_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

static inline void bz_agc_force_pip_flag_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x02000000);
    localVal |= (x << 25)&((uint32_t)0x02000000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_pkdet_flag_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline void bz_agc_force_pkdet_flag_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x01000000);
    localVal |= (x << 24)&((uint32_t)0x01000000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_pkdet_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void bz_agc_force_pkdet_flag_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_adc_sat_flag_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void bz_agc_force_adc_sat_flag_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_adc_sat_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void bz_agc_force_adc_sat_flag_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_fe_sat_flag_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void bz_agc_force_fe_sat_flag_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_fe_sat_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void bz_agc_force_fe_sat_flag_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_lna_ind_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void bz_agc_force_lna_ind_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_lna_ind_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x0003c000)) >> 14);
}

static inline void bz_agc_force_lna_ind_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x0003c000);
    localVal |= (x << 14)&((uint32_t)0x0003c000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_rbb_ind_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void bz_agc_force_rbb_ind_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_rbb_ind_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00001f00)) >> 8);
}

static inline void bz_agc_force_rbb_ind_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00001f00);
    localVal |= (x << 8)&((uint32_t)0x00001f00);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_dg_ind_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void bz_agc_force_dg_ind_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_force_dg_ind_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x0000007e)) >> 1);
}

static inline void bz_agc_force_dg_ind_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x0000007e);
    localVal |= (x << 1)&((uint32_t)0x0000007e);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void bz_agc_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c00);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40002c00,localVal);
}

static inline uint32_t bz_agc_adc_amp_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void bz_agc_adc_amp_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40002c04,localVal);
}

static inline uint32_t bz_agc_dbg_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_dbg_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c04,localVal);
}

static inline uint32_t bz_agc_force_adc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void bz_agc_force_adc_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40002c04,localVal);
}

static inline uint32_t bz_agc_force_adc_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    return ((localVal & ((uint32_t)0x0007f800)) >> 11);
}

static inline void bz_agc_force_adc_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    localVal &= ~((uint32_t)0x0007f800);
    localVal |= (x << 11)&((uint32_t)0x0007f800);
    REG_PL_WR(0x40002c04,localVal);
}

static inline uint32_t bz_agc_force_fe_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void bz_agc_force_fe_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40002c04,localVal);
}

static inline uint32_t bz_agc_force_fe_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    return ((localVal & ((uint32_t)0x000003fc)) >> 2);
}

static inline void bz_agc_force_fe_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    localVal &= ~((uint32_t)0x000003fc);
    localVal |= (x << 2)&((uint32_t)0x000003fc);
    REG_PL_WR(0x40002c04,localVal);
}

static inline uint32_t bz_agc_force_trig_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void bz_agc_force_trig_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40002c04,localVal);
}

static inline uint32_t bz_agc_force_trig_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void bz_agc_force_trig_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c04);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40002c04,localVal);
}

static inline uint32_t bz_agc_force_fe_dg_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c08);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void bz_agc_force_fe_dg_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c08);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40002c08,localVal);
}

static inline uint32_t bz_agc_force_fe_dg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c08);
    return ((localVal & ((uint32_t)0x00007e00)) >> 9);
}

static inline void bz_agc_force_fe_dg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c08);
    localVal &= ~((uint32_t)0x00007e00);
    localVal |= (x << 9)&((uint32_t)0x00007e00);
    REG_PL_WR(0x40002c08,localVal);
}

static inline uint32_t bz_agc_force_fe_rssi_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c08);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void bz_agc_force_fe_rssi_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c08);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40002c08,localVal);
}

static inline uint32_t bz_agc_force_fe_rssi_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c08);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_force_fe_rssi_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c08);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c08,localVal);
}

static inline uint32_t bz_agc_pkdet_flag_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c0c);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void bz_agc_pkdet_flag_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c0c);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40002c0c,localVal);
}

static inline uint32_t bz_agc_pkdet_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c0c);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void bz_agc_pkdet_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c0c);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40002c0c,localVal);
}

static inline uint32_t bz_agc_pkdet_win_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c0c);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_pkdet_win_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c0c);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c0c,localVal);
}

static inline uint32_t bz_agc_pkdet_cnt_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c0c);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_pkdet_cnt_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c0c);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c0c,localVal);
}

static inline uint32_t bz_agc_adc_sat_flag_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c10);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void bz_agc_adc_sat_flag_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c10);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40002c10,localVal);
}

static inline uint32_t bz_agc_adc_sat_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c10);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void bz_agc_adc_sat_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c10);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40002c10,localVal);
}

static inline uint32_t bz_agc_adc_sat_thr_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c14);
    return ((localVal & ((uint32_t)0x0001ff00)) >> 8);
}

static inline void bz_agc_adc_sat_thr_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c14);
    localVal &= ~((uint32_t)0x0001ff00);
    localVal |= (x << 8)&((uint32_t)0x0001ff00);
    REG_PL_WR(0x40002c14,localVal);
}

static inline uint32_t bz_agc_adc_sat_cnt_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c14);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_adc_sat_cnt_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c14);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c14,localVal);
}

static inline uint32_t bz_agc_adc_sat_win_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c14);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_adc_sat_win_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c14);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c14,localVal);
}

static inline uint32_t bz_agc_adc_sat_thr_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c18);
    return ((localVal & ((uint32_t)0x0001ff00)) >> 8);
}

static inline void bz_agc_adc_sat_thr_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c18);
    localVal &= ~((uint32_t)0x0001ff00);
    localVal |= (x << 8)&((uint32_t)0x0001ff00);
    REG_PL_WR(0x40002c18,localVal);
}

static inline uint32_t bz_agc_adc_sat_cnt_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c18);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_adc_sat_cnt_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c18);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c18,localVal);
}

static inline uint32_t bz_agc_adc_sat_win_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c18);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_adc_sat_win_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c18);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c18,localVal);
}

static inline uint32_t bz_agc_adc_sat_thr_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c1c);
    return ((localVal & ((uint32_t)0x0001ff00)) >> 8);
}

static inline void bz_agc_adc_sat_thr_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c1c);
    localVal &= ~((uint32_t)0x0001ff00);
    localVal |= (x << 8)&((uint32_t)0x0001ff00);
    REG_PL_WR(0x40002c1c,localVal);
}

static inline uint32_t bz_agc_adc_sat_cnt_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c1c);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_adc_sat_cnt_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c1c);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c1c,localVal);
}

static inline uint32_t bz_agc_adc_sat_win_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c1c);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_adc_sat_win_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c1c);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c1c,localVal);
}

static inline uint32_t bz_agc_adc_sat_thr_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c20);
    return ((localVal & ((uint32_t)0x0001ff00)) >> 8);
}

static inline void bz_agc_adc_sat_thr_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c20);
    localVal &= ~((uint32_t)0x0001ff00);
    localVal |= (x << 8)&((uint32_t)0x0001ff00);
    REG_PL_WR(0x40002c20,localVal);
}

static inline uint32_t bz_agc_adc_sat_cnt_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c20);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_adc_sat_cnt_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c20);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c20,localVal);
}

static inline uint32_t bz_agc_adc_sat_win_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c20);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_adc_sat_win_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c20);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c20,localVal);
}

static inline uint32_t bz_agc_fe_sat_flag_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c24);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void bz_agc_fe_sat_flag_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c24);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40002c24,localVal);
}

static inline uint32_t bz_agc_fe_sat_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c24);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void bz_agc_fe_sat_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c24);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40002c24,localVal);
}

static inline uint32_t bz_agc_fe_sat_thr_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c28);
    return ((localVal & ((uint32_t)0x0001ff00)) >> 8);
}

static inline void bz_agc_fe_sat_thr_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c28);
    localVal &= ~((uint32_t)0x0001ff00);
    localVal |= (x << 8)&((uint32_t)0x0001ff00);
    REG_PL_WR(0x40002c28,localVal);
}

static inline uint32_t bz_agc_fe_sat_cnt_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c28);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_fe_sat_cnt_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c28);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c28,localVal);
}

static inline uint32_t bz_agc_fe_sat_win_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c28);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_fe_sat_win_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c28);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c28,localVal);
}

static inline uint32_t bz_agc_fe_sat_thr_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c2c);
    return ((localVal & ((uint32_t)0x0001ff00)) >> 8);
}

static inline void bz_agc_fe_sat_thr_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c2c);
    localVal &= ~((uint32_t)0x0001ff00);
    localVal |= (x << 8)&((uint32_t)0x0001ff00);
    REG_PL_WR(0x40002c2c,localVal);
}

static inline uint32_t bz_agc_fe_sat_cnt_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c2c);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_fe_sat_cnt_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c2c);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c2c,localVal);
}

static inline uint32_t bz_agc_fe_sat_win_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c2c);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_fe_sat_win_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c2c);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c2c,localVal);
}

static inline uint32_t bz_agc_fe_sat_thr_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c30);
    return ((localVal & ((uint32_t)0x0001ff00)) >> 8);
}

static inline void bz_agc_fe_sat_thr_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c30);
    localVal &= ~((uint32_t)0x0001ff00);
    localVal |= (x << 8)&((uint32_t)0x0001ff00);
    REG_PL_WR(0x40002c30,localVal);
}

static inline uint32_t bz_agc_fe_sat_cnt_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c30);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_fe_sat_cnt_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c30);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c30,localVal);
}

static inline uint32_t bz_agc_fe_sat_win_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c30);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_fe_sat_win_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c30);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c30,localVal);
}

static inline uint32_t bz_agc_fe_sat_thr_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c34);
    return ((localVal & ((uint32_t)0x0001ff00)) >> 8);
}

static inline void bz_agc_fe_sat_thr_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c34);
    localVal &= ~((uint32_t)0x0001ff00);
    localVal |= (x << 8)&((uint32_t)0x0001ff00);
    REG_PL_WR(0x40002c34,localVal);
}

static inline uint32_t bz_agc_fe_sat_cnt_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c34);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void bz_agc_fe_sat_cnt_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c34);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40002c34,localVal);
}

static inline uint32_t bz_agc_fe_sat_win_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c34);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_fe_sat_win_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c34);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c34,localVal);
}

static inline uint32_t bz_agc_pip_flag_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

static inline void bz_agc_pip_flag_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    localVal &= ~((uint32_t)0x08000000);
    localVal |= (x << 27)&((uint32_t)0x08000000);
    REG_PL_WR(0x40002c38,localVal);
}

static inline uint32_t bz_agc_pip_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    return ((localVal & ((uint32_t)0x06000000)) >> 25);
}

static inline void bz_agc_pip_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    localVal &= ~((uint32_t)0x06000000);
    localVal |= (x << 25)&((uint32_t)0x06000000);
    REG_PL_WR(0x40002c38,localVal);
}

static inline uint32_t bz_agc_pip_mag_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    return ((localVal & ((uint32_t)0x01ff0000)) >> 16);
}

static inline void bz_agc_pip_mag_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    localVal &= ~((uint32_t)0x01ff0000);
    localVal |= (x << 16)&((uint32_t)0x01ff0000);
    REG_PL_WR(0x40002c38,localVal);
}

static inline uint32_t bz_agc_pip_cnt_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    return ((localVal & ((uint32_t)0x0000f000)) >> 12);
}

static inline void bz_agc_pip_cnt_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    localVal &= ~((uint32_t)0x0000f000);
    localVal |= (x << 12)&((uint32_t)0x0000f000);
    REG_PL_WR(0x40002c38,localVal);
}

static inline uint32_t bz_agc_pip_win_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    return ((localVal & ((uint32_t)0x00000f00)) >> 8);
}

static inline void bz_agc_pip_win_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    localVal &= ~((uint32_t)0x00000f00);
    localVal |= (x << 8)&((uint32_t)0x00000f00);
    REG_PL_WR(0x40002c38,localVal);
}

static inline uint32_t bz_agc_pip_rssi_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_pip_rssi_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c38);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c38,localVal);
}

static inline uint32_t bz_agc_disapp_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void bz_agc_disapp_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40002c3c,localVal);
}

static inline uint32_t bz_agc_disapp_freeze_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

static inline void bz_agc_disapp_freeze_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    localVal &= ~((uint32_t)0x20000000);
    localVal |= (x << 29)&((uint32_t)0x20000000);
    REG_PL_WR(0x40002c3c,localVal);
}

static inline uint32_t bz_agc_disapp_top_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void bz_agc_disapp_top_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x40002c3c,localVal);
}

static inline uint32_t bz_agc_disapp_cnt_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    return ((localVal & ((uint32_t)0x0ffc0000)) >> 18);
}

static inline void bz_agc_disapp_cnt_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    localVal &= ~((uint32_t)0x0ffc0000);
    localVal |= (x << 18)&((uint32_t)0x0ffc0000);
    REG_PL_WR(0x40002c3c,localVal);
}

static inline uint32_t bz_agc_disapp_lna_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    return ((localVal & ((uint32_t)0x0003c000)) >> 14);
}

static inline void bz_agc_disapp_lna_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    localVal &= ~((uint32_t)0x0003c000);
    localVal |= (x << 14)&((uint32_t)0x0003c000);
    REG_PL_WR(0x40002c3c,localVal);
}

static inline uint32_t bz_agc_disapp_rbb_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    return ((localVal & ((uint32_t)0x00003e00)) >> 9);
}

static inline void bz_agc_disapp_rbb_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    localVal &= ~((uint32_t)0x00003e00);
    localVal |= (x << 9)&((uint32_t)0x00003e00);
    REG_PL_WR(0x40002c3c,localVal);
}

static inline uint32_t bz_agc_disapp_adc_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    return ((localVal & ((uint32_t)0x000001ff)) >> 0);
}

static inline void bz_agc_disapp_adc_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c3c);
    localVal &= ~((uint32_t)0x000001ff);
    localVal |= (x << 0)&((uint32_t)0x000001ff);
    REG_PL_WR(0x40002c3c,localVal);
}

static inline uint32_t bz_agc_bz_phy_agc_rssi_upd_cyc_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_bz_phy_agc_rssi_upd_cyc_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002c40,localVal);
}

static inline uint32_t bz_agc_gain_unlock_ndl1_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_gain_unlock_ndl1_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c40,localVal);
}

static inline uint32_t bz_agc_gain_unlock_ndl2_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void bz_agc_gain_unlock_ndl2_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40002c40,localVal);
}

static inline uint32_t bz_agc_gain_unlock_th_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_gain_unlock_th_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c40,localVal);
}

static inline uint32_t bz_agc_gain_unlock_win_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_gain_unlock_win_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c40);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c40,localVal);
}

static inline uint32_t bz_agc_gain_lock_ndl1_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c44);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_gain_lock_ndl1_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c44);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c44,localVal);
}

static inline uint32_t bz_agc_gain_lock_ndl2_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c44);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void bz_agc_gain_lock_ndl2_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c44);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40002c44,localVal);
}

static inline uint32_t bz_agc_gain_lock_th_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c44);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_gain_lock_th_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c44);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c44,localVal);
}

static inline uint32_t bz_agc_gain_lock_win_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c44);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_gain_lock_win_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c44);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c44,localVal);
}

static inline uint32_t bz_agc_bz_phy_agc_rssi_upd_cyc_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_bz_phy_agc_rssi_upd_cyc_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002c48,localVal);
}

static inline uint32_t bz_agc_gain_unlock_ndl1_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_gain_unlock_ndl1_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c48,localVal);
}

static inline uint32_t bz_agc_gain_unlock_ndl2_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void bz_agc_gain_unlock_ndl2_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40002c48,localVal);
}

static inline uint32_t bz_agc_gain_unlock_th_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_gain_unlock_th_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c48,localVal);
}

static inline uint32_t bz_agc_gain_unlock_win_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_gain_unlock_win_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c48);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c48,localVal);
}

static inline uint32_t bz_agc_gain_lock_ndl1_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c4c);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_gain_lock_ndl1_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c4c);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c4c,localVal);
}

static inline uint32_t bz_agc_gain_lock_ndl2_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c4c);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void bz_agc_gain_lock_ndl2_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c4c);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40002c4c,localVal);
}

static inline uint32_t bz_agc_gain_lock_th_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c4c);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_gain_lock_th_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c4c);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c4c,localVal);
}

static inline uint32_t bz_agc_gain_lock_win_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c4c);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_gain_lock_win_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c4c);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c4c,localVal);
}

static inline uint32_t bz_agc_bz_phy_agc_rssi_upd_cyc_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_bz_phy_agc_rssi_upd_cyc_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002c50,localVal);
}

static inline uint32_t bz_agc_gain_unlock_ndl1_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_gain_unlock_ndl1_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c50,localVal);
}

static inline uint32_t bz_agc_gain_unlock_ndl2_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void bz_agc_gain_unlock_ndl2_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40002c50,localVal);
}

static inline uint32_t bz_agc_gain_unlock_th_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_gain_unlock_th_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c50,localVal);
}

static inline uint32_t bz_agc_gain_unlock_win_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_gain_unlock_win_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c50);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c50,localVal);
}

static inline uint32_t bz_agc_gain_lock_ndl1_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c54);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_gain_lock_ndl1_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c54);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c54,localVal);
}

static inline uint32_t bz_agc_gain_lock_ndl2_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c54);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void bz_agc_gain_lock_ndl2_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c54);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40002c54,localVal);
}

static inline uint32_t bz_agc_gain_lock_th_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c54);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_gain_lock_th_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c54);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c54,localVal);
}

static inline uint32_t bz_agc_gain_lock_win_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c54);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_gain_lock_win_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c54);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c54,localVal);
}

static inline uint32_t bz_agc_bz_phy_agc_rssi_upd_cyc_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_bz_phy_agc_rssi_upd_cyc_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002c58,localVal);
}

static inline uint32_t bz_agc_gain_unlock_ndl1_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_gain_unlock_ndl1_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c58,localVal);
}

static inline uint32_t bz_agc_gain_unlock_ndl2_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void bz_agc_gain_unlock_ndl2_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40002c58,localVal);
}

static inline uint32_t bz_agc_gain_unlock_th_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_gain_unlock_th_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c58,localVal);
}

static inline uint32_t bz_agc_gain_unlock_win_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_gain_unlock_win_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c58);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c58,localVal);
}

static inline uint32_t bz_agc_gain_lock_ndl1_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c5c);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void bz_agc_gain_lock_ndl1_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c5c);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x40002c5c,localVal);
}

static inline uint32_t bz_agc_gain_lock_ndl2_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c5c);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void bz_agc_gain_lock_ndl2_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c5c);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40002c5c,localVal);
}

static inline uint32_t bz_agc_gain_lock_th_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c5c);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_gain_lock_th_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c5c);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c5c,localVal);
}

static inline uint32_t bz_agc_gain_lock_win_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c5c);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_gain_lock_win_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c5c);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c5c,localVal);
}

static inline uint32_t bz_agc_adc_loop_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c60);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void bz_agc_adc_loop_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c60);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40002c60,localVal);
}

static inline uint32_t bz_agc_adc_gt_err_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c60);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void bz_agc_adc_gt_err_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c60);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40002c60,localVal);
}

static inline uint32_t bz_agc_adc_gt_hyst_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c60);
    return ((localVal & ((uint32_t)0x0003fc00)) >> 10);
}

static inline void bz_agc_adc_gt_hyst_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c60);
    localVal &= ~((uint32_t)0x0003fc00);
    localVal |= (x << 10)&((uint32_t)0x0003fc00);
    REG_PL_WR(0x40002c60,localVal);
}

static inline uint32_t bz_agc_adc_gt_err_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c60);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_agc_adc_gt_err_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c60);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002c60,localVal);
}

static inline uint32_t bz_agc_adc_up_coeff_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    return ((localVal & ((uint32_t)0x0fc00000)) >> 22);
}

static inline void bz_agc_adc_up_coeff_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    localVal &= ~((uint32_t)0x0fc00000);
    localVal |= (x << 22)&((uint32_t)0x0fc00000);
    REG_PL_WR(0x40002c64,localVal);
}

static inline uint32_t bz_agc_adc_dn_coeff_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_adc_dn_coeff_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002c64,localVal);
}

static inline uint32_t bz_agc_adc_fast_coeff_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    return ((localVal & ((uint32_t)0x0000fc00)) >> 10);
}

static inline void bz_agc_adc_fast_coeff_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    localVal &= ~((uint32_t)0x0000fc00);
    localVal |= (x << 10)&((uint32_t)0x0000fc00);
    REG_PL_WR(0x40002c64,localVal);
}

static inline uint32_t bz_agc_adc_slow_coeff_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    return ((localVal & ((uint32_t)0x000003f0)) >> 4);
}

static inline void bz_agc_adc_slow_coeff_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    localVal &= ~((uint32_t)0x000003f0);
    localVal |= (x << 4)&((uint32_t)0x000003f0);
    REG_PL_WR(0x40002c64,localVal);
}

static inline uint32_t bz_agc_adc_gt_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_adc_gt_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c64);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c64,localVal);
}

static inline uint32_t bz_agc_adc_up_coeff_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    return ((localVal & ((uint32_t)0x0fc00000)) >> 22);
}

static inline void bz_agc_adc_up_coeff_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    localVal &= ~((uint32_t)0x0fc00000);
    localVal |= (x << 22)&((uint32_t)0x0fc00000);
    REG_PL_WR(0x40002c68,localVal);
}

static inline uint32_t bz_agc_adc_dn_coeff_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_adc_dn_coeff_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002c68,localVal);
}

static inline uint32_t bz_agc_adc_fast_coeff_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    return ((localVal & ((uint32_t)0x0000fc00)) >> 10);
}

static inline void bz_agc_adc_fast_coeff_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    localVal &= ~((uint32_t)0x0000fc00);
    localVal |= (x << 10)&((uint32_t)0x0000fc00);
    REG_PL_WR(0x40002c68,localVal);
}

static inline uint32_t bz_agc_adc_slow_coeff_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    return ((localVal & ((uint32_t)0x000003f0)) >> 4);
}

static inline void bz_agc_adc_slow_coeff_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    localVal &= ~((uint32_t)0x000003f0);
    localVal |= (x << 4)&((uint32_t)0x000003f0);
    REG_PL_WR(0x40002c68,localVal);
}

static inline uint32_t bz_agc_adc_gt_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_adc_gt_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c68);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c68,localVal);
}

static inline uint32_t bz_agc_adc_up_coeff_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    return ((localVal & ((uint32_t)0x0fc00000)) >> 22);
}

static inline void bz_agc_adc_up_coeff_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    localVal &= ~((uint32_t)0x0fc00000);
    localVal |= (x << 22)&((uint32_t)0x0fc00000);
    REG_PL_WR(0x40002c6c,localVal);
}

static inline uint32_t bz_agc_adc_dn_coeff_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_adc_dn_coeff_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002c6c,localVal);
}

static inline uint32_t bz_agc_adc_fast_coeff_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    return ((localVal & ((uint32_t)0x0000fc00)) >> 10);
}

static inline void bz_agc_adc_fast_coeff_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    localVal &= ~((uint32_t)0x0000fc00);
    localVal |= (x << 10)&((uint32_t)0x0000fc00);
    REG_PL_WR(0x40002c6c,localVal);
}

static inline uint32_t bz_agc_adc_slow_coeff_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    return ((localVal & ((uint32_t)0x000003f0)) >> 4);
}

static inline void bz_agc_adc_slow_coeff_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    localVal &= ~((uint32_t)0x000003f0);
    localVal |= (x << 4)&((uint32_t)0x000003f0);
    REG_PL_WR(0x40002c6c,localVal);
}

static inline uint32_t bz_agc_adc_gt_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_adc_gt_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c6c);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c6c,localVal);
}

static inline uint32_t bz_agc_adc_up_coeff_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    return ((localVal & ((uint32_t)0x0fc00000)) >> 22);
}

static inline void bz_agc_adc_up_coeff_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    localVal &= ~((uint32_t)0x0fc00000);
    localVal |= (x << 22)&((uint32_t)0x0fc00000);
    REG_PL_WR(0x40002c70,localVal);
}

static inline uint32_t bz_agc_adc_dn_coeff_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_adc_dn_coeff_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002c70,localVal);
}

static inline uint32_t bz_agc_adc_fast_coeff_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    return ((localVal & ((uint32_t)0x0000fc00)) >> 10);
}

static inline void bz_agc_adc_fast_coeff_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    localVal &= ~((uint32_t)0x0000fc00);
    localVal |= (x << 10)&((uint32_t)0x0000fc00);
    REG_PL_WR(0x40002c70,localVal);
}

static inline uint32_t bz_agc_adc_slow_coeff_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    return ((localVal & ((uint32_t)0x000003f0)) >> 4);
}

static inline void bz_agc_adc_slow_coeff_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    localVal &= ~((uint32_t)0x000003f0);
    localVal |= (x << 4)&((uint32_t)0x000003f0);
    REG_PL_WR(0x40002c70,localVal);
}

static inline uint32_t bz_agc_adc_gt_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_adc_gt_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c70);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c70,localVal);
}

static inline uint32_t bz_agc_fe_loop_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c74);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void bz_agc_fe_loop_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c74);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40002c74,localVal);
}

static inline uint32_t bz_agc_fe_gt_err_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c74);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void bz_agc_fe_gt_err_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c74);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40002c74,localVal);
}

static inline uint32_t bz_agc_fe_gt_hyst_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c74);
    return ((localVal & ((uint32_t)0x0003fc00)) >> 10);
}

static inline void bz_agc_fe_gt_hyst_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c74);
    localVal &= ~((uint32_t)0x0003fc00);
    localVal |= (x << 10)&((uint32_t)0x0003fc00);
    REG_PL_WR(0x40002c74,localVal);
}

static inline uint32_t bz_agc_fe_gt_err_th_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c74);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void bz_agc_fe_gt_err_th_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c74);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40002c74,localVal);
}

static inline uint32_t bz_agc_fe_fast_coeff_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    return ((localVal & ((uint32_t)0x0fc00000)) >> 22);
}

static inline void bz_agc_fe_fast_coeff_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    localVal &= ~((uint32_t)0x0fc00000);
    localVal |= (x << 22)&((uint32_t)0x0fc00000);
    REG_PL_WR(0x40002c78,localVal);
}

static inline uint32_t bz_agc_fe_slow_coeff_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_fe_slow_coeff_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002c78,localVal);
}

static inline uint32_t bz_agc_fe_up_coeff_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    return ((localVal & ((uint32_t)0x0000fc00)) >> 10);
}

static inline void bz_agc_fe_up_coeff_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    localVal &= ~((uint32_t)0x0000fc00);
    localVal |= (x << 10)&((uint32_t)0x0000fc00);
    REG_PL_WR(0x40002c78,localVal);
}

static inline uint32_t bz_agc_fe_dn_coeff_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    return ((localVal & ((uint32_t)0x000003f0)) >> 4);
}

static inline void bz_agc_fe_dn_coeff_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    localVal &= ~((uint32_t)0x000003f0);
    localVal |= (x << 4)&((uint32_t)0x000003f0);
    REG_PL_WR(0x40002c78,localVal);
}

static inline uint32_t bz_agc_fe_gt_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_fe_gt_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c78);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c78,localVal);
}

static inline uint32_t bz_agc_fe_fast_coeff_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    return ((localVal & ((uint32_t)0x0fc00000)) >> 22);
}

static inline void bz_agc_fe_fast_coeff_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    localVal &= ~((uint32_t)0x0fc00000);
    localVal |= (x << 22)&((uint32_t)0x0fc00000);
    REG_PL_WR(0x40002c7c,localVal);
}

static inline uint32_t bz_agc_fe_slow_coeff_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_fe_slow_coeff_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002c7c,localVal);
}

static inline uint32_t bz_agc_fe_up_coeff_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    return ((localVal & ((uint32_t)0x0000fc00)) >> 10);
}

static inline void bz_agc_fe_up_coeff_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    localVal &= ~((uint32_t)0x0000fc00);
    localVal |= (x << 10)&((uint32_t)0x0000fc00);
    REG_PL_WR(0x40002c7c,localVal);
}

static inline uint32_t bz_agc_fe_dn_coeff_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    return ((localVal & ((uint32_t)0x000003f0)) >> 4);
}

static inline void bz_agc_fe_dn_coeff_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    localVal &= ~((uint32_t)0x000003f0);
    localVal |= (x << 4)&((uint32_t)0x000003f0);
    REG_PL_WR(0x40002c7c,localVal);
}

static inline uint32_t bz_agc_fe_gt_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_fe_gt_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c7c);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c7c,localVal);
}

static inline uint32_t bz_agc_fe_fast_coeff_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    return ((localVal & ((uint32_t)0x0fc00000)) >> 22);
}

static inline void bz_agc_fe_fast_coeff_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    localVal &= ~((uint32_t)0x0fc00000);
    localVal |= (x << 22)&((uint32_t)0x0fc00000);
    REG_PL_WR(0x40002c80,localVal);
}

static inline uint32_t bz_agc_fe_slow_coeff_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_fe_slow_coeff_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002c80,localVal);
}

static inline uint32_t bz_agc_fe_up_coeff_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    return ((localVal & ((uint32_t)0x0000fc00)) >> 10);
}

static inline void bz_agc_fe_up_coeff_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    localVal &= ~((uint32_t)0x0000fc00);
    localVal |= (x << 10)&((uint32_t)0x0000fc00);
    REG_PL_WR(0x40002c80,localVal);
}

static inline uint32_t bz_agc_fe_dn_coeff_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    return ((localVal & ((uint32_t)0x000003f0)) >> 4);
}

static inline void bz_agc_fe_dn_coeff_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    localVal &= ~((uint32_t)0x000003f0);
    localVal |= (x << 4)&((uint32_t)0x000003f0);
    REG_PL_WR(0x40002c80,localVal);
}

static inline uint32_t bz_agc_fe_gt_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_fe_gt_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c80);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c80,localVal);
}

static inline uint32_t bz_agc_fe_fast_coeff_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    return ((localVal & ((uint32_t)0x0fc00000)) >> 22);
}

static inline void bz_agc_fe_fast_coeff_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    localVal &= ~((uint32_t)0x0fc00000);
    localVal |= (x << 22)&((uint32_t)0x0fc00000);
    REG_PL_WR(0x40002c84,localVal);
}

static inline uint32_t bz_agc_fe_slow_coeff_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_fe_slow_coeff_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002c84,localVal);
}

static inline uint32_t bz_agc_fe_up_coeff_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    return ((localVal & ((uint32_t)0x0000fc00)) >> 10);
}

static inline void bz_agc_fe_up_coeff_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    localVal &= ~((uint32_t)0x0000fc00);
    localVal |= (x << 10)&((uint32_t)0x0000fc00);
    REG_PL_WR(0x40002c84,localVal);
}

static inline uint32_t bz_agc_fe_dn_coeff_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    return ((localVal & ((uint32_t)0x000003f0)) >> 4);
}

static inline void bz_agc_fe_dn_coeff_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    localVal &= ~((uint32_t)0x000003f0);
    localVal |= (x << 4)&((uint32_t)0x000003f0);
    REG_PL_WR(0x40002c84,localVal);
}

static inline uint32_t bz_agc_fe_gt_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_fe_gt_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c84);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002c84,localVal);
}

static inline uint32_t bz_agc_tia_sat_rst_rbb_mode_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c88);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void bz_agc_tia_sat_rst_rbb_mode_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c88);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40002c88,localVal);
}

static inline uint32_t bz_agc_tia_sat_rst_dg_mode_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c88);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void bz_agc_tia_sat_rst_dg_mode_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c88);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40002c88,localVal);
}

static inline uint32_t bz_agc_adc_sat_rst_dg_mode_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c88);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void bz_agc_adc_sat_rst_dg_mode_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c88);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40002c88,localVal);
}

static inline uint32_t bz_agc_tia_sat_rst_rbb_mode_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c8c);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void bz_agc_tia_sat_rst_rbb_mode_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c8c);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40002c8c,localVal);
}

static inline uint32_t bz_agc_tia_sat_rst_dg_mode_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c8c);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void bz_agc_tia_sat_rst_dg_mode_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c8c);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40002c8c,localVal);
}

static inline uint32_t bz_agc_adc_sat_rst_dg_mode_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c8c);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void bz_agc_adc_sat_rst_dg_mode_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c8c);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40002c8c,localVal);
}

static inline uint32_t bz_agc_tia_sat_rst_rbb_mode_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c90);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void bz_agc_tia_sat_rst_rbb_mode_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c90);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40002c90,localVal);
}

static inline uint32_t bz_agc_tia_sat_rst_dg_mode_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c90);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void bz_agc_tia_sat_rst_dg_mode_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c90);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40002c90,localVal);
}

static inline uint32_t bz_agc_adc_sat_rst_dg_mode_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c90);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void bz_agc_adc_sat_rst_dg_mode_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c90);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40002c90,localVal);
}

static inline uint32_t bz_agc_tia_sat_rst_rbb_mode_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c94);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void bz_agc_tia_sat_rst_rbb_mode_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c94);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40002c94,localVal);
}

static inline uint32_t bz_agc_tia_sat_rst_dg_mode_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c94);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void bz_agc_tia_sat_rst_dg_mode_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c94);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40002c94,localVal);
}

static inline uint32_t bz_agc_adc_sat_rst_dg_mode_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c94);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void bz_agc_adc_sat_rst_dg_mode_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c94);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40002c94,localVal);
}

static inline uint32_t bz_agc_proc_dly_tia_sat_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c98);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void bz_agc_proc_dly_tia_sat_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c98);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x40002c98,localVal);
}

static inline uint32_t bz_agc_proc_dly_adc_sat_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c98);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_proc_dly_adc_sat_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c98);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c98,localVal);
}

static inline uint32_t bz_agc_proc_dly_dg_sat_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c98);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_proc_dly_dg_sat_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c98);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c98,localVal);
}

static inline uint32_t bz_agc_proc_dly_tia_sat_rbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c9c);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void bz_agc_proc_dly_tia_sat_rbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c9c);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x40002c9c,localVal);
}

static inline uint32_t bz_agc_proc_dly_adc_sat_rbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c9c);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_proc_dly_adc_sat_rbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c9c);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002c9c,localVal);
}

static inline uint32_t bz_agc_proc_dly_dg_sat_rbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002c9c);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_proc_dly_dg_sat_rbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002c9c);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002c9c,localVal);
}

static inline uint32_t bz_agc_proc_dly_tia_sat_dg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca0);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void bz_agc_proc_dly_tia_sat_dg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca0);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x40002ca0,localVal);
}

static inline uint32_t bz_agc_proc_dly_adc_sat_dg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca0);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_proc_dly_adc_sat_dg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca0);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002ca0,localVal);
}

static inline uint32_t bz_agc_proc_dly_dg_sat_dg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca0);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_proc_dly_dg_sat_dg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca0);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002ca0,localVal);
}

static inline uint32_t bz_agc_proc_dly_rbb_adj_bb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca4);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void bz_agc_proc_dly_rbb_adj_bb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca4);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x40002ca4,localVal);
}

static inline uint32_t bz_agc_proc_dly_rbb_adj_dg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca4);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void bz_agc_proc_dly_rbb_adj_dg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca4);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40002ca4,localVal);
}

static inline uint32_t bz_agc_proc_dly_dg_adj_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca4);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void bz_agc_proc_dly_dg_adj_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca4);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40002ca4,localVal);
}

static inline uint32_t bz_agc_lna_ind_init_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca8);
    return ((localVal & ((uint32_t)0x0f000000)) >> 24);
}

static inline void bz_agc_lna_ind_init_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca8);
    localVal &= ~((uint32_t)0x0f000000);
    localVal |= (x << 24)&((uint32_t)0x0f000000);
    REG_PL_WR(0x40002ca8,localVal);
}

static inline uint32_t bz_agc_lna_ind_max_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca8);
    return ((localVal & ((uint32_t)0x00000f00)) >> 8);
}

static inline void bz_agc_lna_ind_max_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca8);
    localVal &= ~((uint32_t)0x00000f00);
    localVal |= (x << 8)&((uint32_t)0x00000f00);
    REG_PL_WR(0x40002ca8,localVal);
}

static inline uint32_t bz_agc_lna_ind_min_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ca8);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void bz_agc_lna_ind_min_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ca8);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40002ca8,localVal);
}

static inline uint32_t bz_agc_rbb_ind_init_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cac);
    return ((localVal & ((uint32_t)0x1f000000)) >> 24);
}

static inline void bz_agc_rbb_ind_init_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cac);
    localVal &= ~((uint32_t)0x1f000000);
    localVal |= (x << 24)&((uint32_t)0x1f000000);
    REG_PL_WR(0x40002cac,localVal);
}

static inline uint32_t bz_agc_rbb_ind_step_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cac);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void bz_agc_rbb_ind_step_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cac);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40002cac,localVal);
}

static inline uint32_t bz_agc_rbb_ind_max_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cac);
    return ((localVal & ((uint32_t)0x00001f00)) >> 8);
}

static inline void bz_agc_rbb_ind_max_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cac);
    localVal &= ~((uint32_t)0x00001f00);
    localVal |= (x << 8)&((uint32_t)0x00001f00);
    REG_PL_WR(0x40002cac,localVal);
}

static inline uint32_t bz_agc_rbb_ind_min_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cac);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void bz_agc_rbb_ind_min_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cac);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40002cac,localVal);
}

static inline uint32_t bz_agc_dg_ind_init_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb0);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_dg_ind_init_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb0);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002cb0,localVal);
}

static inline uint32_t bz_agc_dg_ind_step_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb0);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_dg_ind_step_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb0);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002cb0,localVal);
}

static inline uint32_t bz_agc_dg_ind_max_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb0);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void bz_agc_dg_ind_max_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb0);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40002cb0,localVal);
}

static inline uint32_t bz_agc_dg_ind_min_zb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb0);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void bz_agc_dg_ind_min_zb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb0);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40002cb0,localVal);
}

static inline uint32_t bz_agc_dg_ind_init_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb4);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_dg_ind_init_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb4);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002cb4,localVal);
}

static inline uint32_t bz_agc_dg_ind_step_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb4);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_dg_ind_step_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb4);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002cb4,localVal);
}

static inline uint32_t bz_agc_dg_ind_max_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb4);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void bz_agc_dg_ind_max_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb4);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40002cb4,localVal);
}

static inline uint32_t bz_agc_dg_ind_min_ble1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb4);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void bz_agc_dg_ind_min_ble1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb4);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40002cb4,localVal);
}

static inline uint32_t bz_agc_dg_ind_init_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb8);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_dg_ind_init_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb8);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002cb8,localVal);
}

static inline uint32_t bz_agc_dg_ind_step_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb8);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_dg_ind_step_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb8);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002cb8,localVal);
}

static inline uint32_t bz_agc_dg_ind_max_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb8);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void bz_agc_dg_ind_max_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb8);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40002cb8,localVal);
}

static inline uint32_t bz_agc_dg_ind_min_ble2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cb8);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void bz_agc_dg_ind_min_ble2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cb8);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40002cb8,localVal);
}

static inline uint32_t bz_agc_dg_ind_init_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cbc);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_dg_ind_init_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cbc);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002cbc,localVal);
}

static inline uint32_t bz_agc_dg_ind_step_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cbc);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_dg_ind_step_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cbc);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002cbc,localVal);
}

static inline uint32_t bz_agc_dg_ind_max_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cbc);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void bz_agc_dg_ind_max_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cbc);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40002cbc,localVal);
}

static inline uint32_t bz_agc_dg_ind_min_blec_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cbc);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void bz_agc_dg_ind_min_blec_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cbc);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40002cbc,localVal);
}

static inline uint32_t bz_agc_lna_ind_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cc0);
    return ((localVal & ((uint32_t)0x0f000000)) >> 24);
}

static inline uint32_t bz_agc_rbb_ind_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cc0);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline uint32_t bz_agc_dg_ind_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cc0);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline uint32_t bz_agc_rssi_out_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cc0);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline uint32_t bz_agc_status_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cc4);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t bz_agc_status_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cc8);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t bz_agc_status_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ccc);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t bz_agc_agc_ctrl_reserved_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002cd0);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void bz_agc_agc_ctrl_reserved_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002cd0);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40002cd0,localVal);
}

static inline uint32_t bz_agc_lna_gain_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce0);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_lna_gain_3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce0);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002ce0,localVal);
}

static inline uint32_t bz_agc_lna_gain_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce0);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_lna_gain_2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce0);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002ce0,localVal);
}

static inline uint32_t bz_agc_lna_gain_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce0);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void bz_agc_lna_gain_1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce0);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40002ce0,localVal);
}

static inline uint32_t bz_agc_lna_gain_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce0);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void bz_agc_lna_gain_0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce0);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40002ce0,localVal);
}

static inline uint32_t bz_agc_lna_gain_7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce4);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void bz_agc_lna_gain_7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce4);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40002ce4,localVal);
}

static inline uint32_t bz_agc_lna_gain_6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce4);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void bz_agc_lna_gain_6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce4);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40002ce4,localVal);
}

static inline uint32_t bz_agc_lna_gain_5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce4);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void bz_agc_lna_gain_5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce4);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40002ce4,localVal);
}

static inline uint32_t bz_agc_lna_gain_4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce4);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void bz_agc_lna_gain_4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce4);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40002ce4,localVal);
}

static inline uint32_t bz_agc_lna_gain_8_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40002ce8);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void bz_agc_lna_gain_8_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40002ce8);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40002ce8,localVal);
}

#endif