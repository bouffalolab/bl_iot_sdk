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

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <bl702_hbn.h>
#include <bl702_glb.h>
#include <bl_hbn.h>
#include <bl_gpio.h>
#include <bl_flash.h>
#include <utils_log.h>

int bl_hbn_enter(hbn_type_t *hbn, uint32_t *time)
{
#if 0
    SPI_Flash_Cfg_Type Gd_Q80E_Q16E = {
            .resetCreadCmd=0xff,
            .resetCreadCmdSize=3,
            .mid=0xc8,

            .deBurstWrapCmd=0x77,
            .deBurstWrapCmdDmyClk=0x3,
            .deBurstWrapDataMode=SF_CTRL_DATA_4_LINES,
            .deBurstWrapData=0xF0,

            /*reg*/
            .writeEnableCmd=0x06,
            .wrEnableIndex=0x00,
            .wrEnableBit=0x01,
            .wrEnableReadRegLen=0x01,

            .qeIndex=1,
            .qeBit=0x01,
            .qeWriteRegLen=0x02,
            .qeReadRegLen=0x1,

            .busyIndex=0,
            .busyBit=0x00,
            .busyReadRegLen=0x1,
            .releasePowerDown=0xab,

            .readRegCmd[0]=0x05,
            .readRegCmd[1]=0x35,
            .writeRegCmd[0]=0x01,
            .writeRegCmd[1]=0x01,

            .fastReadQioCmd=0xeb,
            .frQioDmyClk=16/8,
            .cReadSupport=1,
            .cReadMode=0xA0,

            .burstWrapCmd=0x77,
            .burstWrapCmdDmyClk=0x3,
            .burstWrapDataMode=SF_CTRL_DATA_4_LINES,
            .burstWrapData=0x40,
             /*erase*/
            .chipEraseCmd=0xc7,
            .sectorEraseCmd=0x20,
            .blk32EraseCmd=0x52,
            .blk64EraseCmd=0xd8,
            /*write*/
            .pageProgramCmd=0x02,
            .qpageProgramCmd=0x32,
            .qppAddrMode=SF_CTRL_ADDR_1_LINE,

            .ioMode=SF_CTRL_QIO_MODE,
            .clkDelay=1,
            .clkInvert=0x3f,

            .resetEnCmd=0x66,
            .resetCmd=0x99,
            .cRExit=0xff,
            .wrEnableWriteRegLen=0x00,

            /*id*/
            .jedecIdCmd=0x9f,
            .jedecIdCmdDmyClk=0,
            .qpiJedecIdCmd=0x9f,
            .qpiJedecIdCmdDmyClk=0x00,
            .sectorSize=4,
            .pageSize=256,

            /*read*/
            .fastReadCmd=0x0b,
            .frDmyClk=8/8,
            .qpiFastReadCmd =0x0b,
            .qpiFrDmyClk=8/8,
            .fastReadDoCmd=0x3b,
            .frDoDmyClk=8/8,
            .fastReadDioCmd=0xbb,
            .frDioDmyClk=0,
            .fastReadQoCmd=0x6b,
            .frQoDmyClk=8/8,

            .qpiFastReadQioCmd=0xeb,
            .qpiFrQioDmyClk=16/8,
            .qpiPageProgramCmd=0x02,
            .writeVregEnableCmd=0x50,

            /* qpi mode */
            .enterQpi=0x38,
            .exitQpi=0xff,

             /*AC*/
            .timeEsector=300,
            .timeE32k=1200,
            .timeE64k=1200,
            .timePagePgm=5,
            .timeCe=20*1000,
            .pdDelay=20,
            .qeData=0,
    };
#endif
    HBN_APP_CFG_Type cfg = {
        .useXtal32k =0,                                        /*!< Wheather use xtal 32K as 32K clock source,otherwise use rc32k */
        .sleepTime =0,                                         /*!< HBN sleep time */
        .gpioWakeupSrc=HBN_WAKEUP_GPIO_NONE,                   /*!< GPIO Wakeup source */
        .gpioTrigType=HBN_GPIO_INT_TRIGGER_ASYNC_FALLING_EDGE, /*!< GPIO Triger type */
        .flashCfg= NULL,                                      /*!< Flash config pointer, used when power down flash */
        .flashPinCfg=0,                                       /*!< 0 ext flash 23-28, 1 internal flash 23-28, 2 internal flash 23-28, 3 ext flash 17-22 */
        .hbnLevel=HBN_LEVEL_1,                                /*!< HBN level */
        .ldoLevel=HBN_LDO_LEVEL_1P10V,                        /*!< LDO level */
    };

    if (hbn) {
        printf("hbn.buflen = %d\r\n", hbn->buflen);
        printf("hbn.active = %d\r\n", hbn->active);
        log_buf(hbn->buf, hbn->buflen);
    }

    cfg.sleepTime = (*time << 15) / 1000;  // ms -> rtc cycles
    if ((!hbn->buf) || (hbn->buflen > 5)) {
        printf("not support arg.\r\n");
        return -1;
    }

    int i;
    for (i=0; i<hbn->buflen; i++) {
        if (hbn->buf[i] == 9) {
            cfg.gpioWakeupSrc |= HBN_WAKEUP_GPIO_9;
        } else if (hbn->buf[i] == 10) {
            cfg.gpioWakeupSrc |= HBN_WAKEUP_GPIO_10;
        } else if (hbn->buf[i] == 11) {
            cfg.gpioWakeupSrc |= HBN_WAKEUP_GPIO_11;
        } else if (hbn->buf[i] == 12) {
            cfg.gpioWakeupSrc |= HBN_WAKEUP_GPIO_12;
        } else if (hbn->buf[i] == 13) {
            cfg.gpioWakeupSrc |= HBN_WAKEUP_GPIO_13;
        } else {
            printf("invalid arg.\r\n");
            return -1;
        }
    }
    if (hbn->buflen > 0) {
        printf("hbn");
        for (i=0; i<hbn->buflen; i++) {
            printf(" gpio%d", hbn->buf[i]);
        }
        printf(".\r\n");
    }

    cfg.flashCfg = bl_flash_get_flashCfg();

    HBN_Mode_Enter(&cfg);
    return -1;
}

