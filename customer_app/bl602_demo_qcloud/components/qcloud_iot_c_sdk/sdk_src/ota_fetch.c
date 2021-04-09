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

#include "ota_fetch.h"

#include <string.h>

#include "qcloud_iot_ca.h"
#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"
#include "qutils_url_download.h"

void *ofc_Init(const char *url, uint32_t offset, uint32_t size)
{
    return qcloud_url_download_init(url, offset, size);
}

int32_t qcloud_ofc_connect(void *handle)
{
#ifdef OTA_USE_HTTPS
    return qcloud_url_download_connect(handle, 1);
#endif
    return qcloud_url_download_connect(handle, 0);
}

int32_t qcloud_ofc_fetch(void *handle, char *buf, uint32_t bufLen, uint32_t timeout_s)
{
    int rc = qcloud_url_download_fetch(handle, buf, bufLen, timeout_s);
    if (QCLOUD_RET_SUCCESS != rc) {
        if (rc == QCLOUD_ERR_HTTP_NOT_FOUND)
            IOT_FUNC_EXIT_RC(IOT_OTA_ERR_FETCH_NOT_EXIST);

        if (rc == QCLOUD_ERR_HTTP_AUTH)
            IOT_FUNC_EXIT_RC(IOT_OTA_ERR_FETCH_AUTH_FAIL);

        if (rc == QCLOUD_ERR_HTTP_TIMEOUT)
            IOT_FUNC_EXIT_RC(IOT_OTA_ERR_FETCH_TIMEOUT);
    }
    IOT_FUNC_EXIT_RC(rc);
}

int qcloud_ofc_deinit(void *handle)
{
    return qcloud_url_download_deinit(handle);
}

#ifdef __cplusplus
}
#endif
