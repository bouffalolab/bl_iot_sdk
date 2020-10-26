#ifndef __OAD_SERVICE_H__
#define __OAD_SERVICE_H__

#include "types.h"
#include "gatt.h"

typedef void (*oad_upper_recv_cb)(struct bt_conn *conn, const u8_t *data, u16_t len);
void bt_oad_register_callback(oad_upper_recv_cb cb);
void bt_oad_service_enable(void);
void bt_oad_servkce_disable(void);
void bt_oad_notify(struct bt_conn *conn, const void *data, u16_t len);
#endif //__OAD_SERVICE_H__