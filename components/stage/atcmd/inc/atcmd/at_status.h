/*
 * Copyright (C) 2017 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of XRADIO TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _AT_STATUS_H_
#define _AT_STATUS_H_

#include "atcmd/at_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    at_text_t version[32]; /* 140128-caf4b79-SPWF01S SPWF01S Software Version */
    at_di_t reset_reason; /* 2 H/W reported reason for last reset
                                                                0 = POWER_ON
                                                                1 = WATCHDOG
                                                                2 = SOFT RESET
                                                                3 = LOW POWER
                                                                */
    at_di_t conf_flag; /* 5 Module HW revision */
    at_di_t system_uptime; /* 22006 System running time in seconds */
    at_di_t system_sleeptime; /* 500 System sleeping time in seconds */
    at_di_t gpio_enable; /* 0 Interrupt-enabled GPIO bitmask, expressed in base 10 */
    at_di_t captiveportal; /* 1 Mini AP enabled/disabled */
    at_di_t wifi_state; /* 10
                            0= Hardware power up
                            1=Hardware failure
                            2=Radio task terminated by user
                            3=Radio idle
                            4=Scan in progress
                            5=Scan complete
                            6=Join in progress
                            7=Joined
                            8=Access point started
                            9=802.11 handshake complete
                            10=Ready to transmit data (i.e. ¡°Link Up¡±)
                            */
    at_hex_t wifi_bssid[6]; /* 00:18:F8:3C:D9:18 BSSID of current association */
    at_di_t wifi_aid; /* 0 Association ID of current association */
    at_di_t wifi_channelnum; /* 11 Current radio channel number */
    at_hi_t wifi_sup_rate_mask; /* 0x003FFFCF Radio: supported data rate mask */
    at_hi_t wifi_bas_rate_mask; /* 0x0000000F AP reported: basic data rate mask */
    at_hi_t wifi_chan_activity2; /* 0x00003FFF Channels where we are allowed to transmit. Channel mask. i.e. 0x00003FFF => from channel 0 to channel 13 */
    at_di_t wifi_max_tx_power; /* 18 max allowed transmit power for the defined reg domain */
    at_di_t wifi_reg_country; /* IT Current regulatory domain */
    at_di_t wifi_dtim_period; /* 1 AP reported DTIM period (used in STA mode) */
    at_di_t wifi_sleeping; /* 0 Radio sleeping state (0 = active, 1 = sleep) */
    at_di_t wifi_num_assoc; /* 1 Number of the client associated to the module */
    at_ip_t ip_ipaddr; /* 192.168.121.184 Current IP address */
    at_ip_t ip_netmask; /* 255.255.252.0 Current IP netmask */
    at_ip_t ip_gw; /* 192.168.123.20 Current IP default gateway */
    at_ip_t ip_dns; /* 192.168.123.20 Current IP DNS server */
    at_di_t ip_sock_open; /* 0 Bitmask of Socket Client ID currently opened, expressed in base 10 (ip_sock_open=13 (00001101 in binary),
                           means that socket#0socket#2 and socket#3 are currently opened) */
    at_di_t ip_sockd_port; /* 0 Socket server port opened */
    at_di_t free_heap; /* 30472 Current free heap space */
    at_di_t min_heap; /* 26552 Minimum free heap space thus far */
    at_di_t current_time; /* 90643 Current time in seconds */
} at_status_t;

typedef struct {
    at_di_t link_id; /* 0 Identifier of the client */
    at_di_t state; /* 4
                    0 = Hardware Power Up
                    1 = HW link initialization
                    2 = Client Link identifier allocated
                    3 = Authenticated
                    4 = Associated
                    5 = Peer lost beacons
                    6 = Peer in power save state
                    */
    at_hex_t addr[6]; /* 90:18:7C:96:0D:0B MAC address of the client */
    at_di_t last_rx; /* 21244 Timestamp of last received packet */
    at_di_t last_tx; /* 21244 Timestamp of last transmitted packet */
    at_di_t rx_drops; /* 0 Count of frames dropped during reception */
    at_di_t tx_drops; /* 1 Count of frames dropped during transmission */
    at_di_t rx_pkts; /* 50 Count of received frames */
    at_di_t tx_pkts; /* 44 Count of transmitted frames */
    at_di_t tx_errs; /* 0 Count of errors detected during frame transmit */
    at_di_t rate_mask; /* 0x00003FCF AP reported Operational data rate mask */
    at_di_t cur_rate_idx; /* 3 Most significant byte of the rate_mask */
    at_di_t cur_rate_ok; /* 5 Counter to perform rate step up */
    at_di_t cur_rate_fail; /* 0 Counter to perform rate step down */
    at_di_t tx_consec_fail; /* 0 Counter to perform disassociation */
    at_hi_t rx_seqnum; /* 0x0000AF40 Sequence number of last RX directed frame */
    at_hi_t rx_seqnum_mc; /* 0x00000000 Sequence number of last RX multicast frame */
    at_di_t rx_rssi; /* -37 Signal strength of last received packet */
    at_di_t rx_rateidx; /* 0 Rate index of last received packet */
    at_di_t setprot; /* 0 Bitmask to indicate protection for TX (bit 1) and/or RX (bit 0) IEEE 802.11 frames */
    at_di_t listen_interval; /* 10 AP reported listen interval */
    at_hi_t capinfo; /* 0x00000000 Information about the AP capabilities */
} at_peer_t;

#ifdef __cplusplus
}
#endif

#endif
