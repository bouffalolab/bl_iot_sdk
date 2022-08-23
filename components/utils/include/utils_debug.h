#ifndef __UTILS_DEBUG_H__
#define __UTILS_DEBUG_H__
#include <stdio.h>
#define BL_ASSERT_ERROR(cond) do {\
    if (!(cond)) { \
        printf("[ASSERT] [ERR] %s:%d\r\n", __FILENAME__, __LINE__); \
        while (1) { \
        } \
    } \
} while (0)

#endif
