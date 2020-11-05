/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <string.h>
#include <ethernetif.h>
#include <netif/etharp.h>
#include <lwip/dns.h>
#include <bl_efuse.h>
#include <bl_wifi.h>

#include "bl_defs.h"
#include "bl_tx.h"
#include "bl_msg_tx.h"
#include "os_hal.h"
#include "wifi_mgmr.h"
#include "wifi_mgmr_api.h"

#define WIFI_MTU_SIZE 1514

#if 0
#define NET_TRACE
#define ETH_RX_DUMP
#define ETH_TX_DUMP
#endif
#define MAX_ADDR_LEN    6

#ifdef NET_TRACE
#define NET_DEBUG         os_printf
#else
#define NET_DEBUG(...)
#endif
/**
 ****************************************************************************************
 *
 * @file wifi.c
 * Copyright (C) Bouffalo Lab 2016-2018
 *
 ****************************************************************************************
 */


extern int bl_main_rtthread_start(struct bl_hw **bl_hw);

struct net_device
{
    struct bl_hw *bl_hw;
};

static struct net_device bl606a0_sta;

#if 1
/* ethernet device interface */
/* Transmit packet. */
static err_t wifi_tx(struct netif *netif, struct pbuf* p)
{
    struct wlan_netif *wlan;
#if 0
    struct net_device * bl606a0_sta = (struct net_device *)dev;
#endif
    struct pbuf* q;
    static uint32_t ticks;
#define WARNING_LIMIT_TICKS_TX_SIZE  2000
#ifdef ETH_TX_DUMP
    int dump_count = 0;
    uint8_t * dump_ptr;
    int dump_i;
#endif

    if (p->tot_len > WIFI_MTU_SIZE) {
        if (os_tick_get() - ticks > WARNING_LIMIT_TICKS_TX_SIZE) {
            os_printf("[TX] %s, TX size too big: %u bytes\r\n", __func__, p->tot_len);
            ticks = os_tick_get();
        }
        return ERR_IF;
    }

#ifdef ETH_TX_DUMP
    NET_DEBUG("tx_dump, size:%d\r\n", p->tot_len);
#endif
    for (q = p; q != NULL; q = q->next)
    {
#ifdef ETH_RX_DUMP
        dump_ptr = q->payload;
        for(dump_i=0; dump_i<q->len; dump_i++)
        {
            NET_DEBUG("%02x ", *dump_ptr);
            if( ((dump_count+1)%8) == 0 )
            {
                NET_DEBUG("  ");
            }
            if( ((dump_count+1)%16) == 0 )
            {
                NET_DEBUG("\r\n");
            }
            dump_count++;
            dump_ptr++;
        }
#endif
    }
#ifdef ETH_RX_DUMP
    NET_DEBUG("\r\n");
#endif
    wlan = container_of(netif, struct wlan_netif, netif);
    bl_output(bl606a0_sta.bl_hw, netif, p, 0 == wlan->mode);
    return 0;
}
#endif

static void netif_status_callback(struct netif *netif)
{
    os_printf("[lwip] netif status callback\r\n"
                "  IP: %s\r\n", ip4addr_ntoa(netif_ip4_addr(netif)));
    os_printf("  MK: %s\r\n", ip4addr_ntoa(netif_ip4_netmask(netif)));
    os_printf("  GW: %s\r\n", ip4addr_ntoa(netif_ip4_gw(netif)));
    if (ip4_addr_isany(netif_ip4_addr(netif))) {
        os_printf(" SKIP Notify for set Empty Address\r\n");
    } else {
        wifi_mgmr_api_ip_update();
        wifi_mgmr_api_ip_got(
            netif_ip4_addr(netif)->addr,
            netif_ip4_netmask(netif)->addr,
            netif_ip4_gw(netif)->addr,
            ((const ip4_addr_t*)ip_2_ip4(dns_getserver(0)))->addr,
            ((const ip4_addr_t*)ip_2_ip4(dns_getserver(1)))->addr
        );
    }
}

err_t bl606a0_wifi_netif_init(struct netif *netif)
{
    netif->hostname = "bl606a0";
    netif->hwaddr_len = ETHARP_HWADDR_LEN;
    /* set netif maximum transfer unit */
    netif->mtu = 1500;
    /* Accept broadcast address and ARP traffic */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;
    netif->output = etharp_output;
    netif->linkoutput = wifi_tx;
    netif_set_status_callback(netif, netif_status_callback);

    return 0;
}

int bl606a0_wifi_init(wifi_conf_t *conf)
{
    uint8_t mac[6];
    int ret;

    os_printf("\r\n\r\n[BL] Initi Wi-Fi");
    memset(mac, 0, sizeof(mac));
    bl_wifi_mac_addr_get(mac);
    os_printf(" with MAC #### %02X:%02X:%02X:%02X:%02X:%02X ####\r\n", mac[0],
            mac[1],
            mac[2],
            mac[3],
            mac[4],
            mac[5]
    );
    bl_msg_update_channel_cfg(conf->country_code);
    os_printf("-----------------------------------------------------\r\n");
    bl_wifi_clock_enable();//Enable wifi clock
    memset(&bl606a0_sta, 0, sizeof(bl606a0_sta));
    ret = bl_main_rtthread_start(&(bl606a0_sta.bl_hw));

    return ret;
}
