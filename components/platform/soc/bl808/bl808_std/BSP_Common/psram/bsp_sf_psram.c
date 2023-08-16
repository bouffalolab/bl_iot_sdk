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

#include "bsp_sf_psram.h"
#include "bflb_platform.h"
#include "bl702_psram.h"
#include "bl702_l1c.h"
#include "bl702_sec_eng.h"
#include "bl702_glb.h"

/* bsp sf psram private variables */

SPI_Psram_Cfg_Type apMemory1604 = {
    .readIdCmd = 0x9F,
    .readIdDmyClk = 0,
    .burstToggleCmd = 0xC0,
    .resetEnableCmd = 0x66,
    .resetCmd = 0x99,
    .enterQuadModeCmd = 0x35,
    .exitQuadModeCmd = 0xF5,
    .readRegCmd = 0xB5,
    .readRegDmyClk = 1,
    .writeRegCmd = 0xB1,
    .readCmd = 0x03,
    .readDmyClk = 0,
    .fReadCmd = 0x0B,
    .fReadDmyClk = 1,
    .fReadQuadCmd = 0xEB,
    .fReadQuadDmyClk = 3,
    .writeCmd = 0x02,
    .quadWriteCmd = 0x38,
    .pageSize = 512,
    .ctrlMode = PSRAM_SPI_CTRL_MODE,
    .driveStrength = PSRAM_DRIVE_STRENGTH_50_OHMS,
    .burstLength = PSRAM_BURST_LENGTH_512_BYTES,
};

SF_Ctrl_Cmds_Cfg cmdsCfg = {
    .cmdsEn = ENABLE,
    .burstToggleEn = ENABLE,
    .wrapModeEn = DISABLE,
    .wrapLen = SF_CTRL_WRAP_LEN_512,
};
SF_Ctrl_Psram_Cfg sfCtrlPsramCfg = {
    .owner = SF_CTRL_OWNER_SAHB,
    .padSel = SF_CTRL_PAD_SEL_DUAL_CS_SF2,
    .bankSel = SF_CTRL_SEL_PSRAM,
    .psramRxClkInvertSrc = ENABLE,
    .psramRxClkInvertSel = DISABLE,
    .psramDelaySrc = ENABLE,
    .psramClkDelay = 1,
};

/* bsp sf psram gpio init */
/**
 * @brief
 *
 * @return None
 *
 */
void ATTR_TCM_SECTION bsp_sf_psram_gpio_init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[7];
    uint8_t i = 0;

    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_UP;
    cfg.drive = 3;
    cfg.smtCtrl = 1;
    cfg.gpioFun = GPIO_FUN_FLASH_PSRAM;

    gpiopins[0] = BFLB_EXTPSRAM_CLK_GPIO;
    gpiopins[1] = BFLB_EXTPSRAM_CS_GPIO;
    gpiopins[2] = BFLB_EXTPSRAM_DATA0_GPIO;
    gpiopins[3] = BFLB_EXTPSRAM_DATA1_GPIO;
    gpiopins[4] = BFLB_EXTPSRAM_DATA2_GPIO;
    gpiopins[5] = BFLB_EXTPSRAM_DATA3_GPIO;
    gpiopins[6] = BFLB_EXTFLASH_CS_GPIO;

    for (i = 0; i < sizeof(gpiopins); i++) {
        cfg.gpioPin = gpiopins[i];

        if (i == 0 || i == 1 || i == 6) {
            /*flash clk and cs is output*/
            cfg.gpioMode = GPIO_MODE_OUTPUT;
        } else {
            /*data are bidir*/
            cfg.gpioMode = GPIO_MODE_AF;
        }

        GLB_GPIO_Init(&cfg);
    }
}

/* bsp sf psram init */
/**
 * @brief
 *
 * @param sw_reset
 *
 * @return None
 *
 */
void ATTR_TCM_SECTION bsp_sf_psram_init(uint8_t sw_reset)
{
    uint8_t psramId[8] = { 0 };
    bsp_sf_psram_gpio_init();

    Psram_Init(&apMemory1604, &cmdsCfg, &sfCtrlPsramCfg);

    if (sw_reset) {
        Psram_SoftwareReset(&apMemory1604, apMemory1604.ctrlMode);
    }

    Psram_ReadId(&apMemory1604, psramId);
    Psram_Cache_Write_Set(&apMemory1604, SF_CTRL_QIO_MODE, ENABLE, DISABLE, DISABLE);
    L1C_Cache_Enable_Set(L1C_WAY_DISABLE_NONE);
}

void ATTR_TCM_SECTION bsp_sf_psram_read_id(uint8_t *data)
{
    Psram_ReadId(&apMemory1604, data);
}
