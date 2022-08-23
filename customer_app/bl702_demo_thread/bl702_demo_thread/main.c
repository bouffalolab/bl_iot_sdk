#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

#include <main.h>

void vApplicationTickHook( void )
{
#if defined(CFG_USB_CDC_ENABLE)
    extern void usb_cdc_monitor(void);
    usb_cdc_monitor();
#endif
}

void vApplicationSleep( TickType_t xExpectedIdleTime )
{
    
}

void otrAppProcess(ot_system_event_t sevent) 
{
    /** for application code */
    /** Note,   NO heavy execution, no delay and semaphore pending here.
     *          do NOT stop/suspend this task */

}

#ifdef SYS_AOS_CLI_ENABLE

void _cli_init(int fd_console)
{
    ot_uartSetFd(fd_console);

#if defined(CFG_USB_CDC_ENABLE)
    extern void usb_cdc_start(int fd_console);
    usb_cdc_start(fd_console);
    printf("_cli_init = %d\r\n", fd_console);
#endif
}

#endif

int main(int argc, char *argv[])
{
#if defined(CFG_BLE_ENABLE)
    ble_stack_start();
#endif

    otrStart();
#ifdef CONFIG_OTDEMO
    app_task();
#endif

    return 0;
}
