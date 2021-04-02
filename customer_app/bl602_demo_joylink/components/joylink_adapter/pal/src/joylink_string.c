#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// joylink platform layer header files
#include "joylink_string.h"


/** @defgroup group_platform_string_api_manage
 *  @{
 */

/**
 * @brief   把 src 所指向的字符串复制到 dest
 *
 * @param[in] dest: 指向用于存储复制内容的目标数组
 * @param[in] src:  要复制的字符串
 * @return 
    一个指向最终的目标字符串 dest 的指针。
 * @see None.
 * @note None.
 */
char *jl_platform_strcpy(char *dest, const char*src)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    return strcpy(dest, src);
#else
    return NULL;
#endif
#endif
    return strcpy(dest, src);
}


/**
 * @brief   把 src 所指向的字符串复制指定长度到 dest
 *
 * @param[in] dest: 指向用于存储复制内容的目标数组
 * @param[in] src:  要复制的字符串
 * @param[in] n:  要复制的字符串的长度
 * @return 
    一个指向最终的目标字符串 dest 的指针。
 * @see None.
 * @note None.
 */
char *jl_platform_strncpy(char *dest, const char*src, int n)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    return strncpy(dest, src, n);
#else
    return NULL;
#endif
#endif
    return strncpy(dest, src, n);
}

/**
 * @brief   在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置。
 *
 * @param[in]  s:  要被检索的 C 字符串。
 * @param[in]  c:  在 str 中要搜索的字符。
 * @return
    该函数返回在字符串 str 中第一次出现字符 c 的位置，如果未找到该字符则返回 NULL。
 * @see None.
 * @note None.
 */
char *jl_platform_strchr(const char *s, int32_t c)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    return strchr(s, c);
#else
    return NULL;
#endif
#endif
    return strchr(s, c);
}

/**
 * @brief   在字符串 haystack 中查找第一次出现字符串 needle 的位置，不包含终止符 '\0'
 *
 * @param[in]  haystack:  要被检索的 C 字符串
 * @param[in]  needle:  在 haystack 字符串内要搜索的小字符串
 * @return
    该函数返回在 haystack 中第一次出现 needle 字符串的位置，如果未找到则返回 null
 * @see None.
 * @note None.
 */
char *jl_platform_strstr(const char *haystack, const char* needle)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    return strstr(haystack, needle);
#else
    return NULL;
#endif
#endif
    return strstr(haystack, needle);
}

/**
 * @brief   把 s1 所指向的字符串和 s2 所指向的字符串进行比较
 *
 * @param[in]  s1:  要进行比较的第一个字符串
 * @param[in]  s2:  要进行比较的第二个字符串
 * @return
    如果返回值 < 0，则表示 s1 小于 s2
    如果返回值 > 0，则表示 s2 小于 s1
    如果返回值 = 0，则表示 s1 等于 s2
 * @see None.
 * @note None.
 */
int32_t   jl_platform_strcmp(const char *s1, const char *s2)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    return strcmp(s1, s2);
#else
    return 0;
#endif
#endif
    return strcmp(s1, s2);
}

/**
 * @brief   把 s1 所指向的字符串和 s2 所指向的字符串进行比较, 最多比较前 n 个字节
 *
 * @param[in]  s1:  要进行比较的第一个字符串
 * @param[in]  s2:  要进行比较的第二个字符串
 * @param[in]  n:   要比较的最大字符数
 * @return
    如果返回值 < 0，则表示 s1 小于 s2
    如果返回值 > 0，则表示 s2 小于 s1
    如果返回值 = 0，则表示 s1 等于 s2
 * @see None.
 * @note None.
 */
int32_t   jl_platform_strncmp(const char *s1, const char *s2, uint32_t n)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    return strncmp(s1, s2, n);
#else
    return 0;
#endif
#endif
    return strncmp(s1, s2, n);
}

/**
 * @brief   把参数 str 所指向的字符串转换为一个整数（类型为 int 型）
 *
 * @param[in]  nptr:  要转换为整数的字符串
 * @return
    该函数返回转换后的长整数，如果没有执行有效的转换，则返回零
 * @see None.
 * @note None.
 */
int32_t   jl_platform_atoi(const char* nptr)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    return atoi(nptr);
#else
    return 0;
#endif
#endif
    return atoi(nptr);
}

/**
 * @brief   计算字符串 str 的长度，直到空结束字符，但不包括空结束字符
 *
 * @param[in] s: 要计算长度的字符串.
 * @return
 * 该函数返回字符串的长度
 * @see None.
 * @note None.
 */
uint32_t jl_platform_strlen(const char *s)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    return strlen(s);
#else
    return 0;
#endif
#endif
    return strlen(s);
}

/** @} */ /* end of platform_string_api_manage */
