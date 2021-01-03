/****************************************************************************
FILE NAME
    ble_tp_svc.h

DESCRIPTION
NOTES
*/
/****************************************************************************/

#ifndef _BLE_TP_SVC_H_
#define _BLE_TP_SVC_H_

#include "config.h"

//07af27a6-9c22-11ea-9afe-02fcdc4e7412
#define BT_UUID_SVC_BLE_TP              BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x07af27a6, 0x9c22, 0x11ea, 0x9afe, 0x02fcdc4e7412))
//07af27a7-9c22-11ea-9afe-02fcdc4e7412
#define BT_UUID_CHAR_BLE_TP_TX      BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x07af27a7, 0x9c22, 0x11ea, 0x9afe, 0x02fcdc4e7412))
//07af27a8-9c22-11ea-9afe-02fcdc4e7412
#define BT_UUID_CHAR_BLE_TP_RX      BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x07af27a8, 0x9c22, 0x11ea, 0x9afe, 0x02fcdc4e7412))

//TX value handle offset 2
#define BT_CHAR_BLE_TP_TX_ATTR_VAL_INDEX    (2)
//RX value handle offset 5
#define BT_CHAR_BLE_TP_RX_ATTR_VAL_INDEX    (5)

void ble_tp_init();
struct bt_gatt_attr *get_attr(u8_t index);

#endif

