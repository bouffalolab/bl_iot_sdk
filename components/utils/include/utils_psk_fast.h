#ifndef __UTILS_PSK_FAST_H__
#define __UTILS_PSK_FAST_H__

int utils_wifi_psk_cal_fast(char *password, char *ssid, int ssid_len, char *output);
int utils_wifi_psk_cal_fast_bin(char *password, unsigned char *ssid, int ssidlength, unsigned char *output);

#endif /* __UTILS_PSK_FAST_H__ */
