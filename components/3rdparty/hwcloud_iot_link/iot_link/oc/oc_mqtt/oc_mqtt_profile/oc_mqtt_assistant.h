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

#ifndef LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_AL_OC_MQTT_ASSISTANT_H_
#define LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_AL_OC_MQTT_ASSISTANT_H_

#include <cJSON.h>

//////////////////////////OC MQTT ASSISTANT INTERFACE///////////////////////////
/* msg type, json name, its value is string*/
#define cn_msg_type_name          "msgType"
/* msg type report data, json value */
#define cn_msg_type_device_req    "deviceReq"   ///< device report
#define cn_msg_type_cloud_req     "cloudReq"    ///< cloud command
#define cn_msg_type_device_resp   "deviceRsp"   ///< device response to the command

/* more data, json name, its value is int, 0 for no more data, 1 for more data */
#define cn_has_more_name "hasMore"
typedef enum
{
    en_oc_mqtt_has_more_no = 0,
    en_oc_mqtt_has_more_yes =1,
}en_oc_mqtt_has_more;


/* ServiceData array, json name, its value is ServiceData array */
#define cn_data_name "data"

/* ServiceData */
/* service id, json name, its value is string */
#define cn_service_id_name   "serviceId"

/* service data, json name, its value is an object defined in profile for the device */
#define cn_service_data_name "serviceData"

/* service data, json name, its value is string, format yyyyMMddTHHmmssZ such as 20161219T114920Z */
#define cn_service_time_name  "eventTime"


#define cn_cmd_name       "cmd"
#define cn_paras_name     "paras"
#define cn_mid_name       "mid"

#define cn_err_code_name  "errcode"
//typedef enum
//{
//    en_oc_mqtt_resp_code_ok = 0,
//    en_oc_mqtt_resp_code_err =1,
//}en_oc_mqtt_resp_code;

#define cn_body_name      "body"

/* deviceReq data msg jason format example to server
the message can be decoded in json or binary.
{
        "msgType":      "deviceReq",
        "hasMore":      0,
        "data": [{
                        "serviceId":    "serviceIdValue",
                        "serviceData": {
                                "defineData": "defineValue"
                        },
                        "eventTime":    "20161219T114920Z"
                }]
}
*/
/*
cloudReq data msg jason format example from server
{
    "msgType":"cloudReq",
    "serviceId":"serviceIdValue",
    "paras":{
        "paraName":"paraValue"
    },
    "cmd":"cmdValue",
    "hasMore":0,
    "mid":0
}
*/
/*
deviceRsp data msg jason format example to server
{
    "msgType":  "deviceRsp",
    "mid":  0,
    "errcode":  0,
    "hasMore":  0,
    "body": {
        "bodyParaName": "bodyParaValue"
    }
}
*/
typedef enum
{
    en_key_value_type_int = 0,
    en_key_value_type_string,
    en_key_value_type_array,
}en_value_type;

typedef struct
{
    char           *name;    ///< key name
    char           *buf;     ///< used to storage the key value
    int             len;     ///< how long the key value
    en_value_type   type;    ///< the value type
}tag_key_value;

typedef struct
{
    void            *next;
    tag_key_value    item;
}tag_key_value_list;

/**
 *
 * @brief:this data structure used for the message send and message receive
 *
 * */
typedef struct
{
    char                  *serviceid;
    tag_key_value_list    *paralst;
    char                  *eventtime;
    en_oc_mqtt_has_more    hasmore;
}tag_oc_mqtt_report;

///< use this function to format the message to json mode
cJSON *oc_mqtt_json_fmt_report(tag_oc_mqtt_report  *report);

/**
 * @brief: this data structure used for the command response
 *         when you receive a command, you should do the response
 * */
typedef struct
{

    int                     mid;     ///< should get from the command message
    int                     errcode; ///< error code
    en_oc_mqtt_has_more     hasmore; ///< has more or not
    tag_key_value_list     *bodylst; ///< response body
}tag_oc_mqtt_response;
///< use this function to format the response message to json mode
cJSON *oc_mqtt_json_fmt_response(tag_oc_mqtt_response *response);



#endif /* LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_AL_OC_MQTT_ASSISTANT_H_ */
