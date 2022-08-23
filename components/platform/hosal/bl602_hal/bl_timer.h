#ifndef __BL_TIMER_H__
#define __BL_TIMER_H__
#include <stdint.h>
uint32_t bl_timer_now_us(void);
void bl_timer_delay_us(uint32_t us);
uint64_t bl_timer_now_us64(void);
#endif
