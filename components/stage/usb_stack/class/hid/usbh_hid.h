#ifndef _USBH_HID_H
#define _USBH_HID_H

#include "usb_hid.h"

struct usbh_hid {
    struct usbh_hubport *hport;

    uint8_t intf; /* interface number */
    uint8_t minor;
    usbh_epinfo_t intin;  /* INTR IN endpoint */
    usbh_epinfo_t intout; /* INTR OUT endpoint */
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_hid_set_idle(struct usbh_hid *hid_class, uint8_t report_id, uint8_t duration);
int usbh_hid_get_idle(struct usbh_hid *hid_class, uint8_t *buffer);

#ifdef __cplusplus
}
#endif

#endif
