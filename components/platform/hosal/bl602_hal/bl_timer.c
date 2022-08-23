#include "bl_timer.h"
#include "bl_irq.h"
#include <bl602_timer.h>

#include <FreeRTOS.h>
#include <task.h>

#define MTIMER_TICKS_PER_US     (10)
static inline uint64_t timer_us_now()
{
    uint32_t tick_low, tick_high, tick_tmp;
    uint64_t tick64;

    do {
        tick_high = *(volatile uint32_t*)0x0200BFFC;
        tick_low = *(volatile uint32_t*)0x0200BFF8;

        tick_tmp = *(volatile uint32_t*)0x0200BFFC;//make sure no overflow
    } while (tick_high != tick_tmp);

    tick64 = (((uint64_t)tick_high) << 32) | tick_low;
    return tick64;
}

uint32_t bl_timer_now_us(void)
{
    return timer_us_now() / MTIMER_TICKS_PER_US;
}

uint64_t bl_timer_now_us64(void)
{
    return timer_us_now() / MTIMER_TICKS_PER_US;
}

void bl_timer_delay_us(uint32_t us)
{
    uint32_t tick_now, tick_start;
    int ticks, diff;

    tick_start = *(volatile uint32_t*)0x0200BFF8;
    ticks = us * MTIMER_TICKS_PER_US;

    do {
        tick_now = *(volatile uint32_t*)0x0200BFF8;
        diff = (int32_t)tick_now - (int32_t)tick_start;
    } while (diff < ticks);
}

static BL_Err_Type Timer_INT_Case(TIMER_CFG_Type *timerCfg)
{
    /* Disable all interrupt */
    TIMER_IntMask(timerCfg->timerCh,TIMER_INT_ALL, MASK);

    /* Disable timer before config */
    TIMER_Disable(timerCfg->timerCh);

    /* Timer init with default configuration */
    TIMER_Init(timerCfg);

    /* Clear interrupt status*/
    TIMER_ClearIntStatus(timerCfg->timerCh,TIMER_COMP_ID_0);
    TIMER_ClearIntStatus(timerCfg->timerCh,TIMER_COMP_ID_1);
    TIMER_ClearIntStatus(timerCfg->timerCh,TIMER_COMP_ID_2);

    /* Enable timer match interrupt */
    TIMER_IntMask(timerCfg->timerCh, TIMER_INT_COMP_0, UNMASK);
    TIMER_IntMask(timerCfg->timerCh, TIMER_INT_COMP_1, MASK);
    TIMER_IntMask(timerCfg->timerCh, TIMER_INT_COMP_2, MASK);

    /* Enable timer */
    TIMER_Enable(timerCfg->timerCh);

    return SUCCESS;
}

static void int_timer_cb(void)
{
    TIMER_ClearIntStatus(TIMER_CH1, TIMER_COMP_ID_0);
    if (xTaskIncrementTick()) {
        vTaskSwitchContext();
    }
}

int bl_timer_tick_enable(void)
{
    TIMER_CFG_Type timerCh1Cfg = 
    {
        TIMER_CH1,                           /* timer channel 1 */
        TIMER_CLKSRC_FCLK,                   /* timer clock source:bus clock */
        TIMER_PRELOAD_TRIG_COMP0,            /* reaload on comaparator 0  */
        TIMER_COUNT_PRELOAD,                 /* preload when match occur */
        15,                                 /* Timer clock divison value */
        //10 * 1000 * 1000 * 2,                /* match value 0  */
        10 * 1 * 1000 * 1 - 2,                /* match value 0  */
        360000,                              /* match value 1 */
        390000,                              /* match value 2 */
        0,                                   /* preload value */
    };

    Timer_INT_Case(&timerCh1Cfg);

    bl_irq_enable(TIMER_CH1_IRQn);
    bl_irq_register(TIMER_CH1_IRQn, int_timer_cb);

    return 0;
}
