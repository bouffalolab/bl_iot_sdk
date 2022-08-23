#ifndef __HAL_HBNRAM_H__
#define __HAL_HBNRAM_H__

typedef struct _hbnram_handle {
    uint8_t *block_addr;
    int read_idex;
    int write_idex;
    int size;
} hbnram_handle_t;

int hal_hbnram_init(void);
int hal_hbnram_deinit(void);
int hal_hbnram_alloc(const char *key, int len);
int hal_hbnram_buffer_set(const char *key, uint8_t *buf, int length);
int hal_hbnram_buffer_get(const char *key, uint8_t *buf, int length);
int hal_hbnram_handle_get_fromkey(const char *key, hbnram_handle_t *handle);
int hal_hbnram_copy_from_stream(hbnram_handle_t *handle, uint8_t *buf, int len);
int hal_hbnram_copy_to_stream(hbnram_handle_t *handle, uint8_t *buf, int len);

void print_mem_map(void);

#endif
