#include <stdlib.h>
#include "conn.h"
#include "gatt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cli.h"
#include "mesh_cli_cmds.h"
#include "include/mesh.h"
#include "errno.h"

#include "mesh.h"
#include "net.h"
#include "transport.h"
#include "foundation.h"
#include "mesh_settings.h"
#include "adv.h"
#include "beacon.h"
#include "hci_core.h"
#include "log.h"
#if defined(CONFIG_BT_MESH_MODEL)
#if (defined(CONFIG_BT_MESH_MODEL_GEN_SRV) || defined(CONFIG_BT_MESH_MODEL_GEN_CLI))
#include "bfl_ble_mesh_generic_model_api.h"
#endif
#if (defined(CONFIG_BT_MESH_MODEL_LIGHT_SRV) || defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI))
#include "bfl_ble_mesh_lighting_model_api.h"
#endif
#include "bfl_ble_mesh_local_data_operation_api.h"
#include "bfl_ble_mesh_networking_api.h"
#else
#if defined(CONFIG_BT_MESH_MODEL_GEN_SRV)
#include "gen_srv.h"
#endif
#endif /* CONFIG_BT_MESH_MODEL */


#if defined(CONFIG_BT_SETTINGS)
#include "easyflash.h"
#endif

#define CUR_FAULTS_MAX 4

bool blemesh_inited = false;
#if defined(CONFIG_BT_MESH_LOW_POWER)
//below value is for Tmall Genie
u8_t dev_uuid[16] = {0xA8,0x01,0x71,0x5e,0x1c,0x00,0x00,0xe4,0x46,0x46,0x63,0xa7,0xf8,0x02,0x00,0x00};
u8_t auth_value[16] = {0x78,0x8A,0xE3,0xEE,0x0F,0x2A,0x7E,0xFA,0xD3,0x67,0x35,0x81,0x41,0xFE,0x1B,0x06};
#else
u8_t dev_uuid[16] = {0xA8,0x01,0x71,0xe0,0x1a,0x00,0x00,0x0f,0x7e,0x35,0x63,0xa7,0xf8,0x02,0x00,0x00};
u8_t auth_value[16] = {0x7f,0x80,0x1a,0xf4,0xa0,0x8c,0x50,0x39,0xae,0x7d,0x7b,0x44,0xa0,0x92,0xd9,0xc2};
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

#if defined(BL602) || defined(BL702)
#define vOutputString(...)  printf(__VA_ARGS__)
#else
#define vOutputString(...)  bl_print(SYSTEM_UART_ID, PRINT_MODULE_CLI, __VA_ARGS__)
#endif

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

static void blemesh_init(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_set_dev_uuid(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_input_num(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_input_str(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
#if defined(CONFIG_BT_MESH_MODEL)
#if defined(CONFIG_BT_MESH_MODEL_GEN_CLI)
static void blemesh_gen_oo_cli(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
#endif
#if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
static void blemesh_light_lgn_cli(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_light_ctl_cli(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_light_hsl_cli(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
#endif
#endif /* CONFIG_BT_MESH_MODEL */
static void blemesh_pb(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_reset(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_net_send(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_seg_send(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_rpl_clr(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_ivu_test(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_iv_update(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
static void blemesh_fault_set(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);

#if defined(CONFIG_BT_MESH_LOW_POWER)
static void blemesh_lpn_set(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
#endif

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

#if defined(CONFIG_BT_MESH_MODEL)
#if defined(CONFIG_BT_MESH_MODEL_GEN_SRV)
BFL_BLE_MESH_MODEL_PUB_DEFINE(onoff_pub, 2 + 3, ROLE_NODE);
static bfl_ble_mesh_gen_onoff_srv_t onoff_server = {
    .rsp_ctrl.get_auto_rsp = BFL_BLE_MESH_SERVER_AUTO_RSP,
    .rsp_ctrl.set_auto_rsp = BFL_BLE_MESH_SERVER_AUTO_RSP,
};

#endif

#if defined(CONFIG_BT_MESH_MODEL_GEN_CLI)
BFL_BLE_MESH_MODEL_PUB_DEFINE(onoff_cli_pub, 2 + 1, ROLE_NODE);
static bfl_ble_mesh_client_t onoff_client;
#endif

#if defined(CONFIG_BT_MESH_MODEL_LIGHT_SRV)
BFL_BLE_MESH_MODEL_PUB_DEFINE(lightness_pub, 2 + 3, ROLE_NODE);
static bfl_ble_mesh_light_lightness_state_t lightness_state;
static bfl_ble_mesh_light_lightness_srv_t lightness_server = {
    .rsp_ctrl.get_auto_rsp = BFL_BLE_MESH_SERVER_RSP_BY_APP,
    .rsp_ctrl.set_auto_rsp = BFL_BLE_MESH_SERVER_RSP_BY_APP,
    .state = &lightness_state,
};
#endif

#if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
BFL_BLE_MESH_MODEL_PUB_DEFINE(lightness_cli_pub, 2 + 1, ROLE_NODE);
static bfl_ble_mesh_client_t lightness_client;
#endif

#if defined(CONFIG_BT_MESH_MODEL_LIGHT_SRV)
BFL_BLE_MESH_MODEL_PUB_DEFINE(ctl_pub, 2 + 3, ROLE_NODE);
static bfl_ble_mesh_light_ctl_state_t ctl_state;
static bfl_ble_mesh_light_ctl_srv_t ctl_server = {
    .rsp_ctrl.get_auto_rsp = BFL_BLE_MESH_SERVER_AUTO_RSP,
    .rsp_ctrl.set_auto_rsp = BFL_BLE_MESH_SERVER_AUTO_RSP,
    .state = &ctl_state,
};
#endif

#if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
BFL_BLE_MESH_MODEL_PUB_DEFINE(ctl_cli_pub, 2 + 1, ROLE_NODE);
static bfl_ble_mesh_client_t ctl_client;
#endif

#if defined(CONFIG_BT_MESH_MODEL_LIGHT_SRV)
BFL_BLE_MESH_MODEL_PUB_DEFINE(hsl_pub, 2 + 3, ROLE_NODE);
static bfl_ble_mesh_light_hsl_state_t hsl_state;
static bfl_ble_mesh_light_hsl_srv_t hsl_server = {
    .rsp_ctrl.get_auto_rsp = BFL_BLE_MESH_SERVER_AUTO_RSP,
    .rsp_ctrl.set_auto_rsp = BFL_BLE_MESH_SERVER_AUTO_RSP,
    .state = &hsl_state,
};
#endif

#if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
BFL_BLE_MESH_MODEL_PUB_DEFINE(hsl_cli_pub, 2 + 1, ROLE_NODE);
static bfl_ble_mesh_client_t hsl_client;
#endif

#else
#if defined(CONFIG_BT_MESH_MODEL_GEN_SRV)
struct bt_mesh_gen_onoff_srv onoff_srv = {
};
#endif
#endif /* CONFIG_BT_MESH_MODEL */

static struct bt_mesh_model sig_models[] = {
    BT_MESH_MODEL_CFG_SRV(&cfg_srv),
    BT_MESH_MODEL_CFG_CLI(&cfg_cli),
    BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub),
    BT_MESH_MODEL_HEALTH_CLI(&health_cli),
#if !defined(CONFIG_BT_MESH_MODEL)
    #if defined(CONFIG_BT_MESH_MODEL_GEN_SRV)
    BT_MESH_MODEL_GEN_ONOFF(&onoff_srv),
    #endif
#else
    #if defined(CONFIG_BT_MESH_MODEL_GEN_SRV)
    BFL_BLE_MESH_MODEL_GEN_ONOFF_SRV(&onoff_pub, &onoff_server),
    #endif
    #if defined(CONFIG_BT_MESH_MODEL_GEN_CLI)
    BFL_BLE_MESH_MODEL_GEN_ONOFF_CLI(&onoff_cli_pub, &onoff_client),
    #endif
    #if defined(CONFIG_BT_MESH_MODEL_LIGHT_SRV)
    BFL_BLE_MESH_MODEL_LIGHT_LIGHTNESS_SRV(&lightness_pub, &lightness_server),
    #endif
    #if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
    BFL_BLE_MESH_MODEL_LIGHT_LIGHTNESS_CLI(&lightness_cli_pub, &lightness_client),
    #endif
    #if defined(CONFIG_BT_MESH_MODEL_LIGHT_SRV)
    BFL_BLE_MESH_MODEL_LIGHT_CTL_SRV(&ctl_pub, &ctl_server),
    #endif
    #if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
    BFL_BLE_MESH_MODEL_LIGHT_CTL_CLI(&ctl_cli_pub, &ctl_client),
    #endif
    #if defined(CONFIG_BT_MESH_MODEL_LIGHT_SRV)
    BFL_BLE_MESH_MODEL_LIGHT_HSL_SRV(&hsl_pub, &hsl_server),
    #endif
    #if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
    BFL_BLE_MESH_MODEL_LIGHT_HSL_CLI(&hsl_cli_pub, &hsl_client),
    #endif
#endif /* CONFIG_BT_MESH_MODEL */
};

#define VENDOR_DATA_LEN (BT_MESH_TX_SDU_MAX-4-3)
struct vendor_data_t{
    uint8_t data[VENDOR_DATA_LEN];
}vendor_data;

static void vendor_data_set(struct bt_mesh_model *model,
                              struct bt_mesh_msg_ctx *ctx,
                              struct net_buf_simple *buf)
{
    NET_BUF_SIMPLE_DEFINE(msg, 3 + VENDOR_DATA_LEN + 4);

    vOutputString("data[%s]\n", bt_hex(buf->data, buf->len));

    if (buf == NULL) {
        BT_ERR("%s, Invalid model user_data", __func__);
        return;
    }
    bt_mesh_model_msg_init(&msg, 0xC2003F);
    net_buf_simple_add_mem(&msg, buf->data, buf->len);

    bt_mesh_model_send(model, ctx, &msg, NULL, NULL);
}

/* Mapping of message handlers for Generic Power OnOff Server (0x1006) */
const struct bt_mesh_model_op vendor_data_op[] = {
    { 0xC1003F, 1, vendor_data_set },
    BT_MESH_MODEL_OP_END,
};

static struct bt_mesh_model vendor_models[] = {
    BT_MESH_MODEL_VND(0x003F, 0x002A, vendor_data_op, NULL, &vendor_data),
};

static struct bt_mesh_elem elements[] = {
    BT_MESH_ELEM(0, sig_models, vendor_models),
};

static const struct bt_mesh_comp comp = {
    .cid = BL_COMP_ID,
    .elem = elements,
    .elem_count = ARRAY_SIZE(elements),
};

#if defined(BL602) || defined(BL702)
const struct cli_command btMeshCmdSet[] STATIC_CLI_CMD_ATTRIBUTE = {
#else
const struct cli_command btMeshCmdSet[] = {
#endif
    {"blemesh_init", "\r\nblemesh_init:[Initialize]\r\n Parameter[Null]\r\n", blemesh_init},
    {"blemesh_set_dev_uuid", "\r\nblemesh_input_num:[input number in provisionging procedure]\r\n\
     [Size:16 Octets, e.g.112233445566778899AA]\r\n", blemesh_set_dev_uuid},
    {"blemesh_pb", "\r\nblemesh_pb:[Enable or disable provisioning]\r\n\
     [bear, 1:adv bear, 2:gatt bear]\r\n\
     [enable, 0:disable provisioning, 1:enable provisioning]\r\n", blemesh_pb},

    {"blemesh_reset", "\r\nblemesh_reset:[Reset the state of the local mesh node]\r\n Parameter[Null]\r\n", blemesh_reset},
    {"blemesh_net_send", "\r\nblemesh_net_send:[Send a network packet]\r\n Parameter[TTL CTL SRC DST]\r\n", blemesh_net_send},
    {"blemesh_seg_send", "\r\nblemesh_seg_send:[Send a segmented message]\r\n Parameter[SRC DST]\r\n", blemesh_seg_send},
    {"blemesh_rpl_clr", "\r\nblemesh_rpl_clr:[Clear replay protection list]\r\n Parameter[Null]\r\n", blemesh_rpl_clr},
    {"blemesh_ivu_test", "\r\nblemesh_ivu_test:[Enable or disable iv update test mode]\r\n\
     [enable, 0:disable, 1:enable]\r\n", blemesh_ivu_test},
    {"blemesh_iv_update", "\r\nblemesh_iv_update:[Enable or disable iv update procedure]\r\n\
     [enable, 0:disable, 1:enable by sending secure network beacons]\r\n", blemesh_iv_update},
    {"blemesh_fault_set", "\r\nblemesh_fault_set:[Set current fault or registered fault values]\r\n\
     [type, 0:current fault, 1:registered fault]\r\n\
     [fault, fault array in hex format]\r\n", blemesh_fault_set},
    #if defined(CONFIG_BT_MESH_LOW_POWER)
    {"blemesh_lpn_set", "\r\nblemesh_lpn_set:[Enable or disable low power node]\r\n\
     [enable, 0:disable lpn, 1:enable lpn]\r\n", blemesh_lpn_set},
    #endif
    {"blemesh_input_num", "\r\nblemesh_input_num:[input number in provisionging procedure]\r\n\
     [Max Size:16 Octets, e.g.112233445566778899AA]\r\n", blemesh_input_num},

    {"blemesh_input_str", "\r\nblemesh_input_str:[input Alphanumeric in provisionging procedure]\r\n\
     [Max Size:16 Characters, e.g.123ABC]\r\n", blemesh_input_str},
#if defined(CONFIG_BT_MESH_MODEL)
#if defined(CONFIG_BT_MESH_MODEL_GEN_CLI)
    {"blemesh_gen_oo_cli", "\r\blemesh_gen_oo_cli:[cmd op app_idx opcode msg_role addr net_idx op_en_t onoff tid trans_time delay]\r\n\
     []\r\n", blemesh_gen_oo_cli},
#endif
#if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
     {"blemesh_light_lgn_cli", "\r\blemesh_light_lgn_cli:[cmd op app_idx opcode msg_role addr net_idx op_en_t lightness tid trans_time delay]\r\n\
     []\r\n", blemesh_light_lgn_cli},
     {"blemesh_light_ctl_cli", "\r\blemesh_light_ctl_cli:[cmd op app_idx opcode msg_role addr net_idx op_en_t ctl_lightness ctl_temperatrue ctl_delta_uv tid trans_time delay]\r\n\
     []\r\n", blemesh_light_ctl_cli},
     {"blemesh_light_hsl_cli", "\r\blemesh_light_hsl_cli:[cmd op app_idx opcode msg_role addr net_idx op_en lightness hue saturation tid trans_time delay]\r\n\
     []\r\n", blemesh_light_hsl_cli},
#endif
#endif /* CONFIG_BT_MESH_MODEL */

    #if defined(BL70X)
    {NULL, NULL, "No handler / Invalid command", NULL}
    #endif
};

#if defined(CONFIG_BT_MESH_LOW_POWER)
static void blemesh_lpn_set(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    static bool lpn_enabled;
    u8_t enable;
    int err;


    get_uint8_from_string(&argv[1], &enable);

    if(enable){
        if(lpn_enabled){
            vOutputString("LPN already enabled\r\n");
            return;
        }

        err = bt_mesh_lpn_set(true);
        if(err){
            vOutputString("Failed to enable LPN\r\n");
        }else{
            lpn_enabled = true;
            vOutputString("Enable LPN successfully\r\n");
        }
    }else{
        if(!lpn_enabled){
            vOutputString("LPN already disabled\r\n");
            return;
        }

        err = bt_mesh_lpn_set(false);
        if(err){
            vOutputString("Failed to disable LPN\r\n");
        }else{
            lpn_enabled = false;
            vOutputString("Disable LPN successfully\r\n");
        }
    }
}

static void lpn_cb(u16_t friend_addr, bool established)
{
    if (established) {
        vOutputString("Friendship (as LPN) established to Friend 0x%04x\r\n", friend_addr);
    } else {
        vOutputString("Friendship (as LPN) lost with Friend 0x%04x\r\n", friend_addr);
    }
}
#endif

static void blemesh_init(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
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

#ifdef CONFIG_BT_MESH_PTS
    int i;

    // used for almost all test cases
    vOutputString("[PTS] TSPX_bd_addr_iut: ");
    for(i=0; i<6; i++) {
        vOutputString("%02X", bt_dev.id_addr[0].a.val[i]);
    }
    vOutputString("\r\n");

    // used for almost all test cases
    vOutputString("[PTS] TSPX_device_uuid: ");
    for(i=0; i<16; i++) {
        vOutputString("%02X", dev_uuid[i]);
    }
    vOutputString("\r\n");

    // used for test case MESH/NODE/RLY/BV-02-C
    vOutputString("[PTS] TSPX_maximum_network_message_cache_entries: %d\r\n", CONFIG_BT_MESH_MSG_CACHE_SIZE);

    // used for test case MESH/NODE/CFG/CFGR/BV-01-C
    vOutputString("[PTS] TSPX_iut_supports_relay: %s\r\n", cfg_srv.relay == BT_MESH_RELAY_ENABLED ? "TRUE" : "FALSE");

    // used for test case MESH/NODE/CFG/SL/BV-03-C
    vOutputString("[PTS] TSPX_vendor_model_id: %04X%04X\r\n", vendor_models[0].vnd.company, vendor_models[0].vnd.id);
#endif

#if IS_ENABLED(CONFIG_BT_MESH_LOW_POWER)
    bt_mesh_lpn_set_cb(lpn_cb);
#endif
}

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
static void blemesh_pb(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int err;
    uint8_t bearer;
    uint8_t enable;

    if(argc != 3){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    get_uint8_from_string(&argv[1], &bearer);
    get_uint8_from_string(&argv[2], &enable);

    if (enable) {
        err = bt_mesh_prov_enable(bearer);
        if (err) {
            vOutputString("Failed to enable %s (err %d)\r\n", bearer2str(bearer), err);
        } else {
            vOutputString("%s enabled\r\n", bearer2str(bearer));
        }
    } else {
        err = bt_mesh_prov_disable(bearer);
        if (err) {
            vOutputString("Failed to disable %s (err %d)\r\n",
                    bearer2str(bearer), err);
        } else {
            vOutputString("%s disabled\r\n", bearer2str(bearer));
        }
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

static void blemesh_set_dev_uuid(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    if(argc != 2){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    vOutputString("device uuid is %s\r\n", argv[1]);
    get_bytearray_from_string(&argv[1], dev_uuid,16);
}

static void blemesh_input_num(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int err;
    uint32_t num;

    if(argc != 2){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    num = strtoul(argv[1], NULL, 10);

    if (input_act != BT_MESH_ENTER_NUMBER) {
        vOutputString("A number hasn't been requested!\r\n");
        return;
    }

    if (strlen(argv[1]) < input_size) {
        vOutputString("Too short input (%u digits required)\r\n", input_size);
        return;
    }

    err = bt_mesh_input_number(num);
    if (err) {
        vOutputString("Numeric input failed (err %d)\r\n", err);
        return;
    }

    input_act = BT_MESH_NO_INPUT;
}

static void blemesh_input_str(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int err;

    if(argc != 2){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    if (input_act != BT_MESH_ENTER_STRING) {
        vOutputString("A string hasn't been requested!\r\n");
        return;
    }

    if (strlen(argv[1]) < input_size) {
        vOutputString("Too short input (%u characters required)\r\n", input_size);
        return;
    }

    err = bt_mesh_input_string(argv[1]);
    if (err) {
        vOutputString("String input failed (err %d)\r\n", err);
        return;
    }

    input_act = BT_MESH_NO_INPUT;
}

#if defined(CONFIG_BT_MESH_MODEL)
#if defined(CONFIG_BT_MESH_MODEL_GEN_CLI)
void ble_mesh_generic_onoff_client_model_cb(bfl_ble_mesh_generic_client_cb_event_t event,
        bfl_ble_mesh_generic_client_cb_param_t *param)
{
    uint32_t opcode = param->params->opcode;

    vOutputString("enter %s: event is %d, error code is %d, opcode is 0x%x\n",
             __func__, event, param->error_code, opcode);

    switch (event) {
    case BFL_BLE_MESH_GENERIC_CLIENT_GET_STATE_EVT: {
        switch (opcode) {
        case BFL_BLE_MESH_MODEL_OP_GEN_ONOFF_GET:
            if (param->error_code == BFL_OK) {
                vOutputString("GenOnOffClient:GetStatus,OK[%x]\n", param->status_cb.onoff_status.present_onoff);
            } else {
                vOutputString("GenOnOffClient:GetStatus,Fail[%x]\n", param->error_code);
            }
            break;
        default:
            break;
        }
        break;
    }
    case BFL_BLE_MESH_GENERIC_CLIENT_SET_STATE_EVT: {
        switch (opcode) {
        case BFL_BLE_MESH_MODEL_OP_GEN_ONOFF_SET:
            if (param->error_code == BFL_OK) {
                vOutputString("GenOnOffClient:SetStatus,OK[%x]\n", param->status_cb.onoff_status.present_onoff);
            } else {
                vOutputString("GenOnOffClient:SetStatus,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK:
            if (param->error_code == BFL_OK) {
                vOutputString("GenOnOffClient:SetUNACK,OK\n");
            } else {
                vOutputString("GenOnOffClient:SetUNACK,Fail[%x]\n", param->error_code);
            }
            break;
        default:
            break;
        }
        break;
    }
    case BFL_BLE_MESH_GENERIC_CLIENT_PUBLISH_EVT: {
        if (param->error_code == BFL_OK) {
            vOutputString("GenOnOffClient:Publish,OK\n");
        } else {
            vOutputString("GenOnOffClient:Publish,Fail[%x]\n", param->error_code);
        }
        break;
    }
    case BFL_BLE_MESH_GENERIC_CLIENT_TIMEOUT_EVT:
        vOutputString("GenOnOffClient:TimeOut[%x]\n", param->error_code);
        break;
    case BFL_BLE_MESH_GENERIC_CLIENT_EVT_MAX:
        vOutputString("GenONOFFClient:InvalidEvt[%x]\n", param->error_code);
        break;
    default:
        break;
    }
    vOutputString("exit %s \n", __func__);
}


static void blemesh_gen_oo_cli(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int err = BFL_OK;

    if(argc < 1){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    bfl_ble_mesh_generic_client_set_state_t gen_client_set;
    bfl_ble_mesh_generic_client_get_state_t gen_client_get;
    bfl_ble_mesh_client_common_param_t onoff_common = {
        .msg_timeout = 0,
        .ctx.send_ttl = 7,
        .model = NULL,
    };

    vOutputString("enter %s\n", __func__);

    /*Get client model*/
    for(int i = 0; i < sizeof(sig_models)/sizeof(struct bt_mesh_model); ++i){
        if(sig_models[i].id == BFL_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI){
             onoff_common.model = &sig_models[i];
        }
    }
    if(onoff_common.model == NULL){
        vOutputString("Can't find gen onoff cli %s\n", __func__);
        return;
    }

    if(argc > 6){
        /* appkey_index */
        get_uint16_from_string(&argv[2], &onoff_common.ctx.app_idx);
        /* opcode */
        get_uint32_from_string(&argv[3], &onoff_common.opcode);
        /* role */
        get_uint8_from_string(&argv[4], &onoff_common.msg_role);
        /* address */
        get_uint16_from_string(&argv[5], &onoff_common.ctx.addr);
        /* network key index */
        get_uint16_from_string(&argv[6], &onoff_common.ctx.net_idx);
    }
    if(argc > 11){
        /* op_en */
        uint8_t op_en_t;
        get_uint8_from_string(&argv[7], &op_en_t);
        gen_client_set.onoff_set.op_en = op_en_t?true:false;

        /* onoff */
        get_uint8_from_string(&argv[8], &gen_client_set.onoff_set.onoff);
        /* tid */
        get_uint8_from_string(&argv[9], &gen_client_set.onoff_set.tid);
        /* trans_time */
        get_uint8_from_string(&argv[10], &gen_client_set.onoff_set.trans_time);
        /* delay */
        get_uint8_from_string(&argv[11], &gen_client_set.onoff_set.delay);
    }

    if (strcmp(argv[1], "get") == 0) {
        err = bfl_ble_mesh_generic_client_get_state(&onoff_common, &gen_client_get);
    } else if (strcmp(argv[1], "set") == 0) {
        err = bfl_ble_mesh_generic_client_set_state(&onoff_common, &gen_client_set);
    } else if (strcmp(argv[1], "reg") == 0) {
        err = bfl_ble_mesh_register_generic_client_callback(ble_mesh_generic_onoff_client_model_cb);
        if (err == BFL_OK) {
            vOutputString("GenONOFFClient:Reg,OK\n");
        }
    }
    vOutputString("exit %s\n", __func__);
}
#endif

#if defined(CONFIG_BT_MESH_MODEL_LIGHT_CLI)
void ble_mesh_light_client_model_cb(bfl_ble_mesh_light_client_cb_event_t event,
        bfl_ble_mesh_light_client_cb_param_t *param)
{
    uint32_t opcode = param->params->opcode;

    vOutputString("enter %s: event is %d, error code is %d, opcode is 0x%x\n",
             __func__, event, param->error_code, opcode);

    switch (event) {
    case BFL_BLE_MESH_LIGHT_CLIENT_GET_STATE_EVT: {
        switch (opcode) {
        case BFL_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_GET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light lightness Client:GetStatus,OK, ln[%x]ln_t[%x]\n"
                                , param->status_cb.lightness_status.present_lightness
                                , param->status_cb.lightness_status.target_lightness);
            } else {
                vOutputString("Light lightness Client:GetStatus,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_CTL_GET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light ctl Client:GetStatus,OK,ln[%x]ln_t[%x] tp[%x]tp_t[%x]\n",
                    param->status_cb.ctl_status.present_ctl_lightness,
                    param->status_cb.ctl_status.target_ctl_lightness,
                    param->status_cb.ctl_status.present_ctl_temperature,
                    param->status_cb.ctl_status.target_ctl_temperature);
            } else {
                vOutputString("Light ctl Client:GetStatus,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_HSL_GET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light hsl Client:GetStatus,OK,l[%x] h[%x] s[%x]\n",
                    param->status_cb.hsl_status.hsl_lightness,
                    param->status_cb.hsl_status.hsl_hue,
                    param->status_cb.hsl_status.hsl_saturation);
            } else {
                vOutputString("Light hsl Client:GetStatus,Fail[%x]\n", param->error_code);
            }
            break;
        default:
            break;
        }
        break;
    }
    case BFL_BLE_MESH_LIGHT_CLIENT_SET_STATE_EVT: {
        switch (opcode) {
        case BFL_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_SET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light lightness Client:SetStatus,OK, ln[%x]ln_t[%x]\n"
                                , param->status_cb.lightness_status.present_lightness
                                , param->status_cb.lightness_status.target_lightness);
            } else {
                vOutputString("Light lightness Client:SetStatus,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_SET_UNACK:
            if (param->error_code == BFL_OK) {
                vOutputString("Light lightness Client:SetUNACK,OK\n");
            } else {
                vOutputString("Light lightness Client:SetUNACK,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_CTL_SET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light ctl Client:SetStatus,OK, ln[%x]ln_t[%x] tp[%x]tp_t[%x]\n",
                    param->status_cb.ctl_status.present_ctl_lightness,
                    param->status_cb.ctl_status.target_ctl_lightness,
                    param->status_cb.ctl_status.present_ctl_temperature,
                    param->status_cb.ctl_status.target_ctl_temperature);
            } else {
                vOutputString("Light ctl Client:SetStatus,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_CTL_SET_UNACK:
            if (param->error_code == BFL_OK) {
                vOutputString("Light ctl Client:SetUNACK,OK\n");
            } else {
                vOutputString("Light ctl Client:SetUNACK,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_HSL_SET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light hsl Client:SetStatus,OK, l[%x] h[%x] s[%x]\n",
                    param->status_cb.hsl_status.hsl_lightness,
                    param->status_cb.hsl_status.hsl_hue,
                    param->status_cb.hsl_status.hsl_saturation);
            } else {
                vOutputString("Light ctl Client:SetStatus,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_HSL_SET_UNACK:
            if (param->error_code == BFL_OK) {
                vOutputString("Light hsl Client:SetUNACK,OK\n");
            } else {
                vOutputString("Light hsl Client:SetUNACK,Fail[%x]\n", param->error_code);
            }
            break;
        default:
            break;
        }
        break;
    }
    case BFL_BLE_MESH_LIGHT_CLIENT_PUBLISH_EVT: {
        switch (opcode) {
        case BFL_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_GET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light lightness Client:Publish,OK\n");
            } else {
                vOutputString("Light lightness Client:Publish,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_CTL_GET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light ctl Client:Publish,OK\n");
            } else {
                vOutputString("Light ctl Client:Publish,Fail[%x]\n", param->error_code);
            }
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_HSL_GET:
            if (param->error_code == BFL_OK) {
                vOutputString("Light hsl Client:Publish,OK\n");
            } else {
                vOutputString("Light hsl Client:Publish,Fail[%x]\n", param->error_code);
            }
            break;
        default:
            break;
        }
        break;
    }
    case BFL_BLE_MESH_LIGHT_CLIENT_TIMEOUT_EVT:{
        switch (opcode) {
        case BFL_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_GET:
        case BFL_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_SET:
        case BFL_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_SET_UNACK:
            vOutputString("Light lightness Client:TimeOut[%x]\n", param->error_code);
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_CTL_GET:
        case BFL_BLE_MESH_MODEL_OP_LIGHT_CTL_SET:
        case BFL_BLE_MESH_MODEL_OP_LIGHT_CTL_SET_UNACK:
            vOutputString("Light ctl Client:TimeOut[%x]\n", param->error_code);
            break;
        case BFL_BLE_MESH_MODEL_OP_LIGHT_HSL_GET:
        case BFL_BLE_MESH_MODEL_OP_LIGHT_HSL_SET:
        case BFL_BLE_MESH_MODEL_OP_LIGHT_HSL_SET_UNACK:
            vOutputString("Light hsl Client:TimeOut[%x]\n", param->error_code);
            break;
        default:
            break;
        }
        break;
    }
    case BFL_BLE_MESH_LIGHT_CLIENT_EVT_MAX:{
        vOutputString("InvalidEvt, Opcode[%x] [%x]\n", opcode, param->error_code);
        break;
    }
    default:
        break;
    }
    vOutputString("exit %s \n", __func__);
}

static void blemesh_light_lgn_cli(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int err = BFL_OK;

    if(argc < 1){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    bfl_ble_mesh_light_client_set_state_t light_client_set;
    bfl_ble_mesh_light_client_get_state_t light_client_get;
    bfl_ble_mesh_client_common_param_t lgn_common = {
        .msg_timeout = 0,
        .ctx.send_ttl = 7,
        .model = NULL,
    };

    vOutputString("enter %s\n", __func__);

    /*Get client model*/
    for(int i = 0; i < sizeof(sig_models)/sizeof(struct bt_mesh_model); ++i){
        if(sig_models[i].id == BFL_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI){
             lgn_common.model = &sig_models[i];
        }
    }
    if(lgn_common.model == NULL){
        vOutputString("Can't find light ligntness cli %s\n", __func__);
        return;
    }

    if(argc > 6){
        /* appkey_index */
        get_uint16_from_string(&argv[2], &lgn_common.ctx.app_idx);
        /* opcode */
        get_uint32_from_string(&argv[3], &lgn_common.opcode);
        /* role */
        get_uint8_from_string(&argv[4], &lgn_common.msg_role);
        /* address */
        get_uint16_from_string(&argv[5], &lgn_common.ctx.addr);
        /* network key index */
        get_uint16_from_string(&argv[6], &lgn_common.ctx.net_idx);
    }
    if(argc > 11){
        /* op_en */
        uint8_t op_en_t;
        get_uint8_from_string(&argv[7], &op_en_t);
        light_client_set.lightness_set.op_en = op_en_t?true:false;

        /* lightness */
        get_uint16_from_string(&argv[8], &light_client_set.lightness_set.lightness);
        /* tid */
        get_uint8_from_string(&argv[9], &light_client_set.lightness_set.tid);
        /* trans_time */
        get_uint8_from_string(&argv[10], &light_client_set.lightness_set.trans_time);
        /* delay */
        get_uint8_from_string(&argv[11], &light_client_set.lightness_set.delay);
    }

    if (strcmp(argv[1], "get") == 0) {
        err = bfl_ble_mesh_light_client_get_state(&lgn_common, &light_client_get);
    } else if (strcmp(argv[1], "set") == 0) {
        err = bfl_ble_mesh_light_client_set_state(&lgn_common, &light_client_set);
    } else if (strcmp(argv[1], "reg") == 0) {
        err = bfl_ble_mesh_register_light_client_callback(ble_mesh_light_client_model_cb);
        if (err == BFL_OK) {
            vOutputString("Light lightness client:Reg,OK\n");
        }
    }
    vOutputString("exit %s\n", __func__);
}

static void blemesh_light_ctl_cli(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int err = BFL_OK;

    if(argc < 1){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    bfl_ble_mesh_light_client_set_state_t light_client_set;
    bfl_ble_mesh_light_client_get_state_t light_client_get;
    bfl_ble_mesh_client_common_param_t ctl_common = {
        .msg_timeout = 0,
        .ctx.send_ttl = 7,
        .model = NULL,
    };

    vOutputString("enter %s\n", __func__);

    /*Get client model*/
    for(int i = 0; i < sizeof(sig_models)/sizeof(struct bt_mesh_model); ++i){
        if(sig_models[i].id == BFL_BLE_MESH_MODEL_ID_LIGHT_CTL_CLI){
             ctl_common.model = &sig_models[i];
        }
    }
    if(ctl_common.model == NULL){
        vOutputString("Can't find light ctl cli %s\n", __func__);
        return;
    }

    if(argc > 6){
        /* appkey_index */
        get_uint16_from_string(&argv[2], &ctl_common.ctx.app_idx);
        /* opcode */
        get_uint32_from_string(&argv[3], &ctl_common.opcode);
        /* role */
        get_uint8_from_string(&argv[4], &ctl_common.msg_role);
        /* address */
        get_uint16_from_string(&argv[5], &ctl_common.ctx.addr);
        /* network key index */
        get_uint16_from_string(&argv[6], &ctl_common.ctx.net_idx);
    }
    if(argc > 13){
        /* op_en */
        uint8_t op_en_t;
        get_uint8_from_string(&argv[7], &op_en_t);
        light_client_set.ctl_set.op_en = op_en_t?true:false;

        /* onoff */
        get_uint16_from_string(&argv[8], &light_client_set.ctl_set.ctl_lightness);

        get_uint16_from_string(&argv[9], &light_client_set.ctl_set.ctl_temperatrue);

        get_uint16_from_string(&argv[10], (uint16_t*)&light_client_set.ctl_set.ctl_delta_uv);
        /* tid */
        get_uint8_from_string(&argv[11], &light_client_set.ctl_set.tid);
        /* trans_time */
        get_uint8_from_string(&argv[12], &light_client_set.ctl_set.trans_time);
        /* delay */
        get_uint8_from_string(&argv[13], &light_client_set.ctl_set.delay);
    }

    if (strcmp(argv[1], "get") == 0) {
        err = bfl_ble_mesh_light_client_get_state(&ctl_common, &light_client_get);
    } else if (strcmp(argv[1], "set") == 0) {
        err = bfl_ble_mesh_light_client_set_state(&ctl_common, &light_client_set);
    } else if (strcmp(argv[1], "reg") == 0) {
        err = bfl_ble_mesh_register_light_client_callback(ble_mesh_light_client_model_cb);
        if (err == BFL_OK) {
            vOutputString("Light lightness client:Reg,OK\n");
        }
    }
    vOutputString("exit %s\n", __func__);
}

static void blemesh_light_hsl_cli(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int err = BFL_OK;

    if(argc < 1){
        vOutputString("Number of Parameters is not correct\n");
        return;
    }

    bfl_ble_mesh_light_client_set_state_t light_client_set;
    bfl_ble_mesh_light_client_get_state_t light_client_get;
    bfl_ble_mesh_client_common_param_t hsl_common = {
        .msg_timeout = 0,
        .ctx.send_ttl = 7,
        .model = NULL,
    };

    vOutputString("enter %s\n", __func__);

    /*Get client model*/
    for(int i = 0; i < sizeof(sig_models)/sizeof(struct bt_mesh_model); ++i){
        if(sig_models[i].id == BFL_BLE_MESH_MODEL_ID_LIGHT_HSL_CLI){
             hsl_common.model = &sig_models[i];
        }
    }
    if(hsl_common.model == NULL){
        vOutputString("Can't find light ligntness cli %s\n", __func__);
        return;
    }

    if(argc > 6){
        /* appkey_index */
        get_uint16_from_string(&argv[2], &hsl_common.ctx.app_idx);
        /* opcode */
        get_uint32_from_string(&argv[3], &hsl_common.opcode);
        /* role */
        get_uint8_from_string(&argv[4], &hsl_common.msg_role);
        /* address */
        get_uint16_from_string(&argv[5], &hsl_common.ctx.addr);
        /* network key index */
        get_uint16_from_string(&argv[6], &hsl_common.ctx.net_idx);
    }
    if(argc > 13){
        /* op_en */
        uint8_t op_en_t;
        get_uint8_from_string(&argv[7], &op_en_t);
        light_client_set.hsl_set.op_en = op_en_t?true:false;

        /* onoff */
        get_uint16_from_string(&argv[8], &light_client_set.hsl_set.hsl_lightness);
        get_uint16_from_string(&argv[9], &light_client_set.hsl_set.hsl_hue);
        get_uint16_from_string(&argv[10], &light_client_set.hsl_set.hsl_saturation);
        /* tid */
        get_uint8_from_string(&argv[11], &light_client_set.hsl_set.tid);
        /* trans_time */
        get_uint8_from_string(&argv[12], &light_client_set.hsl_set.trans_time);
        /* delay */
        get_uint8_from_string(&argv[13], &light_client_set.hsl_set.delay);
    }

    if (strcmp(argv[1], "get") == 0) {
        err = bfl_ble_mesh_light_client_get_state(&hsl_common, &light_client_get);
    } else if (strcmp(argv[1], "set") == 0) {
        err = bfl_ble_mesh_light_client_set_state(&hsl_common, &light_client_set);
    } else if (strcmp(argv[1], "reg") == 0) {
        err = bfl_ble_mesh_register_light_client_callback(ble_mesh_light_client_model_cb);
        if (err == BFL_OK) {
            vOutputString("Light lightness client:Reg,OK\n");
        }
    }
    vOutputString("exit %s\n", __func__);
}
#endif
#endif /* CONFIG_BT_MESH_MODEL */

static int input(bt_mesh_input_action_t act, u8_t size)
{
    switch (act) {
    case BT_MESH_ENTER_NUMBER:
        vOutputString("Enter a number (max %u digits) with: input-num <num>\r\n", size);
        break;
    case BT_MESH_ENTER_STRING:
        vOutputString("Enter a string (max %u chars) with: input-str <str>\r\n", size);
        break;
    default:
        vOutputString("Unknown input action %u (size %u) requested!\r\n", act, size);
        return -EINVAL;
    }

    input_act = act;
    input_size = size;
    return 0;
}

static void blemesh_reset(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    bt_mesh_reset();
    vOutputString("Local node reset complete\r\n");
}

static void blemesh_net_send(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    uint8_t ttl;
    uint8_t ctl;
    uint16_t src;
    uint16_t dst;
    uint8_t payload[16] = {0x00};

    if(argc != 5){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    if (!bt_mesh_is_provisioned()) {
        vOutputString("Local node is not yet provisioned\r\n");
        return;
    }

    get_uint8_from_string(&argv[1], &ttl);
    get_uint8_from_string(&argv[2], &ctl);
    get_uint16_from_string(&argv[3], &src);
    get_uint16_from_string(&argv[4], &dst);

    struct bt_mesh_msg_ctx ctx = {
        .net_idx = net.net_idx,
        .app_idx = ctl ? BT_MESH_KEY_UNUSED : BT_MESH_KEY_DEV,
        .addr = dst,
        .send_rel = 0,
        .send_ttl = ttl,
    };

    struct bt_mesh_net_tx tx = {
        .sub = bt_mesh_subnet_get(ctx.net_idx),
        .ctx = &ctx,
        .src = src,
        .xmit = bt_mesh_net_transmit_get(),
        .friend_cred = 0,
    };

    struct net_buf *buf = bt_mesh_adv_create(BT_MESH_ADV_DATA, tx.xmit, K_NO_WAIT);
    if (!buf) {
        vOutputString("Out of network buffers\r\n");
        return;
    }

    vOutputString("Sending network packet\r\n");

    net_buf_reserve(buf, BT_MESH_NET_HDR_LEN);
    net_buf_add_mem(buf, payload, sizeof(payload));

    bt_mesh_net_send(&tx, buf, NULL, NULL);
}

static uint16_t get_app_idx(void)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(bt_mesh.app_keys); i++) {
        struct bt_mesh_app_key *key = &bt_mesh.app_keys[i];

        if (key->net_idx != BT_MESH_KEY_UNUSED) {
            return key->app_idx;
        }
    }

    return BT_MESH_KEY_UNUSED;
}

static void blemesh_seg_send(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    NET_BUF_SIMPLE_DEFINE(sdu, BT_MESH_TX_SDU_MAX);
    uint16_t src;
    uint16_t dst;
    uint8_t payload[12] = {0xFF};

    if(argc != 3){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    if (!bt_mesh_is_provisioned()) {
        vOutputString("Local node is not yet provisioned\r\n");
        return;
    }

    get_uint16_from_string(&argv[1], &src);
    get_uint16_from_string(&argv[2], &dst);

    struct bt_mesh_msg_ctx ctx = {
        .net_idx = net.net_idx,
        .app_idx = get_app_idx(),
        .addr = dst,
        .send_rel = 1,
        .send_ttl = 0,
    };

    struct bt_mesh_net_tx tx = {
        .sub = bt_mesh_subnet_get(ctx.net_idx),
        .ctx = &ctx,
        .src = src,
        .xmit = bt_mesh_net_transmit_get(),
        .friend_cred = 0,
    };

    vOutputString("Sending segmented message\r\n");

    net_buf_simple_add_mem(&sdu, payload, sizeof(payload));

    bt_mesh_trans_send(&tx, &sdu, NULL, NULL);
}

static void blemesh_rpl_clr(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
#if defined(CONFIG_BT_SETTINGS)
    int err;
    err = ef_del_env(NV_MESH_RPL);
    if(err) {
        vOutputString("Failed to clear replay protection list\r\n");
    } else {
        vOutputString("Replay protection list (size: %d) cleared\r\n", CONFIG_BT_MESH_CRPL);
    }
#endif

    memset(bt_mesh.rpl, 0, sizeof(bt_mesh.rpl));
}

static void blemesh_ivu_test(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    uint8_t enable;

    if(argc != 2){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    get_uint8_from_string(&argv[1], &enable);

#if defined(CONFIG_BT_MESH_IV_UPDATE_TEST)
    bt_mesh_iv_update_test(enable);
#endif

    if (enable) {
        vOutputString("IV Update test mode enabled\r\n");
    } else {
        vOutputString("IV Update test mode disabled\r\n");
    }
}

static void blemesh_iv_update(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    uint8_t enable;

    if(argc != 2){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    if (!bt_mesh_is_provisioned()) {
        vOutputString("Local node is not yet provisioned\r\n");
        return;
    }

    get_uint8_from_string(&argv[1], &enable);

    if (enable) {
        vOutputString("IV Update procedure started\r\n");

#if defined(CONFIG_BT_MESH_IV_UPDATE_TEST)
        bt_mesh_iv_update();
#endif

        if (!atomic_test_bit(bt_mesh.flags, BT_MESH_IVU_INITIATOR)) {
            bt_mesh_beacon_ivu_initiator(1);
        }
    } else {
        vOutputString("IV Update procedure stopped\r\n");

        if (atomic_test_bit(bt_mesh.flags, BT_MESH_IVU_INITIATOR)) {
            bt_mesh_beacon_ivu_initiator(0);
        }
    }
}

static void blemesh_fault_set(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    uint8_t type;
    int i;

    if(argc != 3){
        vOutputString("Number of Parameters is not correct\r\n");
        return;
    }

    get_uint8_from_string(&argv[1], &type);

    if (type == 0) {
        if(strlen(argv[2])/2 >= sizeof(cur_faults)) {
            get_bytearray_from_string(&argv[2], cur_faults,sizeof(cur_faults));
        } else {
            memset(cur_faults, 0x00, sizeof(cur_faults));
            get_bytearray_from_string(&argv[2], cur_faults,strlen(argv[2])/2);
        }

        vOutputString("Current Fault: ");
        for(i=0; i<sizeof(cur_faults); i++) {
            vOutputString("%02X", cur_faults[i]);
        }
        vOutputString("\r\n");
    } else {
        if(strlen(argv[2])/2 >= sizeof(reg_faults)) {
            get_bytearray_from_string(&argv[2], reg_faults,sizeof(reg_faults));
        } else {
            memset(reg_faults, 0x00, sizeof(reg_faults));
            get_bytearray_from_string(&argv[2], reg_faults,strlen(argv[2])/2);
        }

        vOutputString("Registered Fault: ");
        for(i=0; i<sizeof(reg_faults); i++) {
            vOutputString("%02X", reg_faults[i]);
        }
        vOutputString("\r\n");
    }
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

void show_faults(u8_t test_id, u16_t cid, u8_t *faults, size_t fault_count)
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
#ifdef CONFIG_BT_MESH_PTS
    vOutputString("[PTS] Attention timer on\r\n");
#endif
}

static void attn_off(struct bt_mesh_model *model)
{
#ifdef CONFIG_BT_MESH_PTS
    vOutputString("[PTS] Attention timer off\r\n");
#endif
}

#if defined(CONFIG_BT_MESH_GATT_PROXY)
static void __attribute__((unused)) blemesh_ident(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int err;

    err = bt_mesh_proxy_identity_enable();
    if (err) {
        vOutputString("Failed advertise using Node Identity (err ""%d)\r\n", err);
    }
}
#endif /* MESH_GATT_PROXY */

int blemesh_cli_register(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //aos_cli_register_commands(btStackCmdSet, sizeof(btMeshCmdSet)/sizeof(btMeshCmdSet[0]));
    return 0;
}
