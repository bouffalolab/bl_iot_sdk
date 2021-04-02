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
#include "include/mesh.h"


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

int bt_mesh_local_model_bind(u16_t net_idx, u16_t mod_app_idx)
{
	int i, j, err = 0;
	const struct bt_mesh_comp* dev_comp = bt_mesh_comp_get();
	u16_t addr = bt_mesh_primary_addr();
	u8_t status;
	
	for (i = 0; i < dev_comp->elem_count; i++) {
		struct bt_mesh_elem *elem = &dev_comp->elem[i];

		for (j = 0; j < elem->model_count; j++) {
			struct bt_mesh_model *model = &elem->models[j];
			
			if(model->id == BT_MESH_MODEL_ID_CFG_CLI
				|| model->id == BT_MESH_MODEL_ID_CFG_SRV){
				continue;
			}
			err = bt_mesh_cfg_mod_app_bind(net_idx, addr, addr+i,
								mod_app_idx, model->id, &status);
		}

		for (j = 0; j < elem->vnd_model_count; j++) {
			struct bt_mesh_model *model = &elem->vnd_models[j];

			err = bt_mesh_cfg_mod_app_bind_vnd(net_idx, addr,
						   addr+i, mod_app_idx,
						   model->vnd.id, model->vnd.company, &status);
		}
	}
	return err;
}