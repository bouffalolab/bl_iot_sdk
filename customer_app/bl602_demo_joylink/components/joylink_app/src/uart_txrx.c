#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FreeRTOS.h>
#include <queue.h>

#include <vfs.h>

#include <uart_txrx.h>
#include <device/vfs_uart.h>

int jl_app_uart_init(jl_app_uart_ctx_t *ctx, const char *uart_dev, const int baudrate,
        const uint16_t msg_len, const uint16_t queue_length,
        const uint8_t *frame_header, const uint16_t frame_header_length)
{
    int ret = 0;
    jl_app_uart_rx_ring_t *ring = NULL;
    if (!ctx || !uart_dev || !baudrate || !msg_len || !queue_length
            || !frame_header || !frame_header_length) {
        ret = -1;
        goto ret;
    }

    memset(ctx, 0, sizeof(*ctx));

    if ((ctx->uart_fd = aos_open(uart_dev, 0)) < 0) {
        printf("[JL_APP_UART]: open uart failed\r\n");
        ret = -1;
        goto clean;
    }
    aos_ioctl(ctx->uart_fd, IOCTL_UART_IOC_BAUD_MODE, baudrate);

    if ((ctx->msg_queue = xQueueCreate(queue_length, JL_APP_UART_MSG_ITEM_HEADER_LEN + msg_len )) == NULL) {
        printf("[JL_APP_UART]: create queue failed\r\n");
        ret = -1;
        goto clean;
    }
    ctx->send_buf = pvPortMalloc(JL_APP_UART_MSG_ITEM_HEADER_LEN + msg_len);
    ctx->recv_buf = pvPortMalloc(JL_APP_UART_MSG_ITEM_HEADER_LEN + msg_len);
    ctx->send_buf2 = pvPortMalloc(JL_APP_UART_MSG_ITEM_HEADER_LEN + msg_len);
    ctx->frame_header = pvPortMalloc(frame_header_length);

    ring = &ctx->ring;
    ring->buf = pvPortMalloc(msg_len);
    ctx->ring_linear_buf = pvPortMalloc(msg_len);
    if (!ctx->send_buf || !ctx->recv_buf || !ctx->send_buf2 || !ctx->frame_header || !ring->buf || !ctx->ring_linear_buf) {
        ret = -1;
        goto clean;
    }

    ring->cap = msg_len;

    ctx->msg_len = msg_len;
    memcpy(ctx->frame_header, frame_header, frame_header_length);
    ctx->frame_header_length = frame_header_length;
    goto ret;
clean:
    if (ctx) {
        if (ctx->uart_fd >= 0) {
            aos_close(ctx->uart_fd);
        }
        if (ctx->msg_queue) {
            vQueueDelete(ctx->msg_queue);
        }
        if (ctx->send_buf) {
            vPortFree(ctx->send_buf);
        }
        if (ctx->recv_buf) {
            vPortFree(ctx->recv_buf);
        }
        if (ctx->send_buf2) {
            vPortFree(ctx->send_buf);
        }
        if (ctx->frame_header) {
            vPortFree(ctx->frame_header);
        }
        if (ring && ring->buf) {
            vPortFree(ring->buf);
        }
        if (ctx->ring_linear_buf) {
            vPortFree(ctx->ring_linear_buf);
        }
    }
ret:

    return ret;
}

int jl_app_uart_recv_cb_register(jl_app_uart_ctx_t *ctx, jl_app_uart_recv_cb_t cb, void *cb_arg)
{
    if (!ctx || !cb) {
        return -1;
    }

    ctx->recv_cb = cb;
    ctx->recv_cb_arg = cb_arg;
    return 0;
}

int jl_app_uart_msg_check_cb_register(jl_app_uart_ctx_t *ctx, jl_app_uart_msg_check_cb_t cb, void *cb_arg)
{
    if (!ctx || !cb) {
        return -1;
    }
    ctx->msg_check_cb = cb;
    ctx->msg_check_cb_arg = cb_arg;
    return 0;
}

int jl_app_uart_send(const jl_app_uart_ctx_t *const ctx, const uint8_t *data, const uint16_t data_len, const uint16_t delay_before_send_ms)
{
    jl_app_uart_msg_item_t *send_buf;

    if (!ctx || !data || !(0 < data_len && data_len <= ctx->msg_len)) {
        return -1;
    }

    send_buf = ctx->send_buf;
    send_buf->type = JL_APP_UART_MSG_APP2CTL;
    send_buf->len = data_len;
    send_buf->delay_ms = delay_before_send_ms;
    memcpy(send_buf->msg, data, data_len);

    xQueueSend(ctx->msg_queue, send_buf, 0);

    return 0;
}

static inline int ring_size(jl_app_uart_rx_ring_t *ring)
{
    return ring->size;
}

static inline int ring_capacity(jl_app_uart_rx_ring_t *ring)
{
    return ring->cap;
}

static inline int ring_remaining(jl_app_uart_rx_ring_t *ring)
{
    return ring->cap - ring->size;
}

static int ring_get_copy(const jl_app_uart_rx_ring_t *ring, uint8_t *out_buf)
{
    int ret;
    int cp_sz;
    if (ring->size) {
        cp_sz = ring->size < (ring->cap - ring->r) ? ring->size : (ring->cap - ring->r);
        memcpy(out_buf, ring->buf + ring->r, cp_sz);
        out_buf += cp_sz;
        cp_sz = ring->size - cp_sz;
        if (cp_sz > 0) {
            memcpy(out_buf, ring->buf, cp_sz);
            out_buf += cp_sz;
        }
        ret = ring->size;
    } else {
        ret = 0;
    }
    return ret;
}

static int ring_write(jl_app_uart_rx_ring_t *ring, const uint8_t *src, const int sz)
{
    int cp_sz;
    cp_sz = sz < (ring->cap - ring->w) ? sz : (ring->cap - ring->w);
    memcpy(ring->buf + ring->w, src, cp_sz);
    ring->w = (ring->w + cp_sz) % ring->cap;
    ring->size += cp_sz;
    src += cp_sz;
    cp_sz = sz - cp_sz;
    if (cp_sz > 0) {
        memcpy(ring->buf, src, cp_sz);
        ring->w = cp_sz;
        ring->size += cp_sz;
    }
    return 0;
}

static int ring_mark_read(jl_app_uart_rx_ring_t *ring, const int sz)
{
    ring->size -= sz;
    ring->r = (ring->r + sz) % ring->cap;
    return 0;
}

static void uart_recv_entry(void *arg)
{
    jl_app_uart_ctx_t *ctx = arg;
    int res;
    uart_ioc_waitread_t waitr_arg;
    uint8_t recv_buf[JL_APP_UART_RECV_BUF_LEN];
    int ring_left;
    int p_sz;
    uint8_t *rd_ptr;
    void *header_pos;
    int pos_idx;
    jl_app_uart_rx_ring_t *ring = &ctx->ring;

    void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);

    waitr_arg.buf = (char *)recv_buf;
    waitr_arg.read_size = sizeof(recv_buf);
    waitr_arg.timeout = 5;

    while (1) {
        res = aos_ioctl(ctx->uart_fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg));
        rd_ptr = recv_buf;
        while (res > 0) {
            ring_left = ring_remaining(ring);
            p_sz = ring_left < res ? ring_left : res;
            ring_write(ring, rd_ptr, p_sz);
            rd_ptr += p_sz;
            res -= p_sz;
            if (ring_size(ring) == ring_capacity(ring)) {
                ring_get_copy(ring, ctx->ring_linear_buf);
                header_pos = memmem(ctx->ring_linear_buf, ctx->msg_len, ctx->frame_header, ctx->frame_header_length);
                if (header_pos) {
                    pos_idx = header_pos - (void *)ctx->ring_linear_buf;
                    if (pos_idx) {
                        ring_mark_read(ring, pos_idx);
                    } else {
                        if ((ctx->msg_check_cb && ctx->msg_check_cb(ctx->ring_linear_buf, ctx->msg_len, ctx->msg_check_cb_arg) == 0)
                                || !ctx->msg_check_cb) {
                            ctx->send_buf2->type = JL_APP_UART_MSG_CTL2APP;
                            ctx->send_buf2->len = ctx->msg_len;
                            memcpy(ctx->send_buf2->msg, ctx->ring_linear_buf, ctx->msg_len);
                            xQueueSend(ctx->msg_queue, ctx->send_buf2, 0);
                        }
                        ring_mark_read(ring, ring_capacity(ring));
                    }
                } else {
                    ring_mark_read(ring, ring_size(ring) - (ctx->frame_header_length - 1));
                }
            }
        }
    }
}

void jl_app_write_uart(jl_app_uart_ctx_t *ctx, const uint8_t *buf, uint16_t len)
{
    if (ctx) {
        if (ctx->uart_fd >= 0) {
            aos_write(ctx->uart_fd, buf, len);
        }
    }
}

static void uart_queue_proc_entry(void *arg)
{
    jl_app_uart_ctx_t *ctx = arg;
    
    while (1) {
        if (xQueueReceive(ctx->msg_queue, ctx->recv_buf, portMAX_DELAY) == pdPASS) {
            switch (ctx->recv_buf->type) {
            case JL_APP_UART_MSG_CTL2APP:
                if (ctx->recv_cb) {
                    ctx->recv_cb(ctx->recv_buf->msg, ctx->recv_buf->len, ctx->recv_cb_arg);
                } 
                break;
            case JL_APP_UART_MSG_APP2CTL:
                if (ctx->recv_buf->delay_ms) {
                    vTaskDelay(ctx->recv_buf->delay_ms);
                }
                jl_app_write_uart(ctx, ctx->recv_buf->msg, ctx->recv_buf->len);
                break;
            default:
                break;
            }
        }
    }
}

int jl_app_uart_start_txrx(jl_app_uart_ctx_t *ctx)
{
    if (!ctx) {
        return -1;
    }
    if (xTaskCreate(uart_recv_entry, "jl_app_uart_recv",
                JL_APP_UART_RECV_TASK_STACK_DEPTH, ctx, 16, &ctx->recv_task) != pdPASS) {
        return -1;
    }
    if (xTaskCreate(uart_queue_proc_entry, "jl_app_uart_queue_proc",
                JL_APP_UART_QUEUE_PROC_TASK_STACK_DEPTH, ctx, 17, &ctx->queue_proc_task) != pdPASS) {
        return -1;
    }
    return 0;
}
