#include <stdlib.h>
#include <stdio.h>
#include <cli.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>

#include <vfs_err.h>
#include <vfs_register.h>
#include <vfs.h>
#include <hal/soc/uart.h>
#include <device/vfs_uart.h>
#include <device/vfs_spi.h>

#include <blog.h>
#include <bl_dma.h>

#define TRANSFER_SIZE    5111


static void init_buf(uint8_t *buf, int size)
{
    int i = 0;

    for (i = 0; i < TRANSFER_SIZE; i++) {
        buf[i] = i % 256;
    }
}

void demo_spi_master(char *buf, int len, int argc, char **argv)
{
    int a = 0;
    int spi_dev = -1;
    int ret;

    uint8_t *pbuf0_tx = NULL;
    uint8_t *pbuf0_rx = NULL;
    struct spi_ioc_transfer *pxfer = NULL;
   
    spi_dev = aos_open("/dev/spi0", 0);
    blog_info("start open spi_dev = %d.\r\n", spi_dev);
    if (spi_dev < 0) {
        blog_error("start open spi_dev = %d.\r\n", spi_dev);
        return;
    }

    pbuf0_tx = bl_dma_mem_malloc(TRANSFER_SIZE);
    pbuf0_rx = bl_dma_mem_malloc(TRANSFER_SIZE);
    printf("pbuf0_tx = %p  pbuf0_rx = %p \r\n", pbuf0_tx, pbuf0_rx);
    pxfer = (struct spi_ioc_transfer*)bl_dma_mem_malloc(2 * (sizeof(struct spi_ioc_transfer)));

    if ((!pbuf0_tx) || (!pbuf0_rx) || (!pxfer)) {
        blog_error("mem err.\r\n");
        return;
    }
 
    init_buf(pbuf0_tx, TRANSFER_SIZE);
    memset(pbuf0_rx, 0x00, TRANSFER_SIZE);

    pxfer[0].tx_buf = (uint32_t)pbuf0_tx;
    pxfer[0].rx_buf = (uint32_t)pbuf0_rx;
    pxfer[0].len = TRANSFER_SIZE;
    a = aos_ioctl(spi_dev, IOCTL_SPI_IOC_MESSAGE(1), (unsigned long)&pxfer[0]);
    if (a != 0) {
        blog_error("ERROR: SPI WRITE FAILURE\n");
    }

    ret = memcmp(pbuf0_tx, pbuf0_rx, TRANSFER_SIZE);
    if (ret == 0) {
        printf("data corrcet \r\n");
    } else {
        printf("data error \r\n");
    }

    bl_dma_mem_free(pbuf0_tx);
    bl_dma_mem_free(pbuf0_rx);
    bl_dma_mem_free(pxfer);
    aos_close(spi_dev);
}

void demo_spi_slave(char *buf, int len, int argc, char **argv)
{
    int a = 0;
    int spi_dev = -1;
    int ret;

    uint8_t *pbuf0_tx = NULL;
    uint8_t *pbuf0_rx = NULL;
    struct spi_ioc_transfer *pxfer = NULL;
   
    spi_dev = aos_open("/dev/spi0", 0);
    blog_info("start open spi_dev = %d.\r\n", spi_dev);
    if (spi_dev < 0) {
        blog_error("start open spi_dev = %d.\r\n", spi_dev);
        return;
    }

    pbuf0_tx = bl_dma_mem_malloc(TRANSFER_SIZE);
    pbuf0_rx = bl_dma_mem_malloc(TRANSFER_SIZE);
    printf("pbuf0_tx = %p  pbuf0_rx = %p \r\n", pbuf0_tx, pbuf0_rx);
    pxfer = (struct spi_ioc_transfer*)bl_dma_mem_malloc(2 * (sizeof(struct spi_ioc_transfer)));

    if ((!pbuf0_tx) || (!pbuf0_rx) || (!pxfer)) {
        blog_error("mem err.\r\n");
        return;
    }
 
    init_buf(pbuf0_tx, TRANSFER_SIZE);
    memset(pbuf0_rx, 0x00, TRANSFER_SIZE);

    pxfer[0].tx_buf = (uint32_t)pbuf0_tx;
    pxfer[0].rx_buf = (uint32_t)pbuf0_rx;
    pxfer[0].len = TRANSFER_SIZE;
    a = aos_ioctl(spi_dev, IOCTL_SPI_IOC_MESSAGE(1), (unsigned long)&pxfer[0]);
    if (a != 0) {
        blog_error("ERROR: SPI WRITE FAILURE\n");
    }

    ret = memcmp(pbuf0_tx, pbuf0_rx, TRANSFER_SIZE);
    if (ret == 0) {
        printf("data corrcet \r\n");
    } else {
        printf("data error \r\n");
    }

    vPortFree(pbuf0_tx);
    vPortFree(pbuf0_rx);
    vPortFree(pxfer);
    aos_close(spi_dev);
}

void spi_loop_master(char *buf, int len, int argc, char **argv)
{   
    int i = 0;
    for (i = 0; i < 100; i++) {
        demo_spi_master(NULL, 1, 1, NULL);
        vTaskDelay(3000);
    }
    
    return;
}

void spi_loop_slave(char *buf, int len, int argc, char **argv)
{   
    int i = 0;
    for (i = 0; i < 100; i++) {
        demo_spi_slave(NULL, 1, 1, NULL);
        vTaskDelay(200);
    }
    
    return;
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"test_slave", "spi test slave", demo_spi_slave},
    {"test_master", "spi test master", demo_spi_master},
    {"test_loop_master", "loop test master", spi_loop_master},
    {"test_loop_slave", "loop test slave", spi_loop_slave},
};                                                                                   

int spi_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
