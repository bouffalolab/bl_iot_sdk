
/*
 * Copyright (c) 2020 Bouffalolab.
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


#include "bl_utils.h"
#include "lmac_msg.h"

static const char *const bl_mmid2str[MSG_I(MM_MAX)] = {
    [MSG_I(MM_RESET_REQ)]                 = "MM_RESET_REQ",
    [MSG_I(MM_RESET_CFM)]                 = "MM_RESET_CFM",
    [MSG_I(MM_START_REQ)]                 = "MM_START_REQ",
    [MSG_I(MM_START_CFM)]                 = "MM_START_CFM",
    [MSG_I(MM_VERSION_REQ)]               = "MM_VERSION_REQ",
    [MSG_I(MM_VERSION_CFM)]               = "MM_VERSION_CFM",
    [MSG_I(MM_ADD_IF_REQ)]                = "MM_ADD_IF_REQ",
    [MSG_I(MM_ADD_IF_CFM)]                = "MM_ADD_IF_CFM",
    [MSG_I(MM_REMOVE_IF_REQ)]             = "MM_REMOVE_IF_REQ",
    [MSG_I(MM_REMOVE_IF_CFM)]             = "MM_REMOVE_IF_CFM",
    [MSG_I(MM_STA_ADD_REQ)]               = "MM_STA_ADD_REQ",
    [MSG_I(MM_STA_ADD_CFM)]               = "MM_STA_ADD_CFM",
    [MSG_I(MM_STA_DEL_REQ)]               = "MM_STA_DEL_REQ",
    [MSG_I(MM_STA_DEL_CFM)]               = "MM_STA_DEL_CFM",
    [MSG_I(MM_SET_FILTER_REQ)]            = "MM_SET_FILTER_REQ",
    [MSG_I(MM_SET_FILTER_CFM)]            = "MM_SET_FILTER_CFM",
    [MSG_I(MM_SET_CHANNEL_REQ)]           = "MM_SET_CHANNEL_REQ",
    [MSG_I(MM_SET_CHANNEL_CFM)]           = "MM_SET_CHANNEL_CFM",
    [MSG_I(MM_SET_DTIM_REQ)]              = "MM_SET_DTIM_REQ",
    [MSG_I(MM_SET_DTIM_CFM)]              = "MM_SET_DTIM_CFM",
    [MSG_I(MM_SET_BEACON_INT_REQ)]        = "MM_SET_BEACON_INT_REQ",
    [MSG_I(MM_SET_BEACON_INT_CFM)]        = "MM_SET_BEACON_INT_CFM",
    [MSG_I(MM_SET_BASIC_RATES_REQ)]       = "MM_SET_BASIC_RATES_REQ",
    [MSG_I(MM_SET_BASIC_RATES_CFM)]       = "MM_SET_BASIC_RATES_CFM",
    [MSG_I(MM_SET_BSSID_REQ)]             = "MM_SET_BSSID_REQ",
    [MSG_I(MM_SET_BSSID_CFM)]             = "MM_SET_BSSID_CFM",
    [MSG_I(MM_SET_EDCA_REQ)]              = "MM_SET_EDCA_REQ",
    [MSG_I(MM_SET_EDCA_CFM)]              = "MM_SET_EDCA_CFM",
    [MSG_I(MM_SET_MODE_REQ)]              = "MM_SET_MODE_REQ",
    [MSG_I(MM_SET_MODE_CFM)]              = "MM_SET_MODE_CFM",
    [MSG_I(MM_SET_VIF_STATE_REQ)]         = "MM_SET_VIF_STATE_REQ",
    [MSG_I(MM_SET_VIF_STATE_CFM)]         = "MM_SET_VIF_STATE_CFM",
    [MSG_I(MM_SET_SLOTTIME_REQ)]          = "MM_SET_SLOTTIME_REQ",
    [MSG_I(MM_SET_SLOTTIME_CFM)]          = "MM_SET_SLOTTIME_CFM",
    [MSG_I(MM_SET_IDLE_REQ)]              = "MM_SET_IDLE_REQ",
    [MSG_I(MM_SET_IDLE_CFM)]              = "MM_SET_IDLE_CFM",
    [MSG_I(MM_KEY_ADD_REQ)]               = "MM_KEY_ADD_REQ",
    [MSG_I(MM_KEY_ADD_CFM)]               = "MM_KEY_ADD_CFM",
    [MSG_I(MM_KEY_DEL_REQ)]               = "MM_KEY_DEL_REQ",
    [MSG_I(MM_KEY_DEL_CFM)]               = "MM_KEY_DEL_CFM",
    [MSG_I(MM_BA_ADD_REQ)]                = "MM_BA_ADD_REQ",
    [MSG_I(MM_BA_ADD_CFM)]                = "MM_BA_ADD_CFM",
    [MSG_I(MM_BA_DEL_REQ)]                = "MM_BA_DEL_REQ",
    [MSG_I(MM_BA_DEL_CFM)]                = "MM_BA_DEL_CFM",
    [MSG_I(MM_PRIMARY_TBTT_IND)]          = "MM_PRIMARY_TBTT_IND",
    [MSG_I(MM_SECONDARY_TBTT_IND)]        = "MM_SECONDARY_TBTT_IND",
    [MSG_I(MM_SET_POWER_REQ)]             = "MM_SET_POWER_REQ",
    [MSG_I(MM_SET_POWER_CFM)]             = "MM_SET_POWER_CFM",
    [MSG_I(MM_DENOISE_REQ)]               = "MM_DENOISE_REQ",
    [MSG_I(MM_SET_PS_MODE_REQ)]           = "MM_SET_PS_MODE_REQ",
    [MSG_I(MM_SET_PS_MODE_CFM)]           = "MM_SET_PS_MODE_CFM",
    [MSG_I(MM_CHAN_CTXT_ADD_REQ)]         = "MM_CHAN_CTXT_ADD_REQ",
    [MSG_I(MM_CHAN_CTXT_ADD_CFM)]         = "MM_CHAN_CTXT_ADD_CFM",
    [MSG_I(MM_CHAN_CTXT_DEL_REQ)]         = "MM_CHAN_CTXT_DEL_REQ",
    [MSG_I(MM_CHAN_CTXT_DEL_CFM)]         = "MM_CHAN_CTXT_DEL_CFM",
    [MSG_I(MM_CHAN_CTXT_LINK_REQ)]        = "MM_CHAN_CTXT_LINK_REQ",
    [MSG_I(MM_CHAN_CTXT_LINK_CFM)]        = "MM_CHAN_CTXT_LINK_CFM",
    [MSG_I(MM_CHAN_CTXT_UNLINK_REQ)]      = "MM_CHAN_CTXT_UNLINK_REQ",
    [MSG_I(MM_CHAN_CTXT_UNLINK_CFM)]      = "MM_CHAN_CTXT_UNLINK_CFM",
    [MSG_I(MM_CHAN_CTXT_UPDATE_REQ)]      = "MM_CHAN_CTXT_UPDATE_REQ",
    [MSG_I(MM_CHAN_CTXT_UPDATE_CFM)]      = "MM_CHAN_CTXT_UPDATE_CFM",
    [MSG_I(MM_CHAN_CTXT_SCHED_REQ)]       = "MM_CHAN_CTXT_SCHED_REQ",
    [MSG_I(MM_CHAN_CTXT_SCHED_CFM)]       = "MM_CHAN_CTXT_SCHED_CFM",
    [MSG_I(MM_BCN_CHANGE_REQ)]            = "MM_BCN_CHANGE_REQ",
    [MSG_I(MM_BCN_CHANGE_CFM)]            = "MM_BCN_CHANGE_CFM",
    [MSG_I(MM_TIM_UPDATE_REQ)]            = "MM_TIM_UPDATE_REQ",
    [MSG_I(MM_TIM_UPDATE_CFM)]            = "MM_TIM_UPDATE_CFM",
    [MSG_I(MM_CONNECTION_LOSS_IND)]       = "MM_CONNECTION_LOSS_IND",
    [MSG_I(MM_CHANNEL_SWITCH_IND)]        = "MM_CHANNEL_SWITCH_IND",
    [MSG_I(MM_CHANNEL_PRE_SWITCH_IND)]    = "MM_CHANNEL_PRE_SWITCH_IND",
    [MSG_I(MM_REMAIN_ON_CHANNEL_REQ)]     = "MM_REMAIN_ON_CHANNEL_REQ",
    [MSG_I(MM_REMAIN_ON_CHANNEL_CFM)]     = "MM_REMAIN_ON_CHANNEL_CFM",
    [MSG_I(MM_REMAIN_ON_CHANNEL_EXP_IND)] = "MM_REMAIN_ON_CHANNEL_EXP_IND",
    [MSG_I(MM_PS_CHANGE_IND)]             = "MM_PS_CHANGE_IND",
    [MSG_I(MM_TRAFFIC_REQ_IND)]           = "MM_TRAFFIC_REQ_IND",
    [MSG_I(MM_SET_PS_OPTIONS_REQ)]        = "MM_SET_PS_OPTIONS_REQ",
    [MSG_I(MM_SET_PS_OPTIONS_CFM)]        = "MM_SET_PS_OPTIONS_CFM",
    [MSG_I(MM_P2P_VIF_PS_CHANGE_IND)]     = "MM_P2P_VIF_PS_CHANGE_IND",
    [MSG_I(MM_CSA_COUNTER_IND)]           = "MM_CSA_COUNTER_IND",
    [MSG_I(MM_CHANNEL_SURVEY_IND)]        = "MM_CHANNEL_SURVEY_IND",
    [MSG_I(MM_SET_P2P_NOA_REQ)]           = "MM_SET_P2P_NOA_REQ",
    [MSG_I(MM_SET_P2P_OPPPS_REQ)]         = "MM_SET_P2P_OPPPS_REQ",
    [MSG_I(MM_SET_P2P_NOA_CFM)]           = "MM_SET_P2P_NOA_CFM",
    [MSG_I(MM_SET_P2P_OPPPS_CFM)]         = "MM_SET_P2P_OPPPS_CFM",
    [MSG_I(MM_CFG_RSSI_REQ)]              = "MM_CFG_RSSI_REQ",
    [MSG_I(MM_RSSI_STATUS_IND)]           = "MM_RSSI_STATUS_IND",
    [MSG_I(MM_CSA_FINISH_IND)]            = "MM_CSA_FINISH_IND",
    [MSG_I(MM_CSA_TRAFFIC_IND)]           = "MM_CSA_TRAFFIC_IND",
    [MSG_I(MM_MU_GROUP_UPDATE_REQ)]       = "MM_MU_GROUP_UPDATE_REQ",
    [MSG_I(MM_MU_GROUP_UPDATE_CFM)]       = "MM_MU_GROUP_UPDATE_CFM",
};

static const char *const bl_dbgid2str[MSG_I(DBG_MAX)] = {
    [MSG_I(DBG_MEM_READ_REQ)]        = "DBG_MEM_READ_REQ",
    [MSG_I(DBG_MEM_READ_CFM)]        = "DBG_MEM_READ_CFM",
    [MSG_I(DBG_MEM_WRITE_REQ)]       = "DBG_MEM_WRITE_REQ",
    [MSG_I(DBG_MEM_WRITE_CFM)]       = "DBG_MEM_WRITE_CFM",
    [MSG_I(DBG_SET_MOD_FILTER_REQ)]  = "DBG_SET_MOD_FILTER_REQ",
    [MSG_I(DBG_SET_MOD_FILTER_CFM)]  = "DBG_SET_MOD_FILTER_CFM",
    [MSG_I(DBG_SET_SEV_FILTER_REQ)]  = "DBG_SET_SEV_FILTER_REQ",
    [MSG_I(DBG_SET_SEV_FILTER_CFM)]  = "DBG_SET_SEV_FILTER_CFM",
    [MSG_I(DBG_ERROR_IND)]           = "DBG_ERROR_IND",
    [MSG_I(DBG_GET_SYS_STAT_REQ)]    = "DBG_GET_SYS_STAT_REQ",
    [MSG_I(DBG_GET_SYS_STAT_CFM)]    = "DBG_GET_SYS_STAT_CFM",
};

static const char *const bl_scanid2str[MSG_I(SCAN_MAX)] = {
    [MSG_I(SCAN_START_REQ)]          = "SCAN_START_REQ",
    [MSG_I(SCAN_START_CFM)]          = "SCAN_START_CFM",
    [MSG_I(SCAN_DONE_IND)]           = "SCAN_DONE_IND",
};

static const char *const bl_tdlsid2str[MSG_I(TDLS_MAX)] = {
    [MSG_I(TDLS_CHAN_SWITCH_CFM)] = "TDLS_CHAN_SWITCH_CFM",
    [MSG_I(TDLS_CHAN_SWITCH_REQ)] = "TDLS_CHAN_SWITCH_REQ",
    [MSG_I(TDLS_CHAN_SWITCH_IND)] = "TDLS_CHAN_SWITCH_IND",
    [MSG_I(TDLS_CHAN_SWITCH_BASE_IND)] = "TDLS_CHAN_SWITCH_BASE_IND",
};

#ifdef CONFIG_RWNX_FULLMAC

static const char *const bl_scanuid2str[MSG_I(SCANU_MAX)] = {
    [MSG_I(SCANU_START_REQ)]  = "SCANU_START_REQ",
    [MSG_I(SCANU_START_CFM)]  = "SCANU_START_CFM",
    [MSG_I(SCANU_JOIN_REQ)]   = "SCANU_JOIN_REQ",
    [MSG_I(SCANU_JOIN_CFM)]   = "SCANU_JOIN_CFM",
    [MSG_I(SCANU_RESULT_IND)] = "SCANU_RESULT_IND",
    [MSG_I(SCANU_RAW_SEND_REQ)]   = "SCANU_RAW_SEND_REQ",
    [MSG_I(SCANU_RAW_SEND_CFM)]   = "SCANU_RAW_SEND_CFM",
};

static const char *const bl_meid2str[MSG_I(ME_MAX)] = {
    [MSG_I(ME_CONFIG_REQ)]           = "ME_CONFIG_REQ",
    [MSG_I(ME_CONFIG_CFM)]           = "ME_CONFIG_CFM",
    [MSG_I(ME_CHAN_CONFIG_REQ)]      = "ME_CHAN_CONFIG_REQ",
    [MSG_I(ME_CHAN_CONFIG_CFM)]      = "ME_CHAN_CONFIG_CFM",
    [MSG_I(ME_SET_CONTROL_PORT_REQ)] = "ME_SET_CONTROL_PORT_REQ",
    [MSG_I(ME_SET_CONTROL_PORT_CFM)] = "ME_SET_CONTROL_PORT_CFM",
    [MSG_I(ME_TKIP_MIC_FAILURE_IND)] = "ME_TKIP_MIC_FAILURE_IND",
    [MSG_I(ME_STA_ADD_REQ)]          = "ME_STA_ADD_REQ",
    [MSG_I(ME_STA_ADD_CFM)]          = "ME_STA_ADD_CFM",
    [MSG_I(ME_STA_DEL_REQ)]          = "ME_STA_DEL_REQ",
    [MSG_I(ME_STA_DEL_CFM)]          = "ME_STA_DEL_CFM",
    [MSG_I(ME_TX_CREDITS_UPDATE_IND)]= "ME_TX_CREDITS_UPDATE_IND",
    [MSG_I(ME_RC_STATS_REQ)]         = "ME_RC_STATS_REQ",
    [MSG_I(ME_RC_STATS_CFM)]         = "ME_RC_STATS_CFM",
    [MSG_I(ME_RC_SET_RATE_REQ)]      = "ME_RC_SET_RATE_REQ",
    [MSG_I(ME_TRAFFIC_IND_REQ)]      = "ME_TRAFFIC_IND_REQ",
    [MSG_I(ME_TRAFFIC_IND_CFM)]      = "ME_TRAFFIC_IND_CFM",
};

static const char *const bl_smid2str[MSG_I(SM_MAX)] = {
    [MSG_I(SM_CONNECT_REQ)]       = "SM_CONNECT_REQ",
    [MSG_I(SM_CONNECT_CFM)]       = "SM_CONNECT_CFM",
    [MSG_I(SM_CONNECT_IND)]       = "SM_CONNECT_IND",
    [MSG_I(SM_DISCONNECT_REQ)]    = "SM_DISCONNECT_REQ",
    [MSG_I(SM_DISCONNECT_CFM)]    = "SM_DISCONNECT_CFM",
    [MSG_I(SM_DISCONNECT_IND)]    = "SM_DISCONNECT_IND",
    [MSG_I(SM_RSP_TIMEOUT_IND)]   = "SM_RSP_TIMEOUT_IND",
};

static const char *const bl_apmid2str[MSG_I(APM_MAX)] = {
    [MSG_I(APM_START_REQ)]     = "APM_START_REQ",
    [MSG_I(APM_START_CFM)]     = "APM_START_CFM",
    [MSG_I(APM_STOP_REQ)]      = "APM_STOP_REQ",
    [MSG_I(APM_STOP_CFM)]      = "APM_STOP_CFM",
    [MSG_I(APM_START_CAC_REQ)] = "APM_START_CAC_REQ",
    [MSG_I(APM_START_CAC_CFM)] = "APM_START_CAC_CFM",
    [MSG_I(APM_STOP_CAC_REQ)]  = "APM_STOP_CAC_REQ",
    [MSG_I(APM_STOP_CAC_CFM)]  = "APM_STOP_CAC_CFM",
    [MSG_I(APM_STA_CONNECT_TIMEOUT)]  = "APM_STA_CONNECT_TIMEOUT",
    [MSG_I(APM_STA_DEL_REQ)]   = "APM_STA_DEL_REQ",
    [MSG_I(APM_STA_DEL_CFM)]   = "APM_STA_DEL_CFM",
    [MSG_I(APM_CONF_MAX_STA_REQ)]   = "APM_CONF_MAX_STA_REQ",
    [MSG_I(APM_CONF_MAX_STA_CFM)]   = "APM_CONF_MAX_STA_CFM",
};

static const char *const bl_meshid2str[MSG_I(MESH_MAX)] = {
    [MSG_I(MESH_START_REQ)]        = "MESH_START_REQ",
    [MSG_I(MESH_START_CFM)]        = "MESH_START_CFM",
    [MSG_I(MESH_STOP_REQ)]         = "MESH_STOP_REQ",
    [MSG_I(MESH_STOP_CFM)]         = "MESH_STOP_CFM",
    [MSG_I(MESH_UPDATE_REQ)]       = "MESH_UPDATE_REQ",
    [MSG_I(MESH_UPDATE_CFM)]       = "MESH_UPDATE_CFM",
    [MSG_I(MESH_PATH_CREATE_REQ)]  = "MESH_PATH_CREATE_REQ",
    [MSG_I(MESH_PATH_CREATE_CFM)]  = "MESH_PATH_CREATE_CFM",
    [MSG_I(MESH_PATH_UPDATE_REQ)]  = "MESH_PATH_UPDATE_REQ",
    [MSG_I(MESH_PATH_UPDATE_CFM)]  = "MESH_PATH_UPDATE_CFM",
    [MSG_I(MESH_PROXY_ADD_REQ)]    = "MESH_PROXY_ADD_REQ",
    [MSG_I(MESH_PEER_UPDATE_IND)]  = "MESH_PEER_UPDATE_IND",
    [MSG_I(MESH_PATH_UPDATE_IND)]  = "MESH_PATH_UPDATE_IND",
    [MSG_I(MESH_PROXY_UPDATE_IND)] = "MESH_PROXY_UPDATE_IND",
};

#endif /* CONFIG_RWNX_FULLMAC */

const char *const *bl_id2str[TASK_LAST_EMB + 1] = {
    [TASK_MM]    = bl_mmid2str,
    [TASK_DBG]   = bl_dbgid2str,
    [TASK_SCAN]  = bl_scanid2str,
    [TASK_TDLS]  = bl_tdlsid2str,
#ifdef CONFIG_RWNX_FULLMAC
    [TASK_SCANU] = bl_scanuid2str,
    [TASK_ME]    = bl_meid2str,
    [TASK_SM]    = bl_smid2str,
    [TASK_APM]   = bl_apmid2str,
    [TASK_MESH]  = bl_meshid2str,
#endif
};
