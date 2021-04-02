#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <joylink_stdio.h>
#include <jl_tc.h>

void jl_tc_stdio()
{
    int s = 0, f = 0;
    char buf[128];
    int ret;
    int i;
    char rand_test_dict[256];
    uint8_t low_byte;
    int ones_cnt;

    jl_platform_printf("hello, %s, 3 + 4 = %d\r\n", __func__, 3 + 4);

    memset(buf, 0xA5, sizeof buf);
    ret = jl_platform_sprintf(buf, "%s-%d", "AB", 98);
    if (ret == (2+1+2) && buf[0] == 'A' && buf[1] == 'B' && buf[2] == '-' && buf[3] == '9' && buf[4] == '8' && buf[5] == '\0') {
        s++;
    } else {
        f++;
    }

    memset(buf, 0xA5, sizeof buf);
    ret = jl_platform_snprintf(buf, 128, "%s-%d", "AB", 98);
    if (ret == (2+1+2) && buf[0] == 'A' && buf[1] == 'B' && buf[2] == '-' && buf[3] == '9' && buf[4] == '8' && buf[5] == '\0') {
        s++;
    } else {
        f++;
    }

    for (i = 0; i < 16; ++i) {
        printf("jl_get_random -> %08lX\r\n", jl_get_random());
    }
    memset(rand_test_dict, 0, 256);
    for (i = 0; i < 256 * 1024; ++i) {
        low_byte = jl_get_random() & 255;
        rand_test_dict[low_byte] = 1;
    }
    for (i = 0, ones_cnt = 0; i < 256; ++i) {
        if (rand_test_dict[i] == 1) {
            ones_cnt++;
        }
    }
    printf("ones_cnt %d\r\n", ones_cnt);
    if (ones_cnt > 250) {
        s++;
    } else {
        f++;
    }

    if (f == 0) {
        printf("%s SUCCESS\r\n", __func__);
    } else {
        printf("%s FAILED\r\n", __func__);
    }
}
