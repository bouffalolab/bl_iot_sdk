#ifndef __HAL_UART_H__
#define __HAL_UART_H__
int vfs_uart_init(uint32_t fdt, uint32_t dtb_uart_offset);
int vfs_uart_init_simple_mode(uint8_t id, uint8_t pin_tx, uint8_t pin_rx, int baudrate, const char *path);
int hal_uart_data_notify(int number, int dir);
#endif
