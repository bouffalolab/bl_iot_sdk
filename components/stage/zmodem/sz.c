/*
 * File      : sz.c
 * the implemention of sending files to the remote computers
 * through the zmodem protocol.
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-29     itspy
 */
#include <stdio.h>
#include <string.h>
#include "zdef.h"


static uint8_t TX_BUFFER[TX_BUFFER_SIZE];         /* sender buffer */
static uint8_t file_cnt = 0;                      /* count of number of files opened */
static uint8_t Rxflags  = 0;                      /* rx parameter flags */
static uint8_t ZF2_OP;                            /* file transfer option */

void zs_start(zfile_t *zf);
static void zsend_init(void);
static z_err_t zsend_files(zfile_t *zf);
static z_err_t zsend_file(zfile_t *zf, uint8_t *buf, size_t len);
static z_err_t zsend_file_data(zfile_t *zf);
//static uint16_t zfill_buffer(uint8_t *buf, uint16_t size, uint8_t *data, size_t remain_len, size_t data_size);
static z_err_t zget_sync(void);
static void zsay_bibi(void);




/* start zmodem send process */
void zs_start(zfile_t *zf)
{
    z_err_t res;
    printf("\r\nsz: ready...\r\n");    /* here ready to send things */
    if (zdevice_init()) {
        printf("init device fail\r\n");
        return;
    }
    res = zsend_files(zf);
    if (res == RT_EOK) {
#if __riscv_xlen == 64
        printf("zmodem send file ok name:%s size:%ubytes\r\n", zf->fname, zf->bytes_total);
#elif __riscv_xlen == 32
        printf("zmodem send file ok name:%s size:%lubytes\r\n", zf->fname, zf->bytes_total);
#endif
    } else {
        printf("zmodem send file fail name:%s\r\n", zf->fname);
    }
    zdevice_uninit();
    return;
}

/* init the parameters */
static void zsend_init(void)
{
    z_err_t res = -RT_ERROR;

    zinit_parameter();
    for(;;)          /* wait ZPAD */
    {
        res = zread_line(800);
        if (res == ZPAD) break;
    }
    for (;;)
    {
        res = zget_header(rx_header);
        if (res == ZRINIT) break;
    }
    if ((rx_header[ZF1] & ZRQNVH))
    {
        zput_pos(0x80L);    /* Show we can var header */
        zsend_hex_header(ZRQINIT, tx_header);
    }
    Rxflags = rx_header[ZF0] & 0377;
    if (Rxflags & CANFC32) Txfcs32 = 1;    /* used 32bits CRC check */

    if (ZF2_OP == ZTRLE && (Rxflags & CANRLE))    /* for RLE packet */
         Txfcs32 = 2;
    else
        ZF2_OP = 0;
    /* send SINIT cmd */
    return;
}

/* send files */
static z_err_t zsend_files(zfile_t *zf)
{
    char *p,*q;
    char *str = "/";
    z_err_t res = -RT_ERROR;

    if (zf->fname == NULL)
    {
        printf("\r\nerror: no file to be send.\r\n");
        return res;
    }

    ++file_cnt;
    /* extract file name */
    p = zf->fname;
    for (;;)
    {
        q = strstr(p,str);
        if (q == NULL)  break;
        p = q+1;
    }
    q = (char*)TX_BUFFER;
    for (;;)
    {
        *q++ = *p++;
        if (*p == 0) break;
    }
    *q++ = 0;
    p=q;
    while (q < (char*)(TX_BUFFER + 1024))
        *q++ = 0;
    /* get file attributes */
    Left_sizes += zf->bytes_total;
    sprintf(p, "%lu %lo %o 3 %d %lu", (long unsigned)zf->bytes_total, (long)6666,
              33, file_cnt, (long unsigned)Left_sizes);
    Left_sizes -= zf->bytes_total;
    //TX_BUFFER[127] = (zf->bytes_total + 127) >>7; /*MAYBE FIXME do not know why add this value*/
    //TX_BUFFER[126] = (zf->bytes_total + 127) >>15;

    zsend_init();
    /* start sending files */
    res = zsend_file(zf, TX_BUFFER, (p-(char*)TX_BUFFER)+strlen(p)+1);
    zsay_bibi();

    return res;
}

/* send file name and related info */
static z_err_t zsend_file(zfile_t *zf, uint8_t *buf, size_t len)
{
    uint8_t cnt;
    z_err_t res = -RT_ERROR;

    for (cnt=0;cnt<5;cnt++)
    {
        tx_header[ZF0] = ZF0_CMD;               /* file conversion option */
        tx_header[ZF1] = ZF1_CMD;               /* file management option */
        tx_header[ZF2] = (ZF3_CMD|ZF2_OP);      /* file transfer option   */
        tx_header[ZF3] = ZF3_CMD;
        zsend_bin_header(ZFILE, tx_header);
        zsend_bin_data(buf, len, ZCRCW);
loop:
        res = zget_header(rx_header);
        switch (res)
        {
        case ZRINIT:
             while ((res = zread_line(50)) > 0)
             {
                 if (res == ZPAD)
                 {
                    goto loop;
                 }
             }
             break;
        case ZCAN:
        case TIMEOUT:
        case ZABORT:
        case ZFIN:
             break;
        case -RT_ERROR:
        case ZNAK:
             break;
        case ZCRC:                           /* no CRC request */
             goto loop;
        case ZFERR:
        case ZSKIP:
             break;
        case ZRPOS:                          /* here we want */
             zget_pos(Rxpos);
             Txpos = Rxpos;
             return(zsend_file_data(zf));
        default:
             break;
        }
    }

    return res;
}

/* send the file data */
static z_err_t zsend_file_data(zfile_t *zf)
{
    int16_t cnt;
    uint8_t cmd;
    z_err_t res = -RT_ERROR;
    /* send ZDATA packet, start to send data */
start_send:
    zput_pos(Txpos);
    zsend_bin_header(ZDATA, tx_header);
    do
    {
        cnt = zf->fill_cb(zf, TX_BUFFER, RX_BUFFER_SIZE, Txpos);
        if (cnt < RX_BUFFER_SIZE ) {
            cmd = ZCRCE;
        } else {
            cmd = ZCRCG;
        }
        Txpos += cnt;
        zsend_bin_data(TX_BUFFER, cnt, cmd);
        if (cmd == ZCRCW)
            goto get_syn1;
    } while (cnt == RX_BUFFER_SIZE);
    for (;;)                         /*  get ack and check if send finish */
    {
        zput_pos(Txpos);
        zsend_bin_header(ZEOF, tx_header);
get_syn1:
        res = zget_sync();
        switch (res)
        {
        case ZACK:
             goto get_syn1;
        case ZNAK:
             continue;
        case ZRPOS:                     /* resend here */
             //lseek(zf->fd,Txpos,0);
             goto start_send;
        case ZRINIT:                   /*  send finish,then begin to send next file */
             return RT_EOK;
        case ZSKIP:
        case -RT_ERROR:
             return res;
        default:
             return res;
        }
    }
}

#if 0
/* fill file data to buffer*/
static uint16_t zfill_buffer(uint8_t *buf, uint16_t size, uint8_t *data, size_t remain_len, size_t data_size)
{
    size_t cpy_size = remain_len > size ? size : remain_len;
    memcpy(buf, data + data_size - remain_len, cpy_size);
    return cpy_size;
}
#endif

/* wait sync(ack) from the receiver */
static z_err_t zget_sync(void)
{
    z_err_t res = -RT_ERROR;

    for (;;)
    {
        res = zget_header(rx_header);
        switch (res)
        {
        case ZCAN:
        case ZABORT:
        case ZFIN:
        case TIMEOUT:
             return -RT_ERROR;
        case ZRPOS:                  /* get pos, need to resend */
             zget_pos(Rxpos);
             Txpos = Rxpos;
             return res;
        case ZACK:
             return res;
        case ZRINIT:                 /* get ZRINIT indicate that the prev file send completed */
             return res;
        case ZSKIP:
             return res;
        case -RT_ERROR:
        default:
             zsend_bin_header(ZNAK, tx_header);
             continue;
        }
    }
}

/* say "bibi" to the receiver */
static void zsay_bibi(void)
{
    for (;;)
    {
        zput_pos(0L);                         /* reninit position of next file*/
        zsend_hex_header(ZFIN, tx_header);    /* send finished session cmd */
        switch (zget_header(rx_header))
        {
        case ZFIN:
            zsend_line('O');
            zsend_line('O');
        case ZCAN:
        case TIMEOUT:
            return;
        }
    }
}
/* end of sz.c */
