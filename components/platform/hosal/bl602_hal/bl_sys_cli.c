#include <stdlib.h>
#include <stdio.h>
#include <cli.h>
#include <bl602_glb.h>
#include <blog.h>
#include <FreeRTOS.h>
#include <task.h>

typedef struct _para_div {
    int hdiv;
    int bdiv;
} para_div;

static void clk(void *para)
{
    para_div *p = (para_div *)para;
    int hdiv = p->hdiv;
    int bdiv = p->bdiv;
    blog_info("hdiv:%d, bdiv:%d\r\n", hdiv, bdiv);

    vTaskEnterCritical();
    __disable_irq();
    GLB_Set_System_CLK_Div(hdiv, bdiv);
    __enable_irq();
    vTaskExitCritical();
    vTaskDelete(NULL);
}

static void cmd_clk_change(char *buf, int len, int argc, char **argv)
{
    para_div clk_div;
    if (3 != argc) {
        blog_error("please input para!\r\n");
        return;
    } else {
        clk_div.hdiv = atoi(argv[1]);
        clk_div.bdiv = atoi(argv[2]);
        xTaskCreate(clk, (char*)"clk", 512, &clk_div, 20, NULL );
    }
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "clk", "change hdiv and bdiv", cmd_clk_change},
};

int bl_sys_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
