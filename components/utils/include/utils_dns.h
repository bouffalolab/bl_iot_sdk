#ifndef __UTILS_DNS_H__
#define __UTILS_DNS_H__
#include <stdint.h>
int utils_dns_domain_get(uint8_t *records, uint8_t *buf, int *len);
#endif
