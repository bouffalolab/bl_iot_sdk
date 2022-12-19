#ifndef _REG_RF_FSM_H_
#define _REG_RF_FSM_H_

#include "co_int.h"
#include "arch.h"
#include "_reg_access.h"

static inline uint32_t rf_fsm_vector_21_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_fsm_vector_21_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_fsm_vector_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_19_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_fsm_vector_19_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_18_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_fsm_vector_18_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_17_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_fsm_vector_17_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_16_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_fsm_vector_16_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_fsm_vector_15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_fsm_vector_14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_fsm_vector_13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_fsm_vector_12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_fsm_vector_11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_fsm_vector_10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_09_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_fsm_vector_09_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_08_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_fsm_vector_08_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_07_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_fsm_vector_07_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_06_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_fsm_vector_06_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_05_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_fsm_vector_05_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_04_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_fsm_vector_04_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fsm_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_fsm_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_fsm_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_fsm_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001500);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001500,localVal);
}

static inline uint32_t rf_fsm_sb_vector_21_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_fsm_sb_vector_21_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_fsm_sb_vector_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_19_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_fsm_sb_vector_19_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_18_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_fsm_sb_vector_18_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_17_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_fsm_sb_vector_17_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_16_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_fsm_sb_vector_16_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_fsm_sb_vector_15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_fsm_sb_vector_14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_fsm_sb_vector_13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_fsm_sb_vector_12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_fsm_sb_vector_11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_fsm_sb_vector_10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_09_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_fsm_sb_vector_09_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_08_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_fsm_sb_vector_08_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_07_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_fsm_sb_vector_07_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_06_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_fsm_sb_vector_06_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_05_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_fsm_sb_vector_05_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_04_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_fsm_sb_vector_04_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fsm_sb_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_fsm_sb_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_fsm_sb_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_sb_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_fsm_sb_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001504);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001504,localVal);
}

static inline uint32_t rf_fsm_lo_vector_21_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_fsm_lo_vector_21_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_fsm_lo_vector_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_19_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_fsm_lo_vector_19_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_18_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_fsm_lo_vector_18_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_17_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_fsm_lo_vector_17_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_16_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_fsm_lo_vector_16_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_fsm_lo_vector_15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_fsm_lo_vector_14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_fsm_lo_vector_13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_fsm_lo_vector_12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_fsm_lo_vector_11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_fsm_lo_vector_10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_09_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_fsm_lo_vector_09_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_08_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_fsm_lo_vector_08_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_07_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_fsm_lo_vector_07_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_06_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_fsm_lo_vector_06_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_05_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_fsm_lo_vector_05_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_04_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_fsm_lo_vector_04_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fsm_lo_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_fsm_lo_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_fsm_lo_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_lo_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_fsm_lo_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001508);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001508,localVal);
}

static inline uint32_t rf_fsm_rx_vector_21_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_fsm_rx_vector_21_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_fsm_rx_vector_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_19_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_fsm_rx_vector_19_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_18_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_fsm_rx_vector_18_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_17_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_fsm_rx_vector_17_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_16_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_fsm_rx_vector_16_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_fsm_rx_vector_15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_fsm_rx_vector_14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_fsm_rx_vector_13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_fsm_rx_vector_12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_fsm_rx_vector_11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_fsm_rx_vector_10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_09_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_fsm_rx_vector_09_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_08_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_fsm_rx_vector_08_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_07_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_fsm_rx_vector_07_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_06_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_fsm_rx_vector_06_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_05_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_fsm_rx_vector_05_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_04_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_fsm_rx_vector_04_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fsm_rx_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_fsm_rx_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_fsm_rx_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_rx_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_fsm_rx_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000150c);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x4000150c,localVal);
}

static inline uint32_t rf_fsm_tx_vector_21_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_fsm_tx_vector_21_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_fsm_tx_vector_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_19_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_fsm_tx_vector_19_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_18_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_fsm_tx_vector_18_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_17_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_fsm_tx_vector_17_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_16_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_fsm_tx_vector_16_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_fsm_tx_vector_15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_fsm_tx_vector_14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_fsm_tx_vector_13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_fsm_tx_vector_12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_fsm_tx_vector_11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_fsm_tx_vector_10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_09_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_fsm_tx_vector_09_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_08_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_fsm_tx_vector_08_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_07_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_fsm_tx_vector_07_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_06_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_fsm_tx_vector_06_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_05_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_fsm_tx_vector_05_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_04_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_fsm_tx_vector_04_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fsm_tx_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_fsm_tx_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_fsm_tx_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_tx_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_fsm_tx_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001510);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001510,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_21_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_fsm_t2r_iros_vector_21_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_fsm_t2r_iros_vector_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_19_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_fsm_t2r_iros_vector_19_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_18_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_fsm_t2r_iros_vector_18_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_17_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_fsm_t2r_iros_vector_17_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_16_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_fsm_t2r_iros_vector_16_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_fsm_t2r_iros_vector_15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_fsm_t2r_iros_vector_14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_fsm_t2r_iros_vector_13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_fsm_t2r_iros_vector_12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_fsm_t2r_iros_vector_11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_fsm_t2r_iros_vector_10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_09_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_fsm_t2r_iros_vector_09_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_08_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_fsm_t2r_iros_vector_08_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_07_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_fsm_t2r_iros_vector_07_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_06_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_fsm_t2r_iros_vector_06_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_05_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_fsm_t2r_iros_vector_05_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_04_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_fsm_t2r_iros_vector_04_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fsm_t2r_iros_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_fsm_t2r_iros_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_fsm_t2r_iros_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_t2r_iros_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_fsm_t2r_iros_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001514);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001514,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_21_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00200000)) >> 21);
}

static inline void rf_fsm_r2t_vector_21_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00200000);
    localVal |= (x << 21)&((uint32_t)0x00200000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_20_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00100000)) >> 20);
}

static inline void rf_fsm_r2t_vector_20_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00100000);
    localVal |= (x << 20)&((uint32_t)0x00100000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_19_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00080000)) >> 19);
}

static inline void rf_fsm_r2t_vector_19_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00080000);
    localVal |= (x << 19)&((uint32_t)0x00080000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_18_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00040000)) >> 18);
}

static inline void rf_fsm_r2t_vector_18_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00040000);
    localVal |= (x << 18)&((uint32_t)0x00040000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_17_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00020000)) >> 17);
}

static inline void rf_fsm_r2t_vector_17_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00020000);
    localVal |= (x << 17)&((uint32_t)0x00020000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_16_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00010000)) >> 16);
}

static inline void rf_fsm_r2t_vector_16_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00010000);
    localVal |= (x << 16)&((uint32_t)0x00010000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_15_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00008000)) >> 15);
}

static inline void rf_fsm_r2t_vector_15_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00008000);
    localVal |= (x << 15)&((uint32_t)0x00008000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_14_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00004000)) >> 14);
}

static inline void rf_fsm_r2t_vector_14_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00004000);
    localVal |= (x << 14)&((uint32_t)0x00004000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_13_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00002000)) >> 13);
}

static inline void rf_fsm_r2t_vector_13_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00002000);
    localVal |= (x << 13)&((uint32_t)0x00002000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_12_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00001000)) >> 12);
}

static inline void rf_fsm_r2t_vector_12_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00001000);
    localVal |= (x << 12)&((uint32_t)0x00001000);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_11_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000800)) >> 11);
}

static inline void rf_fsm_r2t_vector_11_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000800);
    localVal |= (x << 11)&((uint32_t)0x00000800);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_10_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000400)) >> 10);
}

static inline void rf_fsm_r2t_vector_10_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000400);
    localVal |= (x << 10)&((uint32_t)0x00000400);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_09_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000200)) >> 9);
}

static inline void rf_fsm_r2t_vector_09_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000200);
    localVal |= (x << 9)&((uint32_t)0x00000200);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_08_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000100)) >> 8);
}

static inline void rf_fsm_r2t_vector_08_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000100);
    localVal |= (x << 8)&((uint32_t)0x00000100);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_07_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000080)) >> 7);
}

static inline void rf_fsm_r2t_vector_07_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000080);
    localVal |= (x << 7)&((uint32_t)0x00000080);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_06_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000040)) >> 6);
}

static inline void rf_fsm_r2t_vector_06_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000040);
    localVal |= (x << 6)&((uint32_t)0x00000040);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_05_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000020)) >> 5);
}

static inline void rf_fsm_r2t_vector_05_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000020);
    localVal |= (x << 5)&((uint32_t)0x00000020);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_04_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000010)) >> 4);
}

static inline void rf_fsm_r2t_vector_04_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000010);
    localVal |= (x << 4)&((uint32_t)0x00000010);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_fsm_r2t_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_fsm_r2t_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_fsm_r2t_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001518,localVal);
}

static inline uint32_t rf_fsm_r2t_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_fsm_r2t_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001518);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001518,localVal);
}

#endif