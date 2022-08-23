#include "blog.h"
#include "bl602_mfg_efuse.h"
#include "bl_irq.h"
#include "hosal_efuse.h"

int hosal_efuse_read(uint32_t addr, uint32_t *data, uint32_t len)
{
    /* we must ensure 4-byte alignment */
    if (addr % 4 || (uint32_t)data % 4) {
        blog_error("parameter error!\r\n");
        return -1;
    }
    
    GLOBAL_IRQ_SAVE();
    mfg_efuse_read(addr, data, len, 1);
    GLOBAL_IRQ_RESTORE();
    
    return 0;
}

int hosal_efuse_write(uint32_t addr, uint32_t *data, uint32_t len)
{
    /* we must ensure 4-byte alignment */
    if (addr % 4 || (uint32_t)data % 4) {
        blog_error("parameter error!\r\n");
        return -1;
    }

    GLOBAL_IRQ_SAVE();
    mfg_efuse_write_pre(addr, data, len);
    mfg_efuse_program();
    GLOBAL_IRQ_RESTORE();

    return 0;
}
