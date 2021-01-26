/*----------------------------------------------------------------------------
 * Copyright (c) <2019>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

/*
 * coap.h -- main header file for CoAP stack of libcoap
 *
 * Copyright (C) 2010-2012,2015-2017 Olaf Bergmann <bergmann@tzi.org>
 *               2015 Carsten Schoenert <c.schoenert@t-online.de>
 *
 * This file is part of the CoAP library libcoap. Please see README for terms
 * of use.
 */

#ifndef COAP_H_
#define COAP_H_

/* Define the address where bug reports for libcoap should be sent. */
#define LIBCOAP_PACKAGE_BUGREPORT "libcoap-developers@lists.sourceforge.net"

/* Define the full name of libcoap. */
#define LIBCOAP_PACKAGE_NAME "libcoap"

/* Define the full name and version of libcoap. */
#define LIBCOAP_PACKAGE_STRING "libcoap 4.2.0"

/* Define the home page for libcoap. */
#define LIBCOAP_PACKAGE_URL "https://libcoap.net/"

/* Define the version of libcoap this file belongs to. */
#define LIBCOAP_PACKAGE_VERSION "4.2.0"

#ifdef __cplusplus
extern "C" {
#endif

#include "libcoap.h"

#include "address.h"
#include "async.h"
#include "bits.h"
#include "block.h"
#include "coap_dtls.h"
#include "coap_event.h"
#include "coap_io.h"
#include "coap_time.h"
#include "coap_debug.h"
#include "encode.h"
#include "coap2/mem.h"
#include "net.h"
#include "option.h"
#include "pdu.h"
#include "prng.h"
#include "resource.h"
#include "str.h"
#include "subscribe.h"
#include "uri.h"

#ifdef __cplusplus
}
#endif

#endif /* COAP_H_ */
