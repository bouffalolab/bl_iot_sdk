/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2019>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/
#include "usip.h"

#ifdef USIP_MCU
#include "usip_uart.h"
#endif

#ifdef USIP_WIFI
#include "hardware_interface.h"
#endif

#ifdef USIP_WIFI
#include "hlink_coap.h"
#endif

struct usip_io_cb
{
    unsigned short        write_index;    //the index of buf to be write when receive data
    unsigned short        is_ESC;   //1:the last receive data is ESC
    unsigned char         rcvbuf[USIP_UART_RCV_BUFF];//usip receive buffer
    unsigned short        is_receive_frame_head;
    UINT32  usip_uart_rx_sem;//if a frame has been written to the receive buffer, then active it
    UINT32  usip_wait_ack_sem;//if ack has been received, then active it
};

struct usip_frame_postion
{
    unsigned short pos;
    unsigned short len;
};

typedef struct {
    unsigned short tag;
    unsigned short len;
    unsigned char* val;
} usip_tlv;

typedef struct {
    unsigned char pkg_num;
    unsigned char seq;
    unsigned short cmd;
    unsigned short tlv_tag;
    unsigned short tlv_len;
    unsigned char tlv_val[USIP_FRM_DATA_MAX_LEN];
    struct frame_data_list *next;
} frame_data_list;

static struct usip_io_cb   g_usipio_cb;
static struct usip_frame_postion g_skb[USIP_UART_SKB_NUM];
static unsigned short g_skb_write_index = 0;
static unsigned short g_skb_read_index = 0;

unsigned char g_usip_send_buf[USIP_FRM_MAX_LEN];

static unsigned short g_frame_len = 0;// frame length

unsigned short g_seq = 0;//seq of cmd 0X00~0X7F
unsigned short g_wait_seq = 0;
unsigned short g_last_pkgnum_received = 0; //0 not received 1 received

static UINT32 g_send_timeout = 0;

static const unsigned char g_usip_crc_table[USIP_CRC_TABLE_LEN] = {
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
};

cmd_process_callback g_cmd_process_callback = NULL;
INT8 receive_one_frame_to_list(frame_data_list *frame_list);

void register_cmd_process_callback(cmd_process_callback cmd_process)
{
    g_cmd_process_callback = cmd_process;
}

unsigned short g_received_devreg_result = 0;//only used for mcu demo

void* usip_malloc(uint16_t size)
{
    return LOS_MemAlloc(m_aucSysMem0,size);
}

UINT32 usip_free(void* addr)
{
    return LOS_MemFree(m_aucSysMem0,addr);
}

void list_insert(frame_data_list *head,frame_data_list *node)
{
    frame_data_list *temp;
    temp = head;
    while(temp->next !=NULL)
    {
        temp = temp->next;//find the last node
    }
    temp->next = node;
}

unsigned short calc_total_len_from_frame_list(frame_data_list *head)
{
    unsigned short len = 0;
    frame_data_list *temp;
    temp = head->next;
    while(NULL!=temp)
    {
    	len = len + temp->tlv_len;
    	temp=temp->next;
    }
    return len;
}

void get_data_frame_list(frame_data_list *head,unsigned char* out_data)
{
    frame_data_list *temp;
    unsigned char* out_tmp = out_data;
    unsigned short len = 0;
    temp = head->next;
    while(NULL!=temp)
    {
        len = temp->tlv_len;
        unsigned char* source_data =temp->tlv_val;
        (void) memcpy(out_tmp, source_data,len);
        temp=temp->next;
        out_tmp = out_tmp + len;
    }
}

void free_frame_list(frame_data_list *head)
{
    frame_data_list *p = head;
    frame_data_list *pr = NULL;
    while (p != NULL)
    {
        pr = p;
        p = p->next;
        usip_free(pr);
        pr = NULL;
    }
}


int usip_rec_task(void *args)
{
    frame_data_list *head = (frame_data_list *)usip_malloc(sizeof(frame_data_list));
    (void) memset(head, 0, sizeof(frame_data_list));
    unsigned int rec_times=0;
    unsigned short json_data_len=0;

    unsigned char* json_data = NULL;
    unsigned short cmd = 0;
    while(1)//do the loop here
    {
        rec_times ++ ;
        if(g_cmd_process_callback == NULL)
        {
#ifdef USIP_LOG
            USIP_PRINTF("====cmd_process_callback is NULL!\r\n");
#endif
           break;
        }
        if(LOS_SemPend(g_usipio_cb.usip_uart_rx_sem, LOS_WAIT_FOREVER ) == LOS_OK)
        {
            frame_data_list *node = (frame_data_list *)usip_malloc(sizeof(frame_data_list));
            (void) memset(node, 0, sizeof(frame_data_list));
            UINT8 ret = receive_one_frame_to_list(node);
            if((ret > USIP_OK))
            {
#ifdef USIP_LOG
                USIP_PRINTF("====usip_rec_task pkg_num %d\r\n",node->pkg_num);
                USIP_PRINTF("====usip_rec_task tlv_len %d\r\n",node->tlv_len);
#endif
                json_data_len = json_data_len + node->tlv_len;
                list_insert(head,node);
                if(g_last_pkgnum_received == 1)
                {
                    g_last_pkgnum_received = 0;
                    cmd = node->cmd;
                    json_data = (unsigned char*)usip_malloc(json_data_len + 1);
                    (void) memset(json_data, 0, json_data_len + 1);
                    get_data_frame_list(head,json_data);
                    g_cmd_process_callback(cmd,json_data,json_data_len);
                    usip_free(json_data);
                    json_data = NULL;
                    json_data_len = 0;
                    free_frame_list(head->next);
                    head->next = NULL;
                }
            }else
            {
                usip_free(node);
            }
        }
    }
    usip_free(head);
    head = NULL;
}


int usip_rec_task_entry()
{

    int ret = -1;
    UINT32 uwRet = LOS_OK;
    UINT32  handle;
    TSK_INIT_PARAM_S task_init_param;

    (void) memset (&task_init_param, 0, sizeof (TSK_INIT_PARAM_S));
    task_init_param.uwArg = (unsigned int)NULL;
    task_init_param.usTaskPrio = 6;
    task_init_param.pcName =(char *) "usip_rec_task";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)usip_rec_task;
    task_init_param.uwStackSize = 0x1000;
    uwRet = LOS_TaskCreate(&handle, &task_init_param);
    if(LOS_OK == uwRet){
        ret = 0;
    }
    return ret;
}


UINT32 usip_init()
{
	UINT32 ret = LOS_OK;

    (void) memset(&g_usipio_cb,0,sizeof(g_usipio_cb));
    (void) memset(&g_skb,0,sizeof(g_skb));
    g_send_timeout = LOS_MS2Tick(USIP_WAIT_ACK_TIMEOUT);
    ret = LOS_BinarySemCreate(0,&g_usipio_cb.usip_uart_rx_sem);
    if (ret != LOS_OK)
    {
#ifdef USIP_LOG
        USIP_PRINTF("====LOS_BinarySemCreate g_usipio_cb.usip_uart_rx_sema failed!error:0x%X\n",ret);
#endif
        return ret;
    }

    ret = LOS_BinarySemCreate(0,&g_usipio_cb.usip_wait_ack_sem);
    if (ret != LOS_OK)
    {
#ifdef USIP_LOG
        USIP_PRINTF("====LOS_BinarySemCreate g_usipio_cb.usip_uart_hw_sem failed!error:0x%X\n",ret);
#endif
    	return ret;
    }

	return ret;
}

//change short data to EA format data
static short short_to_EA(unsigned short data,unsigned char* EA_data,unsigned short* EA_data_len)
{
    unsigned short len = 0;

    if (data < USIP_EA_BIT)
    {// one byte
        EA_data[0] = (((unsigned char)data) | USIP_EA_BIT);
        len = 1;
    }
    else
    {//two bytes
    	unsigned char tmp_data;
        EA_data[0] = (unsigned char)(data >> USIP_EA_VALID_BITS);
        tmp_data = (unsigned char)(data & (~USIP_EA_BIT));
        EA_data[1] = tmp_data | USIP_EA_BIT;
        len = 2;
    }
    *EA_data_len = len;
    return USIP_OK;
}

//change EA format data to short data
static short EA_to_short(unsigned char* EA_data,unsigned short* data,unsigned short* len)
{
    unsigned char tmp = EA_data[0];
    if((tmp & USIP_EA_BIT) != 0)
    {
        //one byte
        *data = tmp & (~USIP_EA_BIT);
        *len = 1;
        return USIP_OK;
    }
    else
    {
        *data = tmp << USIP_EA_VALID_BITS;
        tmp = EA_data[1];
        if((tmp & USIP_EA_BIT) == 0)
        {
            return USIP_ERROR;
        }
        tmp = tmp & (~USIP_EA_BIT);
        *data += tmp;
        *len = 2;
    }
    return USIP_OK;
}

//Support one frame
unsigned short convert_tlv_to_usip_frame(unsigned char pkg_num,unsigned char seq,unsigned short cmd,usip_tlv data)
{
    unsigned short j = 0;
    unsigned char crc = 0;
    unsigned short i = 0;

    for (i = 0; i < USIP_FRM_MAX_LEN; i++) {
        *(g_usip_send_buf + i) = 0;
    }
    // head
    g_usip_send_buf[j] = END;
    j++;

    g_usip_send_buf[j] = pkg_num;
    //calc crc from package_num
    crc = g_usip_crc_table[crc ^ g_usip_send_buf[j]];
    j++;

    g_usip_send_buf[j] = seq;
    crc = g_usip_crc_table[crc ^ g_usip_send_buf[j]];
    j++;

    //cmd
    unsigned char EA_cmd[2] = {0};
    unsigned short EA_cmd_len = 0;
    if(short_to_EA(cmd,EA_cmd,&EA_cmd_len) != USIP_OK)
    {
        return USIP_ERROR;
    }
    for (i = 0; i < EA_cmd_len; i++) {
        g_usip_send_buf[j] = *(EA_cmd + i);
        crc = g_usip_crc_table[crc ^ g_usip_send_buf[j]];
        j++;
    }

    //tlv tag
    unsigned char EA_tlv_tag[2] = {0};
    unsigned short EA_tlv_tag_len = 0;
    if(short_to_EA(data.tag,EA_tlv_tag,&EA_tlv_tag_len) != USIP_OK)
    {
        return USIP_ERROR;
    }

    for (i = 0; i < EA_tlv_tag_len; i++) {
        g_usip_send_buf[j] = *(EA_tlv_tag + i);
        crc = g_usip_crc_table[crc ^ g_usip_send_buf[j]];
        j++;
    }

    //tlv len
    unsigned char EA_tlv_len[2] = {0};
    unsigned short EA_tlv_len_len = 0;
    if(short_to_EA(data.len,EA_tlv_len,&EA_tlv_len_len) != USIP_OK)
    {
        return USIP_ERROR;
    }

    for (i = 0; i < EA_tlv_len_len; i++) {
        g_usip_send_buf[j] = *(EA_tlv_len + i);
        crc = g_usip_crc_table[crc ^ g_usip_send_buf[j]];
        j++;
    }

    /* tlv val */
    for (i = 0; i < data.len; i++) {
        g_usip_send_buf[j] = *(data.val + i);
        crc = g_usip_crc_table[crc ^ g_usip_send_buf[j]];
        j++;
    }

    /* CRC */
    g_usip_send_buf[j] = crc;
    j++;

    /* Flag */
    g_usip_send_buf[j] = END;

    return j + 1;
}

void send_one_frame(unsigned char* buf, unsigned short len)
{
    unsigned short i = 0;

    //send frame head END
    send_one_byte(buf[0]);
    i++;

    //deal END or ESC of frame data
    for (; i < len - 1; i++)
    {
        switch (buf[i]) {
            case END:
                send_one_byte(ESC);
                send_one_byte(ESC_END);
                break;
            case ESC:
                send_one_byte(ESC);
                send_one_byte(ESC_ESC);
                break;
            default:
                send_one_byte(buf[i]);
                break;
        }
    }

    //send frame end END
    send_one_byte(buf[i]);
}

unsigned char get_seq()
{
    unsigned char seq = g_seq++;
    if(g_seq > USIP_SEQ_MAX)
    {
        g_seq = USIP_SEQ_MIN;
    }
    return seq;
}

int usip_send_tlv(unsigned char pkg_num,unsigned char seq,unsigned short cmd,usip_tlv data)
{
    unsigned short frame_len = convert_tlv_to_usip_frame(pkg_num,seq,cmd,data);
    unsigned short loop_cnt = 0;
    while(1)  //do the loop here for wait ack
    {
        send_one_frame(g_usip_send_buf,frame_len);
        if(loop_cnt == USIP_MAX_ARQ_TIMES)
        {
#ifdef USIP_LOG
            USIP_PRINTF("====Retransmission send times = %d\r\n",USIP_MAX_ARQ_TIMES);
#endif
            return USIP_ERROR;
        }
        if(LOS_SemPend(g_usipio_cb.usip_wait_ack_sem, g_send_timeout) == LOS_OK)
        {
            return USIP_OK;
        }
        loop_cnt ++ ;
    }
    return USIP_OK;
}

//return 0 means success
int usip_send_data(unsigned short cmd,unsigned char* data, unsigned short len)
{
#ifdef USIP_LOG
    USIP_PRINTF("====usip_send_data cmd:%d\r\n",cmd);
    USIP_PRINTF("====usip_send_data data:%s\r\n",data);
    USIP_PRINTF("====usip_send_data len:%d\r\n",len);
#endif

    unsigned short ret = USIP_OK;
    unsigned char package_num = 0;
    unsigned short left_len = len;
    unsigned char* tmp_data = data;
    unsigned char EA_cmd[2] = {0};
    unsigned short EA_cmd_len = 0;
    usip_tlv tlv = {0};
    if(short_to_EA(cmd,EA_cmd,&EA_cmd_len) != USIP_OK)
    {
        return USIP_ERROR;
    }

    unsigned short tlv_val_max_len = USIP_FRM_CMD_AND_TLVS_MAX_LEN - EA_cmd_len - 2*USIP_TLV_TAG_LEN;

    if(left_len > ((USIP_PKGNUM_MAX+1) * tlv_val_max_len))
    {//data is too long,128 packages are not enough
        return USIP_ERROR;
    }

    unsigned char seq = get_seq();
    g_wait_seq = seq;

//HEAD+PKGNUM+SEQ+CMD+TLV.tag+TLV.len+TLV.val+CRC8+END <=128
    while (left_len > tlv_val_max_len) {
        tlv.tag = USIP_TLV_TAG_RST;
        tlv.len = tlv_val_max_len;
        tlv.val = tmp_data;
        if(usip_send_tlv(package_num,seq,cmd,tlv) != USIP_OK)
        {
#ifdef USIP_LOG
        USIP_PRINTF("====usip_send_tlv failed!\r\n");
#endif
            return USIP_ERROR;
        }
#ifdef USIP_LOG
        USIP_PRINTF("====usip_send_data package_num:%d\r\n",package_num);
#endif
        package_num++;
        tmp_data += tlv_val_max_len;
        left_len -= tlv_val_max_len;
    }
    tlv.tag = USIP_TLV_TAG_RST;//the last package
    tlv.len = left_len;
    tlv.val = tmp_data;
    if(usip_send_tlv(package_num|USIP_EA_BIT,seq,cmd,tlv) != USIP_OK)
    {
        return USIP_ERROR;
    }
#ifdef USIP_LOG
    USIP_PRINTF("====usip_send_data package_num:%d\r\n",package_num);
#endif
    return USIP_OK;
}

// receive one byte according usip_uart UART_FLAG_RXNE interrupt
void receive_one_byte(unsigned char data)
{
    unsigned char receive_data = data;

    //the last received data is ESC
    if (g_usipio_cb.is_ESC == 1) {
        // data is not ESC_END or ESC_ESC,ignore this frame
        if ((receive_data != ESC_END) && (receive_data != ESC_ESC)) {
            g_frame_len = 0;
            g_usipio_cb.is_ESC = 0;
            g_usipio_cb.is_receive_frame_head = 0;

            g_skb[g_skb_write_index].len = 0;
            g_skb[g_skb_write_index].pos = g_usipio_cb.write_index;
        }
    }

    //received frame head
    if((receive_data == END)&&(g_usipio_cb.is_receive_frame_head == 0))
    {
        g_usipio_cb.is_receive_frame_head = 1;
        //todo:optimize if the recbuf will full
        if ((USIP_UART_RCV_BUFF - g_usipio_cb.write_index) < USIP_FRM_DATA_MAX_LEN)
        {
            g_usipio_cb.write_index = 0;
        }
        g_skb[g_skb_write_index].pos = g_usipio_cb.write_index;
        return;
    }

    if(g_usipio_cb.is_receive_frame_head == 1)
    {
        switch (receive_data) {
            case END:
                // receive two END
                g_usipio_cb.is_receive_frame_head = 0;
                if (g_frame_len == 0)
                    return;
                g_skb[g_skb_write_index].len = g_frame_len;
                g_frame_len = 0;
                g_usipio_cb.is_ESC = 0;
                g_skb_write_index++;
                LOS_SemPost(g_usipio_cb.usip_uart_rx_sem);//receive one frame
                break;
            case ESC:
                g_usipio_cb.is_ESC = 1;
                break;
            case ESC_END:
                if (g_usipio_cb.is_ESC == 1) {
                    receive_data = END;
                    g_usipio_cb.is_ESC = 0;
                }
                g_frame_len++;
                g_usipio_cb.rcvbuf[g_usipio_cb.write_index] = receive_data;
                g_usipio_cb.write_index++;
                break;
            case ESC_ESC:
                if (g_usipio_cb.is_ESC == 1) {
                    receive_data = ESC;
                    g_usipio_cb.is_ESC = 0;
                }
                g_frame_len++;
                g_usipio_cb.rcvbuf[g_usipio_cb.write_index] = receive_data;
                g_usipio_cb.write_index++;
                break;
            default:
                g_frame_len++;
                g_usipio_cb.rcvbuf[g_usipio_cb.write_index] = receive_data;
                g_usipio_cb.write_index++;
                break;
        }
    }

    if (g_usipio_cb.write_index == USIP_UART_RCV_BUFF)
    {
        g_usipio_cb.write_index = 0;
    }

    if(g_skb_write_index == USIP_UART_SKB_NUM)
    {
        g_skb_write_index = 0;
    }
}


unsigned short usip_send_ack(unsigned short seq,unsigned short cmd,unsigned char pkg_num)
{
    unsigned char ack_pkg_num = 0 | USIP_EA_BIT;
    usip_tlv data;
    data.tag = USIP_TLV_TAG_ACK;
    data.len = 1;
    data.val = &pkg_num;

    unsigned short frame_len = convert_tlv_to_usip_frame(ack_pkg_num,seq,cmd,data);
    send_one_frame(g_usip_send_buf,frame_len);
}

INT8 receive_one_frame_to_list(frame_data_list *frame_list)
{
    if(g_skb_read_index == USIP_UART_SKB_NUM) {
        g_skb_read_index = 0;
    }
    unsigned short frame_pos = g_skb[g_skb_read_index].pos;
    unsigned short frame_len = g_skb[g_skb_read_index].len;
    unsigned char* data = g_usipio_cb.rcvbuf;
    unsigned char crc = 0;
    data = data +frame_pos;

    if(frame_len == 0) {
        g_skb_read_index++;
        return USIP_ERROR;
    }
    if (frame_len > USIP_FRM_DATA_MAX_LEN) {
#ifdef USIP_LOG
        USIP_PRINTF("====receive frame data len more than %d\r\n",USIP_FRM_DATA_MAX_LEN);
#endif
        //ignor this frame
        g_skb[g_skb_read_index].len = 0;
        g_skb_read_index ++;
        return USIP_ERROR;
    }
    //check crc
    for (unsigned short i = 0; i < (frame_len - 1); i++)
    {
        crc = g_usip_crc_table[crc ^ (g_usipio_cb.rcvbuf[frame_pos + i])];
    }
    if (crc != g_usipio_cb.rcvbuf[frame_pos + frame_len - 1])
    {
        g_skb[g_skb_read_index].len = 0;
        g_skb_read_index ++;
#ifdef USIP_LOG
        USIP_PRINTF("====crc error\r\n");
#endif
        return USIP_ERROR;
    }

    //get pkg_num
    unsigned char pkg_num = *data;
    if((pkg_num & USIP_EA_BIT) != 0)//the last package
    {
        g_last_pkgnum_received = 1;
        frame_list->pkg_num = (pkg_num & (~USIP_EA_BIT));
    }
    else
    {
        frame_list->pkg_num = pkg_num;
    }
    data++;

    //get seq
    frame_list->seq = *data;
    if((frame_list->seq & USIP_EA_BIT) != 0)// EA = 1 ack,ack not need store to list
    {
        g_last_pkgnum_received = 0;
        if(g_wait_seq == (frame_list->seq & (~USIP_EA_BIT)))
        {
            LOS_SemPost(g_usipio_cb.usip_wait_ack_sem);
            g_skb[g_skb_read_index].len = 0;
            g_skb_read_index ++;
            return USIP_OK;
        }
        else
        {
            return USIP_ERROR;
        }
    }
    data++;

// get cmd
    unsigned short frame_cmd_num = 0;
    EA_to_short(data,&(frame_list->cmd),&frame_cmd_num);
    data = data + frame_cmd_num;

//get tlv_tag
    unsigned short tlv_tag_num = 0;
    EA_to_short(data,&(frame_list->tlv_tag),&tlv_tag_num);
    data = data + tlv_tag_num;

//get tlv_len
    unsigned short tlv_len_num = 0;
    EA_to_short(data,&(frame_list->tlv_len),&tlv_len_num);
    data = data + tlv_len_num;

//get tlv_val
    for (int i = 0; i < frame_list->tlv_len; i++)
    {
        frame_list->tlv_val[i]= *data;
        data++;
    }

    usip_send_ack(frame_list->seq | USIP_EA_BIT,frame_list->cmd,frame_list->pkg_num);
    g_skb_read_index ++;
    return frame_list->tlv_len;
}
void usip_cmd_process(unsigned short cmd,unsigned char* data, unsigned short len)
{
#ifdef USIP_LOG
    USIP_PRINTF("====cmd_process cmd =%d\r\n",cmd);
    USIP_PRINTF("====cmd_process data =%s\r\n",data);
    USIP_PRINTF("====cmd_process len =%d\r\n",len);
#endif
    switch (cmd) {
        case USIP_CMD_DEV_REG:
#ifdef USIP_WIFI
            hlink_coap_api_dev_reg(data,len);
#endif
            break;
        case USIP_CMD_SESS_MNGR:
#ifdef USIP_WIFI
            hlink_coap_api_session_add(data,len);
#endif
            break;
        case USIP_CMD_FILE_MNGR:
#ifdef USIP_WIFI
            hlink_coap_api_file_mngr(data,len);
#endif
            break;
        case USIP_CMD_DATA_REPORT:
#ifdef USIP_WIFI
            hlink_coap_api_srv_data_report(data,len);
#endif
            break;
        case USIP_CMD_DEV_REG_RSP:
            //todo
            g_received_devreg_result = 1;//only used for mcu demo
            break;
        case USIP_CMD_SESS_MNGR_RSP:
            //todo
            break;
        case USIP_CMD_FILE_MNGR_RSP:
            //todo
            break;
        case USIP_CMD_DATA_REPORT_RSP:
            //todo
            break;
        default:
            //unknown cmd
#ifdef USIP_LOG
            USIP_PRINTF("====unknown cmd\r\n");
#endif
            return;
    }
}

