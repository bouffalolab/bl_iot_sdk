#include <stdio.h>
#include <stdint.h>
#include <joylink_memory.h>
#include <jl_tc.h>

void jl_tc_memory()
{
    int failures = 0;
    int success = 0;
    void *ptr1;
    uint8_t *u8ptr1;

    ptr1 = jl_platform_malloc(32);
    if (ptr1) {
        success++;
    } else {
        failures++;
    }

    u8ptr1 = ptr1;
    u8ptr1[0] = 0xef;
    u8ptr1[1] = 0xbb;
    u8ptr1[2] = 0xbf;

    ptr1 = jl_platform_realloc(ptr1, 64);
    if (ptr1) {
        u8ptr1 = ptr1;
        if (u8ptr1[0] == 0xef && u8ptr1[1] == 0xbb && u8ptr1[2] == 0xbf) {
            success++;
        } else {
            failures++;
        }
    } else {
        failures++;
    }
    jl_platform_free(ptr1);
    ptr1 = NULL;

    ptr1 = jl_platform_calloc(1, 3);
    if (ptr1) {
        u8ptr1 = ptr1;
        if (u8ptr1[0] == 0 && u8ptr1[1] == 0 && u8ptr1[2] == 0) {
            success++;
        } else {
            failures++;
        }
    } else {
        failures++;
    }
    jl_platform_free(ptr1);
    ptr1 = NULL;

    if (failures == 0) {
        printf("%s SUCCESS\r\n", __func__);
    } else {
        printf("%s FAILED\r\n", __func__);
    }
}
