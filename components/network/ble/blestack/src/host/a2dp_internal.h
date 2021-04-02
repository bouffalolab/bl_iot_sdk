/** @file
 * @brief Advance Audio Distribution Profile Internal header.
 */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 /** @brief A2DP Codec Specific Information */
struct bt_a2dp_codec_info {
    /** Sampling Frequency */
    uint8_t sampling_frequency:4;
    /** Channel Mode */
    uint8_t channel_mode:4;
    /** Block Length */
    uint8_t block_length:4;
    /** Subbands */
    uint8_t subbands:2;
    /** Allocation Method */
    uint8_t allocation_method:2;
    /** Minimum Bitpool Value */
    uint8_t minimum_bitpool;
    /** Maximum Bitpool Value */
    uint8_t maximum_bitpool;
} __packed;

struct bt_a2dp_codec_capability
{
    uint8_t media_type;
    uint8_t codec_type;
    struct bt_a2dp_codec_info codec_info;
} __packed;

/* To be called when first SEP is being registered */
int bt_a2dp_init(void);
