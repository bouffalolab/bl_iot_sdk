#include <stdint.h>
#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

#include <utils_log.h>

#include <uart_txrx.h>

static void uart_recv_cb(const uint8_t *data, const uint16_t data_len, void *cb_arg)
{
    log_info("UART RECV %u bytes\r\n", data_len);
    log_buf(data, data_len);
}

// Return 0 to accept data
// Otherwise drop it
static int uart_check_cb(const uint8_t *data, const uint16_t data_len, void *cb_ag)
{
    return 0;
}

static void uart_txrx_test_entry(void *parm)
{
    jl_app_uart_ctx_t *ctx = parm;
#define BUF_LEN 36
    uint8_t buf[BUF_LEN];
    int len;
    int cnt = 0;
    int i;

    while (1) {
        vTaskDelay(100);
        len = snprintf((char *)buf, sizeof(buf), "FAKE MSG CNT %d", cnt++);
        for (i = 0; i < BUF_LEN - len; ++i) {
            buf[len + i] = 'F';
        }
        jl_app_uart_send(ctx, buf, BUF_LEN, 0);
    }
}

void test_jl_uart_txrx()
{
    jl_app_uart_ctx_t *ctx = pvPortMalloc(sizeof(jl_app_uart_ctx_t));
    if (ctx) {
        if (jl_app_uart_init(ctx, "/dev/ttyS1", 9600, 36, 3, (uint8_t *)"aaba", 4)) {
            printf("uart init error\r\n");
            return;
        }
        jl_app_uart_recv_cb_register(ctx, uart_recv_cb, ctx);
        jl_app_uart_msg_check_cb_register(ctx, uart_check_cb, ctx);
        jl_app_uart_start_txrx(ctx);

        xTaskCreate(uart_txrx_test_entry, "uart_test", 1024, ctx, 15, NULL);
    }
}
