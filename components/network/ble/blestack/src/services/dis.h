/** @file
 *  @brief GATT Device Information Service
 */

/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __cplusplus
extern "C" {
#endif
enum{
    DIS_PNP_VID_SRC = 0x01,
    USB_IMPL_VID    
};
void dis_init(u8_t vid_src, u16_t vid, u16_t pid, u16_t pnp_ver);
#ifdef __cplusplus
}
#endif
