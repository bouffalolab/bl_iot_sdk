/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2018-2020 THL A29 Limited, a Tencent company. All rights
 reserved.

 * Licensed under the MIT License (the "License"); you may not use this file
 except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software
 distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND,
 * either express or implied. See the License for the specific language
 governing permissions and
 * limitations under the License.
 *
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "qcloud_iot_export_error.h"
#include "qcloud_iot_export_log.h"
#include "qcloud_iot_import.h"

#ifdef COAP_COMM_ENABLED

/* lwIP socket handle start from 0 */
#define LWIP_SOCKET_FD_SHIFT 3

uintptr_t HAL_UDP_Connect(const char *host, unsigned short port)
{
#define NETWORK_ADDR_LEN (16)

    int             ret;
    struct addrinfo hints, *addr_list, *cur;
    int             fd = 0;

    char port_str[6] = {0};
    HAL_Snprintf(port_str, 6, "%d", port);

    memset((char *)&hints, 0x00, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family   = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;

    Log_d("establish tcp connection with server(host=%s port=%s)", STRING_PTR_PRINT_SANITY_CHECK(host), port_str);

    if (getaddrinfo(host, port_str, &hints, &addr_list) != 0) {
        Log_e("getaddrinfo error,errno:%s", STRING_PTR_PRINT_SANITY_CHECK(strerror(errno)));
        return 0;
    }

    for (cur = addr_list; cur != NULL; cur = cur->ai_next) {
        fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
        if (fd < 0) {
            ret = 0;
            continue;
        }

        if (0 == connect(fd, cur->ai_addr, cur->ai_addrlen)) {
            ret = fd + LWIP_SOCKET_FD_SHIFT;
            break;
        }

        close(fd);
        ret = 0;
    }

    if (0 == ret) {
        Log_e("fail to establish udp");
    } else {
        Log_d("success to establish udp, fd=%d", ret);
    }

    freeaddrinfo(addr_list);

    return (uintptr_t)ret;

#undef NETWORK_ADDR_LEN
}

void HAL_UDP_Disconnect(uintptr_t fd)
{
    long socket_id = -1;
    fd -= LWIP_SOCKET_FD_SHIFT;

    socket_id = (int)fd;
    close(socket_id);
}

int HAL_UDP_Write(uintptr_t fd, const unsigned char *p_data, unsigned int datalen)
{
    int  rc        = -1;
    long socket_id = -1;
    fd -= LWIP_SOCKET_FD_SHIFT;

    socket_id = (int)fd;
    rc        = send(socket_id, (char *)p_data, (int)datalen, 0);
    if (-1 == rc) {
        return -1;
    }

    return rc;
}

int HAL_UDP_Read(uintptr_t fd, unsigned char *p_data, unsigned int datalen)
{
    long socket_id = -1;
    int  count     = -1;
    fd -= LWIP_SOCKET_FD_SHIFT;

    socket_id = (int)fd;
    count     = (int)read(socket_id, p_data, datalen);

    return count;
}

int HAL_UDP_ReadTimeout(uintptr_t fd, unsigned char *p_data, unsigned int datalen, unsigned int timeout_ms)
{
    int            ret;
    struct timeval tv;
    fd_set         read_fds;
    int            socket_id = -1;
    fd -= LWIP_SOCKET_FD_SHIFT;

    socket_id = (int)fd;

    if (socket_id < 0) {
        return -1;
    }

    FD_ZERO(&read_fds);
    FD_SET(socket_id, &read_fds);

    tv.tv_sec  = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    ret = select(socket_id + 1, &read_fds, NULL, NULL, timeout_ms == 0 ? NULL : &tv);

    /* Zero fds ready means we timed out */
    if (ret == 0) {
        return QCLOUD_ERR_SSL_READ_TIMEOUT; /* receive timeout */
    }

    if (ret < 0) {
        if (errno == EINTR) {
            return -3; /* want read */
        }

        return QCLOUD_ERR_SSL_READ; /* receive failed */
    }

    /* This call will not block */
    return HAL_UDP_Read(fd, p_data, datalen);
}
#endif

#ifdef WIFI_CONFIG_ENABLED
/* lwIP socket handle start from 0 */
#define WIFI_LWIP_SOCKET_FD_SHIFT 3

int HAL_UDP_CreateBind(const char *host, unsigned short port)
{
#define NETWORK_ADDR_LEN (16)

    int             ret;
    struct addrinfo hints, *addr_list, *cur;
    int             fd = 0;

    char port_str[6] = {0};
    HAL_Snprintf(port_str, 6, "%d", port);

    memset((char *)&hints, 0x00, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family   = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;

    Log_d("establish udp connection with server(host=%s port=%s)", host, port_str);

    if (getaddrinfo(host, port_str, &hints, &addr_list) != 0) {
        Log_e("getaddrinfo error,errno:%s", strerror(errno));
        return 0;
    }

    for (cur = addr_list; cur != NULL; cur = cur->ai_next) {
        fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
        if (fd < 0) {
            ret = 0;
            continue;
        }

        Log_d("establish udp connection with server(host=%d port=%d)", ((struct sockaddr_in *)cur->ai_addr)->sin_addr,
              ((struct sockaddr_in *)cur->ai_addr)->sin_port);

        if (0 == bind(fd, cur->ai_addr, cur->ai_addrlen)) {
            ret = fd + WIFI_LWIP_SOCKET_FD_SHIFT;
            break;
        }

        close(fd);
        ret = 0;
    }

    if (0 == ret) {
        Log_e("fail to establish udp");
    } else {
        Log_d("success to establish udp, fd=%d", ret);
    }

    freeaddrinfo(addr_list);

    Log_i("HAL_UDP_Connect fd:%d", ret);

    return (uintptr_t)ret;

#undef NETWORK_ADDR_LEN
}

int HAL_UDP_ReadTimeoutPeerInfo(uintptr_t fd, unsigned char *p_data, unsigned int datalen, unsigned int timeout_ms,
                                char *recv_ip_addr, unsigned char recv_addr_len, unsigned short *recv_port)
{
    int                ret;
    struct timeval     tv;
    fd_set             read_fds;
    int                socket_id = -1;
    struct sockaddr_in source_addr;
    uint               addrLen = sizeof(source_addr);
    int                len     = 0;

    Log_i("HAL_UDP_ReadTimeoutPeerInfo fd:%d", fd);

    fd -= WIFI_LWIP_SOCKET_FD_SHIFT;

    socket_id = (int)fd;

    if (socket_id < 0) {
        return -1;
    }

    FD_ZERO(&read_fds);
    FD_SET(socket_id, &read_fds);

    tv.tv_sec  = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    ret = select(socket_id + 1, &read_fds, NULL, NULL, timeout_ms == 0 ? NULL : &tv);

    /* Zero fds ready means we timed out */
    if (ret == 0) {
        return 0; /* receive timeout */
    }

    if (ret < 0) {
        if (errno == EINTR) {
            return -3; /* want read */
        }

        return QCLOUD_ERR_SSL_READ; /* receive failed */
    }

    /* This call will not block */
    len = recvfrom((int)fd, p_data, datalen, MSG_DONTWAIT, (struct sockaddr *)&source_addr, &addrLen);

    inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, recv_ip_addr, recv_addr_len - 1);
    *recv_port = ntohs(source_addr.sin_port);

    return len;
}

int HAL_UDP_GetErrno()
{
    return errno;
}

char *HAL_UDP_GetErrnoStr()
{
    return strerror(errno);
}

int HAL_UDP_WriteTo(uintptr_t fd, const unsigned char *p_data, unsigned int datalen, char *host, unsigned short port)
{
    int             rc = -1;
    struct addrinfo hints, *addr_list;
    char            port_str[6] = {0};

    HAL_Snprintf(port_str, 6, "%d", port);
    fd -= WIFI_LWIP_SOCKET_FD_SHIFT;

    memset((char *)&hints, 0x00, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family   = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;
    Log_i("HAL_UDP_WriteTo host:%s, port:%d, fd:%d", host, port, fd);

    if ((rc = getaddrinfo(host, port_str, &hints, &addr_list)) != 0) {
        Log_e("getaddrinfo error,errno:%s, rc:%d", strerror(errno), rc);
        return 0;
    }

    Log_d("HAL_UDP_WriteTo(host=%d port=%d)", ((struct sockaddr_in *)addr_list->ai_addr)->sin_addr,
          ((struct sockaddr_in *)addr_list->ai_addr)->sin_port);

    rc = sendto(fd, p_data, datalen, 0, addr_list->ai_addr, addr_list->ai_addrlen);

    freeaddrinfo(addr_list);

    return rc;
}

void HAL_UDP_Close(uintptr_t fd)
{
    long socket_id = -1;
    fd -= WIFI_LWIP_SOCKET_FD_SHIFT;

    socket_id = (int)fd;
    close(socket_id);
}

#endif
