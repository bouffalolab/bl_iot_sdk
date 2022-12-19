#ifndef _PHY_DBG_H_
#define _PHY_DBG_H_

#ifdef CFG_SDIO_WIFI
#if CFG_DBG
#include "dbg.h"
#define phy_dbg(fmt, ...)   dbg_test_print(fmt, ## __VA_ARGS__)
#warning "[PHY_DBG] CFG_SDIO_WIFI defined!!!"
#else
#define phy_dbg(...)
#endif
#else
#define phy_dbg(...)
#endif

#endif
