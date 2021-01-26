#include <string.h>

#include "sinn_client.h"
#include "sinn_config.h"

sinn_time_t sinn_gettime_ms(void)
{
    return osal_sys_time();
}


static void sinn_buf_malloc(sinn_buf_t *abuf, size_t size)
{
    abuf->size = size;
    abuf->len = 0;
    abuf->data = (unsigned char *)osal_malloc(size);
}

static void sinn_buf_free(sinn_buf_t *abuf)
{
    abuf->size = 0;
    abuf->len = 0;
    if (abuf && abuf->data)
        osal_free((void *)abuf->data);
}

void sinn_register_proto(sinn_connection_t *nc, sinn_event_handler proto_handler)
{
    nc->proto_handler = proto_handler;
}

void sinn_init(sinn_manager_t *m, sinn_device_info_t *param)
{
    LINK_LOG_DEBUG("sinn init\r\n");

    m->interface = (sinn_if_t *)osal_malloc(sizeof(sinn_if_t));   //TODO  check malloc and osal_malloc
    m->interface->mgr = m;

    m->interface->ifuncs = param->ifuncs;
    m->interface->ifuncs->if_init(m->interface);
}

sinn_connection_t* sinn_connect(sinn_manager_t *m, sinn_event_handler cb, sinn_connect_param_t *param)
{
    int ret = 0;
    sinn_connection_t *nc = NULL;
    LINK_LOG_DEBUG("sinn connect\r\n");
    if ((nc = (sinn_connection_t *)osal_malloc(sizeof(sinn_connection_t))) != NULL)
    {
        nc->mgr = m;
        m->nc = nc;
        nc->flags |= (param->proto_type == SOCK_STREAM) ? 0 : SINN_FG_UDP;
        nc->flags |= SINN_FG_CONNECTING;
        nc->sock_fd = -1;
        nc->user_handler = cb;
        nc->proto_handler = NULL;
        nc->last_time = sinn_gettime_ms();
        nc->user_data = param;
        sinn_buf_malloc(&(nc->send_buf), SINN_SEND_BUF_SIZE);
        sinn_buf_malloc(&(nc->recv_buf), SINN_RECV_BUF_SIZE);
        nc->server_ip = param->server_ip;
        nc->server_port = param->server_port;
    }
    else
        return nc;

    ret = m->interface->ifuncs->if_connect(nc);
    if (ret)
    {
        sinn_destory(nc);
        return NULL;
    }

    return nc;
}

void sinn_poll(sinn_manager_t *m, int timeout_ms)
{
    m->interface->ifuncs->if_poll(m->nc, timeout_ms);
}

void sinn_destory(sinn_connection_t* nc)
{
    if (nc && nc->mgr && nc->mgr->interface)
        osal_free(nc->mgr->interface);

    if (nc && nc->mgr)
        osal_free(nc->mgr);

    if (nc && nc->proto_data)
        osal_free(nc->proto_data);

    if (nc && nc->user_data)
        osal_free(nc->user_data);

    sinn_buf_free(&nc->send_buf);
    sinn_buf_free(&nc->recv_buf);

    if (nc)
        osal_free(nc);
    nc = NULL;
}
