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

#include "FreeRTOS.h"
#include <task.h> 

#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip/tcpip.h"

#include <sal_imp.h>   ///< register the lwip to sal

/* include */
#include <stdio.h>
#include <stdlib.h>

#include <osal.h>
#include <wifi_mgmr_ext.h>
#include <hal_wifi.h>

char  HWCLOUD_SSID[33]={0};
char  HWCLOUD_PWD[32]={0};
static int wifi_state_hw = WIFI_STATE_UNKNOWN;

static void hwcloud_wifi_sta_connect(char *ssid, char *password)  //
{

    do{

        switch (wifi_state_hw) {
            case WIFI_STATE_UNKNOWN:
                printf("wifi state unknown\r\n");
                printf("huawei cloud connect AP now...\r\n");

                wifi_interface_t wifi_interface;
                wifi_interface = wifi_mgmr_sta_enable();

                wifi_mgmr_sta_connect(wifi_interface, ssid, password, NULL, NULL, 0, 0);
                wifi_mgmr_sta_autoconnect_enable();

                break;
            case WIFI_STATE_IDLE:
                printf("wifi state idle\r\n");
                break;
            case WIFI_STATE_CONNECTING:
                printf("wifi state connecting\r\n");
                break;
            case WIFI_STATE_CONNECTED_IP_GETTING:
                printf("wifi state connected ip getting\r\n");
                break;
            case WIFI_STATE_CONNECTED_IP_GOT:
                printf("wifi state connected ip got\r\n");
                break;
            case WIFI_STATE_DISCONNECT:
                printf("wifi state disconnect\r\n");
                break;
            case WIFI_STATE_WITH_AP_IDLE:
                printf("wifi state with ap idle\r\n");
                break;
            case WIFI_STATE_WITH_AP_CONNECTING:
                printf("wifi state with ap connecting\r\n");
                break;
            case WIFI_STATE_WITH_AP_CONNECTED_IP_GETTING:
                printf("wifi state with ap connected ip getting\r\n");
                break;
            case WIFI_STATE_WITH_AP_CONNECTED_IP_GOT:
                printf("wifi state with ap connected ip got\r\n");
                break;
            case WIFI_STATE_WITH_AP_DISCONNECT:
                printf("wifi state with ap disconnect\r\n");
                break;
            case WIFI_STATE_IFDOWN:
                printf("wifi state ifdown\r\n");
                break;
            case WIFI_STATE_SNIFFER:
                printf("wifi state sniffer\r\n");
                break;
            case WIFI_STATE_PSK_ERROR:
                printf("wifi state psk error\r\n");
                break;
            case WIFI_STATE_NO_AP_FOUND:
                printf("wifi state no ap found\r\n");
                break;
            default:
                break;
            }

    wifi_mgmr_state_get(&wifi_state_hw);
    vTaskDelay(500);
    
    }while(wifi_state_hw != WIFI_STATE_CONNECTED_IP_GOT);

}


///< struct sockaddr and struct sockaddr_in is quit different from the normal defines, so must translate it here
///< something which seems very foolish i think
static int __lwip_bind(int fd, struct sockaddr *addr, int addrlen)
{
    int ret;
    unsigned char buf[2];
    unsigned short family;

    (void) memcpy(&family,addr,2);
    buf[0] = addrlen;
    buf[1] = family;
    (void) memcpy(addr,buf,2);

    ret = lwip_bind(fd,addr,addrlen);

    (void) memcpy(addr,&family,2);  ///< recover the addr--we should not modify the user's information


    return ret;
}

static int __lwip_connect(int fd, struct sockaddr *addr, int addrlen)
{
    int ret;
    unsigned char buf[2];
    unsigned short family;

    (void) memcpy(&family,addr,2);
    buf[0] = addrlen;
    buf[1] = family;
    (void) memcpy(addr,buf,2);

    ret = lwip_connect(fd,addr,addrlen);

    return ret;
}

static int __lwip_accept(int fd, struct sockaddr *addr, socklen_t *addrlen)
{
    int ret;
    unsigned char buf[2];
    unsigned short family;

    ret = lwip_accept(fd, addr, addrlen);

    (void) memcpy(buf,addr,2);
    family = buf[1];
    (void) memcpy(addr,&family,2);

    return ret;
}


static int __lwip_sendto(int fd, const void *msg, int len, int flag, struct sockaddr *addr, int addrlen)
{

    int ret;
    unsigned char buf[2];
    unsigned short family;

    (void) memcpy(&family,addr,2);
    buf[0] = addrlen;
    buf[1] = family;
    (void) memcpy(addr,buf,2);

    ret = lwip_sendto(fd,msg,len,flag,addr,addrlen);
    (void) memcpy(addr,&family,2);  ///< recover the addr--we should not modify the user's information

    return ret;
}

static int __lwip_recvfrom(int fd, void *msg, int len, int flag, struct sockaddr *addr, socklen_t *addrlen)
{

    int ret;
    unsigned char buf[2];
    unsigned short family;

    ret = lwip_recvfrom(fd, msg, len,flag,addr,addrlen);

    (void) memcpy(buf,addr,2);
    family = buf[1];
    (void) memcpy(addr,&family,2);

    return ret;
}


///< map the level and option
static int __lwip_setsockopt(int fd, int level, int option, const void *option_value, int option_len)
{
    struct timeval *time_delay;

    if(level == 0xffff)
    {
        level = SOL_SOCKET;
        if((option == SO_SNDTIMEO) || (option == SO_RCVTIMEO))
        {
            time_delay = (struct timeval *)option_value;
            if((time_delay->tv_sec == 0)&&(time_delay->tv_usec == 0))
            {
                // LINK_LOG_DEBUG("%s:log:::::::timeout should be mapped:::::modified it 1000 us\n\r",__FUNCTION__); 
                time_delay->tv_usec = 1000;
            }
        }

    }

    return setsockopt(fd, level, option, option_value, option_len);
}


static const tag_tcpip_ops s_tcpip_lwip_ops =
{
    .socket = (fn_sal_socket)lwip_socket,
    .bind = (fn_sal_bind)__lwip_bind,
    .listen = (fn_sal_listen)lwip_listen,
    .connect = (fn_sal_connect)__lwip_connect,
    .accept = (fn_sal_accept)__lwip_accept,
    .send = (fn_sal_send)lwip_send,
    .sendto = (fn_sal_sendto)__lwip_sendto,
    .recv = (fn_sal_recv)lwip_recv,
    .recvfrom = (fn_sal_recvfrom)__lwip_recvfrom,
    .setsockopt = (fn_sal_setsockopt)__lwip_setsockopt,
    .getsockopt = (fn_sal_getsockopt)lwip_getsockopt,
    .shutdown =(fn_sal_shutdown) lwip_shutdown,
    .closesocket =(fn_sal_closesocket) lwip_close,
    .getpeername =(fn_sal_getpeername)lwip_getpeername,
    .getsockname = (fn_sal_getsockname)lwip_getsockname,
    .gethostbyname =(fn_sal_gethostbyname)lwip_gethostbyname,
    .select = (fn_sal_select)lwip_select,
};

static const tag_tcpip_domain s_tcpip_lwip =
{
    .name = "lwip",
    .domain = AF_INET,
    .ops = &s_tcpip_lwip_ops,
};

#if 0 //
extern int netdriver_install();
__attribute__((weak)) int netdriver_install()
{
    LINK_LOG_DEBUG("please remember to supply a netdriver---- please\n\r");

    return 0;
}
#endif

int link_tcpip_imp_init(void)
{
    int ret = -1;
    /* Initilialize the LwIP stack with RTOS */
    // tcpip_init(NULL, NULL);

    // (void) netdriver_install(); 
	printf("\n\r%s(%d), Available heap 0x%x\r\n", __FUNCTION__, __LINE__, xPortGetFreeHeapSize());	
	hwcloud_wifi_sta_connect(HWCLOUD_SSID, HWCLOUD_PWD);;  //
	printf("\n\r%s(%d), Available heap 0x%x\r\n", __FUNCTION__, __LINE__, xPortGetFreeHeapSize());	

    ret = link_sal_install(&s_tcpip_lwip);
    LINK_LOG_DEBUG("%s:install ret:%d\n\r",__FUNCTION__,ret);

    return ret;
}
