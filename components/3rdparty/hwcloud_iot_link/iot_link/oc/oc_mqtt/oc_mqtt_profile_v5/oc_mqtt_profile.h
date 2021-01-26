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

#ifndef LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_PROFILE_OC_MQTT_PROFILE_H_
#define LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_PROFILE_OC_MQTT_PROFILE_H_

#include <stdint.h>
#include <oc_mqtt_al.h>

///< UP means the device send data to the cloud
typedef enum
{
    EN_OC_MQTT_PROFILE_MSG_TYPE_UP_MSGUP = 0,            ///< DEVICE REPORT MESSAG DIRECTLY
    EN_OC_MQTT_PROFILE_MSG_TYPE_UP_PROPERTYREPORT,       ///< DEVICE REPORT PROPERTY
    EN_OC_MQTT_PROFILE_MSG_TYPE_UP_SUBPROPERTYREPORT,    ///< GATWAY REPORT SUBDEVICEPROPERTY
    EN_OC_MQTT_PROFILE_MSG_TYPE_UP_PROPERTYSETRESPONSE,  ///< RESPONSE TO THE PROPERTY SET
    EN_OC_MQTT_PROFILE_MSG_TYPE_UP_PROPERTYGETRESPONSE,  ///< RESPONSE TO THE PROPERTY GET
    EN_OC_MQTT_PROFILE_MSG_TYPE_UP_CMDRESPONSE,          ///< RESPONSE TO THE COMMAND
    EN_OC_MQTT_PROFILE_MSG_TYPE_UP_LAST,
}en_oc_mqtt_profile_msg_type_up_t;


///< DOWN means the cloud send data to the device
typedef enum
{
    EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_MSGDOWN = 0,        ///< THIS IS THE MESSAGE DOWN
    EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_COMMANDS,           ///< THIS IS THE PLATFORM COMMANDS
    EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_PROPERTYSET,        ///< THIS IS THE PLATFORM SET PROPERTY
    EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_PROPERTYGET,        ///< THIS IS THE PLATFORM GET PROPERTY
    EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_EVENT,              ///< THIS IS THE EVENT
    EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_LAST,
}en_oc_mqtt_profile_msg_type_down_t;


////< enum all the data type for the oc profile
typedef enum
{
    EN_OC_MQTT_PROFILE_VALUE_INT = 0,
    EN_OC_MQTT_PROFILE_VALUE_LONG,
    EN_OC_MQTT_PROFILE_VALUE_FLOAT,
    EN_OC_MQTT_PROFILE_VALUE_DOUBLE,
    EN_OC_MQTT_PROFILE_VALUE_STRING,           ///< must be ended with '\0'
    EN_OC_MQTT_PROFILE_VALUE_LAST,
}en_oc_profile_data_t;


typedef struct
{
    void                 *nxt;   ///< ponit to the next key
    char                 *key;
    en_oc_profile_data_t  type;
    void                 *value;
}oc_mqtt_profile_kv_t;


typedef struct
{
    en_oc_mqtt_profile_msg_type_down_t type;       ///< defined as en_oc_mqtt_profile_msg_type_down_t
    char *request_id;                              ///< get from the topic, NULL if not supplied
    void *msg;                                     ///< the send from the cloud platform
    int   msg_len;                                 ///< the message length
}oc_mqtt_profile_msgrcv_t;

/**
 * @brief: this the message from the cloud call back function
 *
 * @param[in] payload:defined as oc_mqtt_profile_msgrcv_t
 *
 * @return: not used yet
 *
 * */
typedef int (*fn_oc_mqtt_profile_rcvdeal)(oc_mqtt_profile_msgrcv_t *payload);

typedef struct
{
    int boostrap;              ///< we use the bootstrap mode or not

    int life_time;             ///< ping echo cycle
    char             *server_addr;
    char             *sevver_port;
    char             *device_id;
    char             *device_passwd;
    dtls_al_security_t security;

    fn_oc_mqtt_profile_rcvdeal   rcvfunc;
    fn_oc_mqtt_log               logfunc;

}oc_mqtt_profile_connect_t;

/**
 * @brief: use this function to connect to the cloud
 *
 * @param[in] payload: defined as oc_mqtt_profile_connect_t
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_connect(oc_mqtt_profile_connect_t *payload);

/**
 * @brief: use this function to disconnect to the cloud
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_disconnect(void);

typedef struct
{
    char *device_id;   ///< you could specify it,if NULL,then use the device_id which used to connect
    char *name;        ///< message name, could be NULL
    char *id;          ///< message id, could be NULL
    void *msg;         ///< message to send
    int   msg_len;     ///< message length
}oc_mqtt_profile_msgup_t;


/**
 * @brief: use this function to send data to the platform without profile decode
 *
 * @param[in] deviceid: the cloud message receiver, if NULL then send to the connected one
 *
 * @param[in] payload: defined as oc_mqtt_profile_msgup_t
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_msgup(char *deviceid,oc_mqtt_profile_msgup_t *payload);


typedef struct
{
   void *nxt;
   char *service_id;                         ///< the service id in the profile, which could not be NULL
   char *event_time;                         ///< eventtime, which could be NULL means use the platform time
   oc_mqtt_profile_kv_t *service_property;   ///< the property in the profile, which could not be NULL
}oc_mqtt_profile_service_t;

/**
 * @brief: use this function to send data to the platform with profile decode
 *
 * @param[in] deviceid: the cloud message receiver, if NULL then send to the connected one
 *
 * @param[in] payload: properties list to send to the platform
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_propertyreport(char *deviceid,oc_mqtt_profile_service_t *payload);

typedef struct
{
    void *nxt;                                                  ///< maybe much more
    char                                *subdevice_id;          ///< the specified device, which could not be NULL
    oc_mqtt_profile_service_t           *subdevice_property;    ///< the property of the specified device, which could not be NULL
}oc_mqtt_profile_device_t;

/**
 * @brief: use this function to send data to the platform with profile decode
 *
 * @param[in] deviceid: the cloud message receiver, if NULL then send to the connected one
 *
 * @param[in] payload:defined as oc_mqtt_profile_device_t
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_gwpropertyreport(char *deviceid,oc_mqtt_profile_device_t *payload);


typedef struct
{
    int     ret_code;           ///< response code, 0 success while others failed
    char   *ret_description;    ///< response description,maybe used when failed
    char   *request_id;         ///< specified by the setproperty command
}oc_mqtt_profile_propertysetresp_t;
/**
 * @brief: use this function to send the response to the setproperty command
 *
 * @param[in] deviceid: the cloud message receiver, if NULL then send to the connected one
 *
 * @param[in] payload: description as oc_mqtt_profile_propertysetresp_t
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_propertysetresp(char *deviceid,oc_mqtt_profile_propertysetresp_t *payload);


typedef struct
{
    char *request_id;                              ///< specified by the getproperty command
    oc_mqtt_profile_service_t  *services;          ///< defined as oc_mqtt_profile_service_t
}oc_mqtt_profile_propertygetresp_t;

/**
 * @brief: use this function to send the response to the setproperty command

 * @param[in] deviceid: the cloud message receiver, if NULL then send to the connected one

 * @param[in] payload: description as oc_mqtt_profile_propertygetresp_t
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_propertygetresp(char *deviceid,oc_mqtt_profile_propertygetresp_t *payload);


typedef struct
{
    int     ret_code;           ///< response code, 0 success while others failed
    char   *ret_name;           ///< response description,maybe used when failed
    char   *request_id;         ///< specified by the message command
    oc_mqtt_profile_kv_t  *paras;///< the command paras

}oc_mqtt_profile_cmdresp_t;
/**
 * @brief: use this function to send the response to the setproperty command
 *
 * @param[in] deviceid: the cloud message receiver, if NULL then send to the connected one
 *
 * @param[in] payload: description as oc_mqtt_profile_cmdresp_t
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_cmdresp(char *deviceid,oc_mqtt_profile_cmdresp_t *payload);



typedef struct
{

    char   *object_device_id;           ///< target deice_id, optional
    char   *service_id;                 ///< service_id, optional
    char   *request_id;                 ///< the request_id, must be supplied by the service
}oc_mqtt_profile_shadowget_t;
/**
 * @brief: use this function to send get the platform shadow data
 *
 * @param[in] deviceid: the device we registered
 *
 * @param[in] payload: description as oc_mqtt_profile_p_t
 *
 * @return :defined as en_oc_mqtt_err_code_t
 *
 * */
int oc_mqtt_profile_getshadow(char *deviceid,oc_mqtt_profile_shadowget_t *payload);





#endif /* LITEOS_LAB_IOT_LINK_OC_OC_MQTT_OC_MQTT_PROFILE_OC_MQTT_PROFILE_H_ */
