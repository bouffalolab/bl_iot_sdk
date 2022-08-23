
#include <stdio.h>
#include <aos/kernel.h>

#include <blog.h>

#define BLOG_HARD_DECLARE_DISABLE 1
BLOG_DECLARE(blog_testc1);

void blog_testc1_entry(void *arg)
{
    aos_msleep(5000);

    blog_debug("blog_testc1 debug\r\n");
    blog_info("blog_testc1 info\r\n");
    blog_warn("blog_testc1 warn\r\n");
    blog_error("blog_testc1 error\r\n");

    blog_debug_user(blog_testc1,"blog_testc1 debug user\r\n");
    blog_info_user(blog_testc1,"blog_testc1 info user\r\n");
    blog_warn_user(blog_testc1,"blog_testc1 warn user\r\n");
    blog_error_user(blog_testc1,"blog_testc1 error user\r\n");
    blog_assert_user(blog_testc1,"blog_testc1 assert user\r\n");

    while (1) {
        aos_msleep(5000);
        blog_debug("blog_testc1 debug\r\n");
        blog_info("blog_testc1 info\r\n");
        blog_warn("blog_testc1 warn\r\n");
        blog_error("blog_testc1 error\r\n");

        blog_debug_user(blog_testc1,"blog_testc1 debug user\r\n");
        blog_info_user(blog_testc1,"blog_testc1 info user\r\n");
        blog_warn_user(blog_testc1,"blog_testc1 warn user\r\n");
        blog_error_user(blog_testc1,"blog_testc1 error user\r\n");
        blog_assert_user(blog_testc1,"blog_testc1 assert user\r\n");
    }
}

int blog_testc1_init(void)
{
    aos_task_new("blog_testc1", blog_testc1_entry, NULL, 2048);

    return 0;
}
