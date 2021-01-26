/**
 * Copyright (c) [2019] maminjie <canpool@163.com>
 *
 * vlink is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *    http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */

#include "lwm2m_uri.h"

void lwm2m_uri_inst(lwm2m_uri_t *uri, uint16_t obj_id, uint16_t inst_id)
{
    if (NULL == uri)
    {
        return;
    }

    uri->objectId = obj_id;
    uri->instanceId = inst_id;
    uri->resourceId = 0;
}

void lwm2m_uri_res(lwm2m_uri_t *uri, uint16_t obj_id, uint16_t inst_id, uint16_t res_id)
{
    if (NULL == uri)
    {
        return;
    }

    uri->objectId = obj_id;
    uri->instanceId = inst_id;
    uri->resourceId = res_id;
}

int lwm2m_uri_equal(const lwm2m_uri_t *uri0, const lwm2m_uri_t *uri1)
{
    if (LWM2M_URI_IS_SET_RESOURCE(uri0) && LWM2M_URI_IS_SET_RESOURCE(uri1))
    {
        return (uri0->objectId == uri1->objectId) && (uri0->instanceId == uri1->instanceId)
               && (uri0->resourceId == uri1->resourceId);
    }

    return (uri0->objectId == uri1->objectId) && (uri0->instanceId == uri1->instanceId);
}