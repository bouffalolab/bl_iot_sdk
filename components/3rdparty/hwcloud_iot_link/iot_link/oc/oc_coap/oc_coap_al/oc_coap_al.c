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


#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include <link_log.h>
#include <osal.h>
#include <oc_coap_al.h>

typedef struct
{
    const char            *name;    ///< lwm2m implement name
    const oc_coap_opt_t  *opt;     ///< lwm2m implement method
}oc_coap_t;
static oc_coap_t  s_oc_coap_ops;

typedef struct
{
    void                   *handle;
    const oc_coap_opt_t    *ops;
    oc_config_param_t       param;
}oc_coap_context_t;


int oc_coap_register(const char *name,const oc_coap_opt_t *opt)
{
    int ret = -1;

    if(NULL == s_oc_coap_ops.opt)
    {
        s_oc_coap_ops.name = name;
        s_oc_coap_ops.opt =  opt;
        ret = 0;
    }
    return ret;
}

int oc_coap_unregister(const char *name)
{
    int ret = -1;

    if((NULL != name) && (NULL != s_oc_coap_ops.name))
    {
        if(0 == strcmp(name,s_oc_coap_ops.name))
        {
            s_oc_coap_ops.opt = NULL;   ///< also think about clear all the ops in the context,
            s_oc_coap_ops.name = NULL;
            ret = 0;
        }
    }

    return ret;
}


//////////////////////////APPLICATION INTERFACE/////////////////////////////////
int oc_coap_report(void *context, char  *buf, int len)
{
    int ret = -1;
    oc_coap_context_t  *oc_coap;
    oc_coap = context;

    if((NULL != oc_coap) &&(NULL != oc_coap->ops) &&(NULL != oc_coap->ops->report))
    {
       ret = oc_coap->ops->report(oc_coap->handle,buf,len);
    }

    return ret;
}


void *oc_coap_config(oc_config_param_t *param)
{
    void *ret = NULL;
    oc_coap_context_t  *oc_coap;

    if((NULL != s_oc_coap_ops.opt) &&(NULL != s_oc_coap_ops.opt->config))
    {
        oc_coap = osal_zalloc(sizeof(oc_coap_context_t));
        if(NULL != oc_coap)
        {
            oc_coap->param = *param;
            oc_coap->ops = s_oc_coap_ops.opt;
            oc_coap->handle = s_oc_coap_ops.opt->config(param);
            if(NULL == oc_coap->handle)
            {
                osal_free(oc_coap);
            }
            else
            {
                ret = oc_coap;
            }
        }
    }

    return ret;
}


int oc_coap_deconfig(void *context)
{
    int ret = -1;
    oc_coap_context_t  *oc_coap;
    oc_coap = context;

    if((NULL != oc_coap) &&(NULL != oc_coap->ops) && (NULL != oc_coap->ops->deconfig))
    {
        ret = oc_coap->ops->deconfig(oc_coap->handle); ///<  should check if deconfigure error
        if(ret == 0)
        {
            osal_free(oc_coap);
        }
    }

    return ret;
}

#if 0 //
__attribute__((weak)) int oc_coap_imp_init(void)
{
    LINK_LOG_DEBUG("%s:PLEASE IMPLEMENT THE OC COAP YOURSELF\r\n",__FUNCTION__);
    return -1;
}
#endif

__attribute__((weak)) int oc_coap_demo_main(void)
{
    LINK_LOG_DEBUG("%s:PLEASE IMPLEMENT THE OC COAP DEMO YOURSELF\r\n",__FUNCTION__);
    return -1;
}

///////////////////////OC LWM2M AGENT INITIALIZE////////////////////////////////
int oc_coap_init()
{
    int ret;

    ret = oc_coap_imp_init();
    LINK_LOG_DEBUG("IOT_LINK:DO OCCOAP LOAD-IMPLEMENT RET:%d\n\r",ret);

#ifdef CONFIG_OCCOAP_DEMO_ENABLE
    (void) oc_coap_demo_main();
#endif

    return ret;
}

