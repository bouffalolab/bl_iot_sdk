
#include <stdio.h>
#include <string.h>
#include "bl_sys.h"
#include "bl_hbn.h"
#include "hal_sys.h"
#include <utils_log.h> 
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <utils_notifier.h>
#include <blog.h> 

static ntf_list_t *hbn_list = NULL;

static int ntf_init(void)
{
    hbn_list = pvPortMalloc(sizeof(ntf_list_t));
    if (!hbn_list) {
        blog_error("malloc error.\r\n");
        return -1;
    }
    utils_notifier_chain_init(hbn_list);//utils_list_init
    return 0;
}

static int ntf_reg(utils_notifier_fn_t cb, void *arg)
{
    utils_notifier_t *hbn_node = NULL;

    if (!hbn_list) {
        blog_error("ntfgpio not init.\r\n");
        return -1;
    }
    hbn_node = pvPortMalloc(sizeof(utils_notifier_t));
    if (!hbn_node) {
        blog_error("malloc error.\r\n");
        return -1;
    }
    hbn_node->cb = cb;
    hbn_node->cb_arg = arg;

    utils_notifier_chain_register(hbn_list, hbn_node);

    return 0;
}

int hal_hbn_init(uint8_t *pinbuf, uint8_t pinbuf_size)
{
    hbn_type_t *hbn = NULL;

    if ((pinbuf_size == 0) || (pinbuf_size > 128)) {
        blog_error("arg error.\r\n");
        return -1;
    }
    hbn = pvPortMalloc(pinbuf_size + sizeof(hbn_type_t));
    if (!hbn) {
        blog_error("mem error");
        return -1;
    }

    hbn->active = 1;
    hbn->buflen = pinbuf_size;
    memcpy(hbn->buf, pinbuf, pinbuf_size);
    
    if (!hbn_list) {
        ntf_init();
    }

    ntf_reg((utils_notifier_fn_t)bl_hbn_enter, hbn);

    return 0;
}

int hal_hbn_enter(uint32_t time)
{
    utils_notifier_chain_call(hbn_list, &time);

    return -1;
}

