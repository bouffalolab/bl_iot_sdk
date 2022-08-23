
#include <stdio.h>
#include <hosal_rng.h>
#include <bl_sec.h>

int hosal_rng_init(void)
{
    bl_sec_init();
    return 0;
}

int hosal_random_num_read(void *buf, uint32_t bytes)
{
    uint32_t tmp;
    uint32_t *val;
    int i, nwords;

	if(buf == NULL)
	{
		return -1;
	}
    
    val = (uint32_t *)buf;

    nwords = bytes / 4;

    for (i = 0; i < nwords; i++) {
        val[i] = bl_rand();
    }
    val += nwords;
    
    tmp = bl_rand();
    
    if (bytes % 4 == 1) {
        *((uint8_t *)val) = (uint8_t)tmp;
    }
    if (bytes % 4 == 2) {
        *((uint8_t *)val) = (uint8_t)tmp;
        *((uint8_t *)val + 1) = (uint8_t)(tmp >> 8);
    }
    if (bytes % 4 == 3) {
        *((uint8_t *)val) = (uint8_t)tmp;
        *((uint8_t *)val + 1) = (uint8_t)(tmp >> 16);
        *((uint8_t *)val + 2) = (uint8_t)(tmp >> 24);
    }
   
    return 0;
}


