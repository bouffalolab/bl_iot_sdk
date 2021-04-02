#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <joylink_memory.h>
#include <joylink_extern.h>
#include <jl_tc.h>

#include <FreeRTOS.h>
#include <task.h>

static jl_tc_result_t jl_tc_dev_http_post()
{
    int f = 0;
    char *recv_buf;
    int ret;
    char *req1_host = "jd.com";
    char *req1_pyld = "GET / HTTP/1.1\r\nHost: jd.com\r\n" "\r\n";
    const int recvbuf_len = 512;

    recv_buf = jl_platform_malloc(recvbuf_len);
    if (recv_buf == NULL) {
        f++;
        goto RET;
    }

    ret = joylink_dev_http_post(req1_host, req1_pyld, recv_buf, recvbuf_len);
    if (ret <= 0) {
        f++;
    } else {
        printf("Returned body:\r\n<<EOF\r\n%.*s\r\nEOF\r\n", ret, recv_buf);
    }
RET:
    return f;
}

static jl_tc_result_t jl_tc_dev_https_post()
{
    int f = 0;
    char *recv_buf;
    int ret;
    char *req1_host = "jd.com";
    char *req1_pyld = "GET / HTTP/1.1\r\nHost: jd.com\r\n" "\r\n";
    const int recvbuf_len = 2048;

    recv_buf = jl_platform_malloc(recvbuf_len);
    if (recv_buf == NULL) {
        f++;
        goto RET;
    }

    ret = joylink_dev_https_post(req1_host, req1_pyld, recv_buf, recvbuf_len);
    if (ret <= 0) {
        f++;
    } else {
        printf("Returned body:\r\n<<EOF\r\n%.*s\r\nEOF\r\n", ret, recv_buf);
    }
RET:
    return f;
}

void jl_tc_extern_task(void *parm)
{
    int f = 0;

    f += jl_tc_dev_http_post();
    f += jl_tc_dev_https_post();

    if (f == 0) {
        printf("%s SUCCESS\r\n", __func__);
    } else {
        printf("%s FAILED\r\n", __func__);
    }

    vTaskDelete(NULL);
}

void jl_tc_extern()
{
    xTaskCreate(jl_tc_extern_task, "jl_tc_extern_task", 20 * 1024 / 4, NULL, 15, NULL);
}
