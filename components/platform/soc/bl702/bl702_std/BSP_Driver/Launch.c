#include "hal_uart.h"
#include "hal_dma.h"
#include "hal_adc.h"
#include "hal_dac.h"
#include "hal_pin.h"
#include "hal_spi.h"
#include "hal_pwm.h"
#include "hal_wtd.h"
#include "hal_timer.h"
#include "hal_i2c.h"
#include "lhal_bl702_uart.h"
#include "lhal_bl702_dma.h"
#include "lhal_bl702_adc.h"
#include "lhal_bl702_dac.h"
#include "lhal_bl702_pin.h"
#include "lhal_bl702_spi.h"
#include "lhal_bl702_pwm.h"
#include "lhal_bl702_wtd.h"
#include "lhal_bl702_timer.h"
#include "lhal_bl702_i2c.h"
#include "launch.h"
#include "bl702.h"
#include "bl702_glb.h"
#include "bl702_romdriver.h"
#include "bl702_common.h"
#include "bl702_adc.h"
#include "bflb_platform.h"
#include "ring_buffer.h"

UARTBLXXX_Object uartBLXXXObjects[BL702EVB_LAUNCHXL_UARTCOUNT];

uint8_t uartBLXXXRingBuffer[BL702EVB_LAUNCHXL_UARTCOUNT][32];

extern const UART_FxnTable UARTBLXXX_fxnTable;

//error handle
void uart_error_callback(UART_Handle handle, uint32_t error){
    // handle occour error 
    MSG("UART handle = %d error ,error id = %d\r\n",handle,error);
}

//
const UARTBLXXX_HWAttrsV2 uartBLXXXHWAttrs[BL702EVB_LAUNCHXL_UARTCOUNT] = {
    {
        .deviceIndex       = 0,
        .txPin          = BL702EVB_LAUNCHXL_UART_DEBUG_TX,
        .rxPin          = BL702EVB_LAUNCHXL_UART_DEBUG_RX,
        .ctsPin         = 0,
        .rtsPin         = 0,
        .ringBufPtr     = uartBLXXXRingBuffer[BL702EVB_LAUNCHXL_UART0],
        .ringBufSize    = sizeof(uartBLXXXRingBuffer[BL702EVB_LAUNCHXL_UART0]),
        .ringBufferLockFnx = NULL,
        .ringBufferUnlockFnx = NULL,
        .dmaTxIntFifoThr   = 16,
        .dmaRxIntFifoThr   = 16,
        .errorFxn       = uart_error_callback
    },

    {
        .deviceIndex       = 1,
        .txPin          = BL702EVB_LAUNCHXL_UART_DATA_TX,
        .rxPin          = BL702EVB_LAUNCHXL_UART_DATA_RX,
        .ctsPin         = 0,
        .rtsPin         = 0,
        .ringBufPtr     = uartBLXXXRingBuffer[BL702EVB_LAUNCHXL_UART1],
        .ringBufSize    = sizeof(uartBLXXXRingBuffer[BL702EVB_LAUNCHXL_UART1]),
        .ringBufferLockFnx = NULL,
        .ringBufferUnlockFnx = NULL,
        .dmaTxIntFifoThr   = 16,
        .dmaRxIntFifoThr   = 16,
        .errorFxn       = uart_error_callback
    }
};


const UART_Config UART_config[BL702EVB_LAUNCHXL_UARTCOUNT] = {
    {
        .fxnTablePtr = &UARTBLXXX_fxnTable,
        .object      = &uartBLXXXObjects[BL702EVB_LAUNCHXL_UART0],
        .hwAttrs     = &uartBLXXXHWAttrs[BL702EVB_LAUNCHXL_UART0]
    },
    {
        .fxnTablePtr = &UARTBLXXX_fxnTable,
        .object      = &uartBLXXXObjects[BL702EVB_LAUNCHXL_UART1],
        .hwAttrs     = &uartBLXXXHWAttrs[BL702EVB_LAUNCHXL_UART1]
    },
};

const uint8_t UART_count = BL702EVB_LAUNCHXL_UARTCOUNT;



//==================DMA=======================

DMABLXXX_Object dmaBLXXXObjects[DMA_CH_MAX];

extern const DMA_FxnTable DMABLXXX_fxnTable;

//error handle
void dma_ch0_error_callback(void){
    // handle occour error 
    MSG("DMA CH0 ERROR HAPPEND\r\n");
}

//error handle
void dma_ch1_error_callback(void){
    // handle occour error 
    MSG("DMA CH1 ERROR HAPPEND\r\n");
}
//error handle
void dma_ch2_error_callback(void){
    // handle occour error 
    MSG("DMA CH2 ERROR HAPPEND\r\n");
}
//error handle
void dma_ch3_error_callback(void){
    // handle occour error 
    MSG("DMA CH3 ERROR HAPPEND\r\n");
}
//
__WEAK 
const DMABLXXX_HWAttrsV2 dmaBLXXXHWAttrs[DMA_CH_MAX] = {
    {
        .errorFxn       = dma_ch0_error_callback
    },
    {
        .errorFxn       = dma_ch1_error_callback
    },
    {
        .errorFxn       = dma_ch2_error_callback
    },
    {
        .errorFxn       = dma_ch3_error_callback
    },
};

const DMA_Config DMA_config[DMA_CH_MAX] = {
    {
        .fxnTablePtr = &DMABLXXX_fxnTable,
        .object      = &dmaBLXXXObjects[DMA_CH0],
        .hwAttrs     = &dmaBLXXXHWAttrs[DMA_CH0]
    },
    {
        .fxnTablePtr = &DMABLXXX_fxnTable,
        .object      = &dmaBLXXXObjects[DMA_CH1],
        .hwAttrs     = &dmaBLXXXHWAttrs[DMA_CH1]
    },
    {
        .fxnTablePtr = &DMABLXXX_fxnTable,
        .object      = &dmaBLXXXObjects[DMA_CH2],
        .hwAttrs     = &dmaBLXXXHWAttrs[DMA_CH2]
    },
    {
        .fxnTablePtr = &DMABLXXX_fxnTable,
        .object      = &dmaBLXXXObjects[DMA_CH3],
        .hwAttrs     = &dmaBLXXXHWAttrs[DMA_CH3]
    },
    {
        .fxnTablePtr = &DMABLXXX_fxnTable,
        .object      = &dmaBLXXXObjects[DMA_CH4],
        .hwAttrs     = &dmaBLXXXHWAttrs[DMA_CH4]
    },
    {
        .fxnTablePtr = &DMABLXXX_fxnTable,
        .object      = &dmaBLXXXObjects[DMA_CH5],
        .hwAttrs     = &dmaBLXXXHWAttrs[DMA_CH5]
    },
    {
        .fxnTablePtr = &DMABLXXX_fxnTable,
        .object      = &dmaBLXXXObjects[DMA_CH6],
        .hwAttrs     = &dmaBLXXXHWAttrs[DMA_CH6]
    },
    {
        .fxnTablePtr = &DMABLXXX_fxnTable,
        .object      = &dmaBLXXXObjects[DMA_CH7],
        .hwAttrs     = &dmaBLXXXHWAttrs[DMA_CH7]
    },
};

const uint8_t DMA_count = DMA_CH_MAX;



//==================ADC===========================
ADCBLXXX_Object adcBLXXXObjects[DMA_CH_MAX];

extern const ADC_FxnTable ADCBLXXX_fxnTable;

//error handle
void adc_pos_saturation_callback(void)
{
    MSG("adc_pos_saturation error happend\r\n");
}
void adc_neg_saturation_callback(void)
{
    MSG("adc_neg_saturation error happend\r\n");
}
void adc_overrun_callback(void)
{
    MSG("adc_overrun_saturation error happend\r\n");
}
void adc_underrun_callback(void)
{
    MSG("adc_underrun_saturation error happend\r\n");
}

/*
 * In This Version ADC conversion queue only support one woring mode ,diff or single
 * 
 *          {ADC_CHAN0,ADC_CHAN_GND},
 *          {ADC_CHAN1,ADC_CHAN_GND},
 *          {ADC_CHAN2,ADC_CHAN3},
 * 
 * lt is a not correctly pin assign and will throw a exception 
 * 
 * Correct configuration is
 *          {ADC_CHAN0,ADC_CHAN_GND},
            {ADC_CHAN1,ADC_CHAN_GND},
            {ADC_CHAN2,ADC_CHAN_GND},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
    or

 *          {ADC_CHAN0,ADC_CHAN1},
            {ADC_CHAN2,ADC_CHAN3},
            {ADC_CHAN4,ADC_CHAN5},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},    

    if user want to use two mode at one program please ADC_open and get data then ADC_close
    and re initial adc parameter .

    or single input mode using diff mode , but that means the single input precision is reduced .
    0-65535 single input will reduced as (-32768 ,0 ,32768) 

 * if user use adc single input mode(is_diff = false) , negative gpio assign should set as GLB_GPIO_GND 
 *
 * if user want to use mic function , BLXXXEVB_MIC Config must define at first position
 */



__WEAK 
const ADCBLXXX_HWAttrsV2 adcBLXXXHWAttrs[BL702EVB_LAUNCHXL_ADCCOUNT] = {
    {
        .adc_gpio_pin_list = {
            {GLB_GPIO_PIN_6,GLB_GPIO_GND},
            {GLB_GPIO_PIN_5,GLB_GPIO_GND},
            {GLB_GPIO_PIN_4,GLB_GPIO_GND},
            {PIN_UNASSIGNED,PIN_UNASSIGNED},
            {PIN_UNASSIGNED,PIN_UNASSIGNED},
            {PIN_UNASSIGNED,PIN_UNASSIGNED},
            {PIN_UNASSIGNED,PIN_UNASSIGNED},
            {PIN_UNASSIGNED,PIN_UNASSIGNED},
            {PIN_UNASSIGNED,PIN_UNASSIGNED},
            {PIN_UNASSIGNED,PIN_UNASSIGNED},
            {PIN_UNASSIGNED,PIN_UNASSIGNED},
        },

        .adc_gpio_ch_list = {
            {ADC_CHAN5,ADC_CHAN_GND},
            {ADC_CHAN4,ADC_CHAN_GND},
            {ADC_CHAN1,ADC_CHAN_GND},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
            {ADC_CHANNEL_UNUSED,ADC_CHANNEL_UNUSED},
        },
        .is_diff_input = false,
        .adc_fifo_dma_threshold = ADC_FIFO_THRESHOLD_16,
        .underrun_callback = adc_underrun_callback,
        .overrun_callback = adc_overrun_callback,
        .pos_Saturation_callback = adc_pos_saturation_callback,
        .neg_Saturation_callback = adc_neg_saturation_callback,
    }
};


const ADC_Config ADC_config[BL702EVB_LAUNCHXL_ADCCOUNT] = {
    {
        .fxnTablePtr = &ADCBLXXX_fxnTable,
        .object      = &adcBLXXXObjects[BL702EVB_LAUNCHXL_ADC],
        .hwAttrs     = &adcBLXXXHWAttrs[BL702EVB_LAUNCHXL_ADC]
    },
};

const uint8_t ADC_count = BL702EVB_LAUNCHXL_ADCCOUNT;

//==================DAC===========================

DACBLXXX_Object dacBLXXXObjects[DMA_CH_MAX];
extern const DAC_FxnTable DACBLXXX_fxnTable;
__WEAK 
const DACBLXXX_HWAttrsV2 dacBLXXXHWAttrs[BL702EVB_LAUNCHXL_DACCOUNT] = {
    {
    .dac_output_pin_0 = GLB_GPIO_PIN_13,
    .dac_output_pin_1 = GLB_GPIO_PIN_14,
    },
};

const DAC_Config DAC_config[BL702EVB_LAUNCHXL_DACCOUNT] = {
    {
        .fxnTablePtr = &DACBLXXX_fxnTable,
        .object      = &dacBLXXXObjects[BL702EVB_LAUNCHXL_DAC],
        .hwAttrs     = &dacBLXXXHWAttrs[BL702EVB_LAUNCHXL_DAC]
    },
};

const uint8_t DAC_count = BL702EVB_LAUNCHXL_DACCOUNT;


//==================PIN===========================
extern const PIN_FxnTable PINBLXXX_fxnTable;
PINBLXXX_Object pinBLXXXObjects;
const PIN_Config PIN_config = {
    .fxnTablePtr = &PINBLXXX_fxnTable,
    .object = &pinBLXXXObjects,
};

const uint8_t PIN_count = BL702_PIN_MAX;


//==================SPI============================
SPIBLXXX_Object SPIBLXXXObjects[BL702EVB_LAUNCHXL_SPICOUNT];
extern const SPI_FxnTable SPIBLXXX_fxnTable;
__WEAK 
const SPIBLXXX_HWAttrsV2 SPIBLXXXHWAttrs[BL702EVB_LAUNCHXL_SPICOUNT] = {
    {
        .spi_sclk_pin = GLB_GPIO_PIN_3,
        .spi_miso_pin = GLB_GPIO_PIN_4,
        .spi_mosi_pin = GLB_GPIO_PIN_5,
        .spi_cs_pin = PIN_UNASSIGNED,
        .spi_index = 0,
        .spi_tx_dma_thr = 1,
        .spi_rx_dma_thr = 1,
    },
};

const SPI_Config SPI_config[BL702EVB_LAUNCHXL_SPICOUNT] = {
    {
        .fxnTablePtr = &SPIBLXXX_fxnTable,
        .object      = &SPIBLXXXObjects[BL702EVB_LAUNCHXL_SPI],
        .hwAttrs     = &SPIBLXXXHWAttrs[BL702EVB_LAUNCHXL_SPI]
    },
};

const uint8_t SPI_count = BL702EVB_LAUNCHXL_SPICOUNT;

//==================PWM============================
PWMBLXXX_Object PWMBLXXXObjects[DMA_CH_MAX];
extern const PWM_FxnTable PWMBLXXX_fxnTable;
__WEAK 
const PWMBLXXX_HWAttrsV2 PWMBLXXXHWAttrs[BL702EVB_LAUNCHXL_PWMCOUNT] = {
    {
        .pwm_output_pin = {
            GLB_GPIO_PIN_0,
            GLB_GPIO_PIN_1,
            GLB_GPIO_PIN_2,
            GLB_GPIO_PIN_3,
            GLB_GPIO_PIN_4,
        },
    },
};

const PWM_Config PWM_config[BL702EVB_LAUNCHXL_PWMCOUNT] = {
    {
        .fxnTablePtr = &PWMBLXXX_fxnTable,
        .object      = &PWMBLXXXObjects[BL702EVB_LAUNCHXL_PWM],
        .hwAttrs     = &PWMBLXXXHWAttrs[BL702EVB_LAUNCHXL_PWM]
    },
};

const uint8_t PWM_count = BL702EVB_LAUNCHXL_PWMCOUNT;

/*
 *  =============================== Watchdog ===============================
 */
WatchdogBLXXX_Object watchdogBLXXXObjects[BL702EVB_LAUNCHXL_WATCHDOGCOUNT];
extern const Watchdog_FxnTable WatchdogBLXXX_fxnTable;
const WatchdogBLXXX_HWAttrs watchdogBLXXXHWAttrs[BL702EVB_LAUNCHXL_WATCHDOGCOUNT] = {
    {
        .baseAddr    = 0,
        .reloadValue = 32768 
    },
};

const Watchdog_Config Watchdog_config[BL702EVB_LAUNCHXL_WATCHDOGCOUNT] = {
    {
        .fxnTablePtr = &WatchdogBLXXX_fxnTable,
        .object      = &watchdogBLXXXObjects[BL702EVB_LAUNCHXL_WATCHDOG],
        .hwAttrs     = &watchdogBLXXXHWAttrs[BL702EVB_LAUNCHXL_WATCHDOG]
    },
};

const uint_least8_t Watchdog_count = BL702EVB_LAUNCHXL_WATCHDOGCOUNT;

/*
 *  =============================== Timer ===============================
 */
TIMERBLXXX_Object TimerBLXXXObjects[BL702EVB_LAUNCHXL_TIMERCOUNT];
extern const Timer_FxnTable TimerBLXXX_fxnTable;
__WEAK
const TIMERBLXXX_HWAttrsV2 TimerBLXXXHWAttrs[BL702EVB_LAUNCHXL_TIMERCOUNT] = {
    {
        .deviceIndex = 0,
        .width = TIMER_WIDTH_32BIT,
    },
    {
        .deviceIndex = 1,
        .width = TIMER_WIDTH_32BIT,        
    }
};

const Timer_Config Timer_config[BL702EVB_LAUNCHXL_TIMERCOUNT] = {
    {
        .fxnTablePtr = &TimerBLXXX_fxnTable,
        .object      = &TimerBLXXXObjects[BL702EVB_LAUNCHXL_TIMER_0],
        .hwAttrs     = &TimerBLXXXHWAttrs[BL702EVB_LAUNCHXL_TIMER_0]
    },
    {
        .fxnTablePtr = &TimerBLXXX_fxnTable,
        .object      = &TimerBLXXXObjects[BL702EVB_LAUNCHXL_TIMER_1],
        .hwAttrs     = &TimerBLXXXHWAttrs[BL702EVB_LAUNCHXL_TIMER_1]
    },
};

const uint_least8_t Timer_count = BL702EVB_LAUNCHXL_TIMERCOUNT;

/*
 *  =============================== I2C ===============================
 */
I2CBLXXX_Object I2CBLXXXObjects[BL702EVB_LAUNCHXL_I2CCOUNT];
extern const I2C_FxnTable I2CBLXXX_fxnTable;
__WEAK
const I2CBLXXX_HWAttrsV2 I2CBLXXXHWAttrs[BL702EVB_LAUNCHXL_I2CCOUNT] = {
    {
    .deviceIndex = 0,
    .sdaPin = GLB_GPIO_PIN_1,
    .sclPin = GLB_GPIO_PIN_0,
    },
};

const I2C_Config I2C_config[BL702EVB_LAUNCHXL_I2CCOUNT] = {
    {
        .fxnTablePtr = &I2CBLXXX_fxnTable,
        .object      = &I2CBLXXXObjects[BL702EVB_LAUNCHXL_I2C],
        .hwAttrs     = &I2CBLXXXHWAttrs[BL702EVB_LAUNCHXL_I2C]
    },
};

const uint_least8_t I2C_count = BL702EVB_LAUNCHXL_I2CCOUNT;
