#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <joylink_memory.h>
#include <joylink_socket.h>
#include <jl_tc.h>

static jl_tc_result_t jl_tc_platform_gethostbyname()
{
    int s = 0, f = 0;
    char ip_buff[32];

    memset(ip_buff, 0, 32);
    if (jl_platform_gethostbyname("dev.bouffalolab.com", ip_buff, 32) == 0 && (strcmp("106.15.195.166", ip_buff) == 0)) {
        s++;
    } else {
        f++;
    }

    if (jl_platform_gethostbyname("aabb", ip_buff, 32) == -1) {
        s++;
    } else {
        f++;
    }

    return f;
}

void jl_tc_socket()
{
    int f = 0;

    f += jl_tc_platform_gethostbyname();

    if (f == 0) {
        printf("%s SUCCESS\r\n", __func__);
    } else {
        printf("%s FAILED\r\n", __func__);
    }
}
