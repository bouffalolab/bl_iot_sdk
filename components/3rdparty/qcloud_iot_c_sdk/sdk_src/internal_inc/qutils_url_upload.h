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

#ifndef UTILS_URL_UPLOAD_H_
#define UTILS_URL_UPLOAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void *qcloud_url_upload_init(const char *url, uint32_t content_len);

int32_t qcloud_url_upload_connect(void *handle, int method);

int32_t qcloud_url_upload_body(void *handle, char *data_buf, uint32_t data_Len, uint32_t timeout_ms);

int32_t qcloud_url_upload_recv_response(void *handle, char *response_buf, uint32_t bufLen, uint32_t timeout_ms);

int qcloud_url_upload_deinit(void *handle);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_URL_DOWNLOAD_H_ */
