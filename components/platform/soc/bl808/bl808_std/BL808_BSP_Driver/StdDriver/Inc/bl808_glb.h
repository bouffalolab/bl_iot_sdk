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
#ifndef __BL808_GLB_H__
#define __BL808_GLB_H__

#if (BL80X_HW_VER <= BL80X_HW_A0)
#include "mmsys_misc_reg_a0.h"
#else
#include "mmsys_misc_reg.h"
#endif
#include "clkrst_reg.h"
#include "bl808_common.h"
#include "bl808_glb_gpio.h"
#include "bl808_gpio.h"
#include "glb_reg.h"
#include "cci_reg.h"
#include "mm_glb_reg.h"
#include "pds_reg.h"
#include "bl808_gpio.h"
#include "bl808_hbn.h"
#include "bl808_sf_ctrl.h"
#include "bl808_sf_cfg.h"
#include "bl808_aon.h"
#include "bl808_ef_ctrl.h"
#include "bl808_pds.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GLB
 *  @{
 */

/** @defgroup  GLB_Public_Types
 *  @{
 */



/**
 *  @brief XTAL type definition
 */
typedef enum {
    GLB_XTAL_NONE,  /*!< XTAL is none */
    GLB_XTAL_24M,   /*!< XTAL is 24M */
    GLB_XTAL_32M,   /*!< XTAL is 32M */
    GLB_XTAL_38P4M, /*!< XTAL is 38.4M */
    GLB_XTAL_40M,   /*!< XTAL is 40M */
    GLB_XTAL_26M,   /*!< XTAL is 26M */
    GLB_XTAL_RC32M, /*!< XTAL is RC32M */
    GLB_XTAL_MAX,   /*!< type max num */
} GLB_XTAL_Type;


typedef struct {
    uint8_t clkpllRefdivRatio;  /*!< xxx pll_refdiv_ratio */
    uint8_t clkpllSelSampleClk; /*!< xxx pll_sel_sample_clk */
    uint8_t clkpllVcoSpeed;     /*!< xxx pll_vco_speed */
    uint8_t clkpllEvenDivEn;    /*!< xxx pll_even_div_en */
    uint8_t clkpllEvenDivRatio; /*!< xxx pll_even_div_ratio */
} GLB_MU_PLL_CFG_BASIC_Type;

typedef struct {
    const GLB_MU_PLL_CFG_BASIC_Type *const basicCfg; /*!< pll basic configuration */
    uint32_t clkpllSdmin;                            /*!< pll sdmin value */
} GLB_MU_PLL_Cfg_Type;


typedef struct {
    uint8_t clkpllRefdivRatio;  /*!< xxx pll_refdiv_ratio */
    uint8_t clkpllIntFracSw;    /*!< xxx pll_int_frac_sw */
    uint8_t clkpllIcp1u;        /*!< xxx pll_icp_1u */
    uint8_t clkpllIcp5u;        /*!< xxx pll_icp_5u */
    uint8_t clkpllRz;           /*!< xxx pll_rz */
    uint8_t clkpllCz;           /*!< xxx pll_cz */
    uint8_t clkpllC3;           /*!< xxx pll_c3 */
    uint8_t clkpllR4Short;      /*!< xxx pll_r4_short */
    uint8_t clkpllC4En;         /*!< xxx pll_r4_en */
    uint8_t clkpllSelSampleClk; /*!< xxx pll_sel_sample_clk */
    uint8_t clkpllVcoSpeed;     /*!< xxx pll_vco_speed */
    uint8_t clkpllSdmCtrlHw;    /*!< xxx pll_sdm_ctrl_hw */
    uint8_t clkpllSdmBypass;    /*!< xxx pll_sdm_bypass */
} GLB_WAC_PLL_CFG_BASIC_Type;

typedef struct {
    const GLB_WAC_PLL_CFG_BASIC_Type *const basicCfg; /*!< pll basic configuration */
    uint32_t clkpllSdmin;                             /*!< pll sdmin value */
} GLB_WAC_PLL_Cfg_Type;




/**
 *  @brief PLL power on type definition
 */
typedef enum {
    GLB_PLL_NONE = 0,    /*!< power on xtal and pll */
    GLB_PLL_WIFIPLL = 1, /*!< power on WIFIPLL */
    GLB_PLL_AUPLL = 2,   /*!< power on AUPLL */
    GLB_PLL_CPUPLL = 4,  /*!< power on CPUPLL */
    GLB_PLL_MIPIPLL = 8, /*!< power on ETHPLL */
    GLB_PLL_UHSPLL = 16, /*!< power on ETHPLL */
} GLB_PLL_Type;

/**
 *  @brief WAC PLL XTAL type definition
 */
typedef enum {
    GLB_WAC_PLL_WIFIPLL, /*!< wifi pll */
    GLB_WAC_PLL_AUPLL,   /*!< audio pll */
    GLB_WAC_PLL_CPUPLL,  /*!< cpu pll */
} GLB_WAC_PLL_Type;

/**
 *  @brief MU PLL XTAL type definition
 */
typedef enum {
    GLB_MU_PLL_MIPIPLL, /*!< mipi pll */
    GLB_MU_PLL_UHSPLL,  /*!< uhs pll */
} GLB_MU_PLL_Type;

/**
 *  @brief DISP clock type definition
 */
typedef enum {
    GLB_DISP_CLK_MIPIPLL_1500M, /*!< mipi pll 1500M */
} GLB_DISP_CLK_Type;


/** @defgroup  GLB_XTAL_TYPE
 *  @{
 */
#define IS_GLB_XTAL_TYPE(type) (((type) == GLB_XTAL_NONE) ||  \
                                ((type) == GLB_XTAL_24M) ||   \
                                ((type) == GLB_XTAL_32M) ||   \
                                ((type) == GLB_XTAL_38P4M) || \
                                ((type) == GLB_XTAL_40M) ||   \
                                ((type) == GLB_XTAL_26M) ||   \
                                ((type) == GLB_XTAL_RC32M) || \
                                ((type) == GLB_XTAL_MAX))

/** @defgroup  GLB_PLL_TYPE
 *  @{
 */
#define IS_GLB_PLL_TYPE(type) (((type) == GLB_PLL_NONE) ||    \
                               ((type) == GLB_PLL_WIFIPLL) || \
                               ((type) == GLB_PLL_AUPLL) ||   \
                               ((type) == GLB_PLL_CPUPLL) ||  \
                               ((type) == GLB_PLL_MIPIPLL) || \
                               ((type) == GLB_PLL_UHSPLL))

/**
 *  @brief GLB dsp system clock type definition
 */
typedef enum {
    GLB_PLL_REFCLK_XTAL = 0,  /*!< use XTAL as pll ref clock */
    GLB_PLL_REFCLK_RC32M = 3, /*!< use RC32M as pll ref clock */
} GLB_PLL_REF_CLK_Type;


/** @defgroup  GLB_DISP_CLK_TYPE
 *  @{
 */
#define IS_GLB_DISP_CLK_TYPE(type) (((type) == GLB_DISP_CLK_MIPIPLL_1500M))


/** @defgroup  GLB_PLL_REF_CLK_TYPE
 *  @{
 */
#define IS_GLB_PLL_REF_CLK_TYPE(type) (((type) == GLB_PLL_REFCLK_XTAL) || \
                                       ((type) == GLB_PLL_REFCLK_RC32M))

/** @defgroup  GLB_WAC_PLL_TYPE
 *  @{
 */
#define IS_GLB_WAC_PLL_TYPE(type) (((type) == GLB_WAC_PLL_WIFIPLL) || \
                                   ((type) == GLB_WAC_PLL_AUPLL) ||   \
                                   ((type) == GLB_WAC_PLL_CPUPLL))




/** @defgroup  GLB_MU_PLL_TYPE
 *  @{
 */
#define IS_GLB_MU_PLL_TYPE(type) (((type) == GLB_MU_PLL_MIPIPLL) || \
                                  ((type) == GLB_MU_PLL_UHSPLL))

/** @defgroup  GLB_DISP_CLK_TYPE
 *  @{
 */
#define IS_GLB_DISP_CLK_TYPE(type) (((type) == GLB_DISP_CLK_MIPIPLL_1500M))

/**
 *  @brief GLB AHB clock IP type definition
 */
typedef enum {
    GLB_AHB_CLOCK_IP_CPU,
    GLB_AHB_CLOCK_IP_SDU,
    GLB_AHB_CLOCK_IP_SEC,
    GLB_AHB_CLOCK_IP_DMA_0,
    GLB_AHB_CLOCK_IP_DMA_1,
    GLB_AHB_CLOCK_IP_DMA_2,
    GLB_AHB_CLOCK_IP_CCI,
    GLB_AHB_CLOCK_IP_RF_TOP,
    GLB_AHB_CLOCK_IP_GPIP,
    GLB_AHB_CLOCK_IP_TZC,
    GLB_AHB_CLOCK_IP_EF_CTRL,
    GLB_AHB_CLOCK_IP_SF_CTRL,
    GLB_AHB_CLOCK_IP_EMAC,
    GLB_AHB_CLOCK_IP_UART0,
    GLB_AHB_CLOCK_IP_UART1,
    GLB_AHB_CLOCK_IP_UART2,
    GLB_AHB_CLOCK_IP_UART3,
    GLB_AHB_CLOCK_IP_UART4,
    GLB_AHB_CLOCK_IP_SPI,
    GLB_AHB_CLOCK_IP_I2C,
    GLB_AHB_CLOCK_IP_PWM,
    GLB_AHB_CLOCK_IP_TIMER,
    GLB_AHB_CLOCK_IP_IR,
    GLB_AHB_CLOCK_IP_CHECKSUM,
    GLB_AHB_CLOCK_IP_QDEC,
    GLB_AHB_CLOCK_IP_KYS,
    GLB_AHB_CLOCK_IP_I2S,
    GLB_AHB_CLOCK_IP_USB11,
    GLB_AHB_CLOCK_IP_CAM,
    GLB_AHB_CLOCK_IP_MJPEG,
    GLB_AHB_CLOCK_IP_BT_BLE_NORMAL,
    GLB_AHB_CLOCK_IP_BT_BLE_LP,
    GLB_AHB_CLOCK_IP_ZB_NORMAL,
    GLB_AHB_CLOCK_IP_ZB_LP,
    GLB_AHB_CLOCK_IP_WIFI_NORMAL,
    GLB_AHB_CLOCK_IP_WIFI_LP,
    GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL,
    GLB_AHB_CLOCK_IP_BT_BLE_2_LP,
    GLB_AHB_CLOCK_IP_EMI_MISC,
    GLB_AHB_CLOCK_IP_PSRAM0_CTRL,
    GLB_AHB_CLOCK_IP_PSRAM1_CTRL,
    GLB_AHB_CLOCK_IP_USB20,
    GLB_AHB_CLOCK_IP_MIX2,
    GLB_AHB_CLOCK_IP_AUDIO,
    GLB_AHB_CLOCK_IP_SDH,
    GLB_AHB_CLOCK_IP_ZB2_NORMAL,
    GLB_AHB_CLOCK_IP_ZB2_LP,
    GLB_AHB_CLOCK_IP_I2C1,
    GLB_AHB_CLOCK_IP_WIFI_PHY,
    GLB_AHB_CLOCK_IP_WIFI_MAC_PHY,
    GLB_AHB_CLOCK_IP_WIFI_PLATFORM,
    GLB_AHB_CLOCK_IP_LZ4,
    GLB_AHB_CLOCK_IP_AUPDM,
    GLB_AHB_CLOCK_IP_GAUGE,
} GLB_AHB_CLOCK_IP_Type;
/**
 *  @brief GLB core ID type definition
 */
typedef enum {
    GLB_CORE_ID_M0,                         /*!< M0 */
    GLB_CORE_ID_M1,                         /*!< M1 */
    GLB_CORE_ID_D0,                         /*!< D0 */
    GLB_CORE_ID_D1,                         /*!< D1 */
    GLB_CORE_ID_LP,                         /*!< LP */
    GLB_CORE_ID_MAX,                        /*!< ID max */
    GLB_CORE_ID_INVALID,                    /*!< ID invalid */
}GLB_CORE_ID_Type;

/**
 *  @brief GLB root clock type definition
 */
typedef enum {
    GLB_ROOT_CLK_RC32M=0,                   /*!< Select RC32M as main clock input */
    GLB_ROOT_CLK_XTAL,                      /*!< Select XTAL as main clock input */
    GLB_ROOT_CLK_PLL_WITH_XTAL_ON,          /*!< Select PLL as main clock input */
    GLB_ROOT_CLK_OFF,                       /*!< Select no clock input */
}GLB_Root_CLK_Type;

/**
 *  @brief GLB PLL clock type definition
 */
typedef enum {
    GLB_PLL_CLK_120M,                       /*!< Select PLL 120M output */
    GLB_PLL_CLK_160M,                       /*!< Select PLL 160M output */
    GLB_PLL_CLK_320M,                       /*!< Select PLL 320M output */
    GLB_PLL_CLK_400M,                       /*!< Select PLL 400M output */
}GLB_PLL_CLK_Type;

/**
 *  @brief GLB muxpll 320M clock type definition
 */
typedef enum {
    GLB_MUXPLL_SEL_320M_ETHPLL,             /*!< muxpll select ethpll 320M */
    GLB_MUXPLL_SEL_300M_CPUPLL,             /*!< muxpll select cpupll 320M */
}GLB_MUXPLL_320M_CLK_SEL_Type;

/**
 *  @brief GLB muxpll 240M clock type definition
 */
typedef enum {
    GLB_MUXPLL_SEL_240M_WIFIPLL,            /*!< muxpll select wifipll 240M */
    GLB_MUXPLL_SEL_240M_CPUPLL,             /*!< muxpll select cpupll 240M */
}GLB_MUXPLL_240M_CLK_SEL_Type;

/**
 *  @brief GLB muxpll 200M clock type definition
 */
typedef enum {
    GLB_MUXPLL_SEL_200M_ETHPLL,             /*!< muxpll select ethpll 200M */
    GLB_MUXPLL_SEL_200M_CPUPLL,             /*!< muxpll select cpupll 200M */
}GLB_MUXPLL_200M_CLK_SEL_Type;

/**
 *  @brief GLB muxpll 160M clock type definition
 */
typedef enum {
    GLB_MUXPLL_SEL_160M_ETHPLL,             /*!< muxpll select ethpll 160M */
    GLB_MUXPLL_SEL_150M_CPUPLL,             /*!< muxpll select cpupll 150M */
}GLB_MUXPLL_160M_CLK_SEL_Type;

typedef enum {
    GLB_CAM_CLK_XCLK,        /*!< Select XCLK as CAM clock */
    GLB_CAM_CLK_WIFIPLL_96M, /*!< Select WIFIPLL_96M as CAM clock */
    GLB_CAM_CLK_CPUPLL_100M, /*!< Select CPUPLL_96M as CAM clock */
} GLB_CAM_CLK_Type;

typedef enum {
    GLB_DSP_I2C_CLK_DSP_PBCLK, /*!< Select dsp pbclk as I2C clock */
    GLB_DSP_I2C_CLK_XCLK,      /*!< Select xclk as I2C clock */
} GLB_DSP_I2C_CLK_Type;

/**
 *  @brief GLB I2C clock type definition
 */
typedef enum {
    GLB_I2C_CLK_BCLK, /*!< Select bus clk as I2C clock */
    GLB_I2C_CLK_XCLK, /*!< Select xclk as I2C clock */
} GLB_I2C_CLK_Type;


/** @defgroup  GLB_CAM_CLK_TYPE
 *  @{
 */
#define IS_GLB_CAM_CLK_TYPE(type) (((type) == GLB_CAM_CLK_XCLK) ||        \
                                   ((type) == GLB_CAM_CLK_WIFIPLL_96M) || \
                                   ((type) == GLB_CAM_CLK_CPUPLL_100M))

#define IS_GLB_DSP_I2C_CLK_TYPE(type) (((type) == GLB_DSP_I2C_CLK_DSP_PBCLK) || \
                                       ((type) == GLB_DSP_I2C_CLK_XCLK))
/**
 *  @brief GLB muxpll 54M clock type definition
 */
typedef enum {
    GLB_MUXPLL_SEL_53M_ETHPLL,              /*!< muxpll select ethpll 53M */
    GLB_MUXPLL_SEL_60M_CPUPLL,              /*!< muxpll select cpupll 60M */
}GLB_MUXPLL_54M_CLK_SEL_Type;
/**
 *  @brief GLB DSP xclk clock type definition
 */
typedef enum {
    GLB_DSP_XCLK_RC32M,                     /*!< use RC32M as xclk clock */
    GLB_DSP_XCLK_XTAL,                      /*!< use XTAL as xclk clock */
}GLB_DSP_XCLK_Type;

/**
 *  @brief GLB DSP root clock type definition
 */
typedef enum {
    GLB_DSP_ROOT_CLK_RC32M,                 /*!< use RC32M as root clock */
    GLB_DSP_ROOT_CLK_XTAL,                  /*!< use XTAL as root clock */
    GLB_DSP_ROOT_CLK_PLL,                   /*!< use PLL as root clock */
}GLB_DSP_ROOT_CLK_Type;

/**
 *  @brief GLB flash clock type definition
 */
typedef enum {
    GLB_SFLASH_CLK_120M,                    /*!< Select 120M as flash clock */
    GLB_SFLASH_CLK_80M,                     /*!< Select 80M as flash clock */
    GLB_SFLASH_CLK_FDIV2,                   /*!< Select FCLK divide 2 as flash clock */
    GLB_SFLASH_CLK_96M,                     /*!< Select 96M as flash clock */
    GLB_SFLASH_CLK_XTAL,                    /*!< Select XTAL as flash clock */
    GLB_SFLASH_CLK_50M,                     /*!< Select 50M as flash clock */
}GLB_SFLASH_CLK_Type;

/**
 *  @brief GLB PSRAM clock type definition
 */
typedef enum {
    GLB_PSRAM_CLK_BCLK,                     /*!< Select BClk as PSRAM clock */
    GLB_PSRAM_CLK_240M,                     /*!< Select 240M as PSRAM clock */
    GLB_PSRAM_CLK_320M,                     /*!< Select 320M as PSRAM clock */
    GLB_PSRAM_CLK_400M,                     /*!< Select 400M as PSRAM clock */
}GLB_PSRAM_CLK_Type;

/**
 *  @brief GLB SDH clock type definition
 */
typedef enum {
    GLB_SDH_CLK_24M,                        /*!< Select 24M as SDH clock */
    GLB_SDH_CLK_48M,                        /*!< Select 48M as SDH clock */
    GLB_SDH_CLK_96M,                        /*!< Select 96M as SDH clock */
    GLB_SDH_CLK_192M,                       /*!< Select 192M as SDH clock */
    GLB_SDH_CLK_25M,                        /*!< Select 25M as SDH clock */
    GLB_SDH_CLK_50M,                        /*!< Select 50M as SDH clock */
    GLB_SDH_CLK_100M,                       /*!< Select 100M as SDH clock */
    GLB_SDH_CLK_208M,                       /*!< Select 208M as SDH clock */
}GLB_SDH_CLK_Type;

/**
 *  @brief GLB UART clock type definition
 */
typedef enum {
    GLB_UART_CLK_FCLK,                      /*!< Select FLCK as UART clock */
    GLB_UART_CLK_160M,                      /*!< Select 160M as UART clock */
}GLB_UART_CLK_Type;

#if (BL80X_HW_VER <= BL80X_HW_A0)
typedef enum {
    HDMI_CLK_80_MHZ = 0,
    HDMI_CLK_160_MHZ = 1,
    HDMI_CLK_240_MHZ = 2,
    HDMI_CLK_267_MHZ = 3,
} HDMI_CLK_SEL_E;
#else
typedef enum {
    HDMI_CLK_27_MHZ = 0,        /* for HDMI_OUT_480P */
    HDMI_CLK_74_25_MHZ = 1,
} HDMI_CLK_SEL_E;
#endif

typedef enum {
    H264_CLK_160_MHZ = 0,
    H264_CLK_240_MHZ = 1,
    H264_CLK_267_MHZ = 2,
    H264_CLK_320_MHZ = 3,
} H264_CLK_SEL_E;

/**
 *  @brief GLB DAC clock type definition
 */
typedef enum {
    GLB_DAC_CLK_512K,                       /*!< Select 512K as DAC clock */
    GLB_DAC_CLK_256K,                       /*!< Select 256K as DAC clock */
    GLB_DAC_CLK_128K,                       /*!< Select 128K as DAC clock */
}GLB_DAC_CLK_Type;

/**
 *  @brief GLB DMA clock ID type definition
 */
typedef enum {
    GLB_DMA_CLK_DMA0_CH0,                   /*!< DMA clock ID:channel 0 */
    GLB_DMA_CLK_DMA0_CH1,                   /*!< DMA clock ID:channel 1 */
    GLB_DMA_CLK_DMA0_CH2,                   /*!< DMA clock ID:channel 2 */
    GLB_DMA_CLK_DMA0_CH3,                   /*!< DMA clock ID:channel 3 */
    GLB_DMA_CLK_DMA0_CH4,                   /*!< DMA clock ID:channel 4 */
    GLB_DMA_CLK_MASTERS,                    /*!< DMA clock ID:AHB master */
    GLB_DMA_CLK_SLAVES,                     /*!< DMA clock ID:AHB slave */
    GLB_DMA_CLK_RQS,                        /*!< DMA clock ID:RQS */
}GLB_DMA_CLK_ID_Type;

/**
 *  @brief GLB UART signal type definition
 */
typedef enum {
    GLB_UART_SIG_0,                         /*!< UART signal 0 */
    GLB_UART_SIG_1,                         /*!< UART signal 1 */
    GLB_UART_SIG_2,                         /*!< UART signal 2 */
    GLB_UART_SIG_3,                         /*!< UART signal 3 */
    GLB_UART_SIG_4,                         /*!< UART signal 4 */
    GLB_UART_SIG_5,                         /*!< UART signal 5 */
    GLB_UART_SIG_6,                         /*!< UART signal 6 */
    GLB_UART_SIG_7,                         /*!< UART signal 7 */
    GLB_UART_SIG_8,                         /*!< UART signal 8 */
    GLB_UART_SIG_9,                         /*!< UART signal 9 */
    GLB_UART_SIG_10,                        /*!< UART signal 10 */
    GLB_UART_SIG_11,                        /*!< UART signal 11 */
}GLB_UART_SIG_Type;

/**
 *  @brief GLB UART signal  function type definition
 */
typedef enum {
    GLB_UART_SIG_FUN_UART0_RTS,             /*!< UART funtion: UART 0 RTS */
    GLB_UART_SIG_FUN_UART0_CTS,             /*!< UART funtion: UART 0 CTS */
    GLB_UART_SIG_FUN_UART0_TXD,             /*!< UART funtion: UART 0 TXD */
    GLB_UART_SIG_FUN_UART0_RXD,             /*!< UART funtion: UART 0 RXD */
    GLB_UART_SIG_FUN_UART1_RTS,             /*!< UART funtion: UART 1 RTS */
    GLB_UART_SIG_FUN_UART1_CTS,             /*!< UART funtion: UART 1 CTS */
    GLB_UART_SIG_FUN_UART1_TXD,             /*!< UART funtion: UART 1 TXD */
    GLB_UART_SIG_FUN_UART1_RXD,             /*!< UART funtion: UART 1 RXD */
    GLB_UART_SIG_FUN_UART2_RTS,             /*!< UART funtion: UART 2 RTS */
    GLB_UART_SIG_FUN_UART2_CTS,             /*!< UART funtion: UART 2 CTS */
    GLB_UART_SIG_FUN_UART2_TXD,             /*!< UART funtion: UART 2 TXD */
    GLB_UART_SIG_FUN_UART2_RXD,             /*!< UART funtion: UART 2 RXD */
}GLB_UART_SIG_FUN_Type;

/**
 *  @brief GLB UART sig swap group type definition
 */
typedef enum {
    GLB_UART_SIG_SWAP_GRP_GPIO0_GPIO11,  /*!< SWAP UART SIG GROUP GPIO0  -  GPIO11 */
    GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, /*!< SWAP UART SIG GROUP GPIO12 -  GPIO23 */
    GLB_UART_SIG_SWAP_GRP_GPIO24_GPIO35, /*!< SWAP UART SIG GROUP GPIO24 -  GPIO35 */
    GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45, /*!< SWAP UART SIG GROUP GPIO36 -  GPIO45 */
} GLB_UART_SIG_SWAP_GRP_Type;

typedef enum {
    GLB_CPU_CM4,
    GLB_CPU_CA5,
}GLB_CPU_SEL_Type;

typedef enum {
    GLB_CLKPLL_EN_25M,                        /*!< PLL CLK 25M */
    GLB_CLKPLL_EN_50M,                        /*!< PLL CLK 50M */
    GLB_CLKPLL_EN_100M,                       /*!< PLL CLK 100M */
    GLB_CLKPLL_EN_120M,                       /*!< PLL CLK 120M */
    GLB_CLKPLL_EN_160M,                       /*!< PLL CLK 160M */
    GLB_CLKPLL_EN_192M,                       /*!< PLL CLK 192M */
    GLB_CLKPLL_EN_240M,                       /*!< PLL CLK 240M */
    GLB_CLKPLL_EN_267M,                       /*!< PLL CLK 267M */
    GLB_CLKPLL_EN_320M,                       /*!< PLL CLK 320M */
    GLB_CLKPLL_EN_400M,                       /*!< PLL CLK 400M */
}GLB_PLL_CLK_EN_Type;

/**
 *  @brief GLB mcu system clock type definition
 */
typedef enum {
    GLB_MCU_SYS_CLK_RC32M,                  /*!< use RC32M as system clock frequency */
    GLB_MCU_SYS_CLK_XTAL,                   /*!< use XTAL as system clock */
    GLB_MCU_SYS_CLK_160M_WIFIPLL,           /*!< use WIFIPLL output 160M as system clock */
    GLB_MCU_SYS_CLK_192M_WIFIPLL,           /*!< use WIFIPLL output 192M as system clock */
    GLB_MCU_SYS_CLK_240M_WIFIPLL,           /*!< use WIFIPLL output 240M as system clock */
    GLB_MCU_SYS_CLK_320M_ETHPLL,            /*!< use ETHPLL output 320M as system clock */
    GLB_MCU_SYS_CLK_300M_CPUPLL,            /*!< use CPUPLL output 300M as system clock */
}GLB_MCU_SYS_CLK_Type;

/**
 *  @brief GLB dsp system clock type definition
 */
typedef enum {
    GLB_DSP_SYS_CLK_RC32M,                  /*!< use RC32M as system clock frequency */
    GLB_DSP_SYS_CLK_XTAL,                   /*!< use XTAL as system clock */
    GLB_DSP_SYS_CLK_240M_WIFIPLL,           /*!< use WIFIPLL output 240M as system clock */
    GLB_DSP_SYS_CLK_320M_ETHPLL,            /*!< use ETHPLL output 320M as system clock */
    GLB_DSP_SYS_CLK_400M_ETHPLL,            /*!< use ETHPLL output 400M as system clock */
    GLB_DSP_SYS_CLK_640M_CPUPLL,            /*!< use CPUPLL output 640M as system clock */
    GLB_DSP_SYS_CLK_240M_CPUPLL,            /*!< use CPUPLL output 240M as system clock */
    GLB_DSP_SYS_CLK_300M_CPUPLL,            /*!< use CPUPLL output 320M as system clock */
}GLB_DSP_SYS_CLK_Type;

/**
 *  @brief GLB DSP PLL clock type definition
 */
typedef enum {
    GLB_DSP_PLL_CLK_PLL120M,                /*!< select DSP PLL output 120M as cpu clock */
    GLB_DSP_PLL_CLK_PLL160M,                /*!< select DSP PLL output 160M as cpu clock */
    GLB_DSP_PLL_CLK_PLL320M,                /*!< select DSP PLL output 320M as cpu clock */
    GLB_DSP_PLL_CLK_PLL400M,                /*!< select DSP PLL output 400M as cpu clock */
}GLB_DSP_PLL_CLK_Type;

/**
 *  @brief GLB SPI clock type definition
 */
typedef enum {
    GLB_SPI_CLK_MCU_MUXPLL_160M, /*!< Select MCU MUXPLL 160M as SPI clock */
    GLB_SPI_CLK_XCLK,            /*!< Select xclk as SPI clock */
} GLB_SPI_CLK_Type;

/**
 *  @brief GLB DSP SPI clock type definition
 */
typedef enum {
    GLB_DSP_SPI_CLK_DSP_MUXPLL_160M, /*!< Select muxpll 160M as SPI clock */
    GLB_DSP_SPI_CLK_DSP_XCLK,        /*!< Select xclk as SPI clock */
} GLB_DSP_SPI_CLK_Type;

/**
 *  @brief GLB SPI pad action type definition
 */
typedef enum {
    GLB_SPI_PAD_ACT_AS_SLAVE,  /*!< SPI pad act as slave */
    GLB_SPI_PAD_ACT_AS_MASTER, /*!< SPI pad act as master */
} GLB_SPI_PAD_ACT_AS_Type;

/**
 *  @brief GLB AHB software type definition
 */
typedef enum {
    GLB_AHB_MCU_SW_RSV0 = 0,
    GLB_AHB_MCU_SW_RSV1 = 1,
    GLB_AHB_MCU_SW_WIFI = 4,
    GLB_AHB_MCU_SW_BTDM = 8,
    GLB_AHB_MCU_SW_ZIGBEE = 9,
    GLB_AHB_MCU_SW_BLE2 = 10,
    GLB_AHB_MCU_SW_ZIGBEE2 = 11,
    GLB_AHB_MCU_SW_EMI_MISC = 16,
    GLB_AHB_MCU_SW_PSRAM0_CTRL = 17,
    GLB_AHB_MCU_SW_PSRAM1_CTRL = 18,
    GLB_AHB_MCU_SW_USB_EMAC = 19,
    GLB_AHB_MCU_SW_RSV20 = 20,
    GLB_AHB_MCU_SW_AUDIO = 21,
    GLB_AHB_MCU_SW_SDH = 22,
    GLB_AHB_MCU_SW_RSV23 = 23,
    GLB_AHB_MCU_SW_DMA2 = 24,
    GLB_AHB_MCU_SW_GLB = 32,
    GLB_AHB_MCU_SW_MIX = 33,
    GLB_AHB_MCU_SW_GPIP = 34,
    GLB_AHB_MCU_SW_SEC_DBG = 35,
    GLB_AHB_MCU_SW_SEC_ENG = 36,
    GLB_AHB_MCU_SW_TZ1 = 37,
    GLB_AHB_MCU_SW_TZ2 = 38,
    GLB_AHB_MCU_SW_EFUSE = 39,
    GLB_AHB_MCU_SW_CCI = 40,
    GLB_AHB_MCU_SW_MCU_PERI_BUS = 41,
    GLB_AHB_MCU_SW_RSV42 = 42,
    GLB_AHB_MCU_SW_SF = 43,
    GLB_AHB_MCU_SW_DMA = 44,
    GLB_AHB_MCU_SW_SDU = 45,
    GLB_AHB_MCU_SW_PDS = 46,
    GLB_AHB_MCU_SW_RSV47 = 47,
    GLB_AHB_MCU_SW_UART0 = 48,
    GLB_AHB_MCU_SW_UART1 = 49,
    GLB_AHB_MCU_SW_SPI = 50,
    GLB_AHB_MCU_SW_I2C = 51,
    GLB_AHB_MCU_SW_PWM = 52,
    GLB_AHB_MCU_SW_TIMER = 53,
    GLB_AHB_MCU_SW_IR_REMOTE = 54,
    GLB_AHB_MCU_SW_CHECKSUM = 55,
    GLB_AHB_MCU_SW_IPC = 56,
    GLB_AHB_MCU_SW_I2C1 = 57,
    GLB_AHB_MCU_SW_UART2 = 58,
    GLB_AHB_MCU_SW_I2S = 59,
    GLB_AHB_MCU_SW_AUPDM = 60,
    GLB_AHB_MCU_SW_LZ4 = 61,
    GLB_AHB_MCU_SW_RSV62 = 62,
    GLB_AHB_MCU_SW_RSV63 = 63,
    GLB_AHB_MCU_SW_PWRON_RST = 64,
    GLB_AHB_MCU_SW_CPU_RESET = 65,
    GLB_AHB_MCU_SW_SYS_RESET = 66,
    GLB_AHB_MCU_SW_PICO_RESET = 67,
    GLB_AHB_MCU_SW_CPU2_RESET = 68,
    GLB_AHB_MCU_SW_CHIP_RESET = 69,
    GLB_AHB_MCU_SW_WL_WDT_RESET_MM_EN = 70,
    GLB_AHB_MCU_SW_MMWDT2WL_RST_MSK = 71,
} GLB_AHB_MCU_SW_Type;

/**
 *  @brief GLB AHB software type definition
 */
typedef enum {
    GLB_AHB_DSP_SW_REG_CTRL_SYS_RESET = 0,
    GLB_AHB_DSP_SW_REG_CTRL_PWRON_RST = 2,
    GLB_AHB_DSP_SW_REG_CTRL_MMCPU0_RESET = 8,
    GLB_AHB_DSP_SW_SWRST_MM_MISC = 32,
    GLB_AHB_DSP_SW_SWRST_DMA = 33,
    GLB_AHB_DSP_SW_SWRST_UART0 = 34,
    GLB_AHB_DSP_SW_SWRST_I2C0 = 35,
    GLB_AHB_DSP_SW_SWRST_I2C1 = 36,
    GLB_AHB_DSP_SW_SWRST_IPC = 37,
    GLB_AHB_DSP_SW_SWRST_DMA2D = 38,
    GLB_AHB_DSP_SW_SWRST_SPI = 40,
    GLB_AHB_DSP_SW_SWRST_TIMER = 41,
    GLB_AHB_DSP_SW_SWRST_I2S0 = 42,
    GLB_AHB_DSP_SW_SWRST_I2S1 = 43,
    GLB_AHB_DSP_SW_SWRST_PDM0 = 44,
    GLB_AHB_DSP_SW_SWRST_PDM1 = 45,
    GLB_AHB_DSP_SW_SWRST_UART1 = 46,
    GLB_AHB_DSP_SW_SWRST_PUHS = 47,
    GLB_AHB_DSP_SW_SWRST_ISP_MISC = 64,
    GLB_AHB_DSP_SW_SWRST_ISP_MAIN = 65,
    GLB_AHB_DSP_SW_SWRST_ISP_TSRC = 66,
    GLB_AHB_DSP_SW_SWRST_DP_TSRC = 67,
    GLB_AHB_DSP_SW_SWRST_NR3D_CTRL = 68,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSA = 69,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSB = 70,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSC = 71,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSD = 72,
    GLB_AHB_DSP_SW_SWRST_MIPI = 73,
    GLB_AHB_DSP_SW_SWRST_ISP_REG = 80,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSE = 81,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSF = 82,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSG = 83,
    GLB_AHB_DSP_SW_SWRST_DVP2BUSH = 84,
    GLB_AHB_DSP_SW_SWRST_CODEC_MISC = 96,
    GLB_AHB_DSP_SW_SWRST_MJPEG = 97,
    GLB_AHB_DSP_SW_SWRST_H264 = 98,
    GLB_AHB_DSP_SW_SWRST_MJPEG_DEC = 99,
    GLB_AHB_DSP_SW_SWRST_CNN = 100,
    GLB_AHB_DSP_SW_SWRST_VRAM = 112,
    GLB_AHB_DSP_SW_RG_IS_RST_N = 128,
} GLB_AHB_DSP_SW_Type;
/*@} end of group GLB_Public_Types */

/**
 *  @brief GLB LDO15CIS level type definition
 */
typedef enum {
    GLB_LDO15CIS_LEVEL_1P00V = 0,  /*!< GLB LDO15CIS voltage 1.00V */
    GLB_LDO15CIS_LEVEL_1P05V = 1,  /*!< GLB LDO15CIS voltage 1.05V */
    GLB_LDO15CIS_LEVEL_1P10V = 2,  /*!< GLB LDO15CIS voltage 1.10V */
    GLB_LDO15CIS_LEVEL_1P15V = 3,  /*!< GLB LDO15CIS voltage 1.15V */
    GLB_LDO15CIS_LEVEL_1P20V = 4,  /*!< GLB LDO15CIS voltage 1.20V */
    GLB_LDO15CIS_LEVEL_1P30V = 5,  /*!< GLB LDO15CIS voltage 1.30V */
    GLB_LDO15CIS_LEVEL_1P40V = 6,  /*!< GLB LDO15CIS voltage 1.40V */
    GLB_LDO15CIS_LEVEL_1P45V = 7,  /*!< GLB LDO15CIS voltage 1.45V */
    GLB_LDO15CIS_LEVEL_1P50V = 8,  /*!< GLB LDO15CIS voltage 1.50V */
    GLB_LDO15CIS_LEVEL_1P55V = 9,  /*!< GLB LDO15CIS voltage 1.55V */
    GLB_LDO15CIS_LEVEL_1P60V = 10, /*!< GLB LDO15CIS voltage 1.60V */
    GLB_LDO15CIS_LEVEL_1P65V = 11, /*!< GLB LDO15CIS voltage 1.65V */
    GLB_LDO15CIS_LEVEL_1P70V = 12, /*!< GLB LDO15CIS voltage 1.70V */
    GLB_LDO15CIS_LEVEL_1P75V = 13, /*!< GLB LDO15CIS voltage 1.75V */
    GLB_LDO15CIS_LEVEL_1P80V = 14, /*!< GLB LDO15CIS voltage 1.80V */
    GLB_LDO15CIS_LEVEL_1P85V = 15, /*!< GLB LDO15CIS voltage 1.85V */
} GLB_LDO15CIS_LEVEL_Type;

/** @defgroup  GLB_Public_Constants
 *  @{
 */

/** @defgroup  GLB_MCU_SYS_CLK_TYPE
 *  @{
 */
#define IS_GLB_MCU_SYS_CLK_TYPE(type)                    (((type) == GLB_MCU_SYS_CLK_RC32M) || \
                                                          ((type) == GLB_MCU_SYS_CLK_XTAL) || \
                                                          ((type) == GLB_MCU_SYS_CLK_160M_WIFIPLL) || \
                                                          ((type) == GLB_MCU_SYS_CLK_192M_WIFIPLL) || \
                                                          ((type) == GLB_MCU_SYS_CLK_240M_WIFIPLL) || \
                                                          ((type) == GLB_MCU_SYS_CLK_320M_ETHPLL) || \
                                                          ((type) == GLB_MCU_SYS_CLK_300M_CPUPLL))

/** @defgroup  GLB_DSP_SYS_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_SYS_CLK_TYPE(type)                    (((type) == GLB_DSP_SYS_CLK_RC32M) || \
                                                          ((type) == GLB_DSP_SYS_CLK_XTAL) || \
                                                          ((type) == GLB_DSP_SYS_CLK_240M_WIFIPLL) || \
                                                          ((type) == GLB_DSP_SYS_CLK_320M_ETHPLL) || \
                                                          ((type) == GLB_DSP_SYS_CLK_400M_ETHPLL) || \
                                                          ((type) == GLB_DSP_SYS_CLK_640M_CPUPLL) || \
                                                          ((type) == GLB_DSP_SYS_CLK_240M_CPUPLL) || \
                                                          ((type) == GLB_DSP_SYS_CLK_300M_CPUPLL))

/** @defgroup  GLB_DSP_PLL_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_PLL_CLK_TYPE(type)                    (((type) == GLB_DSP_PLL_CLK_PLL120M) || \
                                                          ((type) == GLB_DSP_PLL_CLK_PLL160M) || \
                                                          ((type) == GLB_DSP_PLL_CLK_PLL320M) || \
                                                          ((type) == GLB_DSP_PLL_CLK_PLL400M))

/** @defgroup  GLB_MUXPLL_240M_CLK_SEL_TYPE
 *  @{
 */
#define IS_GLB_MUXPLL_240M_CLK_SEL_TYPE(type)            (((type) == GLB_MUXPLL_SEL_240M_WIFIPLL) || \
                                                          ((type) == GLB_MUXPLL_SEL_240M_CPUPLL))

/** @defgroup  GLB_ROOT_CLK_TYPE
 *  @{
 */
#define IS_GLB_ROOT_CLK_TYPE(type)                       (((type) == GLB_ROOT_CLK_RC32M) || \
                                                          ((type) == GLB_ROOT_CLK_XTAL) || \
                                                          ((type) == GLB_ROOT_CLK_PLL_WITH_XTAL_ON))

/** @defgroup  GLB_PLL_CLK_TYPE
 *  @{
 */
#define IS_GLB_PLL_CLK_TYPE(type)                        (((type) == GLB_PLL_CLK_120M) || \
                                                          ((type) == GLB_PLL_CLK_160M) || \
                                                          ((type) == GLB_PLL_CLK_320M) || \
                                                          ((type) == GLB_PLL_CLK_400M))

/** @defgroup  GLB_SFLASH_CLK_TYPE
 *  @{
 */
#define IS_GLB_SFLASH_CLK_TYPE(type)                     (((type) == GLB_SFLASH_CLK_120M) || \
                                                          ((type) == GLB_SFLASH_CLK_80M) || \
                                                          ((type) == GLB_SFLASH_CLK_FDIV2) || \
                                                          ((type) == GLB_SFLASH_CLK_96M) || \
                                                          ((type) == GLB_SFLASH_CLK_XTAL) || \
                                                          ((type) == GLB_SFLASH_CLK_50M))

/** @defgroup  GLB_PSRAM_CLK_TYPE
 *  @{
 */
#define IS_GLB_PSRAM_CLK_TYPE(type)                      (((type) == GLB_PSRAM_CLK_320M ) || \
                                                          ((type) == GLB_PSRAM_CLK_240M) || \
                                                          ((type) == GLB_PSRAM_CLK_160M) || \
                                                          ((type) == GLB_PSRAM_CLK_120M))

/** @defgroup  GLB_SDH_CLK_TYPE
 *  @{
 */
#define IS_GLB_SDH_CLK_TYPE(type)                        (((type) == GLB_SDH_CLK_24M) || \
                                                          ((type) == GLB_SDH_CLK_48M) || \
                                                          ((type) == GLB_SDH_CLK_96M) || \
                                                          ((type) == GLB_SDH_CLK_192M) || \
                                                          ((type) == GLB_SDH_CLK_25M) || \
                                                          ((type) == GLB_SDH_CLK_50M) || \
                                                          ((type) == GLB_SDH_CLK_100M) || \
                                                          ((type) == GLB_SDH_CLK_208M))

/** @defgroup  GLB_UART_CLK_TYPE
 *  @{
 */
#define IS_GLB_UART_CLK_TYPE(type)                       (((type) == GLB_UART_CLK_FCLK) || \
                                                          ((type) == GLB_UART_CLK_160M))

/** @defgroup  GLB_DAC_CLK_TYPE
 *  @{
 */
#define IS_GLB_DAC_CLK_TYPE(type)                        (((type) == GLB_DAC_CLK_512K) || \
                                                          ((type) == GLB_DAC_CLK_256K) || \
                                                          ((type) == GLB_DAC_CLK_128K))

/** @defgroup  GLB_DSP_XCLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_XCLK_TYPE(type)                       (((type) == GLB_DSP_XCLK_RC32M) || \
                                                          ((type) == GLB_DSP_XCLK_XTAL))

/** @defgroup  GLB_DSP_ROOT_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_ROOT_CLK_TYPE(type)                   (((type) == GLB_DSP_ROOT_CLK_RC32M) || \
                                                          ((type) == GLB_DSP_ROOT_CLK_XTAL) || \
                                                          ((type) == GLB_DSP_ROOT_CLK_PLL))

/** @defgroup  GLB_DSP_SPI_CLK_TYPE
 *  @{
 */
#define IS_GLB_DSP_SPI_CLK_TYPE(type) (((type) == GLB_DSP_SPI_CLK_DSP_MUXPLL_160M) || \
                                       ((type) == GLB_DSP_SPI_CLK_DSP_XCLK))

/** @defgroup  GLB_MUXPLL_320M_CLK_SEL_TYPE
 *  @{
 */
#define IS_GLB_MUXPLL_320M_CLK_SEL_TYPE(type)            (((type) == GLB_MUXPLL_SEL_320M_ETHPLL) || \
                                                          ((type) == GLB_MUXPLL_SEL_300M_CPUPLL))

/** @defgroup  GLB_DMA_CLK_ID_TYPE
 *  @{
 */
#define IS_GLB_DMA_CLK_ID_TYPE(type)                     (((type) == GLB_DMA_CLK_DMA0_CH0) || \
                                                          ((type) == GLB_DMA_CLK_DMA0_CH1) || \
                                                          ((type) == GLB_DMA_CLK_DMA0_CH2) || \
                                                          ((type) == GLB_DMA_CLK_DMA0_CH3) || \
                                                          ((type) == GLB_DMA_CLK_DMA0_CH4) || \
                                                          ((type) == GLB_DMA_CLK_MASTERS) || \
                                                          ((type) == GLB_DMA_CLK_SLAVES) || \
                                                          ((type) == GLB_DMA_CLK_RQS))

/** @defgroup  GLB_SPI_CLK_TYPE
 *  @{
 */
#define IS_GLB_SPI_CLK_TYPE(type) (((type) == GLB_SPI_CLK_MCU_MUXPLL_160M) || \
                                   ((type) == GLB_SPI_CLK_XCLK))

/** @defgroup  GLB_UART_SIG_TYPE
 *  @{
 */
#define IS_GLB_UART_SIG_TYPE(type)                       (((type) == GLB_UART_SIG_0) || \
                                                          ((type) == GLB_UART_SIG_1) || \
                                                          ((type) == GLB_UART_SIG_2) || \
                                                          ((type) == GLB_UART_SIG_3) || \
                                                          ((type) == GLB_UART_SIG_4) || \
                                                          ((type) == GLB_UART_SIG_5) || \
                                                          ((type) == GLB_UART_SIG_6) || \
                                                          ((type) == GLB_UART_SIG_7) || \
                                                          ((type) == GLB_UART_SIG_8) || \
                                                          ((type) == GLB_UART_SIG_9) || \
                                                          ((type) == GLB_UART_SIG_10) || \
                                                          ((type) == GLB_UART_SIG_11))

/** @defgroup  GLB_UART_SIG_FUN_TYPE
 *  @{
 */
#define IS_GLB_UART_SIG_FUN_TYPE(type)                   (((type) == GLB_UART_SIG_FUN_UART0_RTS) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART0_CTS) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART0_TXD) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART0_RXD) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART1_RTS) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART1_CTS) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART1_TXD) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART1_RXD) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART2_RTS) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART2_CTS) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART2_TXD) || \
                                                          ((type) == GLB_UART_SIG_FUN_UART2_RXD))

/** @defgroup  GLB_GLB_UART_SIG_SWAP_SET_TYPE
 *  @{
 */
#define IS_GLB_UART_SIG_SWAP_GRP_TYPE(type)              (((type) == GLB_UART_SIG_SWAP_GRP_GPIO0_GPIO11) ||  \
                                                          ((type) == GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23) || \
                                                          ((type) == GLB_UART_SIG_SWAP_GRP_GPIO24_GPIO35) || \
                                                          ((type) == GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45))
#define IS_GLB_I2C_CLK_TYPE(type) (((type) == GLB_I2C_CLK_BCLK) || \
                                   ((type) == GLB_I2C_CLK_XCLK))

/** @defgroup  GLB_SPI_PAD_ACT_AS_TYPE
 *  @{
 */
#define IS_GLB_SPI_PAD_ACT_AS_TYPE(type) (((type) == GLB_SPI_PAD_ACT_AS_SLAVE) || \
                                          ((type) == GLB_SPI_PAD_ACT_AS_MASTER))

/** @defgroup  GLB_AHB_SW_TYPE
 *  @{
 */
#define IS_GLB_AHB_MCU_SW_TYPE(type) (((type) == GLB_AHB_MCU_SW_RSV0) ||               \
                                      ((type) == GLB_AHB_MCU_SW_RSV1) ||               \
                                      ((type) == GLB_AHB_MCU_SW_WIFI) ||               \
                                      ((type) == GLB_AHB_MCU_SW_BTDM) ||               \
                                      ((type) == GLB_AHB_MCU_SW_ZIGBEE) ||             \
                                      ((type) == GLB_AHB_MCU_SW_BLE2) ||               \
                                      ((type) == GLB_AHB_MCU_SW_ZIGBEE2) ||            \
                                      ((type) == GLB_AHB_MCU_SW_EMI_MISC) ||           \
                                      ((type) == GLB_AHB_MCU_SW_PSRAM0_CTRL) ||        \
                                      ((type) == GLB_AHB_MCU_SW_PSRAM1_CTRL) ||        \
                                      ((type) == GLB_AHB_MCU_SW_AUDIO) ||              \
                                      ((type) == GLB_AHB_MCU_SW_SDH) ||                \
                                      ((type) == GLB_AHB_MCU_SW_DMA2) ||               \
                                      ((type) == GLB_AHB_MCU_SW_GLB) ||                \
                                      ((type) == GLB_AHB_MCU_SW_MIX) ||                \
                                      ((type) == GLB_AHB_MCU_SW_GPIP) ||               \
                                      ((type) == GLB_AHB_MCU_SW_SEC_DBG) ||            \
                                      ((type) == GLB_AHB_MCU_SW_SEC_ENG) ||            \
                                      ((type) == GLB_AHB_MCU_SW_TZ1) ||                \
                                      ((type) == GLB_AHB_MCU_SW_TZ2) ||                \
                                      ((type) == GLB_AHB_MCU_SW_EFUSE) ||              \
                                      ((type) == GLB_AHB_MCU_SW_CCI) ||                \
                                      ((type) == GLB_AHB_MCU_SW_RSV42) ||              \
                                      ((type) == GLB_AHB_MCU_SW_SF) ||                 \
                                      ((type) == GLB_AHB_MCU_SW_DMA) ||                \
                                      ((type) == GLB_AHB_MCU_SW_SDU) ||                \
                                      ((type) == GLB_AHB_MCU_SW_PDS) ||                \
                                      ((type) == GLB_AHB_MCU_SW_RSV47) ||              \
                                      ((type) == GLB_AHB_MCU_SW_UART0) ||              \
                                      ((type) == GLB_AHB_MCU_SW_UART1) ||              \
                                      ((type) == GLB_AHB_MCU_SW_SPI) ||                \
                                      ((type) == GLB_AHB_MCU_SW_I2C) ||                \
                                      ((type) == GLB_AHB_MCU_SW_PWM) ||                \
                                      ((type) == GLB_AHB_MCU_SW_TIMER) ||              \
                                      ((type) == GLB_AHB_MCU_SW_IR_REMOTE) ||          \
                                      ((type) == GLB_AHB_MCU_SW_CHECKSUM) ||           \
                                      ((type) == GLB_AHB_MCU_SW_UART2) ||              \
                                      ((type) == GLB_AHB_MCU_SW_RSV62) ||              \
                                      ((type) == GLB_AHB_MCU_SW_RSV63) ||              \
                                      ((type) == GLB_AHB_MCU_SW_PWRON_RST) ||          \
                                      ((type) == GLB_AHB_MCU_SW_CPU_RESET) ||          \
                                      ((type) == GLB_AHB_MCU_SW_SYS_RESET) ||          \
                                      ((type) == GLB_AHB_MCU_SW_PICO_RESET) ||         \
                                      ((type) == GLB_AHB_MCU_SW_CPU2_RESET) ||         \
                                      ((type) == GLB_AHB_MCU_SW_CHIP_RESET) ||         \
                                      ((type) == GLB_AHB_MCU_SW_WL_WDT_RESET_MM_EN) || \
                                      ((type) == GLB_AHB_MCU_SW_MMWDT2WL_RST_MSK))

/** @defgroup  GLB_AHB_DSP_SW_TYPE
 *  @{
 */
#define IS_GLB_AHB_DSP_SW_TYPE(type) (((type) == GLB_AHB_DSP_SW_REG_CTRL_SYS_RESET) ||    \
                                      ((type) == GLB_AHB_DSP_SW_REG_CTRL_PWRON_RST) ||    \
                                      ((type) == GLB_AHB_DSP_SW_REG_CTRL_MMCPU0_RESET) || \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_MM_MISC) ||         \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DMA) ||             \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_UART0) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_I2C0) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_I2C1) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_IPC) ||             \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DMA2D) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_SPI) ||             \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_TIMER) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_I2S0) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_I2S1) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_PDM0) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_PDM1) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_UART1) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_PUHS) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_ISP_MISC) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_ISP_MAIN) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_ISP_TSRC) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DP_TSRC) ||         \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_NR3D_CTRL) ||       \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSA) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSB) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSC) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSD) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_MIPI) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_ISP_REG) ||         \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSE) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSF) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSG) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_DVP2BUSH) ||        \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_CODEC_MISC) ||      \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_MJPEG) ||           \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_H264) ||            \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_MJPEG_DEC) ||       \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_CNN) ||             \
                                      ((type) == GLB_AHB_DSP_SW_SWRST_VRAM) ||            \
                                      ((type) == GLB_AHB_DSP_SW_RG_IS_RST_N))


/** @defgroup  GLB_LDO15CIS_LEVEL_TYPE
 *  @{
 */
#define IS_GLB_LDO15CIS_LEVEL_TYPE(type) (((type) == GLB_LDO15CIS_LEVEL_1P00V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P05V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P10V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P15V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P20V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P30V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P40V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P45V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P50V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P55V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P60V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P65V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P70V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P75V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P80V) || \
                                          ((type) == GLB_LDO15CIS_LEVEL_1P85V))


/*@} end of group GLB_Public_Constants */

/** @defgroup  GLB_Public_Macros
 *  @{
 */

/** @defgroup  GLB_Public_Macros
 *  @{
 */
#define UART_SIG_SWAP_NONE          (0x00) /* uart_sig[0:11] -> uart_sig[0:11] */
#define UART_SIG_SWAP_GPIO0_GPIO11  (0x01) /* GPIO0-11  uart_sig[ 0:11] -> uart_sig[ 6:11], uart_sig[ 0: 5] */
#define UART_SIG_SWAP_GPIO12_GPIO23 (0x02) /* GPIO12-23 uart_sig[12:23] -> uart_sig[18:23], uart_sig[12:17] */
#define UART_SIG_SWAP_GPIO24_GPIO35 (0x04) /* GPIO24-35 uart_sig[24:35] -> uart_sig[30:35], uart_sig[24:29] */
#define UART_SIG_SWAP_GPIO36_GPIO47 (0x08) /* GPIO36-47 uart_sig[36:47] -> uart_sig[42:47], uart_sig[36:41] */

#define JTAG_SIG_SWAP_NONE 0x00 /* GPIO0-22  E21_TMS/E21_TDI/E21_TCK/E21_TDO <- E21_TCK/E21_TDO/E21_TMS/E21_TDI */

#define GLB_AHB_CLOCK_CPU             (0x0000000000000001UL)
#define GLB_AHB_CLOCK_SDU             (0x0000000000000002UL)
#define GLB_AHB_CLOCK_SEC             (0x0000000000000004UL)
#define GLB_AHB_CLOCK_DMA_0           (0x0000000000000008UL)
#define GLB_AHB_CLOCK_DMA_1           (0x0000000000000010UL)
#define GLB_AHB_CLOCK_DMA_2           (0x0000000000000020UL)
#define GLB_AHB_CLOCK_CCI             (0x0000000000000040UL)
#define GLB_AHB_CLOCK_RF_TOP          (0x0000000000000080UL)
#define GLB_AHB_CLOCK_GPIP            (0x0000000000000100UL)
#define GLB_AHB_CLOCK_TZC             (0x0000000000000200UL)
#define GLB_AHB_CLOCK_EF_CTRL         (0x0000000000000400UL)
#define GLB_AHB_CLOCK_SF_CTRL         (0x0000000000000800UL)
#define GLB_AHB_CLOCK_EMAC            (0x0000000000001000UL)
#define GLB_AHB_CLOCK_UART0           (0x0000000000002000UL)
#define GLB_AHB_CLOCK_UART1           (0x0000000000004000UL)
#define GLB_AHB_CLOCK_UART2           (0x0000000000008000UL)
#define GLB_AHB_CLOCK_UART3           (0x0000000000010000UL)
#define GLB_AHB_CLOCK_UART4           (0x0000000000020000UL)
#define GLB_AHB_CLOCK_SPI             (0x0000000000040000UL)
#define GLB_AHB_CLOCK_I2C             (0x0000000000080000UL)
#define GLB_AHB_CLOCK_PWM             (0x0000000000100000UL)
#define GLB_AHB_CLOCK_TIMER           (0x0000000000200000UL)
#define GLB_AHB_CLOCK_IR              (0x0000000000400000UL)
#define GLB_AHB_CLOCK_CHECKSUM        (0x0000000000800000UL)
#define GLB_AHB_CLOCK_QDEC            (0x0000000001000000UL)
#define GLB_AHB_CLOCK_KYS             (0x0000000002000000UL)
#define GLB_AHB_CLOCK_I2S             (0x0000000004000000UL)
#define GLB_AHB_CLOCK_USB11           (0x0000000008000000UL)
#define GLB_AHB_CLOCK_CAM             (0x0000000010000000UL)
#define GLB_AHB_CLOCK_MJPEG           (0x0000000020000000UL)
#define GLB_AHB_CLOCK_BT_BLE_NORMAL   (0x0000000040000000UL)
#define GLB_AHB_CLOCK_BT_BLE_LP       (0x0000000080000000UL)
#define GLB_AHB_CLOCK_ZB_NORMAL       (0x0000000100000000UL)
#define GLB_AHB_CLOCK_ZB_LP           (0x0000000200000000UL)
#define GLB_AHB_CLOCK_WIFI_NORMAL     (0x0000000400000000UL)
#define GLB_AHB_CLOCK_WIFI_LP         (0x0000000800000000UL)
#define GLB_AHB_CLOCK_BT_BLE_2_NORMAL (0x0000001000000000UL)
#define GLB_AHB_CLOCK_BT_BLE_2_LP     (0x0000002000000000UL)
#define GLB_AHB_CLOCK_EMI_MISC        (0x0000004000000000UL)
#define GLB_AHB_CLOCK_PSRAM0_CTRL     (0x0000008000000000UL)
#define GLB_AHB_CLOCK_PSRAM1_CTRL     (0x0000010000000000UL)
#define GLB_AHB_CLOCK_USB20           (0x0000020000000000UL)
#define GLB_AHB_CLOCK_MIX2            (0x0000040000000000UL)
#define GLB_AHB_CLOCK_AUDIO           (0x0000080000000000UL)
#define GLB_AHB_CLOCK_SDH             (0x0000100000000000UL)
#define GLB_AHB_CLOCK_ZB_2_NORMAL     (0x0000200000000000UL)
#define GLB_AHB_CLOCK_ZB_2_LP         (0x0000400000000000UL)
#define GLB_AHB_CLOCK_I2C1            (0x0000800000000000UL)
#define GLB_AHB_CLOCK_WIFI_PHY        (0x0001000000000000UL)
#define GLB_AHB_CLOCK_WIFI_MAC_PHY    (0x0002000000000000UL)
#define GLB_AHB_CLOCK_WIFI_PLATFORM   (0x0004000000000000UL)
#define GLB_AHB_CLOCK_LZ4             (0x0008000000000000UL)
#define GLB_AHB_CLOCK_AUPDM           (0x0010000000000000UL)
#define GLB_AHB_CLOCK_GAUGE           (0x0020000000000000UL)

#define GLB_AUTO_CALC_XTAL_FLAG_MASK  0x0000ff00
#define GLB_AUTO_CALC_XTAL_FLAG_VALUE 0x5800
/*@} end of group GLB_Public_Macros */


extern const GLB_MU_PLL_Cfg_Type mipiPllCfg_1500M[GLB_XTAL_MAX];


/** @defgroup  GLB_Public_Functions
 *  @{
 */

GLB_CORE_ID_Type ATTR_CLOCK_SECTION GLB_Get_Core_Type(void);
void GLB_Set_Root_CLK(GLB_Root_CLK_Type rootClk);
void GLB_Set_PLL_CLK(GLB_PLL_CLK_Type pllClk);
void GLB_Set_System_CLK_Div(uint8_t hclkDiv, uint8_t bclkDiv);
void GLB_Set_System_CLK(GLB_PLL_CLK_Type fClk);
void SystemCoreClockUpdate (void);
void GLB_Set_PSRAM_CLK(GLB_PSRAM_CLK_Type clkSel);
void GLB_DMA_CLK_Enable(GLB_DMA_CLK_ID_Type clk);
void GLB_DMA_CLK_Disable(GLB_DMA_CLK_ID_Type clk);
void GLB_Set_UART_CLK(BL_Fun_Type enable, GLB_UART_CLK_Type clkSel,uint8_t clkDiv);
void GLB_Set_SDH_CLK(BL_Fun_Type enable, GLB_SDH_CLK_Type clkSel);
void GLB_Set_PDM_CLK(uint8_t id, BL_Fun_Type enable, uint8_t clkDiv);
void GLB_Set_I2S_CLK(uint8_t id, BL_Fun_Type enable, uint8_t refSel, uint8_t outClkEnable, uint8_t outClkDiv);
BL_Err_Type GLB_Set_SPI_CLK(uint8_t enable, GLB_SPI_CLK_Type clkSel, uint8_t div);
// void GLB_Set_I2C_CLK(uint8_t id, BL_Fun_Type enable);
BL_Err_Type GLB_Set_I2C_CLK(uint8_t enable, GLB_I2C_CLK_Type clkSel, uint8_t div);
void GLB_Set_HDMI_CLK(BL_Fun_Type enable, HDMI_CLK_SEL_E clkSel, uint8_t outClkDiv);
BL_Err_Type GLB_Set_DSP_I2C0_CLK(uint8_t enable, GLB_DSP_I2C_CLK_Type clkSel, uint8_t divEn, uint8_t div);
void GLB_Set_H264_CLK(BL_Fun_Type enable, H264_CLK_SEL_E clkSel, uint8_t outClkDiv);
void GLB_Set_Fbdiv_Ratio(uint32_t ratio);
void GLB_Enable_PLL_CLK(GLB_PLL_CLK_EN_Type clkSel);
BL_Err_Type GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod);
BL_Err_Type GLB_Set_MCU_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod);
BL_Err_Type GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_Type swrst);
void GLB_SW_CPU_Reset(GLB_CPU_SEL_Type cpu);
void GLB_SW_System_Reset(void);
//void GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg);
//uint8_t GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin);
//void GLB_GPIO_Write(GLB_GPIO_Type gpioPin, uint32_t val);
//uint32_t GLB_GPIO_Read(GLB_GPIO_Type gpioPin);
void GLB_Power_On_Audio_PLL(uint32_t audClk);
GLB_DSP_ROOT_CLK_Type GLB_Get_DSP_ROOT_CLK_Sel(void);
GLB_DSP_XCLK_Type GLB_Get_DSP_XCLK_Sel(void);
BL_Err_Type GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_Type xclk);
BL_Err_Type GLB_Set_CAM_CLK(uint8_t enable, GLB_CAM_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_Type rootClk);
BL_Err_Type GLB_Set_Muxpll_320M_Sel(GLB_MUXPLL_320M_CLK_SEL_Type clkSel);
BL_Err_Type GLB_AHB_Slave3_Clock_Gate(uint8_t enable,BL_AHB_Slave3_Type slave3);
BL_Err_Type GLB_Set_DSP_PLL_CLK_Sel(GLB_DSP_PLL_CLK_Type pllClk);
BL_Err_Type GLB_Set_Muxpll_240M_Sel(GLB_MUXPLL_240M_CLK_SEL_Type clkSel);
BL_Err_Type GLB_Set_MCU_System_CLK_Div(uint8_t hclkDiv,uint8_t mcuBclkDiv,uint8_t periBclkDiv,uint8_t lpDiv);
BL_Err_Type GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_Type clkFreq);
BL_Err_Type GLB_Set_DSP_System_CLK_Div(uint8_t cpuDiv,uint8_t dspBclkDiv,uint8_t mmBclkDiv);
BL_Err_Type GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_Type clkFreq);
BL_Err_Type GLB_Set_DSP_SPI_CLK(uint8_t enable, GLB_DSP_SPI_CLK_Type clkSel, uint8_t div);
BL_Err_Type GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_Type group, uint8_t swap);
BL_Err_Type GLB_UART_Fun_Sel(GLB_UART_SIG_Type sig, GLB_UART_SIG_FUN_Type fun);
void GLB_Set_Cam_Ref_CLK(BL_Fun_Type enable, uint8_t clkSel, uint8_t clkDiv);
void GLB_Set_ClkOutSel(uint8_t clkout_num, uint8_t val);
BL_Err_Type GLB_PER_Clock_UnGate(uint64_t ips);
BL_Err_Type GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_Type swrst);

BL_Err_Type GLB_Config_CPU_PLL(GLB_XTAL_Type xtalType, const GLB_WAC_PLL_Cfg_Type * pllCfgList);
BL_Err_Type GLB_Config_MIPI_PLL(GLB_XTAL_Type xtalType, const GLB_MU_PLL_Cfg_Type * pllCfgList);
BL_Err_Type GLB_Config_MIPI_PLL_Div(uint8_t divEn, uint8_t divRatio);

BL_Err_Type GLB_Power_Off_MU_PLL(GLB_MU_PLL_Type pllType);
BL_Err_Type GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_Type pllType, GLB_PLL_REF_CLK_Type refClk);
BL_Err_Type GLB_Power_On_MU_PLL(GLB_MU_PLL_Type pllType, const GLB_MU_PLL_Cfg_Type *const cfg, uint8_t waitStable);
BL_Err_Type GLB_Set_Display_CLK(uint8_t enable, GLB_DISP_CLK_Type srcClk, uint8_t evenDiv);

BL_Err_Type GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_Type pllType);
BL_Err_Type GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_Type pllType, GLB_PLL_REF_CLK_Type refClk);
BL_Err_Type GLB_Power_On_WAC_PLL(GLB_WAC_PLL_Type pllType, const GLB_WAC_PLL_Cfg_Type *const cfg, uint8_t waitStable);

BL_Err_Type GLB_Set_Ldo15cis_Vout(GLB_LDO15CIS_LEVEL_Type ldoLevel);
BL_Err_Type GLB_CSI_Config_MIPIPLL(uint8_t postDivSel, uint32_t sdmin);
BL_Err_Type GLB_CSI_Power_Up_MIPIPLL(void);
/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL60x_Peripheral_Driver */

#endif /* __BL808_GLB_H__ */
