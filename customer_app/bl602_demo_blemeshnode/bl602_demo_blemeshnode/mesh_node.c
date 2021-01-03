#include <stdlib.h>
#include "conn.h"
#include "gatt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cli.h"
#include "include/mesh.h"
#include "errno.h"
#include "bluetooth.h"
#include "ble_lib_api.h"
#include "mesh.h"
#include "net.h"
#include "transport.h"
#include "foundation.h"
#include "mesh_settings.h"
#include "adv.h"
#include "beacon.h"
#include "hci_core.h"
#include "log.h"
#include "mesh_node.h"
#include "hci_driver.h"
#include "gen_srv.h"
#include <bl_gpio.h>
#if defined(CONFIG_BT_SETTINGS)
#include "easyflash.h"
#endif
#include <../../../components/network/ble/blestack/src/include/bluetooth/crypto.h>
#include "local_operation.h"
#define CUR_FAULTS_MAX 4

static bool blemesh_inited = false;

#if defined(CONFIG_BT_MESH_LOW_POWER)
//below value is for Tmall Genie
static u8_t dev_uuid[16] = {0xA8,0x01,0x71,0x5e,0x1c,0x00,0x00,0xe4,0x46,0x46,0x63,0xa7,0xf8,0x02,0x00,0x00};
static u8_t auth_value[16] = {0x78,0x8A,0xE3,0xEE,0x0F,0x2A,0x7E,0xFA,0xD3,0x67,0x35,0x81,0x41,0xFE,0x1B,0x06};
#else
static u8_t dev_uuid[16] = {0xA8,0x01,0x71,0xe0,0x1a,0x00,0x00,0x0f,0x7e,0x35,0x63,0xa7,0xf8,0x02,0x00,0x00};
static u8_t auth_value[16] = {0x7f,0x80,0x1a,0xf4,0xa0,0x8c,0x50,0x39,0xae,0x7d,0x7b,0x44,0xa0,0x92,0xd9,0xc2};
#endif

static bt_mesh_input_action_t input_act;
static u8_t input_size;
static u8_t cur_faults[CUR_FAULTS_MAX];
static u8_t reg_faults[CUR_FAULTS_MAX * 2];

static struct {
	u16_t local;
	u16_t dst;
	u16_t net_idx;
	u16_t app_idx;
} net = {
	.local = BT_MESH_ADDR_UNASSIGNED,
	.dst = BT_MESH_ADDR_UNASSIGNED,
};

#if defined(BL602) 
#define vOutputString(...)  printf(__VA_ARGS__)
#else
#define vOutputString(...)  bl_print(SYSTEM_UART_ID, PRINT_MODULE_CLI, __VA_ARGS__)
#endif
static const char *bearer2str(bt_mesh_prov_bearer_t bearer);
static void prov_reset(void);
static void gen_dev_uuid(void);
static void link_open(bt_mesh_prov_bearer_t bearer);
static void link_close(bt_mesh_prov_bearer_t bearer);
static int output_number(bt_mesh_output_action_t action, u32_t number);

static int output_string(const char *str);
static void prov_input_complete(void);
static void prov_complete(u16_t net_idx, u16_t addr);
static void prov_reset(void);
static int input(bt_mesh_input_action_t act, u8_t size);
static void get_faults(u8_t *faults, u8_t faults_size, u8_t *dst, u8_t *count);
static void health_current_status(struct bt_mesh_health_cli *cli, u16_t addr,
				  u8_t test_id, u16_t cid, u8_t *faults, size_t fault_count);
static int fault_get_cur(struct bt_mesh_model *model, u8_t *test_id,
			 u16_t *company_id, u8_t *faults, u8_t *fault_count);
static int fault_get_reg(struct bt_mesh_model *model, u16_t cid,
			 u8_t *test_id, u8_t *faults, u8_t *fault_count);
static int fault_clear(struct bt_mesh_model *model, uint16_t cid);
static int fault_test(struct bt_mesh_model *model, uint8_t test_id, uint16_t cid);
static void attn_on(struct bt_mesh_model *model);
static void attn_off(struct bt_mesh_model *model);

static void blemesh_init(void);

static void blemesh_pb_gatt(void);
static void blemesh_pb_adv(void);

static struct bt_mesh_prov prov = {
	.uuid = dev_uuid,
    .oob_info = 0,
	.link_open = link_open,
	.link_close = link_close,
	.complete = prov_complete,
	.reset = prov_reset,
	.static_val = auth_value,
	.static_val_len = 16,
	.output_size = 6,
	.output_actions = (BT_MESH_DISPLAY_NUMBER | BT_MESH_DISPLAY_STRING),
	.output_number = output_number,
	.output_string = output_string,
	.input_size = 6,
	.input_actions = (BT_MESH_ENTER_NUMBER | BT_MESH_ENTER_STRING),
	.input = input,
	.input_complete = prov_input_complete,
};

static const struct bt_mesh_health_srv_cb health_srv_cb = {
	.fault_get_cur = fault_get_cur,
	.fault_get_reg = fault_get_reg,
	.fault_clear = fault_clear,
	.fault_test = fault_test,
	.attn_on = attn_on,
	.attn_off = attn_off,
};

static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};

static struct bt_mesh_health_cli health_cli = {
	.current_status = health_current_status,
};

BT_MESH_HEALTH_PUB_DEFINE(health_pub, CUR_FAULTS_MAX);

static struct bt_mesh_cfg_cli cfg_cli = {
};

static struct bt_mesh_cfg_srv cfg_srv = {
	.relay = BT_MESH_RELAY_ENABLED,
	.beacon = BT_MESH_BEACON_ENABLED,//BT_MESH_BEACON_DISABLED,
#if defined(CONFIG_BT_MESH_FRIEND)
	.frnd = BT_MESH_FRIEND_DISABLED,
#else
	.frnd = BT_MESH_FRIEND_NOT_SUPPORTED,
#endif
#if defined(CONFIG_BT_MESH_GATT_PROXY)
	.gatt_proxy = BT_MESH_GATT_PROXY_ENABLED,
#else
	.gatt_proxy = BT_MESH_GATT_PROXY_NOT_SUPPORTED,
#endif

	.default_ttl = 7,

	/* 6 transmissions with 20ms interval */
	.net_transmit = BT_MESH_TRANSMIT(5, 20),
	/* 3 transmissions with 20ms interval */
	.relay_retransmit = BT_MESH_TRANSMIT(2, 20),
};


struct bt_mesh_gen_onoff_srv onoff_srv = {
};


static void borad_rgb_init(void)
{
    
    bl_gpio_enable_output(LED_RED_PIN,1,0);
    bl_gpio_enable_output(LED_GREEN_PIN,1,0);
    bl_gpio_enable_output(LED_BLUE_PIN,1,0);
    bl_gpio_output_set(LED_RED_PIN,1);
    bl_gpio_output_set(LED_GREEN_PIN,1);
    bl_gpio_output_set(LED_BLUE_PIN,1);

}
static void borad_rgb_off(void)
{

    bl_gpio_output_set(LED_RED_PIN,1);
    bl_gpio_output_set(LED_GREEN_PIN,1);
    bl_gpio_output_set(LED_BLUE_PIN,1);

}
void model_gen_cb(uint8_t value)
{
	printf("onff value=%d \n",value);
	if(value==1){
		 bl_gpio_output_set(LED_RED_PIN,0);
	}else if(value==0){

		borad_rgb_off();
	}
}
static struct bt_mesh_model sig_models[] = {
	BT_MESH_MODEL_CFG_SRV(&cfg_srv),
	BT_MESH_MODEL_CFG_CLI(&cfg_cli),
	BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub),
	BT_MESH_MODEL_HEALTH_CLI(&health_cli),
	BT_MESH_MODEL_GEN_ONOFF(&onoff_srv),
};

static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(0, sig_models, BT_MESH_MODEL_NONE),
};

static const struct bt_mesh_comp comp = {
	.cid = BL_COMP_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};

/* Read string from uart */
static void read_str(char* str, u8_t size)
{
	extern int cli_getchar(char *inbuf);
	char* str_s = str;
	while(str - str_s <= size){
		while(!cli_getchar(str));
		if(*str == '\r' || *str == '\n'){
			*str = 0;
			break;
		}
		vOutputString("%c", *str);
		str++;
	}
}

static void blemesh_init(void)
{
    int err;

    if(blemesh_inited){
        vOutputString("Has initialized \r\n");
        return;
    }

    // auto generate device uuid
    gen_dev_uuid();

    err = bt_mesh_init(&prov, &comp);
    if(err){
        vOutputString("Failed to init \r\n");
        return;
    }

    blemesh_inited = true;
    vOutputString("Init successfully \r\n");

    if (IS_ENABLED(CONFIG_BT_SETTINGS)) {
        mesh_set();
        mesh_commit();
    }

    if (bt_mesh_is_provisioned()) {
		vOutputString("Mesh network restored from flash\r\n");
	} else {
		vOutputString("Use pb-adv or pb-gatt to enable advertising\r\n");
	}


}
static const u16_t net_idx = 0x0000;
static const u16_t app_idx = 0x0000;


static const char *bearer2str(bt_mesh_prov_bearer_t bearer)
{
	switch (bearer) {
	case BT_MESH_PROV_ADV:
		return "PB-ADV";
	case BT_MESH_PROV_GATT:
		return "PB-GATT";
	default:
		return "unknown";
	}
}

#if defined(CONFIG_BT_MESH_PROV)
static void blemesh_pb_gatt(void)
{
    int err;
	err = bt_mesh_prov_enable(BT_MESH_PROV_GATT);
	if (err) {
		vOutputString("blemesh_pb_gatt Failed to enable\n");
	} else {
		vOutputString("blemesh_pb_gatt enable\n");
	}
}
static void blemesh_pb_adv(void)
{
    int err;

	err = bt_mesh_prov_enable(BT_MESH_PROV_ADV);
	if (err) {
		vOutputString("blemesh_pb_adv Failed to enable\n");
	} else {
		vOutputString("blemesh_pb_adv enable\n");
	}
}
#endif



static void link_open(bt_mesh_prov_bearer_t bearer)
{
	vOutputString("Provisioning link opened on %s\r\n", bearer2str(bearer));
}

static void link_close(bt_mesh_prov_bearer_t bearer)
{
	vOutputString("Provisioning link closed on %s\r\n", bearer2str(bearer));
}

static int output_number(bt_mesh_output_action_t action, u32_t number)
{
	vOutputString("OOB Number: %u\r\n", number);
	return 0;
}

static int output_string(const char *str)
{
	vOutputString("OOB String: %s\r\n", str);
	return 0;
}

static void prov_input_complete(void)
{
	vOutputString("Input complete\r\n");
}

static void prov_complete(u16_t net_idx, u16_t addr)
{
	vOutputString("Local node provisioned, net_idx 0x%04x address 0x%04x\r\n", net_idx, addr);
	net.net_idx = net_idx,
	net.local = addr;
	net.dst = addr;
}

static void prov_reset(void)
{
	vOutputString("The local node has been reset and needs reprovisioning\r\n");
	mesh_node_reset();
}

static void gen_dev_uuid(void)
{
//device uuid: 07af0000-1111-2222-3333-mac address(6 bytes)

	bt_addr_le_t adv_addr;
	bt_get_local_public_address(&adv_addr);
	u8_t uuid[16] = {0x07,0xaf,0x00,0x00,0x11,0x11,0x22,0x22,0x33,0x33,
	                        adv_addr.a.val[5],
	                        adv_addr.a.val[4],
	                        adv_addr.a.val[3],
	                        adv_addr.a.val[2],
	                        adv_addr.a.val[1],
	                        adv_addr.a.val[0]};
	memcpy(dev_uuid, uuid, 16);

}

static int input(bt_mesh_input_action_t act, u8_t size)
{
	char str[20];
	switch (act) {
	case BT_MESH_ENTER_NUMBER:{
		vOutputString("Enter a number (max %u digits) with: input-num <num>:", size);
		read_str(str, sizeof(str)-1);
		u32_t num = strtoul(str, NULL, 10);
		vOutputString("Recved num[%d]\n", num);
		int err = bt_mesh_input_number(num);
		if (err) {
			vOutputString("Numeric input failed (err %d)\r\n", err);
		}
	}break;
	case BT_MESH_ENTER_STRING:{
		vOutputString("Enter a string (max %u chars) with: input-str <str>\r\n", size);
		read_str(str, sizeof(str)-1);
		vOutputString("Recved string[%d]\n", str);
		int err = bt_mesh_input_string(str);
		if (err) {
			vOutputString("String input failed (err %d)\r\n", err);
		}
	}break;
	default:
		vOutputString("Unknown input action %u (size %u) requested!\r\n", act, size);
		return -EINVAL;
	}

	input_act = act;
	input_size = size;
	return 0;
}

static void blemesh_reset(void)
{
	if(!blemesh_inited){
		vOutputString("blemesh not init\n");
		return;
	}
	bt_mesh_reset();
	vOutputString("Local node reset complete\r\n");

}

static void get_faults(u8_t *faults, u8_t faults_size, u8_t *dst, u8_t *count)
{
	u8_t i, limit = *count;

	for (i = 0U, *count = 0U; i < faults_size && *count < limit; i++) {
		if (faults[i]) {
			*dst++ = faults[i];
			(*count)++;
		}
	}
}

static void show_faults(u8_t test_id, u16_t cid, u8_t *faults, size_t fault_count)
{
	size_t i;

	if (!fault_count) {
		vOutputString("Health Test ID 0x%02x Company ID 0x%04x: no faults\r\n", test_id, cid);
		return;
	}

	vOutputString("Health Test ID 0x%02x Company ID 0x%04x Fault Count %zu:\r\n", test_id, cid, fault_count);

	for (i = 0; i < fault_count; i++) {
		vOutputString("\t0x%02x", faults[i]);
	}
}

static void health_current_status(struct bt_mesh_health_cli *cli, u16_t addr,
				  u8_t test_id, u16_t cid, u8_t *faults,
				  size_t fault_count)
{
	vOutputString("Health Current Status from 0x%04x\r\n", addr);
	show_faults(test_id, cid, faults, fault_count);
}

static int fault_get_cur(struct bt_mesh_model *model, u8_t *test_id,
			 u16_t *company_id, u8_t *faults, u8_t *fault_count)
{
	vOutputString("Sending current faults\r\n");

	*test_id = 0x00;
	*company_id = BT_COMP_ID_LF;

	get_faults(cur_faults, sizeof(cur_faults), faults, fault_count);

	return 0;
}

static int fault_get_reg(struct bt_mesh_model *model, u16_t cid,
			 u8_t *test_id, u8_t *faults, u8_t *fault_count)
{
	if (cid != BT_COMP_ID_LF) {
		vOutputString("Faults requested for unknown Company ID 0x%04x\r\n", cid);
		return -EINVAL;
	}

	vOutputString("Sending registered faults\r\n");

	*test_id = 0x00;

	get_faults(reg_faults, sizeof(reg_faults), faults, fault_count);

	return 0;
}

static int fault_clear(struct bt_mesh_model *model, uint16_t cid)
{
	if (cid != BT_COMP_ID_LF) {
		return -EINVAL;
	}

	(void)memset(reg_faults, 0, sizeof(reg_faults));

	return 0;
}

static int fault_test(struct bt_mesh_model *model, uint8_t test_id, uint16_t cid)
{
	if (cid != BT_COMP_ID_LF) {
		return -EINVAL;
	}

	if (test_id != 0x00) {
		return -EINVAL;
	}

	return 0;
}

static void attn_on(struct bt_mesh_model *model)
{

	vOutputString("Attention timer on\r\n");

}

static void attn_off(struct bt_mesh_model *model)
{
	vOutputString("Attention timer off\r\n");
}

static void bt_enable_cb(int err)
{
	if (!err) {
		blemesh_init();
		mesh_gen_srv_callback_register(model_gen_cb);
		vTaskDelay(500);
		blemesh_pb_gatt();
	}
}
void mesh_node_open(void)
{

	blemesh_pb_gatt();

}
void mesh_node_reset(void)
{

	blemesh_reset();

}
int blemesh_node(void)
{
	borad_rgb_init();	
	// Initialize BLE controller
    ble_controller_init(configMAX_PRIORITIES - 1);
    // Initialize BLE Host stack
    hci_driver_init();
    bt_enable(bt_enable_cb);
    return 0;
}
