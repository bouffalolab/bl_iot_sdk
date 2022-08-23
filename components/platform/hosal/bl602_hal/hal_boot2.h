#ifndef __HAL_BOOT2_H__
#define __HAL_BOOT2_H__
#include <stdint.h>

typedef int (*fptr_Flash_Erase_t)(uint32_t startaddr,uint32_t endaddr);
typedef int (*fptr_Flash_Write_t)(uint32_t addr,uint8_t *data, uint32_t len);
typedef int (*fptr_Flash_Read_t) (uint32_t addr,uint8_t *data, uint32_t len);

typedef struct {
    uint8_t type;                           /*!< Partition entry type */
    uint8_t device;                         /*!< Partition entry device */
    uint8_t activeIndex;                    /*!< Partition entry active index */
    uint8_t name[9];                        /*!< Partition entry name */
    uint32_t Address[2];                    /*!< Partition entry start address */
    uint32_t maxLen[2];                     /*!< Partition entry max length */
    uint32_t len;                           /*!< Partition entry length */
    uint32_t age;                           /*!< Partition entry age */
} HALPartition_Entry_Config;

/**
 *  @brief Partition id type definition
 */
typedef enum {
    HAL_PT_ENTRY_FW_CPU0,                       /*!< Partition entry type:CPU0 firmware */
    HAL_PT_ENTRY_FW_CPU1,                       /*!< Partition entry type:CPU1 firmware */
    HAL_PT_ENTRY_MAX=16,                        /*!< Partition entry type:Max */
} HALPtTable_Entry_Type;

#define BOOT2_PARTITION_TYPE_FW     (0)

/**
 * @brief Error type definition
 */
typedef enum 
{
  HAL_SUCCESS  = 0, 
  HAL_ERROR   = 1,
} HAL_Err_Type;

typedef HAL_Err_Type (*HALpPtTable_Flash_Erase)(uint32_t startaddr,uint32_t endaddr);
typedef HAL_Err_Type (*HALpPtTable_Flash_Write)(uint32_t addr,uint8_t *data, uint32_t len);
typedef HAL_Err_Type (*HALpPtTable_Flash_Read) (uint32_t addr,uint8_t *data, uint32_t len);

void hal_boot2_set_ptable_opt(HALpPtTable_Flash_Erase erase, HALpPtTable_Flash_Write write);
int hal_boot2_partition_bus_addr_active(const char *name, uint32_t *addr, uint32_t *size);
int hal_boot2_partition_bus_addr_inactive(const char *name, uint32_t *addr, uint32_t *size);
int hal_boot2_partition_bus_addr(const char *name, uint32_t *addr0, uint32_t *addr1, uint32_t *size0, uint32_t *size1, int *active);
int hal_boot2_partition_addr_active(const char *name, uint32_t *addr, uint32_t *size);
int hal_boot2_partition_addr_inactive(const char *name, uint32_t *addr, uint32_t *size);
int hal_boot2_partition_addr(const char *name, uint32_t *addr0, uint32_t *addr1, uint32_t *size0, uint32_t *size1, int *active);
uint8_t hal_boot2_get_active_partition(void);
int hal_boot2_get_active_entries(int type, HALPartition_Entry_Config *ptEntry);
int hal_boot2_update_ptable(HALPartition_Entry_Config *ptEntry);
int hal_boot2_dump(void);
int hal_boot2_init(void);
void hal_update_mfg_ptable(void);

#endif
