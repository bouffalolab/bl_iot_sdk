#ifndef _REG_RF_H_
#define _REG_RF_H_

#include "co_int.h"
#include "arch.h"
#include "_reg_access.h"

static inline uint32_t rf_hw_rev_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001000);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline uint32_t rf_fw_rev_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001000);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline uint32_t rf_id_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001000);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline uint32_t rf_rc_state_value_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

static inline uint32_t rf_fsm_st_int_set_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline void rf_fsm_st_int_set_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    localVal &= ~((uint32_t)0x01000000);
    localVal |= (x << 24)&((uint32_t)0x01000000);
    REG_PL_WR(0x40001004,localVal);
}

static inline uint32_t rf_fsm_st_int_clr_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_fsm_st_int_clr_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001004,localVal);
}

static inline uint32_t rf_fsm_st_int_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline uint32_t rf_fsm_st_int_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_fsm_st_int_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001004,localVal);
}

static inline uint32_t rf_rc_state_dbg_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_rc_state_dbg_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001004,localVal);
}

static inline uint32_t rf_rc_state_dbg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_rc_state_dbg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x40001004,localVal);
}

static inline uint32_t rf_fsm_state_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline uint32_t rf_fsm_t2r_cal_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void rf_fsm_t2r_cal_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40001004,localVal);
}

static inline uint32_t rf_fsm_ctrl_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_fsm_ctrl_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001004);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001004,localVal);
}

static inline uint32_t rf_lo_unlocked_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline uint32_t rf_inc_cal_timeout_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_inc_cal_timeout_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001008,localVal);
}

static inline uint32_t rf_full_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_full_cal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001008,localVal);
}

static inline uint32_t rf_fsm_sw_st_vld_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_fsm_sw_st_vld_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001008,localVal);
}

static inline uint32_t rf_fsm_sw_st_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_fsm_sw_st_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001008);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001008,localVal);
}

static inline uint32_t rf_adda_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_adda_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_rbb_pkdet_out_rstn_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_rbb_pkdet_out_rstn_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_rbb_pkdet_en_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_rbb_pkdet_en_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_sdm_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_sdm_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_inc_fcal_ctrl_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_inc_fcal_ctrl_en_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_inc_acal_ctrl_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_inc_acal_ctrl_en_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_lo_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_lo_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_trxcal_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_trxcal_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_rbb_bw_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_rbb_bw_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_lna_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_lna_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_tx_gain_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_tx_gain_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_rx_gain_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_rx_gain_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_pu_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_pu_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000100c);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x4000100c,localVal);
}

static inline uint32_t rf_temp_comp_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001010);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_temp_comp_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001010);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001010,localVal);
}

static inline uint32_t rf_const_fcal_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001010);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_const_fcal_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001010);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001010,localVal);
}

static inline uint32_t rf_const_acal_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001010);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void rf_const_acal_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001010);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x40001010,localVal);
}

static inline uint32_t rf_dpd_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rf_dpd_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_tenscal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void rf_tenscal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_pwdet_cal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x0c000000)) >> 26);
}

static inline void rf_pwdet_cal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x0c000000);
    localVal |= (x << 26)&((uint32_t)0x0c000000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_riqcal_status_resv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_riqcal_status_resv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_tiqcal_status_resv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x00c00000)) >> 22);
}

static inline void rf_tiqcal_status_resv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x00c00000);
    localVal |= (x << 22)&((uint32_t)0x00c00000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_lo_leakcal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void rf_lo_leakcal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_rccal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x000c0000)) >> 18);
}

static inline void rf_rccal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x000c0000);
    localVal |= (x << 18)&((uint32_t)0x000c0000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_tos_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_tos_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_ros_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_ros_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_clkpll_cal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_clkpll_cal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_inc_acal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_inc_acal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_inc_fcal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_inc_fcal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_acal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x000000c0)) >> 6);
}

static inline void rf_acal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x000000c0);
    localVal |= (x << 6)&((uint32_t)0x000000c0);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_fcal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_fcal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_adc_oscal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void rf_adc_oscal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_rcal_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_rcal_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001014);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001014,localVal);
}

static inline uint32_t rf_dl_rfcal_table_status_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001018);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_dl_rfcal_table_status_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001018);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001018,localVal);
}

static inline uint32_t rf_dpd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_dpd_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_tsencal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_tsencal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_pwdet_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_pwdet_cal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_riqcal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_riqcal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_tiqcal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_tiqcal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_lo_leakcal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_lo_leakcal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_rccal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_rccal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_toscal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_toscal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_roscal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_roscal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_clkpll_cal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_clkpll_cal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_roscal_inc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_roscal_inc_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_acal_inc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_acal_inc_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_fcal_inc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_fcal_inc_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_acal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_acal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_fcal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fcal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_dl_rfcal_table_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_dl_rfcal_table_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_adc_oscal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_adc_oscal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rf_rcal_en_resv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_rcal_en_resv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000101c);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x4000101c,localVal);
}

static inline uint32_t rfcal_level_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rfcal_level_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_dpd_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_dpd_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_tsencal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_tsencal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_pwdet_cal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_pwdet_cal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_riqcal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_riqcal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_tiqcal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_tiqcal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_lo_leakcal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_lo_leakcal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_rccal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_rccal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_toscal_sten_resv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_toscal_sten_resv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_roscal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_roscal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_clkpll_cal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_clkpll_cal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_inc_acal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_inc_acal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_inc_fcal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_inc_fcal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_acal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_acal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_fcal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fcal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_dl_rfcal_table_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_dl_rfcal_table_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_adc_oscal_sten_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_adc_oscal_sten_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_rcal_sten_resv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_rcal_sten_resv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001020);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001020,localVal);
}

static inline uint32_t rf_mbg_trim_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    return ((localVal & ((uint32_t)0x18000000)) >> 27);
}

static inline void rf_mbg_trim_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    localVal &= ~((uint32_t)0x18000000);
    localVal |= (x << 27)&((uint32_t)0x18000000);
    REG_PL_WR(0x40001028,localVal);
}

static inline uint32_t rf_pud_pa_dly_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_pud_pa_dly_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x40001028,localVal);
}

static inline uint32_t rf_pud_iref_dly_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_pud_iref_dly_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x40001028,localVal);
}

static inline uint32_t rf_pud_vco_dly_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_pud_vco_dly_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x40001028,localVal);
}

static inline uint32_t rf_ppu_lead_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_ppu_lead_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001028,localVal);
}

static inline uint32_t rf_lo_sdm_rst_dly_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void rf_lo_sdm_rst_dly_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40001028,localVal);
}

static inline uint32_t rf_aupll_sdm_rst_dly_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_aupll_sdm_rst_dly_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001028);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001028,localVal);
}

static inline uint32_t rf_pu_tosdac_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_pu_tosdac_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_pwrmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void rf_pu_pwrmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_rosdac_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

static inline void rf_pu_rosdac_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x20000000);
    localVal |= (x << 29)&((uint32_t)0x20000000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_pkdet_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void rf_pu_pkdet_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_trsw_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

static inline void rf_trsw_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x04000000);
    localVal |= (x << 26)&((uint32_t)0x04000000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_txbuf_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

static inline void rf_pu_txbuf_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x02000000);
    localVal |= (x << 25)&((uint32_t)0x02000000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_rxbuf_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline void rf_pu_rxbuf_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x01000000);
    localVal |= (x << 24)&((uint32_t)0x01000000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_osmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void rf_pu_osmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_pfd_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void rf_pu_pfd_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_fbdv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_pu_fbdv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_vco_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_pu_vco_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_dac_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_pu_dac_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_pu_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_pu_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_pa_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_pu_pa_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_op_atest_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_pu_op_atest_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_adc_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_pu_adc_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_adc_clk_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_adc_clk_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_adda_ldo_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_pu_adda_ldo_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_rbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_pu_rbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_rmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_pu_rmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_pu_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_pu_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_sfreg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_pu_sfreg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001030);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001030,localVal);
}

static inline uint32_t rf_pu_tosdac_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline uint32_t rf_pu_rosdac_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

static inline uint32_t rf_pu_pkdet_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline uint32_t rf_trsw_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

static inline uint32_t rf_pu_txbuf_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

static inline uint32_t rf_pu_rxbuf_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline uint32_t rf_pu_osmx_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline uint32_t rf_pu_pfd_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline uint32_t rf_pu_fbdv_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline uint32_t rf_pu_vco_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline uint32_t rf_pu_dac_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline uint32_t rf_pu_tbb_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline uint32_t rf_pu_tmx_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline uint32_t rf_pu_pa_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline uint32_t rf_pu_adc_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline uint32_t rf_adc_clk_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline uint32_t rf_pu_adda_ldo_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline uint32_t rf_pu_rbb_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline uint32_t rf_pu_rmx_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline uint32_t rf_pu_rmxgm_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline uint32_t rf_pu_lna_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline uint32_t rf_pu_sfreg_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001034);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline uint32_t rf_ppu_txbuf_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

static inline uint32_t rf_ppu_rxbuf_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline uint32_t rf_ppu_osmx_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline uint32_t rf_ppu_pfd_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline uint32_t rf_ppu_fbdv_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline uint32_t rf_ppu_vco_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline uint32_t rf_ppu_rbb_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline uint32_t rf_ppu_rmxgm_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline uint32_t rf_ppu_lna_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001040);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline uint32_t rf_pud_vco_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001044);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline uint32_t rf_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void rf_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40001048,localVal);
}

static inline uint32_t rf_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    return ((localVal & ((uint32_t)0x01f00000)) >> 20);
}

static inline void rf_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    localVal &= ~((uint32_t)0x01f00000);
    localVal |= (x << 20)&((uint32_t)0x01f00000);
    REG_PL_WR(0x40001048,localVal);
}

static inline uint32_t rf_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

static inline void rf_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    localVal &= ~((uint32_t)0x00070000);
    localVal |= (x << 16)&((uint32_t)0x00070000);
    REG_PL_WR(0x40001048,localVal);
}

static inline uint32_t rf_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001048,localVal);
}

static inline uint32_t rf_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001048,localVal);
}

static inline uint32_t rf_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40001048,localVal);
}

static inline uint32_t rf_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001048);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x40001048,localVal);
}

static inline uint32_t rf_gc_tbb_boost_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000104c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline uint32_t rf_gc_tbb_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000104c);
    return ((localVal & ((uint32_t)0x01f00000)) >> 20);
}

static inline uint32_t rf_gc_tmx_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000104c);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

static inline uint32_t rf_gc_rbb2_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000104c);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline uint32_t rf_gc_rbb1_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000104c);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline uint32_t rf_gc_rmxgm_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000104c);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline uint32_t rf_gc_lna_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000104c);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline uint32_t rf_ten_lodist_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

static inline void rf_ten_lodist_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x08000000);
    localVal |= (x << 27)&((uint32_t)0x08000000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_lf_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

static inline void rf_ten_lf_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x04000000);
    localVal |= (x << 26)&((uint32_t)0x04000000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_pfdcp_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

static inline void rf_ten_pfdcp_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x02000000);
    localVal |= (x << 25)&((uint32_t)0x02000000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_vco_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline void rf_ten_vco_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x01000000);
    localVal |= (x << 24)&((uint32_t)0x01000000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_dac_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void rf_ten_dac_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_dac_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_ten_dac_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_adc_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_ten_adc_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_ten_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_atest_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_ten_atest_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_bq_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_ten_bq_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_tia_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_ten_tia_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_ten_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_pa_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_ten_pa_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_rrf_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_ten_rrf_1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_rrf_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_ten_rrf_0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_clkpll_sfreg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_ten_clkpll_sfreg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_ten_clkpll_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_ten_clkpll_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_dc_tp_clkpll_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_dc_tp_clkpll_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_dc_tp_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_dc_tp_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_tmux_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_tmux_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001050);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x40001050,localVal);
}

static inline uint32_t rf_dtest_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void rf_dtest_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dtest_pull_down_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_dtest_pull_down_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dten_lo_fref_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_dten_lo_fref_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dten_lo_fsdm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_dten_lo_fsdm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dten_clkpll_fin_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_dten_clkpll_fin_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dten_clkpll_fref_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_dten_clkpll_fref_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dten_clkpll_fsdm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_dten_clkpll_fsdm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dten_clkpll_clk32m_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_dten_clkpll_clk32m_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dten_clkpll_clk96m_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_dten_clkpll_clk96m_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_dten_clkpll_postdiv_clk_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_dten_clkpll_postdiv_clk_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001054);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001054,localVal);
}

static inline uint32_t rf_atest_in_en_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void rf_atest_in_en_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_in_en_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void rf_atest_in_en_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_out_en_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_atest_out_en_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_out_en_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_atest_out_en_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_gain_r5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

static inline void rf_atest_gain_r5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00070000);
    localVal |= (x << 16)&((uint32_t)0x00070000);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_gain_r6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_atest_gain_r6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_gain_r7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_atest_gain_r7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_gain_r8_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_atest_gain_r8_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_gain_r9_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_atest_gain_r9_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_in_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_atest_in_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_in_trx_sw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_atest_in_trx_sw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_dac_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_atest_dac_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_atest_op_cc_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void rf_atest_op_cc_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001058);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40001058,localVal);
}

static inline uint32_t rf_vg13_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001060);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void rf_vg13_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001060);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x40001060,localVal);
}

static inline uint32_t rf_vg11_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001060);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_vg11_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001060);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001060,localVal);
}

static inline uint32_t rf_pa_att_gc_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0xf0000000)) >> 28);
}

static inline void rf_pa_att_gc_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0xf0000000);
    localVal |= (x << 28)&((uint32_t)0xf0000000);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_pwrmx_bm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void rf_pa_pwrmx_bm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_pwrmx_dac_pn_switch_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void rf_pa_pwrmx_dac_pn_switch_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_pwrmx_osdac_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x003c0000)) >> 18);
}

static inline void rf_pa_pwrmx_osdac_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x003c0000);
    localVal |= (x << 18)&((uint32_t)0x003c0000);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_lz_bias_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_pa_lz_bias_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_ib_fix_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_pa_ib_fix_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_half_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_pa_half_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_vbcas_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_pa_vbcas_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_vbcore_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x00000f00)) >> 8);
}

static inline void rf_pa_vbcore_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x00000f00);
    localVal |= (x << 8)&((uint32_t)0x00000f00);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_iet_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void rf_pa_iet_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_etb_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_pa_etb_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_iaq_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_pa_iaq_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001064);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x40001064,localVal);
}

static inline uint32_t rf_pa_ib_fix_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001068);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline uint32_t rf_pa_half_on_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001068);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline uint32_t rf_pa_vbcas_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001068);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline uint32_t rf_pa_vbcore_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001068);
    return ((localVal & ((uint32_t)0x00000f00)) >> 8);
}

static inline uint32_t rf_pa_iet_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001068);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline uint32_t rf_pa_etb_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001068);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline uint32_t rf_tx_tsense_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_tx_tsense_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x4000106c,localVal);
}

static inline uint32_t rf_tmx_bm_cas_bulk_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_tmx_bm_cas_bulk_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x4000106c,localVal);
}

static inline uint32_t rf_tmx_bm_cas_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_tmx_bm_cas_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x4000106c,localVal);
}

static inline uint32_t rf_tmx_bm_sw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_tmx_bm_sw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x4000106c,localVal);
}

static inline uint32_t rf_tmx_cs_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_tmx_cs_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000106c);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x4000106c,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rf_tbb_tosdac_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40001070,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rf_tbb_tosdac_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40001070,localVal);
}

static inline uint32_t rf_tbb_atest_out_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_tbb_atest_out_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001070,localVal);
}

static inline uint32_t rf_tbb_iq_bias_short_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_tbb_iq_bias_short_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001070,localVal);
}

static inline uint32_t rf_tbb_cflt_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_tbb_cflt_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x40001070,localVal);
}

static inline uint32_t rf_tbb_vcm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_tbb_vcm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001070,localVal);
}

static inline uint32_t rf_tbb_bm_cg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_tbb_bm_cg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40001070,localVal);
}

static inline uint32_t rf_tbb_bm_sf_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_tbb_bm_sf_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001070);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001070,localVal);
}

static inline uint32_t rf_lna_lg_gsel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void rf_lna_lg_gsel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x40001074,localVal);
}

static inline uint32_t rf_lna_cap_lg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void rf_lna_cap_lg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x40001074,localVal);
}

static inline uint32_t rf_lna_rfb_match_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

static inline void rf_lna_rfb_match_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    localVal &= ~((uint32_t)0x00070000);
    localVal |= (x << 16)&((uint32_t)0x00070000);
    REG_PL_WR(0x40001074,localVal);
}

static inline uint32_t rf_lna_load_csw_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    return ((localVal & ((uint32_t)0x0000f000)) >> 12);
}

static inline uint32_t rf_lna_load_csw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    return ((localVal & ((uint32_t)0x00000f00)) >> 8);
}

static inline void rf_lna_load_csw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    localVal &= ~((uint32_t)0x00000f00);
    localVal |= (x << 8)&((uint32_t)0x00000f00);
    REG_PL_WR(0x40001074,localVal);
}

static inline uint32_t rf_lna_bm_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline uint32_t rf_lna_bm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void rf_lna_bm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001074);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40001074,localVal);
}

static inline uint32_t rf_rmxgm_10m_mode_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001078);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_rmxgm_10m_mode_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001078);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001078,localVal);
}

static inline uint32_t rf_rmxgm_bm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001078);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_rmxgm_bm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001078);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x40001078,localVal);
}

static inline uint32_t rf_rmx_bm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001078);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_rmx_bm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001078);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x40001078,localVal);
}

static inline uint32_t rf_rosdac_range_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000107c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_rosdac_range_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000107c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000107c,localVal);
}

static inline uint32_t rf_rosdac_i_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000107c);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline uint32_t rf_rosdac_q_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000107c);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline uint32_t rf_rosdac_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000107c);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rf_rosdac_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000107c);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x4000107c,localVal);
}

static inline uint32_t rf_rosdac_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000107c);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rf_rosdac_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000107c);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x4000107c,localVal);
}

static inline uint32_t rf_rbb_cap1_fc_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001080);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rf_rbb_cap1_fc_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001080);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40001080,localVal);
}

static inline uint32_t rf_rbb_cap1_fc_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001080);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rf_rbb_cap1_fc_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001080);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40001080,localVal);
}

static inline uint32_t rf_rbb_cap2_fc_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001080);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rf_rbb_cap2_fc_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001080);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40001080,localVal);
}

static inline uint32_t rf_rbb_cap2_fc_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001080);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rf_rbb_cap2_fc_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001080);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40001080,localVal);
}

static inline uint32_t rf_pwr_det_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_pwr_det_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rxiqcal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void rf_rxiqcal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_bw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_rbb_bw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_tia_iqbias_short_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_rbb_tia_iqbias_short_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_bq_iqbias_short_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_rbb_bq_iqbias_short_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_vcm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_rbb_vcm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_bm_op_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_rbb_bm_op_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_deq_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_rbb_deq_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_bt_fif_tune_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x00000060)) >> 5);
}

static inline void rf_rbb_bt_fif_tune_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x00000060);
    localVal |= (x << 5)&((uint32_t)0x00000060);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_bt_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_rbb_bt_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001084,localVal);
}

static inline uint32_t rf_rbb_bt_mode_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001084);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline uint32_t rf_pkdet_out_latch_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline uint32_t rf_pkdet_out_raw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline uint32_t rf_rbb_pkdet_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline uint32_t rf_rbb_pkdet_out_rstn_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline uint32_t rf_rbb_pkdet_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_rbb_pkdet_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001088,localVal);
}

static inline uint32_t rf_rbb_pkdet_out_rstn_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_rbb_pkdet_out_rstn_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001088,localVal);
}

static inline uint32_t rf_rbb_pkdet_vth_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void rf_rbb_pkdet_vth_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001088);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40001088,localVal);
}

static inline uint32_t rf_adda_ldo_dvdd_sel_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline uint32_t rf_adda_ldo_dvdd_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_adda_ldo_dvdd_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x4000108c,localVal);
}

static inline uint32_t rf_adda_ldo_byps_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_adda_ldo_byps_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x4000108c,localVal);
}

static inline uint32_t rf_dac_clk_sync_inv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_dac_clk_sync_inv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x4000108c,localVal);
}

static inline uint32_t rf_dac_rccalsel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_dac_rccalsel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x4000108c,localVal);
}

static inline uint32_t rf_dac_clk_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_dac_clk_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x4000108c,localVal);
}

static inline uint32_t rf_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x4000108c,localVal);
}

static inline uint32_t rf_dac_dvdd_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_dac_dvdd_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000108c);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x4000108c,localVal);
}

static inline uint32_t rf_adc_clk_div_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void rf_adc_clk_div_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x40001090,localVal);
}

static inline uint32_t rf_adc_clk_inv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline void rf_adc_clk_inv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    localVal &= ~((uint32_t)0x01000000);
    localVal |= (x << 24)&((uint32_t)0x01000000);
    REG_PL_WR(0x40001090,localVal);
}

static inline uint32_t rf_adc_clk_sync_inv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_adc_clk_sync_inv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001090,localVal);
}

static inline uint32_t rf_adc_gt_rm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_adc_gt_rm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001090,localVal);
}

static inline uint32_t rf_adc_sar_ascal_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_adc_sar_ascal_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001090,localVal);
}

static inline uint32_t rf_adc_dvdd_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_adc_dvdd_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001090,localVal);
}

static inline uint32_t rf_adc_dly_ctl_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_adc_dly_ctl_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40001090,localVal);
}

static inline uint32_t rf_adc_vref_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_adc_vref_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001090);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001090,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a0);
    return ((localVal & ((uint32_t)0x1f000000)) >> 24);
}

static inline uint32_t rf_lo_vco_idac_cw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a0);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010a0);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x400010a0,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a0);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline uint32_t rf_lo_vco_freq_cw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a0);
    return ((localVal & ((uint32_t)0x000000ff)) >> 0);
}

static inline void rf_lo_vco_freq_cw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010a0);
    localVal &= ~((uint32_t)0x000000ff);
    localVal |= (x << 0)&((uint32_t)0x000000ff);
    REG_PL_WR(0x400010a0,localVal);
}

static inline uint32_t rf_acal_inc_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline uint32_t rf_acal_vco_ud_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline uint32_t rf_acal_vref_cw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_acal_vref_cw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x400010a4,localVal);
}

static inline uint32_t rf_lo_vco_short_idac_filter_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_lo_vco_short_idac_filter_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x400010a4,localVal);
}

static inline uint32_t rf_lo_vco_short_vbias_filter_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_lo_vco_short_vbias_filter_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x400010a4,localVal);
}

static inline uint32_t rf_lo_vco_idac_boot_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_lo_vco_idac_boot_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x400010a4,localVal);
}

static inline uint32_t rf_lo_vco_vbias_cw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_lo_vco_vbias_cw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010a4);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x400010a4,localVal);
}

static inline uint32_t rf_fcal_cnt_op_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a8);
    return ((localVal & ((uint32_t)0xffff0000)) >> 16);
}

static inline uint32_t rf_fcal_div_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010a8);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void rf_fcal_div_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010a8);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x400010a8,localVal);
}

static inline uint32_t rf_fcal_inc_vctrl_ud_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010ac);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline uint32_t rf_fcal_cnt_rdy_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010ac);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline uint32_t rf_fcal_inc_large_range_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010ac);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_fcal_inc_large_range_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010ac);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x400010ac,localVal);
}

static inline uint32_t rf_fcal_inc_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010ac);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline uint32_t rf_fcal_cnt_start_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010ac);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_fcal_cnt_start_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010ac);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x400010ac,localVal);
}

static inline uint32_t rf_lo_pfd_rst_csd_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

static inline uint32_t rf_lo_pfd_rst_csd_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void rf_lo_pfd_rst_csd_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x400010b0,localVal);
}

static inline uint32_t rf_lo_pfd_rvdd_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline void rf_lo_pfd_rvdd_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    localVal &= ~((uint32_t)0x01000000);
    localVal |= (x << 24)&((uint32_t)0x01000000);
    REG_PL_WR(0x400010b0,localVal);
}

static inline uint32_t rf_lo_cp_hiz_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_lo_cp_hiz_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x400010b0,localVal);
}

static inline uint32_t rf_lo_cp_opamp_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_lo_cp_opamp_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x400010b0,localVal);
}

static inline uint32_t rf_lo_cp_ota_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_lo_cp_ota_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x400010b0,localVal);
}

static inline uint32_t rf_lo_cp_startup_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_lo_cp_startup_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x400010b0,localVal);
}

static inline uint32_t rf_lo_cp_sel_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline uint32_t rf_lo_cp_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_lo_cp_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b0);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x400010b0,localVal);
}

static inline uint32_t rf_lo_slipped_up_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline uint32_t rf_lo_slipped_dn_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline uint32_t rf_lo_lf_r4_short_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_lo_lf_r4_short_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x400010b4,localVal);
}

static inline uint32_t rf_lo_lf_r4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_lo_lf_r4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x400010b4,localVal);
}

static inline uint32_t rf_lo_lf_cz_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_lo_lf_cz_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x400010b4,localVal);
}

static inline uint32_t rf_lo_lf_rz_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_lo_lf_rz_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x400010b4,localVal);
}

static inline uint32_t rf_lo_lf_cz_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline uint32_t rf_lo_lf_r4_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline uint32_t rf_lo_lf_rz_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b4);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline uint32_t rf_lo_fbdv_rst_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline uint32_t rf_lo_fbdv_rst_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_lo_fbdv_rst_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x400010b8,localVal);
}

static inline uint32_t rf_lo_fbdv_sel_fb_clk_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_lo_fbdv_sel_fb_clk_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x400010b8,localVal);
}

static inline uint32_t rf_lo_fbdv_sel_sample_clk_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_lo_fbdv_sel_sample_clk_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x400010b8,localVal);
}

static inline uint32_t rf_lo_fbdv_halfstep_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_lo_fbdv_halfstep_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x400010b8,localVal);
}

static inline uint32_t rf_lo_fbdv_halfstep_en_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010b8);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline uint32_t rf_lo_lodist_rxbuf_stre_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void rf_lo_lodist_rxbuf_stre_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x400010bc,localVal);
}

static inline uint32_t rf_lo_lodist_txbuf_stre_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    return ((localVal & ((uint32_t)0x01000000)) >> 24);
}

static inline void rf_lo_lodist_txbuf_stre_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    localVal &= ~((uint32_t)0x01000000);
    localVal |= (x << 24)&((uint32_t)0x01000000);
    REG_PL_WR(0x400010bc,localVal);
}

static inline uint32_t rf_lo_osmx_cap_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    return ((localVal & ((uint32_t)0x00f00000)) >> 20);
}

static inline void rf_lo_osmx_cap_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    localVal &= ~((uint32_t)0x00f00000);
    localVal |= (x << 20)&((uint32_t)0x00f00000);
    REG_PL_WR(0x400010bc,localVal);
}

static inline uint32_t rf_lo_osmx_capbank_bias_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_lo_osmx_capbank_bias_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x400010bc,localVal);
}

static inline uint32_t rf_lo_osmx_vbuf_stre_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_lo_osmx_vbuf_stre_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x400010bc,localVal);
}

static inline uint32_t rf_lo_osmx_fix_cap_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_lo_osmx_fix_cap_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x400010bc,localVal);
}

static inline uint32_t rf_lo_osmx_en_xgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_lo_osmx_en_xgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x400010bc,localVal);
}

static inline uint32_t rf_lo_osmx_xgm_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_lo_osmx_xgm_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010bc);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x400010bc,localVal);
}

static inline uint32_t rf_lo_sdm_flag_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_lo_sdm_flag_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x400010c0,localVal);
}

static inline uint32_t rf_lo_sdm_rstb_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline uint32_t rf_lo_sdm_rstb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_lo_sdm_rstb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x400010c0,localVal);
}

static inline uint32_t rf_lo_sdm_bypass_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_lo_sdm_bypass_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x400010c0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_lo_sdm_dither_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x400010c0,localVal);
}

static inline uint32_t rf_lo_sdm_bypass_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline uint32_t rf_lo_sdm_dither_sel_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c0);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline uint32_t rf_lo_sdmin_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c4);
    return ((localVal & ((uint32_t)0x3fffffff)) >> 0);
}

static inline void rf_lo_sdmin_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010c4);
    localVal &= ~((uint32_t)0x3fffffff);
    localVal |= (x << 0)&((uint32_t)0x3fffffff);
    REG_PL_WR(0x400010c4,localVal);
}

static inline uint32_t rf_lo_sdmin_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010c8);
    return ((localVal & ((uint32_t)0x3fffffff)) >> 0);
}

static inline uint32_t rf_reserved0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010ec);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void rf_reserved0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010ec);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x400010ec,localVal);
}

static inline uint32_t rf_reserved1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f0);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void rf_reserved1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f0);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x400010f0,localVal);
}

static inline uint32_t rf_reserved2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f4);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t rf_gain_ctrl5_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x38000000)) >> 27);
}

static inline void rf_gain_ctrl5_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x38000000);
    localVal |= (x << 27)&((uint32_t)0x38000000);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl5_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x06000000)) >> 25);
}

static inline void rf_gain_ctrl5_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x06000000);
    localVal |= (x << 25)&((uint32_t)0x06000000);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl4_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x01c00000)) >> 22);
}

static inline void rf_gain_ctrl4_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x01c00000);
    localVal |= (x << 22)&((uint32_t)0x01c00000);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl4_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void rf_gain_ctrl4_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl3_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x000e0000)) >> 17);
}

static inline void rf_gain_ctrl3_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x000e0000);
    localVal |= (x << 17)&((uint32_t)0x000e0000);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl3_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x00018000)) >> 15);
}

static inline void rf_gain_ctrl3_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x00018000);
    localVal |= (x << 15)&((uint32_t)0x00018000);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl2_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_gain_ctrl2_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl2_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_gain_ctrl2_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl1_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x00000380)) >> 7);
}

static inline void rf_gain_ctrl1_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x00000380);
    localVal |= (x << 7)&((uint32_t)0x00000380);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl1_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x00000060)) >> 5);
}

static inline void rf_gain_ctrl1_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x00000060);
    localVal |= (x << 5)&((uint32_t)0x00000060);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl0_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x0000001c)) >> 2);
}

static inline void rf_gain_ctrl0_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x0000001c);
    localVal |= (x << 2)&((uint32_t)0x0000001c);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl0_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_gain_ctrl0_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010f8);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x400010f8,localVal);
}

static inline uint32_t rf_gain_ctrl6_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_gain_ctrl6_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x400010fc,localVal);
}

static inline uint32_t rf_gain_ctrl6_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_gain_ctrl6_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x400010fc,localVal);
}

static inline uint32_t rf_gain_ctrl7_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    return ((localVal & ((uint32_t)0x00000380)) >> 7);
}

static inline void rf_gain_ctrl7_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    localVal &= ~((uint32_t)0x00000380);
    localVal |= (x << 7)&((uint32_t)0x00000380);
    REG_PL_WR(0x400010fc,localVal);
}

static inline uint32_t rf_gain_ctrl7_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    return ((localVal & ((uint32_t)0x00000060)) >> 5);
}

static inline void rf_gain_ctrl7_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    localVal &= ~((uint32_t)0x00000060);
    localVal |= (x << 5)&((uint32_t)0x00000060);
    REG_PL_WR(0x400010fc,localVal);
}

static inline uint32_t rf_gain_ctrl8_gc_lna_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    return ((localVal & ((uint32_t)0x0000001c)) >> 2);
}

static inline void rf_gain_ctrl8_gc_lna_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    localVal &= ~((uint32_t)0x0000001c);
    localVal |= (x << 2)&((uint32_t)0x0000001c);
    REG_PL_WR(0x400010fc,localVal);
}

static inline uint32_t rf_gain_ctrl8_gc_rmxgm_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_gain_ctrl8_gc_rmxgm_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400010fc);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x400010fc,localVal);
}

static inline uint32_t rf_lna_load_csw_lg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001100);
    return ((localVal & ((uint32_t)0x0000f000)) >> 12);
}

static inline void rf_lna_load_csw_lg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001100);
    localVal &= ~((uint32_t)0x0000f000);
    localVal |= (x << 12)&((uint32_t)0x0000f000);
    REG_PL_WR(0x40001100,localVal);
}

static inline uint32_t rf_lna_load_csw_hg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001100);
    return ((localVal & ((uint32_t)0x00000f00)) >> 8);
}

static inline void rf_lna_load_csw_hg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001100);
    localVal &= ~((uint32_t)0x00000f00);
    localVal |= (x << 8)&((uint32_t)0x00000f00);
    REG_PL_WR(0x40001100,localVal);
}

static inline uint32_t rf_lna_bm_lg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001100);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void rf_lna_bm_lg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001100);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x40001100,localVal);
}

static inline uint32_t rf_lna_bm_hg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001100);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void rf_lna_bm_hg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001100);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x40001100,localVal);
}

static inline uint32_t rf_gain_ctrl3_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

static inline void rf_gain_ctrl3_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    localVal &= ~((uint32_t)0x70000000);
    localVal |= (x << 28)&((uint32_t)0x70000000);
    REG_PL_WR(0x40001104,localVal);
}

static inline uint32_t rf_gain_ctrl3_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_gain_ctrl3_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x40001104,localVal);
}

static inline uint32_t rf_gain_ctrl2_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_gain_ctrl2_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x40001104,localVal);
}

static inline uint32_t rf_gain_ctrl2_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_gain_ctrl2_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x40001104,localVal);
}

static inline uint32_t rf_gain_ctrl1_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_gain_ctrl1_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001104,localVal);
}

static inline uint32_t rf_gain_ctrl1_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_gain_ctrl1_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001104,localVal);
}

static inline uint32_t rf_gain_ctrl0_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_gain_ctrl0_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x40001104,localVal);
}

static inline uint32_t rf_gain_ctrl0_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_gain_ctrl0_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001104);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001104,localVal);
}

static inline uint32_t rf_gain_ctrl7_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

static inline void rf_gain_ctrl7_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    localVal &= ~((uint32_t)0x70000000);
    localVal |= (x << 28)&((uint32_t)0x70000000);
    REG_PL_WR(0x40001108,localVal);
}

static inline uint32_t rf_gain_ctrl7_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_gain_ctrl7_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x40001108,localVal);
}

static inline uint32_t rf_gain_ctrl6_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_gain_ctrl6_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x40001108,localVal);
}

static inline uint32_t rf_gain_ctrl6_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_gain_ctrl6_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x40001108,localVal);
}

static inline uint32_t rf_gain_ctrl5_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_gain_ctrl5_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001108,localVal);
}

static inline uint32_t rf_gain_ctrl5_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_gain_ctrl5_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001108,localVal);
}

static inline uint32_t rf_gain_ctrl4_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_gain_ctrl4_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x40001108,localVal);
}

static inline uint32_t rf_gain_ctrl4_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_gain_ctrl4_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001108);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001108,localVal);
}

static inline uint32_t rf_gain_ctrl11_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

static inline void rf_gain_ctrl11_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    localVal &= ~((uint32_t)0x70000000);
    localVal |= (x << 28)&((uint32_t)0x70000000);
    REG_PL_WR(0x4000110c,localVal);
}

static inline uint32_t rf_gain_ctrl11_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_gain_ctrl11_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x4000110c,localVal);
}

static inline uint32_t rf_gain_ctrl10_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_gain_ctrl10_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x4000110c,localVal);
}

static inline uint32_t rf_gain_ctrl10_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_gain_ctrl10_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x4000110c,localVal);
}

static inline uint32_t rf_gain_ctrl9_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_gain_ctrl9_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x4000110c,localVal);
}

static inline uint32_t rf_gain_ctrl9_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_gain_ctrl9_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x4000110c,localVal);
}

static inline uint32_t rf_gain_ctrl8_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_gain_ctrl8_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x4000110c,localVal);
}

static inline uint32_t rf_gain_ctrl8_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_gain_ctrl8_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000110c);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x4000110c,localVal);
}

static inline uint32_t rf_gain_ctrl15_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

static inline void rf_gain_ctrl15_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    localVal &= ~((uint32_t)0x70000000);
    localVal |= (x << 28)&((uint32_t)0x70000000);
    REG_PL_WR(0x40001110,localVal);
}

static inline uint32_t rf_gain_ctrl15_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_gain_ctrl15_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x40001110,localVal);
}

static inline uint32_t rf_gain_ctrl14_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_gain_ctrl14_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x40001110,localVal);
}

static inline uint32_t rf_gain_ctrl14_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_gain_ctrl14_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x40001110,localVal);
}

static inline uint32_t rf_gain_ctrl13_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_gain_ctrl13_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001110,localVal);
}

static inline uint32_t rf_gain_ctrl13_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_gain_ctrl13_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001110,localVal);
}

static inline uint32_t rf_gain_ctrl12_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_gain_ctrl12_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x40001110,localVal);
}

static inline uint32_t rf_gain_ctrl12_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_gain_ctrl12_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001110);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001110,localVal);
}

static inline uint32_t rf_gain_ctrl16_gc_rbb2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001114);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_gain_ctrl16_gc_rbb2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001114);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x40001114,localVal);
}

static inline uint32_t rf_gain_ctrl16_gc_rbb1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001114);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_gain_ctrl16_gc_rbb1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001114);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x40001114,localVal);
}

static inline uint32_t rf_gain_ctrl1_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rf_gain_ctrl1_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x40001118,localVal);
}

static inline uint32_t rf_gain_ctrl1_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void rf_gain_ctrl1_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40001118,localVal);
}

static inline uint32_t rf_gain_ctrl1_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void rf_gain_ctrl1_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x40001118,localVal);
}

static inline uint32_t rf_gain_ctrl1_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_gain_ctrl1_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001118,localVal);
}

static inline uint32_t rf_gain_ctrl0_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_gain_ctrl0_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x40001118,localVal);
}

static inline uint32_t rf_gain_ctrl0_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_gain_ctrl0_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x40001118,localVal);
}

static inline uint32_t rf_gain_ctrl0_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_gain_ctrl0_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x40001118,localVal);
}

static inline uint32_t rf_gain_ctrl0_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_gain_ctrl0_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001118);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001118,localVal);
}

static inline uint32_t rf_gain_ctrl3_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rf_gain_ctrl3_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x4000111c,localVal);
}

static inline uint32_t rf_gain_ctrl3_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void rf_gain_ctrl3_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x4000111c,localVal);
}

static inline uint32_t rf_gain_ctrl3_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void rf_gain_ctrl3_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x4000111c,localVal);
}

static inline uint32_t rf_gain_ctrl3_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_gain_ctrl3_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x4000111c,localVal);
}

static inline uint32_t rf_gain_ctrl2_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_gain_ctrl2_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x4000111c,localVal);
}

static inline uint32_t rf_gain_ctrl2_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_gain_ctrl2_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x4000111c,localVal);
}

static inline uint32_t rf_gain_ctrl2_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_gain_ctrl2_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x4000111c,localVal);
}

static inline uint32_t rf_gain_ctrl2_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_gain_ctrl2_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000111c);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x4000111c,localVal);
}

static inline uint32_t rf_gain_ctrl5_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rf_gain_ctrl5_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x40001120,localVal);
}

static inline uint32_t rf_gain_ctrl5_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void rf_gain_ctrl5_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40001120,localVal);
}

static inline uint32_t rf_gain_ctrl5_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void rf_gain_ctrl5_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x40001120,localVal);
}

static inline uint32_t rf_gain_ctrl5_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_gain_ctrl5_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001120,localVal);
}

static inline uint32_t rf_gain_ctrl4_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_gain_ctrl4_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x40001120,localVal);
}

static inline uint32_t rf_gain_ctrl4_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_gain_ctrl4_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x40001120,localVal);
}

static inline uint32_t rf_gain_ctrl4_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_gain_ctrl4_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x40001120,localVal);
}

static inline uint32_t rf_gain_ctrl4_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_gain_ctrl4_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001120);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001120,localVal);
}

static inline uint32_t rf_gain_ctrl7_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rf_gain_ctrl7_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x40001124,localVal);
}

static inline uint32_t rf_gain_ctrl7_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void rf_gain_ctrl7_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x40001124,localVal);
}

static inline uint32_t rf_gain_ctrl7_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void rf_gain_ctrl7_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x40001124,localVal);
}

static inline uint32_t rf_gain_ctrl7_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_gain_ctrl7_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001124,localVal);
}

static inline uint32_t rf_gain_ctrl6_gc_tbb_boost_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_gain_ctrl6_gc_tbb_boost_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x40001124,localVal);
}

static inline uint32_t rf_gain_ctrl6_dac_bias_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_gain_ctrl6_dac_bias_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x40001124,localVal);
}

static inline uint32_t rf_gain_ctrl6_gc_tmx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_gain_ctrl6_gc_tmx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x40001124,localVal);
}

static inline uint32_t rf_gain_ctrl6_gc_tbb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_gain_ctrl6_gc_tbb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001124);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001124,localVal);
}

static inline uint32_t rf_pa_vbcas_11n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001128);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_pa_vbcas_11n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001128);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x40001128,localVal);
}

static inline uint32_t rf_pa_vbcore_11n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001128);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void rf_pa_vbcore_11n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001128);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x40001128,localVal);
}

static inline uint32_t rf_pa_iet_11n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001128);
    return ((localVal & ((uint32_t)0x0000f000)) >> 12);
}

static inline void rf_pa_iet_11n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001128);
    localVal &= ~((uint32_t)0x0000f000);
    localVal |= (x << 12)&((uint32_t)0x0000f000);
    REG_PL_WR(0x40001128,localVal);
}

static inline uint32_t rf_pa_vbcas_11b_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_pa_vbcas_11b_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x4000112c,localVal);
}

static inline uint32_t rf_pa_vbcore_11b_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    return ((localVal & ((uint32_t)0x000f0000)) >> 16);
}

static inline void rf_pa_vbcore_11b_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    localVal &= ~((uint32_t)0x000f0000);
    localVal |= (x << 16)&((uint32_t)0x000f0000);
    REG_PL_WR(0x4000112c,localVal);
}

static inline uint32_t rf_pa_iet_11b_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    return ((localVal & ((uint32_t)0x0000f000)) >> 12);
}

static inline void rf_pa_iet_11b_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    localVal &= ~((uint32_t)0x0000f000);
    localVal |= (x << 12)&((uint32_t)0x0000f000);
    REG_PL_WR(0x4000112c,localVal);
}

static inline uint32_t rf_pa_vbcas_11g_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_pa_vbcas_11g_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x4000112c,localVal);
}

static inline uint32_t rf_pa_vbcore_11g_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    return ((localVal & ((uint32_t)0x000000f0)) >> 4);
}

static inline void rf_pa_vbcore_11g_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    localVal &= ~((uint32_t)0x000000f0);
    localVal |= (x << 4)&((uint32_t)0x000000f0);
    REG_PL_WR(0x4000112c,localVal);
}

static inline uint32_t rf_pa_iet_11g_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline void rf_pa_iet_11g_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000112c);
    localVal &= ~((uint32_t)0x0000000f);
    localVal |= (x << 0)&((uint32_t)0x0000000f);
    REG_PL_WR(0x4000112c,localVal);
}

static inline uint32_t rf_pa_ib_fix_wifi_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001130);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_pa_ib_fix_wifi_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001130);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001130,localVal);
}

static inline uint32_t rf_pa_etb_en_wifi_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001130);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_pa_etb_en_wifi_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001130);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001130,localVal);
}

static inline uint32_t rf_pa_half_on_wifi_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001130);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_pa_half_on_wifi_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001130);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001130,localVal);
}

static inline uint32_t rf_adda_ldo_dvdd_sel_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001134);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_adda_ldo_dvdd_sel_tx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001134);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x40001134,localVal);
}

static inline uint32_t rf_adda_ldo_dvdd_sel_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001134);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_adda_ldo_dvdd_sel_rx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001134);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x40001134,localVal);
}

static inline uint32_t rf_lo_lf_r4_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_lo_lf_r4_tx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_lf_r4_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void rf_lo_lf_r4_rx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_lf_rz_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_lo_lf_rz_tx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_lf_rz_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_lo_lf_rz_rx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_lf_cz_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_lo_lf_cz_tx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_lf_cz_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_lo_lf_cz_rx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_cp_sel_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_lo_cp_sel_tx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_cp_sel_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_lo_cp_sel_rx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_fbdv_halfstep_en_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_lo_fbdv_halfstep_en_tx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_fbdv_halfstep_en_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_lo_fbdv_halfstep_en_rx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001138);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001138,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2408_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000113c);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2408_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000113c);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x4000113c,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2408_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000113c);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2408_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000113c);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x4000113c,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2404_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000113c);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2404_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000113c);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x4000113c,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2404_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000113c);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2404_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000113c);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x4000113c,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2416_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001140);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2416_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001140);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40001140,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2416_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001140);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2416_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001140);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001140,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2412_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001140);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2412_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001140);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001140,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2412_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001140);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2412_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001140);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001140,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2424_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001144);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2424_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001144);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40001144,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2424_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001144);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2424_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001144);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001144,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2420_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001144);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2420_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001144);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001144,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2420_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001144);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2420_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001144);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001144,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2432_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001148);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2432_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001148);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40001148,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2432_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001148);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2432_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001148);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001148,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2428_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001148);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2428_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001148);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001148,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2428_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001148);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2428_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001148);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001148,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2440_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000114c);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2440_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000114c);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x4000114c,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2440_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000114c);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2440_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000114c);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x4000114c,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2436_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000114c);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2436_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000114c);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x4000114c,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2436_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000114c);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2436_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000114c);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x4000114c,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2448_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001150);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2448_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001150);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40001150,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2448_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001150);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2448_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001150);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001150,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2444_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001150);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2444_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001150);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001150,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2444_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001150);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2444_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001150);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001150,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2456_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001154);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2456_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001154);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40001154,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2456_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001154);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2456_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001154);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001154,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2452_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001154);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2452_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001154);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001154,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2452_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001154);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2452_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001154);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001154,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2464_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001158);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2464_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001158);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40001158,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2464_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001158);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2464_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001158);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001158,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2460_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001158);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2460_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001158);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001158,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2460_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001158);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2460_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001158);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001158,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2472_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000115c);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2472_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000115c);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x4000115c,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2472_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000115c);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2472_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000115c);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x4000115c,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2468_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000115c);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2468_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000115c);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x4000115c,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2468_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000115c);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2468_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000115c);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x4000115c,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2480_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001160);
    return ((localVal & ((uint32_t)0xff000000)) >> 24);
}

static inline void rf_lo_vco_freq_cw_2480_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001160);
    localVal &= ~((uint32_t)0xff000000);
    localVal |= (x << 24)&((uint32_t)0xff000000);
    REG_PL_WR(0x40001160,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2480_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001160);
    return ((localVal & ((uint32_t)0x001f0000)) >> 16);
}

static inline void rf_lo_vco_idac_cw_2480_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001160);
    localVal &= ~((uint32_t)0x001f0000);
    localVal |= (x << 16)&((uint32_t)0x001f0000);
    REG_PL_WR(0x40001160,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2476_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001160);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2476_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001160);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001160,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2476_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001160);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2476_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001160);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001160,localVal);
}

static inline uint32_t rf_lo_vco_freq_cw_2484_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001164);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_lo_vco_freq_cw_2484_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001164);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001164,localVal);
}

static inline uint32_t rf_lo_vco_idac_cw_2484_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001164);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_lo_vco_idac_cw_2484_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001164);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001164,localVal);
}

static inline uint32_t rf_rosdac_q_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001168);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rf_rosdac_q_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001168);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40001168,localVal);
}

static inline uint32_t rf_rosdac_i_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001168);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rf_rosdac_i_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001168);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40001168,localVal);
}

static inline uint32_t rf_rosdac_q_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001168);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rf_rosdac_q_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001168);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40001168,localVal);
}

static inline uint32_t rf_rosdac_i_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001168);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rf_rosdac_i_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001168);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40001168,localVal);
}

static inline uint32_t rf_rosdac_q_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000116c);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rf_rosdac_q_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000116c);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x4000116c,localVal);
}

static inline uint32_t rf_rosdac_i_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000116c);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rf_rosdac_i_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000116c);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x4000116c,localVal);
}

static inline uint32_t rf_rosdac_q_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000116c);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rf_rosdac_q_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000116c);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x4000116c,localVal);
}

static inline uint32_t rf_rosdac_i_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000116c);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rf_rosdac_i_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000116c);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x4000116c,localVal);
}

static inline uint32_t rf_rx_iq_gain_comp_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001170);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_rx_iq_gain_comp_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001170);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x40001170,localVal);
}

static inline uint32_t rf_rx_iq_phase_comp_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001170);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_rx_iq_phase_comp_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001170);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001170,localVal);
}

static inline uint32_t rf_rx_iq_gain_comp_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001174);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_rx_iq_gain_comp_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001174);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x40001174,localVal);
}

static inline uint32_t rf_rx_iq_phase_comp_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001174);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_rx_iq_phase_comp_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001174);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001174,localVal);
}

static inline uint32_t rf_rx_iq_gain_comp_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001178);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_rx_iq_gain_comp_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001178);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x40001178,localVal);
}

static inline uint32_t rf_rx_iq_phase_comp_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001178);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_rx_iq_phase_comp_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001178);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001178,localVal);
}

static inline uint32_t rf_rx_iq_gain_comp_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000117c);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_rx_iq_gain_comp_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000117c);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x4000117c,localVal);
}

static inline uint32_t rf_rx_iq_phase_comp_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000117c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_rx_iq_phase_comp_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000117c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000117c,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001180);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rf_tbb_tosdac_q_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001180);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40001180,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001180);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rf_tbb_tosdac_i_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001180);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40001180,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001180);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rf_tbb_tosdac_q_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001180);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40001180,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001180);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rf_tbb_tosdac_i_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001180);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40001180,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001184);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rf_tbb_tosdac_q_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001184);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40001184,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001184);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rf_tbb_tosdac_i_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001184);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40001184,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001184);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rf_tbb_tosdac_q_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001184);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40001184,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001184);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rf_tbb_tosdac_i_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001184);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40001184,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_gc5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001188);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rf_tbb_tosdac_q_gc5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001188);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x40001188,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_gc5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001188);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rf_tbb_tosdac_i_gc5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001188);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x40001188,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_gc4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001188);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rf_tbb_tosdac_q_gc4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001188);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x40001188,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_gc4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001188);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rf_tbb_tosdac_i_gc4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001188);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x40001188,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_gc7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000118c);
    return ((localVal & ((uint32_t)0x3f000000)) >> 24);
}

static inline void rf_tbb_tosdac_q_gc7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000118c);
    localVal &= ~((uint32_t)0x3f000000);
    localVal |= (x << 24)&((uint32_t)0x3f000000);
    REG_PL_WR(0x4000118c,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_gc7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000118c);
    return ((localVal & ((uint32_t)0x003f0000)) >> 16);
}

static inline void rf_tbb_tosdac_i_gc7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000118c);
    localVal &= ~((uint32_t)0x003f0000);
    localVal |= (x << 16)&((uint32_t)0x003f0000);
    REG_PL_WR(0x4000118c,localVal);
}

static inline uint32_t rf_tbb_tosdac_q_gc6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000118c);
    return ((localVal & ((uint32_t)0x00003f00)) >> 8);
}

static inline void rf_tbb_tosdac_q_gc6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000118c);
    localVal &= ~((uint32_t)0x00003f00);
    localVal |= (x << 8)&((uint32_t)0x00003f00);
    REG_PL_WR(0x4000118c,localVal);
}

static inline uint32_t rf_tbb_tosdac_i_gc6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000118c);
    return ((localVal & ((uint32_t)0x0000003f)) >> 0);
}

static inline void rf_tbb_tosdac_i_gc6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000118c);
    localVal &= ~((uint32_t)0x0000003f);
    localVal |= (x << 0)&((uint32_t)0x0000003f);
    REG_PL_WR(0x4000118c,localVal);
}

static inline uint32_t rf_tx_iq_gain_comp_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001190);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_tx_iq_gain_comp_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001190);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x40001190,localVal);
}

static inline uint32_t rf_tx_iq_phase_comp_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001190);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iq_phase_comp_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001190);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001190,localVal);
}

static inline uint32_t rf_tx_iq_gain_comp_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001194);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_tx_iq_gain_comp_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001194);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x40001194,localVal);
}

static inline uint32_t rf_tx_iq_phase_comp_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001194);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iq_phase_comp_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001194);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001194,localVal);
}

static inline uint32_t rf_tx_iq_gain_comp_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001198);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_tx_iq_gain_comp_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001198);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x40001198,localVal);
}

static inline uint32_t rf_tx_iq_phase_comp_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001198);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iq_phase_comp_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001198);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001198,localVal);
}

static inline uint32_t rf_tx_iq_gain_comp_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000119c);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_tx_iq_gain_comp_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000119c);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x4000119c,localVal);
}

static inline uint32_t rf_tx_iq_phase_comp_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000119c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iq_phase_comp_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000119c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000119c,localVal);
}

static inline uint32_t rf_tx_iq_gain_comp_gc4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011a0);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_tx_iq_gain_comp_gc4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011a0);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x400011a0,localVal);
}

static inline uint32_t rf_tx_iq_phase_comp_gc4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011a0);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iq_phase_comp_gc4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011a0);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400011a0,localVal);
}

static inline uint32_t rf_tx_iq_gain_comp_gc5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011a4);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_tx_iq_gain_comp_gc5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011a4);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x400011a4,localVal);
}

static inline uint32_t rf_tx_iq_phase_comp_gc5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011a4);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iq_phase_comp_gc5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011a4);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400011a4,localVal);
}

static inline uint32_t rf_tx_iq_gain_comp_gc6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011a8);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_tx_iq_gain_comp_gc6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011a8);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x400011a8,localVal);
}

static inline uint32_t rf_tx_iq_phase_comp_gc6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011a8);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iq_phase_comp_gc6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011a8);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400011a8,localVal);
}

static inline uint32_t rf_tx_iq_gain_comp_gc7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011ac);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline void rf_tx_iq_gain_comp_gc7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011ac);
    localVal &= ~((uint32_t)0x07ff0000);
    localVal |= (x << 16)&((uint32_t)0x07ff0000);
    REG_PL_WR(0x400011ac,localVal);
}

static inline uint32_t rf_tx_iq_phase_comp_gc7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011ac);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iq_phase_comp_gc7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011ac);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x400011ac,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2484_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x0c000000)) >> 26);
}

static inline void rf_lo_sdm_dither_sel_wlan_2484_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x0c000000);
    localVal |= (x << 26)&((uint32_t)0x0c000000);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2472_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_lo_sdm_dither_sel_wlan_2472_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2467_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x00c00000)) >> 22);
}

static inline void rf_lo_sdm_dither_sel_wlan_2467_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x00c00000);
    localVal |= (x << 22)&((uint32_t)0x00c00000);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2462_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void rf_lo_sdm_dither_sel_wlan_2462_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2457_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x000c0000)) >> 18);
}

static inline void rf_lo_sdm_dither_sel_wlan_2457_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x000c0000);
    localVal |= (x << 18)&((uint32_t)0x000c0000);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2452_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_lo_sdm_dither_sel_wlan_2452_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2447_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_lo_sdm_dither_sel_wlan_2447_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2442_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_lo_sdm_dither_sel_wlan_2442_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2437_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_lo_sdm_dither_sel_wlan_2437_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2432_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_lo_sdm_dither_sel_wlan_2432_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2427_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x000000c0)) >> 6);
}

static inline void rf_lo_sdm_dither_sel_wlan_2427_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x000000c0);
    localVal |= (x << 6)&((uint32_t)0x000000c0);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2422_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_lo_sdm_dither_sel_wlan_2422_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2417_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void rf_lo_sdm_dither_sel_wlan_2417_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_wlan_2412_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_lo_sdm_dither_sel_wlan_2412_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b0);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x400011b0,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2432_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rf_lo_sdm_dither_sel_ble_2432_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2430_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void rf_lo_sdm_dither_sel_ble_2430_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2428_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x0c000000)) >> 26);
}

static inline void rf_lo_sdm_dither_sel_ble_2428_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x0c000000);
    localVal |= (x << 26)&((uint32_t)0x0c000000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2426_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_lo_sdm_dither_sel_ble_2426_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2424_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x00c00000)) >> 22);
}

static inline void rf_lo_sdm_dither_sel_ble_2424_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x00c00000);
    localVal |= (x << 22)&((uint32_t)0x00c00000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2422_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void rf_lo_sdm_dither_sel_ble_2422_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2420_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x000c0000)) >> 18);
}

static inline void rf_lo_sdm_dither_sel_ble_2420_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x000c0000);
    localVal |= (x << 18)&((uint32_t)0x000c0000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2418_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_lo_sdm_dither_sel_ble_2418_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2416_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_lo_sdm_dither_sel_ble_2416_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2414_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_lo_sdm_dither_sel_ble_2414_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2412_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_lo_sdm_dither_sel_ble_2412_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2410_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_lo_sdm_dither_sel_ble_2410_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2408_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x000000c0)) >> 6);
}

static inline void rf_lo_sdm_dither_sel_ble_2408_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x000000c0);
    localVal |= (x << 6)&((uint32_t)0x000000c0);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2406_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_lo_sdm_dither_sel_ble_2406_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2404_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void rf_lo_sdm_dither_sel_ble_2404_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2402_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_lo_sdm_dither_sel_ble_2402_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b4);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x400011b4,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2464_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rf_lo_sdm_dither_sel_ble_2464_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2462_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x30000000)) >> 28);
}

static inline void rf_lo_sdm_dither_sel_ble_2462_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x30000000);
    localVal |= (x << 28)&((uint32_t)0x30000000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2460_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x0c000000)) >> 26);
}

static inline void rf_lo_sdm_dither_sel_ble_2460_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x0c000000);
    localVal |= (x << 26)&((uint32_t)0x0c000000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2458_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x03000000)) >> 24);
}

static inline void rf_lo_sdm_dither_sel_ble_2458_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x03000000);
    localVal |= (x << 24)&((uint32_t)0x03000000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2456_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x00c00000)) >> 22);
}

static inline void rf_lo_sdm_dither_sel_ble_2456_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x00c00000);
    localVal |= (x << 22)&((uint32_t)0x00c00000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2454_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x00300000)) >> 20);
}

static inline void rf_lo_sdm_dither_sel_ble_2454_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x00300000);
    localVal |= (x << 20)&((uint32_t)0x00300000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2452_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x000c0000)) >> 18);
}

static inline void rf_lo_sdm_dither_sel_ble_2452_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x000c0000);
    localVal |= (x << 18)&((uint32_t)0x000c0000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2450_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_lo_sdm_dither_sel_ble_2450_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2448_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_lo_sdm_dither_sel_ble_2448_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2446_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_lo_sdm_dither_sel_ble_2446_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2444_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_lo_sdm_dither_sel_ble_2444_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2442_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_lo_sdm_dither_sel_ble_2442_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2440_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x000000c0)) >> 6);
}

static inline void rf_lo_sdm_dither_sel_ble_2440_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x000000c0);
    localVal |= (x << 6)&((uint32_t)0x000000c0);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2438_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_lo_sdm_dither_sel_ble_2438_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2436_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void rf_lo_sdm_dither_sel_ble_2436_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2434_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_lo_sdm_dither_sel_ble_2434_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011b8);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x400011b8,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_lo_sdm_dither_sel_ble_tx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2480_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x0000c000)) >> 14);
}

static inline void rf_lo_sdm_dither_sel_ble_2480_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x0000c000);
    localVal |= (x << 14)&((uint32_t)0x0000c000);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2478_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x00003000)) >> 12);
}

static inline void rf_lo_sdm_dither_sel_ble_2478_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x00003000);
    localVal |= (x << 12)&((uint32_t)0x00003000);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2476_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x00000c00)) >> 10);
}

static inline void rf_lo_sdm_dither_sel_ble_2476_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x00000c00);
    localVal |= (x << 10)&((uint32_t)0x00000c00);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2474_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x00000300)) >> 8);
}

static inline void rf_lo_sdm_dither_sel_ble_2474_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x00000300);
    localVal |= (x << 8)&((uint32_t)0x00000300);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2472_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x000000c0)) >> 6);
}

static inline void rf_lo_sdm_dither_sel_ble_2472_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x000000c0);
    localVal |= (x << 6)&((uint32_t)0x000000c0);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2470_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x00000030)) >> 4);
}

static inline void rf_lo_sdm_dither_sel_ble_2470_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x00000030);
    localVal |= (x << 4)&((uint32_t)0x00000030);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2468_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x0000000c)) >> 2);
}

static inline void rf_lo_sdm_dither_sel_ble_2468_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x0000000c);
    localVal |= (x << 2)&((uint32_t)0x0000000c);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_dither_sel_ble_2466_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    return ((localVal & ((uint32_t)0x00000003)) >> 0);
}

static inline void rf_lo_sdm_dither_sel_ble_2466_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011bc);
    localVal &= ~((uint32_t)0x00000003);
    localVal |= (x << 0)&((uint32_t)0x00000003);
    REG_PL_WR(0x400011bc,localVal);
}

static inline uint32_t rf_lo_sdm_bypass_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011c0);
    return ((localVal & ((uint32_t)0x0003f000)) >> 12);
}

static inline void rf_lo_sdm_bypass_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011c0);
    localVal &= ~((uint32_t)0x0003f000);
    localVal |= (x << 12)&((uint32_t)0x0003f000);
    REG_PL_WR(0x400011c0,localVal);
}

static inline uint32_t rf_lo_center_freq_mhz_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011c0);
    return ((localVal & ((uint32_t)0x00000fff)) >> 0);
}

static inline void rf_lo_center_freq_mhz_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011c0);
    localVal &= ~((uint32_t)0x00000fff);
    localVal |= (x << 0)&((uint32_t)0x00000fff);
    REG_PL_WR(0x400011c0,localVal);
}

static inline uint32_t rf_lo_sdmin_center_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011c4);
    return ((localVal & ((uint32_t)0x1fffffff)) >> 0);
}

static inline void rf_lo_sdmin_center_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011c4);
    localVal &= ~((uint32_t)0x1fffffff);
    localVal |= (x << 0)&((uint32_t)0x1fffffff);
    REG_PL_WR(0x400011c4,localVal);
}

static inline uint32_t rf_lo_sdmin_1m_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011c8);
    return ((localVal & ((uint32_t)0x000fffff)) >> 0);
}

static inline void rf_lo_sdmin_1m_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011c8);
    localVal &= ~((uint32_t)0x000fffff);
    localVal |= (x << 0)&((uint32_t)0x000fffff);
    REG_PL_WR(0x400011c8,localVal);
}

static inline uint32_t rf_lo_sdmin_if_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011cc);
    return ((localVal & ((uint32_t)0x000fffff)) >> 0);
}

static inline void rf_lo_sdmin_if_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011cc);
    localVal &= ~((uint32_t)0x000fffff);
    localVal |= (x << 0)&((uint32_t)0x000fffff);
    REG_PL_WR(0x400011cc,localVal);
}

static inline uint32_t rf_rbb_bt_mode_ble_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x400011d0);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_rbb_bt_mode_ble_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x400011d0);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x400011d0,localVal);
}

static inline uint32_t rf_singen_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_singen_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x4000120c,localVal);
}

static inline uint32_t rf_singen_clkdiv_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    return ((localVal & ((uint32_t)0x60000000)) >> 29);
}

static inline void rf_singen_clkdiv_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    localVal &= ~((uint32_t)0x60000000);
    localVal |= (x << 29)&((uint32_t)0x60000000);
    REG_PL_WR(0x4000120c,localVal);
}

static inline uint32_t rf_singen_unsign_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void rf_singen_unsign_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x4000120c,localVal);
}

static inline uint32_t rf_singen_inc_step0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void rf_singen_inc_step0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000120c,localVal);
}

static inline uint32_t rf_singen_inc_step1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_singen_inc_step1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000120c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000120c,localVal);
}

static inline uint32_t rf_singen_mode_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001210);
    return ((localVal & ((uint32_t)0xf0000000)) >> 28);
}

static inline void rf_singen_mode_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001210);
    localVal &= ~((uint32_t)0xf0000000);
    localVal |= (x << 28)&((uint32_t)0xf0000000);
    REG_PL_WR(0x40001210,localVal);
}

static inline uint32_t rf_singen_clkdiv_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001210);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void rf_singen_clkdiv_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001210);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40001210,localVal);
}

static inline uint32_t rf_singen_mode_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001210);
    return ((localVal & ((uint32_t)0x0000f000)) >> 12);
}

static inline void rf_singen_mode_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001210);
    localVal &= ~((uint32_t)0x0000f000);
    localVal |= (x << 12)&((uint32_t)0x0000f000);
    REG_PL_WR(0x40001210,localVal);
}

static inline uint32_t rf_singen_clkdiv_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001210);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_singen_clkdiv_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001210);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001210,localVal);
}

static inline uint32_t rf_singen_start_addr0_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001214);
    return ((localVal & ((uint32_t)0xffc00000)) >> 22);
}

static inline void rf_singen_start_addr0_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001214);
    localVal &= ~((uint32_t)0xffc00000);
    localVal |= (x << 22)&((uint32_t)0xffc00000);
    REG_PL_WR(0x40001214,localVal);
}

static inline uint32_t rf_singen_start_addr1_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001214);
    return ((localVal & ((uint32_t)0x003ff000)) >> 12);
}

static inline void rf_singen_start_addr1_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001214);
    localVal &= ~((uint32_t)0x003ff000);
    localVal |= (x << 12)&((uint32_t)0x003ff000);
    REG_PL_WR(0x40001214,localVal);
}

static inline uint32_t rf_singen_gain_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001214);
    return ((localVal & ((uint32_t)0x000007ff)) >> 0);
}

static inline void rf_singen_gain_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001214);
    localVal &= ~((uint32_t)0x000007ff);
    localVal |= (x << 0)&((uint32_t)0x000007ff);
    REG_PL_WR(0x40001214,localVal);
}

static inline uint32_t rf_singen_start_addr0_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001218);
    return ((localVal & ((uint32_t)0xffc00000)) >> 22);
}

static inline void rf_singen_start_addr0_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001218);
    localVal &= ~((uint32_t)0xffc00000);
    localVal |= (x << 22)&((uint32_t)0xffc00000);
    REG_PL_WR(0x40001218,localVal);
}

static inline uint32_t rf_singen_start_addr1_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001218);
    return ((localVal & ((uint32_t)0x003ff000)) >> 12);
}

static inline void rf_singen_start_addr1_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001218);
    localVal &= ~((uint32_t)0x003ff000);
    localVal |= (x << 12)&((uint32_t)0x003ff000);
    REG_PL_WR(0x40001218,localVal);
}

static inline uint32_t rf_singen_gain_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001218);
    return ((localVal & ((uint32_t)0x000007ff)) >> 0);
}

static inline void rf_singen_gain_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001218);
    localVal &= ~((uint32_t)0x000007ff);
    localVal |= (x << 0)&((uint32_t)0x000007ff);
    REG_PL_WR(0x40001218,localVal);
}

static inline uint32_t rf_singen_fix_en_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000121c);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void rf_singen_fix_en_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000121c);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x4000121c,localVal);
}

static inline uint32_t rf_singen_fix_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000121c);
    return ((localVal & ((uint32_t)0x0fff0000)) >> 16);
}

static inline void rf_singen_fix_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000121c);
    localVal &= ~((uint32_t)0x0fff0000);
    localVal |= (x << 16)&((uint32_t)0x0fff0000);
    REG_PL_WR(0x4000121c,localVal);
}

static inline uint32_t rf_singen_fix_en_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000121c);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_singen_fix_en_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000121c);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x4000121c,localVal);
}

static inline uint32_t rf_singen_fix_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000121c);
    return ((localVal & ((uint32_t)0x00000fff)) >> 0);
}

static inline void rf_singen_fix_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000121c);
    localVal &= ~((uint32_t)0x00000fff);
    localVal |= (x << 0)&((uint32_t)0x00000fff);
    REG_PL_WR(0x4000121c,localVal);
}

static inline uint32_t rf_test_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0xf0000000)) >> 28);
}

static inline void rf_test_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0xf0000000);
    localVal |= (x << 28)&((uint32_t)0xf0000000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_bbmode_4s_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x08000000)) >> 27);
}

static inline void rf_bbmode_4s_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x08000000);
    localVal |= (x << 27)&((uint32_t)0x08000000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_bbmode_4s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

static inline void rf_bbmode_4s_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x04000000);
    localVal |= (x << 26)&((uint32_t)0x04000000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_wifimode_4s_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x02000000)) >> 25);
}

static inline void rf_wifimode_4s_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x02000000);
    localVal |= (x << 25)&((uint32_t)0x02000000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_wifimode_4s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x01800000)) >> 23);
}

static inline void rf_wifimode_4s_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x01800000);
    localVal |= (x << 23)&((uint32_t)0x01800000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_ch_ind_ble_4s_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00400000)) >> 22);
}

static inline void rf_ch_ind_ble_4s_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00400000);
    localVal |= (x << 22)&((uint32_t)0x00400000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_ch_ind_ble_4s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x003f8000)) >> 15);
}

static inline void rf_ch_ind_ble_4s_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x003f8000);
    localVal |= (x << 15)&((uint32_t)0x003f8000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_pad_dac_clkout_inv_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_pad_dac_clkout_inv_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_pad_adc_clkout_inv_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_pad_adc_clkout_inv_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_tx_test_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00001800)) >> 11);
}

static inline void rf_tx_test_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00001800);
    localVal |= (x << 11)&((uint32_t)0x00001800);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_rx_test_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000600)) >> 9);
}

static inline void rf_rx_test_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000600);
    localVal |= (x << 9)&((uint32_t)0x00000600);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_tx_dfe_en_4s_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_tx_dfe_en_4s_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_tx_dfe_en_4s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_tx_dfe_en_4s_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_rx_dfe_en_4s_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_rx_dfe_en_4s_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_rx_dfe_en_4s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_rx_dfe_en_4s_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rfckg_dac_afifo_inv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rfckg_dac_afifo_inv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rfckg_adc_clkout_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rfckg_adc_clkout_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rfckg_adc_afifo_inv_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rfckg_adc_afifo_inv_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rfckg_txclk_4s_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rfckg_txclk_4s_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rfckg_rxclk_4s_on_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rfckg_rxclk_4s_on_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001220);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001220,localVal);
}

static inline uint32_t rf_test_read_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001224);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t rfif_ppud_manaual_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void rfif_ppud_manaual_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40001228,localVal);
}

static inline uint32_t rfif_ppud_cnt1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    return ((localVal & ((uint32_t)0x3e000000)) >> 25);
}

static inline void rfif_ppud_cnt1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    localVal &= ~((uint32_t)0x3e000000);
    localVal |= (x << 25)&((uint32_t)0x3e000000);
    REG_PL_WR(0x40001228,localVal);
}

static inline uint32_t rfif_ppud_cnt2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    return ((localVal & ((uint32_t)0x01ff0000)) >> 16);
}

static inline void rfif_ppud_cnt2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    localVal &= ~((uint32_t)0x01ff0000);
    localVal |= (x << 16)&((uint32_t)0x01ff0000);
    REG_PL_WR(0x40001228,localVal);
}

static inline uint32_t rfif_int_lo_unlocked_mask_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rfif_int_lo_unlocked_mask_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001228,localVal);
}

static inline uint32_t rfckg_rxclk_div2_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rfckg_rxclk_div2_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001228,localVal);
}

static inline uint32_t rf_test_gc_from_pad_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_test_gc_from_pad_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001228,localVal);
}

static inline uint32_t rf_test_from_pad_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_test_from_pad_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001228);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001228,localVal);
}

static inline uint32_t rf_data_temp_0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000122c);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void rf_data_temp_0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000122c);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x4000122c,localVal);
}

static inline uint32_t rf_data_temp_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001230);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void rf_data_temp_1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001230);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40001230,localVal);
}

static inline uint32_t rf_data_temp_2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001234);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void rf_data_temp_2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001234);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40001234,localVal);
}

static inline uint32_t rf_data_temp_3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001238);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void rf_data_temp_3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001238);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40001238,localVal);
}

static inline uint32_t rf_sram_ext_clr_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000123c);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_sram_ext_clr_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000123c);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x4000123c,localVal);
}

static inline uint32_t rf_sram_swap_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000123c);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_sram_swap_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000123c);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x4000123c,localVal);
}

static inline uint32_t rf_sram_link_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000123c);
    return ((localVal & ((uint32_t)0x00030000)) >> 16);
}

static inline void rf_sram_link_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000123c);
    localVal &= ~((uint32_t)0x00030000);
    localVal |= (x << 16)&((uint32_t)0x00030000);
    REG_PL_WR(0x4000123c,localVal);
}

static inline uint32_t rf_sram_link_dly_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000123c);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void rf_sram_link_dly_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000123c);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x4000123c,localVal);
}

static inline uint32_t rf_sram_adc_done_cnt_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001240);
    return ((localVal & ((uint32_t)0xffff0000)) >> 16);
}

static inline uint32_t rf_sram_adc_sts_clr_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001240);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_sram_adc_sts_clr_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001240);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001240,localVal);
}

static inline uint32_t rf_sram_adc_loop_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001240);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_sram_adc_loop_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001240);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001240,localVal);
}

static inline uint32_t rf_sram_adc_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001240);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_sram_adc_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001240);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001240,localVal);
}

static inline uint32_t rf_sram_adc_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001240);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline uint32_t rf_sram_adc_addr_start_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001244);
    return ((localVal & ((uint32_t)0xffff0000)) >> 16);
}

static inline void rf_sram_adc_addr_start_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001244);
    localVal &= ~((uint32_t)0xffff0000);
    localVal |= (x << 16)&((uint32_t)0xffff0000);
    REG_PL_WR(0x40001244,localVal);
}

static inline uint32_t rf_sram_adc_addr_end_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001244);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void rf_sram_adc_addr_end_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001244);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x40001244,localVal);
}

static inline uint32_t rf_sram_adc_sts_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001248);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t rf_sram_dac_done_cnt_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000124c);
    return ((localVal & ((uint32_t)0xffff0000)) >> 16);
}

static inline uint32_t rf_sram_dac_sts_clr_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000124c);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_sram_dac_sts_clr_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000124c);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x4000124c,localVal);
}

static inline uint32_t rf_sram_dac_loop_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000124c);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_sram_dac_loop_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000124c);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x4000124c,localVal);
}

static inline uint32_t rf_sram_dac_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000124c);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_sram_dac_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000124c);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x4000124c,localVal);
}

static inline uint32_t rf_sram_dac_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000124c);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline uint32_t rf_sram_dac_addr_start_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001250);
    return ((localVal & ((uint32_t)0xffff0000)) >> 16);
}

static inline void rf_sram_dac_addr_start_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001250);
    localVal &= ~((uint32_t)0xffff0000);
    localVal |= (x << 16)&((uint32_t)0xffff0000);
    REG_PL_WR(0x40001250,localVal);
}

static inline uint32_t rf_sram_dac_addr_end_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001250);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void rf_sram_dac_addr_end_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001250);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x40001250,localVal);
}

static inline uint32_t rf_sram_dac_sts_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001254);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline uint32_t rf_ical_f_ud_inv_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_ical_f_ud_inv_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40001258,localVal);
}

static inline uint32_t rf_ical_a_ud_inv_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void rf_ical_a_ud_inv_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40001258,localVal);
}

static inline uint32_t rf_ical_f_cnt_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    return ((localVal & ((uint32_t)0x3ff00000)) >> 20);
}

static inline void rf_ical_f_cnt_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    localVal &= ~((uint32_t)0x3ff00000);
    localVal |= (x << 20)&((uint32_t)0x3ff00000);
    REG_PL_WR(0x40001258,localVal);
}

static inline uint32_t rf_ical_a_cnt_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    return ((localVal & ((uint32_t)0x000ffc00)) >> 10);
}

static inline void rf_ical_a_cnt_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    localVal &= ~((uint32_t)0x000ffc00);
    localVal |= (x << 10)&((uint32_t)0x000ffc00);
    REG_PL_WR(0x40001258,localVal);
}

static inline uint32_t rf_ical_r_cnt_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_ical_r_cnt_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001258);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001258,localVal);
}

static inline uint32_t rf_ical_r_os_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000125c);
    return ((localVal & ((uint32_t)0x3ff00000)) >> 20);
}

static inline uint32_t rf_ical_r_os_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000125c);
    return ((localVal & ((uint32_t)0x000ffc00)) >> 10);
}

static inline uint32_t rf_ical_r_avg_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000125c);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void rf_ical_r_avg_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000125c);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x4000125c,localVal);
}

static inline uint32_t rf_ical_period_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001260);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void rf_ical_period_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001260);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x40001260,localVal);
}

static inline uint32_t rf_ch_ind_wifi_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001264);
    return ((localVal & ((uint32_t)0x00000fff)) >> 0);
}

static inline void rf_ch_ind_wifi_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001264);
    localVal &= ~((uint32_t)0x00000fff);
    localVal |= (x << 0)&((uint32_t)0x00000fff);
    REG_PL_WR(0x40001264,localVal);
}

static inline uint32_t rf_fsm_pu_pa_dly_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    return ((localVal & ((uint32_t)0x3ff00000)) >> 20);
}

static inline void rf_fsm_pu_pa_dly_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    localVal &= ~((uint32_t)0x3ff00000);
    localVal |= (x << 20)&((uint32_t)0x3ff00000);
    REG_PL_WR(0x40001268,localVal);
}

static inline uint32_t rf_fsm_lo_rdy_sbclr_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_fsm_lo_rdy_sbclr_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001268,localVal);
}

static inline uint32_t rf_fsm_lo_rdy_4s_1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_fsm_lo_rdy_4s_1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001268,localVal);
}

static inline uint32_t rf_fsm_lo_rdy_rst_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_fsm_lo_rdy_rst_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001268,localVal);
}

static inline uint32_t rf_fsm_lo_rdy_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline uint32_t rf_fsm_lo_time_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void rf_fsm_lo_time_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001268);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x40001268,localVal);
}

static inline uint32_t rf_fsm_dfe_rx_dly_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    return ((localVal & ((uint32_t)0x3ff00000)) >> 20);
}

static inline void rf_fsm_dfe_rx_dly_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    localVal &= ~((uint32_t)0x3ff00000);
    localVal |= (x << 20)&((uint32_t)0x3ff00000);
    REG_PL_WR(0x4000126c,localVal);
}

static inline uint32_t rf_fsm_dfe_tx_dly_n_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    return ((localVal & ((uint32_t)0x000ffc00)) >> 10);
}

static inline void rf_fsm_dfe_tx_dly_n_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    localVal &= ~((uint32_t)0x000ffc00);
    localVal |= (x << 10)&((uint32_t)0x000ffc00);
    REG_PL_WR(0x4000126c,localVal);
}

static inline uint32_t rf_trx_ble_4s_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_trx_ble_4s_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x4000126c,localVal);
}

static inline uint32_t rf_trx_sw_ble_4s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_trx_sw_ble_4s_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x4000126c,localVal);
}

static inline uint32_t rf_trx_en_ble_4s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_trx_en_ble_4s_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x4000126c,localVal);
}

static inline uint32_t rf_fsm_st_dbg_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fsm_st_dbg_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x4000126c,localVal);
}

static inline uint32_t rf_fsm_st_dbg_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_fsm_st_dbg_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000126c);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x4000126c,localVal);
}

static inline uint32_t rf_pkdet_out_mode_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001270);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_pkdet_out_mode_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001270);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001270,localVal);
}

static inline uint32_t rf_pkdet_out_cnt_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001270);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_pkdet_out_cnt_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001270);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001270,localVal);
}

static inline uint32_t rf_pkdet_out_cnt_sts_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001270);
    return ((localVal & ((uint32_t)0x0000000f)) >> 0);
}

static inline uint32_t rf_tx_dvga_gain_ctrl_hw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_tx_dvga_gain_ctrl_hw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40001600,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    return ((localVal & ((uint32_t)0x7f000000)) >> 24);
}

static inline void rf_tx_dvga_gain_qdb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    localVal &= ~((uint32_t)0x7f000000);
    localVal |= (x << 24)&((uint32_t)0x7f000000);
    REG_PL_WR(0x40001600,localVal);
}

static inline uint32_t rf_tx_iqc_gain_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void rf_tx_iqc_gain_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x40001600,localVal);
}

static inline uint32_t rf_tx_iqc_gain_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    return ((localVal & ((uint32_t)0x007ff000)) >> 12);
}

static inline void rf_tx_iqc_gain_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    localVal &= ~((uint32_t)0x007ff000);
    localVal |= (x << 12)&((uint32_t)0x007ff000);
    REG_PL_WR(0x40001600,localVal);
}

static inline uint32_t rf_tx_iqc_phase_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_tx_iqc_phase_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001600,localVal);
}

static inline uint32_t rf_tx_iqc_phase_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_tx_iqc_phase_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001600);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001600,localVal);
}

static inline uint32_t rf_tx_dac_iq_swap_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001604);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_tx_dac_iq_swap_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001604);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40001604,localVal);
}

static inline uint32_t rf_tx_dac_dat_format_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001604);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void rf_tx_dac_dat_format_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001604);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40001604,localVal);
}

static inline uint32_t rf_tx_dac_os_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001604);
    return ((localVal & ((uint32_t)0x0fff0000)) >> 16);
}

static inline void rf_tx_dac_os_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001604);
    localVal &= ~((uint32_t)0x0fff0000);
    localVal |= (x << 16)&((uint32_t)0x0fff0000);
    REG_PL_WR(0x40001604,localVal);
}

static inline uint32_t rf_tx_dac_os_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001604);
    return ((localVal & ((uint32_t)0x00000fff)) >> 0);
}

static inline void rf_tx_dac_os_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001604);
    localVal &= ~((uint32_t)0x00000fff);
    localVal |= (x << 0)&((uint32_t)0x00000fff);
    REG_PL_WR(0x40001604,localVal);
}

static inline uint32_t rf_rx_adc_iq_swap_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_rx_adc_iq_swap_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40001608,localVal);
}

static inline uint32_t rf_rx_adc_dat_format_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void rf_rx_adc_dat_format_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40001608,localVal);
}

static inline uint32_t rf_rx_adc_low_pow_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

static inline void rf_rx_adc_low_pow_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    localVal &= ~((uint32_t)0x20000000);
    localVal |= (x << 29)&((uint32_t)0x20000000);
    REG_PL_WR(0x40001608,localVal);
}

static inline uint32_t rf_rx_adc_dce_flt_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void rf_rx_adc_dce_flt_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x40001608,localVal);
}

static inline uint32_t rf_rx_adc_os_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void rf_rx_adc_os_q_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40001608,localVal);
}

static inline uint32_t rf_rx_adc_os_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_rx_adc_os_i_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001608);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001608,localVal);
}

static inline uint32_t rf_rx_adc_4s_q_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000160c);
    return ((localVal & ((uint32_t)0x04000000)) >> 26);
}

static inline void rf_rx_adc_4s_q_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000160c);
    localVal &= ~((uint32_t)0x04000000);
    localVal |= (x << 26)&((uint32_t)0x04000000);
    REG_PL_WR(0x4000160c,localVal);
}

static inline uint32_t rf_rx_adc_4s_q_val_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000160c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void rf_rx_adc_4s_q_val_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000160c);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x4000160c,localVal);
}

static inline uint32_t rf_rx_adc_4s_i_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000160c);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_rx_adc_4s_i_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000160c);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x4000160c,localVal);
}

static inline uint32_t rf_rx_adc_4s_i_val_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000160c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_rx_adc_4s_i_val_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000160c);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x4000160c,localVal);
}

static inline uint32_t rf_rx_pf_i_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001610);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void rf_rx_pf_i_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001610);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40001610,localVal);
}

static inline uint32_t rf_rx_pf_q_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001610);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void rf_rx_pf_q_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001610);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40001610,localVal);
}

static inline uint32_t rf_rx_pf_th1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001610);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline void rf_rx_pf_th1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001610);
    localVal &= ~((uint32_t)0x03ff0000);
    localVal |= (x << 16)&((uint32_t)0x03ff0000);
    REG_PL_WR(0x40001610,localVal);
}

static inline uint32_t rf_rx_pf_th2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001610);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_rx_pf_th2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001610);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001610,localVal);
}

static inline uint32_t rf_rx_iqc_gain_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001614);
    return ((localVal & ((uint32_t)0x00800000)) >> 23);
}

static inline void rf_rx_iqc_gain_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001614);
    localVal &= ~((uint32_t)0x00800000);
    localVal |= (x << 23)&((uint32_t)0x00800000);
    REG_PL_WR(0x40001614,localVal);
}

static inline uint32_t rf_rx_iqc_gain_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001614);
    return ((localVal & ((uint32_t)0x007ff000)) >> 12);
}

static inline void rf_rx_iqc_gain_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001614);
    localVal &= ~((uint32_t)0x007ff000);
    localVal |= (x << 12)&((uint32_t)0x007ff000);
    REG_PL_WR(0x40001614,localVal);
}

static inline uint32_t rf_rx_iqc_phase_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001614);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_rx_iqc_phase_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001614);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001614,localVal);
}

static inline uint32_t rf_rx_iqc_phase_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001614);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline void rf_rx_iqc_phase_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001614);
    localVal &= ~((uint32_t)0x000003ff);
    localVal |= (x << 0)&((uint32_t)0x000003ff);
    REG_PL_WR(0x40001614,localVal);
}

static inline uint32_t rf_rx_pm_in_sel_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    return ((localVal & ((uint32_t)0xc0000000)) >> 30);
}

static inline void rf_rx_pm_in_sel_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    localVal &= ~((uint32_t)0xc0000000);
    localVal |= (x << 30)&((uint32_t)0xc0000000);
    REG_PL_WR(0x40001618,localVal);
}

static inline uint32_t rf_rx_pm_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

static inline void rf_rx_pm_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    localVal &= ~((uint32_t)0x20000000);
    localVal |= (x << 29)&((uint32_t)0x20000000);
    REG_PL_WR(0x40001618,localVal);
}

static inline uint32_t rf_rx_pm_done_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline uint32_t rf_rx_pm_freqshift_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_rx_pm_freqshift_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001618,localVal);
}

static inline uint32_t rf_rx_pm_freqshift_cw_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    return ((localVal & ((uint32_t)0x000fffff)) >> 0);
}

static inline void rf_rx_pm_freqshift_cw_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001618);
    localVal &= ~((uint32_t)0x000fffff);
    localVal |= (x << 0)&((uint32_t)0x000fffff);
    REG_PL_WR(0x40001618,localVal);
}

static inline uint32_t rf_rx_pm_acc_len_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000161c);
    return ((localVal & ((uint32_t)0xffff0000)) >> 16);
}

static inline void rf_rx_pm_acc_len_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000161c);
    localVal &= ~((uint32_t)0xffff0000);
    localVal |= (x << 16)&((uint32_t)0xffff0000);
    REG_PL_WR(0x4000161c,localVal);
}

static inline uint32_t rf_rx_pm_start_ofs_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000161c);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void rf_rx_pm_start_ofs_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000161c);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x4000161c,localVal);
}

static inline uint32_t rf_rx_pm_iqacc_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001620);
    return ((localVal & ((uint32_t)0x01ffffff)) >> 0);
}

static inline uint32_t rf_rx_pm_iqacc_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001624);
    return ((localVal & ((uint32_t)0x01ffffff)) >> 0);
}

static inline uint32_t rf_dfe_dac_raw_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001628);
    return ((localVal & ((uint32_t)0x07ff0000)) >> 16);
}

static inline uint32_t rf_dfe_dac_raw_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001628);
    return ((localVal & ((uint32_t)0x000007ff)) >> 0);
}

static inline uint32_t rf_dfe_adc_raw_q_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000162c);
    return ((localVal & ((uint32_t)0x03ff0000)) >> 16);
}

static inline uint32_t rf_dfe_adc_raw_i_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000162c);
    return ((localVal & ((uint32_t)0x000003ff)) >> 0);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001630);
    return ((localVal & ((uint32_t)0x7f000000)) >> 24);
}

static inline void rf_tx_dvga_gain_qdb_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001630);
    localVal &= ~((uint32_t)0x7f000000);
    localVal |= (x << 24)&((uint32_t)0x7f000000);
    REG_PL_WR(0x40001630,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001630);
    return ((localVal & ((uint32_t)0x007f0000)) >> 16);
}

static inline void rf_tx_dvga_gain_qdb_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001630);
    localVal &= ~((uint32_t)0x007f0000);
    localVal |= (x << 16)&((uint32_t)0x007f0000);
    REG_PL_WR(0x40001630,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001630);
    return ((localVal & ((uint32_t)0x00007f00)) >> 8);
}

static inline void rf_tx_dvga_gain_qdb_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001630);
    localVal &= ~((uint32_t)0x00007f00);
    localVal |= (x << 8)&((uint32_t)0x00007f00);
    REG_PL_WR(0x40001630,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001630);
    return ((localVal & ((uint32_t)0x0000007f)) >> 0);
}

static inline void rf_tx_dvga_gain_qdb_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001630);
    localVal &= ~((uint32_t)0x0000007f);
    localVal |= (x << 0)&((uint32_t)0x0000007f);
    REG_PL_WR(0x40001630,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001634);
    return ((localVal & ((uint32_t)0x7f000000)) >> 24);
}

static inline void rf_tx_dvga_gain_qdb_gc7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001634);
    localVal &= ~((uint32_t)0x7f000000);
    localVal |= (x << 24)&((uint32_t)0x7f000000);
    REG_PL_WR(0x40001634,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001634);
    return ((localVal & ((uint32_t)0x007f0000)) >> 16);
}

static inline void rf_tx_dvga_gain_qdb_gc6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001634);
    localVal &= ~((uint32_t)0x007f0000);
    localVal |= (x << 16)&((uint32_t)0x007f0000);
    REG_PL_WR(0x40001634,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001634);
    return ((localVal & ((uint32_t)0x00007f00)) >> 8);
}

static inline void rf_tx_dvga_gain_qdb_gc5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001634);
    localVal &= ~((uint32_t)0x00007f00);
    localVal |= (x << 8)&((uint32_t)0x00007f00);
    REG_PL_WR(0x40001634,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001634);
    return ((localVal & ((uint32_t)0x0000007f)) >> 0);
}

static inline void rf_tx_dvga_gain_qdb_gc4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001634);
    localVal &= ~((uint32_t)0x0000007f);
    localVal |= (x << 0)&((uint32_t)0x0000007f);
    REG_PL_WR(0x40001634,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001638);
    return ((localVal & ((uint32_t)0x7f000000)) >> 24);
}

static inline void rf_tx_dvga_gain_qdb_gc11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001638);
    localVal &= ~((uint32_t)0x7f000000);
    localVal |= (x << 24)&((uint32_t)0x7f000000);
    REG_PL_WR(0x40001638,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001638);
    return ((localVal & ((uint32_t)0x007f0000)) >> 16);
}

static inline void rf_tx_dvga_gain_qdb_gc10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001638);
    localVal &= ~((uint32_t)0x007f0000);
    localVal |= (x << 16)&((uint32_t)0x007f0000);
    REG_PL_WR(0x40001638,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc9_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001638);
    return ((localVal & ((uint32_t)0x00007f00)) >> 8);
}

static inline void rf_tx_dvga_gain_qdb_gc9_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001638);
    localVal &= ~((uint32_t)0x00007f00);
    localVal |= (x << 8)&((uint32_t)0x00007f00);
    REG_PL_WR(0x40001638,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc8_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001638);
    return ((localVal & ((uint32_t)0x0000007f)) >> 0);
}

static inline void rf_tx_dvga_gain_qdb_gc8_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001638);
    localVal &= ~((uint32_t)0x0000007f);
    localVal |= (x << 0)&((uint32_t)0x0000007f);
    REG_PL_WR(0x40001638,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000163c);
    return ((localVal & ((uint32_t)0x7f000000)) >> 24);
}

static inline void rf_tx_dvga_gain_qdb_gc15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000163c);
    localVal &= ~((uint32_t)0x7f000000);
    localVal |= (x << 24)&((uint32_t)0x7f000000);
    REG_PL_WR(0x4000163c,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000163c);
    return ((localVal & ((uint32_t)0x007f0000)) >> 16);
}

static inline void rf_tx_dvga_gain_qdb_gc14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000163c);
    localVal &= ~((uint32_t)0x007f0000);
    localVal |= (x << 16)&((uint32_t)0x007f0000);
    REG_PL_WR(0x4000163c,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000163c);
    return ((localVal & ((uint32_t)0x00007f00)) >> 8);
}

static inline void rf_tx_dvga_gain_qdb_gc13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000163c);
    localVal &= ~((uint32_t)0x00007f00);
    localVal |= (x << 8)&((uint32_t)0x00007f00);
    REG_PL_WR(0x4000163c,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_gc12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000163c);
    return ((localVal & ((uint32_t)0x0000007f)) >> 0);
}

static inline void rf_tx_dvga_gain_qdb_gc12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000163c);
    localVal &= ~((uint32_t)0x0000007f);
    localVal |= (x << 0)&((uint32_t)0x0000007f);
    REG_PL_WR(0x4000163c,localVal);
}

static inline uint32_t rf_tbb_ind_gc7_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

static inline void rf_tbb_ind_gc7_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    localVal &= ~((uint32_t)0x70000000);
    localVal |= (x << 28)&((uint32_t)0x70000000);
    REG_PL_WR(0x40001640,localVal);
}

static inline uint32_t rf_tbb_ind_gc6_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void rf_tbb_ind_gc6_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x40001640,localVal);
}

static inline uint32_t rf_tbb_ind_gc5_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_tbb_ind_gc5_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x40001640,localVal);
}

static inline uint32_t rf_tbb_ind_gc4_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

static inline void rf_tbb_ind_gc4_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    localVal &= ~((uint32_t)0x00070000);
    localVal |= (x << 16)&((uint32_t)0x00070000);
    REG_PL_WR(0x40001640,localVal);
}

static inline uint32_t rf_tbb_ind_gc3_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_tbb_ind_gc3_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001640,localVal);
}

static inline uint32_t rf_tbb_ind_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_tbb_ind_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x40001640,localVal);
}

static inline uint32_t rf_tbb_ind_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_tbb_ind_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x40001640,localVal);
}

static inline uint32_t rf_tbb_ind_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_tbb_ind_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001640);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x40001640,localVal);
}

static inline uint32_t rf_tbb_ind_gc15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    return ((localVal & ((uint32_t)0x70000000)) >> 28);
}

static inline void rf_tbb_ind_gc15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    localVal &= ~((uint32_t)0x70000000);
    localVal |= (x << 28)&((uint32_t)0x70000000);
    REG_PL_WR(0x40001644,localVal);
}

static inline uint32_t rf_tbb_ind_gc14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    return ((localVal & ((uint32_t)0x07000000)) >> 24);
}

static inline void rf_tbb_ind_gc14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    localVal &= ~((uint32_t)0x07000000);
    localVal |= (x << 24)&((uint32_t)0x07000000);
    REG_PL_WR(0x40001644,localVal);
}

static inline uint32_t rf_tbb_ind_gc13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    return ((localVal & ((uint32_t)0x00700000)) >> 20);
}

static inline void rf_tbb_ind_gc13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    localVal &= ~((uint32_t)0x00700000);
    localVal |= (x << 20)&((uint32_t)0x00700000);
    REG_PL_WR(0x40001644,localVal);
}

static inline uint32_t rf_tbb_ind_gc12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    return ((localVal & ((uint32_t)0x00070000)) >> 16);
}

static inline void rf_tbb_ind_gc12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    localVal &= ~((uint32_t)0x00070000);
    localVal |= (x << 16)&((uint32_t)0x00070000);
    REG_PL_WR(0x40001644,localVal);
}

static inline uint32_t rf_tbb_ind_gc11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    return ((localVal & ((uint32_t)0x00007000)) >> 12);
}

static inline void rf_tbb_ind_gc11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    localVal &= ~((uint32_t)0x00007000);
    localVal |= (x << 12)&((uint32_t)0x00007000);
    REG_PL_WR(0x40001644,localVal);
}

static inline uint32_t rf_tbb_ind_gc10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    return ((localVal & ((uint32_t)0x00000700)) >> 8);
}

static inline void rf_tbb_ind_gc10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    localVal &= ~((uint32_t)0x00000700);
    localVal |= (x << 8)&((uint32_t)0x00000700);
    REG_PL_WR(0x40001644,localVal);
}

static inline uint32_t rf_tbb_ind_gc9_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    return ((localVal & ((uint32_t)0x00000070)) >> 4);
}

static inline void rf_tbb_ind_gc9_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    localVal &= ~((uint32_t)0x00000070);
    localVal |= (x << 4)&((uint32_t)0x00000070);
    REG_PL_WR(0x40001644,localVal);
}

static inline uint32_t rf_tbb_ind_gc8_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_tbb_ind_gc8_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001644);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x40001644,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_ble_gc2_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001648);
    return ((localVal & ((uint32_t)0x007f0000)) >> 16);
}

static inline void rf_tx_dvga_gain_qdb_ble_gc2_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001648);
    localVal &= ~((uint32_t)0x007f0000);
    localVal |= (x << 16)&((uint32_t)0x007f0000);
    REG_PL_WR(0x40001648,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_ble_gc1_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001648);
    return ((localVal & ((uint32_t)0x00007f00)) >> 8);
}

static inline void rf_tx_dvga_gain_qdb_ble_gc1_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001648);
    localVal &= ~((uint32_t)0x00007f00);
    localVal |= (x << 8)&((uint32_t)0x00007f00);
    REG_PL_WR(0x40001648,localVal);
}

static inline uint32_t rf_tx_dvga_gain_qdb_ble_gc0_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001648);
    return ((localVal & ((uint32_t)0x0000007f)) >> 0);
}

static inline void rf_tx_dvga_gain_qdb_ble_gc0_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001648);
    localVal &= ~((uint32_t)0x0000007f);
    localVal |= (x << 0)&((uint32_t)0x0000007f);
    REG_PL_WR(0x40001648,localVal);
}

static inline uint32_t rf_rx_notch1_nrmfc_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    return ((localVal & ((uint32_t)0x00ff0000)) >> 16);
}

static inline void rf_rx_notch1_nrmfc_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    localVal &= ~((uint32_t)0x00ff0000);
    localVal |= (x << 16)&((uint32_t)0x00ff0000);
    REG_PL_WR(0x40001700,localVal);
}

static inline uint32_t rf_rx_notch0_nrmfc_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    return ((localVal & ((uint32_t)0x0000ff00)) >> 8);
}

static inline void rf_rx_notch0_nrmfc_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    localVal &= ~((uint32_t)0x0000ff00);
    localVal |= (x << 8)&((uint32_t)0x0000ff00);
    REG_PL_WR(0x40001700,localVal);
}

static inline uint32_t rf_rx_notch1_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_rx_notch1_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001700,localVal);
}

static inline uint32_t rf_rx_notch0_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_rx_notch0_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001700,localVal);
}

static inline uint32_t rf_rx_notch1_alpha_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    return ((localVal & ((uint32_t)0x00000038)) >> 3);
}

static inline void rf_rx_notch1_alpha_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    localVal &= ~((uint32_t)0x00000038);
    localVal |= (x << 3)&((uint32_t)0x00000038);
    REG_PL_WR(0x40001700,localVal);
}

static inline uint32_t rf_rx_notch0_alpha_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    return ((localVal & ((uint32_t)0x00000007)) >> 0);
}

static inline void rf_rx_notch0_alpha_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001700);
    localVal &= ~((uint32_t)0x00000007);
    localVal |= (x << 0)&((uint32_t)0x00000007);
    REG_PL_WR(0x40001700,localVal);
}

#endif