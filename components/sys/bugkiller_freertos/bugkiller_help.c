#include <stdio.h>

struct bugkiller_command {
    char *name;
    char *help;
    char *example;
};
struct bugkiller_command __attribute__((used, section(".static_bugkiller_command"))) bg_help[] = {
 {
             "task_dump",
	     "list all task",
	     "call bugkiller_task_dump ()",
 },
 {
             "uart_dump",
	     "dump uart info, (need remap uart coredump section to another address)",
	     "call bugkiller_uart_dump ()",
 },
 {
             "switch_task",
	     "switch regs to interrupted time point, specify $sp of interrupted task",
	     "call bugkiller_switch_task (pxCurrentTCB->pxTopOfStack)",
 },
 {
             "sem_dump",
	     "dump semaphore",
	     "call bugkiller_sem_dump (Queue_t *res)",
 },
 {
             "softtimer_dump",
	     "dump softtimer",
	     "call bugkiller_softtimer_dump (Timer_t *res)",
 },
 {
             "streambuffer_dump",
	     "dump streambuffer",
	     "call bugkiller_streambuffer_dump (StreamBufferHandle_t res)",
 },
 {
             "eventgroup_dump",
	     "dump eventgroup",
	     "call bugkiller_eventgroup_dump (EventGroup_t *res)",
 },
 {
             "heap_dump",
	     "dump heap",
	     "call bugkiller_heap_dump ()",
 },
 {
             "sockets_dump",
	     "dump sockets",
	     "call bugkiller_sockets_dump ()",
 },
 {
             "help",
	     "list all command usage",
	     "call bugkiller_help ()",
 },
};
void bugkiller_help(void)
{
    extern char __bugkiller_command_start, __bugkiller_command_end;
    struct bugkiller_command *start = &__bugkiller_command_start;
    struct bugkiller_command *end = &__bugkiller_command_end;
    while(start < end) {
	printf("name: %s\r\nhelp: %s\r\nexample: %s\r\n\r\n", start->name, start->help, start->example);
	start++;
    }
}
