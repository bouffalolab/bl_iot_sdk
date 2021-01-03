
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

#include "bl_defs.h"
#include "hal_desc.h"
#include "reg_mac_core.h"

#define COMMON_PARAM(name, default_softmac, default_fullmac)    \
    .name = default_fullmac,
#define SOFTMAC_PARAM(name, default)
#define FULLMAC_PARAM(name, default) .name = default,

struct bl_mod_params bl_mod_params = {
    /* common parameters */
    COMMON_PARAM(ht_on, true, true)
    COMMON_PARAM(vht_on, false, false)
    COMMON_PARAM(mcs_map, IEEE80211_VHT_MCS_SUPPORT_0_7, IEEE80211_VHT_MCS_SUPPORT_0_7)
    COMMON_PARAM(ldpc_on, false, false)
    COMMON_PARAM(vht_stbc, false, false)
    COMMON_PARAM(phy_cfg, 2, 2)
    COMMON_PARAM(uapsd_timeout, 300, 300)
    COMMON_PARAM(ap_uapsd_on, true, true)
    COMMON_PARAM(sgi, false, false)
    COMMON_PARAM(sgi80, false, false)
    COMMON_PARAM(use_2040, 0, 0)
    COMMON_PARAM(nss, 1, 1)
    COMMON_PARAM(bfmee, true, true)
    COMMON_PARAM(bfmer, false, false)
    COMMON_PARAM(mesh, false, false)
    COMMON_PARAM(murx, false, false)
    COMMON_PARAM(mutx, false, false)
    COMMON_PARAM(mutx_on, false, false)
    COMMON_PARAM(use_80, false, false)
    COMMON_PARAM(custregd, false, false)
    COMMON_PARAM(roc_dur_max, 500, 500)
    COMMON_PARAM(listen_itv, 1, 1)
    COMMON_PARAM(listen_bcmc, true, true)
    COMMON_PARAM(lp_clk_ppm, 20, 20)
    COMMON_PARAM(ps_on, false, false)
    COMMON_PARAM(tx_lft, RWNX_TX_LIFETIME_MS, RWNX_TX_LIFETIME_MS)
    COMMON_PARAM(amsdu_maxnb, NX_TX_PAYLOAD_MAX, NX_TX_PAYLOAD_MAX)
    // By default, only enable UAPSD for Voice queue (see IEEE80211_DEFAULT_UAPSD_QUEUE comment)
    COMMON_PARAM(uapsd_queues, IEEE80211_WMM_IE_STA_QOSINFO_AC_VO, IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
    COMMON_PARAM(tdls, false, false)

    /* FULLMAC only parameters */
};

#if 0
/* Regulatory rules */
static const struct ieee80211_regdomain bl_regdom = {
    .n_reg_rules = 3,
    .alpha2 = "99",
    .reg_rules = {
        REG_RULE(2412 - 10, 2472 + 10, 40, 0, 1000, 0),
        REG_RULE(2484 - 10, 2484 + 10, 20, 0, 1000, 0),
        REG_RULE(5150 - 10, 5850 + 10, 80, 0, 1000, 0),
    }
};
#endif

#if 0
/**
 * Do some sanity check
 *
 */
static int bl_check_fw_hw_feature(struct bl_hw *bl_hw,
                                    struct wiphy *wiphy)
{
    u32_l sys_feat = bl_hw->version_cfm.features;
    u32_l mac_feat = bl_hw->version_cfm.version_machw_1;
    u32_l phy_feat = bl_hw->version_cfm.version_phy_1;


    if (!(sys_feat & BIT(MM_FEAT_UMAC_BIT))) {
        wiphy_err(wiphy,
                  "Loading softmac firmware with fullmac driver\n");
        return -1;
    }


    if (!(sys_feat & BIT(MM_FEAT_VHT_BIT))) {
        bl_hw->mod_params->vht_on = false;
    }

    if (!(sys_feat & BIT(MM_FEAT_PS_BIT))) {
        bl_hw->mod_params->ps_on = false;
    }

    /* AMSDU (non)support implies different shared structure definition
       so insure that fw and drv have consistent compilation option */
    if (sys_feat & BIT(MM_FEAT_AMSDU_BIT)) {
#ifndef CONFIG_RWNX_SPLIT_TX_BUF
        wiphy_err(wiphy,
                  "AMSDU enabled in firmware but support not compiled in driver\n");
        return -1;
#else
        if (bl_hw->mod_params->amsdu_maxnb > NX_TX_PAYLOAD_MAX)
            bl_hw->mod_params->amsdu_maxnb = NX_TX_PAYLOAD_MAX;
#endif /* CONFIG_RWNX_SPLIT_TX_BUF */
    } else {
#ifdef CONFIG_RWNX_SPLIT_TX_BUF
        wiphy_err(wiphy,
                  "AMSDU disabled in firmware but support compiled in driver\n");
        return -1;
#endif /* CONFIG_RWNX_SPLIT_TX_BUF */
    }

    if (!(sys_feat & BIT(MM_FEAT_UAPSD_BIT))) {
        bl_hw->mod_params->uapsd_timeout = 0;
    }

    if (!(sys_feat & BIT(MM_FEAT_BFMEE_BIT))) {
        bl_hw->mod_params->bfmee = false;
    }

    if ((sys_feat & BIT(MM_FEAT_BFMER_BIT))) {
#ifndef CONFIG_RWNX_BFMER
        wiphy_err(wiphy,
                  "BFMER enabled in firmware but support not compiled in driver\n");
        return -1;
#endif /* CONFIG_RWNX_BFMER */
        // Check PHY and MAC HW BFMER support and update parameter accordingly
        if (!(phy_feat & MDM_BFMER_BIT) || !(mac_feat & NXMAC_BFMER_BIT)) {
            bl_hw->mod_params->bfmer = false;
            // Disable the feature in the bitfield so that it won't be displayed
            sys_feat &= ~BIT(MM_FEAT_BFMER_BIT);
        }
    } else {
#ifdef CONFIG_RWNX_BFMER
        wiphy_err(wiphy,
                  "BFMER disabled in firmware but support compiled in driver\n");
        return -1;
#else
        bl_hw->mod_params->bfmer = false;
#endif /* CONFIG_RWNX_BFMER */
    }

    if (!(sys_feat & BIT(MM_FEAT_MESH_BIT))) {
        bl_hw->mod_params->mesh = false;
    }

    if (!(sys_feat & BIT(MM_FEAT_TDLS_BIT))) {
        bl_hw->mod_params->tdls = false;
    }

    if (!(sys_feat & BIT(MM_FEAT_MU_MIMO_RX_BIT)) ||
        !bl_hw->mod_params->bfmee) {
        bl_hw->mod_params->murx = false;
    }

    if ((sys_feat & BIT(MM_FEAT_MU_MIMO_TX_BIT))) {
#ifndef CONFIG_RWNX_MUMIMO_TX
        wiphy_err(wiphy,
                  "MU-MIMO TX enabled in firmware but support not compiled in driver\n");
        return -1;
#endif /* CONFIG_RWNX_MUMIMO_TX */
        if (!bl_hw->mod_params->bfmer)
            bl_hw->mod_params->mutx = false;
        // Check PHY and MAC HW MU-MIMO TX support and update parameter accordingly
        else if (!(phy_feat & MDM_MUMIMOTX_BIT) || !(mac_feat & NXMAC_MU_MIMO_TX_BIT)) {
                bl_hw->mod_params->mutx = false;
                // Disable the feature in the bitfield so that it won't be displayed
                sys_feat &= ~BIT(MM_FEAT_MU_MIMO_TX_BIT);
        }
    } else {
#ifdef CONFIG_RWNX_MUMIMO_TX
        wiphy_err(wiphy,
                  "MU-MIMO TX disabled in firmware but support compiled in driver\n");
        return -1;
#else
        bl_hw->mod_params->mutx = false;
#endif /* CONFIG_RWNX_MUMIMO_TX */
    }

    if (sys_feat & BIT(MM_FEAT_WAPI_BIT)) {
        bl_enable_wapi(bl_hw);
    }

#ifdef CONFIG_RWNX_FULLMAC
    if (sys_feat & BIT(MM_FEAT_MFP_BIT)) {
        bl_enable_mfp(bl_hw);
    }
#endif

#ifdef CONFIG_RWNX_SOFTMAC
#define QUEUE_NAME "BEACON queue "
#else
#define QUEUE_NAME "Broadcast/Multicast queue "
#endif /* CONFIG_RWNX_SOFTMAC */

    if (sys_feat & BIT(MM_FEAT_BCN_BIT)) {
#if NX_TXQ_CNT == 4
        wiphy_err(wiphy, QUEUE_NAME
                  "enabled in firmware but support not compiled in driver\n");
        return -1;
#endif /* NX_TXQ_CNT == 4 */
    } else {
#if NX_TXQ_CNT == 5
        wiphy_err(wiphy, QUEUE_NAME
                  "disabled in firmware but support compiled in driver\n");
        return -1;
#endif /* NX_TXQ_CNT == 5 */
    }
#undef QUEUE_NAME

#ifdef CONFIG_RWNX_RADAR
    if (sys_feat & BIT(MM_FEAT_RADAR_BIT)) {
        /* Enable combination with radar detection */
        wiphy->n_iface_combinations++;
    }
#endif /* CONFIG_RWNX_RADAR */

#ifndef CONFIG_RWNX_SDM
    switch (__MDM_PHYCFG_FROM_VERS(phy_feat)) {
        case MDM_PHY_CONFIG_TRIDENT:
        case MDM_PHY_CONFIG_ELMA:
            bl_hw->mod_params->nss = 1;
            break;
        case MDM_PHY_CONFIG_KARST:
            {
                int nss_supp = (phy_feat & MDM_NSS_MASK) >> MDM_NSS_LSB;
                if (bl_hw->mod_params->nss > nss_supp)
                    bl_hw->mod_params->nss = nss_supp;
            }
            break;
        default:
            WARN_ON(1);
            break;
    }
#endif /* CONFIG_RWNX_SDM */

    if (bl_hw->mod_params->nss < 1 || bl_hw->mod_params->nss > 2)
        bl_hw->mod_params->nss = 1;

    wiphy_info(wiphy, "PHY features: [NSS=%d][CHBW=%d]%s\n",
               bl_hw->mod_params->nss,
               20 * (1 << ((phy_feat & MDM_CHBW_MASK) >> MDM_CHBW_LSB)),
               bl_hw->mod_params->ldpc_on ? "[LDPC]" : "");

#define PRINT_RWNX_FEAT(feat)                                   \
    (sys_feat & BIT(MM_FEAT_##feat##_BIT) ? "["#feat"]" : "")

    wiphy_info(wiphy, "FW features: %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
               PRINT_RWNX_FEAT(BCN),
               PRINT_RWNX_FEAT(AUTOBCN),
               PRINT_RWNX_FEAT(HWSCAN),
               PRINT_RWNX_FEAT(CMON),
               PRINT_RWNX_FEAT(MROLE),
               PRINT_RWNX_FEAT(RADAR),
               PRINT_RWNX_FEAT(PS),
               PRINT_RWNX_FEAT(UAPSD),
               PRINT_RWNX_FEAT(DPSM),
               PRINT_RWNX_FEAT(AMPDU),
               PRINT_RWNX_FEAT(AMSDU),
               PRINT_RWNX_FEAT(CHNL_CTXT),
               PRINT_RWNX_FEAT(REORD),
               PRINT_RWNX_FEAT(P2P),
               PRINT_RWNX_FEAT(P2P_GO),
               PRINT_RWNX_FEAT(UMAC),
               PRINT_RWNX_FEAT(VHT),
               PRINT_RWNX_FEAT(BFMEE),
               PRINT_RWNX_FEAT(BFMER),
               PRINT_RWNX_FEAT(WAPI),
               PRINT_RWNX_FEAT(MFP),
               PRINT_RWNX_FEAT(MU_MIMO_RX),
               PRINT_RWNX_FEAT(MU_MIMO_TX),
               PRINT_RWNX_FEAT(MESH),
               PRINT_RWNX_FEAT(TDLS));
#undef PRINT_RWNX_FEAT

    return 0;
}
#endif


int bl_handle_dynparams(struct bl_hw *bl_hw)
{
    int nss;

    /* FULLMAC specific parameters */
    bl_hw->flags |= WIPHY_FLAG_REPORTS_OBSS;

    if (bl_hw->mod_params->tdls) {
        /* TDLS support */
        bl_hw->flags |= WIPHY_FLAG_SUPPORTS_TDLS;
        /* TDLS external setup support */
        bl_hw->flags |= WIPHY_FLAG_TDLS_EXTERNAL_SETUP;
    }

    if (bl_hw->mod_params->ap_uapsd_on)
        bl_hw->flags |= WIPHY_FLAG_AP_UAPSD;

    if (bl_hw->mod_params->phy_cfg < 0 || bl_hw->mod_params->phy_cfg > 5)
        bl_hw->mod_params->phy_cfg = 2;

    if (bl_hw->mod_params->mcs_map < 0 || bl_hw->mod_params->mcs_map > 2)
        bl_hw->mod_params->mcs_map = 0;

    nss = bl_hw->mod_params->nss;

    /* HT capabilities */
    bl_hw->ht_cap.cap |= 1 << IEEE80211_HT_CAP_RX_STBC_SHIFT;
    if (bl_hw->mod_params->ldpc_on)
        bl_hw->ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;
    if (bl_hw->mod_params->use_2040) {
        bl_hw->ht_cap.mcs.rx_mask[4] = 0x1; /* MCS32 */
        bl_hw->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
        bl_hw->ht_cap.mcs.rx_highest = cpu_to_le16(135 * nss);
    } else {
        bl_hw->ht_cap.mcs.rx_highest = cpu_to_le16(65 * nss);
        //Fixed leo disable MCS5/6/7
        bl_hw->ht_cap.mcs.rx_mask[0] = 0xFF;
    }
    if (nss > 1)
        bl_hw->ht_cap.cap |= IEEE80211_HT_CAP_TX_STBC;

    if (bl_hw->mod_params->sgi) {
        bl_hw->ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;
        if (bl_hw->mod_params->use_2040) {
            bl_hw->ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;
            bl_hw->ht_cap.mcs.rx_highest = cpu_to_le16(150 * nss);
        } else
            bl_hw->ht_cap.mcs.rx_highest = cpu_to_le16(72 * nss);
    }
    //disable green field leo+
    //bl_hw->ht_cap.cap |= IEEE80211_HT_CAP_GRN_FLD;
    //diable sm power leo+
    bl_hw->ht_cap.cap |= IEEE80211_HT_CAP_SM_PS;
    if (!bl_hw->mod_params->ht_on)
        bl_hw->ht_cap.ht_supported = false;

    if (bl_hw->mod_params->custregd) {
        printf("\n\n%s: CAUTION: USING PERMISSIVE CUSTOM REGULATORY RULES\n\n", __func__);
    }
    return 0;
}
