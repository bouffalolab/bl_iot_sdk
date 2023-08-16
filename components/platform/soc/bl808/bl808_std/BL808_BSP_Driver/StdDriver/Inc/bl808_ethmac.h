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
#ifndef __BL808_ETHMAC_H__
#define __BL808_ETHMAC_H__

#include "bl808_common.h"
#include "ethmac_reg.h"
#include "bd_reg.h"



#define ETHPHY_ADDR 0x01

#define PHY_FIXED_ID		0xa5a55a5a

#define PHY_MAX_ADDR 32

#define PHY_FLAG_BROKEN_RESET	(1 << 0) /* soft reset not supported */

#define PHY_DEFAULT_FEATURES	(SUPPORTED_Autoneg | \
				 SUPPORTED_TP | \
				 SUPPORTED_MII)

#define PHY_10BT_FEATURES	(SUPPORTED_10baseT_Half | \
				 SUPPORTED_10baseT_Full)

#define PHY_100BT_FEATURES	(SUPPORTED_100baseT_Half | \
				 SUPPORTED_100baseT_Full)

#define PHY_1000BT_FEATURES	(SUPPORTED_1000baseT_Half | \
				 SUPPORTED_1000baseT_Full)

#define PHY_BASIC_FEATURES	(PHY_10BT_FEATURES | \
				 PHY_100BT_FEATURES | \
				 PHY_DEFAULT_FEATURES)

#define PHY_GBIT_FEATURES	(PHY_BASIC_FEATURES | \
				 PHY_1000BT_FEATURES)

#define PHY_10G_FEATURES	(PHY_GBIT_FEATURES | \
				SUPPORTED_10000baseT_Full)

#define PHY_ANEG_TIMEOUT	4000


/* Indicates what features are supported by the interface. */
#define SUPPORTED_10baseT_Half		(1 << 0)
#define SUPPORTED_10baseT_Full		(1 << 1)
#define SUPPORTED_100baseT_Half		(1 << 2)
#define SUPPORTED_100baseT_Full		(1 << 3)
#define SUPPORTED_1000baseT_Half	(1 << 4)
#define SUPPORTED_1000baseT_Full	(1 << 5)
#define SUPPORTED_Autoneg		(1 << 6)
#define SUPPORTED_TP			(1 << 7)
#define SUPPORTED_AUI			(1 << 8)
#define SUPPORTED_MII			(1 << 9)
#define SUPPORTED_FIBRE			(1 << 10)
#define SUPPORTED_BNC			(1 << 11)
#define SUPPORTED_10000baseT_Full	(1 << 12)
#define SUPPORTED_Pause			(1 << 13)
#define SUPPORTED_Asym_Pause		(1 << 14)
#define SUPPORTED_2500baseX_Full	(1 << 15)
#define SUPPORTED_Backplane		(1 << 16)
#define SUPPORTED_1000baseKX_Full	(1 << 17)
#define SUPPORTED_10000baseKX4_Full	(1 << 18)
#define SUPPORTED_10000baseKR_Full	(1 << 19)
#define SUPPORTED_10000baseR_FEC	(1 << 20)
#define SUPPORTED_1000baseX_Half	(1 << 21)
#define SUPPORTED_1000baseX_Full	(1 << 22)

/* Indicates what features are advertised by the interface. */
#define ADVERTISED_10baseT_Half		(1 << 0)
#define ADVERTISED_10baseT_Full		(1 << 1)
#define ADVERTISED_100baseT_Half	(1 << 2)
#define ADVERTISED_100baseT_Full	(1 << 3)
#define ADVERTISED_1000baseT_Half	(1 << 4)
#define ADVERTISED_1000baseT_Full	(1 << 5)
#define ADVERTISED_Autoneg		(1 << 6)
#define ADVERTISED_TP			(1 << 7)
#define ADVERTISED_AUI			(1 << 8)
#define ADVERTISED_MII			(1 << 9)
#define ADVERTISED_FIBRE		(1 << 10)
#define ADVERTISED_BNC			(1 << 11)
#define ADVERTISED_10000baseT_Full	(1 << 12)
#define ADVERTISED_Pause		(1 << 13)
#define ADVERTISED_Asym_Pause		(1 << 14)
#define ADVERTISED_2500baseX_Full	(1 << 15)
#define ADVERTISED_Backplane		(1 << 16)
#define ADVERTISED_1000baseKX_Full	(1 << 17)
#define ADVERTISED_10000baseKX4_Full	(1 << 18)
#define ADVERTISED_10000baseKR_Full	(1 << 19)
#define ADVERTISED_10000baseR_FEC	(1 << 20)
#define ADVERTISED_1000baseX_Half	(1 << 21)
#define ADVERTISED_1000baseX_Full	(1 << 22)

/* The forced speed, 10Mb, 100Mb, gigabit, 2.5Gb, 10GbE. */
#define SPEED_10		10
#define SPEED_100		100
#define SPEED_1000		1000
#define SPEED_2500		2500
#define SPEED_10000		10000

/* Duplex, half or full. */
#define DUPLEX_HALF		0x00
#define DUPLEX_FULL		0x01

/* Which connector port. */
#define PORT_TP			0x00
#define PORT_AUI		0x01
#define PORT_MII		0x02
#define PORT_FIBRE		0x03
#define PORT_BNC		0x04
#define PORT_DA			0x05
#define PORT_NONE		0xef
#define PORT_OTHER		0xff

/* Which transceiver to use. */
#define XCVR_INTERNAL		0x00
#define XCVR_EXTERNAL		0x01
#define XCVR_DUMMY1		0x02
#define XCVR_DUMMY2		0x03
#define XCVR_DUMMY3		0x04

/* Enable or disable autonegotiation.  If this is set to enable,
 * the forced link modes above are completely ignored.
 */
#define AUTONEG_DISABLE		0x00
#define AUTONEG_ENABLE		0x01

/* Mode MDI or MDI-X */
#define ETH_TP_MDI_INVALID	0x00
#define ETH_TP_MDI		0x01
#define ETH_TP_MDI_X		0x02

/* Wake-On-Lan options. */
#define WAKE_PHY		(1 << 0)
#define WAKE_UCAST		(1 << 1)
#define WAKE_MCAST		(1 << 2)
#define WAKE_BCAST		(1 << 3)
#define WAKE_ARP		(1 << 4)
#define WAKE_MAGIC		(1 << 5)
#define WAKE_MAGICSECURE	(1 << 6) /* only meaningful if WAKE_MAGIC */

/* L2-L4 network traffic flow types */
#define	TCP_V4_FLOW	0x01	/* hash or spec (tcp_ip4_spec) */
#define	UDP_V4_FLOW	0x02	/* hash or spec (udp_ip4_spec) */
#define	SCTP_V4_FLOW	0x03	/* hash or spec (sctp_ip4_spec) */
#define	AH_ESP_V4_FLOW	0x04	/* hash only */
#define	TCP_V6_FLOW	0x05	/* hash only */
#define	UDP_V6_FLOW	0x06	/* hash only */
#define	SCTP_V6_FLOW	0x07	/* hash only */
#define	AH_ESP_V6_FLOW	0x08	/* hash only */
#define	AH_V4_FLOW	0x09	/* hash or spec (ah_ip4_spec) */
#define	ESP_V4_FLOW	0x0a	/* hash or spec (esp_ip4_spec) */
#define	AH_V6_FLOW	0x0b	/* hash only */
#define	ESP_V6_FLOW	0x0c	/* hash only */
#define	IP_USER_FLOW	0x0d	/* spec only (usr_ip4_spec) */
#define	IPV4_FLOW	0x10	/* hash only */
#define	IPV6_FLOW	0x11	/* hash only */
#define	ETHER_FLOW	0x12	/* spec only (ether_spec) */

/* L3-L4 network traffic flow hash options */
#define	RXH_L2DA	(1 << 1)
#define	RXH_VLAN	(1 << 2)
#define	RXH_L3_PROTO	(1 << 3)
#define	RXH_IP_SRC	(1 << 4)
#define	RXH_IP_DST	(1 << 5)
#define	RXH_L4_B_0_1	(1 << 6) /* src port in case of TCP/UDP/SCTP */
#define	RXH_L4_B_2_3	(1 << 7) /* dst port in case of TCP/UDP/SCTP */
#define	RXH_DISCARD	(1 << 31)

#define	RX_CLS_FLOW_DISC	0xffffffffffffffffULL


typedef enum {
    ETHMAC_INT_TX,                             /*!< TX buffer interrupt */
    ETHMAC_INT_RX,                             /*!< RX buffer interrupt */
    ETHMAC_INT_TX_ERROR,                       /*!< TX error interrupt */
    ETHMAC_INT_RX_ERROR,                       /*!< RX error interrupt */
    ETHMAC_INT_BUSY,                           /*!< Busy interrupt */
    ETHMAC_INT_ALL,                            /*!< All the interrupt */
} ETHMAC_INT_Type;


#define IS_ETHMAC_INT_TYPE(type)               ((signed int)type >= 0 && type <= ETHMAC_INT_ALL)

#define BD_TX_CS_POS                     (0)  /*!< Carrier Sense Lost */
#    define BD_TX_CS_LEN                     (1)
#define BD_TX_DF_POS                     (1)  /*!< Defer Indication */
#    define BD_TX_DF_LEN                     (1)
#define BD_TX_LC_POS                     (2)  /*!< Late Collision */
#    define BD_TX_LC_LEN                     (1)
#define BD_TX_RL_POS                     (3)  /*!< Retransmission Limit */
#    define BD_TX_RL_LEN                     (1)
#define BD_TX_RTRY_POS                   (4)  /*!< Retry Count */
#    define BD_TX_RTRY_LEN                   (4)
#define BD_TX_UR_POS                     (8)  /*!< Underrun */
#    define BD_TX_UR_LEN                     (1)
#define BD_TX_EOF_POS                    (10)  /*!< EOF */
#    define BD_TX_EOF_LEN                     (1)
#define BD_TX_CRC_POS                    (11) /*!< CRC Enable */
#    define BD_TX_CRC_LEN                    (1)
#define BD_TX_PAD_POS                    (12) /*!< PAD enable */
#    define BD_TX_PAD_LEN                    (1)
#define BD_TX_WR_POS                     (13) /*!< Wrap */
#    define BD_TX_WR_LEN                     (1)
#define BD_TX_IRQ_POS                    (14) /*!< Interrupt Request Enable */
#    define BD_TX_IRQ_LEN                    (1)
#define BD_TX_RD_POS                     (15) /*!< The data buffer is ready for transmission or is currently being transmitted. You are not allowed to change it */
#    define BD_TX_RD_LEN                     (1)
#define BD_TX_LEN_POS                    (16) /*!< TX Data buffer length */
#    define BD_TX_LEN_LEN                    (16)

#define BD_RX_LC_POS                     (0)  /*!< Late Collision */
#    define BD_RX_LC_LEN                     (1)
#define BD_RX_CRC_POS                    (1)  /*!< RX CRC Error */
#    define BD_RX_CRC_LEN                    (1)
#define BD_RX_SF_POS                     (2)  /*!< Short Frame */
#    define BD_RX_SF_LEN                     (1)
#define BD_RX_TL_POS                     (3)  /*!< Too Long */
#    define BD_RX_TL_LEN                     (1)
#define BD_RX_DN_POS                     (4)  /*!< Dribble Nibble */
#    define BD_RX_DN_LEN                     (1)
#define BD_RX_RE_POS                     (5)  /*!< Receive Error */
#    define BD_RX_RE_LEN                     (1)
#define BD_RX_OR_POS                     (6)  /*!< Overrun */
#    define BD_RX_OR_LEN                     (1)
#define BD_RX_M_POS                      (7)  /*!< Miss */
#    define BD_RX_M_LEN                      (1)
#define BD_RX_CF_POS                     (8)  /*!< Control Frame Received */
#    define BD_RX_CF_LEN                     (1)
#define BD_RX_WR_POS                     (13) /*!< Wrap */
#    define BD_RX_WR_LEN                     (1)
#define BD_RX_IRQ_POS                    (14) /*!< Interrupt Request Enable */
#    define BD_RX_IRQ_LEN                    (1)
#define BD_RX_E_POS                      (15) /*!< The data buffer is empty (and ready for receiving data) or currently receiving data */
#    define BD_RX_E_LEN                      (1)
#define BD_RX_LEN_POS                    (16) /*!< RX Data buffer length */
#    define BD_RX_LEN_LEN                    (16)

#define ETHMAC_BD_FIELD_MSK(field)       (((1U << BD_##field##_LEN) - 1) << BD_##field##_POS)
#define ETHMAC_BD_FIELD_UMSK(field)      (~(((1U << BD_##field##_LEN) - 1) << BD_##field##_POS))

#define ETHMAC_TX_COMMON_FLAGS (ETHMAC_BD_FIELD_MSK(TX_RD)  | \
                                ETHMAC_BD_FIELD_MSK(TX_IRQ) | \
                                ETHMAC_BD_FIELD_MSK(TX_PAD) | \
                                ETHMAC_BD_FIELD_MSK(TX_EOF) | \
                                ETHMAC_BD_FIELD_MSK(TX_CRC) )

#define ETHMAC_RX_COMMON_FLAGS (ETH_MAX_PACKET_SIZE << 16)  | \
                                ETHMAC_BD_FIELD_MSK(RX_IRQ) )

typedef enum _BD_TYPE_ {
    EMAC_BD_TYPE_INVLAID,
    EMAC_BD_TYPE_TX,
    EMAC_BD_TYPE_RX,
    EMAC_BD_TYPE_NONE,
    EMAC_BD_TYPE_MAX = 0x7FFFFFFF
} ETHMAC_BD_TYPE_e;

typedef struct {
    uint32_t C_S_L;                         /*!< Buffer Descriptors(BD) control,status,length */
    uint32_t Buffer;                        /*!< BD buffer address */
}ETHMAC_BD_Desc_Type;

typedef struct {
    ETHMAC_BD_Desc_Type *bd;                /*!< Tx descriptor header pointer */
    uint8_t txIndexEMAC;                  /*!< TX index: EMAC */
    uint8_t txIndexCPU;                   /*!< TX index: CPU/SW */
    uint8_t txBuffLimit;                  /*!< TX index max */
    uint8_t rsv0;
    uint8_t rxIndexEMAC;                  /*!< RX index: EMAC */
    uint8_t rxIndexCPU;                   /*!< RX index: CPU/SW */
    uint8_t rxBuffLimit;                  /*!< RX index max */
    uint8_t rsv1;
}ETHMAC_Handle_Type;

typedef struct blphy_device {
	/* forced speed & duplex (no autoneg)
	 * partner speed & duplex & pause (autoneg)
	 */
	int speed;
	int duplex;

	/* The most recently read link state */
	int link;
	int port;

	uint32_t advertising;
	uint32_t supported;
	uint32_t mmds;
	uint8_t mac_addr[6];

	int autoneg;
	int addr;
	int pause;
	int asym_pause;
	uint32_t phy_id;
	// 
	bool is_c45;
	// 是否是RMII接口
	bool is_rmii;
	uint32_t flags;
} phy_device;

int M88e1111s_startup(phy_device *phydev);
int M88e1111s_config(phy_device *phydev);
int ETHMAC_PhyInit(phy_device *phydev);
int ETHMAC_Cfg(phy_device *phydev);
int ETHMAC_Cfg_BD(void);
int ETHMAC_Transmit_Enable(void);
int ETHMAC_Receive_Enable(void);
void ETHMAC_IntMask(ETHMAC_INT_Type intType, BL_Mask_Type intMask);

int ETHMAC_DMADescListInit(ETHMAC_Handle_Type *handle,uint8_t *txBuff, uint32_t txBuffCount,uint8_t *rxBuff, uint32_t rxBuffCount);
int ETHMAC_BD_RX_enqueue(uint32_t index);
int ETHMAC_BD_RX_dequeue(uint32_t flags, uint32_t *len, uint8_t *data_out);
int ETHMAC_BD_TX_enqueue(uint32_t flags, uint32_t len, const uint8_t *data_in, bool no_copy);
int ETHMAC_BD_TX_dequeue(uint32_t index);
uint32_t ETHMAC_BD_Get_CurActive(ETHMAC_BD_TYPE_e bdt);

void ETHMAC_IRQHandler(void);


#endif /* __BL808_ETHMAC_H__ */

