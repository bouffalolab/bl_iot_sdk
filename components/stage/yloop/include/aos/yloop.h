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

#ifndef AOS_YLOOP_H
#define AOS_YLOOP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <event_type_code.h>

#ifndef AOS_DOXYGEN_MODE

/* special event filter */
#define EV_ALL                       0
#define EV_FLAG_URGENT               0x8000

/* system event */
#define EV_SYS                       0x0001
#define CODE_SYS_ON_STARTING         1
#define CODE_SYS_ON_START_COMPLETED  2
#define CODE_SYS_ON_START_FAILED     4
#define CODE_SYS_ON_IDLE             3
#define CODE_SYS_ON_START_UOTA       5
#define CODE_SYS_ON_ALINK_ONLINE     6
#define CODE_SYS_ON_ALINK_OFFLINE    7
#define CODE_SYS_ON_MQTT_READ        8
#define CODE_SYS_ON_COAP_AUTHED      9

/* WiFi event */
#define  EV_WIFI                  0x0002
#define  CODE_WIFI_ON_INIT_DONE   1
#define  CODE_WIFI_ON_MGMR_DONE   2
#define  CODE_WIFI_CMD_RECONNECT  3
#define  CODE_WIFI_ON_CONNECTED   4
#define  CODE_WIFI_ON_DISCONNECT  5
#define  CODE_WIFI_ON_PRE_GOT_IP  6
#define  CODE_WIFI_ON_GOT_IP      7
#define  CODE_WIFI_ON_CONNECTING  8
#define  CODE_WIFI_ON_SCAN_DONE   9
#define  CODE_WIFI_ON_SCAN_DONE_ONJOIN  10
#define  CODE_WIFI_ON_AP_STARTED        11
#define  CODE_WIFI_ON_AP_STOPPED        12
#define  CODE_WIFI_ON_PROV_SSID         13
#define  CODE_WIFI_ON_PROV_BSSID        14
#define  CODE_WIFI_ON_PROV_PASSWD       15
#define  CODE_WIFI_ON_PROV_CONNECT      16
#define  CODE_WIFI_ON_PROV_DISCONNECT   17
#define  CODE_WIFI_ON_PROV_SCAN_START   18
#define  CODE_WIFI_ON_PROV_STATE_GET    19
#define  CODE_WIFI_ON_MGMR_DENOISE      20
#define  CODE_WIFI_ON_AP_STA_ADD        21
#define  CODE_WIFI_ON_AP_STA_DEL        22
#define  CODE_WIFI_ON_EMERGENCY_MAC     23
#define  CODE_WIFI_ON_EXIT_PS           24
#define  CODE_WIFI_ON_GOT_IP6           25
#define  CODE_WIFI_ON_SET_PS_DONE       26

/* Network Event */
#define EV_NETWORK EV_WIFI
#define CODE_ON_DISCONNECT CODE_WIFI_ON_DISCONNECT
#define CODE_ON_GOT_IP CODE_WIFI_ON_GOT_IP

/* Mesh event */
#define  EV_MESH                  0x0003

/* Mudule event */
#define EV_ADCKEY                   0x0010
#define CODE_ADCKEY_INT_TRIGGER     1

/* user app start 0x1000 - 0x7fff */
#define EV_USER     0x1000

/** uData event */
#define EV_UDATA                           0x0004
#define CODE_UDATA_DEV_READ                1
#define CODE_UDATA_DEV_IOCTL               2
#define CODE_UDATA_DEV_OPEN                3
#define CODE_UDATA_DEV_CLOSE               4
#define CODE_UDATA_DEV_ENABLE              5
#define CODE_UDATA_DEV_DISABLE             6
#define CODE_UDATA_SERVICE_SUBSRIBE        7 /* for external component */
#define CODE_UDATA_SERVICE_UNSUBSRIBE      8 /* for external component */
#define CODE_UDATA_SERVICE_PROCESS         9
#define CODE_UDATA_SERVICE_IOCTL           10
#define CODE_UDATA_REPORT_PUBLISH          11
#define CODE_UDATA_DATA_PUBLISH            12
#define CODE_UDATA_DATA_SUBSCRIB           13

/* CLI Event */
#define EV_CLI                             0x0005
#define CODE_CLI_DATA_RAW                  1
#endif

/* IR event */
#define  EV_IR                             0x0006
#define  CODE_IR_RECEIVE_NEC               1
#define  CODE_IR_RECEIVE_NEC_REPEAT        2

typedef struct {
    /* The time event is generated, auto filled by aos event system */
    uint32_t time;
    /* Event type, value < 0x1000 are used by aos system */
    uint16_t type;
    /* Defined according to type */
    uint16_t code;
    /* Defined according to type/code */
    unsigned long value;
    /* Defined according to type/code */
    unsigned long extra;
} input_event_t;

/* Event callback */
typedef void (*aos_event_cb)(input_event_t *event, void *private_data);
/* Delayed execution callback */
typedef void (*aos_call_t)(void *arg);
/* Delayed execution callback */
typedef void (*aos_poll_call_t)(int fd, void *arg);

/**
 * Register system event filter callback.
 *
 * @param[in]  type  event type interested.
 * @param[in]  cb    system event callback.
 * @param[in]  priv  private data past to cb.
 *
 * @return  the operation status, 0 is OK, others is error.
 */
int aos_register_event_filter(uint16_t type, aos_event_cb cb, void *priv);

/**
 * Unregister native event callback.
 *
 * @param[in]  type  event type interested.
 * @param[in]  cb    system event callback.
 * @param[in]  priv  private data past to cb.
 *
 * @return  the operation status, 0 is OK, others is error.
 */
int aos_unregister_event_filter(uint16_t type, aos_event_cb cb, void *priv);

/**
 * Post local event.
 *
 * @param[in]  type   event type.
 * @param[in]  code   event code.
 * @param[in]  value  event value.
 *
 * @return  the operation status, 0 is OK,others is error.
 */
int aos_post_event(uint16_t type, uint16_t code, unsigned long  value);

/**
 * Register a poll event in main loop.
 *
 * @param[in]  fd      poll fd.
 * @param[in]  action  action to be executed.
 * @param[in]  param   private data past to action.
 *
 * @return  the operation status, 0 is OK,others is error.
 */
int aos_poll_read_fd(int fd, aos_poll_call_t action, void *param);

/**
 * Cancel a poll event to be executed in main loop.
 *
 * @param[in]  fd      poll fd.
 * @param[in]  action  action to be executed.
 * @param[in]  param   private data past to action.
 */
void aos_cancel_poll_read_fd(int fd, aos_poll_call_t action, void *param);

/**
 * Post a delayed action to be executed in main loop.
 *
 * @param[in]  ms      milliseconds to wait.
 * @param[in]  action  action to be executed.
 * @param[in]  arg     private data past to action.
 *
 * @return  the operation status, 0 is OK,others is error.
 */
int aos_post_delayed_action(int ms, aos_call_t action, void *arg);

/**
 * Cancel a delayed action to be executed in main loop.
 *
 * @param[in]  ms      milliseconds to wait, -1 means don't care.
 * @param[in]  action  action to be executed.
 * @param[in]  arg     private data past to action.
 */
void aos_cancel_delayed_action(int ms, aos_call_t action, void *arg);


/**
 * Schedule a callback in next event loop.
 * Unlike aos_post_delayed_action,
 * this function can be called from non-aos-main-loop context.

 * @param[in]  action  action to be executed.
 * @param[in]  arg     private data past to action.
 *
 * @return  the operation status, <0 is error,others is OK.
 */
int aos_schedule_call(aos_call_t action, void *arg);

typedef void *aos_loop_t;

/**
 * Init a per-task event loop.
 *
 * @return  the handler of aos_loop_t,NULL failure,others success.
 */
aos_loop_t aos_loop_init(void);

/**
 * Get current event loop.
 *
 * @return  default event loop.
 */
aos_loop_t aos_current_loop(void);

/**
 * Start event loop.
 */
void aos_loop_run(void);

/**
 * Exit event loop, aos_loop_run() will return.
 */
void aos_loop_exit(void);

/**
 * Free event loop resources.
 */
void aos_loop_destroy(void);

/**
 * Schedule a callback specified event loop.
 *
 * @param[in]  loop    event loop to be scheduled, NULL for default main loop.
 * @param[in]  action  action to be executed.
 * @param[in]  arg     private data past to action.
 *
 * @return  the operation status, <0 is error,others is OK.
 */
int aos_loop_schedule_call(aos_loop_t *loop, aos_call_t action, void *arg);

/**
 * Schedule a work to be executed in workqueue.
 *
 * @param[in]  ms       milliseconds to delay before execution, 0 means immediately.
 * @param[in]  action   action to be executed.
 * @param[in]  arg1     private data past to action.
 * @param[in]  fini_cb  finish callback to be executed after action is done in current event loop.
 * @param[in]  arg2     data past to fini_cb.
 *
 * @return  work handle,NULL failure,others is OK.
 */
void *aos_loop_schedule_work(int ms, aos_call_t action, void *arg1,
                             aos_call_t fini_cb, void *arg2);

/**
 * Cancel a work.
 *
 * @param[in]  work    work to be cancelled.
 * @param[in]  action  action to be executed.
 * @param[in]  arg1    private data past to action.
 */
void aos_cancel_work(void *work, aos_call_t action, void *arg1);

#ifdef __cplusplus
}
#endif

#endif /* AOS_YLOOP_H */

