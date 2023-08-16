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
#ifndef  __BL80X_GPIO_H__
#define  __BL80X_GPIO_H__


typedef enum
{
    GLB_GPIO_PIN_0 = 0,
    GLB_GPIO_PIN_1,
    GLB_GPIO_PIN_2,
    GLB_GPIO_PIN_3,
    GLB_GPIO_PIN_4,
    GLB_GPIO_PIN_5,
    GLB_GPIO_PIN_6,
    GLB_GPIO_PIN_7,
    GLB_GPIO_PIN_8,
    GLB_GPIO_PIN_9,
    GLB_GPIO_PIN_10,
    GLB_GPIO_PIN_11,
    GLB_GPIO_PIN_12,
    GLB_GPIO_PIN_13,
    GLB_GPIO_PIN_14,
    GLB_GPIO_PIN_15,
    GLB_GPIO_PIN_16,
    GLB_GPIO_PIN_17,
    GLB_GPIO_PIN_18,
    GLB_GPIO_PIN_19,
    GLB_GPIO_PIN_20,
    GLB_GPIO_PIN_21,
    GLB_GPIO_PIN_22,
    GLB_GPIO_PIN_23,
    GLB_GPIO_PIN_24,
    GLB_GPIO_PIN_25,
    GLB_GPIO_PIN_26,
    GLB_GPIO_PIN_27,
    GLB_GPIO_PIN_28,
    GLB_GPIO_PIN_29,
    GLB_GPIO_PIN_30,
    GLB_GPIO_PIN_31,
    GLB_GPIO_PIN_32,
    GLB_GPIO_PIN_33,
    GLB_GPIO_PIN_34,
    GLB_GPIO_PIN_35,
    GLB_GPIO_PIN_36,
    GLB_GPIO_PIN_37,
    GLB_GPIO_PIN_38,
    GLB_GPIO_PIN_39,
    GLB_GPIO_PIN_40,
    GLB_GPIO_PIN_41,
    GLB_GPIO_PIN_42,
    GLB_GPIO_PIN_43,
    GLB_GPIO_PIN_44,
    GLB_GPIO_PIN_45,
    GLB_GPIO_PIN_46,
    GLB_GPIO_PIN_47,
    GLB_GPIO_PIN_48,
    GLB_GPIO_PIN_49,
    GLB_GPIO_PIN_50,
    GLB_GPIO_PIN_51,
    GLB_GPIO_PIN_52,
    GLB_GPIO_PIN_53,
    GLB_GPIO_PIN_MAX,
}GLB_GPIO_Type;

#define  GPIO_MODE_INPUT                        ((uint32_t)0x00000000U)   /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT                       ((uint32_t)0x00000001U)   /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_AF                           ((uint32_t)0x00000002U)   /*!< Alternate function                    */
#define  GPIO_PULL_UP                           ((uint32_t)0x00000000U)   /*!< GPIO pull up                          */
#define  GPIO_PULL_DOWN                         ((uint32_t)0x00000001U)   /*!< GPIO pull down                        */
#define  GPIO_PULL_NONE                         ((uint32_t)0x00000002U)   /*!< GPIO no pull up or down               */

#define  GPIO_FUN_AP_SWD                        0
#define  GPIO_FUN_NP_FLASH                      1
#define  GPIO_FUN_AP_FLASH                      2
#define  GPIO_FUN_I2S0                          3
#define  GPIO_FUN_SPI0                          4
#define  GPIO_FUN_SPI1                          5
#define  GPIO_FUN_I2C0                          6
#define  GPIO_FUN_UART                          7
#define  GPIO_FUN_PWM                           8
#define  GPIO_FUN_SPI2                          9
#define  GPIO_FUN_ADC_TOUCH                     10
#define  GPIO_FUN_GPIO                          11
#define  GPIO_FUN_RF_TEST                       12
#define  GPIO_FUN_SCAN                          13
#define  GPIO_FUN_NP_SWD                        14
#define  GPIO_FUN_CCI                           15
#define  GPIO_FUN_PDM0                          16
#define  GPIO_FUN_USB_DIGITAL                   17
#define  GPIO_FUN_UJTAG                         18

typedef struct
{
    uint8_t gpioPin;
    uint8_t gpioFun;
    uint8_t gpioMode;
    uint8_t pullType;
    uint8_t drive;
    uint8_t smtCtrl;
}GLB_GPIO_Cfg_Type;

/* GPIO0 function definition */
#define GPIO0_FUN_UNUSED0                       0
#define GPIO0_FUN_I2S0_BCLK                     6

/* GPIO1 function definition */
#define GPIO1_FUN_UNUSED0                       0
#define GPIO1_FUN_I2C0_SDA                      1
#define GPIO1_FUN_I2C1_SDA                      2
#define GPIO1_FUN_SPI_MOSI_SPI_MISO             3
#define GPIO1_FUN_UNUSED4                       4
#define GPIO1_FUN_HDMI_D_17                     5
#define GPIO1_FUN_I2S0_FS                       6
#define GPIO1_FUN_I2S1_FS                       7
#define GPIO1_FUN_PDM0_OUT                      8
#define GPIO1_FUN_PDM1_OUT                      9
#define GPIO1_FUN_UNUSED10                      10
#define GPIO1_FUN_REG_GPIO_1                    11
#define GPIO1_FUN_UART_CTS                      12
#define GPIO1_FUN_M4_SWCLK                      13
#define GPIO1_FUN_A5_SWDIO                      14
#define GPIO1_FUN_DEBUG_1                       15
#define GPIO1_FUN_UNUSED16                      16
#define GPIO1_FUN_UNUSED17                      17
#define GPIO1_FUN_UNUSED18                      18
/* GPIO2 function definition */
#define GPIO2_FUN_UNUSED0                       0
#define GPIO2_FUN_I2C0_SCL                      1
#define GPIO2_FUN_I2C1_SCL                      2
#define GPIO2_FUN_SPI_SS                        3
#define GPIO2_FUN_UNUSED4                       4
#define GPIO2_FUN_HDMI_HSYNC                    5
#define GPIO2_FUN_I2S0_DIO                      6
#define GPIO2_FUN_I2S1_DIO                      7
#define GPIO2_FUN_PDM0_OUT2                     8
#define GPIO2_FUN_PDM1_OUT2                     9
#define GPIO2_FUN_UNUSED10                      10
#define GPIO2_FUN_REG_GPIO_2                    11
#define GPIO2_FUN_UART_TXD                      12
#define GPIO2_FUN_M4_SWDIO                      13
#define GPIO2_FUN_A5_SWCLK                      14
#define GPIO2_FUN_DEBUG_2                       15
#define GPIO2_FUN_UNUSED16                      16
#define GPIO2_FUN_UNUSED17                      17
#define GPIO2_FUN_UNUSED18                      18
/* GPIO3 function definition */
#define GPIO3_FUN_UNUSED0                       0
#define GPIO3_FUN_I2C0_SDA                      1
#define GPIO3_FUN_I2C1_SDA                      2
#define GPIO3_FUN_SPI_SCLK                      3
#define GPIO3_FUN_UNUSED4                       4
#define GPIO3_FUN_HDMI_VSYNC                    5
#define GPIO3_FUN_I2S0_RCLK_O_I2S0_DI           6
#define GPIO3_FUN_I2S1_RCLK_O_I2S0_DI           7
#define GPIO3_FUN_PDM0_IN                       8
#define GPIO3_FUN_PDM1_IN                       9
#define GPIO3_FUN_UNUSED10                      10
#define GPIO3_FUN_REG_GPIO_3                    11
#define GPIO3_FUN_UART_RXD                      12
#define GPIO3_FUN_M4_SWV                        13
#define GPIO3_FUN_A5_SWDIO                      14
#define GPIO3_FUN_DEBUG_3                       15
#define GPIO3_FUN_UNUSED16                      16
#define GPIO3_FUN_UNUSED17                      17
#define GPIO3_FUN_UNUSED18                      18
/* GPIO4 function definition */
#define GPIO4_FUN_UNUSED0                       0
#define GPIO4_FUN_I2C0_SCL                      1
#define GPIO4_FUN_I2C1_SCL                      2
#define GPIO4_FUN_SPI_MISO_SPI_MOSI             3
#define GPIO4_FUN_UNUSED4                       4
#define GPIO4_FUN_HDMI_DE                       5
#define GPIO4_FUN_I2S0_BCLK                     6
#define GPIO4_FUN_I2S1_BCLK                     7
#define GPIO4_FUN_PDM0_SEL_OUT                  8
#define GPIO4_FUN_PDM1_SEL_OUT                  9
#define GPIO4_FUN_UNUSED10                      10
#define GPIO4_FUN_REG_GPIO_4                    11
#define GPIO4_FUN_UART_RTS                      12
#define GPIO4_FUN_M4_SWCLK                      13
#define GPIO4_FUN_A5_SWCLK                      14
#define GPIO4_FUN_DEBUG_4                       15
#define GPIO4_FUN_UNUSED16                      16
#define GPIO4_FUN_UNUSED17                      17
#define GPIO4_FUN_UNUSED18                      18
/* GPIO5 function definition */
#define GPIO5_FUN_PIX_DATA_0                    0
#define GPIO5_FUN_I2C0_SDA                      1
#define GPIO5_FUN_I2C1_SDA                      2
#define GPIO5_FUN_SPI_MOSI_SPI_MISO             3
#define GPIO5_FUN_UNUSED4                       4
#define GPIO5_FUN_UNUSED5                       5
#define GPIO5_FUN_I2S0_FS                       6
#define GPIO5_FUN_I2S1_FS                       7
#define GPIO5_FUN_PDM0_OUT                      8
#define GPIO5_FUN_PDM1_OUT                      9
#define GPIO5_FUN_UNUSED10                      10
#define GPIO5_FUN_REG_GPIO_5                    11
#define GPIO5_FUN_UART_CTS                      12
#define GPIO5_FUN_M4_SWDIO                      13
#define GPIO5_FUN_A5_SWDIO                      14
#define GPIO5_FUN_DEBUG_8                       15
#define GPIO5_FUN_UNUSED16                      16
#define GPIO5_FUN_UNUSED17                      17
#define GPIO5_FUN_UNUSED18                      18
/* GPIO6 function definition */
#define GPIO6_FUN_PIX_DATA_1                    0
#define GPIO6_FUN_I2C0_SCL                      1
#define GPIO6_FUN_I2C1_SCL                      2
#define GPIO6_FUN_SPI_SS                        3
#define GPIO6_FUN_UNUSED4                       4
#define GPIO6_FUN_UNUSED5                       5
#define GPIO6_FUN_I2S0_DIO                      6
#define GPIO6_FUN_I2S1_DIO                      7
#define GPIO6_FUN_PDM0_OUT2                     8
#define GPIO6_FUN_PDM1_OUT2                     9
#define GPIO6_FUN_UNUSED10                      10
#define GPIO6_FUN_REG_GPIO_6                    11
#define GPIO6_FUN_UART_TXD                      12
#define GPIO6_FUN_M4_SWV                        13
#define GPIO6_FUN_A5_SWCLK                      14
#define GPIO6_FUN_DEBUG_9                       15
#define GPIO6_FUN_UNUSED16                      16
#define GPIO6_FUN_UNUSED17                      17
#define GPIO6_FUN_UNUSED18                      18
/* GPIO7 function definition */
#define GPIO7_FUN_PIX_DATA_2                    0
#define GPIO7_FUN_I2C0_SDA                      1
#define GPIO7_FUN_I2C1_SDA                      2
#define GPIO7_FUN_SPI_SCLK                      3
#define GPIO7_FUN_UNUSED4                       4
#define GPIO7_FUN_UNUSED5                       5
#define GPIO7_FUN_I2S0_RCLK_O_I2S0_DI           6
#define GPIO7_FUN_I2S1_RCLK_O_I2S0_DI           7
#define GPIO7_FUN_PDM0_IN                       8
#define GPIO7_FUN_PDM1_IN                       9
#define GPIO7_FUN_UNUSED10                      10
#define GPIO7_FUN_REG_GPIO_7                    11
#define GPIO7_FUN_UART_RXD                      12
#define GPIO7_FUN_M4_SWCLK                      13
#define GPIO7_FUN_A5_SWDIO                      14
#define GPIO7_FUN_DEBUG_10                      15
#define GPIO7_FUN_UNUSED16                      16
#define GPIO7_FUN_UNUSED17                      17
#define GPIO7_FUN_UNUSED18                      18
/* GPIO8 function definition */
#define GPIO8_FUN_PIX_DATA_3                    0
#define GPIO8_FUN_I2C0_SCL                      1
#define GPIO8_FUN_I2C1_SCL                      2
#define GPIO8_FUN_SPI_MISO_SPI_MOSI             3
#define GPIO8_FUN_UNUSED4                       4
#define GPIO8_FUN_UNUSED5                       5
#define GPIO8_FUN_I2S0_BCLK                     6
#define GPIO8_FUN_I2S1_BCLK                     7
#define GPIO8_FUN_PDM0_SEL_OUT                  8
#define GPIO8_FUN_PDM1_SEL_OUT                  9
#define GPIO8_FUN_UNUSED10                      10
#define GPIO8_FUN_REG_GPIO_8                    11
#define GPIO8_FUN_UART_RTS                      12
#define GPIO8_FUN_M4_SWDIO                      13
#define GPIO8_FUN_A5_SWCLK                      14
#define GPIO8_FUN_DEBUG_11                      15
#define GPIO8_FUN_UNUSED16                      16
#define GPIO8_FUN_UNUSED17                      17
#define GPIO8_FUN_UNUSED18                      18
/* GPIO9 function definition */
#define GPIO9_FUN_PIX_DATA_4                    0
#define GPIO9_FUN_I2C0_SDA                      1
#define GPIO9_FUN_I2C1_SDA                      2
#define GPIO9_FUN_SPI_MOSI_SPI_MISO             3
#define GPIO9_FUN_UNUSED4                       4
#define GPIO9_FUN_UNUSED5                       5
#define GPIO9_FUN_I2S0_FS                       6
#define GPIO9_FUN_I2S1_FS                       7
#define GPIO9_FUN_PDM0_OUT                      8
#define GPIO9_FUN_PDM1_OUT                      9
#define GPIO9_FUN_UNUSED10                      10
#define GPIO9_FUN_REG_GPIO_9                    11
#define GPIO9_FUN_UART_CTS                      12
#define GPIO9_FUN_M4_SWV                        13
#define GPIO9_FUN_A5_SWDIO                      14
#define GPIO9_FUN_DEBUG_12                      15
#define GPIO9_FUN_UNUSED16                      16
#define GPIO9_FUN_UNUSED17                      17
#define GPIO9_FUN_UNUSED18                      18
/* GPIO10 function definition */
#define GPIO10_FUN_PIX_DATA_5                   0
#define GPIO10_FUN_I2C0_SCL                     1
#define GPIO10_FUN_I2C1_SCL                     2
#define GPIO10_FUN_SPI_SS                       3
#define GPIO10_FUN_UNUSED4                      4
#define GPIO10_FUN_UNUSED5                      5
#define GPIO10_FUN_I2S0_DIO                     6
#define GPIO10_FUN_I2S1_DIO                     7
#define GPIO10_FUN_PDM0_OUT2                    8
#define GPIO10_FUN_PDM1_OUT2                    9
#define GPIO10_FUN_UNUSED10                     10
#define GPIO10_FUN_REG_GPIO_10                  11
#define GPIO10_FUN_UART_TXD                     12
#define GPIO10_FUN_M4_SWCLK                     13
#define GPIO10_FUN_A5_SWCLK                     14
#define GPIO10_FUN_DEBUG_13                     15
#define GPIO10_FUN_UNUSED16                     16
#define GPIO10_FUN_UNUSED17                     17
#define GPIO10_FUN_UNUSED18                     18
/* GPIO11 function definition */
#define GPIO11_FUN_PIX_CLK                      0
#define GPIO11_FUN_I2C0_SDA                     1
#define GPIO11_FUN_I2C1_SDA                     2
#define GPIO11_FUN_SPI_SCLK                     3
#define GPIO11_FUN_UNUSED4                      4
#define GPIO11_FUN_UNUSED5                      5
#define GPIO11_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO11_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO11_FUN_PDM0_IN                      8
#define GPIO11_FUN_PDM1_IN                      9
#define GPIO11_FUN_UNUSED10                     10
#define GPIO11_FUN_REG_GPIO_11                  11
#define GPIO11_FUN_UART_RXD                     12
#define GPIO11_FUN_M4_SWDIO                     13
#define GPIO11_FUN_A5_SWDIO                     14
#define GPIO11_FUN_DEBUG_14                     15
#define GPIO11_FUN_UNUSED16                     16
#define GPIO11_FUN_UNUSED17                     17
#define GPIO11_FUN_UNUSED18                     18
/* GPIO12 function definition */
#define GPIO12_FUN_PIX_DATA_6                   0
#define GPIO12_FUN_I2C0_SCL                     1
#define GPIO12_FUN_I2C1_SCL                     2
#define GPIO12_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO12_FUN_UNUSED4                      4
#define GPIO12_FUN_UNUSED5                      5
#define GPIO12_FUN_I2S0_BCLK                    6
#define GPIO12_FUN_I2S1_BCLK                    7
#define GPIO12_FUN_PDM0_SEL_OUT                 8
#define GPIO12_FUN_PDM1_SEL_OUT                 9
#define GPIO12_FUN_UNUSED10                     10
#define GPIO12_FUN_REG_GPIO_12                  11
#define GPIO12_FUN_UART_RTS                     12
#define GPIO12_FUN_M4_SWV                       13
#define GPIO12_FUN_A5_SWCLK                     14
#define GPIO12_FUN_DEBUG_15                     15
#define GPIO12_FUN_UNUSED16                     16
#define GPIO12_FUN_UNUSED17                     17
#define GPIO12_FUN_UNUSED18                     18
/* GPIO13 function definition */
#define GPIO13_FUN_PIX_DATA_7                   0
#define GPIO13_FUN_I2C0_SDA                     1
#define GPIO13_FUN_I2C1_SDA                     2
#define GPIO13_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO13_FUN_UNUSED4                      4
#define GPIO13_FUN_UNUSED5                      5
#define GPIO13_FUN_I2S0_FS                      6
#define GPIO13_FUN_I2S1_FS                      7
#define GPIO13_FUN_PDM0_OUT                     8
#define GPIO13_FUN_PDM1_OUT                     9
#define GPIO13_FUN_UNUSED10                     10
#define GPIO13_FUN_REG_GPIO_13                  11
#define GPIO13_FUN_UART_CTS                     12
#define GPIO13_FUN_M4_SWCLK                     13
#define GPIO13_FUN_A5_SWDIO                     14
#define GPIO13_FUN_DEBUG_16                     15
#define GPIO13_FUN_UNUSED16                     16
#define GPIO13_FUN_UNUSED17                     17
#define GPIO13_FUN_UNUSED18                     18
/* GPIO14 function definition */
#define GPIO14_FUN_PIX_DATA_8                   0
#define GPIO14_FUN_I2C0_SCL                     1
#define GPIO14_FUN_I2C1_SCL                     2
#define GPIO14_FUN_SPI_SS                       3
#define GPIO14_FUN_UNUSED4                      4
#define GPIO14_FUN_UNUSED5                      5
#define GPIO14_FUN_I2S0_DIO                     6
#define GPIO14_FUN_I2S1_DIO                     7
#define GPIO14_FUN_PDM0_OUT2                    8
#define GPIO14_FUN_PDM1_OUT2                    9
#define GPIO14_FUN_UNUSED10                     10
#define GPIO14_FUN_REG_GPIO_14                  11
#define GPIO14_FUN_UART_TXD                     12
#define GPIO14_FUN_M4_SWDIO                     13
#define GPIO14_FUN_A5_SWCLK                     14
#define GPIO14_FUN_DEBUG_17                     15
#define GPIO14_FUN_UNUSED16                     16
#define GPIO14_FUN_UNUSED17                     17
#define GPIO14_FUN_UNUSED18                     18
/* GPIO15 function definition */
#define GPIO15_FUN_PIX_DATA_9                   0
#define GPIO15_FUN_I2C0_SDA                     1
#define GPIO15_FUN_I2C1_SDA                     2
#define GPIO15_FUN_SPI_SCLK                     3
#define GPIO15_FUN_UNUSED4                      4
#define GPIO15_FUN_UNUSED5                      5
#define GPIO15_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO15_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO15_FUN_PDM0_IN                      8
#define GPIO15_FUN_PDM1_IN                      9
#define GPIO15_FUN_UNUSED10                     10
#define GPIO15_FUN_REG_GPIO_15                  11
#define GPIO15_FUN_UART_RXD                     12
#define GPIO15_FUN_M4_SWV                       13
#define GPIO15_FUN_A5_SWDIO                     14
#define GPIO15_FUN_DEBUG_18                     15
#define GPIO15_FUN_UNUSED16                     16
#define GPIO15_FUN_UNUSED17                     17
#define GPIO15_FUN_UNUSED18                     18
/* GPIO16 function definition */
#define GPIO16_FUN_PIX_DATA_10                  0
#define GPIO16_FUN_I2C0_SCL                     1
#define GPIO16_FUN_I2C1_SCL                     2
#define GPIO16_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO16_FUN_UNUSED4                      4
#define GPIO16_FUN_UNUSED5                      5
#define GPIO16_FUN_I2S0_BCLK                    6
#define GPIO16_FUN_I2S1_BCLK                    7
#define GPIO16_FUN_PDM0_SEL_OUT                 8
#define GPIO16_FUN_PDM1_SEL_OUT                 9
#define GPIO16_FUN_UNUSED10                     10
#define GPIO16_FUN_REG_GPIO_16                  11
#define GPIO16_FUN_UART_RTS                     12
#define GPIO16_FUN_M4_SWCLK                     13
#define GPIO16_FUN_A5_SWCLK                     14
#define GPIO16_FUN_DEBUG_19                     15
#define GPIO16_FUN_UNUSED16                     16
#define GPIO16_FUN_UNUSED17                     17
#define GPIO16_FUN_UNUSED18                     18
/* GPIO17 function definition */
#define GPIO17_FUN_PIX_DATA_11                  0
#define GPIO17_FUN_I2C0_SDA                     1
#define GPIO17_FUN_I2C1_SDA                     2
#define GPIO17_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO17_FUN_UNUSED4                      4
#define GPIO17_FUN_UNUSED5                      5
#define GPIO17_FUN_I2S0_FS                      6
#define GPIO17_FUN_I2S1_FS                      7
#define GPIO17_FUN_PDM0_OUT                     8
#define GPIO17_FUN_PDM1_OUT                     9
#define GPIO17_FUN_UNUSED10                     10
#define GPIO17_FUN_REG_GPIO_17                  11
#define GPIO17_FUN_UART_CTS                     12
#define GPIO17_FUN_M4_SWDIO                     13
#define GPIO17_FUN_A5_SWDIO                     14
#define GPIO17_FUN_DEBUG_20                     15
#define GPIO17_FUN_UNUSED16                     16
#define GPIO17_FUN_UNUSED17                     17
#define GPIO17_FUN_UNUSED18                     18
/* GPIO18 function definition */
#define GPIO18_FUN_HSYNC                        0
#define GPIO18_FUN_I2C0_SCL                     1
#define GPIO18_FUN_I2C1_SCL                     2
#define GPIO18_FUN_SPI_SS                       3
#define GPIO18_FUN_UNUSED4                      4
#define GPIO18_FUN_UNUSED5                      5
#define GPIO18_FUN_I2S0_DIO                     6
#define GPIO18_FUN_I2S1_DIO                     7
#define GPIO18_FUN_PDM0_OUT2                    8
#define GPIO18_FUN_PDM1_OUT2                    9
#define GPIO18_FUN_UNUSED10                     10
#define GPIO18_FUN_REG_GPIO_18                  11
#define GPIO18_FUN_UART_TXD                     12
#define GPIO18_FUN_M4_SWV                       13
#define GPIO18_FUN_A5_SWCLK                     14
#define GPIO18_FUN_DEBUG_21                     15
#define GPIO18_FUN_UNUSED16                     16
#define GPIO18_FUN_UNUSED17                     17
#define GPIO18_FUN_UNUSED18                     18
/* GPIO19 function definition */
#define GPIO19_FUN_VSYNC                        0
#define GPIO19_FUN_I2C0_SDA                     1
#define GPIO19_FUN_I2C1_SDA                     2
#define GPIO19_FUN_SPI_SCLK                     3
#define GPIO19_FUN_UNUSED4                      4
#define GPIO19_FUN_UNUSED5                      5
#define GPIO19_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO19_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO19_FUN_PDM0_IN                      8
#define GPIO19_FUN_PDM1_IN                      9
#define GPIO19_FUN_UNUSED10                     10
#define GPIO19_FUN_REG_GPIO_19                  11
#define GPIO19_FUN_UART_RXD                     12
#define GPIO19_FUN_M4_SWCLK                     13
#define GPIO19_FUN_A5_SWDIO                     14
#define GPIO19_FUN_DEBUG_22                     15
#define GPIO19_FUN_UNUSED16                     16
#define GPIO19_FUN_UNUSED17                     17
#define GPIO19_FUN_UNUSED18                     18
/* GPIO20 function definition */
#define GPIO20_FUN_REF_CLK_O                    0
#define GPIO20_FUN_I2C0_SCL                     1
#define GPIO20_FUN_I2C1_SCL                     2
#define GPIO20_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO20_FUN_UNUSED4                      4
#define GPIO20_FUN_UNUSED5                      5
#define GPIO20_FUN_I2S0_BCLK                    6
#define GPIO20_FUN_I2S1_BCLK                    7
#define GPIO20_FUN_PDM0_SEL_OUT                 8
#define GPIO20_FUN_PDM1_SEL_OUT                 9
#define GPIO20_FUN_UNUSED10                     10
#define GPIO20_FUN_REG_GPIO_20                  11
#define GPIO20_FUN_UART_RTS                     12
#define GPIO20_FUN_M4_SWDIO                     13
#define GPIO20_FUN_A5_SWCLK                     14
#define GPIO20_FUN_DEBUG_23                     15
#define GPIO20_FUN_UNUSED16                     16
#define GPIO20_FUN_UNUSED17                     17
#define GPIO20_FUN_UNUSED18                     18
/* GPIO21 function definition */
#define GPIO21_FUN_RESET_O                      0
#define GPIO21_FUN_I2C0_SDA                     1
#define GPIO21_FUN_I2C1_SDA                     2
#define GPIO21_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO21_FUN_UNUSED4                      4
#define GPIO21_FUN_UNUSED5                      5
#define GPIO21_FUN_I2S0_FS                      6
#define GPIO21_FUN_I2S1_FS                      7
#define GPIO21_FUN_PDM0_OUT                     8
#define GPIO21_FUN_PDM1_OUT                     9
#define GPIO21_FUN_UNUSED10                     10
#define GPIO21_FUN_REG_GPIO_21                  11
#define GPIO21_FUN_UART_CTS                     12
#define GPIO21_FUN_M4_SWV                       13
#define GPIO21_FUN_A5_SWDIO                     14
#define GPIO21_FUN_DEBUG_24                     15
#define GPIO21_FUN_UNUSED16                     16
#define GPIO21_FUN_UNUSED17                     17
#define GPIO21_FUN_UNUSED18                     18
/* GPIO22 function definition */
#define GPIO22_FUN_UNUSED0                      0
#define GPIO22_FUN_I2C0_SCL                     1
#define GPIO22_FUN_I2C1_SCL                     2
#define GPIO22_FUN_SPI_SS                       3
#define GPIO22_FUN_UNUSED4                      4
#define GPIO22_FUN_UNUSED5                      5
#define GPIO22_FUN_I2S0_DIO                     6
#define GPIO22_FUN_I2S1_DIO                     7
#define GPIO22_FUN_PDM0_OUT2                    8
#define GPIO22_FUN_PDM1_OUT2                    9
#define GPIO22_FUN_UNUSED10                     10
#define GPIO22_FUN_REG_GPIO_22                  11
#define GPIO22_FUN_UART_TXD                     12
#define GPIO22_FUN_M4_SWCLK                     13
#define GPIO22_FUN_A5_SWCLK                     14
#define GPIO22_FUN_DEBUG_25                     15
#define GPIO22_FUN_UNUSED16                     16
#define GPIO22_FUN_UNUSED17                     17
#define GPIO22_FUN_UNUSED18                     18
/* GPIO23 function definition */
#define GPIO23_FUN_UNUSED0                      0
#define GPIO23_FUN_I2C0_SDA                     1
#define GPIO23_FUN_I2C1_SDA                     2
#define GPIO23_FUN_SPI_SCLK                     3
#define GPIO23_FUN_UNUSED4                      4
#define GPIO23_FUN_UNUSED5                      5
#define GPIO23_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO23_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO23_FUN_PDM0_IN                      8
#define GPIO23_FUN_PDM1_IN                      9
#define GPIO23_FUN_UNUSED10                     10
#define GPIO23_FUN_REG_GPIO_23                  11
#define GPIO23_FUN_UART_RXD                     12
#define GPIO23_FUN_M4_SWDIO                     13
#define GPIO23_FUN_A5_SWDIO                     14
#define GPIO23_FUN_DEBUG_26                     15
#define GPIO23_FUN_UNUSED16                     16
#define GPIO23_FUN_UNUSED17                     17
#define GPIO23_FUN_UNUSED18                     18
/* GPIO24 function definition */
#define GPIO24_FUN_UNUSED0                      0
#define GPIO24_FUN_I2C0_SCL                     1
#define GPIO24_FUN_I2C1_SCL                     2
#define GPIO24_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO24_FUN_UNUSED4                      4
#define GPIO24_FUN_UNUSED5                      5
#define GPIO24_FUN_I2S0_BCLK                    6
#define GPIO24_FUN_I2S1_BCLK                    7
#define GPIO24_FUN_PDM0_SEL_OUT                 8
#define GPIO24_FUN_PDM1_SEL_OUT                 9
#define GPIO24_FUN_UNUSED10                     10
#define GPIO24_FUN_REG_GPIO_24                  11
#define GPIO24_FUN_UART_RTS                     12
#define GPIO24_FUN_M4_SWV                       13
#define GPIO24_FUN_A5_SWCLK                     14
#define GPIO24_FUN_DEBUG_27                     15
#define GPIO24_FUN_UNUSED16                     16
#define GPIO24_FUN_UNUSED17                     17
#define GPIO24_FUN_UNUSED18                     18
/* GPIO25 function definition */
#define GPIO25_FUN_UNUSED0                      0
#define GPIO25_FUN_I2C0_SDA                     1
#define GPIO25_FUN_I2C1_SDA                     2
#define GPIO25_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO25_FUN_UNUSED4                      4
#define GPIO25_FUN_UNUSED5                      5
#define GPIO25_FUN_I2S0_FS                      6
#define GPIO25_FUN_I2S1_FS                      7
#define GPIO25_FUN_PDM0_OUT                     8
#define GPIO25_FUN_PDM1_OUT                     9
#define GPIO25_FUN_UNUSED10                     10
#define GPIO25_FUN_REG_GPIO_25                  11
#define GPIO25_FUN_UART_CTS                     12
#define GPIO25_FUN_M4_SWCLK                     13
#define GPIO25_FUN_A5_SWDIO                     14
#define GPIO25_FUN_DEBUG_28                     15
#define GPIO25_FUN_UNUSED16                     16
#define GPIO25_FUN_UNUSED17                     17
#define GPIO25_FUN_UNUSED18                     18
/* GPIO26 function definition */
#define GPIO26_FUN_UNUSED0                      0
#define GPIO26_FUN_I2C0_SCL                     1
#define GPIO26_FUN_I2C1_SCL                     2
#define GPIO26_FUN_SPI_SS                       3
#define GPIO26_FUN_UNUSED4                      4
#define GPIO26_FUN_UNUSED5                      5
#define GPIO26_FUN_I2S0_DIO                     6
#define GPIO26_FUN_I2S1_DIO                     7
#define GPIO26_FUN_PDM0_OUT2                    8
#define GPIO26_FUN_PDM1_OUT2                    9
#define GPIO26_FUN_UNUSED10                     10
#define GPIO26_FUN_REG_GPIO_26                  11
#define GPIO26_FUN_UART_TXD                     12
#define GPIO26_FUN_M4_SWDIO                     13
#define GPIO26_FUN_A5_SWCLK                     14
#define GPIO26_FUN_DEBUG_29                     15
#define GPIO26_FUN_UNUSED16                     16
#define GPIO26_FUN_UNUSED17                     17
#define GPIO26_FUN_UNUSED18                     18
/* GPIO27 function definition */
#define GPIO27_FUN_UNUSED0                      0
#define GPIO27_FUN_I2C0_SDA                     1
#define GPIO27_FUN_I2C1_SDA                     2
#define GPIO27_FUN_SPI_SCLK                     3
#define GPIO27_FUN_UNUSED4                      4
#define GPIO27_FUN_UNUSED5                      5
#define GPIO27_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO27_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO27_FUN_PDM0_IN                      8
#define GPIO27_FUN_PDM1_IN                      9
#define GPIO27_FUN_UNUSED10                     10
#define GPIO27_FUN_REG_GPIO_27                  11
#define GPIO27_FUN_UART_RXD                     12
#define GPIO27_FUN_M4_SWV                       13
#define GPIO27_FUN_A5_SWDIO                     14
#define GPIO27_FUN_DEBUG_30                     15
#define GPIO27_FUN_UNUSED16                     16
#define GPIO27_FUN_UNUSED17                     17
#define GPIO27_FUN_UNUSED18                     18
/* GPIO28 function definition */
#define GPIO28_FUN_UNUSED0                      0
#define GPIO28_FUN_I2C0_SCL                     1
#define GPIO28_FUN_I2C1_SCL                     2
#define GPIO28_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO28_FUN_UNUSED4                      4
#define GPIO28_FUN_UNUSED5                      5
#define GPIO28_FUN_I2S0_BCLK                    6
#define GPIO28_FUN_I2S1_BCLK                    7
#define GPIO28_FUN_PDM0_SEL_OUT                 8
#define GPIO28_FUN_PDM1_SEL_OUT                 9
#define GPIO28_FUN_UNUSED10                     10
#define GPIO28_FUN_REG_GPIO_28                  11
#define GPIO28_FUN_UART_RTS                     12
#define GPIO28_FUN_M4_SWCLK                     13
#define GPIO28_FUN_A5_SWCLK                     14
#define GPIO28_FUN_DEBUG_31                     15
#define GPIO28_FUN_UNUSED16                     16
#define GPIO28_FUN_UNUSED17                     17
#define GPIO28_FUN_UNUSED18                     18
/* GPIO29 function definition */
#define GPIO29_FUN_UNUSED0                      0
#define GPIO29_FUN_I2C0_SDA                     1
#define GPIO29_FUN_I2C1_SDA                     2
#define GPIO29_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO29_FUN_UNUSED4                      4
#define GPIO29_FUN_UNUSED5                      5
#define GPIO29_FUN_I2S0_FS                      6
#define GPIO29_FUN_I2S1_FS                      7
#define GPIO29_FUN_PDM0_OUT                     8
#define GPIO29_FUN_PDM1_OUT                     9
#define GPIO29_FUN_UNUSED10                     10
#define GPIO29_FUN_REG_GPIO_29                  11
#define GPIO29_FUN_UART_CTS                     12
#define GPIO29_FUN_M4_SWDIO                     13
#define GPIO29_FUN_A5_SWDIO                     14
#define GPIO29_FUN_UNUSED15                     15
#define GPIO29_FUN_UNUSED16                     16
#define GPIO29_FUN_UNUSED17                     17
#define GPIO29_FUN_UNUSED18                     18
/* GPIO30 function definition */
#define GPIO30_FUN_UNUSED0                      0
#define GPIO30_FUN_I2C0_SCL                     1
#define GPIO30_FUN_I2C1_SCL                     2
#define GPIO30_FUN_SPI_SS                       3
#define GPIO30_FUN_SDH_CLK                      4
#define GPIO30_FUN_UNUSED5                      5
#define GPIO30_FUN_I2S0_DIO                     6
#define GPIO30_FUN_I2S1_DIO                     7
#define GPIO30_FUN_PDM0_OUT2                    8
#define GPIO30_FUN_PDM1_OUT2                    9
#define GPIO30_FUN_UNUSED10                     10
#define GPIO30_FUN_REG_GPIO_30                  11
#define GPIO30_FUN_UART_TXD                     12
#define GPIO30_FUN_M4_SWV                       13
#define GPIO30_FUN_A5_SWCLK                     14
#define GPIO30_FUN_S_CCI_DAT1                   15
#define GPIO30_FUN_UNUSED16                     16
#define GPIO30_FUN_UNUSED17                     17
#define GPIO30_FUN_UNUSED18                     18
/* GPIO31 function definition */
#define GPIO31_FUN_UNUSED0                      0
#define GPIO31_FUN_I2C0_SDA                     1
#define GPIO31_FUN_I2C1_SDA                     2
#define GPIO31_FUN_SPI_SCLK                     3
#define GPIO31_FUN_SDH_CMD                      4
#define GPIO31_FUN_UNUSED5                      5
#define GPIO31_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO31_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO31_FUN_PDM0_IN                      8
#define GPIO31_FUN_PDM1_IN                      9
#define GPIO31_FUN_UNUSED10                     10
#define GPIO31_FUN_REG_GPIO_31                  11
#define GPIO31_FUN_UART_RXD                     12
#define GPIO31_FUN_M4_SWCLK                     13
#define GPIO31_FUN_A5_SWDIO                     14
#define GPIO31_FUN_S_CCI_DAT0                   15
#define GPIO31_FUN_UNUSED16                     16
#define GPIO31_FUN_UNUSED17                     17
#define GPIO31_FUN_UNUSED18                     18
/* GPIO32 function definition */
#define GPIO32_FUN_UNUSED0                      0
#define GPIO32_FUN_I2C0_SCL                     1
#define GPIO32_FUN_I2C1_SCL                     2
#define GPIO32_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO32_FUN_SDH_DAT0                     4
#define GPIO32_FUN_UNUSED5                      5
#define GPIO32_FUN_I2S0_BCLK                    6
#define GPIO32_FUN_I2S1_BCLK                    7
#define GPIO32_FUN_PDM0_SEL_OUT                 8
#define GPIO32_FUN_PDM1_SEL_OUT                 9
#define GPIO32_FUN_UNUSED10                     10
#define GPIO32_FUN_REG_GPIO_32                  11
#define GPIO32_FUN_UART_RTS                     12
#define GPIO32_FUN_M4_SWDIO                     13
#define GPIO32_FUN_A5_SWCLK                     14
#define GPIO32_FUN_S_CCI_CS                     15
#define GPIO32_FUN_UNUSED16                     16
#define GPIO32_FUN_UNUSED17                     17
#define GPIO32_FUN_UNUSED18                     18
/* GPIO33 function definition */
#define GPIO33_FUN_UNUSED0                      0
#define GPIO33_FUN_I2C0_SDA                     1
#define GPIO33_FUN_I2C1_SDA                     2
#define GPIO33_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO33_FUN_SDH_DAT1                     4
#define GPIO33_FUN_UNUSED5                      5
#define GPIO33_FUN_I2S0_FS                      6
#define GPIO33_FUN_I2S1_FS                      7
#define GPIO33_FUN_PDM0_OUT                     8
#define GPIO33_FUN_PDM1_OUT                     9
#define GPIO33_FUN_UNUSED10                     10
#define GPIO33_FUN_REG_GPIO_33                  11
#define GPIO33_FUN_UART_CTS                     12
#define GPIO33_FUN_M4_SWV                       13
#define GPIO33_FUN_A5_SWDIO                     14
#define GPIO33_FUN_S_CCI_CLK                    15
#define GPIO33_FUN_UNUSED16                     16
#define GPIO33_FUN_UNUSED17                     17
#define GPIO33_FUN_UNUSED18                     18
/* GPIO34 function definition */
#define GPIO34_FUN_UNUSED0                      0
#define GPIO34_FUN_I2C0_SCL                     1
#define GPIO34_FUN_I2C1_SCL                     2
#define GPIO34_FUN_SPI_SS                       3
#define GPIO34_FUN_SDH_DAT2                     4
#define GPIO34_FUN_UNUSED5                      5
#define GPIO34_FUN_I2S0_DIO                     6
#define GPIO34_FUN_I2S1_DIO                     7
#define GPIO34_FUN_PDM0_OUT2                    8
#define GPIO34_FUN_PDM1_OUT2                    9
#define GPIO34_FUN_UNUSED10                     10
#define GPIO34_FUN_REG_GPIO_34                  11
#define GPIO34_FUN_UART_TXD                     12
#define GPIO34_FUN_M4_SWCLK                     13
#define GPIO34_FUN_A5_SWCLK                     14
#define GPIO34_FUN_UNUSED15                     15
#define GPIO34_FUN_UNUSED16                     16
#define GPIO34_FUN_UNUSED17                     17
#define GPIO34_FUN_UNUSED18                     18
/* GPIO35 function definition */
#define GPIO35_FUN_UNUSED0                      0
#define GPIO35_FUN_I2C0_SDA                     1
#define GPIO35_FUN_I2C1_SDA                     2
#define GPIO35_FUN_SPI_SCLK                     3
#define GPIO35_FUN_SDH_DAT3                     4
#define GPIO35_FUN_UNUSED5                      5
#define GPIO35_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO35_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO35_FUN_PDM0_IN                      8
#define GPIO35_FUN_PDM1_IN                      9
#define GPIO35_FUN_UNUSED10                     10
#define GPIO35_FUN_REG_GPIO_35                  11
#define GPIO35_FUN_UART_RXD                     12
#define GPIO35_FUN_M4_SWDIO                     13
#define GPIO35_FUN_A5_SWDIO                     14
#define GPIO35_FUN_UNUSED15                     15
#define GPIO35_FUN_UNUSED16                     16
#define GPIO35_FUN_UNUSED17                     17
#define GPIO35_FUN_UNUSED18                     18
/* GPIO36 function definition */
#define GPIO36_FUN_UNUSED0                      0
#define GPIO36_FUN_I2C0_SCL                     1
#define GPIO36_FUN_I2C1_SCL                     2
#define GPIO36_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO36_FUN_UNUSED4                      4
#define GPIO36_FUN_UNUSED5                      5
#define GPIO36_FUN_I2S0_BCLK                    6
#define GPIO36_FUN_I2S1_BCLK                    7
#define GPIO36_FUN_PDM0_SEL_OUT                 8
#define GPIO36_FUN_PDM1_SEL_OUT                 9
#define GPIO36_FUN_UNUSED10                     10
#define GPIO36_FUN_REG_GPIO_36                  11
#define GPIO36_FUN_UART_RTS                     12
#define GPIO36_FUN_M4_SWV                       13
#define GPIO36_FUN_A5_SWCLK                     14
#define GPIO36_FUN_M_CCI_CLK                    15
#define GPIO36_FUN_UNUSED16                     16
#define GPIO36_FUN_UNUSED17                     17
#define GPIO36_FUN_UNUSED18                     18
/* GPIO37 function definition */
#define GPIO37_FUN_UNUSED0                      0
#define GPIO37_FUN_I2C0_SDA                     1
#define GPIO37_FUN_I2C1_SDA                     2
#define GPIO37_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO37_FUN_UNUSED4                      4
#define GPIO37_FUN_HDMI_D_0                     5
#define GPIO37_FUN_I2S0_FS                      6
#define GPIO37_FUN_I2S1_FS                      7
#define GPIO37_FUN_PDM0_OUT                     8
#define GPIO37_FUN_PDM1_OUT                     9
#define GPIO37_FUN_UNUSED10                     10
#define GPIO37_FUN_REG_GPIO_37                  11
#define GPIO37_FUN_UART_CTS                     12
#define GPIO37_FUN_M4_SWCLK                     13
#define GPIO37_FUN_A5_SWDIO                     14
#define GPIO37_FUN_M_CCI_CS                     15
#define GPIO37_FUN_UNUSED16                     16
#define GPIO37_FUN_UNUSED17                     17
#define GPIO37_FUN_UNUSED18                     18
/* GPIO38 function definition */
#define GPIO38_FUN_UNUSED0                      0
#define GPIO38_FUN_I2C0_SCL                     1
#define GPIO38_FUN_I2C1_SCL                     2
#define GPIO38_FUN_SPI_SS                       3
#define GPIO38_FUN_UNUSED4                      4
#define GPIO38_FUN_HDMI_D_1                     5
#define GPIO38_FUN_I2S0_DIO                     6
#define GPIO38_FUN_I2S1_DIO                     7
#define GPIO38_FUN_PDM0_OUT2                    8
#define GPIO38_FUN_PDM1_OUT2                    9
#define GPIO38_FUN_UNUSED10                     10
#define GPIO38_FUN_REG_GPIO_38                  11
#define GPIO38_FUN_UART_TXD                     12
#define GPIO38_FUN_M4_SWDIO                     13
#define GPIO38_FUN_A5_SWCLK                     14
#define GPIO38_FUN_M_CCI_DAT0                   15
#define GPIO38_FUN_UNUSED16                     16
#define GPIO38_FUN_UNUSED17                     17
#define GPIO38_FUN_UNUSED18                     18
/* GPIO39 function definition */
#define GPIO39_FUN_UNUSED0                      0
#define GPIO39_FUN_I2C0_SDA                     1
#define GPIO39_FUN_I2C1_SDA                     2
#define GPIO39_FUN_SPI_SCLK                     3
#define GPIO39_FUN_UNUSED4                      4
#define GPIO39_FUN_HDMI_D_2                     5
#define GPIO39_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO39_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO39_FUN_PDM0_IN                      8
#define GPIO39_FUN_PDM1_IN                      9
#define GPIO39_FUN_UNUSED10                     10
#define GPIO39_FUN_REG_GPIO_39                  11
#define GPIO39_FUN_UART_RXD                     12
#define GPIO39_FUN_M4_SWV                       13
#define GPIO39_FUN_A5_SWDIO                     14
#define GPIO39_FUN_M_CCI_DAT1                   15
#define GPIO39_FUN_UNUSED16                     16
#define GPIO39_FUN_UNUSED17                     17
#define GPIO39_FUN_UNUSED18                     18
/* GPIO40 function definition */
#define GPIO40_FUN_UNUSED0                      0
#define GPIO40_FUN_I2C0_SCL                     1
#define GPIO40_FUN_I2C1_SCL                     2
#define GPIO40_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO40_FUN_SDH_CLK                      4
#define GPIO40_FUN_HDMI_D_3                     5
#define GPIO40_FUN_I2S0_BCLK                    6
#define GPIO40_FUN_I2S1_BCLK                    7
#define GPIO40_FUN_PDM0_SEL_OUT                 8
#define GPIO40_FUN_PDM1_SEL_OUT                 9
#define GPIO40_FUN_UNUSED10                     10
#define GPIO40_FUN_REG_GPIO_40                  11
#define GPIO40_FUN_UART_RTS                     12
#define GPIO40_FUN_M4_SWCLK                     13
#define GPIO40_FUN_A5_SWCLK                     14
#define GPIO40_FUN_M_CCI_CLK                    15
#define GPIO40_FUN_UNUSED16                     16
#define GPIO40_FUN_UNUSED17                     17
#define GPIO40_FUN_UNUSED18                     18
/* GPIO41 function definition */
#define GPIO41_FUN_UNUSED0                      0
#define GPIO41_FUN_I2C0_SDA                     1
#define GPIO41_FUN_I2C1_SDA                     2
#define GPIO41_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO41_FUN_SDH_CMD                      4
#define GPIO41_FUN_HDMI_D_4                     5
#define GPIO41_FUN_I2S0_FS                      6
#define GPIO41_FUN_I2S1_FS                      7
#define GPIO41_FUN_PDM0_OUT                     8
#define GPIO41_FUN_PDM1_OUT                     9
#define GPIO41_FUN_UNUSED10                     10
#define GPIO41_FUN_REG_GPIO_41                  11
#define GPIO41_FUN_UART_CTS                     12
#define GPIO41_FUN_M4_SWDIO                     13
#define GPIO41_FUN_A5_SWDIO                     14
#define GPIO41_FUN_M_CCI_CS                     15
#define GPIO41_FUN_UNUSED16                     16
#define GPIO41_FUN_UNUSED17                     17
#define GPIO41_FUN_UNUSED18                     18
/* GPIO42 function definition */
#define GPIO42_FUN_UNUSED0                      0
#define GPIO42_FUN_I2C0_SCL                     1
#define GPIO42_FUN_I2C1_SCL                     2
#define GPIO42_FUN_SPI_SS                       3
#define GPIO42_FUN_SDH_DAT0                     4
#define GPIO42_FUN_HDMI_D_5                     5
#define GPIO42_FUN_I2S0_DIO                     6
#define GPIO42_FUN_I2S1_DIO                     7
#define GPIO42_FUN_PDM0_OUT2                    8
#define GPIO42_FUN_PDM1_OUT2                    9
#define GPIO42_FUN_UNUSED10                     10
#define GPIO42_FUN_REG_GPIO_42                  11
#define GPIO42_FUN_UART_TXD                     12
#define GPIO42_FUN_M4_SWV                       13
#define GPIO42_FUN_A5_SWCLK                     14
#define GPIO42_FUN_M_CCI_DAT0                   15
#define GPIO42_FUN_UNUSED16                     16
#define GPIO42_FUN_UNUSED17                     17
#define GPIO42_FUN_UNUSED18                     18
/* GPIO43 function definition */
#define GPIO43_FUN_UNUSED0                      0
#define GPIO43_FUN_I2C0_SDA                     1
#define GPIO43_FUN_I2C1_SDA                     2
#define GPIO43_FUN_SPI_SCLK                     3
#define GPIO43_FUN_SDH_DAT1                     4
#define GPIO43_FUN_HDMI_D_6                     5
#define GPIO43_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO43_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO43_FUN_PDM0_IN                      8
#define GPIO43_FUN_PDM1_IN                      9
#define GPIO43_FUN_UNUSED10                     10
#define GPIO43_FUN_REG_GPIO_43                  11
#define GPIO43_FUN_UART_RXD                     12
#define GPIO43_FUN_M4_SWCLK                     13
#define GPIO43_FUN_A5_SWDIO                     14
#define GPIO43_FUN_M_CCI_DAT1                   15
#define GPIO43_FUN_UNUSED16                     16
#define GPIO43_FUN_UNUSED17                     17
#define GPIO43_FUN_UNUSED18                     18
/* GPIO44 function definition */
#define GPIO44_FUN_UNUSED0                      0
#define GPIO44_FUN_I2C0_SCL                     1
#define GPIO44_FUN_I2C1_SCL                     2
#define GPIO44_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO44_FUN_SDH_DAT2                     4
#define GPIO44_FUN_HDMI_D_7                     5
#define GPIO44_FUN_I2S0_BCLK                    6
#define GPIO44_FUN_I2S1_BCLK                    7
#define GPIO44_FUN_PDM0_SEL_OUT                 8
#define GPIO44_FUN_PDM1_SEL_OUT                 9
#define GPIO44_FUN_UNUSED10                     10
#define GPIO44_FUN_REG_GPIO_44                  11
#define GPIO44_FUN_UART_RTS                     12
#define GPIO44_FUN_M4_SWDIO                     13
#define GPIO44_FUN_A5_SWCLK                     14
#define GPIO44_FUN_UNUSED15                     15
#define GPIO44_FUN_UNUSED16                     16
#define GPIO44_FUN_UNUSED17                     17
#define GPIO44_FUN_UNUSED18                     18
/* GPIO45 function definition */
#define GPIO45_FUN_UNUSED0                      0
#define GPIO45_FUN_I2C0_SDA                     1
#define GPIO45_FUN_I2C1_SDA                     2
#define GPIO45_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO45_FUN_SDH_DAT3                     4
#define GPIO45_FUN_HDMI_D_8                     5
#define GPIO45_FUN_I2S0_FS                      6
#define GPIO45_FUN_I2S1_FS                      7
#define GPIO45_FUN_PDM0_OUT                     8
#define GPIO45_FUN_PDM1_OUT                     9
#define GPIO45_FUN_UNUSED10                     10
#define GPIO45_FUN_REG_GPIO_45                  11
#define GPIO45_FUN_UART_CTS                     12
#define GPIO45_FUN_M4_SWV                       13
#define GPIO45_FUN_A5_SWDIO                     14
#define GPIO45_FUN_UNUSED15                     15
#define GPIO45_FUN_UNUSED16                     16
#define GPIO45_FUN_UNUSED17                     17
#define GPIO45_FUN_UNUSED18                     18
/* GPIO46 function definition */
#define GPIO46_FUN_UNUSED0                      0
#define GPIO46_FUN_I2C0_SCL                     1
#define GPIO46_FUN_I2C1_SCL                     2
#define GPIO46_FUN_SPI_SS                       3
#define GPIO46_FUN_UNUSED4                      4
#define GPIO46_FUN_HDMI_D_9                     5
#define GPIO46_FUN_I2S0_DIO                     6
#define GPIO46_FUN_I2S1_DIO                     7
#define GPIO46_FUN_PDM0_OUT2                    8
#define GPIO46_FUN_PDM1_OUT2                    9
#define GPIO46_FUN_UNUSED10                     10
#define GPIO46_FUN_REG_GPIO_46                  11
#define GPIO46_FUN_UART_TXD                     12
#define GPIO46_FUN_M4_SWCLK                     13
#define GPIO46_FUN_A5_SWCLK                     14
#define GPIO46_FUN_UNUSED15                     15
#define GPIO46_FUN_UNUSED16                     16
#define GPIO46_FUN_UNUSED17                     17
#define GPIO46_FUN_UNUSED18                     18
/* GPIO47 function definition */
#define GPIO47_FUN_UNUSED0                      0
#define GPIO47_FUN_I2C0_SDA                     1
#define GPIO47_FUN_I2C1_SDA                     2
#define GPIO47_FUN_SPI_SCLK                     3
#define GPIO47_FUN_UNUSED4                      4
#define GPIO47_FUN_HDMI_CK                      5
#define GPIO47_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO47_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO47_FUN_PDM0_IN                      8
#define GPIO47_FUN_PDM1_IN                      9
#define GPIO47_FUN_UNUSED10                     10
#define GPIO47_FUN_REG_GPIO_47                  11
#define GPIO47_FUN_UART_RXD                     12
#define GPIO47_FUN_M4_SWDIO                     13
#define GPIO47_FUN_A5_SWDIO                     14
#define GPIO47_FUN_S_CCI_DAT1                   15
#define GPIO47_FUN_UNUSED16                     16
#define GPIO47_FUN_UNUSED17                     17
#define GPIO47_FUN_UNUSED18                     18
/* GPIO48 function definition */
#define GPIO48_FUN_UNUSED0                      0
#define GPIO48_FUN_I2C0_SCL                     1
#define GPIO48_FUN_I2C1_SCL                     2
#define GPIO48_FUN_SPI_MISO_SPI_MOSI            3
#define GPIO48_FUN_UNUSED4                      4
#define GPIO48_FUN_HDMI_D_10                    5
#define GPIO48_FUN_I2S0_BCLK                    6
#define GPIO48_FUN_I2S1_BCLK                    7
#define GPIO48_FUN_PDM0_SEL_OUT                 8
#define GPIO48_FUN_PDM1_SEL_OUT                 9
#define GPIO48_FUN_UNUSED10                     10
#define GPIO48_FUN_REG_GPIO_48                  11
#define GPIO48_FUN_UART_RTS                     12
#define GPIO48_FUN_M4_SWV                       13
#define GPIO48_FUN_A5_SWCLK                     14
#define GPIO48_FUN_S_CCI_DAT0                   15
#define GPIO48_FUN_UNUSED16                     16
#define GPIO48_FUN_UNUSED17                     17
#define GPIO48_FUN_UNUSED18                     18
/* GPIO49 function definition */
#define GPIO49_FUN_UNUSED0                      0
#define GPIO49_FUN_I2C0_SDA                     1
#define GPIO49_FUN_I2C1_SDA                     2
#define GPIO49_FUN_SPI_MOSI_SPI_MISO            3
#define GPIO49_FUN_UNUSED4                      4
#define GPIO49_FUN_HDMI_D_11                    5
#define GPIO49_FUN_I2S0_FS                      6
#define GPIO49_FUN_I2S1_FS                      7
#define GPIO49_FUN_PDM0_OUT                     8
#define GPIO49_FUN_PDM1_OUT                     9
#define GPIO49_FUN_UNUSED10                     10
#define GPIO49_FUN_REG_GPIO_49                  11
#define GPIO49_FUN_UART_CTS                     12
#define GPIO49_FUN_M4_SWCLK                     13
#define GPIO49_FUN_A5_SWDIO                     14
#define GPIO49_FUN_S_CCI_CS                     15
#define GPIO49_FUN_UNUSED16                     16
#define GPIO49_FUN_UNUSED17                     17
#define GPIO49_FUN_UNUSED18                     18
/* GPIO50 function definition */
#define GPIO50_FUN_UNUSED0                      0
#define GPIO50_FUN_I2C0_SCL                     1
#define GPIO50_FUN_I2C1_SCL                     2
#define GPIO50_FUN_SPI_SS                       3
#define GPIO50_FUN_UNUSED4                      4
#define GPIO50_FUN_HDMI_D_12                    5
#define GPIO50_FUN_I2S0_DIO                     6
#define GPIO50_FUN_I2S1_DIO                     7
#define GPIO50_FUN_PDM0_OUT2                    8
#define GPIO50_FUN_PDM1_OUT2                    9
#define GPIO50_FUN_UNUSED10                     10
#define GPIO50_FUN_REG_GPIO_50                  11
#define GPIO50_FUN_UART_TXD                     12
#define GPIO50_FUN_M4_SWDIO                     13
#define GPIO50_FUN_A5_SWCLK                     14
#define GPIO50_FUN_S_CCI_CLK                    15
#define GPIO50_FUN_UNUSED16                     16
#define GPIO50_FUN_UNUSED17                     17
#define GPIO50_FUN_UNUSED18                     18
/* GPIO51 function definition */
#define GPIO51_FUN_UNUSED0                      0
#define GPIO51_FUN_I2C0_SDA                     1
#define GPIO51_FUN_I2C1_SDA                     2
#define GPIO51_FUN_SPI_SCLK                     3
#define GPIO51_FUN_UNUSED4                      4
#define GPIO51_FUN_HDMI_D_13                    5
#define GPIO51_FUN_I2S0_RCLK_O_I2S0_DI          6
#define GPIO51_FUN_I2S1_RCLK_O_I2S0_DI          7
#define GPIO51_FUN_PDM0_IN                      8
#define GPIO51_FUN_PDM1_IN                      9
#define GPIO51_FUN_UNUSED10                     10
#define GPIO51_FUN_REG_GPIO_51                  11
#define GPIO51_FUN_UART_RXD                     12
#define GPIO51_FUN_M4_SWV                       13
#define GPIO51_FUN_A5_SWDIO                     14
#define GPIO51_FUN_DEBUG_5                      15
#define GPIO51_FUN_UNUSED16                     16
#define GPIO51_FUN_UNUSED17                     17
#define GPIO51_FUN_UNUSED18                     18
/* GPIO52 function definition */
#define GPIO52_FUN_UNUSED0                      0
#define GPIO52_FUN_I2C0_SCL                     1
#define GPIO52_FUN_I2C1_SCL                     2
#define GPIO52_FUN_SPI_SS                       3
#define GPIO52_FUN_UNUSED4                      4
#define GPIO52_FUN_HDMI_D_14                    5
#define GPIO52_FUN_I2S0_BCLK                    6
#define GPIO52_FUN_I2S1_BCLK                    7
#define GPIO52_FUN_PDM0_SEL_OUT                 8
#define GPIO52_FUN_PDM1_SEL_OUT                 9
#define GPIO52_FUN_UNUSED10                     10
#define GPIO52_FUN_REG_GPIO_52                  11
#define GPIO52_FUN_UART_RTS                     12
#define GPIO52_FUN_M4_SWCLK                     13
#define GPIO52_FUN_A5_SWCLK                     14
#define GPIO52_FUN_DEBUG_6                      15
#define GPIO52_FUN_UNUSED16                     16
#define GPIO52_FUN_UNUSED17                     17
#define GPIO52_FUN_UNUSED18                     18
/* GPIO53 function definition */
#define GPIO53_FUN_UNUSED0                      0
#define GPIO53_FUN_I2C0_SDA                     1
#define GPIO53_FUN_I2C1_SDA                     2
#define GPIO53_FUN_SPI_SCLK                     3
#define GPIO53_FUN_UNUSED4                      4
#define GPIO53_FUN_HDMI_D_15                    5
#define GPIO53_FUN_I2S0_FS                      6
#define GPIO53_FUN_I2S1_FS                      7
#define GPIO53_FUN_PDM0_OUT                     8
#define GPIO53_FUN_PDM1_OUT                     9
#define GPIO53_FUN_UNUSED10                     10
#define GPIO53_FUN_REG_GPIO_53                  11
#define GPIO53_FUN_UART_CTS                     12
#define GPIO53_FUN_M4_SWDIO                     13
#define GPIO53_FUN_A5_SWDIO                     14
#define GPIO53_FUN_DEBUG_7                      15
#define GPIO53_FUN_UNUSED16                     16
#define GPIO53_FUN_UNUSED17                     17
#define GPIO53_FUN_UNUSED18                     18

#endif  /*__BL70X_GPIO_H__ */
