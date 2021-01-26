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


#ifndef __OC_MQTT_AL_H
#define __OC_MQTT_AL_H


#include <stddef.h>
#include <stdint.h>
#include <mqtt_al.h>


///< the mode for the huawei OceanConnect  mode
///< bs: if bs then the connection will first connect the bootstrap server then the hub server
///< static:means we connect the server use the generated id and pwd when create device on the platform
///< nodeid:means we connect use the nodeid and pwd generated

typedef enum
{
    en_oc_mqtt_mode_bs_static_nodeid_hmacsha256_notimecheck_json =0,
    en_oc_mqtt_mode_nobs_static_nodeid_hmacsha256_notimecheck_json,
    en_oc_mqtt_mode_last,
}en_oc_mqtt_mode;

typedef enum
{
    en_oc_mqtt_err_ok          = 0,      ///< this means the status ok
    en_oc_mqtt_err_parafmt,              ///< this means the parameter err format
    en_oc_mqtt_err_network,              ///< this means the network wrong status
    en_oc_mqtt_err_conversion,           ///< this means the mqtt version err
    en_oc_mqtt_err_conclientid,          ///< this means the client id is err
    en_oc_mqtt_err_conserver,            ///< this means the server refused the service for some reason(likely the id and pwd)
    en_oc_mqtt_err_conuserpwd,           ///< bad user name or pwd
    en_oc_mqtt_err_conclient,            ///< the client id /user/pwd is right, but does not allowed
    en_oc_mqtt_err_subscribe,            ///< this means subscribe the topic failed
    en_oc_mqtt_err_unsubscribe,          ///< this means un-subscribe failed
    en_oc_mqtt_err_publish,              ///< this means publish the topic failed
    en_oc_mqtt_err_configured,           ///< this means we has configured, please deconfigured it and then do configure again
    en_oc_mqtt_err_noconfigured,         ///< this means we have not configure it yet,so could not connect
    en_oc_mqtt_err_noconected,           ///< this means the connection has not been built, so you could not send data
    en_oc_mqtt_err_gethubaddrtimeout,    ///< this means get the hub address timeout
    en_oc_mqtt_err_sysmem,               ///< this means the system memory is not enough
    en_oc_mqtt_err_system,               ///< this means that the system porting may have some problem,maybe not install yet
    en_oc_mqtt_err_last,
}en_oc_mqtt_err_code_t;


typedef enum
{
    en_oc_mqtt_log_connected = 0,
    en_oc_mqtt_log_disconnected,
}en_oc_mqtt_log_t;

typedef void (*fn_oc_mqtt_log)(en_oc_mqtt_log_t  logtype);


/** @brief this is the message dealer module for the application*/
typedef int (*fn_oc_mqtt_msg_deal)(void *arg,mqtt_al_msgrcv_t *msg);

typedef struct
{
    en_oc_mqtt_mode  boot_mode;            ///< if bs mode, then the server and port must be the bs server's
    uint16_t         lifetime;             ///< the keep alive time, used for the mqtt protocol
    char            *server_addr;          ///< server address:domain name or ip address
    char            *server_port;          ///< server port:
    ///< define for the tls
    dtls_al_security_t  security;          ///< used for the transport
    ///< define for the mqtt
    char                              *id;
    char                              *pwd;
    fn_oc_mqtt_msg_deal                msg_deal;       ///< when the agent receive any applciation data, please call this function
    void                              *msg_deal_arg;   ///< call back for the fn_oc_mqtt_msg_deal
    fn_oc_mqtt_log                     log_dealer;

}oc_mqtt_config_t;

///////////////////////////MQTT AGENT INTERFACE//////////////////////////////////
///< the returned code defines by en_oc_mqtt_err_code
typedef  int (*fn_oc_mqtt_config)(oc_mqtt_config_t *param);
typedef  int (*fn_oc_mqtt_deconfig)(void);
typedef  int (*fn_oc_mqtt_publish)(char *topic,uint8_t *msg,int msg_len,int qos);
typedef  int (*fn_oc_mqtt_subscribe)(char *topic, int qos);
typedef  int (*fn_oc_mqtt_unsubscribe)(char *topic);


/**
 * @brief this data structure defines the mqtt agent implement
 */

typedef struct
{
    fn_oc_mqtt_config      config;       ///< this function used for the configuration
    fn_oc_mqtt_deconfig    deconfig;     ///< this function used for the deconfig
    fn_oc_mqtt_publish     publish;      ///< this function added by the new device profile
    fn_oc_mqtt_subscribe   subscribe;    ///< this function make the tiny extended
    fn_oc_mqtt_unsubscribe unsubscribe;  ///< this function make the tiny extended
}oc_mqtt_op_t;

typedef struct
{
    const char         *name;     ///< this is the name for the ops
    oc_mqtt_op_t        op;
}oc_mqtt_t;

/**
 *@brief the mqtt agent should use this function to register the method for the application
 *
 *@param[in] opt, the operation method implement by the mqtt agent developer
 *
 *@return 0 success while -1 failed
 */
int oc_mqtt_register(const oc_mqtt_t *opt);

int oc_mqtt_unregister(const char *name);

/////////////////////////THE APPLICATION USER DEVELOPER INTERFACE//////////////
///< return code defines by en_oc_mqtt_err_code

/**
 * @brief the application use this function to configure the lwm2m agent
 *
 * @param[in] param, refer to oc_mqtt_config_t
 *
 * @return code: define by en_oc_mqtt_err_code while 0 means success
 */
int oc_mqtt_config(oc_mqtt_config_t *param);


/**
 * @brief the application use this function to send message to the default topic(old interface)
 *
 * @param[in] msg:the message to send
 *
 * @param[in] msg_len:the message length
 *
 * @param[in] qos: defines as the mqtt does
 *
 * @return code: define by en_oc_mqtt_err_code while 0 means success
 */
int oc_mqtt_report(uint8_t *msg,int len, int qos);

/**
 *@brief: the application use this function to deconfigure the mqtt agent
 *
 * @return code: define by en_oc_mqtt_err_code while 0 means success
 */

int oc_mqtt_deconfig(void);

/**
 * @brief the application use this function to publish message to specified topic
 *
 * @param[in] topic: the destination topic
 *
 * @param[in] msg:the message to send
 *
 * @param[in] msg_len:the message length
 *
 * @return code: define by en_oc_mqtt_err_code while 0 means success
 */
int oc_mqtt_publish(char *topic,uint8_t *msg,int msg_len,int qos);

/**
 * @brief the application use this function to subscribe the specified topic
 *
 * @param[in] topic: the destination topic
 *
 * @param[in] qos:the topic qos
 *
 * @return code: define by en_oc_mqtt_err_code while 0 means success
 */
 int oc_mqtt_subscribe(char *topic,int qos);

/**
 * @brief the application use this function to unsubscribe the specified topic
 *
 * @param[in] topic: the destination topic
 *
 * @param[in] qos:the topic qos
 *
 * @return code: define by en_oc_mqtt_err_code while 0 means success
 *
 * @note: you should make the topic specified by your self
 */
 int oc_mqtt_unsubscribe(char *topic);



/**
 *@brief this is the oc mqtt  initialize function,must be called first
 *
 *@return 0 success while <0 failed
 */
int oc_mqtt_init();

/**
 *@brief use this function to get the errcode for the oc mqtt
 *
 *@return the  reason  corresponding to the code
 */
const char *oc_mqtt_err(en_oc_mqtt_err_code_t code);




#endif /* __OC_MQTT_AL_H */
