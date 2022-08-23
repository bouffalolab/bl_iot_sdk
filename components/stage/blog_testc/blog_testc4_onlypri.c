
#include <stdio.h>
#include <aos/kernel.h>

#include <blog.h>

BLOG_DECLARE(blog_testc4);

void blog_testc4_entry(void *arg)
{
    aos_msleep(5000);

    blog_debug_user(blog_testc4,"blog_testc4 debug user\r\n");
    blog_info_user(blog_testc4,"blog_testc4 info user\r\n");
    blog_warn_user(blog_testc4,"blog_testc4 warn user\r\n");
    blog_error_user(blog_testc4,"blog_testc4 error user\r\n");
    blog_assert_user(blog_testc4,"blog_testc4 assert user\r\n");

    while (1) {
        aos_msleep(5000);
        blog_debug_user(blog_testc4,"blog_testc4 debug user\r\n");
        blog_info_user(blog_testc4,"blog_testc4 info user\r\n");
        blog_warn_user(blog_testc4,"blog_testc4 warn user\r\n");
        blog_error_user(blog_testc4,"blog_testc4 error user\r\n");
        blog_assert_user(blog_testc4,"blog_testc4 assert user\r\n");
    }
}

int blog_testc4_init(void)
{
    aos_task_new("blog_testc4", blog_testc4_entry, NULL, 2048);

    return 0;
}
