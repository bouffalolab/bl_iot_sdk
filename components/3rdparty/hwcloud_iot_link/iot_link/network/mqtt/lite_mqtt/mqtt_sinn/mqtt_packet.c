#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mqtt_packet.h"

static int mqtt_encode_len(unsigned char *buf, int len)
{
    int rc = 0;

    do
    {
        unsigned char d = len & (MQTT_PACKET_LEN_MASK - 1);
        len >>= MQTT_PACKET_LEN_BIT_NUM;

        if (len > 0)
            d |= MQTT_PACKET_LEN_MASK;
        buf[rc++] = d;
    } while (len > 0);

    return rc;
}

static int mqtt_decode_len(unsigned char *buf, int *len)
{
    int rc = 0;
    int mul = 1;
    unsigned char byte;

    *len = 0;
    do
    {
        byte = *(buf++);
        *len += (byte & ~MQTT_PACKET_LEN_MASK) * mul;
        if (mul > (MQTT_PACKET_LEN_MASK * MQTT_PACKET_LEN_MASK * MQTT_PACKET_LEN_MASK))
        {
            return -1;
        }
        mul *= MQTT_PACKET_LEN_MASK;
        rc++;
    } while ((byte & MQTT_PACKET_LEN_MASK) != 0);

    return rc;
}

static int mqtt_encode_num(unsigned char *buf, unsigned short num)
{
    if (buf)
    {
        buf[0] = num >> 8;
        buf[1] = num & 0xFF;
    }
    
    return MQTT_DATA_LEN;
}

static int mqtt_decode_num(unsigned char *buf, unsigned short *num)
{
    if (buf)
    {
        *num = (buf[0] << 8) + buf[1];
    }

    return MQTT_DATA_LEN;
}

static int mqtt_encode_string(unsigned char *buf, const char *str)
{
    size_t str_len = 0;
    int len = 0;

    str_len = strlen(str);
    len = mqtt_encode_num(buf, str_len);
    memcpy(buf + len, str, str_len);

    return  (len + str_len);
}

static int mqtt_decode_string(unsigned char *buf, char **str, unsigned short *num)
{
    int len = 0;

    len = mqtt_decode_num(buf, num);
    *str = (char *)buf + len;

    return (len + *num);
}


int mqtt_encode_fixhead(unsigned char *buf, unsigned char type, unsigned char dup,
                                unsigned char qos, unsigned char retain, int remaining_len)
{
    int len = 1;

    mqtt_fix_head_t *head = (mqtt_fix_head_t *)buf;

    head->mqtt_first_byte_u.bits.type = type;
    head->mqtt_first_byte_u.bits.dup = dup;
    head->mqtt_first_byte_u.bits.qos = qos;
    head->mqtt_first_byte_u.bits.retain = retain;
    len += mqtt_encode_len( head->remaining_len, remaining_len);

    return len;
}

int mqtt_decode_fixhead(unsigned char *buf, unsigned char *type, unsigned char *dup,
                        unsigned char *qos, unsigned char *retain, int *remaining_len)
{
    int len = 1;

    mqtt_fix_head_t *head = (mqtt_fix_head_t *)buf;

    *type = head->mqtt_first_byte_u.bits.type;
    *dup = head->mqtt_first_byte_u.bits.dup;
    *qos = head->mqtt_first_byte_u.bits.qos;
    *retain = head->mqtt_first_byte_u.bits.retain;
    len += mqtt_decode_len(head->remaining_len, remaining_len);

    return len;
}

int mqtt_encode_connect(unsigned char *buf, int buf_len, mqtt_connect_opt_t *options)
{
    int len = 0;
    int remaining_len = 0;
    unsigned char *vhead_buf;
    unsigned char *payload_buf;

    //SINN_ASSERT(options->connect_payload.client_id, "client id is null");
    // add connect variable header size
    remaining_len += sizeof(mqtt_connect_head_t);

    // add payload size
    remaining_len += (int)strlen(options->connect_payload.client_id) + MQTT_STRING_LEN;
    if (options->connect_head.mqtt_connect_flag_u.bits.will_flag
        && options->connect_payload.will_topic
        && options->connect_payload.will_msg)
    {
        remaining_len += (int)strlen(options->connect_payload.will_topic) + MQTT_STRING_LEN;
        remaining_len += (int)strlen(options->connect_payload.will_msg) + MQTT_STRING_LEN;
    }

    if (options->connect_head.mqtt_connect_flag_u.bits.user_name_flag && options->connect_payload.user_name)
        remaining_len += (int)strlen(options->connect_payload.user_name) + MQTT_STRING_LEN;

    if (options->connect_head.mqtt_connect_flag_u.bits.psd_flag && options->connect_payload.password)
        remaining_len += (int)strlen(options->connect_payload.password) + MQTT_STRING_LEN;

    /* Encode fix header */
    len = mqtt_encode_fixhead(buf, MQTT_PACKET_TYPE_CONNECT, 0, 0, 0, remaining_len);
    if ((len + remaining_len) > buf_len)
        return -1;

    /* check variable header and payload */
    // TODO
    /* Encode variable header */
    vhead_buf = buf + len;
    //#define SWAP16(x) ((x & 0xFF00) >> 8) | ((x & 0x00FF) << 8)
    //options->connect_head.keep_alive = SWAP16(options->connect_head.keep_alive);
    memcpy(vhead_buf, &(options->connect_head), sizeof(options->connect_head) - sizeof(options->connect_head.keep_alive));
    mqtt_encode_num(vhead_buf + sizeof(options->connect_head) - sizeof(options->connect_head.keep_alive), options->connect_head.keep_alive);

    /* Encode payload*/
    payload_buf = vhead_buf + sizeof(options->connect_head);

    payload_buf += mqtt_encode_string(payload_buf, options->connect_payload.client_id);

    if (options->connect_head.mqtt_connect_flag_u.bits.will_flag
        && options->connect_payload.will_topic
        && options->connect_payload.will_msg)
    {
        payload_buf += mqtt_encode_string(payload_buf, options->connect_payload.will_topic);
        payload_buf += mqtt_encode_string(payload_buf, options->connect_payload.will_msg);
    }

    if (options->connect_head.mqtt_connect_flag_u.bits.user_name_flag && options->connect_payload.user_name)
        payload_buf += mqtt_encode_string(payload_buf, options->connect_payload.user_name);

    if (options->connect_head.mqtt_connect_flag_u.bits.psd_flag && options->connect_payload.password)
        payload_buf += mqtt_encode_string(payload_buf, options->connect_payload.password);

    return (len + remaining_len);
}

int mqtt_encode_publish(unsigned char *buf, int buf_len, mqtt_publish_opt_t *options)
{
    int len = 0;
    int remaining_len = 0;
    unsigned char *vhead_buf;
    unsigned char *payload_buf;

    // add connect variable header size
    if (options->publish_head.topic)
        remaining_len += (int)strlen(options->publish_head.topic) + MQTT_STRING_LEN;

    remaining_len += sizeof(options->publish_head.packet_id);

    if (options->publish_payload.msg)
        remaining_len += (int)strlen(options->publish_payload.msg);
    /* Encode fix header */
    len = mqtt_encode_fixhead(buf, MQTT_PACKET_TYPE_PUBLISH, options->dup, 
                              options->qos, options->retain, remaining_len);

    /* Encode variable header */
    vhead_buf = buf + len;
    vhead_buf += mqtt_encode_string(vhead_buf, options->publish_head.topic);
    if (options->qos > 0)
        vhead_buf += mqtt_encode_num(vhead_buf, options->publish_head.packet_id);

    /* Encode payload*/
    payload_buf = vhead_buf;
    if (options->publish_payload.msg)
        memcpy(payload_buf, options->publish_payload.msg, strlen(options->publish_payload.msg));

    return (len + remaining_len);
}

int mqtt_decode_publish(unsigned char *buf, int buf_len, mqtt_publish_opt_t *options)
{
    int len = 0, remaning_len = 0;
    unsigned char type = 0;
    unsigned char *vhead_buf;
    unsigned char *payload_buf;
    len = mqtt_decode_fixhead(buf, &type, &options->dup, &options->qos, &options->retain, &remaning_len);
    if (type != MQTT_PACKET_TYPE_PUBLISH)
    {
        LINK_LOG_DEBUG("decode pulish error\r\n");
        return -1;
    }

    vhead_buf = buf + len;
    vhead_buf += mqtt_decode_string(vhead_buf, &options->publish_head.topic, &options->publish_head.topic_len);

    if (options->qos > 0)
        vhead_buf += mqtt_decode_num(vhead_buf, &options->publish_head.packet_id);

    payload_buf = vhead_buf;
    options->publish_payload.msg = (char *)payload_buf;
    options->publish_payload.msg_len = remaning_len - options->publish_head.topic_len - MQTT_STRING_LEN;

    return 0;
}


int mqtt_encode_subscribe(unsigned char *buf, int buf_len, mqtt_subscribe_opt_t *options)
{
    int i = 0;
    int len = 0;
    int remaining_len = 0;
    unsigned char *vhead_buf;
    unsigned char *payload_buf;

    remaining_len += sizeof(options->subscribe_head);
    for (i = 0; i < options->subscribe_payload.count; i++)
    {
        remaining_len += MQTT_STRING_LEN + MQTT_QOS_LEN + (int)strlen(options->subscribe_payload.topic[i]);
    }

    /* Encode fix header */
    len = mqtt_encode_fixhead(buf, MQTT_PACKET_TYPE_SUBSCRIBE, 0, 1, 0, remaining_len);
    /* Encode variable header */
    vhead_buf = buf + len;
    vhead_buf += mqtt_encode_num(vhead_buf, options->subscribe_head.packet_id);

    /* Encode payload*/
    payload_buf = vhead_buf;
    for (i = 0; i < options->subscribe_payload.count; i++)
    {
        payload_buf += mqtt_encode_string(payload_buf, options->subscribe_payload.topic[i]);
        *payload_buf = options->subscribe_payload.qoss[i];
        payload_buf += 1;
    }

    return (len + remaining_len);
}

int mqtt_decode_suback(unsigned char *buf, int buf_len, mqtt_suback_opt_t *options)
{
    int i = 0;
    int len = 0, remaning_len = 0;
    unsigned char type = 0;
    unsigned char reserved = 0;
    unsigned char *vhead_buf;
    unsigned char *payload_buf;
    len = mqtt_decode_fixhead(buf, &type, &reserved, &reserved, &reserved, &remaning_len);
    if (type != MQTT_PACKET_TYPE_SUBACK)
    {
        LINK_LOG_DEBUG("decode suback error\r\n");
        return -1;
    }

    vhead_buf = buf + len;
    vhead_buf += mqtt_decode_num(vhead_buf, &options->suback_head.packet_id);

    payload_buf = vhead_buf;
    options->count = (remaning_len - MQTT_DATA_LEN);
    options->suback_payload.ret_code = (unsigned char *)malloc(options->count);
    for (i = 0; i < options->count; i++)
        options->suback_payload.ret_code[i] = payload_buf[i];

    return 0;
}


int mqtt_encode_puback(unsigned char *buf, int buf_len, mqtt_puback_opt_t *options)
{
    int len = 0;
    int remaining_len = sizeof(options->puback_head);
    unsigned char *vhead_buf;

    len = mqtt_encode_fixhead(buf, options->type, 0, (options->type == MQTT_PACKET_TYPE_PUBREL) ? 1 : 0, 0, remaining_len);
    vhead_buf = buf + len;
    vhead_buf += mqtt_encode_num(vhead_buf, options->puback_head.packet_id);

    return (len + remaining_len);
}


int mqtt_decode_puback(unsigned char *buf, int buf_len, mqtt_puback_opt_t *options, unsigned char mqtt_type)
{
    int len = 0, remaning_len = 0;
    unsigned char type = 0;
    unsigned char reserved = 0;
    unsigned char *vhead_buf;
    len = mqtt_decode_fixhead(buf, &type, &reserved, &reserved, &reserved, &remaning_len);
    if (type != mqtt_type)
    {
        LINK_LOG_DEBUG("decode puback error\r\n");
        return -1;
    }

    vhead_buf = buf + len;
    vhead_buf += mqtt_decode_num(vhead_buf, &options->puback_head.packet_id);

    return 0;
}


int mqtt_encode_unsubscribe(unsigned char *buf, int buf_len, mqtt_unsubscribe_opt_t *options)
{
    int i = 0;
    int len = 0;
    int remaining_len = 0;
    unsigned char *vhead_buf;
    unsigned char *payload_buf;

    remaining_len += sizeof(options->unsubscribe_head);

    for (i = 0; i < options->unsubscribe_payload.count; i++)
    {
        remaining_len += MQTT_STRING_LEN + (int)strlen(options->unsubscribe_payload.topic[i]);
    }

    /* Encode fix header */
    len = mqtt_encode_fixhead(buf, MQTT_PACKET_TYPE_UNSUBSCRIBE, 0, 1, 0, remaining_len);
    /* Encode variable header */
    vhead_buf = buf + len;
    vhead_buf += mqtt_encode_num(vhead_buf, options->unsubscribe_head.packet_id);

    /* Encode payload*/
    payload_buf = vhead_buf;
    for (i = 0; i < options->unsubscribe_payload.count; i++)
    {
        payload_buf += mqtt_encode_string(payload_buf, options->unsubscribe_payload.topic[i]);
    }

    return (len + remaining_len);
}


int mqtt_encode_ping(unsigned char *buf, int buf_len)
{
    int len = 0;
    len = mqtt_encode_fixhead(buf, MQTT_PACKET_TYPE_PINGREQ, 0, 0, 0, 0);

    return len;
}

int mqtt_encode_disconnect(unsigned char *buf, int buf_len)
{
    int len = 0;
    len = mqtt_encode_fixhead(buf, MQTT_PACKET_TYPE_DISCONNECT, 0, 0, 0, 0);

    return len;
}
