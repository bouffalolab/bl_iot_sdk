#include "byteorder.h"
#include "oad_service.h"
#include "oad.h"
 
oad_upper_recv_cb upper_recv_cb;

static int oad_recv(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr, const void *buf,
			  u16_t len, u16_t offset, u8_t flags)
{
    (upper_recv_cb)(conn, buf, len);
    return 0;
}

static ssize_t oad_ccc_write(struct bt_conn *conn,
			       const struct bt_gatt_attr *attr,
			       const void *buf, u16_t len,
			       u16_t offset, u8_t flags)
{
    uint16_t *value = attr->user_data;
    
    if(len != sizeof(*value)){
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    *value = sys_get_le16(buf);

    return len;
}

static ssize_t oad_ccc_read(struct bt_conn *conn,
			      const struct bt_gatt_attr *attr,
			      void *buf, u16_t len, u16_t offset)
{
    u16_t *value = attr->user_data;

    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(*value));
}

static struct bt_gatt_attr oad_attrs[] = {
    BT_GATT_PRIMARY_SERVICE(BT_UUID_OAD),
    BT_GATT_CHARACTERISTIC(BT_UUID_OAD_DATA_IN,
            BT_GATT_CHRC_WRITE_WITHOUT_RESP,
            BT_GATT_PERM_WRITE, NULL, oad_recv, NULL),
    BT_GATT_CHARACTERISTIC(BT_UUID_OAD_DATA_OUT,
            BT_GATT_CHRC_NOTIFY,BT_GATT_PERM_NONE,
            NULL, NULL, NULL),
    BT_GATT_DESCRIPTOR(BT_UUID_GATT_CCC, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                       oad_ccc_read, oad_ccc_write, 0),
};

static struct bt_gatt_service oad_svc = BT_GATT_SERVICE(oad_attrs);

void bt_oad_notify(struct bt_conn *conn, const void *data, u16_t len)  
{
    bt_gatt_notify(conn, &oad_attrs[2], data, len);
}

void bt_oad_register_callback(oad_upper_recv_cb cb)
{
    upper_recv_cb = cb;
}

void bt_oad_service_enable(void)
{
    bt_gatt_service_register(&oad_svc);
}

void bt_oad_service_disable(void)
{
    bt_gatt_service_unregister(&oad_svc);
}
