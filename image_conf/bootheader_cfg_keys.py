# -*- coding:utf-8 -*-

bootheader_cfg_keys = {
    "magic_code": {
        "offset": "0",
        "pos": "0",
        "bitlen": "32"
    },
    "revision": {
        "offset": "4",
        "pos": "0",
        "bitlen": "32"
    },

    #########################flash cfg#############################
    "flashcfg_magic_code": {
        "offset": "8",
        "pos": "0",
        "bitlen": "32"
    },
    "io_mode": {
        "offset": "12",
        "pos": "0",
        "bitlen": "8"
    },
    "cont_read_support": {
        "offset": "12",
        "pos": "8",
        "bitlen": "8"
    },
    "sfctrl_clk_delay": {
        "offset": "12",
        "pos": "16",
        "bitlen": "8"
    },
    "sfctrl_clk_invert": {
        "offset": "12",
        "pos": "24",
        "bitlen": "8"
    },
    "reset_en_cmd": {
        "offset": "16",
        "pos": "0",
        "bitlen": "8"
    },
    "reset_cmd": {
        "offset": "16",
        "pos": "8",
        "bitlen": "8"
    },
    "exit_contread_cmd": {
        "offset": "16",
        "pos": "16",
        "bitlen": "8"
    },
    "exit_contread_cmd_size": {
        "offset": "16",
        "pos": "24",
        "bitlen": "8"
    },
    "jedecid_cmd": {
        "offset": "20",
        "pos": "0",
        "bitlen": "8"
    },
    "jedecid_cmd_dmy_clk": {
        "offset": "20",
        "pos": "8",
        "bitlen": "8"
    },
    "qpi_jedecid_cmd": {
        "offset": "20",
        "pos": "16",
        "bitlen": "8"
    },
    "qpi_jedecid_dmy_clk": {
        "offset": "20",
        "pos": "24",
        "bitlen": "8"
    },
    "sector_size": {
        "offset": "24",
        "pos": "0",
        "bitlen": "8"
    },
    "mfg_id": {
        "offset": "24",
        "pos": "8",
        "bitlen": "8"
    },
    "page_size": {
        "offset": "24",
        "pos": "16",
        "bitlen": "16"
    },
    "chip_erase_cmd": {
        "offset": "28",
        "pos": "0",
        "bitlen": "8"
    },
    "sector_erase_cmd": {
        "offset": "28",
        "pos": "8",
        "bitlen": "8"
    },
    "blk32k_erase_cmd": {
        "offset": "28",
        "pos": "16",
        "bitlen": "8"
    },
    "blk64k_erase_cmd": {
        "offset": "28",
        "pos": "24",
        "bitlen": "8"
    },
    "write_enable_cmd": {
        "offset": "32",
        "pos": "0",
        "bitlen": "8"
    },
    "page_prog_cmd": {
        "offset": "32",
        "pos": "8",
        "bitlen": "8"
    },
    "qpage_prog_cmd": {
        "offset": "32",
        "pos": "16",
        "bitlen": "8"
    },
    "qual_page_prog_addr_mode": {
        "offset": "32",
        "pos": "24",
        "bitlen": "8"
    },
    "fast_read_cmd": {
        "offset": "36",
        "pos": "0",
        "bitlen": "8"
    },
    "fast_read_dmy_clk": {
        "offset": "36",
        "pos": "8",
        "bitlen": "8"
    },
    "qpi_fast_read_cmd": {
        "offset": "36",
        "pos": "16",
        "bitlen": "8"
    },
    "qpi_fast_read_dmy_clk": {
        "offset": "36",
        "pos": "24",
        "bitlen": "8"
    },
    "fast_read_do_cmd": {
        "offset": "40",
        "pos": "0",
        "bitlen": "8"
    },
    "fast_read_do_dmy_clk": {
        "offset": "40",
        "pos": "8",
        "bitlen": "8"
    },
    "fast_read_dio_cmd": {
        "offset": "40",
        "pos": "16",
        "bitlen": "8"
    },
    "fast_read_dio_dmy_clk": {
        "offset": "40",
        "pos": "24",
        "bitlen": "8"
    },
    "fast_read_qo_cmd": {
        "offset": "44",
        "pos": "0",
        "bitlen": "8"
    },
    "fast_read_qo_dmy_clk": {
        "offset": "44",
        "pos": "8",
        "bitlen": "8"
    },
    "fast_read_qio_cmd": {
        "offset": "44",
        "pos": "16",
        "bitlen": "8"
    },
    "fast_read_qio_dmy_clk": {
        "offset": "44",
        "pos": "24",
        "bitlen": "8"
    },
    "qpi_fast_read_qio_cmd": {
        "offset": "48",
        "pos": "0",
        "bitlen": "8"
    },
    "qpi_fast_read_qio_dmy_clk": {
        "offset": "48",
        "pos": "8",
        "bitlen": "8"
    },
    "qpi_page_prog_cmd": {
        "offset": "48",
        "pos": "16",
        "bitlen": "8"
    },
    "write_vreg_enable_cmd": {
        "offset": "48",
        "pos": "24",
        "bitlen": "8"
    },
    "wel_reg_index": {
        "offset": "52",
        "pos": "0",
        "bitlen": "8"
    },
    "qe_reg_index": {
        "offset": "52",
        "pos": "8",
        "bitlen": "8"
    },
    "busy_reg_index": {
        "offset": "52",
        "pos": "16",
        "bitlen": "8"
    },
    "wel_bit_pos": {
        "offset": "52",
        "pos": "24",
        "bitlen": "8"
    },
    "qe_bit_pos": {
        "offset": "56",
        "pos": "0",
        "bitlen": "8"
    },
    "busy_bit_pos": {
        "offset": "56",
        "pos": "8",
        "bitlen": "8"
    },
    "wel_reg_write_len": {
        "offset": "56",
        "pos": "16",
        "bitlen": "8"
    },
    "wel_reg_read_len": {
        "offset": "56",
        "pos": "24",
        "bitlen": "8"
    },
    "qe_reg_write_len": {
        "offset": "60",
        "pos": "0",
        "bitlen": "8"
    },
    "qe_reg_read_len": {
        "offset": "60",
        "pos": "8",
        "bitlen": "8"
    },
    "release_power_down": {
        "offset": "60",
        "pos": "16",
        "bitlen": "8"
    },
    "busy_reg_read_len": {
        "offset": "60",
        "pos": "24",
        "bitlen": "8"
    },
    "reg_read_cmd0": {
        "offset": "64",
        "pos": "0",
        "bitlen": "8"
    },
    "reg_read_cmd1": {
        "offset": "64",
        "pos": "8",
        "bitlen": "8"
    },
    "reg_write_cmd0": {
        "offset": "68",
        "pos": "0",
        "bitlen": "8"
    },
    "reg_write_cmd1": {
        "offset": "68",
        "pos": "8",
        "bitlen": "8"
    },
    "enter_qpi_cmd": {
        "offset": "72",
        "pos": "0",
        "bitlen": "8"
    },
    "exit_qpi_cmd": {
        "offset": "72",
        "pos": "8",
        "bitlen": "8"
    },
    "cont_read_code": {
        "offset": "72",
        "pos": "16",
        "bitlen": "8"
    },
    "cont_read_exit_code": {
        "offset": "72",
        "pos": "24",
        "bitlen": "8"
    },
    "burst_wrap_cmd": {
        "offset": "76",
        "pos": "0",
        "bitlen": "8"
    },
    "burst_wrap_dmy_clk": {
        "offset": "76",
        "pos": "8",
        "bitlen": "8"
    },
    "burst_wrap_data_mode": {
        "offset": "76",
        "pos": "16",
        "bitlen": "8"
    },
    "burst_wrap_code": {
        "offset": "76",
        "pos": "24",
        "bitlen": "8"
    },
    "de_burst_wrap_cmd": {
        "offset": "80",
        "pos": "0",
        "bitlen": "8"
    },
    "de_burst_wrap_cmd_dmy_clk": {
        "offset": "80",
        "pos": "8",
        "bitlen": "8"
    },
    "de_burst_wrap_code_mode": {
        "offset": "80",
        "pos": "16",
        "bitlen": "8"
    },
    "de_burst_wrap_code": {
        "offset": "80",
        "pos": "24",
        "bitlen": "8"
    },
    "sector_erase_time": {
        "offset": "84",
        "pos": "0",
        "bitlen": "16"
    },
    "blk32k_erase_time": {
        "offset": "84",
        "pos": "16",
        "bitlen": "16"
    },
    "blk64k_erase_time": {
        "offset": "88",
        "pos": "0",
        "bitlen": "16"
    },
    "page_prog_time": {
        "offset": "88",
        "pos": "16",
        "bitlen": "16"
    },
    "chip_erase_time": {
        "offset": "92",
        "pos": "0",
        "bitlen": "16"
    },
    "power_down_delay": {
        "offset": "92",
        "pos": "16",
        "bitlen": "8"
    },
    "qe_data": {
        "offset": "92",
        "pos": "24",
        "bitlen": "8"
    },
    "flashcfg_crc32": {
        "offset": "96",
        "pos": "0",
        "bitlen": "32"
    },

    #########################clk cfg#####################################
    "clkcfg_magic_code": {
        "offset": "100",
        "pos": "0",
        "bitlen": "32"
    },
    "xtal_type": {
        "offset": "104",
        "pos": "0",
        "bitlen": "8"
    },
    "pll_clk": {
        "offset": "104",
        "pos": "8",
        "bitlen": "8"
    },
    "hclk_div": {
        "offset": "104",
        "pos": "16",
        "bitlen": "8"
    },
    "bclk_div": {
        "offset": "104",
        "pos": "24",
        "bitlen": "8"
    },
    "flash_clk_type": {
        "offset": "108",
        "pos": "0",
        "bitlen": "8"
    },
    "flash_clk_div": {
        "offset": "108",
        "pos": "8",
        "bitlen": "8"
    },
    "clkcfg_crc32": {
        "offset": "112",
        "pos": "0",
        "bitlen": "32"
    },

    ########################bootcfg####################################
    "sign": {
        "offset": "116",
        "pos": "0",
        "bitlen": "2"
    },
    "encrypt_type": {
        "offset": "116",
        "pos": "2",
        "bitlen": "2"
    },
    "key_sel": {
        "offset": "116",
        "pos": "4",
        "bitlen": "2"
    },
    "no_segment": {
        "offset": "116",
        "pos": "8",
        "bitlen": "1"
    },
    "cache_enable": {
        "offset": "116",
        "pos": "9",
        "bitlen": "1"
    },
    "notload_in_bootrom": {
        "offset": "116",
        "pos": "10",
        "bitlen": "1"
    },
    "aes_region_lock": {
        "offset": "116",
        "pos": "11",
        "bitlen": "1"
    },
    "cache_way_disable": {
        "offset": "116",
        "pos": "12",
        "bitlen": "4"
    },
    "crc_ignore": {
        "offset": "116",
        "pos": "16",
        "bitlen": "1"
    },
    "hash_ignore": {
        "offset": "116",
        "pos": "17",
        "bitlen": "1"
    },

    # total image len or segment count
    "img_len": {
        "offset": "120",
        "pos": "0",
        "bitlen": "32"
    },
    "bootentry": {
        "offset": "124",
        "pos": "0",
        "bitlen": "32"
    },

    # img RAM address or flash offset
    "img_start": {
        "offset": "128",
        "pos": "0",
        "bitlen": "32"
    },

    # img hash
    "hash_0": {
        "offset": "132",
        "pos": "0",
        "bitlen": "32"
    },
    "hash_1": {
        "offset": "136",
        "pos": "0",
        "bitlen": "32"
    },
    "hash_2": {
        "offset": "140",
        "pos": "0",
        "bitlen": "32"
    },
    "hash_3": {
        "offset": "144",
        "pos": "0",
        "bitlen": "32"
    },
    "hash_4": {
        "offset": "148",
        "pos": "0",
        "bitlen": "32"
    },
    "hash_5": {
        "offset": "152",
        "pos": "0",
        "bitlen": "32"
    },
    "hash_6": {
        "offset": "156",
        "pos": "0",
        "bitlen": "32"
    },
    "hash_7": {
        "offset": "160",
        "pos": "0",
        "bitlen": "32"
    },

    # 164
    # 168
    "crc32": {
        "offset": "172",
        "pos": "0",
        "bitlen": "32"
    },
}
