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
#ifdef CPU_M0

#include <stdbool.h>
#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>
#include <aos/kernel.h>
#include <vfs.h>
#include <fs/vfs_romfs.h>
#include <cli.h>

#include <xz.h>

#include <bl_irq.h>
#include <hal_sys.h>
#include <bl808_tzc_sec.h>
#include <bl808_usb.h>
#include <bl808_ipc.h>

#include "linux_cfg.h"

#define XIP_A_ADDR              0x58000000

struct load_item {
    const char *desc;
    const char *filename;
    void *load_addr;
    size_t dst_size;
    bool xz;
};

static struct load_item load_items[] = {
    { "opensbi", "/romfs/sbi.bin",        (void *)OPENSBI_ADDR, 0,                false },
    { "kernel",  "/romfs/Image.xz",       (void *)KERNEL_ADDR,  32 * 1024 * 1024, true },
    { "rootfs",  "/romfs/rootfs.cpio.gz", (void *)ROOTFS_ADDR,  0,                false },
    { "dtb",     "/romfs/hw.dtb",         (void *)DTB_ADDR,     0,                false },
};

static int load_one_bin(struct load_item *item)
{
    int fd = -1;
    romfs_filebuf_t filebuf;

    fd = aos_open(item->filename, 0);
    aos_ioctl(fd, IOCTL_ROMFS_GET_FILEBUF, (long unsigned int)&filebuf);
    if (fd < 0) {
        printf("%s not found!\r\n", item->filename);
        return -1;
    }

    aos_close(fd);
    printf("Found file %s. XIP Addr %p, len %lu",
            item->filename,
            filebuf.buf,
            (unsigned long)filebuf.bufsize);
    if (!item->xz) {
        memcpy(item->load_addr, filebuf.buf, filebuf.bufsize);
        csi_dcache_clean_invalid_range((void*)item->load_addr, filebuf.bufsize);
    } else {
        struct xz_buf b;
        struct xz_dec *s;
        enum xz_ret xzret;

        if (!(s = xz_dec_init(XZ_SINGLE, 0))) {
            printf("xz init failed\r\n");
            return -1;
        }

        b.in = (uint8_t *)filebuf.buf;
        b.in_pos = 0;
        b.in_size = filebuf.bufsize;

        b.out = item->load_addr;
        b.out_pos = 0;
        b.out_size = item->dst_size;

        xzret = xz_dec_run(s, &b);
        xz_dec_end(s);
        if (xzret != XZ_STREAM_END) {
            printf("decoding failed, ret %d", xzret);
            return -1;
        } else {
            printf("successfully extracted %u bytes", b.out_pos);
        }
        csi_dcache_clean_range((void*)item->load_addr, b.out_pos);
    }
    return 0;
}

static void init_wl_sys_all_int(void)
{
    for (int i = 0; i < 64; ++i) {
        GLB_DSP_Set_MCU_IntMask(i, MASK);
        GLB_DSP_Clr_MCU_IntStatus(i);
    }
    GLB_DSP_Set_MCU_IntMask(GLB_MCU_ALL_INT_USB_INT, UNMASK);
}

static void init_usb_host(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
    tmpVal |= (1 << 13);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpVal);
    GLB_Set_USB_CLK_From_WIFIPLL(1);
    PDS_Turn_On_USB(1);

    /* enable device-A for host */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_USB_CTL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_REG_USB_IDDIG);
    BL_WR_REG(PDS_BASE, PDS_USB_CTL, tmpVal);

    USB_Global_IntMask(USB_GLOBAL_INT_HC, UNMASK);
    USB_Global_IntMask(USB_GLOBAL_INT_OTG, MASK);
    USB_Global_IntMask(USB_GLOBAL_INT_DEV, MASK);

    init_wl_sys_all_int();
}

typedef enum {
    LINUX_40M,
    LINUX_76M,
    LINUX_95M,
    LINUX_190M,
    LINUX_380M,
    LINUX_480M,
} linux_cfg_t;

static void configure_clock(linux_cfg_t cfg)
{
    uint32_t reg;
    uint16_t rtc_div = 0;

    if (cfg == LINUX_40M) {
        // C906 40M
        reg = *(volatile unsigned int *)0x30007000;
        reg |= (1 << 10); // mm_xclk <--- xtal
        reg |= (3 <<  4); // mm_uart_clk <--- mm_xclk
        reg &= ~(1 << 11); // mm_cpu_clk <--- xclk
        *(volatile unsigned int *)0x30007000 = reg;
        *(volatile unsigned int *)0x30007004 = 0x00010100;

        rtc_div = 40;
    } else if (cfg == LINUX_480M) {
        GLB_Config_CPU_PLL(GLB_XTAL_40M, cpuPllCfg_480M);
        GLB_Set_DSP_System_CLK_Div(0, 1);
        rtc_div = 480;
    } else {
        GLB_Config_CPU_PLL(GLB_XTAL_40M, cpuPllCfg_380M);
        if (cfg == LINUX_76M) {
            GLB_Set_DSP_System_CLK_Div(4, 1);
            rtc_div = 76;
        } else if (cfg == LINUX_95M) {
            GLB_Set_DSP_System_CLK_Div(3, 1);
            rtc_div = 95;
        } else if (cfg == LINUX_190M) {
            GLB_Set_DSP_System_CLK_Div(1, 1);
            rtc_div = 190;
        } else if (cfg == LINUX_380M) {
            GLB_Set_DSP_System_CLK_Div(0, 1);
            rtc_div = 380;
        }
    }
    // RTC 1M
    reg = 0x80000000 | (rtc_div - 1);
    *(volatile unsigned int *)0x30000018 = reg;
}

static void c906_bringup_entry(void *arg)
{
    int fd = -1;
    uint32_t flash_offset_d0 = 0;
    uint32_t flash_offset_m0 = 0;
    romfs_filebuf_t filebuf;

    GLB_GPIO_Cfg_Type gpio_init;
    linux_cfg_t linux_cfg = (linux_cfg_t)arg;

    xz_crc32_init();

    vTaskDelay(100);

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
    /* boot c906 */
    csi_dcache_clean_range((void*)filebuf.buf, filebuf.bufsize);
    flash_offset_d0 = (uint32_t)filebuf.buf - XIP_A_ADDR;
    flash_offset_m0 = SF_Ctrl_Get_Flash_Image_Offset(0, SF_CTRL_FLASH_BANK0);
    flash_offset_d0 += flash_offset_m0;
    /* FIXME */
    Tzc_Sec_Set_CPU_Group(GLB_CORE_ID_D0, 1);
    SF_Ctrl_Set_Flash_Image_Offset(flash_offset_d0, 1, SF_CTRL_FLASH_BANK0);
    PDS_Power_On_MM_System();
    hal_halt_cpu0();

    /* Enable C906 JTAG */
    gpio_init.gpioFun = 27; // C906 JTAG
    gpio_init.gpioMode = GPIO_MODE_AF;
    gpio_init.pullType = GPIO_PULL_UP;
    gpio_init.drive=1;
    gpio_init.smtCtrl=1;

    gpio_init.gpioPin = 0;
    GLB_GPIO_Init(&gpio_init);

    gpio_init.gpioPin = 1;
    GLB_GPIO_Init(&gpio_init);

    gpio_init.gpioPin = 2;
    GLB_GPIO_Init(&gpio_init);

    gpio_init.gpioPin = 3;
    GLB_GPIO_Init(&gpio_init);

    for (int i = 0; i < sizeof(load_items) / sizeof(load_items[0]); ++i) {
        struct load_item *item = &load_items[i];
        printf("loading %s to addr %p ", item->desc, (void *)item->load_addr);
        if (load_one_bin(item)) {
            printf("\tfailed\r\n");
            goto exit;
        }
        printf("\tDone\r\n");
    }

    // C906 1.2V
    /* *(volatile uint32_t *)0x2000f814 = 0x14476c20; */

#if 0
    *(volatile uint32_t *)0x30007000 = 0x45105E3F;
    *(volatile uint32_t *)0x30007004 = 0x00010100;
    *(volatile uint32_t *)0x30000018 = 0x80000009;
#endif


    init_usb_host();
    configure_clock(linux_cfg);

    printf("Booting C906\r\n");
    hal_boot_cpu0((uint32_t)XIP_A_ADDR);

    goto exit;
exit:
    vTaskDelete(NULL);
}

static void cmd_linux_(char *buf, int len, int argc, char **argv)
{
    linux_cfg_t cfg = LINUX_480M;
    if (argc > 1) {
        if (!strcmp(argv[1], "40")) {
            cfg = LINUX_40M;
        } else if (!strcmp(argv[1], "76")) {
            cfg = LINUX_76M;
        } else if (!strcmp(argv[1], "95")) {
            cfg = LINUX_95M;
        } else if (!strcmp(argv[1], "190")) {
            cfg = LINUX_190M;
        } else if (!strcmp(argv[1], "380")) {
            cfg = LINUX_380M;
        } else if (!strcmp(argv[1], "480")) {
            cfg = LINUX_480M;
        }
    }
    xTaskCreate(c906_bringup_entry, (char*)"bootc906", 2048, (void *)cfg, 10, NULL);
}

void linux_default_boot(void)
{
    linux_cfg_t cfg = LINUX_480M;
    xTaskCreate(c906_bringup_entry, (char*)"bootc906", 2048, (void *)cfg, 10, NULL);
}

#define LINUX_CMD_HELP "boot linux.\r\n" \
    "cmd fmt: linux <freq: 40|76|95|190|380|480>\r\n" \
    "freq default: 480"
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"linux", LINUX_CMD_HELP, cmd_linux_},
};

void linux_m0_cli_register(void)
{
}

#endif // CPU_M0
