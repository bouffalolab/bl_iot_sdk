/****************************************************************************
FILE NAME
    ble_tp_svc.c

DESCRIPTION
NOTES
*/
/****************************************************************************/

#include <errno.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>
#include <blog.h>

#include "bluetooth.h"
#include "conn.h"
#include "gatt.h"
#include "hci_core.h"
#include "uuid.h"
#include "ble_tp_svc.h"

static void ble_tp_connected(struct bt_conn *conn, u8_t err);
static void ble_tp_disconnected(struct bt_conn *conn, u8_t reason);

struct bt_conn *ble_tp_conn;
struct bt_gatt_exchange_params exchg_mtu;
TaskHandle_t ble_tp_task_h;
int tx_mtu_size = 20;

static struct bt_conn_cb ble_tp_conn_callbacks = {
    .connected  =   ble_tp_connected,
    .disconnected   =   ble_tp_disconnected,
};

/*************************************************************************
NAME
    ble_tp_tx_mtu_size
*/
static void ble_tp_tx_mtu_size(struct bt_conn *conn, u8_t err,
              struct bt_gatt_exchange_params *params)
{
       if(!err)
       {
                tx_mtu_size = bt_gatt_get_mtu(ble_tp_conn);
                printf("ble tp echange mtu size success, mtu size: %d\n", tx_mtu_size);
       }
       else
       {
                printf("ble tp echange mtu size failure, err: %d\n", err);
       }
}

/*************************************************************************
NAME
    ble_tp_connected
*/
static void ble_tp_connected(struct bt_conn *conn, u8_t err)
{
    int tx_octets = 0x00fb;
    int tx_time = 0x0848;
    int ret = -1;

    printf("%s\n",__func__);
    ble_tp_conn = conn;

    //set data length after connected.
    ret = bt_le_set_data_len(ble_tp_conn, tx_octets, tx_time);
    if(!ret)
    {
        printf("ble tp set data length success.\n");
    }
    else
    {
        printf("ble tp set data length failure, err: %d\n", ret);
    }

    //exchange mtu size after connected.
    exchg_mtu.func = ble_tp_tx_mtu_size;
    ret = bt_gatt_exchange_mtu(ble_tp_conn, &exchg_mtu);
    if (!ret) {
        printf("ble tp exchange mtu size pending.\n");
    } else {
        printf("ble tp exchange mtu size failure, err: %d\n", ret);
    }
}

/*************************************************************************
NAME
    ble_tp_disconnected
*/
static void ble_tp_disconnected(struct bt_conn *conn, u8_t reason)
{
    printf("%s\n",__func__);

    ble_tp_conn = NULL;
}

/*************************************************************************
NAME
    ble_tp_notify
*/

static void ble_tp_notify_task(void *pvParameters)
{
    int err = -1;
    char data[244] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

    while(1)
    {
        err = bt_gatt_notify(ble_tp_conn, get_attr(BT_CHAR_BLE_TP_TX_ATTR_VAL_INDEX), data, (tx_mtu_size - 3));
        blog_debug("bletp tx : %d\n", err);
    }
}

/*************************************************************************
NAME
    ble_tp_ccc_cfg_changed
*/
static void ble_tp_ccc_cfg_changed(const struct bt_gatt_attr *attr, u16_t value)
{
    if(value == BT_GATT_CCC_NOTIFY) {
        if(xTaskCreate(ble_tp_notify_task, (char*)"bletp", 256, NULL, 15, &ble_tp_task_h) == pdPASS)
        {
                printf("Create throughput tx task success .\n");
        }
        else
        {
                printf("Create throughput tx taskfail .\n");
        }
    } else {
        printf("Delete throughput tx task .\n");
        vTaskDelete(ble_tp_task_h);
    }

}

/*************************************************************************
NAME
    ble_tp_recv
*/
static int ble_tp_recv(struct bt_conn *conn,
              const struct bt_gatt_attr *attr, const void *buf,
              u16_t len, u16_t offset, u8_t flags)
{
    blog_debug("bletp rx\n");
    return 0;
}

/*************************************************************************
*  DEFINE : attrs
*/
static struct bt_gatt_attr attrs[]= {
    BT_GATT_PRIMARY_SERVICE(BT_UUID_SVC_BLE_TP),

    BT_GATT_CHARACTERISTIC(BT_UUID_CHAR_BLE_TP_TX,
                            BT_GATT_CHRC_NOTIFY,
                            BT_GATT_PERM_READ,
                            NULL,
                            NULL,
                            NULL),

    BT_GATT_CCC(ble_tp_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

    BT_GATT_CHARACTERISTIC(BT_UUID_CHAR_BLE_TP_RX,
                            BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                            BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                            NULL,
                            ble_tp_recv,
                            NULL)
};

/*************************************************************************
NAME
    get_attr
*/
struct bt_gatt_attr *get_attr(u8_t index)
{
    return &attrs[index];
}


struct bt_gatt_service ble_tp_server = BT_GATT_SERVICE(attrs);


/*************************************************************************
NAME
    ble_tp_init
*/
void ble_tp_init()
{
    bt_conn_cb_register(&ble_tp_conn_callbacks);
    bt_gatt_service_register(&ble_tp_server);
}



