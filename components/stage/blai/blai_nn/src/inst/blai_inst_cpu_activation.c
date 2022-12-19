#include "blai_core.h"
#include "blai_def_internal.h"

int32_t PE_LEAKY(int32_t pass_data) {
    int falpha = 9;
    fixed_point_t alpha = float_to_fixed(0.1, falpha);
    return pass_data = (pass_data > 0) ? pass_data : alpha * pass_data;
}

int32_t PE_RELU(int32_t pass_data) {
    return pass_data = (pass_data > 0) ? pass_data : 0;
}

int32_t PE_RELU6(int32_t pass_data, int fshift) {
    int32_t fixed_6 = fixed32_to_fixed32(6, -fshift);
    int32_t pass_data_ = (pass_data > 0) ? pass_data : 0;
    pass_data_ = (pass_data_ > fixed_6) ? fixed_6 : pass_data_;
    return pass_data_;
}
int32_t PE_RELUN(int32_t pass_data, int fshift, int n) {
    int32_t fixed_6 = fixed32_to_fixed32(n, -fshift);
    int32_t pass_data_ = (pass_data > 0) ? pass_data : 0;
    pass_data_ = (pass_data_ > fixed_6) ? fixed_6 : pass_data_;
    return pass_data_;
}
fixed_point_t PE_MISH(int32_t pass_data, int fin, int fout) {
    // MISH look up table
    fixed_point_t  mish_d[256] = { 0, -5, -9, -14, -18, -22, -26, -30, -33, -37, -40, -43, -46, -49, -52, -54, -57, -59, -61, -63, -65, -66, -68, -69, -71, -72, -73, -74, -75, -76, -77, -77, -78, -78, -78, -79, -79, -79, -79, -79, -79, -79, -79, -78, -78, -78, -77, -77, -76, -76, -75, -75, -74, -73, -73, -72, -71, -70, -70, -69, -68, -67, -66, -66, -65, -64, -63, -62, -61, -60, -59, -58, -58, -57, -56, -55, -54, -53, -52, -51, -50, -50, -49, -48, -47, -46, -45, -44, -44, -43, -42, -41, -40, -40, -39, -38, -37, -37, -36, -35, -34, -34, -33, -32, -32, -31, -30, -30, -29, -28, -28, -27, -27, -26, -26, -25, -24, -24, -23, -23, -22, -22, -21, -21, -20, -20, -19, -19, -19, -18, -18, -17, -17, -17, -16, -16, -15, -15, -15, -14, -14, -14, -13, -13, -13, -12, -12, -12, -12, -11, -11, -11, -10, -10, -10, -10, -9, -9, -9, -9, -9, -8, -8, -8, -8, -8, -7, -7, -7, -7, -7, -7, -6, -6, -6, -6, -6, -6, -5, -5, -5, -5, -5, -5, -5, -5, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    // MISH input: -8~0  output: -1~0  (x = expf(x) - 1)
    //int f_mish = 28;
    int f_mish = 5;
    int shift = fin - f_mish;
    int32_t f_fixed_in = fixed32_to_fixed32(pass_data, shift);
    // mapping input to LUT index (23 = 16 + 7) max 2^31 / 2^16 / 2^7 = 2^8
    //int select = (-1 * (f_fixed_in >> 23) - 1);
    int select = (-1 * (f_fixed_in)-1);
    int index = (f_fixed_in == 0) ? 0 : (select >= 0 && select < 256) ? select : 255;

    fixed_point_t mish_out = mish_d[index];
    int fshift = 7 - fout;
    fixed_point_t mish_out_shfit = fixed8_to_fixed8(mish_out, fshift);
    return mish_out_shfit;
}
