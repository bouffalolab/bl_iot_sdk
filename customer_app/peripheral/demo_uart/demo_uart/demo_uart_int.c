/**
 * Copyright (c) 2016-2021 Bouffalolab Co., Ltd.
 *
 * Contact information:
 * web site:    https://www.bouffalolab.com/
 */

#include <stdio.h>
#include <cli.h>
#include <hosal_uart.h>
#include <blog.h>

/**
 * hal uart TX interrupt callback
 */
static int __uart_tx_callback(void *p_arg)
{
    static uint8_t tx_counts = 0;
    char buf[] = "TX interrupt TEST\r\n";
    hosal_uart_dev_t *p_dev = (hosal_uart_dev_t *)p_arg;

    if (tx_counts < sizeof(buf)) {
        hosal_uart_send(p_dev, &buf[tx_counts++], 1);
    } else {
        /* If the data transfer is completed, turn off the TX trigger mode */
        hosal_uart_ioctl(p_dev, HOSAL_UART_TX_TRIGGER_OFF, NULL);
    }

    return 0;
}

/**
 * hal uart RX interrupt callback
 */
static int __uart_rx_callback(void *p_arg)
{
    int ret;
    uint8_t data_buf[32];
    hosal_uart_dev_t *p_dev = (hosal_uart_dev_t *)p_arg;

    ret = hosal_uart_receive(p_dev, data_buf, sizeof(data_buf));
    hosal_uart_send(p_dev, data_buf, ret);
    return 0;
}

/**
 * hal uart interrupt mode demo
 */
void demo_hosal_uart_int(int uart_id)
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

    /* Uart init device */
    hosal_uart_init(&uart_dev);

    /* Configure UART to interrupt mode */
    hosal_uart_ioctl(&uart_dev, HOSAL_UART_MODE_SET, (void *)HOSAL_UART_MODE_INT);

    /* Set TX RX interrupt callback */
    hosal_uart_callback_set(&uart_dev, HOSAL_UART_RX_CALLBACK,
                          __uart_rx_callback, &uart_dev);
    hosal_uart_callback_set(&uart_dev, HOSAL_UART_TX_CALLBACK,
                          __uart_tx_callback, &uart_dev);

    /* UART TX interrupt start */
    hosal_uart_ioctl(&uart_dev, HOSAL_UART_TX_TRIGGER_ON, NULL);

    while (1) {
        /* Do not let the test return */
    }
}
