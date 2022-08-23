
#ifndef __NOTIFIER_H__
#define __NOTIFIER_H__

#include <utils_list.h>

typedef struct utils_list ntf_list_t;
typedef int (*utils_notifier_fn_t)(void *cb_arg, void *env);

typedef struct utils_notifier {
    struct utils_list_hdr node;
    utils_notifier_fn_t cb;
    void *cb_arg;
    int priority;
} utils_notifier_t;

int utils_notifier_chain_init(ntf_list_t *nl);
int utils_notifier_chain_register(ntf_list_t *nl, utils_notifier_t *node);
int utils_notifier_chain_call(ntf_list_t *nl, void *env);

#endif

