
#include <stdio.h>
#include <aos/kernel.h>

#include <blog.h>

BLOG_DECLARE(blog_testc2);

void test_buf(void)
{
    int i;
    static uint8_t buf[256];

    for(i = 0; i < sizeof(buf); i++) {
        buf[i] = (uint8_t)i;
    }

    blog_debug_hexdump("hexdumpbuf", buf, sizeof(buf));
    blog_info_hexdump("hexdumpbuf", buf, sizeof(buf));
    blog_warn_hexdump("hexdumpbuf", buf, sizeof(buf));
    blog_error_hexdump("hexdumpbuf", buf, sizeof(buf));
    blog_assert_hexdump("hexdumpbuf", buf, sizeof(buf));
}
void blog_testc2_entry(void *arg)
{
    aos_msleep(5000);

    blog_debug("blog_testc2 debug\r\n");
    blog_info("blog_testc2 info\r\n");
    blog_warn("blog_testc2 warn\r\n");
    blog_error("blog_testc2 error\r\n");

    blog_debug_user(blog_testc2,"blog_testc2 debug user\r\n");
    blog_info_user(blog_testc2,"blog_testc2 info user\r\n");
    blog_warn_user(blog_testc2,"blog_testc2 warn user\r\n");
    blog_error_user(blog_testc2,"blog_testc2 error user\r\n");
    blog_assert_user(blog_testc2,"blog_testc2 assert user\r\n");

    while (1) {
        aos_msleep(5000);

        test_buf();

        blog_debug("blog_testc2 debug\r\n");
        blog_info("blog_testc2 info\r\n");
        blog_warn("blog_testc2 warn\r\n");
        blog_error("blog_testc2 error\r\n");

        blog_debug_user(blog_testc2,"blog_testc2 debug user\r\n");
        blog_info_user(blog_testc2,"blog_testc2 info user\r\n");
        blog_warn_user(blog_testc2,"blog_testc2 warn user\r\n");
        blog_error_user(blog_testc2,"blog_testc2 error user\r\n");
        blog_assert_user(blog_testc2,"blog_testc2 assert user\r\n");
    }
}

int blog_testc2_init(void)
{
    aos_task_new("blog_testc2", blog_testc2_entry, NULL, 2048);

    return 0;
}
