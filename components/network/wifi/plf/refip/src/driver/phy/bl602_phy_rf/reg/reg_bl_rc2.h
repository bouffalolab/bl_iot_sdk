#ifndef _REG_BL_RC2_H_
#define _REG_BL_RC2_H_

#include "co_int.h"
#include "arch.h"
#include "_reg_access.h"

static inline uint32_t rc2_rx0_vga_approx_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c040);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rc2_rx0_vga_approx_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c040);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x44c0c040,localVal);
}

static inline uint32_t rc2_rx0_vga_gain_min_db_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c040);
    return ((localVal & ((uint32_t)0x7e000000)) >> 25);
}

static inline void rc2_rx0_vga_gain_min_db_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c040);
    localVal &= ~((uint32_t)0x7e000000);
    localVal |= (x << 25)&((uint32_t)0x7e000000);
    REG_PL_WR(0x44c0c040,localVal);
}

static inline uint32_t rc2_rx0_vga_idx_max_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c040);
    return ((localVal & ((uint32_t)0x01f00000)) >> 20);
}

static inline void rc2_rx0_vga_idx_max_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c040);
    localVal &= ~((uint32_t)0x01f00000);
    localVal |= (x << 20)&((uint32_t)0x01f00000);
    REG_PL_WR(0x44c0c040,localVal);
}

static inline uint32_t rc2_rx0_vga_idx_min_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c040);
    return ((localVal & ((uint32_t)0x000f8000)) >> 15);
}

static inline void rc2_rx0_vga_idx_min_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c040);
    localVal &= ~((uint32_t)0x000f8000);
    localVal |= (x << 15)&((uint32_t)0x000f8000);
    REG_PL_WR(0x44c0c040,localVal);
}

static inline uint32_t rc2_rx0_lna_idx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c044);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline uint32_t rc2_rx0_lna_idx_max_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c044);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rc2_rx0_lna_idx_max_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c044);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x44c0c044,localVal);
}

static inline uint32_t rc2_rx0_lna_idx_min_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c044);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void rc2_rx0_lna_idx_min_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c044);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x44c0c044,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c080);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rc2_rx0_lna_gain_3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c080);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x44c0c080,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c080);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void rc2_rx0_lna_gain_2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c080);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x44c0c080,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c080);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rc2_rx0_lna_gain_1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c080);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x44c0c080,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c080);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void rc2_rx0_lna_gain_0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c080);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x44c0c080,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c084);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rc2_rx0_lna_gain_7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c084);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x44c0c084,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c084);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void rc2_rx0_lna_gain_6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c084);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x44c0c084,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c084);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rc2_rx0_lna_gain_5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c084);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x44c0c084,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c084);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void rc2_rx0_lna_gain_4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c084);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x44c0c084,localVal);
}

static inline uint32_t rc2_rx0_lna_gain_8_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c088);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void rc2_rx0_lna_gain_8_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c088);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x44c0c088,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c180);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rc2_rx0_nf_gain_3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c180);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x44c0c180,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c180);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rc2_rx0_nf_gain_2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c180);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x44c0c180,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c180);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rc2_rx0_nf_gain_1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c180);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x44c0c180,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c180);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rc2_rx0_nf_gain_0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c180);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x44c0c180,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c184);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rc2_rx0_nf_gain_7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c184);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x44c0c184,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c184);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rc2_rx0_nf_gain_6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c184);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x44c0c184,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c184);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rc2_rx0_nf_gain_5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c184);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x44c0c184,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c184);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rc2_rx0_nf_gain_4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c184);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x44c0c184,localVal);
}

static inline uint32_t rc2_rx0_nf_gain_8_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c188);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rc2_rx0_nf_gain_8_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c188);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x44c0c188,localVal);
}

static inline uint32_t rc2_txhbf20coeffsel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c218);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void rc2_txhbf20coeffsel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c218);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x44c0c218,localVal);
}

static inline uint32_t rc2_rx_ramp_ctrl_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rc2_rx_ramp_ctrl_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x44c0c800,localVal);
}

static inline uint32_t rc2_feadc0_dly_ena_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rc2_feadc0_dly_ena_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x44c0c800,localVal);
}

static inline uint32_t rc2_feadc0_dly_num_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

static inline void rc2_feadc0_dly_num_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    localVal &= ~((uint32_t)0x00070000);
    localVal |= (x << 16)&((uint32_t)0x00070000);
    REG_PL_WR(0x44c0c800,localVal);
}

static inline uint32_t rc2_fe0dcest_dly_ena_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rc2_fe0dcest_dly_ena_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x44c0c800,localVal);
}

static inline uint32_t rc2_fe0dcest_dly_num_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    return ((localVal & ((uint32_t)0x00000f00)) >> 8);
}

static inline void rc2_fe0dcest_dly_num_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    localVal &= ~((uint32_t)0x00000f00);
    localVal |= (x << 8)&((uint32_t)0x00000f00);
    REG_PL_WR(0x44c0c800,localVal);
}

static inline uint32_t rc2_fe0dcest_dly_ena_40_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rc2_fe0dcest_dly_ena_40_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x44c0c800,localVal);
}

static inline uint32_t rc2_fe0dcest_dly_num_40_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void rc2_fe0dcest_dly_num_40_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c800);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x44c0c800,localVal);
}

static inline uint32_t rc2_txdsssdiggainlin0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c80c);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rc2_txdsssdiggainlin0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c80c);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x44c0c80c,localVal);
}

static inline uint32_t rc2_pkdet_cnt_win_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c814);
    return ((localVal & ((uint32_t)0x000003c0)) >> 6);
}

static inline void rc2_pkdet_cnt_win_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c814);
    localVal &= ~((uint32_t)0x000003c0);
    localVal |= (x << 6)&((uint32_t)0x000003c0);
    REG_PL_WR(0x44c0c814,localVal);
}

static inline uint32_t rc2_pkdet_cnt_thr_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c814);
    return ((localVal & ((uint32_t)0x0000003c)) >> 2);
}

static inline void rc2_pkdet_cnt_thr_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c814);
    localVal &= ~((uint32_t)0x0000003c);
    localVal |= (x << 2)&((uint32_t)0x0000003c);
    REG_PL_WR(0x44c0c814,localVal);
}

static inline uint32_t rc2_pkdet_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c814);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rc2_pkdet_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c814);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x44c0c814,localVal);
}

static inline uint32_t rc2_inbdpowfastvalid_cnt_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    return ((localVal & ((uint32_t)0x00ff8000)) >> 15);
}

static inline void rc2_inbdpowfastvalid_cnt_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    localVal &= ~((uint32_t)0x00ff8000);
    localVal |= (x << 15)&((uint32_t)0x00ff8000);
    REG_PL_WR(0x44c0c82c,localVal);
}

static inline uint32_t rc2_inbdpowfastvalid_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rc2_inbdpowfastvalid_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x44c0c82c,localVal);
}

static inline uint32_t rc2_inbdpowinfthr_adj_step_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rc2_inbdpowinfthr_adj_step_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x44c0c82c,localVal);
}

static inline uint32_t rc2_inbdpowinfthr_adj_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rc2_inbdpowinfthr_adj_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x44c0c82c,localVal);
}

static inline uint32_t rc2_inbdpowsupthr_adj_step_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    return ((localVal & ((uint32_t)0x00000600)) >> 9);
}

static inline void rc2_inbdpowsupthr_adj_step_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    localVal &= ~((uint32_t)0x00000600);
    localVal |= (x << 9)&((uint32_t)0x00000600);
    REG_PL_WR(0x44c0c82c,localVal);
}

static inline uint32_t rc2_inbdpowsupthr_adj_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rc2_inbdpowsupthr_adj_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x44c0c82c,localVal);
}

static inline uint32_t rc2_inbdpow_adj_thr_dbm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void rc2_inbdpow_adj_thr_dbm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c82c);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x44c0c82c,localVal);
}

static inline uint32_t rc2_evt4op1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    return ((localVal & ((uint32_t)0xfc000000)) >> 26);
}

static inline void rc2_evt4op1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    localVal &= ~((uint32_t)0xfc000000);
    localVal |= (x << 26)&((uint32_t)0xfc000000);
    REG_PL_WR(0x44c0c830,localVal);
}

static inline uint32_t rc2_evt4op2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    return ((localVal & ((uint32_t)0x03f00000)) >> 20);
}

static inline void rc2_evt4op2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    localVal &= ~((uint32_t)0x03f00000);
    localVal |= (x << 20)&((uint32_t)0x03f00000);
    REG_PL_WR(0x44c0c830,localVal);
}

static inline uint32_t rc2_evt4op3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    return ((localVal & ((uint32_t)0x000fc000)) >> 14);
}

static inline void rc2_evt4op3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    localVal &= ~((uint32_t)0x000fc000);
    localVal |= (x << 14)&((uint32_t)0x000fc000);
    REG_PL_WR(0x44c0c830,localVal);
}

static inline uint32_t rc2_evt4pathcomb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rc2_evt4pathcomb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x44c0c830,localVal);
}

static inline uint32_t rc2_evt4opcomb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    return ((localVal & ((uint32_t)0x00001c00)) >> 10);
}

static inline void rc2_evt4opcomb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    localVal &= ~((uint32_t)0x00001c00);
    localVal |= (x << 10)&((uint32_t)0x00001c00);
    REG_PL_WR(0x44c0c830,localVal);
}

static inline uint32_t rc2_evt4tgtadd_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    return ((localVal & ((uint32_t)0x000001ff)) >> 0);
}

static inline void rc2_evt4tgtadd_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c830);
    localVal &= ~((uint32_t)0x000001ff);
    localVal |= (x << 0)&((uint32_t)0x000001ff);
    REG_PL_WR(0x44c0c830,localVal);
}

static inline uint32_t rc2_adcpowinsel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c834);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rc2_adcpowinsel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c834);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x44c0c834,localVal);
}

static inline uint32_t rc2_reflevofdmthd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c838);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rc2_reflevofdmthd_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c838);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x44c0c838,localVal);
}

static inline uint32_t rc2_reflevofdmthd_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c838);
    return ((localVal & ((uint32_t)0x0007ffff)) >> 0);
}

static inline void rc2_reflevofdmthd_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c838);
    localVal &= ~((uint32_t)0x0007ffff);
    localVal |= (x << 0)&((uint32_t)0x0007ffff);
    REG_PL_WR(0x44c0c838,localVal);
}

static inline uint32_t rc2_reflevdsssthd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c83c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rc2_reflevdsssthd_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c83c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x44c0c83c,localVal);
}

static inline uint32_t rc2_reflevdsssthd_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c83c);
    return ((localVal & ((uint32_t)0x000fffff)) >> 0);
}

static inline void rc2_reflevdsssthd_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c83c);
    localVal &= ~((uint32_t)0x000fffff);
    localVal |= (x << 0)&((uint32_t)0x000fffff);
    REG_PL_WR(0x44c0c83c,localVal);
}

static inline uint32_t rc2_reflevdssscontthd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c840);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rc2_reflevdssscontthd_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c840);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x44c0c840,localVal);
}

static inline uint32_t rc2_reflevdssscontthd_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c840);
    return ((localVal & ((uint32_t)0x003fffff)) >> 0);
}

static inline void rc2_reflevdssscontthd_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c840);
    localVal &= ~((uint32_t)0x003fffff);
    localVal |= (x << 0)&((uint32_t)0x003fffff);
    REG_PL_WR(0x44c0c840,localVal);
}

static inline uint32_t rc2_agcrampupthr2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c844);
    return ((localVal & ((uint32_t)0x3fff0000)) >> 16);
}

static inline void rc2_agcrampupthr2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c844);
    localVal &= ~((uint32_t)0x3fff0000);
    localVal |= (x << 16)&((uint32_t)0x3fff0000);
    REG_PL_WR(0x44c0c844,localVal);
}

static inline uint32_t rc2_agcrampupthr1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c844);
    return ((localVal & ((uint32_t)0x00003fff)) >> 0);
}

static inline void rc2_agcrampupthr1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c844);
    localVal &= ~((uint32_t)0x00003fff);
    localVal |= (x << 0)&((uint32_t)0x00003fff);
    REG_PL_WR(0x44c0c844,localVal);
}

static inline uint32_t rc2_agcrampupthr3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c848);
    return ((localVal & ((uint32_t)0x00003fff)) >> 0);
}

static inline void rc2_agcrampupthr3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c848);
    localVal &= ~((uint32_t)0x00003fff);
    localVal |= (x << 0)&((uint32_t)0x00003fff);
    REG_PL_WR(0x44c0c848,localVal);
}

static inline uint32_t rc2_agcrampupcorrecten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c84c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rc2_agcrampupcorrecten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c84c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x44c0c84c,localVal);
}

static inline uint32_t rc2_agcrampupcorrect3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c84c);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void rc2_agcrampupcorrect3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c84c);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x44c0c84c,localVal);
}

static inline uint32_t rc2_agcrampupcorrect2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c84c);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rc2_agcrampupcorrect2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c84c);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x44c0c84c,localVal);
}

static inline uint32_t rc2_agcrampupcorrect1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c84c);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void rc2_agcrampupcorrect1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x44c0c84c);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x44c0c84c,localVal);
}

static inline uint32_t rc2_sts_agc_gain_target0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c900);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline uint32_t rc2_sts_rx0_lna_gain_idx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c904);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline uint32_t rc2_sts_rx0_rbb_cfg_idx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c904);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline uint32_t rc2_sts_rx0_lna_gain_db_s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c908);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline uint32_t rc2_sts_rx0_vga_gain_db_s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c908);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline uint32_t rc2_sts_rx0_total_gain_db_s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c908);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline uint32_t rc2_sts_rx0_nf_gain_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x44c0c908);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

#endif