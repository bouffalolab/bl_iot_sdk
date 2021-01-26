/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
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

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#include <link_endian.h>
#include <link_misc.h>
#include <crc.h>
#include <osal.h>
#include <pcp.h>
#include <ota_flag.h>
#include <ota_manager.h>


#define CN_VER_LEN      16
#define CN_SND_BUF_LEN  128

typedef enum
{
    EN_PCP_MSG_GETVER       = 19,
    EN_PCP_MSG_NOTIFYNEWVER,
    EN_PCP_MSG_GETBLOCK,
    EN_PCP_MSG_REPORTDOWNLOADSTATE,
    EN_PCP_MSG_EXCUTEUPDATE,
    EN_PCP_MSG_NOTIFYSTATE = 24
}en_pcp_msg_code_t;

typedef enum
{
    EN_PCP_RESPONSE_CODE_OK = 0x0,
    EN_PCP_RESPONSE_CODE_DEVBUSY = 0x1,
    EN_PCP_RESPONSE_CODE_DEVWEAKSIGNAL = 0x2,
    EN_PCP_RESPONSE_CODE_DEVLATESTVER = 0x3,
    EN_PCP_RESPONSE_CODE_LOWBATTERY = 0x4,
    EN_PCP_RESPONSE_CODE_NOSPACE = 0x5,
    EN_PCP_RESPONSE_CODE_DOWNLOADTIMEOUT = 0x6,
    EN_PCP_RESPONSE_CODE_FIRMWARECHECKERROR = 0x7,
    EN_PCP_RESPONSE_CODE_FIRMWARENOTMATH = 0x8,
    EN_PCP_RESPONSE_CODE_MEMORYEXHAUSTED = 0x9,
    EN_PCP_RESPONSE_CODE_INNERERROR = 0x7f,
    EN_PCP_RESPONSE_CODE_TASKEXIT = 0x80,
    EN_PCP_RESPONSE_CODE_BLOCKINVALID = 0x81
}en_pcp_response_code_t;

#pragma pack(1)
typedef struct
{
    uint16_t  ori_id;
    uint8_t   ver_num;
    uint8_t   msg_code;
    uint16_t  chk_code;
    uint16_t  data_len;
}pcp_head_t;

typedef struct
{
    uint8_t  ret;
    uint8_t  ver[CN_VER_LEN];
}pcp_response_version_t;

typedef struct
{
    uint8_t  ver[CN_VER_LEN];
    uint16_t block_size;
    uint16_t block_totalnum;
    uint16_t ver_chk_code;
}pcp_notify_version_t;

typedef struct
{
    uint8_t   ver[CN_VER_LEN];
    uint16_t  blocknum;
}pcp_request_block_t;

typedef struct
{
    uint8_t    retcode;
    uint16_t   block_num;
}pcp_response_block_t;


typedef struct
{
    uint8_t retcode;
}pcp_response_code_t;


typedef struct
{
    uint8_t retcode;
    uint8_t ver[CN_VER_LEN];
}pcp_report_ret_t;

#pragma pack()

#include <queue.h>   ///< we will build a message queue to talk with the application

#define CN_PCP_LIFE_TIMEBASE       2000  ///< the time uinit is minisecond

typedef struct
{
    ota_flag_t record;                         ///< this will do the continue work when the power recover
    int (*fn_pcp_send_msg)(void *msg,int len); ///< use this function to send the message
    unsigned long long timer_deadline;         ///< this is the deadline if we do the resend
    queue_t    *msg_queue;
}pcp_cb_t;

static pcp_cb_t  s_pcp_cb;        ///< this is the pcp controller block here
#define CN_PCP_HEADFLAG           0xFFFE


static void pcp_msg_print(const char *index,void *msg, int len)
{
    uint8_t *buf;
    buf = msg;
    int i = 0;
    LINK_LOG_DEBUG("%s:",index);
    for(i =0;i<len;i ++)
    {
        LINK_LOG_DEBUG("%02x",buf[i]);
    }
    LINK_LOG_DEBUG("\n\r");
}

static int pcp_save_flag()
{
    int ret;
    s_pcp_cb.record.crc = calc_crc32(0,&s_pcp_cb.record,sizeof(s_pcp_cb.record) - sizeof(s_pcp_cb.record.crc));
    ret = ota_storage_flag_write(&s_pcp_cb.record);
    return ret;
}

static int pcp_save_newversion(pcp_notify_version_t *newversion)
{
    int ret;
    s_pcp_cb.record.file_off = 0;
    s_pcp_cb.record.file_size = 0;
    s_pcp_cb.record.blk_cur = 0;
    s_pcp_cb.record.blk_size = newversion->block_size;
    s_pcp_cb.record.blk_num = newversion->block_totalnum;
    s_pcp_cb.record.ver_code = newversion->ver_chk_code;

    (void) memcpy(s_pcp_cb.record.ver, newversion->ver, CN_VER_LEN);
    s_pcp_cb.record.cur_state = EN_OTA_STATUS_DOWNLOADING;

    ret = pcp_save_flag();

    return ret;
}

///< use this function to write the message to the flash,and update the info
static int pcp_save_newblock(void *msg,int len)
{
    int ret = -1;
    if(0 == ota_storage_bin_write(s_pcp_cb.record.file_off,msg,len))
    {
        s_pcp_cb.record.blk_cur ++;
        s_pcp_cb.record.file_off += len;
        ret = pcp_save_flag();
    }

    return ret;
}


///< use this function to send the message to the server
static int pcp_send_msg(en_pcp_msg_code_t msg_code, void *msg, int len)
{
    int ret;
    pcp_head_t *pcp;
    uint8_t         *msg_buf;
    int              msg_len;

    ret = -1;
    msg_len = len  + sizeof(pcp_head_t);
    if (msg_len>= CN_SND_BUF_LEN)
    {
        return ret;
    }

    msg_buf = osal_malloc(msg_len);
    if(NULL == msg_buf)
    {
        return ret;
    }

    pcp = (pcp_head_t *)msg_buf;

    pcp->ori_id = htons(CN_PCP_HEADFLAG);
    pcp->ver_num =1;
    pcp->msg_code = msg_code;
    pcp->data_len = htons(len);
    pcp->chk_code = 0;
    (void) memcpy(msg_buf+sizeof(pcp_head_t),msg,len);
    ///< should check the crc here
    pcp->chk_code = calc_crc16(0,msg_buf,len +sizeof(pcp_head_t));
    pcp->chk_code = htons(pcp->chk_code);

    pcp_msg_print("PCP SND MSG:",msg_buf,msg_len);

    if(NULL != s_pcp_cb.fn_pcp_send_msg)
    {
        ret = s_pcp_cb.fn_pcp_send_msg(msg_buf,msg_len);
        if(0 != ret)
        {
            LINK_LOG_DEBUG("######PCP SEND FAILED######\n\r");
        }
    }

    osal_free(msg_buf);

    s_pcp_cb.timer_deadline = osal_sys_time() + CN_PCP_LIFE_TIMEBASE;

    return ret;
}

static void pcp_send_response_code(en_pcp_msg_code_t msg_code, en_pcp_response_code_t code)
{

    pcp_response_code_t  response;

    response.retcode = code;

    pcp_send_msg(msg_code, (uint8_t *)&response, sizeof(response));
}

static void pcp_request_block()
{
    pcp_request_block_t request;
    (void) memcpy(request.ver,s_pcp_cb.record.ver,CN_VER_LEN);
    request.blocknum = htons(s_pcp_cb.record.blk_cur);
    pcp_send_msg(EN_PCP_MSG_GETBLOCK, &request, sizeof(request));
}

static void pcp_report_downloadstate()
{
    pcp_send_response_code(EN_PCP_MSG_REPORTDOWNLOADSTATE, EN_PCP_RESPONSE_CODE_OK);

    return;
}

///< this function used to deal the get version message
static void pcp_cmd_getversion(const pcp_head_t *head, const uint8_t *pbuf)
{
    pcp_response_version_t  version;
    version.ret = 0;
    (void) memcpy(&version.ver,(uint8_t *)s_pcp_cb.record.ver, CN_VER_LEN);
    pcp_send_msg(EN_PCP_MSG_GETVER, (uint8_t *)&version, sizeof(version));

    return;
}

///< this function used to deal the notify the newversion message
static void pcp_cmd_notifyversion(const pcp_head_t *head, const uint8_t *pbuf)
{

    pcp_notify_version_t notify;  ///< make sure that the unaligned occurred

    if(head->data_len < sizeof(pcp_notify_version_t))
    {
        return ;
    }

    (void) memcpy(&notify,pbuf,sizeof(notify));
    notify.block_size = ntohs(notify.block_size);
    notify.block_totalnum = ntohs(notify.block_totalnum);
    notify.ver_chk_code= ntohs(notify.ver_chk_code);

    if ((strncmp((char *)s_pcp_cb.record.ver, (char *)notify.ver, CN_VER_LEN) == 0)
        && (notify.ver_chk_code == s_pcp_cb.record.ver_code))
    {
        ///< which means that we have the same version,check if we are downloading or not
        if(s_pcp_cb.record.cur_state == EN_OTA_STATUS_IDLE)  ///< we are already the same version
        {
            pcp_send_response_code(EN_PCP_MSG_NOTIFYNEWVER,EN_PCP_RESPONSE_CODE_DEVLATESTVER);
        }
        else
        {
            pcp_send_response_code(EN_PCP_MSG_NOTIFYNEWVER,EN_PCP_RESPONSE_CODE_OK);
        }
    }
    else
    {
        pcp_save_newversion(&notify);
        pcp_send_response_code(EN_PCP_MSG_NOTIFYNEWVER, EN_PCP_RESPONSE_CODE_OK);
        pcp_request_block();
    }
}
///< this function used to deal with the block message
static void pcp_cmd_notifyblock(const pcp_head_t *head, const uint8_t *pbuf)
{
    pcp_response_block_t response;

    if (s_pcp_cb.record.cur_state != EN_OTA_STATUS_DOWNLOADING)
    {
       return;
    }

    if(head->data_len <= sizeof(response))
    {
        return;
    }

    (void) memcpy(&response,pbuf,sizeof(response));
    response.block_num = ntohs(response.block_num);
    pbuf += sizeof(response);

    if (response.retcode != EN_PCP_RESPONSE_CODE_OK)
    {
        return ;
    }

    if (s_pcp_cb.record.blk_cur != response.block_num)
    {
        return ;
    }

    if(0 != pcp_save_newblock((uint8_t *)pbuf,head->data_len - sizeof(response)))
    {
        pcp_send_response_code(EN_PCP_MSG_REPORTDOWNLOADSTATE, EN_PCP_RESPONSE_CODE_NOSPACE);
        return;
    }

    if ((s_pcp_cb.record.blk_cur) < s_pcp_cb.record.blk_num)
    {
        pcp_request_block();
        return;
    }
    else
    {
        s_pcp_cb.record.cur_state = EN_OTA_STATUS_DOWNLOADED;
        s_pcp_cb.record.file_size = s_pcp_cb.record.file_off;

        pcp_save_flag();
        pcp_report_downloadstate();

        return;
    }
}

static void pcp_response_downloadstatus(const pcp_head_t *head, const uint8_t *pbuf)
{
    return;
}

static void pcp_response_upgradestatus(const pcp_head_t *head, const uint8_t *pbuf)
{
    s_pcp_cb.record.cur_state = EN_OTA_STATUS_IDLE;
    s_pcp_cb.record.ret_upgrade = EN_PCP_RESPONSE_CODE_OK;
    pcp_save_flag();
    return;
}


///< this function used to deal with the upgrade message
static void pcp_cmd_upgrade(const pcp_head_t *head, const uint8_t *pbuf)
{

    if (s_pcp_cb.record.cur_state != EN_OTA_STATUS_DOWNLOADED)
    {
        return;
    }
    s_pcp_cb.record.cur_state = EN_OTA_STATUS_UPGRADING;
    s_pcp_cb.record.updater = UPDATER_SOTA;
    pcp_save_flag();

    pcp_send_response_code(EN_PCP_MSG_EXCUTEUPDATE, EN_PCP_RESPONSE_CODE_OK);
}


///< this function used to deal withe message receive from the iot platform
static void pcp_handle_msg(uint8_t *msg, int msglen)
{

    pcp_head_t      pcp_head;                ///< the buffer maybe not aligned, so we should copy it
    uint8_t        *pcp_data = NULL;

    if(msglen < sizeof(pcp_head))
    {
        return;
    }
    (void) memcpy(&pcp_head,msg,sizeof(pcp_head));
    pcp_head.ori_id = ntohs(pcp_head.ori_id);
    pcp_head.chk_code = ntohs(pcp_head.chk_code);
    pcp_head.data_len = ntohs(pcp_head.data_len);

    ///< first we should check the crc right or not
    if(pcp_head.data_len > 0)
    {
        pcp_data = (uint8_t *)(msg + sizeof(pcp_head));
    }

    switch (pcp_head.msg_code)
    {
        case EN_PCP_MSG_GETVER:  ///< the server want to get the terminal version
            pcp_cmd_getversion(&pcp_head, pcp_data);
            break;

        case EN_PCP_MSG_NOTIFYNEWVER:
             pcp_cmd_notifyversion(&pcp_head, pcp_data);
            break;

        case EN_PCP_MSG_GETBLOCK:
            pcp_cmd_notifyblock(&pcp_head, pcp_data);
            break;
        case EN_PCP_MSG_REPORTDOWNLOADSTATE:   ///< this is the response message
            pcp_response_downloadstatus(&pcp_head, pcp_data);
            break;

        case EN_PCP_MSG_EXCUTEUPDATE:    ///< received the upgrade command, report the result when finish the upgrading
            pcp_cmd_upgrade(&pcp_head, pcp_data);

            //ota binary signature check
            if (ota_pack_get_signature_verify_result(OTA_SIGNATURE_LEN, s_pcp_cb.record.file_size) != 0) {
              s_pcp_cb.record.cur_state = EN_OTA_STATUS_UPGRADED;
              s_pcp_cb.record.ret_upgrade = EN_PCP_RESPONSE_CODE_FIRMWARENOTMATH;
              pcp_save_flag();
              break;
            }

	    ///< we should do the reboot
            osal_task_sleep(5000);
	    LINK_LOG_DEBUG("downloaded, goto loader!!!\n");
            osal_reboot();
	    while(1);   /* never come back */
            ///< todo , think we upgrade success--DO THESIMULATE
            ///////////////////////////////////////////////////////////////////
            s_pcp_cb.record.cur_state = EN_OTA_STATUS_UPGRADED;
            s_pcp_cb.record.ret_upgrade = EN_PCP_RESPONSE_CODE_OK;
            pcp_save_flag();
            ///////////////////////////////////////////////////////////////////

            break;
        case EN_PCP_MSG_NOTIFYSTATE:
             pcp_response_upgradestatus(&pcp_head,pcp_data);
             break;


        default:
            break;
    }

    return;
}

static void pcp_handle_timeout(void)
{
    pcp_report_ret_t upgrade_ret;
    switch (s_pcp_cb.record.cur_state )
    {
        case EN_OTA_STATUS_IDLE:
            break;
        case EN_OTA_STATUS_DOWNLOADING:
            ///< RESEND THE BLOCK REQUEST
            pcp_request_block();
            break;
        case EN_OTA_STATUS_DOWNLOADED:
            ///< RESEND THE DOWNLOADED STATUS
            pcp_report_downloadstate();
            break;
        case EN_OTA_STATUS_UPGRADING:
            ///< here we maybe need a reboot here
            break;
        case EN_OTA_STATUS_UPGRADED:
            upgrade_ret.retcode = s_pcp_cb.record.ret_upgrade;
            (void) memcpy(upgrade_ret.ver,s_pcp_cb.record.ver,CN_VER_LEN);
            ///< tell the server the result
	    if (s_pcp_cb.record.updater == UPDATER_SOTA) {
	      pcp_send_msg(EN_PCP_MSG_NOTIFYSTATE,&upgrade_ret,sizeof(upgrade_ret));
	    }
            break;
        default:
            break;
    }

    return;
}



int pcp_msg_push(void *msg, int len)
{
    int ret = -1;

    uint8_t  *buf;
    uint32_t  buflen;
    buflen = len +sizeof(buflen);

    buf = osal_malloc(buflen);
    if(NULL != buf)
    {
        (void) memcpy(buf,&buflen,sizeof(buflen));
        (void) memcpy(buf + sizeof(buflen),msg,len);

        ret = queue_push(s_pcp_cb.msg_queue,buf,10);
        if(ret != 0)
        {
            osal_free(buf);
        }
    }

    return ret;
}

///< for the software not implement yet, we now use a task as the soft timer
static int pcp_entry(void *args)
{
    uint32_t crc;
    int      time_wait;

    uint8_t *buf;
    uint8_t *msg;
    uint32_t msglen;
    ///< first we should read the log from the storage
    ota_storage_flag_read(&s_pcp_cb.record);

    crc = calc_crc32(0,&s_pcp_cb.record,sizeof(s_pcp_cb.record) - sizeof(s_pcp_cb.record.crc));
    if(crc != s_pcp_cb.record.crc)
    {
        ///< do the initialize and save it
        (void) memset(&s_pcp_cb.record,0,sizeof(s_pcp_cb.record));
        s_pcp_cb.record.cur_state = EN_OTA_STATUS_IDLE;
        pcp_save_flag();
    }
    while(1)
    {
        ///< compute the about wait time here
        if(s_pcp_cb.record.cur_state == EN_OTA_STATUS_IDLE)
        {
            time_wait = cn_osal_timeout_forever;
        }
        else
        {
            time_wait = CN_PCP_LIFE_TIMEBASE;
        }
        buf = NULL;
        queue_pop(s_pcp_cb.msg_queue,(void **)&buf,time_wait);
        if(NULL != buf)
        {
            msg = buf + sizeof(msglen);
            (void) memcpy(&msglen,buf,sizeof(msglen));
            msglen -= sizeof(msglen);

            pcp_msg_print("PCP RCV MSG:",(uint8_t *)msg,msglen >32?32:msglen);


            pcp_handle_msg(msg,msglen);
            osal_free(buf);
        }

        if(s_pcp_cb.timer_deadline < osal_sys_time())
        {
            pcp_handle_timeout();
        }
    }
    return 0;
}


int ota_pcp_init(int (*fn_pcp_send_msg)(void *msg,int len))
{
    int ret = -1;

    (void) memset(&s_pcp_cb,0,sizeof(s_pcp_cb));
    if(NULL == fn_pcp_send_msg)
    {
        return ret;
    }

    s_pcp_cb.fn_pcp_send_msg = fn_pcp_send_msg;
    s_pcp_cb.msg_queue = queue_create("pcp_rcv_queue",8,1);
    if(NULL == s_pcp_cb.msg_queue)
    {
        return ret;
    }

    osal_task_create("pcp_main",pcp_entry,NULL,0x1000,NULL,10);

    return 0;
}
