#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <utils_bitmap_window.h>

int utils_bitmap_window_init(struct utils_bitmap_ctx *ctx, int ssn, int ssn_max)
{
    memset(ctx, 0, sizeof(struct utils_bitmap_ctx));
    ctx->ssn = ssn;
    ctx->ssn_duration = ssn_max + 1;//ssn start from 0

    return 0;
}

int utils_bitmap_window_bit_set(struct utils_bitmap_ctx *ctx, int bit_pos)
{
    int i;
    int pos_offset;

    if (bit_pos < ctx->ssn) {
        /*failed case*/
        if (ctx->ssn_duration - ctx->ssn + bit_pos + 1 > sizeof(ctx->bitmap) * 8) {
            printf("small ssn %d\r\n", bit_pos);
            return -INT_MAX;
        }
    }
    pos_offset = bit_pos + ctx->ssn_duration - ctx->ssn;
    if (pos_offset >= ctx->ssn_duration) {
        pos_offset -= ctx->ssn_duration;
    }

    if (ctx->bitmap.map64 & (1 << pos_offset)) {
        printf("Dup bit_pos %d with pos_offset %d\r\n", bit_pos, pos_offset);
        return -bit_pos;
    }
    ctx->bitmap.map64 |= (1 << pos_offset);//TODO use bytearray

    for (i = 0; i < sizeof(ctx->bitmap.bytes) * 8; i++) {
        if (ctx->bitmap.map64 & 0x1) {
            ctx->bitmap.map64 >>= 1;
            ctx->ssn += 1;
            if (ctx->ssn == ctx->ssn_duration) {
                ctx->ssn = 0;
            }
        }
    }
    return pos_offset;
}

uint64_t utils_bitmap_window_map_get(struct utils_bitmap_ctx *ctx)
{
    return ctx->bitmap.map64;
}

int utils_bitmap_window_ssn_get(struct utils_bitmap_ctx *ctx)
{
    return ctx->ssn;
}
