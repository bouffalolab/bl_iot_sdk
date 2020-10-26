# -*- coding:utf-8 -*-

efuse_cfg_keys = {
    "ef_sf_aes_mode": {
        "offset": "0",
        "pos": "0",
        "bitlen": "2"
    },
    "ef_sboot_sign_mode": {
        "offset": "0",
        "pos": "2",
        "bitlen": "2"
    },
    "ef_sboot_en": {
        "offset": "0",
        "pos": "4",
        "bitlen": "2"
    },
    "ef_cpu_enc_en": {
        "offset": "0",
        "pos": "7",
        "bitlen": "1"
    },
    "trim_enable": {
        "offset": "0",
        "pos": "12",
        "bitlen": "1"
    },
    "ef_sw_usage_1": {
        "offset": "0",
        "pos": "13",
        "bitlen": "1"
    },
    "ef_sdu_dis": {
        "offset": "0",
        "pos": "14",
        "bitlen": "1"
    },
    "ef_ble_dis": {
        "offset": "0",
        "pos": "15",
        "bitlen": "1"
    },
    "ef_wifi_dis": {
        "offset": "0",
        "pos": "16",
        "bitlen": "1"
    },
    "ef_0_key_enc_en": {
        "offset": "0",
        "pos": "17",
        "bitlen": "1"
    },
    "ef_sf_dis": {
        "offset": "0",
        "pos": "19",
        "bitlen": "1"
    },
    "ef_cpu_rst_dbg_dis": {
        "offset": "0",
        "pos": "21",
        "bitlen": "1"
    },
    "ef_se_dbg_dis": {
        "offset": "0",
        "pos": "22",
        "bitlen": "1"
    },
    "ef_efuse_dbg_dis": {
        "offset": "0",
        "pos": "23",
        "bitlen": "1"
    },
    "ef_dbg_jtag_dis": {
        "offset": "0",
        "pos": "26",
        "bitlen": "2"
    },
    "ef_dbg_mode": {
        "offset": "0",
        "pos": "28",
        "bitlen": "4"
    },
    "ef_dbg_pwd_low": {
        "offset": "4",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_dbg_pwd_high": {
        "offset": "8",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_ana_trim_0": {
        "offset": "12",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_sw_usage_0": {
        "offset": "16",
        "pos": "0",
        "bitlen": "32"
    },
    ###################################################################
    "bootrom_protect": {
        "offset": "16",
        "pos": "0",
        "bitlen": "1"
    },
    "uart_log_disable": {
        "offset": "16",
        "pos": "1",
        "bitlen": "1"
    },
    "sdio_pin_init": {
        "offset": "16",
        "pos": "2",
        "bitlen": "1"
    },
    "disable_cci_coexist": {
        "offset": "16",
        "pos": "3",
        "bitlen": "1"
    },
    "xtal_type": {
        "offset": "16",
        "pos": "4",
        "bitlen": "3"
    },
    "pll_clk": {
        "offset": "16",
        "pos": "7",
        "bitlen": "3"
    },
    "hclk_div": {
        "offset": "16",
        "pos": "10",
        "bitlen": "1"
    },
    "bclk_div": {
        "offset": "16",
        "pos": "11",
        "bitlen": "1"
    },
    "flash_clk_type": {
        "offset": "16",
        "pos": "12",
        "bitlen": "3"
    },
    "flash_clk_div": {
        "offset": "16",
        "pos": "15",
        "bitlen": "1"
    },
    "flash_cfg": {
        "offset": "16",
        "pos": "16",
        "bitlen": "2"
    },
    "flash_pwr_delay": {
        "offset": "16",
        "pos": "18",
        "bitlen": "2"
    },
    "tz_boot": {
        "offset": "16",
        "pos": "20",
        "bitlen": "1"
    },
    "encrypted_tz_boot": {
        "offset": "16",
        "pos": "21",
        "bitlen": "1"
    },
    "hbn_check_sign": {
        "offset": "16",
        "pos": "22",
        "bitlen": "1"
    },
    "keep_dbg_port_closed": {
        "offset": "16",
        "pos": "23",
        "bitlen": "1"
    },
    "mediaboot_disable": {
        "offset": "16",
        "pos": "24",
        "bitlen": "1"
    },
    "uartboot_disable": {
        "offset": "16",
        "pos": "25",
        "bitlen": "1"
    },
    "sdioboot_disable": {
        "offset": "16",
        "pos": "26",
        "bitlen": "1"
    },
    "hbn_jump_disable": {
        "offset": "16",
        "pos": "27",
        "bitlen": "1"
    },
    "jtag_switch": {
        "offset": "16",
        "pos": "28",
        "bitlen": "1"
    },
    "jtag_init": {
        "offset": "16",
        "pos": "29",
        "bitlen": "1"
    },
    "qfn40": {
        "offset": "16",
        "pos": "30",
        "bitlen": "1"
    },
    "debug_log_reopen": {
        "offset": "16",
        "pos": "31",
        "bitlen": "1"
    },
    ############################################## ###########################
    "ef_wifi_mac_low": {
        "offset": "20",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_wifi_mac_high": {
        "offset": "24",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_0_w0": {
        "offset": "28",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_0_w1": {
        "offset": "32",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_0_w2": {
        "offset": "36",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_0_w3": {
        "offset": "40",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_1_w0": {
        "offset": "44",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_1_w1": {
        "offset": "48",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_1_w2": {
        "offset": "52",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_1_w3": {
        "offset": "56",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_2_w0": {
        "offset": "60",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_2_w1": {
        "offset": "64",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_2_w2": {
        "offset": "68",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_2_w3": {
        "offset": "72",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_3_w0": {
        "offset": "76",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_3_w1": {
        "offset": "80",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_3_w2": {
        "offset": "84",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_3_w3": {
        "offset": "88",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_4_w0": {
        "offset": "92",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_4_w1": {
        "offset": "96",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_4_w2": {
        "offset": "100",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_4_w3": {
        "offset": "104",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_5_w0": {
        "offset": "108",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_5_w1": {
        "offset": "112",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_5_w2": {
        "offset": "116",
        "pos": "0",
        "bitlen": "32"
    },
    "ef_key_slot_5_w3": {
        "offset": "120",
        "pos": "0",
        "bitlen": "32"
    },
    "wr_lock_key_slot_4_l": {
        "offset": "124",
        "pos": "13",
        "bitlen": "1"
    },
    "wr_lock_key_slot_5_l": {
        "offset": "124",
        "pos": "14",
        "bitlen": "1"
    },
    "wr_lock_boot_mode": {
        "offset": "124",
        "pos": "15",
        "bitlen": "1"
    },
    "wr_lock_dbg_pwd": {
        "offset": "124",
        "pos": "16",
        "bitlen": "1"
    },
    "wr_lock_sw_usage_0": {
        "offset": "124",
        "pos": "17",
        "bitlen": "1"
    },
    "wr_lock_wifi_mac": {
        "offset": "124",
        "pos": "18",
        "bitlen": "1"
    },
    "wr_lock_key_slot_0": {
        "offset": "124",
        "pos": "19",
        "bitlen": "1"
    },
    "wr_lock_key_slot_1": {
        "offset": "124",
        "pos": "20",
        "bitlen": "1"
    },
    "wr_lock_key_slot_2": {
        "offset": "124",
        "pos": "21",
        "bitlen": "1"
    },
    "wr_lock_key_slot_3": {
        "offset": "124",
        "pos": "22",
        "bitlen": "1"
    },
    "wr_lock_key_slot_4_h": {
        "offset": "124",
        "pos": "23",
        "bitlen": "1"
    },
    "wr_lock_key_slot_5_h": {
        "offset": "124",
        "pos": "24",
        "bitlen": "1"
    },
    "rd_lock_dbg_pwd": {
        "offset": "124",
        "pos": "25",
        "bitlen": "1"
    },
    "rd_lock_key_slot_0": {
        "offset": "124",
        "pos": "26",
        "bitlen": "1"
    },
    "rd_lock_key_slot_1": {
        "offset": "124",
        "pos": "27",
        "bitlen": "1"
    },
    "rd_lock_key_slot_2": {
        "offset": "124",
        "pos": "28",
        "bitlen": "1"
    },
    "rd_lock_key_slot_3": {
        "offset": "124",
        "pos": "29",
        "bitlen": "1"
    },
    "rd_lock_key_slot_4": {
        "offset": "124",
        "pos": "30",
        "bitlen": "1"
    },
    "rd_lock_key_slot_5": {
        "offset": "124",
        "pos": "31",
        "bitlen": "1"
    },
}
