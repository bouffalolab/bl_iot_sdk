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

#ifndef _LWM2M_LIST_H

#define _LWM2M_LIST_H
#define LWM2M_INLINE static inline


#ifdef __cplusplus
#if __cplusplus

extern "C" {

#endif /* __cplusplus */

#endif /* __cplusplus */


/**

 *@ingroup atiny_list

 *Structure of a node in a doubly linked list.

 */

typedef struct lwm2m_dl_list
{
    struct lwm2m_dl_list *prev;            /**< Current node's pointer to the previous node*/
    struct lwm2m_dl_list *next;            /**< Current node's pointer to the next node*/

} lwm2m_dl_list;


LWM2M_INLINE void lwm2m_list_init(lwm2m_dl_list *list)
{
    list->next = list;
    list->prev = list;
}

#define LWM2M_DL_LIST_FIRST(object) ((object)->next)

LWM2M_INLINE void lwm2m_list_add_ex(lwm2m_dl_list *list, lwm2m_dl_list *node)
{
    node->next = list->next;
    node->prev = list;
    list->next->prev = node;
    list->next = node;
}

LWM2M_INLINE void lwm2m_list_insert_tail(lwm2m_dl_list *list, lwm2m_dl_list *node)
{
    lwm2m_list_add_ex(list->prev, node);
}

LWM2M_INLINE lwm2m_dl_list *lwm2m_list_get_head(lwm2m_dl_list *header)
{
    return header->next;
}

LWM2M_INLINE void lwm2m_list_delete(lwm2m_dl_list *node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = (lwm2m_dl_list *)NULL;
    node->prev = (lwm2m_dl_list *)NULL;
}

LWM2M_INLINE int lwm2m_list_empty(lwm2m_dl_list *node)
{
    return (node->next == node);
}

#define LWM2M_OFFSET_OF_FIELD(type, field)    ((UINT32)&(((type *)0)->field))
#define LWM2M_OFF_SET_OF(type, member) ((long)&((type *)0)->member)   /*lint -e(413) */
#define LWM2M_FIELD_TO_STRUCT(field_addr, type, member) \
    ((type *)((char *)(field_addr) - LWM2M_OFF_SET_OF(type, member)))

#define LWM2M_DL_LIST_ENTRY(item, type, member)\
    ((type *)((char *)item - LWM2M_OFF_SET_OF(type, member)))\


#define LWM2M_DL_LIST_FOR_EACH_ENTRY(item, list, type, member)\
    for (item = LWM2M_DL_LIST_ENTRY((list)->next, type, member);\
        &item->member != (list);\
        item = LWM2M_DL_LIST_ENTRY(item->member.next, type, member))


#define LWM2M_DL_LIST_FOR_EACH_ENTRY_SAFE(item, next, list, type, member)\
    for (item = LWM2M_DL_LIST_ENTRY((list)->next, type, member),\
        next = LWM2M_DL_LIST_ENTRY(item->member->next, type, member);\
        &item->member != (list);\
        item = next, item = LWM2M_DL_LIST_ENTRY(item->member.next, type, member))

LWM2M_INLINE void LWM2M_ListDel(lwm2m_dl_list *pstPrevNode, lwm2m_dl_list *pstNextNode)
{
    pstNextNode->prev = pstPrevNode;
    pstPrevNode->next = pstNextNode;
}

LWM2M_INLINE void LWM2M_ListDelInit(lwm2m_dl_list *pstList)
{
    LWM2M_ListDel(pstList->prev, pstList->next);
    lwm2m_list_init(pstList);
}

#define LWM2M_DL_LIST_FOR_EACH(item, list)\
    for ((item) = (list)->next;\
        (item) != (list);\
        (item) = (item)->next)

#define LWM2M_DL_LIST_FOR_EACH_SAFE(item, next, list)\
    for (item = (list)->next, next = item->next; item != (list);\
        item = next, next = item->next)

#define LWM2M_DL_LIST_HEAD(list)\
            lwm2m_dl_list list = { &(list), &(list) }

#ifdef __cplusplus

#if __cplusplus

}

#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* _ATINY_LIST_H */
