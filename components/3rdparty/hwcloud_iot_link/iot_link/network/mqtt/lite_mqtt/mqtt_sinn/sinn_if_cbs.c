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


#include "sinn_if_cbs.h"

void sinn_dispatch_event(sinn_connection_t *nc, sinn_event_handler event_handler, void *user_data, int event, void *event_data)
{
    if (event_handler == NULL)
    {
        event_handler = nc->proto_handler ? nc->proto_handler : nc->user_handler;
    }

    if (event_handler)
    {
        event_handler(nc, event, event_data);
    }
}


void sinn_nc_connect_cb(sinn_connection_t *nc)
{
    nc->flags &= ~SINN_FG_CONNECTING;

    sinn_dispatch_event(nc, NULL, NULL, SINN_EV_CONNECTED,NULL);
}

void sinn_nc_can_write_cb(sinn_connection_t *nc)
{
    int rc = 0;
    const unsigned char *buf = nc->send_buf.data;
    size_t len = nc->send_buf.len;

    if(nc->sock_fd == -1)
        return;

    nc->flags &= ~SINN_FG_CAN_WR;
    if (len > 0)
        rc = nc->mgr->interface->ifuncs->if_send(nc, buf, len);

    if (rc < 0)
    {
        perror("sinn write error\r\n");
        nc->flags &= ~SINN_FG_CAN_WR;
        return;
    }
    else if (rc > 0)
    {
        nc->last_time = sinn_gettime_ms();
        if(nc->send_buf.len > rc)
            memmove(nc->send_buf.data, nc->send_buf.data + rc, nc->send_buf.len - rc);
        nc->send_buf.len -= rc;
        nc->flags |= SINN_FG_CAN_WR;
    }
    else if (rc == 0)
        nc->flags |= SINN_FG_CAN_WR;

    sinn_dispatch_event(nc, NULL, NULL, SINN_EV_SEND, NULL);
}

void sinn_nc_can_read_cb(sinn_connection_t *nc)
{
    int rc = 0;
    unsigned char *buf = nc->recv_buf.data + nc->recv_buf.len;
    size_t len = nc->recv_buf.size - nc->recv_buf.len;
    nc->flags &= ~SINN_FG_CAN_RD;

    if(nc->sock_fd == -1)
        return;

    if (len > 0)
        rc = nc->mgr->interface->ifuncs->if_recv(nc, buf, len);

    if (rc < 0)
    {
        perror("read error");
        nc->flags &= ~SINN_FG_CAN_RD;
        return;
    }
    else if (rc == 0)
    {
        nc->flags |= SINN_FG_CAN_RD;
    }
    else if (rc > 0)
    {
        nc->last_time = sinn_gettime_ms();
        nc->recv_buf.len += rc;
        sinn_dispatch_event(nc, NULL, NULL, SINN_EV_RECV, NULL);
        nc->flags |= SINN_FG_CAN_RD;
    }
}

int sinn_nc_poll_cb(sinn_connection_t *nc)
{
    unsigned long int now = sinn_gettime_ms();

    if (nc->flags & SINN_FG_RECONNECT)
    {
        LINK_LOG_DEBUG("reconnect ~~~~~~\r\n");
        nc->flags &= ~SINN_FG_RECONNECT;
        sinn_dispatch_event(nc, NULL, NULL, SINN_EV_RECONN, &now);
        return 1;
    }
    sinn_dispatch_event(nc, NULL, NULL, SINN_EV_POLL, &now);
    return 0;
}

void sinn_mgr_handle_conn(sinn_connection_t *nc)
{
    if (sinn_nc_poll_cb(nc))
        return;

    if (nc->flags & SINN_FG_CONNECTING)
    {
        sinn_nc_connect_cb(nc);
    }

    if (nc->flags & SINN_FG_CAN_RD)
    {
        sinn_nc_can_read_cb(nc);
    }

    if (nc->flags & SINN_FG_CAN_WR)
    {
        sinn_nc_can_write_cb(nc);
    }
}
