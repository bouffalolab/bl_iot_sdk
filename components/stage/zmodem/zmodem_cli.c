#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <cli.h>
#include <aos/kernel.h>
#include <zdef.h>

static size_t fill_data(zfile_t *zf, uint8_t *buf, size_t size, uint32_t tx_pos)
{
    size_t remain_size = zf->bytes_total - tx_pos;
    size_t cpy_size = remain_size > size ? size : remain_size;
    memcpy(buf, zf->data + tx_pos, cpy_size);
    return cpy_size;
}

static void cmd_sz(char *buf, int len, int argc, char **argv)
{
    zfile_t zf;
    if (argc == 4) {
        zf.fname = argv[1];
        printf("addr %p len 0x%x\r\n",(char *)strtol(argv[2], NULL, 0), (unsigned int)strtol(argv[3], NULL, 0));
        zf.data = (uint8_t *)strtol(argv[2], NULL, 0);
        zf.bytes_total = (uint32_t)strtol(argv[3], NULL, 0);
        zf.fill_cb = (void *)fill_data;
        vTaskDelay(50);
        zs_start(&zf);
    }
}

static void cmd_rz(char *buf, int len, int argc, char **argv)
{
    zfile_t zf;

    if (argc == 3) {
        memset(&zf, 0 , sizeof(zf));
        zf.fname = (char *)argv[1];
        zf.data = (uint8_t *)strtol(argv[2], NULL, 0);
        zf.bytes_total = 0;
        zf.bytes_received = 0;

        /* for pc enter ctrl+a ctrl+r */
        vTaskDelay(50);

        zr_start(&zf);
    }
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "sz", "zmodem sz", cmd_sz},
        { "rz", "zmodem rz", cmd_rz}
};

int zmodem_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
