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
#ifndef __BL808_PSRAM_CTRL_H__
#define __BL808_PSRAM_CTRL_H__

#include "psram_ctrl_reg.h"
#include "bl808_glb.h"
#include "bl808_common.h"

typedef enum {
    PSRAM0_ID,                                /*!< PSRAM0 define */
    PSRAM1_ID,                                /*!< PSRAM1 define */
}PSRAM_ID_Type;

typedef enum {
    PSRAM_3_CLOCKS_RLATENCY = 0,          /*!< PSRAM 3 clocks latency */
    PSRAM_4_CLOCKS_RLATENCY = 1,          /*!< PSRAM 4 clocks latency */
    PSRAM_5_CLOCKS_RLATENCY = 2,          /*!< PSRAM 5 clocks latency(default) */
    PSRAM_6_CLOCKS_RLATENCY = 3,          /*!< PSRAM 6 clocks latency */
    PSRAM_7_CLOCKS_RLATENCY = 4,          /*!< PSRAM 7 clocks latency */
}PSRAM_RLatency_Type;

typedef enum {
    PSRAM_3_CLOCKS_WLATENCY = 0,            /*!< PSRAM 3 clocks latency */
    PSRAM_4_CLOCKS_WLATENCY = 4,            /*!< PSRAM 4 clocks latency */
    PSRAM_5_CLOCKS_WLATENCY = 2,            /*!< PSRAM 5 clocks latency(default) */
    PSRAM_6_CLOCKS_WLATENCY = 6,            /*!< PSRAM 6 clocks latency */
    PSRAM_7_CLOCKS_WLATENCY = 1,            /*!< PSRAM 7 clocks latency */
}PSRAM_WLatency_Type;


#define IS_PSRAM_R_LATENCY_TYPE(type)                      (((type) == PSRAM_3_CLOCKS_RLATENCY) || \
                                                          ((type) == PSRAM_4_CLOCKS_RLATENCY) || \
                                                          ((type) == PSRAM_5_CLOCKS_RLATENCY) || \
                                                          ((type) == PSRAM_6_CLOCKS_RLATENCY) || \
                                                          ((type) == PSRAM_7_CLOCKS_RLATENCY))

#define IS_PSRAM_W_LATENCY_TYPE(type)                      (((type) == PSRAM_3_CLOCKS_WLATENCY) || \
                                                          ((type) == PSRAM_4_CLOCKS_WLATENCY) || \
                                                          ((type) == PSRAM_5_CLOCKS_WLATENCY) || \
                                                          ((type) == PSRAM_6_CLOCKS_WLATENCY) || \
                                                          ((type) == PSRAM_7_CLOCKS_WLATENCY))

void PSram_Ctrl_APMemory_Cfg_Latency(PSRAM_ID_Type id,
    PSRAM_RLatency_Type r_latency, PSRAM_WLatency_Type w_latency);

void PSram_Ctrl_Set_Output_Delay(PSRAM_ID_Type id);

#endif /* __BL808_PSRAM_CTRL_H__ */

