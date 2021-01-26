/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#ifndef LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_OTA_OTA_HTTPS_H_
#define LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_OTA_OTA_HTTPS_H_


///< this file implement the downloading profile
#ifndef CONFIG_OCMQTT_HTTPS_CACHELEN
#define CONFIG_OCMQTT_HTTPS_CACHELEN  1024
#endif

#ifndef CONFIG_OCMQTT_HTTPS_TIMEOUT
#define CONFIG_OCMQTT_HTTPS_TIMEOUT   (10*1000)
#endif

///< this function used for write the data to the flash
typedef int (*fn_binwrite)(int offset, uint8_t *buf, int len);
typedef enum
{
    EN_HTTPS_DOWNLOADLOG_BEGINDDOWNLOAD = 0,
    EN_HTTPS_DOWNLOADLOG_DOWNLOADTIMEOUT,
    EN_HTTPS_DOWNLOADLOG_DOWNLOADSUCCESS,
    EN_HTTPS_DOWNLOADLOG_NETCONNERR,
    EN_HTTPS_DOWNLOADLOG_PARAERR,
    EN_HTTPS_DOWNLOADLOG_MEMERR,
}en_https_downloadlog_t;
const char *https_eventlogname(en_https_downloadlog_t type);
typedef int (*fn_httpsdownload_event)(en_https_downloadlog_t type);
typedef struct
{
    const char *url;
    const char *signatural;
    const char *authorize;
    const char *version;
    int                 file_size;
    int                 file_offset;
    uint8_t             cache[CONFIG_OCMQTT_HTTPS_CACHELEN];
    int                 ota_type;
    fn_httpsdownload_event eventlog;
    fn_binwrite         file_write;
}ota_https_para_t;
int ota_https_download(ota_https_para_t *param);


#endif /* LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_OTA_OTA_HTTPS_H_ */
