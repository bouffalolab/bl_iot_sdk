#include <string.h>

#include "sinn_client.h"
#include "sinn_mqtt.h"

int sinn_mqtt_packetid(sinn_connection_t *nc)
{
    sinn_mqtt_proto_data_t *pd = (sinn_mqtt_proto_data_t *)nc->proto_data;
    return pd->next_packetid = (pd->next_packetid == MAX_PACKET_ID) ? 1 : pd->next_packetid + 1;
}


int sinn_mqtt_parser(sinn_buf_t *io, sinn_mqtt_msg_t *amm)
{
    int len = 0;
    int rem_len = 0;

    len = mqtt_decode_fixhead(io->data, &amm->type, &amm->dup, (unsigned char *)&amm->qos, &amm->retained, &rem_len);
    if (io->len < 2)
        return MQTTPACKET_BUFFER_TOO_SHORT;

    switch(amm->type)
    {
        case MQTT_PACKET_TYPE_PINGREQ:
            break;
        case MQTT_PACKET_TYPE_CONNACK:
            amm->ret = malloc(sizeof(char));
            amm->ret[0] = io->data[len+rem_len-1];
            break;
        case MQTT_PACKET_TYPE_PUBACK:
            break;
        case MQTT_PACKET_TYPE_SUBACK:
            {
                int i = 0;
                mqtt_suback_opt_t options;
                mqtt_decode_suback(io->data, len, &options);
                amm->ret = malloc(sizeof(char) * options.count);
                for (i = 0; i < options.count; i++)
                {
                    if (options.suback_payload.ret_code[i] != 0x80)
                    {
                        amm->mqtt_data->messageHandlers[i].efficient = 1;
                        amm->ret[i] = options.suback_payload.ret_code[i];
                    }
                    else
                    {
                        amm->mqtt_data->messageHandlers[i].efficient = 0;
                    }
                }
                free(options.suback_payload.ret_code);
            }
            break;
        case MQTT_PACKET_TYPE_UNSUBACK:
            break;
        case MQTT_PACKET_TYPE_PUBLISH:
            {
                int i = 0;
                mqtt_publish_opt_t options;
                mqtt_decode_publish(io->data, len, &options);
                amm->payloadlen = options.publish_payload.msg_len;
                amm->payload = options.publish_payload.msg;
                amm->topiclen = options.publish_head.topic_len;
                amm->topic = options.publish_head.topic;
                amm->id = options.publish_head.packet_id;
                LINK_LOG_DEBUG("pub payload:%d %s\r\n", (int)amm->payloadlen, (char *)amm->payload);
                for (i = 0; i < SINN_MQTT_BUILTIN_NUM; i++)
                {
                    if(amm->mqtt_data->messageHandlers[i].topicFilter && (memcmp(options.publish_head.topic, amm->mqtt_data->messageHandlers[i].topicFilter, options.publish_head.topic_len) == 0))
                    {
                        amm->arg = amm->mqtt_data->messageHandlers[i].arg;
                        if(amm->mqtt_data->messageHandlers[i].efficient)
                        {
                            amm->mqtt_data->messageHandlers[i].cb(amm);
                        }
                    }
                }
            }
            break;
        case MQTT_PACKET_TYPE_PUBREC:
        case MQTT_PACKET_TYPE_PUBREL:
            {
                mqtt_puback_opt_t options;
                mqtt_decode_puback(io->data, len, &options, amm->type);
                amm->id = options.puback_head.packet_id;
            }
            break;
    }

    amm->len = len + rem_len;
    return amm->len;
}

void sinn_mqtt_event_handler(sinn_connection_t *nc, int event, void *event_data)
{
    int len;
    sinn_mqtt_msg_t amm = {0};
    sinn_mqtt_proto_data_t *data = (sinn_mqtt_proto_data_t *)nc->proto_data;
    amm.mqtt_data = data;
    sinn_time_t now;
    sinn_buf_t *io = &nc->recv_buf;
    nc->user_handler(nc, event, event_data);
    switch(event)
    {
        case SINN_EV_RECV:
            while(1)
            {
                len = sinn_mqtt_parser(io, &amm);
                if(len <= 0)
                {
                    /* TODO */
                    break;
                }
                nc->user_handler(nc, EV_MQTT_BASE + amm.type, &amm);
                memmove(nc->recv_buf.data, nc->recv_buf.data + len, nc->recv_buf.len);
                nc->recv_buf.len -= len;
            }
            break;
        case SINN_EV_POLL:
            now = sinn_gettime_ms();
            if(((now - data->last_time) > data->keep_alive*1000) && (data->last_time > 0) && (data->keep_alive > 0))
            {
                sinn_mqtt_ping(nc);
            }
            break;
    }
}

int sinn_mqtt_connect(sinn_connection_t *nc, mqtt_connect_opt_t *options)
{
    int rc = -1;
    sinn_mqtt_proto_data_t *data;
    mqtt_connect_opt_t default_options = (mqtt_connect_opt_t)MQTT_CONNECT_OPT_INIT;
    int len = 0;

    if (options == NULL)
        options = &default_options; /* set default options if none were supplied */

    data = (sinn_mqtt_proto_data_t *)nc->proto_data;
    data->keep_alive = options->connect_head.keep_alive;
    data->next_packetid = 1;

    if ((len = mqtt_encode_connect((nc->send_buf.data + nc->send_buf.len), (nc->send_buf.size - nc->send_buf.len), options)) <= 0)
    {
        LINK_LOG_DEBUG("mqtt connect error\r\n");
        return rc;
    }
    nc->send_buf.len += len;
    data->last_time = sinn_gettime_ms();

    return 0;
}

int sinn_mqtt_ping(sinn_connection_t *nc)
{
    int len = 0;
    sinn_mqtt_proto_data_t *data;
    data = (sinn_mqtt_proto_data_t *)nc->proto_data;
    len = mqtt_encode_ping((nc->send_buf.data + nc->send_buf.len), (nc->send_buf.size - nc->send_buf.len));
    if (len > 0)
        nc->send_buf.len += len;
    data->last_time = sinn_gettime_ms();

    return len;
}

int sinn_mqtt_disconnect(sinn_connection_t *nc)
{
    int len = 0;
    sinn_mqtt_proto_data_t *data;
    data = (sinn_mqtt_proto_data_t *)nc->proto_data;
    len = mqtt_encode_disconnect((nc->send_buf.data + nc->send_buf.len), (nc->send_buf.size - nc->send_buf.len));
    if (len > 0)
        nc->send_buf.len += len;
    data->last_time = sinn_gettime_ms();

    return len;
}

int sinn_mqtt_publish(sinn_connection_t *nc, mqtt_publish_opt_t *options)
{
    int len = 0;

    sinn_mqtt_proto_data_t *data;
    data = (sinn_mqtt_proto_data_t *)nc->proto_data;

    if(options->qos)
        options->publish_head.packet_id = sinn_mqtt_packetid(nc);
    len = mqtt_encode_publish((nc->send_buf.data + nc->send_buf.len), (nc->send_buf.size - nc->send_buf.len), options);
    if (len > 0)
        nc->send_buf.len += len;
    data->last_time = sinn_gettime_ms();

    return len;
}

int sinn_mqtt_subscribe(sinn_connection_t *nc, mqtt_subscribe_opt_t *options, sinn_mqtt_msg_handler cbs, void *arg)
{
    int len = 0;
    int i = 0;
    sinn_mqtt_proto_data_t *data;
    data = (sinn_mqtt_proto_data_t *)nc->proto_data;
    options->subscribe_head.packet_id = sinn_mqtt_packetid(nc);

    for ( i = 0; i < options->subscribe_payload.count; i++)
    {
        data->messageHandlers[i].topicFilter = options->subscribe_payload.topic[i];
        data->messageHandlers[i].cb = cbs;
        data->messageHandlers[i].arg = arg;
    }

    len = mqtt_encode_subscribe((nc->send_buf.data + nc->send_buf.len), (nc->send_buf.size - nc->send_buf.len), options);
    if (len > 0)
        nc->send_buf.len += len;
    data->last_time = sinn_gettime_ms();

    return len;
}

int sinn_mqtt_puback(sinn_connection_t *nc, mqtt_puback_opt_t *options)
{
    int len = 0;
    sinn_mqtt_proto_data_t *data;
    data = (sinn_mqtt_proto_data_t *)nc->proto_data;

    len = mqtt_encode_puback((nc->send_buf.data + nc->send_buf.len), (nc->send_buf.size - nc->send_buf.len), options);
    if (len > 0)
        nc->send_buf.len += len;
    data->last_time = sinn_gettime_ms();

    return len;
}

int sinn_mqtt_unsubscribe(sinn_connection_t *nc, mqtt_unsubscribe_opt_t *options)
{
    int len = 0;
    sinn_mqtt_proto_data_t *data;
    data = (sinn_mqtt_proto_data_t *)nc->proto_data;
    options->unsubscribe_head.packet_id = sinn_mqtt_packetid(nc);

    len = mqtt_encode_unsubscribe((nc->send_buf.data + nc->send_buf.len), (nc->send_buf.size - nc->send_buf.len), options);
    if (len > 0)
        nc->send_buf.len += len;
    data->last_time = sinn_gettime_ms();

    return len;
}
