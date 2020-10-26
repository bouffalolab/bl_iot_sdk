/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __MESH_SETTING_H__
#define __MESH_SETTING_H__

#if defined(BFLB_BLE)
#define NV_MESH_IV          "bt/mesh/IV"
#define NV_MESH_NET         "bt/mesh/NetInfo"
#define NV_MESH_SEQ         "bt/mesh/Seq"
#define NV_MESH_RPL         "bt/mesh/RPL"
#define NV_MESH_HBPUB       "bt/mesh/HBPub"
#define NV_MESH_CFG         "bt/mesh/Cfg"

int mesh_set(void);
int mesh_commit(void);
#endif

void bt_mesh_store_net(void);
void bt_mesh_store_iv(bool only_duration);
void bt_mesh_store_seq(void);
void bt_mesh_store_rpl(struct bt_mesh_rpl *rpl);
void bt_mesh_store_subnet(struct bt_mesh_subnet *sub);
void bt_mesh_store_app_key(struct bt_mesh_app_key *key);
void bt_mesh_store_hb_pub(void);
void bt_mesh_store_cfg(void);
void bt_mesh_store_mod_bind(struct bt_mesh_model *mod);
void bt_mesh_store_mod_sub(struct bt_mesh_model *mod);
void bt_mesh_store_mod_pub(struct bt_mesh_model *mod);

void bt_mesh_clear_net(void);
void bt_mesh_clear_subnet(struct bt_mesh_subnet *sub);
void bt_mesh_clear_app_key(struct bt_mesh_app_key *key);
void bt_mesh_clear_rpl(void);

void bt_mesh_settings_init(void);

#endif /*__MESH_SETTING_H__*/
