#include <stdlib.h>
#include <stdio.h>
#include <cli.h>
#include <bl_wdt.h>

#include <blog.h>

static void cmd_wdt_init(char *buf, int len, int argc, char **argv) 
{
    int ms = 0;

    if (2 != argc) {
        blog_error("Usage: %s ms\r\n", argv[0]);
        return;
    }
    ms = atoi(argv[1]);
    blog_info("Init WDT with %dms\r\n", ms);
    if (ms <= 0) {
        return;
    }
    bl_wdt_init(ms);
}

static void cmd_wdt_feed(char *buf, int len, int argc, char **argv) 
{
    bl_wdt_feed();
}

static void cmd_wdt_disable(char *buf, int len, int argc, char **argv) 
{
    bl_wdt_disable();
}

static void cmd_timer_start(char *buf, int len, int argc, char **argv) 
{
int bl_timer_tick_enable(void);
    bl_timer_tick_enable();
}
// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"wdt-init", "wdt-init ms", cmd_wdt_init},
    {"wdt-feed", "wdt-feed", cmd_wdt_feed},
    {"wdt-disable", "wdt-disable", cmd_wdt_disable},
    {"timer-start", "timer-start", cmd_timer_start},
};                                                                                   

int bl_wdt_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
