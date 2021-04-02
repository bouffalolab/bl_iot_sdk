#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <joylink_memory.h>
#include <joylink_time.h>
#include <jl_tc.h>

#include <FreeRTOS.h>
#include <task.h>

static jl_tc_result_t jl_tc_time_str()
{
    int f = 0;
    //char time_str[32];
    char *time_str = NULL;
    jl_time_stamp_t ts = {
        .second = 1588075098,
        .ms = 451
    };
    jl_set_UTCtime(ts);

    time_str = jl_get_time_str();
    printf("%s: time_str %s\r\n", __func__, time_str);
    printf("%s: ts %u\r\n", __func__, jl_get_time_msec(NULL));

    printf("%s: delay 1s\r\n", __func__);
    vTaskDelay(pdMS_TO_TICKS(1000));
    time_str = jl_get_time_str();
    printf("%s: time_str %s\r\n", __func__, time_str);
    printf("%s: ts %u\r\n", __func__, jl_get_time_msec(NULL));

    printf("%s: delay 5s\r\n", __func__);
    vTaskDelay(pdMS_TO_TICKS(5000));
    time_str = jl_get_time_str();
    printf("%s: time_str %s\r\n", __func__, time_str);
    printf("%s: ts %u\r\n", __func__, jl_get_time_msec(NULL));

    return f;
}

void jl_tc_time()
{
    int f = 0;

    f += jl_tc_time_str();

    if (f == 0) {
        printf("%s SUCCESS\r\n", __func__);
    } else {
        printf("%s FAILED\r\n", __func__);
    }
}
