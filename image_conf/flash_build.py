#! /usr/bin/env python3
# -*- coding:utf-8 -*-

import os
import sys
import fdt
import struct
import shutil
import binascii
import hashlib
import lzma
import toml
import itertools
import bootheader_cfg_keys as B_CFG_KEYS
import efuse_cfg_keys as E_CFG_KEYS
from configobj import ConfigObj
from Cryptodome.Hash import SHA256

app_path = ""
chip_name = ""

bl_factory_params_file_prefix = 'bl_factory_params_'
bin_build_out_path = "build_out"
default_conf_path = ""
efuse_mask_file = ""
efuse_file = ""

eflash_loader_cfg_org = ""
eflash_loader_cfg = ""

dict_xtal = {"24M": 1, "32M": "2", "38.4M": "3", "40M": "4", "26M": "5", "RC32M": "6"}


def bl_find_file_list(key_val, endswith):
    file_path_list = []
    conf_path = os.path.join(app_path, "img_conf")
    if os.path.exists(conf_path):
        files = os.listdir(conf_path)
        for f in files:
            if key_val in f and f.endswith(endswith):
                find_file = os.path.join(conf_path, f)
                file_path_list.append(find_file)
                # return find_file
    if file_path_list != []:
        return file_path_list
    conf_path = os.path.join(os.path.abspath('..'), "image_conf",  default_conf_path)
    files = os.listdir(conf_path)
    for f in files:
        if key_val in f and f.endswith(endswith):
            find_file = os.path.join(conf_path, f)
            file_path_list.append(find_file)
            # return find_file
    return file_path_list


def bl_find_file(key_val, endswith):
    conf_path = os.path.join(app_path, "img_conf")
    if os.path.exists(conf_path):
        files = os.listdir(conf_path)
        for f in files:
            if key_val in f and f.endswith(endswith):
                find_file = os.path.join(conf_path, f)
                return find_file
    conf_path = os.path.join(os.path.abspath('..'), "image_conf",  default_conf_path)
    files = os.listdir(conf_path)
    for f in files:
        if key_val in f and f.endswith(endswith):
            find_file = os.path.join(conf_path, f)
            return find_file

class bl_efuse_boothd_gen():

    def __init__(self):
        self.utils = bl_utils()

    def bootheader_update_flash_pll_crc(self, bootheader_data):
        flash_cfg_start = 8
        flash_cfg_len = 4 + 84 + 4
        # magic+......+CRC32
        flash_cfg = bootheader_data[flash_cfg_start + 4:flash_cfg_start + flash_cfg_len - 4]
        crcarray = self.utils.get_crc32_bytearray(flash_cfg)
        bootheader_data[flash_cfg_start + flash_cfg_len - 4:flash_cfg_start + flash_cfg_len] = crcarray
        pll_cfg_start = flash_cfg_start + flash_cfg_len
        pll_cfg_len = 4 + 8 + 4
        # magic+......+CRC32
        pll_cfg = bootheader_data[pll_cfg_start + 4:pll_cfg_start + pll_cfg_len - 4]
        crcarray = self.utils.get_crc32_bytearray(pll_cfg)
        bootheader_data[pll_cfg_start + pll_cfg_len - 4:pll_cfg_start + pll_cfg_len] = crcarray
        return bootheader_data


    def get_int_mask(self, pos, length):
        ones = "1" * 32
        zeros = "0" * 32
        mask = ones[0:32 - pos - length] + zeros[0:length] + ones[0:pos]
        return int(mask, 2)


    def update_data_from_cfg(self, config_keys, config_file, section):
        cfg = BFConfigParser()
        cfg.read(config_file)
        # get finally data len
        filelen = 0
        for key in config_keys:
            offset = int(config_keys.get(key)["offset"], 10)
            if offset > filelen:
                filelen = offset
        filelen += 4
        data = bytearray(filelen)
        data_mask = bytearray(filelen)
        for key in cfg.options(section):
            if config_keys.get(key) == None:
                print(key + " not exist")
                continue
            val = cfg.get(section, key)
            if val.startswith("0x"):
                val = int(val, 16)
            else:
                val = int(val, 10)
            offset = int(config_keys.get(key)["offset"], 10)
            pos = int(config_keys.get(key)["pos"], 10)
            bitlen = int(config_keys.get(key)["bitlen"], 10)

            oldval = self.utils.bytearray_to_int(self.utils.bytearray_reverse(data[offset:offset + 4]))
            oldval_mask = self.utils.bytearray_to_int(self.utils.bytearray_reverse(data_mask[offset:offset + 4]))
            newval = (oldval & self.get_int_mask(pos, bitlen)) + (val << pos)
            if val != 0:
                newval_mask = (oldval_mask | (~self.get_int_mask(pos, bitlen)))
            else:
                newval_mask = oldval_mask
            data[offset:offset + 4] = self.utils.int_to_4bytearray_l(newval)
            data_mask[offset:offset + 4] = self.utils.int_to_4bytearray_l(newval_mask)
        return data, data_mask


    def bootheader_create_do(self, chipname, chiptype, config_file, section, output_file=None, if_img=False):
        efuse_bootheader_path = os.path.join(app_path, bin_build_out_path)
        try:
            # sub_module = __import__("bootheader_cfg_keys", fromlist=[chiptype])
            bh_data, tmp = self.update_data_from_cfg(B_CFG_KEYS.bootheader_cfg_keys, config_file, section)
            # bh_data, tmp = self.update_data_from_cfg(sub_module.bootheader_cfg_keys, config_file, section)
            bh_data = self.bootheader_update_flash_pll_crc(bh_data)
            if output_file == None:
                fp = open(efuse_bootheader_path + "/" + section.lower().replace("_cfg", ".bin"), 'wb+')
            else:
                fp = open(output_file, 'wb+')
            if section == "BOOTHEADER_CFG" and chiptype == "bl60x":
                final_data = bytearray(8 * 1024)
                # add sp core feature
                # halt
                bh_data[118] = (bh_data[118] | (1 << 2))
                final_data[0:176] = bh_data
                final_data[4096 + 0:4096 + 176] = bh_data
                # change magic
                final_data[4096 + 2] = 65
                # change waydis to 0xf
                final_data[117] = (final_data[117] | (15 << 4))
                # change crc and hash ignore
                final_data[4096 + 118] = final_data[4096 + 118] | 0x03
                bh_data = final_data
            if if_img == True:
                # clear flash magic
                bh_data[8:12] = bytearray(4)
                # clear clock magic
                bh_data[100:104] = bytearray(4)
                fp.write(bh_data[0:176])
            else:
                fp.write(bh_data)
            fp.close()
            fp = open(efuse_bootheader_path + "/flash_para.bin", 'wb+')
            fp.write(bh_data[12:12 + 84])
            fp.close()
        except Exception as err:
            print("bootheader_create_do  fail!!")
            print(err)
            traceback.print_exc(limit=5, file=sys.stdout)

    def bootheader_create_process(self, chipname, chiptype, config_file, output_file1=None, output_file2=None, if_img=False):
        fp = open(config_file, 'r')
        data = fp.read()
        fp.close()
        if "BOOTHEADER_CFG" in data:
            self.bootheader_create_do(chipname, chiptype, config_file, "BOOTHEADER_CFG", output_file1, if_img)
        if "BOOTHEADER_CPU0_CFG" in data:
            self.bootheader_create_do(chipname, chiptype, config_file, "BOOTHEADER_CPU0_CFG", output_file1, if_img)
        if "BOOTHEADER_CPU1_CFG" in data:
            self.bootheader_create_do(chipname, chiptype, config_file, "BOOTHEADER_CPU1_CFG", output_file2, if_img)


    def efuse_create_process(self, chipname, chiptype, config_file, output_file=None):
        efuse_file = os.path.join(app_path, bin_build_out_path, "efusedata.bin")
        # sub_module = __import__("efuse_cfg_keys.py", fromlist=[chiptype])
        efuse_data, mask = self.update_data_from_cfg(E_CFG_KEYS.efuse_cfg_keys, config_file, "EFUSE_CFG")
        # efuse_data, mask = self.update_data_from_cfg(sub_module.efuse_cfg_keys, config_file, "EFUSE_CFG")
        if output_file == None:
            fp = open(efuse_file, 'wb+')
        else:
            fp = open(output_file, 'wb+')
        fp.write(efuse_data)
        fp.close()
        efuse_mask_file = os.path.join(app_path, bin_build_out_path, "efusedata_mask.bin")
        if output_file == None:
            fp = open(efuse_mask_file, 'wb+')
        else:
            fp = open(output_file.replace(".bin", "_mask.bin"), 'wb+')
        fp.write(mask)
        fp.close()

    def efuse_boothd_create_process(self, chipname, chiptype, config_file):
        self.bootheader_create_process(chipname, chiptype, config_file)
        self.efuse_create_process(chipname, chiptype, config_file)

class bl_utils():

    #12345678->0x12,0x34,0x56,0x78
    def hexstr_to_bytearray_b(self, hexstring):
        return bytearray.fromhex(hexstring)


    def hexstr_to_bytearray(self, hexstring):
        return bytearray.fromhex(hexstring)


    def hexstr_to_bytearray_l(self, hexstring):
        b = bytearray.fromhex(hexstring)
        b.reverse()
        return b


    def int_to_2bytearray_l(self, intvalue):
        return struct.pack("<H", intvalue)


    def int_to_2bytearray_b(self, intvalue):
        return struct.pack(">H", intvalue)


    def int_to_4bytearray_l(self, intvalue):
        src = bytearray(4)
        src[3] = ((intvalue >> 24) & 0xFF)
        src[2] = ((intvalue >> 16) & 0xFF)
        src[1] = ((intvalue >> 8) & 0xFF)
        src[0] = ((intvalue >> 0) & 0xFF)
        return src


    def int_to_4bytearray_b(self, intvalue):
        val = int_to_4bytearray_l(intvalue)
        val.reverse()
        return val


    def bytearray_reverse(self, a):
        l = len(a)
        b = bytearray(l)
        i = 0
        while i < l:
            b[i] = a[l - i - 1]
            i = i + 1
        return b


    def bytearray_to_int(self, b):
        return int(binascii.hexlify(b), 16)


    def string_to_bytearray(self, string):
        return bytes(string, encoding="utf8")


    def bytearray_to_str(self, bytesarray):
        return str(bytesarray)


    def get_random_hexstr(self, n_bytes):
        hextring = ""
        i = 0
        while i < n_bytes:
            hextring = hextring + str(binascii.hexlify(random.randint(0, 255)))
            i = i + 1
        return hextring


    def get_crc32_bytearray(self, data):
        crc = binascii.crc32(data)
        return self.int_to_4bytearray_l(crc)


    def copyfile(self, srcfile, dstfile):
        if os.path.isfile(srcfile):
            fpath, fname = os.path.split(dstfile)
            if not os.path.exists(fpath):
                os.makedirs(fpath)
            shutil.copyfile(srcfile, dstfile)
        else:
            print("Src file not exists")
            sys.exit()

    def enable_udp_send_log(self, server,local_echo):
        global udp_send_log,udp_socket_server,upd_log_local_echo
        udp_send_log=True
        upd_log_local_echo=local_echo
        udp_socket_server=server

    def add_udp_client(self, tid,upd_client):
        udp_clinet_dict[tid]=upd_client

    def remove_udp_client(self, tid):
        del udp_clinet_dict[tid]

    def Update_Cfg(self, cfg, section, key, value):
        if cfg.has_option(section, key):
            cfg.set(section, key, str(value))
        else:
            #print key," not found,adding it"
            cfg.set(section, key, str(value))


    def get_byte_array(self, str):
        return str.encode("utf-8")

#class BFConfigParser(configparser.ConfigParser):
#    def __init__(self, defaults=None):
#        configparser.ConfigParser.__init__(self, defaults=defaults)
#
#    def optionxform(self, optionstr):
#        return optionstr


class BFConfigParser():
    cfg_infile = None
    cfg_obj = ConfigObj()

    def __init__(self, file=None):
        self.cfg_infile = file
        self.cfg_obj = ConfigObj(self.cfg_infile)

    def read(self, file=None):
        self.cfg_infile = file
        self.cfg_obj = ConfigObj(self.cfg_infile, encoding='UTF8')
        return self.cfg_obj

    def get(self, section, key):
        ret = self.cfg_obj[section][key]
        if ret == "\"\"":
            return ""
        else:
            return ret

    def set(self, section, key, value):
        self.cfg_obj[section][key] = str(value)

    def sections(self,):
        return self.cfg_obj.keys()

    def delete_section(self, section):
        del self.cfg_obj[section]

    def update_section_name(self, oldsection, newsection):
        _sections = self.cfg_obj.keys()
        for _section in _sections:
            print(_section)
            if _section == oldsection:
                print(self.cfg_obj[_section])
                self.cfg_obj[newsection] = self.cfg_obj[oldsection]
        self.delete_section(oldsection)

    def options(self, section):
        return self.cfg_obj[section]

    def has_option(self, section, key):
        _sections = self.cfg_obj.keys()
        for _section in _sections:
            if _section == section:
                for _key in self.cfg_obj[_section]:
                    if _key == key:
                        return True
                    else:
                        continue
            else:
                continue
        return False

    def write(self, outfile=None, flag=None):
        if outfile == None:
            self.cfg_obj.filename = self.cfg_infile
        else:
            self.cfg_obj.filename = outfile
        self.cfg_obj.write()

class PtCreater(bl_utils):

    def __init__(self, config_file):
        #if not os.path.exists(config_file):
        #    config_file = os.path.join(default_conf_path, "partition_cfg_2M.toml")
        #config_file = bl_find_file("partition_cfg_", ".toml")
        self.parsed_toml = toml.load(config_file)
        self.entry_max = 16
        self.pt_new = False

    def __create_pt_table_do(self, lists, file):
        entry_table = bytearray(36 * self.entry_max)
        entry_cnt = 0
        for item in lists:
            entry_type = item["type"]
            entry_name = item["name"]
            entry_device = item["device"]
            entry_addr0 = item["address0"]
            entry_addr1 = item["address1"]
            entry_maxlen0 = item["size0"]
            entry_maxlen1 = item["size1"]
            entry_len = item["len"]

            entry_table[36 * entry_cnt + 0] = self.int_to_2bytearray_l(entry_type)[0]
            if len(entry_name) >= 8:
                print("Entry name is too long!")
                return False
            entry_table[36 * entry_cnt + 3:36 * entry_cnt + 3 + len(entry_name)] = bytearray(entry_name, "utf-8") + bytearray(0)
            entry_table[36 * entry_cnt + 12:36 * entry_cnt + 16] = self.int_to_4bytearray_l(entry_addr0)
            entry_table[36 * entry_cnt + 16:36 * entry_cnt + 20] = self.int_to_4bytearray_l(entry_addr1)
            entry_table[36 * entry_cnt + 20:36 * entry_cnt + 24] = self.int_to_4bytearray_l(entry_maxlen0)
            entry_table[36 * entry_cnt + 24:36 * entry_cnt + 28] = self.int_to_4bytearray_l(entry_maxlen1)
            entry_cnt += 1
        #partition table header
        #0x54504642
        pt_table = bytearray(16)
        pt_table[0] = 0x42
        pt_table[1] = 0x46
        pt_table[2] = 0x50
        pt_table[3] = 0x54
        pt_table[6:8] = self.int_to_2bytearray_l(int(entry_cnt))
        pt_table[12:16] = self.get_crc32_bytearray(pt_table[0:12])
        entry_table[36 * entry_cnt:36 * entry_cnt + 4] = self.get_crc32_bytearray(entry_table[0:36 * entry_cnt])
        data = pt_table + entry_table[0:36 * entry_cnt + 4]
        fp = open(file, 'wb+')
        fp.write(data)
        fp.close()
        return True

    def create_pt_table(self, file):
        self.pt_new = True
        return self.__create_pt_table_do(self.parsed_toml["pt_entry"], file)

    def get_pt_table_addr(self):
        addr0 = self.parsed_toml["pt_table"]["address0"]
        addr1 = self.parsed_toml["pt_table"]["address1"]
        return addr0, addr1

    def construct_table(self):
        parcel = {}
        if self.pt_new == True:
            parcel['pt_new'] = True
        else:
            parcel['pt_new'] = False
        parcel['pt_addr0'] = self.parsed_toml["pt_table"]["address0"]
        parcel['pt_addr1'] = self.parsed_toml["pt_table"]["address1"]
        for tbl_item in self.parsed_toml["pt_entry"]:
            if tbl_item['name'] == 'factory':
                parcel['conf_addr'] = tbl_item['address0']
            if tbl_item['name'] == 'FW_CPU0':
                parcel['fw_cpu0_addr'] = tbl_item['address0']
            if tbl_item['name'] == 'FW':
                parcel['fw_addr'] = tbl_item['address0']
            if tbl_item['name'] == 'media':
                parcel['media_addr'] = tbl_item['address0']
            if tbl_item['name'] == 'mfg':
                parcel['mfg_addr'] = tbl_item['address0']
        return parcel

class bl_img_create_do(bl_utils):

    def __init__(self):

        cfg = BFConfigParser()

        keyslot0 = 28
        keyslot1 = keyslot0 + 16
        keyslot2 = keyslot1 + 16
        keyslot3 = keyslot2 + 16
        keyslot4 = keyslot3 + 16
        keyslot5 = keyslot4 + 16
        keyslot6 = keyslot5 + 16

        wr_lock_key_slot_4_l = 13
        wr_lock_key_slot_5_l = 14
        wr_lock_boot_mode = 15
        wr_lock_dbg_pwd = 16
        wr_lock_sw_usage_0 = 17
        wr_lock_wifi_mac = 18
        wr_lock_key_slot_0 = 19
        wr_lock_key_slot_1 = 20
        wr_lock_key_slot_2 = 21
        wr_lock_key_slot_3 = 22
        wr_lock_key_slot_4_h = 23
        wr_lock_key_slot_5_h = 24
        rd_lock_dbg_pwd = 25
        rd_lock_key_slot_0 = 26
        rd_lock_key_slot_1 = 27
        rd_lock_key_slot_2 = 28
        rd_lock_key_slot_3 = 29
        rd_lock_key_slot_4 = 30
        rd_lock_key_slot_5 = 31

    #####################update efuse info##########################################
    def img_update_efuse(self, sign, pk_hash, flash_encryp_type, flash_key, sec_eng_key_sel, sec_eng_key):
        fp = open(cfg.get("Img_Cfg", "efuse_file"), 'rb')
        efuse_data = bytearray(fp.read()) + bytearray(0)
        fp.close()
        fp = open(cfg.get("Img_Cfg", "efuse_mask_file"), 'rb')
        efuse_mask_data = bytearray(fp.read()) + bytearray(0)
        fp.close()

        mask_4bytes = bytearray.fromhex("FFFFFFFF")

        efuse_data[0] |= flash_encryp_type
        efuse_data[0] |= (sign << 2)
        if flash_encryp_type > 0:
            efuse_data[0] |= 0x80
        efuse_mask_data[0] |= 0xff
        rw_lock = 0
        if pk_hash != None:
            efuse_data[keyslot0:keyslot2] = pk_hash
            efuse_mask_data[keyslot0:keyslot2] = mask_4bytes * 8
            rw_lock |= (1 << wr_lock_key_slot_0)
            rw_lock |= (1 << wr_lock_key_slot_1)
        if flash_key != None:
            if flash_encryp_type == 1:
                # aes 128
                efuse_data[keyslot2:keyslot4] = flash_key
                efuse_mask_data[keyslot2:keyslot4] = mask_4bytes * 8
            elif flash_encryp_type == 2:
                # aes 192
                efuse_data[keyslot2:keyslot4] = flash_key
                efuse_mask_data[keyslot2:keyslot4] = mask_4bytes * 8
            elif flash_encryp_type == 3:
                # aes 256
                efuse_data[keyslot2:keyslot4] = flash_key
                efuse_mask_data[keyslot2:keyslot4] = mask_4bytes * 8

            rw_lock |= (1 << wr_lock_key_slot_2)
            rw_lock |= (1 << wr_lock_key_slot_3)
            rw_lock |= (1 << rd_lock_key_slot_2)
            rw_lock |= (1 << rd_lock_key_slot_3)

        if sec_eng_key != None:
            if flash_encryp_type == 0:
                if sec_eng_key_sel == 0:
                    efuse_data[keyslot2:keyslot3] = sec_eng_key[16:32]
                    efuse_data[keyslot3:keyslot4] = sec_eng_key[0:16]
                    efuse_mask_data[keyslot2:keyslot4] = mask_4bytes * 8
                    rw_lock |= (1 << wr_lock_key_slot_2)
                    rw_lock |= (1 << wr_lock_key_slot_3)
                    rw_lock |= (1 << rd_lock_key_slot_2)
                    rw_lock |= (1 << rd_lock_key_slot_3)
                if sec_eng_key_sel == 1:
                    efuse_data[keyslot3:keyslot4] = sec_eng_key[16:32]
                    efuse_data[keyslot2:keyslot3] = sec_eng_key[0:16]
                    efuse_mask_data[keyslot2:keyslot4] = mask_4bytes * 8
                    rw_lock |= (1 << wr_lock_key_slot_2)
                    rw_lock |= (1 << wr_lock_key_slot_3)
                    rw_lock |= (1 << rd_lock_key_slot_2)
                    rw_lock |= (1 << rd_lock_key_slot_3)
            if flash_encryp_type == 1:
                if sec_eng_key_sel == 0:
                    efuse_data[keyslot4:keyslot5] = sec_eng_key[0:16]
                    efuse_mask_data[keyslot4:keyslot5] = mask_4bytes * 4
                    rw_lock |= (1 << wr_lock_key_slot_4_l)
                    rw_lock |= (1 << wr_lock_key_slot_4_h)
                    rw_lock |= (1 << rd_lock_key_slot_4)
                if sec_eng_key_sel == 1:
                    efuse_data[keyslot4:keyslot5] = sec_eng_key[0:16]
                    efuse_mask_data[keyslot4:keyslot5] = mask_4bytes * 4
                    rw_lock |= (1 << wr_lock_key_slot_4_l)
                    rw_lock |= (1 << wr_lock_key_slot_4_h)
                    rw_lock |= (1 << rd_lock_key_slot_4)
        # set read write lock key
        efuse_data[124:128] = self.int_to_4bytearray_l(rw_lock)
        efuse_mask_data[124:128] = self.int_to_4bytearray_l(rw_lock)
        fp = open(cfg.get("Img_Cfg", "efuse_file"), 'wb+')
        fp.write(efuse_data)
        fp.close()
        fp = open(cfg.get("Img_Cfg", "efuse_mask_file"), 'wb+')
        fp.write(efuse_mask_data)
        fp.close()


    ####################get sign and encrypt info##########################################


    def img_create_get_sign_encrypt_info(self, bootheader_data):
        sign = bootheader_data[116] & 0x3
        encrypt = ((bootheader_data[116] >> 2) & 0x3)
        key_sel = ((bootheader_data[116] >> 4) & 0x3)
        return sign, encrypt, key_sel


    ####################get hash ignore ignore##########################################


    def img_create_get_hash_ignore(self, bootheader_data):
        return (bootheader_data[118] >> 1) & 0x1


    ####################get crc ignore ignore##########################################


    def img_create_get_crc_ignore(self, bootheader_data):
        return bootheader_data[118] & 0x1


    #####################update boot header info##########################################


    def img_create_update_bootheader(self, bootheader_data, hash, seg_cnt):
        # update segment count
        bootheader_data[120:124] = self.int_to_4bytearray_l(seg_cnt)

        # update hash
        sign, encrypt, key_sel = self.img_create_get_sign_encrypt_info(bootheader_data)
        if self.img_create_get_hash_ignore(bootheader_data) == 1 and sign == 0:
            # do nothing
            pass
        else:
            bootheader_data[132:164] = hash

        # update header crc
        if self.img_create_get_crc_ignore(bootheader_data) == 1:
            # do nothing
            pass
        else:
            hd_crcarray = self.get_crc32_bytearray(bootheader_data[0:176 - 4])
            bootheader_data[176 - 4:176] = hd_crcarray
            print("Header crc: ", binascii.hexlify(hd_crcarray))
        return bootheader_data[0:176]


    #####################update segment header according segdata#########################


    def img_create_update_segheader(self, segheader, segdatalen, segdatacrc):
        segheader[4:8] = segdatalen
        segheader[8:12] = segdatacrc
        return segheader


    #####################do hash of image################################################


    def img_create_sha256_data(self, data_bytearray):
        hashfun = SHA256.new()
        hashfun.update(data_bytearray)
        return self.hexstr_to_bytearray(hashfun.hexdigest())


    #####################encrypt image, mainly segdata#####################################


    def img_create_encrypt_data(self, data_bytearray, key_bytearray, iv_bytearray, flash_img):
        if flash_img == 0:
            cryptor = AES.new(key_bytearray, AES.MODE_CBC, iv_bytearray)
            ciphertext = cryptor.encrypt(data_bytearray)
        else:
            #iv = Crypto.Util.Counter.new(128, initial_value = long(binascii.hexlify(iv_bytearray),16))
            iv = Counter.new(128, initial_value=int(binascii.hexlify(iv_bytearray), 16))
            cryptor = AES.new(key_bytearray, AES.MODE_CTR, counter=iv)
            ciphertext = cryptor.encrypt(data_bytearray)
        return ciphertext


    #####################sign image(hash code)#####################################


    def img_create_sign_data(self, data_bytearray, privatekey_file_uecc, publickey_file):
        sk = ecdsa.SigningKey.from_pem(open(privatekey_file_uecc).read())
        vk = ecdsa.VerifyingKey.from_pem(open(publickey_file).read())
        pk_data = vk.to_string()
        pk_hash = self.img_create_sha256_data(pk_data)

        signature = sk.sign(data_bytearray, hashfunc=hashlib.sha256, sigencode=ecdsa.util.sigencode_string)

        # return len+signature+crc
        len_array = self.int_to_4bytearray_l(len(signature))
        sig_field = len_array + signature
        crcarray = self.get_crc32_bytearray(sig_field)
        return pk_data, pk_hash, sig_field + crcarray


    ######################## read one file and append crc if needed#####################


    def img_create_read_file_append_crc(self, file, crc):
        fp = open(file, 'rb')
        read_data = bytearray(fp.read())
        crcarray = bytearray(0)
        if crc:
            crcarray = self.get_crc32_bytearray(read_data)
        fp.close()
        return read_data + crcarray


    def img_creat_process(self, flash_img):
        encrypt_blk_size = 16
        padding = bytearray(encrypt_blk_size)
        data_tohash = bytearray(0)
        ret = 'OK'
        cfg_section = "Img_Cfg"

        # get segdata to deal with
        segheader_file = []
        if flash_img == 0:
            for files in cfg.get(cfg_section, "segheader_file").split(" "):
                segheader_file.append(str(files))
        segdata_file = []
        for files in cfg.get(cfg_section, "segdata_file").split(" "):
            segdata_file.append(str(files))
            if flash_img == 1:
                break

        # get bootheader
        boot_header_file = cfg.get(cfg_section, "boot_header_file")
        bootheader_data = self.img_create_read_file_append_crc(boot_header_file, 0)
        # decide encrypt and sign
        encrypt = 0
        sign, encrypt, key_sel = self.img_create_get_sign_encrypt_info(bootheader_data)
        aesiv_data = bytearray(0)
        pk_data = bytearray(0)
        if sign != 0:
            publickey_file = cfg.get(cfg_section, "publickey_file")
            privatekey_file_uecc = cfg.get(cfg_section, "privatekey_file_uecc")

        if encrypt != 0:
            encrypt_key_org = self.hexstr_to_bytearray(cfg.get(cfg_section, "aes_key_org"))
            global encrypt_key
            if encrypt == 1:
                encrypt_key = encrypt_key_org[0:16]
            elif encrypt == 2:
                encrypt_key = encrypt_key_org[0:32]
            elif encrypt == 3:
                encrypt_key = encrypt_key_org[0:24]
            encrypt_iv = self.hexstr_to_bytearray(cfg.get(cfg_section, "aes_iv"))
            iv_crcarray = self.get_crc32_bytearray(encrypt_iv)
            aesiv_data = encrypt_iv + iv_crcarray
            data_tohash = data_tohash + aesiv_data

        # decide seg_cnt values
        seg_cnt = len(segheader_file)
        if flash_img == 0 and seg_cnt != len(segdata_file):
            print("Segheader count and segdata count not match")
            return "FAIL", data_tohash

        data_toencrypt = bytearray(0)
        if flash_img == 0:
            i = 0
            seg_header_list = []
            seg_data_list = []
            while i < seg_cnt:
                # read seg data and calculate crcdata
                seg_data = self.img_create_read_file_append_crc(segdata_file[i], 0)
                padding_size = 0
                if len(seg_data) % encrypt_blk_size != 0:
                    padding_size = encrypt_blk_size - \
                        len(seg_data) % encrypt_blk_size
                    seg_data += padding[0:padding_size]
                segdata_crcarray = self.get_crc32_bytearray(seg_data)
                seg_data_list.append(seg_data)

                # read seg header and replace segdata's CRC
                seg_header = self.img_create_read_file_append_crc(segheader_file[i], 0)
                seg_header = img_create_update_segheader(seg_header, self.int_to_4bytearray_l(len(seg_data)), segdata_crcarray)
                segheader_crcarray = self.get_crc32_bytearray(seg_header)
                seg_header = seg_header + segheader_crcarray
                seg_header_list.append(seg_header)
                i = i + 1

            # get all data to encrypt
            i = 0
            while i < seg_cnt:
                # ,now changed to encrypted since download tool's segdata len is from bootrom
                data_toencrypt += seg_header_list[i]
                data_toencrypt += seg_data_list[i]
                i += 1
        else:
            seg_data = self.img_create_read_file_append_crc(segdata_file[0], 0)
            padding_size = 0
            if len(seg_data) % encrypt_blk_size != 0:
                padding_size = encrypt_blk_size - len(seg_data) % encrypt_blk_size
                seg_data += padding[0:padding_size]
            data_toencrypt += seg_data
            seg_cnt = len(data_toencrypt)

        # do encrypt
        if encrypt != 0:
            data_toencrypt = img_create_encrypt_data(data_toencrypt, encrypt_key, encrypt_iv, flash_img)

        # get fw data
        fw_data = bytearray(0)
        data_tohash += data_toencrypt
        fw_data = data_toencrypt

        # hash fw img
        hash = self.img_create_sha256_data(data_tohash)
        # update boot header and recalculate crc
        bootheader_data = self.img_create_update_bootheader(bootheader_data, hash, seg_cnt)

        # add signautre
        signature = bytearray(0)
        pk_hash = None
        if sign == 1:
            pk_data, pk_hash, signature = img_create_sign_data(data_tohash, privatekey_file_uecc, publickey_file)
            pk_data = pk_data + self.get_crc32_bytearray(pk_data)

        # write whole image
        if flash_img == 1:
            bootinfo_file_name = cfg.get(cfg_section, "bootinfo_file")
            fp = open(bootinfo_file_name, 'wb+')
            bootinfo = bootheader_data + pk_data + signature + aesiv_data
            fp.write(bootinfo)
            fp.close()
            fw_file_name = cfg.get(cfg_section, "img_file")
            fp = open(fw_file_name, 'wb+')
            fp.write(fw_data)
            fp.close()
            # update efuse
            if encrypt != 0:
                if encrypt == 1:
                    # AES 128
                    img_update_efuse(sign, pk_hash, 1, encrypt_key + bytearray(32 - len(encrypt_key)), key_sel, None)
                if encrypt == 2:
                    # AES 256
                    img_update_efuse(sign, pk_hash, 3, encrypt_key + bytearray(32 - len(encrypt_key)), key_sel, None)
                if encrypt == 3:
                    # AES 192
                    img_update_efuse(sign, pk_hash, 2, encrypt_key + bytearray(32 - len(encrypt_key)), key_sel, None)
            else:
                self.img_update_efuse(sign, pk_hash, encrypt, None, key_sel, None)
        else:
            whole_img_file_name = cfg.get(cfg_section, "whole_img_file")
            fp = open(whole_img_file_name, 'wb+')
            img_data = bootheader_data + pk_data + signature + aesiv_data + fw_data
            fp.write(img_data)
            fp.close()
            # update efuse
            if encrypt != 0:
                if encrypt == 1:
                    # AES 128
                    img_update_efuse(sign, pk_hash, 1, None, key_sel, encrypt_key + bytearray(32 - len(encrypt_key)))
                if encrypt == 2:
                    # AES 256
                    img_update_efuse(sign, pk_hash, 3, None, key_sel, encrypt_key + bytearray(32 - len(encrypt_key)))
                if encrypt == 3:
                    # AES 192
                    img_update_efuse(sign, pk_hash, 2, None, key_sel, encrypt_key + bytearray(32 - len(encrypt_key)))
            else:
                img_update_efuse(sign, pk_hash, 0, None, key_sel, bytearray(32))
        return "OK", data_tohash


    def usage():
        print(sys.argv[0], "\n")
        print("-i/--img_type=  :image type:media or if")
        print("-h/--help       :helper")


    #######################################################################


    def img_create_do(self, options, img_dir_path=None, config_file=None):

        print("Image create path: ", img_dir_path)

        if config_file == None:
            config_file = img_dir_path + "/img_create_cfg.ini"
        cfg.read(config_file)
        print("Config file: ", config_file)

        img_type = "media"
        signer = "none"
        ret = "OK"
        data_tohash = bytearray(0)

        try:
            opts, args = getopt.getopt(options, 'i:s:Hh', ["img_type=", "signer=", "help"])
            for option, value in opts:
                if option in ["-h", "-H"]:
                    usage()
                if option in ["-i", "--img_type"]:
                    img_type = value
                if option in ["-s", "--signer"]:
                    signer = value
        except getopt.GetoptError as err:
            # will  something like "option -a not recognized")
            print(err)
            usage()


        if img_type == "media":
            flash_img = 1
        else:
            flash_img = 0

        # deal image creation
        ret, data_tohash = self.img_creat_process(flash_img)

        if ret != "OK":
            print("Fail to create images!")
            return

    def create_sp_media_image(self, config, cpu_type=None):
        global cfg
        cfg = BFConfigParser()
        cfg.read(config)
        self.img_creat_process(1)

class bl_img_create(bl_img_create_do):
    def img_create(self, options, chipname="bl60x", chiptype="bl60x", img_dir=None, config_file=None):
        img_dir_path = os.path.join(app_path, chipname, "img_create")
        if img_dir is None:
            self.img_create_do(options, img_dir_path, config_file)
        else:
            self.img_create_do(options, img_dir, config_file)

    def create_sp_media_image_file(self, config, chiptype="bl60x", cpu_type=None):
        self.create_sp_media_image(config, cpu_type)

class bl_device_tree():
    def bl_dts2dtb(self, src_addr="", dest_addr=""):
        if "" == src_addr or "" == dest_addr:
            print("bl_dts2dtb please check arg.")
            return
        with open(src_addr, "r") as f:
            tmp1_dts = f.read()

        tmp2_dtb = fdt.parse_dts(tmp1_dts)

        dest_addr = os.path.join(app_path, bin_build_out_path, dest_addr)
        with open(dest_addr, "wb") as f:
            f.write(tmp2_dtb.to_dtb(version=17))

    def bl_ro_params_device_tree(self, in_dts_config, out_bin_file):
        dts_config = in_dts_config
        bin_file = out_bin_file
        self.bl_dts2dtb(dts_config, bin_file)

class bl_whole_img_generate():
    def bl_create_flash_default_data(self, length):
        datas = bytearray(length)
        for i in range(length):
            datas[i] = 0xff
        return datas

    def bl_get_largest_addr(self, addrs, files):
        maxlen = 0
        datalen = 0
        for i in range(len(addrs)):
            if int(addrs[i], 16) > maxlen:
                maxlen = int(addrs[i], 16)
                datalen = os.path.getsize(files[i])
        return maxlen + datalen

    def bl_get_file_data(self, files):
        datas = []
        for file in files:
            with open(file, 'rb') as fp:
                data = fp.read()
            datas.append(data)
        return datas

    def bl_write_flash_img(self, d_addrs, d_files, flash_size):
        whole_img_len = self.bl_get_largest_addr(d_addrs, d_files)
        whole_img_data = self.bl_create_flash_default_data(whole_img_len)
        filedatas = self.bl_get_file_data(d_files)
        for i in range(len(d_addrs)):
            start_addr = int(d_addrs[i], 16)
            whole_img_data[start_addr:start_addr + len(filedatas[i])] = filedatas[i]
        # dst_file = os.path.join(app_path, bin_build_out_path, "whole_flash_data.bin")
        dst_file = os.path.join(app_path, bin_build_out_path, "whole_{}.bin".format(file_finally_name))
        fp = open(dst_file, 'wb+')
        fp.write(whole_img_data)
        print("Generating BIN File to %s" %(dst_file))
        fp.close()

    def bl_image_gen_cfg(self, raw_bin_name, bintype, key=None, iv=None, cfg_ini=None, cpu_type=None):
        cfg = BFConfigParser()
        if cfg_ini in [None, '']:
            f_org = bl_find_file("img_create_cfg", ".conf")
            f = os.path.join(app_path, bin_build_out_path, "img_create_cfg.ini")
            #if os.path.isfile(f) == False:
            shutil.copy(f_org, f)
        else:
            f = cfg_ini
        cfg.read(f)
        if bintype == "fw":
            if cpu_type == None:
                bootinfo_file = os.path.join(app_path, bin_build_out_path, "bootinfo.bin")
                img_file = os.path.join(app_path, bin_build_out_path, "img.bin")
            else:
                bootinfo_file = os.path.join(app_path, bin_build_out_path, "bootinfo_{0}.bin".format(cpu_type.lower()))
                img_file = os.path.join(app_path, bin_build_out_path, "img_{0}.bin".format(cpu_type.lower()))
        else:
            bootinfo_file = os.path.join(app_path, bin_build_out_path, "bootinfo_{0}.bin".format(bintype))
            img_file = os.path.join(app_path, bin_build_out_path, "img_{0}.bin".format(bintype))

        if cpu_type != None:
            img_section_name = "Img_" + cpu_type + "_Cfg"
        else:
            if "Img_CPU0_Cfg" in cfg.sections():
                img_section_name = "Img_CPU0_Cfg"
            else:
                img_section_name = "Img_Cfg"

        bh_file = os.path.join(app_path, bin_build_out_path, "bootheader.bin")
        efuse_file = os.path.join(app_path, bin_build_out_path, "efusedata.bin")
        efuse_mask_file = os.path.join(app_path, bin_build_out_path, "efusedata_mask.bin")
        cfg.set(img_section_name, 'boot_header_file', bh_file)
        cfg.set(img_section_name, 'efuse_file', efuse_file)
        cfg.set(img_section_name, 'efuse_mask_file', efuse_mask_file)
        cfg.set(img_section_name, 'segdata_file', raw_bin_name)
        cfg.set(img_section_name, 'bootinfo_file', bootinfo_file)
        cfg.set(img_section_name, 'img_file', img_file)
        if key:
            cfg.set(img_section_name, 'aes_key_org', key)
        if iv:
            cfg.set(img_section_name, 'aes_iv', iv)
        cfg.write(f, 'w')
        return f

    def bl_image_gen(self, bintype, raw_bin_name, key=None, iv=None, cfg_ini=None):
        # python bflb_img_create.py -c np -i media -s none
        f = self.bl_image_gen_cfg(raw_bin_name, bintype)
        #exe_genitor(['bflb_img_create.exe', '-c', 'np', '-i', 'media', '-s', 'none'])
        img_create = bl_img_create()
        img_create.create_sp_media_image_file(f)

    def bl_fw_boot_head_gen(self, boot2, xtal, config, encrypt=False, chipname="bl60x", chiptype="bl60x", cpu_type=None):
        cfg = BFConfigParser()
        cfg.read(config)

        if cpu_type != None:
            bootheader_section_name = "BOOTHEADER_" + cpu_type + "_CFG"
        else:
            if "BOOTHEADER_CPU0_CFG" in cfg.sections():
                bootheader_section_name = "BOOTHEADER_CPU0_CFG"
            else:
                bootheader_section_name = "BOOTHEADER_CFG"

        if boot2 == True:
            cfg.set(bootheader_section_name, 'img_start', '0x2000')
            cfg.set(bootheader_section_name, 'cache_enable', '1')
            cfg.set(bootheader_section_name, 'crc_ignore', '1')
            cfg.set(bootheader_section_name, 'hash_ignore', '1')
            #cfg.set(bootheader_section_name,'sfctrl_clk_delay', '0')
            if cpu_type != None:
                cfg.set(bootheader_section_name, 'halt_cpu1', '1')
            cfg.set(bootheader_section_name, 'key_sel', '0')

        if encrypt:
            cfg.set(bootheader_section_name, 'encrypt_type', '1')
        else:
            cfg.set(bootheader_section_name, 'encrypt_type', '0')

        cfg.set(bootheader_section_name, 'xtal_type', dict_xtal[xtal])

        cfg.write(config)
        create = bl_efuse_boothd_gen()
        create.efuse_boothd_create_process(chipname, chiptype, config)

    def bl_whole_flash_bin_create(self, bin_file, boot2, ro_params, pt_parcel, media, mfg, flash_opt="1M"):

        d_files = []
        d_addrs = []

        if pt_parcel == None:
            return False

        if boot2 == True:
            d_files.append(os.path.join(app_path, bin_build_out_path, "bootinfo_boot2.bin"))
            d_addrs.append("00000000")
            d_files.append(os.path.join(app_path, bin_build_out_path, "img_boot2.bin"))
            d_addrs.append("00002000")

        if pt_parcel != None and len(pt_parcel) > 0 and pt_parcel['pt_new'] == True:
            d_files.append(os.path.join(app_path, bin_build_out_path, "partition.bin"))
            d_addrs.append(hex(pt_parcel['pt_addr0'])[2:])
            d_files.append(os.path.join(app_path, bin_build_out_path, "partition.bin"))
            d_addrs.append(hex(pt_parcel['pt_addr1'])[2:])

        if bin_file == True and 'fw_addr' in pt_parcel:
            d_files.append(os.path.join(app_path, bin_build_out_path, "bootinfo.bin"))
            d_addrs.append(hex(pt_parcel['fw_addr'])[2:])
            d_files.append(os.path.join(app_path, bin_build_out_path, "img.bin"))
            d_addrs.append(hex(pt_parcel['fw_addr'] + 0x1000)[2:])

        if ro_params != None and len(ro_params) > 0 and pt_parcel['conf_addr'] != None:
            bl_ro_device_tree = bl_device_tree()
            dtb_file = os.path.join(app_path, bin_build_out_path, "ro_params.dtb")
            bl_ro_device_tree.bl_ro_params_device_tree(ro_params, dtb_file)
            d_files.append(os.path.join(app_path, bin_build_out_path, "ro_params.dtb"))
            d_addrs.append(hex(pt_parcel['conf_addr'])[2:])

        if media == True and pt_parcel['media_addr'] != None:
            d_files.append(os.path.join(app_path, bin_build_out_path, "media.bin"))
            d_addrs.append(hex(pt_parcel['media_addr'])[2:])

        if mfg == True:
            d_files.append(os.path.join(app_path, bin_build_out_path, "bootinfo_mfg.bin"))
            d_addrs.append(hex(pt_parcel['mfg_addr'])[2:])
            d_files.append(os.path.join(app_path, bin_build_out_path, "img_mfg.bin"))
            d_addrs.append(hex(pt_parcel['mfg_addr'] + 0x1000)[2:])

        if len(d_files) > 0 and len(d_addrs) > 0:
            cfg = BFConfigParser()
            cfg.read(eflash_loader_cfg)
            self.bl_write_flash_img(d_addrs, d_files, flash_opt)
            files_str = " ".join(d_files)
            addrs_str = " ".join(d_addrs)
            cfg.set('FLASH_CFG', 'file', files_str)
            cfg.set('FLASH_CFG', 'address', addrs_str)
            cfg.write(eflash_loader_cfg, 'w')
            return True
        else:
            return False

class bl_img_ota():
    def bl_mfg_ota_header(self, file_bytearray, use_xz):
        ota_conf = bl_find_file("ota", ".toml")
        parsed_toml = toml.load(ota_conf)
        header_len = 512
        header = bytearray()
        file_len = len(file_bytearray)
        m = hashlib.sha256()

        # 16 Bytes header
        data = b'BL60X_OTA_Ver1.0'
        for b in data:
            header.append(b)
        # 4 Byte ota file type
        if use_xz:
            data = b'XZ  '
        else:
            data = b'RAW '
        for b in data:
            header.append(b)

        # 4 Bytes file length
        file_len_bytes = file_len.to_bytes(4, byteorder='little')
        for b in file_len_bytes:
            header.append(b)

        # 8 Bytes pad
        header.append(0x01)
        header.append(0x02)
        header.append(0x03)
        header.append(0x04)
        header.append(0x05)
        header.append(0x06)
        header.append(0x07)
        header.append(0x08)

        # 16 Bytes Hardware version
        data = bytearray(parsed_toml["ota"]["version_hardware"].encode())
        data_len = 16 - len(data)
        for b in data:
            header.append(b)
        while data_len > 0:
            header.append(0x00)
            data_len = data_len - 1

        # 16 Bytes firmware version
        data = bytearray(parsed_toml["ota"]["version_software"].encode())
        data_len = 16 - len(data)
        for b in data:
            header.append(b)
        while data_len > 0:
            header.append(0x00)
            data_len = data_len - 1

        # 32 Bytes SHA256
        m.update(file_bytearray)
        hash_bytes = m.digest()
        for b in hash_bytes:
            header.append(b)
        header_len = header_len - len(header)
        while header_len > 0:
            header.append(0xFF)
            header_len = header_len - 1
        return header

    def bl_mfg_ota_xz_gen(self, chipname="bl60x", chiptype="bl60x", cpu_type=None):
        bl60x_xz_filters = [
            {
                "id": lzma.FILTER_LZMA2,
                "dict_size": 32768
            },
        ]

        fw_ota_bin = bytearray()
        fw_ota_bin_xz = bytearray()
        if cpu_type == None:
            FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota/{}/FW_OTA.bin".format(file_finally_name))
        else:
            FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota/{}/".format(file_finally_name) + cpu_type + "_OTA.bin")
        with open(FW_OTA_path, mode="rb") as bin_f:
            file_bytes = bin_f.read()
            for b in file_bytes:
                fw_ota_bin.append(b)
        if cpu_type == None:
            FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota/{}/FW_OTA.bin.xz".format(file_finally_name))
        else:
            FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota/{}/".format(file_finally_name) + cpu_type + "_OTA.bin.xz")
        with lzma.open(FW_OTA_path, mode="wb", check=lzma.CHECK_CRC32, filters=bl60x_xz_filters) as xz_f:
            xz_f.write(fw_ota_bin)
        print("Generating BIN File to %s" %(FW_OTA_path))
        with open(FW_OTA_path, mode="rb") as f:
            file_bytes = f.read()
            for b in file_bytes:
                fw_ota_bin_xz.append(b)
        fw_ota_bin_xz_ota = self.bl_mfg_ota_header(fw_ota_bin_xz, use_xz=1)
        for b in fw_ota_bin_xz:
            fw_ota_bin_xz_ota.append(b)
        if cpu_type == None:
            FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota/{}/FW_OTA.bin.xz.ota".format(file_finally_name))
        else:
            FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota/{}/".format(file_finally_name) + cpu_type + "_OTA.bin.xz.ota")
        with open(FW_OTA_path, mode="wb") as f:
            f.write(fw_ota_bin_xz_ota)
        print("Generating BIN File to %s" %(FW_OTA_path))


    def bl_mfg_ota_bin_gen(self, chipname="bl60x", chiptype="bl60x", cpu_type=None):
        fw_header_len = 4096
        fw_ota_bin = bytearray()

        ota_path = os.path.join(app_path, bin_build_out_path)
        if os.path.isdir(ota_path)==False:
            os.mkdir(ota_path)

        if cpu_type == None:
            bootinfo_fw_path = os.path.join(app_path, bin_build_out_path, "bootinfo.bin")
        else:
            bootinfo_fw_path = os.path.join(app_path, bin_build_out_path, "bootinfo_" + cpu_type.lower() + ".bin")
        with open(bootinfo_fw_path, mode="rb") as f:
            file_bytes = f.read(4096)
            for b in file_bytes:
                fw_ota_bin.append(b)
        i = fw_header_len - len(fw_ota_bin)
        while i > 0:
            fw_ota_bin.append(0xFF)
            i = i - 1
        if cpu_type == None:
            img_fw_path = os.path.join(app_path, bin_build_out_path, "img.bin")
        else:
            img_fw_path = os.path.join(app_path, bin_build_out_path, "img_" + cpu_type.lower() + ".bin")
        with open(img_fw_path, mode="rb") as f:
            file_bytes = f.read()
            for b in file_bytes:
                fw_ota_bin.append(b)
        fw_ota_bin_header = self.bl_mfg_ota_header(fw_ota_bin, use_xz=0)

        FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota")
        if not os.path.exists(FW_OTA_path):
            os.makedirs(FW_OTA_path)
        FW_OTA_path = os.path.join(FW_OTA_path, file_finally_name)
        if not os.path.exists(FW_OTA_path):
            os.makedirs(FW_OTA_path)
        if cpu_type == None:
            FW_OTA_path = os.path.join(FW_OTA_path, "FW_OTA.bin")
        else:
            FW_OTA_path = os.path.join(FW_OTA_path, cpu_type + "_OTA.bin")
        with open(FW_OTA_path, mode="wb") as f:
            f.write(fw_ota_bin)
        print("Generating BIN File to %s" %(FW_OTA_path))
        for b in fw_ota_bin:
            fw_ota_bin_header.append(b)
        if cpu_type == None:
            FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota/{}/FW_OTA.bin.ota".format(file_finally_name))
        else:
            FW_OTA_path = os.path.join(app_path, bin_build_out_path, "ota/{}/".format(file_finally_name) + cpu_type + "_OTA.bin.ota")
        with open(FW_OTA_path, mode="wb") as f:
            f.write(fw_ota_bin_header)
        print("Generating BIN File to %s" %(FW_OTA_path))
        self.bl_mfg_ota_xz_gen(chipname, chiptype, cpu_type)

class bl_flash_select():
    def get_suitable_file_name(self, cfg_dir, flash_id):
        conf_files = []
        for home, dirs, files in os.walk(cfg_dir):
            for filename in files:
                if filename.split('_')[-1] == flash_id + '.conf':
                    conf_files.append(filename)

        if len(conf_files) > 1:
            for i in range(len(conf_files)):
                tmp = conf_files[i].split('.')[0]
                print("%d:%s" % (i + 1, tmp))
            return conf_files[i]
        elif len(conf_files) == 1:
            return conf_files[0]
        else:
            return ""

    def update_flash_cfg_do(self, chipname, chiptype, flash_id, file=None, create=False, section=None):
        cfg_dir = os.path.join(os.getcwd(), chiptype, "flash_select")
        conf_name = self.get_suitable_file_name(cfg_dir, flash_id)
        print(os.path.join(cfg_dir, conf_name))
        value_key = []
        if os.path.isfile(os.path.join(cfg_dir, conf_name)) == False:
            return False
        fp = open(os.path.join(cfg_dir, conf_name), 'r')
        for line in fp.readlines():
            value = line.split("=")[0].strip()
            if value == "[FLASH_CFG]":
                continue
            value_key.append(value)

        cfg1 = BFConfigParser()
        cfg1.read(os.path.join(cfg_dir, conf_name))
        cfg2 = BFConfigParser()
        cfg2.read(file)
        for i in range(len(value_key)):
            if cfg1.has_option("FLASH_CFG", value_key[i]) and cfg2.has_option(section, value_key[i]) :
                tmp_value = cfg1.get("FLASH_CFG", value_key[i])
                bflb_utils = bl_utils()
                bflb_utils.Update_Cfg(cfg2, section, value_key[i], tmp_value)

        cfg2.write(file, "w+")

    def bl_flash_loader_list(self, chipname, chiptype, bh_cfg_file):
        eflash_loader_cfg = os.path.join(app_path, bin_build_out_path, "eflash_loader_cfg.ini")
        cfg = BFConfigParser()
        cfg.read(eflash_loader_cfg)

        if cfg.has_option("FLASH_CFG", "flash_id"):
            flash_id_str = cfg.get("FLASH_CFG", "flash_id")
            if type(flash_id_str) is str:
                flash_id_list = flash_id_str.split(',')
                return flash_id_list
            elif type(flash_id_str) is list:
                return flash_id_str
            # for flash_id in flash_id_list:
            #     print("========= chip flash id: %s =========" % flash_id)
            #     if chiptype == "bl602":
            #         if self.update_flash_cfg_do(chipname, chiptype, flash_id, bh_cfg_file, False, "BOOTHEADER_CFG") == False:
            #             error = "flash_id:" + flash_id + " do not support"
            #             return error
            #     elif chiptype == "bl60x":
            #         if self.update_flash_cfg_do(chipname, chiptype, flash_id, bh_cfg_file, False, "BOOTHEADER_CPU0_CFG") == False:
            #             error = "flash_id:" + flash_id + " do not support"
            #             return error
        else:
            error = "Do not find flash_id in eflash_loader_cfg.ini"
            return error

    def bl_flash_update(self, chipname, chiptype, bh_cfg_file, flash_id):
        print("========= chip flash id: %s =========" % flash_id)
        if chiptype == "bl602":
            if self.update_flash_cfg_do(chipname, chiptype, flash_id, bh_cfg_file, False, "BOOTHEADER_CFG") == False:
                error = "flash_id:" + flash_id + " do not support"
                return error
        elif chiptype == "bl60x":
            if self.update_flash_cfg_do(chipname, chiptype, flash_id, bh_cfg_file, False,
                                        "BOOTHEADER_CPU0_CFG") == False:
                error = "flash_id:" + flash_id + " do not support"
                return error

    def bl_flash_loader(self, chipname, chiptype, bh_cfg_file):
        eflash_loader_cfg = os.path.join(app_path, bin_build_out_path, "eflash_loader_cfg.ini")
        cfg = BFConfigParser()
        cfg.read(eflash_loader_cfg)
        if cfg.has_option("FLASH_CFG", "flash_id"):
            flash_id_str = cfg.get("FLASH_CFG", "flash_id")
            flash_id_list = flash_id_str.split(',')
            print('++++++++')
            print(flash_id_list, type(flash_id_list))
            for flash_id in flash_id_list:
                print(flash_id)
                print("========= chip flash id: %s =========" % flash_id)
                if chiptype == "bl602":
                    if self.update_flash_cfg_do(chipname, chiptype, flash_id, bh_cfg_file, False, "BOOTHEADER_CFG") == False:
                        error = "flash_id:" +  flash_id + " do not support"
                        return error
                elif chiptype == "bl60x":
                    if self.update_flash_cfg_do(chipname, chiptype, flash_id, bh_cfg_file, False, "BOOTHEADER_CPU0_CFG") == False:
                        error = "flash_id:" +  flash_id + " do not support"
                        return error
        else:
            error = "Do not find flash_id in eflash_loader_cfg.ini"
            return error

if __name__ == '__main__':
    abs_path = os.path.abspath('..')
    app_path = os.path.join(abs_path, "customer_app", sys.argv[1])
    demo_name = sys.argv[1]
    chip_name = sys.argv[2].lower()
    default_conf_path = chip_name
    eflash_loader_cfg_org = bl_find_file("eflash_loader_cfg", ".conf")
    eflash_loader_cfg = os.path.join(app_path, bin_build_out_path, "eflash_loader_cfg.ini")
    shutil.copy(eflash_loader_cfg_org, eflash_loader_cfg)

    # 找到efuse_bootheader_cfg
    f_org = bl_find_file("efuse_bootheader_cfg", ".conf")
    f = os.path.join(app_path, bin_build_out_path, "efuse_bootheader_cfg.ini")
    # if os.path.isfile(f) == False:
    shutil.copy(f_org, f)
    # 选择flash型号
    flash_sele = bl_flash_select()

    flashid_list = flash_sele.bl_flash_loader_list(chip_name, chip_name, f)

    pt_file_list = bl_find_file_list("partition_cfg_", ".toml")
    ro_list = bl_find_file_list(bl_factory_params_file_prefix, ".dts")
    img_boot2_file_list = bl_find_file_list("blsp_boot2_", ".bin")

    arrange_group_list = list(itertools.product(pt_file_list, ro_list, img_boot2_file_list, flashid_list))

    for group in arrange_group_list:
        # 找到partition
        # pt_file = bl_find_file("partition_cfg_", ".toml")
        pt_file = group[0]
        pt_name = pt_file.split("partition_cfg_")
        pt_name = pt_name[1].split('.toml')
        pt_name = 'pt{}'.format(pt_name[0])

        pt_helper = PtCreater(pt_file)
        pt_helper.create_pt_table(os.path.join(app_path, bin_build_out_path, "partition.bin"))
        pt_parcel = pt_helper.construct_table()

        # flashid
        flash_sele.bl_flash_update(chip_name, chip_name, f, group[3])
        flash_id_name = group[3]

        #找到device_tree
        # ro = bl_find_file(bl_factory_params_file_prefix, ".dts")
        ro = group[1]
        xtal = ro.split("IoTKitA_")
        xtal = xtal[1].split(".dts")
        xtal = xtal[0]
        dts_name = 'dts{}'.format(xtal)

        img_gen = bl_whole_img_generate()
        img_gen.bl_fw_boot_head_gen(True, xtal, f, False, chip_name, chip_name)

        #找到boot2
        # img_boot2_file = bl_find_file("blsp_boot2_", ".bin")
        img_boot2_file = group[2]
        boot2_name = img_boot2_file.split("blsp_boot2_")
        boot2_name = boot2_name[1].split('.bin')
        boot2_name = 'boot2{}'.format(boot2_name[0])

        file_finally_name = '{}_{}_{}_{}'.format(dts_name, pt_name, boot2_name, flash_id_name)

        img_gen.bl_image_gen("boot2", img_boot2_file)

        img_gen.bl_fw_boot_head_gen(False, xtal, f, False, chip_name, chip_name)
        img_gen.bl_image_gen("fw", os.path.join(app_path, "build_out", demo_name + ".bin"))
        img_ota = bl_img_ota()
        img_ota.bl_mfg_ota_bin_gen(chip_name, chip_name, None)
        img_gen.bl_whole_flash_bin_create(True, True, ro, pt_parcel, None, None, "2M")

