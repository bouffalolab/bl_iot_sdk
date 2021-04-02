/* --------------------------------------------------
 * @file: joylink_extern_tool.h
 *
 * @brief: 
 *
 * @version: 2.0
 *
 * @date: 2018/07/26 PM
 *
 * --------------------------------------------------
 */

#ifndef _JOYLINK_EXTERN_TOOL_H_
#define _JOYLINK_EXTERN_TOOL_H_

#ifdef __cplusplus
extern "C"{
#endif

#define MEMORY_WRITE  0
#define MEMORY_READ   1

int joylink_memory_init(void *index, int flag);

int joylink_memory_write(int offset, char *data, int len);
int joylink_memory_read(int offset, char *data, int len);

int joylink_memory_finish(void);

#ifdef __cplusplus
}
#endif

#endif
