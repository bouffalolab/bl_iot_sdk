/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2018>, <Huawei Technologies Co., Ltd>
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

#include "lwm2m_common.h"
#ifdef CONFIG_FEATURE_FOTA
    #include "ota/ota_api.h"
    #include "ota_port.h"
#endif

#include <osal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>


#define LWM2M_POWER_VOLTAGE     3800
#define LWM2M_BATTERY_LEVEL     90
#define LWM2M_MEMORY_FREE       50
#define LWM2M_NETWORK_BEARER    5
#define LWM2M_SIGNAL_STRENGTH   90
#define LWM2M_CELL_ID           21103
#define LWM2M_LINK_QUALITY      98
#define LWM2M_LINK_UTRILIZATION 10
#define LWM2M_POWER_SOURCE      1
#define LWM2M_POWER_CURRENT     125
#define LWM2M_LATITUDE          27.986065f
#define LWM2M_LONGITUDE         86.922623f
#define LWM2M_ALTITUDE          8495.0000f
#define LWM2M_RADIUS            0.0f
#define LWM2M_SPEED             0.0f
#define LWM2M_TIME_CODE         1367491215

typedef enum
{
    EN_LWM2M_MSG_APPWRITE = 0,  ///< we have received the application command data
    EN_LWM2M_MSG_APPDISCOVER,
    EN_LWM2M_MSG_APPEXECUTE,
    EN_LWM2M_MSG_SERVERREBS,    ///<we  have received the rebootstrap command from the platform
} en_lwm2m_msg_t;

fn_lwm2m_msg_deal s_default_dealer = NULL;

int lwm2m_cmd_register_dealer(fn_lwm2m_msg_deal dealer)
{
    s_default_dealer = dealer;
    return 0;
}

static int lwm2m_cmd_default(char *msg, int len, va_list valist)
{
    int op = va_arg(valist, int);
    const char *uri = va_arg(valist, const char *);

    if (NULL == uri)
    {
        return -1;
    }

    if (s_default_dealer)
    {
        return s_default_dealer(op, uri, msg, len);
    }
    else
    {
        printf("op: %d, uri: %s\n", op, uri);
    }

    return 0;
}

int lwm2m_get_manufacturer(char *manu, int len)
{
    (void)snprintf(manu, len, "Open Mobile Alliance");
    return LWM2M_OK;
}

int lwm2m_get_model_number(char *mode, int len)
{
    (void)snprintf(mode, len, "Lightweight M2M Client");
    return LWM2M_OK;
}

int lwm2m_get_serial_number(char *num, int len)
{
    (void)snprintf(num, len, "345000123");
    return LWM2M_OK;
}

int lwm2m_get_firmware_ver(char *version, int len)
{
    (void)snprintf(version, len, "example_ver001");
    return LWM2M_OK;
}

int lwm2m_do_dev_reboot(void)
{
    LINK_LOG_DEBUG("device is rebooting......\r\n");
    //LOS_TaskDelay(1000);
    osal_reboot();///< here may be we never comeback
    return LWM2M_OK;
}

int lwm2m_do_factory_reset(void)
{
    LINK_LOG_DEBUG("\n\t FACTORY RESET\r\n\n");
    return LWM2M_OK;
}

int lwm2m_get_power_source(int *arg)
{
    *arg = LWM2M_POWER_SOURCE;
    return LWM2M_OK;
}

int lwm2m_get_source_voltage(int *voltage)
{
    *voltage = LWM2M_POWER_VOLTAGE;
    return LWM2M_OK;
}

int lwm2m_get_power_current(int *arg)
{
    *arg = LWM2M_POWER_CURRENT;
    return LWM2M_OK;
}

int lwm2m_get_baterry_level(int *voltage)
{
    *voltage = LWM2M_BATTERY_LEVEL;
    return LWM2M_OK;
}

int lwm2m_get_memory_free(int *voltage)
{
    int tmp;
    //    (void)atiny_random(&tmp, sizeof(tmp));
    link_random(&tmp, sizeof(tmp));
    tmp %= 30;
    *voltage = LWM2M_MEMORY_FREE + tmp;
    return LWM2M_OK;
}

static int err_code = LWM2M_OK;

int lwm2m_get_dev_err(int *arg)
{
    *arg = err_code;
    return LWM2M_OK;
}

int lwm2m_do_reset_dev_err(void)
{
    err_code = LWM2M_OK;
    return LWM2M_OK;
}

static int64_t g_current_time = LWM2M_TIME_CODE;

int lwm2m_get_current_time(int64_t *arg)
{
    *arg = g_current_time + (int64_t)osal_sys_time() / 1000;
    return LWM2M_OK;
}

int lwm2m_set_current_time(const int64_t *arg)
{
    g_current_time = *arg - (int64_t)osal_sys_time() / 1000;
    return LWM2M_OK;
}

#define UTC_OFFSET_MAX_LEN 7
static char g_UTC_offset[UTC_OFFSET_MAX_LEN] = "+01:00";

int lwm2m_get_UTC_offset(char *offset, int len)
{
    if (len > strlen(g_UTC_offset) + 1)
    {
        (void)snprintf(offset, len, "%s", g_UTC_offset);
    }

    return LWM2M_OK;
}

int lwm2m_set_UTC_offset(const char *offset, int len)
{
    (void)snprintf(g_UTC_offset, len + 1, "%s", offset);
    return LWM2M_OK;
}

#define TIMEZONE_MAXLEN 25
static char g_timezone[TIMEZONE_MAXLEN] = "Europe/Berlin";

int lwm2m_get_timezone(char *timezone, int len)
{
    if (len > strlen(g_timezone) + 1)
    {
        (void)snprintf(timezone, len, "%s", g_timezone);
    }

    return LWM2M_OK;
}

int lwm2m_set_timezone(const char *timezone, int len)
{
    (void)snprintf(g_timezone, len + 1, "%s", timezone);
    return LWM2M_OK;
}

int lwm2m_get_bind_mode(char *mode, int len)
{
    LINK_LOG_DEBUG("bind type is UQ......\r\n");
    (void)snprintf(mode, len, "UQ");
    return LWM2M_OK;
}

int lwm2m_trig_firmware_update(void)
{
    LINK_LOG_DEBUG("firmware is updating......\r\n");
    return LWM2M_OK;
}

int lwm2m_get_firmware_result(int *result)
{
    *result = 0;
    return LWM2M_OK;
}

int lwm2m_get_firmware_state(int *state)
{
    *state = 0;
    return LWM2M_OK;
}

int lwm2m_get_network_bearer(int *network_brearer)
{
    *network_brearer = LWM2M_NETWORK_BEARER;
    return LWM2M_OK;
}

int lwm2m_get_signal_strength(int *singal_strength)
{
    *singal_strength = LWM2M_SIGNAL_STRENGTH;
    return LWM2M_OK;
}

int lwm2m_get_cell_id(long *cell_id)
{
    *cell_id = LWM2M_CELL_ID;
    return LWM2M_OK;
}

int lwm2m_get_link_quality(int *quality)
{
    *quality = LWM2M_LINK_QUALITY;
    return LWM2M_OK;
}

int lwm2m_get_link_utilization(int *utilization)
{
    *utilization = LWM2M_LINK_UTRILIZATION;
    return LWM2M_OK;
}

/*
int lwm2m_app_write(void *msg, int len)
{
    LINK_LOG_DEBUG("write num19 object success\r\n");
    lwm2m_receive(EN_LWM2M_MSG_APPWRITE,msg,len);
    return LWM2M_OK;
}

int lwm2m_app_execute(void *msg, int len)
{
    LINK_LOG_DEBUG("EXCUTE num19 object success\r\n");
    lwm2m_receive(EN_LWM2M_MSG_APPEXECUTE,msg,len);
    return LWM2M_OK;
}

int lwm2m_server_bootrigger(void *msg, int len)
{
    LINK_LOG_DEBUG("SERVER TRIGGERE BOOTSTRAP\r\n");
    lwm2m_receive(EN_LWM2M_MSG_SERVERREBS,msg,len);
    return LWM2M_OK;
}*/

int lwm2m_update_psk(char *psk_id, int len)
{
    //(void) memcpy_s(g_psk_value,psk_id,len,16);
    LINK_LOG_DEBUG("update psk success\r\n");
    return LWM2M_OK;
}

int lwm2m_get_latitude(float *latitude)
{
    *latitude = LWM2M_LATITUDE;
    return LWM2M_OK;
}

int lwm2m_get_longitude(float *longitude)
{
    *longitude = LWM2M_LONGITUDE;
    return LWM2M_OK;
}

int lwm2m_get_altitude(float *altitude)
{
    *altitude = LWM2M_ALTITUDE;
    return LWM2M_OK;
}

int lwm2m_get_radius(float *radius)
{
    *radius = LWM2M_RADIUS;
    return LWM2M_OK;
}

int lwm2m_get_speed(float *speed)
{
    *speed = LWM2M_SPEED;
    return LWM2M_OK;
}

int lwm2m_get_timestamp(uint64_t *timestamp)
{
    *timestamp = osal_sys_time() / 1000 + LWM2M_TIME_CODE;
    return LWM2M_OK;
}

//-----  3GPP TS 23.032 V11.0.0(2012-09) ---------
#define HORIZONTAL_VELOCITY                  0
#define HORIZONTAL_VELOCITY_VERTICAL         1
#define HORIZONTAL_VELOCITY_WITH_UNCERTAINTY 2

#define VELOCITY_OCTETS                      5

void location_get_velocity(lwm2m_velocity_s *velocity,
                           uint16_t bearing,
                           uint16_t horizontal_speed,
                           uint8_t speed_uncertainty)
{
    uint8_t tmp[VELOCITY_OCTETS];
    int copy_len;
    tmp[0] = HORIZONTAL_VELOCITY_WITH_UNCERTAINTY << 4;
    tmp[0] |= (bearing & 0x100) >> 8;
    tmp[1] = (bearing & 0xff);
    tmp[2] = horizontal_speed >> 8;
    tmp[3] = horizontal_speed & 0xff;
    tmp[4] = speed_uncertainty;
    copy_len = MAX_VELOCITY_LEN > sizeof(tmp) ? sizeof(tmp) : MAX_VELOCITY_LEN;
    (void) memcpy(velocity->opaque, tmp, copy_len);
    velocity->length = copy_len;
}

int lwm2m_get_velocity(lwm2m_velocity_s *velocity)
{
    location_get_velocity(velocity, 0, 0, 255);
    return LWM2M_OK;
}

int lwm2m_cmd_ioctl(lwm2m_cmd_e cmd, char *arg, int len, ...)
{
    int result = LWM2M_OK;
    va_list valist;

    switch (cmd)
    {
        case LWM2M_GET_MANUFACTURER:
            result = lwm2m_get_manufacturer(arg, len);
            break;

        case LWM2M_GET_MODEL_NUMBER:
            result = lwm2m_get_model_number(arg, len);
            break;

        case LWM2M_GET_SERIAL_NUMBER:
            result = lwm2m_get_serial_number(arg, len);
            break;

        case LWM2M_GET_FIRMWARE_VER:
            result = lwm2m_get_firmware_ver(arg, len);
            break;

        case LWM2M_DO_DEV_REBOOT:
            result = lwm2m_do_dev_reboot();
            break;

        case LWM2M_DO_FACTORY_RESET:
            result = lwm2m_do_factory_reset();
            break;

        case LWM2M_GET_POWER_SOURCE:
            result = lwm2m_get_power_source((int *)arg);
            break;

        case LWM2M_GET_SOURCE_VOLTAGE:
            result = lwm2m_get_source_voltage((int *)arg);
            break;

        case LWM2M_GET_POWER_CURRENT:
            result = lwm2m_get_power_current((int *)arg);
            break;

        case LWM2M_GET_BATERRY_LEVEL:
            result = lwm2m_get_baterry_level((int *)arg);
            break;

        case LWM2M_GET_MEMORY_FREE:
            result = lwm2m_get_memory_free((int *)arg);
            break;

        case LWM2M_GET_DEV_ERR:
            result = lwm2m_get_dev_err((int *)arg);
            break;

        case LWM2M_DO_RESET_DEV_ERR:
            result = lwm2m_do_reset_dev_err();
            break;

        case LWM2M_GET_CURRENT_TIME:
            result = lwm2m_get_current_time((int64_t *)arg);
            break;

        case LWM2M_SET_CURRENT_TIME:
            result = lwm2m_set_current_time((const int64_t *)arg);
            break;

        case LWM2M_GET_UTC_OFFSET:
            result = lwm2m_get_UTC_offset(arg, len);
            break;

        case LWM2M_SET_UTC_OFFSET:
            result = lwm2m_set_UTC_offset(arg, len);
            break;

        case LWM2M_GET_TIMEZONE:
            result = lwm2m_get_timezone(arg, len);
            break;

        case LWM2M_SET_TIMEZONE:
            result = lwm2m_set_timezone(arg, len);
            break;

        case LWM2M_GET_BINDING_MODES:
            result = lwm2m_get_bind_mode(arg, len);
            break;

        case LWM2M_GET_FIRMWARE_STATE:
            result = lwm2m_get_firmware_state((int *)arg);
            break;

        case LWM2M_GET_NETWORK_BEARER:
            result = lwm2m_get_network_bearer((int *)arg);
            break;

        case LWM2M_GET_SIGNAL_STRENGTH:
            result = lwm2m_get_signal_strength((int *)arg);
            break;

        case LWM2M_GET_CELL_ID:
            result = lwm2m_get_cell_id((long *)arg);
            break;

        case LWM2M_GET_LINK_QUALITY:
            result = lwm2m_get_link_quality((int *)arg);
            break;

        case LWM2M_GET_LINK_UTILIZATION:
            result = lwm2m_get_link_utilization((int *)arg);
            break;

        /*
        case LWM2M_WRITE_APP_DATA:
            result = lwm2m_app_write((int *)arg, len);
            break;
        case LWM2M_EXECUTE_APP_DATA:
            result = lwm2m_app_execute((int *)arg, len);
            break;
        */
        case LWM2M_UPDATE_PSK:
            result = lwm2m_update_psk(arg, len);
            break;

        case LWM2M_GET_LATITUDE:
            result = lwm2m_get_latitude((float *)arg);
            break;

        case LWM2M_GET_LONGITUDE:
            result = lwm2m_get_longitude((float *)arg);
            break;

        case LWM2M_GET_ALTITUDE:
            result = lwm2m_get_altitude((float *)arg);
            break;

        case LWM2M_GET_RADIUS:
            result = lwm2m_get_radius((float *)arg);
            break;

        case LWM2M_GET_SPEED:
            result = lwm2m_get_speed((float *)arg);
            break;

        case LWM2M_GET_TIMESTAMP:
            result = lwm2m_get_timestamp((uint64_t *)arg);
            break;

        case LWM2M_GET_VELOCITY:
            result = lwm2m_get_velocity((lwm2m_velocity_s *)arg);
            break;
#ifdef CONFIG_FEATURE_FOTA

        case LWM2M_GET_OTA_OPT:
        {
            ota_opt_s *opt = (ota_opt_s *)arg;
            hal_get_ota_opt(opt);
            opt->key.rsa_N = "C94BECB7BCBFF459B9A71F12C3CC0603B11F0D3A366A226FD3E73D453F96EFBBCD4DFED6D9F77FD78C3AB1805E1BD3858131ACB5303F61AF524F43971B4D429CB847905E68935C1748D0096C1A09DD539CE74857F9FDF0B0EA61574C5D76BD9A67681AC6A9DB1BB22F17120B1DBF3E32633DCE34F5446F52DD7335671AC3A1F21DC557FA4CE9A4E0E3E99FED33A0BAA1C6F6EE53EDD742284D6582B51E4BF019787B8C33C2F2A095BEED11D6FE68611BD00825AF97DB985C62C3AE0DC69BD7D0118E6D620B52AFD514AD5BFA8BAB998332213D7DBF5C98DC86CB8D4F98A416802B892B8D6BEE5D55B7E688334B281E4BEDDB11BD7B374355C5919BA5A9A1C91F";
            opt->key.rsa_E = "10001";
            result = LWM2M_OK;
            break;
        }

#endif
        /*
        case LWM2M_CMD_TRIGER_SERVER_INITIATED_BS:
            lwm2m_server_bootrigger(arg,len);
            result = LWM2M_OK;
            break;
	*/
        default:
            va_start(valist, len);
            result = lwm2m_cmd_default(arg, len, valist);
            va_end(valist);
            break;
    }

    return result;
}

void lwm2m_event_notify(lwm2m_event_e event, const char *arg, int len)
{
    LINK_LOG_DEBUG("notify:stat:%d\r\n", event);
}

