#if defined(CFG_BLE_ENABLE)
#include <FreeRTOS.h>
#include <task.h>

#include "bluetooth.h"
#include "ble_cli_cmds.h"

#include "hci_driver.h"
#include "ble_lib_api.h"

#if defined(CONFIG_BLE_TP_SERVER)
#include "ble_tp_svc.h"
#endif

void bt_enable_cb(int err)
{
    if (!err) {     
#ifdef CONFIG_BT_STACK_CLI 
        ble_cli_register();
#endif /* CONFIG_BT_STACK_CLI */

#if defined(CONFIG_BLE_TP_SERVER)
        ble_tp_init();
#endif
        
    }
}

void ble_stack_start(void)
{
     // Initialize BLE controller
    ble_controller_init(configMAX_PRIORITIES - 1);
    // Initialize BLE Host stack
    hci_driver_init();
    bt_enable(bt_enable_cb);
}
#endif
