/*
 * Copyright (c) 2016-2023 Bouffalolab.
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

/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "cli.h"
#include "utils_ringblk.h"

#include "lwip/etharp.h"
#include "lwip/mem.h"
#include "lwip/netif.h"
#include "lwip/netifapi.h"
#include "lwip/pbuf.h"
#include "lwip/tcpip.h"

#ifdef XRAM_CPU_E907
#include <aos/yloop.h>
#include <bl60x_wifi_driver/wifi_mgmr.h>
#include <rnm_server.h>
#include <wifi_pkt_hooks.h>
#endif

#ifdef XRAM_CPU_C906
#include <rnm_client_cmds.h>
#endif

#include "xram.h"
#include "xram_net.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Macro define ------------------------------------------------------------- */

#define XRAM_NET_READ_TIMEOUT (5)

#ifdef XRAM_CPU_E907
#define XRAM_ETH_RX_DESC_CNT (2)
#else
#define XRAM_ETH_RX_DESC_CNT (13)
#endif

#define XRAM_NET_MTU (2048)

#ifdef XRAM_CPU_E907
#define XRAM_NET_DATA_MAX_LEN (XRAM_ETH_RX_DESC_CNT * (XRAM_NET_MTU + PBUF_LINK_ENCAPSULATION_HLEN))
#else
#define XRAM_NET_DATA_MAX_LEN (XRAM_ETH_RX_DESC_CNT * XRAM_NET_MTU)
#endif

#define XRAM_NET_HEADER ("\x72\x69\x6e\x67")

#ifdef XRAM_CPU_E907
typedef void (*bl_custom_tx_callback_t)(void *cb_arg, bool tx_ok);

struct bl_custom_tx_cfm {
    bl_custom_tx_callback_t cb;
    void *cb_arg;
};

int bl_wifi_eth_tx(struct pbuf *p, bool is_sta, struct bl_custom_tx_cfm *custom_cfm);
#endif  // XRAM_CPU_E907

/* Exported types ------------------------------------------------------------*/

#pragma pack(push, 4)

typedef struct xram_net_custom_pbuf {
    struct pbuf_custom custom_pbuf;

    struct utils_rbb_blk *rx_rbk;
} xram_net_custom_pbuf_t;

#pragma pack(pop)

struct eth_tx_msg {
    struct netif *netif;
    struct pbuf *pbuf;
};

typedef enum xram_msg_type {
    MSG_COMMAND,
    MSG_FRAME,
    MSG_SNIFFER_PKT,
} xram_msg_type_t;

struct xram_msg_desc {
    xram_msg_type_t type;
    void *state;
    union {
        struct
        {
            void *payload;
            uint16_t length;
        } command;
        struct
        {
            struct pbuf *pbuf;
            uint16_t flag;
        } frame;
    };
};
/* Global variable ---------------------------------------------------------- */

struct netif g_e907_netif;

#ifdef XRAM_CPU_C906
static char g_net_name[XRAM_NET_DEV_TYPE_MAX][2] = {{'w', 'i'}, {'w', 'r'}};
#endif
static xram_net_t g_xram_netdev[XRAM_NET_DEV_NUM_MAX];

static TaskHandle_t g_rx_task;
static TaskHandle_t g_tx_task;
static TaskHandle_t g_tx_bench_task;
static xQueueHandle g_xram_tx_msg;

static struct utils_rbb g_rx_rbb;
static utils_rbb_t g_rx_rbb_t = &g_rx_rbb;
static uint8_t g_rbb_blk_desc[XRAM_ETH_RX_DESC_CNT * sizeof(struct utils_rbb_blk)];

static uint32_t g_rx_count = 0;
static uint32_t g_rx_count_error = 0;
volatile uint8_t g_e907_out_flag = 1;

#ifdef XRAM_CPU_E907
static uint8_t *g_rbb_buf;
rnms_t *g_rnms;
#endif

#ifdef XRAM_CPU_C906
static __attribute__((section(".wifi_ram"))) uint8_t g_rbb_buf[XRAM_NET_DATA_MAX_LEN];
rnmc_t *g_rnmc;
#endif

/* Static functions --------------------------------------------------------- */

/* Exported functions ------------------------------------------------------- */

/**
 * @brief   Free custom pbuf
 * @note
 * @param
 * @retval
 */
#ifdef XRAM_CPU_C906
#define LWIP_DECLARE_MEMORY_ALIGNED(variable_name, size) \
    u8_t variable_name[LWIP_MEM_ALIGN_BUFFER(size)] __attribute__((section(".wifi_ram")))
LWIP_MEMPOOL_DECLARE(RX_POOL, 8, sizeof(struct xram_net_custom_pbuf), "bl_zero_copy_rx");
#endif

static void my_pbuf_free_custom(struct pbuf *p)
{
    struct xram_net_custom_pbuf *custom_pbuf = (struct xram_net_custom_pbuf *)p;
    struct utils_rbb_blk *rx_blk = custom_pbuf->rx_rbk;

    xram_log("free rblk %p %d\r\n", rx_blk->buf, rx_blk->size);
    utils_rbb_blk_free(g_rx_rbb_t, rx_blk);

#ifdef XRAM_CPU_C906
    LWIP_MEMPOOL_FREE(RX_POOL, custom_pbuf);
#endif

    xTaskNotifyGive(g_rx_task);
}

/**
 * @brief   Free custom pbuf
 * @note
 * @param
 * @retval
 */
static inline int mac_is_unvalid(uint8_t mac[6])
{
    int i;
    uint8_t data;

    data = mac[0];
    for (i = 1; i < 6; i++) {
        if (data != mac[i]) {
            break;
        }
    }

    if (6 == i) {
        if (0 == data || 0xFF == data) {
            /* all 0 or 0xFF found */
            return 1;
        }
    }

    return 0;
}

/**
 * @brief   Protocol stack data is written to xram
 * @note
 * @param   netdev - Network card for data transmission
 *          tx_config - the config of tx data
 * @retval  ret - tx data len
 */
int xram_net_output(xram_net_t *netdev, struct xram_net_data_config *tx_config)
{
    int ret = 0;
    static uint8_t s_tx_buf[XRAM_NET_DATA_HDR_LEN];
    struct xram_net_data_hdr *hdr = (struct xram_net_data_hdr *)&s_tx_buf[0];

    // if (IS_XRAM_ETH_TX_DATA_VALID(tx_config) && IS_XRAM_NETDEV_UP(netdev))
    if (IS_XRAM_NETDEV_UP(netdev) || tx_config->type == XRAM_NET_MSG_TYPE_COMMAND) {
        /* fill data header */

        memcpy((void *)&hdr->header, XRAM_NET_HEADER, 4);
        hdr->len = tx_config->len;
        hdr->type = XRAM_NET_DATA_TYPE_MAKE(tx_config->type, netdev->type);
        hdr->flag = tx_config->flag;
        hdr->crc16 = 0x0;

        xram_log("send net data type: %x len: %d flag: %x\r\n", (uint16_t)hdr->type, hdr->len, hdr->flag);

        ret += XRAMRingWrite(XRAM_RING_ID_NET, s_tx_buf, XRAM_NET_DATA_HDR_LEN);

        if (hdr->len > 0) {
            ret += XRAMRingWrite(XRAM_RING_ID_NET, tx_config->buf, tx_config->len);
        }

        // ret = hdr->len + XRAM_NET_DATA_HDR_LEN;
    }

    return ret;
}

/**
 * @brief   Read xram data and write to ringbuf
 * @note
 * @param   hdr: Packet information waiting to be read
 * @retval  ret: Whether to read xram data successfully
 *            -1 fail
 *            0  succ
 */
static int xram_net_data_handler(xram_net_data_hdr_t *hdr)
{
    int ret = 0;
    uint32_t len = 0;
    struct xram_net_data_hdr *data_hdr;
    struct utils_rbb_blk *rx_blk;
    bool is_non_eth;

    if (hdr->len > 0) {
        uint32_t alloc_len;
        is_non_eth = XRAM_NET_DATA_TYPE_MAJOR(hdr) != XRAM_NET_MSG_TYPE_FRAME;
        /* malloc rx buff from ringblk */
        if (is_non_eth)
            alloc_len = hdr->len + sizeof(xram_net_data_hdr_t);
        else
#ifdef XRAM_CPU_E907
            /* Alloc for 2 more bytes, leaving space for 4-byte alignment */
            alloc_len = hdr->len + sizeof(xram_net_data_hdr_t) + sizeof(struct xram_net_custom_pbuf) + PBUF_LINK_ENCAPSULATION_HLEN + 2;
#else
            alloc_len = hdr->len + sizeof(xram_net_data_hdr_t) + 2;
#endif

        rx_blk = utils_rbb_blk_alloc(g_rx_rbb_t, alloc_len);

        if (rx_blk) {
            void *dst;
            xram_log("Alloc rblk succ %p %" PRId32 "\r\n", rx_blk->buf, alloc_len);
            /* Fill header */

            data_hdr = (struct xram_net_data_hdr *)rx_blk->buf;

            data_hdr->type = hdr->type;
            data_hdr->flag = hdr->flag;
            data_hdr->len = hdr->len;
            data_hdr->crc16 = hdr->crc16;

            /* Reading eth data body non-blocking */

            if (is_non_eth)
                dst = rx_blk->buf + sizeof(xram_net_data_hdr_t);
            else
#ifdef XRAM_CPU_E907
                dst = LWIP_MEM_ALIGN(rx_blk->buf + sizeof(xram_net_data_hdr_t)) + sizeof(struct xram_net_custom_pbuf) + PBUF_LINK_ENCAPSULATION_HLEN;
#else
                dst = LWIP_MEM_ALIGN(rx_blk->buf + sizeof(xram_net_data_hdr_t));
#endif

#ifdef XRAM_USE_TIMEOUT
            len = XRAMRingReadTimeout(XRAM_RING_ID_NET,
#else
            len = XRAMRingRead(XRAM_RING_ID_NET,
#endif
                                      dst,
#ifdef XRAM_USE_TIMEOUT
                                      data_hdr->len,
                                      5);
#else
                               data_hdr->len);
#endif

            if (len == data_hdr->len) {
                xram_log("Put rblk %d\r\n", rx_blk->size);
                utils_rbb_blk_put(rx_blk);
            } else {
                xram_log("Net data read fail, free rblk\r\n");
                /* Read net data failed */

                utils_rbb_blk_free(g_rx_rbb_t, rx_blk);
                ret = -1;
            }
        } else {
            xram_log("Alloc rblk fail %" PRId32 "\r\n", alloc_len);

            /* Alloc failed */
            ret = -2;
        }
    } else {
        printf("Net hdr len = 0, recive trigger\r\n");
        ret = -1;
    }
    return ret;
}

static void xram_net_input_non_eth(struct utils_rbb_blk *rx_blk, uint8_t type)
{
    struct xram_net_data_hdr *data_hdr = (struct xram_net_data_hdr *)rx_blk->buf;
    uint8_t subtype;
    subtype = XRAM_NET_DATA_TYPE_MINOR(data_hdr);
    xram_net_t *xram_netdev = &g_xram_netdev[XRAM_NETDEV_GET_INDEX(subtype)];
    void *data = rx_blk->buf + sizeof(xram_net_data_hdr_t);
#ifdef XRAM_CPU_C906
    rnmc_t *rnm = xram_netdev->rnm;
    if (type == XRAM_NET_MSG_TYPE_COMMAND) {
        rnmc_cmd_input_raw(rnm, data, data_hdr->len);
    } else if (type == XRAM_NET_MSG_TYPE_SNIFFER_PKT) {
        rnmc_sniffer_packet_input(rnm, data, data_hdr->len);
    }
#endif  // XRAM_CPU_C906

#ifdef XRAM_CPU_E907
    rnms_cmd_input_raw(xram_netdev->rnm, data, data_hdr->len);
#endif  // XRAM_CPU_E907
}

static void xram_net_input_frame(struct utils_rbb_blk *rx_blk)
{
    struct xram_net_data_hdr *data_hdr = (struct xram_net_data_hdr *)rx_blk->buf;
#ifdef XRAM_CPU_C906
    /* Alloc pbuf */
    struct xram_net_custom_pbuf *xram_pbuf;
    uint8_t subtype;

    /* Find the specified network card and netif by network card type */

    subtype = XRAM_NET_DATA_TYPE_MINOR(data_hdr);
    xram_net_t *xram_netdev = &g_xram_netdev[XRAM_NETDEV_GET_INDEX(subtype)];

    /* Get netif for lwip */

    struct netif *netif = (struct netif *)xram_netdev->user;

    if (netif) {
        xram_pbuf = (struct xram_net_custom_pbuf *)LWIP_MEMPOOL_ALLOC(RX_POOL);

        xram_pbuf->rx_rbk = rx_blk;

        xram_pbuf->custom_pbuf.custom_free_function = my_pbuf_free_custom;

        struct pbuf *p = pbuf_alloced_custom(PBUF_RAW,
                                             data_hdr->len,
                                             PBUF_REF,
                                             &xram_pbuf->custom_pbuf,
                                             LWIP_MEM_ALIGN(rx_blk->buf + sizeof(xram_net_data_hdr_t)),
                                             data_hdr->len);

        xram_log("c906 xram netif len %" PRId32 " totlen %" PRId32 "\r\n", p->len, p->tot_len);

        if (g_e907_out_flag == 1) {
            if (netif->input(p, netif) != ERR_OK) {
                pbuf_free(p);
            }
        } else {
            pbuf_free(p);
        }
    } else {
        xram_log("c906 netif not exit %p\r\n", netif);
        utils_rbb_blk_free(g_rx_rbb_t, rx_blk);
    }
#endif  // XRAM_CPU_C906

#ifdef XRAM_CPU_E907
    uint16_t flag = data_hdr->flag;
    bool is_sta = !(flag & XRAM_NET_DATA_FLAG_AP_FRAME);  // TODO support sniffer

    struct xram_net_custom_pbuf *xram_pbuf =
        (struct xram_net_custom_pbuf *)LWIP_MEM_ALIGN((rx_blk->buf + sizeof(xram_net_data_hdr_t)));

    // xram_pbuf = (struct xram_net_custom_pbuf *)LWIP_MEMPOOL_ALLOC(RX_POOL);
    xram_log("rxblk->buf %p, xram_pbuf %p\r\n", rx_blk->buf, xram_pbuf);

    xram_pbuf->custom_pbuf.custom_free_function = my_pbuf_free_custom;

    xram_pbuf->rx_rbk = rx_blk;

    struct pbuf *p = pbuf_alloced_custom(PBUF_RAW_TX,
                                         data_hdr->len,
                                         PBUF_RAM,
                                         &xram_pbuf->custom_pbuf,
                                         (uint8_t *)xram_pbuf + sizeof(struct xram_net_custom_pbuf),
                                         rx_blk->size);

    xram_log("e907 xram linkoutput pbuf len %" PRId16 ", payload %p, totlen %" PRId16 "\r\n",
             p->len,
             p->payload,
             p->tot_len);

    if (g_e907_out_flag == 1) {
        bl_wifi_eth_tx(p, is_sta, NULL);
    }

    pbuf_free(p);
#endif  // XRAM_CPU_E907
}

/**
 * @brief   Data transfer to the protocol stack
 * @note
 * @param   none
 * @retval  ret: whether ringbuff is empty
 */
static void xram_net_stack_input(void)
{
    struct utils_rbb_blk *rx_blk;

    /* Find date point from ringblk */

    rx_blk = utils_rbb_blk_get(g_rx_rbb_t);

    if (rx_blk) {
        struct xram_net_data_hdr *data_hdr = (struct xram_net_data_hdr *)rx_blk->buf;

        xram_log("net stack input get ringblk %d\r\n", rx_blk->size);

        if (data_hdr->len > 0) {
            uint8_t type_major = XRAM_NET_DATA_TYPE_MAJOR(data_hdr);
            if (type_major == XRAM_NET_MSG_TYPE_COMMAND || type_major == XRAM_NET_MSG_TYPE_SNIFFER_PKT) {
                xram_net_input_non_eth(rx_blk, type_major);
                utils_rbb_blk_free(g_rx_rbb_t, rx_blk);
            } else if (type_major == XRAM_NET_MSG_TYPE_FRAME) {
                xram_net_input_frame(rx_blk);
            } else {
                xram_log("%s: type major 0x%x unknown. BUG?\r\n", __func__, type_major);
                utils_rbb_blk_free(g_rx_rbb_t, rx_blk);
            }
        } else {
            utils_rbb_blk_free(g_rx_rbb_t, rx_blk);
        }
    }
}

/**
 * @brief   Block reading xramring data, wake up when data comes in
 * @note
 * @param
 * @retval  none
 */
static void xram_net_task(void *arg)
{
    int ret = 0;
    uint32_t recv = 0;
    static uint8_t s_rx_buf[sizeof(struct xram_net_data_hdr)];

    XRAMRingReset(XRAM_RING_ID_NET);

#if XRAM_NET_BENCH
    uint32_t s_now = 0;
    uint32_t s_total_recv = 0;
    uint32_t s_time = 0;

    s_now = xTaskGetTickCount();
#endif

    while (1) {
        struct xram_net_data_hdr *hdr = (struct xram_net_data_hdr *)&s_rx_buf[0];

        /* First read the data header */

#ifdef XRAM_USE_TIMEOUT
        recv = XRAMRingReadTimeout(XRAM_RING_ID_NET, hdr, sizeof(struct xram_net_data_hdr), 5);
#else
        recv = XRAMRingRead(XRAM_RING_ID_NET, hdr, sizeof(struct xram_net_data_hdr));
#endif

        xram_log("rx task recv type: 0x%x len: %d flag: %x\r\n", (uint16_t)hdr->type, hdr->len, hdr->flag);

        g_rx_count += 1;

        /* Determine whether the data is successfully read,
         * whether the header flag bit is checked correctly,
         * and whether the network card type is legal */

        if (recv > 0 && (memcmp((void *)&hdr->header, XRAM_NET_HEADER, 4) == 0) && IS_XRAM_NET_DEV_TYPE(XRAM_NET_DATA_TYPE_MINOR(hdr))) {
            /* Incoming xram data header, read the body through the data header
             *
             * Process the data in the buffer only if it fails to read the xram data
             */

            while ((-2) == xram_net_data_handler(hdr)) {
                xTaskNotifyStateClear(g_rx_task);

                xTaskNotifyWait(portMAX_DELAY, portMAX_DELAY, NULL, 10);
            }

            /* There are several situations where it returns non-zero:
             *    Receive ringblk is full
             *    Failed to read the body
             */

            if (ret == 0) {
#if XRAM_NET_BENCH
                s_total_recv += hdr->len;
                s_time = xTaskGetTickCount();

                if ((s_time - s_now) > 1000) {
                    float f_now;

                    f_now = (float)(s_total_recv)*8 / ((float)(s_time - s_now) / 1000) / 1000000;

                    printf("xram rx bench: %.4f Mbps. total %" PRId32 " time %" PRId32 "ms\r\n",
                           f_now,
                           s_total_recv,
                           (s_time - s_now));

                    s_total_recv = 0;
                    s_now = s_time;
                }
#endif
                /* Ringbuff data is transferred to the protocol stack */

                xram_net_stack_input();
            }

            if (ret == -1) {
                /* Read net data failed */

                g_rx_count_error += 1;

                // XRAMRingReset(XRAM_RING_ID_NET);
            }
        } else {
            g_rx_count_error += 1;
            printf("Net hdr error %" PRIu32 " %" PRIu32 "\r\n", g_rx_count, g_rx_count_error);
            /* Header matching failed, reset eth xram */

            // XRAMRingReset(XRAM_RING_ID_NET);
        }
    }
}

/**
 * @brief   xram tx thread
 * @note
 * @param
 * @retval
 */
void xram_net_rx_thread(void *arg)
{
    while (1) {
        {
        }
    }
}

/**
 * @brief   Protocol stack data is written to xram
 * @note
 * @param   netdev - Network card for data transmission
 *          tx_config - the config of tx data
 * @retval  ret - tx data len
 */
#ifdef XRAM_CPU_C906
err_t xram_net_tx(struct netif *netif, struct pbuf *p)
#endif
#ifdef XRAM_CPU_E907
    err_t xram_net_tx(struct pbuf *p, bool is_sta, xram_net_t *net)
#endif
{
    struct xram_msg_desc *msg;

    msg = (struct xram_msg_desc *)pvPortMalloc(sizeof(struct xram_msg_desc));

    if (msg) {
#ifdef XRAM_CPU_C906
        pbuf_ref(p);
#endif

        /* send a message to eth tx thread */

        msg->type = MSG_FRAME;
#ifdef XRAM_CPU_C906
        msg->state = netif;
#endif
#ifdef XRAM_CPU_E907
        msg->state = net;
#endif
        msg->frame.pbuf = p;
#ifdef XRAM_CPU_C906
        struct xram_net *netdev = (struct xram_net *)netif->state;
        rnmc_t *rnm = (rnmc_t *)netdev->rnm;
        msg->frame.flag = 0;
        if (rnmc_get_mode(rnm) == RNMC_WIFI_MODE_AP) {
            msg->frame.flag |= XRAM_NET_DATA_FLAG_AP_FRAME;
        }
#endif
#ifdef XRAM_CPU_E907
        msg->frame.flag = 0;
        if (!is_sta) {
            msg->frame.flag |= XRAM_NET_DATA_FLAG_AP_FRAME;
        }
#endif

        xram_log("xram net xQueue send len: %d buf: %p\r\n", p->len, p);

        if (xQueueSend(g_xram_tx_msg, &msg, portMAX_DELAY) != pdPASS) {
            vPortFree(msg);
            printf("send tx msg send failed %p, len %" PRId16 "\r\n", &msg, p->tot_len);

            return ERR_IF;
        }
    } else {
        xram_log("xram tx msg malloc failed\r\n");
    }

    return ERR_OK;
}

int xram_tx_data(void *env, rnm_output_data_type_t type, const void *data, uint16_t data_length)
{
    struct xram_msg_desc *msg = NULL;
    void *payload;
    xram_msg_type_t xm_type = MSG_COMMAND;
    TickType_t ticks_to_wait = portMAX_DELAY;

    msg = (struct xram_msg_desc *)pvPortMalloc(sizeof(*msg));
    if (!msg) {
        return -1;
    }
    if (type == RNM_OUT_SNIFFER_FRAME) {
        struct pbuf *p = (struct pbuf *)data;
        xm_type = MSG_SNIFFER_PKT;
        msg->frame.pbuf = p;
        pbuf_ref(p);
    } else {
        payload = pvPortMalloc(data_length);
        if (payload) {
            memcpy(payload, data, data_length);
            msg->command.payload = payload;
            msg->command.length = data_length;
        } else {
            vPortFree(msg);
            return -1;
        }
    }
    msg->type = xm_type;
    msg->state = env;
    xQueueSend(g_xram_tx_msg, &msg, ticks_to_wait);

    return 0;
}

/**
 * @brief   xram tx thread
 * @note
 * @param
 * @retval
 */
void xram_net_tx_thread(void *arg)
{
    int len = 0;
    struct xram_msg_desc *msg;
    struct xram_net *netdev;
    struct xram_net_data_config tx_config = {0};
    struct pbuf *q;

    while (1) {
        if (pdPASS == xQueueReceive(g_xram_tx_msg, (void *)&msg, portMAX_DELAY)) {
            if (msg->type == MSG_FRAME || msg->type == MSG_SNIFFER_PKT) {
#ifdef XRAM_CPU_C906
                struct netif *netif = (struct netif *)msg->state;
                netdev = (struct xram_net *)netif->state;
#endif  // XRAM_CPU_C906
#ifdef XRAM_CPU_E907
                netdev = (struct xram_net *)msg->state;
#endif  // XRAM_CPU_E907
                q = msg->frame.pbuf;

                xram_log("TX thread msg: %p len: %" PRId16 "\r\n", msg->frame.pbuf, q->tot_len);

                for (; q != NULL; q = q->next) {
                    tx_config.len = q->len;
                    tx_config.buf = q->payload;
                    tx_config.flag = msg->frame.flag;
                    tx_config.type = XRAM_NET_MSG_TYPE_FRAME;

                    if (msg->type == MSG_SNIFFER_PKT) {
                        tx_config.type = XRAM_NET_MSG_TYPE_SNIFFER_PKT;
                    }
                    xram_log("xram net tx netdev: %p len: %d buf: %p\r\n",
                             (void *)netdev,
                             (unsigned int)tx_config.len,
                             tx_config.buf);

                    len = xram_net_output(netdev, &tx_config);

                    if (len == tx_config.len + XRAM_NET_DATA_HDR_LEN) {
                        continue;
                    } else {
                        break;
                    }
                }

                pbuf_free(msg->frame.pbuf);
            } else if (msg->type == MSG_COMMAND) {
                netdev = (struct xram_net *)msg->state;
                tx_config.len = msg->command.length;
                tx_config.buf = msg->command.payload;
                tx_config.type = XRAM_NET_MSG_TYPE_COMMAND;
                len = xram_net_output(netdev, &tx_config);
                vPortFree(msg->command.payload);
            }

            vPortFree(msg);
        } else {
            xram_log("xram tx fetch msg error\r\n");
        }
    }
}

#ifdef XRAM_CPU_E907
static void *eth_input_hook(bool is_sta, void *pkt, void *arg)
{
    xram_net_tx(pkt, is_sta, arg);
    return NULL;
}

static void *eth_output_hook(bool is_sta, void *pkt, void *arg)
{
    printf("dropping local TCP/IP stack traffic\r\n");
    return NULL;
}
#endif  // XRAM_CPU_E907

/**
 * @brief   Initialize the specified type of network card and bind netif
 * @note
 * @param   none
 * @retval  point of netdev
 */
int xram_net_dev_init(xram_net_dev_type_t type, struct netif *p_netif)
{
    int ret = -1;
    xram_net_t *net;

    if (!IS_XRAM_NET_DEV_TYPE(type)) {
        return -1;
    }
    net = &g_xram_netdev[XRAM_NETDEV_GET_INDEX(type)];
    net->type = type;

#ifdef XRAM_CPU_C906
    struct netif *netif = pvPortMalloc(sizeof(struct netif));
    assert(netif);

    ip4_addr_t ipaddr;
    ip4_addr_t netmask;
    ip4_addr_t gw;

    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;

    if (netif) {
        xram_log("Add netif\r\n");
        netifapi_netif_add(netif, &ipaddr, &netmask, &gw, (void *)net, &xram_stack_init, &tcpip_input);

        ret = 0;
    }

#endif  // XRAM_CPU_C906

#ifdef XRAM_CPU_E907
    xram_log("e907 bind net\r\n");

    /* Save netif */
    net->user = NULL;
    net->status = XRAM_NET_STATUS_UP;

    net->rnm = rnm_server_init(net, xram_tx_data, NULL, NULL);
    g_rnms = net->rnm;
    assert(net->rnm);
    bl_pkt_eth_input_hook_register(eth_input_hook, net);
    bl_pkt_eth_output_hook_register(eth_output_hook, NULL);

    ret = 0;
#endif  // XRAM_CPU_E907

    return ret;
}

/**
 * @brief
 * @note
 * @param
 * @retval
 */
int xram_net_ctrl(xram_net_t *netdev, xram_net_event_t event, void *arg)
{
    int ret = 0;

    switch (event) {
    case XRAM_NET_EVENT_GET_MAC:
        break;

    case XRAM_NET_EVENT_UP:
        netdev->status = XRAM_NET_STATUS_UP;
        // xram_rpc_set_status(status);
        break;

    case XRAM_NET_EVENT_RESET:
        // xram_rpc_netdev_reset();
        break;

    default:
        ret = -1;
    }

    return ret;
}

#ifdef XRAM_CPU_C906
static void xram_net_status_callback(struct netif *netif)
{
    printf(
        "[lwip] netif status %s %s\r\n"
        "  IP: %s\r\n",
        netif->flags & NETIF_FLAG_UP ? "UP" : "DOWN",
        netif->flags & NETIF_FLAG_LINK_UP ? "LINK_UP" : "LINK_DOWN",
        ip4addr_ntoa(netif_ip4_addr(netif)));
    printf("  MK: %s\r\n", ip4addr_ntoa(netif_ip4_netmask(netif)));
    printf("  GW: %s\r\n", ip4addr_ntoa(netif_ip4_gw(netif)));
}

static void rnm_async_event_cb(void *arg, rnm_base_msg_t *msg)
{
    xram_net_t *net = (xram_net_t *)arg;
    struct netif *netif = (struct netif *)net->user;

    if (msg->cmd == BF1B_CMD_STA_CONNECTED_IND) {
        if (net->status != XRAM_NET_STATUS_UP) {
            printf("STA connected\r\n");
            net->status = XRAM_NET_STATUS_UP;
            netifapi_netif_set_link_up(netif);
            netifapi_netif_set_up(netif);
            netifapi_dhcp_start(netif);
        }
    } else if (msg->cmd == BF1B_CMD_STA_DISCONNECTED_IND) {
        if (net->status != XRAM_NET_STATUS_DOWN) {
            printf("STA disconnected\r\n");
            net->status = XRAM_NET_STATUS_DOWN;
            netifapi_netif_set_link_down(netif);
            netifapi_netif_set_down(netif);
        }
    } else if (msg->cmd == BF1B_CMD_AP_STARTED_IND) {
        printf("AP started\r\n");
        net->status = XRAM_NET_STATUS_UP;
        netifapi_netif_set_link_up(netif);
        netifapi_netif_set_up(netif);
        void dhcpd_start(struct netif * netif);
        netifapi_netif_common(netif, dhcpd_start, NULL);
    } else if (msg->cmd == BF1B_CMD_AP_STOPPED_IND) {
        printf("AP stopped\r\n");
        err_t dhcp_server_stop(struct netif * netif);
        netifapi_netif_common(netif, NULL, dhcp_server_stop);
        net->status = XRAM_NET_STATUS_DOWN;
        netifapi_netif_set_link_down(netif);
        netifapi_netif_set_down(netif);
    }
}
#endif  // XRAM_CPU_C906

#ifdef XRAM_CPU_C906
err_t xram_stack_init(struct netif *netif)
{
    err_t ret = ERR_IF;

    xram_net_dev_type_t type;

    uint8_t mac_addr[6];
    xram_net_t *net = (xram_net_t *)netif->state;

    type = net->type;

    g_rnmc = rnm_client_init(net, xram_tx_data, net, rnm_async_event_cb);
    net->rnm = g_rnmc;
    assert(net->rnm);
    vTaskDelay(pdMS_TO_TICKS(100));
    assert(RNMC_OK == rnmc_get_mac_addr(net->rnm, mac_addr));
    memcpy(netif->hwaddr, mac_addr, 6);

    for (int i = 0; i < 6; i++) {
        net->mac[i] = netif->hwaddr[i];
    }

    snprintf(net->hostname,
             XRAM_NET_HOSTNAME_LEN,
             "Bouffalolab_%s-%02x%02x%02x",
             BL_CHIP_NAME,
             netif->hwaddr[3],
             netif->hwaddr[4],
             netif->hwaddr[5]);
    net->hostname[XRAM_NET_HOSTNAME_LEN - 1] = '\0';

    netif->name[0] = g_net_name[XRAM_NETDEV_GET_INDEX(type)][0];
    netif->name[1] = g_net_name[XRAM_NETDEV_GET_INDEX(type)][1];
    netif->hwaddr_len = 6;
    netif->mtu = 1500;
    netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;
    netif->state = (void *)net;
    netif->hostname = net->hostname;

    netif->output = etharp_output;
    netif->linkoutput = xram_net_tx;

    /* Save netif */
    net->user = (void *)netif;

    netif_set_status_callback(netif, xram_net_status_callback);

    netif_set_link_down(netif);
    netif_set_down(netif);
    netif_set_default(netif);
    net->status = XRAM_NET_STATUS_DOWN;

    ret = ERR_OK;

    return ret;
}
#endif  // XRAM_CPU_C906

/**
 * @brief Init netdev
 * @note
 * @param none
 * @retval 0 succ, 1 fail
 */
void xram_net_init(void *arg)
{
#ifdef XRAM_CPU_E907
    g_rbb_buf = mem_malloc(XRAM_NET_DATA_MAX_LEN);
    assert(g_rbb_buf);
#endif

    utils_rbb_init(g_rx_rbb_t, g_rbb_buf, XRAM_NET_DATA_MAX_LEN, (utils_rbb_blk_t)g_rbb_blk_desc, XRAM_ETH_RX_DESC_CNT);
    assert(g_rx_rbb_t);

    /* Initialize the RX POOL */
#ifdef XRAM_CPU_C906
    LWIP_MEMPOOL_INIT(RX_POOL);
#endif

    g_xram_tx_msg = xQueueCreate(TCPIP_MBOX_SIZE, sizeof(void *));
    assert(g_xram_tx_msg);

    /* Create xram net rx task */
    xTaskCreate(xram_net_task, "amp_eth_rx", 1024, NULL, 12, &g_rx_task);

    /* Create xram net rx task */
    xTaskCreate(xram_net_tx_thread, "amp_eth_tx", 1024, NULL, 13, &g_tx_task);

#if 0
  utils_rbb_cli_init();
#endif
}

static void cmd_net_send_pbuf_test(char *buf, int len, int argc, char **argv)
{
    static struct pbuf s_p = {0};
#ifdef XRAM_CPU_E907
    xram_net_t *xram_netdev = &g_xram_netdev[XRAM_NETDEV_GET_INDEX(XRAM_NET_DEV_TYPE_WIFI)];
    xram_net_tx(&s_p, true, xram_netdev);
#endif

#ifdef XRAM_CPU_C906
    struct netif *netif = netif_default;
    if (netif != NULL)
        xram_net_tx(netif, &s_p);
#endif
}

static void cmd_net_fw_test(char *buf, int len, int argc, char **argv)
{
    uint8_t open_fw = 0;

    if (argc > 1) {
        open_fw = atoi(argv[1]);

        if (open_fw > 0) {
            g_e907_out_flag = 1;
        } else {
            g_e907_out_flag = 0;
        }
    } else {
        printf("argv error\r\n");
    }
}

static void xram_tx_bench_thread(void *arg)
{
    err_t ret = ERR_OK;
    uint32_t s_total_recv = 0;
    uint32_t s_now = 0;
    uint32_t s_time = 0;

    uint32_t tick = ((uint32_t)arg) * 1000;
    uint32_t now = xTaskGetTickCount();
    struct pbuf *p;

    p = pbuf_alloc(PBUF_RAW, 1300, PBUF_RAM);

    printf("xram tx bench start %" PRId32 " s\r\n", (tick / 1000));

    do {
        if (p) {
#ifdef XRAM_CPU_E907
            xram_net_t *xram_netdev = &g_xram_netdev[XRAM_NETDEV_GET_INDEX(XRAM_NET_DEV_TYPE_WIFI)];
            ret = xram_net_tx(p, true, xram_netdev);
#endif

#ifdef XRAM_CPU_C906
            ret = xram_net_tx(netif_default, p);
#endif

            if (ret == ERR_OK) {
                s_total_recv += p->len;
                s_time = xTaskGetTickCount();

                if ((s_time - s_now) > 1000) {
                    float f_now;

                    f_now = (float)(s_total_recv)*8 / ((float)(s_time - s_now) / 1000) / 1000000;

                    printf("xram tx bench: %.4f Mbps. total %" PRId32 " time %" PRId32 "s\r\n",
                           f_now,
                           s_total_recv,
                           (s_time - now) / 1000);
                    s_total_recv = 0;
                    s_now = s_time;
                }
            }
        }
    } while ((xTaskGetTickCount() - now) < tick);

    pbuf_free(p);

    printf("xram tx bench finish\r\n");

    vTaskDelete(NULL);
}

static void cmd_xram_net_benchmark(char *buf, int len, int argc, char **argv)
{
    uint32_t duration = 10;

    if (argc > 1) {
        duration = atoi(argv[1]);
    }

    if (duration == 0) {
        printf("bench time error!\r\n");
        return;
    }

    xTaskCreate(xram_tx_bench_thread, "tx_bench", 512, (void *)duration, 10, &g_tx_bench_task);
}

static void cmd_xram_net_reset(char *buf, int len, int argc, char **argv)
{
    XRAMRingReset(XRAM_RING_ID_NET);
}

#ifdef XRAM_CPU_E907
static void cmd_rnm_dump(char *buf, int len, int argc, char **argv)
{
    rnms_statistic_dump(g_rnms);
}
#endif

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"xram_trigger", "send pbuf by xram net", cmd_net_send_pbuf_test},
    {"xram_switch", "switch e907 wifi fw", cmd_net_fw_test},
    {"xram_bench", "xram tx benchmark", cmd_xram_net_benchmark},
    {"xram_reset", "xram reset", cmd_xram_net_reset},
#ifdef XRAM_CPU_E907
    {"rnm_dump", "dump rnm statistic", cmd_rnm_dump},
#endif
};

#ifdef __cplusplus
}
#endif
