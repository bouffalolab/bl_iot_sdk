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
#include "bl_pds.h"
#include "bl_irq.h"
#include "bl_flash.h"


typedef __PACKED_STRUCT
{
    uint8_t xtal_type;
    uint8_t pll_clk;
    uint8_t hclk_div;
    uint8_t bclk_div;
    
    uint8_t flash_clk_type;
    uint8_t flash_clk_div;
    uint8_t rsvd[2];
}sys_clk_cfg_t;


#define CLK_CFG_OFFSET             (8+(4+sizeof(SPI_Flash_Cfg_Type)+4)+4)


#if !(defined(CFG_BLE_PDS) || defined(CFG_ZIGBEE_PDS))
/* PDS0 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel0 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 1,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 3,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 0,
        .BzIsoEn                 = 0,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 0,
        .MiscIsoEn               = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 0,
        .cpuRst                  = 0,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 0,
        .BzRst                   = 0,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 0,
        .UsbRst                  = 0,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 0,
        .MiscRst                 = 0,
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};

/* PDS1 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel1 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 1,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 3,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 0,
        .BzIsoEn                 = 0,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 1,
        .MiscIsoEn               = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 0,
        .cpuRst                  = 0,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 0,
        .BzRst                   = 0,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 1,
        .UsbRst                  = 1,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 0,
        .MiscRst                 = 0,
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};

/* PDS2 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel2 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 1,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 2,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 0,
        .BzIsoEn                 = 1,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 0,
        .MiscIsoEn               = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 0,
        .cpuRst                  = 0,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 1,
        .BzRst                   = 1,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 0,
        .UsbRst                  = 0,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 0,
        .MiscRst                 = 0,
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};

/* PDS3 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel3 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 1,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 2,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 0,
        .BzIsoEn                 = 1,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 1,
        .MiscIsoEn               = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 0,
        .cpuRst                  = 0,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 1,
        .BzRst                   = 1,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 1,
        .UsbRst                  = 1,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 0,
        .MiscRst                 = 0,
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};

/* PDS4 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel4 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 1,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 3,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 1,
        .BzIsoEn                 = 0,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 0,
        .MiscIsoEn               = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 1,
        .cpuRst                  = 1,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 0,
        .BzRst                   = 0,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 0,
        .UsbRst                  = 0,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 0,
        .MiscRst                 = 1,  // reset misc if bootrom_protect = 1
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};

/* PDS5 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel5 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 1,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 3,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 1,
        .BzIsoEn                 = 0,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 1,
        .MiscIsoEn               = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 1,
        .cpuRst                  = 1,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 0,
        .BzRst                   = 0,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 1,
        .UsbRst                  = 1,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 0,
        .MiscRst                 = 1,  // reset misc if bootrom_protect = 1
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};

/* PDS6 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel6 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 1,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 2,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 1,
        .BzIsoEn                 = 1,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 0,
        .MiscIsoEn               = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 1,
        .cpuRst                  = 1,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 1,
        .BzRst                   = 1,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 0,
        .UsbRst                  = 0,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 0,
        .MiscRst                 = 1,  // reset misc if bootrom_protect = 1
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};

/* PDS7 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel7 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 1,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 2,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 1,
        .BzIsoEn                 = 1,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 1,
        .MiscIsoEn               = 0,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 1,
        .cpuRst                  = 1,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 1,
        .BzRst                   = 1,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 1,
        .UsbRst                  = 1,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 0,
        .MiscRst                 = 1,  // reset misc if bootrom_protect = 1
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};
#endif

/* PDS31 Configuration */
static const PDS_DEFAULT_LV_CFG_Type pdsCfgLevel31 = {
    .pdsCtl = {
        .pdsStart                = 1,
        .sleepForever            = 0,
        .xtalForceOff            = 0,
        .saveWifiState           = 0,
        .dcdc18Off               = 1,
        .bgSysOff                = 1,
        .gpioIePuPd              = 1,
        .puFlash                 = 0,
        .clkOff                  = 1,
        .memStby                 = 1,
        .swPuFlash               = 1,
        .isolation               = 1,
        .waitXtalRdy             = 0,
        .pdsPwrOff               = 1,
        .xtalOff                 = 1,
        .socEnbForceOn           = 0,
        .pdsRstSocEn             = 0,
        .pdsRC32mOn              = 0,
        .pdsLdoVselEn            = 0,
        .pdsRamLowPowerWithClkEn = 1,
        .cpu0WfiMask             = 0,
        .ldo11Off                = 1,
        .pdsForceRamClkEn        = 0,
        .pdsLdoVol               = 0xA,
        .pdsCtlRfSel             = 2,
        .pdsCtlPllSel            = 0,
    },
    .pdsCtl2 = {
        .forceCpuPwrOff          = 0,
        .forceBzPwrOff           = 0,
        .forceUsbPwrOff          = 0,
        .forceCpuIsoEn           = 0,
        .forceBzIsoEn            = 0,
        .forceUsbIsoEn           = 0,
        .forceCpuPdsRst          = 0,
        .forceBzPdsRst           = 0,
        .forceUsbPdsRst          = 0,
        .forceCpuMemStby         = 0,
        .forceBzMemStby          = 0,
        .forceUsbMemStby         = 0,
        .forceCpuGateClk         = 0,
        .forceBzGateClk          = 0,
        .forceUsbGateClk         = 0,
    },
    .pdsCtl3 = {
        .forceMiscPwrOff         = 0,
        .forceBlePwrOff          = 0,
        .forceBleIsoEn           = 0,
        .forceMiscPdsRst         = 0,
        .forceBlePdsRst          = 0,
        .forceMiscMemStby        = 0,
        .forceBleMemStby         = 0,
        .forceMiscGateClk        = 0,
        .forceBleGateClk         = 0,
        .CpuIsoEn                = 1,
        .BzIsoEn                 = 1,
        .BleIsoEn                = 1,
        .UsbIsoEn                = 1,
        .MiscIsoEn               = 1,
    },
    .pdsCtl4 = {
        .cpuPwrOff               = 1,
        .cpuRst                  = 1,
        .cpuMemStby              = 1,
        .cpuGateClk              = 1,
        .BzPwrOff                = 1,
        .BzRst                   = 1,
        .BzMemStby               = 1,
        .BzGateClk               = 1,
        .BlePwrOff               = 1,
        .BleRst                  = 1,
        .BleMemStby              = 1,
        .BleGateClk              = 1,
        .UsbPwrOff               = 1,
        .UsbRst                  = 1,
        .UsbMemStby              = 1,
        .UsbGateClk              = 1,
        .MiscPwrOff              = 1,
        .MiscRst                 = 1,
        .MiscMemStby             = 1,
        .MiscGateClk             = 1,
        .MiscAnaPwrOff           = 1,
        .MiscDigPwrOff           = 1,
    }
};

/* Cache Way Disable, will get from l1c register */
static uint8_t cacheWayDisable;

/* PSRAM IO Configuration, will get from glb register */
static uint32_t psramIoCfg;

/* EM Select, will get from glb register */
static uint32_t emSel;

/* Device Information, will get from efuse */
static Efuse_Device_Info_Type devInfo;

/* Clock Configuration, will get from bootheader */
static sys_clk_cfg_t clkCfg;

/* Flash Configuration Pointer, will get from bl_flash_get_flashCfg() */
static SPI_Flash_Cfg_Type *flashCfgPtr;

/* Flash Image Offset, will get from SF_Ctrl_Get_Flash_Image_Offset() */
static uint32_t flashImageOffset;

/* SF Control Configuration, will set based on flash configuration */
static SF_Ctrl_Cfg_Type sfCtrlCfg;


static void bl_pds_set_sf_ctrl(SPI_Flash_Cfg_Type *pFlashCfg)
{
    uint8_t index;
    uint8_t delay[8] = {0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe};
    
    sfCtrlCfg.owner = SF_CTRL_OWNER_SAHB;
    
    /* bit0-3 for clk delay */
    sfCtrlCfg.clkDelay = pFlashCfg->clkDelay&0x0f;
    
    /* bit4-6 for do delay */
    index = (pFlashCfg->clkDelay>>4)&0x07;
    sfCtrlCfg.doDelay = delay[index];
    
    /* bit0 for clk invert */
    sfCtrlCfg.clkInvert = pFlashCfg->clkInvert&0x01;
    
    /* bit1 for rx clk invert */
    sfCtrlCfg.rxClkInvert=(pFlashCfg->clkInvert>>1)&0x01;
    
    /* bit2-4 for di delay */
    index = (pFlashCfg->clkInvert>>2)&0x07;
    sfCtrlCfg.diDelay = delay[index];
    
    /* bit5-7 for oe delay */
    index = (pFlashCfg->clkInvert>>5)&0x07;
    sfCtrlCfg.oeDelay = delay[index];
}


void bl_pds_init(void)
{
    // Get cache way disable setting
    cacheWayDisable = (*(volatile uint32_t *)(L1C_BASE + 0x00) >> 8) & 0x0F;
    
    // Get psram io configuration
    psramIoCfg = *(volatile uint32_t *)(GLB_BASE + 0x88);
    
    // Get em select
    emSel = *(volatile uint32_t *)(GLB_BASE + 0x7C);
    
    // Get device information from efuse
    EF_Ctrl_Read_Device_Info(&devInfo);
    devInfo.flash_cfg &= 0x03;
    
    // Get clock configuration from bootheader
    bl_flash_read_need_lock(CLK_CFG_OFFSET, (uint8_t *)(&clkCfg), sizeof(sys_clk_cfg_t));
    
    // Get flash configuration pointer
    flashCfgPtr = (SPI_Flash_Cfg_Type *)bl_flash_get_flashCfg();
    
    // Get flash image offset
    flashImageOffset = SF_Ctrl_Get_Flash_Image_Offset();
    
    // Set SF control configuration
    bl_pds_set_sf_ctrl(flashCfgPtr);
    
    // Select XTAL32K (XTAL32K is default on)
#ifdef CFG_USE_XTAL32K
    HBN_32K_Sel(HBN_32K_XTAL);
#else
    HBN_32K_Sel(HBN_32K_RC);
#endif
    
    // Disable GPIO9 pull up/down to reduce PDS current, 0x4000F014[16]=0
    HBN_Hw_Pu_Pd_Cfg(DISABLE);
    
    // Disable GPIO9 - GPIO13 IE/SMT, 0x4000F014[12:8]=5'b00000
    HBN_Aon_Pad_IeSmt_Cfg(0);
    
    // Disable GPIO9 - GPIO13 wakeup, 0x4000F014[7:3]=5'b11111
    HBN_Pin_WakeUp_Mask(0x1F);
    
    // Configure PDS_SLEEP_CNT as wakeup source
    PDS_IntEn(PDS_INT_PDS_SLEEP_CNT, ENABLE);
    PDS_IntEn(PDS_INT_HBN_IRQ_OUT0, DISABLE);
    PDS_IntEn(PDS_INT_HBN_IRQ_OUT1, DISABLE);
    PDS_IntEn(PDS_INT_GPIO_IRQ, DISABLE);
    PDS_IntEn(PDS_INT_IRRX, DISABLE);
    PDS_IntEn(PDS_INT_BLE_SLP_IRQ, DISABLE);
    PDS_IntEn(PDS_INT_USB_WKUP, DISABLE);
    PDS_IntEn(PDS_INT_KYS_QDEC, DISABLE);
}

void bl_pds_fastboot_cfg(uint32_t addr)
{
    HBN_Set_Wakeup_Addr(addr);
    HBN_Set_Status_Flag(HBN_STATUS_ENTER_FLAG);
}


// must be placed in pds section
static void ATTR_PDS_SECTION bl_pds_restore_flash(SPI_Flash_Cfg_Type *pFlashCfg)
{
    uint32_t tmp[1];
    
    *(volatile uint32_t *)0x4000E030 = 0;
    
    RomDriver_SF_Cfg_Init_Flash_Gpio((devInfo.flash_cfg<<2)|devInfo.sf_swap_cfg, 1);
    
    RomDriver_SFlash_Init(&sfCtrlCfg);
    
    RomDriver_SFlash_Releae_Powerdown(pFlashCfg);
    
    RomDriver_SFlash_Reset_Continue_Read(pFlashCfg);
    
    RomDriver_SFlash_Software_Reset(pFlashCfg);
    
    RomDriver_SFlash_Write_Enable(pFlashCfg);
    
    RomDriver_SFlash_DisableBurstWrap(pFlashCfg);
    
    RomDriver_SFlash_SetSPIMode(SF_CTRL_SPI_MODE);
    
    RomDriver_SF_Ctrl_Set_Flash_Image_Offset(0);
    
    if((pFlashCfg->ioMode&0x0f)==SF_CTRL_QO_MODE||(pFlashCfg->ioMode&0x0f)==SF_CTRL_QIO_MODE){
        RomDriver_SFlash_Qspi_Enable(pFlashCfg);
    }
    
    if(((pFlashCfg->ioMode>>4)&0x01)==1){
        RomDriver_L1C_Set_Wrap(DISABLE);
    }else{
        RomDriver_L1C_Set_Wrap(ENABLE);
        RomDriver_SFlash_Write_Enable(pFlashCfg);
        RomDriver_SFlash_SetBurstWrap(pFlashCfg);
    }
    
    if(pFlashCfg->cReadSupport){
        RomDriver_SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);
        RomDriver_SFlash_Read(pFlashCfg, pFlashCfg->ioMode&0xf, 1, 0x00000000, (uint8_t *)tmp, sizeof(tmp));
    }
    
    RomDriver_SF_Ctrl_Set_Flash_Image_Offset(flashImageOffset);
    RomDriver_SFlash_Cache_Read_Enable(pFlashCfg, pFlashCfg->ioMode&0xf, pFlashCfg->cReadSupport, cacheWayDisable);
}

// can be placed in flash, here placed in pds section to reduce fast boot time
static void ATTR_NOINLINE ATTR_PDS_SECTION bl_pds_restore_tcm(void)
{
    extern uint8_t _tcm_load;
    extern uint8_t _tcm_run;
    extern uint8_t _tcm_run_end;
    uint32_t src = (uint32_t)&_tcm_load;
    uint32_t dst = (uint32_t)&_tcm_run;
    uint32_t end = (uint32_t)&_tcm_run_end;
    
    while(dst < end){
        *(uint32_t *)dst = *(uint32_t *)src;
        src += 4;
        dst += 4;
    }
}

// can be placed in flash, here placed in pds section to reduce fast boot time
static void ATTR_NOINLINE ATTR_PDS_SECTION bl_pds_restore_cpu_reg(void)
{
    __asm__ __volatile__(
            "la     a2,     __ld_pds_bak_addr\n\t"
            "lw     ra,     0(a2)\n\t"
            "lw     sp,     1*4(a2)\n\t"
            "lw     tp,     2*4(a2)\n\t"
            "lw     t0,     3*4(a2)\n\t"
            "lw     t1,     4*4(a2)\n\t"
            "lw     t2,     5*4(a2)\n\t"
            "lw     fp,     6*4(a2)\n\t"
            "lw     s1,     7*4(a2)\n\t"
            "lw     a0,     8*4(a2)\n\t"
            "lw     a1,     9*4(a2)\n\t"
            "lw     a3,     10*4(a2)\n\t"
            "lw     a4,     11*4(a2)\n\t"
            "lw     a5,     12*4(a2)\n\t"
            "lw     a6,     13*4(a2)\n\t"
            "lw     a7,     14*4(a2)\n\t"
            "lw     s2,     15*4(a2)\n\t"
            "lw     s3,     16*4(a2)\n\t"
            "lw     s4,     17*4(a2)\n\t"
            "lw     s5,     18*4(a2)\n\t"
            "lw     s6,     19*4(a2)\n\t"
            "lw     s7,     20*4(a2)\n\t"
            "lw     s8,     21*4(a2)\n\t"
            "lw     s9,     22*4(a2)\n\t"
            "lw     s10,    23*4(a2)\n\t"
            "lw     s11,    24*4(a2)\n\t"
            "lw     t3,     25*4(a2)\n\t"
            "lw     t4,     26*4(a2)\n\t"
            "lw     t5,     27*4(a2)\n\t"
            "lw     t6,     28*4(a2)\n\t"
            "csrw   mtvec,  a0\n\t"
            "csrw   mstatus,a1\n\t"
            "ret\n\t"
    );
}

#define FAST_BOOT_TEST        0
#define FAST_RESTORE          0

// must be placed in pds section
static void ATTR_PDS_SECTION bl_pds_fastboot_entry(void)
{
#if FAST_BOOT_TEST == 1 || FAST_BOOT_TEST == 2
    GLB_GPIO_Cfg_Type gpioCfg;
    GLB_GPIO_Type gpioPin=31;
    uint32_t *pOut=(uint32_t *)(GLB_BASE+GLB_GPIO_OUTPUT_OFFSET+((gpioPin>>5)<<2));
    uint32_t pos=gpioPin%32;
    
    gpioCfg.gpioPin=gpioPin;
    gpioCfg.gpioFun=11;
    gpioCfg.gpioMode=GPIO_MODE_OUTPUT;
    gpioCfg.pullType=GPIO_PULL_NONE;
    gpioCfg.drive=0;
    gpioCfg.smtCtrl=1;
    RomDriver_GLB_GPIO_Init(&gpioCfg);
#endif
    
#if FAST_BOOT_TEST == 1
    while(1){
        *pOut |= (1<<pos);
        RomDriver_BL702_Delay_MS(100);
        *pOut &= ~(1<<pos);
        RomDriver_BL702_Delay_MS(100);
    }
#endif
    
    __asm__ __volatile__(
            "la gp, __global_pointer$\n\t"
    );
    
#if FAST_BOOT_TEST == 2
    *pOut |= (1<<pos);
    RomDriver_BL702_Delay_US(1);
    *pOut &= ~(1<<pos);
#endif
    
    // Configure clock (must use rom driver, since tcm code is lost and flash is power down)
#if FAST_RESTORE == 1
    RomDriver_GLB_Set_System_CLK(GLB_DLL_XTAL_32M, GLB_SYS_CLK_DLL144M);
    RomDriver_GLB_Set_SF_CLK(1, GLB_SFLASH_CLK_96M, 0);
#else
    RomDriver_GLB_Set_System_CLK(clkCfg.xtal_type, clkCfg.pll_clk);
    RomDriver_GLB_Set_System_CLK_Div(clkCfg.hclk_div, clkCfg.bclk_div);
    RomDriver_GLB_Set_SF_CLK(1, clkCfg.flash_clk_type, clkCfg.flash_clk_div);
#endif
    
#if FAST_BOOT_TEST == 2
    *pOut |= (1<<pos);
    RomDriver_BL702_Delay_US(1);
    *pOut &= ~(1<<pos);
#endif
    
    // Configure flash (must use rom driver, since tcm code is lost and flash is power down)
    bl_pds_restore_flash(flashCfgPtr);
    
#if FAST_BOOT_TEST == 2
    *pOut |= (1<<pos);
    RomDriver_BL702_Delay_US(1);
    *pOut &= ~(1<<pos);
#endif
    
    // Restore tcm code
    bl_pds_restore_tcm();
    
#if FAST_BOOT_TEST == 2
    *pOut |= (1<<pos);
    RomDriver_BL702_Delay_US(1);
    *pOut &= ~(1<<pos);
#endif
    
#if FAST_RESTORE == 1
    // Restore clock
    RomDriver_GLB_Set_System_CLK(clkCfg.xtal_type, clkCfg.pll_clk);
    RomDriver_GLB_Set_System_CLK_Div(clkCfg.hclk_div, clkCfg.bclk_div);
    RomDriver_GLB_Set_SF_CLK(1, clkCfg.flash_clk_type, clkCfg.flash_clk_div);
    
#if FAST_BOOT_TEST == 2
    *pOut |= (1<<pos);
    RomDriver_BL702_Delay_US(1);
    *pOut &= ~(1<<pos);
#endif
#endif
    
#if FAST_BOOT_TEST == 3
    ((void (*)(void))0x23000000)();
#endif
    
    // Patch: restore psram io configuration
    *(volatile uint32_t *)(GLB_BASE + 0x88) = psramIoCfg;
    
    // Restore em select
    *(volatile uint32_t *)(GLB_BASE + 0x7C) = emSel;
    
    // Restore cpu registers
    bl_pds_restore_cpu_reg();
}

static void bl_pds_IRQHandler(void)
{
    PDS_IntClear();
}

// can be placed in flash, here placed in pds section to reduce fast boot time
static void ATTR_NOINLINE ATTR_PDS_SECTION bl_pds_set_gpio_high_z(void)
{
    uint32_t pin;
    
    // Set all gpio pads in High-Z state (GPIO0 - GPIO22, jtag & uart pads excluded)
    for(pin=0; pin<=22; pin++){
        if(pin == 0 || pin == 1 || pin == 2 || pin == 9){
            continue;
        }
        if(pin == 14 || pin == 15){
            continue;
        }
        GLB_GPIO_Set_HZ(pin);
    }
    
    // Set all psram pads in High-Z state
    GLB_Set_Psram_Pad_HZ();
}

// can be placed in flash, here placed in pds section to reduce fast boot time
static int ATTR_NOINLINE ATTR_PDS_SECTION bl_pds_pre_process_1(uint32_t pdsLevel, PDS_DEFAULT_LV_CFG_Type *pdsCfg, uint32_t *pdFlash, uint32_t *store)
{
    if(pdsLevel == 31){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel31, sizeof(PDS_DEFAULT_LV_CFG_Type));
#if !(defined(CFG_BLE_PDS) || defined(CFG_ZIGBEE_PDS))
    }else if(pdsLevel == 0){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel0, sizeof(PDS_DEFAULT_LV_CFG_Type));
    }else if(pdsLevel == 1){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel1, sizeof(PDS_DEFAULT_LV_CFG_Type));
    }else if(pdsLevel == 2){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel2, sizeof(PDS_DEFAULT_LV_CFG_Type));
    }else if(pdsLevel == 3){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel3, sizeof(PDS_DEFAULT_LV_CFG_Type));
    }else if(pdsLevel == 4){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel4, sizeof(PDS_DEFAULT_LV_CFG_Type));
    }else if(pdsLevel == 5){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel5, sizeof(PDS_DEFAULT_LV_CFG_Type));
    }else if(pdsLevel == 6){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel6, sizeof(PDS_DEFAULT_LV_CFG_Type));
    }else if(pdsLevel == 7){
        ARCH_MemCpy_Fast(pdsCfg, &pdsCfgLevel7, sizeof(PDS_DEFAULT_LV_CFG_Type));
#endif
    }else{
        return -1;
    }
    
    if(pdsLevel == 31){
        HBN_Set_Ldo11rt_Drive_Strength(HBN_LDO11RT_DRIVE_STRENGTH_10_100UA);
    }else{
        HBN_Set_Ldo11rt_Drive_Strength(HBN_LDO11RT_DRIVE_STRENGTH_25_250UA);
    }
    
    if(devInfo.flash_cfg == 1 || devInfo.flash_cfg == 2){
        pdsCfg->pdsCtl.puFlash = 1;
        pdsCfg->pdsCtl.swPuFlash = 1;
        
        if(pdsLevel == 31){
            *pdFlash = 1;
        }else{
            *pdFlash = 0;
        }
    }else{
        *pdFlash = 1;
    }
    
    if(pdsLevel >= 4 && HBN_Get_Status_Flag() != HBN_STATUS_ENTER_FLAG){
        HBN_Set_Wakeup_Addr((uint32_t)bl_pds_fastboot_entry);
        HBN_Set_Status_Flag(HBN_STATUS_ENTER_FLAG);
        *store = 1;
    }else{
        *store = 0;
    }
    
    if(pdsCfg->pdsCtl.cpu0WfiMask == 0){
        PDS_IntMask(PDS_INT_WAKEUP, UNMASK);
        PDS_IntMask(PDS_INT_RF_DONE, MASK);
        PDS_IntMask(PDS_INT_PLL_DONE, MASK);
        PDS_IntClear();
        
        bl_irq_register(PDS_WAKEUP_IRQn, bl_pds_IRQHandler);
        bl_irq_enable(PDS_WAKEUP_IRQn);
    }
    
    // Disable global interrupt
    __disable_irq();
    
#if 0
    // Disable GPIO9 pull up/down to reduce PDS current, 0x4000F014[16]=0
    HBN_Hw_Pu_Pd_Cfg(DISABLE);
    
    // Disable GPIO9 - GPIO13 IE/SMT, 0x4000F014[12:8]=5'b00000
    HBN_Aon_Pad_IeSmt_Cfg(0);
    
    // Disable GPIO9 - GPIO13 wakeup, 0x4000F014[7:3]=5'b11111
    HBN_Pin_WakeUp_Mask(0x1F);
#endif
    
#if !(defined(CFG_BLE_PDS) || defined(CFG_ZIGBEE_PDS))
    bl_pds_set_gpio_high_z();
#endif
    
    return 0;
}

// can be placed in tcm section, here placed in pds section to reduce fast boot time
static void ATTR_NOINLINE ATTR_PDS_SECTION bl_pds_pre_process_2(uint32_t pdFlash)
{
    // Power down flash
    if(pdFlash){
        SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);
        SFlash_Reset_Continue_Read(flashCfgPtr);
        SFlash_Powerdown();
    }
    
    // Pull up flash pads
    if(devInfo.flash_cfg == 0){
        // External SF2 (GPIO23 - GPIO28)
        *(volatile uint32_t *)0x4000E030 = (0x1F << 24);  // As boot pin, GPIO28 should not be pulled up
    }else if(devInfo.flash_cfg == 3){
        // External SF1 (GPIO17 - GPIO22)
        *(volatile uint32_t *)0x4000E030 = (0x3F << 8);
    }else{
        // Internal SF2 (GPIO23 - GPIO28)
        // Do nothing
    }
    
    // Set all flash pads in High-Z state
    if(pdFlash){
        GLB_Set_Flash_Pad_HZ();
    }
    
    // Select RC32M
    HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_RC32M);
    GLB_Power_Off_DLL();
    AON_Power_Off_XTAL();
}

// can be placed in tcm section, here placed in pds section to reduce fast boot time
static void ATTR_NOINLINE ATTR_PDS_SECTION bl_pds_enter_do(PDS_DEFAULT_LV_CFG_Type *pdsCfg, uint32_t pdsSleepCycles, uint32_t store)
{
    if(store){
        __asm__ __volatile__(
            "la     a2,     __ld_pds_bak_addr\n\t"
            "sw     ra,     0(a2)\n\t"
        );
    }
    
    PDS_Default_Level_Config(pdsCfg, pdsSleepCycles);
    if(pdsCfg->pdsCtl.cpu0WfiMask == 0){
        __WFI();
    }
}

// can be placed in tcm section, here placed in pds section to reduce fast boot time
static void ATTR_NOINLINE ATTR_PDS_SECTION bl_pds_post_process_1(uint32_t pdsLevel, uint32_t pdFlash)
{
#if !(defined(CFG_BLE_PDS) || defined(CFG_ZIGBEE_PDS))
    // For pdsLevel >=4, clock and flash will be configured in fast boot entry
    if(pdsLevel < 4){
        // Select DLL or XTAL32M
        AON_Power_On_XTAL();
        GLB_Power_On_DLL(GLB_DLL_XTAL_32M);
        if(clkCfg.pll_clk >= 2){
            HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_DLL);
        }else{
            HBN_Set_ROOT_CLK_Sel(HBN_ROOT_CLK_XTAL);
        }
        
        // Clear flash pads pull configuration
        *(volatile uint32_t *)0x4000E030 = 0;
        
        // Power up flash
        if(pdFlash){
            SF_Cfg_Init_Flash_Gpio((devInfo.flash_cfg<<2)|devInfo.sf_swap_cfg, 1);
            SF_Ctrl_Set_Owner(SF_CTRL_OWNER_SAHB);
            SFlash_Restore_From_Powerdown(flashCfgPtr, flashCfgPtr->cReadSupport);
        }
    }
#endif
}

// can be placed in flash, here placed in pds section to reduce fast boot time
static void ATTR_NOINLINE ATTR_PDS_SECTION bl_pds_post_process_2(void)
{
#if (defined(CFG_BLE_PDS) || defined(CFG_ZIGBEE_PDS))
    bl_pds_set_gpio_high_z();
#endif
    
#if 0
    // Enable GPIO9 pull up/down, 0x4000F014[16]=1
    HBN_Hw_Pu_Pd_Cfg(ENABLE);
    
    // Enable GPIO9 - GPIO13 IE/SMT, 0x4000F014[12:8]=5'b11111
    HBN_Aon_Pad_IeSmt_Cfg(0x1F);
    
    // Enable GPIO9 - GPIO13 wakeup, 0x4000F014[7:3]=5'b00000
    HBN_Pin_WakeUp_Mask(0);
#endif
    
    // Enable global interrupt
    __enable_irq();
}


// can be placed in tcm section, here placed in pds section to reduce fast boot time
void ATTR_PDS_SECTION bl_pds_enter(uint32_t pdsLevel, uint32_t pdsSleepCycles)
{
    PDS_DEFAULT_LV_CFG_Type pdsCfg;
    uint32_t pdFlash;
    uint32_t store;
    
    // Pre-process
    if(bl_pds_pre_process_1(pdsLevel, &pdsCfg, &pdFlash, &store) != 0){
        return;
    }
    bl_pds_pre_process_2(pdFlash);
    
    // Store cpu registers except for ra
    if(store){
        __asm__ __volatile__(
            "csrr   a0,     mtvec\n\t"
            "csrr   a1,     mstatus\n\t"
            "la     a2,     __ld_pds_bak_addr\n\t"
            "sw     sp,     1*4(a2)\n\t"
            "sw     tp,     2*4(a2)\n\t"
            "sw     t0,     3*4(a2)\n\t"
            "sw     t1,     4*4(a2)\n\t"
            "sw     t2,     5*4(a2)\n\t"
            "sw     fp,     6*4(a2)\n\t"
            "sw     s1,     7*4(a2)\n\t"
            "sw     a0,     8*4(a2)\n\t"
            "sw     a1,     9*4(a2)\n\t"
            "sw     a3,     10*4(a2)\n\t"
            "sw     a4,     11*4(a2)\n\t"
            "sw     a5,     12*4(a2)\n\t"
            "sw     a6,     13*4(a2)\n\t"
            "sw     a7,     14*4(a2)\n\t"
            "sw     s2,     15*4(a2)\n\t"
            "sw     s3,     16*4(a2)\n\t"
            "sw     s4,     17*4(a2)\n\t"
            "sw     s5,     18*4(a2)\n\t"
            "sw     s6,     19*4(a2)\n\t"
            "sw     s7,     20*4(a2)\n\t"
            "sw     s8,     21*4(a2)\n\t"
            "sw     s9,     22*4(a2)\n\t"
            "sw     s10,    23*4(a2)\n\t"
            "sw     s11,    24*4(a2)\n\t"
            "sw     t3,     25*4(a2)\n\t"
            "sw     t4,     26*4(a2)\n\t"
            "sw     t5,     27*4(a2)\n\t"
            "sw     t6,     28*4(a2)\n\t"
        );
    }
    
    // Enter PDS
    bl_pds_enter_do(&pdsCfg, pdsSleepCycles, store);
    
    // Post-process
    bl_pds_post_process_1(pdsLevel, pdFlash);
    bl_pds_post_process_2();
}
