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

#if CONF_BL602_USE_1M_FLASH
#include <bl602_xip_sflash_ext.h>
#endif

#include <bl602_romdriver.h>
#include "bl_flash.h"
#include "bl_irq.h"
#include <blog.h>

#define USER_UNUSED(a) ((void)(a))

static struct {
    uint32_t magic;
    SPI_Flash_Cfg_Type flashCfg;
} boot2_flashCfg; //XXX Dont change the name of varaible, since we refer this boot2_partition_table in linker script

int bl_flash_erase(uint32_t addr, int len)
{
    uint8_t isAesEnable;

    /*We assume mid zeor is illegal*/
    if (0 == boot2_flashCfg.flashCfg.mid) {
        return -1;
    }

#if CONF_BL602_USE_1M_FLASH
    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Erase_Need_Lock_Ext(
            &boot2_flashCfg.flashCfg,
            addr,
            addr + len - 1
    );
    GLOBAL_IRQ_RESTORE();
#else
    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Opt_Enter(&isAesEnable);
    RomDriver_XIP_SFlash_Erase_Need_Lock(
            &boot2_flashCfg.flashCfg,
            addr,
            addr + len - 1
    );
    XIP_SFlash_Opt_Exit(isAesEnable);
    GLOBAL_IRQ_RESTORE();
#endif

    return 0;
}

int bl_flash_write(uint32_t addr, uint8_t *src, int len)
{
    uint8_t isAesEnable;

    /*We assume mid zeor is illegal*/
    if (0 == boot2_flashCfg.flashCfg.mid) {
        return -1;
    }

#if CONF_BL602_USE_1M_FLASH
    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Write_Need_Lock_Ext(
            &boot2_flashCfg.flashCfg,
            addr,
            src,
            len
    );
    GLOBAL_IRQ_RESTORE();
#else
    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Opt_Enter(&isAesEnable);
    RomDriver_XIP_SFlash_Write_Need_Lock(
            &boot2_flashCfg.flashCfg,
            addr,
            src,
            len
    );
    XIP_SFlash_Opt_Exit(isAesEnable);
    GLOBAL_IRQ_RESTORE();
#endif

    return 0;
}

int bl_flash_read(uint32_t addr, uint8_t *dst, int len)
{
    uint8_t isAesEnable;

    /*We assume mid zeor is illegal*/
    if (0 == boot2_flashCfg.flashCfg.mid) {
        return -1;
    }

#if CONF_BL602_USE_1M_FLASH
    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Read_Need_Lock_Ext(
            &boot2_flashCfg.flashCfg,
            addr,
            dst,
            len
    );
    GLOBAL_IRQ_RESTORE();
#else
    GLOBAL_IRQ_SAVE();
    XIP_SFlash_Opt_Enter(&isAesEnable);
    RomDriver_XIP_SFlash_Read_Need_Lock(
            &boot2_flashCfg.flashCfg,
            addr,
            dst,
            len
    );
    XIP_SFlash_Opt_Exit(isAesEnable);
    GLOBAL_IRQ_RESTORE();
#endif

    return 0;
}

static void _dump_flash_config()
{
    extern uint8_t __boot2_flashCfg_src;

    USER_UNUSED(__boot2_flashCfg_src);

    blog_info("======= FlashCfg magiccode @%p, code 0x%08lX =======\r\n",
            &__boot2_flashCfg_src,
            boot2_flashCfg.magic
    );
    blog_info("mid \t\t0x%X\r\n", boot2_flashCfg.flashCfg.mid);
    blog_info("clkDelay \t0x%X\r\n", boot2_flashCfg.flashCfg.clkDelay);
    blog_info("clkInvert \t0x%X\r\n", boot2_flashCfg.flashCfg.clkInvert);
    blog_info("sector size\t%uKBytes\r\n", boot2_flashCfg.flashCfg.sectorSize);
    blog_info("page size\t%uBytes\r\n", boot2_flashCfg.flashCfg.pageSize);
    blog_info("---------------------------------------------------------------\r\n");
}

int bl_flash_config_update(void)
{
    _dump_flash_config();

    return 0;
}

void* bl_flash_get_flashCfg(void)
{
    return &boot2_flashCfg.flashCfg;
}

int bl_flash_read_byxip(uint32_t addr, uint8_t *dst, int len)
{
    uint32_t offset;
    uint32_t xipaddr;

    offset = RomDriver_SF_Ctrl_Get_Flash_Image_Offset();

    if ((addr < offset) || (addr >= 0x1000000)) {
        // not support or arg err ?
        return -1;
    }

    xipaddr =  0x23000000 - offset + addr;

    memcpy(dst, (void *)xipaddr, len);

    return 0;
}

