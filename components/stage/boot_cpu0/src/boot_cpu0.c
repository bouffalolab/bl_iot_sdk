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
#include <FreeRTOS.h>
#include <task.h>
#include <vfs.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cli.h>
#include <getopt.h>
#include <bl_sys.h>
#include <hal_sys.h>
#include <bl808_glb.h>
#include <bl808_glb_gpio.h>
#include <bl808_tzc_sec.h>
#include <bl_wifi.h>
#include <bl_romfs.h>
#include <bl_psram.h>
#include <bl_timer.h>
#include <fs/vfs_romfs.h>
#include <core_rv32.h>
#include <bl_mm_clock.h>
#include "boot_cpu0.h"

#include "ipc_xram_test.h"

#define ROMFS_DIR                "/romfs"
#define TASK_NAME_LOAD_ROMFS     "load_romfs"
#define TASK_NAME_BOOT_C906      "boot_c906"
#define LOAD_BIN_ADDR             0x80000000
#define MAX_LEN_ROMFS_NAME        40
#define CORES_FLAG_ADDRESS      0x3ef80000
#define XIP_A_ADDR              0x58000000
#define C906_START_ADDR         0x50100000
#define XIP_START_FLAG          1
static char   c906_bin_name[MAX_LEN_ROMFS_NAME];
static uint   c906_bin_addr;

static void cmd_cli(char *buf, int len, int argc, char **argv)
{
    printf("hello world\r\n");
}

static int is_task_alive(char* task_name)
{
    char *pos;
    char *pcWriteBuffer;

    pcWriteBuffer = pvPortMalloc(1024);
    if (NULL == pcWriteBuffer) {
        printf("alloc task lisk buffer error!\r\n");
        return 1;
    }

    vTaskList(pcWriteBuffer);
    pos = strstr(pcWriteBuffer, task_name);
    vPortFree(pcWriteBuffer);

    return (pos==NULL)?0:1;
}

static void load_romfs_bin(void *pvParameters)
{
    char path_name[128];
    aos_dir_t * dp;
    aos_dirent_t *out_dirent;
    struct stat *st;
    size_t ret;
    int file_fd = 0;

    st = pvPortMalloc(sizeof(struct stat));
    if (NULL == st) {
        printf("malloc st fail\r\n");
        goto exit;
    }
    memset(stat, 0, sizeof(struct stat));
    memset(path_name, 0, sizeof(path_name));
    dp = (aos_dir_t *)aos_opendir(ROMFS_DIR);
    if (dp) {
        while(1) {
            out_dirent = (aos_dirent_t *)aos_readdir(dp);
            if (out_dirent == NULL) {
                printf("%s not in romfs\r\n", c906_bin_name);
                aos_closedir(dp);
                goto exit;
            }
            if (0 == strncmp(out_dirent->d_name, c906_bin_name, MAX_LEN_ROMFS_NAME)) {
                break;
            }
        }

        snprintf(path_name, sizeof(path_name) - 1, "%s", ROMFS_DIR);
        if (path_name[strlen(path_name) - 1] != '/') {
            path_name[strlen(path_name)] = '/';
        }
        snprintf(path_name + strlen(path_name), sizeof(path_name)- strlen(path_name) - 1, "%s", out_dirent->d_name);
        if (0 == aos_stat(path_name, st)) {
            file_fd = aos_open(path_name, 0);
            if (file_fd) {
                hal_enable_cpu0();
                printf("open file :%s\t size:%10ldbytes\t\t\r\n", out_dirent->d_name, st->st_size);
                ret = aos_read(file_fd, (void*)c906_bin_addr, st->st_size);
                csi_dcache_clean_range((void*)c906_bin_addr, st->st_size);
                if (ret == st->st_size) {
                    printf("load c906 bin successfully\r\n");
                    hal_boot_cpu0(c906_bin_addr);
                } else {
                    printf("load c906 bin fail\r\n");
                }
                aos_close(file_fd);
            } else {
                printf("open romfs file fail\r\n");
            }
        }
        aos_closedir(dp);
    } else {
        printf("can not open romfs\r\n");
    }
exit:
    vPortFree(st);
    vTaskDelete(NULL);
}

void mm_clk_config(void)
{
    bl_mm_xclk_config(XCLK_XTAL); /*xclk select XTAL*/
    bl_mm_bclk_config(BCLK_MUXPLL_160M); /*bclk1x select 160M*/
    bl_mm_cpu_root_clk_config(CPU_ROOT_CLK_PLL); /*cpu root clk select PLL*/
    bl_mm_cpu_clk_config(CPU_CLK_MUXPLL_400M); /*cpu pll select 400M*/
    bl_mm_uart_clk_config(UART_CLK_XCLK1); /*uart select xclk and xclk select XTAL*/
    bl_mm_i2c_clk_config(I2C_CLK_XCLK); /*i2c select xclk and xclk select XTAL*/
}

static void set_c906_xip_offset(uint32_t e907_xip_addr)
{
    uint32_t flash_offset_d0 = 0;
    uint32_t flash_offset_m0 = 0;

    flash_offset_d0 = e907_xip_addr - XIP_A_ADDR;
    flash_offset_m0 = SF_Ctrl_Get_Flash_Image_Offset(0, SF_CTRL_FLASH_BANK0);
    flash_offset_d0 += flash_offset_m0;
    /* FIXME */
    Tzc_Sec_Set_CPU_Group(GLB_CORE_ID_D0, 1);
    SF_Ctrl_Set_Flash_Image_Offset(flash_offset_d0, 1, SF_CTRL_FLASH_BANK0);
}

extern void l2_sram_vram_config(void);

void c906_bringup(uint32_t start_addr)
{
    int fd = -1;
    romfs_filebuf_t filebuf;

    fd = aos_open("/romfs/c906.bin", 0);
    aos_ioctl(fd, IOCTL_ROMFS_GET_FILEBUF, (long unsigned int)&filebuf);
    if (fd < 0) {
        printf("/romfs/c906.bin not found!\r\n");
        vTaskDelete(NULL);
        return;
    }

    aos_close(fd);
    printf("Found file %s. XIP Addr %p, len %lu\r\n",
            "/romfs/c906.bin",
            filebuf.buf,
            (unsigned long)filebuf.bufsize);
    if (start_addr == 0) {
        start_addr = (uint32_t)XIP_A_ADDR;
        set_c906_xip_offset((uint32_t)filebuf.buf);
        printf("setup c906 on XIP");
    } else {
        /* copy c906 bin on psram */
        memcpy((void *)start_addr, filebuf.buf, (unsigned long)filebuf.bufsize);
        csi_dcache_clean_range((uint32_t *)start_addr, (unsigned long)filebuf.bufsize);
        printf("setup c906 on psram\r\n");
    }
    /* boot c906 */
    hal_enable_cpu0();
    hal_halt_cpu0();
    mm_clk_config();
    l2_sram_vram_config();

    bl_mtimer_c906_clock_init();

    hal_boot_cpu0(start_addr);

    bl_mm_clk_dump();
}

static void c906_bringup_entry(void *arg)
{
    uint32_t start_addr;

    if (*(int *)arg == XIP_START_FLAG)
        start_addr = 0;
    else
        start_addr = C906_START_ADDR;

    c906_bringup(start_addr);

    vTaskDelete(NULL);
}

static void boot_c906(void *pvParameters)
{
    char path_name[128];
    aos_dir_t * dp;
    aos_dirent_t *out_dirent;
    romfs_filebuf_t filebuf;
    int file_fd = 0;
    char *bin_name = (char *)pvParameters;
    uint32_t flash_offset_d0 = 0, flash_offset_m0 = 0;

    if (NULL == bin_name) {
        printf("load bin name is NULL\r\n");
        goto exit;
    }

    memset(path_name, 0, sizeof(path_name));
    dp = (aos_dir_t *)aos_opendir(ROMFS_DIR);
    if (dp) {
        while(1) {
            out_dirent = (aos_dirent_t *)aos_readdir(dp);
            if (out_dirent == NULL) {
                printf("%s not in romfs\r\n", bin_name);
                aos_closedir(dp);
                goto exit;
            }
            if (0 == strncmp(out_dirent->d_name, bin_name, MAX_LEN_ROMFS_NAME)) {
                break;
            }
        }
        aos_closedir(dp);

        snprintf(path_name, sizeof(path_name) - 1, "%s", ROMFS_DIR);
        if (path_name[strlen(path_name) - 1] != '/') {
            path_name[strlen(path_name)] = '/';
        }
        snprintf(path_name + strlen(path_name), sizeof(path_name)- strlen(path_name) - 1, "%s", out_dirent->d_name);
        file_fd = aos_open(path_name, 0);

        if (file_fd) {
            /* boot c906 */
            aos_ioctl(file_fd, IOCTL_ROMFS_GET_FILEBUF, (long unsigned int)&filebuf);
            flash_offset_d0 = (uint32_t)filebuf.buf - XIP_A_ADDR;
            flash_offset_m0 = SF_Ctrl_Get_Flash_Image_Offset(0, SF_CTRL_FLASH_BANK0);
            flash_offset_d0 += flash_offset_m0;
            printf("Found file %s. XIP Addr %p, len %lu\r\n", path_name, filebuf.buf, (unsigned long)filebuf.bufsize);
            aos_close(file_fd);
            /* FIXME */
            hal_enable_cpu0();
            hal_halt_cpu0();
            /* Set C906 GRP1 AND OFFSET */
            Tzc_Sec_Set_CPU_Group(GLB_CORE_ID_D0, 1);
            SF_Ctrl_Set_Flash_Image_Offset(flash_offset_d0, 1, SF_CTRL_FLASH_BANK0);
            l2_sram_vram_config();
            hal_boot_cpu0((uint32_t)XIP_A_ADDR);
            printf("boot c906 bin %s successfully\r\n", bin_name);
            bl_mm_clk_dump();
        } else {
            printf("open romfs file fail\r\n");
        }
    } else {
        printf("can not open romfs\r\n");
    }
exit:
    vTaskDelete(NULL);
}

static void show_usage(void)
{
    aos_cli_printf("load_c906_bin [options]\r\n");
    aos_cli_printf("--name name of c906 bin\r\n");
    aos_cli_printf("--addr c906 bin address to load memory\r\n");
    aos_cli_printf("example:\r\n");
    aos_cli_printf("    load_c906_bin -n bl808_demo_helloworld11.bin -a 0x80000000\r\n");
}

static void cmd_romfs_load(char *buf, int len, int argc, char **argv)
{
    int ch;
    optind = 0;

    if (is_task_alive(TASK_NAME_LOAD_ROMFS)) {
        printf("romfs_load_bin task busy\r\n");
        return;
    }

    if (5 != argc) {
        printf("Please set name and address of c906 bin\r\n");
        show_usage();
        return;
    }

    static struct option long_options[] =
    {
        {"name",      required_argument, 0, 'n'},
        {"addr",      required_argument, 0, 'a'},
        {0, 0, 0, 0}
    };

    while ((ch = getopt_long (argc, argv, "n:a:h", long_options, NULL)) != -1) {
        switch (ch)
        {
        case 'a':
            sscanf(optarg, "%x", &c906_bin_addr);
            break;
        case 'n':
            strncpy(c906_bin_name, optarg, MAX_LEN_ROMFS_NAME);
            break;
        default:
            show_usage();
            return;
        }
    }

    xTaskCreate(load_romfs_bin, TASK_NAME_LOAD_ROMFS, 1024, NULL, 5, NULL);
}

static void cmd_halt_cpu0(char *buf, int len, int argc, char **argv)
{
    hal_halt_cpu0();
}

static void cmd_release_cpu0(char *buf, int len, int argc, char **argv)
{
    hal_release_cpu0();
}

static void cmd_jtag_cpu0(char *buf, int len, int argc, char **argv)
{
    bl_sys_enabe_jtag(1);
}

static void cmd_c906_bringup(char *buf, int len, int argc, char **argv)
{
    static int c906_ram_flag = 0;
    if (argc >= 2) {
       c906_ram_flag = XIP_START_FLAG;
    }

    if (is_task_alive("bootc906")) {
        printf("startup C906 task busy\r\n");
        return;
    }
    xTaskCreate(
            c906_bringup_entry,
            (char*)"bootc906",
            2048,
            &c906_ram_flag,
            10,
            NULL);
}

static void show_bootc906_usage(void)
{
    aos_cli_printf("boot_c906 [options]\r\n");
    aos_cli_printf("--name name of c906 bin\r\n");
    aos_cli_printf("example:\r\n");
    aos_cli_printf("    boot_c906 -n bl808_demo_helloworld11.bin\r\n");
}

static void cmd_boot_c906(char *buf, int len, int argc, char **argv)
{
    int ch;
    optind = 0;

    if (is_task_alive(TASK_NAME_BOOT_C906)) {
        printf("boot_c906 task busy\r\n");
        return;
    }

    if (3 != argc) {
        printf("Please set name c906 bin\r\n");
        show_bootc906_usage();
        return;
    }

    static struct option long_options[] =
    {
        {"name",      required_argument, 0, 'n'},
        {0, 0, 0, 0}
    };

    while ((ch = getopt_long (argc, argv, "n:h", long_options, NULL)) != -1) {
        switch (ch)
        {
        case 'n':
            strncpy(c906_bin_name, optarg, MAX_LEN_ROMFS_NAME);
            break;
        default:
            show_bootc906_usage();
            return;
        }
    }

    xTaskCreate(boot_c906, TASK_NAME_BOOT_C906, 1024, c906_bin_name, 5, NULL);
}

static void cmd_psram_init(char *buf, int len, int argc, char **argv)
{
    bl_psram_init();
}

#define SPEED_RAM_BASE_ADDR 0x50000000

uint32_t *count = (uint32_t *)SPEED_RAM_BASE_ADDR;

static void speed_report(void *arg) {
  uint32_t curr_count = 0, last_count = 0;
  uint32_t delta = 0;

  while(1) {
    curr_count = *count;

    /* KByte */
    delta = ((curr_count - last_count) >> 5); // * 32 / 1024

    printf("psram speed: %d\r\n", (unsigned int)delta);
    last_count = curr_count;
    vTaskDelay(pdMS_TO_TICKS(1000)); //delay 1s
  }
}

static void speed_test(void *arg) {
  uint32_t *addr = (uint32_t *)(SPEED_RAM_BASE_ADDR + 0x10);
  register uint32_t i  = 0, tmp = 0;

  *count = 0;

  /* total 8 word access, 32Byte, each loop */
  while(1) {
    /* 6 word access */
    *(addr + i + 0) = 0xdeadbaeb;
    *(addr + i + 1) = 0xeadbaebd;
    *(addr + i + 2) = 0xadbaebde;
    *(addr + i + 3) = 0xdbaebdea;
    *(addr + i + 4) = 0xbaebdead;
    *(addr + i + 5) = 0xaebdeadb;
    /*
    *(addr + i + 6) = 0xebdeadba;
    *(addr + i + 7) = 0xbdeadbae;
    */

    /* 2 word access */
    tmp = *count;
    tmp ++;
    *count = tmp;

    i = (i + 8) & 0xFF;
  }
}

static void cmd_psram_speed(char *buf, int len, int argc, char **argv) {
    xTaskCreate(speed_test,(char*)"speed_test",2048,NULL,29,NULL);

    xTaskCreate(speed_report,(char*)"speed_test_reporter",4096,NULL,30,NULL);
}

#define PSRAM_TEST_ADDR  (0x50000000)
#define PSRAM_TEST_SIZE  (64*1024*1024)
#define PSRAM_TEST_END  (PSRAM_TEST_ADDR+PSRAM_TEST_SIZE)
static void cmd_psram_test(char *buf, int len, int argc, char **argv)
{
    int i;
    uint32_t pattern = 0xffffffff;
    volatile uint32_t *addr = (uint32_t *) PSRAM_TEST_ADDR;

    csi_dcache_disable();
    while (pattern != 0) {
        printf("test for pattern 0x%lx\r\n", pattern);
        for (i = 0; i < PSRAM_TEST_SIZE/sizeof(uint32_t); i++) {
            addr[i] = pattern;
        }
        printf("writepass, readback to check\r\n");
        for (i = 0; i < PSRAM_TEST_SIZE/sizeof(uint32_t); i++) {
            if (addr[i] != pattern) {
                printf("0x%lx = 0x%lx, expected 0x%lx\r\n", (uint32_t)&addr[i], addr[i], pattern);
                while(1);
            }
        }
        printf("read pass\r\n");
	pattern = pattern >> 1;
    }

    printf("test done");
}

static void cmd_mac_get(char *buf, int len, int argc, char **argv)
{
    uint8_t mac_addr[6];
    bl_wifi_mac_addr_get(mac_addr);
    printf("bl808 mac addr is %x:%x:%x:%x:%x:%x\n",mac_addr[0],mac_addr[1],mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
}


const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    //{"test", "cli test", cmd_cli},
    //{"load_c906_bin", "romfs_load_bin", cmd_romfs_load},
    //{"ipc_xram_test", "ipc xram test", ipc_xram_test},
    //{"halt_cpu0", "cpu0 halt", cmd_halt_cpu0},
    {"jtag_cpu0", "cpu0 release", cmd_jtag_cpu0},
    //{"release_cpu0", "cpu0 release", cmd_release_cpu0},
    {"c906", "setup c906", cmd_c906_bringup},
    //{"boot_c906", "boot c906 bin", cmd_boot_c906},
    //{"psram", "psram", cmd_psram_init},
    //{"psram_speed", "psram_speed", cmd_psram_speed},
    //{"psram_test", "psram_test", cmd_psram_test},
    //{"wifi_mac_get", "wifi_mac_get", cmd_mac_get},

};

int boot_cpu0_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}

