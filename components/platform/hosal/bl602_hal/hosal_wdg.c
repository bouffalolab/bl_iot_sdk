
#include <stdio.h>
#include <hosal_wdg.h>
#include <bl_wdt.h>
#include <blog.h>

int hosal_wdg_init(hosal_wdg_dev_t *wdg)
{
    uint32_t ms;

    if (NULL == wdg) 
    {
        return -1;
    }

    ms = wdg->config.timeout;

    blog_info("hosal_wdg_init t_ms = %ld\r\n", ms);

    bl_wdt_init((int)ms);

    return 0;
}

void hosal_wdg_reload(hosal_wdg_dev_t *wdg)
{
    bl_wdt_feed();
}

int hosal_wdg_finalize(hosal_wdg_dev_t *wdg)
{
    bl_wdt_disable();

    return 0;
}

