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
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "bl_boot2.h"
#include "bl_flash.h"
#include "hal_boot2.h"
#include <blog.h>

#define USER_UNUSED(a) ((void)(a))

#define PARTITION_BOOT2_RAM_ADDR_ACTIVE (0x62047e00)
#define PARTITION_MAGIC                 (0x54504642)
#define PARTITION_FW_PART_NAME          "FW"
#define PARTITION_FW_PART_HEADER_SIZE   (0x1000)
//TODO use header file from project
#define FW_XIP_ADDRESS                  (0x58000000)

static struct {
    uint8_t partition_active_idx;
    uint8_t pad[3];
    pt_table_stuff_config table;
} boot2_partition_table;//XXX Dont change the name of varaible, since we refer this boot2_partition_table in linker script

void hal_boot2_set_ptable_opt(HALpPtTable_Flash_Erase erase, HALpPtTable_Flash_Write write, HALpPtTable_Flash_Read read)
{
    pt_table_set_flash_operation((p_pt_table_flash_erase)erase, (p_pt_table_flash_write)write, (p_pt_table_flash_read)read);
}

int hal_boot2_update_ptable(HALPartition_Entry_Config *ptEntry_hal)
{
    int ret;
    //FIXME force covert
    pt_table_entry_config *ptEntry = (pt_table_entry_config*)ptEntry_hal;

    ptEntry->active_index = !ptEntry->active_index;
    (ptEntry->age)++;
    ret = pt_table_update_entry(!boot2_partition_table.partition_active_idx, &boot2_partition_table.table, ptEntry);
    return ret;
}

static void _dump_partition(void)
{
    int i;
    pt_table_stuff_config *part = &boot2_partition_table.table;

    USER_UNUSED(i);
    USER_UNUSED(part);

    blog_info("======= PtTable_Config @%p=======\r\n", part);
    blog_info("magicCode 0x%08X;", (unsigned int)(part->pt_table.magicCode));
    blog_info_raw(" version 0x%04X;", part->pt_table.version);
    blog_info_raw(" entryCnt %u;", part->pt_table.entryCnt);
    blog_info_raw(" age %lu;", part->pt_table.age);
    blog_info_raw(" crc32 0x%08X\r\n", (unsigned int)part->pt_table.crc32);

    blog_info("idx  type device active_index     name   Address[0]  Address[1]  Length[0]   Length[1]   age\r\n");
    for (i = 0; i < part->pt_table.entryCnt; i++) {
        blog_info("[%02d] ", i);
        blog_info_raw(" %02u", part->pt_entries[i].type);
        blog_info_raw("     %u", part->pt_entries[i].device);
        blog_info_raw("         %u", part->pt_entries[i].active_index);
        blog_info_raw("     %8s", part->pt_entries[i].name);
        blog_info_raw("  0x%08lx", (part->pt_entries[i].start_address[0]));
        blog_info_raw("  0x%08lx", (part->pt_entries[i].start_address[1]));
        blog_info_raw("  0x%08lx", (part->pt_entries[i].max_len[0]));
        blog_info_raw("  0x%08lx", (part->pt_entries[i].max_len[1]));
        blog_info_raw("  %lu\r\n", (part->pt_entries[i].age));
    }
}

uint32_t hal_boot2_get_flash_addr(void)
{
    extern uint8_t __boot2_flashCfg_src;

    return  (uint32_t)(&__boot2_flashCfg_src + 
            (sizeof(boot2_partition_table.table.pt_entries[0]) * boot2_partition_table.table.pt_table.entryCnt));
}

int hal_boot2_partition_bus_addr(const char *name, uint32_t *addr0, uint32_t *addr1, uint32_t *size0, uint32_t *size1, int *active)
{
    int i;
    uint32_t addr0_t, addr1_t;

    if (PARTITION_MAGIC != boot2_partition_table.table.pt_table.magicCode) {
        return -EIO;
    }

    /*Get Target partition*/
    for (i = 0; i < boot2_partition_table.table.pt_table.entryCnt; i++) {
        if (0 == strcmp((char *)&(boot2_partition_table.table.pt_entries[i].name[0]), name)) {
            break;
        }
    }
    if (boot2_partition_table.table.pt_table.entryCnt == i) {
        return -ENOENT;
    }
    addr0_t = boot2_partition_table.table.pt_entries[i].start_address[0];
    addr1_t = boot2_partition_table.table.pt_entries[i].start_address[1];
    *active = boot2_partition_table.table.pt_entries[i].active_index;
    *size0 = boot2_partition_table.table.pt_entries[i].max_len[0];
    *size1 = boot2_partition_table.table.pt_entries[i].max_len[1];

    /*cal partition address*/
    for (i = 0; i < boot2_partition_table.table.pt_table.entryCnt; i++) {
        if (0 == strcmp((char *)&(boot2_partition_table.table.pt_entries[i].name[0]), PARTITION_FW_PART_NAME)) {
            break;
        }
    }
    if (boot2_partition_table.table.pt_table.entryCnt == i) {
        return -ECANCELED;
    }
    /*Make sure target partition is after FW partition*/
    if ( (addr0_t && (addr0_t < boot2_partition_table.table.pt_entries[i].start_address[0])) ||
         (addr0_t && (addr0_t < boot2_partition_table.table.pt_entries[i].start_address[1])) ||
         (addr1_t && (addr1_t < boot2_partition_table.table.pt_entries[i].start_address[0])) ||
         (addr1_t && (addr1_t < boot2_partition_table.table.pt_entries[i].start_address[1]))) {
        return -EINVAL;
    }
    if ((0 != boot2_partition_table.table.pt_entries[i].active_index) &&
        (1 != boot2_partition_table.table.pt_entries[i].active_index)) {
        return -EFAULT;
    }
    *addr0 = addr0_t - boot2_partition_table.table.pt_entries[i].start_address[boot2_partition_table.table.pt_entries[i].active_index] - PARTITION_FW_PART_HEADER_SIZE + FW_XIP_ADDRESS;
    *addr1 = addr1_t - boot2_partition_table.table.pt_entries[i].start_address[boot2_partition_table.table.pt_entries[i].active_index] - PARTITION_FW_PART_HEADER_SIZE + FW_XIP_ADDRESS;

    return 0;
}

int hal_boot2_partition_bus_addr_active(const char *name, uint32_t *addr, uint32_t *size)
{
    uint32_t addr0, addr1;
    uint32_t size0, size1;
    int active, ret;

    if ((ret = hal_boot2_partition_bus_addr(name, &addr0, &addr1, &size0, &size1, &active))) {
        return ret;
    }
    *addr = active ? addr1 : addr0;
    *size = active ? size1 : size0;

    return 0;
}

int hal_boot2_partition_bus_addr_inactive(const char *name, uint32_t *addr, uint32_t *size)
{
    uint32_t addr0, addr1;
    uint32_t size0, size1;
    int active, ret;

    if ((ret = hal_boot2_partition_bus_addr(name, &addr0, &addr1, &size0, &size1, &active))) {
        return ret;
    }
    *addr = active ? addr0 : addr1;
    *size = active ? size0 : size1;

    return 0;
}

int hal_boot2_partition_addr(const char *name, uint32_t *addr0, uint32_t *addr1, uint32_t *size0, uint32_t *size1, int *active)
{
    int i;

    if (PARTITION_MAGIC != boot2_partition_table.table.pt_table.magicCode) {
        return -EIO;
    }

    /*Get Target partition*/
    for (i = 0; i < boot2_partition_table.table.pt_table.entryCnt; i++) {
        if (0 == strcmp((char *)&(boot2_partition_table.table.pt_entries[i].name[0]), name)) {
            break;
        }
    }
    if (boot2_partition_table.table.pt_table.entryCnt == i) {
        return -ENOENT;
    }
    *addr0 = boot2_partition_table.table.pt_entries[i].start_address[0];
    *addr1 = boot2_partition_table.table.pt_entries[i].start_address[1];
    *size0 = boot2_partition_table.table.pt_entries[i].max_len[0];
    *size1 = boot2_partition_table.table.pt_entries[i].max_len[1];
    *active = boot2_partition_table.table.pt_entries[i].active_index;

    return 0;
}

int hal_boot2_partition_addr_active(const char *name, uint32_t *addr, uint32_t *size)
{
    uint32_t addr0, addr1;
    uint32_t size0, size1;
    int active, ret;

    if ((ret = hal_boot2_partition_addr(name, &addr0, &addr1, &size0, &size1, &active))) {
        return ret;
    }
    *addr = active ? addr1 : addr0;
    *size = active ? size1 : size0;

    return 0;
}

int hal_boot2_partition_addr_inactive(const char *name, uint32_t *addr, uint32_t *size)
{
    uint32_t addr0, addr1;
    uint32_t size0, size1;
    int active, ret;

    if ((ret = hal_boot2_partition_addr(name, &addr0, &addr1, &size0, &size1, &active))) {
        return ret;
    }
    *addr = active ? addr0 : addr1;
    *size = active ? size0 : size1;

    return 0;
}

uint8_t hal_boot2_get_active_partition(void)
{
    return boot2_partition_table.partition_active_idx;
}

int hal_boot2_get_active_entries_byname(uint8_t *name, HALPartition_Entry_Config *ptEntry_hal)
{
    pt_table_entry_config *ptEntry = (pt_table_entry_config*)ptEntry_hal;
    if (pt_table_get_active_entries_by_name(&boot2_partition_table.table, name, ptEntry)) {
        return -1;
    }
    return 0;
}

int hal_boot2_get_active_entries(int type, HALPartition_Entry_Config *ptEntry_hal)
{
    pt_table_entry_config *ptEntry = (pt_table_entry_config*)ptEntry_hal;
    if (pt_table_get_active_entries_by_id(&boot2_partition_table.table, type, ptEntry)) {
        return -1;
    }
    return 0;
}

int hal_boot2_dump(void)
{
    _dump_partition();
    return 0;
}

int hal_boot2_init(void)
{
    pt_table_stuff_config ptstuff[2];
    pt_table_id_type active_id;

    active_id = pt_table_get_active_partition_need_lock(ptstuff);

    if (active_id < PT_TABLE_ID_INVALID) {
        boot2_partition_table.partition_active_idx = active_id;
        ARCH_MemCpy_Fast(&boot2_partition_table.table, &ptstuff[active_id], sizeof(pt_table_stuff_config));
    } else {
        printf("[HAL] [BOOT2] hal boot2 init fail!\r\n");
        return -1;
    }

    printf("[HAL] [BOOT2] Active Partition[%u] consumed %d Bytes\r\n",
            boot2_partition_table.partition_active_idx,
            sizeof(pt_table_stuff_config)
    );
    _dump_partition();
    bl_flash_config_update();

    return 0;
}

#define     PT_OTA_TYPE_NAME         "FW"
#define     PT_MEDIA_TYPE_NAME       "mfg"
void hal_update_mfg_ptable(void)
{
    pt_table_entry_config ptEntry_fw;
    pt_table_entry_config ptEntry_media;

    printf("update mfg table.\r\n");
    printf("====================\r\n");
    if (0 == hal_boot2_get_active_entries_byname((uint8_t *)PT_OTA_TYPE_NAME, (HALPartition_Entry_Config *)(&ptEntry_fw))) {       // ota
        if (0 == hal_boot2_get_active_entries_byname((uint8_t *)PT_MEDIA_TYPE_NAME, (HALPartition_Entry_Config *)(&ptEntry_media))) { // media
            if (ptEntry_fw.start_address[1] == ptEntry_media.start_address[0]) {

                //memset(ptEntry_media.name, 0, sizeof(ptEntry_media.name));
                pt_table_update_entry(!boot2_partition_table.partition_active_idx, &boot2_partition_table.table, &ptEntry_media);

                printf("===== update mfg partition =====\r\n");
            }
        }
    }

    printf("====================\r\n");
    printf("update mfg table.\r\n");
}

