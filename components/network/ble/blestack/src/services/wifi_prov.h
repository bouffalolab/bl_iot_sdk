#ifndef _WIFI_PROV_H_
#define _WIFI_PROV_H_

#include "config.h"

//07af8aa0-9f1f-11ea-b294-02fcdc4e7412
#define BT_UUID_WIFI_PROV                BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x07af8aa0, 0x9f1f, 0x11ea, 0xb294, 0x02fcdc4e7412))
//07af8aa1-9f1f-11ea-b294-02fcdc4e7412
#define BT_UUID_WIFIPROV_WRITE     BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x07af8aa1, 0x9f1f, 0x11ea, 0xb294, 0x02fcdc4e7412))
//07af8aa2-9f1f-11ea-b294-02fcdc4e7412
#define BT_UUID_WIFIPROV_READ       BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x07af8aa2, 0x9f1f, 0x11ea, 0xb294, 0x02fcdc4e7412))

#define WIFIPROV_INVALID_SEQ    0xff
#define WIFIPROV_FRAME_TYPE_BITMASK  0x03
#define WIFIPROV_FRAME_TYPE_OFFSET   0x02
#define WIFIPROV_TYPE_CTRL_FRAME     0x00
#define WIFIPROV_TYPE_DATA_FRAME     0x01
#define WIFIPROV_FRAME_CTRL_ACK_BITMASK 0x08
#define WIFIPROV_FRAME_CTRL_NO_ACK      0x00
#define WIFIPROV_FRAME_CTRL_NEED_ACK    0x08
#define WIFIPROV_FRAME_ACK_DATA_LEN     0x01

struct conn_callback{
	void (*local_connect_remote_ap) (void);
	void (*local_disconnect_remote_ap) (void);
	void (*get_remote_ap_ssid)(void *args,size_t size); 
	void (*get_remote_ap_bssid)(void *args,size_t size); 
	void (*get_remote_password)(void *args,size_t size); 
}; 	

enum wifiprov_ctrlfrm_type{
    SUB_TYPE_CTRL_ACK = 0x00,
    SUB_TYPE_CTRL_CONN_AP = 0x03,
    SUB_TYPE_CTRL_DISCONN_AP
};

enum wifiprov_datafrm_type{
    SUB_TYPE_DATA_BSSID = 0x01,
    SUB_TYPE_DATA_SSID,
    SUB_TYPE_DATA_PASSWORD
};

#define WIFIPROV_FRAME_DATA_PYLD_OFFSET    4
struct wifiprov_data_format{
	u8_t type;   /*type : highest 2 bit ; subtype : lowest 6 bit;*/
	u8_t frame_control;  /* if 5th bit set "1" indicate fragmentation frame */
	u8_t sequence_number;
	u8_t len;
	u8_t *data;
};

void WifiProv_init(struct conn_callback *cb);
#endif 
