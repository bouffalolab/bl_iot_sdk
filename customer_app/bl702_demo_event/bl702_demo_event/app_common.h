#ifndef __APP_COMMON_H__
#define __APP_COMMON_H__
#include <aos/kernel.h>
#include <aos/yloop.h>

struct AppEvent{
    input_event_t event;
    void *pdata;
};

static struct AppEvent gAppEvt;

__inline static void AppDelayHandler(void *private_data)
{
    struct AppEvent *evt = (struct AppEvent *)private_data;
    input_event_t *event = &evt->event;
    aos_post_event(event->type,event->code,event->value);
}

/*!
    Task register.
*/
#define TASK_REGISTER(TASK,TASK_ID,DATA) {\
        aos_register_event_filter(TASK_ID,TASK,DATA);\
}

/*!
    Immediately trigger asynchronous events.
*/
#define SEND_EVENT_NOW(TASK_ID,EVT_ID,VAL){\
        aos_post_event(TASK_ID,EVT_ID,VAL);\
}

/*!
    Condition: Valid only in registered TASK
    Cancel current delay messages.
*/
#define CANCEL_MESSAGE(TASK_ID,EVT_ID,MSG){\
        gAppEvt.event.type = TASK_ID;\
        gAppEvt.event.code = EVT_ID;\
        gAppEvt.pdata = MSG;\
        aos_cancel_delayed_action(-1,AppDelayHandler,&gAppEvt);\
}

/*!
    Condition: Valid only in registered TASK.
    Delay time to send messages.
*/
#define SEND_MESSAGE_LATER(TASK_ID,EVT_ID,MSG,TIME){\
        gAppEvt.event.type = TASK_ID;\
        gAppEvt.event.code = EVT_ID;\
        gAppEvt.pdata = MSG;\
        aos_cancel_delayed_action(-1,AppDelayHandler,&gAppEvt);\
        aos_post_delayed_action(TIME,AppDelayHandler,&gAppEvt);\
}

#endif
