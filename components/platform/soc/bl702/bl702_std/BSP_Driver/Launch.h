#ifndef __LAUNCH_FILE__
#define __LAUNCH_FILE__


/*
 * launch file describe hardware infomation 
 * such as board pin assign or chip select
 * 
 */ 


//uart pin assign
#define BL702EVB_LAUNCHXL_UART_DEBUG_TX          GLB_GPIO_PIN_14
#define BL702EVB_LAUNCHXL_UART_DEBUG_RX          GLB_GPIO_PIN_15

#define BL702EVB_LAUNCHXL_UART_DATA_TX           GLB_GPIO_PIN_0
#define BL702EVB_LAUNCHXL_UART_DATA_RX           GLB_GPIO_PIN_1
//uart define
typedef enum {
    BL702EVB_LAUNCHXL_UART0=0,
    BL702EVB_LAUNCHXL_UART1,
    BL702EVB_LAUNCHXL_UARTCOUNT,
}BL702_EVB_UART_NUMBER;


//adc pin assign 


//adc define
typedef enum {
    BL702EVB_LAUNCHXL_ADC=0,
    BL702EVB_LAUNCHXL_ADCCOUNT,
}BL702_EVB_ADC_NUMBER;


//adc define
typedef enum {
    BL702EVB_LAUNCHXL_DAC=0,
    BL702EVB_LAUNCHXL_DACCOUNT,
}BL702_EVB_DAC_NUMBER;

//pin define
/* This length define maximum number of IO chips Which Depending on how the chip is packaged*/
#define BL702_PIN_MAX   23


//spi define
typedef enum {
    BL702EVB_LAUNCHXL_SPI=0,
    BL702EVB_LAUNCHXL_SPICOUNT,
}BL702_EVB_SPI_NUMBER;


//pwm define

typedef enum{
    BL702EVB_LAUNCHXL_PWM=0,
    BL702EVB_LAUNCHXL_PWMCOUNT,
}BL702_EVB_PWM_NUMBER;


//watch dog 
typedef enum{
    BL702EVB_LAUNCHXL_WATCHDOG=0,
    BL702EVB_LAUNCHXL_WATCHDOGCOUNT,
}BL702_EVB_WATCHDOG_NUMBER;


//timer
typedef enum{
    BL702EVB_LAUNCHXL_TIMER_0=0,
    BL702EVB_LAUNCHXL_TIMER_1,
    BL702EVB_LAUNCHXL_TIMERCOUNT,
}BL702_EVB_TIMER_NUMBER;


//i2c
typedef enum{
    BL702EVB_LAUNCHXL_I2C=0,
    BL702EVB_LAUNCHXL_I2CCOUNT,
}BL702_EVB_I2C_NUMBER;
#endif