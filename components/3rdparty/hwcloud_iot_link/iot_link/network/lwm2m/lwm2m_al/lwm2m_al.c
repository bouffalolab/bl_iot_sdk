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



#include <stddef.h>

#include <link_log.h>
#include <lwm2m_al.h>


typedef struct
{
    lwm2m_al_op_t  *ops;
    lwm2m_al_op_t   mem;
} lwm2m_al_op_cb_t;

static lwm2m_al_op_cb_t s_lwm2m_al_op_cb;

/////////////////CREATE THE API FOR THE LWM2M LIB////////////////////////////////
int lwm2m_al_config(void **handle, lwm2m_al_init_param_t *init_param)
{
    int ret = (int)LWM2M_ERR;

    if ((NULL != handle)
        && (NULL != init_param)
        && (NULL != s_lwm2m_al_op_cb.ops)
        && (NULL != s_lwm2m_al_op_cb.ops->config))
    {
        ret = s_lwm2m_al_op_cb.ops->config(handle, init_param);
    }

    return ret;
}

int lwm2m_al_deconfig(void *handle)
{
    int ret = (int)LWM2M_ERR;

    if ((NULL != handle)
        && (NULL != s_lwm2m_al_op_cb.ops)
        && (NULL != s_lwm2m_al_op_cb.ops->deconfig))
    {
        ret = s_lwm2m_al_op_cb.ops->deconfig(handle);
    }

    return ret;
}

int lwm2m_al_add_object(void *handle, int object_id, int object_instance_id, int resource_id, void *param)
{
    int ret = (int)LWM2M_ERR;

    if ((NULL != handle)
        && (NULL != s_lwm2m_al_op_cb.ops)
        && (NULL != s_lwm2m_al_op_cb.ops->add_object))
    {
        ret = s_lwm2m_al_op_cb.ops->add_object(handle, object_id, object_instance_id, resource_id, param);
    }

    return ret;
}

int lwm2m_al_delete_object(void *handle, int object_id)
{
    int ret = (int)LWM2M_ERR;

    if ((NULL != handle)
        && (NULL != s_lwm2m_al_op_cb.ops)
        && (NULL != s_lwm2m_al_op_cb.ops->delete_object))
    {
        ret = s_lwm2m_al_op_cb.ops->delete_object(handle, object_id);
    }

    return ret;
}

int lwm2m_al_connect(void *handle)
{
    int ret = (int)LWM2M_ERR;

    if ((NULL != handle)
        && (NULL != s_lwm2m_al_op_cb.ops)
        && (NULL != s_lwm2m_al_op_cb.ops->connect))
    {
        ret = s_lwm2m_al_op_cb.ops->connect(handle);
    }

    return ret;
}

int  lwm2m_al_disconnect(void *handle)
{
    int ret = (int)LWM2M_ERR;

    if ((NULL != handle)
        && (NULL != s_lwm2m_al_op_cb.ops)
        && (NULL != s_lwm2m_al_op_cb.ops->disconnect))
    {
        ret = s_lwm2m_al_op_cb.ops->disconnect(handle);
    }

    return ret;
}

int  lwm2m_al_send(void *handle, lwm2m_al_send_param_t *send_param)
{
    int ret = (int)LWM2M_ERR;

    if ((NULL != handle)
        && (NULL != send_param)
        && (NULL != s_lwm2m_al_op_cb.ops)
        && (NULL != s_lwm2m_al_op_cb.ops->send))
    {
        ret = s_lwm2m_al_op_cb.ops->send(handle, send_param);
    }

    return ret;
}

int lwm2m_al_install(lwm2m_al_op_t *op)
{
    int ret = (int)LWM2M_ERR;

    if ((NULL != op) && (NULL == s_lwm2m_al_op_cb.ops))
    {
        s_lwm2m_al_op_cb.mem  = *op;
        s_lwm2m_al_op_cb.ops = &s_lwm2m_al_op_cb.mem;
        ret = 0;
    }

    return ret;
}

int lwm2m_al_uninstall(void)
{
    int ret = (int)LWM2M_ERR;

    if (NULL != s_lwm2m_al_op_cb.ops)
    {
        s_lwm2m_al_op_cb.ops = NULL;
        ret = 0;
    }

    return ret;
}

#if 0 //
__attribute__((weak))  int lwm2m_imp_init(void)
{
    LINK_LOG_DEBUG("%s:###please implement lwm2m by yourself####\n\r",__FUNCTION__);
    return -1;
}
#endif

int lwm2m_al_init(void)
{

    int ret;

    ret = lwm2m_imp_init();

    LINK_LOG_DEBUG("IOT_LINK:DO LWM2M LOAD-IMPLEMENT RET:%d\n\r",ret);


    return ret;
}

