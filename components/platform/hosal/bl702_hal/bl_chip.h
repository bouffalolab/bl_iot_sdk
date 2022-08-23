#ifndef __BL_CHIP_H__
#define __BL_CHIP_H__
int bl_chip_info(char *info);
int bl_chip_banner(const char **banner);
int bl_chip_memory_ram(int *num, unsigned int addr[], unsigned int size[], char desc[][6]);
#endif
