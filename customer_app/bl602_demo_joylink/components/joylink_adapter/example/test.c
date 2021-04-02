#include "joylink_stdio.h"
#include "joylink_thread.h"
#include "joylink_extern.h"
#include "joylink.h"
#include "joylink_softap.h"

#include <softap/joylink_softap_start.h>

#include <hal_sys.h>
#include <bl_gpio.h>
#include <wifi_mgmr_ext.h>
#include <easyflash.h>

#ifdef JOYLINK_SDK_EXAMPLE_MWO
#include <uart_txrx.h>
#endif

#include <bl602_timer.h>
static void jl_wdt_init(int ms)
{
    WDT_Disable();
    WDT_Set_Clock(TIMER_CLKSRC_32K,3);
    WDT_SetCompValue(32 * ms / (3 + 1));
    WDT_ResetCounterValue();
    WDT_IntMask(WDT_INT, MASK);

    WDT_Enable();
}

static void jl_wdt_feed(void)
{
    WDT_ResetCounterValue();
}

static void jl_wdt_task(void *arg)
{
    jl_wdt_init(5000);
    while (1) {
        jl_wdt_feed();
        vTaskDelay(500);
    }
}

static void start_watchdog()
{
    jl_thread_t task_id; 

    task_id.thread_task = jl_wdt_task;
    task_id.stackSize = 512;
    task_id.priority = JL_THREAD_PRI_HIGHEST;
    task_id.parameter = NULL;
    jl_platform_thread_start(&task_id);
}

int 
joylink_main()
{
    jl_thread_t task_id; 

    task_id.thread_task = (threadtask) joylink_main_start;
    task_id.stackSize = 0x5000;
    task_id.priority = JL_THREAD_PRI_DEFAULT;
    task_id.parameter = NULL;
    jl_platform_thread_start(&task_id);

//   joylink_softap_start();

    jl_platform_msleep(2000);
    // 开启局域网激活模式
    joylink_dev_lan_active_switch(0);

#if 0
    while(1)
    {
        jl_platform_msleep(1000);
    }
#endif
    return 0;
}

static void jl_ap_net_config_mode_task(void *parm)
{
    joylink_softap_start(5 * 60 * 1000);
    joylink_main();
    jl_platform_thread_exit(NULL);
}

int jl_enter_ap_net_config_mode()
{
    jl_thread_t task_id; 

    task_id.thread_task = (threadtask) jl_ap_net_config_mode_task;
    task_id.stackSize = 0x5000;
    task_id.priority = JL_THREAD_PRI_DEFAULT;
    task_id.parameter = NULL;
    jl_platform_thread_start(&task_id);

    return 0;
}

#ifdef JOYLINK_SDK_EXAMPLE_MWO

#define RESET_CMD       "\xA5\xA5\x5A\x5A\x98\xC1\xE8\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define RESET_ACK_CMD   "\xA5\xA5\x5A\x5A\x99\xC1\xE9\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

#define GET_STATUS_CMD  "\xA5\xA5\x5A\x5A\xC6\xC0\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define FRAME_CMD_OFFSET (4 + 2)

static void uart_recv_cb(const uint8_t *data, const uint16_t data_len, void *cb_arg)
{
    jl_app_uart_ctx_t *ctx = cb_arg;
    log_info("[UART RECV cb] RECV %u bytes:\r\n", data_len);
    my_log_buf(data, data_len);

    if (memcmp(data, RESET_CMD, 8) == 0) {
        log_debug("To RESET module\r\n");
        jl_app_write_uart(ctx, (uint8_t *)RESET_ACK_CMD, 36);
        ef_env_set_default();
        hal_reboot();
    }
    if (data[FRAME_CMD_OFFSET] == 0x03 && data[FRAME_CMD_OFFSET + 1] == 0x00) {
        // ACK_STATUS
        log_debug("Update ACKED_STATUS\r\n");
        memcpy(user_dev.acked_status, data, 36);
        patch_ack_status(user_dev.acked_status);
    }
}

// Return 0 to accept UART RX data
// Otherwise drop it
static int uart_check_cb(const uint8_t *data, const uint16_t data_len, void *cb_ag)
{
    // GLS messed up the checksum, just ignore checking!
    return 0;
}

static int build_dev_status_uart_msg(jl_device_status_t st, uint8_t *out)
{
    int off = 0;

    if (!out) {
        return -1;
    }
    memcpy(out + off, "\xA5\xA5\x5A\x5A", 4);
    off += 4;
    if (st == S_CONFIGURING) {
        out[off] = 0xA0;
    } else if (st == S_CONNECTING_AP) {
        out[off] = 0xA1;
    } else if (st == S_LAN_CTRL) {
        out[off] = 0xA2;
    } else if (st == S_CLOUD_CTRL) {
        out[off] = 0xA3;
    } else {
        return -1;
    }
    off++;
    memcpy(out + off, "\xC1\xEC\x03\x04\x00\x00\x00", 7);
    off += 7;
    if (st == S_CONFIGURING) {
        out[off] = 0x00;
    } else if (st == S_CONNECTING_AP) {
        out[off] = 0x01;
    } else if (st == S_LAN_CTRL) {
        out[off] = 0x02;
    } else if (st == S_CLOUD_CTRL) {
        out[off] = 0x03;
    } else {
        return -1;
    }
    off++;
    while (off < 36) {
        out[off++] = 0;
    }
    return 0;
}

static void jl_uart_task(void *parm)
{
    int dev_status_sent_cnt[4] = { 0 };
    int idx = -1;
    uint8_t tx_buf[36];
    jl_uart_ctx = pvPortMalloc(sizeof(jl_app_uart_ctx_t));
    if (jl_uart_ctx) {
        if (jl_app_uart_init(jl_uart_ctx, "/dev/ttyS1", 9600, 36, 3, (uint8_t *)"\xA5\xA5\x5A\x5A", 4)) {
            printf("uart init error\r\n");
            goto end;
        }
        jl_app_uart_recv_cb_register(jl_uart_ctx, uart_recv_cb, jl_uart_ctx);
        jl_app_uart_msg_check_cb_register(jl_uart_ctx, uart_check_cb, jl_uart_ctx);
        jl_app_uart_start_txrx(jl_uart_ctx);
    } else {
        printf("uart ctx alloc error\r\n");
        goto end;
    }
loop:
    switch (jl_device_status) {
        case S_NONE:
            break;
        case S_CONFIGURING:
            idx = 0;
            break;
        case S_CONNECTING_AP:
            idx = 1;
            break;
        case S_LAN_CTRL:
            idx = 2;
            break;
        case S_CLOUD_CTRL:
            idx = 3;
            break;
        default:
            break;
    }
    if (idx != -1) {
#define DEVICE_STATUS_REPORT_CNT 2
        if (dev_status_sent_cnt[idx] < DEVICE_STATUS_REPORT_CNT) {
            dev_status_sent_cnt[idx]++;
            if (build_dev_status_uart_msg(jl_device_status, tx_buf) == 0) {
                log_debug("[UART TX] Send\r\n");
                my_log_buf(tx_buf, 36);
                jl_app_uart_send(jl_uart_ctx, tx_buf, 36, 0);
            }
        }
    }
    if (jl_device_status == S_CLOUD_CTRL && dev_status_sent_cnt[3] == DEVICE_STATUS_REPORT_CNT) {
        jl_app_uart_send(jl_uart_ctx, (uint8_t *)GET_STATUS_CMD, 36, 0);
        vTaskDelay(100); // delay to receive ACK_STATUS
        joylink_server_upload_req();
    }
    vTaskDelay(2000);
    goto loop;
end:
    vTaskDelete(NULL);
}

static int jl_start_uart_tasks()
{
    jl_thread_t task_id; 

    task_id.thread_task = (threadtask) jl_uart_task;
    task_id.stackSize = 4096;
    task_id.priority = JL_THREAD_PRI_DEFAULT;
    task_id.parameter = NULL;
    jl_platform_thread_start(&task_id);

    return 0;
}
#endif

static void wifi_sta_connect(char *ssid, char *password)
{
    log_info("Connecting to Router SSID %s, PWD %s", ssid, password);
    wifi_interface_t wifi_interface;

    wifi_interface = wifi_mgmr_sta_enable();
    wifi_mgmr_sta_connect(wifi_interface, ssid, password, NULL, NULL, 0, 0);
}

#ifdef JOYLINK_SDK_EXAMPLE_BUTTON
static int power_ctr = 0;
int get_power_ctr()
{
    return power_ctr;
}

void inc_snapshot_power()
{
    ++power_ctr;
    joylink_server_upload_req();
}

void set_power_ctr(int ctr)
{
    power_ctr = ctr;
}

#endif

#ifdef JOYLINK_SDK_EXAMPLE_TEST
#define DEMO_GPIO_PIN 17
static int led_state = 0;

static void init_led()
{
    bl_gpio_enable_output(DEMO_GPIO_PIN, 0, 0);
    bl_gpio_output_set(DEMO_GPIO_PIN, 0);
    led_state = 0;
}

int get_led_state()
{
    return led_state;
}

void set_led_on()
{
    log_debug("led on");
    bl_gpio_output_set(DEMO_GPIO_PIN, 1);
    led_state = 1;
}

void set_led_off()
{
    log_debug("led off");
    bl_gpio_output_set(DEMO_GPIO_PIN, 0);
    led_state = 0;
}
#endif

int start_joylink()
{
    wifi_interface_t wifi_interface;
    char *is_activated_env = NULL;
    char ssid[33] = { 0 }, passwd[65] = { 0 };
    char pmk[66] = { 0 };
    char *p = NULL;
    // (1) if device is activated, connect to router and start joylink_main_start
    // (2) else, start AP and start jl_ap_net_config_mode_task

    start_watchdog();
#ifdef JOYLINK_SDK_EXAMPLE_MWO
    jl_start_uart_tasks();
#endif
#ifdef JOYLINK_SDK_EXAMPLE_TEST
    init_led();
#endif
    is_activated_env = ef_get_env(JL_EF_IS_ACTIVATED_KEY);
    if (is_activated_env && is_activated_env[0] == '1') {
        p = ef_get_env(JL_EF_ROUTER_SSID_KEY);
        if (p) {
            strcpy(ssid, p);
            p = ef_get_env(JL_EF_ROUTER_PSWD_KEY);
            if (p) {
#ifdef JOYLINK_SDK_EXAMPLE_MWO
                jl_device_status = S_CONNECTING_AP;
#endif
                strcpy(passwd, p);
                p = ef_get_env(JL_EF_ROUTER_PMK_KEY);
                if (p) {
                    strcpy(pmk, p);
                    log_info("Connecting to Router SSID %s, PWD %s, PMK %s", ssid, passwd, pmk);
                    wifi_interface = wifi_mgmr_sta_enable();
                    wifi_mgmr_sta_connect(wifi_interface, ssid, passwd, pmk, NULL, 0, 0);
                    /* wifi_sta_connect(ssid, passwd); */
                    joylink_main();
                    return 0;
                }
                log_error("Router PMK null, this should not happen");
                return -1;
            }
            log_error("Router PASSWD null, this should not happen");
            return -1;
        }
        log_error("Router SSID null, this should not happen");
        return -1;
    } else {
#ifdef JOYLINK_SDK_EXAMPLE_MWO
        jl_device_status = S_CONFIGURING;
#endif
        jl_softap_enter_ap_mode();
        jl_enter_ap_net_config_mode();
    }

    return 0;
}
