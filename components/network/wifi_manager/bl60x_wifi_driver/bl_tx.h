/*
 * Copyright (c) 2016-2023 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __RWNX_TX_H__
#define __RWNX_TX_H__
#include <lwip/opt.h>
#include <lwip/mem.h>
#include <utils_list.h>

#include "lmac_types.h"
#include "ipc_shared.h"
#include "bl_utils.h"

/**
 ****************************************************************************************
 *
 * @file bl_tx.h
 * Copyright (C) Bouffalo Lab 2016-2018
 *
 ****************************************************************************************
 */

// Customer callback function type definition
typedef void (*bl_tx_callback_t)(void *cb_arg, bool tx_ok);

// Customer callback
struct bl_tx_cfm {
    bl_tx_callback_t cb;
    void *cb_arg;
};

// TX status from FW/HW
union bl_hw_txstatus {
    struct {
        u32 tx_done            : 1;
        u32 retry_required     : 1;
        u32 sw_retry_required  : 1;
        u32 reserved           :29;
    };
    u32 value;
};

/**
 * struct bl_txhdr - Stucture to control transimission of packet
 * (Added in skb headroom)
 *
 * @item:       List item for list operation
 * @custom_cfm: Customer callback for TX
 * @status:     Status for FW/HW to return TX result
 * @p:          Pbuf from upper tcp/ip stack
 * @vif_type:   0: STA, 1: AP, [2-F]:Other
 * @sta_id:     staid, here range is [0-f]
 * @repush:     Repush counter
 */
struct bl_txhdr {
    struct utils_list_hdr item;
    struct bl_tx_cfm      custom_cfm;
    union bl_hw_txstatus  status;
    uint32_t             *p;
    uint16_t              len      : 16;
    uint16_t              vif_type : 4;
    uint16_t              sta_id   : 4;
    uint16_t              repush   : 8;
};

/// XXX: put here for now
struct ke_tx_fc {
    /// 0: sta, 1: ap
    uint8_t vif_bits;
    /// For ap
    struct {
        uint8_t fc_chan;
        uint8_t fc_ps_sta_bits;
    } ap;
    /// For sta
    struct {
        uint8_t fc_chan;
        uint8_t fc_ps;
    } sta;
};

#ifdef CFG_NETBUS_WIFI_ENABLE
err_t bl_output(struct bl_hw *bl_hw, int is_sta, struct pbuf *p, struct bl_tx_cfm *custom_cfm, uint8_t from_local);
#else
err_t bl_output(struct bl_hw *bl_hw, int is_sta, struct pbuf *p, struct bl_tx_cfm *custom_cfm);
#endif
int   bl_tx_cfm(void *pthis, void *host_id);
void  bl_tx_try_flush(int param, struct ke_tx_fc *tx_fc_field);
void  bl_tx_cntrl_link_up(struct bl_sta *sta);
void  bl_tx_cntrl_link_down(struct bl_sta *sta);
#endif
