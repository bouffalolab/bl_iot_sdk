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

#ifndef QCLOUD_IOT_EXPORT_SYSTEM_H_
#define QCLOUD_IOT_EXPORT_SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IP_MAX_NUM     10
#define ONE_IP_MAX_LEN 24

typedef enum {
    eRESOURCE_TIME = 0,
    eRESOURCE_IP,
} eSysResourcType;

/**
 * @brief Get domain ip list for dns disaster recovery
 *
 * @param pClient           MQTTClient pointer
 * @param eType             type of sys resource to get
 * @param usrArg            usr arg to return the target resource
 * @return                  QCLOUD_RET_SUCCESS for success
 *                          otherwise, failure
 */
int IOT_Get_Sys_Resource(void *pClient, eSysResourcType eType, DeviceInfo *pDevInfo, void *usrArg);

#ifdef __cplusplus
}
#endif

#endif /* QCLOUD_IOT_EXPORT_COAP_H_ */