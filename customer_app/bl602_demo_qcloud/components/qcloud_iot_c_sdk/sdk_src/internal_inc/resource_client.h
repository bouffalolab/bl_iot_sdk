/*
 * Tencent is pleased to support the open source community by making IoT Hub available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef IOT_RESOURCE_CLIENT_H_
#define IOT_RESOURCE_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "qcloud_iot_export_resource.h"

#define MAX_RES_WAIT_POST (10)

typedef enum {
    eRESOURCE_PROGRESS,
    eRESOURCE_VERSION,
    eRESOURCE_UPGRADE_RESULT,
    eRESOURCE_POST_REQ,
    eRESOURCE_POST_RESULT
} eResourceReportType;

#ifdef __cplusplus
}
#endif

#endif /* IOT_RESOURCE_CLIENT_H_ */
