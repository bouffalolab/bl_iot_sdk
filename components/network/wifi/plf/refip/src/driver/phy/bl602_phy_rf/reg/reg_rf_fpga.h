#ifndef _REG_RF_FPGA_H_
#define _REG_RF_FPGA_H_

#include "co_int.h"
#include "arch.h"
#include "_reg_access.h"

static inline uint32_t fpga_rf_fsm_pu_sb_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x80000000)) >> 31);
}

static inline void fpga_rf_fsm_pu_sb_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    localVal &= ~((uint32_t)0x80000000);
    localVal |= (x << 31)&((uint32_t)0x80000000);
    REG_PL_WR(0x40001f00,localVal);
}

static inline uint32_t fpga_rf_fsm_pu_lo_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x40000000)) >> 30);
}

static inline void fpga_rf_fsm_pu_lo_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    localVal &= ~((uint32_t)0x40000000);
    localVal |= (x << 30)&((uint32_t)0x40000000);
    REG_PL_WR(0x40001f00,localVal);
}

static inline uint32_t fpga_rf_fsm_pu_tx_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x20000000)) >> 29);
}

static inline void fpga_rf_fsm_pu_tx_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    localVal &= ~((uint32_t)0x20000000);
    localVal |= (x << 29)&((uint32_t)0x20000000);
    REG_PL_WR(0x40001f00,localVal);
}

static inline uint32_t fpga_rf_fsm_pu_rx_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x10000000)) >> 28);
}

static inline void fpga_rf_fsm_pu_rx_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    localVal &= ~((uint32_t)0x10000000);
    localVal |= (x << 28)&((uint32_t)0x10000000);
    REG_PL_WR(0x40001f00,localVal);
}

static inline uint32_t fpga_rf_fsm_state_cci_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x0f800000)) >> 23);
}

static inline uint32_t fpga_rf_fsm_gpio_first_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void fpga_rf_fsm_gpio_first_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001f00,localVal);
}

static inline uint32_t fpga_rf_fsm_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void fpga_rf_fsm_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001f00,localVal);
}

static inline uint32_t fpga_rf_fsm_st_cci_4s_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void fpga_rf_fsm_st_cci_4s_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001f00,localVal);
}

static inline uint32_t fpga_rf_fsm_st_cci_4s_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    return ((localVal & ((uint32_t)0x0000001f)) >> 0);
}

static inline void fpga_rf_fsm_st_cci_4s_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f00);
    localVal &= ~((uint32_t)0x0000001f);
    localVal |= (x << 0)&((uint32_t)0x0000001f);
    REG_PL_WR(0x40001f00,localVal);
}

static inline uint32_t fpga_rf_fsm_cci_wr_time_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f04);
    return ((localVal & ((uint32_t)0x00000fff)) >> 0);
}

static inline void fpga_rf_fsm_cci_wr_time_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f04);
    localVal &= ~((uint32_t)0x00000fff);
    localVal |= (x << 0)&((uint32_t)0x00000fff);
    REG_PL_WR(0x40001f04,localVal);
}

static inline uint32_t fpga_rf_fsm_dly_01_time_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f08);
    return ((localVal & ((uint32_t)0x0fff0000)) >> 16);
}

static inline void fpga_rf_fsm_dly_01_time_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f08);
    localVal &= ~((uint32_t)0x0fff0000);
    localVal |= (x << 16)&((uint32_t)0x0fff0000);
    REG_PL_WR(0x40001f08,localVal);
}

static inline uint32_t fpga_rf_fsm_dly_30_time_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f08);
    return ((localVal & ((uint32_t)0x00000fff)) >> 0);
}

static inline void fpga_rf_fsm_dly_30_time_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f08);
    localVal &= ~((uint32_t)0x00000fff);
    localVal |= (x << 0)&((uint32_t)0x00000fff);
    REG_PL_WR(0x40001f08,localVal);
}

static inline uint32_t fpga_rf_fsm_pu_sb_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f0c);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void fpga_rf_fsm_pu_sb_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f0c);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40001f0c,localVal);
}

static inline uint32_t fpga_rf_fsm_pu_lo_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f10);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void fpga_rf_fsm_pu_lo_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f10);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40001f10,localVal);
}

static inline uint32_t fpga_rf_fsm_pu_tx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f14);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void fpga_rf_fsm_pu_tx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f14);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40001f14,localVal);
}

static inline uint32_t fpga_rf_fsm_pu_rx_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f18);
    return ((localVal & ((uint32_t)0xffffffff)) >> 0);
}

static inline void fpga_rf_fsm_pu_rx_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f18);
    localVal &= ~((uint32_t)0xffffffff);
    localVal |= (x << 0)&((uint32_t)0xffffffff);
    REG_PL_WR(0x40001f18,localVal);
}

static inline uint32_t fpga_rf_fsm_cmd_en_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001f1c);
    return ((localVal & ((uint32_t)0x0000ffff)) >> 0);
}

static inline void fpga_rf_fsm_cmd_en_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001f1c);
    localVal &= ~((uint32_t)0x0000ffff);
    localVal |= (x << 0)&((uint32_t)0x0000ffff);
    REG_PL_WR(0x40001f1c,localVal);
}

#endif