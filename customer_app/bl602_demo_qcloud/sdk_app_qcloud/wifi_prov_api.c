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
#include "wifi_prov_api.h"

#include <string.h>
#include <stdio.h>
#include <FreeRTOS.h>

#include <vfs.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>

int wifi_prov_api_event_trigger_connect(struct wifi_conn *info)
{
    if (aos_post_event(EV_WIFI, CODE_WIFI_ON_PROV_CONNECT, (unsigned long)info) >= 0) {
        puts("[APP] [PROV] trigger CONNECT event OK\r\n");
    } else {
        puts("[APP] [PROV] trigger CONNECT event failed\r\n");
        return -1;
    }

    return 0;
}

int wifi_prov_api_event_trigger_disconnect(void)
{
    if (aos_post_event(EV_WIFI, CODE_WIFI_ON_PROV_DISCONNECT, 0) >= 0) {
        puts("[APP] [PROV] trigger DISCONNECT event OK\r\n");
    } else {
        puts("[APP] [PROV] trigger DISCONNECT event failed\r\n");
        return -1;
    }

    return 0;
}

int wifi_prov_api_event_trigger_scan(void(*complete)(void *))
{
    if (aos_post_event(EV_WIFI, CODE_WIFI_ON_PROV_SCAN_START, (unsigned long)complete) >= 0) {
        puts("[APP] [PROV] trigger scan event OK\r\n");
    } else {
        puts("[APP] [PROV] trigger scan event failed\r\n");
        return -1;
    }

    return 0;
}

int wifi_prov_api_event_state_get(void(*state_get)(void *))
{
    if (aos_post_event(EV_WIFI, CODE_WIFI_ON_PROV_STATE_GET, (unsigned long)state_get) >= 0) {
        puts("[APP] [PROV] trigger scan event OK\r\n");
    } else {
        puts("[APP] [PROV] trigger scan event failed\r\n");
        return -1;
    }

    return 0;
}
