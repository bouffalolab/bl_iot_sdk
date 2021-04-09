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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "resource_client.h"
#include "service_mqtt.h"
#include "qcloud_iot_export.h"
#include "qutils_param_check.h"

#include "qutils_timer.h"
#include "qutils_md5.h"
#include "qutils_list.h"
#include "qutils_url_download.h"
#include "qutils_url_upload.h"
#include "json_parser.h"

#include "qutils_httpc.h"
#include "qcloud_iot_ca.h"

#if ((defined(ASR_ENABLED)) && (!defined OTA_USE_HTTPS))
#error ASR NEED HTTPS ENABLE
#endif

#define FIELD_TYPE           "type"
#define FIELD_MD5            "md5sum"
#define FIELD_VERSION        "version"
#define FIELD_URL            "url"
#define FIELD_FILE_SIZE      "file_size"
#define FIELD_RESULT         "result_code"
#define FIELD_RESOURCE_NAME  "resource_name"
#define FIELD_FILE_TYPE      "resource_type"
#define FIELD_RESOURCE_URL   "resource_url"
#define FIELD_RESOURCE_TOKEN "resource_token"
#define FIELD_REQUEST_ID     "request_id"

#define MSG_REPORT_LEN (256)

typedef struct {
    const char *product_id;  /* point to product id */
    const char *device_name; /* point to device name */

    uint32_t          id;                /* message id */
    IOT_RES_StateCode state;             /* state */
    uint32_t          size_last_fetched; /* size of last downloaded */
    uint32_t          size_fetched;      /* size of already downloaded */
    uint32_t          size_file;         /* size of file */

    char *url;        /* point to URL */
    char *version;    /* point to string */
    char *file_name;  /* point to string */
    char *file_type;  /* point to string */
    char  md5sum[33]; /* MD5 string */

    void *md5;       /* MD5 handle */
    void *ch_signal; /* channel handle of signal exchanged with server */
    void *ch_fetch;  /* channel handle of download */

    int   request_id;
    void *mutex;
    List *res_wait_post_list;
    void *usr_context;

    int   err;       /* last error code */
    int   report_rc; /* result of _resource_report_upgrade_result in IOT_Resource_FetchYield*/
    Timer report_timer;

    OnResourceEventUsrCallback usr_cb;
} ResourceHandle;

typedef struct {
    int   request_id;
    char *res_name;
    char *res_version;
    char *res_type;
    Timer post_timer;
} ResPostInfo;

/*====================funtion ===================*/
char *strdup(const char *src)
{
    size_t len = strlen(src) + 1;
    char * ret = HAL_Malloc(len);
    if (ret != NULL) {
        strcpy(ret, src);
    }

    return ret;
}

/* static function*/
static int _gen_resource_ver_info(char *buf, size_t bufLen, uint16_t res_num, resInfo *res_list[])
{
    POINTER_SANITY_CHECK(buf, QCLOUD_ERR_INVAL);

    resInfo *pInfo = NULL;

    int ret;
    int pos;
    int i;

    ret = HAL_Snprintf(buf, bufLen, "{\"method\":\"report_version\",\"report\":{\"resource_list\":[");
    if (ret < 0) {
        Log_e("HAL_Snprintf failed");
        return QCLOUD_ERR_FAILURE;
    }

    for (i = 0; i < res_num; i++) {
        pInfo = res_list[i];
        if (!pInfo) {
            Log_e("version list invalid");
            return QCLOUD_ERR_FAILURE;
        }

        ret =
            HAL_Snprintf(buf + strlen(buf), bufLen - strlen(buf),
                         "{\"resource_name\":\"%s\",\"version\":\"%s\",\"resource_type\":\"%s\"},",
                         STRING_PTR_PRINT_SANITY_CHECK(pInfo->res_name), STRING_PTR_PRINT_SANITY_CHECK(pInfo->res_ver),
                         STRING_PTR_PRINT_SANITY_CHECK(pInfo->res_type));
        if (ret < 0) {
            Log_e("HAL_Snprintf failed");
            return QCLOUD_ERR_FAILURE;
        }
    }

    pos = (i > 0) ? 1 : 0;

    ret = HAL_Snprintf(buf + strlen(buf) - pos, bufLen - strlen(buf), "]}}");
    if (ret < 0) {
        Log_e("HAL_Snprintf failed");
        return QCLOUD_ERR_FAILURE;
    }

    return QCLOUD_RET_SUCCESS;
}

static int _gen_resource_report_msg(char *buf, size_t bufLen, const char *file_name, const char *version,
                                    const char *type, int progress, IOT_RES_ReportType reportType)
{
    IOT_FUNC_ENTRY;

    int ret;

    switch (reportType) {
        /* report download begin */
        case IOT_RES_TYPE_DOWNLOAD_BEGIN:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\": \"report_progress\", \"report\": {\"progress\": "
                               "{\"resource_name\":\"%s\",\"state\":\"downloading\", \"percent\":\"0\", "
                               "\"result_code\":\"0\", \"result_msg\":\"\"}, \"version\": \"%s\"}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name), STRING_PTR_PRINT_SANITY_CHECK(version));
            break;
        /* report download progress */
        case IOT_RES_TYPE_DOWNLOADING:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\": \"report_progress\", \"report\": {\"progress\": "
                               "{\"resource_name\":\"%s\",\"state\":\"downloading\", \"percent\":\"%d\", "
                               "\"result_code\":\"0\", \"result_msg\":\"\"}, \"version\": \"%s\"}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name), progress,
                               STRING_PTR_PRINT_SANITY_CHECK(version));
            break;

        case IOT_RES_TYPE_SPACE_NOT_ENOUGH:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\": \"report_result\", \"report\": {\"progress\": "
                               "{\"resource_name\":\"%s\",\"state\":\"done\", \"result_code\":\"%d\", "
                               "\"result_msg\":\"space not enough\"}, \"version\": \"%s\"}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name), reportType,
                               STRING_PTR_PRINT_SANITY_CHECK(version));
            break;

        case IOT_RES_TYPE_MD5_NOT_MATCH:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\": \"report_result\", \"report\": {\"progress\": "
                               "{\"resource_name\":\"%s\",\"state\":\"done\", \"result_code\":\"%d\", "
                               "\"result_msg\":\"md5 check fail\"}, \"version\": \"%s\"}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name), reportType,
                               STRING_PTR_PRINT_SANITY_CHECK(version));
            break;

        case IOT_RES_TYPE_DOWNLOAD_TIMEOUT:
        case IOT_RES_TYPE_FILE_NOT_EXIST:
        case IOT_RES_TYPE_AUTH_FAIL:
        case IOT_RES_TYPE_UPGRADE_FAIL:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\": \"report_result\", \"report\": {\"progress\": "
                               "{\"resource_name\":\"%s\",\"state\":\"done\", \"result_code\":\"%d\", "
                               "\"result_msg\":\"time_out\"}, \"version\": \"%s\"}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name), reportType,
                               STRING_PTR_PRINT_SANITY_CHECK(version));
            break;

        case IOT_RES_TYPE_UPGRADE_BEGIN:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\": \"report_progress\", "
                               "\"report\":{\"progress\":{\"resource_name\":\"%s\",\"state\":\"burning\", "
                               "\"result_code\":\"0\", \"result_msg\":\"\"}, \"version\":\"%s\"}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name), STRING_PTR_PRINT_SANITY_CHECK(version));
            break;

        /* report OTA upgrade finish */
        case IOT_RES_TYPE_UPGRADE_SUCCESS:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\":\"report_result\", "
                               "\"report\":{\"progress\":{\"resource_name\":\"%s\",\"state\":\"done\", "
                               "\"result_code\":\"0\",\"result_msg\":\"success\"}, \"version\":\"%s\"}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name), STRING_PTR_PRINT_SANITY_CHECK(version));
            break;

        case IOT_RES_TYPE_FILE_DEL_SUCCESS:
            ret = HAL_Snprintf(
                buf, bufLen,
                "{\"method\": \"del_result\", \"report\":{\"progress\":{\"resource_name\":\"%s\",\"state\":\"done\", "
                "\"result_code\":\"0\", \"result_msg\":\"success\"}, \"version\":\"%s\"}}",
                STRING_PTR_PRINT_SANITY_CHECK(file_name), STRING_PTR_PRINT_SANITY_CHECK(version));
            break;

        case IOT_RES_TYPE_FILE_DEL_FAIL:
            ret = HAL_Snprintf(
                buf, bufLen,
                "{\"method\": \"del_result\", \"report\":{\"progress\":{\"resource_name\":\"%s\",\"state\":\"done\", "
                "\"result_code\":\"%d\", \"result_msg\":\"file del fail\"}, \"version\":\"%s\"}}",
                STRING_PTR_PRINT_SANITY_CHECK(file_name), reportType, STRING_PTR_PRINT_SANITY_CHECK(version));

            break;

        case IOT_RES_TYPE_REQUEST_URL:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\":\"request_url\",\"request_id\":\"%d\","
                               "\"report\":{\"resource_name\":\"%s\",\"version\":\"%s\",\"resource_type\":\"%s\"}}",
                               progress, STRING_PTR_PRINT_SANITY_CHECK(file_name),
                               STRING_PTR_PRINT_SANITY_CHECK(version), STRING_PTR_PRINT_SANITY_CHECK(type));

            break;

        case IOT_RES_TYPE_POST_SUCCESS:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\":\"report_post_result\",\"report\":{\"progress\":{\"resource_token\":\"%s\","
                               "\"state\":\"done\",\"result_code\":\"0\", \"result_msg\":\"success\"}}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name));

            break;

        case IOT_RES_TYPE_POST_FAIL:
            ret = HAL_Snprintf(buf, bufLen,
                               "{\"method\":\"report_post_result\",\"report\":{\"progress\":{\"resource_token\":\"%s\","
                               "\"state\":\"done\",\"result_code\":\"-1\", \"result_msg\":\"post_fail\"}}}",
                               STRING_PTR_PRINT_SANITY_CHECK(file_name));
            break;

        default:
            IOT_FUNC_EXIT_RC(IOT_RES_ERR_FAIL);
            break;
    }

    if (ret < 0) {
        Log_e("HAL_Snprintf failed");
        IOT_FUNC_EXIT_RC(IOT_RES_ERR_FAIL);
    } else if (ret >= bufLen) {
        Log_e("msg is too long");
        IOT_FUNC_EXIT_RC(IOT_RES_ERR_STR_TOO_LONG);
    }

    IOT_FUNC_EXIT_RC(IOT_RES_ERR_NONE);
}

static void _reset_handle_status(void *handle)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    Log_i("reset resource handle state!");

    pHandle->state = IOT_RES_STATE_INITTED;
    pHandle->err   = 0;

    HAL_Free(pHandle->url);
    pHandle->url = NULL;

    HAL_Free(pHandle->version);
    pHandle->version = NULL;

    HAL_Free(pHandle->file_name);
    pHandle->file_name = NULL;

    HAL_Free(pHandle->file_type);
    pHandle->file_type = NULL;

    utils_md5_reset(pHandle->md5);
}

static int _resource_report_progress(void *handle, int progress, IOT_RES_ReportType reportType)
{
    int             ret          = QCLOUD_ERR_FAILURE;
    char *          msg_reported = NULL;
    ResourceHandle *pHandle      = (ResourceHandle *)handle;

    if (IOT_RES_STATE_UNINITTED == pHandle->state) {
        Log_e("handle is uninitialized");
        pHandle->err = IOT_OTA_ERR_INVALID_STATE;
        return QCLOUD_ERR_FAILURE;
    }

    if (NULL == (msg_reported = HAL_Malloc(MSG_REPORT_LEN))) {
        Log_e("allocate for msg_reported failed");
        pHandle->err = IOT_OTA_ERR_NOMEM;
        return QCLOUD_ERR_FAILURE;
    }

    ret = _gen_resource_report_msg(msg_reported, MSG_REPORT_LEN, pHandle->file_name, pHandle->version, NULL, progress,
                                   reportType);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("generate resource inform message failed");
        pHandle->err = ret;
        ret          = QCLOUD_ERR_FAILURE;
        goto exit;
    }

    ret = qcloud_service_mqtt_post_msg(pHandle->ch_signal, msg_reported, QOS0);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("Report progress failed");
        pHandle->err = IOT_RES_ERR_REPORT_PROGRESS;
        goto exit;
    }

    ret = QCLOUD_RET_SUCCESS;

exit:

    HAL_Free(msg_reported);

    return ret;
}

static int _resource_report_upgrade_result(void *handle, const char *version, IOT_RES_ReportType reportType)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    int   ret, len;
    char *msg_upgrade = NULL;

    if (IOT_RES_STATE_UNINITTED == pHandle->state) {
        Log_e("handle is uninitialized");
        pHandle->err = IOT_RES_ERR_INVALID_STATE;
        return QCLOUD_ERR_FAILURE;
    }

    version = (version == NULL) ? pHandle->version : version;

    if (!version) {
        Log_e("version is null!");
        pHandle->err = IOT_RES_ERR_INVALID_PARAM;
        return QCLOUD_ERR_INVAL;
    }

    len = strlen(version);
    if ((len < RESOURCE_VERSION_STR_LEN_MIN) || (len > RESOURCE_VERSION_STR_LEN_MAX)) {
        Log_e("version string is invalid: must be [1, 32] chars");
        pHandle->err = IOT_RES_ERR_INVALID_PARAM;
        return QCLOUD_ERR_INVAL;
    }

    if (NULL == (msg_upgrade = HAL_Malloc(MSG_REPORT_LEN))) {
        Log_e("allocate for msg_informed failed");
        pHandle->err = IOT_OTA_ERR_NOMEM;
        return QCLOUD_ERR_FAILURE;
    }

    ret = _gen_resource_report_msg(msg_upgrade, MSG_REPORT_LEN, pHandle->file_name, version, NULL, 1, reportType);
    if (ret != 0) {
        Log_e("generate resource inform message failed");
        pHandle->err = ret;
        ret          = QCLOUD_ERR_FAILURE;
        goto exit;
    }

    ret = qcloud_service_mqtt_post_msg(pHandle->ch_signal, msg_upgrade, QOS1);
    if (0 > ret) {
        Log_e("Report result failed");
        pHandle->err = IOT_RES_ERR_REPORT_UPGRADE_RESULT;
        ret          = QCLOUD_ERR_FAILURE;
        goto exit;
    }

exit:
    if ((IOT_RES_TYPE_DOWNLOAD_BEGIN != reportType) && (IOT_RES_TYPE_DOWNLOADING != reportType) &&
        (IOT_RES_TYPE_UPGRADE_BEGIN != reportType) && (IOT_RES_TYPE_NONE != reportType)) {
        _reset_handle_status(pHandle);
    }
    HAL_Free(msg_upgrade);
    return ret;
}

static int _resource_report_post_result(void *handle, const char *res_token, IOT_RES_ReportType reportType)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;
    int             ret;
    char *          msg_post = NULL;

    if (IOT_RES_STATE_UNINITTED == pHandle->state) {
        Log_e("handle is uninitialized");
        pHandle->err = IOT_RES_ERR_INVALID_STATE;
        return QCLOUD_ERR_FAILURE;
    }

    if (NULL == (msg_post = HAL_Malloc(MSG_REPORT_LEN))) {
        Log_e("allocate for msg_informed failed");
        pHandle->err = IOT_OTA_ERR_NOMEM;
        return QCLOUD_ERR_FAILURE;
    }

    ret = _gen_resource_report_msg(msg_post, MSG_REPORT_LEN, res_token, NULL, NULL, 0, reportType);
    if (ret != 0) {
        Log_e("generate resource inform message failed");
        pHandle->err = ret;
        ret          = QCLOUD_ERR_FAILURE;
        goto exit;
    }

    ret = qcloud_service_mqtt_post_msg(pHandle->ch_signal, msg_post, QOS1);
    if (0 > ret) {
        Log_e("Report result failed");
        pHandle->err = IOT_RES_ERR_REPORT_UPGRADE_RESULT;
        ret          = QCLOUD_ERR_FAILURE;
        goto exit;
    }

exit:
    if ((IOT_RES_TYPE_DOWNLOAD_BEGIN != reportType) && (IOT_RES_TYPE_DOWNLOADING != reportType) &&
        (IOT_RES_TYPE_UPGRADE_BEGIN != reportType) && (IOT_RES_TYPE_NONE != reportType) &&
        (IOT_RES_TYPE_POST_SUCCESS != reportType) && (IOT_RES_TYPE_POST_FAIL != reportType)) {
        _reset_handle_status(pHandle);
    }
    HAL_Free(msg_post);
    return ret;
}

static int _add_resouce_info_to_post_list(void *handle, ResPostInfo *info)
{
    IOT_FUNC_ENTRY;
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    HAL_MutexLock(pHandle->mutex);
    if (pHandle->res_wait_post_list->len >= MAX_RES_WAIT_POST) {
        HAL_MutexUnlock(pHandle->mutex);
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MAX_APPENDING_REQUEST);
    }

    ListNode *node = list_node_new(info);
    if (NULL == node) {
        HAL_MutexUnlock(pHandle->mutex);
        Log_e("run list_node_new is error!");
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_FAILURE);
    }
    list_rpush(pHandle->res_wait_post_list, node);
    HAL_MutexUnlock(pHandle->mutex);

    IOT_FUNC_EXIT_RC(QCLOUD_RET_SUCCESS);
}

static ResPostInfo *_get_resource_info_by_request_id(void *handle, int request_id)
{
    POINTER_SANITY_CHECK(handle, NULL);

    ResourceHandle *pHandle = (ResourceHandle *)handle;
    ResPostInfo *   info    = NULL;
    HAL_MutexLock(pHandle->mutex);
    if (pHandle->res_wait_post_list->len) {
        ListIterator *iter;
        ListNode *    node = NULL;

        if (NULL == (iter = list_iterator_new(pHandle->res_wait_post_list, LIST_TAIL))) {
            HAL_MutexUnlock(pHandle->mutex);
            return NULL;
        }

        for (;;) {
            node = list_iterator_next(iter);
            if (NULL == node) {
                break;
            }

            if (NULL == node->val) {
                Log_e("node's value is invalid!");
                list_remove(pHandle->res_wait_post_list, node);
                continue;
            }
            info = (ResPostInfo *)node->val;

            if (info->request_id == request_id) {
                break;
            } else {
                if (expired(&info->post_timer)) {
                    list_remove(pHandle->res_wait_post_list, node);
                }
                info = NULL;
            }
        }

        list_iterator_destroy(iter);
    }
    HAL_MutexUnlock(pHandle->mutex);

    return info;
}

static int _post_resource_to_cos(const char *resource_url, ResPostInfo *info)
{
#define PER_CHRUNK_READ_SIZE (6400)  // 200ms/16K/16bit ~ 6.4KB
#define COS_REPLY_TIMEOUT_MS (500)

    int   rc            = QCLOUD_ERR_FAILURE;
    char *data_buf      = NULL;
    void *pUploadHandle = NULL;

    Log_d("post %s(%d) %s to cos", STRING_PTR_PRINT_SANITY_CHECK(info->res_name), info->request_id,
          STRING_PTR_PRINT_SANITY_CHECK(info->res_version));
    void *fp = HAL_FileOpen(info->res_name, "rb");
    if (NULL == fp) {
        Log_e("can not open file %s!", STRING_PTR_PRINT_SANITY_CHECK(info->res_name));
        return QCLOUD_ERR_FAILURE;
    }

    long file_size = HAL_FileSize(fp);
    pUploadHandle  = qcloud_url_upload_init(resource_url, file_size);
    if (!pUploadHandle) {
        Log_e("Initialize upload handle failed");
        goto exit;
    }

    rc = qcloud_url_upload_connect(pUploadHandle, HTTP_PUT);
    if (QCLOUD_RET_SUCCESS != rc) {
        Log_e("upload handle connect failed");
        goto exit;
    }

    data_buf = (char *)HAL_Malloc(PER_CHRUNK_READ_SIZE);
    memset(data_buf, 0, PER_CHRUNK_READ_SIZE);
    if (!data_buf) {
        Log_e("malloc data_buff fail");
        goto exit;
    }

    while (!HAL_FileEof(fp) && file_size > 0) {
        int data_len = (file_size > PER_CHRUNK_READ_SIZE) ? PER_CHRUNK_READ_SIZE : file_size;
        int read_len = HAL_FileRead(data_buf, 1, data_len, fp);
        if (data_len != read_len) {
            Log_e("Read file wrong, read_len %d(%d)", read_len, data_len);
            rc = QCLOUD_ERR_FAILURE;
            goto exit;
        }
        file_size -= read_len;

        rc = qcloud_url_upload_body(pUploadHandle, data_buf, read_len, 5000);
        if (QCLOUD_RET_SUCCESS != rc) {
            Log_e("send data failed");
            goto exit;
        }
    }
    Log_d("post file to cos over!");

    memset(data_buf, 0, PER_CHRUNK_READ_SIZE);
    rc = qcloud_url_upload_recv_response(pUploadHandle, data_buf, PER_CHRUNK_READ_SIZE, COS_REPLY_TIMEOUT_MS);
    if (QCLOUD_RET_SUCCESS != rc) {
        Log_e("Failed to recv response %d", rc);
    }
    // Log_d("response:%s", data_buf);

exit:

    if (fp) {
        HAL_FileClose(fp);
    }

    if (data_buf) {
        HAL_Free(data_buf);
    }

    if (pUploadHandle) {
        qcloud_url_upload_deinit(pUploadHandle);
    }

    return rc;

#undef PER_CHRUNK_READ_SIZE
#undef COS_REPLY_TIMEOUT_MS
}

/* callback when resource topic msg is received */
static void _resource_msg_callback(void *handle, const char *msg, uint32_t msg_len)
{
    ResourceHandle *pHandle     = (ResourceHandle *)handle;
    char *          json_method = NULL;
    char *          json_str    = (char *)msg;
    int             rc;

    if (pHandle->state >= IOT_RES_STATE_FETCHING) {
        Log_i("In downloading or downloaded state(%d)", pHandle->state);
        goto exit;
    }

    if (json_str == NULL || msg_len <= 0) {
        Log_e("OTA response message is NULL");
        return;
    }

    json_method = LITE_json_value_of(FIELD_METHOD, json_str);

    if (!json_method) {
        Log_e("Get resource method failed!");
        goto exit;
    }

    Log_d("method: %s", json_method);
    if (!strcmp(json_method, METHOD_RES_REPORT_VERSION_RSP)) {  // report version resp
        char *result_code = LITE_json_value_of(FIELD_RESULT, json_str);

        if (strcmp(result_code, "0") != 0 || !result_code) {
            Log_e("Report resource version failed!");
            pHandle->err   = IOT_RES_ERR_REPORT_VERSION;
            pHandle->state = IOT_RES_STATE_FETCHED;
        } else {
            Log_i("Report resource version success!");
            pHandle->usr_cb(pHandle->usr_context, json_str, msg_len, IOT_RES_EVENT_REPORT_VERSION_RESP);
        }

        HAL_Free(result_code);
        goto exit;
    } else if (strcmp(json_method, METHOD_RES_UPDATE_RESOURCE) == 0) {  // update resource
        pHandle->version   = LITE_json_value_of(FIELD_VERSION, json_str);
        pHandle->url       = LITE_json_value_of(FIELD_URL, json_str);
        pHandle->file_name = LITE_json_value_of(FIELD_RESOURCE_NAME, json_str);
        pHandle->file_type = LITE_json_value_of(FIELD_FILE_TYPE, json_str);

        char *md5       = LITE_json_value_of(FIELD_MD5, json_str);
        char *file_size = LITE_json_value_of(FIELD_FILE_SIZE, json_str);

        if (!pHandle->version || !pHandle->url || !pHandle->file_name || !pHandle->file_type || !md5 || !file_size) {
            Log_e("Get resource parameter failed");
            HAL_Free(md5);
            HAL_Free(file_size);
            _resource_report_upgrade_result(pHandle, pHandle->version, IOT_RES_TYPE_FILE_NOT_EXIST);
            goto exit;
        }

        // copy md5sum
        strncpy(pHandle->md5sum, md5, 33);
        HAL_Free(md5);

        // copy file_size
        pHandle->size_file = atoi(file_size);
        HAL_Free(file_size);

        Log_d("res_para: file_name:%s, file_size:%d, md5:%s, version:%s, url:%s", pHandle->file_name,
              pHandle->size_file, pHandle->md5sum, pHandle->version, pHandle->url);
        pHandle->state = IOT_RES_STATE_FETCHING;
    } else if (strcmp(json_method, METHOD_RES_DELETE_RESOURCE) == 0) {  // delete resource

        pHandle->state = IOT_RES_STATE_DELETING;

        pHandle->version   = LITE_json_value_of(FIELD_VERSION, json_str);
        pHandle->file_type = LITE_json_value_of(FIELD_FILE_TYPE, json_str);
        pHandle->file_name = LITE_json_value_of(FIELD_RESOURCE_NAME, json_str);

        if (!pHandle->version || !pHandle->file_type || !pHandle->file_name) {
            Log_e("Get resource parameter failed");
            // this will call _reset_handle_status and free the memory
            _resource_report_upgrade_result(pHandle, pHandle->version, IOT_RES_TYPE_FILE_DEL_FAIL);
            goto exit;
        }
        rc = pHandle->usr_cb(pHandle->usr_context, pHandle->file_name, strlen(pHandle->file_name),
                             IOT_RES_EVENT_DEL_RESOURCE);
        if (0 != rc) {
            Log_e("Delete resource file(%s) fail", pHandle->file_name);
            _resource_report_upgrade_result(pHandle, pHandle->version, IOT_RES_TYPE_FILE_DEL_FAIL);
            goto exit;
        } else {
            _resource_report_upgrade_result(pHandle, pHandle->version, IOT_RES_TYPE_FILE_DEL_SUCCESS);
        }
    } else if (strcmp(json_method, METHOD_RES_REQ_URL_RESP) == 0) {
        char *request_id = LITE_json_value_of(FIELD_REQUEST_ID, json_str);
        if (!request_id) {
            Log_e("no request_id found");
            goto exit;
        }
        uint32_t     id   = atoi(request_id);
        ResPostInfo *info = _get_resource_info_by_request_id(handle, id);
        if (info) {
            char *res_token = LITE_json_value_of(FIELD_RESOURCE_TOKEN, json_str);
            if (!res_token) {
                Log_e("parse request_token fail");
                HAL_Free(request_id);
                goto exit;
            }
            char *res_url = LITE_json_value_of(FIELD_RESOURCE_URL, json_str);
            if (!res_url) {
                Log_e("parse request_url fail");
                HAL_Free(request_id);
                HAL_Free(res_url);
                goto exit;
            }

            int ret = _post_resource_to_cos(res_url, info);
            if (ret == QCLOUD_RET_SUCCESS) {
                _resource_report_post_result(pHandle, res_token, IOT_RES_TYPE_POST_SUCCESS);
            } else {
                _resource_report_post_result(pHandle, res_token, IOT_RES_TYPE_POST_FAIL);
            }

            char res_msg[MSG_REPORT_LEN];
            HAL_Snprintf(res_msg, MSG_REPORT_LEN,
                         "{\"resource_token\": \"%s\",\"request_id\": \"%s\", \"result\": \"%d\"}", res_token,
                         request_id, ret);
            Log_d("res_msg:%s", res_msg);
            pHandle->usr_cb(pHandle->usr_context, json_str, msg_len, IOT_RES_EVENT_REQUEST_URL_RESP);
            HAL_Free(res_token);
            HAL_Free(res_url);
            HAL_Free(info->res_name);
            HAL_Free(info->res_version);
            HAL_MutexLock(pHandle->mutex);
            list_remove(pHandle->res_wait_post_list, list_find(pHandle->res_wait_post_list, info));
            HAL_MutexUnlock(pHandle->mutex);
        } else {
            Log_e("request_id %s not found", request_id);
        }

        HAL_Free(request_id);
    } else {
        Log_e("invalid method:%s", json_method);
    }

exit:
    HAL_Free(json_method);
}

/* init & destroy */
void *IOT_Resource_Init(const char *product_id, const char *device_name, void *mqtt_client,
                        OnResourceEventUsrCallback usr_cb, void *usr_context)
{
    POINTER_SANITY_CHECK(product_id, NULL);
    POINTER_SANITY_CHECK(device_name, NULL);
    POINTER_SANITY_CHECK(mqtt_client, NULL);
    int rc;

    ResourceHandle *handle;
    handle = HAL_Malloc(sizeof(ResourceHandle));
    if (!handle) {
        Log_e("allocate failed");
        goto exit;
    }

    memset(handle, 0, sizeof(ResourceHandle));
    handle->usr_cb    = usr_cb;
    handle->ch_signal = mqtt_client;

    // init service
    rc = qcloud_service_mqtt_init(product_id, device_name, mqtt_client);
    if (rc < 0) {
        Log_e("service init failed: %d", rc);
        goto exit;
    }

    rc = qcloud_service_mqtt_event_register(eSERVICE_RESOURCE, _resource_msg_callback, handle);
    if (QCLOUD_RET_SUCCESS != rc) {
        Log_e("register service event %d fail", eSERVICE_RESOURCE);
        goto exit;
    }

    handle->md5 = utils_md5_create();
    if (!handle->md5) {
        Log_e("initialize md5 failed");
        goto exit;
    }

    handle->product_id         = product_id;
    handle->device_name        = device_name;
    handle->state              = IOT_RES_STATE_INITTED;
    handle->usr_context        = usr_context;
    handle->request_id         = 0;
    handle->res_wait_post_list = list_new();
    if (handle->res_wait_post_list) {
        handle->res_wait_post_list->free = HAL_Free;
    } else {
        Log_e("create res_wait_post_list fail");
        goto exit;
    }

    handle->mutex = HAL_MutexCreate();
    if (handle->mutex == NULL) {
        Log_e("create res mutex fail");
        goto exit;
    }

    return handle;

exit:
    qcloud_service_mqtt_event_register(eSERVICE_RESOURCE, NULL, NULL);
    if (handle) {
        if (handle->md5) {
            utils_md5_delete(handle->md5);
        }

        if (handle->res_wait_post_list) {
            list_destroy(handle->res_wait_post_list);
        }

        if (handle->mutex) {
            HAL_MutexDestroy(handle->mutex);
        }

        HAL_Free(handle);
    }
    return NULL;
}

int IOT_Resource_Destroy(void *handle)
{
    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);

    ResourceHandle *pHandle = (ResourceHandle *)handle;

    if (!pHandle) {
        Log_e("handle is NULL");
        return QCLOUD_ERR_INVAL;
    }

    if (IOT_RES_STATE_UNINITTED == pHandle->state) {
        Log_e("handle is uninitialized");
        pHandle->err = IOT_RES_ERR_INVALID_STATE;
        return QCLOUD_ERR_FAILURE;
    }

    qcloud_service_mqtt_event_register(eSERVICE_RESOURCE, NULL, NULL);
    qcloud_url_download_deinit(pHandle->ch_fetch);
    utils_md5_delete(pHandle->md5);
    if (pHandle->res_wait_post_list) {
        list_destroy(pHandle->res_wait_post_list);
    }

    if (pHandle) {
        HAL_Free(pHandle->url);
        HAL_Free(pHandle->version);
        HAL_Free(pHandle->file_name);
        HAL_Free(pHandle->file_type);
        HAL_Free(pHandle);
    }

    return QCLOUD_RET_SUCCESS;
}

/* md5 function */
void IOT_Resource_UpdateClientMd5(void *handle, char *buff, uint32_t size)
{
    POINTER_SANITY_CHECK_RTN(handle);
    POINTER_SANITY_CHECK_RTN(buff);

    ResourceHandle *pHandle = (ResourceHandle *)handle;
    utils_md5_update(pHandle->md5, (const unsigned char *)buff, size);
}

int IOT_Resource_ResetClientMD5(void *handle)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    utils_md5_delete(pHandle->md5);
    pHandle->md5 = utils_md5_create();
    if (!pHandle->md5) {
        return QCLOUD_ERR_FAILURE;
    }
    return QCLOUD_RET_SUCCESS;
}

/* download */
int IOT_Resource_StartDownload(void *handle, uint32_t offset, uint32_t size)
{
    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);

    ResourceHandle *pHandle = (ResourceHandle *)handle;

    int ret;

    Log_d("to download FW from offset: %u, size: %u", offset, size);
    pHandle->size_fetched = offset;

    if (offset == 0) {
        ret = IOT_Resource_ResetClientMD5(pHandle);
        if (QCLOUD_RET_SUCCESS != ret) {
            Log_e("initialize md5 failed");
            return QCLOUD_ERR_FAILURE;
        }
    }

    qcloud_url_download_deinit(pHandle->ch_fetch);
    pHandle->ch_fetch = qcloud_url_download_init(pHandle->url, offset, size);
    if (!pHandle->ch_fetch) {
        Log_e("Initialize fetch module failed");
        return QCLOUD_ERR_FAILURE;
    }

#ifdef OTA_USE_HTTPS
    ret = qcloud_url_download_connect(pHandle->ch_fetch, 1);
#else
    ret = qcloud_url_download_connect(pHandle->ch_fetch, 0);
#endif

    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("Connect fetch module failed");
        pHandle->state = IOT_RES_STATE_DISCONNECTED;
    }

    return ret;
}

int IOT_Resource_IsFetching(void *handle)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    if (!handle) {
        Log_e("handle is NULL");
        return 0;
    }

    if (IOT_RES_STATE_UNINITTED == pHandle->state) {
        Log_e("handle is uninitialized");
        pHandle->err = IOT_RES_ERR_INVALID_STATE;
        return 0;
    }

    return (IOT_RES_STATE_FETCHING == pHandle->state);
}

int IOT_Resource_IsFetchFinish(void *handle)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    if (!handle) {
        Log_e("handle is NULL");
        return 0;
    }

    if (IOT_RES_STATE_UNINITTED == pHandle->state) {
        Log_e("handle is uninitialized");
        pHandle->err = IOT_RES_ERR_INVALID_STATE;
        return 0;
    }

    return (IOT_RES_STATE_FETCHED == pHandle->state);
}

int IOT_Resource_FetchYield(void *handle, char *buf, uint32_t buf_len, uint32_t timeout_s)
{
    int             ret;
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(buf, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(buf_len, QCLOUD_ERR_INVAL);

    if (IOT_RES_STATE_FETCHING != pHandle->state) {
        pHandle->err = IOT_RES_ERR_INVALID_STATE;
        return QCLOUD_ERR_FAILURE;
    }

    ret = qcloud_url_download_fetch(pHandle->ch_fetch, buf, buf_len, timeout_s);
    if (ret < 0) {
        pHandle->state = IOT_RES_STATE_FETCHED;
        pHandle->err   = IOT_RES_ERR_FETCH_FAILED;
        if (ret == QCLOUD_ERR_HTTP_AUTH) {  // OTA auth failed
            pHandle->report_rc = _resource_report_upgrade_result(pHandle, pHandle->version, IOT_RES_TYPE_AUTH_FAIL);
            pHandle->err       = IOT_RES_ERR_FETCH_AUTH_FAIL;
        } else if (ret == QCLOUD_ERR_HTTP_NOT_FOUND) {  // fetch not existed
            pHandle->report_rc =
                _resource_report_upgrade_result(pHandle, pHandle->version, IOT_RES_TYPE_FILE_NOT_EXIST);
            pHandle->err = IOT_RES_ERR_FETCH_NOT_EXIST;
        } else if (ret == QCLOUD_ERR_HTTP_TIMEOUT) {  // fetch timeout
            pHandle->report_rc =
                _resource_report_upgrade_result(pHandle, pHandle->version, IOT_RES_TYPE_DOWNLOAD_TIMEOUT);
            pHandle->err = IOT_RES_ERR_FETCH_TIMEOUT;
        }
        return ret;
    } else if (0 == pHandle->size_fetched) {
        /* force report status in the first */
        _resource_report_progress(pHandle, 0, IOT_RES_TYPE_DOWNLOAD_BEGIN);

        InitTimer(&pHandle->report_timer);
        countdown(&pHandle->report_timer, 1);
    }

    pHandle->size_last_fetched = ret;
    pHandle->size_fetched += ret;

    /* report percent every second. */
    uint32_t percent = (pHandle->size_fetched * 100) / pHandle->size_file;
    if (percent == 100) {
        _resource_report_progress(pHandle, percent, IOT_RES_TYPE_DOWNLOADING);
    } else if (pHandle->size_last_fetched > 0 && expired(&pHandle->report_timer)) {
        _resource_report_progress(pHandle, percent, IOT_RES_TYPE_DOWNLOADING);
        countdown(&pHandle->report_timer, 1);
    }

    if (pHandle->size_fetched >= pHandle->size_file) {
        pHandle->state = IOT_RES_STATE_FETCHED;
    }

    utils_md5_update(pHandle->md5, (const unsigned char *)buf, ret);
    return ret;
}

/* report */
int IOT_Resource_ReportVersion(void *handle, uint16_t res_num, resInfo *res_list[])
{
    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);

    ResourceHandle *pHandle = (ResourceHandle *)handle;

    int   ret = QCLOUD_RET_SUCCESS;
    int   buff_len;
    char *msg_informed = NULL;

    if (res_num && !res_list) {
        Log_e("Invalid argument res_list");
        return QCLOUD_ERR_INVAL;
    }

    if (IOT_RES_STATE_UNINITTED == pHandle->state) {
        Log_e("handle is uninitialized");
        pHandle->err = IOT_RES_ERR_INVALID_STATE;
        ret          = QCLOUD_ERR_FAILURE;
        goto do_exit;
    }

    _reset_handle_status(pHandle);

    buff_len = res_num * RESOURCE_INFO_LEN_MAX + 128;
    if (NULL == (msg_informed = HAL_Malloc(buff_len))) {
        Log_e("allocate for msg_informed failed");
        pHandle->err = IOT_RES_ERR_MALLOC;
        ret          = QCLOUD_ERR_MALLOC;
        goto do_exit;
    }

    ret = _gen_resource_ver_info(msg_informed, buff_len, res_num, res_list);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("generate inform message failed");
        pHandle->err = ret;
        ret          = QCLOUD_ERR_FAILURE;
        goto do_exit;
    }

    ret = qcloud_service_mqtt_post_msg(pHandle->ch_signal, msg_informed, QOS1);
    if (0 > ret) {
        Log_e("Report version failed");
        pHandle->err = IOT_RES_ERR_REPORT_VERSION;
        ret          = QCLOUD_ERR_FAILURE;
        goto do_exit;
    }

do_exit:
    HAL_Free(msg_informed);

    return ret;
}

int IOT_Resource_ReportUpgradeBegin(void *handle)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;
    return _resource_report_upgrade_result(handle, pHandle->version, IOT_RES_TYPE_UPGRADE_BEGIN);
}

int IOT_Resource_ReportUpgradeSuccess(void *handle, const char *version)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;
    int             ret;

    if (!version) {
        ret = _resource_report_upgrade_result(handle, pHandle->version, IOT_RES_TYPE_UPGRADE_SUCCESS);
    } else {
        ret = _resource_report_upgrade_result(handle, version, IOT_RES_TYPE_UPGRADE_SUCCESS);
    }

    return ret;
}

int IOT_Resource_ReportUpgradeFail(void *handle, const char *version)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;
    int             ret;

    if (!version) {
        ret = _resource_report_upgrade_result(handle, pHandle->version, IOT_RES_TYPE_UPGRADE_FAIL);
    } else {
        ret = _resource_report_upgrade_result(handle, version, IOT_RES_TYPE_UPGRADE_FAIL);
    }

    return ret;
}

int IOT_Resource_ReportSpaceNotEnough(void *handle, const char *version)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;
    int             ret;

    if (!version) {
        ret = _resource_report_upgrade_result(handle, pHandle->version, IOT_RES_TYPE_SPACE_NOT_ENOUGH);
    } else {
        ret = _resource_report_upgrade_result(handle, version, IOT_RES_TYPE_SPACE_NOT_ENOUGH);
    }

    return ret;
}

/* get status*/
int IOT_Resource_Ioctl(void *handle, IOT_RES_CmdType type, void *buf, size_t buf_len)
{
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    POINTER_SANITY_CHECK(handle, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(buf, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(buf_len, QCLOUD_ERR_INVAL);

    if (pHandle->state < IOT_RES_STATE_FETCHING) {
        pHandle->err = IOT_RES_ERR_INVALID_STATE;
        return QCLOUD_ERR_FAILURE;
    }

    switch (type) {
        case IOT_RES_CMD_FETCHED_SIZE:
            if ((4 != buf_len) || (0 != ((unsigned long)buf & 0x3))) {
                Log_e("Invalid parameter");
                pHandle->err = IOT_RES_ERR_INVALID_PARAM;
                return QCLOUD_ERR_FAILURE;
            } else {
                *((uint32_t *)buf) = pHandle->size_fetched;
                return 0;
            }

        case IOT_RES_CMD_FILE_SIZE:
            if ((4 != buf_len) || (0 != ((unsigned long)buf & 0x3))) {
                Log_e("Invalid parameter");
                pHandle->err = IOT_RES_ERR_INVALID_PARAM;
                return QCLOUD_ERR_FAILURE;
            } else {
                *((uint32_t *)buf) = pHandle->size_file;
                break;
            }

        case IOT_RES_CMD_FILE_TYPE:
            strncpy(buf, pHandle->file_type, buf_len);
            ((char *)buf)[buf_len - 1] = '\0';
            break;

        case IOT_RES_CMD_VERSION:
            strncpy(buf, pHandle->version, buf_len);
            ((char *)buf)[buf_len - 1] = '\0';
            break;

        case IOT_RES_CMD_MD5SUM:
            strncpy(buf, pHandle->md5sum, buf_len);
            ((char *)buf)[buf_len - 1] = '\0';
            break;

        case IOT_RES_CMD_FILE_NAME:
            strncpy(buf, pHandle->file_name, buf_len);
            ((char *)buf)[buf_len - 1] = '\0';
            break;

        case IOT_RES_CMD_CHECK_FIRMWARE:
            if ((4 != buf_len) || (0 != ((unsigned long)buf & 0x3))) {
                Log_e("Invalid parameter");
                pHandle->err = IOT_RES_ERR_INVALID_PARAM;
                return QCLOUD_ERR_FAILURE;
            } else if (pHandle->state != IOT_RES_STATE_FETCHED) {
                pHandle->err = IOT_RES_ERR_INVALID_STATE;
                Log_e("Firmware can be checked in IOT_RES_STATE_FETCHED state only");
                return QCLOUD_ERR_FAILURE;
            } else {
                char md5_str[33];
                utils_md5_finish_str(pHandle->md5, md5_str);
                Log_d("origin=%s, now=%s", pHandle->md5sum, md5_str);
                if (0 == strcmp(pHandle->md5sum, md5_str)) {
                    *((uint32_t *)buf) = 1;
                } else {
                    *((uint32_t *)buf) = 0;
                    // report MD5 inconsistent
                    _resource_report_upgrade_result(pHandle, pHandle->version, IOT_RES_TYPE_MD5_NOT_MATCH);
                }
                return 0;
            }

        default:
            Log_e("invalid cmd type");
            pHandle->err = IOT_RES_ERR_INVALID_PARAM;
            return QCLOUD_ERR_FAILURE;
    }

    return 0;
}

int IOT_Resource_GetLastError(void *handle)
{
    POINTER_SANITY_CHECK(handle, IOT_OTA_ERR_INVALID_PARAM);
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    return pHandle->err;
}

int IOT_Resource_GetReportResult(void *handle)
{
    POINTER_SANITY_CHECK(handle, IOT_OTA_ERR_INVALID_PARAM);
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    return pHandle->report_rc;
}

int IOT_Resource_Post_Request(void *handle, uint32_t timeout_ms, const char *res_name, char *res_version,
                              char *res_type)
{
    POINTER_SANITY_CHECK(handle, IOT_OTA_ERR_INVALID_PARAM);
    ResourceHandle *pHandle      = (ResourceHandle *)handle;
    char *          msg_reported = NULL;
    int             ret          = QCLOUD_RET_SUCCESS;

    pHandle->request_id++;

    ResPostInfo *info = (ResPostInfo *)HAL_Malloc(sizeof(ResPostInfo));
    info->request_id  = pHandle->request_id;
    info->res_name    = strdup(res_name);
    info->res_version = strdup(res_version);
    info->res_type    = strdup(res_type);
    InitTimer(&(info->post_timer));
    countdown(&(info->post_timer), timeout_ms);
    ret = _add_resouce_info_to_post_list(handle, info);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("add resource to post list fail,rc:%d", ret);
        goto exit;
    }

    if (NULL == (msg_reported = HAL_Malloc(MSG_REPORT_LEN))) {
        Log_e("allocate for msg_reported failed");
        ret = QCLOUD_ERR_MALLOC;
        goto exit;
    }

    char *file_name_post = strrchr(res_name, '/');
    if (!file_name_post) {
        file_name_post = (char *)res_name;
    } else {
        file_name_post += 1;
    }
    ret = _gen_resource_report_msg(msg_reported, MSG_REPORT_LEN, file_name_post, res_version, res_type,
                                   pHandle->request_id, IOT_RES_TYPE_REQUEST_URL);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("generate resource inform message failed");
        goto exit;
    }
    Log_d("request:%s", msg_reported);
    ret = qcloud_service_mqtt_post_msg(pHandle->ch_signal, msg_reported, QOS1);
    if (ret < 0) {
        Log_e("Request url msg publish failed");
        goto exit;
    }

exit:

    if (msg_reported) {
        HAL_Free(msg_reported);
    }

    return (ret < 0) ? ret : pHandle->request_id;
}

int IOT_Resource_Report_Msg(void *handle, char *msg)
{
    POINTER_SANITY_CHECK(handle, IOT_OTA_ERR_INVALID_PARAM);
    ResourceHandle *pHandle = (ResourceHandle *)handle;

    return qcloud_service_mqtt_post_msg(pHandle->ch_signal, msg, QOS0);
}

#ifdef __cplusplus
}
#endif
