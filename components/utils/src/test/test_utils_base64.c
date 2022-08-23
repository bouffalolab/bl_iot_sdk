#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <FreeRTOS.h>
#include <cli.h>
#include "utils_base64.h"
#include <utils_log.h>

#ifdef UTILS_BASE64_TEST

static void cmd_encode(char *buf, int len, int argc, char **argv)
{
    uint32_t input_len, output_len = 0;
    char *inbuf, *outbuf = NULL;

    if (argc != 3)
    {
        log_error("Usage:\r\n");
        log_error("encode_base64 0x420c0000 512\r\n");
        return;
    }

    inbuf = (char *)strtol(argv[1], NULL, 0);
    input_len = strtol(argv[2], NULL, 0);
    if (inbuf != NULL && input_len != 0)
    {
        output_len = 4 * ((input_len + 2) / 3);
        outbuf = calloc(1, output_len);

        if (outbuf)
        {
            if (SUCCESS_RETURN == utils_base64encode((uint8_t *)inbuf, input_len, output_len, (uint8_t *)outbuf, &output_len))
            {
                uint32_t i = 0;
                char *addr = outbuf;
                for (i = 0; i < output_len; i++)
                {
                    aos_cli_printf("%c", *(char *)addr);
                    addr += 1;
                }
            }
            else
            {
                log_error("base64 encode error\r\n");
            }

            free(outbuf);
        }
        else
        {
            log_error("base64 encode mem not enough %d\r\n", output_len);
        }
    }
    else
    {
        log_error("base64 encode argc error\r\n");
    }

}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "encode_base64", "base64 encode", cmd_encode},
};

int base64_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

#endif