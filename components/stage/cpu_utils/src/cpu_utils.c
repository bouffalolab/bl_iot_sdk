/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#include <cpu_utils.h>

#define TEST_TIME  (2000) // 2s

int osCPU_Usage = 0;
uint64_t  osCPU_TotalIdleTime = 0;
static cpu_usage_t cpu_usage;
static uint32_t cpu_freq = 0;
static uint8_t count_32s[32];
static uint8_t count_64s[64];

#if defined (__riscv_xlen)
#include "bl808_clock.h"

static uint32_t mtimer_freq = 0;

#define KIN1_InitCycleCounter() \
  mtimer_freq = CPU_Get_MTimer_Clock(); \

#define KIN1_ResetCycleCounter()
#define KIN1_EnableCycleCounter()
#define KIN1_DisableCycleCounter()
static inline uint64_t KIN1_GetCycleCounter() {
#if __riscv_xlen == 32
#warning "build in e907"
  register uint32_t cycle, cycleh, cycleh_tmp;
  do {
    asm volatile ("rdcycleh %0" : "=r"(cycleh));
    asm volatile ("rdcycle %0" : "=r"(cycle));
    asm volatile ("rdcycleh %0" : "=r"(cycleh_tmp));
  } while(cycleh != cycleh_tmp);
  return (cycleh << 32) | cycle;
#elif __riscv_xlen == 64
#warning "build in c906"
  register uint64_t cycle;
  asm volatile ("rdcycle %0" : "=r"(cycle));
  return cycle;
#endif
}

static inline uint64_t KIN1_GetTimeMS(void) {
#if __riscv_xlen == 32
#define CLINT_CTRL_ADDR             ( 0xE0000000UL )
#define configMTIME_BASE_ADDRESS    ( CLINT_CTRL_ADDR + 0xBFF8UL )
#define configMTIMECMP_BASE_ADDRESS ( CLINT_CTRL_ADDR + 0x4000UL )
  uint32_t ulCurrentTimeHigh, ulCurrentTimeLow;
  volatile uint32_t * const pulTimeHigh = ( volatile uint32_t * const ) ( ( configMTIME_BASE_ADDRESS ) + 4UL ); /* 8-byte typer so high 32-bit word is 4 bytes up. */
  volatile uint32_t * const pulTimeLow = ( volatile uint32_t * const ) ( configMTIME_BASE_ADDRESS );
  do {
    ulCurrentTimeHigh = *pulTimeHigh;
    ulCurrentTimeLow = *pulTimeLow;
  } while( ulCurrentTimeHigh != *pulTimeHigh );

  return ((ulCurrentTimeHigh << 32) | ulCurrentTimeLow) / (mtimer_freq / 1000);

#elif __riscv_xlen == 64
  uint64_t current_time;
  asm volatile( "csrr %0, time" : "=r"( current_time ) );
  return current_time / (mtimer_freq / 1000);
#endif
}
#else
#define KIN1_DWT_CONTROL             (*((volatile uint32_t*)0xE0001000))
    /*!< DWT Control register */
#define KIN1_DWT_CYCCNTENA_BIT       (1UL<<0)
    /*!< CYCCNTENA bit in DWT_CONTROL register */
#define KIN1_DWT_CYCCNT              (*((volatile uint32_t*)0xE0001004))
    /*!< DWT Cycle Counter register */
#define KIN1_DEMCR                   (*((volatile uint32_t*)0xE000EDFC))
    /*!< DEMCR: Debug Exception and Monitor Control Register */
#define KIN1_TRCENA_BIT              (1UL<<24)
    /*!< Trace enable bit in DEMCR register */
#define KIN1_InitCycleCounter() \
  KIN1_DEMCR |= KIN1_TRCENA_BIT
  /*!< Init cycle counter */
#define KIN1_ResetCycleCounter() \
  KIN1_DWT_CYCCNT = 0
  /*!< Reset cycle counter */
#define KIN1_EnableCycleCounter() \
  KIN1_DWT_CONTROL |= KIN1_DWT_CYCCNTENA_BIT
  /*!< Enable cycle counter */
#define KIN1_DisableCycleCounter() \
  KIN1_DWT_CONTROL &= ~KIN1_DWT_CYCCNTENA_BIT
  /*!< Disable cycle counter */
#define KIN1_GetCycleCounter() \
  KIN1_DWT_CYCCNT
  /*!< Read cycle counter register */
#define KIN1_GetTimeMS()  \
  (MAC_TIMER / 1000)
#endif

void cpu_utils_usage_init(void)
{
    KIN1_InitCycleCounter();
    KIN1_ResetCycleCounter();
    KIN1_EnableCycleCounter();
#if defined (__riscv_xlen)
    cpu_freq = SystemCoreClockGet();
#else
    cpu_freq = 160*100*100;
#endif

    printf("cpu_freq: %d, mtimer_freq:%d\r\n", (int)cpu_freq, (int)mtimer_freq);
}

int cpu_utils_usage_get(cpu_usage_t *usage)
{
    uint16_t total_32s_usage = 0;
    uint16_t total_64s_usage = 0;
    uint8_t i;
    for(i = 0;i < 32;i++){
        total_32s_usage += count_32s[i];
        total_64s_usage += count_64s[i];
        cpu_usage.usage_30s_mean = total_32s_usage >> 5;
    }
    for(i = 32;i < 64;i++){
        total_64s_usage += count_64s[i];
        cpu_usage.usage_60s_mean = total_64s_usage >> 6;
    }
    *usage = cpu_usage;
    return 0;
}

void cpu_utils_usage_count(void)
{
    static uint64_t Cycle_Counter = 0,Cycle_Record = 0;
    static uint64_t Cycle_mininal = 10000000;
    static uint64_t current_time = 0;
    static uint64_t record_time = 0;
    static uint8_t record_count = 0;
    uint32_t Time_interval;

    Cycle_Counter = KIN1_GetCycleCounter();
    if ((Cycle_Counter - Cycle_Record > 0) && (Cycle_Counter - Cycle_Record <= Cycle_mininal)){
        osCPU_TotalIdleTime += (Cycle_Counter - Cycle_Record);
    }

    Cycle_mininal = (Cycle_Counter - Cycle_Record) < Cycle_mininal
      ? (Cycle_Counter - Cycle_Record) + 100
      : Cycle_mininal;

    Cycle_Record = Cycle_Counter;

    current_time = KIN1_GetTimeMS();
    Time_interval = current_time - record_time;
    if (Time_interval > TEST_TIME){
        record_time = current_time;
        //printf("osCPU_TotalIdleTime:%ld, min:%ld\r\n", (long int)osCPU_TotalIdleTime, (long int)Cycle_mininal);
        osCPU_Usage = (100 - (osCPU_TotalIdleTime / (cpu_freq / 100) ) / (Time_interval / 1000));  /* 2 is 2s */
        cpu_usage.usage_realtime = osCPU_Usage;
        osCPU_TotalIdleTime = 0;
        count_32s[record_count%32] = osCPU_Usage;
        count_64s[record_count%64] = osCPU_Usage;
        record_count++;
    }
    if (record_count == 255) {
        record_count = 0;
    }
}

void __attribute__ ((weak))
vApplicationIdleHook( void )
{
  cpu_utils_usage_count();
}
