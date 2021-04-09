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

#ifndef QCLOUD_IOT_EXPORT_RESOURCE_H_
#define QCLOUD_IOT_EXPORT_RESOURCE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "qcloud_iot_import.h"

//{"resource_name":"","version":"","resource_type":""},
#define RESOURCE_VERSION_STR_LEN_MIN (1)
#define RESOURCE_VERSION_STR_LEN_MAX (32)
#define RESOURCE_NAME_STR_LEN_MAX    (64)
#define RESOURCE_TYPE_STR_LEN_MAX    (10)  
#define RESOURCE_INFO_FIXED_LEN      (53)
#define RESOURCE_INFO_LEN_MAX \
    (RESOURCE_VERSION_STR_LEN_MAX + RESOURCE_NAME_STR_LEN_MAX + RESOURCE_INFO_FIXED_LEN + RESOURCE_TYPE_STR_LEN_MAX)

#define RESOURCE_TYPE_FILE			"FILE"
#define RESOURCE_TYPE_AUDIO			"AUDIO"
#define RESOURCE_TYPE_VOICE			"VOICE"
#define RESOURCE_TYPE_VIDEO			"VIDEO"

/* error code of resource update */
typedef enum {
    IOT_RES_ERR_FAIL                  = -1,
    IOT_RES_ERR_INVALID_PARAM         = -2,
    IOT_RES_ERR_INVALID_STATE         = -3,
    IOT_RES_ERR_STR_TOO_LONG          = -4,
    IOT_RES_ERR_FETCH_FAILED          = -5,
    IOT_RES_ERR_FETCH_NOT_EXIST       = -6,
    IOT_RES_ERR_FETCH_AUTH_FAIL       = -7,
    IOT_RES_ERR_FETCH_TIMEOUT         = -8,
    IOT_RES_ERR_MALLOC                = -9,
    IOT_RES_ERR_REPORT_VERSION        = -10,
    IOT_RES_ERR_REPORT_PROGRESS       = -11,
    IOT_RES_ERR_REPORT_UPGRADE_RESULT = -12,
    IOT_RES_ERR_NONE                  = 0
} IOT_RES_ErrorCode;

/* type of resource update state */
typedef enum {
    IOT_RES_STATE_UNINITTED = 0, /* un-initted */
    IOT_RES_STATE_INITTED,       /* initted */
    IOT_RES_STATE_FETCHING,      /* fetching */
    IOT_RES_STATE_FETCHED,       /* fetched */
    IOT_RES_STATE_DELETING,      /* deleting */
    IOT_RES_STATE_DELETED,       /* deleted */
    IOT_RES_STATE_DISCONNECTED   /* disconnected */
} IOT_RES_StateCode;

/* cmd type of resource update */
typedef enum {
    IOT_RES_CMD_FETCHED_SIZE = 0, /* Size of firmware fetched */
    IOT_RES_CMD_FILE_SIZE,        /* Total size of firmware */
    IOT_RES_CMD_MD5SUM,           /* firmware md5 checksum (string) */
    IOT_RES_CMD_VERSION,          /* firmware version (string) */
    IOT_RES_CMD_FILE_NAME,        /* file name (string) */
    IOT_RES_CMD_FILE_TYPE,        /* file type */
    IOT_RES_CMD_CHECK_FIRMWARE    /* check firmware */
} IOT_RES_CmdType;

/* report type of resource update */
typedef enum {
    IOT_RES_TYPE_DOWNLOAD_TIMEOUT = -1,
    IOT_RES_TYPE_FILE_NOT_EXIST   = -2,
    IOT_RES_TYPE_AUTH_FAIL        = -3,
    IOT_RES_TYPE_MD5_NOT_MATCH    = -4,
    IOT_RES_TYPE_UPGRADE_FAIL     = -5,
    IOT_RES_TYPE_SPACE_NOT_ENOUGH = -6,
    IOT_RES_TYPE_FILE_DEL_FAIL    = -7,
    IOT_RES_TYPE_POST_FAIL        = -8,
    IOT_RES_TYPE_NONE             = 0,
    IOT_RES_TYPE_DOWNLOAD_BEGIN   = 1,
    IOT_RES_TYPE_DOWNLOADING      = 2,
    IOT_RES_TYPE_UPGRADE_BEGIN    = 3,
    IOT_RES_TYPE_UPGRADE_SUCCESS  = 4,
    IOT_RES_TYPE_FILE_DEL_SUCCESS = 5,
    IOT_RES_TYPE_REQUEST_URL      = 6,
    IOT_RES_TYPE_POST_SUCCESS     = 7,

} IOT_RES_ReportType;

/* usr event of resource update */
typedef enum {
    IOT_RES_EVENT_DEL_RESOURCE        = 0,
    IOT_RES_EVENT_REPORT_VERSION_RESP = 1,
    IOT_RES_EVENT_REQUEST_URL_RESP    = 2,
} IOT_RES_UsrEvent;

/* resource info filed */
typedef struct {
    char *res_name;
    char *res_ver;
    char *res_type;
} resInfo;

typedef int (*OnResourceEventUsrCallback)(void *pContext, const char *msg, uint32_t msgLen, IOT_RES_UsrEvent event);

//=========== init & destory =================//

/**
 * @brief Init resource module
 *        MQTT Client should be constructed beforehand
 *
 * @param product_id:   product Id
 * @param device_name:  device name
 * @param mqtt_client:  resouce MQTT channel
 * @param usr_cb:       user call back
 * @param usr_context:  user context
 *
 * @return a valid resource module handle when success, or NULL otherwise
 */
void *IOT_Resource_Init(const char *product_id, const char *device_name, void *mqtt_client,
								OnResourceEventUsrCallback usr_cb, void *usr_context);

/**
 * @brief Destroy resource module
 *
 * @param handle: resource module handle
 *
 * @return QCLOUD_RET_SUCCESS when success, or err code for failure
 */
int IOT_Resource_Destroy(void *handle);

//=========== md5 function =================//

/**
 * @brief Update MD5 of local resource
 *
 * @param handle: resource module handle
 * @param buff: buff to resource
 * @param size: size of buff
 *
 * @return
 */
void IOT_Resource_UpdateClientMd5(void *handle, char *buff, uint32_t size);

/**
 * @brief Reset MD5 context
 *
 * @param handle: resource module handle
 *
 * @return QCLOUD_RET_SUCCESS when success, or err code for failure
 */
int IOT_Resource_ResetClientMD5(void *handle);

//=========== download =================//

/**
 * @brief Setup HTTP connection and prepare resource download
 *
 * @param handle: resource module handle
 * @param offset: offset of resource downloaded
 * @param size: size of resource
 *
 * @return QCLOUD_RET_SUCCESS when success, or err code for failure
 */
int IOT_Resource_StartDownload(void *handle, uint32_t offset, uint32_t size);

/**
 * @brief Check if resource is fetching/downloading
 *
 * @param handle: resource module handle
 *
 * @retval 1 : Yes.
 * @retval 0 : No.
 */
int IOT_Resource_IsFetching(void *handle);

/**
 * @brief Check if resource fetching/downloading is finished
 *
 * @param handle: resource module handle
 *
 * @retval 1 : Yes.
 * @retval 0 : No.
 */
int IOT_Resource_IsFetchFinish(void *handle);

/**
 * @brief Download resource from HTTP server and save to buffer
 *
 * @param handle:       resource module handle
 * @param buf:          buffer to store resource
 * @param buf_len:      length of buffer
 * @param timeout_s:    timeout value in second
 *
 * @retval      < 0 : error code
 * @retval        0 : no data is downloaded in this period and timeout happen
 * @retval (0, len] : size of the downloaded data
 */
int IOT_Resource_FetchYield(void *handle, char *buf, uint32_t buf_len, uint32_t timeout_s);

//=========== report =================//

/**
 * @brief Report local resource version list to server
 *        NOTE: do this report before real download
 *
 * @param handle: resource module handle
 * @param ver_list:  local resource version list
 *
 * @return packet id (>=0) when success, or err code (<0) for failure
 */
int IOT_Resource_ReportVersion(void *handle, uint16_t res_num, resInfo *res_list[]);

/**
 * @brief Report upgrade begin to server
 *
 * @param handle: resource module handle
 *
 * @return packet id (>=0) when success, or err code (<0) for failure
 */
int IOT_Resource_ReportUpgradeBegin(void *handle);

/**
 * @brief Report upgrade success to server
 *
 * @param handle: resource module handle
 * @param version:  version string of firmware to upgrade
 *
 * @return packet id (>=0) when success, or err code (<0) for failure
 */
int IOT_Resource_ReportUpgradeSuccess(void *handle, const char *version);

/**
 * @brief Report upgrade fail to server
 *
 * @param handle: resource module handle
 * @param version:  version string of firmware to upgrade
 *
 * @return packet id (>=0) when success, or err code (<0) for failure
 */
int IOT_Resource_ReportUpgradeFail(void *handle, const char *version);

/**
 * @brief Report space not enough to server
 *
 * @param handle: resource module handle
 * @param version:  version string of firmware to upgrade
 *
 * @return packet id (>=0) when success, or err code (<0) for failure
 */
int IOT_Resource_ReportSpaceNotEnough(void *handle, const char *version);

//=========== get status =================//

/**
 * @brief Get resource info (file name, version, file_size, MD5, download state) from resource module
 *
 * @param handle:   resource module handle
 * @param type:     type of info to get, refer to IOT_RES_CmdType
 * @param buf:      buffer for the data
 * @param buf_len:  length of buffer
 * @return
      NOTE:
      1) if type==IOT_RES_CMD_FETCHED_SIZE, 'buf' = uint32_t pointer, 'buf_len' = 4
      2) if type==IOT_RES_CMD_FILE_SIZE, 'buf' = uint32_t pointer, 'buf_len' = 4
      3) if type==IOT_RES_CMD_MD5SUM, 'buf' = char array buffer, 'buf_len = 33
      4) if type==IOT_RES_CMD_VERSION, 'buf'= char array buffer, 'buf_len > RESOURCE_VERSION_STR_LEN_MAX
      5) if type==IOT_RES_CMD_FILE_NAME, 'buf'= char array buffer, 'buf_len > RESOURCE_NAME_STR_LEN_MAX
      6) if type==IOT_RES_CMD_FILE_TYPE, 'buf'= char array buffer, 'buf_len' = 5
      7) if type==IOT_RES_CMD_CHECK_FIRMWARE, 'buf' = uint32_t pointer, 'buf_len' = 4
 *
 * @retval   0 : success
 * @retval < 0 : error code for failure
 */
int IOT_Resource_Ioctl(void *handle, IOT_RES_CmdType type, void *buf, size_t buf_len);

/**
 * @brief Get error code of last operation
 *
 * @param handle: resource module handle
 *
 * @return error code
 */
int IOT_Resource_GetLastError(void *handle);

/**
 * @brief Get result of _resource_report_upgrade_result in IOT_Resource_FetchYield
 *
 * @param handle: resource module handle
 *
 * @return QCLOUD_RET_SUCCESS when success, or err code for failure
 */
int IOT_Resource_GetReportResult(void *handle);

/**
 * @brief publish msg to resource topic
 *
 * @param handle: resource module handle
 *
 * @param msg: msg to be reported
 *
 * @return QCLOUD_RET_SUCCESS when success, or err code for failure
 */
int IOT_Resource_Report_Msg(void *handle, char *msg);

//=========== request_url =================//

/**
 * @brief request url for resource post
 *
 * @param handle: resource module handle
 *
 * @param timeout_ms: request timeout
 *
 * @param res_name:  resource name to be posted
 *
 * @param res_version:  resource version to be posted
 *
 * @param res_type:  resource type to be posted
 * 
 * @return request id (>0) when success, or err code (<0) for failure
 */
int IOT_Resource_Post_Request(void *handle, uint32_t timeout_ms, const char *res_name, char *res_version, char *res_type);

#ifdef __cplusplus
}
#endif

#endif /* QCLOUD_IOT_EXPORT_OTA_H_ */
