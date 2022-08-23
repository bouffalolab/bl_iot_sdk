
#ifndef __UTILS_FEC_H__
#define __UTILS_FEC_H__

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FEC_MSG_LENGTH	128
#define FEC_ECC_LENGTH	126

#define bl_assert(expr)

typedef struct
{
	int dummy[1120];
} fec_t;

int  reedsolomon_getmemsize(void);
void reedsolomon_init(void *context);
void reedsolomon_encode(void *context, void* src, void* dst);
char reedsolomon_decode(void *context, void* src, void* dst);

#ifdef __cplusplus
}
#endif

#endif

