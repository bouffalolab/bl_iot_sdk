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

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "wifi_hosal.h"

/****************************************************************************
 * Definition
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: wifi_hosal_efuse_read_mac
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/

int wifi_hosal_efuse_read_mac(uint8_t mac[6])
{
  return g_wifi_hosal_funcs.efuse_read_mac(mac);
}

/****************************************************************************
 * Name: wifi_hosal_pds_rf_turnon
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/

int wifi_hosal_rf_turn_on(void *arg)
{
  return g_wifi_hosal_funcs.rf_turn_on(arg);
}

/****************************************************************************
 * Name: wifi_hosal_pds_rf_turnoff
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/

int wifi_hosal_rf_turn_off(void *arg)
{
  return g_wifi_hosal_funcs.rf_turn_off(arg);
}

/****************************************************************************
 * Name: wifi_hosal_adc_device_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/

hosal_adc_dev_t* wifi_hosal_adc_device_get(void)
{
  return g_wifi_hosal_funcs.adc_device_get();
}


/****************************************************************************
 * Name: wifi_hosal_adc_tsen_value_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/

int wifi_hosal_adc_tsen_value_get(hosal_adc_dev_t *adc)
{
  return g_wifi_hosal_funcs.adc_tsen_value_get(adc);
}

/****************************************************************************
 * Name: wifi_hosal_adc_tsen_value_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/
int wifi_hosal_pm_init(void)
{
  return g_wifi_hosal_funcs.pm_init();
}

/****************************************************************************
 * Name: wifi_hosal_adc_tsen_value_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/
int wifi_hosal_pm_event_register(enum PM_EVEMT event, uint32_t code, uint32_t cap_bit, uint16_t pirority, bl_pm_cb_t ops, void *arg, enum PM_EVENT_ABLE enable)
{
  return g_wifi_hosal_funcs.pm_event_register(event, code, cap_bit, pirority, ops, arg, enable);
}

/****************************************************************************
 * Name: wifi_hosal_adc_tsen_value_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/
int wifi_hosal_pm_deinit(void)
{
  return g_wifi_hosal_funcs.pm_deinit();
}

/****************************************************************************
 * Name: wifi_hosal_adc_tsen_value_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/
int wifi_hosal_pm_state_run(void)
{
  return g_wifi_hosal_funcs.pm_state_run();
}

/****************************************************************************
 * Name: wifi_hosal_adc_tsen_value_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/
int wifi_hosal_pm_capacity_set(enum PM_LEVEL level)
{
  return g_wifi_hosal_funcs.pm_capacity_set(level);
}

/****************************************************************************
 * Name: wifi_hosal_adc_tsen_value_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/
int wifi_hosal_pm_post_event(enum PM_EVEMT event, uint32_t code, uint32_t *retval)
{
  return g_wifi_hosal_funcs.pm_post_event(event, code, retval);
}

/****************************************************************************
 * Name: wifi_hosal_adc_tsen_value_get
 *
 * Description:
 *   Disable irq num
 *
 * Input Parameters:
 *
 * Returned Value:
 *
 ****************************************************************************/
int wifi_hosal_pm_event_switch(enum PM_EVEMT event, uint32_t code, enum PM_EVENT_ABLE enable)
{
  return g_wifi_hosal_funcs.pm_event_switch(event, code, enable);
}




#ifdef __cplusplus
}
#endif

