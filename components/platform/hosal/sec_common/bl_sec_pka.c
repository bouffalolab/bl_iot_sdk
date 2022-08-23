#include <FreeRTOS.h>
#include <semphr.h>

#include <bl_sec.h>
#include "bl_sec_hw_common.h"

static StaticSemaphore_t pka_mutex_buf;
static SemaphoreHandle_t pka_mutex = NULL;

int bl_sec_pka_init(void)
{
#if defined(BL616) || defined BL808
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_MCU_MUXPLL_160M);
#elif defined(BL702L)
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_SRC_HCLK);
#else
    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_HCLK);
#endif

    pka_mutex = xSemaphoreCreateMutexStatic(&pka_mutex_buf);
    if (pka_mutex) {
        return 0;
    } else {
        return -1;
    }
}

int bl_sec_pka_mutex_take(void)
{
    if (pdPASS != xSemaphoreTake(pka_mutex, portMAX_DELAY)) {
        return -1;
    }
    return 0;
}

int bl_sec_pka_mutex_give(void)
{
    if (pdPASS != xSemaphoreGive(pka_mutex)) {
        return -1;
    }
    return 0;
}
