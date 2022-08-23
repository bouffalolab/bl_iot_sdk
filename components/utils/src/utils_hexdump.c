#include <stdio.h>
#include <ctype.h>

#include <utils_hexdump.h>

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 16
#endif
//FIXME fix putchar
extern int bl_putchar(int c);
 
void utils_hexdump(void *mem, unsigned int len)
{
    unsigned int i, j;

    for (i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++) {
        /* print offset */
        if (i % HEXDUMP_COLS == 0) {
            printf("0x%06x: ", i);
        }

        /* print hex data */
        if (i < len) {
            printf("%02x ", 0xFF & ((char*)mem)[i]);
        } else {
            /* end of block, just aligning for ASCII dump */
            printf("   ");
        }

        /* print ASCII dump */
        if (i % HEXDUMP_COLS == (HEXDUMP_COLS - 1)) {
            for (j = i - (HEXDUMP_COLS - 1); j <= i; j++) {
                if (j >= len) {
                    /* end of block, not really printing */
                    bl_putchar(' ');
                } else if(isprint((int)((char*)mem)[j])) {
                    /* printable char */
                    bl_putchar(0xFF & ((char*)mem)[j]);
                } else {
                    /* other char */
                    bl_putchar('.');
                }
            }
            puts("\r\n");
        }
    }
}
 
