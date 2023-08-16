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

/* Define to prevent recursive inclusion */
#ifndef _XRAM_NET_H_
#define _XRAM_NET_H_

/* Includes ------------------------------------------------------------------*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "utils_list.h"
#include "xram.h"

#include "lwip/api.h"
#include "lwip/def.h"
#include "lwip/err.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/netif.h"


/* Macro define ------------------------------------------------------------- */

#define XRAM_NET_ALEN         6
#define XRAM_NET_NAME_LEN     8
#define XRAM_NET_HOSTNAME_LEN 32
#define XRAM_MBOX_MSG_LEN     8

#define EV_XRAM_NET (0x7269)

#define XRAM_NET_BENCH        0

#ifndef xram_log
#if 0
#define xram_log(M, ...) printf(M, ##__VA_ARGS__)
#else
#define xram_log(M, ...)
#endif
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum xram_chip
{
  XRAM_CHIP_C906 = 0,
  XRAM_CHIP_E907
} xram_chip_t;

#pragma pack(push, 1)

typedef enum xram_net_event
{
  XRAM_NET_EVENT_UP = 0xa7a0,
  XRAM_NET_EVENT_DOWN,
  XRAM_NET_EVENT_GET_STATUS,
  XRAM_NET_EVENT_GET_MAC,
  XRAM_NET_EVENT_SET_MAC,
  XRAM_NET_EVENT_RESET,
  XRAM_NET_EVENT_MAX
} xram_net_event_t;

#define IS_XRAM_NET_EVENT(x) ((x >= XRAM_NET_EVENT_UP) && (x < XRAM_NET_EVENT_MAX))

typedef enum xram_net_dev_type
{
  XRAM_NET_DEV_TYPE_WIFI = 0,
  XRAM_NET_DEV_TYPE_WIRED,
  XRAM_NET_DEV_TYPE_MAX
} xram_net_dev_type_t;

#define XRAM_NET_DEV_NUM_MAX     (XRAM_NET_DEV_TYPE_MAX)
#define XRAM_NETDEV_GET_INDEX(x) ((x) - XRAM_NET_DEV_TYPE_WIFI)
#define IS_XRAM_NET_DEV_TYPE(x)  ((x) < XRAM_NET_DEV_TYPE_MAX)

typedef enum xram_net_msg_type
{
  XRAM_NET_MSG_TYPE_COMMAND,
  XRAM_NET_MSG_TYPE_FRAME,
  XRAM_NET_MSG_TYPE_SNIFFER_PKT,
} xram_net_msg_type_t;

typedef struct xram_net_data_hdr
{
  uint32_t header; // should be named magic

  uint16_t type;   // LSB: major, of xram_net_msg_type_t
                   // MSB: minor, subtype, iface index, etc

  uint16_t flag;

  uint16_t len;

  uint16_t crc16;
} xram_net_data_hdr_t;

#define XRAM_NET_DATA_TYPE_MAJOR(x) ((x)->type & 0xff)
#define XRAM_NET_DATA_TYPE_MINOR(x) ((x)->type >> 8)
#define XRAM_NET_DATA_TYPE_MAKE(major, minor) ((major) | (((minor) << 8) & 0xff00))
#define XRAM_NET_DATA_HDR_LEN (sizeof(xram_net_data_hdr_t))

#define XRAM_NET_DATA_FLAG_FRAG     (0x1 << 0)
#define XRAM_NET_DATA_FLAG_AP_FRAME (0x1 << 1)
#define XRAM_NET_DATA_FLAG_SNIFFER_FRAME (0x1 << 2)
#define XRAM_NET_DATA_IS_FRAG(flag) ((flag & XRAM_NET_DATA_FLAG_FRAG) == XRAM_NET_DATA_FLAG_FRAG)

#pragma pack(pop)

typedef enum xram_net_status
{
  XRAM_NET_STATUS_DOWN = 0,
  XRAM_NET_STATUS_UP,
  XRAM_NET_STATUS_MAX
} xram_net_status_t;

#define IS_XRAM_NET_STATUS(x) ((x >= XRAM_NET_STATUS_DOWN) && (x < XRAM_NET_STATUS_MAX))

typedef enum
{
  XRAM_NET_MODE_STA,
  XRAM_NET_MODE_AP,
} xram_net_mode_t;

typedef struct xram_net
{
  utils_slist_t *type_node;

  xram_net_dev_type_t type;

  utils_slist_t *dev_node;

  uint8_t index;

  uint8_t mac[XRAM_NET_ALEN];

  char hostname[XRAM_NET_HOSTNAME_LEN];

  uint16_t status;

  /* Default maximum transmit unit advice */
  uint16_t mtu;

  /** This field can be set by the stack and could point
   *  to state information for netif. */
  void *user;

  void *rnm;
  xram_net_mode_t mode;
} xram_net_t;

#define IS_XRAM_NETDEV_UP(x) ((x->status) == XRAM_NET_STATUS_UP)

typedef struct xram_net_data_config
{
  uint32_t len;
  uint16_t type;
  uint16_t flag;
  uint8_t *buf;
} xram_net_data_config_t;

#define IS_XRAM_ETH_TX_DATA_VALID(x) ((x->len > 0) && (x->buf != NULL))

/* Exported constants --------------------------------------------------------*/

extern struct netif g_e907_netif;

extern volatile uint8_t g_e907_out_flag;

/* Exported functions ------------------------------------------------------- */

/**
 * @brief   Initialize the specified type of network card and bind netif
 * @note
 * @param   none
 * @retval  point of netdev
 */
err_t xram_stack_init(struct netif *netif);

/**
 * @brief   Protocol stack data is written to xram
 * @note
 * @param   netdev - Network card for data transmission
 *          tx_config - the config of tx data
 * @retval  ret - tx data len
 */
#ifdef XRAM_CPU_C906
err_t xram_net_tx(struct netif *netif, struct pbuf *p);
#endif
#ifdef XRAM_CPU_E907
err_t xram_net_tx(struct pbuf *p, bool is_sta, xram_net_t *net);
#endif

/**
 * @brief   xram tx thread
 * @note
 * @param
 * @retval
 */
void xram_net_tx_thread(void *arg);

/**
 * @brief Init netdev
 * @note
 * @param none
 * @retval 0 succ, 1 fail
 */
void xram_net_init(void *arg);

/**
 * @brief
 * @note
 * @param
 * @retval
 */
int xram_net_ctrl(xram_net_t *netdev, xram_net_event_t event, void *arg);

/**
 * @brief   Protocol stack data is written to xram
 * @note
 * @param   netdev - Network card for data transmission
 *          tx_config - the config of tx data
 * @retval  ret - tx data len
 */
int xram_net_output(xram_net_t *netdev, struct xram_net_data_config *tx_config);

/**
 * @brief   Initialize the specified type of network card and bind netif
 * @note
 * @param   none
 * @retval  point of netdev
 */
int xram_net_dev_init(xram_net_dev_type_t type, struct netif *p_netif);

#endif /* _HOSAL_NETDEV_H_ */
