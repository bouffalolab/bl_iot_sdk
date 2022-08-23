#ifndef __BL_IRQ_H__
#define __BL_IRQ_H__

#include "clic.h"
#include "riscv_encoding.h"

void bl_irq_enable(unsigned int source);
void bl_irq_disable(unsigned int source);
void bl_irq_pending_set(unsigned int source);
void bl_irq_pending_clear(unsigned int source);
typedef enum {
    BL_IRQ_EXCEPTION_TYPE_LOAD_MISALIGN,
    BL_IRQ_EXCEPTION_TYPE_STORE_MISALIGN,
    BL_IRQ_EXCEPTION_TYPE_ACCESS_ILLEGAL,
    BL_IRQ_EXCEPTION_TYPE_ILLEGAL_INSTRUCTION,
} BL_IRQ_EXCEPTION_TYPE_T;
void bl_irq_exception_trigger(BL_IRQ_EXCEPTION_TYPE_T type, void *ptr);

void bl_irq_init(void);
/*The following section define the IRQ handler for other files*/
void bl_sec_aes_IRQHandler(void);
void bl_sec_sha_IRQHandler(void);
void bl_sec_pka_IRQHandler(void);
void bl_dma_IRQHandler(void);
void intc_irq(void);//MAC IRQ
void bl_irq_handler(void);//IPC host IRQ
void bl_irq_register_with_ctx(int irqnum, void *handler, void *ctx);
void bl_irq_register(int irqnum, void *handler);
void bl_irq_unregister(int irqnum, void *handler);
void bl_irq_ctx_get(int irqnum, void **ctx);
void bl_irq_handler_get(int irqnum, void **handler);

int bl_irq_save(void);
void bl_irq_restore(int flags);

#define GLOBAL_IRQ_SAVE()  if (1) { \
  int ____global_prev_mie_irq____ = bl_irq_save();

#define GLOBAL_IRQ_RESTORE() \
  bl_irq_restore(____global_prev_mie_irq____ ); \
}

#endif
