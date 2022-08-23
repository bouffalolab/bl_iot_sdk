#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <cli.h>
#include <lwip/tcpip.h>
#include <lwip/stats.h>
#include <netutils/netutils.h>

#if LWIP_STATS

static void cmd_netstat(char *buf, int len, int argc, char **argv) 
{
  tcpip_callback(stats_netstat, NULL);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"netstat", "show current net states", cmd_netstat},
};                                                                                   

#endif

int network_netutils_netstat_cli_register()
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
