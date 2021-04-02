#ifndef _JOYLINK_STDIO_H_
#define _JOYLINK_STDIO_H_

#include <stddef.h>
#include "joylink_stdint.h"

/** @} */ /* end of platform_memory_manage */

/**
 * @brief 将数据格式化打印到流
 *
 * @param [in] fmt: @n String that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return None.
 * @see None.
 * @note None.
 */
int32_t   jl_platform_printf(const char *fmt, ...);

/**
 * @brief 将数据安格式化写入到字符串
 *
 * @param [out] str: @n String that holds written text.
 * @param [in] fmt: @n Format that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return bytes of character successfully written into string.
 * @see None.
 * @note None.
 */
int32_t jl_platform_sprintf(char *str, const char *fmt, ...);

/**
 * @brief 将数据安指定长度格式化写入到字符串
 *
 * @param [out] str: @n String that holds written text.
 * @param [in] len: @n Maximum length of character will be written
 * @param [in] fmt: @n Format that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return bytes of character successfully written into string.
 * @see None.
 * @note None.
 */
int32_t jl_platform_snprintf(char *str, const int32_t len, const char *fmt, ...);

/**
 * @brief 将字符串格式化写入到数据
 *
 * @param [in] str: @n String that holds written text.
 * @param [in] fmt: @n Format that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [out] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return bytes of character successfully written into string.
 * @see None.
 * @note None.
 */
int jl_platform_sscanf(const char *str, const char *format, ...);

/** @defgroup group_platform_file_api_manage
 *  @{
 */

/**
 * @brief Opens the file whose name is specified in the parameter filename and associates it
 *  with a stream that can be identified in future operations by the void pointer returned.
 *
 * @param [in] path: @n The file path to open.With reference to fopen
 * @param [in] mode: @n C string containing a file access mode.
 * @return If the file is successfully opened, the function returns a pointer to void object that can be used to
 * identify the stream on future operations.Otherwise, a null pointer is returned.
 * @see None.
 * @note None.
 */
void *jl_platform_fopen(const char *path, const char *mode);

/**
 * @brief Reads an array of count elements, each one with a size of size bytes, from the stream and
 * stores them in the block of memory specified by ptr.
 *
 * @param [in] buff: @n Pointer to a block of memory with a size of at least (size*count) bytes, converted to a void*.
 * @param [in] size: @n size in bytes, of each element to be read.
 * @param [in] count: @n Number of elements, each one with a size of size bytes.
 * @param [in] stream: @n Pointer to void that specifies an input stream.
 * @return The total number of elements successfully read is returned.If either size or count is zero, the function returns zero
 * @see None.
 * @note None.
 */
uint32_t jl_platform_fread(void *buff, uint32_t size, uint32_t count, void *stream);

/**
 * @brief Writes an array of count elements, each one with a size of size bytes, from the block of memory pointed
 * by ptr to the current position in the stream.
 *
 * @param [in] ptr: @n Pointer to the array of elements to be written, converted to a const void*.
 * @param [in] size: @n Size in bytes of each element to be written.
 * @param [in] count: @n Number of elements, each one with a size of size bytes.
 * @param [in] stream: @n Pointer to void that specifies an output stream.
 * @return The total number of elements successfully written is returned.If either size or count is zero, the function returns zero.
 * @see None.
 * @note None.
 */
uint32_t jl_platform_fwrite(const void *ptr, uint32_t size, uint32_t count, void *stream);

/**
 * @brief Sets the position indicator associated with the stream to a new position.
 *
 * @param [in] stream: @n Pointer to void that identifies the stream.
 * @param [in] offset: @n Binary files: Number of bytes to offset from origin.
 * @param [in] origin: @n Position used as reference for the offset. It is specified by one of value enum in hal_fs_seek_type_t.
 *
 * @return If successful, the function returns zero.Otherwise, it returns non-zero value.
 * @see None.
 * @note None.
 */
int32_t jl_platform_fseek(void *stream, long offset, int32_t origin);

/**
 * @brief Closes the file associated with the stream and disassociates it.
 *
 * @param [in] stream: @n Pointer to void that identifies the stream.
 *
 * @return If the stream is successfully closed, a zero value is returned.On failure, non-zero is returned.
 * @see None.
 * @note None.
 */
int32_t jl_platform_fclose(void *stream);

/**
 * @brief Closes the file associated with the stream and disassociates it.
 *
 * @param [in] stream: @n Pointer to void that identifies the stream.
 *
 * @return If the stream is successfully flushed, a zero value is returned.On failure, non-zero is returned.
 * @see None.
 * @note None.
 */
int32_t jl_platform_fflush(void *stream);

/** @} */ /* end of platform_file_api_manage */

/** @defgroup group_platform_net_api_manage
 *  @{
 */

/**
 * brief: 
 *
 * @Param: msg
 * @Param: buff
 * @Param: len
 */
void jl_print_buffer(const char *msg, const uint8_t *buff, int len);

/*
* @brief get a random
* 
* @param none
* @return the random value
*/
int32_t jl_get_random(void);

#endif


