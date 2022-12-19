#ifndef __BL_ROMFS_H__
#define __BL_ROMFS_H__

#include <stdint.h>

#define ALIGNUP16(x)           (((x)+15)&~15)

#define U32MK_HL(a,b,c,d)      (((uint32_t)((a) & 0xff) << 24) | \
                               ((uint32_t)((b) & 0xff) << 16) | \
                               ((uint32_t)((c) & 0xff) << 8)  | \
                                (uint32_t)((d) & 0xff))
#define U32HTONL(x) ((((x) & (uint32_t)0x000000ffUL) << 24) | \
                     (((x) & (uint32_t)0x0000ff00UL) <<  8) | \
                     (((x) & (uint32_t)0x00ff0000UL) >>  8) | \
                     (((x) & (uint32_t)0xff000000UL) >> 24))
#define U32NTOHL(x) U32HTONL(x)

int romfs_register(void);
void test1_romfs(void);
void test2_romfs(void);
void test3_romfs(void);

#endif
