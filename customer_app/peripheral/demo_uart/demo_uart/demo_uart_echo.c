/**
 * Copyright (c) 2016-2021 Bouffalolab Co., Ltd.
 *
 * Contact information:
 * web site:    https://www.bouffalolab.com/
 */

#include <stdio.h>
#include <cli.h>
#include <hosal_uart.h>

/**
 * hosal uart echo demo
 */
void demo_hosal_uart_echo(int uart_id)
{
    /**
     *  Define a UART device,
     *  TX pin : 16/14
     *  RX pin : 7/15
     *  baud : 2000000
     */
#ifdef CONF_USER_BL702
HOSAL_UART_DEV_DECL(uart_dev, uart_id, 14, 15, 2000000);
#elif CONF_USER_BL602
HOSAL_UART_DEV_DECL(uart_dev, uart_id, 16, 7, 2000000);
#endif
    uint8_t data[32];
    int ret;

    /* Uart init device */
    hosal_uart_init(&uart_dev);

    while (1) {
        /* Uart receive poll */
        ret = hosal_uart_receive(&uart_dev, data, sizeof(data));
        if (ret > 0) {
            /* Uart send poll */
            hosal_uart_send(&uart_dev, data, ret);
        }
    }
}
