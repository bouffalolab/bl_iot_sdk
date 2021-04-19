/*
 * Copyright (c) 2020 Tencent Cloud. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <string.h>
#include <stdint.h>

#include "cJSON.h"
#include "qcloud_iot_export_log.h"
#include "qcloud_iot_export_error.h"
#include "qcloud_iot_import.h"

#include "qcloud_wifi_config.h"
#include "qcloud_wifi_config_internal.h"

/************** WiFi config error msg collect and post feature ******************/

#if WIFI_ERR_LOG_POST

static const char *g_err_log[] = {
    "Everything OK!",               /* SUCCESS_TYPE = 0,*/
    "MQTT connect error!",          /* ERR_MQTT_CONNECT = 1, */
    "APP command error!",           /* ERR_APP_CMD = 2,*/
    "WIFI boarding stop!",          /* ERR_BD_STOP = 3,*/
    "RTOS task error!",             /* ERR_OS_TASK = 4,*/
    "RTOS queue error!",            /* ERR_OS_QUEUE = 5,*/
    "WIFI STA init error!",         /* ERR_WIFI_STA_INIT = 6,*/
    "WIFI AP init error!",          /* ERR_WIFI_AP_INIT = 7,*/
    "WIFI start error!",            /* ERR_WIFI_START = 8,*/
    "WIFI config error!",           /* ERR_WIFI_CONFIG = 9,*/
    "WIFI connect error!",          /* ERR_WIFI_CONNECT = 10,*/
    "WIFI disconnect error!",       /* ERR_WIFI_DISCONNECT = 11,*/
    "WIFI AP STA error!",           /* ERR_WIFI_AP_STA = 12,*/
    "ESP smartconfig start error!", /* ERR_SC_START = 13,*/
    "ESP smartconfig data error!",  /* ERR_SC_DATA = 14, */
    "SRV socket open error!",       /* ERR_SOCKET_OPEN = 15,*/
    "SRV socket bind error!",       /* ERR_SOCKET_BIND = 16,*/
    "SRV socket listen error!",     /* ERR_SOCKET_LISTEN = 17,*/
    "SRV socket fcntl error!",      /* ERR_SOCKET_FCNTL = 18,*/
    "SRV socket accept error!",     /* ERR_SOCKET_ACCEPT = 19,*/
    "SRV socket recv error!",       /* ERR_SOCKET_RECV = 20,*/
    "SRV socket select error!",     /* ERR_SOCKET_SELECT = 21,*/
    "SRV socket send error!",       /* ERR_SOCKET_SEND = 22,*/
    "MQTT Token send error!",       /* ERR_TOKEN_SEND = 23,*/
    "MQTT Token reply error!",      /* ERR_TOKEN_REPLY = 24,*/
};

typedef struct {
    uint8_t  record;
    uint8_t  reserved;
    uint16_t err_id;     /* error msg Id */
    int32_t  err_sub_id; /* error msg sub Id */
} err_log_t;

typedef struct {
    uint32_t  magic_header; /* VALID_MAGIC_CODE for valid info */
    uint32_t  log_cnt;
    err_log_t err_log[0];
} save_err_log_t;

#define ERR_LOG_QUEUE_SIZE 16
#define VALID_MAGIC_CODE   0xF00DBEEF

/* FreeRTOS msg queue */
static void *g_err_log_queue = NULL;

static int check_err_log(uint32_t *log_cnt)
{
    int      ret;
    uint32_t header, msg_cnt;
    ret = HAL_Wifi_read_err_log(0, (uint32_t *)&header, sizeof(uint32_t));
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e(" wifi log read error: %d", ret);
        return (int)ret;
    }

    /* not a valid log */
    if (header != VALID_MAGIC_CODE) {
        Log_i("invalid magic code: 0x%x", header);
        return 0;
    }

    ret = HAL_Wifi_read_err_log(sizeof(uint32_t), (uint32_t *)&msg_cnt, sizeof(uint32_t));
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("wifi log read error: %d", ret);
        return (int)ret;
    }

    *log_cnt = msg_cnt;
    return 0;
}

static int load_err_log(void *log, size_t log_size)
{
    int    ret;
    size_t log_offset = 2 * sizeof(uint32_t);
    ret               = HAL_Wifi_read_err_log(log_offset, (uint32_t *)log, log_size);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("wifi log read error: %d", ret);
        return ret;
    }

    return 0;
}

static int save_err_log(void *log, size_t log_size)
{
    int ret;

    ret = HAL_Wifi_write_err_log(0, (uint32_t *)log, log_size);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("wifi log write error: %d", ret);
        return ret;
    }

    return 0;
}

static int clear_err_log(void)
{
    return HAL_Wifi_clear_err_log();
}

int handle_saved_error_log(void)
{
    uint32_t log_cnt = 0;
    if (check_err_log(&log_cnt)) {
        Log_e("check error log cnt failed");
        return -1;
    }

    if (log_cnt == 0)
        return 0;

    if (log_cnt > ERR_LOG_QUEUE_SIZE) {
        Log_e("invalid log cnt: %u", log_cnt);
        return -1;
    }

    size_t     log_size = log_cnt * sizeof(err_log_t);
    err_log_t *log_src  = (err_log_t *)HAL_Malloc(log_size);
    if (log_src == NULL) {
        Log_e("malloc failed");
        return -1;
    }

    if (load_err_log(log_src, log_size)) {
        HAL_Free(log_src);
        Log_e("load error log failed");
        return -1;
    }

    clear_err_log();

    uint32_t i = 0;
    do {
        /* change the record type to previous error */
        log_src[i].record = PRE_ERR;
        Log_i("Handle Previous Error: %s (%u, %d)", g_err_log[log_src[i].err_id], log_src[i].err_id,
              log_src[i].err_sub_id);

        /* unblocking send */
        int ret = HAL_QueueItemPush(g_err_log_queue, &log_src[i], 0);
        if (ret != QCLOUD_RET_SUCCESS) {
            Log_e("xQueueGenericSend failed: %d", ret);
            HAL_Free(log_src);
            return ERR_OS_QUEUE;
        }
        i++;
    } while (i < log_cnt);

    HAL_Free(log_src);
    return 0;
}

#endif  // WIFI_ERR_LOG_POST

// error happen flag
static bool sg_error_happen = false;

int init_error_log_queue(void)
{
    sg_error_happen = false;

#if WIFI_ERR_LOG_POST
    if (g_err_log_queue) {
        Log_d("re-enter, reset queue");
        HAL_QueueReset(g_err_log_queue);
        return 0;
    }

    g_err_log_queue = HAL_QueueCreate(ERR_LOG_QUEUE_SIZE, sizeof(err_log_t));
    if (g_err_log_queue == NULL) {
        Log_e("HAL_QueueCreate failed");
        return ERR_OS_QUEUE;
    }

    handle_saved_error_log();
#endif

    return 0;
}

int push_error_log(uint16_t err_id, int32_t err_sub_id)
{
    sg_error_happen = true;

#if WIFI_ERR_LOG_POST
    if (g_err_log_queue == NULL) {
        Log_e("log queue not initialized and push_error_log called");
        return ERR_OS_QUEUE;
    }

    err_log_t err_log = {.record = CUR_ERR, .err_id = err_id, .err_sub_id = err_sub_id};
    Log_e("Boarding error happen: %s (%u, %d)", g_err_log[err_log.err_id], err_log.err_id, err_log.err_sub_id);
    /* unblocking send */
    int ret = HAL_QueueItemPush(g_err_log_queue, &err_log, 0);
    if (ret != QCLOUD_RET_SUCCESS) {
        Log_e("HAL_QueueItemPush failed: %d", ret);
        return ERR_OS_QUEUE;
    }
#else
    Log_e("error happen, err_id: %u err_sub_id: %d", err_id, err_sub_id);
#endif
    return 0;
}

bool is_config_error_happen(void)
{
    return sg_error_happen;
}

int app_send_error_log(comm_peer_t *peer, uint8_t record, uint16_t err_id, int32_t err_sub_id)
{
#if WIFI_ERR_LOG_POST
    int  ret;
    char msg_str[64]   = {0};
    //char json_str[128] = {0};
    char *json_str=NULL;
    HAL_Snprintf(msg_str, sizeof(msg_str), "%s (%u, %d)", g_err_log[err_id], err_id, err_sub_id);

    cJSON *reply_json = cJSON_CreateObject();
    cJSON_AddNumberToObject(reply_json, "cmdType", (int)CMD_DEVICE_REPLY);
    cJSON_AddStringToObject(reply_json, "deviceReply", record == CUR_ERR ? "Current_Error" : "Previous_Error");
    cJSON_AddStringToObject(reply_json, "log", msg_str);
    #if 0
    if (0 == cJSON_PrintPreallocated(reply_json, json_str, sizeof(json_str), 0)) {
        Log_e("cJSON_PrintPreallocated failed!");
        cJSON_Delete(reply_json);
        return -1;
    }
    #endif
    json_str= cJSON_Print(reply_json);
    if (!json_str) 
    {
        Log_e("cJSON_PrintPreallocated failed!");
        cJSON_Delete(reply_json);
        app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ERR_JSON_PRINT);
        return -1;
    }
    /* append msg delimiter */
    strcat(json_str, "\r\n");

    ret = HAL_UDP_WriteTo(peer->socket_id, (unsigned char *)json_str, strlen(json_str), peer->peer_addr, peer->port);
    if (ret < 0) {
        Log_e("send error: %s", HAL_UDP_GetErrnoStr());
    } else
        Log_w("send error msg: %s", json_str);

    cJSON_Delete(reply_json);
    return ret;
#else
    return 0;
#endif
}

int get_and_post_error_log(comm_peer_t *peer)
{
    int err_cnt = 0;
#if WIFI_ERR_LOG_POST
    err_log_t err_msg;
    int       rc = QCLOUD_RET_SUCCESS;
    do {
        if (QCLOUD_RET_SUCCESS == (rc = HAL_QueueItemPop(g_err_log_queue, &err_msg, 0))) {
            app_send_error_log(peer, err_msg.record, err_msg.err_id, err_msg.err_sub_id);
            if (err_msg.record == CUR_ERR)
                err_cnt++;
        }
    } while (rc == QCLOUD_RET_SUCCESS);
#endif
    return err_cnt;
}

int save_error_log(void)
{
#if WIFI_ERR_LOG_POST
    int      rc      = QCLOUD_RET_SUCCESS;
    uint32_t log_cnt = (uint32_t)HAL_QueueItemWaitingCount(g_err_log_queue);
    if (log_cnt == 0)
        return 0;

    size_t          log_size = 2 * sizeof(uint32_t) + log_cnt * sizeof(err_log_t);
    save_err_log_t *log_src  = (save_err_log_t *)HAL_Malloc(log_size);
    if (log_src == NULL) {
        Log_e("malloc failed");
        return -1;
    }

    uint32_t i = 0, j = 0;
    do {
        if (QCLOUD_RET_SUCCESS == (rc = HAL_QueueItemPop(g_err_log_queue, &log_src->err_log[i], 0))) {
            /* only save current error */
            if (log_src->err_log[i].record == CUR_ERR) {
                Log_w("Save unhandled Current Error %u: %s (%u, %d)", j + 1, g_err_log[log_src->err_log[i].err_id],
                      log_src->err_log[i].err_id, log_src->err_log[i].err_sub_id);
                j++;
            } else {
                Log_w("Discard Previous Error: %s (%u, %d)", g_err_log[log_src->err_log[i].err_id],
                      log_src->err_log[i].err_id, log_src->err_log[i].err_sub_id);
            }
            i++;
        }
    } while (i < log_cnt && rc == QCLOUD_RET_SUCCESS);

    HAL_QueueDestory(g_err_log_queue);

    log_src->magic_header = VALID_MAGIC_CODE;
    log_src->log_cnt      = j;
    log_size              = 2 * sizeof(uint32_t) + log_src->log_cnt * sizeof(err_log_t);
    if (log_size != save_err_log(log_src, log_size)) {
        HAL_Free(log_src);
        Log_e("save error log to flash failed");
        return -1;
    }
    HAL_Free(log_src);
#endif
    return 0;
}
