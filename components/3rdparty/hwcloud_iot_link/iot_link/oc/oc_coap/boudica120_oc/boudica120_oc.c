/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2018>, <Huawei Technologies Co., Ltd>
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

///< you must config the at module ,for the NB modules need the at


#include <string.h>
#include <at.h>
#include <boudica120_oc.h>
#include <oc_coap_al.h>
#include <osal.h>

///<  only support the bootstrap mode

#define cn_boudica120_cmd_timeout  (2*1000)
#define cn_boudica120_try_times    (32)
#define cn_boudica120_rcvindex     "\r\n+NNMI:"
#define cn_urc_qlwevtind           "\r\n+QLWEVTIND:"
#define cn_boudica120_cachelen     128

typedef struct
{
    //initialize by the NB module init
    const char *plmn;
    const char *apn;
    const char *bands;

    //initialized by the applicaiton
    oc_config_param_t  oc_param;

    //this is the control block
    bool_t            sndenable;
    unsigned char     sndbuf[cn_boudica120_cachelen];  //used for the receive
    unsigned char     rcvbuf[cn_boudica120_cachelen];
    //for the debug
    unsigned int   rcvlen;
    unsigned int   sndlen;


}boudica120_cb_t;
static boudica120_cb_t   s_boudica120_oc_cb;
static osal_mutex_t s_report_mutex;
static void  *s_oc_handle = NULL;

int wireless_stats[4] = {0};

//bc95 common at command
/* Use at component to send command("cmd").
 * If response include "index",return true, else return false
 * Don't store response
 */
static bool_t boudica120_atcmd(const char *cmd,const char *index)
{
    int ret = 0;
    ret = at_command((unsigned char *)cmd,strlen(cmd),index,NULL,0,cn_boudica120_cmd_timeout);
    if(ret >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//nb command  with response
//bc95 common at command
/* Use at component to send command("cmd").
 * If response include "index",return true, else return false
 * And store response to "buf"
 */
static bool_t boudica120_atcmd_response(const char *cmd,const char *index,char *buf, int len)
{
    int ret = 0;
    ret = at_command((unsigned char *)cmd,strlen(cmd),index,(char *)buf,len,cn_boudica120_cmd_timeout);
    if(ret >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}



//make a byte to 2 ascii hex
static int byte_to_hexstr(const unsigned char *bufin, int len, char *bufout)
{
    int i = 0;
    if (NULL == bufin || len <= 0 || NULL == bufout)
    {
        return -1;
    }
    for(i = 0; i < len; i++)
    {
        (void) sprintf(bufout+i*2, "%02X", bufin[i]);
    }
    return 0;
}

/* Use "AT+NMGS" to send coap message.
 *
 */
static int boudica120_oc_report(void *handle,char *buf,int len)
{
    int ret = en_oc_coap_err_noconfigured;
	int timeout = cn_boudica120_cmd_timeout;
    const char *cmd = "AT+NMGS=";
    const char *index = "OK";

    if(NULL == s_oc_handle)
    {
        return ret;
    }

    if ((NULL == buf) || (len >= cn_boudica120_cachelen/2 )||(false == s_boudica120_oc_cb.sndenable))
    {
        ret = en_oc_coap_err_parafmt;
        return ret;
    }
    osal_mutex_lock(s_report_mutex);
    (void) memset(s_boudica120_oc_cb.sndbuf, 0, cn_boudica120_cachelen);
    (void) snprintf((char *)s_boudica120_oc_cb.sndbuf,cn_boudica120_cachelen,"%s%d,",cmd,len);
    ret = byte_to_hexstr((unsigned char *)buf, len, (char *)&s_boudica120_oc_cb.sndbuf[strlen((char *)s_boudica120_oc_cb.sndbuf)]);
    s_boudica120_oc_cb.sndbuf[strlen((char *)s_boudica120_oc_cb.sndbuf)]='\r';

    ret = at_command((unsigned char *)s_boudica120_oc_cb.sndbuf,strlen((char *)s_boudica120_oc_cb.sndbuf),index,NULL,0,timeout);
    (void) osal_mutex_unlock(s_report_mutex);
    if(ret >= 0)
    {
        ret = en_oc_coap_err_ok;
    }
    else
    {
        ret = en_oc_coap_err_network;
    }

    return ret;
}


static int hexstr_to_byte(const char *bufin, int len, char *bufout)
{
    int i = 0;
    unsigned char tmp2 = 0x0;
    unsigned int tmp = 0;
    if (NULL == bufin || len <= 0 || NULL == bufout)
    {
        return -1;
    }
    for(i = 0; i < len; i = i+2)
    {
        tmp2 =  bufin[i];
        tmp2 =  tmp2 <= '9'?tmp2-0x30:tmp2-0x37;
        tmp =  bufin[i+1];
        tmp =  tmp <= '9'?tmp-0x30:tmp-0x37;
        bufout[i/2] =(tmp2<<4)|(tmp&0x0F);
    }
    return 0;
}

static int boudica120_rcvdeal(void *args,void *msg,size_t len)
{
    int ret = 0;
    int datalen;
    char *data;
    char  *str;

    data = msg;
    if(len <strlen(cn_boudica120_rcvindex))
    {
        LINK_LOG_DEBUG("%s:invalid frame:%d byte:%s\n\r",__FUNCTION__,len,(char *)data);
        return ret;
    }
    //now deal the data
    str = strstr((char *)data,":");
    if(NULL == str)
    {
        LINK_LOG_DEBUG("%s:format error\n\r",__FUNCTION__);
        return ret; //format error
    }
    str++;
    datalen = 0;
    for (; *str <= '9' && *str >= '0' ;str++)
    {
        datalen = (datalen * 10 + (*str - '0'));
    }
    str++;
    //now this is data of hex string
    if((unsigned int)(str + datalen*2 +2) > (unsigned int)(data + len))
    {
        LINK_LOG_DEBUG("%s:implement error\n\r",__FUNCTION__);
        return ret; //
    }
    if(datalen > cn_boudica120_cachelen)
    {
        LINK_LOG_DEBUG("%s:frame over: frame:%d  cachelen:%d \n\r",__FUNCTION__,datalen,cn_boudica120_cachelen);
        return ret; //
    }
    (void) memset(s_boudica120_oc_cb.rcvbuf,0,cn_boudica120_cachelen);
    hexstr_to_byte(str,datalen*2,(char *)s_boudica120_oc_cb.rcvbuf);

    if(NULL != s_boudica120_oc_cb.oc_param.rcv_func)
    {
        s_boudica120_oc_cb.oc_param.rcv_func((char *)s_boudica120_oc_cb.rcvbuf,datalen);
    }

    return len;
}

//enable the echooff
static bool_t boudica120_set_echo(int enable)
{
    bool_t ret ;
    char cmd[64];
    (void) memset(cmd,0,64);
    (void) snprintf(cmd,64,"ATE%d\r",enable);

    ret = boudica120_atcmd(cmd,"OK");

    return ret;
}


//use this function to do the module reboot
static bool_t boudica120_reboot(void)
{
    //do the module reset
    boudica120_set_echo (0);
    boudica120_set_echo (0);

    boudica120_atcmd("AT+NRB\r","REBOOTING");
    osal_task_sleep(10000); //wait for the module boot
    //do the module reset
    boudica120_set_echo (0);
    boudica120_set_echo (0);

    return true;
}

//enable the cfun
static bool_t boudica120_set_fun(int enable)  //unit second
{
    bool_t ret ;
    char cmd[64];

    (void) memset(cmd,0,64);
    (void) snprintf(cmd,64,"AT+CFUN=%d\r",enable);

    ret = boudica120_atcmd(cmd,"OK");
    //i think we should do some wait here
    osal_task_sleep(2000);

    return ret;
}

//use this function to set the band
static bool_t boudica120_set_bands(const char *bands)
{
    char cmd[64];
    char resp[64];
    bool_t ret = true;

    if(NULL != bands)  //which means we need to set if the default is not the same
    {
        (void) memset(resp,0,64);
        ret = boudica120_atcmd_response("AT+NBAND?\r","OK",resp,64);

        (void) memset(cmd,0,64);
        (void) snprintf(cmd,63,"+NBAND:%s\r",bands);

        if((false == ret)||(NULL == strstr(resp,cmd)))//which means we need to set it
        {
            boudica120_set_fun(0);

            (void) memset(cmd,0,64);
            (void) snprintf(cmd,63,"AT+NBAND=%s\r",bands);
            ret = boudica120_atcmd(cmd,"OK");

            boudica120_set_fun(1);
        }
        else
        {
            ret = true;  //we need not to set
        }
    }
    return ret;
}

//set the plmn
static bool_t boudica120_set_plmn(const char *plmn)
{
    char cmd[64];
    char resp[64];
    bool_t ret;

    if(NULL != plmn)  //which measn we need to set if the default is not the same
    {
        (void) memset(resp,0,64);
        ret = boudica120_atcmd_response("AT+COPS?\r","+COPS",resp,64);

        (void) memset(cmd,0,64);
        (void) snprintf(cmd,63,"+COPS:1,2,\"%s\"\r",plmn);

        if((false == ret)||(NULL == strstr(resp,cmd)))//which means we need to set it
        {
            (void) memset(cmd,0,64);
            (void) snprintf(cmd,63,"AT+COPS=1,2,\"%s\"\r",plmn);

            ret = boudica120_atcmd(cmd,"OK");
        }
        else
        {
            ret = true;  //we need not to set
        }
    }
    else  //set it to auto
    {
        (void) memset(cmd,0,64);
        (void) snprintf(cmd,64,"AT+COPS=0\r");
        ret = boudica120_atcmd(cmd,"OK");
    }

    return ret;
}

//set the apn
static bool_t boudica120_set_apn(const char *apn)
{
    char cmd[64];
    char resp[64];

    bool_t ret = true;

    if(NULL != apn)  //which measn we need to set if the default is not the same
    {
        (void) memset(resp,0,64);
        ret = boudica120_atcmd_response("AT+CGDCONT?\r","OK",resp,64);

        (void) memset(cmd,0,64);
        (void) snprintf(cmd,63,"+CGDCONT:\"%s\"\r",apn); //TODO, check if it is right
        if((false == ret)||(NULL == strstr(resp,cmd)))//which means we need to set it
        {
            (void) memset(cmd,0,64);
            (void) snprintf(cmd,63,"AT+CGDCONT=%s\r",apn);
            ret = boudica120_atcmd(cmd,"OK");
        }
        else
        {
            ret = true;  //we need not to set
        }
    }
    return ret;
}

//set the cdp
static bool_t boudica120_set_cdp(const char *server,const char *port)
{
    char cmd[64];
    char resp[64];
    char cmp[64];
    bool_t ret = true;

    if(NULL != server)  //which measn we need to set if the default is not the same
    {
        (void) memset(resp,0,64);
        (void) memset(cmp,0,64);
        (void) memset(cmd,0,64);
        ret = boudica120_atcmd_response("AT+NCDP?\r","OK",resp,64);
        (void) snprintf(cmp,64,"+NCDP:%s,%s\r",server,port);
        if((false == ret)||(NULL == strstr(resp,cmp)))//which means we need to set it
        {
            (void) memset(cmd,0,64);
            (void) snprintf(cmd,64,"AT+NCDP=%s,%s\r",server,port);
            ret = boudica120_atcmd(cmd,"OK");
        }
        else
        {
            ret = true;  //we need not to set
        }
    }
    return ret;
}

//enable the cmee

static bool_t boudica120_set_cmee(int enable)
{
    bool_t ret;
    char cmd[64];

    (void) memset(cmd,0,64);
    (void) snprintf(cmd,64,"AT+CMEE=%d\r",enable);

    ret = boudica120_atcmd(cmd,"OK");

    return ret;
}

//enable the network
static bool_t boudica120_set_cgatt(int enable)  //unit second
{
    bool_t ret ;
    char cmd[64];

    (void) memset(cmd,0,64);
    (void) snprintf(cmd,64,"AT+CGATT=%d\r",enable);

    ret = boudica120_atcmd(cmd,"OK");

    return ret;
}

//enable the NNMI
static bool_t boudica120_set_nnmi(int enable)  //unit second
{
    bool_t ret ;
    char cmd[64];

    (void) memset(cmd,0,64);
    (void) snprintf(cmd,64,"AT+NNMI=%d\r",enable);

    ret = boudica120_atcmd(cmd,"OK");

    return ret;
}

/*  bc95 can't use "\r\n+QLWEVTIND:" to check whether  join cdp 	server is successful or unsuccessful.
 * we can send "AT+NMGS="  to check.
 */
static bool_t boudica120_check_platform_register(int time)  //unit second
{
    //wait for the server observed
    bool_t ret = false;
    int times;
	char *cmd = "AT+NMGS=2,3232\r";	//use for check cdp register status

    for(times =0;times <time;times++ )
    {
		ret = boudica120_atcmd(cmd,"OK");
        if(ret)
        {
            ret = true;
            break;
        }
        osal_task_sleep(1000);
    }

    return ret;



}





//check if attached to the network
static bool_t boudica120_check_netattach(int time)  //unit second
{
    //wait for the server observed
    bool_t ret = false;
    int times;

    for(times =0;times <time;times++ )
    {
        if(boudica120_atcmd("AT+CGATT?\r", "CGATT:1"))
        {
            ret = true;
            break;
        }
        osal_task_sleep(1000);
    }

    return ret;
}

//set the autoconfig mode
static bool_t boudica120_set_autoconnect(int enable)
{
    char cmd[64];
    char resp[64];
    bool_t ret = true;
    const char *mode;

    if(enable)
    {
        mode = "AUTOCONNECT,TRUE";
    }
    else
    {
        mode = "AUTOCONNECT,FALSE";
    }

    (void) memset(resp,0,64);
    ret = boudica120_atcmd_response("AT+NCONFIG?\r","+NCONFIG",resp,64);
    if((false == ret)||(NULL == strstr(resp,mode)))//which means we need to set it
    {
        (void) memset(cmd,0,64);
        (void) snprintf(cmd,64,"AT+NCONFIG=%s\r",mode);
        ret = boudica120_atcmd(cmd,"OK");

        boudica120_reboot();
    }
    else
    {
        ret = true;  //we need not to set
    }

    return ret;
}

//use this function to set the band,which corresponding with YUNYINGSHANG AND MOZU
static bool_t boudica120_boot(const char *plmn, const char *apn, const char *bands,const char *server,const char *port)
{
    //(void) memset(&s_boudica120_oc_cb,0,sizeof(s_boudica120_oc_cb));

    at_oobregister("boudica120rcv",cn_boudica120_rcvindex,strlen(cn_boudica120_rcvindex),boudica120_rcvdeal,NULL);

    while(1)
    {


        boudica120_reboot();

        boudica120_set_echo (0);

        boudica120_set_cmee(1);

        boudica120_set_autoconnect(0);     //cgatt and cfun must be called if autoconnect is false

        boudica120_set_bands(bands);

        boudica120_set_fun(1);

        //boudica120_set_plmn(plmn);

        boudica120_set_apn(apn);

        boudica120_set_cdp(server,port);

        boudica120_set_cgatt(1);

        boudica120_set_nnmi(1);

        if(false == boudica120_check_netattach(16))
        {
            continue;
        }

        if(false == boudica120_check_platform_register(16)) //TODO--maybe this only compatible with QUETEL MODULES
        {
            continue; //we should do the reboot for the nB
        }

        break;
    }
   //reach here means everything is ok, we can go now
    s_boudica120_oc_cb.sndenable = true;
    LINK_LOG_DEBUG("NB MODULE RXTX READY NOW\n\r");
    return true;
}


static int* boudica120_oc_config(oc_config_param_t *param)
{
    int ret = en_oc_coap_err_configured;

    if(NULL == param)
    {
        ret = en_oc_coap_err_parafmt;
		LINK_LOG_DEBUG("en_oc_coap_err_parafmt");
        return NULL;
    }

    if(NULL == s_oc_handle)
    {
        s_boudica120_oc_cb.oc_param = *param;

        if(boudica120_boot(s_boudica120_oc_cb.plmn,s_boudica120_oc_cb.apn,s_boudica120_oc_cb.bands,\
                s_boudica120_oc_cb.oc_param.app_server.address,s_boudica120_oc_cb.oc_param.app_server.port))
        {
            s_oc_handle = &s_boudica120_oc_cb;
            ret = en_oc_coap_err_ok;
			LINK_LOG_DEBUG("en_oc_coap_err_ok");
        }
        else
        {
			LINK_LOG_DEBUG("en_oc_coap_err_network");
            return NULL;
        }
    }

    return s_oc_handle;
}

static int boudica120_oc_deconfig(void *handle)
{
    int ret = en_oc_coap_err_noconfigured;

    if(NULL != handle)
    {
        handle = NULL;
        ret = en_oc_coap_err_ok;
    }
    return ret;
}


//this function to get the csq
int boudica120_get_csq(int *value)
{
    char cmd[64];
    char resp[64];
    const char *index = "OK";
    const char *str;
    int csq = 0;
    int ret = -1;

    if(NULL == value)
    {
        return ret;
    }

    (void) memset(cmd,0,64);
    (void) memset(resp,0,64);
    (void) snprintf(cmd,64,"AT+CSQ\r");
    if(boudica120_atcmd_response(cmd,index,resp,64))
    {
        str = strstr((char *)resp,"+CSQ:");
        if(NULL != str)
        {
            str += strlen("+CSQ:");
            for (; *str <= '9' && *str >= '0' ;str++)
            {
                csq = (csq * 10 + (*str - '0'));
            }
            if(csq != 99) //99 is invalid
            {
                *value = csq;
                ret = 0;
            }
        }
    }
    return ret;
}

int* boudica120_check_nuestats(void)
{
    char cmd[64];
    char resp[256];
    char *str;

    (void) memset(cmd,0,64);
    (void) memset(resp,0,64);
    (void) snprintf(cmd,64,"AT+NUESTATS=CELL\r");

    if (boudica120_atcmd_response(cmd,"NUESTATS:",resp,256) < 0)
    {
    	return NULL;
    }
    str = strstr(resp,"NUESTATS:");
    if (str == NULL)
    {
    	return NULL;
    }
    int earfcn, physical_cellid, primary_cell, rsrp, rsrq, rssi, snr;  //for now only rsrp is needed, others for future use
    sscanf(str,"NUESTATS:CELL,%d,%d,%d,%d,%d,%d,%d",&earfcn, &physical_cellid, &primary_cell, &rsrp, &rsrq, &rssi, &snr);
    wireless_stats[0] = rsrp;

    (void) memset(cmd,0,64);
    (void) snprintf(cmd,64,"AT+NUESTATS\r");
    if (boudica120_atcmd_response(cmd,"OK",resp,256) < 0)
    {
        return NULL;
    }
    str = strstr(resp,"ECL:");
    if (str == NULL)
    {
    	return NULL;
    }
    sscanf(str,"ECL:%d",&wireless_stats[1]);

    str = strstr(resp,"SNR:");
    if (str == NULL)
    {
        return NULL;
    }
    sscanf(str,"SNR:%d",&wireless_stats[2]);

    str = strstr(resp,"Cell ID:");
    if (str == NULL)
    {
        return NULL;
    }
    sscanf(str,"Cell ID:%d",&wireless_stats[3]);

    return wireless_stats;
}

const oc_coap_opt_t  g_boudica120_oc_opt = \
{
    .config = boudica120_oc_config,
    .deconfig = boudica120_oc_deconfig,
    .report = (fn_oc_coap_report)boudica120_oc_report,
};


#ifndef CONFIG_BOUDICA120_PLMN
#define CONFIG_BOUDICA120_PLMN  "460001"
#endif


#ifndef CONFIG_BOUDICA120_APN
#define CONFIG_BOUDICA120_APN   "cmnet"
#endif


#ifndef CONFIG_BOUDICA120_BANDS
#define CONFIG_BOUDICA120_BANDS  "5"	
#endif

int oc_coap_imp_init(void)
{
    int ret = -1;

    s_boudica120_oc_cb.plmn = NULL;
    s_boudica120_oc_cb.apn = NULL;
    s_boudica120_oc_cb.bands = CONFIG_BOUDICA120_BANDS;

    osal_mutex_create(&s_report_mutex);

    ret = oc_coap_register("boudica120",&g_boudica120_oc_opt);

    return ret;
}


