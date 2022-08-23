#ifndef __BL_WDT_H__
#define __BL_WDT_H__
int bl_wdt_init(int ms);
void bl_wdt_feed(void);
void bl_wdt_disable(void);
int bl_wdt_restore(void);  // restore wdt e.g. after timer reset
#endif
