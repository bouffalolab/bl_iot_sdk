/*----------------------------------------------------------------------------
 * Copyright (c) <2019>, <Huawei Technologies Co., Ltd>
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

#ifndef LITEOS_LAB_IOT_LINK_NETWORK_LWM2M_LWM2M_AL_LWM2M_AL_H_
#define LITEOS_LAB_IOT_LINK_NETWORK_LWM2M_LWM2M_AL_LWM2M_AL_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_STRURI_LEN                  20
#define URI_FMT                         "/%u/%u/%u"

#define URI_TRIGER_SERVER_INITIATED_BS "/1/0/9"


#define LWM2M_AL_OP_READ                1
#define LWM2M_AL_OP_WRITE               2
#define LWM2M_AL_OP_EXCUTE              3
#define LWM2M_AL_OP_DISCOVER            4
#define LWM2M_AL_OP_SERVERREBS          5

typedef enum
{
    LWM2M_OK                            = 0,
    LWM2M_ARG_INVALID                   = -1,
    LWM2M_BUF_OVERFLOW                  = -2,
    LWM2M_MSG_CONGEST                   = -3,
    LWM2M_MALLOC_FAILED                 = -4,
    LWM2M_RESOURCE_NOT_FOUND            = -5,
    LWM2M_RESOURCE_NOT_ENOUGH           = -6,
    LWM2M_CLIENT_UNREGISTERED           = -7,
    LWM2M_SOCKET_CREATE_FAILED          = -8,
    LWM2M_ERR                           = -9,
    LWM2M_OBJECT_INSTANCE_EXISTED       = -10,
    LWM2M_SUPPORT_SINGLE_INSTANCE_ONLY  = -11,
    LWM2M_NOT_SUPPORTED                 = -12,
    LWM2M_NULL_POINTER                  = -13,
    LWM2M_COAP_400_BAD_REQUEST          = -14,
    LWM2M_ADD_OBJECT_FAILED             = -15,
    LWM2M_ERRNO_NORES                   = -16,
    LWM2M_ERRNO_REPEAT                  = -17,
#ifdef MBEDTLS_ERR_NET_SOCKET_FAILED
    LWM2M_DTLS_NET_SOCKET_FAILED        = MBEDTLS_ERR_NET_SOCKET_FAILED,
#endif
#ifdef MBEDTLS_ERR_NET_CONNECT_FAILED
    LWM2M_DTLS_NET_CONNECT_FAILED       = MBEDTLS_ERR_NET_CONNECT_FAILED,
#endif
#ifdef MBEDTLS_ERR_NET_BIND_FAILED
    LWM2M_DTLS_NET_BIND_FAILED          = MBEDTLS_ERR_NET_BIND_FAILED,
#endif
#ifdef MBEDTLS_ERR_NET_LISTEN_FAILED
    LWM2M_DTLS_NET_LISTEN_FAILED        = MBEDTLS_ERR_NET_LISTEN_FAILED,
#endif
#ifdef MBEDTLS_ERR_NET_ACCEPT_FAILED
    LWM2M_DTLS_NET_ACCEPT_FAILED        = MBEDTLS_ERR_NET_ACCEPT_FAILED,
#endif
#ifdef MBEDTLS_ERR_NET_RECV_FAILED
    LWM2M_DTLS_NET_RECV_FAILED          = MBEDTLS_ERR_NET_RECV_FAILED,
#endif
#ifdef MBEDTLS_ERR_NET_SEND_FAILED
    LWM2M_DTLS_NET_SEND_FAILED          = MBEDTLS_ERR_NET_SEND_FAILED,
#endif
#ifdef MBEDTLS_ERR_NET_CONN_RESET
    LWM2M_DTLS_NET_CONN_RESET           = MBEDTLS_ERR_NET_CONN_RESET,
#endif
#ifdef MBEDTLS_ERR_NET_UNKNOWN_HOST
    LWM2M_DTLS_NET_UNKNOWN_HOST         = MBEDTLS_ERR_NET_UNKNOWN_HOST,
#endif
#ifdef MBEDTLS_ERR_NET_BUFFER_TOO_SMALL
    LWM2M_DTLS_NET_BUFFER_TOO_SMALL     = MBEDTLS_ERR_NET_BUFFER_TOO_SMALL,
#endif
#ifdef MBEDTLS_ERR_NET_INVALID_CONTEXT
    LWM2M_DTLS_NET_INVALID_CONTEXT      = MBEDTLS_ERR_NET_INVALID_CONTEXT,
#endif
#ifdef MBEDTLS_ERR_NET_POLL_FAILED
    LWM2M_DTLS_NET_POLL_FAILED          = MBEDTLS_ERR_NET_POLL_FAILED,
#endif
#ifdef MBEDTLS_ERR_NET_BAD_INPUT_DATA
    LWM2M_DTLS_NET_BAD_INPUT_DATA       = MBEDTLS_ERR_NET_BAD_INPUT_DATA,
#endif
} lwm2m_errorcode_e;

typedef enum
{
    OBJ_SECURITY_ID = 0,
    OBJ_SERVER_ID,
    OBJ_ACCESS_CONTROL_ID,
    OBJ_DEVICE_ID,
    OBJ_CONNECTIVITY_MONITORING_ID,
    OBJ_FIRMWARE_UPDATE_ID,
    OBJ_LOCATION_ID,
    OBJ_CONNECTIVITY_STATISTICS_ID,
    OBJ_APP_DATA_ID = 19
} lwm2m_object_id_e;

typedef struct
{
    uint16_t            server_id;
    bool                is_bootstrap;
    int                 hold_off_time;  /* bootstrap hold off time for server initiated bootstrap */
    char               *server_ip;
    char               *server_port;
    char               *psk_id;
    char               *psk;
    uint16_t            psk_len;
} lwm2m_al_sec_obj_param_t;

typedef struct
{
    uint16_t            server_id;
    char               *binding;        /* support U and UQ bind mode */
    int                 life_time;      /* required option */
    uint32_t            storing_cnt;    /* storing count */
} lwm2m_al_srv_obj_param_t;

typedef int (*fn_lwm2m_msg_deal)(int op, const char *uri, char *msg, int len);

typedef struct
{
    char               *endpoint_name;
    fn_lwm2m_msg_deal   dealer;         /* command dealer, called to process iot platform */
    void               *user_data;
    int                 bootstrap_type;
} lwm2m_al_init_param_t;

typedef struct
{
    int                 object_id;
    int                 object_instance_id;
    int                 resource_id;
    void               *data;
    int                 length;
    int                 mode;           /* mode: 0-nonconfirmable；1-confirmable */
} lwm2m_al_send_param_t;

/* opertate interface */
typedef struct
{
    /* lwm2m config, prepare endpoint name and message deal callback */
    int (*config)(void **handle, lwm2m_al_init_param_t *init_param);

    /* lwm2m deinit */
    int (*deconfig)(void *handle);

    /* lwm2m add object */
    int (*add_object)(void *handle, int object_id, int object_instance_id, int resource_id, void *param);

    /* lwm2m delete object */
    int (*delete_object)(void *handle, int object_id);

    /* lwm2m connect */
    int (*connect)(void *handle);

    /* lwm2m disconnect */
    int (*disconnect)(void *handle);

    /* lwm2m send */
    int (*send)(void *handle, lwm2m_al_send_param_t *send_param);
} lwm2m_al_op_t;

/**
 * @brief     : the lwm2m service should call this function to init necessary parameters
 *
 *@param[in] init_param  refer to the data of lwm2m_al_init_param_t
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_config(void **handle, lwm2m_al_init_param_t *init_param);

/**
 * @brief     : when you don't want to use the lwm2m service ,please call this function
 *
 *@param[in] void
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_deconfig(void *handle);

/**
 * @brief     : the lwm2m service should call this function to add some necessary objects
 *
 *@param[in] op  refer to the data  lwm2m_al_op_t
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_add_object(void *handle, int object_id, int object_instance_id, int resource_id, void *param);

/**
 * @brief     : you could call this function to delete the object by given object id
 *
 *@param[in] object_id
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_delete_object(void *handle, int object_id);

/**
 * @brief     : you could use this function to connect to the lwm2m server
 *
 *@param[in] void
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_connect(void *handle);

/**
 * @brief     : you could use this function to disconnect from the lwm2m server
 *
 *@param[in] void
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_disconnect(void *handle);

/**
 * @brief     : you could use this function to send a message to the server
 *
 *@param[in] send_param refer to the data of lwm2m_al_send_param_t
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_send(void *handle, lwm2m_al_send_param_t *send_param);

/**
 * @brief     : the lwm2m lib should call this function to register its implement as a service
 *
 *@param[in] op  refer to the data of lwm2m_al_op_t
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_install(lwm2m_al_op_t *op);

/**
 * @brief     : call this function to unregister the lwm2m service
 *
 *@param[in] void
 *
 * @return 0 success,otherwise it's a special error code if failed
 */
int lwm2m_al_uninstall(void);


/*
 * @brief: initialize the lwm2m abstract layer
 *
 *         and will call the lwm2m implement internal
 *
 * @ return 0 success while others failed
 * */


int lwm2m_al_init(void);


#endif /* LITEOS_LAB_IOT_LINK_NETWORK_LWM2M_LWM2M_AL_LWM2M_AL_H_ */

