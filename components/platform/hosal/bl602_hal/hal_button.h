#ifndef __HAL_BUTTON_H__
#define __HAL_BUTTON_H__

void fdt_button_module_init(const void *fdt, int button_offset);
void hal_button_module_init(int pin,int short_press_end_ms,int long_press_end_ms,int longlong_press_ms);

#endif
