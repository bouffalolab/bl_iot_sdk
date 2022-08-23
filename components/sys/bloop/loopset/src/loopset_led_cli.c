#include <stdio.h>
#include <stdlib.h>
#include <cli.h>

#include <loopset.h>

void cmd_loopset_led_trigger(char *buf, int len, int argc, char **argv)
{
    int pin = -1, active = -1, type = -1;
    if (4 != argc) {
        printf("Usage: %s pin 0/1[0:Lo Active, 1:Hi Active] 0/1[0:Hearbeat, 1:Blink]\r\n",
            argv[0]
        );
        return;
    }
    pin = atoi(argv[1]);
    active = atoi(argv[2]);
    type = atoi(argv[3]);
    if (pin <= 0 || active < 0 || type < 0) {
        puts("Illegal Params\r\n");
        return;
    }
    loopset_led_trigger(pin, 100);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "loopset-led-trigger", "Trigger LED on PIN", cmd_loopset_led_trigger},
};

int loopset_led_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
