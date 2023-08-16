/*
 * Copyright (c) 2016-2023 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "bflb_platform.h"
#include "hal_dma.h"
#include "hal_uart.h"
#include "ring_buffer.h"
#include "uart_common.h"
#include "usbd_core.h"

#define USB_OUT_RINGBUFFER_SIZE (16 * 1024)
#define UART_RX_RINGBUFFER_SIZE (16 * 1024)

USB_NOCACHE_RAM_SECTION uint8_t usb_rx_mem[UART0_ENABLE + UART1_ENABLE][USB_OUT_RINGBUFFER_SIZE];
USB_NOCACHE_RAM_SECTION uint8_t uart_rx_mem[UART0_ENABLE + UART1_ENABLE][UART_RX_RINGBUFFER_SIZE];

struct device *uart0;
struct device *uart1;

struct device *dma_ch0;
struct device *dma_ch1;

Ring_Buffer_Type usb_rx_rb[2];
Ring_Buffer_Type uart_rx_rb[2];

volatile uint32_t uart_dma_send_complete_len[2] = { 0, 0 };

void uart0_irq_callback(struct device *dev, void *args, uint32_t size, uint32_t state)
{
    Ring_Buffer_Write(&uart_rx_rb[0], (uint8_t *)args, size);
}

void uart1_irq_callback(struct device *dev, void *args, uint32_t size, uint32_t state)
{
    Ring_Buffer_Write(&uart_rx_rb[1], (uint8_t *)args, size);
}

void dma0_irq_callback(struct device *dev, void *args, uint32_t size, uint32_t state)
{
    usb_rx_rb[0].readIndex += uart_dma_send_complete_len[0];
    if (usb_rx_rb[0].readIndex == usb_rx_rb[0].size) {
        usb_rx_rb[0].readIndex = 0;
        usb_rx_rb[0].readMirror = ~usb_rx_rb[0].readMirror;
    }
}

void dma1_irq_callback(struct device *dev, void *args, uint32_t size, uint32_t state)
{
    usb_rx_rb[1].readIndex += uart_dma_send_complete_len[1];

    if (usb_rx_rb[1].readIndex == usb_rx_rb[1].size) {
        usb_rx_rb[1].readIndex = 0;
        usb_rx_rb[1].readMirror = ~usb_rx_rb[1].readMirror;
    }
}

void uartx_init(void)
{
#if UART0_ENABLE
    Ring_Buffer_Init(&usb_rx_rb[0], usb_rx_mem[0], USB_OUT_RINGBUFFER_SIZE, NULL, NULL);
    Ring_Buffer_Init(&uart_rx_rb[0], uart_rx_mem[0], UART_RX_RINGBUFFER_SIZE, NULL, NULL);
#endif
#if UART1_ENABLE
    Ring_Buffer_Init(&usb_rx_rb[1], usb_rx_mem[UART0_ENABLE], USB_OUT_RINGBUFFER_SIZE, NULL, NULL);
    Ring_Buffer_Init(&uart_rx_rb[1], uart_rx_mem[UART0_ENABLE], UART_RX_RINGBUFFER_SIZE, NULL, NULL);
#endif

#if UART0_ENABLE
    uart_register(UART0_INDEX, "uart0");
    uart0 = device_find("uart0");

    if (uart0) {
        UART_DEV(uart0)->fifo_threshold = UART_RX_FIFO_SIZE;
        device_open(uart0, DEVICE_OFLAG_DMA_TX | DEVICE_OFLAG_INT_RX);
        device_set_callback(uart0, uart0_irq_callback);
        device_control(uart0, DEVICE_CTRL_SET_INT, (void *)(UART_RX_FIFO_IT | UART_RTO_IT));
    }
    dma_register(DMA0_CH0_INDEX, "ch0");
    dma_ch0 = device_find("ch0");
    if (dma_ch0) {
        DMA_DEV(dma_ch0)->direction = DMA_MEMORY_TO_PERIPH;
        DMA_DEV(dma_ch0)->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(dma_ch0)->src_req = DMA_REQUEST_NONE;
        DMA_DEV(dma_ch0)->dst_req = DMA_REQUEST_UART0_TX;
        DMA_DEV(dma_ch0)->src_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
        DMA_DEV(dma_ch0)->dst_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
        DMA_DEV(dma_ch0)->src_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_ch0)->dst_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_ch0)->src_width = DMA_TRANSFER_WIDTH_8BIT;
        DMA_DEV(dma_ch0)->dst_width = DMA_TRANSFER_WIDTH_8BIT;
        device_open(dma_ch0, 0);
        device_set_callback(dma_ch0, dma0_irq_callback);
        device_control(dma_ch0, DEVICE_CTRL_SET_INT, NULL);
    }
    device_control(uart0, DEVICE_CTRL_ATTACH_TX_DMA, dma_ch0);
#endif
#if UART1_ENABLE
    uart_register(UART1_INDEX, "uart1");
    uart1 = device_find("uart1");

    if (uart1) {
        UART_DEV(uart1)->fifo_threshold = UART_RX_FIFO_SIZE;
        device_open(uart1, DEVICE_OFLAG_DMA_TX | DEVICE_OFLAG_INT_RX);
        device_set_callback(uart1, uart1_irq_callback);
        device_control(uart1, DEVICE_CTRL_SET_INT, (void *)(UART_RX_FIFO_IT | UART_RTO_IT));
    }

    dma_register(DMA0_CH1_INDEX, "ch1");
    dma_ch1 = device_find("ch1");
    if (dma_ch1) {
        DMA_DEV(dma_ch1)->direction = DMA_MEMORY_TO_PERIPH;
        DMA_DEV(dma_ch1)->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(dma_ch1)->src_req = DMA_REQUEST_NONE;
        DMA_DEV(dma_ch1)->dst_req = DMA_REQUEST_UART1_TX;
        DMA_DEV(dma_ch1)->src_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
        DMA_DEV(dma_ch1)->dst_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
        DMA_DEV(dma_ch1)->src_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_ch1)->dst_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_ch1)->src_width = DMA_TRANSFER_WIDTH_8BIT;
        DMA_DEV(dma_ch1)->dst_width = DMA_TRANSFER_WIDTH_8BIT;
        device_open(dma_ch1, 0);
        device_set_callback(dma_ch1, dma1_irq_callback);
        device_control(dma_ch1, DEVICE_CTRL_SET_INT, NULL);
    }
    device_control(uart1, DEVICE_CTRL_ATTACH_TX_DMA, dma_ch1);
#endif
}

uint32_t get_rb_read_remain_size(Ring_Buffer_Type *rbType)
{
    return rbType->size - rbType->readIndex;
}

void uartx_send_from_ringbuffer(void)
{
    uint32_t avai_len;
    uint32_t size;
#if UART0_ENABLE
    if (!dma_channel_check_busy(dma_ch0)) {
        avai_len = Ring_Buffer_Get_Length(&usb_rx_rb[0]);
        if (avai_len) {
            /* Get size of space remained in current mirror */
            size = get_rb_read_remain_size(&usb_rx_rb[0]);
            size = MIN(size, avai_len);
            uart_dma_send_complete_len[0] = size;
            device_write(uart0, 0, &usb_rx_rb[0].pointer[usb_rx_rb[0].readIndex], size);
        }
    }
#endif
#if UART1_ENABLE
    if (!dma_channel_check_busy(dma_ch1)) {
        avai_len = Ring_Buffer_Get_Length(&usb_rx_rb[1]);
        if (avai_len) {
            /* Get size of space remained in current mirror */
            size = get_rb_read_remain_size(&usb_rx_rb[1]);
            size = MIN(size, avai_len);
            uart_dma_send_complete_len[1] = size;
            device_write(uart1, 0, &usb_rx_rb[1].pointer[usb_rx_rb[1].readIndex], size);
        }
    }
#endif
}
