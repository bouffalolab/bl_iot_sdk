/*
 * Copyright (c) 2020 Bouffalolab.
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
#include <stdlib.h>
#include <stdio.h>
#include <cli.h>
#include <FreeRTOS.h>
#include <task.h>
#include <vfs.h>
#include <device/vfs_spi.h>
#include <blog.h>
#include <bl_dma.h>


/*
 *  spi clock select 4M, 
 *  two kinds chip WS2812B and UCS1903 ,default chip is WS2812B ,5 spi bits mean WS2812B 0 or 1, 10 spi bits mean UCS1903 0 or 1 
 *
 * */


#define CONF_CHIP_WS2812B

#ifdef CONF_CHIP_WS2812B

#define RESET_BYTES              26     /*reset time > 50us,26 spi bytes 0 mean WS2812B reset 0,here reset time is 52us*/

#else   /*CHIP_UCS1903*/

#define RESET_BYTES             13      /*reset time > 24us,13 spi bytes 0 mean UCS1903 reset 0,here reset time is 26us*/
#endif 

#define ONE_FRAME_BYTESIZE      3       /* chip 24bits */
#define TRANSFER_SIZE           4096

int spi_output_wave(uint8_t *pbuf0_tx, uint8_t *data, uint32_t nbytes)
{
    int i, status, n = 0;
    uint32_t nbits, code;
    /*data is 24bits Integer multiple*/
    if (nbytes % ONE_FRAME_BYTESIZE != 0) {
        blog_error("param error\r\n");
        return -1;
    }

    nbits = nbytes * 8;

#ifdef CONF_CHIP_WS2812B
    int a = 0;
    for (i = 0; i < nbits; i++) {
        /* 5 spi bits mean WS2812B 0 or 1,we let each group 8 WS2812B bits,so one group just right need 5 spi bytes*/
        status = i % 8;
        /*move point*/
        if (i != 0 && i % 8 == 0) {
            data++;
            a++;
            n = 3 * a;
        }
        code = ((*data >> (7 - (i % 8))) & 0x01);
        switch (status) {
            case 0:
            {
                /*0x00 or 0x01 means chip WS2812B bit*/
                if (code == 0x00) {
                    pbuf0_tx[i-n] = 0xC0;
                } else {
                    pbuf0_tx[i-n] = 0xE0;
                }
            }
            break;
            case 1:
            {
                if (code == 0x00) {
                    pbuf0_tx[i-n-1] = (pbuf0_tx[i-n-1] | 0x06);
                    pbuf0_tx[i-n] = 0x00;
                } else {
                    pbuf0_tx[i-n-1] = (pbuf0_tx[i-n-1] | 0x07);
                    pbuf0_tx[i-n] = 0x00;
                }
            }
            break;
            case 2:
            {   
                if (code == 0x00) {
                    pbuf0_tx[i-n-1] = (pbuf0_tx[i-n-1] | 0x30);
                } else {
                    pbuf0_tx[i-n-1] = (pbuf0_tx[i-n-1] | 0x38);
                }    
            }
            break;
            case 3:
            {
                if (code == 0x00) {
                    pbuf0_tx[i-n-2] = (pbuf0_tx[i-n-2] | 0x01);
                    pbuf0_tx[i-n-1] = 0x80;
                } else {
                    pbuf0_tx[i-n-2] = (pbuf0_tx[i-n-2] | 0x01);
                    pbuf0_tx[i-n-1] = 0xC0;
                }
            }
            break;
            case 4:
            {
                if (code == 0x00) {
                    
                    pbuf0_tx[i-n-2] = (pbuf0_tx[i-n-2] | 0x0C);
                    pbuf0_tx[i-n-1] = 0x00;
                } else {
                    pbuf0_tx[i-n-2] = (pbuf0_tx[i-n-2] | 0x0E);
                    pbuf0_tx[i-n-1] = 0x00;
                }
            }
            break;
            case 5:
            {
                if (code == 0x00) {
                    pbuf0_tx[i-n-2] = (pbuf0_tx[i-n-2] | 0x60);
                } else {
                    pbuf0_tx[i-n-2] = (pbuf0_tx[i-n-2] | 0x70);
                }
            }     
            break;
            case 6:
            {
                if (code == 0x00) {
                    pbuf0_tx[i-n-3] = (pbuf0_tx[i-n-3] | 0x03);
                    pbuf0_tx[i-n-2] = 0x00;
                } else {
                    pbuf0_tx[i-n-3] = (pbuf0_tx[i-n-3] | 0x03);
                    pbuf0_tx[i-n-2] = 0x80;
                }
            }     
            break;
            case 7:
            {
                if (code == 0x00) {
                    pbuf0_tx[i-n-3] = (pbuf0_tx[i-n-3] | 0x18);
                } else {
                    pbuf0_tx[i-n-3] = (pbuf0_tx[i-n-3] | 0x1C);
                }
            }           
            break;
            default:
            {
                blog_error("ERROR\r\n");
                return -1;
            }
        }
    }
    /*reset*/
    a++;
    n = 3 * a;
    for (i = 0; i < RESET_BYTES; i++) {
        pbuf0_tx[nbits-n+i] = 0x00;
    }   
#else
    for (i = 0; i < nbits; i++) {
        /* 10 spi bits mean UCS1903 0 or 1,we let each group 4 UCS1903 bits,so one group just right need 5 spi bytes*/
        status = i % 4;
        /*move point*/
        if (i != 0 && i % 8 == 0) {
            data++;
        }
        if (i != 0 && i % 4 == 0) {
            n++;
        }
        code = ((*data >> (7 - (i % 8))) & 0x01);
        switch (status) {
            case 0:
            {
                if (code == 0x00) {
                    pbuf0_tx[i+n] = 0xC0;
                    pbuf0_tx[i+n+1] = 0x00;
                } else {
                    pbuf0_tx[i+n] = 0xFF;
                    pbuf0_tx[i+n+1] = 0x00;
                }
            }
            break;
            case 1:
            {
                if (code == 0x00) {
                    pbuf0_tx[i+n] = (pbuf0_tx[i+n] | 0x30);
                    pbuf0_tx[i+n+1] = 0x00;
                } else {
                    
                    pbuf0_tx[i+n] = (pbuf0_tx[i+n] | 0x3F);
                    pbuf0_tx[i+n+1] = 0xC0;
                }
            }
            break;
            case 2:
            {   
                if (code == 0x00) {
                    pbuf0_tx[i+n] = (pbuf0_tx[i+n] | 0x0C);
                    pbuf0_tx[i+n+1] = 0x00;
                } else {
                    pbuf0_tx[i+n] = (pbuf0_tx[i+n] | 0x0F);
                    pbuf0_tx[i+n+1] = 0xF0;
                }    
            }
            break;
            case 3:
            {
                if (code == 0x00) {
                    pbuf0_tx[i+n] = (pbuf0_tx[i+n] | 0x03);
                    pbuf0_tx[i+n+1] = 0x00;
                } else {
                    pbuf0_tx[i+n] = (pbuf0_tx[i+n] | 0x03);
                    pbuf0_tx[i+n+1] = 0xFC;
                }
            }
            break;
            default:
            {
                blog_error("ERROR\r\n");
                return -1;
            }
        }
    }
    /*reset*/
    n++;
    for (i = 0; i < RESET_BYTES; i++) {
        pbuf0_tx[nbits+n+i] = 0x00;
    }   
#endif
    return 0;
}

void demo_spi_wave(char *buf, int len, int argc, char **argv)
{
    int a = 0;
    int spi_dev = -1;
    int ret;
    
    uint8_t data[12] = {0x02, 0x10, 0x05, 0x12, 0x32, 0xFB, 0x32, 0x45, 0x67, 0x89, 0xAB, 0xDF};
    uint8_t *pbuf0_tx = NULL;
    struct spi_ioc_transfer *pxfer = NULL;
   
    spi_dev = aos_open("/dev/spi0", 0);
    blog_info("start open spi_dev = %d.\r\n", spi_dev);
    if (spi_dev < 0) {
        blog_error("start open spi_dev = %d.\r\n", spi_dev);
        return;
    }

    pbuf0_tx = bl_dma_mem_malloc(TRANSFER_SIZE);
    printf("pbuf0_tx = %p\r\n", pbuf0_tx);
    pxfer = (struct spi_ioc_transfer*)bl_dma_mem_malloc(2 * (sizeof(struct spi_ioc_transfer)));

    if ((!pbuf0_tx) || (!pxfer)) {
        blog_error("mem err.\r\n");
        return;
    }

    memset(pbuf0_tx, 0xFF, TRANSFER_SIZE);

    ret = spi_output_wave(pbuf0_tx, data, sizeof(data)/sizeof(data[0]));
    if (ret < 0) {
        blog_error("error\r\n");
        return;
    }

    pxfer[0].tx_buf = (uint32_t)pbuf0_tx;
    pxfer[0].len = TRANSFER_SIZE;
    a = aos_ioctl(spi_dev, IOCTL_SPI_IOC_MESSAGE(1), (unsigned long)&pxfer[0]);
    if (a != 0) {
        blog_error("ERROR: SPI WRITE FAILURE\n");
    }

    bl_dma_mem_free(pbuf0_tx);
    bl_dma_mem_free(pxfer);
    aos_close(spi_dev);
}

void spi_loop_wave(char *buf, int len, int argc, char **argv)
{   
    int i = 0;
    for (i = 0; i < 100; i++) {
        demo_spi_wave(NULL, 1, 1, NULL);
        vTaskDelay(3000);
    }
    
    return;
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"test_spi_wave", "spi test master", demo_spi_wave},
    {"test_loop_wave", "loop test wave", spi_loop_wave},
};                                                                                   

int spi_wave_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
