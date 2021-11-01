#include "l1c_reg.h"
#include "bl702_it.h"

/** @addtogroup  BL602_Periph_Driver
 *  @{
 */

/** @defgroup DRIVER_COMMON DRIVER_COMMON
 *  @brief Digger driver common functions
 *  @{
 */

/** @defgroup DRIVER_Private_Type
 *  @{
 */


/*@} end of group DRIVER_Private_Type*/

/** @defgroup DRIVER_Private_Defines
 *  @{
 */

/*@} end of group DRIVER_Private_Defines */

/** @defgroup DRIVER_Private_Variables
 *  @{
 */
pFunc __Interrupt_Handlers[IRQn_LAST]={0};

/*@} end of group DRIVER_Private_Variables */

/** @defgroup DRIVER_Global_Variables
 *  @{
 */

/*@} end of group DRIVER_Global_Variables */

/** @defgroup DRIVER_Private_FunctionDeclaration
 *  @{
 */

/*@} end of group DRIVER_Private_FunctionDeclaration */

/** @defgroup DRIVER_Private_Functions
 *  @{
 */

/*@} end of group DRIVER_Private_Functions */

/** @defgroup DRIVER_Public_Functions
 *  @{
 */

void Trap_Handler(void){
    unsigned long cause;
    unsigned long epc;
    unsigned long tval;

    MSG("Trap_Handler\r\n");

    cause = read_csr(mcause);
    MSG("mcause=%08x\r\n",(uint32_t)cause);
    epc=read_csr(mepc);
    MSG("mepc:%08x\r\n",(uint32_t)epc);
    tval=read_csr(mtval);
    MSG("mtval:%08x\r\n",(uint32_t)tval);

    cause=(cause&0x3ff);
    switch(cause){
        case 1:
            MSG("Instruction access fault\r\n");
            break;
        case 2:
            MSG("Illegal instruction\r\n");
            break;
        case 3:
            MSG("Breakpoint\r\n");
            break;
        case 4:
            MSG("Load address misaligned\r\n");
            break;
        case 5:
            MSG("Load access fault\r\n");
            break;
        case 6:
            MSG("Store/AMO address misaligned\r\n");
            break;
        case 7:
            MSG("Store/AMO access fault\r\n");
            break;
        case 8:
            MSG("Environment call from U-mode\r\n");
            epc+=4;
            write_csr(mepc,epc);
            break;
        case 11:
            MSG("Environment call from M-mode\r\n");
            epc+=4;
            write_csr(mepc,epc);
            return;
        default:
            MSG("Cause num=%d\r\n",(uint32_t)cause);
            epc+=4;
            write_csr(mepc,epc);
            break;
    }
    while(1);
}

void Interrupt_Handler_Register(IRQn_Type irq,pFunc interruptFun)
{
    if(irq<IRQn_LAST){
        __Interrupt_Handlers[irq]=interruptFun;
    }
}

void Interrupt_Handler(void)
{
    pFunc interruptFun;
    uint32_t num=0;
    volatile uint32_t ulMEPC = 0UL, ulMCAUSE = 0UL;

    /* Store a few register values that might be useful when determining why this
    function was called. */
    __asm volatile( "csrr %0, mepc" : "=r"( ulMEPC ) );
    __asm volatile( "csrr %0, mcause" : "=r"( ulMCAUSE ) );
    
    if((ulMCAUSE&0x80000000)==0){
        /*Exception*/
        MSG("Exception should not be here\r\n");
    }else{
        num=ulMCAUSE&0x3FF;
        if(num<IRQn_LAST){
            interruptFun=__Interrupt_Handlers[num];
            if(NULL!=interruptFun){
                interruptFun();
            }else{
                MSG("Interrupt num:%d IRQHandler not installed\r\n",(unsigned int)num);
                if(num>=IRQ_NUM_BASE){
                    MSG("Peripheral Interrupt num:%d \r\n",(unsigned int)num-IRQ_NUM_BASE);
                }
                while(1);
            }
        }else{
            MSG("Unexpected interrupt num:%d\r\n",(unsigned int)num);
        }
    }
}

void FreeRTOS_Interrupt_Handler(void)
{
    Interrupt_Handler();
}

/*@} end of group DRIVER_Public_Functions */

/*@} end of group DRIVER_COMMON */

/*@} end of group BL602_Periph_Driver */


