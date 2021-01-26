/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

/**@defgroup agent AgentTiny
 * @defgroup agenttiny Agenttiny Definition
 * @ingroup agent
 */
#ifndef LWM2M_COMMON_H
#define LWM2M_COMMON_H
#include <stdbool.h>
#include <stdint.h>
#include <atiny_log.h>
#ifdef CONFIG_FEATURE_FOTA
    #include "ota/ota_api.h"
#endif
#include "liblwm2m_api.h"
#include <liblwm2m.h>

#include <lwm2m_al.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_REPORT_DATA_LEN         1024
#define MAX_BUFFER_REPORT_CNT       8
#define MAX_SEND_ERR_NUM            10
#define MAX_RECV_ERR_NUM            10

#define MAX_VELOCITY_LEN            16

#define DEVICE_AVL_POWER_SOURCES    "/3/0/6"
#define DEVICE_POWER_SOURCE_VOLTAGE "/3/0/7"
#define DEVICE_POWER_SOURCE_CURRENT "/3/0/8"
#define DEVICE_BATTERY_LEVEL        "/3/0/9"
#define DEVICE_MEMORY_FREE          "/3/0/10"

/******************The following interfaces are implemented by user***********************/

typedef enum
{
    LWM2M_GET_MANUFACTURER,
    LWM2M_GET_MODEL_NUMBER,
    LWM2M_GET_SERIAL_NUMBER,
    LWM2M_GET_FIRMWARE_VER,
    LWM2M_DO_DEV_REBOOT,
    LWM2M_DO_FACTORY_RESET,
    LWM2M_GET_POWER_SOURCE,
    LWM2M_GET_SOURCE_VOLTAGE,
    LWM2M_GET_POWER_CURRENT,
    LWM2M_GET_BATERRY_LEVEL,
    LWM2M_GET_MEMORY_FREE,
    LWM2M_GET_DEV_ERR,
    LWM2M_DO_RESET_DEV_ERR,
    LWM2M_GET_CURRENT_TIME,
    LWM2M_SET_CURRENT_TIME,
    LWM2M_GET_UTC_OFFSET,
    LWM2M_SET_UTC_OFFSET,
    LWM2M_GET_TIMEZONE,
    LWM2M_SET_TIMEZONE,
    LWM2M_GET_BINDING_MODES,
    LWM2M_GET_FIRMWARE_STATE,
    LWM2M_GET_NETWORK_BEARER,
    LWM2M_GET_SIGNAL_STRENGTH,
    LWM2M_GET_CELL_ID,
    LWM2M_GET_LINK_QUALITY,
    LWM2M_GET_LINK_UTILIZATION,
    LWM2M_WRITE_APP_DATA,
    LWM2M_EXECUTE_APP_DATA,
    LWM2M_UPDATE_PSK,
    LWM2M_GET_LATITUDE,
    LWM2M_GET_LONGITUDE,
    LWM2M_GET_ALTITUDE,
    LWM2M_GET_RADIUS,
    LWM2M_GET_SPEED,
    LWM2M_GET_TIMESTAMP,
    LWM2M_GET_VELOCITY,
    LWM2M_GET_OTA_OPT,
    LWM2M_CMD_TRIGER_SERVER_INITIATED_BS,
    LWM2M_CMD_MAX
} lwm2m_cmd_e;

typedef enum
{
    LWM2M_REG_OK,
    LWM2M_REG_FAIL,
    LWM2M_DATA_SUBSCRIBLE,
    LWM2M_DATA_UNSUBSCRIBLE,
    LWM2M_FOTA_STATE
} lwm2m_event_e;

typedef struct
{
    uint8_t opaque[MAX_VELOCITY_LEN];
    int     length;
} lwm2m_velocity_s;

typedef enum
{
    NOT_SENT = 0,
    SENT_WAIT_RESPONSE,
    SENT_FAIL,
    SENT_TIME_OUT,
    SENT_SUCCESS,
    SENT_GET_RST,
    SEND_PENDING,
} data_send_status_e;

typedef enum
{
    FIRMWARE_UPDATE_STATE = 0,
    APP_DATA
} lwm2m_report_type_e;

typedef void (*lwm2m_ack_callback)(lwm2m_report_type_e type, int cookie, data_send_status_e status);

typedef struct _data_report_t
{
    lwm2m_report_type_e type;     /* data type to report */
    int                 cookie;
    int                 len;      /* length of buf variable */
    uint8_t            *buf;      /* data buffer */
    lwm2m_ack_callback  callback; /* report ack callback */
} data_report_t;

typedef lwm2m_bootstrap_type_e   lwm2m_bootstrap_type_e;

typedef struct
{
    char                   *binding;        /*目前支持U或者UQ*/
    int                     life_time;      /*必选，默认50000,如过短，则频繁发送update报文，如过长，在线状态更新时间长*/
    unsigned int            storing_cnt;    /*storing为true时，lwm2m缓存区总字节个数*/
    lwm2m_bootstrap_type_e  bootstrap_mode; /* bootstrap mode  */
    int                     hold_off_time;  /* bootstrap hold off time for server initiated bootstrap */
} lwm2m_server_param_t;

typedef struct
{
    char           *server_ip;
    char           *server_port;
    char           *psk_Id;
    char           *psk;
    unsigned short  psk_len;

} lwm2m_security_param_t;

typedef struct
{

    lwm2m_server_param_t    server_params;

    //both iot_server and bs_server have psk & pskID, index 0 for iot_server, and index 1 for bs_server
    lwm2m_security_param_t  security_params[2];

    void                   *userData;
} lwm2m_param_t;

typedef struct
{
    char *endpoint_name;
    char *manufacturer;
    char *dev_type;
} lwm2m_device_info_t;

/**
 *@ingroup agenttiny
 *@brief issue the command.
 *
 *@par Description:
 *This API is used to issue the command.
 *@attention none.
 *
 *@param cmd            [IN]     The command to be issued. @ref atiny_cmd_e.
 *@param arg            [IN/OUT] Buffer to store the command parameters. Agent_tiny is responsible
                                 for memory allocation. if cmd is GET_XXX, arg is outcoming parameter
                                 and this buffer is filled by device; else arg is incoming parameter
                                 and this buffer is filled by agent_tiny.
 *@param len            [IN]     The length of the argument.
 *
 *@retval #int          0 if succeed, or the error number @ref atiny_error_e if failed.
 *@par Dependency: none.
 *@see none.
 */
int lwm2m_cmd_ioctl(lwm2m_cmd_e cmd, char *arg, int len, ...);

int lwm2m_cmd_register_dealer(fn_lwm2m_msg_deal dealer);

/**
 *@ingroup agenttiny
 *@brief issue the command.
 *
 *@par Description:
 *This API is used to issue the command.
 *@attention none.
 *
 *@param stat           [IN] The event to be issued. @ref atiny_event_e.
 *@param arg            [IN] Buffer to store the event parameters.
 *@param len            [IN] The length of the argument.
 *
 *@retval #int          0 if succeed, or the error number @ref atiny_error_e if failed.
 *@par Dependency: none.
 *@see none.
 */
void lwm2m_event_notify(lwm2m_event_e event, const char *arg, int len);

/**
 *@ingroup agenttiny
 *@brief reconnect lwm2m server.
 *
 *@par Description:
 *This API is used to reconnect lwm2m server.
 *@attention none.
 *
 *@param phandle        [IN] The handle of the agent_tiny.
 *
 *@retval #int          0 if succeed, or the error number @ref atiny_error_e if failed.
 *@par Dependency: none.
 *@see atiny_init | atiny_deinit.
 */
int lwm2m_reconnect_ex(void *phandle);

int add_security_object_instance(lwm2m_object_t *obj, int object_instance_id, void *param);
int add_server_object_instance(lwm2m_object_t *obj, int object_instance_id, void *param);
int add_access_control_object_instance(lwm2m_object_t *obj);
int add_device_object_instance(lwm2m_object_t *obj, int object_instance_id);
int add_connectivity_monitoring_object_instance(lwm2m_object_t *obj, int object_instance_id);
int add_firmware_update_object_instance(lwm2m_object_t *obj, int object_instance_id);
int add_location_object_instance(lwm2m_object_t *obj, int object_instance_id);
int add_app_data_object_instance(lwm2m_object_t *obj, void *obj_instance, int object_instance_id, uint16_t resource_id, void *param);

int config_security_object(lwm2m_object_t *obj, void *param);
int config_server_object(lwm2m_object_t *obj, void *param);
int config_access_control_object(lwm2m_object_t *obj, void *param);
int config_device_object(lwm2m_object_t *obj, void *param);
int config_connectivity_monitoring_object(lwm2m_object_t *obj, void *param);
int config_firmware_update_object(lwm2m_object_t *obj, void *param);
int config_location_object(lwm2m_object_t *obj, void *param);
int config_app_data_object(lwm2m_object_t *obj, void *param);

#ifdef __cplusplus
}
#endif

#endif

