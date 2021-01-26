/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2019>, <Huawei Technologies Co., Ltd>
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
#ifndef UMIP_CMD_H_
#define UMIP_CMD_H_

#ifdef __cplusplus /* Maintain C++ compatibility */
extern "C"
{
#endif /* __cplusplus */

/*
 *        |-------|-------------|-------------------|-------|---------------------------------|
 *        |                             UMIP                                                  |
 *        |                ( Universal Module Interface Protocol )                            |
 *        |-------|-------------|-------------------|-------|---------------------------------|
 *        |       |         UMIP CMD0               |       |         UMIP CMD1               |
 *        |-------|-------------|-------------------|-------|---------------------------------|
 *        | AREA  |    FIELD    |      REGION       |CMD/RSP|      CMD SET and RSP SET        |
 *        |-------|-------------|-------------------|-------|---------------------------------|
 *        |   0   |  FLD_SYS    |   SYS_CONFIG      |  0/1  |                                 |
 *        |   0   |             |   SYS_SECU        |  0/1  |                                 |
 *        |-------|-------------|-------------------|  0/1  |                                 |
 *        |   0   |  FLD_SP2    |   SP_HILINK       |  0/1  |                                 |
 *        |-------|-------------|-------------------|  0/1  |                                 |
 *        |   0   |  FLD_SP3    |   SP_HLINK        |  0/1  |                                 |
 *        |       |             |                   |  0/1  |                                 |
 *        |-------|-------------|-------------------|-------|---------------------------------|
 *        | AREA  |    FIELD    |      REGION       |CMD/RSP|      CMD SET and RSP SET        |
 *        |-------|-------------|-------------------|-------|---------------------------------|
 *        |   1   |             |                   |  0/1  |                                 |
 *        |   1   |             |                   |  0/1  |                                 |
 *        |   1   |             |                   |  0/1  |                                 |
 *        |   1   |             |                   |  0/1  |                                 |
 *        |   1   |             |                   |  0/1  |                                 |
 *        |-------|-------------|-------------------|-------|---------------------------------|
*/

/*-----------------------------------------------------------------------------
 Section: Area Definitions
 -----------------------------------------------------------------------------*/
#define AREA_RESERVED       ((uint8_t)0x0)      // command area for reserved
#define AREA_OPEN           ((uint8_t)0x80)     // command area for openness and cooperation

/*-----------------------------------------------------------------------------
 Section: Area ----->  Field Definitions
 -----------------------------------------------------------------------------*/
 #define FIELD_SHIFT        (4U)                   
/* Reserved area */
#define FLD_SYS             ((uint8_t)(0x00 << FIELD_SHIFT) | AREA_RESERVED)        // system field
#define FLD_CTRL            ((uint8_t)(0x01 << FIELD_SHIFT) | AREA_RESERVED)        // control field
#define FLD_SP0             ((uint8_t)(0x02 << FIELD_SHIFT) | AREA_RESERVED)        // specific purpose 2 field
#define FLD_SP1             ((uint8_t)(0x03 << FIELD_SHIFT) | AREA_RESERVED)        // specific purpose 3 field
#define FLD_SP2             ((uint8_t)(0x04 << FIELD_SHIFT) | AREA_RESERVED)        // specific purpose 4 field
#define FLD_SP3             ((uint8_t)(0x05 << FIELD_SHIFT) | AREA_RESERVED)        // specific purpose 5 field
#define FLD_SERVICE1        ((uint8_t)(0x06 << FIELD_SHIFT) | AREA_RESERVED)        // service 6 field
#define FLD_SERVICE2        ((uint8_t)(0x07 << FIELD_SHIFT) | AREA_RESERVED)        // service 7 field
/* Open area */
#define FLD_RESERVE1        ((uint8_t)(0x00 << FIELD_SHIFT) | AREA_OPEN)        // reserve 0 field
#define FLD_RESERVE2        ((uint8_t)(0x01 << FIELD_SHIFT) | AREA_OPEN)        // reserve 1 field
#define FLD_EXTEND3         ((uint8_t)(0x02 << FIELD_SHIFT) | AREA_OPEN)        // extend purpose 2 field
#define FLD_EXTEND4         ((uint8_t)(0x03 << FIELD_SHIFT) | AREA_OPEN)        // extend purpose 3 field
#define FLD_EXTEND5         ((uint8_t)(0x04 << FIELD_SHIFT) | AREA_OPEN)        // extend purpose 4 field
#define FLD_EXTEND6         ((uint8_t)(0x05 << FIELD_SHIFT) | AREA_OPEN)        // extend purpose 5 field
#define FLD_CLIENT          ((uint8_t)(0x06 << FIELD_SHIFT) | AREA_OPEN)        // vip client field
#define FLD_USER            ((uint8_t)(0x07 << FIELD_SHIFT) | AREA_OPEN)        // normal user field

/*-----------------------------------------------------------------------------
 Section: Area ----->  Filed  ----->  Region Definitions
 -----------------------------------------------------------------------------*/
/* Field system */
#define SYS_CONFIG      ((uint8_t)(0x00 + FLD_SYS))     // system config region
#define SYS_SECU        ((uint8_t)(0x01 + FLD_SYS))     // system security region
/* Field control */
/* NONE */
/* Field specific purpose 2 */                   
#define SP_HILINK       ((uint8_t)(0x00 + FLD_SP2))     // hilink region
/* Field specific purpose 3 */                   
#define SP_HLINK        ((uint8_t)(0x00 + FLD_SP3))     // hlink region
/* Field specific purpose 4 */
/* NONE */
/* Field specific purpose 5 */
/* NONE */
/* Field service 6 */
/* NONE */
/* Field service 7 */
/* NONE */
/* Field reserve 0 */
/* NONE */
/* Field reserve 1 */
/* NONE */
/* Field extend purpose 2 */
/* NONE */
/* Field extend purpose 3 */
/* NONE */
/* Field extend purpose 4 */
/* NONE */
/* Field extend purpose 5 */
/* NONE */
/* Field vip client */
/* NONE */
/* Field normal user */
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Area ----->  Filed  ----->  Region  ----->  Command and Response Definitions
 -----------------------------------------------------------------------------*/
#define REGION_SHIFT(x)        (((uint16_t)(x)) << 8U)
#define F_RSP                  ((uint8_t)0x80)
/* SYS_SECU region */
/* SYS_SECU region  ----->  command set */
#define SECU_CMD_CERT_APPLY                 (0x01 + REGION_SHIFT(SYS_SECU))        // Security certificate apply
#define SECU_CMD_CERT_UPDATE                (0x02 + REGION_SHIFT(SYS_SECU))        // Security certificate update   
#define SECU_CMD_CERT_REVOKE                (0x03 + REGION_SHIFT(SYS_SECU))        // Security certificate revoke   
#define SECU_CMD_CERT_BATCH_APPLY           (0x04 + REGION_SHIFT(SYS_SECU))        // Security certificate batch apply 
#define SECU_CMD_CERT_DLINFO                (0x05 + REGION_SHIFT(SYS_SECU))        // Security certificate download info   
#define SECU_CMD_CERT_DOWNLOAD              (0x06 + REGION_SHIFT(SYS_SECU))        // Security certificate download 
/* SYS_SECU region  ----->  response set */
#define SECU_CMD_CERT_APPLY_RSP                 ((0x01 | F_RSP) + REGION_SHIFT(SYS_SECU))        // response Security certificate apply 
#define SECU_CMD_CERT_UPDATE_RSP                ((0x02 | F_RSP) + REGION_SHIFT(SYS_SECU))        // response Security certificate update   
#define SECU_CMD_CERT_REVOKE_RSP                ((0x03 | F_RSP) + REGION_SHIFT(SYS_SECU))        // response Security certificate revoke   
#define SECU_CMD_CERT_BATCH_APPLY_RSP           ((0x04 | F_RSP) + REGION_SHIFT(SYS_SECU))        // response Security certificate batch apply 
#define SECU_CMD_CERT_DLINFO_RSP                ((0x05 | F_RSP) + REGION_SHIFT(SYS_SECU))        // response Security certificate download info   
#define SECU_CMD_CERT_DOWNLOAD_RSP              ((0x06 | F_RSP) + REGION_SHIFT(SYS_SECU))        // response Security certificate download 

/* hilink region */
/* hilink region  ----->  command set */
#define HLK_CMD_DEVCTL_WM           (0x01 + REGION_SHIFT(SP_HILINK))        // Control module working mode
#define HLK_CMD_DEVCTL_RB           (0x02 + REGION_SHIFT(SP_HILINK))        // Control module restart
#define HLK_CMD_DEVCTL_RST          (0x03 + REGION_SHIFT(SP_HILINK))        // Reset module
#define HLK_CMD_DEVCTL_QWM          (0x04 + REGION_SHIFT(SP_HILINK))        // Query module working mode
#define HLK_CMD_DEVCTL_QNS          (0x05 + REGION_SHIFT(SP_HILINK))        // Query module network status
#define HLK_CMD_MDLRSP_WM           (0x07 + REGION_SHIFT(SP_HILINK))        // Module working mode change notification
#define HLK_CMD_MDLRSP_RNS          (0x09 + REGION_SHIFT(SP_HILINK))        // Module network status change
#define HLK_CMD_MDLRSP_UGD          (0x0A + REGION_SHIFT(SP_HILINK))        // Upgrade notice
#define HLK_CMD_DEVUPD_STA          (0x0B + REGION_SHIFT(SP_HILINK))        // Report device status
#define HLK_CMD_MDCTL_DEV_PROT      (0x0D + REGION_SHIFT(SP_HILINK))        // Device control
#define HLK_CMD_MDCTL_DEV_QPROT     (0x0E + REGION_SHIFT(SP_HILINK))        // Device inquiry
#define HLK_CMD_DEV_QUPG            (0x10 + REGION_SHIFT(SP_HILINK))        // Query MCU board to be upgraded
#define HLK_CMD_DEV_SUPG            (0x11 + REGION_SHIFT(SP_HILINK))        // Start MCU board upgrade command
#define HLK_CMD_DEV_TRANSING        (0x12 + REGION_SHIFT(SP_HILINK))        // Transmission of MCU board OTA data
#define HLK_CMD_DEV_EUPG            (0x13 + REGION_SHIFT(SP_HILINK))        // End MCU board OTA transmission
#define HLK_CMD_DEVREG_PROFILE      (0x20 + REGION_SHIFT(SP_HILINK))        // MCU board device registration
#define HLK_CMD_DEVREG_AC           (0x21 + REGION_SHIFT(SP_HILINK))        // MCU board device AC registration
#define HLK_CMD_DEVREG_RSA          (0x22 + REGION_SHIFT(SP_HILINK))        // MCU board device RSA registration
/* hilink region  ----->  response set */
#define HLK_CMD_DEVCTL_WM_RSP           ((0x01 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Control module working mode
#define HLK_CMD_DEVCTL_RB_RSP           ((0x02 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Control module restart
#define HLK_CMD_DEVCTL_RST_RSP          ((0x03 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Reset module
#define HLK_CMD_DEVCTL_QWM_RSP          ((0x04 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Query module working mode
#define HLK_CMD_DEVCTL_QNS_RSP          ((0x05 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Query module network status
#define HLK_CMD_MDLRSP_WM_RSP           ((0x07 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Module working mode change notification
#define HLK_CMD_MDLRSP_RNS_RSP          ((0x09 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Module network status change
#define HLK_CMD_MDLRSP_UGD_RSP          ((0x0A | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Upgrade notice
#define HLK_CMD_DEVUPD_STA_RSP          ((0x0B | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Report device status
#define HLK_CMD_MDCTL_DEV_PROT_RSP      ((0x0D | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Device control
#define HLK_CMD_MDCTL_DEV_QPROT_RSP     ((0x0E | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Device inquiry
#define HLK_CMD_DEV_QUPG_RSP            ((0x10 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Query MCU board to be upgraded
#define HLK_CMD_DEV_SUPG_RSP            ((0x11 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Start MCU board upgrade command
#define HLK_CMD_DEV_TRANSING_RSP        ((0x12 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response Transmission of MCU board OTA data
#define HLK_CMD_DEV_EUPG_RSP            ((0x13 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response End MCU board OTA transmission
#define HLK_CMD_DEVREG_PROFILE_RSP      ((0x20 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response MCU board device registration
#define HLK_CMD_DEVREG_AC_RSP           ((0x21 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response MCU board device AC registration
#define HLK_CMD_DEVREG_RSA_RSP          ((0x22 | F_RSP) + REGION_SHIFT(SP_HILINK))        // response MCU board device RSA registration

/* hlink region */
/* hlink region  ----->  command set */
#define HLINK_CMD_DEV_REG               (0x01 + REGION_SHIFT(SP_HLINK))        // Device registration command   
#define HLINK_CMD_SESS_MNGR             (0x02 + REGION_SHIFT(SP_HLINK))        // Session Management Command  
#define HLINK_CMD_FILE_MNGR             (0x03 + REGION_SHIFT(SP_HLINK))        // File Management Command   
#define HLINK_CMD_DATA_REPORT           (0x04 + REGION_SHIFT(SP_HLINK))        // Data reporting command   
#define HLINK_CMD_FILE_MNGR_RSP_END     (0x05 + REGION_SHIFT(SP_HLINK))        // File transfer end command 
#define HLINK_CMD_SRV_CMD               (0x06 + REGION_SHIFT(SP_HLINK))        // SRV command     
#define HLINK_CMD_DEV_REG_REQ           (0x07 + REGION_SHIFT(SP_HLINK))        // Device registration request command 
/* hlink region  ----->  response set */
#define HLINK_CMD_DEV_REG_RSP               ((0x01 | F_RSP) + REGION_SHIFT(SP_HLINK))        // response Device registration command   
#define HLINK_CMD_SESS_MNGR_RSP             ((0x02 | F_RSP) + REGION_SHIFT(SP_HLINK))        // response Session Management Command 
#define HLINK_CMD_FILE_MNGR_RSP             ((0x03 | F_RSP) + REGION_SHIFT(SP_HLINK))        // response File Management Command  
#define HLINK_CMD_DATA_REPORT_RSP           ((0x04 | F_RSP) + REGION_SHIFT(SP_HLINK))        // response Data reporting command   
#define HLINK_CMD_FILE_MNGR_RSP_END_RSP     ((0x05 | F_RSP) + REGION_SHIFT(SP_HLINK))        // response File transfer end command 
#define HLINK_CMD_SRV_CMD_RSP               ((0x06 | F_RSP) + REGION_SHIFT(SP_HLINK))        // response SRV command     
#define HLINK_CMD_DEV_REG_REQ_RSP           ((0x07 | F_RSP) + REGION_SHIFT(SP_HLINK))        // response Device registration request command 

/* xx region */
/* xx region  ----->  command set */
/* NONE */
/* xx region  ----->  response set */
/* NONE */

#ifdef __cplusplus /* Maintain C++ compatibility */
}
#endif /* __cplusplus */

#endif /* UMIP_CMD_H_ */
