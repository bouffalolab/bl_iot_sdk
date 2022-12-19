/*
 * File      : rz.c
 * the implemention of receiving files from the remote computers
 * through the zmodem protocol.
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-29     itspy
 * 2011-12-12     aozima       fixed syntax error.
 */

#include <stdio.h>
#include "zdef.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
//#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <aos/kernel.h>
#include <aos/yloop.h>

#include <cli.h>

void zr_start(zfile_t *zf);
static z_err_t zrec_init(uint8_t *rxbuf, struct zfile *zf);
static z_err_t zrec_files(struct zfile *zf);
static z_err_t zrec_file_data(uint8_t *buf, struct zfile *zf);;
static z_err_t zrec_file(uint8_t *rxbuf, struct zfile *zf);
static z_err_t zget_file_info(char *name, struct zfile *zf);
static z_err_t zwrite_file(uint8_t *buf, uint16_t size, struct zfile *zf);
static void zrec_ack_bibi(void);

/* start zmodem receive proccess */
void zr_start(zfile_t *zf)
{
    z_err_t res = -RT_ERROR;

    printf("zrec_files start.\r\n");

    if (zdevice_init()) {
        printf("init device fail\r\n");
        return;
    }

    res = zrec_files(zf);

    printf("zrec_files %d.\r\n", res);

    printf("\r\nfile: %s \r\n",zf->fname);

#if __riscv_xlen == 64
     printf("size: %u bytes\r\n",zf->bytes_received);
#elif __riscv_xlen == 32
     printf("size: %lu bytes\r\n",zf->bytes_received);
#endif

    printf("receive completed.\r\n");

    zdevice_uninit();

    /* waiting,clear console buffer */
    //aos_msleep(500);
}

/* receiver init, wait for ack */
static z_err_t zrec_init(uint8_t *rxbuf, struct zfile *zf)
{
    uint16_t err_cnt = 0;
    z_err_t res = -RT_ERROR;

    for (;;)
    {
        //printf("zrec_init.\r\n");
        zput_pos(0L);
        tx_header[ZF0] = ZF0_CMD;
        tx_header[ZF1] = ZF1_CMD;
        tx_header[ZF2] = ZF2_CMD;
        zsend_hex_header(ZRINIT, tx_header);
        //printf("zsend_hex_header\r\n");
again:
        //printf("zget_header\r\n");
        res = zget_header(rx_header);
        //printf("zget_header res = %02x\r\n", res);
        switch(res) {

        case ZFILE:
             ZF0_CMD  = rx_header[ZF0];
             ZF1_CMD  = rx_header[ZF1];
             ZF2_CMD  = rx_header[ZF2];
             ZF3_CMD  = rx_header[ZF3];
             res = zget_data(rxbuf, RX_BUFFER_SIZE);
             //printf("zget_data_res = %d\r\n", res);
             if (res == GOTCRCW)
             {
                 if ((res =zget_file_info((char*)rxbuf,zf))!= RT_EOK)
                 {
                     zsend_hex_header(ZSKIP, tx_header);
                     return (res);
                 }
                 return RT_EOK;;
             }
             zsend_hex_header(ZNAK, tx_header);
             printf("go again\r\n");
             goto again;
        case ZSINIT:
             if (zget_data((uint8_t*)Attn, ZATTNLEN) == GOTCRCW)       /* send zack */
             {
                zsend_hex_header(ZACK, tx_header);
                goto again;
             }
             zsend_hex_header(ZNAK, tx_header);          /* send znak */
             goto again;
        case ZRQINIT:
             continue;
        case ZEOF:
             continue;
        case ZCOMPL:
             goto again;
        case ZFIN:               /* end file session */
             zrec_ack_bibi();
             return res;
         default:
              if (++err_cnt >1000) return -RT_ERROR;
              continue;
        }
    }
}

/* receive files */
static z_err_t zrec_files(struct zfile *zf)
{
    uint8_t *rxbuf = NULL;
    z_err_t res = -RT_ERROR;

    zinit_parameter();
    rxbuf = aos_malloc(RX_BUFFER_SIZE*sizeof(uint8_t));
    if (rxbuf == NULL)
    {
         printf("rxbuf: out of memory\r\n");
         return -RT_ERROR;
    }
    printf("\r\nrz: ready...\r\n");    /* here ready to receive things */
    if ((res = zrec_init(rxbuf,zf))!= RT_EOK)
    {
         printf("\b\b\breceive init failed\r\n");
         aos_free(rxbuf);
         return -RT_ERROR;
    }

    printf("zrec_file start\r\n");

    res = zrec_file(rxbuf,zf);

    //printf("zrec_file res = %d\r\n", res);

    if (res == ZFIN)
    {
        aos_free(rxbuf);
        return RT_EOK;       /* if finish session */
    }
    else if (res == ZCAN)
    {
        aos_free(rxbuf);
        return ZCAN;        /* cancel by sender */
    }
    else
    {
       zsend_can();
       aos_free(rxbuf);
       return res;
    }
}
/* receive file */
static z_err_t zrec_file(uint8_t *rxbuf, struct zfile *zf)
{
    z_err_t res = - RT_ERROR;
    uint16_t err_cnt = 0;

    do
    {
        zput_pos(zf->bytes_received);
        zsend_hex_header(ZRPOS, tx_header);
again:
        res = zget_header(rx_header);
        switch (res)
        {
        case ZDATA:
             zget_pos(Rxpos);
             if (Rxpos != zf->bytes_received)
             {
                 zsend_break(Attn);
                 continue;
             }
             err_cnt = 0;
             //printf("test zrec_file_data.\r\n");
             res = zrec_file_data(rxbuf,zf);
             if (res == -RT_ERROR)
             {
                 zsend_break(Attn);
                 printf("ZDATA->continue\r\n");
                 continue;
             }
             else if (res == GOTCAN) return res;
             else goto again;
        case ZRPOS:
             zget_pos(Rxpos);
             continue;
        case ZEOF:
             err_cnt = 0;
             zget_pos(Rxpos);
             if (Rxpos != zf->bytes_received  || Rxpos != zf->bytes_total)
             {
#if __riscv_xlen == 64
                 printf("ZEOF->continue Rxpos = %d, bytes_received = %d, bytes_total = %d\r\n",
                    Rxpos, zf->bytes_received, zf->bytes_total);
#elif __riscv_xlen == 32
                 printf("ZEOF->continue Rxpos = %lu, bytes_received = %lu, bytes_total = %lu\r\n",
                    Rxpos, zf->bytes_received, zf->bytes_total);
#endif
                 continue;
             }
             return (zrec_init(rxbuf,zf));    /* resend ZRINIT packet,ready to receive next file */
        case ZFIN:
             zrec_ack_bibi();
             return ZCOMPL;
        case ZCAN:
#ifdef ZDEBUG
             printf("error code: sender cancelled \r\n");
#endif
             zf->bytes_received = 0L;        /* throw the received data */
             return res;
        case ZSKIP:
             return res;
        case -RT_ERROR:
             zsend_break(Attn);
             continue;
        case ZNAK:
        case TIMEOUT:
        default:
            continue;
        }
    } while(++err_cnt < 100);

    return res;
}

/* proccess file infomation */
static z_err_t zget_file_info(char *name, struct zfile *zf)
{
    return RT_EOK;
}

/* receive file data,continously, no ack */
static z_err_t zrec_file_data(uint8_t *buf, struct zfile *zf)
{
    z_err_t res = -RT_ERROR;

more_data:
    res = zget_data(buf,RX_BUFFER_SIZE);
    switch(res)
    {
    case GOTCRCW:                          /* zack received */
         zwrite_file(buf,Rxcount,zf);
         zf->bytes_received += Rxcount;
         zput_pos(zf->bytes_received);
         zsend_line(XON);
         //printf("zsend_hex_header.\r\n");
         zsend_hex_header(ZACK, tx_header);
         return RT_EOK;
    case GOTCRCQ:
         zwrite_file(buf,Rxcount,zf);
         zf->bytes_received += Rxcount;
         zput_pos(zf->bytes_received);
         zsend_hex_header(ZACK, tx_header);
         goto more_data;
    case GOTCRCG:
         zwrite_file(buf,Rxcount,zf);
         zf->bytes_received += Rxcount;
         goto more_data;
    case GOTCRCE:
         zwrite_file(buf,Rxcount,zf);
         zf->bytes_received += Rxcount;
         return RT_EOK;
    case GOTCAN:
#ifdef ZDEBUG
         printf("error code : ZCAN \r\n");
#endif
         return res;
    case TIMEOUT:
         return res;
    case -RT_ERROR:
         zsend_break(Attn);
         return res;
    default:
         return res;
    }
}

/* write file */
static z_err_t zwrite_file(uint8_t *buf,uint16_t size, struct zfile *zf)
{
    //printf("zwrite_file size = %d\r\n", size);

    if (size > 0) {
         memcpy(zf->data + zf->bytes_total, buf, size);
         //printf("zf->data = %p == %p\r\n", zf->data + zf->bytes_total, g_rz_filehex + zf->bytes_total);

         zf->bytes_total += size;
         //printf("memcpy (dest = %p, src = %p, size = %d), buf[0] = 0x%02x\r\n",
         //        (zf->data + zf->bytes_total), buf, size, buf[0]);
         //memcpy(zf->data + zf->bytes_total, buf, size);
    }

    return size;//(write(zf->fd,buf,size));
}

/* ack bibi */
static void zrec_ack_bibi(void)
{
    uint8_t i;

    zput_pos(0L);
    for (i=0;i<3;i++)
    {
        zsend_hex_header(ZFIN, tx_header);
        switch (zread_line(100))
        {
        case 'O':
             zread_line(1);
             return;
        case RCDO:
             return;
        case TIMEOUT:
        default:
             break;
        }
    }
}

/* end of rz.c */
