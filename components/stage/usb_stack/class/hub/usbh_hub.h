#ifndef _USBH_HUB_H_
#define _USBH_HUB_H_

#include "usb_hub.h"

#define USBH_HUB_MAX_PORTS 4
/* Maximum size of an interrupt IN transfer */
#define USBH_HUB_INTIN_BUFSIZE ((USBH_HUB_MAX_PORTS + 8) >> 3)

extern usb_slist_t hub_class_head;

#ifdef __cplusplus
extern "C" {
#endif
int usbh_hub_initialize(void);
#ifdef __cplusplus
}
#endif

#endif /* _USBH_HUB_H_ */
