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

#ifdef WITH_DTLS
#include "dtls_interface.h"
/* timeout for udp client shakehand,the unit is second */
#ifndef DTLS_UDP_CLIENT_SHAKEHAND_TIMEOUT
#define DTLS_UDP_CLIENT_SHAKEHAND_TIMEOUT 60
#endif

#endif

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <link_log.h>
#include <coap_al.h>
#include <litecoap_port.h>

#include "coap_core.h"
#include "litecoap.h"
#include "litecoap_err.h"

extern int g_bind_finsh;

static fn_cmd_dealer cmd_func = NULL;

/* litecoap comunication token */
static char g_tok[COAP_MAX_TOKEN_LEN] = {0};
static char g_tok_len = 0;

/* oc local resources path */
static const coap_res_path_t path_observe = {2, {"t", "d"}};
static const coap_res_path_t path_cmd = {2, {"t", "d"}};

static int handle_observe_request(coap_msg_t *rcvmsg, coap_msg_t *outmsg);
static int handle_cmd_request(coap_msg_t *rcvmsg, coap_msg_t *outmsg);
/* local resources */
static coap_res_t g_oclink_res[] =
{
    {COAP_REQUEST_GET, handle_observe_request, &path_observe, NULL},
    {COAP_REQUEST_POST, handle_cmd_request, &path_cmd, "ct=0"},
    {0, NULL, NULL, NULL}
};


/*****************************************************************************
 Function    : handle_observe_request
 Description : observe request message process function.gen response message
               for observe request.
 Input       : rcvmsg @ recived observer request message
 Output      : outmsg @ observe response coap message
 Return      : OCLINK_OK means process ok
 *****************************************************************************/
int handle_observe_request(coap_msg_t *rcvmsg, coap_msg_t *outmsg)
{
    coap_option_t *opts = NULL;
    char contenttype[2] = {0};
    outmsg->head.msgid[0] = rcvmsg->head.msgid[0];
    outmsg->head.msgid[1] = rcvmsg->head.msgid[1];

    contenttype[0] = ((uint16_t)COAP_CONTENTTYPE_NONE & 0xFF00) >> 8;
    contenttype[1] = ((uint16_t)COAP_CONTENTTYPE_NONE & 0x00FF);
    opts = litecoap_add_option_to_list(opts,
                                COAP_OPTION_CONTENT_FORMAT,
                                (char *)contenttype, 2);
    litecoap_add_option(outmsg, opts);
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : handle_cmd_request
 Description : cmd post message process function.in this function we should
               call cmd_func() to process the cmd we got.and gen a
               response message for that.
 Input       : rcvmsg @ recived cmd post message
 Output      : outmsg @ cmd post response coap message
 Return      : OCLINK_OK means process ok
 *****************************************************************************/
int handle_cmd_request(coap_msg_t *rcvmsg, coap_msg_t *outmsg)
{
    outmsg->head.msgid[0] = rcvmsg->head.msgid[0];
    outmsg->head.msgid[1] = rcvmsg->head.msgid[1];

    if (NULL != cmd_func)
    {
        cmd_func((char *)rcvmsg->payload, rcvmsg->payloadlen);
    }

    return LITECOAP_OK;
}

#ifdef WITH_DTLS

int dtls_setup(coap_al_initpara_t *initparam, int client_or_server)
{
    int ret;
    dtls_shakehand_info_s info;
    dtls_establish_info_s establish_info;

    establish_info.psk_or_cert = VERIFY_WITH_PSK;
    establish_info.udp_or_tcp = MBEDTLS_NET_PROTO_UDP;
    establish_info.v.p.psk = initparam->psk;
    establish_info.v.p.psk_len = initparam->psklen;
    establish_info.v.p.psk_identity = initparam->pskid;

    initparam->ssl = (void *)dtls_ssl_new(&establish_info, client_or_server);
    if (NULL == initparam->ssl)
    {
        return LITECOAP_NG;
    }

    (void) memset(&info, 0, sizeof(info));
    info.client_or_server = client_or_server;
    info.finish_notify = NULL;
    info.step_notify   = NULL;
    info.udp_or_tcp = MBEDTLS_NET_PROTO_UDP;
    info.psk_or_cert = VERIFY_WITH_PSK;

    if (MBEDTLS_SSL_IS_CLIENT == client_or_server)
    {
        info.u.c.host = initparam->address;
        static char tmp[6];
        //itoa(initparam->port, tmp, 10);
        (void) sprintf(tmp, "%d", initparam->port);
        info.u.c.port = tmp;
        info.timeout = DTLS_UDP_CLIENT_SHAKEHAND_TIMEOUT;
    }

    ret = dtls_shakehand(initparam->ssl, &info);

    if (ret != 0)
    {
        dtls_ssl_destroy((mbedtls_ssl_context *)initparam->ssl);
        initparam->ssl = NULL;
        return LITECOAP_NG;
    }

    return LITECOAP_OK;
}
/*
static int __tls_read(mbedtls_ssl_context *ssl, unsigned char *buffer, int len, int timeout)
{
    int ret= -1;
    int rcvlen = -1;

    if(NULL == ssl || NULL == buffer)
    {
        return -1;
    }

    rcvlen = dtls_read(ssl,buffer,len, timeout);

    if(rcvlen == 0)
    {
        ret = -1;
    }
    else if(rcvlen < 0)
    {
        ret = 0;
    }
    else
    {
        ret = rcvlen;
    }

    return ret;
}
static int __tls_write(mbedtls_ssl_context *ssl, unsigned char *buffer, int len, int timeout)
{
    int ret= -1;
    int sndlen = -1;

    if(NULL == ssl || NULL == buffer)
    {
        return -1;
    }

    sndlen = dtls_write(ssl,buffer,len);

    if(sndlen == 0)
    {
        ret = -1;
    }
    else if(sndlen < 0)
    {
        ret = 0;
    }
    else
    {
        ret = sndlen;
    }

    return ret;
}
*/
#endif

/*****************************************************************************
 Function    : handle_coap_response
 Description : process coap response message from huawei iot server. get bind
               flag .
 Input       : ctx @ coap connection intance
               msg @ recived coap message
 Output      : None
 Return      : OCLINK_OK means process ok
 *****************************************************************************/
int handle_coap_response(struct _coap_context_t *ctx, coap_msg_t *msg)
{
    if((COAP_MESSAGE_CON == msg->head.t)
       && (COAP_REQUEST_GET == msg->head.code)
       && (COAP_OPTION_OBSERVE == msg->option->optnum))
    {
        /* bind success */
        if (!g_bind_finsh)
        {
            (void) memcpy(g_tok,msg->tok->token, msg->tok->tklen);
            g_tok_len = msg->tok->tklen;
            g_bind_finsh = 1;
        }
        else
        {
            g_tok_len = 0;
            g_bind_finsh = 0;
        }
        return LITECOAP_OK;
    }
    if(COAP_MESSAGE_RST == msg->head.t)
    {
        /* bind failed */
        g_bind_finsh = 0;
        (void) memset(g_tok,0xf1,sizeof(g_tok));
        g_tok_len = 8;
        return LITECOAP_OK;
    }
    if((COAP_MESSAGE_ACK == msg->head.t) && (0xa0 == msg->head.code))
    {
        /* bind failed */
    	LINK_LOG_DEBUG("device not exist!\r\n");
        return LITECOAP_OK;
    }
    if((COAP_MESSAGE_ACK == msg->head.t) && (0x44 == msg->head.code))
    {
        /* ok,get first back ack, wait another */
        return LITECOAP_OK;
    }
	return LITECOAP_OK;
}

static int __init(coap_al_initpara_t *initparam)
{

    int ret = -1;
    coap_context_t *ctx = NULL;

    if(NULL == initparam)
    {
        return ret;
    }

    void *remoteser = NULL;

#ifdef WITH_DTLS
    dtls_setup(initparam, LITECOAP_IS_CLIENT);
#endif

    remoteser = litecoap_new_resource(initparam->address, initparam->port, initparam->ssl, initparam->proto);
    if(NULL == remoteser)
    {
    	LINK_LOG_DEBUG("litecoap_new_resource failed!\r\n");
    	return ret;
    }
    ctx = litecoap_malloc_context(remoteser);
    if(NULL == ctx)
    {
        litecoap_delete_resource(remoteser);
    	LINK_LOG_DEBUG("litecoap_malloc_context failed!\r\n");
    	return ret;
    }

    ctx->max_retransmit = COAP_DEFAULT_MAX_RETRANSMIT;
    ctx->ack_random_factor = COAP_DEFAULT_ACK_RANDOM_FACTOR;
    ctx->ack_timeout = COAP_DEFAULT_ACK_TIMEOUT;
    ctx->proto = initparam->proto;

    initparam->ctx = (void *)ctx;

    ret = litecoap_register_handler(ctx, handle_coap_response);
    if (ret < 0)
    {
        litecoap_free_context(ctx);
        ctx = NULL;
    	LINK_LOG_DEBUG("litecoap_register_handler failed!\r\n");
    	return ret;
    }
    litecoap_add_resource(ctx, g_oclink_res);

    cmd_func = initparam->dealer;

    if (initparam->proto == COAP_PROTO_TCP) {
        //send CSM
        void *opts = NULL;
        void *msg = NULL;
        char csm_data[] = {0x80, 0x01, 0x00};
        opts = litecoap_add_option_to_list(opts, 2, csm_data, 3);
        msg = litecoap_new_msg(ctx,COAP_AL_MESSAGE_CON, LITECOAP_RESP_701, opts, NULL, 0);
        litecoap_send(ctx, msg);
        litecoap_read(ctx);
    }

    return 0;
}

static int __deinit(void *handle)
{

    int ret = -1;

    coap_context_t *ctx = (coap_context_t *)handle;

    if (ctx)
    {
        ret = litecoap_free_context(ctx);
    }

    return ret;
}

void *__add_opt(coap_al_optpara_t *optparam)
{
	void* ret = NULL;

	ret = litecoap_add_option_to_list(optparam->head, optparam->opt_num, optparam->data, optparam->len);

	return ret;
}

void* __request(coap_al_reqpara_t *reqparam)
{
	void* ret = NULL;
	coap_msg_t *msg = NULL;
	msg = litecoap_new_msg(reqparam->ctx,reqparam->msgtype, reqparam->code, reqparam->optlst, reqparam->payload, reqparam->len);

	if (reqparam->code != LITECOAP_RESP_205 && reqparam->code != LITECOAP_RESP_701)
	{
		g_tok_len = litecoap_generate_token((unsigned char *)g_tok);
	}

	if (litecoap_add_token(msg, g_tok, g_tok_len) < 0)
	{
	    litecoap_free_option(reqparam->optlst);
		reqparam->optlst = NULL;
		litecoap_delete_msg(msg);
	    msg = NULL;
	}
	ret = (void *)msg;
	return ret;
}

static int __send(coap_al_sndpara_t *sndparam)
{

    int ret = -1;

    if (NULL != sndparam->msg)
    {
        ret = litecoap_send(sndparam->handle, sndparam->msg);
    }
    else
    {
        if (sndparam->handle && ((coap_context_t *)(sndparam->handle))->sndque
            && ((coap_context_t *)(sndparam->handle))->sndque->msg)
            ret = litecoap_send(sndparam->handle, ((coap_context_t *)(sndparam->handle))->sndque->msg);
    }

    return ret;
}

static int __recv(coap_al_rcvpara_t *rcvparam)
{

    int ret = -1;

    ret = litecoap_read(rcvparam->ctx);

    return ret;
}

int coap_imp_init()
{
    int ret = -1;

    coap_al_op_t litecoap_op =
    {
    	.init = __init,
		.deinit = __deinit,
		.add_opt = __add_opt,
        .request = __request,
        .send = __send,
        .recv = __recv,
    };

    ret = coap_al_install(&litecoap_op);

    return ret;
}



