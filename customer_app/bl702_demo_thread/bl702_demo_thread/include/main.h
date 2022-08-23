#ifndef  __MAIN_H
#define  __MAIN_H

#include <openthread/thread.h>
#include <openthread/thread_ftd.h>
#include <openthread/icmp6.h>
#include <openthread/cli.h>
#include <openthread/ncp.h>
#include <openthread/coap.h>
#include <openthread_port.h>

#define THREAD_CHANNEL      18
#define THREAD_PANID        0xB702
#define THREAD_UDP_PORT     0xB702
#define THREAD_COAP_PORT    (THREAD_UDP_PORT + 2)

#define DEMO_UDP            1
#define DEMO_COAP           2

void app_gpioInit(void (*keyPress_handler)(void *));
void app_gpioLedOn(uint32_t index);
void app_gpioLedOff(uint32_t index);
uint32_t app_gpioGetKeyValue(void);

void app_sockInit(otInstance *instance, void (*handler)(uint32_t));
void app_udpSend(otInstance *instance, uint32_t val);

void app_coapInit (otInstance *instance, void (*handler)(uint32_t));
void app_coapReq(otInstance *instance, uint32_t val);


void ble_stack_start(void);

void app_task(void);

#endif // __DEMO_GPIO_H