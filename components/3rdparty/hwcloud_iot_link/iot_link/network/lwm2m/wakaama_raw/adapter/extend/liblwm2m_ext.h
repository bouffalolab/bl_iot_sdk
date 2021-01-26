/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2019>, <Huawei Technologies Co., Ltd>
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

#ifndef __LIBLWM2M_EXT_H__
#define __LIBLWM2M_EXT_H__

#include <stdint.h>

#include "liblwm2m_api.h"

#include "er-coap-13/er-coap-13.h"
#include <osal.h>
#include <atiny_log.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*
 * Platform abstraction functions to be implemented by the user
 */

//get len of random bytes in output.
int lwm2m_rand(void *output, size_t len);

//delay sometime
void lwm2m_delay(uint32_t second);

/*
 * Resource IDs for the LWM2M Server Object
 */
#define LWM2M_TRIGER_SERVER_MODE_INITIATED_TIME 60

#define MAX_FACTORY_BS_RETRY_CNT                3
#define MAX_CLIENT_INITIATED_BS_RETRY_CNT       3
#define FACTORY_BS_DELAY_BASE                   0
#define CLIENT_INITIATED_BS_DELAY_BASE          0
#define FACTORY_BS_DELAY_INTERVAL               10
#define CLIENT_INITIATED_BS_DELAY_INTERVAL      10

/*
 * The lwm2m_data
 */

typedef void (*lwm2m_data_process)(void *);

typedef struct _lwm2m_data_cfg_t
{
    int                 type;
    int                 cookie;
    lwm2m_data_process  callback;
} lwm2m_data_cfg_t;

// in liblwm2m.h
//      struct _lwm2m_data_t
typedef struct _lwm2m_data_t lwm2m_data_t;


/*
 * LWM2M Servers
 */

typedef enum
{
    MODULE_LWM2M,
    MODULE_NET,
    MODULE_URI,
} module_type_t;

enum
{
    OBSERVE_UNSUBSCRIBE,
    OBSERVE_SUBSCRIBE,
};

/*
 * LWM2M observed resources
 */

#ifdef LWM2M_CLIENT_MODE

typedef enum
{
    BS_SEQUENCE_STATE_INITIAL = 0,
    BS_SEQUENCE_STATE_FACTORY,
    BS_SEQUENCE_STATE_SERVER_INITIATED,
    BS_SEQUENCE_STATE_CLIENT_INITIATED,
    NO_BS_SEQUENCE_STATE
} lwm2m_bs_sequence_state_t;


#endif

/*
 * LWM2M Context
 */

#ifdef LWM2M_CLIENT_MODE
// Returns a session handle that MUST uniquely identify a peer.
// secObjInstID: ID of the Securty Object instance to open a connection to
// userData: parameter to lwm2m_init()
// bootstrap_flag: If BootstrapServer
void *lwm2m_connect_server_ex(uint16_t secObjInstID, void *userData, bool isServer);

/* use to control the bootstrap, factory bootstrap, client initiated bootstrap, server initiated bootstrap.
factory bootstrap is used security object to register.
*/
typedef struct
{
    lwm2m_bootstrap_type_e  bsType;
    int                     state;     // -> lwm2m_client_state_t
    uint32_t                cnt;
} lwm2m_bs_control_t;


// in liblwm2m.h
//      struct _lwm2m_context_t
//      struct _lwm2m_transaction_
//      void (*lwm2m_transaction_callback_t)(...)
typedef struct _lwm2m_context_ lwm2m_context_t;

typedef struct _lwm2m_transaction_ lwm2m_transaction_t;

// typedef void (*lwm2m_transaction_callback_t) (lwm2m_transaction_t * transacP, void * message);
typedef void (*lwm2m_transaction_callback_t)(lwm2m_context_t *contextP, lwm2m_transaction_t *transacP, void *message);

void lwm2m_register_observe_ack_call_back(lwm2m_transaction_callback_t callback);
typedef void(*lwm2m_event_handler_t)(module_type_t type, int code, const char *arg, int arg_len);
void lwm2m_register_event_handler(lwm2m_event_handler_t callback);
void lwm2m_notify_even(module_type_t type, int code, const char *arg, int arg_len);
int lwm2m_reconnect(lwm2m_context_t *context);


typedef struct
{
    uint32_t    format;
    uint8_t     token[8];
    uint32_t    tokenLen;
    uint32_t    counter;
} lwm2m_observe_info_t;

uint8_t lwm2m_get_observe_info(lwm2m_context_t *contextP, lwm2m_observe_info_t *observe_info);
uint8_t lwm2m_send_notify(lwm2m_context_t *contextP, lwm2m_observe_info_t *observe_info, int firmware_update_state, lwm2m_data_cfg_t  *cfg);

int lwm2m_initBootStrap(lwm2m_context_t *contextP, lwm2m_bootstrap_type_e bsType);

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LIBLWM2M_EXT_H__ */

