#include <cli.h>
#include <stdint.h>

#include <jl_tc.h>

#include <joylink_extern.h>

static void cmd_jl_tc_memory(char *buf, int len, int argc, char **argv) 
{
    jl_tc_memory();
}

static void cmd_jl_tc_stdio(char *buf, int len, int argc, char **argv) 
{
    jl_tc_stdio();
}

static void cmd_jl_tc_socket(char *buf, int len, int argc, char **argv) 
{
    jl_tc_socket();
}

static void cmd_jl_tc_extern(char *buf, int len, int argc, char **argv) 
{
    jl_tc_extern();
}

static void cmd_jl_tc_time(char *buf, int len, int argc, char **argv) 
{
    jl_tc_time();
}

static void print_byte_array(const uint8_t *array, int len)
{
    for (int i = 0; i < len; ++i) {
        printf("%02X", array[i]);
    }
}

static void cmd_jl_dump_jlp(char *buf, int len, int argc, char **argv)
{
    JLPInfo_t jlp;
    printf("Begining of jlp info dump\r\n");
    if (joylink_dev_get_jlp_info(&jlp) == E_RET_OK) {
        printf(".isUsed            = %d\r\n", jlp.isUsed);
        printf(".version           = %hd\r\n", jlp.version);
        printf(".ip                = %s\r\n", jlp.ip);
        printf(".port              = %d\r\n", jlp.port);
        printf(".mac               = %s\r\n", jlp.mac);
        printf(".uuid              = %s\r\n", jlp.uuid);
        printf(".lancon            = %d\r\n", jlp.lancon);
        printf(".cmd_tran_type     = %d\r\n", jlp.cmd_tran_type);
        printf(".devtype           = %d\r\n", jlp.devtype);
        printf(".protocol          = %d\r\n", jlp.protocol);
        printf(".feedid            = %s\r\n", jlp.feedid);
        printf(".accesskey         = %s\r\n", jlp.accesskey);
        printf(".localkey          = %s\r\n", jlp.localkey);
        printf(".prikey            = %s\r\n", jlp.prikey);
        printf(".noSnapshot        = %d\r\n", jlp.noSnapshot);
        printf(".pubkeyC           = "); print_byte_array(jlp.pubkeyC, JL_MAX_KEY_BIN_LEN); printf("(HEX)\r\n");
        printf(".pubkeyS           = %s\r\n", jlp.pubkeyS);
        printf(".sessionKey        = "); print_byte_array(jlp.sessionKey, 33); printf("(HEX)\r\n");
        printf(".joylink_server    = %s\r\n", jlp.joylink_server);
        printf(".joylink_server_ip = %s\r\n", jlp.joylink_server_ip);
        printf(".server_port       = %d\r\n", jlp.server_port);
        printf(".CID               = %s\r\n", jlp.CID);
        printf(".firmwareVersion   = %s\r\n", jlp.firmwareVersion);
        printf(".modelCode         = %s\r\n", jlp.modelCode);
        printf(".is_actived        = %d\r\n", jlp.is_actived);
        printf(".batchBind         = %d\r\n", jlp.batchBind);
        printf(".model_code_flag   = %d\r\n", jlp.model_code_flag);
        printf(".crc32             = %08X\r\n", jlp.crc32);
    } else {
        printf("get jlp info failed\r\n");
    }
    printf("End of jlp info dump\n");
}

static void cmd_jl_dump_time(char *buf, int len, int argc, char **argv)
{
    jl_time_t time;
    jl_get_time(&time);

    printf("jl year %lu, month %d, week %d, day %d, hour %d, minute %d, second %d, timestamp %lu\r\n",
            time.year,
            time.month,
            time.week,
            time.day,
            time.hour,
            time.minute,
            time.second,
            time.timestamp);
}

const static struct cli_command jl_debug_cmds[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"jltc_memory", "test jl_tc_memory", cmd_jl_tc_memory},
    {"jltc_stdio", "test jl_tc_stdio", cmd_jl_tc_stdio},
    {"jltc_socket", "test jl_tc_socket", cmd_jl_tc_socket},
    {"jltc_extern", "test jl_tc_extern", cmd_jl_tc_extern},
    {"jltc_time", "test jl_tc_time", cmd_jl_tc_time},
    {"jl_dump_jlp", "dump jlp info", cmd_jl_dump_jlp},
    {"jl_dump_time", "dump current time", cmd_jl_dump_time},
};

void register_jl_tc_cmds()
{
    // calling me is required to keep the commands
}
