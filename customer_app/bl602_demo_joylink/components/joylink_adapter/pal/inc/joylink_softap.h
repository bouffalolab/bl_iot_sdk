#ifndef _JOYLINK_SOFTAP_H_
#define _JOYLINK_SOFTAP_H_

#include "joylink_stdint.h"

#define JL_EF_ROUTER_SSID_KEY "JL_ROTUER_SSID"
#define JL_EF_ROUTER_PSWD_KEY "JL_ROUTER_PSWD"
#define JL_EF_ROUTER_PMK_KEY  "JL_ROUTER_PMK"

/**
 * @brief:set wifi mode to AP mode.
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_enter_ap_mode(void);

/**
 * @brief:set softap config stop.
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_config_stop(void);

/**
 * @brief:System is expected to get product information that user regiested in Cloud platform.
 *
 * @param[out]: UUID , max length: 8
 * @param[out]: BRAND, max length: 8 
 * @param[out]: CID,   max length: 8
 * @param[out]: dev_soft_ssid max length: 32
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_get_product_info(char *uuid, char *brand, char *cid, char *dev_soft_ssid);

/**
 * @brief:System is expected to connect wifi router with the in parameters.
 *
 * @param[in]: ssid of wifi router
 * @param[in]: passwd  of wifi router
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_connect_wifi_router(char *ssid, char *passwd);

#endif
