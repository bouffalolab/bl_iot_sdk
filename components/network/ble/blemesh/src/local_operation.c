/*  Bluetooth Mesh */

#include <string.h>
#include <errno.h>

#include "mesh.h"
#include "lpn.h"
#include "crypto.h"
#include "access.h"
#include "foundation.h"
#include "transport.h"
#include "include/main.h"
#include "mesh_settings.h"


int bt_mesh_model_subscribe_group_addr(u16_t elem_addr, u16_t cid,
                                       u16_t mod_id, u16_t group_addr)
{
    return -ENOMEM;
}

int bt_mesh_model_unsubscribe_group_addr(u16_t elem_addr, u16_t cid,
                                         u16_t mod_id, u16_t group_addr)
{
    return -ENODEV;
}
