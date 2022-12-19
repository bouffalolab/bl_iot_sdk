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
#include <cli.h>
#include <blog.h>
#include <hosal_dma.h>
#include <hosal_spi.h>
#include <bl808_gpio.h>
#include "bl_spi_cli.h"

#define SPI_TEST_BYTES  8
uint8_t send_data[SPI_TEST_BYTES];
uint8_t recv_data[SPI_TEST_BYTES];

#define SPI_PIN_CS   GLB_GPIO_PIN_8
#define SPI_PIN_CLK  GLB_GPIO_PIN_7
#define SPI_PIN_MOSI GLB_GPIO_PIN_1
#define SPI_PIN_MISO GLB_GPIO_PIN_2

/* spi callback */
void spi_master_cb(void *arg)
{
    for (int i = 0; i < SPI_TEST_BYTES; i++) {
        blog_info("master send %x, recv %x.\r\n",send_data[i], recv_data[i]);
    }
    printf("master complete\r\n");
}

void spi_slave_cb(void *arg)
{
    for (int i = 0; i < SPI_TEST_BYTES; i++) {
        blog_info("slave send %x, recv %x.\r\n",send_data[i], recv_data[i]);
    }
    blog_info("slave complete\r\n");
}

void spi_dma_master_cb(void *arg)
{
    for (int i = 0; i < SPI_TEST_BYTES; i++) {
        blog_info("master send %x, recv %x.\r\n",send_data[i], recv_data[i]);
    }
    printf("spi dma master complete\r\n");
}

void spi_dma_slave_cb(void *arg)
{
    for (int i = 0; i < SPI_TEST_BYTES; i++) {
        blog_info("slave send %x, recv %x.\r\n",send_data[i], recv_data[i]);
    }
    blog_info("spi dma slave complete\r\n");
}

void demo_hosal_spi_master(void)
{
    hosal_spi_dev_t spi;
    /* spi port set */
    spi.port = 1;
    /* spi master mode */
    spi.config.mode  = HOSAL_SPI_MODE_MASTER;

    /* 1: enable dma, 0: disable dma */

    spi.config.dma_enable = 0;
     /* 0: phase 0, polarity low
      * 1: phase 1, polarity low
      * 2: phase 0, polarity high
      * 3: phase 0, polarity high
      */
    spi.config.polar_phase= 0;
    /* 0 ~ 40M */
    spi.config.freq= 100000;
    spi.config.pin_clk = SPI_PIN_CLK;
    // spi.config.pin_cs = SPI_PIN_CS;
    spi.config.pin_mosi= SPI_PIN_MOSI;
    spi.config.pin_miso= SPI_PIN_MISO;
    /* init spi device */
    hosal_spi_init(&spi);

    /* register trans complete callback */
    hosal_spi_irq_callback_set(&spi, spi_master_cb, (void*)&spi);
    memset(recv_data, 0, SPI_TEST_BYTES);

    /* prepara send buf */
    for (int i = 0; i < sizeof(send_data)/sizeof(send_data[0]); i++) {
        send_data[i] = i + 2;
    }

    blog_info("spi send and recieve data by 8-bits fram size\r\n");
    /*send and recv data, timeout is 10s */
    hosal_spi_send(&spi, (uint8_t *)send_data, SPI_TEST_BYTES, 10000);

    for (int i = 0; i < sizeof(send_data)/sizeof(recv_data[0]); i++) {
        printf("recieve: %x \r\n",recv_data[i]);
    }

    hosal_spi_finalize(&spi);
}

void demo_hosal_spi_slave(void)
{
    hosal_spi_dev_t spi;
    /* spi port set */
    spi.port = 1;
    /* spi master mode */
    spi.config.mode  = HOSAL_SPI_MODE_SLAVE;

    /* 1: enable dma, 0: disable dma */

    spi.config.dma_enable = 0;
     /* 0: phase 0, polarity low
      * 1: phase 1, polarity low
      * 2: phase 0, polarity high
      * 3: phase 0, polarity high
      */
    spi.config.polar_phase= 0;
    spi.config.freq= 80000000;
    spi.config.pin_clk = SPI_PIN_CLK;
    // spi.config.pin_cs = SPI_PIN_CS;
    spi.config.pin_mosi= SPI_PIN_MOSI;
    spi.config.pin_miso= SPI_PIN_MISO;
    /* init spi device */
    hosal_spi_init(&spi);

    /* register trans complete callback */
    hosal_spi_irq_callback_set(&spi, spi_slave_cb, (void*)&spi);
    memset(recv_data, 0, SPI_TEST_BYTES);

    /* prepara send buf */
    for (int i = 0; i < sizeof(send_data)/sizeof(send_data[0]); i++) {
        send_data[i] = i + 8;
    }
    blog_info("spi send and recieve data by 8-bits fram size\r\n");
    /*send and recv data, timeout is 10s */
    hosal_spi_send_recv(&spi, (uint8_t *)send_data, (uint8_t *)recv_data, SPI_TEST_BYTES, 10000);

    for (int i = 0; i < sizeof(send_data)/sizeof(recv_data[0]); i++) {
        blog_info("recieve: %x \r\n",recv_data[i]);
    }
    hosal_spi_finalize(&spi);
}

void demo_hosal_spi_dma_master(void)
{
    hosal_spi_dev_t spi;
    /* spi port set */
    spi.port = 1;
    /* spi master mode */
    spi.config.mode  = HOSAL_SPI_MODE_MASTER;

    /* 1: enable dma, 0: disable dma */

    spi.config.dma_enable = 1;
     /* 0: phase 0, polarity low
      * 1: phase 1, polarity low
      * 2: phase 0, polarity high
      * 3: phase 0, polarity high
      */
    spi.config.polar_phase= 0;
    spi.config.freq= 1000000;
    spi.config.pin_clk = SPI_PIN_CLK;
    // spi.config.pin_cs = SPI_PIN_CS;
    spi.config.pin_mosi= SPI_PIN_MOSI;
    spi.config.pin_miso= SPI_PIN_MISO;
    /* init spi device */
    hosal_spi_init(&spi);

    /* register trans complete callback */
    hosal_spi_irq_callback_set(&spi, spi_dma_master_cb, (void*)&spi);
    memset(recv_data, 0, SPI_TEST_BYTES);

    /* prepara send buf */
    for (int i = 0; i < SPI_TEST_BYTES; i++) {
        send_data[i] = i + 2;
    }

    /* software set pin4 as cs pin , and set cs low to slect slave*/
    // hosal_spi_set_cs(4, 0);

    blog_info("spi send and recieve data by 8-bits fram size\r\n");
    /*send and recv data, timeout is 10s */
    //hosal_spi_send_recv(&spi, (uint8_t *)send_data, (uint8_t *)recv_data, SPI_TEST_BYTES, 10000);
    hosal_spi_send(&spi, (uint8_t *)send_data, SPI_TEST_BYTES, 2000);
    /* set cs high, release slave */
    // hosal_spi_set_cs(4, 1);

    hosal_spi_finalize(&spi);
}

void demo_hosal_spi_dma_slave(void)
{
    hosal_spi_dev_t spi;
    /* spi port set */
    spi.port = 1;
    /* spi master mode */
    spi.config.mode  = HOSAL_SPI_MODE_SLAVE;

    /* 1: enable dma, 0: disable dma */
    spi.config.dma_enable = 1;
     /* 0: phase 0, polarity low
      * 1: phase 1, polarity low
      * 2: phase 0, polarity high
      * 3: phase 0, polarity high
      */
    spi.config.polar_phase= 0;
    spi.config.freq= 80000000;
    spi.config.pin_clk = SPI_PIN_CLK;
    // spi.config.pin_cs = SPI_PIN_CS;
    spi.config.pin_mosi= SPI_PIN_MOSI;
    spi.config.pin_miso= SPI_PIN_MISO;
    /* init spi device */
    hosal_spi_init(&spi);

    /* register dma irq callback */
    hosal_spi_irq_callback_set(&spi, spi_dma_slave_cb, (void*)&spi);
    memset(recv_data, 0, SPI_TEST_BYTES);

    /* prepara send buf */
    for (int i = 0; i < sizeof(send_data)/sizeof(send_data[0]); i++) {
        send_data[i] = i + 8;
    }

    blog_info("spi send and recieve data by 8-bits fram size\r\n");
    /*send and recv data, timeout is 10s */
    hosal_spi_send_recv(&spi, (uint8_t *)send_data, (uint8_t *)recv_data, SPI_TEST_BYTES, 10000);

    hosal_spi_finalize(&spi);
}

static void cmd_hosal_spi_master(char *buf, int len, int argc, char **argv)
{
    demo_hosal_spi_master();
}

static void cmd_hosal_spi_slave(char *buf, int len, int argc, char **argv)
{
    demo_hosal_spi_slave();
}

static void cmd_hosal_spi_dma_master(char *buf, int len, int argc, char **argv)
{
    demo_hosal_spi_dma_master();
}

static void cmd_hosal_spi_dma_slave(char *buf, int len, int argc, char **argv)
{
    demo_hosal_spi_dma_slave();
}

static void cmd_hosal_dma_init(char *buf, int len, int argc, char **argv)
{
    hosal_dma_init();
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"spi_master", "demo_hosal_spi_master", cmd_hosal_spi_master},
    {"spi_slave", "demo_hosal_spi_slave", cmd_hosal_spi_slave},
    {"spi_dma_master", "demo_hosal_spi_dma_master", cmd_hosal_spi_dma_master},
    {"spi_dma_slave", "demo_hosal_spi_dma_slave", cmd_hosal_spi_dma_slave},
    {"dma_init", "dma refernce init", cmd_hosal_dma_init},
};

int bl_spi_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
