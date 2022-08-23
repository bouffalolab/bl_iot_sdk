#include <stdio.h>

void bugkiller_switch_task(unsigned int *sp)
{
    printf("set $sp=%p+120\r\n", (void *)sp);
    printf("set $pc=%p\r\n", (void *)*sp++);
    printf("set $ra=%p\r\n", (void *)*sp++);
    printf("set $t0=%p\r\n", (void *)*sp++);
    printf("set $t1=%p\r\n", (void *)*sp++);
    printf("set $t2=%p\r\n", (void *)*sp++);
    printf("set $s0=%p\r\n", (void *)*sp++);
    printf("set $s1=%p\r\n", (void *)*sp++);
    printf("set $a0=%p\r\n", (void *)*sp++);
    printf("set $a1=%p\r\n", (void *)*sp++);
    printf("set $a2=%p\r\n", (void *)*sp++);
    printf("set $a3=%p\r\n", (void *)*sp++);
    printf("set $a4=%p\r\n", (void *)*sp++);
    printf("set $a5=%p\r\n", (void *)*sp++);
    printf("set $a6=%p\r\n", (void *)*sp++);
    printf("set $a7=%p\r\n", (void *)*sp++);
    printf("set $s2=%p\r\n", (void *)*sp++);
    printf("set $s3=%p\r\n", (void *)*sp++);
    printf("set $s4=%p\r\n", (void *)*sp++);
    printf("set $s5=%p\r\n", (void *)*sp++);
    printf("set $s6=%p\r\n", (void *)*sp++);
    printf("set $s7=%p\r\n", (void *)*sp++);
    printf("set $s8=%p\r\n", (void *)*sp++);
    printf("set $s9=%p\r\n", (void *)*sp++);
    printf("set $s10=%p\r\n", (void *)*sp++);
    printf("set $s11=%p\r\n", (void *)*sp++);
    printf("set $t3=%p\r\n", (void *)*sp++);
    printf("set $t4=%p\r\n", (void *)*sp++);
    printf("set $t5=%p\r\n", (void *)*sp++);
    printf("set $t6=%p\r\n", (void *)*sp++);
    printf("printf \"mstatus\"\r\np/x %p\r\n", (void *)*sp);
}
