#ifndef _____REG_ACCESS_H
#define _____REG_ACCESS_H
#include "co_utils.h"

/// Macro to read a platform register
#define REG_PL_RD(addr)              (*(volatile uint32_t *)(HW2CPU(addr)))

/// Macro to write a platform register
#define REG_PL_WR(addr, value)       (*(volatile uint32_t *)(HW2CPU(addr))) = (value)

#endif
