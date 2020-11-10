/*
 * Copyright (C) 2017 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of XRADIO TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _AT_COMMAND_H_
#define _AT_COMMAND_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "atcmd/at_types.h"
#include "atcmd/at_macros.h"
#include "atcmd/at_config.h"
#include "atcmd/at_status.h"
#include "atcmd/at_queue.h"

#include "at_private.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  AEC_OK = 0,
  AEC_BLANK_LINE,
  AEC_CMD_FAIL,
  AEC_CMD_ERROR,
  AEC_PARA_ERROR,
  AEC_NO_PARA,
  AEC_UNSUPPORTED,
  AEC_NOT_FOUND,
  AEC_NULL_POINTER,
  AEC_OUT_OF_RANGE,
  AEC_SCAN_FAIL,
  AEC_READ_ONLY,
  AEC_SEND_FAIL,
  AEC_SWITCH_MODE,
  AEC_CONNECT_FAIL,
  AEC_BIND_FAIL,
  AEC_SOCKET_FAIL,
  AEC_LIMITED,
  AEC_DISCONNECT,
  AEC_NETWORK_ERROR,
  AEC_NOT_ENOUGH_MEMORY,
  AEC_IMPROPER_OPERATION,
  AEC_SOCKET_EXISTING,
  AEC_SEND_READY,
  AEC_SEND_TIMEOUT,
  AEC_UPGRADE_FAILED,
  AEC_UNDEFINED,
  AEC_NO_RESPONSE,
} AT_ERROR_CODE;

typedef enum {
  ACC_ACT = 0,     /* activate config */
  ACC_RST,         /* reset the module */
  ACC_MODE,        /* switch to data mode */
  ACC_SAVE,        /* save config to flash */
  ACC_LOAD,        /* load config from flash */
  ACC_STATUS,      /* update status */
  ACC_FACTORY,     /* Restore factory default settings */
  ACC_PEER,        /* get detail information of the peer */
  ACC_PING,        /* ping test */
  ACC_SOCKON,      /* Open a network socket */
  ACC_SOCKW,       /* Write data to socket */
  ACC_SOCKQ,       /* Query socket for pending data */
  ACC_SOCKR,       /* Read data from socket */
  ACC_SOCKC,       /* Close socket */
  ACC_SOCKD,       /* Disable/Enable socket server. */
  ACC_WIFI,        /* Disable/Enable WiFi */
  ACC_REASSOCIATE, /* Trigger a WiFi Roam */
  ACC_GPIOC,       /*  Configure specified GPIO */
  ACC_GPIOR,       /* Read specified GPIO */
  ACC_GPIOW,       /* Write specified GPIO */
  ACC_SCAN,        /* scan available AP */
  //ADD FOR XR809 ACORDING TO ESP8266
  ACC_GMR,
  ACC_RESTORE,
  ACC_UART_SET,
  ACC_UART_GET,
  ACC_SLEEP,
  ACC_DEEP_SLEEP,
  ACC_WAKEUPGPIO,
  ACC_CWMODE_CUR,
  ACC_CWMODE_GET,
  ACC_CWJAP_CUR,
  ACC_CWJAP_INFO,
  ACC_CWLAPOPT,
  ACC_CWLAP,
  ACC_CWQAP,
  ACC_CWDHCP_CUR,
  ACC_CIPSTAMAC_CUR,
  ACC_CIPSTA_CUR,
  ACC_CWHOSTNAME,
  ACC_APCFG,
  ACC_AP_STA_GET,
  //add
  ACC_CIPSTATUS,
  ACC_CIPDOMAIN,
  ACC_CIPSTART,
  ACC_CIPSENDBUF,
  ACC_CIPCLOSE,
  ACC_CIPSSLCCONF_P,
  ACC_CIPSSLCSNI,
  ACC_CIPSSLCALPN,
  ACC_TCPSERVER,
  ACC_TCPSERVERMAXCONN,
  ACC_CIPMUX,
  ACC_CIPMODE,
  ACC_HTTP_REQ,
  ACC_CIPDNS_CUR,
  ACC_CIPRECVDATA,
  ACC_CIPRECVMODE,
  ACC_CIPSEND,
  ACC_SYSIOSETCFG,
  ACC_SYSIOGETCFG,
  ACC_SYSGPIODIR,
  ACC_SYSGPIOWRITE,
  ACC_SYSGPIOREAD,
  ACC_DELETEAP,
  ACC_OTA,
    ACC_BLESYNC,
  ACC_CIPSTA_IP,
    ACC_CIPSTA_IP_GET,
} AT_CALLBACK_CMD;

////////////////////////////////////////////////////
// AT Param struct
///////////////////////////////////////////////////
typedef struct {
  at_text_t key[AT_PARA_MAX_SIZE];
} at_getcfg_t;

typedef struct {
  at_text_t key[AT_PARA_MAX_SIZE];
} config_key_t;

typedef struct {
  at_text_t ssid[AT_PARA_MAX_SIZE];
} at_ssidtxt_para_t;

typedef struct {
  at_text_t sts_var[AT_PARA_MAX_SIZE];
} at_status_para_t;

typedef struct {
  at_di_t peer_number;
  at_text_t peer_var[AT_PARA_MAX_SIZE];
} at_peers_para_t;

typedef struct {
  at_text_t hostname[AT_PARA_MAX_SIZE];
} at_ping_para_t;

typedef struct {
  at_text_t hostname[AT_PARA_MAX_SIZE];
  at_di_t port;
  at_text_t protocol[1 + 1];
  at_text_t ind[3 + 1];
} at_sockon_para_t;

typedef struct {
  at_di_t uart_id;
  at_di_t baudrate;
  at_di_t data_bits;
  at_di_t stop_bits;
  at_di_t parity;
  at_di_t hwfc;
} at_uart_para_t;

typedef struct {
  int sleepMode;

} at_sleep_para_t;

typedef struct {
  int powersaveMode;
} at_powersave_para_t;

typedef struct {
  int echoSwitch;
} at_echoswitch_para_t;

typedef struct {
  int autoconnectSwitch;
} at_autoconnect_para_t;

typedef struct {
  int IPDinfoSwitch;
} at_ipdinfo_para_t;

typedef struct {
  at_di_t sleep_time;
  at_di_t gpioId;
} at_gpiowakeup_para_t;

typedef struct {
  at_di_t wifi_mode;
} at_wifiMode_para_t;

typedef struct {
  at_text_t ssid[AT_PARA_MAX_SIZE];
  at_text_t pwd[AT_PARA_MAX_SIZE];
} at_joinAp_para_t;

#define CMD_WLAN_MAX_BSS_CNT 50

enum atc_scanap_ecntype {
  ATC_SCANAP_ECN_OPEN = 0,
  ATC_SCANAP_ECN_WEP = 1,
  ATC_SCANAP_ECN_WPA_PSK = 2,
  ATC_SCANAP_ECN_WPA_WPA2_PSK = 3,
};

typedef struct {
  at_text_t ssid[AT_PARA_MAX_SIZE];
} at_getscan_para_t;

typedef struct {
  at_di_t dhcpmode;
  at_di_t dhcpen;
} at_dhcp_para_t;

typedef struct {
  at_di_t en;
  at_di_t lease_time;
  at_ip_t start_ip;
  at_ip_t end_ip;
} at_dhcp_range_para_t;

typedef struct {
  at_hex_t mac[6];
} at_mac_para_t;

typedef struct {
  at_ip_t ip;
  at_ip_t getway;
  at_ip_t netmask;
  at_ip_t dns1;
  at_ip_t dns2;
} at_ip_para_t;

typedef struct {
  at_text_t hostname[AT_PARA_MAX_SIZE];
} at_hostname_para_t;

typedef struct {
  at_text_t hostname[AT_PARA_MAX_SIZE];
  uint8_t type; //0:GET, 1:POST
  /*
   * 0 : application/x-www-form-urlencoded
   * 1 : application/json
   * 2 : multipart/form-data
   * 3 : text/xml
   */
  uint8_t content_type;
  at_text_t data[AT_PARA_MAX_SIZE];
} at_http_para_t;

typedef struct {
  at_di_t linkId;
  /**
   * 0: no authorization. In this case, <pki_number> and <ca_number> are not required.
   * 1: load cert and private key for server authorization.
   * 2: load CA for client authorize server cert and private key.
   * 3: both authorization.
   */
  at_di_t auth_mode;
  at_text_t *ca, *key, *cert; //path
} at_client_ssl_path_para_t;

typedef struct {
  at_di_t linkId;
  at_text_t sni[256];
} at_client_ssl_sni_t;

typedef struct {
  at_di_t linkId;
  at_text_t **alpn;
} at_client_ssl_alpn_t;

typedef struct {
  at_text_t address[AT_PARA_MAX_SIZE];
} at_domain_para_t;

typedef struct {
  at_text_t buffer[AT_PARA_MAX_SIZE];
} at_tcp_data_para_t;

typedef struct {
  at_text_t ssid[AT_PARA_MAX_SIZE];
  at_text_t psk[AT_PARA_MAX_SIZE];
  at_di_t chl;
  at_di_t ecn;
  at_di_t max_conn;
  at_di_t hidden;
} at_set_apcfg_para_t;

typedef struct {
  at_di_t linkId;
} at_close_para_t;

typedef struct {
  at_di_t mux;
} at_mux_para_t;

typedef struct {
  at_di_t mode;
} at_trans_mode_para_t;

typedef struct {
  at_ip_t dns;
} at_dns_para_t;

typedef struct {
  at_di_t port;
  at_di_t enable;
  at_di_t tls;
  at_di_t ca;
} at_tcpserver_para_t;

typedef struct {
  at_di_t value;
} at_wifi_para_t;

typedef struct {
  at_di_t num;
  at_text_t direction[3 + 1];
  at_text_t interrupt[1 + 1];
} at_gpioc_para_t;

typedef struct {
  at_di_t num;
} at_gpior_para_t;

typedef struct {
  at_di_t num;
  at_di_t value;
} at_gpiow_para_t;

typedef struct {
  int mode;
} at_ble_sync_mode_t;

typedef struct {
  at_text_t hostname[AT_PARA_MAX_SIZE];
  at_text_t path[1 + 1];
  at_di_t port;
} at_upgrade_para_t;

typedef struct {
  uint8_t ssid[WLAN_SSID_MAX_LEN];
} at_lapscan_para_t;

typedef struct {
  at_text_t mode[1 + 1];
  at_text_t repeat[1 + 1];
} at_scan_para_t;

typedef struct {
  uint8_t sort_enable;
  uint8_t mask;
} at_scan_opt_t;

typedef struct {
  at_di_t linkId;
  at_text_t type[4];
  at_text_t hostname[AT_PARA_MAX_SIZE];
  at_di_t port;
  at_di_t localport;
  at_di_t keepAlive;
} at_network_para_t;

typedef struct {
  at_di_t ID;
  at_di_t mode;
  at_di_t pull;
} at_setgpio_para_t;

typedef struct {
  at_di_t ID;
  at_di_t data;
} at_writegpio_para_t;

typedef struct {
  at_di_t ID;
  at_di_t mode;
} at_setgpiodir_para_t;

typedef struct {
  at_di_t linkId;
  at_di_t bufferlen;
  at_text_t *buffer;
  at_text_t hostname[AT_PARA_MAX_SIZE];
  at_di_t port;
} at_sendData_para_t;

typedef struct {
  at_config_t *cfg;
  at_status_t *sts;
  union {
    struct {
      char hostname[AT_PARA_MAX_SIZE];
    } ping;
    struct {
      s32 value;
    } wifi;
    struct {
      s32 method; /* 0: default 1: "a,r" 2: "p,r"*/
    } scan;
    at_tcpserver_para_t tcp_server;
    struct {
      s32 len; /* transparent transmission send buffer length */
      u8 *buf; /* transparent transmission send buffer */
    } mode;
    struct {
      int uartId;
      int uartBaud;
      int dataBit;
      int parity;
      int stopBit;
      int hwfc;
    } uart;
    struct {
      uint32_t sleep_time;
      int weakup_pin;
    } sleep;
    //struct{
    //    uint32_t sleep_time;
    //    int gpioId;
    //}wakeupgpio;
    struct {
      int mode;
    } wifiMode;
    struct {
      char ssid[33];
      char pwd[33];
    } joinParam;

    at_ip_para_t at_ip_para;

    struct {
      char ssid[64];
      char psk[64];
      int chl;
      int ecn;
      int max_conn;
      int hidden;
    } apcfgParam;
    struct {
      char hostname[33];
    } iphostname;
    struct {
      char hostname[128];
    } dns_parse;
    struct {
      char hostname[128];
      uint8_t type;
      uint8_t content_type;
      uint8_t *data;
    } http_req;
    struct {
      at_ip_t setdnsip;
    } set_dns;

    at_network_para_t net_param;
    at_sendData_para_t send_param;
    at_close_para_t close_id;
    at_client_ssl_path_para_t client_ssl_path_cfg;
    at_client_ssl_sni_t client_ssl_sni_cfg;
    at_client_ssl_alpn_t client_ssl_alpn_cfg;

    at_ble_sync_mode_t ble_sync_mode;

    struct {
      int ID;
      int mode;
      int pull;
    } setgpio_para;
    struct {
      int ID;
      int mode;
    } setiodir_para;
    struct {
      int ID;
      int data;
    } writeiodata_para;
    struct {
      int ID;
    } readiodata_para;
    struct {
      int apnum;
    } deleteap_para;
  } u;
} at_callback_para_t;

typedef struct
{
  u8 status;  // 0: empty, 1: carry msg
  s32 type;   /* 0: value 1: buffer pointer */
  void *vptr; /* value or buffer pointer */
  s32 vsize;
} at_callback_rsp_t __attribute__ ((deprecated));

typedef struct {
  AT_ERROR_CODE (*handle_cb)
  (AT_CALLBACK_CMD cmd, at_callback_para_t *para, at_callback_rsp_t *rsp);
  s32 (*dump_cb)(u8 *buf, s32 len);
} at_callback_t;

typedef struct {
  u32 baudrate;
  u32 dataBit;
  u32 parity;
  u32 stopBit;
  u32 hwfc;
} at_serial_para_t;

typedef struct {
  char *ptr;
} at_para_t;

typedef struct {
  const char *cmd;
  AT_ERROR_CODE (*handler)
  (at_para_t *at_para);
  const char *usage;
} at_command_handler_t;

typedef struct cmd_cache {
  u32 cnt;
  u8 buf[CMD_SEND_DATA_MAX_LEN];
} cmd_cache_t;

typedef struct cmd_send_cache {
  u32 status;
  u32 cnt;
  u32 linkID;
  u32 length;
  u8 hostname[AT_PARA_MAX_SIZE];
  u16 port;
  u8 buf[CMD_SEND_DATA_MAX_LEN];
} cmd_send_cache_t;

#define AT_CMD_ECHOSTART "\r\n"
#define AT_CMD_TAILED "\r\n"

#define SAVE_KEY_UART_BAUD "uart_baud"
#define SAVE_KEY_UART_DATABIT "databit"
#define SAVE_KEY_UART_STOPBIT "stopbit"
#define SAVE_KEY_UART_PARITY "parity"
#define SAVE_KEY_UART_HWFC "hwfc"
#define SAVE_KEY_WIFI_MODE "wifi_mode"
#define SAVE_KEY_WIFI_AUTO "wifi_auto"
#define SAVE_KEY_WIFI_SSID "wifi_ssid"
#define SAVE_KEY_WIFI_PASK "wifi_pask"
#define SAVE_KEY_UART_ECHO "uart_echo"
#define SAVE_KEY_WIFISCAN_OPT "scan_opt"
#define SAVE_KEY_IP           "ip"
#define SAVE_KEY_MASK         "mask"
#define SAVE_KEY_GW           "gw"
#define SAVE_KEY_DNS1         "dns1"
#define SAVE_KEY_DNS2         "dns2"

extern at_callback_t at_callback;
extern AT_ERROR_CODE at_init(at_callback_t *cb);
extern AT_ERROR_CODE at_parse(void);
extern s32 at_event(s32 idx);
extern s32 at_serial(at_serial_para_t *ppara);
extern s32 at_data_output(char *buf, int size);
extern s32 at_dump_noend(char *format, ...);
#define at_dump(...)                 \
  do {                               \
    at_dump_noend(AT_CMD_ECHOSTART); \
    at_dump_noend(__VA_ARGS__);      \
    at_dump_noend(AT_CMD_TAILED);    \
  } while (0)
extern u32 at_get_errorcode(void);
extern s32 atcmd_send(char *format, ...);
extern int get_reconnect_enable_status(void);
extern void set_reconnect_disable(void);

extern int at_key_value_get(char *key, void *p_value);
extern int at_key_value_set(char *key, void *p_value);

extern AT_ERROR_CODE at_command_register(const at_command_handler_t *cmd, uint32_t cmd_cnt);
extern AT_ERROR_CODE at_callback_do(AT_CALLBACK_CMD cmd, at_callback_para_t *para);

extern AT_ERROR_CODE at_status(char *sts_var);
extern AT_ERROR_CODE at_setsts(char *key, at_value_t *value);
extern AT_ERROR_CODE at_peer(s32 pn, at_peer_t *peer, char *var);
extern AT_ERROR_CODE at_get_parameters(char **ppara, at_para_descriptor_t *list,
                                       s32 lsize, s32 *pcnt);
extern void at_response(AT_ERROR_CODE aec);

extern AT_ERROR_CODE at_reset(void);
extern AT_ERROR_CODE at_help(void);
extern AT_ERROR_CODE at_scan(char *mode, char *repeat);
AT_ERROR_CODE close_network_handler(at_para_t *at_para);
AT_ERROR_CODE create_tcp_udp_handler(at_para_t *at_para);
AT_ERROR_CODE ap_server_handler(at_para_t *at_para);
AT_ERROR_CODE send_data_handler(at_para_t *at_para);
AT_ERROR_CODE client_ssl_config_path(at_para_t *at_para);
AT_ERROR_CODE client_ssl_set_sni(at_para_t *at_para);
AT_ERROR_CODE client_ssl_set_alpn(at_para_t *at_para);

extern AT_ERROR_CODE at_version(char *version);
extern AT_ERROR_CODE at_restore(char *address);
extern AT_ERROR_CODE at_uart_config_get(void);
extern AT_ERROR_CODE at_uart_config(int uartId, int uartBaud, int dataBit,
                                    int parity, int stopBit, int hwfc);

extern AT_ERROR_CODE at_deep_sleep_mode(uint32_t sleep_time, int weakup_pin);
extern AT_ERROR_CODE at_set_tcpserver(int port, int enable, int tls, int ca);
extern AT_ERROR_CODE at_wifi_mode(int wifiMode);
extern AT_ERROR_CODE at_wifi_mode_get(void);
extern AT_ERROR_CODE at_join_ap(char *ssid, char *pwd);
extern AT_ERROR_CODE at_get_apinfo(void);
extern AT_ERROR_CODE at_disconnect(char *at_para);

AT_ERROR_CODE at_get_ssid_psk(char **ppara, char *ssid, char *pwd);
extern AT_ERROR_CODE at_http_request(char* url, uint8_t type,
                                     uint8_t content_type, uint8_t *data,
                                     at_callback_rsp_t *req_rsp);
extern AT_ERROR_CODE at_set_ap(char *ssid, char *psk, char chl, int max_conn);
extern AT_ERROR_CODE at_ap_sta_get(void);
extern AT_ERROR_CODE at_close_network(int linkId);
extern AT_ERROR_CODE at_create_network_connect(at_network_para_t netpara,
                                               at_callback_rsp_t *rsp);
extern AT_ERROR_CODE at_send_data(at_sendData_para_t *param);
extern AT_ERROR_CODE at_network_status(char *param, at_callback_rsp_t *rsp);

extern AT_ERROR_CODE at_sta_ip(at_ip_t *ip, at_ip_t *netmask, at_ip_t *getway, at_ip_t *dns1, at_ip_t *dns2);
extern AT_ERROR_CODE at_sta_ip_get(void);
extern AT_ERROR_CODE at_ble_sync_mode(int mode);

#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#ifdef __cplusplus
}
#endif

#endif
