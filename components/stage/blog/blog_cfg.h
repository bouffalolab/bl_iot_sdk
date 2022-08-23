#ifndef __BLOG_CFG_H__
#define __BLOG_CFG_H__

#define BLOG_POWERON_SOFTLEVEL_COMPONENT    (BLOG_LEVEL_INFO)
#define BLOG_POWERON_SOFTLEVEL_FILE         (BLOG_LEVEL_INFO)
#define BLOG_POWERON_SOFTLEVEL_PRI          (BLOG_LEVEL_INFO)
#define BLOG_NAMELEN_MAX                    (128)
#define BLOG_DUMP_DEDUPLICATE               (1)
#define BLOG_TEST                           (0)

#define BLOG_LINE_BUF_SIZE                  (256)

#define __blog_printf                       bl_printk

#endif
