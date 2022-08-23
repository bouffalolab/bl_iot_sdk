#ifndef HOSAL_TIMER_H
#define HOSAL_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hal_timer TIMER
 *  timer hal API.
 *
 *  @{
 */

#include <stdint.h>

#define TIMER_RELOAD_PERIODIC 1 /**< timer reload automatic */
#define TIMER_RELOAD_ONCE     2 /**< timer reload once and need to reload manually */

typedef void (*hosal_timer_cb_t)(void *arg); /**< Define timer handle function type */

/**
 * Define timer config args 
 */
typedef struct {
    uint32_t          period;         /**< timer period, us */
    uint8_t           reload_mode;    /**< auto reload or not */
    hosal_timer_cb_t  cb;             /**< timer handle when expired */
    void              *arg;           /**< timer handle args */
} hosal_timer_config_t;

/** 
 * Define timer dev handle 
 */
typedef struct {
    int8_t                port;   /**< timer port */
    hosal_timer_config_t  config; /**< timer config */
    void                  *priv;   /**< priv data */
} hosal_timer_dev_t;

/**
 * init a hardware timer
 *
 * @param[in]  tim  timer device
 *
 * @return  
 *       - 0 : success 
 *       - other :error
 */
int hosal_timer_init(hosal_timer_dev_t *tim);

/**
 * start a hardware timer
 *
 * @param[in]  tim  timer device
 *
 * @return
 *       - 0 : success 
 *       - other : error
 */
int hosal_timer_start(hosal_timer_dev_t *tim);

/**
 * stop a hardware timer
 *
 * @param[in]  tim  timer device
 *
 * @return  none
 */
void hosal_timer_stop(hosal_timer_dev_t *tim);

/**
 * De-initialises an TIMER interface, Turns off an TIMER hardware interface
 *
 * @param[in]  tim  timer device
 *
 * @return  
 *       - 0 : success
 *       - other : error
 */
int hosal_timer_finalize(hosal_timer_dev_t *tim);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_TIMER_H */

