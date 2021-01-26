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

#ifndef LITEOS_LAB_IOT_LINK_INC_LINK_LIST_H_
#define LITEOS_LAB_IOT_LINK_INC_LINK_LIST_H_


#include <stdint.h>
#include <stddef.h>


///< this is common double-list , and you could implement the one yourself

/*
 * you could add the node to the data entry like
 *
 * struct {
 *
 *  link_node_t node;
 *
 *  xxx value;
 *
 * }
 *
 *
 * */

typedef struct link_node
{
    struct link_node *nxt, *pre;
}link_node_t;


#define LINK_NODE_ENTRY(node, type, member)   \
    ((type *)((char *)(node) - (size_t)&((type *)0)->member))

typedef void (*fn_link_list_iterate)(link_node_t *node, void *args);


typedef struct
{
    link_node_t root;
}link_list_t;

static inline void link_list_init(link_list_t *list)
{
    list->root.nxt  = &list->root;
    list->root.pre =  &list->root;
}

static inline int link_list_isempty(link_list_t *list)
{
    return list->root.pre == &list->root?1:0;
}

static inline int link_list_ishead(link_list_t *list, link_node_t *node)
{
    return list->root.nxt == node?1:0;
}

static inline int link_list_istail(link_list_t *list, link_node_t *node)
{
    return list->root.pre == node?1:0;
}

///< insert the new_node before the old_node
static inline void link_list_insert(link_node_t *old_node, link_node_t *new_node)
{
    new_node->pre = old_node->pre;
    new_node->nxt = old_node;
    new_node->pre->nxt = new_node;
    old_node->pre = new_node;
}

static inline void link_list_addhead(link_list_t *list, link_node_t *node)
{
    link_list_insert(list->root.nxt,node);
}

static inline void link_list_addtail(link_list_t *list, link_node_t *node)
{
    link_list_insert(&list->root,node);
}

///< node could not bee root
static inline void link_list_removenode( link_node_t *node)
{
    node->pre->nxt = node->nxt;
    node->nxt->pre = node->pre;

}

static inline link_node_t *link_list_removehead(link_list_t *list)
{
    link_node_t *node = list->root.nxt;

    link_list_removenode(node);

    return node;
}

static inline link_node_t *link_list_removetail(link_list_t *list)
{
    link_node_t *node = list->root.pre;

    link_list_removenode(node);

    return node;
}

static inline void link_list_replace(link_node_t *new_node, link_node_t *old_node)
{
    new_node->nxt = old_node->nxt;
    new_node->nxt->pre = new_node;
    new_node->pre = old_node->pre;
    new_node->pre->nxt = new_node;
}

#define LINK_LIST_FOREACH(node, list) \
    for(node = (list)->root.nxt;   \
        node != &(list)->root;     \
        node = (node)->nxt )

#define LINK_LIST_FOREACH_SAFE(node, tmp,list)  \
        for(node = (list)->root.nxt, tmp = (node)->nxt;   \
            node != &(list)->root;     \
            node = tmp,tmp = (node)->nxt )

static inline void link_list_iterate(link_list_t *list, fn_link_list_iterate fn_iterate, void *args)
{
    link_node_t *node;
    LINK_LIST_FOREACH(node, list)
    {
        fn_iterate(node, args);
    }
}

static inline void link_list_iteratesafe(link_list_t *list, fn_link_list_iterate fn_iterate, void *args)
{
    link_node_t *node;
    link_node_t *tmp;
    LINK_LIST_FOREACH_SAFE(node, tmp,list)
    {
        fn_iterate(node, args);
    }
}

#endif /* LITEOS_LAB_IOT_LINK_INC_LINK_LIST_H_ */
