/**
 ****************************************************************************************
 *
 * @file bl_wdt.c
 * Copyright (C) Bouffalo Lab 2016-2018
 *
 ****************************************************************************************
 */

#include <bl602_timer.h>
#include "bl_wdt.h"
#define MAX_MS_WDT (65535)

static void Timer_Watchdog_Case(int ms)
{
    WDT_Disable();
    WDT_Set_Clock(TIMER_CLKSRC_32K, 31);
    WDT_SetCompValue(1 * ms);

    WDT_ResetCounterValue();
    WDT_IntMask(WDT_INT, MASK);

    WDT_Enable();
}

void bl_wdt_feed(void)
{
    WDT_ResetCounterValue();
}

void bl_wdt_disable(void)
{
    WDT_Disable();
}

int bl_wdt_init(int ms)
{
    if (ms >= MAX_MS_WDT) {
        return -1;
    }
    Timer_Watchdog_Case(ms);
    return 0;
}
