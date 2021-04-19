
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

#include "cJSON.h"

#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"

#include "qcloud_wifi_config.h"
#include "qcloud_wifi_config_internal.h"

static bool sg_comm_task_run = false;

static int _app_reply_dev_info(comm_peer_t *peer)
{
    int         ret;
    DeviceInfo  devinfo;
    cJSON_Hooks memoryHook;

    memoryHook.malloc_fn = (void *(*)(size_t))HAL_Malloc;
    memoryHook.free_fn   = (void (*)(void *))HAL_Free;
    cJSON_InitHooks(&memoryHook);

    ret = HAL_GetDevInfo(&devinfo);
    if (ret) {
        Log_e("load dev info failed: %d", ret);
        app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ret);
        return -1;
    }

    cJSON *reply_json = cJSON_CreateObject();
    cJSON_AddNumberToObject(reply_json, "cmdType", (int)CMD_DEVICE_REPLY);
    cJSON_AddStringToObject(reply_json, "productId", devinfo.product_id);
    cJSON_AddStringToObject(reply_json, "deviceName", devinfo.device_name);
    cJSON_AddStringToObject(reply_json, "protoVersion", SOFTAP_BOARDING_VERSION);
    char *json_str=NULL;
    json_str= cJSON_Print(reply_json);
    if (!json_str) {
        Log_e("cJSON_PrintPreallocated failed!");
        cJSON_Delete(reply_json);
        app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ERR_JSON_PRINT);
        return -1;
    }
    /* append msg delimiter */
    //    strcat(json_str, "\r\n");
    cJSON_Delete(reply_json);
    HAL_Printf("Report dev info(%d): %s", strlen(json_str), json_str);

    int udp_resend_cnt = 3;
udp_resend:
    ret = HAL_UDP_WriteTo(peer->socket_id, (unsigned char *)json_str, strlen(json_str), peer->peer_addr, peer->port);
    if (ret < 0) {
        HAL_Free(json_str);
        Log_e("send error: %s", HAL_UDP_GetErrnoStr());
        push_error_log(ERR_SOCKET_SEND, HAL_UDP_GetErrno());
        return -1;
    }
    /* UDP packet could be lost, send it again */
    /* NOT necessary for TCP */
    if (peer->peer_addr != NULL && --udp_resend_cnt) {
        HAL_SleepMs(1000);
        goto udp_resend;
    }

    HAL_Printf("Report dev info: %s", json_str);
    HAL_Free(json_str);
    return 0;
}

#if 0
static int _app_reply_auth_reqinfo(comm_peer_t *peer)
{
    int ret;
    cJSON_Hooks memoryHook;

    memoryHook.malloc_fn = HAL_Malloc;
    memoryHook.free_fn   = HAL_Free;
    cJSON_InitHooks(&memoryHook);

	char tvs_productId[MAX_SIZE_OF_TVS_PRODUCT_ID + 1] = {0};
    char tvs_dsn[MAX_SIZE_OF_TVS_DEVICE_NAME + 1] = {0};
	HAL_GetTvsInfo(tvs_productId, tvs_dsn);
	
    cJSON *reply_json = cJSON_CreateObject();
    cJSON_AddNumberToObject(reply_json, "cmdType", (int)CMD_AUTHINFO_REPLY);
    cJSON_AddStringToObject(reply_json, "pid", tvs_productId);	
    cJSON_AddStringToObject(reply_json, "dsn", tvs_dsn);

	char authReqInfos[150] = {0};
	tvs_authorize_manager_build_auth_req(authReqInfos,sizeof(authReqInfos));
    cJSON_AddStringToObject(reply_json, "authReqInfo", authReqInfos);

    char *json_str = cJSON_Print(reply_json);
    if (!json_str) {
        Log_e("cJSON_PrintPreallocated failed!");
        cJSON_Delete(reply_json);
        app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ERR_JSON_PRINT);
        return -1;
    }
    /* append msg delimiter */
//    strcat(json_str, "\r\n");
    cJSON_Delete(reply_json);
	HAL_Printf("Reply auth reqinfo(%d): %s", strlen(json_str), json_str);

    int udp_resend_cnt = 3;
udp_resend:
    ret = HAL_UDP_WriteTo(peer->socket_id, json_str, strlen(json_str), peer->peer_addr , peer->port);
    if (ret < 0) {
        HAL_Free(json_str);
        Log_e("send error: %s", HAL_UDP_GetErrnoStr());
        push_error_log(ERR_SOCKET_SEND, HAL_UDP_GetErrno());
        return -1;
    }
    /* UDP packet could be lost, send it again */
    /* NOT necessary for TCP */
    if (peer->peer_addr != NULL && --udp_resend_cnt) {
        HAL_SleepMs(1000);
        goto udp_resend;
    }

    HAL_Printf("Reply auth reqinfo: %s", json_str);
    HAL_Free(json_str);
    return 0;
}
#endif

static int _app_handle_recv_data(comm_peer_t *peer, char *pdata, int len)
{
    int    ret  = 0;
    cJSON *root = cJSON_Parse(pdata);
    if (!root) {
        Log_e("Parsing JSON Error: [%s]", cJSON_GetErrorPtr());
        app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ERR_APP_CMD_JSON_FORMAT);
        return -1;
    }

    cJSON *cmd_json = cJSON_GetObjectItem(root, "cmdType");
    if (cmd_json == NULL) {
        Log_e("Invalid cmd JSON: %s", pdata);
        cJSON_Delete(root);
        app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ERR_APP_CMD_JSON_FORMAT);
        return -1;
    }

    int cmd = cmd_json->valueint;
    switch (cmd) {
        /* Token only for simple config  */
        case CMD_TOKEN_ONLY: {
            cJSON *token_json = cJSON_GetObjectItem(root, "token");
            if (token_json) {
                // set device bind token
                qiot_device_bind_set_token(token_json->valuestring);
                ret = _app_reply_dev_info(peer);

                // sleep a while before exit
                HAL_SleepMs(1000);

                /* 0: need to wait for next cmd
                 * 1: Everything OK and we've finished the job */
                return (ret == 0);
            } else {
                cJSON_Delete(root);
                Log_e("invlaid token!");
                app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ERR_APP_CMD_AP_INFO);
                return -1;
            }
        } break;

            /* SSID/PW/TOKEN for softAP */
        case CMD_SSID_PW_TOKEN: {
            cJSON *ssid_json  = cJSON_GetObjectItem(root, "ssid");
            cJSON *psw_json   = cJSON_GetObjectItem(root, "password");
            cJSON *token_json = cJSON_GetObjectItem(root, "token");

            if (ssid_json && psw_json && token_json) {
                // parse token and connect to ap
                qiot_device_bind_set_token(token_json->valuestring);
                _app_reply_dev_info(peer);
                // sleep a while before changing to STA mode
                HAL_SleepMs(3000);

                Log_i("STA to connect SSID:%s PASSWORD:%s", ssid_json->valuestring, psw_json->valuestring);
                PUSH_LOG("SSID:%s|PSW:%s|TOKEN:%s", ssid_json->valuestring, psw_json->valuestring,
                         token_json->valuestring);
                ret = HAL_Wifi_StaConnect(ssid_json->valuestring, psw_json->valuestring, 0);
                if (ret) {
                    Log_e("wifi_sta_connect failed: %d", ret);
                    PUSH_LOG("wifi_sta_connect failed: %d", ret);
                    app_send_error_log(peer, CUR_ERR, ERR_WIFI_AP_STA, ret);
                    cJSON_Delete(root);
#if WIFI_PROV_SOFT_AP_ENABLE
                    set_soft_ap_config_result(WIFI_CONFIG_FAIL);
#endif
                    return -1;
                } else {
                    Log_d("wifi_sta_connect success");
#if WIFI_PROV_SOFT_AP_ENABLE
                    set_soft_ap_config_result(WIFI_CONFIG_SUCCESS);
#endif
                }
                cJSON_Delete(root);

                /* return 1 as device alreay switch to STA mode and unable to recv cmd anymore
                 * 1: Everything OK and we've finished the job */
                return 1;
            } else {
                cJSON_Delete(root);
                Log_e("invlaid ssid/password/token!");
                app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ERR_APP_CMD_AP_INFO);
                return -1;
            }
        } break;

        case CMD_LOG_QUERY:
            ret = app_send_dev_log(peer);
            Log_i("app_send_dev_log ret: %d", ret);
            return 1;

        case CMD_AUTHINFO_QUERY:
            // ret = _app_reply_auth_reqinfo(peer);
            Log_i("_app_reply_auth_reqinfo ret: %d", ret);
            return ret;

        default: {
            cJSON_Delete(root);
            Log_e("Unknown cmd: %d", cmd);
            app_send_error_log(peer, CUR_ERR, ERR_APP_CMD, ERR_APP_CMD_JSON_FORMAT);
        } break;
    }

    return -1;
}

static void _qiot_comm_service_task(void *pvParameters)
{
    int         ret, server_socket = -1;
    char        addr_str[128]   = {0};
    char        rx_buffer[1024] = {0};
    comm_peer_t peer_client     = {0};

    int select_err_cnt = 0;

    /* stay longer than 5 minutes to handle error log */
    uint32_t server_count = WAIT_CNT_5MIN_SECONDS / SELECT_WAIT_TIME_SECONDS + 5;

    server_socket = HAL_UDP_CreateBind("0.0.0.0", APP_SERVER_PORT);
    if (server_socket < 0) {
        Log_e("Unable to create socket: errno %d", HAL_UDP_GetErrno());
        push_error_log(ERR_SOCKET_OPEN, HAL_UDP_GetErrno());
        goto end_of_task;
    }

    Log_i("UDP server socket listening...");

    while (sg_comm_task_run && --server_count) {
        ret =
            HAL_UDP_ReadTimeoutPeerInfo(server_socket, (unsigned char *)rx_buffer, sizeof(rx_buffer) - 1,
                                        SELECT_WAIT_TIME_SECONDS * 1000, addr_str, sizeof(addr_str), &peer_client.port);
        if (ret > 0) {
            select_err_cnt = 0;
            // Get the sender's ip address as string
            peer_client.socket_id = server_socket;
            peer_client.peer_addr = addr_str;

            rx_buffer[ret] = '\0';
            Log_i("Received %d bytes from <%s:%u> msg: %s", ret, peer_client.peer_addr, peer_client.port, rx_buffer);

            // send error log here, otherwise no chance for previous error
            get_and_post_error_log(&peer_client);

            ret = _app_handle_recv_data(&peer_client, rx_buffer, ret);
            if (ret == 1) {
                Log_w("Finish app cmd handling.");
                break;
            }

            get_and_post_error_log(&peer_client);
            continue;
        } else if (0 == ret) {
            select_err_cnt = 0;
            Log_d("wait for read...");
            if (peer_client.peer_addr != NULL) {
                get_and_post_error_log(&peer_client);
            }
            continue;
        } else {
            select_err_cnt++;
            Log_w("select-recv error: %d, cnt: %d", HAL_UDP_GetErrno(), select_err_cnt);
            if (select_err_cnt > 3) {
                Log_e("select-recv error: %d, cnt: %d", HAL_UDP_GetErrno(), select_err_cnt);
                push_error_log(ERR_SOCKET_SELECT, HAL_UDP_GetErrno());
                break;
            }
            HAL_SleepMs(500);
        }
    }

end_of_task:
    if (server_socket != -1) {
        Log_w("Shutting down UDP server socket");
        HAL_UDP_Close(server_socket);
    }

    sg_comm_task_run = false;
    Log_i("UDP server task quit");
}

int qiot_comm_service_start(void)
{
    sg_comm_task_run = true;

    static ThreadParams params;
    params.thread_func = _qiot_comm_service_task;
    params.thread_name = COMM_SERVER_TASK_NAME;
    params.stack_size  = COMM_SERVER_TASK_STACK_BYTES;
    params.priority    = COMM_SERVER_TASK_PRIO;
    params.user_arg    = NULL;
    int ret            = HAL_ThreadCreate(&params);

    if (ret != QCLOUD_RET_SUCCESS) {
        Log_e("create comm_server_task failed: %d", ret);
        PUSH_LOG("create comm_server_task failed: %d", ret);
        push_error_log(ERR_OS_TASK, ret);
        return -1;
    }

    return 0;
}

void qiot_comm_service_stop(void)
{
    sg_comm_task_run = false;
}
