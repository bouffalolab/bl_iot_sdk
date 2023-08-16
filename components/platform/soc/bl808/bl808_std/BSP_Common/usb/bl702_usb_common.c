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
#include "hal_usb.h"
#include "hal_dma.h"
#include "bl702_usb_common.h"
#include "bl702_usb.h"
/**
 * @brief
 *
 * @param dev
 * @param rb
 * @param ep
 * @return int
 */
int usb_dc_receive_to_ringbuffer(Ring_Buffer_Type *rb, uint8_t ep)
{
    uint8_t ep_idx;
    uint8_t recv_len;
    static bool overflow_flag = false;

    ep_idx = USB_EP_GET_IDX(ep);

    recv_len = USB_Get_EPx_RX_FIFO_CNT(ep_idx);

    /*if rx fifo count equal 0,it means last is send nack and ringbuffer is smaller than 64,
    * so,if ringbuffer is larger than 64,set ack to recv next data.
    */
    if (overflow_flag && (Ring_Buffer_Get_Empty_Length(rb) > 64) && (!recv_len)) {
        overflow_flag = false;
        USB_Set_EPx_Rdy(ep_idx);
        return 0;
    } else {
        uint32_t addr = USB_BASE + 0x11C + (ep_idx - 1) * 0x10;
        Ring_Buffer_Write_Callback(rb, recv_len, fifocopy_to_mem, (void *)addr);

        if (Ring_Buffer_Get_Empty_Length(rb) < 64) {
            overflow_flag = true;
            return -USB_DC_RB_SIZE_SMALL_ERR;
        }

        USB_Set_EPx_Rdy(ep_idx);
        return 0;
    }
}
/**
 * @brief
 *
 * @param dev
 * @param rb
 * @param ep
 * @return int
 */
int usb_dc_send_from_ringbuffer(Ring_Buffer_Type *rb, uint8_t ep)
{
    uint8_t ep_idx;
    static bool zlp_flag = false;

    ep_idx = USB_EP_GET_IDX(ep);

    uint32_t addr = USB_BASE + 0x118 + (ep_idx - 1) * 0x10;

    if (zlp_flag == false) {
        if ((USB_Get_EPx_TX_FIFO_CNT(ep_idx) == USB_FS_MAX_PACKET_SIZE) && Ring_Buffer_Get_Length(rb)) {
            uint32_t actual_len = Ring_Buffer_Read_Callback(rb, USB_FS_MAX_PACKET_SIZE, memcopy_to_fifo, (void *)addr);

            if (!Ring_Buffer_Get_Length(rb) && (!(actual_len % 64))) {
                zlp_flag = true;
            }

            USB_Set_EPx_Rdy(ep_idx);
        }
    } else {
        zlp_flag = false;
        USB_Set_EPx_Rdy(ep_idx);
    }
    return 0;
}

struct device *dma_ep[8];

void usb_iso_init(uint8_t ep)
{
    /* register & open dma device */
    char dma_name[16];
    uint8_t ep_idx;

    ep_idx = ep & 0x7f;
    snprintf(dma_name, 16, "dma_ch%d", ep_idx);
    dma_register(ep_idx, dma_name);
    dma_ep[ep_idx] = device_find(dma_name);

    if (ep & 0x80) {
        DMA_DEV(dma_ep[ep_idx])->direction = DMA_MEMORY_TO_PERIPH;
        DMA_DEV(dma_ep[ep_idx])->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(dma_ep[ep_idx])->src_req = DMA_REQUEST_NONE;
        DMA_DEV(dma_ep[ep_idx])->dst_req = DMA_REQUEST_USB_EP0 + ep_idx;
        DMA_DEV(dma_ep[ep_idx])->src_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
        DMA_DEV(dma_ep[ep_idx])->dst_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
        DMA_DEV(dma_ep[ep_idx])->src_burst_size = DMA_BURST_INCR16;
        DMA_DEV(dma_ep[ep_idx])->dst_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_ep[ep_idx])->src_width = DMA_TRANSFER_WIDTH_8BIT;
        DMA_DEV(dma_ep[ep_idx])->dst_width = DMA_TRANSFER_WIDTH_8BIT;
        device_open(dma_ep[ep_idx], 0);
        USB_Set_EPx_TX_DMA_Interface_Config(ep_idx, ENABLE);
    } else {
    }
}

void usbd_ep_iso_write_async(uint8_t ep, uint8_t *buffer, uint32_t len)
{
    uint8_t ep_idx;

    ep_idx = ep & 0x7f;
    uint32_t usb_ep_addr = USB_BASE + 0x308 + ep_idx * 0x10;

    dma_reload(dma_ep[ep_idx], (uint32_t)buffer, usb_ep_addr, len);
    dma_channel_start(dma_ep[ep_idx]);
}

bool usbd_ep_iso_is_complete(uint8_t ep)
{
    uint8_t ep_idx;

    ep_idx = ep & 0x7f;
    return (!dma_channel_check_busy(dma_ep[ep_idx]));
}