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

#ifndef __LWM2M_URI_H__
#define __LWM2M_URI_H__

#include "liblwm2m.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// uri instantiation, like /1/2
void lwm2m_uri_inst(lwm2m_uri_t *uri, uint16_t obj_id, uint16_t inst_id);

// uri resource, like /1/0/1
void lwm2m_uri_res(lwm2m_uri_t *uri, uint16_t obj_id, uint16_t inst_id, uint16_t res_id);

int lwm2m_uri_equal(const lwm2m_uri_t *uri0, const lwm2m_uri_t *uri1);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LWM2M_URI_H__ */
