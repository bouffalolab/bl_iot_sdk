#ifndef __SINN_MQTT_H__
#define __SINN_MQTT_H__
#include "mqtt_packet.h"
#include "sinn_config.h"


typedef enum MQTT_CONNACK_RETCODE
{
    MQTT_CONNACK_ACCEPTED = 0x0,
    MQTT_CONNACK_UNACCEPTABLE_VERSION = 0x1,
    MQTT_CONNACK_CLIENTID_REJECTED = 0x2,
    MQTT_CONNACK_SERVER_UNAVAILABLE = 0x3,
    MQTT_CONNACK_BAD_AUTH = 0x4,
    MQTT_CONNACK_NOT_AUTHORIZED = 0x5,
} MQTT_CONNACK_RETCODE_e;



#define EV_MQTT_BASE             0x100
#define EV_MQTT_CONNECT          (EV_MQTT_BASE + MQTT_PACKET_TYPE_CONNECT)
#define EV_MQTT_CONNACK          (EV_MQTT_BASE + MQTT_PACKET_TYPE_CONNACK)
#define EV_MQTT_PUBLISH          (EV_MQTT_BASE + MQTT_PACKET_TYPE_PUBLISH)
#define EV_MQTT_PUBACK           (EV_MQTT_BASE + MQTT_PACKET_TYPE_PUBACK)
#define EV_MQTT_PUBREC           (EV_MQTT_BASE + MQTT_PACKET_TYPE_PUBREC)
#define EV_MQTT_PUBREL           (EV_MQTT_BASE + MQTT_PACKET_TYPE_PUBREL)
#define EV_MQTT_PUBCOMP          (EV_MQTT_BASE + MQTT_PACKET_TYPE_PUBCOMP)
#define EV_MQTT_SUBSCRIBE        (EV_MQTT_BASE + MQTT_PACKET_TYPE_SUBSCRIBE)
#define EV_MQTT_SUBACK           (EV_MQTT_BASE + MQTT_PACKET_TYPE_SUBACK)
#define EV_MQTT_UNSUBSCRIBE      (EV_MQTT_BASE + MQTT_PACKET_TYPE_UNSUBSCRIBE)
#define EV_MQTT_UNSUBACK         (EV_MQTT_BASE + MQTT_PACKET_TYPE_UNSUBACK)
#define EV_MQTT_PINGREQ          (EV_MQTT_BASE + MQTT_PACKET_TYPE_PINGREQ)
#define EV_MQTT_PINGRESP         (EV_MQTT_BASE + MQTT_PACKET_TYPE_PINGRESP)
#define EV_MQTT_DISCONNECT       (EV_MQTT_BASE + MQTT_PACKET_TYPE_DISCONNECT)



#define MAX_PACKET_ID 0xFFFF


typedef struct sinn_mqtt_proto_data  sinn_mqtt_proto_data_t;

typedef struct sinn_mqtt_msg
{
    unsigned char type;
    EN_QOS qos;
    unsigned int len;
    unsigned char retained;
    unsigned char dup;
    unsigned short id;
    void *payload;
    size_t payloadlen;
    char *topic;
    size_t topiclen;
    sinn_mqtt_proto_data_t *mqtt_data;
    void *arg;

    char *ret;    // used for conret and subret
} sinn_mqtt_msg_t;



typedef void (*sinn_mqtt_msg_handler)(sinn_mqtt_msg_t *);

typedef struct sinn_mqtt_proto_data
{
    unsigned short keep_alive;
    sinn_time_t last_time;
    unsigned int next_packetid;
    struct MessageHandlers
    {
        unsigned char efficient;
        const char* topicFilter;
        sinn_mqtt_msg_handler cb;
        void *arg;
    } messageHandlers[SINN_MQTT_BUILTIN_NUM];      /* Message handlers are indexed by subscription topic */
} sinn_mqtt_proto_data_t;


int sinn_mqtt_packetid(sinn_connection_t *nc);
int sinn_mqtt_connect(sinn_connection_t *nc, mqtt_connect_opt_t *options);
int sinn_mqtt_publish(sinn_connection_t *nc, mqtt_publish_opt_t *options);
int sinn_mqtt_subscribe(sinn_connection_t *nc, mqtt_subscribe_opt_t *options, sinn_mqtt_msg_handler cbs, void *arg);
int sinn_mqtt_puback(sinn_connection_t *nc, mqtt_puback_opt_t *options);
int sinn_mqtt_ping(sinn_connection_t *nc);
int sinn_mqtt_disconnect(sinn_connection_t *nc);
int sinn_mqtt_unsubscribe(sinn_connection_t *nc, mqtt_unsubscribe_opt_t *options);
void sinn_mqtt_event_handler(sinn_connection_t *nc, int event, void *event_data);

#endif
