#include <stdio.h>

#include <cli.h>
#include <bloop.h>
#include <looprt.h>

static void looprt_case_1(void)
{
    printf("struct loop_ctx size is %d\r\n", sizeof(struct loop_ctx));
    printf("MSG size is %d\r\n", sizeof(struct loop_msg));
}

void cmd_looprt_test(char *buf, int len, int argc, char **argv)
{
    puts("====== looprt test ======\r\n");
    looprt_case_1();

    looprt_start_auto();
}

void cmd_looprt_test_status(char *buf, int len, int argc, char **argv)
{
    puts("====== looprt test status ======\r\n");
    looprt_evt_status_dump();
}

void cmd_looprt_test_evt(char *buf, int len, int argc, char **argv)
{
    puts("====== looprt EVT ======\r\n");
    looprt_evt_notify_async(LOOP_TASK_PRIORITY_HIGHEST, 0);
}

void cmd_looprt_test_evt_dump(char *buf, int len, int argc, char **argv)
{
    puts("====== looprt EVT status ======\r\n");
    looprt_evt_notify_async(LOOP_TASK_PRIORITY_HIGHEST, LOOP_TASK_SYS_EVT_DUMP);
}

void cmd_looprt_test_schedule_evt1(char *buf, int len, int argc, char **argv)
{
    puts("====== looprt Schedule EVT1 ======\r\n");
    looprt_evt_schedule(LOOP_TASK_PRIORITY_HIGHEST, LOOP_TASK_SYS_EVT_DUMP, 20000);
}

void cmd_looprt_test_schedule_evt2(char *buf, int len, int argc, char **argv)
{
    puts("====== looprt Schedule EVT2 ======\r\n");
    looprt_evt_schedule(LOOP_TASK_PRIORITY_HIGHEST, LOOP_TASK_SYS_EVT_DUMP, 10000);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "looprt", "looprt based on bloop", cmd_looprt_test},
    { "looprt_status", "looprt based on bloop", cmd_looprt_test_status},
    { "looprt_evt", "looprt notify event", cmd_looprt_test_evt},
    { "looprt_evt_status", "looprt evt to dump", cmd_looprt_test_evt_dump},
    { "looprt_schedule1", "looprt schedule evt 20s", cmd_looprt_test_schedule_evt1},
    { "looprt_schedule2", "looprt schedule evt 10s", cmd_looprt_test_schedule_evt2},
};

int looprt_test_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
