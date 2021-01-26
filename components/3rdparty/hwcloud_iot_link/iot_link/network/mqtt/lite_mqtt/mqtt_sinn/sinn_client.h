#ifndef __SINN_H__
#define __SINN_H__

#include <stdio.h>
#include <stdlib.h>
#ifdef CONFIG_WITH_LWIP
#include <sal.h>
#include "lwip/errno.h"
#else
#include <sal.h>
#include <errno.h>
#endif



#define SINN_FG_UDP (1 << 0)
#define SINN_FG_CONNECTING (1 << 1)

#define SINN_FG_CAN_RD (1 << 2)
#define SINN_FG_CAN_WR (1 << 3)
#define SINN_FG_ERR    (1 << 4)

#define SINN_FG_RECONNECT  (1 << 5)


#define SINN_EV_POLL       (1)
#define SINN_EV_CONNECTED  (2)
#define SINN_EV_SEND       (3)
#define SINN_EV_RECV       (4)
#define SINN_EV_CLOSE      (5)
#define SINN_EV_RECONN     (6)

typedef unsigned long int sinn_time_t;
sinn_time_t sinn_gettime_ms(void);

typedef struct sinn_connection sinn_connection_t;
typedef struct sinn_if sinn_if_t;
typedef struct sinn_buf sinn_buf_t;
typedef struct sinn_if_funcs sinn_if_funcs_t;

typedef void (*sinn_event_handler)(sinn_connection_t *nc, int event, void *event_data);

typedef struct sinn_buf
{
    unsigned char *data;
    size_t len;    //data len
    size_t size;   //total size
} sinn_buf_t;

typedef struct sinn_manager
{
    sinn_connection_t *nc;
    sinn_if_t *interface;
} sinn_manager_t;

typedef struct sinn_connection
{
    sinn_manager_t *mgr;
    int flags;
    int sock_fd;
    struct sockaddr_in address;
    char *server_ip;
    unsigned int server_port;
    sinn_buf_t recv_buf;
    sinn_buf_t send_buf;
    sinn_time_t last_time;
    sinn_event_handler user_handler;
    sinn_event_handler proto_handler;
    void *user_data;
    void *proto_data;
#ifdef WITH_DTLS
    void *ssl_handler;
#endif
} sinn_connection_t;

typedef struct sinn_if
{
    sinn_manager_t *mgr;
    sinn_if_funcs_t *ifuncs;
} sinn_if_t;

typedef struct sinn_if_funcs
{
    void (*if_init)(sinn_if_t *interface);
    void (*if_uninit)(sinn_if_t *interface);
    int (*if_connect)(sinn_connection_t *nc);
    void (*if_discon)(sinn_connection_t *nc);
    sinn_time_t (*if_poll)(sinn_connection_t *nc, int timeout_ms);
    int (*if_send)(sinn_connection_t *nc, const void *buf, size_t len);
    int (*if_recv)(sinn_connection_t *nc, void *buf, size_t len);
} sinn_if_funcs_t;

typedef struct sinn_device_info
{
    sinn_if_funcs_t *ifuncs;
} sinn_device_info_t;

typedef enum sinn_ssl_type
{
    e_sinn_ssl_type_none = 0,
    e_sinn_ssl_type_psk,
    e_sinn_ssl_type_unica,
    e_sinn_ssl_type_bica,
    e_sinn_ssl_type_max,
} sinn_ssl_type_e;

typedef struct sinn_ssl_psk
{
    const unsigned char *psk_id;
    size_t psk_id_len;
    const unsigned char *psk;
    size_t psk_len;
} sinn_ssl_psk_t;

typedef struct sinn_ssl_unica
{
    const  unsigned char *ca_cert;
    size_t ca_cert_len;
} sinn_ssl_unica_t;


typedef struct sinn_ssl_bica
{
    const  char *server_name;
    const  unsigned char *ca_cert;
    size_t ca_cert_len;
    const  unsigned char *client_cert;
    size_t client_cert_len;
    const  unsigned char *client_key;
    size_t client_key_len;
} sinn_ssl_bica_t;

typedef struct sinn_ssl_param
{
    sinn_ssl_type_e type;
    union
    {
        sinn_ssl_psk_t psk;
        sinn_ssl_unica_t uni_ca;
        sinn_ssl_bica_t bi_ca;
    } u;
} sinn_ssl_param_t;


typedef struct sinn_connect_param
{
    int proto_type;
    char *server_ip;
    unsigned int server_port;
    void *protocol_con_param;
#ifdef WITH_DTLS
    // add some param used in dtls, like ca, key etc.
    sinn_ssl_param_t ssl_param;
#endif
} sinn_connect_param_t;

void sinn_register_proto(sinn_connection_t *nc, sinn_event_handler proto_handler);


void sinn_init(sinn_manager_t *m,  sinn_device_info_t *param);
sinn_connection_t* sinn_connect(sinn_manager_t *m, sinn_event_handler cb, sinn_connect_param_t *param);
void sinn_poll(sinn_manager_t *m, int timeout_ms);
void sinn_destory(sinn_connection_t* nc);


unsigned long int sinn_gettime_ms(void);

#endif
