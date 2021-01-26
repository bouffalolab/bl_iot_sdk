/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistributopsn and use in source and binary forms, with or without modificatopsn,
 * are permitted provided that the following conditopsns are met:
 * 1. Redistributopsns of source code must retain the above copyright notice, this list of
 * conditopsns and the following disclaimer.
 * 2. Redistributopsns in binary form must reproduce the above copyright notice, this list
 * of conditopsns and the following disclaimer in the documentatopsn and/or other materials
 * provided with the distributopsn.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific propsr written
 * permissopsn.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTopsN) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulatopsns, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulatopsns.
 *---------------------------------------------------------------------------*/

#include <stdint.h>
#include <stddef.h>
#include <link_log.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


#include <coap_al.h>


typedef struct
{
    coap_al_op_t  *ops;
    coap_al_op_t   mem;
}coap_al_op_cb_t;

static coap_al_op_cb_t   s_coap_al_op_cb;


/////////////////CREATE THE API FOR THE COAP LIB////////////////////////////////
int coap_al_install(coap_al_op_t *op)
{
    int ret = -1;
    if((NULL != op)&&(NULL == s_coap_al_op_cb.ops))
    {
        s_coap_al_op_cb.mem  = *op;
        s_coap_al_op_cb.ops = &s_coap_al_op_cb.mem;

        ret = 0;
    }

    return ret;
}

int coap_al_uninstall()
{
    int ret = -1;
    if(NULL != s_coap_al_op_cb.ops)
    {
        s_coap_al_op_cb.ops = NULL;

        ret = 0;
    }

    return ret;
}

//////////////////////////CREATE THE API FOR THE COAP APPLICATopsN///////////////

int coap_al_imp_init(coap_al_initpara_t *initparam)
{
    int ret = 0;

    if((NULL != initparam) && (NULL != s_coap_al_op_cb.ops) && (NULL != s_coap_al_op_cb.ops->init))
    {
        ret = s_coap_al_op_cb.ops->init(initparam);
    }

    return ret;
}


int  coap_al_imp_deinit(void *handle)
{

    int ret = 0;

    if((NULL != handle) && (NULL != s_coap_al_op_cb.ops) && (NULL != s_coap_al_op_cb.ops->deinit))
    {
        ret = s_coap_al_op_cb.ops->deinit(handle);
    }

    return ret;
}

void *coap_al_add_option(coap_al_optpara_t *optparam)
{

    void *ret = NULL;

    if((NULL != optparam) && (NULL != s_coap_al_op_cb.ops) && (NULL != s_coap_al_op_cb.ops->add_opt))
    {
        ret = s_coap_al_op_cb.ops->add_opt(optparam);
    }

    return ret;

}

void *coap_al_new_request(coap_al_reqpara_t *reqparam)
{

    void *ret = NULL;

    if((NULL != reqparam) && (NULL != s_coap_al_op_cb.ops) && (NULL != s_coap_al_op_cb.ops->request))
    {
        ret = s_coap_al_op_cb.ops->request(reqparam);
    }

    return ret;

}

int coap_al_send(coap_al_sndpara_t *sndparam)
{

    int ret = 0;

    if((NULL != sndparam) && (NULL != s_coap_al_op_cb.ops) && (NULL != s_coap_al_op_cb.ops->send))
    {
        ret = s_coap_al_op_cb.ops->send(sndparam);
    }

    return ret;

}

int coap_al_recv(coap_al_rcvpara_t *rcvparam)
{

    int ret = 0;

    if((NULL != rcvparam) && (NULL != s_coap_al_op_cb.ops) && (NULL != s_coap_al_op_cb.ops->recv))
    {
        ret = s_coap_al_op_cb.ops->recv(rcvparam);
    }

    return ret;

}



#if 0 //
__attribute__((weak))  int coap_imp_init(void)
{
    LINK_LOG_DEBUG("%s:###please implement coap by yourself####\n\r",__FUNCTION__);
    return -1;
}
#endif

int coap_al_init(void)
{

    int ret;

    ret = coap_imp_init();

    LINK_LOG_DEBUG("IOT_LINK:DO COAP LOAD-IMPLEMENT RET:%d\n\r",ret);


    return ret;
}






#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


