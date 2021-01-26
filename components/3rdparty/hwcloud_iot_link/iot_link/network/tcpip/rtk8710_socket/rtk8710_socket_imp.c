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
#include <unistd.h>


#include <sal.h>


#include <sal_imp.h>
#include <sal_define.h>
#include <sal_types.h>
#include <at.h>
#include <link_misc.h>
#include <link_endian.h>
#include <osal.h>

#define cn_rtk8710_cmd_timeout   (5*1000)
#define cn_rtk8710_rcvindex      "RSP"
#define cn_rtk8710_cachelen      (1024 * 2)

#define WIFI_SSID     "TP-LINK_IOT_LINK"
#define WIFI_PASSWD   "iotlink_2019"

typedef enum
{
    STA = 1,
    AP,
    STA_AP,
}enum_net_mode;

typedef struct
{
    int sockfd;
    int domain;
    int type;
    int protocol;
    uint16_t remote_port;
    char remote_ip[20];

    tag_ring_buffer_t rtk8710_rcvring;
    unsigned char rtk8710_rcvbuf[cn_rtk8710_cachelen];

    unsigned int timeout;

    char oob_resp[1024];

    int isconnect;
}rtk8710_sock_cb_t;

static rtk8710_sock_cb_t s_rtk8710_sock_cb;

//rtk8710 common at command
static bool_t rtk8710_atcmd(const char *cmd,const char *index)
{
    int ret = 0;
    ret = at_command((unsigned char *)cmd,strlen(cmd),index,NULL,0,cn_rtk8710_cmd_timeout);
    if(ret >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//at command  with response
static bool_t rtk8710_atcmd_response(const char *cmd,const char *index,char *buf, int len)
{
    int ret = 0;
    ret = at_command((unsigned char *)cmd,strlen(cmd),index,(char *)buf,len,cn_rtk8710_cmd_timeout);
	//LINK_LOG_DEBUG("atcmd rep:%d\r\n", ret);
    if(ret >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


static int rtk8710_rcvdeal(void *args,void *msg,size_t len)
{
    int ret = -1;
    unsigned short datalen;
    char *data;
    char  *str;
    unsigned short ringspace;

    //LINK_LOG_DEBUG("call oob rvdeal len:%d\r\n", len);


    data = msg;
    if(len <strlen(cn_rtk8710_rcvindex) || len > cn_rtk8710_cachelen)
    {
        LINK_LOG_DEBUG("%s:invalid frame:%d byte:%s\n\r",__FUNCTION__,len,(char *)data);
        return ret;
    }

    //if(strstr((char *)data, "CLOSED") != NULL)
    //{
    //    (void)rtk8710_boot();
    //    return ret;
    //}
    //now deal the data
    str = strstr((char *)data,",");
    if(NULL == str)
    {
        LINK_LOG_DEBUG("%s:format error\n\r",__FUNCTION__);
        return ret; //format error
    }
    str++;
	
    str = strstr((char *)str,",");
    if(NULL == str)
    {
        LINK_LOG_DEBUG("%s:format error\n\r",__FUNCTION__);
        return ret; //format error
    }
    str++;
	
    str = strstr((char *)str,",");
    if(NULL == str)
    {
        LINK_LOG_DEBUG("%s:format error\n\r",__FUNCTION__);
        return ret; //format error
    }
    str++;
	
    str = strstr((char *)str,",");
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
    //LINK_LOG_DEBUG("datalen:%d~~~~~~\r\n", datalen);
    //LINK_LOG_DEBUG("@@@@:%d\r\n", str-data);
    if(datalen + (str-data) + 1 + strlen("\r\n") > len)
        return ret;
    str = strstr((char *)str,",");
    if(NULL == str)
    {
        LINK_LOG_DEBUG("%s:format error\n\r",__FUNCTION__);
        return ret; //format error
    }
    str++;

    //now this is data payload
    if(datalen > (cn_rtk8710_cachelen - ring_buffer_datalen(&s_rtk8710_sock_cb.rtk8710_rcvring)))
    {
    	return 0;
    }

    if(s_rtk8710_sock_cb.type == SOCK_DGRAM)
    {
    	ret = ring_buffer_write(&s_rtk8710_sock_cb.rtk8710_rcvring,(unsigned char *)&datalen,sizeof(datalen));
        ret = ring_buffer_write(&s_rtk8710_sock_cb.rtk8710_rcvring,str,datalen);
    }
    else if (s_rtk8710_sock_cb.type == SOCK_STREAM)
    {
        ret = ring_buffer_write(&s_rtk8710_sock_cb.rtk8710_rcvring,str,datalen);
    }

    //LINK_LOG_DEBUG("rcv deal:%d\r\n", ret);
    return ret;

}



static int rtk8710_socket(int domain, int type, int protocol)
{
    s_rtk8710_sock_cb.domain = domain;
    s_rtk8710_sock_cb.type = type;
    s_rtk8710_sock_cb.protocol = protocol;
    s_rtk8710_sock_cb.sockfd = 0;
    s_rtk8710_sock_cb.remote_port = 0;
    (void) memset(s_rtk8710_sock_cb.remote_ip,0,sizeof(s_rtk8710_sock_cb.remote_ip));

    return s_rtk8710_sock_cb.sockfd;
}

static int __rtk8710_bind(int fd, const struct sockaddr *addr, int addrlen)
{
	//not implemented for client
    return 0;
}

static int rtk8710_listen(int fd, int backlog)
{
	//not implemented for client
    return 0;
}

static int __rtk8710_accept(int fd, struct sockaddr *addr, int addrlen)
{
	//not implemented for client
    return 0;
}

//static int __rtk8710_connect(int fd, const struct sockaddr *addr, int addrlen)
static int __rtk8710_connect(int fd, void *addr, int addrlen)
{
    char cmd[64];
    char resp[64];
    int ret = -1;
    char *str;
    char *remote_ip;
    struct sockaddr_in *serv_addr; 

    if(NULL != addr)
    {
        
        (void) memset(cmd,0,64);

        
        serv_addr = (struct sockaddr_in *)addr;
        uint16_t remote_port = ntohs(serv_addr->sin_port);
        struct in_addr remote_ip_int = serv_addr->sin_addr;
        remote_ip = inet_ntoa(remote_ip_int);
        (void) memcpy(s_rtk8710_sock_cb.remote_ip, remote_ip, strlen(remote_ip));
        s_rtk8710_sock_cb.remote_port = remote_port;

        if(s_rtk8710_sock_cb.type == SOCK_DGRAM)
        {
            snprintf(cmd,64,"AT+NWKCUDP=CLIENT,%s,%d,1\r\n",remote_ip,remote_port);
        }
        else if(s_rtk8710_sock_cb.type == SOCK_STREAM)
        {
            snprintf(cmd,64,"AT+NWKCTCP=CLIENT,0,%s,%d\r\n",remote_ip,remote_port);
        }
        else return ret;

        if(s_rtk8710_sock_cb.type == SOCK_DGRAM)
        {
            if(rtk8710_atcmd_response(cmd,"[NWKCUDP_ID]",resp,64))
            {
                ret = 0;
            }
        }
        else if(s_rtk8710_sock_cb.type == SOCK_STREAM)
        {
            if(rtk8710_atcmd_response(cmd,"[NWKCTCP_ID]",resp,64))
            {
                ret = 0;
            }
        }

        str = resp;
        str = strstr(resp,"]");
        str++;

        s_rtk8710_sock_cb.sockfd = atoi(str);
        s_rtk8710_sock_cb.isconnect = 1;
    }
    return ret;
}

static int rtk8710_send(int fd, const void *buf, int len, int flags)
{
    char cmd[64];
    char rsp[64];
    int ret = -1, i;

    if(NULL != buf)
    {
        (void) memset(cmd,0,64);
        (void) memset(s_rtk8710_sock_cb.oob_resp,0,1024);

        if(s_rtk8710_sock_cb.type == SOCK_DGRAM)
        {
            snprintf(cmd,64,"AT+NWKUDPSEND=%d,%s,%d,%d,",s_rtk8710_sock_cb.sockfd,
                     s_rtk8710_sock_cb.remote_ip,s_rtk8710_sock_cb.remote_port,len); //TODO:mux = 1
            if(rtk8710_atcmd(cmd,NULL))
            {
                ret = at_command((unsigned char *)buf,len,NULL,NULL,0,cn_rtk8710_cmd_timeout);
                ret = rtk8710_atcmd_response("\r\n","[NWKUDPSEND]OK\r\n",rsp,64);
            }
        }
        else if(s_rtk8710_sock_cb.type == SOCK_STREAM)
        {
            snprintf(cmd,64,"AT+NWKTCPSEND=%d,%d,",s_rtk8710_sock_cb.sockfd,len); //TODO:mux = 1
            if(rtk8710_atcmd(cmd,NULL))
            {
                ret = at_command((unsigned char *)buf,len,NULL,NULL,0,cn_rtk8710_cmd_timeout);
                ret = rtk8710_atcmd_response("\r\n","[NWKTCPSEND]OK\r\n",rsp,64);
            }
        }
        else return ret;
    }
    if(ret > 0)
    {
    	ret = len;
    }
    return ret;
}
static int __rtk8710_sendto(int fd, const void *msg, int len, int flags, struct sockaddr *addr, int addrlen)
{
	if (!s_rtk8710_sock_cb.isconnect)
	{
		__rtk8710_connect(fd,addr,addrlen);
	}
    return rtk8710_send(fd,msg,len,flags);
}

static int rtk8710_recv(int fd,void *buf,size_t len,int flags)
{
    int ret = -1;
    osal_loop_timer_t sock_timer;

    osal_loop_timer_init(&sock_timer);
    osal_loop_timer_count_downms(&sock_timer,s_rtk8710_sock_cb.timeout);

    while (0 == osal_loop_timer_expired(&sock_timer))
    {
    	if(s_rtk8710_sock_cb.type == SOCK_DGRAM)
    	{
    		unsigned short framelen = 0;
    		ret = ring_buffer_read(&s_rtk8710_sock_cb.rtk8710_rcvring,(unsigned char *)&framelen,sizeof(framelen));
    		ret = ring_buffer_read(&s_rtk8710_sock_cb.rtk8710_rcvring,(unsigned char *)buf,framelen);
    		if(ret > 0)
    		{
    			break;
    		}
    	}
    	else if (s_rtk8710_sock_cb.type == SOCK_STREAM)
    	{
    		ret = ring_buffer_read(&s_rtk8710_sock_cb.rtk8710_rcvring,(unsigned char *)buf,len);
    		if(ret > 0)
    		{
    		    break;
    		}
    	}
    	osal_task_sleep(1);
    }


	if(0 == ret)
	{
		return -1;
	}
	else return ret;
}

static int __rtk8710_recvfrom(int fd, void *msg, int len, int flags, struct sockaddr *addr, socklen_t *addrlen)
{
    return rtk8710_recv(fd,msg,len,flags);
}


static int __rtk8710_setsockopt(int fd, int level, int option, const void *option_value, int option_len)
{
	//TODO:MUX=1
	//struct timeval *timedelay = (struct timeval *)osal_malloc(sizeof(struct timeval));
	struct timeval *timedelay;// = (struct timeval *)osal_malloc(sizeof(struct timeval));
	timedelay = (struct timeval *)option_value;
	s_rtk8710_sock_cb.timeout = (timedelay->tv_sec * 1000) + (timedelay->tv_usec / 1000);
    return 0;
}

static int rtk8710_getsockopt(int fd, int level, int optname, const void *optval, int optlen)
{
	//not implemented
    return 0;
}

static int rtk8710_close(int fd)
{
    char cmd[64];
    int ret = -1;
    (void) memset(cmd,0,64);
    snprintf(cmd,64,"AT+NWKCLOSE=%d\r\n",s_rtk8710_sock_cb.sockfd);//TODO: MUX = 1;
    if(rtk8710_atcmd(cmd,"[NWKCLOSE]OK"))
    {
        ret = 0;
        s_rtk8710_sock_cb.isconnect = 0;
    }
    return ret;
}

static int rtk8710_shutdown(int fd, int how)
{
	return rtk8710_close(fd);
}

static int rtk8710_getsockname(int fd, struct sockaddr *addr,socklen_t *addrlen)
{
    //not implemented
    return 0;
}

static int rtk8710_getpeername(int fd, struct sockaddr *addr,socklen_t *addrlen)
{
    //not implemented
    return 0;
}

static struct hostent s_rtk8710_hostent;
static uint8_t        s_rtk8710_ipv4_addr[4];
static char          *s_rtk8710_ipv4_lst[2];    ///< must be 2 or more because it terminated by NULL
static struct hostent *rtk8710_gethostbyname(const char *name)
{
	char cmd[64];
	char resp[64];

	int ipv4[4];
	int fmt_num;

	char *str;
	struct in_addr *serv_ip;
	struct hostent *hptr = NULL;
	int ret = -1;
    hptr = &s_rtk8710_hostent;
    (void) memset(hptr,0,sizeof(struct hostent));

	(void) memset(cmd,0,64);
	snprintf(cmd,64,"AT+NWKDNS=%s\r\n",name);
	if(false == rtk8710_atcmd_response(cmd,"\r\n",resp,64))
	{
		//name is ip address already
		LINK_LOG_DEBUG("name is ip\r\n");
		sscanf(name,"%d.%d.%d.%d",&hptr->h_addr_list[0][0],&hptr->h_addr_list[0][1],&hptr->h_addr_list[0][2],&hptr->h_addr_list[0][3]);
		return hptr;
	}
	str = resp;
	fmt_num = sscanf(str,"%d.%d.%d.%d",&ipv4[0],&ipv4[1],&ipv4[2],&ipv4[3]);
	if(fmt_num > 0)
	{
		hptr->h_addrtype = AF_INET;
		hptr->h_length = 4;
		s_rtk8710_ipv4_addr[0] = ipv4[0];
		s_rtk8710_ipv4_addr[1] = ipv4[1];
		s_rtk8710_ipv4_addr[2] = ipv4[2];
		s_rtk8710_ipv4_addr[3] = ipv4[3];
	
		s_rtk8710_ipv4_lst[0] = (char *)&s_rtk8710_ipv4_addr[0];
		s_rtk8710_ipv4_lst[1] = NULL;
	
		hptr->h_addr_list = &s_rtk8710_ipv4_lst[0];
		return hptr;
	}
	else
	{
		return NULL;
	}

    return hptr;
}

static const tag_tcpip_ops s_tcpip_socket_ops =
{
   .socket = (fn_sal_socket)rtk8710_socket,
   .bind = (fn_sal_bind)__rtk8710_bind,
   .listen = (fn_sal_listen)rtk8710_listen,
   .connect = (fn_sal_connect)__rtk8710_connect,
   .accept = (fn_sal_accept)__rtk8710_accept,
   .send = (fn_sal_send)rtk8710_send,
   .sendto = (fn_sal_sendto)__rtk8710_sendto,
   .recv = (fn_sal_recv)rtk8710_recv,
   .recvfrom = (fn_sal_recvfrom)__rtk8710_recvfrom,
   .setsockopt = (fn_sal_setsockopt)__rtk8710_setsockopt,
   .getsockopt = (fn_sal_getsockopt)rtk8710_getsockopt,
   .shutdown =(fn_sal_shutdown)rtk8710_shutdown,
   .closesocket =(fn_sal_closesocket)rtk8710_close,
   .getpeername =(fn_sal_getpeername)rtk8710_getpeername,
   .getsockname = (fn_sal_getsockname)rtk8710_getsockname,
   .gethostbyname = (fn_sal_gethostbyname)rtk8710_gethostbyname,
};

static const tag_tcpip_domain s_tcpip_socket =
{
    .name = "rtk8710 socket",
    .domain = AF_INET,
    .ops = &s_tcpip_socket_ops,
};


static bool_t rtk8710_reset(void)
{
    return rtk8710_atcmd("AT+RST\r\n","[RST]OK");
}



static bool_t rtk8710_set_mode(enum_net_mode mode)
{
	char cmd[64];
	(void) memset(cmd,0,64);
	snprintf(cmd,64,"AT+WLMODE=%d\r\n",(int)mode);
	return rtk8710_atcmd(cmd,"[WLMODE]OK");
}

static bool_t rtk8710_joinap(char *ssid, char *passwd)
{
	char cmd[64];
	(void) memset(cmd,0,64);
    snprintf(cmd,64,"AT+WLSTAPARAM=\"%s\",\"%s\"\r\n",ssid, passwd);
    if(rtk8710_atcmd(cmd,"[WLSTAPARAM]OK"))
    {
        snprintf(cmd,64,"AT+WLSETUP\r\n");
        return rtk8710_atcmd(cmd,"[WLSETUP]OK");
    }
}

static bool_t rtk8710_ver()
{
	char cmd[64];
	(void) memset(cmd,0,64);
    snprintf(cmd,64,"AT+SVER\r\n");
    return rtk8710_atcmd(cmd,"OK");

}


int link_tcpip_imp_init(void)
{
    int ret = -1;

    at_oobregister("rtk8710rcv",cn_rtk8710_rcvindex,strlen(cn_rtk8710_rcvindex),rtk8710_rcvdeal,NULL);
    at_streammode_set(1);
    ring_buffer_init(&s_rtk8710_sock_cb.rtk8710_rcvring,s_rtk8710_sock_cb.rtk8710_rcvbuf,cn_rtk8710_cachelen,0,0);

    rtk8710_reset();
    //rtk8710_ver();
    rtk8710_set_mode(STA);

    while(false == rtk8710_joinap(WIFI_SSID, WIFI_PASSWD))
    {
        LINK_LOG_DEBUG("connect ap failed, repeat...\r\n");
    }
    //reach here means everything is ok, we can go now

    ret = link_sal_install(&s_tcpip_socket);

    if(0 == ret)
    {
        LINK_LOG_DEBUG("sal:install socket success\r\n");
    }
    else
    {
        LINK_LOG_DEBUG("sal:install socket failed\r\n");
    }

    return ret;
}
