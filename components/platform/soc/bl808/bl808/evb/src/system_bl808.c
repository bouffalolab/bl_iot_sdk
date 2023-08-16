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
#include "csi_core.h"
#include "bl808.h"
#include "bl808_clock.h"
#include "bl808_glb.h"
#ifdef BOOTROM
#include "bflb_bootrom.h"
#endif

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define  SYSTEM_CLOCK     ( 32000000UL )
uintptr_t g_system_clock = SYSTEM_CLOCK;

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/

void system_bor_init(void)
{
    //HBN_BOR_CFG_Type borCfg = {1/* pu_bor */, 0/* irq_bor_en */, 1/* bor_vth */, 1/* bor_sel */};
    //HBN_Set_BOR_Cfg(&borCfg);
}

void System_Core_Clock_Set(BL_System_Clock_Type type,uint32_t clock)
{
    Clock_Cfg_Type *pClk=(Clock_Cfg_Type *)SYS_CLOCK_CFG_ADDR;

    CHECK_PARAM(IS_BL_SYSTEM_CLOCK_TYPE(type));

    if(type<BL_SYSTEM_CLOCK_MAX){
        pClk->systemClock[type]=clock;
        pClk->magic=SYS_CLOCK_CFG_MAGIC;
    }
}

void SystemInit (void)
{
    uintptr_t tmpVal=0;

    /* turn on cache to speed up boot sequence */
    csi_icache_enable();
    csi_dcache_enable();
    /* enable I/D Cache preload. */

    tmpVal = __get_MHINT();
    tmpVal |= (1 << 8) | (1 << 2);
    tmpVal &= (~0x18);
    __set_MHINT(tmpVal);
    __DSB();


#ifdef BOOTROM
    extern void GLB_Power_On_LDO18_IO(void);
    extern void WDT_Disable(void);
    extern void HBN_Clear_RTC_INT(void);

    BMX_Cfg_Type bmxCfg={
            .timeoutEn=0,
            .errEn=DISABLE,
            .arbMod=BMX_ARB_FIX
    };
    L1C_BMX_Cfg_Type  l1cBmxCfg={
            .timeoutEn=0,
            .errEn=DISABLE,
            .arbMod=L1C_BMX_ARB_FIX,
    };
    
    /* D0 boot log Flag */
    p= (uint32_t *)(BFLB_BOOTROM_D0_BOOT_LOG_ADDR);
    *p=0x5A5AA5A5;
    /*diable BMX error incase Sbooten=0xf,while user send vector(core) reset and CPU read deadbeef,
    if not disable this bit, CPU will also get hardfault at the same time*/
    //GLB->bmx_cfg1.BF.bmx_err_en=0;
    //GLB->bmx_cfg1.BF.bmx_timeout_en=0;
    //GLB->bmx_cfg2.BF.bmx_err_addr_dis=1;
    GLB_BMX_Init(&bmxCfg);
    GLB_BMX_Addr_Monitor_Disable();
    //L1C->l1c_config.BF.l1c_bmx_err_en=0;
    //L1C->l1c_config.BF.l1c_bmx_timeout_en=0;
    //L1C->l1c_bmx_err_addr_en.BF.l1c_bmx_err_addr_dis=1;
    L1C_BMX_Init(&l1cBmxCfg);
    L1C_BMX_Addr_Monitor_Disable();
    //L1C->l1c_config.BF.l1c_way_dis=0xf;
    L1C_Set_Way_Disable(0x0f);
    /* Disable Watchdog */
    WDT_Disable();
    /* Clear RTC */
    HBN_Clear_RTC_INT();
    /* Make OCRAM Idle from retention or sleep */
    GLB_Set_OCRAM_Idle();
    /* Disable embedded flash power up*/
    //HBN_Set_Embedded_Flash_Pullup(DISABLE);
#endif

#if 0
    /* disable hardware_pullup_pull_down (reg_en_hw_pu_pd = 0) */
    tmpVal=BL_RD_REG(HBN_BASE,HBN_IRQ_MODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,HBN_REG_EN_HW_PU_PD);
    BL_WR_REG(HBN_BASE,HBN_IRQ_MODE,tmpVal);

    GLB_Set_EM_Sel(GLB_EM_0KB);

    /* Fix 26M xtal clkpll_sdmin */
    tmpVal=BL_RD_REG(PDS_BASE,PDS_CLKPLL_SDM);
    if(0x49D39D==BL_GET_REG_BITS_VAL(tmpVal,PDS_CLKPLL_SDMIN)){
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CLKPLL_SDMIN,0x49D89E);
        BL_WR_REG(PDS_BASE,PDS_CLKPLL_SDM,tmpVal);
    }

    /* Restore default setting*/
    GLB_UART_Sig_Swap_Set(UART_SIG_SWAP_NONE);
    GLB_JTAG_Sig_Swap_Set(JTAG_SIG_SWAP_NONE);

    /* CLear all interrupt */
    p=(uint32_t *)(CLIC_HART0_ADDR+CLIC_INTIE);
    for(i=0;i<(IRQn_LAST+3)/4;i++){
        p[i]=0;
    }
    p=(uint32_t *)(CLIC_HART0_ADDR+CLIC_INTIP);
    for(i=0;i<(IRQn_LAST+3)/4;i++){
        p[i]=0;
    }
#endif

    /* init bor for all platform */
    system_bor_init();

#ifdef BOOTROM
    /*Power up soc 11 power domain,TODO: This should be optional */
    //AON_Power_On_SOC_11();
    /* Record LDO18 pu flag before power up. This maybe not neccessary but copy from 606*/
    //BL_WR_WORD(BFLB_BOOTROM_AP_BOOT_LOG_ADDR,GLB->ldo18io.BF.pu_ldo18io);
    /* Power up flash power*/
    //GLB_Power_On_LDO18_IO();
#endif

}

void board_init(void)
{
    System_Interrupt_Init();

    /* global IRQ enable */
    __enable_irq();
}

int32_t drv_get_cpu_id(void)
{
    return __get_MHARTID();
}

int32_t drv_get_cpu_freq(int32_t idx)
{
    return g_system_clock;
}

#if defined(DUAL_CORE)
extern void Reset_Handler(void);
void D0_wakeup_D1(void)
{
	GLB_Halt_CPU(GLB_CORE_ID_D1);
    GLB_Set_CPU_Reset_Address(GLB_CORE_ID_D1, (uint32_t)(uintptr_t)Reset_Handler);
    GLB_Release_CPU(GLB_CORE_ID_D1);
}
#endif
