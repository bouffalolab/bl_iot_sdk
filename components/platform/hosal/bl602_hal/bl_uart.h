#ifndef __BL_UART_H__
#define __BL_UART_H__
#include <stdint.h>
#include <bl602_uart.h>
#define BL_UART_BUFFER_SIZE_MIN   (128)
#define BL_UART_BUFFER_SIZE_MASK  (128 - 1)
typedef void (*cb_uart_notify_t)(void *arg);
int bl_uart_gpio_init(uint8_t id, uint8_t tx, uint8_t rx, uint8_t rts, uint8_t cts, int baudrate);
int bl_uart_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin, uint32_t baudrate);
int bl_uart_debug_early_init(uint32_t baudrate);
int bl_uart_early_init(uint8_t id, uint8_t tx_pin, uint32_t baudrate);

int bl_uart_int_rx_enable(uint8_t id);
int bl_uart_int_rx_disable(uint8_t id);
int bl_uart_int_tx_enable(uint8_t id);
int bl_uart_int_tx_disable(uint8_t id);
int bl_uart_string_send(uint8_t id, char *data);
int bl_uart_flush(uint8_t id);
void bl_uart_getdefconfig(uint8_t id, uint8_t *parity);
void bl_uart_setconfig(uint8_t id, uint32_t baudrate, UART_Parity_Type parity);
void bl_uart_setbaud(uint8_t id, uint32_t baud);
int bl_uart_data_send(uint8_t id, uint8_t data);
int bl_uart_datas_send(uint8_t id, uint8_t *data, int len);
int bl_uart_data_recv(uint8_t id);
int bl_uart_int_enable(uint8_t id);
int bl_uart_int_disable(uint8_t id);
int bl_uart_int_rx_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg);
int bl_uart_int_tx_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg);
int bl_uart_int_rx_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg);
int bl_uart_int_tx_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg);
#endif
