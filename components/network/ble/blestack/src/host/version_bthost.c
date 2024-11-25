/** @file
 * @brief BT Host Version.
 */
/*
 * Copyright (c) 2021-2022 Bouffalolab Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "version_bthost.h"
static const char *version_bthost __attribute__((used, section(".version.bthost"))) = "component_version_bthost_" BT_HOST_VERSION_MACSW_NUMBER;

