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
#include "hal_uart.h"
#include "hal_flash.h"
#include "hal_mtimer.h"
#include "drv_mmheap.h"
#include "hal_common.h"
#include "ring_buffer.h"
#include "bflb_platform.h"

extern uint32_t __HeapBase;
extern uint32_t __HeapLimit;

static uint8_t uart_dbg_disable = 0;

struct heap_info mmheap_root;

static struct heap_region system_mmheap[] = {
    { NULL, 0 },
    { NULL, 0 }, /* Terminates the array. */
};

__WEAK__ void board_init(void)
{
}
__WEAK__ void bl_show_info(void)
{
}

__WEAK__ enum uart_index_type board_get_debug_uart_index(void)
{
    return 0;
}

#ifdef CONFIG_SHELL_ENABLE
#include "shell.h"
static void shell_irq_callback(struct device *dev, void *args, uint32_t size, uint32_t state)
{
    uint8_t data;
    for (size_t i = 0; i < size; i++) {
        data = *(uint8_t *)(args + i);
        shell_handler(data);
    }
}
#endif
void bl_show_flashinfo(void)
{
    SPI_Flash_Cfg_Type flashCfg;
    uint8_t *pFlashCfg = NULL;
    uint32_t flashCfgLen = 0;
    uint32_t flashJedecId = 0;

    flashJedecId = flash_get_jedecid();
    flash_get_cfg(&pFlashCfg, &flashCfgLen);
    arch_memcpy((void *)&flashCfg, pFlashCfg, flashCfgLen);
    MSG("show flash cfg:\r\n");
    MSG("jedec id   0x%06X\r\n", flashJedecId);
    MSG("mid            0x%02X\r\n", flashCfg.mid);
    MSG("iomode         0x%02X\r\n", flashCfg.ioMode);
    MSG("clk delay      0x%02X\r\n", flashCfg.clkDelay);
    MSG("clk invert     0x%02X\r\n", flashCfg.clkInvert);
    MSG("read reg cmd0  0x%02X\r\n", flashCfg.readRegCmd[0]);
    MSG("read reg cmd1  0x%02X\r\n", flashCfg.readRegCmd[1]);
    MSG("write reg cmd0 0x%02X\r\n", flashCfg.writeRegCmd[0]);
    MSG("write reg cmd1 0x%02X\r\n", flashCfg.writeRegCmd[1]);
    MSG("qe write len   0x%02X\r\n", flashCfg.qeWriteRegLen);
    MSG("cread support  0x%02X\r\n", flashCfg.cReadSupport);
    MSG("cread code     0x%02X\r\n", flashCfg.cReadMode);
    MSG("burst wrap cmd 0x%02X\r\n", flashCfg.burstWrapCmd);
    MSG("-------------------\r\n");
}

#ifdef CONFIG_SHELL_ENABLE
int reboot(int argc, char **argv)
{
    hal_reboot_cfg_t rbot;

    /* check args */
    if (argc > 2) {
        MSG("too many parameters\r\n");
        return 0;
    }

    if (2 == argc) {
        /* get parm */
        rbot = (hal_reboot_cfg_t)strtoll(argv[1], NULL, 0);

        if (rbot < HAL_REBOOT_MAX) {
            /* config reboot */
            switch (rbot) {
                case 0:
                    MSG("reboot from media, normal run\r\n");
                    rbot = HAL_REBOOT_FROM_MEDIA;
                    break;
                case 1:
                    MSG("reboot from interface for download\r\n");
                    rbot = HAL_REBOOT_FROM_INTERFACE;
                    break;
                default:
                    MSG("reboot parameters only support None/0/1\r\n");
                    return 0;
            }
            arch_delay_us(100);
            hal_reboot_config(rbot);
        }
    } else {
        MSG("reboot\r\n");
        arch_delay_us(100);
    }

    hal_por_reset();
    return 0;
}
SHELL_CMD_EXPORT(reboot, reboot system)
#endif

void bflb_platform_init(uint32_t baudrate)
{
    static uint8_t initialized = 0;

    cpu_global_irq_disable();

#ifdef CONFIG_BL_FLASH_INIT
    BL_Err_Type ret = ERROR;
    ret = flash_init();
#endif

    board_init();

    if (!uart_dbg_disable) {
        uart_register(board_get_debug_uart_index(), "debug_log");
        struct device *uart = device_find("debug_log");

        if (uart) {
            device_open(uart, DEVICE_OFLAG_STREAM_TX | DEVICE_OFLAG_INT_RX);
#ifdef CONFIG_SHELL_ENABLE
            device_set_callback(uart, shell_irq_callback);
            device_control(uart, DEVICE_CTRL_SET_INT, (void *)(UART_RX_FIFO_IT | UART_RTO_IT));
#endif
        }
#ifdef CONFIG_BL_SHOW_INFO
        bl_show_info();
#endif
    }

    if (!initialized) {
        system_mmheap[0].addr = (uint8_t *)&__HeapBase;
        system_mmheap[0].mem_size = ((size_t)&__HeapLimit - (size_t)&__HeapBase);

        if (system_mmheap[0].mem_size > 0) {
            mmheap_init(&mmheap_root, system_mmheap);
        }

        MSG("dynamic memory init success,heap size = %d Kbyte \r\n", system_mmheap[0].mem_size / 1024);
        initialized = 1;
#ifdef CONFIG_BL_FLASH_INIT
        if (ret != SUCCESS) {
            MSG("flash init fail!!!\r\n");
        }
        bl_show_flashinfo();
#endif
#ifdef CONFIG_SHELL_ENABLE
        shell_init();
#endif
    }

    cpu_global_irq_enable();
}

#if ((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
static uint8_t eflash_loader_logbuf[1024] __attribute__((section(".system_ram_noinit")));
static uint32_t log_len = 0;
uint32_t bflb_platform_get_log(uint8_t *data, uint32_t maxlen)
{
    uint32_t len = log_len;
    if (len > maxlen) {
        len = maxlen;
    }
    memcpy(data, eflash_loader_logbuf, len);
    return len;
}
#endif
int puts(const char *fmt) __attribute__((alias("bflb_platform_printf")));
int printf(const char *fmt, ...) __attribute__((alias("bflb_platform_printf")));
void bflb_platform_printf(char *fmt, ...)
{
    struct device *uart;
    char print_buf[128];
    va_list ap;

    if (!uart_dbg_disable) {
        va_start(ap, fmt);
        vsnprintf(print_buf, sizeof(print_buf) - 1, fmt, ap);
        va_end(ap);
#if ((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
        uint32_t len = strlen(print_buf);
        if (log_len + len < sizeof(eflash_loader_logbuf)) {
            memcpy(eflash_loader_logbuf + log_len, print_buf, len);
            log_len += len;
        }
#endif
        uart = device_find("debug_log");
        device_write(uart, 0, (uint8_t *)print_buf, strlen(print_buf));
    }
}

void bflb_platform_print_set(uint8_t disable)
{
    uart_dbg_disable = disable;
}

uint8_t bflb_platform_print_get(void)
{
    return uart_dbg_disable;
}

void bflb_platform_deinit(void)
{
    if (!uart_dbg_disable) {
        struct device *uart = device_find("debug_log");
        if (uart) {
            device_close(uart);
            device_unregister("debug_log");
        }
    }
}

void bflb_platform_dump(uint8_t *data, uint32_t len)
{
    uint32_t i = 0;

    if (!uart_dbg_disable) {
        for (i = 0; i < len; i++) {
            if (i % 16 == 0) {
                bflb_platform_printf("\r\n");
            }

            bflb_platform_printf("%02x ", data[i]);
        }

        bflb_platform_printf("\r\n");
    }
}

void bflb_platform_reg_dump(uint32_t addr)
{
    bflb_platform_printf("%08x[31:0]=%08x\r\n", addr, *(volatile uint32_t *)(uintptr_t)(addr));
}

void bflb_platform_init_time()
{
}

void bflb_platform_deinit_time()
{
}

void bflb_platform_set_alarm_time(uint64_t time, void (*interruptFun)(void))
{
    mtimer_set_alarm_time(time, interruptFun);
}

void bflb_platform_clear_time()
{
}

void bflb_platform_start_time()
{
}

void bflb_platform_stop_time()
{
}

uint64_t bflb_platform_get_time_ms()
{
    return mtimer_get_time_ms();
}

uint64_t bflb_platform_get_time_us()
{
    return mtimer_get_time_us();
}

void bflb_platform_delay_ms(uint32_t ms)
{
    mtimer_delay_ms(ms);
}
void bflb_platform_delay_us(uint32_t us)
{
    mtimer_delay_us(us);
}

void bflb_print_device_list(void)
{
    struct device *dev;
    dlist_t *node;
    uint8_t device_index = 0;

    MSG("Device List Print\r\n");

    dlist_for_each(node, device_get_list_header())
    {
        dev = dlist_entry(node, struct device, list);

        MSG("Index %d\r\nDevice Name = %s \r\n", device_index, dev->name);

        switch (dev->type) {
            case DEVICE_CLASS_GPIO:
                MSG("Device Type = %s \r\n", "GPIO");
                break;

            case DEVICE_CLASS_UART:
                MSG("Device Type = %s \r\n", "UART");
                break;

            case DEVICE_CLASS_SPI:
                MSG("Device Type = %s \r\n", "SPI");
                break;

            case DEVICE_CLASS_I2C:
                MSG("Device Type = %s \r\n", "I2C");
                break;

            case DEVICE_CLASS_ADC:
                MSG("Device Type = %s \r\n", "ADC");
                break;

            case DEVICE_CLASS_DMA:
                MSG("Device Type = %s \r\n", "DMA");
                break;

            case DEVICE_CLASS_TIMER:
                MSG("Device Type = %s \r\n", "TIMER");
                break;

            case DEVICE_CLASS_PWM:
                MSG("Device Type = %s \r\n", "PWM");
                break;

            case DEVICE_CLASS_SDIO:
                MSG("Device Type = %s \r\n", "SDIO");
                break;

            case DEVICE_CLASS_USB:
                MSG("Device Type = %s \r\n", "USB");
                break;

            case DEVICE_CLASS_I2S:
                MSG("Device Type = %s \r\n", "I2S");
                break;

            case DEVICE_CLASS_CAMERA:
                MSG("Device Type = %s \r\n", "CAMERA");
                break;

            case DEVICE_CLASS_NONE:
                break;

            default:
                break;
        }

        MSG("Device Handle = 0x%x \r\n", dev);
        MSG("---------------------\r\n", dev);

        device_index++;
    }
}
