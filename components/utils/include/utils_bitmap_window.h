#include <stdint.h>

struct utils_bitmap_ctx {
    int ssn;
    int ssn_duration;
    union {
        uint8_t bytes[8];
        uint64_t map64;
    } bitmap;
};

int utils_bitmap_window_init(struct utils_bitmap_ctx *ctx, int ssn, int ssn_max);
int utils_bitmap_window_bit_set(struct utils_bitmap_ctx *ctx, int bit_pos);
uint64_t utils_bitmap_window_map_get(struct utils_bitmap_ctx *ctx);
int utils_bitmap_window_ssn_get(struct utils_bitmap_ctx *ctx);
int utils_bitmap_window_cli_init(void);
