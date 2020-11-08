#ifndef _AT_SERVER_H_
#define _AT_SERVER_H_

#include <FreeRTOS.h>
#include <event_groups.h>
#include <atcmd/at_command.h>
#include "atcmd/at_command.h"
#include "at_private.h"

#define AT_UART_ID   1

typedef enum {
    AT_ASYNC_WIFI_CONNECTED = 1,
    AT_ASYNC_DATA_IN,
    AT_ASYNC_PSK_ERROR,
    AT_ASYNC_NO_AP_FOUND,
    AT_WIFI_DISCONNECT,
    AT_WIFI_PRVO_DUMP,
    AT_BLE_CONNECTED,
    AT_BLE_DISCONNECTED,
    AT_WIFI_IP_GET,
} at_evt_t;

#define ATCMDSEND_MAX_BUFF_SIZE (1024)

#if 0
// CA
extern uint8_t *ca;
extern size_t ca_length;

// cert
extern uint8_t *cert;
extern size_t cert_len;
extern uint8_t *priv_key;
extern size_t priv_key_len;
extern uint8_t *priv_key_pwd;
extern size_t pirv_key_pwd_len;
#endif

typedef struct at_sever {
    int wifi_mode;
    uint32_t uart_baud;
    int at_serial_fd;
    SemaphoreHandle_t at_serial_mtx;
    QueueHandle_t xQueue;
    uint8_t queue_buf[ATCMDSEND_MAX_BUFF_SIZE];
} at_sever_t;

int at_server_init(void);
int at_server_notify(at_evt_t event);

#define AT_EV_CTX_NUMS_MAX    4
#define AT_EV_CTX_BYTES_MAX   20
int at_server_notify_with_ctx(at_evt_t event, void *p_ctx, uint32_t ctx_size);

int at_serial_open(void);
int at_serial_close(void);
int at_key_value_set(char *key, void *p_value);
int at_key_value_get(char *key, void *p_value);
int at_serial_lock(void);
int at_serial_unlock(void);

int at_serial_cfg_set(uint32_t baud, uint8_t data_bit, uint8_t stop_bit, uint8_t parity, uint8_t hwfc);

#endif

