

#ifndef __SAL_H
#define __SAL_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
// #include <string.h>
#include <sys/select.h>

#include <sal_define.h>
#include <sal_types.h>
#include <link_endian.h>

/**
 *
 *@brief: list all the api need for the application development,,supported depends on the implement of
 *       the tcpip stack
 *  Thanks to BSD && linux, which must be compatible
 */

int sal_socket(int domain, int type, int protocol);

int sal_bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);

int sal_listen(int sockfd,  int backlog);

int sal_accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);

int sal_connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);

int sal_getsockname(int sockfd, struct sockaddr *addr,socklen_t *addrlen);

int sal_getpeername(int sockfd, struct sockaddr *addr,socklen_t *addrlen);

int sal_getsockopt (int socket, int level, int optname, void *optval, int *optlen);

int sal_setsockopt (int socket, int level, int optname, const void *optval, int optlen);

int sal_recv(int sockfd,void *buf,size_t len,int flags);

int sal_recvfrom(int sockfd, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen);

int sal_send(int sockfd,const void *buf,size_t len,int flags);

int sal_sendto(int sockfd, const void *dataptr, size_t size, int flags,
    const struct sockaddr *to, socklen_t tolen);

int sal_shutdown(int sockfd, int how);

int sal_closesocket(int sockfd);

int sal_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);


struct hostent * sal_gethostbyname(const char *name);


/**
 * @brief: if you want to use the tcpip abstract layer,like install the tcpip stack,
 *         or use the api as the application user, you must call this function first
 *
 * @return:0 success while -1 failed
 * */
int link_tcpip_init( void);

in_addr_t inet_addr(const char *addr);
char *inet_ntoa(struct in_addr addr);
int inet_aton(const char *string,struct in_addr *addr);
const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);



#endif /* __SAL_H */

