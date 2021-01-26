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

#include <link_log.h>
#include "lwm2m_fota_state.h"
#include <string.h>
#include "firmware_update.h"


//TODO:set the update detail result
static int lwm2m_fota_state_default_handle(struct lwm2m_fota_state_tag_s *thi)
{
    ASSERT_THIS(return LWM2M_ERR);
    ATINY_LOG(LOG_ERR, "err state handle state %d", thi->manager ?
              lwm2m_fota_manager_get_state(thi->manager) : -1);
    return LWM2M_ERR;
}


void lwm2m_fota_state_init(lwm2m_fota_state_s *thi, lwm2m_fota_manager_s *manager)
{
    thi->start_download = (int (*)(struct lwm2m_fota_state_tag_s * thi, const char *uri))lwm2m_fota_state_default_handle;
    thi->execute_update = lwm2m_fota_state_default_handle;
    thi->finish_download = (int (*)(struct lwm2m_fota_state_tag_s * thi, int result))lwm2m_fota_state_default_handle;
    thi->repot_result = lwm2m_fota_state_default_handle;
    thi->recv_notify_ack = (int (*)(struct lwm2m_fota_state_tag_s  * thi, data_send_status_e status))lwm2m_fota_state_default_handle;
    thi->manager = manager;
}


static int lwm2m_fota_start_download(lwm2m_fota_state_s *thi, const char *uri)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);
    lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_NULL);
    return lwm2m_fota_manager_rpt_state(thi->manager, LWM2M_FOTA_DOWNLOADING);
}

static int lwm2m_fota_idle_state_recv_notify_ack(lwm2m_fota_state_s *thi, data_send_status_e status)
{
    int ret;
    lwm2m_fota_state_e rpt_state;

    if (SENT_SUCCESS != status)
    {
        ATINY_LOG(LOG_ERR, "idle state notify fail %d", status);
        lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_FAIL);
        return lwm2m_fota_manager_set_state(thi->manager, LWM2M_FOTA_IDLE);
    }

    rpt_state = lwm2m_fota_manager_get_rpt_state(thi->manager) ;

    //idle and downloaded rpt ack
    if ((LWM2M_FOTA_IDLE == rpt_state) || (LWM2M_FOTA_DOWNLOADED == rpt_state))
    {
        return lwm2m_fota_manager_set_state(thi->manager, rpt_state);
    }

    //updating rpt ack
    if (LWM2M_FOTA_UPDATING == rpt_state)
    {
        ATINY_LOG(LOG_ERR, "idle state recv updaing state ack");
        return LWM2M_ERR;
    }

    //downloading rpt ack
    //TODO, return then proper result
    ret = start_firmware_download(lwm2m_fota_manager_get_lwm2m_context(thi->manager), lwm2m_fota_manager_get_pkg_uri(thi->manager),
                                  lwm2m_fota_manager_get_storage_device(thi->manager));

    if (LWM2M_OK  == ret)
    {
        return lwm2m_fota_manager_set_state(thi->manager, LWM2M_FOTA_DOWNLOADING);
    }

    ATINY_LOG(LOG_ERR, "start_firmware_download fail %d", ret);
    lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_FAIL);
    return lwm2m_fota_manager_rpt_state(thi->manager, LWM2M_FOTA_IDLE);
}

static int lwm2m_fota_idle_state_get_result(int *res)
{
    ota_flag_t flag;

    if (LWM2M_ERR != ota_storage_flag_read(&flag))
    {
        LINK_LOG_DEBUG("%s:  ret upgrade = %u\n", __func__, flag.ret_upgrade);
        *res = flag.ret_upgrade;
        return LWM2M_OK;
    }

    return LWM2M_ERR;
}

int lwm2m_fota_idle_state_int_report_result(lwm2m_fota_idle_state_s *thi)
{
    lwm2m_observe_info_t observe_info;
    int ret = LWM2M_ERR;
    int result = LWM2M_ERR;
    ASSERT_THIS(return LWM2M_ARG_INVALID);
    thi->report_flag = false;
    (void) memset(&observe_info, 0, sizeof(lwm2m_observe_info_t));

    if (ota_pack_observe_info_read(&observe_info, sizeof(observe_info)) != LWM2M_OK)
    {
        ATINY_LOG(LOG_ERR, "read observe info fail");
        goto EXIT;
    }

    if (0 == observe_info.tokenLen)
    {
        return LWM2M_OK;
    }

    ret = lwm2m_fota_idle_state_get_result(&result);

    if (LWM2M_OK != ret)
    {
        ATINY_LOG(LOG_ERR, "get_software_result fail");
    }

    //    result = ATINY_OK;
    thi->report_result = result;
    thi->report_flag = true;
    (void) memcpy(&thi->observe_info, &observe_info, sizeof(thi->observe_info));
    ATINY_LOG(LOG_ERR, "need to rpt result %d", result);
EXIT:
    (void) memset(&observe_info, 0, sizeof(observe_info));

    if (ota_pack_observe_info_write(&observe_info, sizeof(observe_info)) != LWM2M_OK)
    {
        ATINY_LOG(LOG_ERR, "write observe info fail");
    }

    return ret;
}

static int lwm2m_fota_idle_state_report_result(lwm2m_fota_state_s *thi)
{
    int ret = LWM2M_ERR;
    lwm2m_fota_idle_state_s *idle_stat = (lwm2m_fota_idle_state_s *)thi;
    int state;
    lwm2m_data_cfg_t dataCfg = {0};
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (!idle_stat->report_flag)
    {
        return LWM2M_OK;
    }

    idle_stat->report_flag = false;
    state = ((LWM2M_OK == idle_stat->report_result) ?  LWM2M_FOTA_IDLE : LWM2M_FOTA_DOWNLOADED);
    lwm2m_fota_manager_set_update_result(thi->manager, (LWM2M_OK == idle_stat->report_result) ? LWM2M_FIRMWARE_UPDATE_SUCCESS : LWM2M_FIRMWARE_UPDATE_FAIL);
    lwm2m_fota_manager_save_rpt_state(thi->manager, state);
    lwm2m_fota_manager_get_data_cfg(thi->manager, &dataCfg);
    ret = lwm2m_send_notify(lwm2m_fota_manager_get_lwm2m_context(thi->manager),
                            &idle_stat->observe_info, state, &dataCfg);
    ATINY_LOG(LOG_ERR, "lwm2m_send_notify result %d, state %d", ret, state);
    return ret;
}


void lwm2m_fota_idle_state_init(lwm2m_fota_idle_state_s *thi, lwm2m_fota_manager_s *manager)
{
    (void) memset(thi, 0, sizeof(*thi));
    lwm2m_fota_state_init(&thi->interface, manager);
    thi->interface.start_download = lwm2m_fota_start_download;
    thi->interface.repot_result = lwm2m_fota_idle_state_report_result;
    thi->interface.recv_notify_ack = lwm2m_fota_idle_state_recv_notify_ack;
}
static int lwm2m_fota_downloading_state_finish_download(lwm2m_fota_state_s *thi, int result)
{
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (LWM2M_OK != result)
    {
        lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_FAIL);
    }

    return lwm2m_fota_manager_rpt_state(thi->manager, (LWM2M_OK == result) ? LWM2M_FOTA_DOWNLOADED : LWM2M_FOTA_IDLE);
}


static int lwm2m_fota_downloading_state_recv_notify_ack(lwm2m_fota_state_s *thi, data_send_status_e status)
{
    lwm2m_fota_state_e rpt_state;

    if (SENT_SUCCESS != status)
    {
        ATINY_LOG(LOG_ERR, "downloading state notify ack fail %d", status);
        lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_FAIL);
        return lwm2m_fota_manager_set_state(thi->manager, LWM2M_FOTA_IDLE);
    }

    rpt_state = lwm2m_fota_manager_get_rpt_state(thi->manager);

    if ((LWM2M_FOTA_IDLE == rpt_state) || (LWM2M_FOTA_DOWNLOADED == rpt_state))
    {
        return lwm2m_fota_manager_set_state(thi->manager, rpt_state);
    }
    else
    {
        ATINY_LOG(LOG_ERR, "recv notify ack err  in downloading state, rpt state %d", rpt_state);
        return LWM2M_ERR;
    }
}
void lwm2m_fota_downloading_state_init(lwm2m_fota_downloading_state_s *thi, lwm2m_fota_manager_s *manager)
{
    lwm2m_fota_state_init(&thi->interface, manager);
    thi->interface.finish_download = lwm2m_fota_downloading_state_finish_download;
    thi->interface.recv_notify_ack = lwm2m_fota_downloading_state_recv_notify_ack;
}

static int lwm2m_fota_downloaded_state_execute_update(lwm2m_fota_state_s *thi)
{
    lwm2m_fota_state_e rpt_state = LWM2M_FOTA_UPDATING;
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (lwm2m_fota_manager_get_update_result(thi->manager) != LWM2M_FIRMWARE_UPDATE_NULL)
    {
        rpt_state = LWM2M_FOTA_IDLE;
        lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_FAIL);
    }

    return lwm2m_fota_manager_rpt_state(thi->manager, rpt_state);
}


static int lwm2m_fota_downloaded_state_recv_notify_ack(lwm2m_fota_state_s *thi, data_send_status_e status)
{
    int ret;
    lwm2m_fota_state_e rpt_state;
    lwm2m_observe_info_t observe_info;
    pack_storage_device_api_s *device;
    ASSERT_THIS(return LWM2M_ARG_INVALID);

    if (SENT_SUCCESS != status)
    {
        ATINY_LOG(LOG_ERR, "downloaded state notify fail %d", status);
        lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_FAIL);
        return lwm2m_fota_manager_set_state(thi->manager, LWM2M_FOTA_IDLE);
    }

    rpt_state = lwm2m_fota_manager_get_rpt_state(thi->manager);

    //rpt downloading state ack
    if (LWM2M_FOTA_DOWNLOADING == rpt_state)
    {
        ret = start_firmware_download(lwm2m_fota_manager_get_lwm2m_context(thi->manager), lwm2m_fota_manager_get_pkg_uri(thi->manager),
                                      lwm2m_fota_manager_get_storage_device(thi->manager));

        if (LWM2M_OK  == ret)
        {
            return lwm2m_fota_manager_set_state(thi->manager, LWM2M_FOTA_DOWNLOADING);
        }

        ATINY_LOG(LOG_ERR, "start_firmware_download fail %d", ret);
        lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_FAIL);
        (void)lwm2m_fota_manager_rpt_state(thi->manager, LWM2M_FOTA_IDLE);
        return LWM2M_ERR;
    }

    //rpt idle state ack
    if (LWM2M_FOTA_IDLE == rpt_state)
    {
        return lwm2m_fota_manager_set_state(thi->manager, rpt_state);
    }

    //rpt downloaded state ack
    if (LWM2M_FOTA_DOWNLOADED == rpt_state)
    {
        return LWM2M_OK;
    }

    //rpt updating state ack
    if ((COAP_NO_ERROR != lwm2m_get_observe_info(lwm2m_fota_manager_get_lwm2m_context(thi->manager), &observe_info))
        || (0 == observe_info.tokenLen))
    {
        ATINY_LOG(LOG_ERR, "lwm2m_get_observe_info fail");
        goto EXIT_DOWNLOADED;
    }

    device = lwm2m_fota_manager_get_storage_device(thi->manager);

    if ((NULL == device) || (NULL == device->active_software) || (LWM2M_OK != device->active_software(device)))
    {
        ATINY_LOG(LOG_ERR, "active_software fail");
        goto EXIT_DOWNLOADED;
    }

    if (ota_pack_observe_info_write(&observe_info, sizeof(observe_info)) != LWM2M_OK)
    {
        ATINY_LOG(LOG_ERR, "flag_write fail");
        goto EXIT_DOWNLOADED;
    }

    lwm2m_set_reboot_flag();
    return lwm2m_fota_manager_set_state(thi->manager, LWM2M_FOTA_UPDATING);
EXIT_DOWNLOADED:
    lwm2m_fota_manager_set_update_result(thi->manager, LWM2M_FIRMWARE_UPDATE_FAIL);
    (void)lwm2m_fota_manager_rpt_state(thi->manager, LWM2M_FOTA_DOWNLOADED);
    return LWM2M_ERR;
}


void lwm2m_fota_downloaded_state_init(lwm2m_fota_downloaded_state_s *thi, lwm2m_fota_manager_s *manager)
{
    lwm2m_fota_state_init(&thi->interface, manager);
    thi->interface.start_download = lwm2m_fota_start_download;
    thi->interface.execute_update = lwm2m_fota_downloaded_state_execute_update;
    thi->interface.recv_notify_ack = lwm2m_fota_downloaded_state_recv_notify_ack;
}

void lwm2m_fota_updating_state_init(lwm2m_fota_updating_state_s *thi, lwm2m_fota_manager_s *manager)
{
    lwm2m_fota_state_init(&thi->interface, manager);
}

