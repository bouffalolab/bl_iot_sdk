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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "atiny_coap.h"
#include <osal.h>
#include <coap_al.h>
#include <oc_coap_al.h>

typedef struct
{
    char* server_ip;
    char* server_port;

    char* psk_Id;
    char* psk;
    unsigned short psk_len;

} atiny_security_param_t;

typedef struct
{
    oc_config_param_t       config_para;
    atiny_security_param_t  security_params[2];
    void                   *task_handle;
    void                   *coap_context;
}oc_coap_imp_agent_t;

static oc_coap_imp_agent_t  *s_oc_coap_agent = NULL;

#define ATINY_MAX_SEND_RETRY 500
#define ATINY_MAX_TOKEN_LEN 8

#define ATINY_MAX_EPID_LEN 50

/* atiny local resources */
unsigned char atiny_res[3]={'t'};
unsigned char atiny_res1[3]={'r'};
unsigned char atiny_res2[ATINY_MAX_EPID_LEN] = "ep=";

static int atiny_state = ATINY_STAT_INIT;
int g_bind_finsh = 0;
static void *ctx = NULL;
static int atiny_err_code = 0;
static char atiny_stop_flag = 0;

static coap_al_initpara_t *initpara = NULL;
static coap_al_optpara_t *optpara = NULL;
static coap_al_reqpara_t *reqpara = NULL;
static coap_al_sndpara_t *sndpara = NULL;
static coap_al_rcvpara_t *rcvpara = NULL;

void get_coap_al_para(void)
{
	initpara = (coap_al_initpara_t *)osal_malloc(sizeof(coap_al_initpara_t));

	optpara = (coap_al_optpara_t *)osal_malloc(sizeof(coap_al_optpara_t));

	reqpara = (coap_al_reqpara_t *)osal_malloc(sizeof(coap_al_reqpara_t));

	sndpara = (coap_al_sndpara_t *)osal_malloc(sizeof(coap_al_sndpara_t));

	rcvpara = (coap_al_rcvpara_t *)osal_malloc(sizeof(coap_al_rcvpara_t));
}

/*****************************************************************************
 Function    : atiny_set_errcode
 Description : set error code of atiny.
 Input       : err @  error code
 Output      : None
 Return      : None
 *****************************************************************************/
static int atiny_set_errcode(int err)
{
    atiny_err_code = err;
    return ATINY_OK;
}

/*****************************************************************************
 Function    : atiny_get_errcode
 Description : get error code of atiny.
 Input       : None
 Output      : None
 Return      : atiny_err_code @ atiny error code
 *****************************************************************************/
int atiny_get_errcode(void)
{
    return atiny_err_code;
}

/*****************************************************************************
 Function    : atiny_set_nextstate
 Description : set atiny next work state
 Input       : state @ curent state
 Output      : state @ next state
 Return      : ATINY_OK means set ok
 *****************************************************************************/
static int atiny_set_nextstate(int *state)
{
    switch(*state)
    {
        case ATINY_STAT_INIT:
            *state = ATINY_STAT_BINDING;
            break;
        case ATINY_STAT_BINDING:
            *state = ATINY_STAT_WAIT_BINDOK;
            break;
        case ATINY_STAT_WAIT_BINDOK:
            *state = ATINY_STAT_IDLE;
            break;
        case ATINY_STAT_IDLE:
            *state = ATINY_STAT_IDLE;
            break;
        case ATINY_STAT_ERR:
            *state = ATINY_STAT_BINDING;
            break;
        default:
            *state = ATINY_STAT_ERR;
            break;
    }
    return ATINY_OK;
}

/*****************************************************************************
 Function    : atiny_get_curstate
 Description : get atiny work state
 Input       : res @ unused
 Output      : None
 Return      : atiny_state @ atiny current state
 *****************************************************************************/
static int atiny_get_curstate(void *res)
{
    return atiny_state;
}

/*****************************************************************************
 Function    : atiny_set_errstate
 Description : set atiny work state is STATE_ERR
 Input       : state @ current work state
 Output      : state @ STATE_ERR
 Return      : atiny_state @ atiny current state
 *****************************************************************************/
static int atiny_set_errstate(int *state)
{
    if (NULL != state)
    {
        *state = ATINY_STAT_ERR;
    }
    return ATINY_OK;
}

/*****************************************************************************
 Function    : atiny_set_state
 Description : set atiny work state by given state
 Input       : state @ the state value that will be setted
 Output      : None
 Return      : ATINY_OK @ set ok.
 *****************************************************************************/
static int atiny_set_state(int state)
{
    if ((state >= ATINY_STAT_INIT) && (state < ATINY_STAT_MAX))
    {
        atiny_state = state;
    }
    return ATINY_OK;
}

/*****************************************************************************
 Function    : atiny_task
 Description : atiny main task. it will start from STAT_INIT to STAT_IDLE,
               and process all coap messages that atiny need send and
               recive.
 Input       : None
 Output      : None
 Return      : ATINY_OK @ atiny finished ok.
 *****************************************************************************/
int __agent_coap_task_entry(void *args)
{

    oc_coap_imp_agent_t *tmp = NULL;
    tmp = args;

	void *opts = NULL;
	void *msg = NULL;
	int ret  = 0;
    int startrcvmsg = 0;

    unsigned long long bindstarttm;
    unsigned long long curtm;

    get_coap_al_para();

    while(1)
    {
        /* stop atiny */
        if (atiny_stop_flag)
        {
            coap_al_imp_deinit(ctx);
            atiny_stop_flag = 0;
            break;
        }

        switch(atiny_get_curstate(NULL))
        {

            case ATINY_STAT_INIT:
            	(void) memset(initpara,0,sizeof(coap_al_initpara_t));
            	initpara->address = tmp->config_para.app_server.address;
            	initpara->port = atoi(tmp->config_para.app_server.port);
            	initpara->dealer = (fn_cmd_dealer)tmp->config_para.rcv_func;
            	initpara->psk = (const unsigned char *)tmp->security_params[0].psk;
            	initpara->psklen = tmp->security_params[0].psk_len;
            	initpara->pskid = (const unsigned char *)tmp->security_params[0].psk_Id;
                initpara->proto = COAP_PROTO_UDP;
                coap_al_imp_init(initpara);

            	ctx = initpara->ctx;
                atiny_set_nextstate(&atiny_state);
                break;
            case ATINY_STAT_BINDING:
                if (strlen(tmp->config_para.app_server.ep_id) == 0)
                {
                    /* no sn data, user should set hte sn data. */
                    osal_task_sleep(100);
                    continue;
                }

                (void) memset(optpara,0,sizeof(coap_al_optpara_t));
                optpara->head = opts;
                optpara->opt_num = COAP_AL_OPTION_URI_PATH;
                optpara->data = (char *)atiny_res;
                optpara->len = 1;
                opts = coap_al_add_option(optpara);

                optpara->head = opts;
                optpara->opt_num = COAP_AL_OPTION_URI_PATH;
                optpara->data = (char *)atiny_res1;
                optpara->len = 1;
                opts = coap_al_add_option(optpara);

                (void) memcpy(atiny_res2+3, tmp->config_para.app_server.ep_id, strlen(tmp->config_para.app_server.ep_id));

                optpara->head = opts;
                optpara->opt_num = COAP_AL_OPTION_URI_QUERY;
                optpara->data = (char *)atiny_res2;
                optpara->len = strlen(tmp->config_para.app_server.ep_id) + 3;
                opts = coap_al_add_option(optpara);

                (void) memset(reqpara,0,sizeof(coap_al_reqpara_t));
                reqpara->ctx = ctx;
                reqpara->msgtype = COAP_AL_MESSAGE_CON;
                reqpara->code = COAP_AL_REQUEST_POST;
                reqpara->optlst = opts;

                msg = coap_al_new_request(reqpara);

                if (msg == NULL)
                {
                    atiny_set_errstate(&atiny_state);
                    break;
                }
                /* send bind msg to huawei iot platform. */
                (void) memset(sndpara,0,sizeof(coap_al_sndpara_t));
                sndpara->handle = ctx;
                sndpara->msg = msg;
                ret = coap_al_send(sndpara);

                if (ret < 0)
                {
                    /* send err */
                    break;
                }
                atiny_set_nextstate(&atiny_state);
                startrcvmsg = 1;
                bindstarttm = osal_sys_time();
                break;
            case ATINY_STAT_WAIT_BINDOK:
                curtm = osal_sys_time();
                if (curtm - bindstarttm >= ATINY_BIND_TIMEOUT)
                {
                    g_bind_finsh = 0;
                    atiny_set_state(ATINY_STAT_BINDING);
                    startrcvmsg = 0;
                    atiny_set_errcode(ATINY_ERR_CODE_BINDTIMEOUT);
                    break;
                }
                if(g_bind_finsh)
                {
                    atiny_set_nextstate(&atiny_state);
                }
                break;
            case ATINY_STAT_IDLE:
            	(void) memset(sndpara,0,sizeof(coap_al_sndpara_t));
                sndpara->handle = ctx;
                sndpara->msg = NULL;
                ret = coap_al_send(sndpara);
                break;
            case ATINY_STAT_ERR:
            default:
                atiny_set_state(ATINY_STAT_BINDING);
                startrcvmsg = 0;
                g_bind_finsh = 0;
                break;
        }
        /* atiny task should recive all coap messages. */

        if (startrcvmsg)
        {
        	(void) memset(rcvpara,0,sizeof(coap_al_rcvpara_t));
        	rcvpara->ctx = ctx;
        	ret = coap_al_recv(rcvpara);

            if (ret < 0)
            {
                atiny_set_errcode(ATINY_ERR_CODE_NETWORK);
                osal_task_sleep(100);
            }
        }
    }
    return ATINY_OK;
}

/*****************************************************************************
 Function    : atiny_send
 Description : send user data to huawei iot platform.
 Input       : buf @ the data that user want to send
               len @ the data's length.
 Output      : None
 Return      : ATINY_OK @ send finished. other value means not send.
 *****************************************************************************/
int __agent_report(void *handle, char *buf, int len)
{
    void *msg = NULL;
    void *opts = NULL;
    int ret = 0;
    static unsigned char lifetime = 0;

    if (NULL == ctx)
    {
        return ATINY_ERR;
    }

    while(atiny_get_curstate(NULL) != ATINY_STAT_IDLE)
    {
        ret++;
        osal_task_sleep(10);
        if (ret >= ATINY_MAX_SEND_RETRY)
        {
            return ATINY_ERR;
        }
    }
    lifetime++;

    (void) memset(optpara,0,sizeof(coap_al_optpara_t));
    optpara->head = opts;
    optpara->opt_num = COAP_AL_OPTION_OBSERVE;
    optpara->data = (char *)&lifetime;
    optpara->len = 1;
    opts = coap_al_add_option(optpara);

    (void) memset(reqpara,0,sizeof(coap_al_reqpara_t));
    reqpara->ctx = ctx;
    reqpara->msgtype = COAP_AL_MESSAGE_NON;
    reqpara->code = COAP_AL_RESP_CODE(205);
    reqpara->optlst = opts;
    reqpara->payload = (void *)buf;
    reqpara->len = len;

    msg = coap_al_new_request(reqpara);

    if (NULL == msg)
    {
        return ATINY_ERR;
    }

    (void) memset(sndpara,0,sizeof(coap_al_sndpara_t));
    sndpara->handle = ctx;
    sndpara->msg = msg;
    ret = coap_al_send(sndpara);
    return ATINY_OK;
}

static void *__agent_config(oc_config_param_t *param)
{

    oc_coap_imp_agent_t  *ret = NULL;

    if(NULL != s_oc_coap_agent)
    {
        return ret;
    }

    ret = osal_zalloc(sizeof(oc_coap_imp_agent_t));

    if(NULL == ret)
    {
        return ret;
    }

    ret->config_para = *param;
    ///< initialize the param that agent tiny need
    atiny_security_param_t  *iot_security_param = NULL;
    atiny_security_param_t  *bs_security_param = NULL;

    //pay attention: index 0 for iot server, index 1 for bootstrap server.
    iot_security_param = &(ret->security_params[0]);
    bs_security_param = &(ret->security_params[1]);

    iot_security_param->server_ip = ret->config_para.app_server.address;
    iot_security_param->server_port = ret->config_para.app_server.port;
    iot_security_param->psk_Id = ret->config_para.app_server.psk_id;
    iot_security_param->psk = ret->config_para.app_server.psk;
    iot_security_param->psk_len = ret->config_para.app_server.psk_len;

    bs_security_param->server_ip = ret->config_para.boot_server.address;
    bs_security_param->server_port = ret->config_para.boot_server.port;
    bs_security_param->psk_Id = ret->config_para.boot_server.psk_id;
    bs_security_param->psk = ret->config_para.boot_server.psk;
    bs_security_param->psk_len = ret->config_para.boot_server.psk_len;


    ///< create the task to do the instance

    ret->task_handle = osal_task_create("agent_coap",__agent_coap_task_entry,ret,0x1000,NULL,10);
    if(NULL == ret->task_handle)
    {
        osal_free(ret);
        ret = NULL;
        return ret;
    }

    s_oc_coap_agent = ret;

    return ret;
}

static int __agent_deconfig(void *handle)
{
    oc_coap_imp_agent_t  *ret = handle;

    if(NULL == handle)
    {
        return -1;
    }

    /* set atiny to stop send data */
    atiny_stop_flag = 1;
    /* wait atiny data process task finish recieve data and exit */
    osal_task_sleep(1000);

    osal_task_kill(ret->task_handle);

    osal_free(ret);
    osal_free(initpara);
    osal_free(optpara);
    osal_free(reqpara);
    osal_free(sndpara);
    osal_free(rcvpara);

    s_oc_coap_agent = NULL;

    return 0;
}

const oc_coap_opt_t  s_oc_coap_agent_opt = \
{
    .config = __agent_config,
    .deconfig = __agent_deconfig,
    .report = __agent_report,
};

int oc_coap_imp_init()
{
    int ret = -1;

    ret = oc_coap_register("oc_coap_agent",&s_oc_coap_agent_opt);

    return ret;
}
