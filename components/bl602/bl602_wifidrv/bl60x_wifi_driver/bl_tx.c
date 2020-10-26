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
#include <stdio.h>
#include <netif/etharp.h>

#include "bl_tx.h"
#include "bl_irqs.h"
#include "bl_utils.h"
#include "os_hal.h"


struct utils_list tx_list_bl;

int internel_cal_size_tx_hdr = sizeof(struct bl_txhdr);

TaskHandle_t taskHandle_output = NULL;
extern struct bl_hw wifi_hw;
static struct bl_hw *bl_hw_static = &wifi_hw;

void bl_tx_push(struct bl_hw *bl_hw, struct bl_txhdr *txhdr)
{
    volatile struct hostdesc *host;
    uint32_t* p = txhdr->p;

    host = &(ipc_host_txdesc_get(bl_hw->ipc_env)->host);
    ASSERT_ERR(host);//TODO protect when host is NULL

    {
        u8 *src, *dst;
        int i;
        dst = (typeof(dst))host;
        src = (typeof(src))&txhdr->host;
        for (i = 0; i < sizeof(*host) / sizeof(*src); i++) {
            *dst++ = *src++;
        }
    }

    ipc_host_txdesc_push(bl_hw->ipc_env, p);
    bl_hw->stats.cfm_balance++;
}

#define TXHDR_HODLER_LEN (8)
#define TXHDR_HODLER_MSK (0x7)
struct bl_txhdr *(txhdr_hodler[8]);
uint32_t txhdr_pos_r = 0;
uint32_t txhdr_pos_w = 0;

void bl_tx_resend()
{
    taskENTER_CRITICAL();
    while (txhdr_pos_r != txhdr_pos_w) {
        if (NULL == ipc_host_txdesc_get(bl_hw_static->ipc_env)) {
            break;
        }
        txhdr_hodler[txhdr_pos_r & TXHDR_HODLER_MSK]->status.value = 0;
#if 0
        printf("Push back %p\r\n", txhdr_hodler[txhdr_pos_r & TXHDR_HODLER_MSK]);
#endif
        bl_tx_push(bl_hw_static, txhdr_hodler[txhdr_pos_r & TXHDR_HODLER_MSK]);
        txhdr_pos_r++;
    }
    taskEXIT_CRITICAL();
}

void bl_tx_try_flush()
{
    struct bl_txhdr *txhdr;

    taskENTER_CRITICAL();
    while (ipc_host_txdesc_get(bl_hw_static->ipc_env)) {
        txhdr = (struct bl_txhdr*)utils_list_pop_front(&tx_list_bl);
        if (NULL == txhdr) {
            break;
        }
        bl_tx_push(bl_hw_static, txhdr);
    }
    taskEXIT_CRITICAL();
}

int bl_txdatacfm(void *pthis, void *host_id)
{
#define RETRY_LIMIT_REACHED_BIT (1 << 16)
    struct pbuf *p = (struct pbuf*)host_id;
    struct bl_txhdr *txhdr;
    union bl_hw_txstatus bl_txst;

    txhdr = (struct bl_txhdr*)(((uint32_t)p->payload) + RWNX_HWTXHDR_ALIGN_PADS((uint32_t)p->payload));


    /* Read status in the TX control header */
    bl_txst = txhdr->status;

    if (bl_txst.value == 0) {
        return -1;
    }
    if (bl_txst.value & RETRY_LIMIT_REACHED_BIT) {
#if 0
        printf("TX STATUS %08lX", bl_txst.value);
        printf(" Retry reached %p:%lu:%lu", txhdr, txhdr_pos_r, txhdr_pos_w);
#endif
        /*we don't pbuf_free here, because we will resend this packet*/
        if (((txhdr_pos_w + 1) & TXHDR_HODLER_MSK) != (txhdr_pos_r & TXHDR_HODLER_MSK)) {
#if 1
            puts(" push back\r\n");
#endif
            txhdr_hodler[txhdr_pos_w & TXHDR_HODLER_MSK] = txhdr;
            txhdr_pos_w++;
        } else {
#if 1
            puts(" NOT push back when no mem\r\n");
#endif
            pbuf_free(p);
        }
    } else {
        pbuf_free(p);
    }

    return 0;
}

void bl_tx_notify()
{
    //TODO static alloc taskHandle_output, no if else anymore
    if (taskHandle_output) {
        xTaskNotifyGive(taskHandle_output);
    }

    return;
}

err_t bl_output(struct bl_hw *bl_hw, struct netif *netif, struct pbuf *p, int is_sta)
{
    struct bl_txhdr *txhdr;
    struct pbuf *q;
    uint32_t *link_header;
    uint32_t *eth_header;
    struct ethhdr *eth;
    struct hostdesc *host;
    int loop = 0;
    u8 tid;
    uint16_t packet_len;

    if (NULL == bl_hw || 0 == (NETIF_FLAG_LINK_UP & netif->flags)) {//TODO avoid call output when Wi-Fi is not ready
        printf("[TX] wifi is down, return now\r\n");
        return ERR_CONN;
    }

    if (0 == taskHandle_output) {
        taskHandle_output = xTaskGetCurrentTaskHandle();
    }

    bl_hw_static = bl_hw;
    eth_header = (uint32_t*)p->payload;
    packet_len = p->tot_len;

    /*Make room in the header for tx*/
    if (pbuf_header(p, PBUF_LINK_ENCAPSULATION_HLEN)) {
        printf("[TX] Reserve room failed for header\r\n");
        return ERR_IF;
    }
    /*Use aligned link_header*/
    link_header = (uint32_t*)(((uint32_t)p->payload) + RWNX_HWTXHDR_ALIGN_PADS((uint32_t)p->payload));
    if (16 + sizeof(struct bl_txhdr) + RWNX_HWTXHDR_ALIGN_PADS((uint32_t)p->payload) > PBUF_LINK_ENCAPSULATION_HLEN) {
        printf("link_header size is %ld vs header %u\r\n",
                sizeof(struct bl_txhdr) + RWNX_HWTXHDR_ALIGN_PADS((uint32_t)p->payload),
                PBUF_LINK_ENCAPSULATION_HLEN
        );
    }

    tid = 0;//XXX set TID to 0 for quick test purpose

    eth = (struct ethhdr *)(eth_header);
    txhdr = (struct bl_txhdr *)(link_header);
    memset(txhdr, 0, sizeof(struct bl_txhdr));
    host = &(txhdr->host);

    txhdr->p         = (uint32_t*)p;//XXX pattention to this filed
    // Fill-in the descriptor
    memcpy(&host->eth_dest_addr, eth->h_dest, ETH_ALEN);
    memcpy(&host->eth_src_addr, eth->h_source, ETH_ALEN);
    host->pbuf_addr = (uint32_t)p;
    host->ethertype = eth->h_proto;
    host->tid = tid;
    host->vif_idx = (is_sta ? bl_hw->vif_index_sta : bl_hw->vif_index_ap);
    host->flags = 0;
    host->packet_len = packet_len - sizeof(*eth);
    if (is_sta) {
        host->staid = bl_hw->sta_idx;
    } else {
        host->staid = bl_utils_idx_lookup(bl_hw, eth->h_dest);
    }

    loop = 0;
    for (q = p; q != NULL; q = q->next) {
        if (0 == loop) {
            /*The first pbuf*/
            host->pbuf_chained_ptr[loop] = (uint32_t)(((uint8_t*)q->payload) + sizeof(*eth)) + PBUF_LINK_ENCAPSULATION_HLEN;//eth header is skipped in the header
            host->pbuf_chained_len[loop] = q->len - sizeof(*eth) - PBUF_LINK_ENCAPSULATION_HLEN;//eth header is skipped in the header
        } else {
            /*Chained pbuf after*/
            if (loop >= 4) {
                /*exceed the limit for pbuf chained*/
                printf("[TX] [PBUF] Please fix for bigger chained pbuf, total_len %d\r\n",
                        p->tot_len
                );
            }
            host->pbuf_chained_ptr[loop] = (uint32_t)(q->payload);
            host->pbuf_chained_len[loop] = q->len;
#if 0
            printf("[%d] ptr %p, size %lu\r\n",
                    0,
                    (void*)host->pbuf_chained_ptr[0],
                    host->pbuf_chained_len[0]
            );
            printf("[%d] ptr %p, size %lu\r\n",
                    loop,
                    (void*)host->pbuf_chained_ptr[loop],
                    host->pbuf_chained_len[loop]
            );
#endif
        }
        loop++;
    }
    if (loop > 2) {
        printf("[TX] [LOOP] Chain Used %d\r\n", loop);
    }

    txhdr->status.value = 0;
    /* Fill-in TX descriptor */
    host->packet_addr = (uint32_t)(0x11111111);//FIXME we use this magic for unvaild packet_addr
    host->status_addr = (uint32_t)(&(txhdr->status));

    /*Ref this pbuf to avoid pbuf release*/
    pbuf_ref(p);

    taskENTER_CRITICAL();
    utils_list_push_back(&tx_list_bl, &(txhdr->item));
    taskEXIT_CRITICAL();

    bl_irq_handler();

    return ERR_OK;
}
