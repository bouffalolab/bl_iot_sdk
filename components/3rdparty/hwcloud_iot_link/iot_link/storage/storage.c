#include "storage.h"

static const storage_device *s_device = NULL;
static uint32_t max_dev_num = 0;

int storage_dev_install(storage_device *dev, uint32_t max_num)
{
  uint32_t i = 0;
  if (dev != NULL && s_device == NULL) {
    for (i = 0; i < max_num; i++) {
      if (dev[i].init != NULL) {
        dev[i].init();
      }
    }

    s_device = dev;
    max_dev_num = max_num;
    return 0;
  }
  return -1;
}

int storage_dev_uninstall()
{
  if (s_device != NULL) {
    s_device = NULL;
    max_dev_num = 0;
    return 0;
  }
  return -1;
}

int storage_device_erase(uint32_t dev_id, uint32_t addr, uint32_t len)
{
  if (dev_id < max_dev_num && s_device != NULL && s_device[dev_id].erase != NULL) {
    return s_device[dev_id].erase(addr, len);
  }
  return -1;
}

int storage_device_erase_write(uint32_t dev_id, uint8_t *buf, uint32_t len, uint32_t addr)
{
  if (dev_id < max_dev_num && s_device != NULL && s_device[dev_id].erase_write != NULL) {
    return s_device[dev_id].erase_write(buf, len, addr);
  }
  return -1;
}

int storage_device_write(uint32_t dev_id, uint8_t *buf, uint32_t len, uint32_t addr)
{
  if (dev_id < max_dev_num && s_device != NULL && s_device[dev_id].write != NULL) {
    return s_device[dev_id].write(buf, len, addr);
  }
  return -1;
}

int storage_device_read(uint32_t dev_id, uint8_t *buf, uint32_t len, uint32_t addr)
{

  if (dev_id < max_dev_num && s_device != NULL && s_device[dev_id].read != NULL) {
    return s_device[dev_id].read(buf, len, addr);
  }
  return -1;
}
