
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include <bl_timer.h>
#include <bl_uart.h>
#include <hosal_uart.h>

#include <openthread-core-config.h>
#include <openthread/config.h>

#include <openthread/platform/debug_uart.h>
#include <openthread/platform/logging.h>
#include <openthread_port.h>
#include <utils/uart.h>


#define OT_UART_RX_TIMER_ID                     1

extern hosal_uart_dev_t uart_stdio;
#if CFG_USB_CDC_ENABLE

otError otPlatUartEnable(void) {return OT_ERROR_NONE;}
otError otPlatUartDisable(void) {return OT_ERROR_NONE;}
otError otPlatUartSend(const uint8_t *aBuf, uint16_t aBufLength) 
{
    extern int usb_cdc_is_port_open(void);
    extern int usb_cdc_data_send(const uint8_t *data, uint32_t len);
    if(usb_cdc_is_port_open()){
        usb_cdc_data_send(aBuf, aBufLength);
    } else
    {
        for (uint32_t i = 0; i < aBufLength; i ++) {
            bl_uart_data_send(uart_stdio.config.uart_id, aBuf[i]);
        }
    }
    otPlatUartSendDone();

    return OT_ERROR_NONE;
}

otError otPlatUartFlush(void) {return OT_ERROR_NONE;}

void ot_uartRecieved(uint8_t * rxbuf, uint32_t rxlen) 
{
    OT_THREAD_SAFE(
        otPlatUartReceived(rxbuf, rxlen);
    );
}

void ot_uartTask (ot_system_event_t sevent) {}
#else

void otPlatDebugUart_write_bytes(const uint8_t *pBytes, int nBytes)
{
}

typedef struct _otUart {
    uint32_t    txlen;
    uint8_t     *ptrTx;
    uint32_t    rxlen;
    uint8_t     rxbuf[OT_UART_RX_BUFFSIZE];
} otUart_t;

static otUart_t otUart_var;

static int ot_uartRxdCb(void *p_arg);

otError otPlatUartEnable(void)
{
    hosal_uart_callback_set(&uart_stdio, HOSAL_UART_RX_CALLBACK, ot_uartRxdCb, NULL);

    uart_stdio.config.mode = HOSAL_UART_MODE_INT;
    hosal_uart_init(&uart_stdio);

    memset(&otUart_var, 0, sizeof(otUart_t));

    return OT_ERROR_NONE;
}

otError otPlatUartDisable(void)
{
    hosal_uart_finalize(&uart_stdio);
    memset(&otUart_var, 0, sizeof(otUart_t));
    return OT_ERROR_NONE;
}

otError otPlatUartSend(const uint8_t *aBuf, uint16_t aBufLength)
{
    hosal_uart_send(&uart_stdio, aBuf, aBufLength);

    otPlatUartSendDone();
    return OT_ERROR_NONE;
}

otError otPlatUartFlush(void)
{
    hosal_uart_ioctl(&uart_stdio, HOSAL_UART_FLUSH, NULL);

    return OT_ERROR_NONE;
}


static void ot_uartRxTimeout(void)
{
    OT_NOTIFY_ISR(OT_SYSTEM_EVENT_UART_RXD);
}

static int ot_uartRxdCb(void *p_arg)
{
    uint32_t len = 0;
    len = hosal_uart_receive(&uart_stdio, otUart_var.rxbuf + otUart_var.rxlen, OT_UART_RX_BUFFSIZE - otUart_var.rxlen);
    otUart_var.rxlen += len;
    bl_timer_stop(OT_UART_RX_TIMER_ID);
    if (otUart_var.rxlen == OT_UART_RX_BUFFSIZE) {
        OT_NOTIFY_ISR(OT_SYSTEM_EVENT_UART_RXD);
    } else {
        bl_timer_start(OT_UART_RX_TIMER_ID, bl_timer_get_current_time() + 10 * 1000, ot_uartRxTimeout);
    }

    return 0;
}

void ot_uartTask (ot_system_event_t sevent) 
{
    if (!(OT_SYSETM_EVENT_UART_ALL_MASK & sevent)) {
        return;
    }

    if (OT_SYSTEM_EVENT_UART_RXD & sevent) {
        otPlatUartReceived(otUart_var.rxbuf, otUart_var.rxlen);
        otUart_var.rxlen = 0;
    }
}

#endif