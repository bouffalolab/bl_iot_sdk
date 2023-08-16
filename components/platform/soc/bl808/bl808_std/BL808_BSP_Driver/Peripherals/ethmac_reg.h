/*
 * Copyright (c) 2016-2023 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 #ifndef  __ETHMAC_REG_H__
 #define  __ETHMAC_REG_H__

#include "bl808.h"

/* 0x0 : MODE */
#define ETHMAC_MODE_OFFSET                                      (0x0)
#define ETHMAC_RXEN                                             ETHMAC_RXEN
#define ETHMAC_RXEN_POS                                         (0U)
#define ETHMAC_RXEN_LEN                                         (1U)
#define ETHMAC_RXEN_MSK                                         (((1U<<ETHMAC_RXEN_LEN)-1)<<ETHMAC_RXEN_POS)
#define ETHMAC_RXEN_UMSK                                        (~(((1U<<ETHMAC_RXEN_LEN)-1)<<ETHMAC_RXEN_POS))
#define ETHMAC_TXEN                                             ETHMAC_TXEN
#define ETHMAC_TXEN_POS                                         (1U)
#define ETHMAC_TXEN_LEN                                         (1U)
#define ETHMAC_TXEN_MSK                                         (((1U<<ETHMAC_TXEN_LEN)-1)<<ETHMAC_TXEN_POS)
#define ETHMAC_TXEN_UMSK                                        (~(((1U<<ETHMAC_TXEN_LEN)-1)<<ETHMAC_TXEN_POS))
#define ETHMAC_NOPRE                                            ETHMAC_NOPRE
#define ETHMAC_NOPRE_POS                                        (2U)
#define ETHMAC_NOPRE_LEN                                        (1U)
#define ETHMAC_NOPRE_MSK                                        (((1U<<ETHMAC_NOPRE_LEN)-1)<<ETHMAC_NOPRE_POS)
#define ETHMAC_NOPRE_UMSK                                       (~(((1U<<ETHMAC_NOPRE_LEN)-1)<<ETHMAC_NOPRE_POS))
#define ETHMAC_BRO                                              ETHMAC_BRO
#define ETHMAC_BRO_POS                                          (3U)
#define ETHMAC_BRO_LEN                                          (1U)
#define ETHMAC_BRO_MSK                                          (((1U<<ETHMAC_BRO_LEN)-1)<<ETHMAC_BRO_POS)
#define ETHMAC_BRO_UMSK                                         (~(((1U<<ETHMAC_BRO_LEN)-1)<<ETHMAC_BRO_POS))
#define ETHMAC_PRO                                              ETHMAC_PRO
#define ETHMAC_PRO_POS                                          (5U)
#define ETHMAC_PRO_LEN                                          (1U)
#define ETHMAC_PRO_MSK                                          (((1U<<ETHMAC_PRO_LEN)-1)<<ETHMAC_PRO_POS)
#define ETHMAC_PRO_UMSK                                         (~(((1U<<ETHMAC_PRO_LEN)-1)<<ETHMAC_PRO_POS))
#define ETHMAC_IFG                                              ETHMAC_IFG
#define ETHMAC_IFG_POS                                          (6U)
#define ETHMAC_IFG_LEN                                          (1U)
#define ETHMAC_IFG_MSK                                          (((1U<<ETHMAC_IFG_LEN)-1)<<ETHMAC_IFG_POS)
#define ETHMAC_IFG_UMSK                                         (~(((1U<<ETHMAC_IFG_LEN)-1)<<ETHMAC_IFG_POS))
#define ETHMAC_FULLD                                            ETHMAC_FULLD
#define ETHMAC_FULLD_POS                                        (10U)
#define ETHMAC_FULLD_LEN                                        (1U)
#define ETHMAC_FULLD_MSK                                        (((1U<<ETHMAC_FULLD_LEN)-1)<<ETHMAC_FULLD_POS)
#define ETHMAC_FULLD_UMSK                                       (~(((1U<<ETHMAC_FULLD_LEN)-1)<<ETHMAC_FULLD_POS))
#define ETHMAC_CRCEN                                            ETHMAC_CRCEN
#define ETHMAC_CRCEN_POS                                        (13U)
#define ETHMAC_CRCEN_LEN                                        (1U)
#define ETHMAC_CRCEN_MSK                                        (((1U<<ETHMAC_CRCEN_LEN)-1)<<ETHMAC_CRCEN_POS)
#define ETHMAC_CRCEN_UMSK                                       (~(((1U<<ETHMAC_CRCEN_LEN)-1)<<ETHMAC_CRCEN_POS))
#define ETHMAC_HUGEN                                            ETHMAC_HUGEN
#define ETHMAC_HUGEN_POS                                        (14U)
#define ETHMAC_HUGEN_LEN                                        (1U)
#define ETHMAC_HUGEN_MSK                                        (((1U<<ETHMAC_HUGEN_LEN)-1)<<ETHMAC_HUGEN_POS)
#define ETHMAC_HUGEN_UMSK                                       (~(((1U<<ETHMAC_HUGEN_LEN)-1)<<ETHMAC_HUGEN_POS))
#define ETHMAC_PAD                                              ETHMAC_PAD
#define ETHMAC_PAD_POS                                          (15U)
#define ETHMAC_PAD_LEN                                          (1U)
#define ETHMAC_PAD_MSK                                          (((1U<<ETHMAC_PAD_LEN)-1)<<ETHMAC_PAD_POS)
#define ETHMAC_PAD_UMSK                                         (~(((1U<<ETHMAC_PAD_LEN)-1)<<ETHMAC_PAD_POS))
#define ETHMAC_RECSMALL                                         ETHMAC_RECSMALL
#define ETHMAC_RECSMALL_POS                                     (16U)
#define ETHMAC_RECSMALL_LEN                                     (1U)
#define ETHMAC_RECSMALL_MSK                                     (((1U<<ETHMAC_RECSMALL_LEN)-1)<<ETHMAC_RECSMALL_POS)
#define ETHMAC_RECSMALL_UMSK                                    (~(((1U<<ETHMAC_RECSMALL_LEN)-1)<<ETHMAC_RECSMALL_POS))
#define ETHMAC_RMIIEN                                           ETHMAC_RMIIEN
#define ETHMAC_RMIIEN_POS                                       (17U)
#define ETHMAC_RMIIEN_LEN                                       (1U)
#define ETHMAC_RMIIEN_MSK                                       (((1U<<ETHMAC_RMIIEN_LEN)-1)<<ETHMAC_RMIIEN_POS)
#define ETHMAC_RMIIEN_UMSK                                      (~(((1U<<ETHMAC_RMIIEN_LEN)-1)<<ETHMAC_RMIIEN_POS))

/* 0x4 : INT_SOURCE */
#define ETHMAC_INT_SOURCE_OFFSET                                (0x4)
#define ETHMAC_TXB                                              ETHMAC_TXB
#define ETHMAC_TXB_POS                                          (0U)
#define ETHMAC_TXB_LEN                                          (1U)
#define ETHMAC_TXB_MSK                                          (((1U<<ETHMAC_TXB_LEN)-1)<<ETHMAC_TXB_POS)
#define ETHMAC_TXB_UMSK                                         (~(((1U<<ETHMAC_TXB_LEN)-1)<<ETHMAC_TXB_POS))
#define ETHMAC_TXE                                              ETHMAC_TXE
#define ETHMAC_TXE_POS                                          (1U)
#define ETHMAC_TXE_LEN                                          (1U)
#define ETHMAC_TXE_MSK                                          (((1U<<ETHMAC_TXE_LEN)-1)<<ETHMAC_TXE_POS)
#define ETHMAC_TXE_UMSK                                         (~(((1U<<ETHMAC_TXE_LEN)-1)<<ETHMAC_TXE_POS))
#define ETHMAC_RXB                                              ETHMAC_RXB
#define ETHMAC_RXB_POS                                          (2U)
#define ETHMAC_RXB_LEN                                          (1U)
#define ETHMAC_RXB_MSK                                          (((1U<<ETHMAC_RXB_LEN)-1)<<ETHMAC_RXB_POS)
#define ETHMAC_RXB_UMSK                                         (~(((1U<<ETHMAC_RXB_LEN)-1)<<ETHMAC_RXB_POS))
#define ETHMAC_RXE                                              ETHMAC_RXE
#define ETHMAC_RXE_POS                                          (3U)
#define ETHMAC_RXE_LEN                                          (1U)
#define ETHMAC_RXE_MSK                                          (((1U<<ETHMAC_RXE_LEN)-1)<<ETHMAC_RXE_POS)
#define ETHMAC_RXE_UMSK                                         (~(((1U<<ETHMAC_RXE_LEN)-1)<<ETHMAC_RXE_POS))
#define ETHMAC_BUSY                                             ETHMAC_BUSY
#define ETHMAC_BUSY_POS                                         (4U)
#define ETHMAC_BUSY_LEN                                         (1U)
#define ETHMAC_BUSY_MSK                                         (((1U<<ETHMAC_BUSY_LEN)-1)<<ETHMAC_BUSY_POS)
#define ETHMAC_BUSY_UMSK                                        (~(((1U<<ETHMAC_BUSY_LEN)-1)<<ETHMAC_BUSY_POS))
#define ETHMAC_TXC                                              ETHMAC_TXC
#define ETHMAC_TXC_POS                                          (5U)
#define ETHMAC_TXC_LEN                                          (1U)
#define ETHMAC_TXC_MSK                                          (((1U<<ETHMAC_TXC_LEN)-1)<<ETHMAC_TXC_POS)
#define ETHMAC_TXC_UMSK                                         (~(((1U<<ETHMAC_TXC_LEN)-1)<<ETHMAC_TXC_POS))
#define ETHMAC_RXC                                              ETHMAC_RXC
#define ETHMAC_RXC_POS                                          (6U)
#define ETHMAC_RXC_LEN                                          (1U)
#define ETHMAC_RXC_MSK                                          (((1U<<ETHMAC_RXC_LEN)-1)<<ETHMAC_RXC_POS)
#define ETHMAC_RXC_UMSK                                         (~(((1U<<ETHMAC_RXC_LEN)-1)<<ETHMAC_RXC_POS))

/* 0x8 : INT_MASK */
#define ETHMAC_INT_MASK_OFFSET                                  (0x8)
#define ETHMAC_TXB_M                                            ETHMAC_TXB_M
#define ETHMAC_TXB_M_POS                                        (0U)
#define ETHMAC_TXB_M_LEN                                        (1U)
#define ETHMAC_TXB_M_MSK                                        (((1U<<ETHMAC_TXB_M_LEN)-1)<<ETHMAC_TXB_M_POS)
#define ETHMAC_TXB_M_UMSK                                       (~(((1U<<ETHMAC_TXB_M_LEN)-1)<<ETHMAC_TXB_M_POS))
#define ETHMAC_TXE_M                                            ETHMAC_TXE_M
#define ETHMAC_TXE_M_POS                                        (1U)
#define ETHMAC_TXE_M_LEN                                        (1U)
#define ETHMAC_TXE_M_MSK                                        (((1U<<ETHMAC_TXE_M_LEN)-1)<<ETHMAC_TXE_M_POS)
#define ETHMAC_TXE_M_UMSK                                       (~(((1U<<ETHMAC_TXE_M_LEN)-1)<<ETHMAC_TXE_M_POS))
#define ETHMAC_RXB_M                                            ETHMAC_RXB_M
#define ETHMAC_RXB_M_POS                                        (2U)
#define ETHMAC_RXB_M_LEN                                        (1U)
#define ETHMAC_RXB_M_MSK                                        (((1U<<ETHMAC_RXB_M_LEN)-1)<<ETHMAC_RXB_M_POS)
#define ETHMAC_RXB_M_UMSK                                       (~(((1U<<ETHMAC_RXB_M_LEN)-1)<<ETHMAC_RXB_M_POS))
#define ETHMAC_RXE_M                                            ETHMAC_RXE_M
#define ETHMAC_RXE_M_POS                                        (3U)
#define ETHMAC_RXE_M_LEN                                        (1U)
#define ETHMAC_RXE_M_MSK                                        (((1U<<ETHMAC_RXE_M_LEN)-1)<<ETHMAC_RXE_M_POS)
#define ETHMAC_RXE_M_UMSK                                       (~(((1U<<ETHMAC_RXE_M_LEN)-1)<<ETHMAC_RXE_M_POS))
#define ETHMAC_BUSY_M                                           ETHMAC_BUSY_M
#define ETHMAC_BUSY_M_POS                                       (4U)
#define ETHMAC_BUSY_M_LEN                                       (1U)
#define ETHMAC_BUSY_M_MSK                                       (((1U<<ETHMAC_BUSY_M_LEN)-1)<<ETHMAC_BUSY_M_POS)
#define ETHMAC_BUSY_M_UMSK                                      (~(((1U<<ETHMAC_BUSY_M_LEN)-1)<<ETHMAC_BUSY_M_POS))
#define ETHMAC_TXC_M                                            ETHMAC_TXC_M
#define ETHMAC_TXC_M_POS                                        (5U)
#define ETHMAC_TXC_M_LEN                                        (1U)
#define ETHMAC_TXC_M_MSK                                        (((1U<<ETHMAC_TXC_M_LEN)-1)<<ETHMAC_TXC_M_POS)
#define ETHMAC_TXC_M_UMSK                                       (~(((1U<<ETHMAC_TXC_M_LEN)-1)<<ETHMAC_TXC_M_POS))
#define ETHMAC_RXC_M                                            ETHMAC_RXC_M
#define ETHMAC_RXC_M_POS                                        (6U)
#define ETHMAC_RXC_M_LEN                                        (1U)
#define ETHMAC_RXC_M_MSK                                        (((1U<<ETHMAC_RXC_M_LEN)-1)<<ETHMAC_RXC_M_POS)
#define ETHMAC_RXC_M_UMSK                                       (~(((1U<<ETHMAC_RXC_M_LEN)-1)<<ETHMAC_RXC_M_POS))

/* 0xC : IPGT */
#define ETHMAC_IPGT_OFFSET                                      (0xC)
#define ETHMAC_IPGT                                             ETHMAC_IPGT
#define ETHMAC_IPGT_POS                                         (0U)
#define ETHMAC_IPGT_LEN                                         (7U)
#define ETHMAC_IPGT_MSK                                         (((1U<<ETHMAC_IPGT_LEN)-1)<<ETHMAC_IPGT_POS)
#define ETHMAC_IPGT_UMSK                                        (~(((1U<<ETHMAC_IPGT_LEN)-1)<<ETHMAC_IPGT_POS))

/* 0x18 : PACKETLEN */
#define ETHMAC_PACKETLEN_OFFSET                                 (0x18)
#define ETHMAC_MAXFL                                            ETHMAC_MAXFL
#define ETHMAC_MAXFL_POS                                        (0U)
#define ETHMAC_MAXFL_LEN                                        (16U)
#define ETHMAC_MAXFL_MSK                                        (((1U<<ETHMAC_MAXFL_LEN)-1)<<ETHMAC_MAXFL_POS)
#define ETHMAC_MAXFL_UMSK                                       (~(((1U<<ETHMAC_MAXFL_LEN)-1)<<ETHMAC_MAXFL_POS))
#define ETHMAC_MINFL                                            ETHMAC_MINFL
#define ETHMAC_MINFL_POS                                        (16U)
#define ETHMAC_MINFL_LEN                                        (16U)
#define ETHMAC_MINFL_MSK                                        (((1U<<ETHMAC_MINFL_LEN)-1)<<ETHMAC_MINFL_POS)
#define ETHMAC_MINFL_UMSK                                       (~(((1U<<ETHMAC_MINFL_LEN)-1)<<ETHMAC_MINFL_POS))

/* 0x1C : COLLCONFIG */
#define ETHMAC_COLLCONFIG_OFFSET                                (0x1C)
#define ETHMAC_COLLVALID                                        ETHMAC_COLLVALID
#define ETHMAC_COLLVALID_POS                                    (0U)
#define ETHMAC_COLLVALID_LEN                                    (10U)
#define ETHMAC_COLLVALID_MSK                                    (((1U<<ETHMAC_COLLVALID_LEN)-1)<<ETHMAC_COLLVALID_POS)
#define ETHMAC_COLLVALID_UMSK                                   (~(((1U<<ETHMAC_COLLVALID_LEN)-1)<<ETHMAC_COLLVALID_POS))
#define ETHMAC_MAXRET                                           ETHMAC_MAXRET
#define ETHMAC_MAXRET_POS                                       (16U)
#define ETHMAC_MAXRET_LEN                                       (4U)
#define ETHMAC_MAXRET_MSK                                       (((1U<<ETHMAC_MAXRET_LEN)-1)<<ETHMAC_MAXRET_POS)
#define ETHMAC_MAXRET_UMSK                                      (~(((1U<<ETHMAC_MAXRET_LEN)-1)<<ETHMAC_MAXRET_POS))

/* 0x20 : TX_BD_NUM */
#define ETHMAC_TX_BD_NUM_OFFSET                                 (0x20)
#define ETHMAC_TXBDNUM                                          ETHMAC_TXBDNUM
#define ETHMAC_TXBDNUM_POS                                      (0U)
#define ETHMAC_TXBDNUM_LEN                                      (8U)
#define ETHMAC_TXBDNUM_MSK                                      (((1U<<ETHMAC_TXBDNUM_LEN)-1)<<ETHMAC_TXBDNUM_POS)
#define ETHMAC_TXBDNUM_UMSK                                     (~(((1U<<ETHMAC_TXBDNUM_LEN)-1)<<ETHMAC_TXBDNUM_POS))
#define ETHMAC_TXBDPTR                                          ETHMAC_TXBDPTR
#define ETHMAC_TXBDPTR_POS                                      (16U)
#define ETHMAC_TXBDPTR_LEN                                      (7U)
#define ETHMAC_TXBDPTR_MSK                                      (((1U<<ETHMAC_TXBDPTR_LEN)-1)<<ETHMAC_TXBDPTR_POS)
#define ETHMAC_TXBDPTR_UMSK                                     (~(((1U<<ETHMAC_TXBDPTR_LEN)-1)<<ETHMAC_TXBDPTR_POS))
#define ETHMAC_RXBDPTR                                          ETHMAC_RXBDPTR
#define ETHMAC_RXBDPTR_POS                                      (24U)
#define ETHMAC_RXBDPTR_LEN                                      (7U)
#define ETHMAC_RXBDPTR_MSK                                      (((1U<<ETHMAC_RXBDPTR_LEN)-1)<<ETHMAC_RXBDPTR_POS)
#define ETHMAC_RXBDPTR_UMSK                                     (~(((1U<<ETHMAC_RXBDPTR_LEN)-1)<<ETHMAC_RXBDPTR_POS))

/* 0x28 : MIIMODE */
#define ETHMAC_MIIMODE_OFFSET                                   (0x28)
#define ETHMAC_CLKDIV                                           ETHMAC_CLKDIV
#define ETHMAC_CLKDIV_POS                                       (0U)
#define ETHMAC_CLKDIV_LEN                                       (8U)
#define ETHMAC_CLKDIV_MSK                                       (((1U<<ETHMAC_CLKDIV_LEN)-1)<<ETHMAC_CLKDIV_POS)
#define ETHMAC_CLKDIV_UMSK                                      (~(((1U<<ETHMAC_CLKDIV_LEN)-1)<<ETHMAC_CLKDIV_POS))
#define ETHMAC_MIINOPRE                                         ETHMAC_MIINOPRE
#define ETHMAC_MIINOPRE_POS                                     (8U)
#define ETHMAC_MIINOPRE_LEN                                     (1U)
#define ETHMAC_MIINOPRE_MSK                                     (((1U<<ETHMAC_MIINOPRE_LEN)-1)<<ETHMAC_MIINOPRE_POS)
#define ETHMAC_MIINOPRE_UMSK                                    (~(((1U<<ETHMAC_MIINOPRE_LEN)-1)<<ETHMAC_MIINOPRE_POS))

/* 0x2C : MIICOMMAND */
#define ETHMAC_MIICOMMAND_OFFSET                                (0x2C)
#define ETHMAC_SCANSTAT                                         ETHMAC_SCANSTAT
#define ETHMAC_SCANSTAT_POS                                     (0U)
#define ETHMAC_SCANSTAT_LEN                                     (1U)
#define ETHMAC_SCANSTAT_MSK                                     (((1U<<ETHMAC_SCANSTAT_LEN)-1)<<ETHMAC_SCANSTAT_POS)
#define ETHMAC_SCANSTAT_UMSK                                    (~(((1U<<ETHMAC_SCANSTAT_LEN)-1)<<ETHMAC_SCANSTAT_POS))
#define ETHMAC_RSTAT                                            ETHMAC_RSTAT
#define ETHMAC_RSTAT_POS                                        (1U)
#define ETHMAC_RSTAT_LEN                                        (1U)
#define ETHMAC_RSTAT_MSK                                        (((1U<<ETHMAC_RSTAT_LEN)-1)<<ETHMAC_RSTAT_POS)
#define ETHMAC_RSTAT_UMSK                                       (~(((1U<<ETHMAC_RSTAT_LEN)-1)<<ETHMAC_RSTAT_POS))
#define ETHMAC_WCTRLDATA                                        ETHMAC_WCTRLDATA
#define ETHMAC_WCTRLDATA_POS                                    (2U)
#define ETHMAC_WCTRLDATA_LEN                                    (1U)
#define ETHMAC_WCTRLDATA_MSK                                    (((1U<<ETHMAC_WCTRLDATA_LEN)-1)<<ETHMAC_WCTRLDATA_POS)
#define ETHMAC_WCTRLDATA_UMSK                                   (~(((1U<<ETHMAC_WCTRLDATA_LEN)-1)<<ETHMAC_WCTRLDATA_POS))

/* 0x30 : MIIADDRESS */
#define ETHMAC_MIIADDRESS_OFFSET                                (0x30)
#define ETHMAC_FIAD                                             ETHMAC_FIAD
#define ETHMAC_FIAD_POS                                         (0U)
#define ETHMAC_FIAD_LEN                                         (5U)
#define ETHMAC_FIAD_MSK                                         (((1U<<ETHMAC_FIAD_LEN)-1)<<ETHMAC_FIAD_POS)
#define ETHMAC_FIAD_UMSK                                        (~(((1U<<ETHMAC_FIAD_LEN)-1)<<ETHMAC_FIAD_POS))
#define ETHMAC_RGAD                                             ETHMAC_RGAD
#define ETHMAC_RGAD_POS                                         (8U)
#define ETHMAC_RGAD_LEN                                         (5U)
#define ETHMAC_RGAD_MSK                                         (((1U<<ETHMAC_RGAD_LEN)-1)<<ETHMAC_RGAD_POS)
#define ETHMAC_RGAD_UMSK                                        (~(((1U<<ETHMAC_RGAD_LEN)-1)<<ETHMAC_RGAD_POS))

/* 0x34 : MIITX_DATA */
#define ETHMAC_MIITX_DATA_OFFSET                                (0x34)
#define ETHMAC_CTRLDATA                                         ETHMAC_CTRLDATA
#define ETHMAC_CTRLDATA_POS                                     (0U)
#define ETHMAC_CTRLDATA_LEN                                     (16U)
#define ETHMAC_CTRLDATA_MSK                                     (((1U<<ETHMAC_CTRLDATA_LEN)-1)<<ETHMAC_CTRLDATA_POS)
#define ETHMAC_CTRLDATA_UMSK                                    (~(((1U<<ETHMAC_CTRLDATA_LEN)-1)<<ETHMAC_CTRLDATA_POS))

/* 0x38 : MIIRX_DATA */
#define ETHMAC_MIIRX_DATA_OFFSET                                (0x38)
#define ETHMAC_PRSD                                             ETHMAC_PRSD
#define ETHMAC_PRSD_POS                                         (0U)
#define ETHMAC_PRSD_LEN                                         (16U)
#define ETHMAC_PRSD_MSK                                         (((1U<<ETHMAC_PRSD_LEN)-1)<<ETHMAC_PRSD_POS)
#define ETHMAC_PRSD_UMSK                                        (~(((1U<<ETHMAC_PRSD_LEN)-1)<<ETHMAC_PRSD_POS))

/* 0x3C : MIISTATUS */
#define ETHMAC_MIISTATUS_OFFSET                                 (0x3C)
#define ETHMAC_MIIM_LINKFAIL                                    ETHMAC_MIIM_LINKFAIL
#define ETHMAC_MIIM_LINKFAIL_POS                                (0U)
#define ETHMAC_MIIM_LINKFAIL_LEN                                (1U)
#define ETHMAC_MIIM_LINKFAIL_MSK                                (((1U<<ETHMAC_MIIM_LINKFAIL_LEN)-1)<<ETHMAC_MIIM_LINKFAIL_POS)
#define ETHMAC_MIIM_LINKFAIL_UMSK                               (~(((1U<<ETHMAC_MIIM_LINKFAIL_LEN)-1)<<ETHMAC_MIIM_LINKFAIL_POS))
#define ETHMAC_MIIM_BUSY                                        ETHMAC_MIIM_BUSY
#define ETHMAC_MIIM_BUSY_POS                                    (1U)
#define ETHMAC_MIIM_BUSY_LEN                                    (1U)
#define ETHMAC_MIIM_BUSY_MSK                                    (((1U<<ETHMAC_MIIM_BUSY_LEN)-1)<<ETHMAC_MIIM_BUSY_POS)
#define ETHMAC_MIIM_BUSY_UMSK                                   (~(((1U<<ETHMAC_MIIM_BUSY_LEN)-1)<<ETHMAC_MIIM_BUSY_POS))

/* 0x40 : MAC_ADDR0 */
#define ETHMAC_MAC_ADDR0_OFFSET                                 (0x40)
#define ETHMAC_MAC_B5                                           ETHMAC_MAC_B5
#define ETHMAC_MAC_B5_POS                                       (0U)
#define ETHMAC_MAC_B5_LEN                                       (8U)
#define ETHMAC_MAC_B5_MSK                                       (((1U<<ETHMAC_MAC_B5_LEN)-1)<<ETHMAC_MAC_B5_POS)
#define ETHMAC_MAC_B5_UMSK                                      (~(((1U<<ETHMAC_MAC_B5_LEN)-1)<<ETHMAC_MAC_B5_POS))
#define ETHMAC_MAC_B4                                           ETHMAC_MAC_B4
#define ETHMAC_MAC_B4_POS                                       (8U)
#define ETHMAC_MAC_B4_LEN                                       (8U)
#define ETHMAC_MAC_B4_MSK                                       (((1U<<ETHMAC_MAC_B4_LEN)-1)<<ETHMAC_MAC_B4_POS)
#define ETHMAC_MAC_B4_UMSK                                      (~(((1U<<ETHMAC_MAC_B4_LEN)-1)<<ETHMAC_MAC_B4_POS))
#define ETHMAC_MAC_B3                                           ETHMAC_MAC_B3
#define ETHMAC_MAC_B3_POS                                       (16U)
#define ETHMAC_MAC_B3_LEN                                       (8U)
#define ETHMAC_MAC_B3_MSK                                       (((1U<<ETHMAC_MAC_B3_LEN)-1)<<ETHMAC_MAC_B3_POS)
#define ETHMAC_MAC_B3_UMSK                                      (~(((1U<<ETHMAC_MAC_B3_LEN)-1)<<ETHMAC_MAC_B3_POS))
#define ETHMAC_MAC_B2                                           ETHMAC_MAC_B2
#define ETHMAC_MAC_B2_POS                                       (24U)
#define ETHMAC_MAC_B2_LEN                                       (8U)
#define ETHMAC_MAC_B2_MSK                                       (((1U<<ETHMAC_MAC_B2_LEN)-1)<<ETHMAC_MAC_B2_POS)
#define ETHMAC_MAC_B2_UMSK                                      (~(((1U<<ETHMAC_MAC_B2_LEN)-1)<<ETHMAC_MAC_B2_POS))

/* 0x44 : MAC_ADDR1 */
#define ETHMAC_MAC_ADDR1_OFFSET                                 (0x44)
#define ETHMAC_MAC_B1                                           ETHMAC_MAC_B1
#define ETHMAC_MAC_B1_POS                                       (0U)
#define ETHMAC_MAC_B1_LEN                                       (8U)
#define ETHMAC_MAC_B1_MSK                                       (((1U<<ETHMAC_MAC_B1_LEN)-1)<<ETHMAC_MAC_B1_POS)
#define ETHMAC_MAC_B1_UMSK                                      (~(((1U<<ETHMAC_MAC_B1_LEN)-1)<<ETHMAC_MAC_B1_POS))
#define ETHMAC_MAC_B0                                           ETHMAC_MAC_B0
#define ETHMAC_MAC_B0_POS                                       (8U)
#define ETHMAC_MAC_B0_LEN                                       (8U)
#define ETHMAC_MAC_B0_MSK                                       (((1U<<ETHMAC_MAC_B0_LEN)-1)<<ETHMAC_MAC_B0_POS)
#define ETHMAC_MAC_B0_UMSK                                      (~(((1U<<ETHMAC_MAC_B0_LEN)-1)<<ETHMAC_MAC_B0_POS))

/* 0x48 : HASH0_ADDR */
#define ETHMAC_HASH0_ADDR_OFFSET                                (0x48)
#define ETHMAC_HASH0                                            ETHMAC_HASH0
#define ETHMAC_HASH0_POS                                        (0U)
#define ETHMAC_HASH0_LEN                                        (32U)
#define ETHMAC_HASH0_MSK                                        (((1U<<ETHMAC_HASH0_LEN)-1)<<ETHMAC_HASH0_POS)
#define ETHMAC_HASH0_UMSK                                       (~(((1U<<ETHMAC_HASH0_LEN)-1)<<ETHMAC_HASH0_POS))

/* 0x4C : HASH1_ADDR */
#define ETHMAC_HASH1_ADDR_OFFSET                                (0x4C)
#define ETHMAC_HASH1                                            ETHMAC_HASH1
#define ETHMAC_HASH1_POS                                        (0U)
#define ETHMAC_HASH1_LEN                                        (32U)
#define ETHMAC_HASH1_MSK                                        (((1U<<ETHMAC_HASH1_LEN)-1)<<ETHMAC_HASH1_POS)
#define ETHMAC_HASH1_UMSK                                       (~(((1U<<ETHMAC_HASH1_LEN)-1)<<ETHMAC_HASH1_POS))

/* 0x50 : TXCTRL */
#define ETHMAC_TXCTRL_OFFSET                                    (0x50)
#define ETHMAC_TXPAUSETV                                        ETHMAC_TXPAUSETV
#define ETHMAC_TXPAUSETV_POS                                    (0U)
#define ETHMAC_TXPAUSETV_LEN                                    (16U)
#define ETHMAC_TXPAUSETV_MSK                                    (((1U<<ETHMAC_TXPAUSETV_LEN)-1)<<ETHMAC_TXPAUSETV_POS)
#define ETHMAC_TXPAUSETV_UMSK                                   (~(((1U<<ETHMAC_TXPAUSETV_LEN)-1)<<ETHMAC_TXPAUSETV_POS))
#define ETHMAC_TXPAUSERQ                                        ETHMAC_TXPAUSERQ
#define ETHMAC_TXPAUSERQ_POS                                    (16U)
#define ETHMAC_TXPAUSERQ_LEN                                    (1U)
#define ETHMAC_TXPAUSERQ_MSK                                    (((1U<<ETHMAC_TXPAUSERQ_LEN)-1)<<ETHMAC_TXPAUSERQ_POS)
#define ETHMAC_TXPAUSERQ_UMSK                                   (~(((1U<<ETHMAC_TXPAUSERQ_LEN)-1)<<ETHMAC_TXPAUSERQ_POS))


struct  ethmac_reg {
    /* 0x0 : MODE */
    union {
        struct {
            uint32_t RXEN                           :  1; /* [    0],        r/w,        0x0 */
            uint32_t TXEN                           :  1; /* [    1],        r/w,        0x0 */
            uint32_t NOPRE                          :  1; /* [    2],        r/w,        0x0 */
            uint32_t BRO                            :  1; /* [    3],        r/w,        0x0 */
            uint32_t rsvd_4                         :  1; /* [    4],       rsvd,        0x0 */
            uint32_t PRO                            :  1; /* [    5],        r/w,        0x0 */
            uint32_t IFG                            :  1; /* [    6],        r/w,        0x0 */
            uint32_t rsvd_9_7                       :  3; /* [ 9: 7],       rsvd,        0x0 */
            uint32_t FULLD                          :  1; /* [   10],        r/w,        0x0 */
            uint32_t rsvd_12_11                     :  2; /* [12:11],       rsvd,        0x0 */
            uint32_t CRCEN                          :  1; /* [   13],        r/w,        0x1 */
            uint32_t HUGEN                          :  1; /* [   14],        r/w,        0x0 */
            uint32_t PAD                            :  1; /* [   15],        r/w,        0x1 */
            uint32_t RECSMALL                       :  1; /* [   16],        r/w,        0x0 */
            uint32_t RMIIEN                         :  1; /* [   17],        r/w,        0x0 */
            uint32_t rsvd_31_18                     : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MODE;

    /* 0x4 : INT_SOURCE */
    union {
        struct {
            uint32_t TXB                            :  1; /* [    0],        r/w,        0x0 */
            uint32_t TXE                            :  1; /* [    1],        r/w,        0x0 */
            uint32_t RXB                            :  1; /* [    2],        r/w,        0x0 */
            uint32_t RXE                            :  1; /* [    3],        r/w,        0x0 */
            uint32_t BUSY                           :  1; /* [    4],        r/w,        0x0 */
            uint32_t TXC                            :  1; /* [    5],        r/w,        0x0 */
            uint32_t RXC                            :  1; /* [    6],        r/w,        0x0 */
            uint32_t rsvd_31_7                      : 25; /* [31: 7],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } INT_SOURCE;

    /* 0x8 : INT_MASK */
    union {
        struct {
            uint32_t TXB_M                          :  1; /* [    0],        r/w,        0x0 */
            uint32_t TXE_M                          :  1; /* [    1],        r/w,        0x0 */
            uint32_t RXB_M                          :  1; /* [    2],        r/w,        0x0 */
            uint32_t RXE_M                          :  1; /* [    3],        r/w,        0x0 */
            uint32_t BUSY_M                         :  1; /* [    4],        r/w,        0x0 */
            uint32_t TXC_M                          :  1; /* [    5],        r/w,        0x0 */
            uint32_t RXC_M                          :  1; /* [    6],        r/w,        0x0 */
            uint32_t rsvd_31_7                      : 25; /* [31: 7],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } INT_MASK;

    /* 0xC : IPGT */
    union {
        struct {
            uint32_t IPGT                           :  7; /* [ 6: 0],        r/w,       0x18 */
            uint32_t reserved_7_31                  : 25; /* [31: 7],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } IPGT;

    /* 0x10  reserved */
    uint8_t RESERVED0x10[8];

    /* 0x18 : PACKETLEN */
    union {
        struct {
            uint32_t MAXFL                          : 16; /* [15: 0],        r/w,      0x600 */
            uint32_t MINFL                          : 16; /* [31:16],        r/w,       0x40 */
        }BF;
        uint32_t WORD;
    } PACKETLEN;

    /* 0x1C : COLLCONFIG */
    union {
        struct {
            uint32_t COLLVALID                      : 10; /* [ 9: 0],        r/w,       0x3f */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t MAXRET                         :  4; /* [19:16],        r/w,        0xf */
            uint32_t reserved_20_31                 : 12; /* [31:20],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } COLLCONFIG;

    /* 0x20 : TX_BD_NUM */
    union {
        struct {
            uint32_t TXBDNUM                        :  8; /* [ 7: 0],        r/w,       0x40 */
            uint32_t reserved_8_15                  :  8; /* [15: 8],       rsvd,        0x0 */
            uint32_t TXBDPTR                        :  7; /* [22:16],          r,        0x0 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t RXBDPTR                        :  7; /* [30:24],          r,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } TX_BD_NUM;

    /* 0x24  reserved */
    uint8_t RESERVED0x24[4];

    /* 0x28 : MIIMODE */
    union {
        struct {
            uint32_t CLKDIV                         :  8; /* [ 7: 0],        r/w,       0x64 */
            uint32_t MIINOPRE                       :  1; /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MIIMODE;

    /* 0x2C : MIICOMMAND */
    union {
        struct {
            uint32_t SCANSTAT                       :  1; /* [    0],        r/w,        0x0 */
            uint32_t RSTAT                          :  1; /* [    1],        r/w,        0x0 */
            uint32_t WCTRLDATA                      :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MIICOMMAND;

    /* 0x30 : MIIADDRESS */
    union {
        struct {
            uint32_t FIAD                           :  5; /* [ 4: 0],        r/w,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t RGAD                           :  5; /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_31                 : 19; /* [31:13],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MIIADDRESS;

    /* 0x34 : MIITX_DATA */
    union {
        struct {
            uint32_t CTRLDATA                       : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MIITX_DATA;

    /* 0x38 : MIIRX_DATA */
    union {
        struct {
            uint32_t PRSD                           : 16; /* [15: 0],          r,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MIIRX_DATA;

    /* 0x3C : MIISTATUS */
    union {
        struct {
            uint32_t MIIM_LINKFAIL                  :  1; /* [    0],          r,        0x0 */
            uint32_t MIIM_BUSY                      :  1; /* [    1],          r,        0x0 */
            uint32_t reserved_2_31                  : 30; /* [31: 2],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MIISTATUS;

    /* 0x40 : MAC_ADDR0 */
    union {
        struct {
            uint32_t MAC_B5                         :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t MAC_B4                         :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t MAC_B3                         :  8; /* [23:16],        r/w,        0x0 */
            uint32_t MAC_B2                         :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } MAC_ADDR0;

    /* 0x44 : MAC_ADDR1 */
    union {
        struct {
            uint32_t MAC_B1                         :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t MAC_B0                         :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } MAC_ADDR1;

    /* 0x48 : HASH0_ADDR */
    union {
        struct {
            uint32_t HASH0                          : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } HASH0_ADDR;

    /* 0x4C : HASH1_ADDR */
    union {
        struct {
            uint32_t HASH1                          : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } HASH1_ADDR;

    /* 0x50 : TXCTRL */
    union {
        struct {
            uint32_t TXPAUSETV                      : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t TXPAUSERQ                      :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } TXCTRL;

};

typedef volatile struct ethmac_reg ethmac_reg_t;


#endif  /* __ETHMAC_REG_H__ */
