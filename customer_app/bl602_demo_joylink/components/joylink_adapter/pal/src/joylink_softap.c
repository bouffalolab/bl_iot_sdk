#include <stdio.h>
#include <string.h>
#include "joylink_string.h"
#include "joylink_extern.h"
#include "joylink_memory.h"
#include "joylink_softap.h"

#include <vfs.h>
#include <easyflash.h>
#include <wifi_mgmr_ext.h>

static int jl_port_softap_get_one_product_info(char *name, char *out)
{
    int fd;
    int read;
    int i;
    char filename[32];
    char buf[128];
    int ret = 0;

    strcpy(filename, "/romfs/");
    strcat(filename, name);
    if ((fd = aos_open(filename, 0)) < 0) {
        ret = -1;
        goto error;
    }
    if ((read = aos_read(fd, buf, 127)) <= 0) {
        ret = -2;
        goto clean;
    }
    for (i = 0; i < read; i++) {
        if (buf[i] == '\r' || buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
    buf[i] = '\0';
    strcpy(out, buf);

clean:
    aos_close(fd);
error:
    return ret;
}

/**
 * @brief:set wifi mode to AP mode.
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_enter_ap_mode(void)
{
    char ssid_name[32];
    wifi_interface_t wifi_interface;

    jl_port_softap_get_one_product_info("dev_soft_ssid", ssid_name);

    wifi_interface = wifi_mgmr_ap_enable();

    wifi_mgmr_ap_start(wifi_interface, ssid_name, 0, NULL, 1);
    return 0;
}


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
int32_t jl_softap_get_product_info(char *uuid, char *brand, char *cid, char *dev_soft_ssid)
{
    if (jl_port_softap_get_one_product_info("uuid", uuid)) {
        goto error;
    }
    if (jl_port_softap_get_one_product_info("brand", brand)) {
        goto error;
    }
    if (jl_port_softap_get_one_product_info("cid", cid)) {
        goto error;
    }
    if (jl_port_softap_get_one_product_info("dev_soft_ssid", dev_soft_ssid)) {
        goto error;
    }

    log_info("uuid %s, brand %s, cid %s, dev_soft_ssid %s\r\n", uuid, brand, cid, dev_soft_ssid);
    return 0;
error:
    log_error("CFG error\r\n");
    return -1;
}

/**
 * @brief:System is expected to connect wifi router with the in parameters.
 *
 * @param[in]: ssid of wifi router
 * @param[in]: passwd  of wifi router
 *
 * @returns:success 0, others failed
 */
int32_t jl_softap_connect_wifi_router(char *ssid, char *passwd)
{
    char pmk[66] = { 0 };
    wifi_interface_t wifi_interface;

    wifi_mgmr_psk_cal(
            passwd,
            ssid,
            strlen(ssid),
            pmk
    );
    log_info("Connecting to Router SSID %s, PWD %s, PMK %s", ssid, passwd, pmk);
    // step 1 save router info to flash
    ef_set_env(JL_EF_ROUTER_SSID_KEY, ssid);
    ef_set_env(JL_EF_ROUTER_PSWD_KEY, passwd);
    ef_set_env(JL_EF_ROUTER_PMK_KEY, pmk);
    ef_save_env();

    // step 2 close AP mode
    wifi_mgmr_ap_stop(NULL);

    // step 3 connect to the router
#ifdef JOYLINK_SDK_EXAMPLE_MWO
    jl_device_status = S_CONNECTING_AP;
#endif
    wifi_interface = wifi_mgmr_sta_enable();
    wifi_mgmr_sta_connect(wifi_interface, ssid, passwd, pmk, NULL, 0, 0);

    return 0;
}
