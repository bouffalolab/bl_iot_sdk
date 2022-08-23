#ifndef HAL_WDG_H
#define HAL_WDG_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_wdg WATCHDOG 
 *  HOSAL WATCHDOG API
 *
 *  @{
 */

#include <stdint.h>

/**
 * @brief wdg config struct
 *
 */
typedef struct {
    uint32_t timeout; /*!< Watchdag timeout in ms*/
} hosal_wdg_config_t;

/**
 * @brief wdg dev struct
 *
 */
typedef struct {
    uint8_t       port;   /**< wdg port */
    hosal_wdg_config_t  config; /**< wdg config */
    void         *priv;   /**< priv data */
} hosal_wdg_dev_t;

/**
 * @brief This function will initialize the on board CPU hardware watch dog
 *
 * @param[in]  wdg  the watch dog device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_wdg_init(hosal_wdg_dev_t *wdg);

/**
 * @brief Reload watchdog counter.
 *
 * @param[in]  wdg  the watch dog device
 */
void hosal_wdg_reload(hosal_wdg_dev_t *wdg);

/**
 * @brief This function performs any platform-specific cleanup needed for hardware watch dog.
 *
 * @param[in]  wdg  the watch dog device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_wdg_finalize(hosal_wdg_dev_t *wdg);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_WDG_H */

