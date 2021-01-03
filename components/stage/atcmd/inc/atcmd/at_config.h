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

#ifndef _AT_CONFIG_H_
#define _AT_CONFIG_H_

#include "atcmd/at_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {

    at_di_t CIPMUX;
    at_di_t apDhcp;
    at_di_t staDhcp;

    at_di_t link_type[5]; // 0 TCP 1UDP


    at_text_t nv_manuf[32]; /* ST TEXT[32] Manufacturer ID string */
    at_text_t nv_model[32]; /* SPWF01Sxyz TEXT[32] Manufacturer model string */
    at_text_t nv_serial[32]; /* 1214003 TEXT[32] Manufacturer serial number */
    at_hex_t nv_wifi_macaddr[6]; /* 02:4D:53:4D:00:01 HEX[6] Manufacturer assigned 802.11 MAC Address */

    at_di_t blink_led; /* 0 INT Enable/disable the blinking led (default=0) */
    at_hi_t wind_off_low; /* 0x00000000 INT Wind 0:31 mask 0xFFFFFFFF are disabled all the 32 Wind indicator */
    at_hi_t wind_off_medium; /* 0x00000000 INT Wind 32:63 mask */
    at_hi_t wind_off_high; /* 0x00000000 INT Wind 64:95 mask */

    at_text_t user_desc[64]; /* anonymous TEXT[64] Free form textual field for host use (used as basic authentication during Mini AP configuration) */
    at_text_t escape_seq[8]; /* at+s. TEXT[8] Escape sequence from data mode to command mode */
    at_di_t localecho1; /* 1 INT Echo command input: 0=off, 1=on */
    at_di_t console1_speed; /* 115200 INT Serial port speed: from 9600 to 921600, default: 115200 */
    at_di_t console1_hwfc; /* 0 INT Hardware flow control: 0=off, 1=on */
    at_di_t console1_enabled; /* 1 INT Enable console on UART1 */
    at_di_t sleep_enabled; /* 0 INT Enable/disable the sleep mode */
    at_di_t standby_enabled; /* 0 INT Enable/disable the standby mode */
    at_di_t standby_time; /* 10 INT Standby mode time, in seconds. Up to 232-1 sec */
    at_di_t wifi_tx_msdu_lifetime; /* 0 INT MSDU lifetime. From 0 to 2^32-1 TUs (1 TUs= 1024¦Ìs). Zero is default (automatic) */
    at_di_t wifi_rx_msdu_lifetime; /* 0 INT MSDU lifetime. From 0 to 2^32-1 TUs (1 TUs= 1024¦Ìs). Zero is default (automatic) */
    at_hi_t wifi_operational_mode; /* 0x00000011 INT Allows choosing Doze (11) or quiescent (12) power device modes */
    at_di_t wifi_beacon_wakeup; /* 1 INT Set the wakeup interval of the WLAN device, from 1 to 255 if wifi_listen_interval = 0; from 1 to 65535 if wifi_listen_interval = 1 */
    at_di_t wifi_beacon_interval; /* 100 INT Beaconing interval in MiniAP mode, from 0 to 2^16-1 */

    at_di_t wifi_listen_interval; /* 0 INT Define the wakeup mode (0 = sleep up to the beacon_wakeup specified, 1 = sleep at least to the beacon_wakeup specified) */
    at_di_t wifi_rts_threshold; /* 3000 INT Frame size over which RTS/CTS is used. Limit: from 0 to 3000 */
    at_hex_t wifi_ssid[33]; /* 50:72:6F:64:75:63:74:69:6F:6E:31:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 HEX[32] Desired SSID specified in hex. All 32 octets should be written. Note that wifi_ssid_len must also be set. */
    at_di_t wifi_ssid_len; /* 11 INT Length of the actual SSID in the 32 byte buffer */
    at_di_t wifi_channelnum; /* 6 INT Channel number to use for MiniAP operation. The user must properly set the channel number to not violate IEEE 802.11 Wi-Fi/WLAN standards. */

    at_hi_t wifi_opr_rate_mask; /* 0xFFFFFFFF INT Operational data rate mask, 0xffffffff is allenabled:
                                    BIT0: 1 Mbps    BIT1: 2 Mbps    BIT2: 5.5 Mbps  BIT3: 11 Mbps   BIT6: 6 Mbps    BIT7: 9 Mbps
                                    BIT8: 12 Mbps   BIT9: 18 Mbps   BIT10: 24 Mbps  BIT11: 36 Mbps  BIT12: 48 Mbps  BIT13: 54 Mbps
                                                                                                        */
    at_hi_t wifi_bas_rate_mask; /* 0x0000000F INT Basic data rate mask, 0x0000000f is [1,2,5.5,11] */
    at_di_t wifi_mode; /* 1 INT Radio Mode.
                                            0=IDLE,
                                            1=STA (Supported Security Modes: OPEN,WEP OpenSystem,WEP SharedKey,WPA/WPA2),
                                            2=MiniAP (Supported Security Modes: OPEN, WEP OpenSystem -Supported Classes: b,g)
                                            3=IBSS(Supported Security Modes: OPEN, WEP OpenSystem, WEP SharedKey);
                                            */
    at_di_t wifi_auth_type; /* 0 INT Authentication type used in IBSS mode:
                                                                            0=OpenSystem,
                                                                            1=SharedKey
                                                                            */
    at_di_t wifi_powersave; /* 1 INT Allows choosing between Active (0), PS (1) or Fast-PS (2) */
    at_di_t wifi_tx_power; /* 18 INT Transmit power [from 0 to 18], in dBm */
    at_di_t wifi_rssi_thresh; /* -50 INT Low signal strength threshold */
    at_di_t wifi_rssi_hyst; /* 10 INT Amount of change in RSSI to trigger signal state change */


    at_di_t wifi_ap_idle_timeout; /* 120 INT Seconds of inactivity to trigger disassociate of the client */
    at_di_t wifi_beacon_loss_thresh; /* 10 INT Number of consecutive loss beacon to detect the AP disassociation */
    at_di_t wifi_priv_mode; /* 2 INT Privacy Mode: 0=none,1=WEP, 2=WPAPersonal (TKIP/AES) or WPA2-Personal (TKIP/AES) */
    at_hex_t wifi_wep_keys[4][16]; /*
                                    wifi_wep_keys[1] 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 HEX[16] WEP key buffer
                                    wifi_wep_keys[1] 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 HEX[16] WEP key buffer
                                    wifi_wep_keys[2] 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 HEX[16] WEP key buffer
                                    wifi_wep_keys[3] 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 HEX[16] WEP key buffer
                                    */
    at_hex_t wifi_wep_key_lens[4]; /* 00:00:00:00 HEX[4] Four octets specifying the length of the actual key data in each WEP key buffer.*/
    at_di_t wifi_wep_default_key; /* 0 INT Default WEP key used for authentication */
    at_hex_t wifi_wpa_psk_raw[32]; /* 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00 HEX[32] Pre-calculated PSK key */

    at_text_t wifi_wpa_psk_text[65]; /* a_psk_pass TEXT[64] WPA(2) PSK passphrase, if set the actual PSK will be generated from this.Used in STA, IBSS and MiniAP. */
    at_di_t ip_use_dhcp; /* 1 INT DHCP server on/off. Used in STA, IBSS and MiniAP.
                                  0=off (in STA mode: the variables ip_ipaddr, ip_netmask and ip_gw must be properly set to connect to the AP),
                                  1=on (in STA mode: the ipaddr, netmask and gw will be provided by the AP),
                                  2=on&customize (in MiniAP mode: user can customize the ip_ipaddr of the MiniAP, the ip_address of the client is automatically assigned by the MiniAP)
                                  */
    at_di_t ip_use_httpd; /* 1 INT HTTP server on/off.0=off, 1=on */
    at_di_t ip_mtu; /* 1500 INT IP maximum transmission unit size. Limit: from 634 to 2412 (1500 for maximum compatibility with Ethernet networks) */
    at_text_t ip_hostname[32]; /* iwm-02-09-97 TEXT[32] IP local hostname */
    at_text_t ip_apdomainname[32]; /* captiveportal.net TEXT[32] IP domain name in Mini AP mode.
                                   If the AP domain name is not quickly opened, it¡¯s suggested to turn off an eventual proxy server (check the connection settings of the device or the browser preferences).
                                    */
    at_ip_t ip_ipaddr; /* 192.168.0.50 IP IP address for static usage (DHCP off) */
    at_ip_t ip_netmask; /* 255.255.255.0 IP IP netmask for static usage (DHCP off) */
    at_ip_t ip_gw; /* 192.168.0.1 IP IP default gateway for static usage (DHCP off) */
    at_ip_t ip_dns; /* 192.168.0.1 IP IP DNS server for static usage (DHCP off) */
    at_di_t ip_http_get_recv_timeout; /* 1000 INT HTTP_GET connection timeout in milliseconds */
    at_di_t ip_dhcp_timeout; /* 20 INT DHCP client timeout, in seconds */
    at_di_t ip_sockd_timeout; /* 250 INT Socket server - buffer timeout management (from 5 ms to 250 ms) Warning: 250 ms is suggested to avoid data loss */
} at_config_t;

extern at_config_t at_cfg;

#ifdef __cplusplus
}
#endif

#endif
