#include "partition.h"
#include "storage.h"

#include <stdio.h>
#include <link_log.h>

static const storage_partition *s_partition = NULL;
static int max_part_num = 0;
int storage_partition_init(storage_partition *part, int32_t max_num)
{
  if (part != NULL && s_partition == NULL) {
    s_partition = part;
    max_part_num = max_num;
    return 0;
  }
  return -1;
}

int storage_partition_deinit()
{
  if (s_partition != NULL) {
    s_partition = NULL;
    max_part_num = 0;
    return 0;
  }
  return -1;
}

int storage_partition_read(int part_id, uint8_t *buf, uint32_t len, uint32_t offset)
{
  const storage_partition *sp;

  if (part_id >= max_part_num || buf == NULL)
    return -1;

  sp = &s_partition[part_id];
  if ((offset + len) > (sp->start_addr + sp->size)) {
    LINK_LOG_DEBUG("%s:invalid args!\n", __func__);
    return -1;
  }

  return storage_device_read(sp->dev_id, buf, len, sp->start_addr + offset);
}

int storage_partition_write(int part_id, uint8_t *buf, uint32_t len, uint32_t offset)
{
  const storage_partition *sp;

  if (part_id >= max_part_num || buf == NULL)
    return -1;

  sp = &s_partition[part_id];
  if ((offset + len) > (sp->start_addr + sp->size)) {
    LINK_LOG_DEBUG("%s:invalid args!\n", __func__);
    return -1;
  }

  return storage_device_write(sp->dev_id, buf, len, sp->start_addr + offset);
}

int storage_partition_erase_write(int part_id, uint8_t *buf, uint32_t len, uint32_t offset)
{
  const storage_partition *sp;

  if (part_id >= max_part_num || buf == NULL)
    return -1;

  sp = &s_partition[part_id];
  if ((offset + len) > (sp->start_addr + sp->size)){
    LINK_LOG_DEBUG("%s:invalid args!\n", __func__);
    return -1;
  }
  return storage_device_erase_write(sp->dev_id, buf, len, sp->start_addr + offset);
}

int storage_partition_erase(int part_id, uint32_t offset, uint32_t len)
{
  const storage_partition *sp;

  if (part_id >= max_part_num)
    return -1;

  sp = &s_partition[part_id];
  if ((offset + len) > (sp->start_addr + sp->size)){
    LINK_LOG_DEBUG("%s:invalid args!\n", __func__);
    return -1;
  }

  return storage_device_erase(sp->dev_id, sp->start_addr + offset, len);
}
