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

#include "cJSON.h"
#include "qcloud_iot_export_log.h"
#include "qcloud_iot_export_error.h"
#include "qcloud_iot_import.h"

#include "qcloud_wifi_config.h"
#include "qcloud_wifi_config_internal.h"

/************** WiFi config error msg collect and post feature ******************/

#define LOG_QUEUE_SIZE 10
#define LOG_ITEM_SIZE  128

#define LOG_SERVER_TASK_NAME        "log_server_task"
#define LOG_SERVER_TASK_STACK_BYTES 4096
#define LOG_SERVER_TASK_PRIO        1

/* msg queue */
#if WIFI_LOG_UPLOAD
static void *sg_dev_log_queue = NULL;
static bool  sg_log_task_run  = false;
#endif

int init_dev_log_queue(void)
{
#if WIFI_LOG_UPLOAD
    if (sg_dev_log_queue) {
        Log_d("re-enter, reset queue");
        HAL_QueueReset(sg_dev_log_queue);
        return 0;
    }

    sg_dev_log_queue = HAL_QueueCreate(LOG_QUEUE_SIZE, LOG_ITEM_SIZE);
    if (sg_dev_log_queue == NULL) {
        Log_e("xQueueCreate failed");
        return ERR_OS_QUEUE;
    }
#endif
    return 0;
}

void delete_dev_log_queue(void)
{
#if WIFI_LOG_UPLOAD
    HAL_QueueDestory(sg_dev_log_queue);
    sg_dev_log_queue = NULL;
#endif
}

int push_dev_log(const char *func, const int line, const char *fmt, ...)
{
#if WIFI_LOG_UPLOAD
    if (sg_dev_log_queue == NULL) {
        Log_e("log queue not initialized!");
        return ERR_OS_QUEUE;
    }

    char log_buf[LOG_ITEM_SIZE];
    memset(log_buf, 0, LOG_ITEM_SIZE);

    // only keep the latest LOG_QUEUE_SIZE log
    uint32_t log_cnt = (uint32_t)HAL_QueueItemWaitingCount(sg_dev_log_queue);
    if (log_cnt == LOG_QUEUE_SIZE) {
        // pop the oldest one
        HAL_QueueItemPop(sg_dev_log_queue, log_buf, 0);
        HAL_Printf("<<< POP LOG: %s", log_buf);
    }

    char *o = log_buf;
    memset(log_buf, 0, LOG_ITEM_SIZE);
    o += HAL_Snprintf(o, LOG_ITEM_SIZE, "%u|%s(%d): ", HAL_GetTimeMs(), func, line);

    va_list ap;
    va_start(ap, fmt);
    HAL_Vsnprintf(o, LOG_ITEM_SIZE - 3 - strlen(log_buf), fmt, ap);
    va_end(ap);

    strcat(log_buf, "\r\n");

    /* unblocking send */
    int ret = HAL_QueueItemPush(sg_dev_log_queue, log_buf, 0);
    if (ret != QCLOUD_RET_SUCCESS) {
        Log_e("HAL_QueueItemPush failed: %d", ret);
        return ERR_OS_QUEUE;
    }
#endif
    return 0;
}

int app_send_dev_log(comm_peer_t *peer)
{
    int ret = 0;
#if WIFI_LOG_UPLOAD

    if (sg_dev_log_queue == NULL) {
        Log_e("log queue not initialized!");
        return ERR_OS_QUEUE;
    }

    uint32_t log_cnt = (uint32_t)HAL_QueueItemWaitingCount(sg_dev_log_queue);
    if (log_cnt == 0)
        return 0;

    size_t max_len  = (log_cnt * LOG_ITEM_SIZE) + 32;
    char * json_buf = HAL_Malloc(max_len);
    if (json_buf == NULL) {
        Log_e("malloc failed!");
        return -1;
    }

    memset(json_buf, 0, max_len);

    char log_buf[LOG_ITEM_SIZE];
    int  rc;
    do {
        memset(log_buf, 0, LOG_ITEM_SIZE);
        rc = HAL_QueueItemPop(sg_dev_log_queue, log_buf, 0);
        if (rc == QCLOUD_RET_SUCCESS) {
            strcat(json_buf, log_buf);
        }
    } while (rc == QCLOUD_RET_SUCCESS);

    HAL_Printf("to reply: %s\r\n", json_buf);

    int i = 0;
    for (i = 0; i < 2; i++) {
        ret =
            HAL_UDP_WriteTo(peer->socket_id, (unsigned char *)json_buf, strlen(json_buf), peer->peer_addr, peer->port);
        if (ret < 0) {
            Log_e("send error: %s", HAL_UDP_GetErrnoStr());
            break;
        }
        HAL_SleepMs(500);
    }
    HAL_Free(json_buf);

#endif
    return ret;
}

#if WIFI_LOG_UPLOAD
static void log_server_task(void *pvParameters)
{
    int  ret, server_socket = -1;
    char rx_buffer[256] = {0};

    /* stay 6 minutes to handle log */
    uint32_t server_count = 360 / SELECT_WAIT_TIME_SECONDS;

    server_socket = HAL_UDP_CreateBind("0.0.0.0", LOG_SERVER_PORT);

    Log_i("LOG server socket waiting recv msg...");
    char           peer_client_addr[128] = {0};
    unsigned short peer_client_port      = 0;
    comm_peer_t    peer                  = {0};

    int select_err_cnt = 0;
    while (sg_log_task_run && --server_count) {
        int len = HAL_UDP_ReadTimeoutPeerInfo(server_socket, (unsigned char *)rx_buffer, sizeof(rx_buffer) - 1,
                                              SELECT_WAIT_TIME_SECONDS * 1000, peer_client_addr,
                                              sizeof(peer_client_addr), &peer_client_port);
        // Error occured during receiving
        if (len > 0) {
            select_err_cnt = 0;
            // Get the sender's ip address as string
            rx_buffer[len] = '0';

            Log_i("Received %d bytes from <%s:%u> msg: %s", len, peer_client_addr, peer_client_port, rx_buffer);

            if (strncmp(rx_buffer, "{\"cmdType\":3}", 12) == 0) {
                peer.socket_id = server_socket;
                peer.peer_addr = peer_client_addr;
                peer.port      = peer_client_port;
                ret            = app_send_dev_log(&peer);
                Log_i("app_send_dev_log ret: %d", ret);
                break;
            }

        } else if (0 == len) {
            select_err_cnt = 0;
            Log_d("wait for read...");
            continue;
        } else {
            select_err_cnt++;
            Log_w("select-recv error: %d, cnt: %d, ret: %d", HAL_UDP_GetErrno(), select_err_cnt, len);
            HAL_SleepMs(500);
        }
    }

    if (server_socket != -1) {
        Log_w("close LOG server socket");
        HAL_UDP_Close(server_socket);
    }

    stop_device_softAP();

    sg_log_task_run = false;
    Log_i("LOG server task quit");
}
#endif

int qiot_log_service_start(void)
{
#if WIFI_LOG_UPLOAD
    sg_log_task_run = true;
    static ThreadParams params;
    params.thread_func = log_server_task;
    params.thread_name = LOG_SERVER_TASK_NAME;
    params.stack_size  = LOG_SERVER_TASK_STACK_BYTES;
    params.priority    = LOG_SERVER_TASK_PRIO;
    params.user_arg    = NULL;
    int ret            = HAL_ThreadCreate(&params);

    if (ret != QCLOUD_RET_SUCCESS) {
        Log_e("create log_server_task failed: %d", ret);
        PUSH_LOG("create log_server_task failed: %d", ret);
        push_error_log(ERR_OS_TASK, ret);
        sg_log_task_run = false;
        return QCLOUD_ERR_FAILURE;
    }
#endif
    return QCLOUD_RET_SUCCESS;
}

void qiot_log_service_stop(void)
{
#if WIFI_LOG_UPLOAD
    sg_log_task_run = false;
#endif
}
