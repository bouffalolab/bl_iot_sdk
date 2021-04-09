/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2018-2020 THL A29 Limited, a Tencent company. All rights
 reserved.

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

#ifndef __ASR_CLIENT_H__
#define __ASR_CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ASR_REQUEST        (20)
#define DEFAULT_REQ_TIMEOUT_MS (5000)
#define ASR_REQUEST_BUFF_LEN   (512)

typedef enum {
    eASR_REQ_IDLE = 0,
    eASR_REQ_INIT = 1,
    eASR_REQ_DONE = 2,
} eAsrReqState;

#ifdef __cplusplus
}
#endif

#endif /* __AT_H__ */
