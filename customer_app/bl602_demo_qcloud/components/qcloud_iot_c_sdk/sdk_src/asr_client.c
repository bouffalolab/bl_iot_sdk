/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file
 except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software
 distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND,
 * either express or implied. See the License for the specific language
 governing permissions and
 * limitations under the License.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "qcloud_iot_export.h"
#include "qutils_param_check.h"
#include "qutils_timer.h"
#include "qutils_list.h"
#include "json_parser.h"
#include "asr_client.h"

#define RESOURCE_TOKEN    "resource_token"
#define REQUEST_ID        "request_id"
#define KEY_ASR_RESULT    "result_code"
#define KEY_ASR_TOKEN     "resource_token"
#define KEY_ASR_TEXT_SEGS "total_num"
#define KEY_ASR_TEXT_SEQ  "seq"
#define KEY_ASR_TEXT      "res_text"
#define ONE_PARA_STR_LEN  (25)

#define ASR_RESPONSE_PROPERTY_KEY       "_sys_asr_response"
#define ASR_SYS_PROPERTY_BUFFF_LEN		2048
#define TOTAL_ASR_SYS_PROPERTY_COUNT 	1

typedef struct _AsrHandle_ {
    void *                        resource_handle;
    OnAsrResourceEventUsrCallback usrCb;
    void *                        mutex;
    List *                        asr_req_list;
} AsrHandle;

typedef struct _AsrReq_ {
    eAsrType req_type;
    int request_id;

    Timer         timer;
    uint32_t      request_timeout_ms;
    OnAsrResultCB result_cb;
    char *        asr_token;
    union {
        RecordAsrConf   record_conf;
        RealTimeAsrConf realtime_conf;
    };
} AsrReq;

typedef struct _ASR_SYS_PROPERTY {
    TYPE_DEF_TEMPLATE_STRING m_asr_response[ASR_SYS_PROPERTY_BUFFF_LEN + 1];
} ASR_SYS_PROPERTY;

static   ASR_SYS_PROPERTY     sg_asr_property;
static 	 sDataPoint    		  sg_asr_data[TOTAL_ASR_SYS_PROPERTY_COUNT];
static   void         		  *sg_asr_client = NULL;

int _asr_result_notify(void *handle, char *asr_response);

static void _init_asr_property()
{
    sg_asr_property.m_asr_response[0] = '\0';
    sg_asr_data[0].data_property.data = sg_asr_property.m_asr_response;
    sg_asr_data[0].data_property.data_buff_len = ASR_SYS_PROPERTY_BUFFF_LEN;
    sg_asr_data[0].data_property.key  = ASR_RESPONSE_PROPERTY_KEY;
    sg_asr_data[0].data_property.type = TYPE_TEMPLATE_STRING;
    sg_asr_data[0].state = eNOCHANGE;
};

static void _OnAsrControlMsgCallback(void *pTemplate_client, const char *pJsonValueBuffer, uint32_t valueLength,
                                     DeviceProperty *pProperty)
{
	if(!strcmp(pProperty->key, ASR_RESPONSE_PROPERTY_KEY)) {
		LITE_string_strip_char((char *)pProperty->data, '\\');		
		int rc = _asr_result_notify(sg_asr_client, (char *)pProperty->data);
		if(QCLOUD_RET_SUCCESS != rc) {
			Log_e("asr result notify fail, err:%d", rc);
		}
	}
}

static int _register_asr_property(void *pTemplate_client)
{
    int i, rc;
	
	_init_asr_property();
    for (i = 0; i < TOTAL_ASR_SYS_PROPERTY_COUNT; i++) {
        rc = IOT_Template_Register_Property(pTemplate_client, &sg_asr_data[i].data_property, _OnAsrControlMsgCallback);
        if (rc != QCLOUD_RET_SUCCESS) {
            return rc;
        } 
    }

    return QCLOUD_RET_SUCCESS;
}

static char *_engine_type_to_str(eAsrEngineType eType)
{
    char *type;
    switch (eType) {
        case eENGINE_8K_EN:
            type = "8k_en";
            break;

        case eENGINE_8K_ZH:
            type = "8k_zh";
            break;

        case eENGINE_8K_ZH_S:
            type = "8k_zh_s";
            break;

        case eENGINE_16K_ZH_VIDEO:
            type = "16k_zh_video";
            break;

        case eENGINE_16K_EN:
            type = "16k_en";
            break;

        case eENGINE_16K_CA:
            type = "16k_ca";
            break;

        case eENGINE_16K_JA:
            type = "16k_ja";
            break;

        case eENGINE_16K_WUU_SH:
            type = "6k_wuu-SH";
            break;

        case eENGINE_16K_ZH:
        default:
            type = "16k_zh";
            break;
    }

    return type;
}

static int _gen_record_asr_request_msg(char *msg_buff, int len, AsrReq *req)
{
    int ret, remain_size;
    POINTER_SANITY_CHECK(msg_buff, QCLOUD_ERR_INVAL);
    // required parameters
    memset(msg_buff, 0, len);
    ret = HAL_Snprintf(msg_buff, len,
                       "{\"method\":\"request_asr\",\"params\":{\"req_type\":%d,"
                       "\"engine_type\":\"%s\",\"channel_num\":%d,\"resource_token\":\"%s\",",
                       req->req_type, _engine_type_to_str(req->record_conf.engine_type), req->record_conf.ch_num,
                       STRING_PTR_PRINT_SANITY_CHECK(req->asr_token));

    // option parameters
    if (req->record_conf.speaker_diarization) {
        if ((remain_size = len - strlen(msg_buff)) < 2 * ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret =
            HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"speaker_diarization\":%d,\"speaker_number\":%d,",
                         req->record_conf.speaker_diarization, req->record_conf.speaker_number);
    }

    if (req->record_conf.filter_dirty) {
        if ((remain_size = len - strlen(msg_buff)) < ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"filter_dirty\":%d,",
                           req->record_conf.filter_dirty);
    }

    if (req->record_conf.filter_modal) {
        if ((remain_size = len - strlen(msg_buff)) < ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"filter_modal\":%d,",
                           req->record_conf.filter_modal);
    }

    if (req->record_conf.filter_punc) {
        if ((remain_size = len - strlen(msg_buff)) < ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret =
            HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"filter_punc\":%d,", req->record_conf.filter_punc);
    }

    if (req->record_conf.convert_num_mode) {
        if ((remain_size = len - strlen(msg_buff)) < ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"convert_num_mode\":%d,",
                           req->record_conf.convert_num_mode);
    }

    if (req->record_conf.hot_word_id) {
        if ((remain_size = len - strlen(msg_buff)) < 2 * ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"hot_word_id\":\"%s\",",
                           req->record_conf.hot_word_id);
    }

    if ((remain_size = len - strlen(msg_buff)) < 2) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }
    ret = HAL_Snprintf(msg_buff + strlen(msg_buff) - 1, remain_size, "}}");

    return ret;
}

static int _gen_realtime_asr_request_msg(char *msg_buff, int len, AsrReq *req)
{
    int ret, remain_size;
    POINTER_SANITY_CHECK(msg_buff, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(req, QCLOUD_ERR_INVAL);
    memset(msg_buff, 0, len);
    // required parameters
    ret = HAL_Snprintf(msg_buff, len,
                       "{\"method\":\"request_asr\",\"params\":{\"req_type\":%d,"
                       "\"engine_type\":\"%s\",\"res_type\":%d,\"voice_format\":%d,"
                       "\"seq\":%d,\"end\":%d,\"voice_id\":\"%s\",\"resource_token\":\"%s\",",
                       req->req_type, _engine_type_to_str(req->realtime_conf.engine_type), req->realtime_conf.res_type,
                       req->realtime_conf.voice_format, req->realtime_conf.seq, req->realtime_conf.end,
                       STRING_PTR_PRINT_SANITY_CHECK(req->realtime_conf.voice_id),
                       STRING_PTR_PRINT_SANITY_CHECK(req->asr_token));

    // option parameters
    if (req->realtime_conf.need_vad) {
        if ((remain_size = len - strlen(msg_buff)) < 2 * ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"need_vad\":%d,\"vad_silence_time\":%d,",
                           req->realtime_conf.need_vad, req->realtime_conf.vad_silence_time);
    }

    if (req->realtime_conf.filter_dirty) {
        if ((remain_size = len - strlen(msg_buff)) < ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"filter_dirty\":%d,",
                           req->realtime_conf.filter_dirty);
    }

    if (req->realtime_conf.filter_modal) {
        if ((remain_size = len - strlen(msg_buff)) < ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"filter_modal\":%d,",
                           req->realtime_conf.filter_modal);
    }

    if (req->realtime_conf.filter_punc) {
        if ((remain_size = len - strlen(msg_buff)) < ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"filter_punc\":%d,",
                           req->realtime_conf.filter_punc);
    }

    if (req->realtime_conf.convert_num_mode) {
        if ((remain_size = len - strlen(msg_buff)) < ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"convert_num_mode\":%d,",
                           req->realtime_conf.convert_num_mode);
    }

    if (req->realtime_conf.hot_word_id) {
        if ((remain_size = len - strlen(msg_buff)) < 2 * ONE_PARA_STR_LEN) {
            return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
        }
        ret = HAL_Snprintf(msg_buff + strlen(msg_buff), remain_size, "\"hot_word_id\":\"%s\",",
                           req->realtime_conf.hot_word_id);
    }

    if ((remain_size = len - strlen(msg_buff)) < 2) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }
    ret = HAL_Snprintf(msg_buff + strlen(msg_buff) - 1, remain_size, "}}");

    return ret;
}

static int _add_request_to_asr_req_list(AsrHandle *pAsrClient, AsrReq *request)
{
    IOT_FUNC_ENTRY;

    HAL_MutexLock(pAsrClient->mutex);
    if (pAsrClient->asr_req_list->len >= MAX_ASR_REQUEST) {
        HAL_MutexUnlock(pAsrClient->mutex);
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MAX_APPENDING_REQUEST);
    }
    ListNode *node = list_node_new(request);
    if (NULL == node) {
        HAL_MutexUnlock(pAsrClient->mutex);
        Log_e("run list_node_new is error!");
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_FAILURE);
    }
    list_rpush(pAsrClient->asr_req_list, node);
    HAL_MutexUnlock(pAsrClient->mutex);

    IOT_FUNC_EXIT_RC(QCLOUD_RET_SUCCESS);
}

static AsrReq *_get_req_node_by_request_id(AsrHandle *pAsrClient, uint32_t request_id)
{
    POINTER_SANITY_CHECK(pAsrClient, NULL);
    AsrReq *req = NULL;
    HAL_MutexLock(pAsrClient->mutex);
    if (pAsrClient->asr_req_list->len) {
        ListIterator *iter;
        ListNode *    node = NULL;

        if (NULL == (iter = list_iterator_new(pAsrClient->asr_req_list, LIST_TAIL))) {
            HAL_MutexUnlock(pAsrClient->mutex);
            return NULL;
        }

        for (;;) {
            node = list_iterator_next(iter);
            if (NULL == node) {
                break;
            }

            if (NULL == node->val) {
                Log_e("node's value is invalid!");
                list_remove(pAsrClient->asr_req_list, node);
                continue;
            }
            req = (AsrReq *)node->val;
            if (req->request_id == request_id) {
                break;
            } else {
                if (expired(&req->timer)) {
                    Log_e("%d timeout removed from list", req->request_id);
                    list_remove(pAsrClient->asr_req_list, node);
                }
                req = NULL;
            }
        }

        list_iterator_destroy(iter);
    }
    HAL_MutexUnlock(pAsrClient->mutex);

    return req;
}

static AsrReq *_get_req_node_by_asr_token(AsrHandle *pAsrClient, const char *asr_token)
{
    POINTER_SANITY_CHECK(pAsrClient, NULL);
    AsrReq *req = NULL;
    HAL_MutexLock(pAsrClient->mutex);
    if (pAsrClient->asr_req_list->len) {
        ListIterator *iter;
        ListNode *    node = NULL;

        if (NULL == (iter = list_iterator_new(pAsrClient->asr_req_list, LIST_TAIL))) {
            HAL_MutexUnlock(pAsrClient->mutex);
            return NULL;
        }

        for (;;) {
            node = list_iterator_next(iter);
            if (NULL == node) {
                break;
            }

            if (NULL == node->val) {
                Log_e("node's value is invalid!");
                list_remove(pAsrClient->asr_req_list, node);
                continue;
            }
            req = (AsrReq *)node->val;
            if (req->asr_token) {
                if (!strcmp(req->asr_token, asr_token)) {
                    break;
                }
            } else {
                if (expired(&req->timer)) {
                    Log_e("%d timeout removed from list", req->request_id);
                    list_remove(pAsrClient->asr_req_list, node);
                }
                req = NULL;
            }
        }

        list_iterator_destroy(iter);
    }
    HAL_MutexUnlock(pAsrClient->mutex);

    return req;
}

static void _del_timeout_req_node(AsrHandle *pAsrClient)
{
    POINTER_SANITY_CHECK_RTN(pAsrClient);
    AsrReq *req = NULL;
    HAL_MutexLock(pAsrClient->mutex);
    if (pAsrClient->asr_req_list->len) {
        ListIterator *iter;
        ListNode *    node = NULL;

        if (NULL == (iter = list_iterator_new(pAsrClient->asr_req_list, LIST_TAIL))) {
            HAL_MutexUnlock(pAsrClient->mutex);
            return;
        }

        for (;;) {
            node = list_iterator_next(iter);
            if (NULL == node) {
                break;
            }

            if (NULL == node->val) {
                Log_e("node's value is invalid!");
                list_remove(pAsrClient->asr_req_list, node);
                continue;
            }
            req = (AsrReq *)node->val;
            if (expired(&req->timer)) {
                Log_e("%d timeout removed from list", req->request_id);
                if (req->req_type == eASR_REALTIME) {
                    Log_d("remove file %s", req->realtime_conf.file_name);
                    HAL_FileRemove(req->realtime_conf.file_name);
                }
                list_remove(pAsrClient->asr_req_list, node);
            }
        }

        list_iterator_destroy(iter);
    }
    HAL_MutexUnlock(pAsrClient->mutex);
}

int _asr_result_notify(void *handle, char *asr_response)
{
    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(asr_response, QCLOUD_ERR_INVAL);

    AsrHandle *asr_handle = (AsrHandle *)handle;
    int        rc         = QCLOUD_RET_SUCCESS;
    char *     str_result = NULL;
    char *     asr_token  = NULL;
    char *     str_num    = NULL;
    char *     str_seq    = NULL;
    char *     asr_txt    = NULL;

    Log_d("asr_response:%s", asr_response);
    str_result = LITE_json_value_of(KEY_ASR_RESULT, asr_response);
    asr_token  = LITE_json_value_of(KEY_ASR_TOKEN, asr_response);
    if (!str_result || !asr_token) {
        Log_e("required result key not found in asr_response:%s", asr_response);
        rc = QCLOUD_ERR_JSON_PARSE;
        goto exit;
    }
    AsrReq *req = _get_req_node_by_asr_token(asr_handle, asr_token);
	if(!req){
        Log_e("asr_token: %s not found", asr_token);
        rc = QCLOUD_ERR_FAILURE;
		goto exit;
	}

    rc = atoi(str_result);
    if (QCLOUD_RET_SUCCESS == rc) {
        str_num = LITE_json_value_of(KEY_ASR_TEXT_SEGS, asr_response);
        str_seq = LITE_json_value_of(KEY_ASR_TEXT_SEQ, asr_response);
        if (!str_num || !str_seq) {
            Log_e("required text key not found in asr_response");
            rc = QCLOUD_ERR_JSON_PARSE;
            goto exit;
        }

        int num = atoi(str_num);
        int seq = atoi(str_seq);
        if (req->result_cb) {
            asr_txt = LITE_json_value_of(KEY_ASR_TEXT, asr_response);
            if (!asr_txt) {
                req->result_cb(req->request_id, "NULL", num, seq);
            } else {
                req->result_cb(req->request_id, asr_txt, num, seq);
            }
        }

        if ((num == seq) || (num < 2)) {
            if (req->asr_token) {
                HAL_Free(req->asr_token);
            }
            HAL_MutexLock(asr_handle->mutex);
            list_remove(asr_handle->asr_req_list, list_find(asr_handle->asr_req_list, req));
            HAL_MutexUnlock(asr_handle->mutex);
        }
    } else {
        Log_e("%s request asr result fail:%d", asr_token, rc);
        if (req->asr_token) {
            HAL_Free(req->asr_token);
        }
        HAL_MutexLock(asr_handle->mutex);
        list_remove(asr_handle->asr_req_list, list_find(asr_handle->asr_req_list, req));
        HAL_MutexUnlock(asr_handle->mutex);
    }

exit:

    if (str_result) {
        HAL_Free(str_result);
    }

    if (asr_token) {
        HAL_Free(asr_token);
    }

    if (str_num) {
        HAL_Free(str_num);
    }

    if (str_seq) {
        HAL_Free(str_seq);
    }

    if (asr_txt) {
        HAL_Free(asr_txt);
    }

    return rc;
}

int _request_asr_resource_result(void *handle, AsrReq *req)
{
    char asr_request_buff[ASR_REQUEST_BUFF_LEN];
    int  ret = 0;

    if (eASR_REALTIME == req->req_type) {
        ret = _gen_realtime_asr_request_msg(asr_request_buff, ASR_REQUEST_BUFF_LEN, req);
    } else {
        ret = _gen_record_asr_request_msg(asr_request_buff, ASR_REQUEST_BUFF_LEN, req);
    }

    if (ret < 0) {
        Log_e("generate asr request message failed");
        return ret;
    }
    Log_d("%s", asr_request_buff);
    ret = IOT_Resource_Report_Msg(handle, asr_request_buff);

    return ret;
}

static int _asr_resource_event_usr_cb(void *pContext, const char *msg, uint32_t msgLen, IOT_RES_UsrEvent event)
{
    int ret = QCLOUD_RET_SUCCESS;

    AsrHandle *asr_handle = (AsrHandle *)pContext;
    char *     json_str   = (char *)msg;
    char *     request_id;
    AsrReq *   req;
    int        id;

    Log_d("event(%d) msg:%*s", event, msgLen, msg);
    switch (event) {
        case IOT_RES_EVENT_REQUEST_URL_RESP:
            request_id = LITE_json_value_of(REQUEST_ID, json_str);
            if (!request_id) {
                Log_e("no request_id found");
                goto exit;
            }
            id  = atoi(request_id);
            req = _get_req_node_by_request_id(asr_handle, id);
            if (!req) {
                Log_e("no req found according to request_id");
                HAL_Free(request_id);
                goto exit;
            }
            req->asr_token = LITE_json_value_of(RESOURCE_TOKEN, json_str);
            if (!req->asr_token) {
                Log_e("no req->asr_token found");
                HAL_Free(request_id);
                goto exit;
            }
            if (req->req_type == eASR_REALTIME) {
                // Log_d("remove file %s", req->realtime_conf.file_name);
                HAL_FileRemove(req->realtime_conf.file_name);
            }
            ret = _request_asr_resource_result(asr_handle->resource_handle, req);
            HAL_Free(request_id);
            break;

        default:
            break;
    }

    if (asr_handle->usrCb) {
        ret = asr_handle->usrCb(asr_handle->resource_handle, msg, msgLen, event);
    }

exit:

    return ret;
}

void *IOT_Asr_Init(const char *product_id, const char *device_name, void *pTemplate_client,
                   OnAsrResourceEventUsrCallback usr_cb)
{
    AsrHandle *asr_handle = NULL;
    int        rc         = QCLOUD_RET_SUCCESS;
	
	rc = _register_asr_property(pTemplate_client);
	if(QCLOUD_RET_SUCCESS != rc){
		Log_e("register asr system property fail,rc:%d",rc);
		goto exit;
	}

    asr_handle = HAL_Malloc(sizeof(AsrHandle));
    if (!asr_handle) {
        Log_e("allocate asr client failed");
        rc = QCLOUD_ERR_MALLOC;
        goto exit;
    }

    // init resource client handle
    asr_handle->resource_handle =
        IOT_Resource_Init(product_id, device_name, IOT_Template_Get_MQTT_Client(pTemplate_client),
                          _asr_resource_event_usr_cb, asr_handle);
    if (!asr_handle->resource_handle) {
        Log_e("init resource client failed");
        rc = QCLOUD_ERR_FAILURE;
        goto exit;
    }

    asr_handle->mutex = HAL_MutexCreate();
    if (asr_handle->mutex == NULL) {
        Log_e("create asr mutex fail");
        rc = QCLOUD_ERR_FAILURE;
        goto exit;
    }

    asr_handle->asr_req_list = list_new();
    if (asr_handle->asr_req_list) {
        asr_handle->asr_req_list->free = HAL_Free;
    } else {
        Log_e("no memory to allocate asr_req_list");
        rc = QCLOUD_ERR_FAILURE;
    }
    asr_handle->usrCb = usr_cb;
	sg_asr_client = asr_handle;

exit:

    if (rc != QCLOUD_RET_SUCCESS) {
        if (asr_handle) {
            HAL_Free(asr_handle);
            if (asr_handle->resource_handle) {
                IOT_Resource_Destroy(asr_handle->resource_handle);
            }
            if (asr_handle->mutex) {
                HAL_MutexDestroy(asr_handle->mutex);
            }
            if (asr_handle->asr_req_list) {
                list_destroy(asr_handle->asr_req_list);
            }
        }
        asr_handle = NULL;
    }

    return asr_handle;
}

int IOT_Asr_Destroy(void *handle)
{
    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);
    AsrHandle *asr_handle = (AsrHandle *)handle;
    int        rc         = QCLOUD_RET_SUCCESS;

    if (asr_handle->resource_handle) {
        rc = IOT_Resource_Destroy(asr_handle->resource_handle);
    }
    if (asr_handle->mutex) {
        HAL_MutexDestroy(asr_handle->mutex);
    }
    if (asr_handle->asr_req_list) {
        list_destroy(asr_handle->asr_req_list);
    }

    return rc;
}

int IOT_Asr_RecordFile_Request(void *handle, const char *file_name, RecordAsrConf *conf, OnAsrResultCB cb)
{
    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);
    AsrHandle *asr_handle = (AsrHandle *)handle;
    int        rc         = QCLOUD_RET_SUCCESS;

    AsrReq *req = (AsrReq *)HAL_Malloc(sizeof(AsrReq));
    if (!req) {
        Log_e("malloc mem err");
        rc = QCLOUD_ERR_MALLOC;
        goto exit;
    }
    // required parameters
    req->req_type                = conf->req_type;
    req->record_conf.engine_type = conf->engine_type;
    req->record_conf.ch_num      = conf->ch_num;
    req->asr_token               = NULL;
    // option parameters
    req->record_conf.filter_dirty        = conf->filter_dirty;
    req->record_conf.filter_modal        = conf->filter_modal;
    req->record_conf.filter_punc         = conf->filter_punc;
    req->record_conf.convert_num_mode    = conf->convert_num_mode;
    req->record_conf.speaker_diarization = conf->speaker_diarization;
    req->record_conf.speaker_number      = conf->speaker_number;
    req->record_conf.hot_word_id         = NULL;

    char time_str[TIME_FORMAT_STR_LEN] = {0};
    HAL_Snprintf(time_str, TIME_FORMAT_STR_LEN, "%d", HAL_Timer_current_sec());
    conf->request_timeout_ms = (conf->request_timeout_ms > 0) ? conf->request_timeout_ms : DEFAULT_REQ_TIMEOUT_MS;
	char *type = (req->req_type == eASR_FILE)?RESOURCE_TYPE_AUDIO:RESOURCE_TYPE_VOICE;
    req->request_id =
        IOT_Resource_Post_Request(asr_handle->resource_handle, conf->request_timeout_ms, file_name, time_str, type);
    if (req->request_id < 0) {
        Log_e("%s resource post request fail", STRING_PTR_PRINT_SANITY_CHECK(file_name));
        HAL_Free(req);
        rc = QCLOUD_ERR_FAILURE;
        goto exit;
    }
    req->result_cb = cb;

    InitTimer(&(req->timer));
    countdown(&(req->timer), conf->request_timeout_ms);
    rc = _add_request_to_asr_req_list(asr_handle, req);
    if (QCLOUD_RET_SUCCESS != rc) {
        _del_timeout_req_node(asr_handle);
    }

exit:

    return (rc == QCLOUD_RET_SUCCESS) ? req->request_id : rc;
}

int IOT_Asr_Realtime_Request(void *handle, char *audio_buff, uint32_t audio_data_len, RealTimeAsrConf *conf,
                             OnAsrResultCB cb)
{
#define VERSION_LEN 10
    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);
    AsrHandle *asr_handle = (AsrHandle *)handle;
    int        rc         = QCLOUD_RET_SUCCESS;

    AsrReq *req = (AsrReq *)HAL_Malloc(sizeof(AsrReq));
    if (!req) {
        Log_e("malloc mem err");
        rc = QCLOUD_ERR_MALLOC;
        goto exit;
    }
    // required parameters
    req->req_type                   = conf->req_type;
    req->realtime_conf.engine_type  = conf->engine_type;
    req->realtime_conf.res_type     = conf->res_type;
    req->realtime_conf.voice_format = conf->voice_format;
    req->realtime_conf.seq          = conf->seq;
    req->realtime_conf.end          = conf->end;
    req->asr_token                  = NULL;

    // option parameters
    req->realtime_conf.need_vad         = conf->need_vad;
    req->realtime_conf.vad_silence_time = conf->vad_silence_time;
    req->realtime_conf.filter_dirty     = conf->filter_dirty;
    req->realtime_conf.filter_modal     = conf->filter_modal;
    req->realtime_conf.filter_punc      = conf->filter_punc;
    req->realtime_conf.convert_num_mode = conf->convert_num_mode;
    req->realtime_conf.hot_word_id      = NULL;

    static char voice_id[VOICE_ID_LEN + 1];
    if (0 == conf->seq) {
        memset(voice_id, '\0', VOICE_ID_LEN + 1);
        HAL_Snprintf(voice_id, VOICE_ID_LEN + 1, "%016d", HAL_Timer_current_sec());
        HAL_FileRemove("./*.bin");
    }
    memset(req->realtime_conf.voice_id, '\0', VOICE_ID_LEN + 1);
    strncpy(req->realtime_conf.voice_id, voice_id, VOICE_ID_LEN);

    char version[VERSION_LEN] = {0};
    HAL_Snprintf(version, VERSION_LEN, "%d", conf->seq);
    memset(req->realtime_conf.file_name, 0, REAL_TIME_SLICE_FILE_NAME_LEN);
    HAL_Snprintf(req->realtime_conf.file_name, VOICE_ID_LEN + VERSION_LEN, "./%s-%s.dat", voice_id, version);
    // save audio data to file
    void *fp = HAL_FileOpen(req->realtime_conf.file_name, "wb");
	if(!fp){
		Log_e("create file %s fail", req->realtime_conf.file_name);
		goto exit;
	}

    if (audio_data_len != HAL_FileWrite(audio_buff, 1, audio_data_len, fp)) {
        Log_e("write data buff to %s fail", req->realtime_conf.file_name);
        HAL_Free(req);
        HAL_FileClose(fp);
        rc = QCLOUD_ERR_FAILURE;
        goto exit;
    }
   
    HAL_FileClose(fp);

    conf->request_timeout_ms = (conf->request_timeout_ms > 0) ? conf->request_timeout_ms : DEFAULT_REQ_TIMEOUT_MS;
    req->request_id          = IOT_Resource_Post_Request(asr_handle->resource_handle, conf->request_timeout_ms,
                                                req->realtime_conf.file_name, version, RESOURCE_TYPE_VOICE);
    if (req->request_id < 0) {
        Log_e("%s resource post request fail", req->realtime_conf.file_name);
        HAL_FileRemove(req->realtime_conf.file_name);
        rc = QCLOUD_ERR_FAILURE;
        HAL_Free(req);
        goto exit;
    }
    req->result_cb = cb;

    InitTimer(&(req->timer));
    countdown(&(req->timer), conf->request_timeout_ms);
    rc = _add_request_to_asr_req_list(asr_handle, req);
    if (QCLOUD_RET_SUCCESS != rc) {
        _del_timeout_req_node(asr_handle);
        HAL_FileRemove(req->realtime_conf.file_name);
        HAL_Free(req);
    }

exit:

    return (rc == QCLOUD_RET_SUCCESS) ? req->request_id : rc;
#undef VERSION_LEN
}
#ifdef __cplusplus
}
#endif
