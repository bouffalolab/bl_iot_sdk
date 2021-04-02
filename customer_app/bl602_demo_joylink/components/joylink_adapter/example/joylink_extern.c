/* --------------------------------------------------
 * @brief: 
 *
 * @version: 1.0
 *
 * @date: 08/01/2018
 * 
 * @desc: Functions in this file must be implemented by the device developers when porting the Joylink SDK.
 *
 * --------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "joylink.h"
#include "joylink_extern.h"
#include "joylink_extern_json.h"

#include "joylink_memory.h"
#include "joylink_socket.h"
#include "joylink_string.h"
#include "joylink_stdio.h"
#include "joylink_stdint.h"
#include "joylink_log.h"
#include "joylink_time.h"
#include "joylink_thread.h"
#include "joylink_extern_ota.h"

#include <FreeRTOS.h>
#include <mbedtls/net_sockets.h>
#include <mbedtls/debug.h>
#include <mbedtls/ssl.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/error.h>
#include <mbedtls/certs.h>

#include <vfs.h>
#include <easyflash.h>

#ifdef JOYLINK_SDK_EXAMPLE_MWO
jl_device_status_t jl_device_status;
jl_app_uart_ctx_t *jl_uart_ctx;

void my_log_buf(const uint8_t *buf, const int len)
{
    const char *str = "";
    for (int i = 0; i < len; ++i) {
        printf("%02X ", buf[i]);
    }
    printf("\r\n");
    if (len == 36) {
        if (buf[6] == 1) {
            printf("CMD: GET_STATUS\r\n");
        } else if (buf[6] == 2) {
            printf("CMD: SET_STATUS\r\n");
        } else if (buf[6] == 3) {
            printf("CMD: ACK_STATUS\r\n");
        }
        if (buf[14] == 0) {
            str = "STAND BY";
        } else if (buf[14] == 1) {
            str = "START";
        } else if (buf[14] == 3) {
            str = "CANCEL";
        } else if (buf[14] == 2) {
            str = "PAUSE";
        } else if (buf[14] == 4) {
            str = "APPOINT";
        } else {
            str = "UNKNOWN";
        }
        printf("POWER: %s\r\n", str);
        printf("TIME_MIN: %u\r\n", buf[27]);
        printf("TIME_SEC: %u\r\n", buf[28]);
    }
}

/*
 * Patch UART CMD
 * Fill current time(hour and minute)
 * Patch not committed status
 * Calculate checksum
 * return 1 if need to commit(i.e. send command to MWO), otherwise 0
 */
int patch_uart_cmd(uint8_t *buf, const int len, int *is_start_cmd)
{
    jl_time_t time;
    jl_time_get_time(&time);
    int i;
    int patches;
    int offset, value;
    int commit = 0;

    //XXX: timezone issue
    buf[30] = (time.hour + 8) % 24;
    buf[31] = time.minute;
    buf[32] = 0; // 24h format

    if (len > 36 && (len % 2) == 0) {
        patches = (len - 36) / 2;
        printf("[PATCH_UART_CMD] patches cnt %d\r\n", patches);

        for (i = 0; i < patches; ++i) {
            offset = buf[36 + i] - 1;
            value = buf[36 + i + 1];
            if (offset < 36) {
                printf("[PATCH_UART_CMD] patches offset %u, value %u\r\n", offset, value);
                user_dev.patches[offset].value = value;
                user_dev.patches[offset].status = MWO_PATCH_STATUS_ENABLED;
            } else {
                printf("[PATCH_UART_CMD] offset %d >= 36\r\n", offset);
            }
        }
        if (user_dev.patches[14].status == MWO_PATCH_STATUS_ENABLED) {
            if (user_dev.patches[14].value == 1) {
                *is_start_cmd = 1;
            } else {
                *is_start_cmd = 0;
            }
            for (i = 0; i < MWO_PATCH_CAP; ++i) {
                if (user_dev.patches[i].status == MWO_PATCH_STATUS_ENABLED) {
                    buf[i] = user_dev.patches[i].value;
                }
                user_dev.patches[i].value = 0;
                user_dev.patches[i].status = MWO_PATCH_STATUS_DISABLED;
            }
            printf("[PATCH_UART_CMD] commit and clean patches\r\n");
            commit = 1;
        }
    }
    calc_uart_cksum(buf);

    return commit;
}

/*
 * Patch not committed status to acked_status
 */
int patch_ack_status(uint8_t *buf)
{
    int i;

    for (i = 0; i < MWO_PATCH_CAP; ++i) {
        if (user_dev.patches[i].status == MWO_PATCH_STATUS_ENABLED) {
            buf[i] = user_dev.patches[i].value;
        }
    }
    return 0;
}

int patch_start_cmd_to_standby(uint8_t *buf)
{
    buf[14] = 0;
    buf[15] = 0;

    calc_uart_cksum(buf);
    return 0;
}

/*
 * Calculate checksum according to document.
 */
void calc_uart_cksum(uint8_t *buf)
{
    int sum = 0xbeaf;
    int i;
    for (i = 0; i < 36; ++i) {
        if (i == 4 || i == 5) {
            continue;
        }
        sum += buf[i];
    }
    buf[4] = sum & 255;
    buf[5] = (sum >> 8) & 255;
}

#endif

jl2_d_idt_t user_idt = 
{
    .type = 0,
    .cloud_pub_key = IDT_CLOUD_PUB_KEY,

    .sig = "01234567890123456789012345678901",
    .pub_key = "01234567890123456789012345678901",

    .f_sig = "01234567890123456789012345678901",
    .f_pub_key = "01234567890123456789012345678901",
};

#ifdef JOYLINK_SDK_EXAMPLE_TEST
user_dev_status_t user_dev = 
{
    .Power = 1,
    .Mode = 0,
    .State = 0,
};
#else
user_dev_status_t user_dev;
#endif

/*E_JLDEV_TYPE_GW*/
#ifdef _SAVE_FILE_
char  *file = "joylink_info.txt";
#endif


/**
 * @brief: 用以返回一个整型随机数
 *
 * @param: 无
 *
 * @returns: 整型随机数
 */
int
joylink_dev_get_random()
{
#if 0 //CSRC
    /**
     *FIXME:must to do
     */
    static unsigned long int next = 1;
    next = next *1103515245 + 12345;
    return (int)(next/65536) % (1134);
#endif
extern int bl_rand();
    return bl_rand();
}

/**
 * @brief: 返回是否可以访问互联网
 *
 * @returns: E_JL_TRUE 可以访问, E_JL_FALSE 不可访问
 */
int jl_pal_is_net_ok = 0;
E_JLBOOL_t joylink_dev_is_net_ok()
{
    /* log_warn("NOT IMPLEMENTED\r\n"); */
    /**
     *FIXME:must to do
     */
    if (jl_pal_is_net_ok) {
        return E_JL_TRUE;
    } else {
        return E_JL_FALSE;
    }
}

/**
 * @brief: 此函数用作通知应用层设备与云端的连接状态.
 *
 * @param: st - 当前连接状态  0-Socket init, 1-Authentication, 2-Heartbeat
 *
 * @returns: 
 */
E_JLRetCode_t
joylink_dev_set_connect_st(int st)
{
    /* log_warn("NOT IMPLEMENTED\r\n"); */
    /**
    *FIXME:must to do
    */
    char buff[64] = {0};
    int ret = 0;

#ifdef JOYLINK_SDK_EXAMPLE_MWO
    if (st == 2) {
        jl_device_status = S_CLOUD_CTRL;
    }
#endif
    jl_platform_sprintf(buff, "{\"conn_status\":\"%d\"}", st);
    log_info("--set_connect_st:%s\n", buff);

    return ret;
}

/**
 * @brief: 传出激活信息
 *
 * @param[in] message: 激活信息
 * 
 * @returns: 0:设置成功
 */
E_JLRetCode_t joylink_dev_active_message(char *message)
{
    log_warn("NOT IMPLEMENTED\r\n");
    log_info("message = %s", message);
    ef_set_env(JL_EF_IS_ACTIVATED_KEY, "1");
    ef_save_env();
    return 0;
}

/**
 * @brief: 存储JLP(Joylink Parameters)信息,将入参jlp结构中的信息持久化存储,如文件、设备flash等方式
 *
 * @param [in]: jlp-JLP structure pointer
 *
 * @returns: 
 */
E_JLRetCode_t
joylink_dev_set_attr_jlp(JLPInfo_t *jlp)
{
#if 0 //CSRC
    if(NULL == jlp){
        return E_RET_ERROR;
    }
    /**
    *FIXME:must to do
    *Must save jlp info to flash or files
    */
    int ret = E_RET_ERROR;

#ifdef _SAVE_FILE_
    //Sample code for saving JLP info in a file.
    FILE *outfile;
    outfile = jl_platform_fopen(file, "wb+" );
    jl_platform_fwrite(jlp, sizeof(JLPInfo_t), 1, outfile );
    jl_platform_fclose(outfile);
#endif
#endif
    int ret;

    ret = E_RET_OK;
    if (ef_set_env_blob(JL_EF_JLP_KEY, jlp, sizeof *jlp) != EF_NO_ERR) {
        ret = E_RET_ERROR;
    }

    if (ret == E_RET_OK) {
        log_info("jlp saved");
    } else {
        log_error("jlp NOT saved");
    }

    return ret;
}

static int jl_port_get_one_product_info(char *name, char *out)
{
    int fd;
    int read;
    int i;
    char filename[32];
    char buf[128];
    int ret = 0;

    strcpy(filename, "/romfs/");
    strcat(filename, name);
    if ((fd = aos_open(filename, 0)) < 0) {
        ret = -1;
        goto error;
    }
    if ((read = aos_read(fd, buf, 127)) <= 0) {
        ret = -2;
        goto clean;
    }
    for (i = 0; i < read; i++) {
        if (buf[i] == '\r' || buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
    buf[i] = '\0';
    strcpy(out, buf);

clean:
    aos_close(fd);
error:
    return ret;
}

/**
 * @brief: 设置设备认证信息
 *
 * @param[out]: pidt--设备认证信息结构体指针,需填入必要信息sig,pub_key,f_sig,f_pub_key,cloud_pub_key
 *
 * @returns: 返回设置成功或失败
 */
E_JLRetCode_t
joylink_dev_get_idt(jl2_d_idt_t *pidt)
{
#if 0 //CSRC
    if(NULL == pidt){
        return E_RET_ERROR; 
    }
    pidt->type = 0;
    /**
    *FIXME:must to do
    */
    jl_platform_strcpy(pidt->sig, user_idt.sig);
    jl_platform_strcpy(pidt->pub_key, user_idt.pub_key);
    //jl_platform_strcpy(pidt->rand, user_idt.rand);
    jl_platform_strcpy(pidt->f_sig, user_idt.f_sig);
    jl_platform_strcpy(pidt->f_pub_key, user_idt.f_pub_key);
    jl_platform_strcpy(pidt->cloud_pub_key, user_idt.cloud_pub_key);

    return E_RET_OK;
#endif
    int ret = 0;
    if(NULL == pidt){
        return E_RET_ERROR; 
    }
    pidt->type = 0;
    
    ret += jl_port_get_one_product_info("sig", pidt->sig);
    ret += jl_port_get_one_product_info("pub_key", pidt->pub_key);
    ret += jl_port_get_one_product_info("f_sig", pidt->f_sig);
    ret += jl_port_get_one_product_info("f_pub_key", pidt->f_pub_key);
    ret += jl_port_get_one_product_info("cloud_pub_key", pidt->cloud_pub_key);
    if (ret < 0) {
        log_error("pidt cfg error\r\n");
        return E_RET_ERROR;
    }

    return E_RET_OK;
}

/**
 * @brief: 此函数需返回设备的MAC地址
 *
 * @param[out] out: 将设备MAC地址赋值给此参数
 * 
 * @returns: E_RET_OK 成功, E_RET_ERROR 失败
 */
E_JLRetCode_t
joylink_dev_get_user_mac(char *out)
{
    log_warn("NOT IMPLEMENTED\r\n");
    // TODO: Get MAC from other places
    if (jl_port_get_one_product_info("mac", out) != 0) {
        log_error("mac cfg error\r\n");
        return E_RET_ERROR;
    }
    return E_RET_OK;
}

/**
 * @brief: 此函数需返回设备私钥private key,该私钥可从小京鱼后台获取
 *
 * @param[out] out: 将私钥字符串赋值给该参数返回
 * 
 * @returns: E_RET_OK:成功, E_RET_ERROR:发生错误
 */
E_JLRetCode_t
joylink_dev_get_private_key(char *out)
{
    if (jl_port_get_one_product_info("private_key", out) != 0) {
        log_error("private_key cfg error\r\n");
        return E_RET_ERROR;
    }
    return E_RET_OK;
}

/**
 * @brief: 从永久存储介质(文件或flash)中读取jlp信息,并赋值给参数jlp,其中feedid, accesskey,localkey,joylink_server,server_port必须正确赋值
 *
 * @param[out] jlp: 将JLP(Joylink Parameters)读入内存,并赋值给该参数
 *
 * @returns: E_RET_OK:成功, E_RET_ERROR:发生错误
 */
E_JLRetCode_t
joylink_dev_get_jlp_info(JLPInfo_t *jlp)
{
#if 0 //CSRC
    if(NULL == jlp){
        return E_RET_ERROR;
    }
    /**
    *FIXME:must to do
    *Must get jlp info from flash 
    */
    int ret = E_RET_OK;

#ifdef _SAVE_FILE_
JLPInfo_t fjlp;
jl_platform_memset(&fjlp, 0, sizeof(JLPInfo_t));

FILE *infile;
infile = jl_platform_fopen(file, "rb+");
if(infile > 0)
{
    jl_platform_fread(&fjlp, sizeof(fjlp), 1, infile);
    jl_platform_fclose(infile);
}

    jl_platform_strcpy(jlp->feedid, fjlp.feedid);
    jl_platform_strcpy(jlp->accesskey, fjlp.accesskey);
    jl_platform_strcpy(jlp->localkey, fjlp.localkey);
    jl_platform_strcpy(jlp->joylink_server, fjlp.joylink_server);
    jlp->server_port = fjlp.server_port;

	jl_platform_strcpy(jlp->gURLStr, fjlp.gURLStr);
	jl_platform_strcpy(jlp->gTokenStr, fjlp.gTokenStr);

    if(joylink_dev_get_user_mac(jlp->mac) < 0){
        jl_platform_strcpy(jlp->mac, fjlp.mac);
    }

    if(joylink_dev_get_private_key(jlp->prikey) < 0){
        jl_platform_strcpy(jlp->prikey, fjlp.prikey);
    }
#endif
    joylink_dev_get_private_key(jlp->prikey);

    jlp->is_actived = E_JL_TRUE;
	jl_platform_strcpy(jlp->modelCode, JLP_CHIP_MODEL_CODE);
    jlp->model_code_flag = E_JL_FALSE;
    jlp->version = JLP_VERSION;
    jl_platform_strcpy(jlp->uuid, JLP_UUID);

    jlp->devtype = JLP_DEV_TYPE;
    jlp->lancon = JLP_LAN_CTRL;
    jlp->cmd_tran_type = JLP_CMD_TYPE;

    jlp->noSnapshot = JLP_SNAPSHOT;

    return ret;
#endif
    if(NULL == jlp){
        return E_RET_ERROR;
    }
    int ret = E_RET_OK;

    size_t ef_get_ret;
    size_t ef_get_read;

    ef_get_ret = ef_get_env_blob(JL_EF_JLP_KEY, jlp, sizeof *jlp, &ef_get_read);

    if (jl_port_get_one_product_info("mac", jlp->mac) != 0) {
        log_error("mac cfg error\r\n");
        return E_RET_ERROR;
    }
    if (jl_port_get_one_product_info("uuid", jlp->uuid) != 0) {
        log_error("uuid cfg error\r\n");
        return E_RET_ERROR;
    }
    if (jl_port_get_one_product_info("cid", jlp->CID) != 0) {
        log_error("cid cfg error\r\n");
        return E_RET_ERROR;
    }

    if (ef_get_ret == 0) {
        // EF does NOT have this info
        log_warn("Using default jlp info");
        joylink_dev_get_private_key(jlp->prikey);

        jlp->is_actived = E_JL_TRUE;

        jl_platform_strcpy(jlp->modelCode, JLP_CHIP_MODEL_CODE);
        jlp->model_code_flag = E_JL_FALSE;

        jlp->version = JLP_VERSION;

        jlp->devtype = JLP_DEV_TYPE;
        jlp->lancon = JLP_LAN_CTRL;
        jlp->cmd_tran_type = JLP_CMD_TYPE;

        jlp->noSnapshot = JLP_SNAPSHOT;
    } else if (ef_get_ret != sizeof *jlp) {
        log_error("ef_get_ret NEQ sizeof *jlp");
        ret = E_RET_ERROR;
    } else {
        jlp->version = JLP_VERSION;
        log_info("Using jlp from flash");
    }

    return ret;
}

/**
 * @brief: 返回设备状态,通过填充user_data参数,返回设备当前状态
 *
 * @param[out] user_data: 设备状态结构体指针
 * 
 * @returns: 0
 */
int
joylink_dev_user_data_get(user_dev_status_t *user_data)
{
    /**
    *FIXME:must to do
    */
#ifdef JOYLINK_SDK_EXAMPLE_TEST
int get_led_state();
    user_data->Power = get_led_state();
    user_data->Mode = 0;
    user_data->State = 0;
#endif
#ifdef JOYLINK_SDK_EXAMPLE_BUTTON
int get_power_ctr();
    user_data->Power = get_power_ctr();
#endif
    return 0;
}

/**
 * @brief: 获取设备快照json结构,结构中包含返回状态码
 *
 * @param[in] ret_code: 返回状态码
 * @param[out] out_snap: 序列化为字符串的设备快照json结构
 * @param[in] out_max: out_snap可写入的最大长度
 *
 * @returns: 实际写入out_snap的数据长度
 */
int
joylink_dev_get_snap_shot_with_retcode(int32_t ret_code, char *out_snap, int32_t out_max)
{
    if(NULL == out_snap || out_max < 0){
        return 0;
    }
    /**
    *FIXME:must to do
    */

    int len = 0;

    joylink_dev_user_data_get(&user_dev);

#if defined(JOYLINK_SDK_EXAMPLE_TEST) || defined(JOYLINK_SDK_EXAMPLE_BUTTON)
    char *packet_data =  joylink_dev_package_info(ret_code, &user_dev);
    if(NULL !=  packet_data){
        len = jl_platform_strlen(packet_data);
        log_info("------>%s:len:%d\n", packet_data, len);
        if(len < out_max){
            jl_platform_memcpy(out_snap, packet_data, len); 
        }else{
            len = 0;
        }
    }

    if(NULL !=  packet_data){
        jl_platform_free(packet_data);
    }
#endif
#ifdef JOYLINK_SDK_EXAMPLE_MWO
    len = 36;
    memcpy(out_snap, user_dev.acked_status, len);
#endif
    return len;
}

/**
 * @brief: 获取设备快照json结构
 *
 * @param[out] out_snap: 序列化为字符串的设备快照json结构
 * @param[in] out_max: out_snap可写入的最大长度
 *
 * @returns: 实际写入out_snap的数据长度
 */
int
joylink_dev_get_snap_shot(char *out_snap, int32_t out_max)
{
    return joylink_dev_get_snap_shot_with_retcode(0, out_snap, out_max); 
}

/**
 * @brief: 获取向App返回的设备快照json结构
 *
 * @param[out] out_snap: 序列化为字符串的设备快照json结构
 * @param[in] out_max: out_snap允许写入的最大长度
 * @param[in] code: 返回状态码
 * @param[in] feedid: 设备的feedid
 *
 * @returns: 
 */
int
joylink_dev_get_json_snap_shot(char *out_snap, int32_t out_max, int code, char *feedid)
{
    log_warn("NOT IMPLEMENTED\r\n");
    /**
     *FIXME:must to do
     */
    jl_platform_sprintf(out_snap, "{\"code\":%d, \"feedid\":\"%s\"}", code, feedid);

    return jl_platform_strlen(out_snap);
}

/**
 * @brief: 通过App控制设备,需要实现此函数,根据传入的json_cmd对设备进行控制
 *
 * @param[in] json_cmd: 设备控制命令
 *
 * @returns: E_RET_OK:控制成功, E_RET_ERROR:发生错误 
 */
E_JLRetCode_t 
joylink_dev_lan_json_ctrl(const char *json_cmd)
{
    log_warn("NOT IMPLEMENTED\r\n");
    /**
     *FIXME:must to do
     */
    log_debug("json ctrl:%s", json_cmd);

    return E_RET_OK;
}

/**
 * @brief: 根据传入的cmd值,设置对应设备属性
 *
 * @param[in] cmd: 设备属性名称
 * @param[out] user_data: 设备状态结构体
 * 
 * @returns: E_RET_OK 设置成功
 */
E_JLRetCode_t
joylink_dev_user_data_set(char *cmd, user_dev_status_t *user_data)
{
#ifdef JOYLINK_SDK_EXAMPLE_TEST
    printf("cmd %s, power %d, mode %d, state %d\r\n", cmd, user_data->Power, user_data->Mode, user_data->State);
void set_led_on();
void set_led_off();
    if (strcmp(cmd, "Power") == 0) {
        if (user_data->Power) {
            set_led_on();
        } else {
            set_led_off();
        }
    }
#endif
#ifdef JOYLINK_SDK_EXAMPLE_BUTTON
    printf("cmd %s, power %d\r\n", cmd, user_data->Power);
    if (strcmp(cmd, "Power") == 0) {
void set_power_ctr(int ctr);
        set_power_ctr(user_data->Power);
    }
#endif
    return E_RET_OK;
}

/**
 * @brief:根据src参数传入的控制命令数据包对设备进行控制.调用joylink_dev_parse_ctrl进行控制命令解析,并更改设备属性值
 *
 * @param[in] src: 控制指令数据包
 * @param[in] src_len: src长度
 * @param[in] ctr: 控制码
 * @param[in] from_server: 是否来自server控制 0-App,2-Server
 *
 * @returns: E_RET_OK 成功, E_RET_ERROR 失败
 */

E_JLRetCode_t 
joylink_dev_script_ctrl(const char *src, int src_len, JLContrl_t *ctr, int from_server)
{
    if(NULL == src || NULL == ctr){
        return E_RET_ERROR;
    }
    /**
    *FIXME:must to do
    */
    int ret = -1;
    ctr->biz_code = (int)(*((int *)(src + 4)));
    ctr->serial = (int)(*((int *)(src +8)));

    uint32_t tt = jl_get_time_second(NULL);
    log_info("bcode:%d:server:%d:time:%ld", ctr->biz_code, from_server,(long)tt);

    if(ctr->biz_code == JL_BZCODE_GET_SNAPSHOT){
        /*
        *Nothing to do!
        */
        ret = E_RET_OK;
    }else if(ctr->biz_code == JL_BZCODE_CTRL){
        joylink_dev_parse_ctrl(src + 12, &user_dev);
        return E_RET_OK;
	}else if(ctr->biz_code == JL_BZCODE_MENU){
		joylink_dev_parse_ctrl(src + 12, &user_dev);
		return E_RET_OK;
    }else{
        char buf[50];
        jl_platform_sprintf(buf, "Unknown biz_code:%d", ctr->biz_code);
        log_error("%s", buf);
    }
    return ret;
}

/**
 * @brief: 实现接收到ota命令和相关参数后的动作,可使用otaOrder提供的参数进行具体的OTA操作
 *
 * @param[in] otaOrder: OTA命令结构体
 *
 * @returns: E_RET_OK 成功, E_RET_ERROR 发生错误
 */
E_JLRetCode_t
joylink_dev_ota(JLOtaOrder_t *otaOrder)
{
    jl_thread_t task_id;

    if(NULL == otaOrder){
        return E_RET_ERROR;
    }
    joylink_set_ota_info(otaOrder);
    task_id.thread_task = (threadtask) joylink_ota_task;
    task_id.stackSize = 15*1024;
    task_id.priority = JL_THREAD_PRI_DEFAULT;
    task_id.parameter = (void *)otaOrder;
    jl_platform_thread_start(&task_id);

    return E_RET_OK;
}


/**
 * @brief: OTA执行状态上报,无需返回值
 */
void
joylink_dev_ota_status_upload()
{
    return; 
}

static int joylink_dev_http_parse_content(
    char *response, 
    int response_len, 
    char *content,
    int content_len)
{
    int length = 0;
    content[0] = 0;
    char* p = jl_platform_strstr(response, "\r\n\r\n");
    if (p == NULL) 
    {
        return -1;
    }
    p += 4;
    length = response_len - (p - response);
    length = length > content_len ? content_len - 1 : length;
    jl_platform_strncpy(content, p, length);
    content[length] = 0;
    // log_info("content = \r\n%s", content);
    
    return length;
}

static void my_debug(void *ctx, int level,
                     const char *file, int line,
                     const char *str)
{
    ((void)level);

    /* printf("%s:%04d: %s", file, line, str); */
}
/**
 * @name:实现HTTPS的POST请求,请求响应填入revbuf参数 
 *
 * @param[in]: host POST请求的目标地址
 * @param[in]: query POST请求的路径、HEADER和Payload
 * @param[out]: revbuf 填入请求的响应信息
 * @param[in]: buflen  revbuf最大长度
 *
 * @returns:   负数 - 发生错误, 非负数 - 实际填充revbuf的长度 
 *
 * @note:此函数必须正确实现,否则设备无法激活绑定
 * @note:小京鱼平台HTTPS使用的证书每年都会更新. 
 * @note:因为Joylink协议层面有双向认证的安全机制,所以此HTTPS请求设备无需校验server的证书. 
 * @note:如果设备必须校验server的证书,那么需要开发者实现时间同步等相关机制.
 */
int joylink_dev_https_post( char* host, char* query ,char *revbuf,int buflen)
{
#if 0 //CSRC
    printf("%s NOT IMPLEMENTED\r\n", __func__);
    int ret = -1;
    /**
         *FIXME:must to do
    */
    return ret;
#endif
#define RCV_BUF_SIZE 2048
    uint8_t *rcv_buf;
    int ret, rcv_ret;
    int r;
    mbedtls_net_context server_fd;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;

    if ((rcv_buf = jl_platform_malloc(RCV_BUF_SIZE)) == NULL) {
        r = -1;
        goto direct_ret;
    }

    mbedtls_net_init(&server_fd);
    mbedtls_ssl_init(&ssl);
    mbedtls_ssl_config_init(&conf);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_entropy_init(&entropy);

    if ((ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0)) != 0) {
        printf("[HTTPS] mbedtls_ctr_drbg_seed returned %d\r\n", ret);
        r = -1;
        goto clean;
    }

    if ((ret = mbedtls_net_connect(&server_fd, host, "443", MBEDTLS_NET_PROTO_TCP)) != 0) {
        printf("[HTTPS] mbedtls_net_connect returned %d\r\n", ret);
        r = -1;
        goto clean;
    }

    if ((ret = mbedtls_ssl_config_defaults(&conf,
                    MBEDTLS_SSL_IS_CLIENT,
                    MBEDTLS_SSL_TRANSPORT_STREAM,
                    MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
        printf("[HTTPS] mbedtls_ssl_config_defaults returned %d\r\n", ret);
        r = -1;
        goto clean;
    }

    mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_NONE);
    mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, &ctr_drbg);
    mbedtls_ssl_conf_dbg(&conf, my_debug, stdout);

    mbedtls_ssl_conf_read_timeout(&conf, 5 * 1000);

    if ((ret = mbedtls_ssl_setup(&ssl, &conf)) != 0)
    {
        printf("[HTTPS] mbedtls_ssl_setup returned %d\r\n", ret);
        r = -1;
        goto clean;
    }

    if ((ret = mbedtls_ssl_set_hostname(&ssl, host)) != 0)
    {
        printf("[HTTPS] mbedtls_ssl_set_hostname returned %d\r\n", ret);
        r = -1;
        goto clean;
    }

    mbedtls_ssl_set_bio(&ssl, &server_fd, mbedtls_net_send, mbedtls_net_recv, mbedtls_net_recv_timeout);

    while ((ret = mbedtls_ssl_handshake(&ssl)) != 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            printf("[HTTPS] mbedtls_ssl_handshake returned -0x%x\r\n", -ret);
            r = -1;
            goto clean;
        }
    }

    while ((ret = mbedtls_ssl_write(&ssl, (const uint8_t *)query, strlen(query))) <= 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            printf("[HTTPS] mbedtls_ssl_write returned %d\r\n", ret);
            r = -1;
            goto clean;
        }
    }

    if (ret != strlen(query)) {
        printf("[HTTPS] write req str failed\r\n");
        r = -1;
        goto clean;
    }

    printf("[HTTPS] >>>> %d bytes written, content:\r\n<<EOF\r\n%.*s\r\nEOF\r\n", ret, ret, query);

    while(1) {
        rcv_ret = mbedtls_ssl_read(&ssl, rcv_buf, RCV_BUF_SIZE);
        if (rcv_ret == MBEDTLS_ERR_SSL_WANT_READ || rcv_ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
            vTaskDelay(1);
        } else if (rcv_ret >= 0) {
            printf("[HTTPS] ssl read: received %d bytes\r\n", (int)rcv_ret);
            if (rcv_ret == 0) {
                r = -1;
                goto clean;
            }

            printf("[HTTPS] <<<< %d bytes read, content:\r\n<<EOF\r\n%.*s\r\nEOF\r\n", rcv_ret, rcv_ret, rcv_buf);
            r = joylink_dev_http_parse_content((char *)rcv_buf, rcv_ret, revbuf, buflen);
            goto clean;
        } else if (rcv_ret == MBEDTLS_ERR_SSL_TIMEOUT) {
            printf("[HTTPS] mbedtls_ssl_read timeout\r\n");
            r = -1;
            goto clean;
        } else if (rcv_ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
                r = -1;
                goto clean;
        } else {
            printf("[HTTPS] mbedtls_ssl_read Ret -%x, returning failed\r\n", -rcv_ret);
            r = -1;
            goto clean;
        }
    } // while(1)

clean:
    if (rcv_buf) {
        jl_platform_free(rcv_buf);
    }
    mbedtls_net_free(&server_fd);
    /* mbedtls_x509_crt_free(&tls->cacert); */
    mbedtls_ssl_free(&ssl);
    mbedtls_ssl_config_free(&conf);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);

direct_ret:
    return r;
}

/**
 * @brief 实现HTTP的POST请求,请求响应填入revbuf参数.
 * 
 * @param[in]  host: POST请求的目标主机
 * @param[in]  query: POST请求的路径、HEADER和Payload
 * @param[out] revbuf: 填入请求的响应信息的Body
 * @param[in]  buflen: revbuf的最大长度
 * 
 * @returns: 负值 - 发生错误, 非负 - 实际填充revbuf的长度
 * 
 * @note: 此函数必须正确实现,否者设备无法校时,无法正常激活绑定
 *
 * */
int joylink_dev_http_post( char* host, char* query, char *revbuf, int buflen)
{
#if 0 //CSRC
#ifdef __LINUX_PAL__
    int log_socket = -1;
    int len = 0;
    int ret = -1;
    char *recv_buf = NULL;
    jl_sockaddr_in saServer; 
    char ip[20] = {0};

    if(host == NULL || query == NULL || revbuf == NULL) {
        log_error("DNS lookup failed");
        goto RET;
    }

    jl_platform_memset(ip,0,sizeof(ip)); 
    ret = jl_platform_gethostbyname(host, ip, SOCKET_IP_ADDR_LEN);
    if(ret < 0){
        log_error("get ip error");
        ret = -1;
        goto RET;
    }
    
    jl_platform_memset(&saServer, 0, sizeof(saServer));
    saServer.sin_family = jl_platform_get_socket_proto_domain(JL_SOCK_PROTO_DOMAIN_AF_INET);
    saServer.sin_port = jl_platform_htons(80);
    saServer.sin_addr.s_addr = jl_platform_inet_addr(ip);

    log_socket = jl_platform_socket(JL_SOCK_PROTO_DOMAIN_AF_INET, JL_SOCK_PROTO_TYPE_SOCK_STREAM, JL_SOCK_PROTO_PROTO_IPPROTO_TCP);
    if(log_socket < 0) {
        log_error("... Failed to allocate socket.");
        goto RET;
    }
    int reuseaddrEnable = 1;
    if (jl_platform_setsockopt(log_socket, 
                JL_SOCK_OPT_LEVEL_SOL_SOCKET,
                JL_SOCK_OPT_NAME_SO_REUSEADDR, 
                (uint8_t *)&reuseaddrEnable, 
                sizeof(reuseaddrEnable)) < 0){
        log_error("set SO_REUSEADDR error");
    }
    
    /*fcntl(log_socket,F_SETFL,fcntl(log_socket,F_GETFL,0)|O_NONBLOCK);*/

    if(jl_platform_connect(log_socket, (jl_sockaddr *)&saServer, sizeof(saServer)) != 0)
    {
        log_error("... socket connect failed");
        goto RET;
    }

    if (jl_platform_send(log_socket, query, jl_platform_strlen(query), 0, 5000) < 0) {
        log_error("... socket send failed");
        goto RET;
    }

    struct timeval receiving_timeout;
    receiving_timeout.tv_sec = 5;
    receiving_timeout.tv_usec = 0;
    if (jl_platform_setsockopt(log_socket,
                   JL_SOCK_OPT_LEVEL_SOL_SOCKET,
                   JL_SOCK_OPT_NAME_SO_RCVTIMEO,
                   &receiving_timeout,
                   sizeof(receiving_timeout)) < 0) {
        log_error("... failed to set socket receiving timeout");
        goto RET;
    }

    int recv_buf_len = 1024; //2048;
    recv_buf = (char *)jl_platform_malloc(recv_buf_len);
    if(recv_buf == NULL)
    {
        goto RET;
    }
    jl_platform_memset(recv_buf, 0, recv_buf_len);
    len = jl_platform_recv(log_socket, recv_buf, recv_buf_len, 0, 0);
    if(len <= 0)
    {
        ret = -1;
        goto RET;
    }
    log_info("... read data length = %d, response data = \r\n%s", len, recv_buf);
    ret = joylink_dev_http_parse_content(recv_buf, len, revbuf, buflen);


RET:
    if(-1 != log_socket){
        jl_platform_close(log_socket);
    }
    if (recv_buf)
    {
        /* code */
        jl_platform_free(recv_buf);
    }
    
    return ret;
#else
    return -1;
#endif
#endif
    int log_socket = -1;
    int len = 0;
    int ret = -1;
    char *recv_buf = NULL;
    jl_sockaddr_in saServer; 
    char ip[20] = {0};

    if(host == NULL || query == NULL || revbuf == NULL) {
        log_error("DNS lookup failed");
        goto RET;
    }

    jl_platform_memset(ip,0,sizeof(ip)); 
    ret = jl_platform_gethostbyname(host, ip, SOCKET_IP_ADDR_LEN);
    if(ret < 0){
        log_error("get ip error");
        ret = -1;
        goto RET;
    }
    
    jl_platform_memset(&saServer, 0, sizeof(saServer));
    saServer.sin_family = jl_platform_get_socket_proto_domain(JL_SOCK_PROTO_DOMAIN_AF_INET);
    saServer.sin_port = jl_platform_htons(80);
    saServer.sin_addr.s_addr = jl_platform_inet_addr(ip);

    log_socket = jl_platform_socket(JL_SOCK_PROTO_DOMAIN_AF_INET, JL_SOCK_PROTO_TYPE_SOCK_STREAM, JL_SOCK_PROTO_PROTO_IPPROTO_TCP);
    if(log_socket < 0) {
        log_error("... Failed to allocate socket.");
        goto RET;
    }
    int reuseaddrEnable = 1;
    if (jl_platform_setsockopt(log_socket, 
                JL_SOCK_OPT_LEVEL_SOL_SOCKET,
                JL_SOCK_OPT_NAME_SO_REUSEADDR, 
                (uint8_t *)&reuseaddrEnable, 
                sizeof(reuseaddrEnable)) < 0){
        log_error("set SO_REUSEADDR error");
    }
    
    /*fcntl(log_socket,F_SETFL,fcntl(log_socket,F_GETFL,0)|O_NONBLOCK);*/

    if(jl_platform_connect(log_socket, (jl_sockaddr *)&saServer, sizeof(saServer)) != 0)
    {
        log_error("... socket connect failed");
        goto RET;
    }

    if (jl_platform_send(log_socket, query, jl_platform_strlen(query), 0, 5000) < 0) {
        log_error("... socket send failed");
        goto RET;
    }

    int recv_buf_len = 1024; //2048;
    recv_buf = (char *)jl_platform_malloc(recv_buf_len);
    if(recv_buf == NULL)
    {
        goto RET;
    }
    jl_platform_memset(recv_buf, 0, recv_buf_len);
    len = jl_platform_recv(log_socket, recv_buf, recv_buf_len, 0, 5000);
    if(len <= 0)
    {
        ret = -1;
        goto RET;
    }
    log_info("... read data length = %d, response data = \r\n%s", len, recv_buf);
    ret = joylink_dev_http_parse_content(recv_buf, len, revbuf, buflen);


RET:
    if(-1 != log_socket){
        jl_platform_close(log_socket);
    }
    if (recv_buf)
    {
        /* code */
        jl_platform_free(recv_buf);
    }
    
    return ret;
}

/**
 * @brief: SDK main loop 运行状态报告,正常情况下此函数每5秒会被调用一次,可以用来判断SDK主任务的运行状态.
 * 
 * @param[in] status: SDK main loop运行状态 0正常, -1异常
 * 
 * @return: reserved 当前此函数仅做通知,调用方不关心返回值.
 */

int joylink_dev_run_status(JLRunStatus_t status)
{
    /* printf("%s NOT IMPLEMENTED\r\n", __func__); */
    /**
         *FIXME:must to do
    */
    return 0;
}

/**
 * @brief: 每间隔1个main loop周期此函数将在SDK main loop中被调用,让用户有机会将代码逻辑运行在核心任务中.
 * 
 * @note:  正常情况下一个main loop周期为1s(取决于socket等待接收数据的timeout时间),但不保证精度,请勿用作定时器
 * @note:  仅用作关键的非阻塞任务执行,例如OTA状态上报或设备状态上报.
 * @note:  执行阻塞或耗时较多的代码,将会妨碍主task运行.
 */
void joylink_dev_run_user_code()
{
    //You may add some code run in the main loop if necessary.
}

