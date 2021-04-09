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

#include "qutils_url_download.h"

#include <string.h>

#include "qcloud_iot_ca.h"
#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"
#include "qutils_httpc.h"
#include "qutils_param_check.h"

#define HTTP_HEAD_CONTENT_LEN 256

typedef struct {
    const char *   url;
    HTTPClient     http;      /* http client */
    HTTPClientData http_data; /* http client data */
} HTTPUrlDownloadHandle;

void *qcloud_url_download_init(const char *url, uint32_t offset, uint32_t size)
{
    POINTER_SANITY_CHECK(url, NULL);
    NUMBERIC_SANITY_CHECK(size, NULL);

    HTTPUrlDownloadHandle *handle = NULL;

    handle = HAL_Malloc(sizeof(HTTPUrlDownloadHandle));
    if (!handle) {
        Log_e("allocate for url download handle failed!");
        return NULL;
    }
    memset(handle, 0, sizeof(HTTPUrlDownloadHandle));

    handle->http.header = HAL_Malloc(HTTP_HEAD_CONTENT_LEN);
    if (!handle->http.header) {
        HAL_Free(handle);
        Log_e("allocate for http header failed!");
        return NULL;
    }
    memset(handle->http.header, 0, HTTP_HEAD_CONTENT_LEN);

    HAL_Snprintf(handle->http.header, HTTP_HEAD_CONTENT_LEN,
                 "Accept: "
                 "text/html,application/xhtml+xml,application/xml;q=0.9,*/"
                 "*;q=0.8\r\n"
                 "Accept-Encoding: gzip, deflate\r\n"
                 "Range: bytes=%d-%d\r\n",
                 offset, size);

    Log_d("head_content:%s", handle->http.header);

    handle->url = url;
    return handle;
}

int32_t qcloud_url_download_connect(void *handle, int https_enabled)
{
    IOT_FUNC_ENTRY;

    if (!handle) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_INVAL);
    }

    HTTPUrlDownloadHandle *pHandle = (HTTPUrlDownloadHandle *)handle;

    int         port   = 80;
    const char *ca_crt = NULL;

    if (strstr(pHandle->url, "https") && https_enabled) {
        port   = 443;
        ca_crt = iot_https_ca_get();
    }

    int32_t rc = qcloud_http_client_common(&pHandle->http, pHandle->url, port, ca_crt, HTTP_GET, &pHandle->http_data);

    IOT_FUNC_EXIT_RC(rc);
}

int32_t qcloud_url_download_fetch(void *handle, char *buf, uint32_t bufLen, uint32_t timeout_s)
{
    IOT_FUNC_ENTRY;

    if (!handle) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_INVAL);
    }

    HTTPUrlDownloadHandle *pHandle      = (HTTPUrlDownloadHandle *)handle;
    pHandle->http_data.response_buf     = buf;
    pHandle->http_data.response_buf_len = bufLen;
    int diff                            = pHandle->http_data.response_content_len - pHandle->http_data.retrieve_len;

    int rc = qcloud_http_recv_data(&pHandle->http, timeout_s * 1000, &pHandle->http_data);
    if (QCLOUD_RET_SUCCESS != rc) {
        IOT_FUNC_EXIT_RC(rc);
    }

    IOT_FUNC_EXIT_RC(pHandle->http_data.response_content_len - pHandle->http_data.retrieve_len - diff);
}

int qcloud_url_download_deinit(void *handle)
{
    IOT_FUNC_ENTRY;

    if (!handle) {
        IOT_FUNC_EXIT_RC(QCLOUD_RET_SUCCESS);
    }

    HTTPUrlDownloadHandle *pHandle = (HTTPUrlDownloadHandle *)handle;
    if (pHandle->http.network_stack.is_connected(&pHandle->http.network_stack)) {
        pHandle->http.network_stack.disconnect(&pHandle->http.network_stack);
    }
    HAL_Free(pHandle->http.header);
    HAL_Free(pHandle);

    IOT_FUNC_EXIT_RC(QCLOUD_RET_SUCCESS);
}

#ifdef __cplusplus
}
#endif
