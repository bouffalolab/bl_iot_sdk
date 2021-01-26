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

#ifndef COAP_AL_H
#define COAP_AL_H

#include <stdint.h>



#if defined(__cplusplus)
extern "C" {
#endif

/* message types */
#define COAP_AL_MESSAGE_CON       0 /* confirmable message (requires ACK/RST) */
#define COAP_AL_MESSAGE_NON       1 /* non-confirmable message (one-shot message) */
#define COAP_AL_MESSAGE_ACK       2 /* used to acknowledge confirmable messages */
#define COAP_AL_MESSAGE_RST       3 /* indicates error in received messages */

/*request methods */
#define COAP_AL_REQUEST_GET       1
#define COAP_AL_REQUEST_POST      2
#define COAP_AL_REQUEST_PUT       3
#define COAP_AL_REQUEST_DELETE    4

#define COAP_PROTO_NONE         0
#define COAP_PROTO_UDP          1
#define COAP_PROTO_DTLS         2
#define COAP_PROTO_TCP          3
#define COAP_PROTO_TLS          4


#define COAP_AL_OPTION_IF_MATCH        1 /* C, opaque, 0-8 B, (none) */
#define COAP_AL_OPTION_URI_HOST        3 /* C, String, 1-255 B, destination address */
#define COAP_AL_OPTION_ETAG            4 /* E, opaque, 1-8 B, (none) */
#define COAP_AL_OPTION_IF_NONE_MATCH   5 /* empty, 0 B, (none) */
#define COAP_AL_OPTION_URI_PORT        7 /* C, uint, 0-2 B, destination port */
#define COAP_AL_OPTION_LOCATION_PATH   8 /* E, String, 0-255 B, - */
#define COAP_AL_OPTION_URI_PATH       11 /* C, String, 0-255 B, (none) */
#define COAP_AL_OPTION_CONTENT_FORMAT 12 /* E, uint, 0-2 B, (none) */
#define COAP_AL_OPTION_CONTENT_TYPE   COAP_AL_OPTION_CONTENT_FORMAT
#define COAP_AL_OPTION_MAXAGE         14 /* E, uint, 0--4 B, 60 Seconds */
#define COAP_AL_OPTION_URI_QUERY      15 /* C, String, 1-255 B, (none) */
#define COAP_AL_OPTION_ACCEPT         17 /* C, uint,   0-2 B, (none) */
#define COAP_AL_OPTION_LOCATION_QUERY 20 /* E, String,   0-255 B, (none) */
#define COAP_AL_OPTION_PROXY_URI      35 /* C, String, 1-1034 B, (none) */
#define COAP_AL_OPTION_PROXY_SCHEME   39 /* C, String, 1-255 B, (none) */
#define COAP_AL_OPTION_SIZE1          60 /* E, uint, 0-4 B, (none) */

/* option types from RFC 7641 */
#define COAP_AL_OPTION_OBSERVE         6 /* E, empty/uint, 0 B/0-3 B, (none) */
#define COAP_AL_OPTION_SUBSCRIPTION  COAP_AL_OPTION_OBSERVE

/* selected option types from RFC 7959 */
#define COAP_AL_OPTION_BLOCK2         23 /* C, uint, 0--3 B, (none) */
#define COAP_AL_OPTION_BLOCK1         27 /* C, uint, 0--3 B, (none) */

/* selected option types from RFC 7967 */
#define COAP_AL_OPTION_NORESPONSE    258 /* N, uint, 0--1 B, 0 */

#define COAP_AL_MAX_OPT            65535 /**< the highest option number we know */

#define COAP_AL_RESP_CODE(N) (((N)/100 << 5) | (N)%100)

/** @brief  defines the coap received cmd dealer*/
typedef void (*fn_cmd_dealer)(void *msg, int len);

typedef struct
{
    char*                   ep_id;            ///< endpoint identifier, which could be recognized by the server
    char*                   address;          ///< server address,maybe domain name
    unsigned short          port;             ///< server port

    void*                   ctx;              ///<coap context
    void*                   session;          ///< coap session, if needed
    unsigned int            keeplive;         ///<

    fn_cmd_dealer           dealer;           ///< coap command dealer, called to process iot platform command

    //these are for dtls, if needed
    const unsigned char*    psk;
    unsigned short          psklen;
    const unsigned char*    pskid;

    void*                   ssl;
    unsigned char           proto;

}coap_al_initpara_t;

/** @brief defines for the coap request */
typedef struct
{
	void*                  ctx;       ///< coap context
	void*                  session;   ///< coap session, if needed
	unsigned char          msgtype;   ///< con non ack rst
	unsigned char          code;      ///< get post put delete
	//char*                  tok;       ///< token
	//char                   tok_len;   ///< token length
	void*                  optlst;    ///< head of option list
	unsigned char*         payload;   ///< user data
	int                    len;       ///< user data length
}coap_al_reqpara_t;

/** @brief defines for the coap send */
typedef struct
{
	void*                  handle;    ///< coap context or session
	void*                  msg;       ///< request message
}coap_al_sndpara_t;

/** @brief defines for the coap recv */
typedef struct
{
	void*                  ctx;       ///< coap context
	int                    now;       ///< current tick
}coap_al_rcvpara_t;

/** @brief defines for the coap option */
typedef struct
{
	void*                  head;      ///< head of option list
	int                    opt_num;   ///< option number
	char*                  data;      ///< option value
	int                    len;       ///< option length
}coap_al_optpara_t;

/**
 *@brief defines the operation of coap client
 *@brief parameter and return code refere to the corresponding api
 *
 */
typedef struct
{
	///< coap init, prepare context, session, etc
	int    (* init)     (coap_al_initpara_t *initparam);
	///< coap deinit
	int    (* deinit)   (void *handle);
	///< coap add option
	void*  (* add_opt)  (coap_al_optpara_t *optparam);
	///< new coap request
	void*  (* request)  (coap_al_reqpara_t *reqparam);
	///< send a request to server
	int	   (* send)     (coap_al_sndpara_t *sndparam);
	///< recv and handle response from server
	int    (* recv)     (coap_al_rcvpara_t *rcvparam);

}coap_al_op_t;


//////////////////////API USED FOR THE COAP APPLICAITON/////////////////////////

int coap_al_init(void);  ///< initialize the coap al

/**
 * @brief maybe the coap lib need do some initialize
 *
 * @return 0 success while -1 failed
 *
 */
int coap_al_imp_init(coap_al_initpara_t *initparam);

/**
 * @brief     :when you don't want to use the coap service ,please call this function
 *
 * @return 0 success while -1 failed
 */
int coap_al_imp_deinit(void *handle);

/**
 *@brief: you could use this function to add coap option
 *
 *@param[in] optparam  the parameter we will be used to add coap options, refer to the data coap_al_optpara_t
 *@
 *@return:
 *
 *@retval NULL which means you could not get the request message
 *@retval head of option list
 */
void *coap_al_add_option(coap_al_optpara_t *optparam);

/**
 *@brief: you could use this function to create coap request
 *
 *@param[in] reqparam  the parameter we will be used to generate a request, refer to the data coap_al_reqpara_t
 *@
 *@return:
 *
 *@retval NULL which means you could not get the request message
 *@retval handle, which means you get the context
 */
void *coap_al_new_request(coap_al_reqpara_t *reqparam);

/**
 * @brief you could use this function to send a request to the server
 *
 * @param[in] sndparam refer to the data coap_al_sndpara_t
 *
 * @return 0 success  -1  failed
 *
 */
int coap_al_send(coap_al_sndpara_t *sndparam);

/**
 * @brief you could use this function to recv and handle response from server
 *
 * @param[in] rcvparam refer to the data coap_al_sndpara_t
 *
 * @return 0 success  -1  failed
 *
 */
int coap_al_recv(coap_al_rcvpara_t *rcvparam);

//////////////////////API USED FOR THE COAP IMPLEMENT/////////////////////////

/**
 *@brief the coap lib should call this function to register its implement as a service
 *
 *@param[in] op  refer to the data  coap_al_op_t
 *
 *@return 0 success while -1 failed
 *
 */
int coap_al_install(coap_al_op_t *op);
/**
 *@brief call this function to unregister the coap service
 *
 *@param[in] NULL
 *
 *@return 0 success while -1 failed
 *
 */
int coap_al_uninstall();


#if defined(__cplusplus)
}
#endif

#endif /* MQTT_AL_H */
