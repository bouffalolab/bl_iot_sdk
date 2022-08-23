#if defined(CONFIG_ZIGBEE_PROV) 
#include "blsync_ble_app.h"
#include <FreeRTOS.h>
#include <task.h>
#include "blsync_ble.h"
#include "bluetooth.h"
#include "ble_cli_cmds.h"
#include "hci_driver.h"
#include "ble_lib_api.h"

static bl_ble_sync_t *gp_index = NULL;

static void zb_setlinkkey(uint8_t*linkkey){

    printf("zb link key =");
    for(int i=0;i<16;i++){

        printf("0x%x ",linkkey[i]);
    }
    printf("\n");

}
static void zb_reset(void){

     printf("%s\n",__func__);
     void zb_reset(void);
}

static struct blesync_zb_func zb_func = {
    .zb_get_installcode = NULL,
    .zb_join_network = NULL,
    .zb_setlinkkey = zb_setlinkkey,
    .zb_setpanid = NULL,
    .zb_reset = zb_reset,
};

static void blesync_complete_cb (void *p_arg)
{
    bl_ble_sync_t *p_index = (bl_ble_sync_t *)p_arg;
    bl_blezb_sync_stop(p_index);
    vPortFree(p_index);
}

void blsync_ble_start (void)
{
    if (gp_index != NULL) {
        printf("blsync already started\r\n");
        return;
    }
#ifdef CONFIG_BT_STACK_CLI 
    ble_cli_register();
#endif /* CONFIG_BT_STACK_CLI */
    gp_index = pvPortMalloc(sizeof(bl_ble_sync_t));
    if (gp_index == NULL) {
        return;
    }

    bl_blezb_sync_start(gp_index,
                      &zb_func,
                      blesync_complete_cb,
                      (void *)gp_index);



}

void blsync_ble_stop (void)
{
    bl_blezb_sync_stop(gp_index);
    vPortFree(gp_index);
    gp_index = NULL;
}

#endif