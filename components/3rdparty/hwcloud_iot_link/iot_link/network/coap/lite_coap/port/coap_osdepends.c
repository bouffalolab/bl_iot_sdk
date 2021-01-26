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
 * include those applicable to Huawei LiteOS of CHN and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#ifdef WITH_DTLS
#include "dtls_interface.h"
#endif

#include <stdlib.h>
#include <sal.h>
#include <osal.h>
#include "litecoap.h"
#include "coap_core.h"
#include "litecoap_err.h"

#define RANDOM_TOKEN_LEN 8

int litecoap_sal_send(void *handle, char *buf, int size);
int litecoap_sal_read(void *handle, char *buf, int size);

struct udp_res_t
{
    int                   fd;// socket fd
    struct sockaddr_in    remoteAddr;

    void*                 ssl;
};

/* coap recive and send function callback */
struct udp_ops network_ops = 
{
    .network_read = litecoap_sal_read,
    .network_send = litecoap_sal_send
};

/*****************************************************************************
 Function    : litecoap_get_random
 Description : generate a ramdon data 
 Input       : None
 Output      : None
 Return      : ret @ 32bit random data.
 *****************************************************************************/
static unsigned int litecoap_get_random(void)
{
	unsigned int ret;
	srand((unsigned long long)osal_sys_time());
	ret = rand() % RAND_MAX;
	return ret;
}

/*****************************************************************************
 Function    : litecoap_generate_token
 Description : generate a ramdon token for coap message. 
 Input       : None
 Output      : token @ token buf that used to store token
 Return      : RANDOM_TOKEN_LEN @ token length.
 *****************************************************************************/
int litecoap_generate_token(unsigned char *token)
{
	unsigned int ret;
	srand((unsigned)osal_sys_time());
	ret = rand() % RAND_MAX;
    token[0] = (unsigned char)ret;
    token[1] = (unsigned char)(ret>>8);
    token[2] = (unsigned char)(ret>>16);
    token[3] = (unsigned char)(ret>>24);
	return RANDOM_TOKEN_LEN;
}

/*****************************************************************************
 Function    : litecoap_malloc
 Description : malloc memory from mempool 
 Input       : size @ the length that want to malloc from mempool.
 Output      : None
 Return      : tmp @ malloced buf's pointer.
 *****************************************************************************/
void *litecoap_malloc(int size)
{
    void *ret = NULL;
    if (size <= 0)
    {
        return NULL;
    }

    ret = osal_malloc(size);
    return ret;
}

/*****************************************************************************
 Function    : litecoap_free
 Description : free memory from mempool 
 Input       : p @ memory that want to free.
 Output      : None
 Return      : LITECOAP_OK free ok, other value means failed.
 *****************************************************************************/
int litecoap_free(void *p)
{
    if (NULL == p)
	{
		return LITECOAP_PARAM_NULL;
	}

    osal_free(p);
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_check_validip
 Description : check if the ip address if valid ip address 
 Input       : ipaddr @ string format ip address that need to check.
 Output      : None
 Return      : LITECOAP_OK means valid, other means invalid.
 *****************************************************************************/
static int litecoap_check_validip(char *ipaddr)
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int ret = 0;
    if(NULL == ipaddr)
    {
        return LITECOAP_PARAM_NULL;
    }
    ret = sscanf(ipaddr, "%d.%d.%d.%d", &a,&b,&c,&d);
    if (ret != 4)
    {
        return LITECOAP_SOCKET_ADDRCHK_ERR;
    }
    if ((a >= 0 && a <= 255)
        && (b >=0 && b <= 255)
        && (c >=0 && c <= 255)
        && (d >=0 && d <= 255))
    {
        return LITECOAP_OK;
    }
    return LITECOAP_SOCKET_ADDRCHK_ERR;
}

/*****************************************************************************
 Function    : litecoap_new_resource
 Description : create socket resource for coap connection
 Input       : ipaddr @ remote endpoint or server's ipaddress
               port @ remote  endpoint or server's port number
 Output      : None
 Return      : tmp @ socket resource's pointer
 *****************************************************************************/
void *litecoap_new_resource(char *ipaddr, unsigned short port, void *ssl, coap_proto_t proto)
{
    int ret = 0;
    struct udp_res_t *tmp = NULL;
    struct sockaddr_in localaddr;
    if (NULL == ipaddr)
    {
        return NULL;
    }
    ret = litecoap_check_validip(ipaddr);
    if (ret != LITECOAP_OK)
    {
        return NULL;
    }

    tmp = osal_malloc(sizeof(struct udp_res_t));
    if (NULL == tmp)
    {
        return NULL;
    }
    (void) memset(tmp, 0, sizeof(struct udp_res_t));
    if (proto == COAP_PROTO_UDP) {
        tmp->fd = sal_socket(AF_INET, SOCK_DGRAM, 0);
    } else {
        tmp->fd = sal_socket(AF_INET, SOCK_STREAM, 0);
    }
    if (tmp->fd < 0)
    {
        osal_free(tmp);
        return NULL;
    }

    tmp->remoteAddr.sin_addr.s_addr = inet_addr((const char *)ipaddr);
    tmp->remoteAddr.sin_port = htons(port);
    tmp->remoteAddr.sin_family = AF_INET;

    sal_connect(tmp->fd, &tmp->remoteAddr, sizeof(tmp->remoteAddr));

    tmp->ssl = ssl;

    return (void *)tmp;
}

/*****************************************************************************
 Function    : litecoap_delete_resource
 Description : release upd resource
 Input       : res @ udp resource pointer
 Output      : None
 Return      : LITECOAP_OK means free ok. other means free failed.
 *****************************************************************************/
int litecoap_delete_resource(void *res)
{
    struct udp_res_t *tmp = NULL;
    if (NULL == res)
	{
		return LITECOAP_PARAM_NULL;
	}
    tmp = (struct udp_res_t *)res;
    if (tmp->fd >= 0)
    {
    	sal_closesocket(tmp->fd);
        tmp->fd = -1;
    }

    osal_free(tmp);
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_malloc_context
 Description : malloc a coap connection and init it.
 Input       : res @ udp resource's pointer.
 Output      : None
 Return      : tmp @ coap connection's pointer.
 *****************************************************************************/
coap_context_t *litecoap_malloc_context(void *res)
{
	coap_context_t *tmp = NULL;
	if (NULL == res)
	{
		return NULL;
	}
	
	tmp = osal_malloc(sizeof(coap_context_t));
	if (NULL == tmp)
	{
		return NULL;
	}
    (void) memset(tmp, 0, sizeof(coap_context_t));
	
	/* FIXED ME */
	tmp->udpio = res;
	
	tmp->sndbuf.buf = osal_malloc(LITECOAP_CONSTRAINED_BUF_SIZE);
	if (NULL == tmp->sndbuf.buf)
	{
		osal_free(tmp);
		return NULL;
	}
	tmp->sndbuf.len = LITECOAP_CONSTRAINED_BUF_SIZE;
	
	tmp->rcvbuf.buf = osal_malloc(LITECOAP_CONSTRAINED_BUF_SIZE);
	if (NULL == tmp->rcvbuf.buf)
	{
		osal_free(tmp->sndbuf.buf);
		osal_free(tmp);
		return NULL;
	}
    
	tmp->rcvbuf.len = LITECOAP_CONSTRAINED_BUF_SIZE;
	tmp->msgid = (unsigned short)litecoap_get_random();
    tmp->netops = &network_ops;
    
    tmp->response_handler = NULL;
	return tmp;	
}

/*****************************************************************************
 Function    : litecoap_free_context
 Description : free a coap connection's resource and memory.
 Input       : ctx @ coap connection's pointer.
 Output      : None
 Return      : LITECOAP_OK @ means free ok. other means error happend.
 *****************************************************************************/
int litecoap_free_context(coap_context_t *ctx)
{
	coap_context_t *tmp = ctx;
    send_queue_t *tmpque = NULL;
    
	if (NULL == ctx)
	{
		return LITECOAP_PARAM_NULL;
	}
	if (NULL != tmp->udpio)
    {
        litecoap_delete_resource(tmp->udpio);
        tmp->udpio = NULL;
    }
    while(NULL != ctx->resndque)
    {
        tmpque = ctx->resndque;
        if (NULL != ctx->resndque->msg)
        {
            litecoap_delete_msg(ctx->resndque->msg);
            ctx->resndque->msg = NULL;
        }
        ctx->resndque = ctx->resndque->next;

        osal_free(tmpque);
        tmpque = NULL;
    }
    while(NULL != ctx->sndque)
    {
        tmpque = ctx->sndque;
        if (NULL != ctx->sndque->msg)
        {
            litecoap_delete_msg(ctx->sndque->msg);
            ctx->sndque->msg = NULL;
        }
        ctx->sndque = ctx->sndque->next;

        osal_free(tmpque);
        tmpque = NULL;
    }
    if (NULL != tmp->sndbuf.buf)
    {
    	osal_free(tmp->sndbuf.buf);
        tmp->sndbuf.buf = NULL;
        tmp->sndbuf.len = 0;
    }
    if (NULL != tmp->rcvbuf.buf)
    {
    	osal_free(tmp->rcvbuf.buf);
        tmp->rcvbuf.buf = NULL;
        tmp->rcvbuf.len = 0;
    }
    tmp->netops = NULL;
    tmp->response_handler = NULL;

    osal_free(ctx);
    
	return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_send
 Description : coap send function.
 Input       : handle @ udp resource pointer
               buf @ coap byte stream data
               size @ coap byte stream data's length.
 Output      : None
 Return      : n @ size that send out by tcp/ip stack.
 *****************************************************************************/
int litecoap_sal_send(void *handle, char *buf, int size)
{
    int n = 0;
    struct udp_res_t *res = NULL;
    if (NULL == handle || NULL == buf)
    {
        return LITECOAP_PARAM_NULL;
    }
    res = (struct udp_res_t *)handle;
    if (res->fd < 0)
    {
        return LITECOAP_SOCKET_HANDLER_ERR;
    }
#ifdef WITH_DTLS
    n = dtls_write((mbedtls_ssl_context *)(res->ssl), (unsigned char *)buf, size);
#else
	n = sal_sendto(res->fd,
			buf,
			size,
			0, 
			(struct sockaddr *)&res->remoteAddr,
			sizeof(struct sockaddr_in));
#endif
    return n;
}

/*****************************************************************************
 Function    : litecoap_read
 Description : coap read function.
 Input       : handle @ udp resource pointer
               buf @ used for storing coap byte stream data
               size @ max size that want to read out.
 Output      : None
 Return      : n @ size that read from tcp/ip stack.
 *****************************************************************************/
int litecoap_sal_read(void *handle, char *buf, int size)
{
    struct timeval tv;
    int n = 0;
    struct sockaddr_in fromAddr;
    socklen_t fromLen;
    struct udp_res_t *res = NULL;
    if (NULL == handle || NULL == buf)
    {
        return LITECOAP_PARAM_NULL;
    }
    res = (struct udp_res_t *)handle;
    if (res->fd < 0)
    {
        return LITECOAP_SOCKET_HANDLER_ERR;
    }
    
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    if(sal_setsockopt(res->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        return LITECOAP_SOCKET_SETOPT_ERR;
    }
    
    (void) memset(&fromAddr,0, sizeof(fromAddr));
    fromAddr.sin_family = AF_INET;
    fromAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    fromAddr.sin_port = res->remoteAddr.sin_port;
    fromLen=sizeof(fromAddr);

#ifdef WITH_DTLS
    n = dtls_read((mbedtls_ssl_context *)(res->ssl), (unsigned char *)buf, size, 1000);
#else
    n = sal_recvfrom( res->fd,
                buf, size, 
                0, 
                (struct sockaddr *)&fromAddr, 
                &fromLen );
#endif
    return n;
}

/*****************************************************************************
 Function    : litecoap_delay
 Description : delay function , use this task will sleep xxx ms
 Input       : ms @ the time that need sleep
 Output      : None
 Return      : LITECOAP_OK @ sleep ok.
 *****************************************************************************/
int litecoap_delay(unsigned int ms)
{
    osal_task_sleep(ms);
    return LITECOAP_OK;
}

unsigned long long litecoap_time()
{
    return osal_sys_time();
}
