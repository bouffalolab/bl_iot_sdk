
#include <stdio.h>
#include <aos/kernel.h>

#include <blog.h>

void blog_testc3_entry(void *arg)
{
    aos_msleep(5000);

    blog_debug("blog_testc3 debug\r\n");
    blog_info("blog_testc3 info\r\n");
    blog_warn("blog_testc3 warn\r\n");
    blog_error("blog_testc3 error\r\n");

    while (1) {
        aos_msleep(5000);
        blog_debug("blog_testc3 debug\r\n");
        blog_info("blog_testc3 info\r\n");
        blog_warn("blog_testc3 warn\r\n");
        blog_error("blog_testc3 error\r\n");
    }
}

int blog_testc3_init(void)
{
    aos_task_new("blog_testc3", blog_testc3_entry, NULL, 2048);

    return 0;
}
