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
#include "bl_cpu.h"

void bl_cpu_word_copy(uint32_t *src, uint32_t *dst, uint32_t words)
{
    
    
    __asm volatile(
        "                                       \r\n"
        "          MOVS   r3, r2, LSR #3        \r\n"
        "          BEQ    copywords             \r\n"
        "          PUSH   {r4-r11}              \r\n"
        "    octcopy:                           \r\n"
        "          LDM    r0!, {r4-r11}         \r\n"
        "          STM    r1!, {r4-r11}         \r\n"
        "          SUBS   r3, r3, #1            \r\n"
        "          BNE    octcopy               \r\n"
        "          POP    {r4-r11}              \r\n"
        "    copywords:                         \r\n"
        "          ANDS   r2, r2, #7            \r\n" //Number of odd words to copy
        "          BEQ    stop                  \r\n" //No words left to copy?
        "    wordcopy:                          \r\n"
        "          LDR    r3, [r0], #4          \r\n" //Load a word from the source and
        "          STR    r3, [r1], #4          \r\n" //store it to the destination
        "          SUBS   r2, r2, #1            \r\n" //Decrement the counter
        "          BNE    wordcopy              \r\n" //... copy more
        "    stop:                              \r\n"
        "          MOV    r0, #0x0              \r\n"
    );
}
