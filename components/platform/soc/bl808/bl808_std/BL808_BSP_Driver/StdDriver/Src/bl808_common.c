/*
 * Copyright (c) 2016-2023 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "bl808_common.h"
#include "bl808_glb.h"
#include "bl808_dma.h"
#include <string.h>

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  COMMON
 *  @{
 */

/** @defgroup  COMMON_Private_Macros
 *  @{
 */

/*@} end of group COMMON_Private_Macros */

/** @defgroup  COMMON_Private_Types
 *  @{
 */

/*@} end of group COMMON_Private_Types */

/** @defgroup  COMMON_Private_Variables
 *  @{
 */
/**
 *  @brief BMX callback function pointer array
 */
#define NO_FPGA    0
intCallback_Type * bmxErrIntCb[]= {NULL};
intCallback_Type * bmxTOIntCb[]= {NULL};
intCallback_Type * l1cBmxErrIntCb[]= {NULL};
intCallback_Type * l1CBmxTOIntCb[]= {NULL};
intCallback_Type * secBMXErrIntCb[]= {NULL};
#ifdef CORE_CLK50M
uint32_t SystemCoreClock = 50 * 1000 * 1000;
#else
uint32_t SystemCoreClock = 400 * 1000 * 1000;
#endif

/**
 *  @brief RF callback function pointer array
 */
intCallback_Type * rfInt0Cb[]= {NULL};
intCallback_Type * rfInt1Cb[]= {NULL};

/**
 *  @brief SDIO interrupt callback function pointer array
 */
intCallback_Type * sdioIntCb[]= {NULL, NULL, NULL, NULL};

/**
 *  @brief SDH MMC1 interrupt callback function pointer array
 */
intCallback_Type * sdhMmc1IntCb[]= {NULL};

/**
 *  @brief SDH MMC3 interrupt callback function pointer array
 */
intCallback_Type * sdhMmc3IntCb[]= {NULL};

/**
 *  @brief SDH to PMU Slot1 interrupt callback function pointer array
 */
intCallback_Type * sdhPmu1IntCb[]= {NULL};

/**
 *  @brief SDH to PMU Slot3 interrupt callback function pointer array
 */
intCallback_Type * sdhPmu3IntCb[]= {NULL};

/**
 *  @brief Security engine interrupt callback function pointer array
 */
intCallback_Type * secEngTrngIntCb[]= {NULL};
intCallback_Type * secEngAesIntCb[]= {NULL};
intCallback_Type * secEngShaIntCb[]= {NULL};

/**
 *  @brief DMA interrupt callback function pointer array
 */
intCallback_Type * dma0Ch0IntCb[]= {NULL, NULL};
intCallback_Type * dma0Ch1IntCb[]= {NULL, NULL};
intCallback_Type * dma0Ch2IntCb[]= {NULL, NULL};
intCallback_Type * dma0Ch3IntCb[]= {NULL, NULL};
intCallback_Type * dma0Ch4IntCb[]= {NULL, NULL};
intCallback_Type * dma0Ch5IntCb[]= {NULL, NULL};
intCallback_Type * dma0Ch6IntCb[]= {NULL, NULL};
intCallback_Type * dma0Ch7IntCb[]= {NULL, NULL};

/**
 *  @brief Serial flash interrupt callback function pointer array
 */
intCallback_Type * sfCtrlIntCb[]= {NULL};

/**
 *  @brief CAM interrupt callback function pointer array
 */
intCallback_Type * gpadcDMAIntCb[]= {NULL, NULL, NULL};

/**
 *  @brief CAM interrupt callback function pointer array
 */
intCallback_Type * camIntCb[]= {NULL, NULL, NULL, NULL};

/**
 *  @brief Efuse interrupt callback function pointer array
 */
intCallback_Type * efuseIntCb[]= {NULL};

/**
 *  @brief SSP interrupt callback function pointer array
 */
intCallback_Type * sspIntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};

/**
 *  @brief SSP grayback interrupt callback function pointer array
 */
intCallback_Type * sspGbIntCb[]= {NULL};

/**
 *  @brief UART interrupt callback function pointer array
 */
intCallback_Type * uart0IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * uart1IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * uart2IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};

/**
 *  @brief I20 interrupt callback function pointer array
 */
intCallback_Type * i2c0IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * i2c1IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};

/**
 *  @brief PWM interrupt callback function pointer array
 */
intCallback_Type * pwmIntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};

/**
 *  @brief Timer interrupt callback function pointer array
 */
intCallback_Type * timer0Ch0IntCb[]= {NULL, NULL, NULL};
intCallback_Type * timer0Ch1IntCb[]= {NULL, NULL, NULL};
intCallback_Type * timer0Ch2IntCb[]= {NULL, NULL, NULL};
intCallback_Type * timer0WdtIntCb[]= {NULL, NULL, NULL};
intCallback_Type * timer1Ch0IntCb[]= {NULL, NULL, NULL};
intCallback_Type * timer1Ch1IntCb[]= {NULL, NULL, NULL};
intCallback_Type * timer1Ch2IntCb[]= {NULL, NULL, NULL};
intCallback_Type * timer1WdtIntCb[]= {NULL, NULL, NULL};

/**
 *  @brief MJPEG interrupt callback function pointer array
 */
intCallback_Type * mjpegIntCb[]= {NULL, NULL, NULL, NULL};

/**
 */

/**
 *  @brief PDS wake up interrupt callback function pointer array
 */
intCallback_Type * pdsIntCb[]= {NULL, NULL};
/**
 *  @brief Hibernate time out interrupt callback function pointer array
 */
intCallback_Type * hbnOut0IntCb[6]= {NULL};
intCallback_Type * hbnOut1IntCb[9]= {NULL};

/**
 *  @brief BOR callback function pointer array
 */
intCallback_Type * borIntCb[]= {NULL, NULL, NULL};

/**
 *  @brief MAC interrupt callback function pointer array
 */
intCallback_Type * macIntCb[]= {NULL, NULL, NULL};

#if NO_FPGA
/**
 *  @brief BL808 interrupt callback function pointer array
 */
intCallback_Type ** intCbfArra[IRQn_LAST - IRQN_PERI_START] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    dma0Ch0IntCb,
    dma0Ch1IntCb,
    dma0Ch2IntCb,
    dma0Ch3IntCb,
    dma0Ch4IntCb,
    dma0Ch5IntCb,
    dma0Ch6IntCb,
    dma0Ch7IntCb,
//    uart0IntCb,
//    i2c0IntCb,
//    i2c1IntCb,
//    mjpegIntCb,
};
#endif
static DMA_Channel_Cfg_Type chCfg={
    0x20000000,
    0x20010000,
    0,
    DMA_TRNS_M2M,
    DMA_CH0,
    DMA_TRNS_WIDTH_32BITS,
    DMA_TRNS_WIDTH_32BITS,
    DMA_BURST_SIZE_4,
    DMA_BURST_SIZE_4,
    DMA_MINC_ENABLE,
    DMA_MINC_ENABLE,
    DMA_REQ_NONE,
    DMA_REQ_NONE,
};
/*@} end of group COMMON_Private_Variables */

/** @defgroup  COMMON_Global_Variables
 *  @{
 */

/*@} end of group COMMON_Global_Variables */

/** @defgroup  COMMON_Private_Fun_Declaration
 *  @{
 */

/*@} end of group COMMON_Private_Fun_Declaration */

/** @defgroup  COMMON_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  NMI handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void NMI_Handler(void)
{
    BL_LOGD("%s\r\n",__func__);
    while(1){};
}
#if NO_FPGA
/****************************************************************************//**
 * @brief  HardFault handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void HardFault_Handler(void)
{
    BL_LOGD("%s\r\n",__func__);
    while(1){};
}
#endif
/****************************************************************************//**
 * @brief  MemManage handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void MemManage_Handler(void)
{
    BL_LOGD("%s\r\n",__func__);
    while(1){};
}

/****************************************************************************//**
 * @brief  BusFault handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void BusFault_Handler(void)
{
    BL_LOGD("%s\r\n",__func__);
    while(1){};
}

/****************************************************************************//**
 * @brief  UsageFault handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void UsageFault_Handler(void)
{
    BL_LOGD("%s\r\n",__func__);
    while(1){};
}

/****************************************************************************//**
 * @brief  SVC handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
/* void SVC_Handler(void)
{
//    BL_LOGD("%s\r\n",__func__);
    while(1){};
} */

/****************************************************************************//**
 * @brief  DebugMon handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DebugMon_Handler(void)
{
    BL_LOGD("%s\r\n",__func__);
    while(1){};
}
#if 0
/****************************************************************************//**
 * @brief  PendSV handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void PendSV_Handler(void)
{
    BL_LOGD("%s\r\n",__func__);
    while(1){};
}
#endif
/****************************************************************************//**
 * @brief  Install interrupt callback function for given interrupt type and peripheral
 *
 * @param  intPeriph: Select the peripheral, such as INT_UART1,INT_AES
 * @param  intType: Specifies the interrupt type. must be select interrupt enum type.
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void).
 *
 * @return none
 *
 *******************************************************************************/
#if NO_FPGA
void Install_Int_Callback(IRQn_Type intPeriph, uint32_t intType, intCallback_Type * cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_INT_PERIPH(intPeriph));

    intCbfArra[intPeriph - IRQN_PERI_START][intType] = cbFun;
}
#endif
/****************************************************************************//**
 * @brief  Delay us
 *
 * @param  cnt:  Delay cnt in us
 *
 * @return none
 *
 *******************************************************************************/
void ATTR_TCM_SECTION BL808_Delay_US(uint32_t cnt)
{
    volatile uint32_t i=((SystemCoreClock/1000000)/5)*cnt;
    while(i--);
}

/****************************************************************************//**
 * @brief  Delay ms
 *
 * @param  cnt: Delay cnt in ms
 *
 * @return none
 *
 *******************************************************************************/
void ATTR_TCM_SECTION BL808_Delay_MS(uint32_t cnt)
{
#ifndef A0_AUDIO_TEST
    BL808_Delay_US(cnt*1000);
#else
    TickType_t xDelay = pdMS_TO_TICKS(cnt);
    vTaskDelay(xDelay);
#endif
}

/****************************************************************************//**
 * @brief      delay us
 *
 * @param[in]  core:  systemcoreclock
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
#ifdef ARCH_ARM
#ifndef __GNUC__
__WEAK
__ASM void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core,uint32_t cnt)
{
    lsrs r0,#0x10
    muls r0,r1,r0
    mov  r2,r0
    lsrs r2,#0x04
    lsrs r2,#0x03
    cmp  r2,#0x01
    beq  end
    cmp  r2,#0x00
    beq  end
loop
    mov  r0,r0
    mov  r0,r0
    mov  r0,r0
    mov  r0,r0
    mov  r0,r0
    subs r2,r2,#0x01
    cmp  r2,#0x00
    bne  loop
end
    bx   lr
}
#else
__WEAK
void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core,uint32_t cnt)
{
    __asm__ __volatile__(
        "lsr r0,#0x10\n\t"
        "mul r0,r1,r0\n\t"
        "mov r2,r0\n\t"
        "lsr r2,#0x04\n\t"
        "lsr r2,#0x03\n\t"
        "cmp r2,#0x01\n\t"
        "beq end\n\t"
        "cmp r2,#0x00\n\t"
        "beq end\n"
        "loop :"
        "mov r0,r0\n\t"
        "mov r0,r0\n\t"
        "mov r0,r0\n\t"
        "mov r0,r0\n\t"
        "mov r0,r0\n\t"
        "sub r2,r2,#0x01\n\t"
        "cmp r2,#0x00\n\t"
        "bne loop\n"
        "end :"
        "mov r0,r0\n\t"
    );
}
#endif
#endif
#ifdef ARCH_RISCV
__WEAK
void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core,uint32_t cnt)
{
    volatile uint32_t divVal = 3;
    volatile uint32_t speed = 0;
    volatile uint32_t cycNum = 0;

    /* 1M=100K*10, so multiple is 10 */
    /* loop function take 4 instructions, so instructionNum is 4 */
    /* divVal = multiple*instructionNum */

    if(core>=1*1000*1000){
        /* CPU clock >= 1MHz */
        speed = core/(100*1000);
        cycNum = speed*cnt;
        cycNum = cycNum/10;
        cycNum = cycNum/divVal;
        /* cycNum >= 0 */
    }else{
        /* CPU clock < 1MHz */
        speed = core/1000;
        cycNum = speed*cnt;
        cycNum = cycNum/1000;
        cycNum = cycNum/divVal;
        /* cycNum >= 0 */
    }

    if(!cycNum){
        return ;
    }

    __asm__ __volatile__(
        "mv       a4,%0\n\t"
        "li       a5,0x0\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        ".align 4\n\t"
        "1  :\n"
        "beq      a5,a4,2f\n\t"
        "addi     a5,a5,0x1\n\t"
        "j        1b\n\t"
        "nop\n\t"
        "nop\n\t"
        "2   :\n\t"
        "nop\n"
        :                                  /* output */
        :"r"(cycNum)                       /* input */
        :"a4","a5"                         /* destruct description */
    );
}
#endif
#endif

/****************************************************************************//**
 * @brief      delay us
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION ARCH_Delay_US(uint32_t cnt)
{
    GLB_CORE_ID_Type coreID;
    uint32_t coreFreq;

    coreID = GLB_Get_Core_Type();

    switch(coreID){
        case GLB_CORE_ID_M0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_M1:
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
            break;
        case GLB_CORE_ID_D0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_D1:
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);
            break;
        case GLB_CORE_ID_LP:
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_LP_CLK);
            break;
        default :
            coreFreq = 32*1000*1000;
            break;
    }

    coreFreq = coreFreq?coreFreq:(32*1000*1000);

    ASM_Delay_Us(coreFreq,cnt);
}
#endif
/****************************************************************************//**
 * @brief      delay ms
 *
 * @param[in]  cnt:  delay cnt ms
 *
 * @return none
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION ARCH_Delay_MS(uint32_t cnt)
{
    uint32_t i = 0;
    uint32_t count = 0;

    if(cnt>=1024){
        /* delay (n*1024) ms */
        for(i=0;i<(cnt/1024);i++){
            ARCH_Delay_US(1024*1000);
        }
    }
    count = cnt&0x3FF;
    if(count){
        /* delay (1-1023)ms */
        ARCH_Delay_US(count*1000);
    }
}
#endif

/****************************************************************************//**
 * @brief  Char memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of char
 *
 * @return Destination pointer
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void* ATTR_TCM_SECTION ARCH_MemCpy(void *dst, const void *src, uint32_t n)
{
    const volatile uint8_t *p = src;
    volatile uint8_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }
    return dst;
}
#endif

/****************************************************************************//**
 * @brief  Word memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of words
 *
 * @return Destination pointer
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
uint32_t* ATTR_TCM_SECTION ARCH_MemCpy4(uint32_t *dst, const uint32_t *src, uint32_t n)
{
    const volatile uint32_t *p = src;
    volatile uint32_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }
    return dst;
}
#endif

/****************************************************************************//**
 * @brief  Fast memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of bytes
 *
 * @return Destination pointer
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void* ATTR_TCM_SECTION ARCH_MemCpy_Fast(void *pdst, const void *psrc, uint32_t n)
{
    uint32_t left,done,i=0;
    volatile uint8_t *dst=(uint8_t *)pdst;
    volatile uint8_t *src=(uint8_t *)psrc;

    if(((uintptr_t)dst&0x3)==0&&((uintptr_t)src&0x3)==0){
        ARCH_MemCpy4((uint32_t *)dst,(const uint32_t *)src,n>>2);
        left=n%4;
        done=n-left;
        while(i<left){
            dst[done+i]=src[done+i];
            i++;
        }
    }else{
        ARCH_MemCpy((void *)dst,(const void *)src,n);
    }
    return (uint8_t *)dst;
}
#endif

/****************************************************************************//**
 * @brief  Char memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of char
 *
 * @return Destination pointer
 *
 *******************************************************************************/
void* ATTR_TCM_SECTION BL60X_MemCpy(void *dst, const void *src, uint32_t n)
{
    const uint8_t *p = src;
    uint8_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }
    return dst;
}

/****************************************************************************//**
 * @brief  Word memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of words
 *
 * @return Destination pointer
 *
 *******************************************************************************/
uint32_t* ATTR_TCM_SECTION BL60X_MemCpy4(uint32_t *dst, const uint32_t *src, uint32_t n)
{
    const uint32_t *p = src;
    uint32_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }
    return dst;
}

/****************************************************************************//**
 * @brief  Fast memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of bytes
 *
 * @return Destination pointer
 *
 *******************************************************************************/
void* ATTR_TCM_SECTION BL60X_MemCpy_Fast(void *pdst, const void *psrc, uint32_t n)
{
    uint32_t left,done,i=0;
    uint8_t *dst=(uint8_t *)pdst;
    uint8_t *src=(uint8_t *)psrc;

    if(((uint32_t)dst&0x3)==0&&((uint32_t)src&0x3)==0){
        BL60X_MemCpy4((uint32_t *)dst,(const uint32_t *)src,n>>2);
        left=n%4;
        done=n-left;
        while(i<left){
            dst[done+i]=src[done+i];
            i++;
        }
    }else{
        BL60X_MemCpy(dst,src,n);
    }
    return dst;
}
/****************************************************************************//**
 * @brief  DMA memcpy init
 *
 * @param  dmaCh: DMA channel
 *
 * @return None
 *
 *******************************************************************************/
void BL60X_MemCpy_Fastest_DMA_Init(DMA_Chan_Type dmaCh)
{
    chCfg.ch=(DMA_Chan_Type)dmaCh;
    DMA_Enable(DMA0_ID);
}

/****************************************************************************//**
 * @brief  DMA memcpy
 *
 * @param  dst: Destination
 * @param  src: Source
 * @param  n:  Count of bytes
 *
 * @return Destination pointer
 *
 *******************************************************************************/
/*NO USE delete for compile pass*/
#if NO_FPGA
void* ATTR_TCM_SECTION BL60X_MemCpy_Fastest(void *pdst, const void *psrc, uint32_t n)
{
#define MAX_MEMCPY_LEN 1024
#define MAX_TRANS_LEN  4095

    uint32_t left,done,transLen,headSize,i=0;
    uint8_t *dst=(uint8_t *)pdst;
    uint8_t *src=(uint8_t *)psrc;

    if((n > MAX_MEMCPY_LEN)) {
        left=n;
        if(((uint32_t)dst&0x3)==((uint32_t)src&0x3)){
            while(i<(4-((uint32_t)dst&0x3))){
                dst[i]=src[i];
                i++;
            }
            i=0;
            left-=(4-((uint32_t)dst&0x3));
            chCfg.srcTransfWidth=chCfg.dstTransfWidth=DMA_TRNS_WIDTH_32BITS;
            chCfg.srcBurstSzie=chCfg.dstBurstSize=DMA_BURST_SIZE_4;
            transLen=MAX_TRANS_LEN*4;
        }else{
            if(((uint32_t)dst&0x1)==((uint32_t)src&0x1)){
                if(((uint32_t)dst&0x1)!=0){
                    dst[0]=src[0];
                    left-=1;
                }
                chCfg.srcTransfWidth=chCfg.dstTransfWidth=DMA_TRNS_WIDTH_16BITS;
                chCfg.srcBurstSzie=chCfg.dstBurstSize=DMA_BURST_SIZE_8;
                transLen=MAX_TRANS_LEN*2;
            }else{
                chCfg.srcTransfWidth=chCfg.dstTransfWidth=DMA_TRNS_WIDTH_8BITS;
                chCfg.srcBurstSzie=chCfg.dstBurstSize=DMA_BURST_SIZE_16;
                transLen=MAX_TRANS_LEN;
            }
        }
        while(left>=transLen){
            chCfg.srcDmaAddr=(uint32_t)psrc+n-left;
            chCfg.destDmaAddr=(uint32_t)pdst+n-left;
            chCfg.transfLength=MAX_TRANS_LEN;
            DMA_Channel_Disable(chCfg.ch);
            DMA_Channel_Init(&chCfg);
            DMA_Channel_Enable(chCfg.ch);
            while(DMA_Channel_Is_Busy(chCfg.ch)==SET);
            left-=transLen;
        }
        chCfg.srcDmaAddr=(uint32_t)psrc+n-left;
        chCfg.destDmaAddr=(uint32_t)pdst+n-left;
        if(chCfg.dstTransfWidth==DMA_TRNS_WIDTH_32BITS){
            chCfg.transfLength=left/4;
        }else if(chCfg.dstTransfWidth==DMA_TRNS_WIDTH_16BITS){
            chCfg.transfLength=left/2;
        }else{
            chCfg.transfLength=left;
        }
        DMA_Channel_Disable(chCfg.ch);
        DMA_Channel_Init(&chCfg);
        DMA_Channel_Enable(chCfg.ch);
        while(DMA_Channel_Is_Busy(chCfg.ch)==SET);
        if(chCfg.dstTransfWidth==DMA_TRNS_WIDTH_32BITS){
            left=n%4;
        }else if(chCfg.dstTransfWidth==DMA_TRNS_WIDTH_16BITS){
            left=n%2;
        }else{
            left=0;
        }
        done=n-left;
        while(i<left){
            dst[done+i]=src[done+i];
            i++;
        }
    }else if(((uint32_t)dst&0x3)==((uint32_t)src&0x3)){
        headSize=4-((uint32_t)dst&0x3);
        while(i<headSize){
            dst[i]=src[i];
            i++;
        }
        i=0;
        BL60X_MemCpy4((uint32_t *)(dst+headSize),(const uint32_t *)(src+headSize),(n-headSize)>>2);
        left=(n-headSize)%4;
        done=n-left;
        while(i<left){
            dst[done+i]=src[done+i];
            i++;
        }
    }else{
        BL60X_MemCpy(dst,src,n);
    }

    return dst;
}
#endif
/****************************************************************************//**
 * @brief  char memset
 *
 * @param  dst: Destination
 * @param  val: Value to set
 * @param  n: Count of char
 *
 * @return Destination pointer
 *
 *******************************************************************************/
void* ATTR_TCM_SECTION BL60X_MemSet(void *s, uint8_t c, uint32_t n)
{
    uint8_t *p = (uint8_t*) s;

    while (n > 0) {
        *p++ = (uint8_t) c;
        --n;
    }
    return s;
}
/****************************************************************************//**
 * @brief  Word memset
 *
 * @param  dst: Destination
 * @param  val: Value to set
 * @param  n: Count of words
 *
 * @return Destination pointer
 *
 *******************************************************************************/
uint32_t* ATTR_TCM_SECTION BL60X_MemSet4(uint32_t *dst, const uint32_t val, uint32_t n)
{
    uint32_t *q = dst;

    while (n--) {
        *q++ = val;
    }
    return dst;
}

#ifdef  DEBUG
/*******************************************************************************
* @brief  Reports the name of the source file and the source line number
*         where the CHECK_PARAM error has occurred.

* @param  file: Pointer to the source file name
* @param  line: assert_param error line source number

* @return None
*******************************************************************************/
void ATTR_TCM_SECTION check_failed(uint8_t *file, uint32_t line)
{
    BL_LOGE("CHECK FAILED @ %s, line %d\r\n", (char *)file, line);

    BL_ABORT();
}
#endif /* DEBUG */


int bl_log_print_level = BL_LOG_INFO;

int BL_DBG_ChgLogPrintLevel(BL_LOGTYPE level)
{
    if (level >= BL_LOG_ALL) {
        return -1;
    }
    bl_log_print_level = level;

    return 0;
}

BL_LOGTYPE BL_DBG_GetLogPrintLevel(void)
{
    return bl_log_print_level;
}

void* BL_MallocDMA(uint8_t mem_id, size_t size)
{
    void* ret;

    if ((ret = pvPortMalloc(size)) == NULL) {
        printf("!!! [BL_MallocDMA] mem_id %d, fail to alloc size 0x%x\r\n", mem_id, (unsigned int)size);
        BL_ABORT();
    }

    BL_LOGI("[BL_MallocDMA] mem_id %d, [0x%p ~ 0x%p], size 0x%x\r\n", mem_id, ret, ret + size, (unsigned int)size);

    return ret;
}

/*@} end of group COMMON_Public_Functions */

/*@} end of group COMMON */

/*@} end of group BL608_Peripheral_Driver */
