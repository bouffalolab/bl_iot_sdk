#ifndef __UART_TXRX_H__
#define __UART_TXRX_H__

#include <stdint.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

typedef enum {
    JL_APP_UART_MSG_APP2CTL,
    JL_APP_UART_MSG_CTL2APP,
    JL_APP_UART_MSG_TYPE_MAX
} jl_app_uart_msg_type_t;

typedef void (*jl_app_uart_recv_cb_t)(const uint8_t *data, const uint16_t data_len, void *cb_arg);
typedef int (*jl_app_uart_msg_check_cb_t)(const uint8_t *data, const uint16_t data_len, void *cb_arg);

typedef struct {
    jl_app_uart_msg_type_t type;
    uint16_t len;
    uint16_t delay_ms;
    uint8_t msg[];
} jl_app_uart_msg_item_t;

typedef struct {
    uint8_t *buf;
    int w;
    int r;
    int size;
    int cap;
} jl_app_uart_rx_ring_t;

typedef struct {
    int uart_fd;
    QueueHandle_t msg_queue;
    uint16_t msg_len;
    uint8_t *frame_header;
    uint16_t frame_header_length;

    jl_app_uart_recv_cb_t recv_cb;
    void *recv_cb_arg;
    jl_app_uart_msg_check_cb_t msg_check_cb;
    void *msg_check_cb_arg;

    jl_app_uart_msg_item_t *send_buf;
    jl_app_uart_msg_item_t *recv_buf;
    jl_app_uart_msg_item_t *send_buf2;

    TaskHandle_t recv_task;
    TaskHandle_t queue_proc_task;

    jl_app_uart_rx_ring_t ring;
    uint8_t *ring_linear_buf;
} jl_app_uart_ctx_t;

#define JL_APP_UART_RECV_BUF_LEN 64
#define JL_APP_UART_MSG_ITEM_HEADER_LEN sizeof(jl_app_uart_msg_item_t)

#define JL_APP_UART_RECV_TASK_STACK_DEPTH       1024
#define JL_APP_UART_QUEUE_PROC_TASK_STACK_DEPTH 2048

int jl_app_uart_init(jl_app_uart_ctx_t *ctx, const char *uart_dev, const int baudrate,
        const uint16_t msg_len, const uint16_t queue_length,
        const uint8_t *frame_header, const uint16_t frame_header_length);
int jl_app_uart_recv_cb_register(jl_app_uart_ctx_t *ctx, jl_app_uart_recv_cb_t cb, void *cb_arg);
int jl_app_uart_msg_check_cb_register(jl_app_uart_ctx_t *ctx, jl_app_uart_msg_check_cb_t cb, void *cb_arg);
int jl_app_uart_send(const jl_app_uart_ctx_t *const ctx, const uint8_t *data, const uint16_t data_len, const uint16_t delay_before_send_ms);
void jl_app_write_uart(jl_app_uart_ctx_t *ctx, const uint8_t *buf, uint16_t len);
int jl_app_uart_start_txrx(jl_app_uart_ctx_t *ctx);

#endif /* ifndef __UART_TXRX_H__ */
