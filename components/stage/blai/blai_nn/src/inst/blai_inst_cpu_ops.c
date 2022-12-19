#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "bl808_common.h"
#include "blai_core.h"
#include "blai_def_internal.h"
#include "riscv_nn_types.h"
#include "blai_riscv_nnfunctions.h"
#include "blai_inst_util.h"

//#include "riscv_nnfunctions.h"
//#include "riscv_nnsupportfunctions.h"

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

fixed_point_t MEM_RW(int write, int addr, fixed_point_t in, int mux, fixed_point_t* DATA_buf, int patch_size) {
    fixed_point_t output = 0;
    int offset = mux * patch_size;

    if (write) DATA_buf[addr + offset] = in;
    else output = DATA_buf[addr + offset];

    return output;
}

float MEM_RW_F32(int write, int addr, float in, int mux, fixed_point_t* DATA_buf, int patch_size) {
	float output = 0;
	int offset = mux * patch_size;
    float* MEM = (float*)(DATA_buf + offset);

	if (write) MEM[addr] = in;
	else output = MEM[addr];

	return output;
}

void fetch_data(struct cpu_inst_layer_t* l, fixed_point_t* data_in, int data_index, int SRAM_in, int win, int hin, fixed_point_t padding, fixed_point_t* DATA_buf, int patch_size) {

    int dila = l->dilation - 1;
    int step = (l->size - 1) / 2;
    int cnt = 0;

    for (int i = -step; i < step + 1; i++) {
        for (int j = -step; j < step + 1; j++) {
            if (i < 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] =  padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index - (l->w * (abs(i) + dila) + abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i < 0 && j == 0) {
                if (hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index - (l->w * (abs(i) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i < 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index - (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index - (abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j == 0) {
                data_in[cnt] = MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j > 0) {
                if (win >= l->w - (j + dila))
                    data_in[cnt] =  padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index + (abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index + (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j == 0) {
                if (hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index + (l->w * (abs(i) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index + (l->w * (abs(i) + dila) + (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else {
                printf("fetch data fail!\n");
            }
            cnt++;
        }
    }
}

void fetch_data_tflite(struct cpu_inst_layer_t* l, int32_t* data_in, int input_offset, int data_index, int SRAM_in, int win, int hin, int padding, fixed_point_t* DATA_buf, int patch_size) {

    int dila = (l->dilation == 0) ? 0 : l->dilation - 1;

    int step = (l->size - 1) / 2;
    int cnt = 0;
    for (int i = -step; i < step + 1; i++) {
        for (int j = -step; j < step + 1; j++) {
            if (i < 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index - (l->w * (abs(i) + dila) + abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i < 0 && j == 0) {
                if (hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index - (l->w * (abs(i) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i < 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index - (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index - (abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j == 0) {
                data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j > 0) {
                if (win >= l->w - (j + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index + (abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index + (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j == 0) {
                if (hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index + (l->w * (abs(i) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index + (l->w * (abs(i) + dila) + (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else {
                printf("fetch data fail!\n");
            }
            cnt++;
        }
    }
}

void fetch_data_even(struct cpu_inst_layer_t* l, fixed_point_t* data_in, int data_index, int SRAM_in, int win, int hin, fixed_point_t padding, fixed_point_t* DATA_buf, int patch_size) {

    int dila = l->dilation - 1;
    int step = (l->size) / 2;
    int cnt = 0;

    for (int i = 0; i < step + 1; i++) {
        for (int j = 0; j < step + 1; j++) {
            if (i < 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index - (l->w * (abs(i) + dila) + abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i < 0 && j == 0) {
                if (hin <= (abs(i) - 1 + dila))
                    data_in[cnt] =  padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index - (l->w * (abs(i) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i < 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index - (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index - (abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j == 0) {
                data_in[cnt] = MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j > 0) {
                if (win >= l->w - (j + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index + (abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index + (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j == 0) {
                if (hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index + (l->w * (abs(i) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = MEM_RW(0, data_index + (l->w * (abs(i) + dila) + (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else {
                printf("fetch data fail!\n");
            }
            cnt++;
        }
    }
}

void fetch_data_even_tflite(struct cpu_inst_layer_t* l, int32_t* data_in, int input_offset, int data_index, int SRAM_in, int win, int hin, int padding, fixed_point_t* DATA_buf, int patch_size) {

    int dila = l->dilation - 1;
    int step = (l->size) / 2;
    int cnt = 0;

    for (int i = 0; i < step + 1; i++) {
        for (int j = 0; j < step + 1; j++) {
            if (i < 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index - (l->w * (abs(i) + dila) + abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i < 0 && j == 0) {
                if (hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index - (l->w * (abs(i) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i < 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index - (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index - (abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j == 0) {
                data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i == 0 && j > 0) {
                if (win >= l->w - (j + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index + (abs(j) + dila) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index + (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j == 0) {
                if (hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index + (l->w * (abs(i) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else if (i > 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)MEM_RW(0, data_index + (l->w * (abs(i) + dila) + (abs(j) + dila)) * l->c, 0, SRAM_in, DATA_buf, patch_size);
            } else {
                printf("fetch data fail!\n");
            }
            cnt++;
        }
    }
}

void fetch_data_i8(struct cpu_inst_layer_t* l, fixed_point_t* data_in, int data_index, int win, int hin, fixed_point_t padding) {
    int dila = l->dilation - 1;
    int step = (l->size - 1) / 2;
    int cnt = 0;

    for (int i = -step; i < step + 1; i++) {
        for (int j = -step; j < step + 1; j++) {
            if (i < 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] =  padding;
                else
                    data_in[cnt] =  l->input_i8[0][ data_index - (l->w * (abs(i) + dila) + abs(j) + dila) * l->c];
            } else if (i < 0 && j == 0) {
                if (hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = l->input_i8[0][ data_index - (l->w * (abs(i) + dila)) * l->c];
            } else if (i < 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = l->input_i8[0][ data_index - (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c];
            } else if (i == 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = l->input_i8[0][ data_index - (abs(j) + dila) * l->c];
            } else if (i == 0 && j == 0) {
                data_in[cnt] =l->input_i8[0][ data_index];
            } else if (i == 0 && j > 0) {
                if (win >= l->w - (j + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = l->input_i8[0][ data_index + (abs(j) + dila) * l->c];
            } else if (i > 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = l->input_i8[0][ data_index + (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c];
            } else if (i > 0 && j == 0) {
                if (hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = l->input_i8[0][data_index + (l->w * (abs(i) + dila)) * l->c];
            } else if (i > 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = l->input_i8[0][ data_index + (l->w * (abs(i) + dila) + (abs(j) + dila)) * l->c];
            } else {
                printf("fetch data fail!\n");
            }
            cnt++;
        }
    }
}

void fetch_data_tflite_i8(struct cpu_inst_layer_t* l, int32_t* data_in, int input_offset, int data_index, int win, int hin, int padding) {
    int dila = (l->dilation == 0) ? 0 : l->dilation - 1;
    int step = (l->size - 1) / 2;
    int cnt = 0;
    for (int i = -step; i < step + 1; i++) {
        for (int j = -step; j < step + 1; j++) {
            if (i < 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index - (l->w * (abs(i) + dila) + abs(j) + dila) * l->c];
            } else if (i < 0 && j == 0) {
                if (hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index - (l->w * (abs(i) + dila)) * l->c];
            } else if (i < 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin <= (abs(i) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index - (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c];
            } else if (i == 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index - (abs(j) + dila) * l->c];
            } else if (i == 0 && j == 0) {
                data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index];
            } else if (i == 0 && j > 0) {
                if (win >= l->w - (j + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index + (abs(j) + dila) * l->c];
            } else if (i > 0 && j < 0) {
                if (win <= (abs(j) - 1 + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index + (l->w * (abs(i) + dila) - (abs(j) + dila)) * l->c];
            } else if (i > 0 && j == 0) {
                if (hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index + (l->w * (abs(i) + dila)) * l->c];
            } else if (i > 0 && j > 0) {
                if (win >= l->w - (j + dila) || hin >= l->h - (i + dila))
                    data_in[cnt] = padding;
                else
                    data_in[cnt] = input_offset + (uint8_t)l->input_i8[0][ data_index + (l->w * (abs(i) + dila) + (abs(j) + dila)) * l->c];
            } else {
                BL_LOGE("fetch data fail!\n");
            }
            cnt++;
        }
    }
}

int32_t PE_CONV(fixed_point_t* data_in, fixed_point_t* weights, int size, int unsgn) {
    int32_t output = 0;

    if (unsgn) {
        for (int i = 0; i < size * size; i++) {
            output += ((uint8_t)data_in[i]) * weights[i];
        }
    }
    else {
        for (int i = 0; i < size * size; i++) {
            output += data_in[i] * weights[i];
        }
    }
    return output;
}

int32_t PE_CONV_tflite(int32_t* data_in, int32_t* weights, int size, int l_current) {
    int32_t output = 0;

    for (int i = 0; i < size * size; i++) {
        output += data_in[i] * weights[i];
    }

    return output;
}

int32_t BL_Add(int32_t a, int32_t b) {
    return a + b;
}


int32_t BL_BitAnd(int32_t a, int32_t b) {
    return a & b;
}

int32_t BL_BitNot(int32_t a) {
    return ~a;
}

int32_t BL_ShiftRight(int32_t a, int offset) {
    return a >> offset;
}

int32_t BL_MaskIfNonZero(int32_t a) {
    const int32_t zero = 0;
    return a ? BL_BitNot(zero) : zero;
}

int32_t BL_MaskIfLessThan(int32_t a, int32_t b) {
    return BL_MaskIfNonZero(a < b);
}

int32_t BL_MaskIfGreaterThan(int32_t a, int32_t b) {
    return BL_MaskIfNonZero(a > b);
}

int32_t BL_RoundingDivideByPOT(int32_t x, int exponent) {
    CHECK_PARAM(exponent >= 0);
    CHECK_PARAM(exponent <= 31);
    const int32_t mask = ((1ll << exponent) - 1);
    const int32_t zero = 0;
    const int32_t one = 1;
    const int32_t remainder = BL_BitAnd(x, mask);
    const int32_t threshold =
        BL_Add(BL_ShiftRight(mask, 1), BL_BitAnd(BL_MaskIfLessThan(x, zero), one));
    return BL_Add(BL_ShiftRight(x, exponent),
        BL_BitAnd(BL_MaskIfGreaterThan(remainder, threshold), one));
}

int32_t BL_SaturatingRoundingDoublingHighMul(int32_t a, int32_t b) {
    bool overflow = (a == b && a == INT32_MIN);
    int64_t a_64 = a;
    int64_t b_64 = b;
    int64_t ab_64 = a_64 * b_64;
    int32_t nudge = ab_64 >= 0 ? (1 << 30) : (1 - (1 << 30));
    int32_t ab_x2_high32 = (int32_t) ((ab_64 + nudge) >> 31);
    ab_x2_high32 = (ab_x2_high32 < 0) ? ab_x2_high32 + 1 : ab_x2_high32;

    return overflow ? INT32_MAX : ab_x2_high32;
}

int32_t BL_MultiplyByQuantizedMultiplier(int32_t x, int32_t quantized_multiplier, int shift) {
    int left_shift = shift > 0 ? shift : 0;
    int right_shift = shift > 0 ? 0 : -shift;

    return BL_RoundingDivideByPOT(BL_SaturatingRoundingDoublingHighMul(x * (1 << left_shift), quantized_multiplier), right_shift);
}

int32_t BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(
    int32_t x, int32_t quantized_multiplier, int left_shift) {

    return BL_RoundingDivideByPOT(
        BL_SaturatingRoundingDoublingHighMul(x, quantized_multiplier), -left_shift);
}

void forward_CONVOLUTIONAL(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current)
{
    fixed_point_t *weights = (fixed_point_t*)BLAI_MALLOC(l->size * l->size*sizeof(fixed_point_t));
    fixed_point_t *data_in = (fixed_point_t*)BLAI_MALLOC(l->size * l->size*sizeof(fixed_point_t));
    int32_t bias = 0;
    int32_t pass_data = 0;
    fixed_point_t pass_data_8;
    int padding = 0;

    for (int outin = 0; outin < l->out_c; outin++) {
        int c_start = (l->groups == 1) ? 0 : (outin / (l->out_c / l->groups)) * (l->c / l->groups);
        int c_end = (l->groups == 1) ? l->c : (1 + (outin / (l->out_c / l->groups))) * (l->c / l->groups);
        for (int hin = 0; hin < l->h; hin += l->stride) {
            for (int win = 0; win < l->w; win += l->stride) {
                pass_data = 0;
                for (int cin = c_start; cin < c_end; cin++) {
                    int data_index = hin * l->w * l->c + win * l->c + cin;
                    if (net->use_npu_accel)
                        fetch_data_i8(l, data_in, data_index, win, hin, padding);
                    else
                        fetch_data(l, data_in, data_index, l->in_layer1_mem, win, hin, padding, DATA_buf, net->patch_size);

                    for (int wt = 0; wt < l->size * l->size; wt++) {
                        int w_index = outin * (l->c / l->groups) * l->size * l->size + (cin - c_start) * l->size * l->size + wt;
                        weights[wt] = l->weights[w_index];
                    }

                    int64_t pass_data_64 = (int64_t)pass_data + (int64_t)PE_CONV(data_in, weights, l->size, (l_current == 0 && net->unsign_input));
                    pass_data = (pass_data_64 > INT32_MAX) ? INT32_MAX : (pass_data_64 < INT32_MIN) ? INT32_MIN : pass_data_64;
                }
                //S-format
                int falpha = (l->activation == LEAKY) ? 9 : 0;
                int f_in = l->fdata + l->fweight;
                int f_bias_out = l->fbias - l->fdata - l->fweight;

                bias = fixed8_to_fixed32(l->biases[outin], f_bias_out);
                pass_data += bias;

                if (l->activation == LINEAR)
                    pass_data = pass_data;
                else if (l->activation == LEAKY)
                    pass_data = PE_LEAKY(pass_data);
                else if (l->activation == RELU)
                    pass_data = PE_RELU(pass_data);
                else if (l->activation == RELU6)
                    pass_data = PE_RELU6(pass_data, f_in);

                falpha = (l->activation == LEAKY && pass_data < 0) ? 9 : 0;
                int ftotal = l->fdata + l->fweight + falpha - l->fout;

                pass_data_8 = (l->activation == MISH && pass_data < 0) ? PE_MISH(pass_data, f_in, l->fout) : fixed32_to_fixed8(pass_data, ftotal);

                int out_index = (hin / l->stride) * l->out_w * l->out_c + (win / l->stride) * l->out_c + outin;

                if (net->use_npu_accel)
                    l->output_i8[out_index] = pass_data_8;
                else
                    MEM_RW(1, out_index, pass_data_8, l->out_layer_mem, DATA_buf, net->patch_size);

            }
        }
    }

    BLAI_FREE(weights);
    BLAI_FREE(data_in);
}

void forward_DEPTHWISE_CONVOLUTIONAL_tflite_nmsis(struct blai_net_info_t *net, struct cpu_inst_layer_t *l, fixed_point_t* DATA_buf, int l_current) {
    //param assignment
    int size_x = (l->size_x > 0) ? l->size_x : l->size;
    int size_y = (l->size_y > 0) ? l->size_y : l->size;
    nmsis_nn_dims input_dims = { 1, l->h, l->w, l->c };
    nmsis_nn_dims filter_dims = { l->out_c, size_y, size_x, l->c };
    nmsis_nn_dims bias_dims = { 1, 1, 1, l->out_c };
    nmsis_nn_dims output_dims = { 1, l->out_h, l->out_w, l->out_c };

    int32_t ctx_size = riscv_convolve_s8_get_buffer_size(&input_dims, &filter_dims);
    int8_t* temp_buffer = NULL;//(q7_t*)xcalloc(ctx_size, sizeof(q7_t));
    nmsis_nn_context ctx = { temp_buffer, 0 };

    uint8_t tflite_padding_x = l->padding_x;
    uint8_t tflite_padding_y = l->padding_y;

    int8_t stride_x = (l->stride_x > 0) ? l->stride_x : l->stride;
    int8_t stride_y = (l->stride_y > 0) ? l->stride_y : l->stride;
    nmsis_nn_tile stride = { stride_x, stride_y }, padding = { tflite_padding_x, tflite_padding_y }, dilation = { l->dilation, l->dilation };
    nmsis_nn_activation activation = { l->quantized_activation_min, l->quantized_activation_max };

    int32_t ch_mult = 1;
    nmsis_nn_dw_conv_params dw_conv_params = { -l->tf_input1_offset, -l->tf_input2_offset, l->tf_output_offset, ch_mult, stride, padding, dilation, activation };


    int32_t* multiplier = (int32_t*)BLAI_MALLOC(output_dims.c * sizeof(int));
    int32_t* shift = (int32_t*)BLAI_MALLOC(output_dims.c * sizeof(int));
    for (int i = 0; i < output_dims.c; i++) {
        multiplier[i] = l->tf_output_multiplier;
        shift[i] = l->tf_output_shift;
    }

    nmsis_nn_per_channel_quant_params quant_params = { multiplier, shift };
    uint16_t ksize = size_x * size_y;
    bool SRAM_MODE = false;
    uint8_t* filter_SRAM;
    int32_t* bias_SRAM;
    uint8_t* input_SRAM;
    //uint8_t* output_SRAM;

    if(SRAM_MODE){
        filter_SRAM = (uint8_t*)BLAI_MALLOC(l->out_c * l->c * ksize / l->groups * sizeof(uint8_t));
        memcpy(filter_SRAM, l->weights, l->out_c * l->c * ksize / l->groups);
        bias_SRAM = (int32_t*)BLAI_MALLOC(l->out_c * sizeof(int32_t));
        memcpy(bias_SRAM, l->biases, l->out_c * 4);
        BL_LOGD("mem:%d\r\n", l->c * l->w * l->h);
        input_SRAM = (uint8_t*)BLAI_MALLOC(l->c * l->w * l->h);
        memcpy(input_SRAM, MEM_PTR(l->in_layer1_mem, DATA_buf, net->patch_size), l->c * l->w * l->h);
        //output_SRAM = (uint8_t*)BLAI_MALLOC(l->out_c * l->out_w * l->out_h);

        const uint8_t* input_data = (uint8_t*)input_SRAM;
        uint8_t* output_data = (uint8_t*)MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size);//(uint8_t*)output_SRAM;
        int32_t* bias_data = bias_SRAM;
        uint8_t* filter_data = (uint8_t*)filter_SRAM;

        riscv_depthwise_conv_u8(&ctx, &dw_conv_params, &quant_params, &input_dims, input_data, &filter_dims, filter_data, &bias_dims, bias_data, &output_dims, output_data);
        //memcpy(MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size), output_SRAM, l->out_c * l->out_w * l->out_h);
    }
    else{
        const uint8_t* input_data = (uint8_t*)MEM_PTR(l->in_layer1_mem, DATA_buf, net->patch_size);
        uint8_t* output_data = (uint8_t*)MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size);
        int32_t* bias_data = l->biases;
        uint8_t* filter_data = (uint8_t*)l->weights;

        riscv_depthwise_conv_u8(&ctx, &dw_conv_params, &quant_params, &input_dims, input_data, &filter_dims, filter_data, &bias_dims, bias_data, &output_dims, output_data);
    }
    BLAI_FREE(multiplier);
    BLAI_FREE(shift);
    if(SRAM_MODE){
        BLAI_FREE(filter_SRAM);
        BLAI_FREE(bias_SRAM);
        BLAI_FREE(input_SRAM);
        //BLAI_FREE(output_SRAM);
    }
}

void forward_CONVOLUTIONAL_tflite_nmsis(struct blai_net_info_t *net, struct cpu_inst_layer_t *l, fixed_point_t* DATA_buf, int l_current) {
    //param assignment
    int size_x = (l->size_x > 0) ? l->size_x : l->size;
    int size_y = (l->size_y > 0) ? l->size_y : l->size;
    nmsis_nn_dims input_dims = { 1, l->h, l->w, l->c };
    nmsis_nn_dims filter_dims = { l->out_c, size_y, size_x, l->c };
    nmsis_nn_dims bias_dims = { 1, 1, 1, l->out_c };
    nmsis_nn_dims output_dims = { 1, l->out_h, l->out_w, l->out_c };

    int32_t ctx_size = riscv_convolve_s8_get_buffer_size(&input_dims, &filter_dims);
    int8_t* temp_buffer = NULL;//(q7_t*)xcalloc(ctx_size, sizeof(q7_t));
    nmsis_nn_context ctx = { temp_buffer, 0 };

    uint8_t tflite_padding_x = l->padding_x;
    uint8_t tflite_padding_y = l->padding_y;

    int8_t stride_x = (l->stride_x > 0) ? l->stride_x : l->stride;
    int8_t stride_y = (l->stride_y > 0) ? l->stride_y : l->stride;
    nmsis_nn_tile stride = { stride_x, stride_y }, padding = { tflite_padding_x, tflite_padding_y }, dilation = { l->dilation, l->dilation };
    nmsis_nn_activation activation = { l->quantized_activation_min, l->quantized_activation_max };
    nmsis_nn_conv_params conv_params = { -l->tf_input1_offset, -l->tf_input2_offset, l->tf_output_offset, stride, padding, dilation, activation };

    int32_t* multiplier = (int32_t*)BLAI_MALLOC(output_dims.c * sizeof(int));
    int32_t* shift = (int32_t*)BLAI_MALLOC(output_dims.c * sizeof(int));
    for (int i = 0; i < output_dims.c; i++) {
        multiplier[i] = l->tf_output_multiplier;
        shift[i] = l->tf_output_shift;
    }
  
    nmsis_nn_per_channel_quant_params quant_params = { multiplier, shift };
    uint16_t ksize = size_x * size_y;
    bool SRAM_MODE = false;
    uint8_t* filter_SRAM;
    int32_t* bias_SRAM;
    uint8_t* input_SRAM;
    //uint8_t* output_SRAM;

    if(SRAM_MODE){
        filter_SRAM = (uint8_t*)BLAI_MALLOC(l->out_c * l->c * ksize / l->groups * sizeof(uint8_t));
        memcpy(filter_SRAM, l->weights, l->out_c * l->c * ksize / l->groups);
        bias_SRAM = (int32_t*)BLAI_MALLOC(l->out_c * sizeof(int32_t));
        memcpy(bias_SRAM, l->biases, l->out_c * 4);
        input_SRAM = (uint8_t*)BLAI_MALLOC(l->c * l->w * l->h);
        memcpy(input_SRAM, MEM_PTR(l->in_layer1_mem, DATA_buf, net->patch_size), l->c * l->w * l->h);
        //output_SRAM = (uint8_t*)BLAI_MALLOC(l->out_c * l->out_w * l->out_h);
        const uint8_t* input_data = (uint8_t*)input_SRAM;
        uint8_t* output_data = (uint8_t*)MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size);//(uint8_t*)output_SRAM;
        int32_t* bias_data = bias_SRAM;
        uint8_t* filter_data = (uint8_t*)filter_SRAM;

        riscv_convolve_u8(&ctx, &conv_params, &quant_params, &input_dims, input_data, &filter_dims, filter_data, &bias_dims, bias_data, &output_dims, output_data);
        //memcpy(MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size), output_SRAM, l->out_c * l->out_w * l->out_h);
    }
    else{
        const uint8_t* input_data = (uint8_t*)MEM_PTR(l->in_layer1_mem, DATA_buf, net->patch_size);
        uint8_t* output_data = (uint8_t*)MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size);
        int32_t* bias_data = l->biases;
        uint8_t* filter_data = (uint8_t*)l->weights;

        riscv_convolve_u8(&ctx, &conv_params, &quant_params, &input_dims, input_data, &filter_dims, filter_data, &bias_dims, bias_data, &output_dims, output_data);
    }

    BLAI_FREE(multiplier);
    BLAI_FREE(shift);

    if(SRAM_MODE){
        BLAI_FREE(filter_SRAM);
        BLAI_FREE(bias_SRAM);
        BLAI_FREE(input_SRAM);
        //BLAI_FREE(output_SRAM);
    }

}

void forward_MAXPOOL_tflite_nmsis(struct blai_net_info_t *net, struct cpu_inst_layer_t *l, fixed_point_t* DATA_buf, int l_current) {

    //param assignment
    nmsis_nn_dims input_dims = { 1, l->h, l->w, l->c };
    nmsis_nn_dims filter_dims = { l->out_c, l->size, l->size, l->c };
    nmsis_nn_dims bias_dims = { 1, 1, 1, l->out_c };
    nmsis_nn_dims output_dims = { 1, l->out_h, l->out_w, l->out_c };

    nmsis_nn_context ctx = { 0, 0 };


    nmsis_nn_tile stride = { l->stride, l->stride }, padding = { l->padding_x, l->padding_y };
    nmsis_nn_activation activation = { 0, 255 };

    nmsis_nn_pool_params pool_params = { stride, padding, activation };

    const uint8_t* input_data = (uint8_t*)MEM_PTR(l->in_layer1_mem, DATA_buf, net->patch_size);
    uint8_t* output_data = (uint8_t*)MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size);

    riscv_max_pool_u8(&ctx, &pool_params, &input_dims, input_data, &filter_dims, &output_dims, output_data);
}


void forward_CONVOLUTIONAL_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t* weights = (int32_t*)BLAI_MALLOC(l->size * l->size*sizeof(int32_t));
    int32_t* data_in = (int32_t*)BLAI_MALLOC(l->size * l->size*sizeof(int32_t));
    int32_t pass_data = 0;
    int w_start = (l->stride == 2) ? 1 : 0;
    int h_start = (l->stride == 2) ? 1 : 0;

    for (int outin = 0; outin < l->out_c; outin++) {
        int c_start = (l->groups == 1) ? 0 : (outin / (l->out_c / l->groups)) * (l->c / l->groups);
        int c_end = (l->groups == 1) ? l->c : (1 + (outin / (l->out_c / l->groups))) * (l->c / l->groups);
        for (int hin = h_start; hin < l->h; hin += l->stride) {
            for (int win = w_start; win < l->w; win += l->stride) {
                pass_data = 0;
                for (int cin = c_start; cin < c_end; cin++) {
                    int data_index = hin * l->w * l->c + win * l->c + cin;

                    if (net->use_npu_accel)
                        fetch_data_tflite_i8(l, data_in, -1*l->tf_input1_offset, data_index, win, hin, 0);
                    else
                        fetch_data_tflite(l, data_in, -1*l->tf_input1_offset, data_index, l->in_layer1_mem, win, hin, 0, DATA_buf, net->patch_size);
                    
                    for (int wt = 0; wt < l->size * l->size; wt++) {
                        int w_index = outin * (l->c / l->groups) * l->size * l->size + (cin - c_start) * l->size * l->size + wt;
                        weights[wt] = (uint8_t)l->weights[w_index];
                        weights[wt] -= l->tf_input2_offset;
                    }

                    pass_data += PE_CONV_tflite((int32_t*)data_in, (int32_t*)weights, l->size, l_current);
                }

                int bias = 0;
                if (l->biases) {
                    bias = (int)l->biases[outin];
                    pass_data += bias;
                }

                if (l->activation == LINEAR)
                    pass_data = pass_data;
                /*
                else if (l->activation == LEAKY)
                    pass_data = PE_LEAKY(pass_data);
                else if (l->activation == RELU)
                    pass_data = PE_RELU(pass_data);
                */

                // 6 byte output_shift
                pass_data = BL_MultiplyByQuantizedMultiplier(pass_data, l->tf_output_multiplier, l->tf_output_shift);

                pass_data += l->tf_output_offset;

                pass_data = max(pass_data, l->quantized_activation_min);
                pass_data = min(pass_data, l->quantized_activation_max);

                int out_index = ((hin - h_start) / l->stride) * l->out_w * l->out_c + ((win - w_start) / l->stride) * l->out_c + outin;

                if (net->use_npu_accel) 
                    l->output_i8[out_index] = pass_data;
                else
                    MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
            }
        }
    }

    BLAI_FREE(weights);
    BLAI_FREE(data_in);
}

void forward_CONV_MAX_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t* weights = (int32_t*)BLAI_MALLOC(l->size * l->size * sizeof(int32_t));
    int32_t* data_in = (int32_t*)BLAI_MALLOC(l->size * l->size * sizeof(int32_t));
    int32_t pass_data = 0;

    int w_start = (l->stride == 2) ? 1 : 0;
    int h_start = (l->stride == 2) ? 1 : 0;

    for (int outin = 0; outin < l->out_c; outin++) {
        int c_start = (l->groups == 1) ? 0 : (outin / (l->out_c / l->groups)) * (l->c / l->groups);
        int c_end = (l->groups == 1) ? l->c : (1 + (outin / (l->out_c / l->groups))) * (l->c / l->groups);
        for (int hin = h_start; hin < l->h; hin += l->stride) {
            for (int win = w_start; win < l->w; win += l->stride) {
                pass_data = 0;
                for (int cin = c_start; cin < c_end; cin++) {
                    int data_index = hin * l->w * l->c + win * l->c + cin;

                    fetch_data_tflite(l, data_in, -l->tf_input1_offset, data_index, l->in_layer1_mem, win, hin, 0, DATA_buf, net->patch_size);
                    for (int wt = 0; wt < l->size * l->size; wt++) {
                        int w_index = outin * (l->c / l->groups) * l->size * l->size + (cin - c_start) * l->size * l->size + wt;
                        weights[wt] = (uint8_t)l->weights[w_index];
                        weights[wt] -= l->tf_input2_offset;
                    }

                    pass_data += PE_CONV_tflite((int32_t*)data_in, (int32_t*)weights, l->size, l_current);
                }

                int bias = 0;
                if (l->biases) {
                    bias = (int)l->biases[outin];
                    pass_data += bias;
                }

                if (l->activation == LINEAR) pass_data = pass_data;
                /*
                else if (l->activation == LEAKY)
                    pass_data = PE_LEAKY(pass_data);
                else if (l->activation == RELU)
                    pass_data = PE_RELU(pass_data);
                */

                // 6 byte output_shift
                pass_data = BL_MultiplyByQuantizedMultiplier(pass_data, l->tf_output_multiplier, l->tf_output_shift);

                pass_data += l->tf_output_offset;

                pass_data = max(pass_data, l->quantized_activation_min);
                pass_data = min(pass_data, l->quantized_activation_max);

                int out_index = (((hin - h_start) / l->stride) / 2) * (l->out_w) * l->out_c + (((win - w_start) / l->stride) / 2) * l->out_c + outin;
                if ((hin / l->stride) % 2 == 0 && (win / l->stride) % 2 == 0) {
                    MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                }
                else {
                    fixed_point_t pre_pass_data = MEM_RW(0, out_index, 0, l->out_layer_mem, DATA_buf, net->patch_size);
                    pass_data = (pre_pass_data > pass_data) ? pre_pass_data : pass_data;
                    MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                }
            }
        }
    }

    BLAI_FREE(weights);
    BLAI_FREE(data_in);
}

void forward_CONV_MAX(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    fixed_point_t* weights = (fixed_point_t*)BLAI_MALLOC(l->size * l->size * sizeof(fixed_point_t));
    fixed_point_t* data_in = (fixed_point_t*)BLAI_MALLOC(l->size * l->size * sizeof(fixed_point_t));
    int32_t bias = 0;
    int32_t pass_data = 0;
    fixed_point_t pass_data_8;
    int padding = 0;
    for (int outin = 0; outin < l->out_c; outin++) {
        int c_start = (l->groups == 1) ? 0 : (outin / (l->out_c / l->groups)) * (l->c / l->groups);
        int c_end = (l->groups == 1) ? l->c : (1 + (outin / (l->out_c / l->groups))) * (l->c / l->groups);
        for (int hin = 0; hin < l->h; hin += l->stride) {
            for (int win = 0; win < l->w; win += l->stride) {
                pass_data = 0;
                for (int cin = c_start; cin < c_end; cin++) {
                    int data_index = hin * l->w * l->c + win * l->c + cin;
                    fetch_data(l, data_in, data_index, l->in_layer1_mem, win, hin, padding, DATA_buf, net->patch_size);
                    for (int wt = 0; wt < l->size * l->size; wt++) {
                        int w_index = outin * (l->c / l->groups) * l->size * l->size + (cin - c_start) * l->size * l->size + wt;
                        weights[wt] = l->weights[w_index];
                    }

                    int64_t pass_data_64 = (int64_t)pass_data + (int64_t)PE_CONV(data_in, weights, l->size, (l_current == 0 && net->unsign_input));
                    pass_data = (pass_data_64 > INT32_MAX) ? INT32_MAX : (pass_data_64 < INT32_MIN) ? INT32_MIN : pass_data_64;

                }
                //S-format
                int falpha = (l->activation == LEAKY) ? 9 : 0;
                int f_in = l->fdata + l->fweight;
                int f_bias_out = l->fbias - l->fdata - l->fweight;

                bias = fixed8_to_fixed32(l->biases[outin], f_bias_out);
                pass_data += bias;

                if (l->activation == LINEAR) pass_data = pass_data;
                else if (l->activation == LEAKY) pass_data = PE_LEAKY(pass_data);
                else if (l->activation == RELU) pass_data = PE_RELU(pass_data);
                else if (l->activation == RELU6) pass_data = PE_RELU6(pass_data, f_in);

                falpha = (l->activation == LEAKY && pass_data < 0) ? 9 : 0;
                int ftotal = l->fdata + l->fweight + falpha - l->fout;

                pass_data_8 = (l->activation == MISH && pass_data < 0) ? PE_MISH(pass_data, f_in, l->fout) : fixed32_to_fixed8(pass_data, ftotal);

                int out_index = ((hin / l->stride) / 2) * (l->out_w) * l->out_c + ((win / l->stride) / 2) * l->out_c + outin;
                if ((hin / l->stride) % 2 == 0 && (win / l->stride) % 2 == 0) {
                    MEM_RW(1, out_index, pass_data_8, l->out_layer_mem, DATA_buf, net->patch_size);
                }
                else {
                    fixed_point_t pre_pass_data = MEM_RW(0, out_index, 0, l->out_layer_mem, DATA_buf, net->patch_size);
                    pass_data_8 = (pre_pass_data > pass_data_8) ? pre_pass_data : pass_data_8;
                    MEM_RW(1, out_index, pass_data_8, l->out_layer_mem, DATA_buf, net->patch_size);
                }
            }
        }
    }

    BLAI_FREE(weights);
    BLAI_FREE(data_in);
}

void forward_MAXPOOL(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    fixed_point_t* data_in = (fixed_point_t*)BLAI_MALLOC(l->size * l->size * sizeof(fixed_point_t));
    fixed_point_t pass_data = 0;
    int padding = -128;
    for (int hin = 0; hin < l->h; hin += l->stride) {
        for (int win = 0; win < l->w; win += l->stride) {
            for (int cin = 0; cin < l->c; cin++) {
                int data_index = hin * l->w * l->c + win * l->c + cin;
                if(l->size % 2 == 0)
                    fetch_data_even(l, data_in, data_index, l->in_layer1_mem, win, hin, padding, DATA_buf, net->patch_size);
                else
                    fetch_data(l, data_in, data_index, l->in_layer1_mem, win, hin, padding, DATA_buf, net->patch_size);

                for (int wt = 0; wt < l->size * l->size; wt++) {
                    pass_data = (wt == 0) ? data_in[wt] : (data_in[wt] > pass_data) ? data_in[wt] : pass_data;
                }
                int out_index = (hin / l->stride) * l->out_w * l->c + (win / l->stride) * l->c + cin;
                MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
            }
        }
    }

    BLAI_FREE(data_in);
}

void forward_MAXPOOL_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t* data_in = (int32_t*)BLAI_MALLOC(l->size * l->size * sizeof(int32_t));
    int32_t pass_data = 0;
    int w_start = (l->stride == 2) ? 1 : 0;
    int h_start = (l->stride == 2) ? 1 : 0;
    int padding = -128;
    for (int hin = h_start; hin < l->h; hin += l->stride) {
        for (int win = w_start; win < l->w; win += l->stride) {
            for (int cin = 0; cin < l->c; cin++) {
                int data_index = hin * l->w * l->c + win * l->c + cin;
                if (l->size % 2 == 0) fetch_data_even_tflite(l, data_in, -l->tf_input1_offset, data_index, l->in_layer1_mem, win, hin, padding, DATA_buf, net->patch_size);
                else fetch_data_tflite(l, data_in, -l->tf_input1_offset, data_index, l->in_layer1_mem, win, hin, padding, DATA_buf, net->patch_size);

                for (int wt = 0; wt < l->size * l->size; wt++) {
                    pass_data = (wt == 0) ? data_in[wt] : (data_in[wt] > pass_data) ? data_in[wt] : pass_data;
                }
                pass_data = BL_MultiplyByQuantizedMultiplier(pass_data, l->tf_output_multiplier, l->tf_output_shift);

                pass_data = max((uint8_t)pass_data, (uint8_t)l->quantized_activation_min);
                pass_data = min((uint8_t)pass_data, (uint8_t)l->quantized_activation_max);

                int out_index = ((hin - h_start) / l->stride) * l->out_w * l->c + ((win - w_start) / l->stride) * l->c + cin;
                MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
            }

        }
    }

    BLAI_FREE(data_in);
}

void forward_AVGPOOL_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t pass_data = 0;
    int pad_c = l->c;
    int pad_out_c = l->out_c;
    if (net->layers[l_current - 1].NPU_on == 1 && net->use_npu_accel == 0)
        pad_c = (l->c % 4 == 0) ? l->c : ((l->c / 4) + 1) * 4;

    if (l_current != net->layer_cnt - 1 && net->layers[l_current + 1].NPU_on == 1 && net->use_npu_accel == 0)
        pad_out_c = (l->out_c % 4 == 0) ? l->out_c : ((l->out_c / 4) + 1) * 4;

    for (int cin = 0; cin < l->c; cin++) {
        pass_data = 0;
        for (int hin = 0; hin < l->h; hin += l->stride) {
            for (int win = 0; win < l->w; win += l->stride) {

                int data_index = hin * l->w * pad_c + win * pad_c + cin;

                if (net->use_npu_accel)
                    pass_data += (uint8_t)l->input_i8[0][data_index];
                else
                    pass_data += (uint8_t)MEM_RW(0, data_index, 0, l->in_layer1_mem, DATA_buf, net->patch_size);                    
            }

        }
        int fliter_count = (l->h * l->w);
        pass_data = (pass_data + fliter_count / 2) / fliter_count;
        int out_index = cin;
        pass_data = max(pass_data, l->quantized_activation_min);
        pass_data = min(pass_data, l->quantized_activation_max);
        pass_data = (uint8_t)(pass_data);
        if (net->use_npu_accel)
            l->output_i8[out_index] = pass_data;
        else
            MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);

    }
}

void forward_ROUTE_CONV(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    int input_c = l->c + l->cn[0];
    fixed_point_t* weights = (fixed_point_t*)BLAI_MALLOC(l->size * l->size * sizeof(fixed_point_t));
    fixed_point_t* data_in = (fixed_point_t*)BLAI_MALLOC(l->size * l->size * sizeof(fixed_point_t));
    fixed_point_t* mid_data = (fixed_point_t*)BLAI_MALLOC(input_c * sizeof(fixed_point_t));
    int32_t bias = 0;
    int32_t pass_data = 0;
    fixed_point_t pass_data_8;
    int padding = 0;

    int layer_c[2] = { l->c, l->cn[0] };
    for (int outin = 0; outin < l->out_c; outin++) {
        int c_start = (l->groups == 1) ? 0 : (outin / (l->out_c / l->groups)) * (input_c / l->groups);
        int c_end = (l->groups == 1) ? input_c : (1 + (outin / (l->out_c / l->groups))) * (input_c / l->groups);
        for (int hin = 0; hin < l->h; hin += l->stride) {
            for (int win = 0; win < l->w; win += l->stride) {
                pass_data = 0;
                for (int cin = c_start; cin < c_end; cin++) {
                    int cl = (cin < l->c) ? 0 : 1;
                    int accum_c = (cl) ? l->c : 0;
                    l->c = layer_c[cl];
                    int data_index = hin * l->w * l->c + win * l->c + (cin - accum_c);
                    int SRAM_in = (cl) ? l->in_layer2_mem : l->in_layer1_mem;
                    int fshift = (cl) ? l->froute2 - l->fdata : l->froute1 - l->fdata;

                    fetch_data(l, data_in, data_index, SRAM_in, win, hin, padding, DATA_buf, net->patch_size);
                    if (outin == 0 && l->mid_out) mid_data[cin] = data_in[l->size * l->size / 2];
                    l->c = layer_c[0];
                    for (int wt = 0; wt < l->size * l->size; wt++) {
                        data_in[wt] = fixed8_to_fixed8(data_in[wt], fshift);
                        int w_index = outin * (input_c / l->groups) * l->size * l->size + (cin - c_start) * l->size * l->size + wt;
                        weights[wt] = l->weights[w_index];
                    }

                    int64_t pass_data_64 = (int64_t)pass_data + (int64_t)PE_CONV(data_in, weights, l->size, (l_current == 0 && net->unsign_input));
                    pass_data = (pass_data_64 > INT32_MAX) ? INT32_MAX : (pass_data_64 < INT32_MIN) ? INT32_MIN : pass_data_64;
                }
                //S-format
                int falpha = (l->activation == LEAKY) ? 9 : 0;
                int f_in = l->fdata + l->fweight;
                int f_bias_out = l->fbias - l->fdata - l->fweight;

                bias = fixed8_to_fixed32(l->biases[outin], f_bias_out);
                pass_data += bias;

                if (l->activation == LINEAR) pass_data = pass_data;
                else if (l->activation == LEAKY) pass_data = PE_LEAKY(pass_data);
                else if (l->activation == RELU) pass_data = PE_RELU(pass_data);
                else if (l->activation == RELU6) pass_data = PE_RELU6(pass_data, f_in);

                falpha = (l->activation == LEAKY && pass_data < 0) ? 9 : 0;
                int ftotal = l->fdata + l->fweight + falpha - l->fout;

                pass_data_8 = (l->activation == MISH && pass_data < 0) ? PE_MISH(pass_data, f_in, l->fout) : fixed32_to_fixed8(pass_data, ftotal);

                int out_index = (hin / l->stride) * l->out_w * l->out_c + (win / l->stride) * l->out_c + outin;

                MEM_RW(1, out_index, pass_data_8, l->out_layer_mem, DATA_buf, net->patch_size);
                if (outin == 0 && l->mid_out) {

                    for (int mid_c = 0; mid_c < input_c; mid_c++) {
                        int mid_data_index = hin * l->w * input_c + win * input_c + mid_c;
                        MEM_RW(1, mid_data_index, mid_data[mid_c], l->mid_layer_mem, DATA_buf, net->patch_size);
                    }
                }
            }
        }
    }

    BLAI_FREE(weights);
    BLAI_FREE(data_in);
    BLAI_FREE(mid_data);
}

void forward_UPSAMPLE(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    fixed_point_t pass_data = 0;
    for (int cin = 0; cin < l->c; ++cin) {
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {
                int data_index = hin * l->w * l->c + win * l->c + cin;

                pass_data = MEM_RW(0, data_index, 0, l->in_layer1_mem, DATA_buf, net->patch_size);

                int fdata = l->fdata;
                int fout = l->fout;

                int fshift = fdata - fout;
                int out_index = hin * l->out_w * l->out_c + win * l->out_c + cin;
                pass_data = fixed8_to_fixed8(pass_data, fshift);

                for (int stride_x = 0; stride_x < l->stride; stride_x++) {
                    for (int stride_y = 0; stride_y < l->stride; stride_y++) {
                        out_index = (hin * l->stride + stride_y) * l->out_w * l->out_c + (win * l->stride + stride_x) * l->out_c + cin;
                        MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                    }
                }
            }
        }
    }
}

void forward_ROUTE_UPSAMPLE(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    fixed_point_t pass_data = 0;
    int layer_c[2] = { l->c, l->cn[0] };

    for (int cin = 0; cin < l->out_c; ++cin) {
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {
                int cl = (cin < l->c) ? 0 : 1;
                int accum_c = (cl) ? l->c : 0;
                l->c = layer_c[cl];

                int SRAM_in = (cl) ? l->in_layer2_mem : l->in_layer1_mem;
                int fshift_route = (cl) ? l->froute2 - l->fdata : l->froute1 - l->fdata;
                int data_index = (hin) * l->w * l->c + (win) * l->c + (cin - accum_c);

                pass_data = MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, net->patch_size);
                pass_data = fixed8_to_fixed8(pass_data, fshift_route);

                l->c = layer_c[0];
                int fdata = l->fdata;
                int fout = l->fout;

                int fshift = fdata - fout;
                pass_data = fixed8_to_fixed8(pass_data, fshift);

                int out_index = hin * l->out_w * l->out_c + win * l->out_c + cin;
                for (int stride_x = 0; stride_x < l->stride; stride_x++) {
                    for (int stride_y = 0; stride_y < l->stride; stride_y++) {
                        out_index = (hin* l->stride + stride_y) * l->out_w * l->out_c + (win * l->stride + stride_x) * l->out_c + cin;
                        MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                    }
                }
            }
        }
    }
}

void forward_SHORTCUT(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    fixed_point_t pass_data = 0;
    for (int cin = 0; cin < l->c; ++cin) {
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {
                int data_index = (hin)*l->w * l->c + (win)*l->c + cin;
                int out_index = hin * l->out_w * l->out_c + win * l->out_c + cin;
                fixed_point_t data_1 = MEM_RW(0, data_index, 0, l->in_layer1_mem, DATA_buf, net->patch_size);
                fixed_point_t data_2 = MEM_RW(0, data_index, 0, l->in_layer2_mem, DATA_buf, net->patch_size);

                int froute1 = l->froute1;
                int froute2 = l->froute2;
                int fdata = (froute1 > froute2) ? froute2 : froute1; // BLAI 1027
                int fout = l->fout;

                int fshift1 = froute1 - fdata;
                int fshift2 = froute2 - fdata;
//                int deshift = fdata - fout;
                int falpha = 9;
                int32_t pass_data_32 = (int32_t)fixed8_to_fixed8(data_1, fshift1) + (int32_t)fixed8_to_fixed8(data_2, fshift2);

                if (l->activation == LINEAR) pass_data_32 = pass_data_32;
                else if (l->activation == LEAKY) pass_data_32 = PE_LEAKY(pass_data_32);
                else if (l->activation == RELU) pass_data_32 = PE_RELU(pass_data_32);
                else if (l->activation == RELU6) pass_data_32 = PE_RELU6(pass_data_32, fdata);

                falpha = (l->activation == LEAKY && pass_data_32 < 0) ? 9 : 0;
                int ftotal = fdata + falpha - fout;

                pass_data = fixed32_to_fixed8(pass_data_32, ftotal);

                MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
            }
        }
    }

}

void forward_SHORTCUT_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    fixed_point_t pass_data = 0;
    int32_t data_1, data_2;
    int32_t shift_data_1, shift_data_2;
    int32_t scaled_data_1, scaled_data_2;
    int32_t raw_sum, raw_output, clamped_output;
    int left_shift = 20;
    for (int cin = 0; cin < l->c; ++cin) {
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {
                int data_index = (hin)*l->w * l->c + (win)*l->c + cin;
                int out_index = hin * l->out_w * l->out_c + win * l->out_c + cin;
                data_1 = (uint8_t)MEM_RW(0, data_index, 0, l->in_layer1_mem, DATA_buf, net->patch_size);
                data_2 = (uint8_t)MEM_RW(0, data_index, 0, l->in_layer2_mem, DATA_buf, net->patch_size);

                data_1 -= l->tf_input1_offset;
                data_2 -= l->tf_input2_offset;

                shift_data_1 = data_1 * (1 << left_shift);
                shift_data_2 = data_2 * (1 << left_shift);
                scaled_data_1 =
                    BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(
                        shift_data_1, l->tf_input1_multiplier, l->tf_input1_shift);
                scaled_data_2 =
                    BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(
                        shift_data_2, l->tf_input2_multiplier, l->tf_input2_shift);
                raw_sum = scaled_data_1 + scaled_data_2;

                raw_output =
                    BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(
                        raw_sum, l->tf_output_multiplier, l->tf_output_shift) +
                    l->tf_output_offset;
                clamped_output = min(l->quantized_activation_max, max(l->quantized_activation_min, raw_output));
                pass_data = (uint8_t)(clamped_output);

                MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);

            }
        }
    }

}

void forward_YOLO(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    float pass_data = 0;
    // fetch data from conv output
    int pad_c = l->c;

    if (net->layers[l_current - 1].NPU_on == 1 && net->use_npu_accel == 0) 
        pad_c = (l->c % 4 == 0) ? l->c : ((l->c / 4) + 1) * 4;

    for (int hin = 0; hin < l->h; hin++) {
        for (int win = 0; win < l->w; win++) {
            for (int cin = 0; cin < l->c; cin++) {
                int data_index = cin * l->h * l->w + hin * l->w + win;
                int data_index_HWC = hin * l->w * pad_c + win * pad_c + cin;

                fixed_point_t data_in = 0;
                if (net->use_npu_accel)
                    data_in = net->layers[l_current - 1].output_i8[data_index_HWC];
                else
                    data_in = MEM_RW(0, data_index_HWC, 0, l->in_layer1_mem, DATA_buf, net->patch_size);

                // Feature map fixed to floating
                //pass_data = FIXED_to_FLOAT_map(pass_data, l_current, ctrl);
                pass_data = fixed_to_float(data_in, l->fdata);
                l->output[data_index] = pass_data;
            }
        }
    }
    // activate yolo layer
    for (int n = 0; n < l->n; ++n) {
        int index = BL_entry_index(l, n * l->w * l->h, 0);
        BL_activate_array(l->output + index, 2 * l->w * l->h, LOGISTIC);
        index = BL_entry_index(l, n * l->w * l->h, 4);
        BL_activate_array(l->output + index, (1 + l->classes) * l->w * l->h, LOGISTIC);
    }

}

void forward_YOLO_lm(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    float pass_data = 0;
    // fetch data from conv output
    int pad_c = l->c;

    if (net->layers[l_current - 1].NPU_on == 1 && net->use_npu_accel == 0)
        pad_c = (l->c % 4 == 0) ? l->c : ((l->c / 4) + 1) * 4;

    for (int hin = 0; hin < l->h; hin++) {
        for (int win = 0; win < l->w; win++) {
            for (int cin = 0; cin < l->c; cin++) {
                int data_index = cin * l->h * l->w + hin * l->w + win;
                int data_index_HWC = hin * l->w * pad_c + win * pad_c + cin;

                fixed_point_t data_in = 0;
                if (net->use_npu_accel)
                    data_in = net->layers[l_current - 1].output_i8[data_index_HWC];
                else
                    data_in = MEM_RW(0, data_index_HWC, 0, l->in_layer1_mem, DATA_buf, net->patch_size);
                // Feature map fixed to floating
                //pass_data = FIXED_to_FLOAT_map(pass_data, l_current, ctrl);
                pass_data = fixed_to_float(data_in, l->fdata);
                l->output[data_index] = pass_data;
            }
        }
    }
    // activate yolo layer
    int scale_x_y = 1;
    for (int n = 0; n < l->n; ++n) {
        int index = lm_entry_index(l, 0, n * l->w * l->h, 0);
        BL_activate_array(l->output + index, 2 * l->w * l->h, LOGISTIC);
        BL_scal_add_cpu(2 * l->w * l->h, scale_x_y, -0.5 * (scale_x_y - 1), l->output + index, 1);    // scale x,y
        index = lm_entry_index(l, 0, n * l->w * l->h, 14);
        BL_activate_array(l->output + index, (1 + l->classes) * l->w * l->h, LOGISTIC);
    }

}


void forward_ROUTE(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    fixed_point_t pass_data = 0;
    int minus_c = 0;
    int current_layer_index = 0;
    int accumulate_c = l->c;

    for (int cin = 0; cin < l->out_c; ++cin) {
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {

                minus_c = (cin < accumulate_c) ? minus_c : accumulate_c;
                current_layer_index = (cin < accumulate_c) ? current_layer_index : current_layer_index + 1;
                accumulate_c = (cin < accumulate_c) ? accumulate_c : accumulate_c + l->cn[current_layer_index - 1];
                int current_c = (current_layer_index == 0) ? l->c : l->cn[current_layer_index - 1];

                int SRAM_in = (current_layer_index == 0) ? l->in_layer1_mem : (current_layer_index == 1) ? l->in_layer2_mem : l->in_layer_mem_n[current_layer_index - 2];
                int data_index = hin * l->out_w * current_c + win * current_c + (cin - minus_c);

                pass_data = MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, net->patch_size);

                int fdata = (current_layer_index == 0) ? l->froute1 : (current_layer_index == 1) ? l->froute2 : l->frouten[current_layer_index - 2];
                int fout = l->fdata;
                int fshift = fdata - fout;
                pass_data = fixed8_to_fixed8(pass_data, fshift);

                int out_index = hin * l->out_w * l->out_c + win * l->out_c + cin;
                MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
            }
        }
    }
}
void forward_ROUTE_MAX(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    fixed_point_t pass_data = 0;
    int minus_c = 0;
    int current_layer_index = 0;
    int accumulate_c = l->c;

    for (int cin = 0; cin < l->out_c; ++cin) {
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {

                minus_c = (cin < accumulate_c) ? minus_c : accumulate_c;
                current_layer_index = (cin < accumulate_c) ? current_layer_index : current_layer_index + 1;
                accumulate_c = (cin < accumulate_c) ? accumulate_c : accumulate_c + l->cn[current_layer_index - 1];
                int current_c = (current_layer_index == 0) ? l->c : l->cn[current_layer_index - 1];

                int SRAM_in = (current_layer_index == 0) ? l->in_layer1_mem : (current_layer_index == 1) ? l->in_layer2_mem : l->in_layer_mem_n[current_layer_index - 2];
                int data_index = hin * l->w * current_c + win * current_c + (cin - minus_c);

                pass_data = MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, net->patch_size);

                int fdata = (current_layer_index == 0) ? l->froute1 : (current_layer_index == 1) ? l->froute2 : l->frouten[current_layer_index - 2];
                int fout = l->fdata;
                int fshift = fdata - fout;
                pass_data = fixed8_to_fixed8(pass_data, fshift);

                int out_index = (hin / 2) * (l->out_w) * l->out_c + (win / 2) * l->out_c + cin;

                if ((hin / l->stride) % 2 == 0 && (win / l->stride) % 2 == 0) {
                    MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                }
                else {
                    fixed_point_t pre_pass_data = MEM_RW(0, out_index, 0, l->out_layer_mem, DATA_buf, net->patch_size);
                    pass_data = (pre_pass_data > pass_data) ? pre_pass_data : pass_data;
                    MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                }
            }
        }
    }
}

void forward_ROUTE_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t pass_data = 0;
    int32_t shifted_input_val, scaled_input_val;
    int left_shift = 20;
    int minus_c = 0;
    int current_layer_index = 0;
    int accumulate_c = l->c;


    for (int cin = 0; cin < l->out_c; ++cin) {
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {

                minus_c = (cin < accumulate_c) ? minus_c : accumulate_c;
                current_layer_index = (cin < accumulate_c) ? current_layer_index : current_layer_index + 1;
                accumulate_c = (cin < accumulate_c) ? accumulate_c : accumulate_c + l->cn[current_layer_index - 1];
                int current_c = (current_layer_index == 0) ? l->c : l->cn[current_layer_index - 1];

                int SRAM_in = (current_layer_index == 0) ? l->in_layer1_mem : (current_layer_index == 1) ? l->in_layer2_mem : l->in_layer_mem_n[current_layer_index - 2];
                int data_index = hin * l->out_w * current_c + win * current_c + (cin - minus_c);

                int input_offset = (current_layer_index == 0) ? l->tf_input1_offset
                    : (current_layer_index == 1) ? l->tf_input2_offset : l->tf_input_offset_extra[current_layer_index - 2];
                int input_multiplier = (current_layer_index == 0) ? l->tf_input1_multiplier
                    : (current_layer_index == 1) ? l->tf_input2_multiplier : l->tf_input_multiplier_extra[current_layer_index - 2];
                int input_shift = (current_layer_index == 0) ? l->tf_input1_shift
                    : (current_layer_index == 1) ? l->tf_input2_shift : l->tf_input_shift_extra[current_layer_index - 2];
                pass_data = (uint8_t)MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, net->patch_size) - input_offset;

                shifted_input_val = pass_data * (1 << left_shift);
                scaled_input_val = BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(shifted_input_val, input_multiplier, input_shift);
                pass_data = BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(scaled_input_val, l->tf_output_multiplier, l->tf_output_shift) + l->tf_output_offset;

                pass_data = max(pass_data, l->quantized_activation_min);
                pass_data = min(pass_data, l->quantized_activation_max);

                int out_index = hin * l->out_w * l->out_c + win * l->out_c + cin;
                MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
            }
        }
    }
}

void forward_ROUTE_W_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t pass_data = 0;
    int32_t shifted_input_val, scaled_input_val;
    int left_shift = 20;
    int minus_c = 0;
    int current_layer_index = 0;
    int accumulate_c = l->c;
    int compare = 0;

    int8_t* output = MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size);
    
    bool easy_route_w = (l->tf_input1_offset == l->tf_input2_offset) && (l->axis == 0);
    for(int i = 0; i < l->input_num - 2; i++){
        easy_route_w = easy_route_w && (l->tf_input1_offset == l->tf_input_offset_extra[i]);
    }
    easy_route_w = easy_route_w && l->tf_output_offset;
    if(easy_route_w){
        int offset = 0;
        for (int hin = 0; hin < l->h; ++hin){
            // memcpy layer 1
            int slice = l->c * l->out_c;
            int8_t* input = MEM_PTR(l->in_layer1_mem, DATA_buf, net->patch_size) + hin * slice;
            
            memcpy(output, input, slice);
            output += slice;
            
            // memcpy layer 2
            slice = l->cn[0] * l->out_c;
            input = MEM_PTR(l->in_layer2_mem, DATA_buf, net->patch_size) + hin * slice;
            memcpy(output, input, slice);
            output += slice;

            // memcpy layer 3~n
            for(int k = 2; k < l->input_num; k++){
                slice = l->cn[k - 1] * l->out_c;
                input = MEM_PTR(l->in_layer_mem_n[k-2], DATA_buf, net->patch_size) + hin * slice;
                memcpy(output, input, slice);
                output += slice;            
            }
        }
    }
    else{
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {
                for (int cin = 0; cin < l->out_c; ++cin) {
                    compare = (l->axis == 0) ? win : hin;
                    minus_c = (compare < accumulate_c) ? minus_c : accumulate_c;
                    current_layer_index = (compare < accumulate_c) ? current_layer_index : current_layer_index + 1;
                    accumulate_c = (compare < accumulate_c) ? accumulate_c : accumulate_c + l->cn[current_layer_index - 1];
                    int current_c = (current_layer_index == 0) ? l->c : l->cn[current_layer_index - 1];

                    int SRAM_in = (current_layer_index == 0) ? l->in_layer1_mem : (current_layer_index == 1) ? l->in_layer2_mem : l->in_layer_mem_n[current_layer_index - 2];
                    int data_index = (l->axis == 0) ? hin * current_c * l->out_c + (win - minus_c) * l->out_c + cin : (hin - minus_c) * l->out_w * l->out_c + win * l->out_c + (cin);

                    int input_offset = (current_layer_index == 0) ? l->tf_input1_offset
                        : (current_layer_index == 1) ? l->tf_input2_offset : l->tf_input_offset_extra[current_layer_index - 2];
                    int input_multiplier = (current_layer_index == 0) ? l->tf_input1_multiplier
                        : (current_layer_index == 1) ? l->tf_input2_multiplier : l->tf_input_multiplier_extra[current_layer_index - 2];
                    int input_shift = (current_layer_index == 0) ? l->tf_input1_shift
                        : (current_layer_index == 1) ? l->tf_input2_shift : l->tf_input_shift_extra[current_layer_index - 2];
                    if (net->use_npu_accel)
                        pass_data = (uint8_t) l->input_i8[current_layer_index][data_index] - input_offset;
                    else
                        pass_data = (uint8_t)MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, net->patch_size) - input_offset;

                    shifted_input_val = pass_data * (1 << left_shift);
                    scaled_input_val = BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(shifted_input_val, input_multiplier, input_shift);

                    pass_data = BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(scaled_input_val, l->tf_output_multiplier, l->tf_output_shift) + l->tf_output_offset;
                    pass_data = max(pass_data, l->quantized_activation_min);
                    pass_data = min(pass_data, l->quantized_activation_max);

                    int out_index = hin * l->out_w * l->out_c + win * l->out_c + cin;
                    if (net->use_npu_accel)
                        l->output_i8[out_index] = pass_data;
                    else
                        MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                }
            }
        }
    }
}



void forward_ROUTE_MAX_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t pass_data = 0;
    int32_t shifted_input_val, scaled_input_val;
    int left_shift = 20;
    int minus_c = 0;
    int current_layer_index = 0;
    int accumulate_c = l->c;


    for (int cin = 0; cin < l->out_c; ++cin) {
        for (int hin = 0; hin < l->h; ++hin) {
            for (int win = 0; win < l->w; ++win) {

                minus_c = (cin < accumulate_c) ? minus_c : accumulate_c;
                current_layer_index = (cin < accumulate_c) ? current_layer_index : current_layer_index + 1;
                accumulate_c = (cin < accumulate_c) ? accumulate_c : accumulate_c + l->cn[current_layer_index - 1];
                int current_c = (current_layer_index == 0) ? l->c : l->cn[current_layer_index - 1];

                int SRAM_in = (current_layer_index == 0) ? l->in_layer1_mem : (current_layer_index == 1) ? l->in_layer2_mem : l->in_layer_mem_n[current_layer_index - 2];
                int data_index = hin * l->w * current_c + win * current_c + (cin - minus_c);

                int input_offset = (current_layer_index == 0) ? l->tf_input1_offset
                    : (current_layer_index == 1) ? l->tf_input2_offset : l->tf_input_offset_extra[current_layer_index - 2];
                int input_multiplier = (current_layer_index == 0) ? l->tf_input1_multiplier
                    : (current_layer_index == 1) ? l->tf_input2_multiplier : l->tf_input_multiplier_extra[current_layer_index - 2];
                int input_shift = (current_layer_index == 0) ? l->tf_input1_shift
                    : (current_layer_index == 1) ? l->tf_input2_shift : l->tf_input_shift_extra[current_layer_index - 2];
                pass_data = (uint8_t)MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, net->patch_size) - input_offset;

                shifted_input_val = pass_data * (1 << left_shift);
                scaled_input_val = BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(shifted_input_val, input_multiplier, input_shift);
                pass_data = BL_MultiplyByQuantizedMultiplierSmallerThanOneExp(scaled_input_val, l->tf_output_multiplier, l->tf_output_shift) + l->tf_output_offset;

                pass_data = max(pass_data, l->quantized_activation_min);
                pass_data = min(pass_data, l->quantized_activation_max);

                int out_index = (hin / 2) * (l->out_w) * l->out_c + (win / 2) * l->out_c + cin;

                //MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                if ((hin / l->stride) % 2 == 0 && (win / l->stride) % 2 == 0) {
                    MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                }
                else {
                    fixed_point_t pre_pass_data = MEM_RW(0, out_index, 0, l->out_layer_mem, DATA_buf, net->patch_size);
                    pass_data = (pre_pass_data > pass_data) ? pre_pass_data : pass_data;
                    MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);
                }
            }
        }
    }
}

static void BL_memset_PSRAM(fixed_point_t* DATA_buf, int PATCH_SIZE,int offset, int index, int size, int data) {
	int8_t* dst = DATA_buf + offset * PATCH_SIZE + index;
	memset(dst, data, size * sizeof(int8_t));
}

static void BL_memcpy_PSRAM_buf(fixed_point_t* DATA_buf, int PATCH_SIZE, int offset, int index, int size, fixed_point_t* src) {
    fixed_point_t* dst = DATA_buf + offset * PATCH_SIZE + index;
    memcpy(dst, src, size * sizeof(fixed_point_t));
}

static void BL_memcpy_PSRAM(fixed_point_t* DATA_buf, int PATCH_SIZE, int dst_offset, int dst_index, int src_offset, int src_index, int size) {

    fixed_point_t* dst = DATA_buf + dst_offset * PATCH_SIZE + dst_index;
    fixed_point_t* src = DATA_buf + src_offset * PATCH_SIZE + src_index;
    memcpy(dst, src, size * sizeof(fixed_point_t));
}

void forward_RESHAPE_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    int32_t pass_data = 0;
    // fetch data from conv output
    int pad_c = l->c;
    int pad_out_c = l->out_c;

    bool input_npu_on = false;
    bool output_npu_on = false;
    
    
    if((l_current > 0 && net->layers[l_current - 1].out_layer_mem == l->in_layer1_mem) && (l_current < net->layer_cnt && net->layers[l_current + 1].in_layer1_mem == l->out_layer_mem)){ 
        if (net->layers[l_current - 1].NPU_on == 1 && net->use_npu_accel == 0)
            pad_c = (l->c % 4 == 0) ? l->c : ((l->c / 4) + 1) * 4;

        if (net->layers[l_current + 1].NPU_on == 1 && net->use_npu_accel == 0)
            pad_out_c = (l->out_c % 4 == 0) ? l->out_c : ((l->out_c / 4) + 1) * 4;
    }
    else{
        for(int i = l_current + 1; i < net->layer_cnt; i++){
            if((l->out_layer_mem == net->layers[i].in_layer1_mem) || (net->layers[i].input_num >= 2 && l->out_layer_mem == net->layers[i].in_layer2_mem)){
                output_npu_on = net->layers[i].NPU_on;
      
                break;
            }
            if(net->layers[i].NPU_on == 0 && net->layers[i].input_num > 2){
                bool jump = false;
                for(int k = 2; k < net->layers[i].input_num; k++){
                    if(l->out_layer_mem == net->layers[i].in_layer_mem_n[k-2]){
                        output_npu_on = net->layers[i].NPU_on;
                 
                        jump = true;
                    }
                }
                if(jump) break;
            }
        }
        
        for(int i = l_current - 1; i >= 0; i--){
            if(l->in_layer1_mem == net->layers[i].out_layer_mem){
                input_npu_on = net->layers[i].NPU_on;
                break;
            }
        }
        if(input_npu_on)
            pad_c = (l->c % 4 == 0) ? l->c : ((l->c / 4) + 1) * 4;
        if(output_npu_on)
            pad_out_c = (l->out_c % 4 == 0) ? l->out_c : ((l->out_c / 4) + 1) * 4;

    }
    int out_index = 0;
    int outc = 0;
    int output_size = l->out_h * l->out_w;

    if(l->c == pad_c && l->out_c == pad_out_c){
        int size = l->c * l->h * l->w;
        int8_t* input = MEM_PTR(l->in_layer1_mem, DATA_buf, net->patch_size);
        int8_t* output = MEM_PTR(l->out_layer_mem, DATA_buf, net->patch_size);   
        
        memcpy(output, input, size);
    }
    else{
        for (int hin = 0; hin < l->h; hin++) {
            for (int win = 0; win < l->w; win++) {
                  for (int cin = 0; cin < l->c; cin++) {
                    int data_index = hin * l->w * pad_c + win * pad_c + cin;
                    if (net->use_npu_accel)
                        pass_data = (uint8_t)l->input_i8[0][data_index];
                    else
                        pass_data = (uint8_t)MEM_RW(0, data_index, 0, l->in_layer1_mem, DATA_buf, net->patch_size);

                    //int out_index =hin * l->out_w * pad_out_c + win * pad_out_c + cin;

                    if (net->use_npu_accel)
                        l->output_i8[out_index] = pass_data;
                    else
                        MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);

                    if(pad_out_c > l->out_c && outc == l->out_c - 1){
                        out_index += (pad_out_c - l->out_c);
                    }
                    out_index++;
                    outc = (outc == l->out_c - 1) ? 0 : outc + 1;
                }
            }
        }
    }
}


void forward_PRE_TRANSCONV_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    int SRAM_in = l->in_layer1_mem;
    int SRAM_out = l->out_layer_mem;
    for (int hin = 0; hin < l->h; hin++) {
		int pad_index = 0;
		for (int win = 0; win < l->w; win++) {
			int data_index = hin * l->w * l->c + win * l->c;
			int out_index = (hin * 2 + 1) * l->out_w * l->c + (win * 2 + 1) * l->c;
			pad_index = (hin * 2 + 1) * l->out_w * l->c + (win * 2) * l->c;
			BL_memcpy_PSRAM(DATA_buf, net->patch_size, SRAM_out, out_index, SRAM_in, data_index, l->c);
			BL_memset_PSRAM(DATA_buf, net->patch_size, SRAM_out, pad_index, l->c, l->tf_input1_offset);

        }
		pad_index = (hin * 2) * l->out_w * l->c;

		BL_memset_PSRAM(DATA_buf, net->patch_size, SRAM_out, pad_index, l->c * l->out_w, l->tf_input1_offset);
	}
}


void forward_MEAN_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    int SRAM_in = l->in_layer1_mem;
    int SRAM_out = l->out_layer_mem;
    int32_t pass_data;
    int32_t data_in;
    int32_t kMinInt8 = 0;
    int32_t kMaxInt8 = 255;
    const int num_elements_in_axis = l->w * l->h;
    int pad_c = l->c;
    int pad_out_c = l->out_c;
    if (net->layers[l_current - 1].NPU_on == 1 && net->use_npu_accel == 0)
        pad_c = (l->c % 4 == 0) ? l->c : ((l->c / 4) + 1) * 4;

    if (l_current != net->layer_cnt - 1 && net->layers[l_current + 1].NPU_on == 1 && net->use_npu_accel == 0)
        pad_out_c = (l->out_c % 4 == 0) ? l->out_c : ((l->out_c / 4) + 1) * 4;

    for (int cin = 0; cin < l->c; cin++) {
        pass_data = 0;
        for (int hin = 0; hin < l->h; hin++) {
            for (int win = 0; win < l->w; win++) {

                int data_index = hin * l->w * pad_c + win * pad_c + cin;
                data_in = (uint8_t)MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, net->patch_size);

                data_in -= l->tf_input1_offset;
                pass_data += data_in;
            }
        }
        int out_index = cin;
        pass_data = BL_MultiplyByQuantizedMultiplier(pass_data, l->tf_output_multiplier, l->tf_output_shift);
        pass_data = pass_data > 0 ? (pass_data + num_elements_in_axis / 2) / num_elements_in_axis
            : (pass_data - num_elements_in_axis / 2) / num_elements_in_axis;
        pass_data += l->tf_output_offset;
        pass_data = min(max(pass_data, kMinInt8), kMaxInt8);

        MEM_RW(1, out_index, pass_data, SRAM_out, DATA_buf, net->patch_size);

    }

}


void forward_PAD_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    int SRAM_in = l->in_layer1_mem;
    int SRAM_out = l->out_layer_mem;
    int pass_data;

    int left_pad_c = 0;
    int left_pad_w = 0;
    int left_pad_h = 0;
    int right_pad_c = 0;
    int right_pad_w = 0;
    int right_pad_h = 0;

    left_pad_c = l->biases[0];
    left_pad_w = l->biases[2];
    left_pad_h = l->biases[4];
    right_pad_c = l->biases[1];
    right_pad_w = l->biases[3];
    right_pad_h = l->biases[5];
    l->out_c = left_pad_c + l->out_c + right_pad_c;
    l->out_h = left_pad_h + l->out_h + right_pad_h;
    l->out_w = left_pad_w + l->out_w + right_pad_w;
    int padding_value = l->tf_output_offset;

    fixed_point_t* data_ch = (fixed_point_t*)BLAI_MALLOC(l->c * sizeof(fixed_point_t));
    if (left_pad_c == 0 && right_pad_c == 0) {

        for (int i = 0; i < l->c; i++)
            data_ch[i] = padding_value;

        for (int hin = 0 - left_pad_h; hin < l->h + right_pad_h; hin++) {
            for (int win = 0 - left_pad_w; win < l->w + right_pad_w; win++) {

                int data_index = hin * l->w * l->c + win * l->c;
                bool pad_check = (hin < 0 || win < 0 || hin >= l->h || win >= l->w);

                int out_index = (hin + left_pad_h) * l->out_w * l->out_c + (win + left_pad_w) * l->out_c;

                if (net->use_npu_accel) {
                    if (pad_check)
                        memcpy(l->output_i8, data_ch, l->c * sizeof(fixed_point_t));
                    else
                        memcpy(l->output_i8, l->input_i8[0], l->c * sizeof(fixed_point_t));
                } else {
                    if (pad_check)
                        BL_memcpy_PSRAM_buf(DATA_buf, net->patch_size, SRAM_out, out_index, l->c, data_ch);
                    else
                        BL_memcpy_PSRAM(DATA_buf, net->patch_size, SRAM_out, out_index, SRAM_in, data_index, l->c);
                }
            }
        }
    }
    else{
        printf("[WARNING] CHANNEL-WISE PAD IS NOT IMPLEMENT\r\n");
    }
    /*for (int cin = 0; cin < l->out_c; cin++) {
        for (int hin = 0; hin < l->out_h; hin++) {
            for (int win = 0; win < l->out_w; win++) {
                int data_index = hin * l->out_w * l->out_c + win * l->out_c + cin;
                int pass_data = (uint8_t)MEM_RW(0, data_index, 0, SRAM_out, DATA_buf, net->patch_size);
            }
        }
    }*/
    BLAI_FREE(data_ch);
}

void forward_TRANSPOSE_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int SRAM_in = l->in_layer1_mem;

    int SRAM_out = l->out_layer_mem;
    int pass_data;

    int c_perm_mux = l->mask[l->n - 1];
    int w_perm_mux = l->mask[l->n - 2];
    int h_perm_mux = l->mask[l->n - 3];

    int cin_t = 0, win_t = 0, hin_t = 0, lc_t = 0, lw_t = 0;
    if (l->n == 4) {
        lc_t = (c_perm_mux == 1) ? l->h : (c_perm_mux == 2) ? l->w : l->c;
        lw_t = (w_perm_mux == 1) ? l->h : (w_perm_mux == 2) ? l->w : l->c;
    }
    else if (l->n == 3) {
        lc_t = (c_perm_mux == 0) ? l->h : (c_perm_mux == 1) ? l->w : l->c;
        lw_t = (w_perm_mux == 0) ? l->h : (w_perm_mux == 1) ? l->w : l->c;
    }

    for (int cin = 0; cin < l->c; cin++) {
        for (int hin = 0; hin < l->h; hin++) {
            for (int win = 0; win < l->w; win++) {

                int data_index = hin * l->w * l->c + win * l->c + cin;

                pass_data = (uint8_t)MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, net->patch_size);

                if (l->n == 4) {
                    cin_t = (c_perm_mux == 1) ? hin : (c_perm_mux == 2) ? win : cin;
                    win_t = (w_perm_mux == 1) ? hin : (w_perm_mux == 2) ? win : cin;
                    hin_t = (h_perm_mux == 1) ? hin : (h_perm_mux == 2) ? win : cin;
                }
                else if (l->n == 3) {
                    cin_t = (c_perm_mux == 0) ? hin : (c_perm_mux == 1) ? win : cin;
                    win_t = (w_perm_mux == 0) ? hin : (w_perm_mux == 1) ? win : cin;
                    hin_t = (h_perm_mux == 0) ? hin : (h_perm_mux == 1) ? win : cin;
                }

                int out_index = hin_t * lw_t * lc_t + win_t * lc_t + cin_t;
                MEM_RW(1, out_index, pass_data, SRAM_out, DATA_buf, net->patch_size);
            }
        }
    }
}


void forward_TRANSPOSELK_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    l->size = l->tf_input1_multiplier;

    int l_size = (l->size % 4 == 0) ? l->size : (l->size / 4 + 1) * 4;
    int layer_h = (l->w == 1) ? l->h : l->w;
    int dilation_width_factor = l->tf_input1_offset;
    int dilation_height_factor = l->tf_input2_offset;
    int dila_h = (l->w == 1) ? dilation_height_factor : dilation_width_factor;
    int fetch_size = (dila_h == 2) ? l->size * dila_h - 1 : l->size;
    int SRAM_out = l->out_layer_mem;
    int offset = l->in_layer1_mem * net->patch_size;

    fixed_point_t* mem_ptr = DATA_buf + offset;
    int padding = 128;

    for (int hin = 0; hin < layer_h - fetch_size + 1; hin += l->stride) {
        mem_ptr = DATA_buf + offset + (l->c * hin);
        for (int cin = 0; cin < l->c; cin++) {
            for (int wt = 0; wt < l_size; wt++) {
                //int out_index = (hin / l->stride) * l->c * l->size + cin * l->size + wt;
                int out_index = (hin / l->stride) * l->c * l_size + cin * l_size + wt;
                int ptr_index = (wt * dila_h) * l->c + cin;
                int pass_data = (wt >= l->size) ? padding : ((wt * dila_h) + hin > layer_h - 1) ? padding : mem_ptr[ptr_index];
                MEM_RW(1, out_index, pass_data, SRAM_out, DATA_buf, net->patch_size);
            }
        }
    }
}

void forward_TRANSPOSELK_V2_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    l->size = l->tf_input1_multiplier;

    int l_size = (l->size % 4 == 0) ? l->size : (l->size / 4 + 1) * 4;
    int pad_size = l_size - l->size;
    int layer_h = (l->w == 1) ? l->h : l->w;
    int dilation_width_factor = l->tf_input1_offset;
    int dilation_height_factor = l->tf_input2_offset;
    int dila_h = (l->w == 1) ? dilation_height_factor : dilation_width_factor;
    int fetch_size = (dila_h == 2) ? l->size * dila_h - 1 : l->size;
    int SRAM_out = l->out_layer_mem;
    int offset = l->in_layer1_mem * net->patch_size;

    fixed_point_t* mem_ptr = DATA_buf + offset;
    int padding = 128;

    for (int hin = 0; hin < layer_h - fetch_size + 1; hin += l->stride) {
        mem_ptr = DATA_buf + offset + (l->c * hin);
        if (hin == 0) {
            for (int cin = 0; cin < l->c; cin++) {
                for (int wt = 0; wt < l->size; wt++) {
                    //int out_index = (hin / l->stride) * l->c * l->size + cin * l->size + wt;
                    int out_index = (hin / l->stride) * l->c * l_size + cin * l_size + wt;
                    int ptr_index = (wt * dila_h) * l->c + cin;
                    int pass_data = (wt >= l->size) ? padding : ((wt * dila_h) + hin > layer_h - 1) ? padding : mem_ptr[ptr_index];
                    MEM_RW(1, out_index, pass_data, SRAM_out, DATA_buf, net->patch_size);
                }
                memset(DATA_buf + SRAM_out * net->patch_size + (hin / l->stride) * l->c * l_size + cin * l_size + l->size, padding, pad_size);
            }
        }
        else {
            int step = l->stride;

            for (int cin = 0; cin < l->c; cin++) {
                fixed_point_t* src = DATA_buf + SRAM_out * net->patch_size + (hin / l->stride - 1) * l->c * l_size + cin * l_size + step;
                fixed_point_t* dst = DATA_buf + SRAM_out * net->patch_size + (hin / l->stride) * l->c * l_size + cin * l_size;
                int size = (l->size - l->stride);

                memcpy(dst, src, size * sizeof(fixed_point_t));
                for (int wt = l->size - l->stride; wt < l->size; wt++) {
                    //int out_index = (hin / l->stride) * l->c * l->size + cin * l->size + wt;
                    int out_index = (hin / l->stride) * l->c * l_size + cin * l_size + wt;
                    int ptr_index = (wt * dila_h) * l->c + cin;
                    int pass_data = (wt >= l->size) ? padding : ((wt * dila_h) + hin > layer_h - 1) ? padding : mem_ptr[ptr_index];
                    MEM_RW(1, out_index, pass_data, SRAM_out, DATA_buf, net->patch_size);
                }
                memset(DATA_buf + SRAM_out * net->patch_size + (hin / l->stride) * l->c * l_size + cin * l_size + l->size, padding, pad_size);
            }
        }
    }

    for (int hin = 0; hin < layer_h - fetch_size + 1; hin += l->stride) {
        for (int cin = 0; cin < l->c; cin++) {
            for (int wt = 0; wt < l_size; wt++) {
                //int out_index = (hin / l->stride) * l->c * l->size + cin * l->size + wt;
                int out_index = (hin / l->stride) * l->c * l_size + cin * l_size + wt;
                int pass_data = MEM_RW(0, out_index, 0, SRAM_out, DATA_buf, net->patch_size);
            }
        }
    }

}

void forward_DEQUANTIZE_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t pass_data;

    int input_zero_point = l->tf_input1_offset;
    float input_scale = l->input_scale;
    int output_zero_point = l->tf_output_offset;
    float output_scale = l->output_scale;
    
    for (int cin = 0; cin < l->c; cin++) {
        for (int hin = 0; hin < l->h; hin++) {
            for (int win = 0; win < l->w; win++) {

                int data_index = hin * l->w * l->c + win * l->c + cin;
         
                pass_data = (uint8_t)MEM_RW(0, data_index, 0, l->in_layer1_mem, DATA_buf, net->patch_size);

                float output = (float)((pass_data - input_zero_point) * input_scale);
                
                int out_index = hin * l->w * l->c + win * l->c + cin;

                MEM_RW_F32(1, out_index, output, l->out_layer_mem, DATA_buf, net->patch_size);
               
            }
        }
    }
}


void forward_LOGISTIC_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    const float cutoff_upper = 16.619047164916992188f;
    const float cutoff_lower = -9.f;

    int32_t pass_data;


    int input_zero_point = l->tf_input1_offset;
    float input_scale = l->input_scale;
    int output_zero_point = l->tf_output_offset;
    float output_scale = l->output_scale;

    for (int cin = 0; cin < l->c; cin++) {
        for (int hin = 0; hin < l->h; hin++) {
            for (int win = 0; win < l->w; win++) {

                int data_index = hin * l->w * l->c + win * l->c + cin;

                if (net->use_npu_accel)
                    pass_data = (uint8_t)l->input_i8[0][data_index];
                else
                    pass_data = (uint8_t)MEM_RW(0, data_index, 0, l->in_layer1_mem, DATA_buf, net->patch_size);

                float val = (float)((pass_data - input_zero_point) * input_scale);
                float result;
                if (val > cutoff_upper) {
                    result = 1.0f;
                }
                else if (val < cutoff_lower) {
                    result = exp(val);
                }
                else {
                    result = 1.f / (1.f + exp(-val));
                }
                uint8_t output =
                    (uint8_t)(result / output_scale + output_zero_point);
                int out_index = hin * l->w * l->c + win * l->c + cin;

                if (net->use_npu_accel)
                    l->output_i8[out_index] = output;
                else
                    MEM_RW(1, out_index, output, l->out_layer_mem, DATA_buf, net->patch_size);

            }
        }
    }
}


void forward_SOFTMAX_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    int32_t pass_data = 0;

    int pad_c = l->c;
    int pad_out_c = l->out_c;
    if (net->layers[l_current - 1].NPU_on == 1 && net->use_npu_accel == 0)
        pad_c = (l->c % 4 == 0) ? l->c : ((l->c / 4) + 1) * 4;

     if (l_current != net->layer_cnt - 1 && net->layers[l_current + 1].NPU_on == 1 && net->use_npu_accel == 0)
        pad_out_c = (l->out_c % 4 == 0) ? l->out_c : ((l->out_c / 4) + 1) * 4;

    for (int cin = 0; cin < l->c; cin++) {
        for (int hin = 0; hin < l->h; hin++) {
            for (int win = 0; win < l->w; win++) {
                int data_index = hin * l->w * pad_c + win * pad_c + cin;
                if (net->use_npu_accel)
                    pass_data = (uint8_t)net->layers[l_current - 1].output_i8[data_index];
                else
                    pass_data = (uint8_t)MEM_RW(0, data_index, 0, l->in_layer1_mem, DATA_buf, net->patch_size);

                int out_index = hin * l->w * pad_out_c + win * pad_out_c + cin;
                if (net->use_npu_accel)
                    net->layers[l_current].output_i8[data_index] = pass_data;
                else
                    MEM_RW(1, out_index, pass_data, l->out_layer_mem, DATA_buf, net->patch_size);

            }
        }
    }
}


void forward_MATMUL(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int32_t pass_data;
    fixed_point_t *data_in = (fixed_point_t*)BLAI_MALLOC(l->size * l->size * sizeof(fixed_point_t));;
    fixed_point_t *weights = (fixed_point_t*)BLAI_MALLOC(l->size * l->size * sizeof(fixed_point_t));;
    struct cpu_inst_layer_t* last_l = (l_current > 0) ? &net->layers[l_current - 1] : &net->layers[l_current];
    int wh = 1;
    bool last_CONV = (last_l->type == CONVOLUTIONAL && l_current > 0);
    if (last_CONV) wh = last_l->out_w * last_l->out_h;
    int falpha = (l->activation == LEAKY) ? 9 : 0;
    int padding = 0;
    for (int hin = 0; hin < l->h; hin++) {
        for (int win = 0; win < l->w; win++) {
            for (int outin = 0; outin < l->out_c; outin++) {
                pass_data = 0;
                for (int cin = 0; cin < l->c; cin++) {
                    int data_index = hin * l->c + cin;

                    fetch_data(l, data_in, data_index, l->in_layer1_mem, 1, hin, padding, DATA_buf, net->patch_size);

                    int w_index = outin * l->c + cin;

                    weights[0] = l->weights[w_index];

                    int64_t pass_data_64 = (int64_t)pass_data + (int64_t)PE_CONV(data_in, weights, l->size, (l_current == 0) && net->unsign_input);
                    pass_data = (pass_data_64 > INT32_MAX) ? INT32_MAX : (pass_data_64 < INT32_MIN) ? INT32_MIN : pass_data_64;
                    //printf("data_index:%d data:%d weights:%d pass_data:%d\n", data_index, data_in[0], weights[0], pass_data);
                }

                // add bias
                fixed_point_t bias_8 = l->biases[outin];

                int f_bias_out = l->fbias - l->fdata - l->fweight;
                int32_t bias = fixed8_to_fixed32(bias_8, f_bias_out);
                pass_data += bias;
                if (l->activation == LINEAR) pass_data = pass_data;
                else if (l->activation == LEAKY) pass_data = PE_LEAKY(pass_data);
                else if (l->activation == RELU) pass_data = PE_RELU(pass_data);
                else if (l->activation == RELU6) pass_data = PE_RELUN(pass_data, l->fdata + l->fweight, net->relu_n);


                falpha = (l->activation == LEAKY && pass_data < 0) ? 9 : 0;

                int ftotal = l->fdata + l->fweight + falpha - l->fout;
                fixed_point_t pass_data_8;
                pass_data_8 = fixed32_to_fixed8(pass_data, ftotal);
                int out_index = hin * l->out_c + outin;

                if (out_index >= 126) {
                    printf("out_index=%d, pass_data=%d, pass_data_8=%d\r\n", out_index, pass_data, pass_data_8);
                }
                MEM_RW(1, out_index, pass_data_8, l->out_layer_mem, DATA_buf, net->patch_size);

            }
        }
    }
}


static float dequantize(int zero_point, float scale, uint8_t x)
{
    return ((float) x - zero_point) * scale;
}

void BL_DequantizeBoxEncodings(int* input_box_encodings, int idx,
    float quant_zero_point, float quant_scale,
    int length_box_encoding,
    struct CenterSizeEncoding* box_centersize) {
    //uint8_t* boxes = (uint8_t*)(input_box_encodings) + length_box_encoding * idx;
    box_centersize->y = dequantize(quant_zero_point, quant_scale, (uint8_t)input_box_encodings[length_box_encoding * idx]);
    box_centersize->x = dequantize(quant_zero_point, quant_scale, (uint8_t)input_box_encodings[length_box_encoding * idx + 1]);
    box_centersize->h = dequantize(quant_zero_point, quant_scale, (uint8_t)input_box_encodings[length_box_encoding * idx + 2]);
    box_centersize->w = dequantize(quant_zero_point, quant_scale, (uint8_t)input_box_encodings[length_box_encoding * idx + 3]);
}

void DequantizeBoxEncodings_PSRAM(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, int SRAM_in, int idx,
    float quant_zero_point, float quant_scale,
    int length_box_encoding,
    struct CenterSizeEncoding* box_centersize, fixed_point_t* DATA_buf, int patch_size) {
    int data_index = length_box_encoding * idx;

    if (net->use_npu_accel) {
        box_centersize->y = dequantize(quant_zero_point, quant_scale, (uint8_t)l->input_i8[0][data_index]);
        box_centersize->x = dequantize(quant_zero_point, quant_scale, (uint8_t)l->input_i8[0][data_index + 1]);
        box_centersize->h = dequantize(quant_zero_point, quant_scale, (uint8_t)l->input_i8[0][data_index + 2]);
        box_centersize->w = dequantize(quant_zero_point, quant_scale, (uint8_t)l->input_i8[0][data_index + 3]);
    } else {
        box_centersize->y = dequantize(quant_zero_point, quant_scale, (uint8_t)MEM_RW(0, data_index, 0, SRAM_in, DATA_buf, patch_size));
        box_centersize->x = dequantize(quant_zero_point, quant_scale, (uint8_t)MEM_RW(0, data_index + 1, 0, SRAM_in, DATA_buf, patch_size));
        box_centersize->h = dequantize(quant_zero_point, quant_scale, (uint8_t)MEM_RW(0, data_index + 2, 0, SRAM_in, DATA_buf, patch_size));
        box_centersize->w = dequantize(quant_zero_point, quant_scale, (uint8_t)MEM_RW(0, data_index + 3, 0, SRAM_in, DATA_buf, patch_size));
    }
}

float* DequantizeClassPredictions_PSRAM(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, int SRAM_in, const int num_boxes, const int num_classes_with_background, fixed_point_t* DATA_buf, int patch_size) {
    float quant_zero_point = l->tf_input2_offset;
    float quant_scale = l->input2_scale;
    float* scores = (float*)BLAI_MALLOC(num_boxes * num_classes_with_background * sizeof(float));
    uint8_t data_in;
    for (int idx = 0; idx < num_boxes * num_classes_with_background; ++idx) {
        if (net->use_npu_accel)
            data_in = (uint8_t) l->input_i8[1][idx];
        else
            data_in = (uint8_t)MEM_RW(0, idx, 0, SRAM_in, DATA_buf, patch_size);
        scores[idx] = dequantize(quant_zero_point, quant_scale, data_in);
    }
    return scores;
}

struct index_map_t {
    float val;
    int index;
};

int dec_sort(const void *i, const void *j)
{
    float a = ((struct index_map_t *) i)->val;
    float b = ((struct index_map_t *) j)->val;

    if (a < b)
        return 1;
    else if (a > b)
        return -1;
    else
        return 0;
}

void DecreasingPartialArgSort_vector(const float* values, int num_values,
    int num_to_sort, struct index_map_t* indices) {
    qsort(indices, num_values, sizeof(struct index_map_t), dec_sort);
}

int SelectDetectionsAboveScoreThreshold_vector(const float* values, int num_boxes,
    const float threshold,
    float* keep_values,
    int* keep_indices) {
    int count = 0;
    for (int i = 0; i < num_boxes; i++)
        if (values[i] >= threshold)
            count++;
    keep_values = BLAI_MALLOC(sizeof(float)*count);
    keep_indices = BLAI_MALLOC(sizeof(int)*count);
    count = 0;
    for (int i = 0; i < num_boxes; i++) {
        if (values[i] >= threshold) {
            keep_values[count] = values[i];
            keep_indices[count++] = i;
        }
    }
    return count;
}

float ComputeIntersectionOverUnion_vector(struct BoxCornerEncoding* decoded_boxes, const int i, const int j) {

    struct BoxCornerEncoding box_i = decoded_boxes[i];
    struct BoxCornerEncoding box_j = decoded_boxes[j];
    const float area_i = (box_i.ymax - box_i.ymin) * (box_i.xmax - box_i.xmin);
    const float area_j = (box_j.ymax - box_j.ymin) * (box_j.xmax - box_j.xmin);
    if (area_i <= 0 || area_j <= 0) return 0.0;
    const float intersection_ymin = max(box_i.ymin, box_j.ymin);
    const float intersection_xmin = max(box_i.xmin, box_j.xmin);
    const float intersection_ymax = min(box_i.ymax, box_j.ymax);
    const float intersection_xmax = min(box_i.xmax, box_j.xmax);
    const float intersection_area =
        max(intersection_ymax - intersection_ymin, 0.0) *
        max(intersection_xmax - intersection_xmin, 0.0);
    return intersection_area / (area_i + area_j - intersection_area);
}

static int* NonMaxSuppressionSingleClassHelper_vector(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, const float* scores, int num_scores, int* num_selected, struct BoxCornerEncoding* decoded_boxes) {

    const int num_boxes = l->w;
    const float non_max_suppression_score_threshold = 9.99999993922529e-9f;
    const float intersection_over_union_threshold = 0.6000000238418579f;

    // threshold scores
    int *keep_indices = NULL;
    float* keep_scores = NULL;
    /*
    int num_scores_kept = SelectDetectionsAboveScoreThreshold_vector(
        scores, num_scores, non_max_suppression_score_threshold, keep_scores, keep_indices);
    */
    int num_scores_kept = 0;
    for (int i = 0; i < num_boxes; i++)
        if (scores[i] >= non_max_suppression_score_threshold)
            num_scores_kept++;
    keep_scores = BLAI_MALLOC(sizeof(float)*num_scores_kept);
    keep_indices = BLAI_MALLOC(sizeof(int)*num_scores_kept);
    num_scores_kept = 0;
    for (int i = 0; i < num_boxes; i++) {
        if (scores[i] >= non_max_suppression_score_threshold) {
            keep_scores[num_scores_kept] = scores[i];
            keep_indices[num_scores_kept++] = i;
        }
    }

    struct index_map_t* sorted_indices = BLAI_MALLOC(sizeof(struct index_map_t)*num_scores_kept);
    for (int i = 0; i < num_scores_kept; i++) {
        sorted_indices[i].index = i;
        sorted_indices[i].val = keep_scores[i];
    }
    DecreasingPartialArgSort_vector(keep_scores, num_scores_kept, num_scores_kept,
        sorted_indices);

    const int num_boxes_kept = num_scores_kept;
    const int output_size = min(num_boxes_kept, l->max_detections);

    int *selected = BLAI_MALLOC(num_boxes_kept*sizeof(int));

    int num_active_candidate = num_boxes_kept;
    uint8_t* active_box_candidate = (uint8_t*)BLAI_MALLOC(num_boxes * sizeof(uint8_t));
    for (int row = 0; row < num_boxes_kept; row++) {
        active_box_candidate[row] = 1;
    }
    int count = 0;
    for (int i = 0; i < num_boxes_kept; ++i) {
        if (num_active_candidate == 0 || count >= output_size)
            break;
        if (active_box_candidate[i] == 1) {
            selected[count++] = keep_indices[sorted_indices[i].index];
//            printf("Selected[%d]=%d, sorted_indices=%d, val=%f\r\n", count-1, selected[count-1], sorted_indices[i].index, sorted_indices[i].val);
            active_box_candidate[i] = 0;
            num_active_candidate--;
        }
        else {
            continue;
        }
        for (int j = i + 1; j < num_boxes_kept; ++j) {
            if (active_box_candidate[j] == 1) {
                float intersection_over_union = ComputeIntersectionOverUnion_vector(
                    decoded_boxes, keep_indices[sorted_indices[i].index],
                    keep_indices[sorted_indices[j].index]);

                if (intersection_over_union > intersection_over_union_threshold) {
                    active_box_candidate[j] = 0;
                    num_active_candidate--;
                }
            }
        }
    }
    BLAI_FREE(active_box_candidate);
    BLAI_FREE(keep_scores);
    BLAI_FREE(keep_indices);
    BLAI_FREE(sorted_indices);

    *num_selected = count;
    return selected;
}

void NonMaxSuppressionMultiClassFastHelper_vector(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, float* scores, struct BoxCornerEncoding* decoded_boxes, struct BoxCornerEncoding* detection_boxes, float* detection_classes, float* detection_scores, float* num_detections) {

    const int num_boxes = l->w;
    const int num_classes = l->classes;
    const int max_categories_per_anchor = l->max_classes_per_detection;
    const int num_classes_with_background = l->cn[0];
    // The row index offset is 1 if background class is included and 0 otherwise.
    int label_offset = num_classes_with_background - num_classes;

    const int num_categories_per_anchor = min(max_categories_per_anchor, num_classes);
    float* max_scores = BLAI_MALLOC(num_boxes*sizeof(float));
    struct index_map_t* sorted_class_indices= BLAI_MALLOC(num_boxes*num_classes*sizeof(struct index_map_t));
    for (int row = 0; row < num_boxes; row++) {
        const float* box_scores =
            scores + row * num_classes_with_background + label_offset;
        struct index_map_t* class_indices = sorted_class_indices + row * num_classes;
        for (int i = 0; i < num_classes; i++) {
            class_indices[i].index = i;
            class_indices[i].val = box_scores[i];
        }
        DecreasingPartialArgSort_vector(box_scores, num_classes, num_categories_per_anchor,
            class_indices);
        max_scores[row] = box_scores[class_indices[0].index];
    }
    // Perform non-maximal suppression on max scores
    int num_selected = 0;
    int* selected = NonMaxSuppressionSingleClassHelper_vector(net, l, max_scores, num_boxes, &num_selected, decoded_boxes);

    int output_box_index = 0;
    for (int i = 0; i < num_selected; i++) {
        int selected_index = selected[i];
        const float* box_scores =
            scores + selected_index * num_classes_with_background + label_offset;
        const struct index_map_t* class_indices =
            sorted_class_indices + selected_index * num_classes;
        for (int col = 0; col < num_categories_per_anchor; ++col) {
            int box_offset = num_categories_per_anchor * output_box_index + col;
            // detection_boxes
            detection_boxes[box_offset] = decoded_boxes[selected_index];
            // detection_classes
            detection_classes[box_offset] = class_indices[col].index;
            // detection_scores
            detection_scores[box_offset] = box_scores[class_indices[col].index];

            output_box_index++;
        }
    }
    num_detections[0] = output_box_index;

    BLAI_FREE(sorted_class_indices);
    BLAI_FREE(max_scores);
    BLAI_FREE(selected);
}

/*
class Dequantizer {
public:
    Dequantizer(int zero_point, float scale)
        : zero_point_(zero_point), scale_(scale) {}
    float operator()(uint8_t x) {
        return (static_cast<float>(x) - zero_point_) * scale_;
    }

private:
    int zero_point_;
    float scale_;
};

*/
void forward_SSD_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current, struct BLAI_data_t *BL_data, const char** name_list, blai_inference_cb result_cb)
{
    //DecodeCenterSizeBoxes
    const int num_boxes = l->w;
    struct CenterSizeEncoding box_centersize;
    struct CenterSizeEncoding scale_values = { 0 };
    scale_values.x = l->x_scale;
    scale_values.y = l->y_scale;
    scale_values.w = l->w_scale;
    scale_values.h = l->h_scale;
    struct CenterSizeEncoding anchor;
//    vector<BoxCornerEncoding> decoded_boxes;
    struct BoxCornerEncoding *decoded_boxes = BLAI_MALLOC(sizeof(struct BoxCornerEncoding)*num_boxes);
    int BOX_SRAM_in = l->in_layer1_mem;
    int CLASS_PREDICTION_SRAM_in = l->in_layer2_mem;
    const int num_classes_with_background = l->cn[0];

    for (int idx = 0; idx < num_boxes; ++idx) {
        DequantizeBoxEncodings_PSRAM(
            net, l, BOX_SRAM_in, idx,
            (float) l->tf_input1_offset,
            (float) l->input_scale,
            l->c, &box_centersize, DATA_buf, net->patch_size);
        BL_DequantizeBoxEncodings(
            l->weights, idx,
            (float) l->anchors_offset,
            (float) l->input3_scale, 4,
            &anchor);

        float ycenter = box_centersize.y / scale_values.y * anchor.h + anchor.y;
        float xcenter = box_centersize.x / scale_values.x * anchor.w + anchor.x;
        float half_h =
            0.5f * ((float) exp(box_centersize.h / scale_values.h)) * anchor.h;
        float half_w =
            0.5f * ((float) exp(box_centersize.w / scale_values.w)) * anchor.w;

        decoded_boxes[idx].ymin = ycenter - half_h;
        decoded_boxes[idx].xmin = xcenter - half_w;
        decoded_boxes[idx].ymax = ycenter + half_h;
        decoded_boxes[idx].xmax = xcenter + half_w;
    }

    // NonMaxSuppressionMultiClass
    const int num_classes = l->classes;
    int output_size = l->max_detections * 4;
    struct BoxCornerEncoding* detection_boxes = (struct BoxCornerEncoding*)BLAI_MALLOC(output_size * sizeof(struct BoxCornerEncoding));
    float* detection_classes = (float*)BLAI_MALLOC(output_size * sizeof(float));
    float* detection_scores = (float*)BLAI_MALLOC(output_size * sizeof(float));
    float* num_detections = (float*)BLAI_MALLOC(output_size * sizeof(float));
    float* scores = DequantizeClassPredictions_PSRAM(net, l, CLASS_PREDICTION_SRAM_in, num_boxes, num_classes_with_background, DATA_buf, net->patch_size);

    NonMaxSuppressionMultiClassFastHelper_vector(net, l, &scores[0], decoded_boxes, detection_boxes, detection_classes, detection_scores, num_detections);

    int names_size = 0;

    for (int i = 0; i < num_detections[0]; i++) {
        struct blai_result_t result;

        BL_LOGI("%s: %.0f%%", name_list[(int)detection_classes[i]], detection_scores[i] * 100);
        BL_LOGI("\t(left_x: %4.0f   top_y: %4.0f   width: %4.0f   height: %4.0f)\n", round(detection_boxes[i].xmin * BL_data->image_width)
            , round(detection_boxes[i].ymin * BL_data->image_height), round(detection_boxes[i].xmax * BL_data->image_width), round(detection_boxes[i].ymax * BL_data->image_height));
        result.r.objdet.rect.x = round(detection_boxes[i].xmin * BL_data->image_width);
        result.r.objdet.rect.y = round(detection_boxes[i].ymin * BL_data->image_height);
        result.r.objdet.rect.w = round(detection_boxes[i].xmax * BL_data->image_width);
        result.r.objdet.rect.h = round(detection_boxes[i].ymax * BL_data->image_height);
        result.r.objdet.best_class = (int)detection_classes[i];
        result.r.objdet.prob = detection_scores[i] * 100;
        result.app_type = OBJECT_DETECTION;
        result_cb(&result);
    }

    BLAI_FREE(decoded_boxes);
    BLAI_FREE(detection_boxes);
    BLAI_FREE(detection_classes);
    BLAI_FREE(detection_scores);
    BLAI_FREE(num_detections);
    BLAI_FREE(scores);
}


