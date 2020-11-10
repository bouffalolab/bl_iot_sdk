/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
* iperf-liked network performance tool
*
*/

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <lwip/sockets.h>
#include <lwip/udp.h>
#include <aos/kernel.h>

#include <cli.h>
#include <netutils/netutils.h>
#include <bl_timer.h>

#define IPERF_PORT_LOCAL    5002
#define IPERF_PORT          5001
#define IPERF_BUFSZ         (4 * 1300)
#define IPERF_BUFSZ_UDP     (1 * 1300)
#define DEBUG_HEADER        "[NET] [IPC] "
#define DEFAULT_HOST_IP     "192.168.11.1"

typedef struct UDP_datagram {
    uint32_t id;
    uint32_t tv_sec;
    uint32_t tv_usec;
} UDP_datagram;

/*
 * The server_hdr structure facilitates the server
 * report of jitter and loss on the client side.
 * It piggy_backs on the existing clear to close
 * packet.
 */
typedef struct server_hdr_v1 {
    /*
     * flags is a bitmap for different options
     * the most significant bits are for determining
     * which information is available. So 1.7 uses
     * 0x80000000 and the next time information is added
     * the 1.7 bit will be set and 0x40000000 will be
     * set signifying additional information. If no
     * information bits are set then the header is ignored.
     */
    int32_t flags;
    int32_t total_len1;
    int32_t total_len2;
    int32_t stop_sec;
    int32_t stop_usec;
    int32_t error_cnt;
    int32_t outorder_cnt;
    int32_t datagrams;
    int32_t jitter1;
    int32_t jitter2;
} server_hdr;

static void iperf_client_tcp(void *arg)
{
    int i;
    int sock;
    int ret;

    uint8_t *send_buf;
    int sentlen;
    uint32_t tick0, tick1, tick2;
    struct sockaddr_in addr;
    char *host = (char*) arg;
    uint64_t bytes_transfered = 0;

    char speed[32] = { 0 };
    float f_min = 8000.0, f_max = 0.0;

    send_buf = (uint8_t *) pvPortMalloc (IPERF_BUFSZ);
    if (!send_buf) {
        vPortFree(arg);
        return;
    }

    for (i = 0; i < IPERF_BUFSZ; i ++) {
        send_buf[i] = i & 0xff;
    }

    while (1) {
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock < 0)
        {
            printf("create socket failed!\r\n");
            vTaskDelay(1000);
            continue;
        }

        addr.sin_family = PF_INET;
        addr.sin_port = htons(IPERF_PORT);
        addr.sin_addr.s_addr = inet_addr(host);

        ret = connect(sock, (const struct sockaddr*)&addr, sizeof(addr));
        if (ret == -1)
        {
            printf("Connect failed!\r\n");
            closesocket(sock);

            vTaskDelay(1000);
            continue;
        }

        printf("Connect to iperf server successful!\r\n");

        {
            int flag = 1;

            setsockopt(sock,
                IPPROTO_TCP,     /* set option at TCP level */
                TCP_NODELAY,     /* name of option */
                (void *) &flag,  /* the cast is historical cruft */
                sizeof(int));    /* length of option value */
        }

        sentlen = 0;

        tick0 = xTaskGetTickCount();
        tick1 = tick0;
        while(1) {
            tick2 = xTaskGetTickCount();
            if (tick2 - tick1 >= 1000 * 5)
            {
                float f_now, f_avg;

                f_now = (float)(sentlen)  / 125 / (((int32_t)tick2 - (int32_t)tick1)) * 1000;
                f_now /= 1000.0f;
                bytes_transfered += sentlen;
                f_avg = (float)(bytes_transfered)  / 125 / (((int32_t)tick2 - (int32_t)tick0)) * 1000;
                f_avg /= 1000.0f;

                if (f_now < f_min) {
                    f_min = f_now;
                }
                if (f_max < f_now) {
                    f_max = f_now;
                }
                snprintf(speed, sizeof(speed), "%.4f(%.4f %.4f %.4f) Mbps!\r\n",
                        f_now,
                        f_min,
                        f_avg,
                        f_max
                );
                printf("%s", speed);
                tick1 = tick2;
                sentlen = 0;
            }

            ret = send(sock, send_buf, IPERF_BUFSZ, 0);
            if (ret > 0)
            {
                sentlen += ret;
            }

            if (ret < 0) break;
        }

        closesocket(sock);

        vTaskDelay(1000*2);
        printf("disconnected!\r\n");
    }
    printf("iper stop\r\n");
    vPortFree(send_buf);
}

static void iperf_client_tcp_entry(const char *name)
{
    int host_len;
    char *host;

    host_len = strlen(name) + 4;
    host = pvPortMalloc(host_len);//mem will be free in tcpc_entry
    strcpy(host, name);
    aos_task_new("ipc", iperf_client_tcp, host, 4096);
}

static void iperf_client_udp(void *arg)
{
    int i;
    int sock;
    int ret;

    uint8_t *send_buf;
    int sentlen;
    uint64_t bytes_transfered = 0;
    uint32_t tick0, tick1, tick2;
    struct sockaddr_in laddr, raddr;
    UDP_datagram udp_header, *udp_header_buf;
    char *host = (char*) arg;

    char speed[64] = { 0 };
    float f_min = 8000.0, f_max = 0.0;

    send_buf = (uint8_t *) pvPortMalloc (IPERF_BUFSZ_UDP);
    if (!send_buf) {
        vPortFree(arg);
        return;
    }

    for (i = 0; i < IPERF_BUFSZ_UDP; i ++) {
        send_buf[i] = i & 0xff;
    }

        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock < 0)
        {
            printf("create socket failed!\r\n");
            vTaskDelay(1000);
            vPortFree(arg);
            return;
        }

        memset(&laddr, 0, sizeof(struct sockaddr_in));
        laddr.sin_family = PF_INET;
        laddr.sin_port = htons(IPERF_PORT_LOCAL);
        laddr.sin_addr.s_addr = inet_addr("0.0.0.0");

        ret = bind(sock, (struct sockaddr*)&laddr, sizeof(laddr));
        if (ret == -1)
        {
            printf("Bind failed!\r\n");
            lwip_close(sock);

            vTaskDelay(1000);
            vPortFree(arg);
            return;
        }

        printf("bind UDP socket successfully!\r\n");

        memset(&raddr, 0, sizeof(struct sockaddr_in));
        raddr.sin_family = PF_INET;
        raddr.sin_port = htons(IPERF_PORT);
        raddr.sin_addr.s_addr = inet_addr(host);

        sentlen = 0;

        udp_header_buf = (UDP_datagram*)send_buf;
        udp_header.id = 0;
        udp_header.tv_sec = 0;
        udp_header.tv_usec = 0;
        tick0 = xTaskGetTickCount();
        tick1 = tick0;
        while (1) {
            tick2 = xTaskGetTickCount();
            if (tick2 - tick1 >= 1000 * 5)
            {
                float f_now, f_avg;

                f_now = (float)(sentlen)  / 125 / (((int32_t)tick2 - (int32_t)tick1)) * 1000;
                f_now /= 1000.0f;
                bytes_transfered += sentlen;
                f_avg = (float)(bytes_transfered)  / 125 / (((int32_t)tick2 - (int32_t)tick0)) * 1000;
                f_avg /= 1000.0f;

                if (f_now < f_min) {
                    f_min = f_now;
                }
                if (f_max < f_now) {
                    f_max = f_now;
                }
                snprintf(speed, sizeof(speed), "%.4f(%.4f %.4f %.4f) Mbps!\r\n",
                        f_now,
                        f_min,
                        f_avg,
                        f_max
                );
                printf("%s", speed);
                tick1 = tick2;
                sentlen = 0;
            }

            udp_header.id++;
            udp_header_buf->id = htonl(udp_header.id);
            udp_header_buf->tv_sec = 0;
            udp_header_buf->tv_usec = 0;
retry:
            ret = sendto(sock, send_buf, IPERF_BUFSZ_UDP, 0, (const struct sockaddr*)&raddr, sizeof(raddr));
            if (ret > 0) {
                sentlen += ret;
            }

            if (ret < 0) {
                if (ERR_MEM == ret) {
                    goto retry;
                }
                break;
            }
        }

        lwip_close(sock);

        vTaskDelay(1000*2);
        printf("disconnected! ret %d\r\n",  ret);
        vTaskDelete(NULL);
}

struct iperf_server_udp_ctx {
    //SemaphoreHandle_t comp_sig_handle;
    volatile int exit_flag;
    uint32_t datagram_cnt;
    int32_t packet_id;
    uint32_t out_of_order_cnt, error_cnt, out_of_order_curr;
    uint32_t receive_start, period_start, current;
    uint64_t recv_total_len, recv_now;
    float f_min, f_max;
};

// 网络字节序转本地字节序，直接从内存读取
#define NTOHL_PTR(ptr)                     \
  ({                                       \
    uint32_t _tmp = 0;                     \
    _tmp |= *((uint8_t *)(ptr) + 0) << 24; \
    _tmp |= *((uint8_t *)(ptr) + 1) << 16; \
    _tmp |= *((uint8_t *)(ptr) + 2) << 8;  \
    _tmp |= *((uint8_t *)(ptr) + 3) << 0;  \
  })

// 本地字节序转网络字节序，直接写入内存
#define HTONL_PTR(ptr, data)                       \
  {                                                \
    uint32_t _tmp = (uint32_t)(data);              \
    *((uint8_t *)(ptr) + 0) = (_tmp >> 24) & 0xff; \
    *((uint8_t *)(ptr) + 1) = (_tmp >> 16) & 0xff; \
    *((uint8_t *)(ptr) + 2) = (_tmp >> 8) & 0xff;  \
    *((uint8_t *)(ptr) + 3) = (_tmp >> 0) & 0xff;  \
  }

static void iperf_server_udp_recv_fn(void *arg, struct udp_pcb *pcb, struct pbuf *p,
    const ip_addr_t *addr, u16_t port)
{
    struct iperf_server_udp_ctx *ctx = (struct iperf_server_udp_ctx *)arg;
    char speed[32] = { 0 };
    UDP_datagram udp_header;

    // 接收数据，等待接收时间
    if (p == NULL)
        return;

    ctx->current = bl_timer_now_us();
    ctx->receive_start = ctx->receive_start ? : ctx->current;
    ctx->period_start = ctx->period_start ? : ctx->current;

    // 记录当前接收的总字节数：payload+Ethernet Link+IP header + UDP header
    ctx->recv_now += p->tot_len + PBUF_LINK_HLEN + PBUF_IP_HLEN + PBUF_TRANSPORT_HLEN;

    ctx->datagram_cnt ++;

    // 获得packet id
    udp_header.id = NTOHL_PTR(p->payload);
    if ((signed)udp_header.id < 0) {    // 发送完成，client端等待应答
        server_hdr *hdr = (server_hdr *)((UDP_datagram *)p->payload + 1);   // server hdr 跟在UDP_datagram后面
        HTONL_PTR(&hdr->flags, 0x80000000u);
        HTONL_PTR(&hdr->total_len1, 0);
        HTONL_PTR(&hdr->total_len2, ctx->recv_total_len);   // 低32位
        HTONL_PTR(&hdr->stop_sec, 0);
        HTONL_PTR(&hdr->stop_usec, 0);
        HTONL_PTR(&hdr->error_cnt, ctx->error_cnt);
        HTONL_PTR(&hdr->outorder_cnt, ctx->out_of_order_cnt);
        HTONL_PTR(&hdr->datagrams, ctx->datagram_cnt);

        printf("iperf finish...\r\nreceive:%ld,out of order:%ld\r\n",
            ctx->datagram_cnt, ctx->out_of_order_cnt);
        udp_sendto(pcb, p, addr, port);

        //xSemaphoreGive(ctx->comp_sig_handle);
        ctx->exit_flag = 1;
    } else if (ctx->current - ctx->period_start >= 500*1000) {  // 500ms
        float f_now, f_avg;

        // f_now = (float)(ctx->recv_now)  / 125 / (((int32_t)ctx->current - (int32_t)ctx->period_start)) * 1000;
        // f_now /= 1000.0f;
        f_now = (float)(ctx->recv_now) * 1000000 / ((int32_t)ctx->current - (int32_t)ctx->period_start) / 131072;

        ctx->recv_total_len += ctx->recv_now;
        // f_avg = (float)(ctx->recv_total_len)  / 125 / (((int32_t)ctx->current - (int32_t)ctx->receive_start)) * 1000;
        // f_avg /= 1000.0f;
        f_avg = (float)(ctx->recv_total_len) * 1000000 / ((int32_t)ctx->current - (int32_t)ctx->receive_start) / 131072;

        if (f_now < ctx->f_min) {
            ctx->f_min = f_now;
        }
        if (ctx->f_max < f_now) {
            ctx->f_max = f_now;
        }
        snprintf(speed, sizeof(speed), "%.4f(%.4f %.4f %.4f) Mbps, out of order: %lu.\r\n",
                f_now,
                ctx->f_min,
                f_avg,
                ctx->f_max,
                ctx->out_of_order_curr
        );
        printf("%s", speed);

        ctx->period_start = ctx->current;
        ctx->recv_now = 0;

        ctx->out_of_order_cnt += ctx->out_of_order_curr;
        ctx->out_of_order_curr = 0;
    }

    // 乱序和错误个数
    if ((signed)udp_header.id != ctx->packet_id + 1) {
      if ((signed)udp_header.id < ctx->packet_id + 1) {
        ctx->out_of_order_curr++;
      } else {
        ctx->error_cnt += (signed)udp_header.id  - ctx->packet_id - 1;
      }
    }

    if ((signed)udp_header.id > ctx->packet_id) {
      ctx->packet_id = (int32_t)udp_header.id;
    }

    pbuf_free(p);
}

static void iperf_server_udp(void *arg)
{
    char *host = (char*) arg;
    struct udp_pcb *server;
    err_t ret;
    ip_addr_t source_ip;
    //StaticSemaphore_t comp_signal;
    struct iperf_server_udp_ctx context;

    configASSERT(arg != NULL);

    //context.comp_sig_handle = xSemaphoreCreateBinaryStatic(&comp_signal);

    // 创建pcb控制块
    server = udp_new();
    if (!server) {
        printf("Create UDP Control block failed!\r\n");
        goto _exit_1;
    }

    source_ip.addr = inet_addr(host);
    ret = udp_bind(server, &source_ip, IPERF_PORT);
    if (ret != ERR_OK) {
        printf("Bind failed!\r\n");
        goto _exit_2;
    }

    printf("bind UDP socket successfully!\r\n");

    memset(&context, 0, sizeof context);
    context.f_min = 8000.0;
    context.packet_id = -1;
    udp_recv(server, iperf_server_udp_recv_fn, (void *)&context);

    // 等待接收退出信号
    //xSemaphoreTake(context.comp_sig_handle, portMAX_DELAY);
    while (!context.exit_flag) {
        vTaskDelay(1000);
    }

    printf("ipus exit..\r\n");

_exit_2:
    udp_remove(server);
_exit_1:
    vPortFree(arg); // XXX 检查前面是否释放
}

static void iperf_client_udp_entry(const char *name)
{
    int host_len;
    char *host;

    host_len = strlen(name) + 4;
    host = pvPortMalloc(host_len);//mem will be free in tcpc_entry
    strcpy(host, name);
    aos_task_new("ipu", iperf_client_udp, host, 4096);
}

static void iperf_server_udp_entry(const char *name)
{
    int host_len;
    char *host;

    host_len = strlen(name) + 1;
    host = pvPortMalloc(host_len);
    strcpy(host, name);
    aos_task_new("ipus", iperf_server_udp, host, 4096);
}

static void iperf_server(void *arg)
{
    uint8_t *recv_data;
    uint32_t sin_size;
    uint32_t tick0, tick1, tick2;
    int sock = -1, connected, bytes_received, recvlen;
    struct sockaddr_in server_addr, client_addr;
    char speed[32] = { 0 };
    char *host = (char*)arg;
    uint64_t bytes_transfered = 0;
    float f_min = 8000.0, f_max = 0.0;

    recv_data = (uint8_t *)pvPortMalloc(IPERF_BUFSZ);
    if (recv_data == NULL)
    {
        printf("No memory\r\n");
        goto __exit;
    }

    (void) host;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket error\r\n");
        goto __exit;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(IPERF_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), 0x0, sizeof(server_addr.sin_zero));

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        printf("Unable to bind\r\n");
        goto __exit;
    }

    if (listen(sock, 5) == -1) {
        printf("Listen error\r\n");
        goto __exit;
    }

    while (1) {
        sin_size = sizeof(struct sockaddr_in);

        connected = accept(sock, (struct sockaddr *)&client_addr, (socklen_t *)&sin_size);

        printf("new client connected from (%s, %d)\r\n",
                  inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        {
            int flag = 1;

            setsockopt(connected,
                IPPROTO_TCP,     /* set option at TCP level */
                TCP_NODELAY,     /* name of option */
                (void *) &flag,  /* the cast is historical cruft */
                sizeof(int));    /* length of option value */
        }

        recvlen = 0;
        tick0 = xTaskGetTickCount();
        tick1 = tick0;
        while (1) {
            bytes_received = recv(connected, recv_data, IPERF_BUFSZ, 0);
            if (bytes_received <= 0) break;

            recvlen += bytes_received;

            tick2 = xTaskGetTickCount();
            if (tick2 - tick1 >= 1000 * 5)
            {
                float f_now, f_avg;

                f_now = (float)(recvlen)  / 125 / (((int32_t)tick2 - (int32_t)tick1)) * 1000;
                f_now /= 1000.0f;
                bytes_transfered += recvlen;
                f_avg = (float)(bytes_transfered)  / 125 / (((int32_t)tick2 - (int32_t)tick0)) * 1000;
                f_avg /= 1000.0f;

                if (f_now < f_min) {
                    f_min = f_now;
                }
                if (f_max < f_now) {
                    f_max = f_now;
                }
                snprintf(speed, sizeof(speed), "%.4f(%.4f %.4f %.4f) Mbps!\r\n",
                        f_now,
                        f_min,
                        f_avg,
                        f_max
                );
                printf("%s", speed);
                tick1 = tick2;
                recvlen = 0;
            }
        }

        if (connected >= 0) closesocket(connected);
        connected = -1;
    }

__exit:
    if (sock >= 0) closesocket(sock);
    if (recv_data) vPortFree(recv_data);
    if (arg) vPortFree(arg);
}

static void iperf_server_entry(const char *name)
{
    int host_len;
    char *host;

    host_len = strlen(name) + 4;
    host = pvPortMalloc(host_len);//mem will be free in tcpc_entry
    strcpy(host, name);
    aos_task_new("ips", iperf_server, host, 4096);
}

static void ipc_test_cmd(char *buf, int len, int argc, char **argv)
{
    if (1 == argc) {
        printf(DEBUG_HEADER "[IPC] Connecting with default address " DEFAULT_HOST_IP "\r\n");
        iperf_client_tcp_entry(DEFAULT_HOST_IP);
    } else if (2 == argc) {
        iperf_client_tcp_entry(argv[1]);
    } else {
        printf(DEBUG_HEADER  "[IPC] illegal address\r\n");
    }
}

static void ips_test_cmd(char *buf, int len, int argc, char **argv)
{
    if (1 == argc) {
        puts(DEBUG_HEADER "[IPS] Starting iperf server on 0.0.0.0\r\n");
        iperf_server_entry(DEFAULT_HOST_IP);
    } else if (2 == argc) {
        iperf_server_entry(argv[1]);
    } else {
        printf(DEBUG_HEADER  "[IPS] illegal address\r\n");
    }
}

static void ipu_test_cmd(char *buf, int len, int argc, char **argv)
{
    if (1 == argc) {
        printf(DEBUG_HEADER "[IPU] Connecting with default address " DEFAULT_HOST_IP "\r\n");
        iperf_client_udp_entry(DEFAULT_HOST_IP);
    } else if (2 == argc) {
        iperf_client_udp_entry(argv[1]);
    } else {
        printf(DEBUG_HEADER  "[IPU] illegal address\r\n");
    }
}

// iperf UDP Server
static void ipus_test_cmd(char *buf, int len, int argc, char **argv)
{
    if (1 == argc) {
        printf(DEBUG_HEADER "[IPUS] Connecting with default address 0.0.0.0\r\n");
        iperf_server_udp_entry("0.0.0.0");
    } else if (2 == argc) {
        iperf_server_udp_entry(argv[1]);
    } else {
        printf(DEBUG_HEADER  "[IPUS] illegal address\r\n");
    }
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "ipc", "iperf TCP client", ipc_test_cmd},
    { "ips", "iperf TCP server", ips_test_cmd},
    { "ipu", "iperf UDP client", ipu_test_cmd},
    { "ipus", "iperf UDP server", ipus_test_cmd},
};

int network_netutils_iperf_cli_register()
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
