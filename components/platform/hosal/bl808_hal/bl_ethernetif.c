/*
 * Copyright (c) 2016-2022 Bouffalolab.
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

/**
* @file
* Ethernet Interface Skeleton
*
*/

/*
* Copyright (c) 2001-2004 Swedish Institute of Computer Science.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 3. The name of the author may not be used to endorse or promote products
*    derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
* SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
*
* This file is part of the lwIP TCP/IP stack.
*
* Author: Adam Dunkels <adam@sics.se>
*
*/

/*
* This file is a skeleton for developing Ethernet network interface
* drivers for lwIP. Add code to the low_level functions and do a
* search-and-replace for the word "ethernetif" to replace it with
* something that better describes your network interface.
*/

#include "FreeRTOS.h"
#include "timers.h"

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/snmp.h"
#include "lwip/pbuf.h"
#include "netif/etharp.h"
#include "bl_ethernetif.h"
#include <bl808_ethmac.h>

#include <string.h>


/* The time to block waiting for input. */
#define emacBLOCK_TIME_WAITING_FOR_INPUT ( ( portTickType ) 100 )
#define netifMTU                                (1500)
#define netifINTERFACE_TASK_STACK_SIZE		( 1024 )
#define netifINTERFACE_TASK_PRIORITY		( configMAX_PRIORITIES - 2 )
#define netifGUARD_BLOCK_TIME			( 250 )
/* The time to block waiting for input. */
#define emacBLOCK_TIME_WAITING_FOR_INPUT	( ( portTickType ) 100 )

/* Define those to better describe your network interface. */
#define IFNAME0 'b'
#define IFNAME1 'l'

#define MAC_CRC_LEN     4
#define PKT_BUFFER_LEN  (1536)
static uint8_t pkt_rx_buffer[PKT_BUFFER_LEN] __attribute__ ((aligned(16))) = {0};
static uint8_t pkt_tx_buffer[PKT_BUFFER_LEN] __attribute__ ((aligned(16))) = {0};

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif {
  struct netif *netif; 
  phy_device phydev;
};

static struct pbuf *bl_low_level_input(struct netif *netif);

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function bl_low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
static void
bl_ethernetif_input(void *arg)
{
  struct netif *netif = (struct netif *)arg;
  struct ethernetif *ethernetif;
  struct eth_hdr    *ethhdr;
  struct pbuf       *p;

  ethernetif = netif->state;
  
  (void)ethernetif;
  (void)ethhdr;
 
  while(1) {
    /* move received packet into a new pbuf */
    p = bl_low_level_input(netif);
    /* if no packet could be read, silently ignore this */
    if (p != NULL) {
      /* pass all packets to ethernet_input, which decides what packets it supports */
      if (netif->input(p, netif) != ERR_OK) {
        LWIP_DEBUGF(NETIF_DEBUG, ("bl_ethernetif_input: IP input error\n"));
        pbuf_free(p);
        p = NULL;
      }
    }
  }
}

/**
* In this function, the hardware should be initialized.
* Called from ethernetif_init().
*
* @param netif the already initialized lwip network interface structure
*        for this ethernetif
*/
static void bl_low_level_init(struct netif *netif)
{
  LWIP_ASSERT("netif != NULL", (netif != NULL));

  struct ethernetif *ethernetif;
  phy_device *phy;

  ethernetif = netif->state;
  LWIP_ASSERT("ethernetif != NULL", (ethernetif != NULL));

  phy = &ethernetif->phydev;
  memset(phy, 0, sizeof(*phy));

  /* set netif MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set netif MAC hardware address */
  netif->hwaddr[0] = phy->mac_addr[0] = 0x18;
  netif->hwaddr[1] = phy->mac_addr[1] = 0xb9;
  netif->hwaddr[2] = phy->mac_addr[2] = 0x05;
  netif->hwaddr[3] = phy->mac_addr[3] = 0x00;
  netif->hwaddr[4] = phy->mac_addr[4] = 0x12;
  netif->hwaddr[5] = phy->mac_addr[5] = 0x34;

  /* set netif maximum transfer unit */
  netif->mtu = netifMTU;
  /* Accept broadcast address and ARP traffic */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;
  
  phy->addr        = ETHPHY_ADDR;
  phy->link        = 0;
  phy->autoneg     = AUTONEG_ENABLE;
  phy->speed       = SPEED_100;
  phy->duplex      = 1;
  phy->advertising = PHY_BASIC_FEATURES;
  phy->supported   = PHY_BASIC_FEATURES;
  phy->is_rmii     = true;

  ETHMAC_PhyInit(phy);
  //M88e1111s_config(phy);
  //M88e1111s_startup(phy);

  ETHMAC_Cfg_BD();
  ETHMAC_Cfg(phy);
  ETHMAC_IntMask(ETHMAC_INT_ALL, UNMASK);
  ETHMAC_Transmit_Enable();
  ETHMAC_Receive_Enable();
 
  printf("PHY initilize done.\r\n");
	
  // set interface up
  netif_set_link_up(netif);
  netif_set_up(netif);

  xTaskCreate(bl_ethernetif_input, "Eth_if", netifINTERFACE_TASK_STACK_SIZE, 
      (void *)netif, netifINTERFACE_TASK_PRIORITY, NULL);

#if 0

  s_pxNetIf =netif;

  /* create binary semaphore used for informing ethernetif of frame reception */
  if (s_xSemaphore == NULL)
  {
    vSemaphoreCreateBinary(s_xSemaphore);
    xSemaphoreTake( s_xSemaphore, 0);
  }

  /* initialize MAC address in ethernet MAC */ 
  ETH_MACAddressConfig(ETH_MAC_Address0, netif->hwaddr); 

  /* Initialize Tx Descriptors list: Chain Mode */
  ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
  /* Initialize Rx Descriptors list: Chain Mode  */
  ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

  /* Enable Ethernet Rx interrrupt */
  { 
    for(i=0; i<ETH_RXBUFNB; i++)
    {
      ETH_DMARxDescReceiveITConfig(&DMARxDscrTab[i], ENABLE);
    }
  }

#ifdef CHECKSUM_BY_HARDWARE
  /* Enable the checksum insertion for the Tx frames */
  {
    for(i=0; i<ETH_TXBUFNB; i++)
    {
      ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
    }
  } 
#endif

  /* create the task that handles the ETH_MAC */
  xTaskCreate(bl_ethernetif_input, (signed char*) "Eth_if", netifINTERFACE_TASK_STACK_SIZE, NULL,
              netifINTERFACE_TASK_PRIORITY,NULL);

    /* Enable MAC and DMA transmission and reception */
    ETH_Start();   
#endif
}


/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *
bl_low_level_input(struct netif *netif)
{
  LWIP_ASSERT("netif != NULL", (netif != NULL));

  struct ethernetif *ethernetif = netif->state;
  struct pbuf *p, *q;
  uint32_t len = 0;

  (void) ethernetif;
  /* Obtain the size of the packet and put it into the "len"
     variable. */
  // asm volatile ("CPSID I");
  taskENTER_CRITICAL();
  ETHMAC_BD_RX_dequeue(-1, &len, pkt_rx_buffer);
  // asm volatile ("CPSIE I");
  taskEXIT_CRITICAL();
  if (!len) {
		vTaskDelay(10);
    return NULL;
  }

#if ETH_PAD_SIZE
  len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

  len = len - MAC_CRC_LEN; //lwip no need MAC CRC
  
  /* We allocate a pbuf chain of pbufs from the pool. */
  p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

  if (p != NULL) {

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    /* We iterate over the pbuf chain until we have read the entire
     * packet into the pbuf. */
    for (q = p; q != NULL; q = q->next) {
      /* Read enough bytes to fill this pbuf in the chain. The
       * available data in the pbuf is given by the q->len
       * variable.
       * This does not necessarily have to be a memcpy, you can also preallocate
       * pbufs for a DMA-enabled MAC and after receiving truncate it to the
       * actually received size. In this case, ensure the tot_len member of the
       * pbuf is the sum of the chained pbuf len members.
       */
      // read data into(q->payload, q->len);
      memcpy(q->payload, pkt_rx_buffer + len - q->tot_len, q->len);
    }
    // XXX acknowledge that packet has been read();

    MIB2_STATS_NETIF_ADD(netif, ifinoctets, p->tot_len);
    if (((u8_t*)p->payload)[0] & 1) {
      /* broadcast or multicast packet*/
      MIB2_STATS_NETIF_INC(netif, ifinnucastpkts);
    } else {
      /* unicast packet*/
      MIB2_STATS_NETIF_INC(netif, ifinucastpkts);
    }
#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.recv);
  } else {
    //drop packet();
    LWIP_DEBUGF(NETIF_DEBUG, ("drop packet!\r\n"));

    LINK_STATS_INC(link.memerr);
    LINK_STATS_INC(link.drop);
    MIB2_STATS_NETIF_INC(netif, ifindiscards);
  }

  return p;
}

/**
* This function should do the actual transmission of the packet. The packet is
* contained in the pbuf that is passed to the function. This pbuf
* might be chained.
*
* @param netif the lwip network interface structure for this ethernetif
* @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
* @return ERR_OK if the packet could be sent
*         an err_t value if the packet couldn't be sent
*
* @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
*       strange results. You might consider waiting for space in the DMA queue
*       to become availale since the stack doesn't retry to send a packet
*       dropped because of memory failure (except for the TCP timers).
*/

static err_t bl_low_level_output(struct netif *netif, struct pbuf *p)
{
  LWIP_ASSERT("netif != NULL", (netif != NULL));
  LWIP_ASSERT("pbuf != NULL", (p != NULL));

  struct ethernetif *ethernetif = netif->state;
  struct pbuf *q;
  int len;
  
  (void) ethernetif;

  // XXX initiate transfer();

#if ETH_PAD_SIZE
  pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

  len = p->tot_len;
  for (q = p; q != NULL; q = q->next) {
    /* Send the data from the pbuf to the interface, one pbuf at a
       time. The size of the data in each pbuf is kept in the ->len
       variable. */
    // send data from(q->payload, q->len);
#ifdef ARCH_ARM
	asm ("PLD [%0, #32]"::"r" (q->payload));
	memcpy(pkt_tx_buffer + len - q->tot_len + 0x90000000, q->payload, q->len); /*FIXME :if MMU enable should add memory map*/
#endif
#ifdef ARCH_RISCV
	memcpy(pkt_tx_buffer + len - q->tot_len, q->payload, q->len);
#endif
  }
#if __riscv_xlen == 64
  csi_dcache_clean_range((uint64_t *)pkt_tx_buffer, (int64_t)len);
#endif
#if __riscv_xlen == 32
  csi_dcache_clean_range((uint32_t *)pkt_tx_buffer, (int32_t)len);
#endif

#if 0
  {
	  static const uint8_t test_frame[60] = {
	  	0xE4, 0x54, 0xE8, 0xB9, 0x45, 0xDA, 0x18, 0xB0, 0x09, 0x00, 0x12, 0x34, 0x08, 0x00,
	  	0x45, 0x00, 0x00, 0x22, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x11, 0x6B, 0x3D, 0x0A, 0x1C,
	  	0x1E, 0x28, 0x0A, 0x1C, 0x1E, 0x2D, 0x22, 0xB8, 0x27, 0x0F, 0x00, 0x0E, 0xCB, 0xE1,
	  	0x31, 0x32, 0x33, 0x34, 0x35, 0x36
	  };
	  ETHMAC_BD_TX_enqueue(-1, sizeof(test_frame), test_frame);
  }
#else
  // asm volatile ("CPSID I");
//  taskENTER_CRITICAL();
	while (ETHMAC_BD_TX_enqueue(-1, len, pkt_tx_buffer, true) == -16);
  // asm volatile ("CPSIE I");
//	taskEXIT_CRITICAL();
#endif

  // signal that packet should be sent();

  MIB2_STATS_NETIF_ADD(netif, ifoutoctets, p->tot_len);
  if (((u8_t*)p->payload)[0] & 1) {
    /* broadcast or multicast packet*/
    MIB2_STATS_NETIF_INC(netif, ifoutnucastpkts);
  } else {
    /* unicast packet */
    MIB2_STATS_NETIF_INC(netif, ifoutucastpkts);
  }
  /* increase ifoutdiscards or ifouterrors on error */

#if ETH_PAD_SIZE
  pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

  LINK_STATS_INC(link.xmit);
  return ERR_OK;
}

/**
* Should be called at the beginning of the program to set up the
* network interface. It calls the function bl_low_level_init() to do the
* actual setup of the hardware.
*
* This function should be passed as a parameter to netif_add().
*
* @param netif the lwip network interface structure for this ethernetif
* @return ERR_OK if the loopif is initialized
*         ERR_MEM if private data couldn't be allocated
*         any other err_t on error
*/
err_t bl_ethernetif_init(struct netif *netif)
{
  struct ethernetif *ethernetif;
  LWIP_ASSERT("netif != NULL", (netif != NULL));

  ethernetif = mem_malloc(sizeof(struct ethernetif));
  if (ethernetif == NULL) {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
    return ERR_MEM;
  }

  
  ethernetif->netif = netif;
#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  MIB2_INIT_NETIF(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);
  
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;

  netif->output = etharp_output;
  netif->linkoutput = bl_low_level_output;
  
  netif->state = (void *)ethernetif;

  /* initialize the hardware */
  bl_low_level_init(netif);
  return ERR_OK;
}
