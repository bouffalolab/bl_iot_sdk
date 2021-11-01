#ifndef __PLATFORM_GPIO_H__
#define __PLATFORM_GPIO_H__


#include "bl702_uart.h"
#include "bl702_glb.h"
#include "bl702_gpio.h"

/*UART  dbug option */
#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
#define BFLB_UART_DBG_RX_GPIO          GLB_GPIO_PIN_15
#define BFLB_UART_DBG_RX_INPUT_FUN     GPIO15_FUN_REG_GPIO_15
#define BFLB_UART_DBG_RX_NORMAL_FUN    GPIO15_FUN_UART_SIG7_UART_SIG3
#define BFLB_UART_DBG_RX_SIG           GLB_UART_SIG_7
#define BFLB_UART_DBG_RX_SIG_FUN       GLB_UART_SIG_FUN_UART0_RXD

#define BFLB_UART_DBG_TX_GPIO          GLB_GPIO_PIN_14
#define BFLB_UART_DBG_TX_INPUT_FUN     GPIO14_FUN_REG_GPIO_14
#define BFLB_UART_DBG_TX_NORMAL_FUN    GPIO14_FUN_UART_SIG6_UART_SIG2
#define BFLB_UART_DBG_TX_SIG           GLB_UART_SIG_6
#define BFLB_UART_DBG_TX_SIG_FUN       GLB_UART_SIG_FUN_UART0_TXD
#else
#define BFLB_UART_DBG_TX_GPIO          GLB_GPIO_PIN_17
#define BFLB_UART_DBG_TX_INPUT_FUN     GPIO17_FUN_REG_GPIO_17
#define BFLB_UART_DBG_TX_NORMAL_FUN    GPIO17_FUN_UART_SIG1_UART_SIG5
#define BFLB_UART_DBG_TX_SIG           GLB_UART_SIG_1
#define BFLB_UART_DBG_TX_SIG_FUN       GLB_UART_SIG_FUN_UART1_TXD
#endif

void bflb_platform_init_uart_debug_gpio(void);
void bflb_platform_deinit_uart_debug_gpio(void);


#endif

