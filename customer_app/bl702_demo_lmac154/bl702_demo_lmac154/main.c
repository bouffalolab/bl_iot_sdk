#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <bl_gpio.h>

#include <easyflash.h>
#include <lmac154.h>


#if ( configUSE_TICK_HOOK != 0 )
void vApplicationTickHook( void )
{
#if defined(CFG_USB_CDC_ENABLE)
    extern void usb_cdc_monitor(void);
    usb_cdc_monitor();
#endif
}
#endif

void _cli_init(int fd_console)
{
#if defined(CFG_USB_CDC_ENABLE)
    extern void usb_cdc_start(int fd_console);
    usb_cdc_start(fd_console);
#endif

    /*Put CLI which needs to be init here*/
    easyflash_cli_init();
}

#if defined(CFG_BLE_ENABLE)
void ble_init(void)
{
    extern void ble_stack_start(void);
    ble_stack_start();
}
#endif

void proc_hellow_entry(void *pvParameters)
{
    uint8_t pin = 22;
    uint8_t output = 0;

    vTaskDelay(500);

    bl_gpio_enable_output(pin, 0, 0);
    bl_gpio_output_set(pin, output);

    while (1) {
        vTaskDelay(1000);

        output = !output;
        bl_gpio_output_set(pin, output);
        //printf("GPIO%d toggled\r\n", pin);
    }
    vTaskDelete(NULL);
}

void _dump_lib_info(void)
{
    puts("LMAC154 LIB Version: ");
    puts(lmac154_getLibVersion());
    puts("\r\n");
}

static void system_init(void)
{
    easyflash_init();
}

static void system_thread_init()
{
#if defined(CFG_BLE_ENABLE)
    ble_init();
#endif
}

void main()
{
    extern void lmac154_example_task(void *pvParameters);

    system_init();
    system_thread_init();

    puts("[OS] Starting proc_hellow_entry task...\r\n");
    xTaskCreate(proc_hellow_entry, (char*)"hellow", 512, NULL, 15, NULL);
    puts("[OS] Starting lmac154_example_task task...\r\n");
    xTaskCreate(lmac154_example_task, (char*)"lmac154", 512, NULL, 15, NULL);
}
