/*
 * Copyright (c) 2016-2022 Bouffalolab.
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

#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <bl_flash.h>
#include <xram_peripheral.h>
#include <xram_peri_spi.h>
#include <xram_peri_common.h>
#include <xram_spi_common.h>
#include <bl808_common.h>
#include <xram.h>
#include "hosal_spi.h"

static int xram_spi_int(struct xram_spi_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = SPI_OP_OK;

    hosal_spi_dev_t spi;
    spi.port = op->port;
    spi.config.mode = op->mode;
    spi.config.dma_enable = op->dma_enable;
    spi.config.polar_phase = op->polar_phase;
    spi.config.freq = op->freq;
    spi.config.pin_clk = op->pin_clk;
    spi.config.pin_mosi = op->pin_mosi;
    spi.config.pin_miso = op->pin_miso;
    if (hosal_spi_init(&spi) != 0)
        operation_ret = SPI_OP_ERR;

    hdr.type = XRAM_PERI_TYPE_SPI;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return SPI_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return SPI_OP_ERR;
    }
}

static int xram_spi_finalize(struct xram_spi_op *op)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = SPI_OP_OK;

    hosal_spi_dev_t spi;
    spi.port = op->port;
    spi.config.mode = op->mode;
    spi.config.dma_enable = op->dma_enable;
    spi.config.polar_phase = op->polar_phase;
    spi.config.freq = op->freq;
    spi.config.pin_clk = op->pin_clk;
    spi.config.pin_mosi = op->pin_mosi;
    spi.config.pin_miso = op->pin_miso;
    if (hosal_spi_finalize(&spi) != 0)
        operation_ret = SPI_OP_ERR;
    else
        hosal_spi_set_cs(op->pin_cs, 1);

    hdr.type = XRAM_PERI_TYPE_SPI;
    hdr.err = operation_ret;
    hdr.len = 0;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    if (bytes == sizeof(struct xram_hdr)) {
        return SPI_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return SPI_OP_ERR;
    }
}

static int xram_spi_trans(struct xram_spi_op *op, void *data, uint32_t size, uint32_t timeout)
{
    struct xram_hdr hdr;
    uint32_t bytes;
    uint8_t operation_ret = SPI_OP_OK;

    hosal_spi_dev_t spi;
    spi.port = op->port;
    spi.config.mode = op->mode;
    spi.config.dma_enable = op->dma_enable;
    spi.config.polar_phase = op->polar_phase;
    spi.config.freq = op->freq;
    spi.config.pin_clk = op->pin_clk;
    spi.config.pin_mosi = op->pin_mosi;
    spi.config.pin_miso = op->pin_miso;
    hosal_spi_set_cs(op->pin_cs, 0);
    if (hosal_spi_send_recv(&spi, data, data, size, timeout) != 0)
        operation_ret = SPI_OP_ERR;
    hosal_spi_set_cs(op->pin_cs, 1);

    hdr.type = XRAM_PERI_TYPE_SPI;
    hdr.err = operation_ret;
    hdr.len = sizeof(struct xram_spi_op)+size;
    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, &hdr, sizeof(struct xram_hdr));
    bytes += XRAMRingWrite(XRAM_PERI_OP_QUEUE, op, sizeof(struct xram_spi_op)+size);
    if (bytes == sizeof(struct xram_hdr)+sizeof(struct xram_spi_op)+size) {
        return SPI_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return SPI_OP_ERR;
    }
}

void xram_spi_operation_handle(uint32_t len)
{
    struct xram_spi_op *spi_op;
    uint32_t bytes;
    uint8_t *buffer = (uint8_t *)pvPortMalloc(len);

    assert(buffer);

    bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, buffer, len);
    if (bytes == len) {
        spi_op = ( struct xram_spi_op *)buffer;

        switch (spi_op->op){
            case XRAM_SPI_INIT: {
                xram_spi_int(spi_op);
                break;
               }
            case XRAM_SPI_FINALIZE: {
                xram_spi_finalize(spi_op);
                break;
            }
            case XRAM_SPI_TRANS: {
                xram_spi_trans(spi_op, spi_op->data, spi_op->len, spi_op->timeout);
                break;
            }
            default: {
                printf("xram spi operate type err.\r\n");
                break;
            }
        }
    }
    vPortFree(buffer);
}

