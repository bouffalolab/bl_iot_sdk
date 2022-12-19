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

#ifndef _XRAM_SPI_COMMON_H_
#define _XRAM_SPI_COMMON_H_

#define SPI_OPERATION_MAX_SIZE (2048)

typedef enum spi_op_err {
    SPI_OP_OK,
    SPI_OP_ERR
} SPI_OP_ERR_TYPE;

enum spi_operation {
    XRAM_SPI_INIT,
    XRAM_SPI_FINALIZE,
    XRAM_SPI_TRANS
};

struct xram_spi_op {
    uint32_t op;
    uint8_t port;               /**< spi port */
    uint8_t mode;           /**< spi communication mode */
    uint8_t dma_enable;     /**< enable dma tansmission or not */
    uint8_t polar_phase;    /**< spi polar and phase */
    uint32_t freq;          /**< communication frequency Hz */
    uint8_t pin_clk;        /**< spi clk pin */
    uint8_t pin_mosi;       /**< spi mosi pin */
    uint8_t pin_miso;       /**< spi miso pin */
    uint8_t pin_cs;       /**< spi cs pin */
    uint32_t timeout;
    uint32_t len;
    uint8_t data[];
};

#endif
