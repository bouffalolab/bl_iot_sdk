/*  Bluetooth Mesh */

#ifndef __LOCAL_OPERATION_H__
#define __LOCAL_OPERATION_H__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

int bt_mesh_model_subscribe_group_addr(u16_t elem_addr, u16_t mod_id,
                                       u16_t cid, u16_t group_addr);

int bt_mesh_model_unsubscribe_group_addr(u16_t elem_addr, u16_t cid,
                                         u16_t mod_id, u16_t group_addr);

#ifdef __cplusplus
}
#endif

#endif /*__LOCAL_OPERATION_H__*/
