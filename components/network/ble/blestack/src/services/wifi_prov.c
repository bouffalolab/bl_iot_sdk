/** @file
 *  @brief wifiprov  Service
 */
#include <errno.h>
#include <stdbool.h>
#include <zephyr/types.h>

#include "bluetooth.h"
#include "conn.h"
#include "gatt.h"
#include "uuid.h"
#include "wifi_prov.h"
#include "log.h"

u8_t local_seq_num = 0x00;
u8_t remote_seq_num = WIFIPROV_INVALID_SEQ;
static struct conn_callback *callback;
//static struct bt_gatt_ccc_cfg  wifiprov_ccc_cfg[BT_GATT_CCC_MAX] = {};
static ssize_t write_data(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
			       u16_t len, u16_t offset, u8_t flags);

static void wifiprov_ccc_cfg_changed(const struct bt_gatt_attr *attr,u16_t value)
{
	ARG_UNUSED(attr);
    BT_DBG("value 0x%02x", value);
}

static ssize_t read_data(struct bt_conn *conn,
			       const struct bt_gatt_attr *attr, void *buf,
			       u16_t len, u16_t offset)
{
    /*As we donot know what info remote wants to read currently, respond value 0 by default.
      This part will be implemented according to specific requirements.*/
	u8_t value = 0x00;
	return bt_gatt_attr_read(conn, attr, buf, len, offset, &value,sizeof(value));
}

static bool remote_need_ack(u8_t ack)
{
	return (ack & WIFIPROV_FRAME_CTRL_ACK_BITMASK) ? 1 : 0;
}

static struct bt_gatt_attr attrs[]= {
	BT_GATT_PRIMARY_SERVICE(BT_UUID_WIFI_PROV),
	BT_GATT_CHARACTERISTIC(BT_UUID_WIFIPROV_READ,
								BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
								BT_GATT_PERM_READ , 
								read_data, 
								NULL,
								NULL),
								
	BT_GATT_CCC(wifiprov_ccc_cfg_changed, BT_GATT_PERM_READ_AUTHEN | BT_GATT_PERM_WRITE_AUTHEN),

	BT_GATT_CHARACTERISTIC(BT_UUID_WIFIPROV_WRITE,
							   	BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
							   	BT_GATT_PERM_WRITE, 
							   	NULL,
							   	write_data,
								NULL),							
};

static ssize_t write_data(struct bt_conn *conn,
			       const struct bt_gatt_attr *attr, const void *buf,
			       u16_t len, u16_t offset, u8_t flags)
{
    struct wifiprov_data_format rcvd_frm;
    u8_t type, subtype;
    u8_t ack_buf[5];

    memcpy(&rcvd_frm, buf, WIFIPROV_FRAME_DATA_PYLD_OFFSET);
    type = rcvd_frm.type & WIFIPROV_FRAME_TYPE_BITMASK;
    subtype = rcvd_frm.type >> WIFIPROV_FRAME_TYPE_OFFSET;

    /*In future, segmented frame will be implemented, below if condition need to be changed if segemented frame
      have the same seq num*/
    if(remote_seq_num != WIFIPROV_INVALID_SEQ && rcvd_frm.sequence_number <= remote_seq_num)
    {
        BT_ERR("Old sequence number,reject!");
        return len;
    }
    else
        remote_seq_num = rcvd_frm.sequence_number;
    
    if(rcvd_frm.len > 0)
        rcvd_frm.data = (u8_t *)(buf + WIFIPROV_FRAME_DATA_PYLD_OFFSET);

    if(remote_need_ack(rcvd_frm.frame_control)){
        ack_buf[0] =  WIFIPROV_TYPE_CTRL_FRAME|(SUB_TYPE_CTRL_ACK << WIFIPROV_FRAME_TYPE_OFFSET);
		ack_buf[1] =  WIFIPROV_FRAME_CTRL_NO_ACK;
		ack_buf[2] =  local_seq_num++;
		ack_buf[3] =  WIFIPROV_FRAME_ACK_DATA_LEN;
		ack_buf[4] =  rcvd_frm.sequence_number;	

		bt_gatt_notify(conn,&attrs[2],ack_buf,5);
    }
        
    if(type == WIFIPROV_TYPE_CTRL_FRAME){
        switch(subtype){
        case SUB_TYPE_CTRL_ACK:
            
            break;
        case SUB_TYPE_CTRL_CONN_AP:
            if(callback && callback->local_connect_remote_ap)
				callback->local_connect_remote_ap();
            break;

        case SUB_TYPE_CTRL_DISCONN_AP:
            if(callback && callback->local_disconnect_remote_ap)
				callback->local_disconnect_remote_ap();
            break;
            
        default:
            BT_ERR("Invalid wifi prov frame type");
        }
    }else if(type == WIFIPROV_TYPE_DATA_FRAME){
        switch(subtype){
        case SUB_TYPE_DATA_BSSID:
            if(callback && callback->get_remote_ap_bssid)
				callback->get_remote_ap_bssid(rcvd_frm.data, rcvd_frm.len);
            break;
        case SUB_TYPE_DATA_SSID:
            if(callback && callback->get_remote_ap_ssid)
				callback->get_remote_ap_ssid(rcvd_frm.data, rcvd_frm.len);
            break;

        case SUB_TYPE_DATA_PASSWORD:
            if(callback && callback->get_remote_password)
				callback->get_remote_password(rcvd_frm.data, rcvd_frm.len);
            break;
            
        default:
            BT_ERR("Invalid wifi prov frame type");
        }    
    }else{
        BT_ERR("Invalid wifi prov frame type");
    }
	
	return len;
}

struct bt_gatt_service wifiprov_server = BT_GATT_SERVICE(attrs);

void WifiProv_init(struct conn_callback *cb)
{
    callback = cb;
	bt_gatt_service_register(&wifiprov_server); 
}
