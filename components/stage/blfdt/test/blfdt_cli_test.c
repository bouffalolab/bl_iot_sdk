#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <cli.h>

#include <utils_log.h>
#include <utils_fec.h>

void blfdt(char *buf, int len, int argc, char **argv)
{
    int tc_fdt_wifi(void);
    int tc_blfdtdump(void);

    tc_fdt_wifi();
    tc_blfdtdump();
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "blfdt", "blfdt", blfdt}
};

int blfdt_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
