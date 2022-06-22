#include <stdbool.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <bl_sec.h>

#include <mbedtls/bignum.h>
#include <mbedtls_port_bignum.h>
#include <mbedtls/platform.h>

#define BIGNUM_COMMON_PORTED

#ifdef BL602
#include <bl602_glb.h>
#include <bl602_sec_eng.h>
#elif defined BL702
#include <bl702_glb.h>
#include <bl702_sec_eng.h>
#else
#undef BIGNUM_COMMON_PORTED
#endif

#define BL_MPI_LARGE_NUM_SOFTWARE_MPI

#define BIGNUM_COMMON_DBG 0

#define BIGNUM_COMMON_MAX(x, y) ((x) > (y) ? (x) : (y))

#define MBEDTLS_INTERNAL_VALIDATE_RET( cond, ret )  \
    do {                                            \
        if( !(cond) )                               \
        {                                           \
            return( ret );                          \
        }                                           \
    } while( 0 )
#define MPI_VALIDATE_RET( cond )                                       \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_MPI_BAD_INPUT_DATA )

#ifdef BIGNUM_COMMON_PORTED

static size_t mpi_reg_size_to_words(int reg_size);

#if BIGNUM_COMMON_DBG
static void dump_bn(const char *tag, const mbedtls_mpi *bn)
{
    const size_t buf_len = 4096 + 1;
    char *buf = (char *)pvPortMalloc(buf_len);
    if (!buf)
        return;
    size_t olen;
    if (tag)
        printf("%s: ", tag);
    if (bn) {
        mbedtls_mpi_write_string(bn, 16, buf, buf_len, &olen);
    } else {
        strcpy(buf, "<null>");
    }
    puts(buf);
    puts("\r\n");
    vPortFree(buf);
}

static void dump_reg(const char *tag, int s, uint8_t reg)
{
    mbedtls_mpi num;
    mbedtls_mpi_init(&num);
    static uint32_t tmp_buf[512/4];
    printf("reg %s:\r\n", tag);
    size_t words = mpi_reg_size_to_words(s);
    memset(tmp_buf, 0, sizeof(tmp_buf));
    Sec_Eng_PKA_Read_Data(s, reg, (void *)tmp_buf, words);
    if (mbedtls_mpi_read_binary(&num, (uint8_t *)tmp_buf, words * 4)) {
        printf("<err>\r\n");
        return;
    }
    dump_bn(NULL, &num);
    mbedtls_mpi_free(&num);
}
#else
#define dump_bn(...) do {} while (0)
#define dump_reg(...) do {} while (0)
#endif

static size_t mpi_words(const mbedtls_mpi *mpi)
{
    for (size_t i = mpi->n; i > 0; i--) {
        if (mpi->p[i - 1] != 0) {
            return i;
        }
    }
    return 0;
}

static int mpi_words_to_reg_size(size_t words)
{
    size_t bytes = words * 4;
    if (bytes <= 8) return SEC_ENG_PKA_REG_SIZE_8;
    else if (bytes <= 16) return SEC_ENG_PKA_REG_SIZE_16;
    else if (bytes <= 32) return SEC_ENG_PKA_REG_SIZE_32;
    else if (bytes <= 64) return SEC_ENG_PKA_REG_SIZE_64;
    else if (bytes <= 96) return SEC_ENG_PKA_REG_SIZE_96;
    else if (bytes <= 128) return SEC_ENG_PKA_REG_SIZE_128;
    else if (bytes <= 192) return SEC_ENG_PKA_REG_SIZE_192;
    else if (bytes <= 256) return SEC_ENG_PKA_REG_SIZE_256;
    else if (bytes <= 384) return SEC_ENG_PKA_REG_SIZE_384;
    else if (bytes <= 512) return SEC_ENG_PKA_REG_SIZE_512;
    else return 0; // too large
}

static size_t mpi_reg_size_to_words(int reg_size)
{
    if (reg_size == SEC_ENG_PKA_REG_SIZE_8) return 8 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_16) return 16 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_32) return 32 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_64) return 64 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_96) return 96 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_128) return 128 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_192) return 192 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_256) return 256 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_384) return 384 / 4;
    else if (reg_size == SEC_ENG_PKA_REG_SIZE_512) return 512 / 4;
    else return 0;
}

// clear upper bits starting from bit(inclusion, zero-indexed)
int mpi_clear_upper_bits(mbedtls_mpi *X, size_t bit)
{
    const size_t limb_bits = sizeof(mbedtls_mpi_uint) * 8;

    if (!X)
        return -1;
    size_t higher_limb_idx = (bit + limb_bits - 1) / limb_bits;

    for (size_t i = higher_limb_idx; i < X->n; ++i)
        X->p[i] = 0;

    size_t bit_offset = bit % limb_bits;
    if (bit_offset && higher_limb_idx - 1 < X->n) {
        mbedtls_mpi_uint mask = 1;
        mask <<= bit_offset;
        mask -= 1;
        X->p[higher_limb_idx - 1] &= mask;
    }

    return 0;
}

int mpi_mod_2n(mbedtls_mpi *X, mbedtls_mpi_uint n)
{
    int ret = 0;
    mbedtls_mpi R;
    if (!X)
        return -1;

    mpi_clear_upper_bits(X, n);
    mbedtls_mpi_init(&R);
    if (X->s < 0) {
        MBEDTLS_MPI_CHK(mbedtls_mpi_set_bit(&R, n, 1));
        MBEDTLS_MPI_CHK(mbedtls_mpi_add_mpi(X, X, &R));
        MBEDTLS_MPI_CHK(mbedtls_mpi_set_bit(X, n, 0));
    }
cleanup:
    mbedtls_mpi_free(&R);
    return ret;
}

int mpi_hensel_quad_mod_inv_prime_n(mbedtls_mpi *U, const mbedtls_mpi *a, mbedtls_mpi_uint m)
{
    int ret;
    if (!(U && a && m))
        return -1;

    if ((a->p[0] & 1) == 0)
        return -1;

    mbedtls_mpi tmp;
    mbedtls_mpi_init(&tmp);

    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(U, 1));
    for (size_t i = 2; i < m; i <<= 1) {
        MBEDTLS_MPI_CHK(mbedtls_mpi_mul_mpi(&tmp, U, U));
        MBEDTLS_MPI_CHK(mpi_mod_2n(&tmp, i));
        MBEDTLS_MPI_CHK(mbedtls_mpi_mul_mpi(&tmp, &tmp, a));
        MBEDTLS_MPI_CHK(mpi_mod_2n(&tmp, i));
        MBEDTLS_MPI_CHK(mbedtls_mpi_shift_l(U, 1));
        MBEDTLS_MPI_CHK(mbedtls_mpi_sub_mpi(U, U, &tmp));
    }
    MBEDTLS_MPI_CHK(mbedtls_mpi_mul_mpi(&tmp, U, U));
    MBEDTLS_MPI_CHK(mpi_mod_2n(&tmp, m));
    MBEDTLS_MPI_CHK(mbedtls_mpi_mul_mpi(&tmp, &tmp, a));
    MBEDTLS_MPI_CHK(mpi_mod_2n(&tmp, m));
    MBEDTLS_MPI_CHK(mbedtls_mpi_shift_l(U, 1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_sub_mpi(U, U, &tmp));
    MBEDTLS_MPI_CHK(mpi_mod_2n(U, m));

    mbedtls_mpi zero;
    mbedtls_mpi_uint z_ = 0;
    zero.s = 1;
    zero.n = 1;
    zero.p = &z_;
    MBEDTLS_MPI_CHK(mbedtls_mpi_sub_mpi(U, &zero, U));
    MBEDTLS_MPI_CHK(mpi_mod_2n(U, m));

cleanup:
    mbedtls_mpi_free(&tmp);

    return 0;
}

int bl_mpi_exp_mod_wo_lock(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *E, const mbedtls_mpi *N, mbedtls_mpi *_RN)
{
    int ret;
    uint8_t *tmp;
    int wsize;
    int i, j;
    MPI_VALIDATE_RET(X != NULL);
    MPI_VALIDATE_RET(A != NULL);
    MPI_VALIDATE_RET(E != NULL);
    MPI_VALIDATE_RET(N != NULL);

    const size_t a_words = mpi_words(A);
    const size_t e_words = mpi_words(E);
    const size_t n_words = mpi_words(N);

    const size_t m_words = BIGNUM_COMMON_MAX(a_words, BIGNUM_COMMON_MAX(e_words, n_words));

    const int reg_size = mpi_words_to_reg_size(m_words);
    const int words = mpi_reg_size_to_words(reg_size);
    const int reg_size_N = mpi_words_to_reg_size(n_words);
    const int words_N = mpi_reg_size_to_words(reg_size_N);
    const int reg_size_E = mpi_words_to_reg_size(e_words);
    const int words_E = mpi_reg_size_to_words(reg_size_E);
    const int d_reg_size = mpi_words_to_reg_size(mpi_reg_size_to_words(reg_size) * 2);
    mbedtls_mpi PrimeN_new;
    mbedtls_mpi *PrimeN = &PrimeN_new;
    int reg_idx_E;
    const int e_bitlen = mbedtls_mpi_bitlen(E);
    int e_bit_idx;
    bool first = true;
    const int sN = reg_size_N;

    // TODO more precise check
    if (reg_size > SEC_ENG_PKA_REG_SIZE_256) {
#ifdef BL_MPI_LARGE_NUM_SOFTWARE_MPI
        return mbedtls_mpi_exp_mod_original(X, A, E, N, _RN);
#else
        return MBEDTLS_ERR_MPI_NOT_ACCEPTABLE;
#endif
    }

    if (mbedtls_mpi_cmp_int(N, 0) <= 0 || (N->p[0] & 1) == 0)
        return MBEDTLS_ERR_MPI_BAD_INPUT_DATA;

    if (mbedtls_mpi_cmp_int(E, 0) < 0)
        return MBEDTLS_ERR_MPI_BAD_INPUT_DATA;

    if (mbedtls_mpi_cmp_int(E, 0) == 0) {
        return mbedtls_mpi_lset(X, 1);
    }

    if ((ret = mbedtls_mpi_grow(X, words))) {
        return ret;
    }

    if ((tmp = mbedtls_calloc(1, words * 4)) == NULL) {
        return MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }

    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();

    mbedtls_mpi_init(&PrimeN_new);

    if (_RN == NULL || _RN->p == NULL) {
        MBEDTLS_MPI_CHK(mpi_hensel_quad_mod_inv_prime_n(&PrimeN_new, N, words_N * 32));
        if (_RN != NULL) {
            MBEDTLS_MPI_CHK(mbedtls_mpi_copy(_RN, PrimeN));
        }
    } else {
        PrimeN = _RN;
    }

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(N, tmp, words_N * 4));
    Sec_Eng_PKA_Write_Data(sN, 0, (uint32_t *)tmp, words_N, 1);
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(A, tmp, words * 4));
    Sec_Eng_PKA_Write_Data(reg_size, 2, (uint32_t *)tmp, words, 1);
    Sec_Eng_PKA_GF2Mont(sN, 3, reg_size, 2, words_N * 32, d_reg_size, 2, sN, 0);

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(PrimeN, tmp, words_N * 4));
    Sec_Eng_PKA_Write_Data(sN, 1, (uint32_t *)tmp, words_N, 1);

    i = e_bitlen;
    wsize = i > 79 ? 4 : i > 23 ? 3 : 1;
    if (words_N > 128 / 4 && wsize > 1)
        wsize = 3;

    if (wsize > 1) {
        int ri = 5;
        Sec_Eng_PKA_Move_Data(sN, 4, sN, 3, 1);
        Sec_Eng_PKA_MSQR(sN, 3, sN, 3, sN, 0, 1);

        j = (1 << (wsize - 1)) - 1;
        for (i = 0; i < j; ++i, ++ri)
            Sec_Eng_PKA_MMUL(sN, ri, sN, ri - 1, sN, 3, sN, 0, 1);
    } else {
        reg_idx_E = (4 * words_N + words_E - 1) / words_E;
        MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(E, tmp, words_E * 4));
        Sec_Eng_PKA_Write_Data(reg_size_E, reg_idx_E, (uint32_t *)tmp, words_E, 1);

        Sec_Eng_PKA_MEXP(sN, 2, sN, 3, reg_size_E, reg_idx_E, sN, 0, 1);
        goto cvt_back;
    }

    e_bit_idx = e_bitlen - 1;
    while (e_bit_idx >= 0) {
        if (mbedtls_mpi_get_bit(E, e_bit_idx) == 0) {
            Sec_Eng_PKA_MSQR(sN, 2, sN, 2, sN, 0, 1);
            e_bit_idx--;
        } else {
            int bitstring_len = wsize;
            int bitstring_val = 0;
            if (e_bit_idx + 1 < bitstring_len)
                bitstring_len = e_bit_idx + 1;

            while (bitstring_len > 0) {
                if (mbedtls_mpi_get_bit(E, e_bit_idx - bitstring_len + 1))
                    break;
                bitstring_len--;
            }
            for (i = 0; i < bitstring_len; ++i) {
                int cur_bit = mbedtls_mpi_get_bit(E, e_bit_idx - i);
                if (i == 0)
                    bitstring_val = cur_bit;
                else
                    bitstring_val = (bitstring_val << 1) + cur_bit;
                if (!first)
                    Sec_Eng_PKA_MSQR(sN, 2, sN, 2, sN, 0, 1);
            }
            i = ((bitstring_val - 1) >> 1)  + 4;
            if (first) {
                Sec_Eng_PKA_Move_Data(sN, 2, sN, i, 1);
                first = false;
            } else {
                Sec_Eng_PKA_MMUL(sN, 2, sN, 2, sN, i, sN, 0, 1);
            }

            e_bit_idx -= bitstring_len;
        }
    }

cvt_back:
    memset(tmp, 0, words_N * 4);
    tmp[words_N * 4 - 1] = 1;
    Sec_Eng_PKA_Write_Data(sN, 3, (uint32_t *)tmp, words_N, 1);
    Sec_Eng_PKA_MMUL(sN, 4, sN, 2, sN, 3, sN, 0, 1);
    Sec_Eng_PKA_Read_Data(sN, 4, (uint32_t *)tmp, words_N);
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(X, tmp, words_N * 4));

    // Compensate for negative X
    if (A->s == -1 && (E->p[0] & 1) != 0) {
        X->s = -1;
        MBEDTLS_MPI_CHK(mbedtls_mpi_add_mpi(X, N, X));
    } else {
        X->s = 1;
    }

cleanup:
    mbedtls_free(tmp);
    mbedtls_mpi_free(&PrimeN_new);
    return ret;
}

int bl_mpi_exp_mod(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *E, const mbedtls_mpi *N, mbedtls_mpi *_RN)
{
    int ret;
    if (bl_sec_pka_mutex_take())
        return -1;
    ret = bl_mpi_exp_mod_wo_lock(X, A, E, N, _RN);
    if (bl_sec_pka_mutex_give())
        return -1;
    return ret;
}

#endif // BIGNUM_COMMON_PORTED
