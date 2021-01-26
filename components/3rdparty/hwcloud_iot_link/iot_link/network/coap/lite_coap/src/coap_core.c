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
 * include those applicable to Huawei LiteOS of CHN and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#include <string.h>
 
#include <litecoap.h>
#include <litecoap_err.h>

/*****************************************************************************
 Function    : litecoap_parse_header_size
 Description : parse coap header info and store it
 Input       : buf @ coap message buf
               proto @ coap over protocol (UDP or TCP)
 Return      : coap header size
 *****************************************************************************/
static size_t litecoap_parse_header_size(const unsigned char *buf, coap_proto_t proto)
{
    size_t header_size = 0;
    if (buf == NULL) {
        return 0;
    }

    if (proto == COAP_PROTO_TCP || proto == COAP_PROTO_TLS) {
        unsigned char len = *buf >> 4;
        if (len < 13) {
            header_size = 2;
        } else if (len == 13) {
            header_size = 3;
        } else if (len == 14) {
            header_size = 4;
        } else {
            header_size = 6;
        }

    } else if (proto == COAP_PROTO_UDP || proto == COAP_PROTO_DTLS) {
        header_size = 4;
    }

    return header_size;
}

/*****************************************************************************
 Function    : litecoap_parse_header
 Description : parse coap header info and store it
 Input       : buf @ coap message buf
               buflen @ coap message buf length
               proto @ coap over protocol (UDP or TCP)
 Output      : msg @ coap message pointer
 Return      : LITECOAP_OK means parse success, other value failed.
 *****************************************************************************/
static int litecoap_parse_header(coap_msg_t *msg, const unsigned char *buf, int buflen, coap_proto_t proto)
{
    size_t header_size;
    if ((NULL == msg) || (NULL == buf))
    {
        return LITECOAP_PARAM_NULL;
    }

    header_size = litecoap_parse_header_size(buf, proto);
    if (buflen < header_size)
    {
        return LITECOAP_BUF_LEN_TOO_SMALL;
    }

    if (proto == COAP_PROTO_UDP || proto == COAP_PROTO_DTLS) {
        msg->head.ver = (buf[0] & COAP_HEADER_VER_MASK) >> 6;
        if (msg->head.ver != COAP_VERSION) {
            return LITECOAP_VER_ERR;
        }
        
        msg->head.t = (buf[0] & 0x30) >> 4;
        msg->head.tkl = buf[0] & 0x0F;
        msg->head.code = buf[1];
        msg->head.msgid[0] = buf[2];
        msg->head.msgid[1] = buf[3];
    } else if (proto == COAP_PROTO_TCP || proto == COAP_PROTO_TLS) {
        msg->head.t = COAP_MESSAGE_CON;
        msg->head.tkl = buf[0] & 0x0F;
        msg->head.code = buf[header_size - 1];
        msg->head.msgid[0] = 0;
        msg->head.msgid[1] = 0;
    }

    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_parse_token
 Description : parse coap token info and store it
 Input       : buf @ coap message buf
               buflen @ coap message buf length
 Output      : msg @ coap message pointer
 Return      : LITECOAP_OK means parse success, other value failed.
 *****************************************************************************/
int litecoap_parse_token(coap_msg_t *msg, unsigned char *buf, int buflen)
{
    if ((msg == NULL) || (buf == NULL)) {
        return LITECOAP_PARAM_NULL;
    }
    if (msg->head.tkl == 0) {
        msg->tok = NULL;
        return LITECOAP_OK;
    } else if (msg->head.tkl <= COAP_MAX_TOKEN_LEN) {
        if (4U + msg->head.tkl > buflen) {
            /* tok bigger than packet */
            return LITECOAP_BUF_LEN_TOO_SMALL;
        }
        if (msg->tok == NULL) {
            msg->tok = (coap_token_t *)litecoap_malloc(sizeof(coap_token_t));
            if (msg->tok == NULL) {
                return LITECOAP_MALLOC_FAILED;
            }
            (void) memset(msg->tok, 0, sizeof(coap_token_t));
        }
        msg->tok->token = (unsigned char *)litecoap_malloc(msg->head.tkl);
        if (msg->tok->token != NULL) {
            (void) memcpy(msg->tok->token, buf+4, msg->head.tkl);  /* skip header */
            msg->tok->tklen = msg->head.tkl;
        } else {
            litecoap_free(msg->tok);
            msg->tok = NULL;
        }
        return LITECOAP_OK;
    } else {
        /* invalid size */
        return LITECOAP_TOKEN_LEN_ERR;
    }
}

/*****************************************************************************
 Function    : litecoap_parse_one_option
 Description : parse coap one option info and store it in msg, it called by
               litecoap_parse_opts_payload()
 Input       : buf @ coap message's buf's pointer that start from option
               buflen @ coap message buf length
 Output      : msg @ coap message pointer
               sumdelta @ last delta that get from last option.
 Return      : LITECOAP_OK means parse success, other value failed.
 *****************************************************************************/
int litecoap_parse_one_option(coap_msg_t *msg, unsigned short *sumdelta,
                              const unsigned char **buf, int buflen)
{
    const unsigned char *p = *buf;
    unsigned char headlen = 1;
    unsigned short len, delta;
    coap_option_t *newopt = NULL;
    coap_option_t *tmpopt = NULL;
    
    if ((msg == NULL) || (sumdelta == NULL) || (buf == NULL))
    {
        return LITECOAP_PARAM_NULL;
    }

    if (buflen < headlen) /* too small */
    {
        return LITECOAP_BUF_LEN_TOO_SMALL;
    }

    delta = (p[0] & 0xF0) >> 4;
    len = p[0] & 0x0F;
    
    if (delta == 13)
    {
        headlen++;
        if (buflen < headlen)
        {
            return LITECOAP_BUF_LEN_TOO_SMALL;
        }
        delta = p[1] + 13;
        p++;
    }
    else if (delta == 14)
    {
        headlen += 2;
        if (buflen < headlen)
        {
            return LITECOAP_BUF_LEN_TOO_SMALL;
        }
        delta = ((p[1] << 8) | p[2]) + 269;
        p += 2;
    }
    else if (delta == 0x000F)
    {
        return LITECOAP_OPTION_DELTA_ERR;
    }

    if (len == 13)
    {
        headlen++;
        if (buflen < headlen)
        {
            return LITECOAP_BUF_LEN_TOO_SMALL;
        }
        len = p[1] + 13;
        p++;
    }
    else if (len == 14)
    {
        headlen += 2;
        if (buflen < headlen)
        {
            return LITECOAP_BUF_LEN_TOO_SMALL;
        }
        len = ((p[1] << 8) | p[2]) + 269;
        p += 2;
    }
    else if (len == 15)
    {
        return LITECOAP_OPTION_LEN_ERR;
    }

    if ((p + 1 + len) > (*buf + buflen))
    {
        return LITECOAP_OPTION_LEN_ERR;
    }

    newopt = (coap_option_t *)litecoap_malloc(sizeof(coap_option_t));
    if (newopt == NULL)
    {
        return LITECOAP_MALLOC_FAILED;
    }
    (void) memset(newopt, 0, sizeof(coap_option_t));
    newopt->optnum = delta + *sumdelta;
    
    if (len > 0)
    {
        newopt->value = (unsigned char *)litecoap_malloc(len);
        if (newopt->value != NULL)
        {
            newopt->optlen = len;
            (void) memcpy(newopt->value, p+1, len);
        }
        else
        {
            litecoap_free(newopt);
            return LITECOAP_MALLOC_FAILED;
        }
    }
    newopt->next = NULL;
    msg->optcnt++;
    tmpopt = msg->option;
    if (tmpopt == NULL)
    {
        msg->option = newopt;
    }
    else
    {
        while(tmpopt->next != NULL)
        {
            tmpopt = tmpopt->next;
        }
        tmpopt->next = newopt;
    }
    
    *buf = p + 1 + len;
    *sumdelta += delta;

    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_parse_opts_payload
 Description : parse coap payload and options and store it in msg
 Input       : buf @ coap message's buf that start from option
               buflen @ coap message buf length
 Output      : msg @ coap message pointer
 Return      : LITECOAP_OK means parse success, other value failed.
 *****************************************************************************/
int litecoap_parse_opts_payload(coap_msg_t *msg, const unsigned char *buf,
                                int buflen)
{
    unsigned short sumdelta = 0;
    const unsigned char *p = NULL;
    const unsigned char *end = buf + buflen;
    int ret;
    if ((msg == NULL) || (buf == NULL) || (buflen < 4)) {
        return LITECOAP_PARAM_NULL;
    }

    p = buf + 4 + msg->head.tkl;

    if (p > end) {
        return LITECOAP_OPTION_OVERRUN_ERR;
    }

    while((p < end) && (*p != 0xFF)) {
        ret = litecoap_parse_one_option(msg, &sumdelta, &p, end-p);
        if (0 != ret) {
            return ret;
        }
    }

    if ((p+1 < end) && (*p == 0xFF))  /* payload marker */ {
        msg->payloadlen = end-(p+1);
        msg->payload = (unsigned char *)litecoap_malloc(msg->payloadlen);
        if (msg->payload != NULL) {
            (void) memcpy(msg->payload, (unsigned char *)p + 1, msg->payloadlen);
        } else {
            msg->payloadlen = 0;
        }
    } else {
        msg->payload = NULL;
        msg->payloadlen = 0;
    }
    msg->payloadmarker = 0xFF;

    return LITECOAP_OK;
}

static int litecoap_option_len(coap_option_t *opt, int lastoptval, int *len)
{
    int delta = 0;
    int delta_ex = 0;
    int optlen = 0;
    int optlen_ex = 0;
    unsigned char tmp;
    int sumlen = 0;

    if ((opt == NULL) || (len == NULL)) {
        return LITECOAP_PARAM_NULL;
    }

    if (opt->optnum < lastoptval) {
        return LITECOAP_OPTION_POSTION_ERR;
    }

    delta = opt->optnum - lastoptval;
    if (delta < 13) {
        delta = opt->optnum - lastoptval;
        delta_ex = 0;
    } else if (delta < 269) {
        delta_ex = delta - 13;
        delta = 13;
    } else if (delta >= 269) {
        delta_ex = delta - 269 - 14;
        delta = 14;
    }

    optlen = opt->optlen;
    if (optlen < 13) {
        optlen = opt->optlen;
        optlen_ex = 0;
    } else if (optlen < 269) {
        optlen_ex = optlen - 13;
        optlen = 13;
    } else if (optlen >= 269) {
        optlen_ex = optlen - 269 -14;
        optlen = 14;
    }

    sumlen = 1;
    if (delta == 13) {
        sumlen++;
    }
    if (delta == 14) {
        sumlen += 2;
    }
    if (optlen == 13) {
        sumlen++;
    }
    if (optlen == 14) {
        sumlen += 2;
    }

    *len = sumlen + opt->optlen;
    return LITECOAP_OK;
}


/*****************************************************************************
 Function    : litecoap_encode_option
 Description : encode coap option from option struct to byte stream
 Input       : opt @ option's pointer
               lastoptval @ last option's value, it used for calc delta.
 Output      : outbuf @ buf that used for storing the options bytes stream
               len @ the bytes number that option changed to byte stream
 Return      : LITECOAP_OK means parse success, other value failed.
 *****************************************************************************/
static int litecoap_encode_option(coap_option_t *opt, int lastoptval,
                                  unsigned char *outbuf, int *len)
{
    int delta = 0;
    int delta_ex = 0;
    int optlen = 0;
    int optlen_ex = 0;
    unsigned char tmp;
    int sumlen = 0;
    
    if ((opt == NULL) || (outbuf == NULL) || (len == NULL))
    {
        return LITECOAP_PARAM_NULL;
    }
    if (opt->optnum < lastoptval)
    {
        return LITECOAP_OPTION_POSTION_ERR;
    }
    
    delta = opt->optnum - lastoptval;
    if (delta < 13)
    {
        delta = opt->optnum - lastoptval;
        delta_ex = 0;
    } 
    else if (delta < 269)
    {
        delta_ex = delta - 13;
        delta = 13;
    }
    else if (delta >= 269)
    {
        delta_ex = delta - 269 - 14;
        delta = 14;
    }

    optlen = opt->optlen;
    if (optlen < 13)
    {
        optlen = opt->optlen;
        optlen_ex = 0;
    } 
    else if (optlen < 269)
    {
        optlen_ex = optlen - 13;
        optlen = 13;
    }
    else if (optlen >= 269)
    {
        optlen_ex = optlen - 269 - 14;
        optlen = 14;
    }
    
    tmp = (unsigned char)delta;
    outbuf[0] = tmp << 4;
    tmp = (unsigned char)optlen;
    outbuf[0] |= tmp &0x0f;
    sumlen = 1;
    if (delta == 13)
    {
        outbuf[sumlen] = delta_ex;
        sumlen++;
    }
    if (delta == 14)
    {
        outbuf[sumlen] = (delta_ex & 0x0000ffff) >> 8;
        outbuf[sumlen + 1] = (delta_ex & 0x000000ff);
        sumlen += 2;
    }
    if (optlen == 13)
    {
        outbuf[sumlen] = optlen_ex;
        sumlen++;
    }
    if (optlen == 14)
    {
        outbuf[sumlen] = (optlen_ex & 0x0000ffff) >> 8;
        outbuf[sumlen+1] = (optlen_ex & 0x000000ff);
        sumlen += 2;
    }
    (void) memcpy(outbuf + sumlen, opt->value, opt->optlen);
    
    *len = sumlen + opt->optlen;
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_build_byte_stream
 Description : encode coap message to byte stream
 Input       : msg @ coap message pointer
 Output      : ctx @ coap connection instance pointer, it contains a buf 
               that can store the byte stream
 Return      : LITECOAP_OK means parse success, other value failed.
 *****************************************************************************/
int litecoap_build_byte_stream(coap_context_t *ctx, coap_msg_t *msg)
{
    int len = 0;
    size_t offset = 0;
    size_t header_size = 0;
    coap_option_t *tmp = NULL;
    int sumdelta = 0;
    int msglen = 0;
    if ((ctx == NULL) || (msg == NULL))
    {
        return LITECOAP_PARAM_NULL;
    }
    
    if (ctx->sndbuf.buf == NULL)
    {
        return LITECOAP_CONTEX_BUF_NULL;
    }
    tmp = msg->option;

    if (ctx->proto == COAP_PROTO_UDP || ctx->proto == COAP_PROTO_DTLS) {
        header_size = 4;
        ctx->sndbuf.buf[0] = ((msg->head.ver & 0x03) << 6);
        ctx->sndbuf.buf[0] |= ((msg->head.t & 0x03) << 4);
        ctx->sndbuf.buf[0] |= (msg->head.tkl & 0x0F);
        ctx->sndbuf.buf[1] = msg->head.code;
        ctx->sndbuf.buf[2] = msg->head.msgid[0];
        ctx->sndbuf.buf[3] = msg->head.msgid[1];
    } else if (ctx->proto == COAP_PROTO_TCP || ctx->proto == COAP_PROTO_TLS) {
        while (tmp != NULL) {
            //litecoap_encode_option(tmp, sumdelta, ctx->sndbuf.buf + offset, &len);
            litecoap_option_len(tmp, sumdelta, &len);
            offset = offset + len;
            len = 0;
            sumdelta = tmp->optnum;
            tmp = tmp->next;
        }

        if ((msg->payload != NULL) && (msg->payloadlen > 0)) {
            offset += msg->payloadlen + 1;
        }
        if (offset < 13) {
            header_size = 2;
            ctx->sndbuf.buf[0] = (((unsigned char)offset << 4) | (msg->head.tkl));
            ctx->sndbuf.buf[1] = msg->head.code;
        } else if (offset < 269) {
            header_size = 3;
            ctx->sndbuf.buf[0] = ((13 << 4) | (msg->head.tkl));
            ctx->sndbuf.buf[1] = offset - 13;
            ctx->sndbuf.buf[2] = msg->head.code;
        } else if (offset < 65805) {
            header_size = 4;
            ctx->sndbuf.buf[0] = ((14 << 4) | msg->head.tkl);
            ctx->sndbuf.buf[1] = (unsigned char)((offset - 269) >> 8);
            ctx->sndbuf.buf[2] = (unsigned char)(offset - 269);
            ctx->sndbuf.buf[3] = msg->head.code;
        } else {
            header_size = 6;
            ctx->sndbuf.buf[0] = (15 << 4) | msg->head.tkl;
            ctx->sndbuf.buf[1] = (unsigned char)((offset - 65805) >> 24);
            ctx->sndbuf.buf[2] = (unsigned char)((offset - 65805) >> 16);
            ctx->sndbuf.buf[3] = (unsigned char)((offset - 65805) >> 8);
            ctx->sndbuf.buf[4] = (unsigned char)((offset - 65805));
            ctx->sndbuf.buf[5] = msg->head.code;
        }
    }

    len = 0;
    len += offset;
    len += header_size;
    if (msg->head.tkl > 0 && msg->tok != NULL) {
        len += msg->tok->tklen;
    }

    msglen = len;
    if (msglen > ctx->sndbuf.len) {
        return LITECOAP_SND_LEN_TOO_BIG;
    }

    offset = header_size;

    if (msg->head.tkl > 0 && msg->tok != NULL) {
        (void) memcpy(ctx->sndbuf.buf + offset, msg->tok->token, msg->tok->tklen);
        offset += msg->tok->tklen;
    }

    tmp = msg->option;
    sumdelta = 0;
    while (tmp != NULL) {
        litecoap_encode_option(tmp, sumdelta, ctx->sndbuf.buf + offset, &len);
        offset = offset + len;
        len = 0;
        sumdelta = tmp->optnum;
        tmp = tmp->next;
    }
    msglen = offset;

    if (NULL != msg->payload)
    {
        ctx->sndbuf.buf[offset++] = msg->payloadmarker;
        (void) memcpy(ctx->sndbuf.buf + offset, msg->payload, msg->payloadlen);
        msglen = msglen + msg->payloadlen + 1;
    }
    return msglen;
}

/*****************************************************************************
 Function    : litecoap_add_option_to_list
 Description : add a option to option list
 Input       : head @ option list head pointer, if the option is the first 
               option for coap message, its value should be NULL.
               option @ the option number
               vale @ option payload
               len @ option payload length
 Output      : None
 Return      : head @ option list head pointer.
 *****************************************************************************/
coap_option_t * litecoap_add_option_to_list(coap_option_t *head,
								unsigned short option, 
								char *value, int len)
{
    coap_option_t *tmp = NULL;
    coap_option_t *next = NULL;
    coap_option_t *newopt = NULL;
    if ((value == NULL) || (len == 0)) {
        return NULL;
    }
    
    newopt = (coap_option_t *)litecoap_malloc(sizeof(coap_option_t));
    if (newopt == NULL) {
        return head;
    }
    (void) memset(newopt, 0, sizeof(coap_option_t));
    newopt->optnum = option;
    newopt->optlen = len;
    newopt->value = (unsigned char *)litecoap_malloc(len);
    if(newopt->value == NULL) {
        litecoap_free(newopt);
        return head;
    }
    (void) memset(newopt->value, 0, len);
    //newopt->value = (unsigned char *)value;
    (void) memcpy(newopt->value, value, len);
    newopt->next = NULL;
    
    /* note that head just a pointer, point to the fisrt node of options */
    tmp = head;
    if (head == NULL) {
        return newopt;
    }
    if (tmp->optnum > option) {
        /* option number is the smallest in the list */
        newopt->next = head;
        return newopt;
    }
    next = tmp->next;
    while ((tmp != NULL) && (next != NULL)) {
        if (tmp->optnum <= option && next->optnum > option) {
            tmp->next = newopt;
            newopt->next = next;
            break;
        } else {
            tmp = tmp->next;
            next = tmp->next;
        }
    }
    tmp->next = newopt;
    newopt->next = next;
    
    return head;
}

/*****************************************************************************
 Function    : litecoap_free_option
 Description : free all option in the option list
 Input       : head @ option list head pointer, 
 Output      : None
 Return      : LITECOAP_OK @ free ok, other value means free failed.
 *****************************************************************************/
int litecoap_free_option(coap_option_t *head)
{
    coap_option_t *tmp = NULL;
    coap_option_t *next = NULL;

    if (head == NULL) {
        return LITECOAP_PARAM_NULL;
    }
    
    tmp = head;
    while (tmp != NULL) {
        next = tmp->next;
        if (tmp->value) {
            litecoap_free(tmp->value);
            tmp->value = NULL;
        }
        litecoap_free(tmp);
        tmp = next;
    }
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_add_token
 Description : add a token to the coap message.
 Input       : tok @ token's pointer 
               tklen @ token length
 Output      : msg @ coap message pointer
 Return      : LITECOAP_OK @ add success , other value means failed.
 *****************************************************************************/
int litecoap_add_token(coap_msg_t *msg, char *tok, int tklen)
{
    if ((msg == NULL) || (tklen < 0) || (tklen > COAP_MAX_TOKEN_LEN)) {
        return LITECOAP_PARAM_NULL;
    }
    if (tklen == 0) {
        return LITECOAP_OK;
    }
    if (msg->tok != NULL) {
        return LITECOAP_TOKEN_LEN_ERR;
    }
    if (msg->tok == NULL) {
        msg->tok = (coap_token_t *)litecoap_malloc(sizeof(coap_token_t));
        if (msg->tok == NULL) {
            return LITECOAP_MALLOC_FAILED;
        }
        (void) memset(msg->tok, 0, sizeof(coap_token_t));
    }
    msg->tok->token = (unsigned char *)litecoap_malloc(tklen);
    if (msg->tok->token == NULL) {
        litecoap_free(msg->tok);
        msg->tok = NULL;
        return LITECOAP_MALLOC_FAILED;
    }
    (void) memset(msg->tok->token, 0, tklen);
    (void) memcpy(msg->tok->token, tok, tklen);
    msg->tok->tklen = tklen;
    msg->head.tkl = tklen;
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_add_option
 Description : add option list to the coap message.
 Input       : opts @ option list pointer 
 Output      : msg @ coap message pointer
 Return      : LITECOAP_OK @ add success , other value means failed.
 *****************************************************************************/
int litecoap_add_option(coap_msg_t *msg, coap_option_t *opts)
{
    if ((msg == NULL) || (opts == NULL)) {
        return LITECOAP_PARAM_NULL;
    }

    msg->option = opts;
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_add_paylaod
 Description : add payload to the coap message.
 Input       : payload @ payload buf's pointer 
               len @ paylaod data length
 Output      : msg @ coap message pointer
 Return      : LITECOAP_OK @ add success , other value means failed.
 *****************************************************************************/
int litecoap_add_paylaod(coap_msg_t *msg, char *payload, int len)
{
    if ((msg == NULL) || (payload == NULL) || (len == 0)) {
        return LITECOAP_PARAM_NULL;
    }
    msg->payload = (unsigned char *)litecoap_malloc(len);
    if (msg->payload != NULL) {
        (void) memcpy(msg->payload, payload, len);
        msg->payloadlen = len;
        msg->payloadmarker = 0xff;
    } else {
        msg->payload = NULL;
        msg->payloadlen = 0;
        return LITECOAP_MALLOC_FAILED;
    }
    
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_new_msg
 Description : create a coap message and init it with some data.and update
               coap message id.
 Input       : msgtype @ coap message type
               code @ coap message code
               optlist @ coap message option list
               paylaod @ coap message payload
               payloadlen @ coap payload length
 Output      : ctx @ coap connection instance, it contains coap message id.
 Return      : msg @ the created message's pointer.
 *****************************************************************************/
coap_msg_t *litecoap_new_msg(coap_context_t *ctx,
                             unsigned char msgtype, 
                             unsigned char code, 
                             coap_option_t *optlist, 
                             unsigned char *payload, 
                             int payloadlen)
{
    coap_msg_t *msg = NULL;

    if (ctx == NULL) {
        return NULL;
    }

    if (msgtype > COAP_MESSAGE_RST) {
        return NULL;
    }

    msg = (coap_msg_t *)litecoap_malloc(sizeof(coap_msg_t));
    if (msg == NULL) {
        return NULL;
    }
    (void) memset(msg, 0, sizeof(coap_msg_t));

    msg->head.t = msgtype;
    msg->head.ver = 1;
    ctx->msgid++;
    msg->head.msgid[0] = (unsigned char)((ctx->msgid)&0x00ff);
    msg->head.msgid[1] = (unsigned char)((ctx->msgid&0xff00)>>8);
    msg->head.code = code;
    msg->option = optlist;
    if (payload != NULL) {
        msg->payloadmarker = 0xff;
        msg->payload = (unsigned char *)litecoap_malloc(payloadlen);
        if (msg->payload != NULL) {
            (void) memcpy(msg->payload, payload, payloadlen);
            msg->payloadlen = payloadlen;
        } else {
            litecoap_delete_msg(msg);
            msg = NULL;
        }
    }
    return msg;
}

/*****************************************************************************
 Function    : litecoap_delete_msg
 Description : free the coap message.
 Input       : msg @ coap message pointer that need free.
 Output      : None
 Return      : LITECOAP_OK @ free message ok, other valude means failed.
 *****************************************************************************/
int litecoap_delete_msg(coap_msg_t *msg)
{
    coap_option_t *tmp = NULL;
    coap_option_t *next = NULL;
    if (msg == NULL) {
        return LITECOAP_PARAM_NULL;
    }

    if (msg->tok) {
        litecoap_free(msg->tok->token);
        msg->tok->token = NULL;
        litecoap_free(msg->tok);
        msg->tok = NULL;
    }

    tmp = msg->option;
    while (tmp != NULL) {
        next = tmp->next;
        litecoap_free(tmp->value);
        tmp->value = NULL;
        litecoap_free(tmp);
        tmp = next;
    }
    if (msg->payload != NULL) {
        litecoap_free(msg->payload);
    }
    msg->payload = NULL;
    litecoap_free(msg);

    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_send_back
 Description : create a new coap message based on recived coap message 
               and send it
 Input       : ctx @ coap connection instance,
               rcvmsg @ recived coap message's pointer
               type @ new coap message's message type
 Output      : None
 Return      : LITECOAP_OK @ process ok, other valude means failed.
 *****************************************************************************/
int litecoap_send_back(coap_context_t *ctx, coap_msg_t *rcvmsg,
                       unsigned char type)
{
    coap_msg_t *newmsg = NULL;
    int datalen = 0;

    if ((ctx == NULL) || (rcvmsg == NULL)) {
        return LITECOAP_PARAM_NULL;
    }
    newmsg = (coap_msg_t *)litecoap_malloc(sizeof(coap_msg_t));
    if (newmsg == NULL) {
        return LITECOAP_MALLOC_FAILED;
    }
    (void) memset(newmsg, 0, sizeof(coap_msg_t));

    newmsg->head.t = type;
    newmsg->head.ver = 1;
    newmsg->head.msgid[0] = rcvmsg->head.msgid[0];
    newmsg->head.msgid[1] = rcvmsg->head.msgid[0];
    newmsg->head.code = 0;
    newmsg->option = NULL;
    newmsg->payload = NULL;
    newmsg->payloadlen = 0;
    
    datalen = litecoap_build_byte_stream(ctx, newmsg);
    if (datalen < 0) {
        litecoap_free(newmsg);
        newmsg = NULL;
        return LITECOAP_ENCODE_PKG_SIZE_ERR;
    }
    /* send msg to network */
    ctx->netops->network_send(ctx->udpio, (char *)ctx->sndbuf.buf, datalen);
    litecoap_free(newmsg);
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_send_rst
 Description : send reset message
 Input       : ctx @ coap connection instance,
               rcvmsg @ recived coap message's pointer
 Output      : None
 Return      : ret @ LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_send_rst(coap_context_t *ctx, coap_msg_t *rcvmsg)
{
    int ret = 0;
    ret = litecoap_send_back(ctx, rcvmsg, COAP_MESSAGE_RST);
    return ret;
}

/*****************************************************************************
 Function    : litecoap_send_rst
 Description : send ack message
 Input       : ctx @ coap connection instance,
               rcvmsg @ recived coap message's pointer
 Output      : None
 Return      : ret @ LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_send_ack(coap_context_t *ctx, coap_msg_t *rcvmsg)
{
    int ret = 0;
    ret = litecoap_send_back(ctx, rcvmsg, COAP_MESSAGE_ACK);
    return ret;
}

/*****************************************************************************
 Function    : litecoap_register_handler
 Description : regist coap message process callback function
 Input       : ctx @ coap connection instance,
               func @ coap message process callback function pointer
 Output      : None
 Return      : ret @ LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_register_handler(coap_context_t *ctx, msghandler func)
{
    if (ctx == NULL) {
        return LITECOAP_PARAM_NULL;
    }
    ctx->response_handler = func;
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_addto_resndqueue
 Description : add coap message to resend list.this list is for confirm mesage
 Input       : ctx @ coap connection instance,
               msg @ coap message pointer
 Output      : None
 Return      : LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_addto_resndqueue(coap_context_t *ctx, coap_msg_t *msg)
{
    send_queue_t *tmp = NULL;
    send_queue_t *s, *t;
    unsigned long long now;
    if (ctx == NULL || msg == NULL) {
        return LITECOAP_PARAM_NULL;
    }


    tmp = (send_queue_t *)litecoap_malloc(sizeof(send_queue_t));
    if (tmp == NULL) {
        return LITECOAP_MALLOC_FAILED;
    }
    (void) memset(tmp, 0, sizeof(send_queue_t));

    tmp->msg = msg;
    now = litecoap_time();

    if (ctx->resndque == NULL) {
        ctx->base_time = now;
        ctx->resndque = tmp;
        tmp->timeout = (ctx->ack_timeout.integer * 1000 + ctx->ack_timeout.decimals)
                        * (2 << ctx->max_retransmit - 1)
                        * (ctx->ack_random_factor.integer * 1000 + ctx->ack_random_factor.decimals)
                        / 1000;
        tmp->time = tmp->timeout;
        return LITECOAP_OK;
    } else {
        tmp->time = (now - ctx->base_time) + tmp->timeout;
    }

    s= ctx->resndque;
    if (s->time > tmp->time) {
        tmp->next = s;
        ctx->resndque = tmp;
        s->time -= tmp->time;
        return LITECOAP_OK;
    }

    do {
        tmp->time -= s->time;
        t = s;
        s = s->next;
    } while (s && s->time <= tmp->time);

    if (s) {
        s->time -= tmp->time;
    }

    tmp->next = s;
    t->next = tmp;

    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_addto_sndqueue
 Description : add coap message to send list.this list's affect is decide by 
               the coap user.
 Input       : ctx @ coap connection instance,
               msg @ coap message pointer
 Output      : None
 Return      : LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_addto_sndqueue(coap_context_t *ctx, coap_msg_t *msg)
{
    send_queue_t *tmp = NULL;
    if ((ctx == NULL) || (msg == NULL)) {
        return LITECOAP_PARAM_NULL;
    }

    tmp = (send_queue_t *)litecoap_malloc(sizeof(send_queue_t));
    if (tmp == NULL) {
        return LITECOAP_MALLOC_FAILED;
    }
    (void) memset(tmp, 0, sizeof(send_queue_t));

    tmp->msg = msg;
    tmp->next = ctx->sndque;
    ctx->sndque = tmp;

    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_remove_resndqueue
 Description : remove a coap message from resend list.
 Input       : ctx @ coap connection instance,
               rcvmsg @ recived coap message pointer, it used for find out which
               coap message need remove from resend list.
 Output      : None
 Return      : LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_remove_resndqueue(coap_context_t *ctx, coap_msg_t *rcvmsg)
{
    send_queue_t *tmp = NULL;
    send_queue_t *before = NULL;
    unsigned long long time = 0;
    if ((ctx == NULL) || (rcvmsg == NULL)) {
        return LITECOAP_PARAM_NULL;
    }

    tmp = ctx->resndque;
    while (tmp != NULL) {
        if (memcmp(rcvmsg->head.msgid, tmp->msg->head.msgid, 2) == 0) {
            if (before == NULL) {
                ctx->resndque = tmp->next;
            } else {
                before->next = tmp->next;
                time = tmp->time;
                while (before->next != NULL) {
                    before->time += time;
                    before = before->next;
                }
            }
            litecoap_delete_msg(tmp->msg);
            litecoap_free(tmp);
            break;
        }
        before = tmp;
        tmp = tmp->next;   
    }
    
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_discard_resndqueue
 Description : remove all coap message from resend list.
 Input       : ctx @ coap connection instance
 Output      : None
 Return      : LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_discard_resndqueue(coap_context_t *ctx)
{
    send_queue_t *tmp = NULL;
    send_queue_t *next = NULL;
    if (ctx == NULL) {
        return LITECOAP_PARAM_NULL;
    }
    
    tmp = ctx->resndque;
    while (tmp != NULL) {
        next = tmp->next;
        litecoap_delete_msg(tmp->msg);
        tmp->msg = NULL;
        litecoap_free(tmp);
        tmp = next;   
    }
    ctx->resndque = NULL;
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_remove_sndqueue
 Description : remove a coap message from send list.
 Input       : ctx @ coap connection instance
               msg @ coap message's pointer, that need remove from send list
 Output      : None
 Return      : LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_remove_sndqueue(coap_context_t *ctx, coap_msg_t *msg)
{
    send_queue_t *tmp = NULL;
    send_queue_t *before = NULL;
    
    if ((ctx == NULL) || (msg == NULL)) {
        return LITECOAP_PARAM_NULL;
    }

    tmp = ctx->sndque;
    while (tmp != NULL) {
        if (tmp->msg != NULL) {
            if (tmp->msg == msg) {
                if (before == NULL) {
                    ctx->sndque = tmp->next;
                } else {
                    before->next = tmp->next;
                }
                tmp->msg = NULL;
                tmp->next = NULL;
                litecoap_free(tmp);
                break;
            }
        }
        before = tmp;
        tmp = tmp->next;   
    }
    
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_add_resource
 Description : add coap resouce, it contains resouce that remote endpoint can
               observe, get, post....
 Input       : ctx @ coap connection instance
               res @ resource of coap endpoint.
 Output      : None
 Return      : LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_add_resource(coap_context_t *ctx, coap_res_t *res)
{
    if (ctx == NULL) {
        return LITECOAP_PARAM_NULL;
    }

    ctx->res = res;
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_option_check_critical
 Description : add coap private resouce, it contains socket handle ...
 Input       : ctx @ coap connection instance
               msg @ coap message that need to checkout.
 Output      : None
 Return      : LITECOAP_OK process ok, other valude means failed.
 *****************************************************************************/
int litecoap_option_check_critical(coap_msg_t *msg)
{
    unsigned short option = 0;
    
    /* note: this func is for the future, now we don't use it */
    switch(option)
    {
        
    }
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_find_opts
 Description : find out a coap option number that equal the input option number
               it called by litecoap_handle_request().
 Input       : rcvmsg @ recived coap message's pointer.
               num @ opition number that need to check.
 Output      : count @ total number of the option number that find in the coap
               messaget
 Return      : first @ the first opion's pointer in the coap message.
 *****************************************************************************/
static coap_option_t *litecoap_find_opts(coap_msg_t *rcvmsg,
                                         unsigned char num, 
                                         unsigned char *count)
{
    /* FIXME, options is always sorted, can find faster than this */
    size_t i;
    coap_option_t *first = NULL;
    coap_option_t *tmp = NULL;
    *count = 0;

    tmp = rcvmsg->option;
    for (i = 0; i < rcvmsg->optcnt; i++) {
        if (tmp->optnum == num) {
            if (first == NULL) {
                first = tmp;
            }
            (*count)++;
        } else {
            if (first != NULL) {
                break;
            }
        }
        tmp = tmp->next;
    }
    return first;
}

/*****************************************************************************
 Function    : litecoap_handle_request
 Description : process reviced coap messages that request resource in the 
               local resource.
 Input       : ctx @ coap connection instance.
               rcvmsg @ recived coap message
 Output      : None
 Return      : LITECOAP_OK means process ok, other value means error happended.
 *****************************************************************************/
int litecoap_handle_request(coap_context_t *ctx, coap_msg_t *rcvmsg)
{
    coap_res_t *res = NULL;
    coap_option_t *tmp = NULL;
    coap_option_t *opthead = NULL;
    coap_msg_t *respmsg = NULL;
    //char contype[2] = {0xff,0xff};
    int i = 0;
    int ret = 0;
    unsigned char pathcnt = 0;
    int findres = 0;

    if ((ctx == NULL) || (rcvmsg == NULL)) {
        return LITECOAP_PARAM_NULL;
    }
    if (rcvmsg->head.code >= 32 || rcvmsg->head.code == 0) {
        return LITECOAP_OK;
    }
    res = ctx->res;
    while (res->handler != NULL) {
        /* find if the res is in the ctx->res */
        if (res->method != rcvmsg->head.code) {
            res++;
            continue;
        }
        opthead = litecoap_find_opts(rcvmsg,
                                     COAP_OPTION_URI_PATH, 
                                     &pathcnt);
        if ((opthead != NULL) 
            && (pathcnt == res->path->count)) {
            tmp = opthead;
            for (i = 0; i < pathcnt; i++) {
                if (tmp->optlen != strlen(res->path->elems[i])) {
                    tmp = tmp->next;
                    break;
                }
                if (0 != memcmp(res->path->elems[i], tmp->value, tmp->optlen)) {
                    tmp = tmp->next;
                    break;
                }
                tmp = tmp->next;
            }
            if (i == pathcnt) {
                findres = 1;
                break;
            }
        }
        res++;
    }
    opthead = NULL;
    if (findres) {
        if (rcvmsg->head.t == COAP_MESSAGE_CON) {
            respmsg = litecoap_new_msg(ctx,COAP_MESSAGE_ACK,
                                       COAP_RESP_CODE(204),
                                       NULL,NULL, 0);
        } else if (rcvmsg->head.t != COAP_MESSAGE_NON){
            respmsg = litecoap_new_msg(ctx,COAP_MESSAGE_NON,
                                       COAP_RESP_CODE(204),
                                       NULL,NULL, 0);
        }

        if (respmsg == NULL) {
            return LITECOAP_PARAM_NULL;
        }

        ret = litecoap_add_token(respmsg, (char *)rcvmsg->tok->token,
                                 rcvmsg->tok->tklen);
        if (ret != LITECOAP_OK) {
            litecoap_delete_msg(respmsg);
            return LITECOAP_NG;
        }

        /* match the option, so deliver msg to resource handler function */
        res->handler(rcvmsg, respmsg);
        litecoap_send(ctx, respmsg);
    } else {
        //opthead = litecoap_add_option_to_list(opthead,
        //                                      COAP_OPTION_CONTENT_FORMAT, 
        //                                      contype, 2);
        if (rcvmsg->head.t == COAP_MESSAGE_CON) {
            respmsg = litecoap_new_msg(ctx, COAP_MESSAGE_ACK,
                                       COAP_RESP_CODE(404), 
                                       opthead, NULL, 0);
        } else {
            respmsg = litecoap_new_msg(ctx,COAP_MESSAGE_NON,
                                       COAP_RESP_CODE(404), 
                                       opthead, NULL, 0);
        }

        if (respmsg == NULL) {
            return LITECOAP_PARAM_NULL;
        }
        if (respmsg && rcvmsg && rcvmsg->tok && rcvmsg->tok->token) {
            ret = litecoap_add_token(respmsg, (char *)rcvmsg->tok->token,
                                 rcvmsg->tok->tklen);
        }
        if (ret != LITECOAP_OK) {
            litecoap_delete_msg(respmsg);
            return LITECOAP_NG;
        }
        litecoap_send(ctx, respmsg);
    }
    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_handle_msg
 Description : process reviced coap messages 
 Input       : ctx @ coap connection instance.
               msg @ recived coap message
 Output      : None
 Return      : LITECOAP_OK means process ok, other value means error happended.
 *****************************************************************************/
int litecoap_handle_msg(coap_context_t *ctx, coap_msg_t *msg)
{
    switch (msg->head.t)
    {
        case COAP_MESSAGE_ACK:
            litecoap_remove_resndqueue(ctx, msg);
            break;
        case COAP_MESSAGE_RST:
            litecoap_remove_resndqueue(ctx, msg);
            break;
        case COAP_MESSAGE_NON :
        case COAP_MESSAGE_CON :
            //litecoap_send_ack(ctx, msg);
            break;
        default:
            break;
    }

    if (ctx->response_handler != NULL) {
        ctx->response_handler(ctx, msg);
    }
    litecoap_handle_request(ctx, msg);

    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_read
 Description : read coap messages from tcp/ip stack.
 Input       : ctx @ coap connection instance.
 Output      : None
 Return      : LITECOAP_OK means process ok, other value means error happended.
 *****************************************************************************/
int litecoap_read(coap_context_t *ctx)
{
    coap_msg_t *msg = NULL;
    int len = 0;
    int ret = 0;
    send_queue_t *node = NULL;
    unsigned long long now;

    if (ctx == NULL) {
        return LITECOAP_PARAM_NULL;
    }
    len = ctx->netops->network_read( ctx->udpio, 
                                     (char *)ctx->rcvbuf.buf, 
                                     ctx->rcvbuf.len);
    if (len == 0) {
        return LITECOAP_OK;
    }
    if (len < 0) {
        return LITECOAP_SOCKET_NETWORK_ERR;
    }
    /* 
        fixed me: need parse data and then handle coap message 
        need malloc coap msg buffers, deal with it and then free, it
    */
    msg = (coap_msg_t *)litecoap_malloc(sizeof(coap_msg_t));
    if (msg == NULL) {
        return LITECOAP_MALLOC_FAILED;
    }
    (void) memset(msg, 0, sizeof(coap_msg_t));
    
    ret = litecoap_parse_header(msg, (const unsigned char *)ctx->rcvbuf.buf, len, ctx->proto);
    if (ret < 0) {
        litecoap_delete_msg(msg);
        return LITECOAP_HEADER_ERR;
    }
    ret = litecoap_parse_token(msg, (unsigned char *)ctx->rcvbuf.buf, len);
    if (ret < 0) {
        litecoap_delete_msg(msg);
        return LITECOAP_TOKEN_ERR;
    }

    ret = litecoap_parse_opts_payload(msg, (const unsigned char *)ctx->rcvbuf.buf, len);
    if (ret < 0) {
        litecoap_delete_msg(msg);
        return LITECOAP_OPTION_ERR;
    }
    
    /* 
       if pack is ack, rst ... no need send anything, if con msg, 
       send a ack and pass to response_handler
    */
    litecoap_handle_msg(ctx, msg);
    litecoap_delete_msg(msg);

    now = litecoap_time();
    node = ctx->resndque;
    while (node && node->time <= (now - ctx->base_time)) {
        litecoap_retransmit(ctx, node);
        node = node->next;
        ctx->resndque = node;
    }

    return LITECOAP_OK;
}

/*****************************************************************************
 Function    : litecoap_send
 Description : send coap messages to tcp/ip stack.
 Input       : ctx @ coap connection instance.
               msg @ coap message that need to send.
 Output      : None
 Return      : LITECOAP_OK means process ok, other value means error happended.
 *****************************************************************************/
int litecoap_send(coap_context_t *ctx, coap_msg_t *msg)
{
    int slen = 0;
    int n = 0;
    int retry = 0;
    if ((ctx == NULL) || (msg == NULL)) {
        return LITECOAP_PARAM_NULL;
    }
    if (msg->head.t == COAP_MESSAGE_CON && (ctx->proto == COAP_PROTO_UDP || ctx->proto == COAP_PROTO_DTLS)) {
        litecoap_addto_resndqueue(ctx, msg);
    }
    /* fixed me: need translate msg to bytes stream, and then send it. */
    slen = litecoap_build_byte_stream(ctx, msg);
    if (slen > ctx->sndbuf.len) {
        if (msg->head.t == COAP_MESSAGE_CON && (ctx->proto == COAP_PROTO_UDP || ctx->proto == COAP_PROTO_DTLS)) {
            litecoap_remove_resndqueue(ctx, msg);
        } else {
            litecoap_delete_msg(msg);
        }
        /* message is too long for ctx buf */
        return LITECOAP_SND_LEN_TOO_BIG;
    }
    do {
        n = ctx->netops->network_send(ctx->udpio, (char *)ctx->sndbuf.buf, slen);
        if (n != slen) {
            retry++;
            litecoap_delay(5);
        }
        if (retry == 10) {
            break;
        }
    } while(n != slen);
    /* delete msg that do not need stored for retransmit */
    if (msg->head.t != COAP_MESSAGE_CON) {
        litecoap_delete_msg(msg);
    }
    return n;
}

int litecoap_retransmit(coap_context_t *ctx, send_queue_t *node) {
    unsigned long long now;
    if (ctx == NULL || node == NULL) {
        return LITECOAP_PARAM_NULL;
    }

    if (node->retransmit_cnt < ctx->max_retransmit) {
        now = litecoap_time();
        node->retransmit_cnt++;
        if (ctx->resndque == NULL) {
            node->time = node->timeout << node->retransmit_cnt;
            ctx->base_time = now;
        } else {
            node->time = (now - ctx->base_time) + (node->timeout << node->retransmit_cnt);
        }

        litecoap_addto_resndqueue(ctx, node->msg);
        litecoap_send(ctx, node->msg);
        litecoap_free(node);
    }

    return LITECOAP_OK;
}
