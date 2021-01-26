/*----------------------------------------------------------------------------
 * Copyright (c) <2019>, <Huawei Technologies Co., Ltd>
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

/* coap_io.c -- Default network I/O functions for libcoap
 *
 * Copyright (C) 2012,2014,2016-2019 Olaf Bergmann <bergmann@tzi.org> and others
 *
 * This file is part of the CoAP library libcoap. Please see
 * README for terms of use.
 */

#include "coap_config.h"

#define OPTVAL_T(t)         (t)
#define OPTVAL_GT(t)        (t)


#include "libcoap.h"
#include "coap_debug.h"
#include "coap2/mem.h"
#include "net.h"
#include "coap_io.h"
#include "pdu.h"
#include "utlist.h"
#include "resource.h"

#include "sal.h"

#ifdef WITH_DTLS
#include "dtls_interface.h"
#endif

#define IPPROTO_IP      0
#define IPPROTO_ICMP    1
#define IPPROTO_TCP     6
#define IPPROTO_UDP     17

#if !defined(WITH_CONTIKI)
 /* define generic PKTINFO for IPv4 */
#if defined(IP_PKTINFO)
#  define GEN_IP_PKTINFO IP_PKTINFO
#elif defined(IP_RECVDSTADDR)
#  define GEN_IP_PKTINFO IP_RECVDSTADDR
#else
#  error "Need IP_PKTINFO or IP_RECVDSTADDR to request ancillary data from OS."
#endif /* IP_PKTINFO */

#ifdef CONFIG_IPV6
/* define generic KTINFO for IPv6 */
#ifdef IPV6_RECVPKTINFO
#  define GEN_IPV6_PKTINFO IPV6_RECVPKTINFO
#elif defined(IPV6_PKTINFO)
#  define GEN_IPV6_PKTINFO IPV6_PKTINFO
#else
#  error "Need IPV6_PKTINFO or IPV6_RECVPKTINFO to request ancillary data from OS."
#endif /* IPV6_RECVPKTINFO */
#endif /* CONFIG_IPV6 */
#endif


void coap_free_endpoint(coap_endpoint_t *ep);

static const char *coap_socket_format_errno( int error );

struct coap_endpoint_t *
  coap_malloc_endpoint(void) {
  return (struct coap_endpoint_t *)coap_malloc_type(COAP_ENDPOINT, sizeof(struct coap_endpoint_t));
}

void
coap_mfree_endpoint(struct coap_endpoint_t *ep) {
  coap_session_mfree(&ep->hello);
  coap_free_type(COAP_ENDPOINT, ep);
}

int
coap_socket_bind_udp(coap_socket_t *sock,
  const coap_address_t *listen_addr,
  coap_address_t *bound_addr) {
  int on = 1, off = 0;

  sock->fd = sal_socket(listen_addr->addr.sa.sa_family, SOCK_DGRAM, 0);

  if (sock->fd == COAP_INVALID_SOCKET) {
    coap_log(LOG_WARNING,
             "coap_socket_bind_udp: socket: %s\n", coap_socket_strerror());
    goto error;
  }

  if (sal_setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, OPTVAL_T(&on), sizeof(on)) == COAP_SOCKET_ERROR)
    coap_log(LOG_WARNING,
             "coap_socket_bind_udp: setsockopt SO_REUSEADDR: %s\n",
              coap_socket_strerror());

  switch (listen_addr->addr.sa.sa_family) {
  case AF_INET:
    if (sal_setsockopt(sock->fd, IPPROTO_IP, GEN_IP_PKTINFO, OPTVAL_T(&on), sizeof(on)) == COAP_SOCKET_ERROR)
      coap_log(LOG_ALERT,
               "coap_socket_bind_udp: setsockopt IP_PKTINFO: %s\n",
                coap_socket_strerror());
    break;
#ifdef CONFIG_IPV6
  case AF_INET6:
    /* Configure the socket as dual-stacked */
    if (sal_setsockopt(sock->fd, IPPROTO_IPV6, IPV6_V6ONLY, OPTVAL_T(&off), sizeof(off)) == COAP_SOCKET_ERROR)
      coap_log(LOG_ALERT,
               "coap_socket_bind_udp: setsockopt IPV6_V6ONLY: %s\n",
                coap_socket_strerror());
    if (sal_setsockopt(sock->fd, IPPROTO_IPV6, GEN_IPV6_PKTINFO, OPTVAL_T(&on), sizeof(on)) == COAP_SOCKET_ERROR)
      coap_log(LOG_ALERT,
               "coap_socket_bind_udp: setsockopt IPV6_PKTINFO: %s\n",
                coap_socket_strerror());
    sal_setsockopt(sock->fd, IPPROTO_IP, GEN_IP_PKTINFO, OPTVAL_T(&on), sizeof(on)); /* ignore error, because the likely cause is that IPv4 is disabled at the os level */
    break;
#endif
  default:
    coap_log(LOG_ALERT, "coap_socket_bind_udp: unsupported sa_family\n");
    break;
  }

  if (sal_bind(sock->fd, &listen_addr->addr.sa, listen_addr->size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_bind_udp: bind: %s\n",
             coap_socket_strerror());
    goto error;
  }

  bound_addr->size = (socklen_t)sizeof(*bound_addr);
  if (sal_getsockname(sock->fd, &bound_addr->addr.sa, &bound_addr->size) < 0) {
    coap_log(LOG_WARNING,
             "coap_socket_bind_udp: getsockname: %s\n",
              coap_socket_strerror());
    goto error;
  }

  return 1;

error:
  coap_socket_close(sock);
  return 0;
}

int
coap_socket_connect_tcp1(coap_socket_t *sock,
                         const coap_address_t *local_if,
                         const coap_address_t *server,
                         int default_port,
                         coap_address_t *local_addr,
                         coap_address_t *remote_addr) {
  int on = 1, off = 0;
  coap_address_t connect_addr;
  coap_address_copy( &connect_addr, server );

  sock->flags &= ~COAP_SOCKET_CONNECTED;
  sock->fd = sal_socket(server->addr.sa.sa_family, SOCK_STREAM, 0);

  if (sock->fd == COAP_INVALID_SOCKET) {
    coap_log(LOG_WARNING,
             "coap_socket_connect_tcp1: socket: %s\n",
             coap_socket_strerror());
    goto error;
  }

  switch (server->addr.sa.sa_family) {
  case AF_INET:
    if (connect_addr.addr.sin.sin_port == 0)
      connect_addr.addr.sin.sin_port = htons(default_port);
    break;
#ifdef CONFIG_IPV6
  case AF_INET6:
    if (connect_addr.addr.sin6.sin6_port == 0)
      connect_addr.addr.sin6.sin6_port = htons(default_port);
    /* Configure the socket as dual-stacked */
    if (sal_setsockopt(sock->fd, IPPROTO_IPV6, IPV6_V6ONLY, OPTVAL_T(&off), sizeof(off)) == COAP_SOCKET_ERROR)
      coap_log(LOG_WARNING,
               "coap_socket_connect_tcp1: setsockopt IPV6_V6ONLY: %s\n",
               coap_socket_strerror());
    break;
#endif
  default:
    coap_log(LOG_ALERT, "coap_socket_connect_tcp1: unsupported sa_family\n");
    break;
  }

  if (local_if && local_if->addr.sa.sa_family) {
    coap_address_copy(local_addr, local_if);
    if (sal_setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, OPTVAL_T(&on), sizeof(on)) == COAP_SOCKET_ERROR)
      coap_log(LOG_WARNING,
               "coap_socket_connect_tcp1: setsockopt SO_REUSEADDR: %s\n",
               coap_socket_strerror());
    if (sal_bind(sock->fd, &local_if->addr.sa, local_if->size) == COAP_SOCKET_ERROR) {
      coap_log(LOG_WARNING, "coap_socket_connect_tcp1: bind: %s\n",
               coap_socket_strerror());
      goto error;
    }
  } else {
    local_addr->addr.sa.sa_family = server->addr.sa.sa_family;
  }

  if (sal_connect(sock->fd, &connect_addr.addr.sa, connect_addr.size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_connect_tcp1: connect: %s\n",
             coap_socket_strerror());
    goto error;
  }

  if (sal_getsockname(sock->fd, &local_addr->addr.sa, &local_addr->size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_connect_tcp1: getsockname: %s\n",
             coap_socket_strerror());
  }

  if (sal_getpeername(sock->fd, &remote_addr->addr.sa, &remote_addr->size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_connect_tcp1: getpeername: %s\n",
             coap_socket_strerror());
  }

  sock->flags |= COAP_SOCKET_CONNECTED;
  return 1;

error:
  coap_socket_close(sock);
  return 0;
}

int
coap_socket_connect_tcp2(coap_socket_t *sock,
                         coap_address_t *local_addr,
                         coap_address_t *remote_addr) {
  int error = 0;
  socklen_t optlen = (socklen_t)sizeof( error );

  sock->flags &= ~(COAP_SOCKET_WANT_CONNECT | COAP_SOCKET_CAN_CONNECT);

  if (sal_getsockopt(sock->fd, SOL_SOCKET, SO_ERROR, OPTVAL_GT(&error),
    &optlen) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_finish_connect_tcp: getsockopt: %s\n",
      coap_socket_strerror());
  }

  if (error) {
    coap_log(LOG_WARNING,
             "coap_socket_finish_connect_tcp: connect failed: %s\n",
             coap_socket_format_errno(error));
    coap_socket_close(sock);
    return 0;
  }

  if (sal_getsockname(sock->fd, &local_addr->addr.sa, &local_addr->size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_connect_tcp: getsockname: %s\n",
             coap_socket_strerror());
  }

  if (sal_getpeername(sock->fd, &remote_addr->addr.sa, &remote_addr->size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_connect_tcp: getpeername: %s\n",
             coap_socket_strerror());
  }

  return 1;
}

int
coap_socket_bind_tcp(coap_socket_t *sock,
                     const coap_address_t *listen_addr,
                     coap_address_t *bound_addr) {
  int on = 1, off = 0;

  sock->fd = sal_socket(listen_addr->addr.sa.sa_family, SOCK_STREAM, 0);

  if (sock->fd == COAP_INVALID_SOCKET) {
    coap_log(LOG_WARNING, "coap_socket_bind_tcp: socket: %s\n",
             coap_socket_strerror());
    goto error;
  }

  if (sal_setsockopt(sock->fd, SOL_SOCKET, SO_KEEPALIVE, OPTVAL_T(&on),
                  sizeof (on)) == COAP_SOCKET_ERROR)
    coap_log(LOG_WARNING,
             "coap_socket_bind_tcp: setsockopt SO_KEEPALIVE: %s\n",
             coap_socket_strerror());

  if (sal_setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, OPTVAL_T(&on),
                 sizeof(on)) == COAP_SOCKET_ERROR)
    coap_log(LOG_WARNING,
             "coap_socket_bind_tcp: setsockopt SO_REUSEADDR: %s\n",
             coap_socket_strerror());

  switch (listen_addr->addr.sa.sa_family) {
  case AF_INET:
    break;
#ifdef CONFIG_IPV6
  case AF_INET6:
    /* Configure the socket as dual-stacked */
    if (sal_setsockopt(sock->fd, IPPROTO_IPV6, IPV6_V6ONLY, OPTVAL_T(&off), sizeof(off)) == COAP_SOCKET_ERROR)
      coap_log(LOG_ALERT,
               "coap_socket_bind_tcp: setsockopt IPV6_V6ONLY: %s\n",
               coap_socket_strerror());
    break;
#endif
  default:
    coap_log(LOG_ALERT, "coap_socket_bind_tcp: unsupported sa_family\n");
  }

  if (sal_bind(sock->fd, &listen_addr->addr.sa, listen_addr->size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_ALERT, "coap_socket_bind_tcp: bind: %s\n",
             coap_socket_strerror());
    goto error;
  }

  bound_addr->size = (socklen_t)sizeof(*bound_addr);
  if (sal_getsockname(sock->fd, &bound_addr->addr.sa, &bound_addr->size) < 0) {
    coap_log(LOG_WARNING, "coap_socket_bind_tcp: getsockname: %s\n",
             coap_socket_strerror());
    goto error;
  }

  if (sal_listen(sock->fd, 5) == COAP_SOCKET_ERROR) {
    coap_log(LOG_ALERT, "coap_socket_bind_tcp: listen: %s\n",
             coap_socket_strerror());
    goto  error;
  }

  return 1;

error:
  coap_socket_close(sock);
  return 0;
}

int
coap_socket_accept_tcp(coap_socket_t *server,
                       coap_socket_t *new_client,
                       coap_address_t *local_addr,
                       coap_address_t *remote_addr) {
  server->flags &= ~COAP_SOCKET_CAN_ACCEPT;

  new_client->fd = sal_accept(server->fd, &remote_addr->addr.sa,
                          &remote_addr->size);
  if (new_client->fd == COAP_INVALID_SOCKET) {
    coap_log(LOG_WARNING, "coap_socket_accept_tcp: accept: %s\n",
             coap_socket_strerror());
    return 0;
  }

  if (sal_getsockname( new_client->fd, &local_addr->addr.sa, &local_addr->size) < 0)
    coap_log(LOG_WARNING, "coap_socket_accept_tcp: getsockname: %s\n",
             coap_socket_strerror());

  return 1;
}

int
coap_socket_connect_udp(coap_socket_t *sock,
  const coap_address_t *local_if,
  const coap_address_t *server,
  int default_port,
  coap_address_t *local_addr,
  coap_address_t *remote_addr) {
  int on = 1, off = 0;
  coap_address_t connect_addr;
  int is_mcast = coap_is_mcast(server);
  coap_address_copy(&connect_addr, server);

  sock->flags &= ~(COAP_SOCKET_CONNECTED | COAP_SOCKET_MULTICAST);
  sock->fd = sal_socket(connect_addr.addr.sa.sa_family, SOCK_DGRAM, 0);

  if (sock->fd == COAP_INVALID_SOCKET) {
    coap_log(LOG_WARNING, "coap_socket_connect_udp: socket: %s\n",
             coap_socket_strerror());
    goto error;
  }

  switch (connect_addr.addr.sa.sa_family) {
  case AF_INET:
    if (connect_addr.addr.sin.sin_port == 0)
      connect_addr.addr.sin.sin_port = htons(default_port);
    break;
#ifdef CONFIG_IPV6
  case AF_INET6:
    if (connect_addr.addr.sin6.sin6_port == 0)
      connect_addr.addr.sin6.sin6_port = htons(default_port);
    /* Configure the socket as dual-stacked */
    if (sal_setsockopt(sock->fd, IPPROTO_IPV6, IPV6_V6ONLY, OPTVAL_T(&off), sizeof(off)) == COAP_SOCKET_ERROR)
      coap_log(LOG_WARNING,
               "coap_socket_connect_udp: setsockopt IPV6_V6ONLY: %s\n",
               coap_socket_strerror());
    break;
#endif
  default:
    coap_log(LOG_ALERT, "coap_socket_connect_udp: unsupported sa_family\n");
    break;
  }

  if (local_if && local_if->addr.sa.sa_family) {
    if (sal_setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, OPTVAL_T(&on), sizeof(on)) == COAP_SOCKET_ERROR)
      coap_log(LOG_WARNING,
               "coap_socket_connect_udp: setsockopt SO_REUSEADDR: %s\n",
               coap_socket_strerror());
    if (sal_bind(sock->fd, &local_if->addr.sa, local_if->size) == COAP_SOCKET_ERROR) {
      coap_log(LOG_WARNING, "coap_socket_connect_udp: bind: %s\n",
               coap_socket_strerror());
      goto error;
    }
  }

  /* special treatment for sockets that are used for multicast communication */
  if (is_mcast) {
    if (sal_getsockname(sock->fd, &local_addr->addr.sa, &local_addr->size) == COAP_SOCKET_ERROR) {
      coap_log(LOG_WARNING,
              "coap_socket_connect_udp: getsockname for multicast socket: %s\n",
              coap_socket_strerror());
    }
    coap_address_copy(remote_addr, &connect_addr);
    sock->flags |= COAP_SOCKET_MULTICAST;
    return 1;
  }

  if (sal_connect(sock->fd, &connect_addr.addr.sa, connect_addr.size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_connect_udp: connect: %s\n",
             coap_socket_strerror());
    goto error;
  }

  if (sal_getsockname(sock->fd, &local_addr->addr.sa, &local_addr->size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_connect_udp: getsockname: %s\n",
             coap_socket_strerror());
  }

  if (sal_getpeername(sock->fd, &remote_addr->addr.sa, &remote_addr->size) == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_connect_udp: getpeername: %s\n",
             coap_socket_strerror());
  }

  sock->flags |= COAP_SOCKET_CONNECTED;
  return 1;

error:
  coap_socket_close(sock);
  return 0;
}

void coap_socket_close(coap_socket_t *sock) {
  if (sock->fd != COAP_INVALID_SOCKET) {
    sal_closesocket(sock->fd);
    sock->fd = COAP_INVALID_SOCKET;
  }
  sock->flags = COAP_SOCKET_EMPTY;
}

ssize_t
coap_socket_write(coap_socket_t *sock, const uint8_t *data, size_t data_len) {
  ssize_t r;

  sock->flags &= ~(COAP_SOCKET_WANT_WRITE | COAP_SOCKET_CAN_WRITE);

  r = sal_send(sock->fd, data, data_len, 0);
  if (r == COAP_SOCKET_ERROR) {
    coap_log(LOG_WARNING, "coap_socket_write: send: %s\n",
             coap_socket_strerror());
    return -1;
  }
  if (r < (ssize_t)data_len)
    sock->flags |= COAP_SOCKET_WANT_WRITE;
  return r;
}

ssize_t
coap_socket_read(coap_socket_t *sock, uint8_t *data, size_t data_len) {
  ssize_t r;

  r = sal_recv(sock->fd, data, data_len, 0);
  if (r == 0) {
    /* graceful shutdown */
    sock->flags &= ~COAP_SOCKET_CAN_READ;
    return -1;
  } else if (r == COAP_SOCKET_ERROR) {
    sock->flags &= ~COAP_SOCKET_CAN_READ;
    return -1;
  }
  if (r < (ssize_t)data_len)
    sock->flags &= ~COAP_SOCKET_CAN_READ;
  return r;
}

ssize_t
coap_network_send(coap_socket_t *sock, const coap_session_t *session, const uint8_t *data, size_t datalen) {
  ssize_t bytes_written = 0;

  if (!coap_debug_send_packet()) {
    bytes_written = (ssize_t)datalen;
  } else if (sock->flags & COAP_SOCKET_CONNECTED) {
 #ifdef WITH_DTLS
    bytes_written = dtls_write((mbedtls_ssl_context *)(session->context->dtls_context), data, datalen);
#else
    bytes_written = sal_send(sock->fd, data, datalen, 0);
#endif
  }

  if (bytes_written < 0)
    coap_log(LOG_CRIT, "coap_network_send: %s\n", coap_socket_strerror());

  return bytes_written;
}


void
coap_packet_get_memmapped(coap_packet_t *packet, unsigned char **address, size_t *length) {
  *address = packet->payload;
  *length = packet->length;
}

void coap_packet_set_addr(coap_packet_t *packet, const coap_address_t *src, const coap_address_t *dst) {
  coap_address_copy(&packet->src, src);
  coap_address_copy(&packet->dst, dst);
}

ssize_t
coap_network_read(coap_socket_t *sock, const coap_session_t *session, coap_packet_t *packet) {
  ssize_t len = -1;

  assert(sock);
  assert(packet);

  if ((sock->flags & COAP_SOCKET_CAN_READ) == 0) {
    return -1;
  } else {
    /* clear has-data flag */
    sock->flags &= ~COAP_SOCKET_CAN_READ;
  }

  if (sock->flags & COAP_SOCKET_CONNECTED) {
#ifdef WITH_DTLS
    len = dtls_read((mbedtls_ssl_context *)(session->context->dtls_context), packet->payload, COAP_RXBUFFER_SIZE, 1000);
#else
    len = sal_recv(sock->fd, packet->payload, COAP_RXBUFFER_SIZE, 0);
#endif
    if (len < 0) {
      coap_log(LOG_WARNING, "coap_network_read: %s\n", coap_socket_strerror());
      goto error;
    } else if (len > 0) {
      packet->length = (size_t)len;
    }
  }

  if (len >= 0)
    return len;

error:
  return -1;
}

static const char *coap_socket_format_errno(int error) {
  return strerror(error);
}

const char *coap_socket_strerror(void) {
  return strerror(-1);
}

ssize_t
coap_socket_send(coap_socket_t *sock, coap_session_t *session,
  const uint8_t *data, size_t data_len) {
  return session->context->network_send(sock, session, data, data_len);
}

