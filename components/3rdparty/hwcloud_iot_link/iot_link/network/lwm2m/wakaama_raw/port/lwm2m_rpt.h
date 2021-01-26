/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2018>, <Huawei Technologies Co., Ltd>
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

#ifndef LWM2M_RPT_H
#define LWM2M_RPT_H
#include <lwm2m_common.h>
#include "lwm2m_list.h"
#include <liblwm2m.h>

#ifdef __cplusplus
extern "C" {
#endif

#define URI_FORMAT "uri(objId:%d, instId:%d, resId:%d)"

#define URI_LOG_PARAM(uri) (uri)->objectId, (uri)->instanceId, (uri)->resourceId

LWM2M_INLINE void get_instance_uri(uint16_t object_id, uint16_t instance_id, lwm2m_uri_t *uri)
{
    if (NULL == uri)
    {
        return;
    }

    uri->objectId = object_id;
    uri->instanceId = instance_id;
    uri->resourceId = 0;
}

LWM2M_INLINE void get_resource_uri(uint16_t object_id, uint16_t instance_id, uint16_t resource_id, lwm2m_uri_t *uri)
{
    if (NULL == uri)
    {
        return;
    }

    uri->objectId = object_id;
    uri->instanceId = instance_id;
    uri->resourceId = resource_id;
}

struct _lwm2m_rpt_list_t;
typedef struct _lwm2m_rpt_list_t *rpt_list_t;

int lwm2m_init_rpt(void);
int lwm2m_add_rpt_uri(const lwm2m_uri_t *uri,  rpt_list_t *list);
int lwm2m_rm_rpt_uri(const lwm2m_uri_t *uri);

int lwm2m_dequeue_rpt_data(rpt_list_t rpt_list,  data_report_t *data);
int lwm2m_queue_rpt_data(const lwm2m_uri_t *uri, const data_report_t *data);
int lwm2m_clear_rpt_data(const lwm2m_uri_t *uri, int result);

int lwm2m_step_rpt(lwm2m_context_t *context);
void lwm2m_destroy_rpt(void);
int lwm2m_set_max_rpt_cnt(const lwm2m_uri_t *uri, uint32_t max_rpt_cnt);

#ifdef __cplusplus
}
#endif

#endif

