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
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <bl_flash.h>
#include <xram_peripheral.h>
#include <xram_peri_flash.h>
#include <xram_peri_common.h>
#include <bl808_common.h>
#include <xram.h>

static uint8_t s_rx_buffer[XRAM_FLASH_OPERATION + FLASH_OPERATION_MAX_SIZE];
static uint8_t s_tx_buffer[XRAM_MSG_HDR + XRAM_FLASH_OPERATION + FLASH_OPERATION_MAX_SIZE];

static int xram_flash_create(xram_flash_op_t opt)
{
    struct xram_hdr *hdr = (struct xram_hdr *)s_tx_buffer;
    xram_flash_op_t flash_op = (xram_flash_op_t)(s_tx_buffer + XRAM_MSG_HDR);
    uint32_t bytes;

    assert(opt != NULL);
    assert(opt->flash_id < XRAM_FLASH_ID_MAX && opt->flash_id >= XRAM_FLASH_ID_0);

    if (opt->offset == 0 && opt->len == 0 && opt->size == 0) {
        /* FIXME: */
        flash_op->size = XRAM_ADDR_LIMIT;
        flash_op->flash_id = opt->flash_id;
        hdr->err = FLASH_OP_OK;
    } else {
        hdr->err = FLASH_OP_ERR;
    }

    hdr->type = XRAM_PERI_TYPE_FLASH;
    hdr->len = XRAM_FLASH_OPERATION;

    flash_op->offset = 0;
    flash_op->len = 0;
    flash_op->op = XRAM_FLASH_CREATE;

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR + hdr->len);
    if (bytes) {
        return FLASH_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return FLASH_OP_ERR;
    }

    return FLASH_OP_ERR;
}

static int xram_flash_destroy(xram_flash_op_t opt)
{
    return FLASH_OP_OK;
}

static int xram_flash_read(xram_flash_op_t opt)
{
    assert(opt != NULL);
    struct xram_hdr *hdr = (struct xram_hdr *)s_tx_buffer;
    BL_Err_Type stat;
    uint32_t bytes;

    /* FIXME: flash_id */
    /* FIXME: offset ,len valid*/

    stat = bl_flash_read(opt->offset, s_tx_buffer + XRAM_MSG_HDR, opt->len);
    if (stat == SUCCESS) {
        hdr->type = XRAM_PERI_TYPE_FLASH;
        hdr->len = opt->len;
        hdr->err = FLASH_OP_OK;

        bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR + hdr->len);
        if (bytes) {
            return FLASH_OP_OK;
        } else {
            printf("xram ring write err.\r\n");
            return FLASH_OP_ERR;
        }

    } else {
        printf("flash read err, errno %d.\r\n", stat);
        hdr->type = XRAM_PERI_TYPE_FLASH;
        hdr->len = 0;
        hdr->err = FLASH_OP_ERR;

        bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR);
        if (bytes) {
            return FLASH_OP_OK;
        } else {
            printf("xram ring write err.\r\n");
            return FLASH_OP_ERR;
        }
    }

    return FLASH_OP_ERR;
}

static int xram_flash_write(xram_flash_op_t opt)
{
    assert(opt != NULL);
    struct xram_hdr *hdr = (struct xram_hdr *)s_tx_buffer;
    BL_Err_Type stat;
    uint32_t bytes;

    /* FIXME: flash_id */
    /* FIXME: offset ,len valid*/

    stat = bl_flash_write(opt->offset, opt->data, opt->len);
    if (stat != SUCCESS) {
        printf("flash write err, errno %d.\r\n", stat);
    }

    hdr->type = XRAM_PERI_TYPE_FLASH;
    hdr->len = 0;
    hdr->err = stat;

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR);
    if (bytes) {
        return FLASH_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return FLASH_OP_ERR;
    }

    return FLASH_OP_ERR;
}

static int xram_flash_erase(xram_flash_op_t opt)
{
    assert(opt != NULL);
    struct xram_hdr *hdr = (struct xram_hdr *)s_tx_buffer;
    BL_Err_Type stat;
    uint32_t bytes;

    /* FIXME: flash_id */
    /* FIXME: offset ,len valid*/

    stat = bl_flash_erase(opt->offset, opt->len);
    if (stat != SUCCESS) {
        printf("flash erase err, errno %d.\r\n", stat);
    }

    hdr->type = XRAM_PERI_TYPE_FLASH;
    hdr->len = 0;
    hdr->err = stat;

    bytes = XRAMRingWrite(XRAM_PERI_OP_QUEUE, s_tx_buffer, XRAM_MSG_HDR);
    if (bytes) {
        return FLASH_OP_OK;
    } else {
        printf("xram ring write err.\r\n");
        return FLASH_OP_ERR;
    }

    return FLASH_OP_ERR;
}

void xram_flash_operation_handle(uint32_t len)
{
    xram_flash_op_t opt = NULL;
    FLASH_OP_ERR_TYPE stat;
    uint32_t bytes;

    while (1) {
        bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, s_rx_buffer, len);
        if (bytes) {
            opt = (xram_flash_op_t)(s_rx_buffer);

            // printf("op [%d] : offset %x %d len.\r\n",(int)opt->op,(int)opt->offset,(int)opt->len);
            switch (opt->op) {
                case XRAM_FLASH_CREATE: {
                    stat = xram_flash_create(opt);
                    break;
                }
                case XRAM_FLASH_DESTROY: {
                    stat = xram_flash_destroy(opt);
                    break;
                }
                case XRAM_FLASH_READ: {
                    stat = xram_flash_read(opt);
                    break;
                }
                case XRAM_FLASH_WRITE: {
                    stat = xram_flash_write(opt);
                    break;
                }
                case XRAM_FLASH_ERASE: {
                    stat = xram_flash_erase(opt);
                    break;
                }
                default: {
                    printf("xram flash operate type err.\r\n");
                    stat = FLASH_OP_ERR;
                    break;
                }
            }

            if (stat == FLASH_OP_ERR) {
                printf("flash operation err.\r\n");
            }
            return;
        }
    }
}

