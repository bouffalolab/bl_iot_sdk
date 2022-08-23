#if defined(CONFIG_BT_MESH_SYNC)
#ifndef __BLE_SYNC_H_
#define __BLE_SYNC_H_

#include "blsync_ble.h"

void blsync_blemesh_start (void);

void blsync_blemesh_stop (void);

#endif 
#endif /* CONFIG_BT_MESH_SYNC */