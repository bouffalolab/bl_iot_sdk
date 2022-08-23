#ifndef __HAL_HWTIMER_H__
#define __HAL_HWTIMER_H__

#include <stdint.h>
#include <utils_list.h>

typedef void (*hw_t)(void);
typedef struct hw_timer {
    utils_dlist_t dlist_item;
    int repeat;
    hw_t handler;
    uint32_t triggle_time;
    uint32_t calc_time; 
} hw_timer_t;

int hal_hwtimer_init(void);
hw_timer_t *hal_hwtimer_create(uint32_t period, hw_t handler, int repeat);
int hal_hwtimer_delete(hw_timer_t *pstnode);
int hal_hwtimer_change_period(hw_timer_t *pstnode, uint32_t period);

#endif
