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

#include "lwm2m_fota_manager.h"
#include "lwm2m_fota_state.h"
#include <string.h>
#include "firmware_update.h"
//#include "ota/package.h"

struct lwm2m_fota_manager_tag_s
{
    char                           *pkg_uri;
    lwm2m_fota_state_e              state;
    lwm2m_update_result_e           update_result;
    lwm2m_fota_idle_state_s         idle_state;
    lwm2m_fota_downloading_state_s  downloading_state;
    lwm2m_fota_downloaded_state_s   downloaded_state;
    lwm2m_fota_updating_state_s     updating_state;
    lwm2m_fota_state_s             *current;
    pack_storage_device_api_s      *device;
    lwm2m_context_t                *lwm2m_context;
    uint32_t                        cookie;
    bool                            wait_ack_flag;
    lwm2m_fota_state_e              rpt_state;
    ota_opt_s                       ota_opt;
    bool                            init_flag;
};

#define PULL_ONLY 0

static uint32_t g_firmware_cookie = 0;


char *lwm2m_fota_manager_get_pkg_uri(const lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return NULL);
    return thi->pkg_uri;
}
int lwm2m_fota_manager_get_state(const lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return LWM2M_FOTA_IDLE);
    return thi->state;
}

int lwm2m_fota_manager_get_rpt_state(const lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return LWM2M_FOTA_IDLE);
    return thi->rpt_state;
}

int lwm2m_fota_manager_get_update_result(const lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return LWM2M_FIRMWARE_UPDATE_NULL);
    return thi->update_result;
}
void lwm2m_fota_manager_set_update_result(lwm2m_fota_manager_s *thi, lwm2m_update_result_e result)
{
    ASSERT_THIS(return);
    thi->update_result = result;
}

int lwm2m_fota_manager_get_deliver_method(const lwm2m_fota_manager_s *thi)
{
    return
        PULL_ONLY;
}
int lwm2m_fota_manager_start_download(lwm2m_fota_manager_s *thi, const char *uri, uint32_t len)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (thi->state != thi->rpt_state)
    {
        ATINY_LOG(LOG_ERR, "start download busy state %u rpt state %u",
                  thi->state, thi->rpt_state);
        return LWM2M_ERR;
    }

    if ((NULL == thi->current) || (NULL == uri))
    {
        ATINY_LOG(LOG_ERR, "null pointer");
        return LWM2M_ERR;
    }

    if (thi->pkg_uri)
    {
        osal_free(thi->pkg_uri);
        thi->pkg_uri = NULL;
    }

    thi->pkg_uri = osal_malloc(len + 1);

    if (NULL == thi->pkg_uri)
    {
        ATINY_LOG(LOG_ERR, "lwm2m_strdup fail");
        return LWM2M_ERR;
    }

    (void) memcpy(thi->pkg_uri, uri, len);
    thi->pkg_uri[len] = '\0';
    ATINY_LOG(LOG_INFO, "start download");
    return thi->current->start_download(thi->current, thi->pkg_uri);
}
int lwm2m_fota_manager_execute_update(lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (thi->state != thi->rpt_state)
    {
        ATINY_LOG(LOG_ERR, "execute update busy state %u rpt state %u",
                  thi->state, thi->rpt_state);
        return LWM2M_ERR;
    }

    if (NULL == thi->current)
    {
        ATINY_LOG(LOG_ERR, "current null pointer");
        return LWM2M_ERR;
    }

    ATINY_LOG(LOG_INFO, "excecute update");
    return thi->current->execute_update(thi->current);
}

int lwm2m_fota_manager_finish_download(lwm2m_fota_manager_s *thi, int result)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (thi->state != thi->rpt_state)
    {
        ATINY_LOG(LOG_ERR, "finish download busy state %u rpt state %u",
                  thi->state, thi->rpt_state);
        return LWM2M_ERR;
    }

    if (NULL == thi->current)
    {
        ATINY_LOG(LOG_ERR, "current null pointer");
        return LWM2M_ERR;
    }

    ATINY_LOG(LOG_INFO, "finish download result %d", result);
    return thi->current->finish_download(thi->current, result);
}
int lwm2m_fota_manager_repot_result(lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (NULL == thi->current)
    {
        ATINY_LOG(LOG_ERR, "current null pointer");
        return LWM2M_ERR;
    }

    return thi->current->repot_result(thi->current);
}


int lwm2m_fota_manager_set_state(lwm2m_fota_manager_s *thi, lwm2m_fota_state_e state)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (state > LWM2M_FOTA_UPDATING)
    {
        ATINY_LOG(LOG_ERR, "invalid download state %d", state);
        return LWM2M_ARG_INVALID;
    }

    ATINY_LOG(LOG_INFO, "download stat from %d to %d", thi->state, state);

    if (thi->state != state)
    {
        /*lint -e614 */
        lwm2m_fota_state_s *states[LWM2M_FOTA_UPDATING + 1];
        states[LWM2M_FOTA_IDLE] = LWM2M_GET_STATE(thi->idle_state);
        states[LWM2M_FOTA_DOWNLOADING] = LWM2M_GET_STATE(thi->downloading_state);
        states[LWM2M_FOTA_DOWNLOADED] = LWM2M_GET_STATE(thi->downloaded_state);
        states[LWM2M_FOTA_UPDATING] = LWM2M_GET_STATE(thi->updating_state);
        thi->current = states[state];
        thi->state = state;
        thi->wait_ack_flag = false;
        /*lint +e614 */
    }

    thi->rpt_state = state;
    lwm2m_event_notify(LWM2M_FOTA_STATE, (const char *)&thi->state, sizeof(thi->state));
    return LWM2M_OK;
}

int lwm2m_fota_manager_rpt_state(lwm2m_fota_manager_s *thi, lwm2m_fota_state_e rpt_state)
{
    lwm2m_uri_t uri;
    const char *uri_str = "/5/0/3";
    ASSERT_THIS(return LWM2M_ARG_INVALID);
    lwm2m_fota_manager_save_rpt_state(thi, rpt_state);
    (void) memset((void *)&uri, 0, sizeof(uri));
    (void)lwm2m_stringToUri(uri_str, strlen(uri_str), &uri);
    lwm2m_resource_value_changed(thi->lwm2m_context, &uri);
    return LWM2M_OK;
}

void lwm2m_fota_manager_save_rpt_state(lwm2m_fota_manager_s *thi, lwm2m_fota_state_e rpt_state)
{
    ASSERT_THIS(return);
    ATINY_LOG(LOG_INFO, "rpt download state %d", rpt_state);
    thi->rpt_state = rpt_state;
    thi->wait_ack_flag = true;
    thi->cookie = g_firmware_cookie++;
}


static int lwm2m_fota_manager_flag_read(void *buf, int32_t len)
{
    int (*read_flash)(ota_flash_type_e type, void *buf, int32_t len, uint32_t location) =
        lwm2m_fota_manager_get_instance()->ota_opt.read_flash;

    if (read_flash)
    {
        return read_flash(OTA_UPDATE_INFO, buf, len, 0);
    }

    ATINY_LOG(LOG_ERR, "write_flash null");
    return -1;
}

static int lwm2m_fota_manager_flag_write(const void *buf, int32_t len)
{
    int (*write_flash)(ota_flash_type_e type, const void *buf, int32_t len, uint32_t location) =
        lwm2m_fota_manager_get_instance()->ota_opt.write_flash;

    if (write_flash)
    {
        return write_flash(OTA_UPDATE_INFO, buf, len, 0);
    }

    ATINY_LOG(LOG_ERR, "write_flash null");
    return -1;
}


int lwm2m_fota_manager_set_storage_device(lwm2m_fota_manager_s *thi)
{
    int ret;
    //    flag_op_s flag_op;
    //    pack_params_s pack_param;
    ASSERT_THIS(return LWM2M_ARG_INVALID);
    ret = lwm2m_cmd_ioctl(LWM2M_GET_OTA_OPT, (char *)&thi->ota_opt, sizeof(thi->ota_opt));

    if (LWM2M_OK != ret)
    {
        ATINY_LOG(LOG_FATAL, "lwm2m_cmd_ioctl fail");
        return ret;
    }

    //    flag_op.func_flag_read = atiny_fota_manager_flag_read;
    //    flag_op.func_flag_write = atiny_fota_manager_flag_write;
    //    (void)flag_init(&flag_op);
    //    ret = flag_upgrade_init();
    //    if (ret != ATINY_OK)
    //    {
    //        ATINY_LOG(LOG_FATAL, "flag_upgrade_init fail");
    //        return ret;
    //    }
    //    (void) memcpy(&pack_param.ota_opt, &thi->ota_opt, sizeof(pack_param.ota_opt));
    //    pack_param.malloc = osal_malloc;
    //    pack_param.free = osal_free;
    //    pack_param.printf = printf;
    //    ret = pack_init_device(&pack_param);
    //    if (ret != ATINY_OK)
    //    {
    //        ATINY_LOG(LOG_FATAL, "pack_init_device fail");
    //        return ret;
    //    }
    thi->device = pack_get_device();
    return lwm2m_fota_idle_state_int_report_result(&thi->idle_state);
}

pack_storage_device_api_s *lwm2m_fota_manager_get_storage_device(lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return NULL);
    return thi->device;
}


void lwm2m_fota_manager_update_notify(firmware_update_rst_e rst, void *param)
{
    lwm2m_fota_manager_s *thi = (lwm2m_fota_manager_s *)param;
    (void)lwm2m_fota_manager_finish_download(thi, rst);
}
void lwm2m_fota_manager_init(lwm2m_fota_manager_s *thi)
{
    (void) memset(thi, 0, sizeof(*thi));
    lwm2m_fota_idle_state_init(&thi->idle_state, thi);
    lwm2m_fota_downloading_state_init(&thi->downloading_state, thi);
    lwm2m_fota_downloaded_state_init(&thi->downloaded_state, thi);
    lwm2m_fota_updating_state_init(&thi->updating_state, thi);
    thi->current = LWM2M_GET_STATE(thi->idle_state);
    set_firmware_update_notify(lwm2m_fota_manager_update_notify, thi);
    lwm2m_event_notify(LWM2M_FOTA_STATE, (const char *)&thi->state, sizeof(thi->state));
    thi->init_flag = true;
}

void lwm2m_fota_manager_destroy(lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return);

    if (thi->pkg_uri)
    {
        osal_free(thi->pkg_uri);
    }

    /*lint -e668 */
    (void) memset(thi, 0, sizeof(*thi));
    /*lint +e668 */
}

int lwm2m_fota_manager_set_lwm2m_context(lwm2m_fota_manager_s *thi, lwm2m_context_t  *lwm2m_context)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);
    thi->lwm2m_context = lwm2m_context;
    return LWM2M_OK;
}
lwm2m_context_t *lwm2m_fota_manager_get_lwm2m_context(lwm2m_fota_manager_s *thi)
{
    ASSERT_THIS(return NULL);
    return thi->lwm2m_context;
}

static int lwm2m_fota_manager_rcv_notify_ack(lwm2m_fota_manager_s *thi, data_send_status_e status)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (NULL == thi->current)
    {
        ATINY_LOG(LOG_ERR, "current null pointer");
        return LWM2M_ERR;
    }

    return thi->current->recv_notify_ack(thi->current, status);
}

static void lwm2m_fota_manager_notify_ack_callback(lwm2m_report_type_e type, int cookie, data_send_status_e status)
{
    ATINY_LOG(LOG_INFO, "download state ack type %d rev cookie %u expect cookie %u status %d, rpt stat %d", type, (uint32_t)cookie, lwm2m_fota_manager_get_instance()->cookie,  status,
              lwm2m_fota_manager_get_instance()->rpt_state);

    if ((lwm2m_fota_manager_get_instance()->wait_ack_flag) && lwm2m_fota_manager_get_instance()->cookie == cookie)
    {
        (void)lwm2m_fota_manager_rcv_notify_ack(lwm2m_fota_manager_get_instance(), status);
        lwm2m_fota_manager_get_instance()->wait_ack_flag = false;
    }
}


void lwm2m_fota_manager_get_data_cfg(const lwm2m_fota_manager_s *thi, lwm2m_data_cfg_t *data_cfg)
{
    ASSERT_THIS(return);

    if (NULL == data_cfg)
    {
        ATINY_LOG(LOG_ERR, "current null pointer");
        return;
    }

    data_cfg->callback = (lwm2m_data_process)lwm2m_fota_manager_notify_ack_callback;
    data_cfg->cookie = thi->cookie;
    // ATINY_LOG(LOG_INFO, "download cookie %d", data_cfg->cookie);
    data_cfg->type = FIRMWARE_UPDATE_STATE;
}



static lwm2m_fota_manager_s g_fota_manager;
lwm2m_fota_manager_s *lwm2m_fota_manager_get_instance(void)
{
    lwm2m_fota_manager_s *manager = &g_fota_manager;

    if (manager->init_flag)
    {
        return manager;
    }

    lwm2m_fota_manager_init(manager);
    return manager;
}



