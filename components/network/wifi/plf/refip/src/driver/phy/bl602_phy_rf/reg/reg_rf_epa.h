#ifndef _REG_RF_EPA_H_
#define _REG_RF_EPA_H_

#include "co_int.h"
#include "arch.h"
#include "_reg_access.h"

static inline uint32_t rf_epa_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001400);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_epa_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001400);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001400,localVal);
}

static inline uint32_t rf_epa_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001400);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_epa_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001400);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001400,localVal);
}

static inline uint32_t rf_epa_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001400);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_epa_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001400);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001400,localVal);
}

static inline uint32_t rf_epa_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001400);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_epa_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001400);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001400,localVal);
}

static inline uint32_t rf_epa_rx2on_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001404);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_epa_rx2on_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001404);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001404,localVal);
}

static inline uint32_t rf_epa_rx2on_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001404);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_epa_rx2on_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001404);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001404,localVal);
}

static inline uint32_t rf_epa_rx2on_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001404);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_epa_rx2on_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001404);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001404,localVal);
}

static inline uint32_t rf_epa_rx2on_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001404);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_epa_rx2on_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001404);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001404,localVal);
}

static inline uint32_t rf_epa_rxon_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001408);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_epa_rxon_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001408);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001408,localVal);
}

static inline uint32_t rf_epa_rxon_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001408);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_epa_rxon_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001408);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001408,localVal);
}

static inline uint32_t rf_epa_rxon_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001408);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_epa_rxon_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001408);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001408,localVal);
}

static inline uint32_t rf_epa_rxon_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001408);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_epa_rxon_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001408);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001408,localVal);
}

static inline uint32_t rf_epa_tx2on_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000140c);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_epa_tx2on_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000140c);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x4000140c,localVal);
}

static inline uint32_t rf_epa_tx2on_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000140c);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_epa_tx2on_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000140c);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x4000140c,localVal);
}

static inline uint32_t rf_epa_tx2on_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000140c);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_epa_tx2on_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000140c);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x4000140c,localVal);
}

static inline uint32_t rf_epa_tx2on_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x4000140c);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_epa_tx2on_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x4000140c);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x4000140c,localVal);
}

static inline uint32_t rf_epa_tx2paon_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001410);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_epa_tx2paon_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001410);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001410,localVal);
}

static inline uint32_t rf_epa_tx2paon_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001410);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_epa_tx2paon_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001410);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001410,localVal);
}

static inline uint32_t rf_epa_tx2paon_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001410);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_epa_tx2paon_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001410);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001410,localVal);
}

static inline uint32_t rf_epa_tx2paon_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001410);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_epa_tx2paon_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001410);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001410,localVal);
}

static inline uint32_t rf_epa_txpaon_vector_03_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001414);
    return ((localVal & ((uint32_t)0x00000008)) >> 3);
}

static inline void rf_epa_txpaon_vector_03_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001414);
    localVal &= ~((uint32_t)0x00000008);
    localVal |= (x << 3)&((uint32_t)0x00000008);
    REG_PL_WR(0x40001414,localVal);
}

static inline uint32_t rf_epa_txpaon_vector_02_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001414);
    return ((localVal & ((uint32_t)0x00000004)) >> 2);
}

static inline void rf_epa_txpaon_vector_02_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001414);
    localVal &= ~((uint32_t)0x00000004);
    localVal |= (x << 2)&((uint32_t)0x00000004);
    REG_PL_WR(0x40001414,localVal);
}

static inline uint32_t rf_epa_txpaon_vector_01_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001414);
    return ((localVal & ((uint32_t)0x00000002)) >> 1);
}

static inline void rf_epa_txpaon_vector_01_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001414);
    localVal &= ~((uint32_t)0x00000002);
    localVal |= (x << 1)&((uint32_t)0x00000002);
    REG_PL_WR(0x40001414,localVal);
}

static inline uint32_t rf_epa_txpaon_vector_00_getf(void)
{
    uint32_t localVal = REG_PL_RD(0x40001414);
    return ((localVal & ((uint32_t)0x00000001)) >> 0);
}

static inline void rf_epa_txpaon_vector_00_setf(uint32_t x)
{
    uint32_t localVal = REG_PL_RD(0x40001414);
    localVal &= ~((uint32_t)0x00000001);
    localVal |= (x << 0)&((uint32_t)0x00000001);
    REG_PL_WR(0x40001414,localVal);
}

#endif