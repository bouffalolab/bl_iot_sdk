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
#ifndef __TIME_STATICS__
#define _TIME_STATICS__

#include <stdint.h>
#include "bl_rtc.h"

#include "rv_hpm.h"

enum {
  TS_WANT_TO_SLEEP,
  TS_ALLOW_SLEEP_WIFI,
  TS_ALLOW_SLEEP_WIFI_DONE,
  TS_ALLOW_SLEEP_BL_LP,
  TS_WAKEUP_APP_START,
  TS_WAKEUP_APP_DONE,
  TS_WAKEUP_EXIT_TICKLESS,
  TS_WAKEUP_RF_DONE,
  TS_MAX,
};

extern uint64_t g_ts_record[TS_MAX][5];

#ifdef TICKLESS_DEBUG
#define TS_RECORD(t) if (unlikely(g_ts_record[t][0] == 0)) { \
  g_ts_record[t][0] = bl_rtc_get_counter(); \
  RV_HPM_L1_ICache_Miss_Stop_M(&g_ts_record[t][1], &g_ts_record[t][2]); \
  RV_HPM_Cycle_Get_M(&g_ts_record[t][3]); \
  RV_HPM_Instret_Get_M(&g_ts_record[t][4]); \
}
#else
#define TS_RECORD(x)
#endif

void time_static_record_dump(void);
#endif
