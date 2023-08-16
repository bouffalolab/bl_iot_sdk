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
#ifndef __BL808_H__
#define __BL808_H__

/* select one or none of the options as below */

#define BL80X_HW_A0                 1
#define BL80X_HW_B0                 2
#define BL80X_HW_B0_NEW_ARCH        3
#ifdef A0_AUDIO_TEST
#define BL80X_HW_VER                BL80X_HW_A0
#else
#define BL80X_HW_VER                BL80X_HW_B0_NEW_ARCH
#endif

#define FPGA_ULTRASCALE             1
#define BL808_BOARD_TYPE            BL_BOARD_808_EVB

/* Set to 1 if verify bittrue; Set to 0 if system integration */
#define BITTRUE_REGRESSION_TEST     0

#define ISP_DVP_TSRC_PIC_ADDR       0xa0000000
#define ISP_INPUT_MODE              ISP_INPUT_MIPI_2LANE
//#define ISP_INPUT_MODE              ISP_INPUT_DVP
#define DVP_8BIT_MODE               0
#define MJPG_AUTO_HEADER            1
#define USE_AEAWB_SRAM              1
#define DUAL_ENC                    1
#define DUAL_UART                   1
#define SEGGER_RTT                  0
#define PSRAM_ID_FOR_ISP_PORT_BUF   0
#define PSRAM_ID_FOR_REF_BUF        1
#define PSRAM_ID_FOR_CREF_HDR_BUF   0
#define PSRAM_ID_FOR_BS_BUF         0
#define PSRAM_ID_FOR_STREAM_BUF     1
#define PSRAM_ID_FOR_3DNR_BUF       0
#define NEW_REF_FRM_CFG_API         1
#define ENCODE_1080P_SVGA		    0
#define H264_BSB_WORKAROUND         0
#define ENABLE_3DNR                 1
#define ENABLE_DVP_RESHAPE          1
#define H264_ENABLE_SRAMCK_OLD      0
#define H264_PREFETCH_MODE          1
#define H264_SUB_PREFETCH_MODE      0
#define H264_DISFILTER              0
//#define ENABLE_3DNR_H264

#if (BITTRUE_REGRESSION_TEST)
#define BS_BUF_SIZE                 0x200000
#define STREAM_BUF_SIZE             0x3000000
#else
#define BS_BUF_SIZE                 0x100000
#define STREAM_BUF_SIZE             0x500000
#endif


#define PRINT_FAST_CAP_TIMING       0
#define FAST_CAPTURE_MODE           0


//#define TEST_AE_LINEARITY
//#define TEST_DIRTY_EDGE_FOR_SC1245

#define WB_BIAS_CT_THRESH           COLOR_TEMP_D50
#define MD_ALARM_BLOCK_CNT_THRESH   (8)


/**
 * @brief BL808 memory address for debug purpose
 */
/* Encoder related memory */
#define	YUV_SRC_ADDR	            0x53000000


#define NVIC_PRIORITYGROUP_0        0x00000007U /*!< 0 bits for pre-emption priority
                                                     3 bits for subpriority */
#define NVIC_PRIORITYGROUP_1        0x00000006U /*!< 1 bits for pre-emption priority
                                                     2 bits for subpriority */
#define NVIC_PRIORITYGROUP_2        0x00000005U /*!< 2 bits for pre-emption priority
                                                     1 bits for subpriority */
#define NVIC_PRIORITYGROUP_3        0x00000004U /*!< 3 bits for pre-emption priority */

#define ATTR_CLOCK_SECTION          __attribute__((section(".sclock_rlt_code")))
#define ATTR_CLOCK_CONST_SECTION    __attribute__((section(".sclock_rlt_const")))
#define ATTR_TCM_SECTION            __attribute__((section(".tcm_code")))
#define ATTR_TCM_CONST_SECTION      __attribute__((section(".tcm_const")))
#define ATTR_VRAM_SECTION           __attribute__((section(".vram_code")))
#define ATTR_VRAM_CONST_SECTION     __attribute__((section(".vram_const")))
#define ATTR_VRAM_ZI_SECTION        __attribute__((section(".vram_zi")))
#define ATTR_VRAM_ZI_SECTION_DMA    __attribute__((aligned (128), section(".vram_zi")))
#if (BL80X_HW_VER >= BL80X_HW_B0)
#define ATTR_SRAM_JPG_HDR_SECTION   __attribute__((section(".jpg_hdr_data")))
#else
#define ATTR_SRAM_JPG_HDR_SECTION
#endif

#define ATTR_FALLTHROUGH()                            __attribute__((fallthrough))

#define CORE_ID_ADDRESS                               (0xF0000000)
#define CORE_ID_M0                                    (0xE906DAD4)
#define CORE_ID_M1                                    (0xE906DAD5)
#define CORE_ID_D0                                    (0xDEAD5500)
#define CORE_ID_D1                                    (0xDEAD5501)
#define CORE_ID_LP                                    (0xDEADE902)

/**
  * @}
  */

/** @addtogroup Peripheral_Interrupt_Number_Section
  * @{
  */
#if CPU_CA5
#define IRQN_PERI_START     32
typedef enum IRQn
{
    /******  SGI Interrupts Numbers                 ****************************************/
    SGI0_IRQn            =  0,
    SGI1_IRQn            =  1,
    SGI2_IRQn            =  2,
    SGI3_IRQn            =  3,
    SGI4_IRQn            =  4,
    SGI5_IRQn            =  5,
    SGI6_IRQn            =  6,
    SGI7_IRQn            =  7,
    SGI8_IRQn            =  8,
    SGI9_IRQn            =  9,
    SGI10_IRQn           = 10,
    SGI11_IRQn           = 11,
    SGI12_IRQn           = 12,
    SGI13_IRQn           = 13,
    SGI14_IRQn           = 14,
    SGI15_IRQn           = 15,

    /******  Cortex-A5 Processor Exceptions Numbers ****************************************/
    GlobalTimer_IRQn     = 27,        /*!< Global Timer Interrupt                        */
    PrivTimer_IRQn       = 29,        /*!< Private Timer Interrupt                       */
    PrivWatchdog_IRQn    = 30,        /*!< Private Watchdog Interrupt                    */

    /******  Platform Exceptions Numbers ***************************************************/
    UART1_IRQn                  = (32 + 3),      /*!< UART1 Interrupt                                                   */
    UART0_IRQn                  = (32 + 4),      /*!< UART0 Interrupt                                                   */
    I2C0_IRQn                   = (32 + 5),      /*!< I2C0 Interrupt                                                    */
    I2C1_IRQn                   = (32 + 6),      /*!< I2C1 Interrupt                                                    */
    AE_STATS_IRQn               = (32 + 8),      /*!< AE statistics ready Interrupt                                     */
    AWB_STATS_IRQn              = (32 + 9),      /*!< AWB statistics ready Interrupt                                    */
    SEOF1_IRQn                  = (32 + 10),     /*!< SEOF 1 Interrupt                                                  */
    SEOF2_IRQn                  = (32 + 11),     /*!< SEOF 2 Interrupt                                                  */
    SEOF3_IRQn                  = (32 + 12),     /*!< SEOF 3 Interrupt                                                  */
    DVP2AXI_A_IRQn              = (32 + 13),     /*!< DVP to AXI A Interrupt                                            */
    DVP2AXI_B_IRQn              = (32 + 14),     /*!< DVP to AXI B Interrupt                                            */
    DVP2AXI_C_IRQn              = (32 + 15),     /*!< DVP to AXI C Interrupt                                            */
    DVP2AXI_D_IRQn              = (32 + 16),     /*!< DVP to AXI D Interrupt                                            */
    H264_BS_FULL_IRQn           = (32 + 17),     /*!< H264 bitsream full Interrupt                                      */
    H264_FRAME_DONE_IRQn        = (32 + 18),     /*!< H264 frame done Interrupt                                         */
    H264_SEQ_DONE_IRQn          = (32 + 19),     /*!< H264 sequence done Interrupt                                      */
    MJPEG_IRQn                  = (32 + 20),     /*!< MJPEG encoder Interrupt                                           */
    H264_S_BS_FULL_IRQn         = (32 + 21),     /*!< H264 (2nd stream) bitsream full Interrupt                         */
    H264_S_FRAME_DONE_IRQn      = (32 + 22),     /*!< H264 (2nd stream) frame done Interrupt                            */
    H264_S_SEQ_DONE_IRQn        = (32 + 23),     /*!< H264 (2nd stream) sequence done Interrupt                         */
    DMA0_CH0_IRQn               = (32 + 24),     /*!< DMA0 Channel 0 Interrupt                                          */
    DMA0_CH1_IRQn               = (32 + 25),     /*!< DMA0 Channel 1 Interrupt                                          */
    DMA0_CH2_IRQn               = (32 + 26),     /*!< DMA0 Channel 2 Interrupt                                          */
    DMA0_CH3_IRQn               = (32 + 27),     /*!< DMA0 Channel 3 Interrupt                                          */
    DMA0_CH4_IRQn               = (32 + 28),     /*!< DMA0 Channel 4 Interrupt                                          */
    DMA0_CH5_IRQn               = (32 + 29),     /*!< DMA0 Channel 5 Interrupt                                          */
    DMA0_CH6_IRQn               = (32 + 30),     /*!< DMA0 Channel 6 Interrupt                                          */
    DMA0_CH7_IRQn               = (32 + 31),     /*!< DMA0 Channel 7 Interrupt                                          */
    SDH_MMC1_IRQn               = (32 + 32),     /*!< SDH MMC 1 Interrupt                                               */
    SDH_MMC3_IRQn               = (32 + 33),     /*!< SDH MMC 3 Interrupt                                               */
    ETHMAC_IRQn                 = (32 + 36),     /*!< Ether MAC Interrupt                                               */
    CSI_IRQn                    = (32 + 37),     /*!< MIPI CSI Interrupt                                               */
    PWM_IRQn                    = (32 + 38),     /*!< PWM Interrupt                                                     */
    CNN_IRQn                    = (32 + 39),     /*!< CNN Interrupt                                                     */
    MJDEC_IRQn                  = (32 + 40),     /*!< MJPEG decoder Interrrupt                                          */
    DVP2AXI_E_IRQn              = (32 + 41),     /*!< DVP to AXI E Interrupt                                            */
    DVP2AXI_F_IRQn              = (32 + 42),     /*!< DVP to AXI F Interrupt                                            */
    DVP2AXI_G_IRQn              = (32 + 43),     /*!< DVP to AXI G Interrupt                                            */
    DVP2AXI_H_IRQn              = (32 + 44),     /*!< DVP to AXI H Interrupt                                            */
    WDR_STATS_IRQn              = (32 + 54),     /*!< WDR decoder Interrrupt                                            */
    AWB2_STATS_IRQn             = (32 + 58),     /*!< AWB statistics ready Interrrupt                                   */

    IRQn_LAST,
} IRQn_Type;
#endif /* CPU_CA5 */

#ifdef ARCH_RISCV
# if (__riscv_xlen == 64)
#   define IRQ_NUM_BASE    16 /* PLIC ===> MEXT_IRQn */
# else
#   define IRQ_NUM_BASE    16
# endif
#endif
/**
 * @brief BL606P Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
#define IRQN_PERI_START     IRQ_NUM_BASE
typedef enum
{
#ifdef ARCH_RISCV
  SSOFT_IRQn                  =1,       /*!< 1 RISCV supervisor software Interrupt                             */
  MSOFT_IRQn                  =3,       /*!< 3 RISCV machine software Interrupt                                */
  STIME_IRQn                  =5,       /*!< 5 RISCV supervisor time Interrupt                                 */
  MTIME_IRQn                  =7,       /*!< 7 RISCV machine time Interrupt                                    */
  SEXT_IRQn                   =9,       /*!< 9 RISCV S-mode external  Interrupt                                */
  MEXT_IRQn                   =11,      /*!< 11 RISCV M-mode external  Interrupt                               */
  CLIC_SOFT_PEND_IRQn         =12,      /*!< 12 RISCV CLIC software pending  Interrupt                         */
# if (__riscv_xlen == 64)
  HPM_OVF_IRQn                =17,      /*!< 17 RISCV HPM counter overflow Interrupt                           */
# endif
#endif

/******  BL808 specific Interrupt Numbers ***************************************************/
  AWB3_STATS_IRQn             = IRQ_NUM_BASE + 1,      /*!< AWB3 histogram statistics ready Interrrupt                        */

  IPC_M0_IRQn                 = IRQ_NUM_BASE + 3,      /*!< ipc0_m0_irq Interrupt                                             */
  UART1_IRQn                  = IRQ_NUM_BASE + 3,      /*!< UART1 Interrupt                                                   */
  UART0_IRQn                  = IRQ_NUM_BASE + 4,      /*!< UART0 Interrupt                                                   */
  I2C0_IRQn                   = IRQ_NUM_BASE + 5,      /*!< I2C0 Interrupt                                                    */
  I2C1_IRQn                   = IRQ_NUM_BASE + 6,      /*!< I2C1 Interrupt                                                    */
  SPI1_IRQn                   = IRQ_NUM_BASE + 7,      /*!< SPI1 Interrupt                                                    */
  AE_STATS_IRQn               = IRQ_NUM_BASE + 8,      /*!< AE statistics ready Interrupt                                     */
  AWB_STATS_IRQn              = IRQ_NUM_BASE + 9,      /*!< AWB statistics ready Interrupt                                    */
  SEOF1_IRQn                  = IRQ_NUM_BASE + 10,     /*!< SEOF 1 Interrupt                                                  */
  SEOF2_IRQn                  = IRQ_NUM_BASE + 11,     /*!< SEOF 2 Interrupt                                                  */
  SEOF3_IRQn                  = IRQ_NUM_BASE + 12,     /*!< SEOF 3 Interrupt                                                  */
  DVP2AXI_A_IRQn              = IRQ_NUM_BASE + 13,     /*!< DVP to AXI A Interrupt                                            */
  DVP2AXI_B_IRQn              = IRQ_NUM_BASE + 14,     /*!< DVP to AXI B Interrupt                                            */
  DVP2AXI_C_IRQn              = IRQ_NUM_BASE + 15,     /*!< DVP to AXI C Interrupt                                            */
  DVP2AXI_D_IRQn              = IRQ_NUM_BASE + 16,     /*!< DVP to AXI D Interrupt                                            */
  H264_BS_FULL_IRQn           = IRQ_NUM_BASE + 17,     /*!< H264 bitsream full Interrupt                                      */
  H264_FRAME_DONE_IRQn        = IRQ_NUM_BASE + 18,     /*!< H264 frame done Interrupt                                         */
  H264_SEQ_DONE_IRQn          = IRQ_NUM_BASE + 19,     /*!< H264 sequence done Interrupt                                      */
  MJPEG_IRQn                  = IRQ_NUM_BASE + 20,     /*!< MJPEG encoder Interrupt                                           */
  H264_S_BS_FULL_IRQn         = IRQ_NUM_BASE + 21,     /*!< H264 (2nd stream) bitsream full Interrupt                         */
  H264_S_FRAME_DONE_IRQn      = IRQ_NUM_BASE + 22,     /*!< H264 (2nd stream) frame done Interrupt                            */
  H264_S_SEQ_DONE_IRQn        = IRQ_NUM_BASE + 23,     /*!< H264 (2nd stream) sequence done Interrupt                         */
  DMA2_INT0_IRQn              = IRQ_NUM_BASE + 24,     /*!< DMA0 Channel 0 Interrupt                                          */
  DMA2_INT1_IRQn              = IRQ_NUM_BASE + 25,     /*!< DMA0 Channel 1 Interrupt                                          */
  DMA2_INT2_IRQn              = IRQ_NUM_BASE + 26,     /*!< DMA0 Channel 2 Interrupt                                          */
  DMA2_INT3_IRQn              = IRQ_NUM_BASE + 27,     /*!< DMA0 Channel 3 Interrupt                                          */
  DMA2_INT4_IRQn              = IRQ_NUM_BASE + 28,     /*!< DMA0 Channel 4 Interrupt                                          */
  DMA2_INT5_IRQn              = IRQ_NUM_BASE + 29,     /*!< DMA0 Channel 5 Interrupt                                          */
  DMA2_INT6_IRQn              = IRQ_NUM_BASE + 30,     /*!< DMA0 Channel 6 Interrupt                                          */
  DMA2_INT7_IRQn              = IRQ_NUM_BASE + 31,     /*!< DMA0 Channel 7 Interrupt                                          */
  SDH_MMC1_IRQn               = IRQ_NUM_BASE + 32,     /*!< SDH MMC 1 Interrupt                                               */
  SDH_MMC3_IRQn               = IRQ_NUM_BASE + 33,     /*!< SDH MMC 3 Interrupt                                               */
  ETHMAC_IRQn                 = IRQ_NUM_BASE + 36,     /*!< Ether MAC Interrupt                                               */
  CSI_IRQn                    = IRQ_NUM_BASE + 37,     /*!< MIPI CSI Interrupt                                               */
  PWM_IRQn                    = IRQ_NUM_BASE + 38,     /*!< PWM Interrupt                                                     */
  IPC_D0_IRQn                 = IRQ_NUM_BASE + 38,     /*!< IPC D0 Interrupt                                                  */
  CNN_IRQn                    = IRQ_NUM_BASE + 39,     /*!< CNN Interrupt                                                     */
  MJDEC_IRQn                  = IRQ_NUM_BASE + 40,     /*!< MJPEG decoder Interrrupt                                          */
  DVP2AXI_E_IRQn              = IRQ_NUM_BASE + 41,     /*!< DVP to AXI E Interrupt                                            */
  DVP2AXI_F_IRQn              = IRQ_NUM_BASE + 42,     /*!< DVP to AXI F Interrupt                                            */
  DVP2AXI_G_IRQn              = IRQ_NUM_BASE + 43,     /*!< DVP to AXI G Interrupt                                            */
  DVP2AXI_H_IRQn              = IRQ_NUM_BASE + 44,     /*!< DVP to AXI H Interrupt                                            */
  DMA2D_INT0_IRQn             = IRQ_NUM_BASE + 45,     /*!< DMA2D INT0 Interrupt                                              */
  DMA2D_INT1_IRQn             = IRQ_NUM_BASE + 46,     /*!< DMA2D INT1 Interrupt                                              */
  DISPLAY_IRQn             = IRQ_NUM_BASE + 47,     /*!< DMA2D INT2 Interrupt                                              */
  DMA2D_INT3_IRQn             = IRQ_NUM_BASE + 48,     /*!< DMA2D INT3 Interrupt                                              */
  SEOF4_IRQn                  = IRQ_NUM_BASE + 49,     /*!< SEOF 4 Interrupt                                                  */
  DMA2D_INT5_IRQn             = IRQ_NUM_BASE + 50,     /*!< DMA2D INT5 Interrupt                                              */
  DMA2D_INT6_IRQn             = IRQ_NUM_BASE + 51,     /*!< DMA2D INT6 Interrupt                                              */
  DMA2D_INT7_IRQn             = IRQ_NUM_BASE + 52,     /*!< DMA2D INT7 Interrupt                                              */
  WDR_STATS_IRQn              = IRQ_NUM_BASE + 54,     /*!< WDR decoder Interrrupt                                            */
  AWB2_STATS_IRQn             = IRQ_NUM_BASE + 58,     /*!< AWB2 statistics ready Interrrupt                                  */
  AE_HIST_STATS_IRQn          = IRQ_NUM_BASE + 60,     /*!< AE histogram statistics ready Interrrupt                          */
  IRQn_LAST,
} IRQn_Type;
#define DMA0_ALL_IRQn                          (IRQn_LAST)  /*FIXME:only for std driver compile no use*/
#define DMA1_ALL_IRQn                          (IRQn_LAST)  /*FIXME:only for std driver compile no use*/
/*@} end of group Peripheral_Interrupt_Number_Section */

/** @addtogroup AHB_Master_Slave_Section
  * @{
  */
typedef enum
{
    BL_MASTER_L1C = 0,
    BL_MASTER_AHB ,
    BL_MASTER_DMA0 ,
    BL_MASTER_DMA1 ,
    BL_MASTER_SEC_ENG ,
    BL_MASTER_MAX,
}BL_Master_Type;

#define IS_BL_MASTER_TYPE(type)                       ((signed int)type >= 0 && type < 5)

typedef enum
{
    BL_AHB_MASTER_SBUS = 0,
    BL_AHB_MASTER_SDU,
    BL_AHB_MASTER_SDH,
    BL_AHB_MASTER_SEC_ENG,
    BL_AHB_MASTER_DMA0,
    BL_AHB_MASTER_DMA1,
    BL_AHB_MASTER_CAM,
    BL_AHB_MASTER_MJPEG,
    BL_AHB_MASTER_DBG,
    BL_AHB_MASTER_MAX,
}BL_AHB_Master_Type;

#define IS_BL_AHB_MASTER_TYPE(type)                       ((signed int)type >= 0 && type < 10)

typedef enum
{
    BL_AHB_SLAVE0_OCRAM = 0,
    BL_AHB_SLAVE0_PSRAM,
    BL_AHB_SLAVE0_MAX,
}BL_AHB_Slave0_Type;

#define IS_BL_AHB_SLAVE0_TYPE(type)                       ((signed int)type >= 0 && type < 2)

typedef enum
{
    BL_AHB_SLAVE1_GLB = 0,
    BL_AHB_SLAVE1_MIX,
    BL_AHB_SLAVE1_SDU,
    BL_AHB_SLAVE1_SDH,
    BL_AHB_SLAVE1_SEC,
    BL_AHB_SLAVE1_TZ1,
    BL_AHB_SLAVE1_TZ2,
    BL_AHB_SLAVE1_DMA,
    BL_AHB_SLAVE1_PATCHRAM,
    BL_AHB_SLAVE1_L1C,
    BL_AHB_SLAVE1_SFC,
    BL_AHB_SLAVE1_CAM,
    BL_AHB_SLAVE1_PDM,
    BL_AHB_SLAVE1_AUX,
    BL_AHB_SLAVE1_EFC,
    BL_AHB_SLAVE1_SSP,
    BL_AHB_SLAVE1_SF_CTRL             = 0x0B,
    BL_AHB_SLAVE1_UART0               = 0x10,
    BL_AHB_SLAVE1_UART1               = 0x11,
    BL_AHB_SLAVE1_UART2               = 0x1A,
    BL_AHB_SLAVE1_SPI                 = 0x12,
    BL_AHB_SLAVE1_I2C                 = 0x13,
    BL_AHB_SLAVE1_MAX,
    BL_AHB_SLAVE1_GPADC               = 0x21,/* not used for cgen and swrst */
    BL_AHB_SLAVE1_GPDAC               = 0x22,/* not used for cgen and swrst */
}BL_AHB_Slave1_Type;

#if 0
/*606p BL_AHB_SLAVE1*/
typedef enum
{
    BL_AHB_SLAVE1_GLB                 = 0x00,//cgen rsvd
    BL_AHB_SLAVE1_RF_TOP              = 0x01,//swrst mix
    BL_AHB_SLAVE1_GPIP                = 0x02,
    BL_AHB_SLAVE1_SEC_DBG             = 0x03,
    BL_AHB_SLAVE1_SEC_ENG             = 0x04,
    BL_AHB_SLAVE1_TZ                  = 0x05,//swrst tz1,cgen tz1+tz2
    BL_AHB_SLAVE1_RSVD6               = 0x06,//swrst tz2,
    BL_AHB_SLAVE1_EF_CTRL             = 0x07,
    BL_AHB_SLAVE1_CCI                 = 0x08,//cgen rsvd
    BL_AHB_SLAVE1_L1C                 = 0x09,//cgen rsvd
    BL_AHB_SLAVE1_RSVD10              = 0x0A,
    BL_AHB_SLAVE1_SF_CTRL             = 0x0B,
    BL_AHB_SLAVE1_DMA                 = 0x0C,
    BL_AHB_SLAVE1_SDU                 = 0x0D,//cgen rsvd
    BL_AHB_SLAVE1_PDS                 = 0x0E,//cgen rsvd
    BL_AHB_SLAVE1_RSVD15              = 0x0F,
    BL_AHB_SLAVE1_UART0               = 0x10,
    BL_AHB_SLAVE1_UART1               = 0x11,
    BL_AHB_SLAVE1_SPI                 = 0x12,
    BL_AHB_SLAVE1_I2C                 = 0x13,
    BL_AHB_SLAVE1_PWM                 = 0x14,
    BL_AHB_SLAVE1_TIMER               = 0x15,
    BL_AHB_SLAVE1_IRR                 = 0x16,
    BL_AHB_SLAVE1_CKS                 = 0x17,
    BL_AHB_SLAVE1_QDEC                = 0x18,
    BL_AHB_SLAVE1_KYS                 = 0x19,
    BL_AHB_SLAVE1_UART2               = 0x1A,
    BL_AHB_SLAVE1_RSVD27              = 0x1B,
    BL_AHB_SLAVE1_RSVD28              = 0x1C,
    BL_AHB_SLAVE1_RSVD29              = 0x1D,
    BL_AHB_SLAVE1_RSVD30              = 0x1E,
    BL_AHB_SLAVE1_RSVD31              = 0x1F,
    BL_AHB_SLAVE1_MAX                 = 0x20,
    BL_AHB_SLAVE1_GPADC               = 0x21,/* not used for cgen and swrst */
    BL_AHB_SLAVE1_GPDAC               = 0x22,/* not used for cgen and swrst */
    BL_AHB_SLAVE1_I2S                 = 0x23,/* not used for cgen and swrst */
    BL_AHB_SLAVE1_CAM                 = 0x24,/* not used for cgen and swrst */
}BL_AHB_Slave1_Type;
#endif
#define IS_BL_AHB_SLAVE1_TYPE(type)                       ((signed int)type >= 0 && type < 0x23)

typedef enum
{
    BL_SEC_ENG_MASTER_AES0 = 0,
    BL_SEC_ENG_MASTER_SHA0,
}BL_Sec_Eng_Master_Type;

#define IS_BL_AHB_SEC_ENG_TYPE(type)                       ((signed int)type >= 0 && type < 4)

typedef enum
{
    BL_DMA0_MASTER_CH0 = 0,
    BL_DMA0_MASTER_CH1,
    BL_DMA0_MASTER_CH2,
    BL_DMA0_MASTER_CH3,
    BL_DMA0_MASTER_CH4,
    BL_DMA0_MASTER_CH5,
    BL_DMA0_MASTER_CH6,
    BL_DMA0_MASTER_CH7,
}BL_DMA0_Master_Type;

#define IS_BL_DMA0_MASTER_TYPE(type)                       ((signed int)type >= 0 && type < 8)

typedef enum
{
    BL_DMA0_SLAVE_CTRL =0,
    BL_DMA0_SLAVE_CH0,
    BL_DMA0_SLAVE_CH1,
    BL_DMA0_SLAVE_CH2,
    BL_DMA0_SLAVE_CH3,
    BL_DMA0_SLAVE_CH4,
    BL_DMA0_SLAVE_CH5,
    BL_DMA0_SLAVE_CH6,
    BL_DMA0_SLAVE_CH7,
}BL_DMA0_Slave_Type;

#define IS_BL_DMA0_SLAVE_TYPE(type)                       ((signed int)type >= 0 && type < 9)

typedef enum
{
    BL_AHB_SLAVE2_UART = 0,
    BL_AHB_SLAVE2_I2C,
    BL_AHB_SLAVE2_PWM,
    BL_AHB_SLAVE2_WIFI_SHARED_RAM,
    BL_AHB_SLAVE2_TIMER,
    BL_AHB_SLAVE2_PSRAMC,
    BL_AHB_SLAVE2_MJPEG,
    BL_AHB_SLAVE2_I2S,
    BL_AHB_SLAVE2_RSVD1,
    BL_AHB_SLAVE2_HBN_DMA,
    BL_AHB_SLAVE2_CCI,
    BL_AHB_SLAVE2_GLB2,
    BL_AHB_SLAVE2_IPC,
    BL_AHB_SLAVE2_SECDBG,
    BL_AHB_SLAVE2_PDS,
    BL_AHB_SLAVE2_AON_HBN_RAM,
    BL_AHB_SLAVE2_EXT_PSRAM0_CTRL     = 0x11,
    BL_AHB_SLAVE2_EXT_PSRAM1_CTRL     = 0x12,
    BL_AHB_SLAVE2_EXT_USB             = 0x13,
    BL_AHB_SLAVE2_EXT_SDH             = 0x16,
    BL_AHB_SLAVE2_MAX,
}BL_AHB_Slave2_Type;

/*606p BL_AHB_Slave2_Type */
#if 0
typedef enum
{
    BL_AHB_SLAVE2_RSVD0               = 0x00,
    BL_AHB_SLAVE2_RSVD1               = 0x01,
    BL_AHB_SLAVE2_RSVD2               = 0x02,
    BL_AHB_SLAVE2_RSVD3               = 0x03,
    BL_AHB_SLAVE2_WIFI                = 0x04,
    BL_AHB_SLAVE2_RSVD5               = 0x05,
    BL_AHB_SLAVE2_RSVD6               = 0x06,
    BL_AHB_SLAVE2_RSVD7               = 0x07,
    BL_AHB_SLAVE2_BT_BLE              = 0x08,
    BL_AHB_SLAVE2_M154                = 0x09,
    BL_AHB_SLAVE2_BT_BLE2             = 0x0A,
    BL_AHB_SLAVE2_M1542               = 0x0B,
    BL_AHB_SLAVE2_RSVD12              = 0x0C,
    BL_AHB_SLAVE2_RSVD13              = 0x0D,
    BL_AHB_SLAVE2_RSVD14              = 0x0E,
    BL_AHB_SLAVE2_RSVD15              = 0x0F,
    BL_AHB_SLAVE2_EXT_EMI_MISC        = 0x10,
    BL_AHB_SLAVE2_EXT_PSRAM0_CTRL     = 0x11,
    BL_AHB_SLAVE2_EXT_PSRAM1_CTRL     = 0x12,
    BL_AHB_SLAVE2_EXT_USB             = 0x13,
    BL_AHB_SLAVE2_EXT_MIX2            = 0x14,
    BL_AHB_SLAVE2_EXT_AUDIO           = 0x15,
    BL_AHB_SLAVE2_EXT_SDH             = 0x16,
    BL_AHB_SLAVE2_EXT_EMAC            = 0x17,
    BL_AHB_SLAVE2_EXT_DMA2            = 0x18,
    BL_AHB_SLAVE2_EXT_RSVD25          = 0x19,
    BL_AHB_SLAVE2_EXT_RSVD26          = 0x1A,
    BL_AHB_SLAVE2_EXT_RSVD27          = 0x1B,
    BL_AHB_SLAVE2_MAX                 = 0x1C,
}BL_AHB_Slave2_Type;
#endif
#define IS_BL_AHB_SLAVE2_TYPE(type)                       ((signed int)type >= 0 && type < 0x17)

typedef enum
{
    BL_AHB_SLAVE3_WIFI = 0,
    BL_AHB_SLAVE3_WIFIPLL_240M        = 0x00,
    BL_AHB_SLAVE3_CPUPLL_128M         = 0x01,
    BL_AHB_SLAVE3_CPUPLL_320M         = 0x02,
    BL_AHB_SLAVE3_CPUPLL_640M         = 0x03,
    BL_AHB_SLAVE3_MAX,
}BL_AHB_Slave3_Type;
/*606p BL_AHB_Slave3_Type*/
#if 0
typedef enum
{
    BL_AHB_SLAVE3_WIFIPLL_240M        = 0x00,
    BL_AHB_SLAVE3_CPUPLL_128M         = 0x01,
    BL_AHB_SLAVE3_CPUPLL_320M         = 0x02,
    BL_AHB_SLAVE3_CPUPLL_640M         = 0x03,
    BL_AHB_SLAVE3_MAX                 = 0x04,
}BL_AHB_Slave3_Type;
#endif
#define IS_BL_AHB_SLAVE3_TYPE(type)                       ((signed int)type >= 0 && type < 4)

typedef enum
{
    BL_L1C_MASTER_IBUS = 0,
    BL_L1C_MASTER_DBUS,
    BL_L1C_MASTER_MAX,
}BL_L1C_Master_Type;

#define IS_BL_L1C_MASTER_TYPE(type)                       ((signed int)type >= 0 && type < 4)

typedef enum
{
    BL_L1C_SLAVE0_TCM1 = 0,
    BL_L1C_SLAVE0_MAX,
}BL_L1C_Slave0_Type;

#define IS_BL_L1C_SLAVE0_TYPE(type)                       ((signed int)type >= 0 && type < 1)

typedef enum
{
    BL_L1C_SLVAE1_XIP = 0,
    BL_L1C_SLVAE1_TCM0,
    BL_L1C_SLVAE1_IROM,
    BL_L1C_SLAVE1_MAX,
}BL_L1C_Slave1_Type;

typedef enum {
    ISP_INPUT_DVP = 0,
    ISP_INPUT_MIPI_1LANE,
    ISP_INPUT_MIPI_2LANE,
} BL_ISP_INPUT_MODE_E;

typedef enum {
    BL_BOARD_808_EVB = 0,
    BL_BOARD_808_OPNM8508PA,
} BL_808_BOARD_TYPE_E;

#define IS_BL_L1C_SLAVE1_TYPE(type)                       ((signed int)type >= 0 && type < 3)





/*@} end of group AHB_Master_Slave_Section */

/** @addtogroup Memory_Map_Section
  * @{
  */

/**
 * @brief BL808 Memory Map Definitions
 */
#define BL808_ITCM_BASE          0x00400000
#define BL808_DTCM_BASE          0x00410000

/*@} end of group Memory_Map_Section */

/** @addtogroup Peripheral_Register_Section
  * @{
  */

#define GLB_BASE                    ((uint32_t)0x20000000)
#define MIX_BASE                    ((uint32_t)0x20001000)
#define GPIP_BASE                   ((uint32_t)0x20002000)
#define SPI0_BASE                   ((uint32_t)0x2000A200)
#define PWM_BASE                    ((uint32_t)0x2000A400)            /*!< PWM modue base address */
#define IPC0_BASE                   ((uint32_t)0x2000a800)
#define IPC1_BASE                   ((uint32_t)0x2000a840)
#define IPC2_BASE                   ((uint32_t)0x30005000)
#define MMSYS_MISC_BASE             ((uint32_t)0x30000000)            /*!< MMSys misc base address */
#define DMA0_BASE                   ((uint32_t)0x2000c000)            /*!< WLAN DMA0 BASE */
#define DMA1_BASE                   ((uint32_t)0x20071000)            /*!< WLAN DMA1 BASE */
#define DMA2_BASE                   ((uint32_t)0x30001000)            /*!< MMSYS DMA22 BASE */
#ifdef  WLAN_DEBUG
#define UART0_BASE                  ((uint32_t)0x2000A000)            /*!< UART0 modue base address */
#else
#define UART0_BASE                  ((uint32_t)0x30002000)            /*!< UART0 modue base address */
#endif
#define DMA2D_BASE                  ((uint32_t)0x30006000)
#define UART1_BASE                  ((uint32_t)0x3000E000)            /*!< UART1 modue base address */ /*FIXME:UART1 TRUE base*/
#define UART2_BASE                  ((uint32_t)0x2000aa00)            /*!< UART2 modue base address */
#define UART3_BASE                  ((uint32_t)0x30002000)            /*!< UART3 modue base address */ /*MMSYS uart*/
#define UART4_BASE                  ((uint32_t)0x3000e000)            /*!< UART4 modue base address */
#define I2C0_BASE                   ((uint32_t)0x30003000)            /*!< I2C_A module base address */
#define I2C1_BASE                   ((uint32_t)0x30004000)            /*!< I2C_B module base address */
#define PSRAM0_CTRL_BASE            ((uint32_t)0x30005000)            /*!< PSRAM0 ctrl module base address */
#define PSRAM1_CTRL_BASE            ((uint32_t)0x30006000)            /*!< PSRAM1 ctrl module base address */
#define CLKRST_BASE                 ((uint32_t)0x30007000)            /*!< Clk rst ctrl module base address */
#define SPI1_BASE                   ((uint32_t)0x30008000)
#define I2S0_BASE                   ((uint32_t)0x3000a000)            /*!< I2S0 module base address */
#define I2S1_BASE                   ((uint32_t)0x3000b000)            /*!< I2S1 module base address */
#define PDM_BASE                    ((uint32_t)0x3000C000)            /*!< PDM0 module base address */
#define PDM1_BASE                   ((uint32_t)0x3000D000)            /*!< PDM1 module base address */
#define ETHMAC_BASE                 ((uint32_t)0x20070000)            /*!< ETHMac module base address */
#define ISP_MISC_BASE               ((uint32_t)0x30010000)            /*!< ISP misc module base address */
#define ISP_BASE                    ((uint32_t)0x30011000)            /*!< ISP module base address */
#define ISP_AWB3_BASE               ((uint32_t)0x30016000)            /*!< ISP AWB3 module base address */

/* ISP_SUBSYS */
#define ISP_MISC_BASE               ((uint32_t)0x30010000)
#define ISP_BASE                    ((uint32_t)0x30011000)
#define DVP0_BASE                   ((uint32_t)0x30012000)
#define DVP1_BASE                   ((uint32_t)0x30012100)
#define DVP2_BASE                   ((uint32_t)0x30012200)
#define DVP3_BASE                   ((uint32_t)0x30012300)
#define DVP4_BASE                   ((uint32_t)0x30012400)
#define DVP5_BASE                   ((uint32_t)0x30012500)
#define DVP6_BASE                   ((uint32_t)0x30012600)
#define DVP7_BASE                   ((uint32_t)0x30012700)
#define DVP_TSRC0_BASE              ((uint32_t)0x30012800)
#define DVP_TSRC1_BASE              ((uint32_t)0x30012900)
#define AXI_CTRL_NR3D_BASE          ((uint32_t)0x30012a00)
#define OSD_DP_BASE                 ((uint32_t)0x30015000)
#define MIPI_BASE                   ((uint32_t)0x3001a000)
#define DBI_BASE                    ((uint32_t)0x3001b000)
#define DSI_BASE                    ((uint32_t)0x3001a100)

/* CODEC_SUBSYS */
#define CODEC_MISC_BASE             ((uint32_t)0x30020000)
#define MJPEG_BASE                  ((uint32_t)0x30021000)
#define VIDEO_BASE                  ((uint32_t)0x30022000)
#define MJPEG_DEC_BASE              ((uint32_t)0x30023000)
#define BL_CNN_BASE                 ((uint32_t)0x30024000)

#define DVP2AXI_A_BASE              ((uint32_t)0x30012000)            /*!< DVP2AXI A module base address */
#define DVP2AXI_B_BASE              ((uint32_t)0x30012100)            /*!< DVP2AXI B module base address */
#define DVP2AXI_C_BASE              ((uint32_t)0x30012200)            /*!< DVP2AXI C module base address */
#define DVP2AXI_D_BASE              ((uint32_t)0x30012300)            /*!< DVP2AXI D module base address */
#define DVP2AXI_E_BASE              ((uint32_t)0x30012400)            /*!< DVP2AXI E module base address */
#define DVP2AXI_F_BASE              ((uint32_t)0x30012500)            /*!< DVP2AXI F module base address */
#define DVP2AXI_G_BASE              ((uint32_t)0x30012600)            /*!< DVP2AXI G module base address */
#define DVP2AXI_H_BASE              ((uint32_t)0x30012700)            /*!< DVP2AXI H module base address */

#define ISP_DVP_TSRC_BASE           ((uint32_t)0x30012800)            /*!< ISP DVP test src module base address */
#define HDMI_DVP_TSRC_BASE          ((uint32_t)0x30012900)            /*!< HDMI DVP test src module base address */
#define ISP_AXI_CTRL_NR3D_BASE      ((uint32_t)0x30012A00)            /*!< 3DNR AXI ctrl module base address */

#define CSI_BASE                    ((uint32_t)0x3001A000)            /*!< MIPI CSI module base address */
#define AE_SRAM_BASE                ((uint32_t)0x30019000)            /*!< AE stats SRAM base address */
#define AWB_SRAM_BASE               ((uint32_t)0x3001C000)            /*!< AWB stats SRAM base address */
#define MJPEG_ENC_BASE              ((uint32_t)0x30021000)            /*!< MJPEG encoder base address */
#define H264_ENC_BASE               ((uint32_t)0x30022000)            /*!< H264 encoder base address */
#define MJPEG_DEC_BASE              ((uint32_t)0x30023000)            /*!< MJPEG decoder base address */
#define NPU_BASE                    ((uint32_t)0x30024000)            /*!< NPU base address */
#define SDH_BASE                    ((uint32_t)0x20060000)            /*!< SDH module base address */

#define MCU_MISC_BASE               ((uint32_t)0x20009000)
#define PDS_BASE                    ((uint32_t)0x2000e000)
#define HBN_BASE                    ((uint32_t)0x2000f000)
#define MM_MISC_BASE                ((uint32_t)0x30000000)
#define MM_GLB_BASE                 ((uint32_t)0x30007000)

#define OSD_PROBE_BASE              ((uint32_t)0x30012B00)            /*!< OSD Probe base address */
#define OSD_A_BASE                  ((uint32_t)0x30013000)            /*!< OSD A base address */
#define OSD_B_BASE                  ((uint32_t)0x30014000)            /*!< OSD B base address */
#  define OSD_BLEND0_OFFSET         (0x000)                           /*!< OSD blend layer 0 offset */
#  define OSD_BLEND1_OFFSET         (0x100)                           /*!< OSD blend layer 1 offset */
#  define OSD_BLEND2_OFFSET         (0x200)                           /*!< OSD blend layer 2 offset */
#  define OSD_BLEND3_OFFSET         (0x300)                           /*!< OSD blend layer 3 offset */
#  define OSD_DRAW_LOW_OFFSET       (0x400)                           /*!< OSD draw layer 0 offset */
#  define OSD_DRAW_HIGH_OFFSET      (0x504)                           /*!< OSD draw layer 1 offset */

#define BL808_FLASH_XIP_BASE                (0x58000000)
#define BL808_FLASH_XIP_END                 (0x58000000+64*1024*1024)
#define BL808_FLASH2_XIP_BASE               (0x5C000000)
#define BL808_FLASH2_XIP_END                (0x5C000000+64*1024*1024)
#define BL808_FLASH_XIP_REMAP0_BASE         (0xD8000000)
#define BL808_FLASH_XIP_REMAP0_END          (0xD8000000+64*1024*1024)
#define BL808_FLASH2_XIP_REMAP0_BASE        (0xDC000000)
#define BL808_FLASH2_XIP_REMAP0_END         (0xDC000000+64*1024*1024)
#include <system_bl808.h>

#include <stdint.h>
#include <stdio.h>

#ifdef ARCH_RISCV
#ifdef __GNUC__
    #include "cmsis_compatible_gcc.h"
    #include <csi_core.h>
#endif
#endif

/*@} end of group Peripheral_Register_Section */

#endif /* __BL808_H__ */
