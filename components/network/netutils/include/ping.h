#ifndef __PING_H__
#define __PING_H__

#include <lwip/opt.h>
#if LWIP_RAW /* don't build if not configured for use in lwipopts.h */
#include <stdbool.h>

#include <utils_list.h>
#include <lwip/ip_addr.h>
#include <lwip/raw.h>
#include <utils_memp.h>

struct ping_var
{
    u32_t total_count;
    u32_t requests_count;
    u16_t interval;
    u16_t data_size;
    u16_t seq_num;
    u16_t id;
    u16_t timeout;
    u8_t  node_num;
    ip_addr_t dest;
    utils_memp_pool_t *pool;
    struct raw_pcb *pcb;
    struct utils_list req_list;
};

struct t_hdr
{
    struct t_hdr *next;
    u16_t ping_seq;
    u32_t send_time;
};

int network_netutils_ping_cli_register();
struct ping_var *ping_api_init(u16_t interval, u16_t size, u32_t count, u16_t timeout, ip_addr_t *dest);

#endif
#endif
