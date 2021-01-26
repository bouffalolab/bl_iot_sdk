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

#include "sal.h"
#include "sinn_sec_socket.h"
#include "sinn_if_cbs.h"

static void __sinn_sock_init(sinn_if_t *interface)
{
    (void)interface;
    LINK_LOG_DEBUG(" using select()\r\n");
}

static void __sinn_sock_uninit(sinn_if_t *interface)
{
    (void)interface;
}

#define PORT_BUF_LEN 16
static int __sinn_sock_connect(sinn_connection_t *nc)
{
    int rc = -1;

    mbedtls_ssl_context *ssl;
    sinn_ssl_param_t *ssl_param;
    sinn_connect_param_t *conn_param;
    dtls_shakehand_info_s shakehand_info;
    dtls_establish_info_s establish_info;
    char port_buf[PORT_BUF_LEN];

    (void) memset(&shakehand_info, 0, sizeof(dtls_shakehand_info_s));
    conn_param = (sinn_connect_param_t *)(nc->user_data);
    ssl_param = &conn_param->ssl_param;
    if (ssl_param->type == e_sinn_ssl_type_psk)
    {
        establish_info.psk_or_cert = VERIFY_WITH_PSK;
        establish_info.v.p.psk =(const unsigned char *) ssl_param->u.psk.psk;
        establish_info.v.p.psk_len = ssl_param->u.psk.psk_len;
        establish_info.v.p.psk_identity = (unsigned char *)ssl_param->u.psk.psk_id;

        shakehand_info.psk_or_cert = VERIFY_WITH_PSK;
    }
    else if (ssl_param->type == e_sinn_ssl_type_unica)
    {
        establish_info.psk_or_cert = VERIFY_WITH_CERT;
        establish_info.v.c.ca_cert = (const unsigned char *)ssl_param->u.uni_ca.ca_cert;
        establish_info.v.c.cert_len = ssl_param->u.uni_ca.ca_cert_len;
        shakehand_info.psk_or_cert = VERIFY_WITH_CERT;
    }
    establish_info.udp_or_tcp = MBEDTLS_NET_PROTO_TCP;

    ssl = (void *)dtls_ssl_new(&establish_info, MBEDTLS_SSL_IS_CLIENT);
    if (NULL == ssl)
    {
        return rc;
    }

    shakehand_info.client_or_server = MBEDTLS_SSL_IS_CLIENT;
    shakehand_info.udp_or_tcp = MBEDTLS_NET_PROTO_TCP;
    shakehand_info.u.c.host = nc->server_ip;
    snprintf(port_buf, PORT_BUF_LEN, "%d", nc->server_port);
    shakehand_info.u.c.port = port_buf;

    rc = dtls_shakehand(ssl, &shakehand_info);
    if(!rc)
    {
        mbedtls_net_context *nfd;
        nc->ssl_handler = ssl;
        nc->flags |= SINN_FG_CONNECTING;
        nc->flags |= SINN_FG_CAN_WR | SINN_FG_CAN_RD;
        nfd = (mbedtls_net_context *)(ssl->p_bio);
        nc->sock_fd = nfd->fd;
    }

    return rc;
}

static void __sinn_sock_discon(sinn_connection_t *nc)
{
    int rc = 0;
    LINK_LOG_DEBUG("__sinn_sock_discon\r\n");
    if(nc->sock_fd == -1)
        return;

    rc = sal_closesocket(nc->sock_fd);
    if(rc < 0)
        LINK_LOG_DEBUG("sock %d rc %d \r\n",  nc->sock_fd, rc);

    nc->sock_fd = -1;
}


static sinn_time_t __sinn_sock_poll(sinn_connection_t *nc, int timeout_ms)
{
    sinn_time_t now;
    fd_set rfds, wfds, efds;
    struct timeval tv;
    int max_fd = -1;
    int rc = 0;

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_ZERO(&efds);

    if(!(nc->flags & SINN_FG_RECONNECT))
        FD_SET(nc->sock_fd, &rfds);
    if(nc->send_buf.len > 0)
    {
        FD_SET(nc->sock_fd, &wfds);
        FD_SET(nc->sock_fd, &efds);
    }

    max_fd = nc->sock_fd;

    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    rc = sal_select(max_fd + 1, &rfds, &wfds, &efds, &tv);
    now = sinn_gettime_ms();

    if(rc == -1)
    {
        LINK_LOG_DEBUG("select() error\r\n");
        return 0;
    }
    else if(rc > 0)
    {
        if(FD_ISSET(nc->sock_fd, &rfds)) {nc->flags |= SINN_FG_CAN_RD;}
        if(FD_ISSET(nc->sock_fd, &wfds)) {nc->flags |= SINN_FG_CAN_WR;}
        if(FD_ISSET(nc->sock_fd, &efds)) {nc->flags |= SINN_FG_ERR;}
    }

    sinn_mgr_handle_conn(nc);

    return now;
}

static int __sinn_sock_send(sinn_connection_t *nc, const void *buf, size_t len)
{
    int ret= -1;
    int sndlen = -1;

    if(NULL == nc->ssl_handler || NULL == buf)
    {
        return -1;
    }

    sndlen = dtls_write(nc->ssl_handler, buf, len);

    if(sndlen == 0)
    {
        ret = -1;
    }
    else if(sndlen < 0)
    {
        ret = 0;
    }
    else
    {
        ret = sndlen;
    }

    return ret;
}

static int __sinn_sock_recv(sinn_connection_t *nc, void *buf, size_t len)
{
    int ret= -1;
    int rcvlen = -1;

    if(NULL == nc->ssl_handler || NULL == buf)
    {
        return -1;
    }

    rcvlen = dtls_read(nc->ssl_handler,buf,len, 1000);

    if(rcvlen == 0)
    {
        ret = -1;
    }
    else if(rcvlen < 0)
    {
        ret = 0;
    }
    else
    {
        ret = rcvlen;
    }

    return ret;
}

sinn_if_funcs_t sinn_sec_if =
{
    __sinn_sock_init,
    __sinn_sock_uninit,
    __sinn_sock_connect,
    __sinn_sock_discon,
    __sinn_sock_poll,
    __sinn_sock_send,
    __sinn_sock_recv,
};
