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
#ifndef __SDIO_SDCARD_H
#define __SDIO_SDCARD_H
#include "bl808_sdh.h"


#define SDIO_CMDTIMEOUT                ((uint32_t)0x00010000)


/*! @brief Reverse byte sequence in uint32_t */
#define SWAP_WORD_BYTE_SEQUENCE(x) (__REV(x))
#define __OCRAM      __attribute__ ((section (".system_ram")))
#define __EALIGN(x)  __attribute((aligned (x)))

typedef enum
{
/** 
  * @brief  SDIO specific error defines  
  */   
  SD_CMD_CRC_FAIL                    = (1), /*!< Command response received (but CRC check failed) */
  SD_DATA_CRC_FAIL                   = (2), /*!< Data bock sent/received (CRC check Failed) */
  SD_CMD_RSP_TIMEOUT                 = (3), /*!< Command response timeout */
  SD_DATA_TIMEOUT                    = (4), /*!< Data time out */
  SD_TX_UNDERRUN                     = (5), /*!< Transmit FIFO under-run */
  SD_RX_OVERRUN                      = (6), /*!< Receive FIFO over-run */
  SD_START_BIT_ERR                   = (7), /*!< Start bit not detected on all data signals in widE bus mode */
  SD_CMD_OUT_OF_RANGE                = (8), /*!< CMD's argument was out of range.*/
  SD_ADDR_MISALIGNED                 = (9), /*!< Misaligned address */
  SD_BLOCK_LEN_ERR                   = (10), /*!< Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length */
  SD_ERASE_SEQ_ERR                   = (11), /*!< An error in the sequence of erase command occurs.*/
  SD_BAD_ERASE_PARAM                 = (12), /*!< An Invalid selection for erase groups */
  SD_WRITE_PROT_VIOLATION            = (13), /*!< Attempt to program a write protect block */
  SD_LOCK_UNLOCK_FAILED              = (14), /*!< Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card */
  SD_COM_CRC_FAILED                  = (15), /*!< CRC check of the previous command failed */
  SD_ILLEGAL_CMD                     = (16), /*!< Command is not legal for the card state */
  SD_CARD_ECC_FAILED                 = (17), /*!< Card internal ECC was applied but failed to correct the data */
  SD_CC_ERROR                        = (18), /*!< Internal card controller error */
  SD_GENERAL_UNKNOWN_ERROR           = (19), /*!< General or Unknown error */
  SD_STREAM_READ_UNDERRUN            = (20), /*!< The card could not sustain data transfer in stream read operation. */
  SD_STREAM_WRITE_OVERRUN            = (21), /*!< The card could not sustain data programming in stream mode */
  SD_CID_CSD_OVERWRITE               = (22), /*!< CID/CSD overwrite error */
  SD_WP_ERASE_SKIP                   = (23), /*!< only partial address space was erased */
  SD_CARD_ECC_DISABLED               = (24), /*!< Command has been executed without using internal ECC */
  SD_ERASE_RESET                     = (25), /*!< Erase sequence was cleared before executing because an out of erase sequence command was received */
  SD_AKE_SEQ_ERROR                   = (26), /*!< Error in sequence of authentication. */
  SD_INVALID_VOLTRANGE               = (27),
  SD_ADDR_OUT_OF_RANGE               = (28),
  SD_SWITCH_ERROR                    = (29),
  SD_SDIO_DISABLED                   = (30),
  SD_SDIO_FUNCTION_BUSY              = (31),
  SD_SDIO_FUNCTION_FAILED            = (32),
  SD_SDIO_UNKNOWN_FUNCTION           = (33),

/** 
  * @brief  Standard error defines   
  */ 
  SD_INTERNAL_ERROR, 
  SD_NOT_CONFIGURED,
  SD_REQUEST_PENDING, 
  SD_REQUEST_NOT_APPLICABLE, 
  SD_INVALID_PARAMETER,  
  SD_UNSUPPORTED_FEATURE,  
  SD_UNSUPPORTED_HW,  
  SD_ERROR, 
	SD_CMD_ERROR,
	SD_CMD_RESP1_ERROR,
	SD_DATA_ERROR,
	SD_ADMA_ALIGN_ERROR,
	SD_CMD_ERASE_ERROR,
	SD_CMD_PROGRAM_ERROR,
	SD_DataCfg_ERROR,
	SD_WAITING,
  SD_OK = 0 
} SD_Error;


/** 
  * @brief  SDIO Transfer state  
  */   
typedef enum
{
  SD_TRANSFER_OK  = 0,
  SD_TRANSFER_BUSY = 1,
  SD_TRANSFER_ERROR
} SDTransferState;

/** 
  * @brief  SD Card States 
  */   
typedef enum
{
  SD_CARD_READY                  = ((uint32_t)0x00000001),
  SD_CARD_IDENTIFICATION         = ((uint32_t)0x00000002),
  SD_CARD_STANDBY                = ((uint32_t)0x00000003),
  SD_CARD_TRANSFER               = ((uint32_t)0x00000004),
  SD_CARD_SENDING                = ((uint32_t)0x00000005),
  SD_CARD_RECEIVING              = ((uint32_t)0x00000006),
  SD_CARD_PROGRAMMING            = ((uint32_t)0x00000007),
  SD_CARD_DISCONNECTED           = ((uint32_t)0x00000008),
  SD_CARD_ERROR                  = ((uint32_t)0x000000FF)
}SDCardState;


/** 
  * @brief  Card Specific Data: CSD Register   
  */ 
typedef struct
{
   uint8_t  CSDStruct;            /*!< CSD structure */
   uint8_t  SysSpecVersion;       /*!< System specification version */
   uint8_t  Reserved1;            /*!< Reserved */
   uint8_t  TAAC;                 /*!< Data read access-time 1 */
   uint8_t  NSAC;                 /*!< Data read access-time 2 in CLK cycles */
   uint8_t  MaxBusClkFrec;        /*!< Max. bus clock frequency */
   uint16_t CardComdClasses;      /*!< Card command classes */
   uint8_t  RdBlockLen;           /*!< Max. read data block length */
   uint8_t  PartBlockRead;        /*!< Partial blocks for read allowed */
   uint8_t  WrBlockMisalign;      /*!< Write block misalignment */
   uint8_t  RdBlockMisalign;      /*!< Read block misalignment */
   uint8_t  DSRImpl;              /*!< DSR implemented */
   uint8_t  Reserved2;            /*!< Reserved */
   uint32_t DeviceSize;           /*!< Device Size */
   uint8_t  MaxRdCurrentVDDMin;   /*!< Max. read current @ VDD min */
   uint8_t  MaxRdCurrentVDDMax;   /*!< Max. read current @ VDD max */
   uint8_t  MaxWrCurrentVDDMin;   /*!< Max. write current @ VDD min */
   uint8_t  MaxWrCurrentVDDMax;   /*!< Max. write current @ VDD max */
   uint8_t  DeviceSizeMul;        /*!< Device size multiplier */
   uint8_t  EraseGrSize;          /*!< Erase group size */
   uint8_t  EraseGrMul;           /*!< Erase group size multiplier */
   uint8_t  WrProtectGrSize;      /*!< Write protect group size */
   uint8_t  WrProtectGrEnable;    /*!< Write protect group enable */
   uint8_t  ManDeflECC;           /*!< Manufacturer default ECC */
   uint8_t  WrSpeedFact;          /*!< Write speed factor */
   uint8_t  MaxWrBlockLen;        /*!< Max. write data block length */
   uint8_t  WriteBlockPaPartial;  /*!< Partial blocks for write allowed */
   uint8_t  Reserved3;            /*!< Reserded */
   uint8_t  ContentProtectAppli;  /*!< Content protection application */
   uint8_t  FileFormatGrouop;     /*!< File format group */
   uint8_t  CopyFlag;             /*!< Copy flag (OTP) */
   uint8_t  PermWrProtect;        /*!< Permanent write protection */
   uint8_t  TempWrProtect;        /*!< Temporary write protection */
   uint8_t  FileFormat;           /*!< File Format */
   uint8_t  ECC;                  /*!< ECC code */
} SD_CSD;

/** 
  * @brief  Card Identification Data: CID Register   
  */
typedef struct
{
   uint8_t  ManufacturerID;       /*!< ManufacturerID */
   uint8_t OEM_AppliID[3];          /*!< OEM/Application ID end with 0 for str display*/
   uint8_t ProdName[6];            /*!< Product Name part1 end with 0 for str display*/
   uint8_t  ProdRev;              /*!< Product Revision */
   uint32_t ProdSN;               /*!< Product Serial Number */
   uint8_t  month;            /*!< Reserved1 */
   uint32_t year;         /*!< Manufacturing Date */
} SD_CID;

/** 
  * @brief SD Card Status 
  */
typedef struct
{
   uint8_t DAT_BUS_WIDTH;
   uint8_t SECURED_MODE;
   uint16_t SD_CARD_TYPE;
   uint32_t SIZE_OF_PROTECTED_AREA;
   uint8_t SPEED_CLASS;
   uint8_t PERFORMANCE_MOVE;
   uint8_t AU_SIZE;
   uint16_t ERASE_SIZE;
   uint8_t ERASE_TIMEOUT;
   uint8_t ERASE_OFFSET;
} SD_CardStatus;

/** 
  * @brief SD Card information 
  */
#if 0
typedef struct
{
  SD_CSD SD_csd;
  SD_CID SD_cid;
  uint32_t CardCapacity;  /*!< Card Capacity */
  uint32_t CardBlockSize; /*!< Card Block Size */
  uint16_t RCA;
  uint8_t CardType;
} SD_CardInfo;
#endif

/*! @brief SD card CID register */
typedef struct _sd_cid
{
    uint8_t manufacturerID;                     /*!< Manufacturer ID [127:120] */
    uint16_t applicationID;                     /*!< OEM/Application ID [119:104] */
    uint8_t productName[5]; /*!< Product name [103:64] */
    uint8_t productVersion;                     /*!< Product revision [63:56] */
    uint32_t productSerialNumber;               /*!< Product serial number [55:24] */
    uint16_t manufacturerData;                  /*!< Manufacturing date [19:8] */
} sd_cid_t;

/*! @brief SD card CSD register */
typedef struct _sd_csd
{
    uint8_t csdStructure;        /*!< CSD structure [127:126] */
    uint8_t dataReadAccessTime1; /*!< Data read access-time-1 [119:112] */
    uint8_t dataReadAccessTime2; /*!< Data read access-time-2 in clock cycles (NSAC*100) [111:104] */
    uint8_t transferSpeed;       /*!< Maximum data transfer rate [103:96] */
    uint16_t cardCommandClass;   /*!< Card command classes [95:84] */
    uint8_t readBlockLength;     /*!< Maximum read data block length [83:80] */
    uint16_t flags;              /*!< Flags in _sd_csd_flag */
    uint32_t deviceSize;         /*!< Device size [73:62] */
    /* Following fields from 'readCurrentVddMin' to 'deviceSizeMultiplier' exist in CSD version 1 */
    uint8_t readCurrentVddMin;    /*!< Maximum read current at VDD min [61:59] */
    uint8_t readCurrentVddMax;    /*!< Maximum read current at VDD max [58:56] */
    uint8_t writeCurrentVddMin;   /*!< Maximum write current at VDD min [55:53] */
    uint8_t writeCurrentVddMax;   /*!< Maximum write current at VDD max [52:50] */
    uint8_t deviceSizeMultiplier; /*!< Device size multiplier [49:47] */

    uint8_t eraseSectorSize;       /*!< Erase sector size [45:39] */
    uint8_t writeProtectGroupSize; /*!< Write protect group size [38:32] */
    uint8_t writeSpeedFactor;      /*!< Write speed factor [28:26] */
    uint8_t writeBlockLength;      /*!< Maximum write data block length [25:22] */
    uint8_t fileFormat;            /*!< File format [11:10] */
} sd_csd_t;
/*! @brief SD card SCR register */
typedef struct _sd_scr
{
    uint8_t scrStructure;             /*!< SCR Structure [63:60] */
    uint8_t sdSpecification;          /*!< SD memory card specification version [59:56] */
    uint16_t flags;                   /*!< SCR flags in _sd_scr_flag */
    uint8_t sdSecurity;               /*!< Security specification supported [54:52] */
    uint8_t sdBusWidths;              /*!< Data bus widths supported [51:48] */
    uint8_t extendedSecurity;         /*!< Extended security support [46:43] */
    uint8_t commandSupport;           /*!< Command support bits [33:32] 33-support CMD23, 32-support cmd20*/
    uint32_t reservedForManufacturer; /*!< reserved for manufacturer usage [31:0] */
} sd_scr_t;
/*! @brief SD Status register */
typedef struct _sd_ssr
{
    uint8_t dataBusWidth;        /*!< Data Bus Width [511:510] 0b00--1line, 0b10--4line*/
    uint8_t secureMode;          /*!< Secure Mode [509] */
    uint16_t SDCardType;          /*!< SD Card Type [495:480] */
    uint32_t sizeOfProtectedArea; /*!< Size Of Protected area [479:448] */
    uint8_t speedClass;         /*!< speed classes [447:440] */
    uint8_t performanceMove;     /*!< performance move [439:432] */
    uint8_t AUSize;              /*!< AU size [431:428] */

    uint16_t eraseSize;           /*!< erase size [423:408] */
    uint8_t eraseTimeOut;         /*!< erase timeout [407:402] */
    uint8_t eraseOffset;          /*!< erase offset [401:400] */
    uint8_t UHSSpeedGrade;        /*!< UHS speed grade [399:396] */
    uint8_t UHSAUSize;            /*!< UHS AU size [395:392] */
} sd_ssr_t;
/*!
 * @brief SD card state
 *
 * Define the card structure including the necessary fields to identify and describe the card.
 */
typedef struct _sd_card
{
    uint32_t relativeAddress;       /*!< Relative address of the card */
    uint32_t version;               /*!< Card version */
    uint32_t flags;                 /*!< Flags in _sd_card_flag */
    uint32_t rawCid[4U];            /*!< Raw CID content */
    uint32_t rawCsd[4U];            /*!< Raw CSD content */
    uint32_t rawScr[2U];            /*!< Raw CSD content */
	  uint32_t rawSsr[16U];            /*!< Raw CSD content */
    uint32_t ocr;                   /*!< Raw OCR content */
    sd_cid_t cid;                   /*!< CID */
    sd_csd_t csd;                   /*!< CSD */
    sd_scr_t scr;                   /*!< SCR */
	  sd_ssr_t ssr;                   /*!< SCR */
    uint32_t blockCount;            /*!< Card total block number */
    uint32_t blockSize;             /*!< Card block size */
} sd_card_t;
/** 
  * @brief SDIO Commands  Index 
  */
#define SD_CMD_GO_IDLE_STATE                       ((uint8_t)0)
#define SD_CMD_SEND_OP_COND                        ((uint8_t)1)
#define SD_CMD_ALL_SEND_CID                        ((uint8_t)2)
#define SD_CMD_SET_REL_ADDR                        ((uint8_t)3) /*!< SDIO_SEND_REL_ADDR for SD Card */
#define SD_CMD_SET_DSR                             ((uint8_t)4)
#define SD_CMD_SDIO_SEN_OP_COND                    ((uint8_t)5)
#define SD_CMD_HS_SWITCH                           ((uint8_t)6)
#define SD_CMD_SEL_DESEL_CARD                      ((uint8_t)7)
#define SD_CMD_HS_SEND_EXT_CSD                     ((uint8_t)8)
#define SDIO_SEND_IF_COND                          ((uint8_t)8)
#define SD_CMD_SEND_CSD                            ((uint8_t)9)
#define SD_CMD_SEND_CID                            ((uint8_t)10)
#define SD_CMD_READ_DAT_UNTIL_STOP                 ((uint8_t)11) /*!< SD Card doesn't support it */
#define SD_CMD_STOP_TRANSMISSION                   ((uint8_t)12)
#define SD_CMD_SEND_STATUS                         ((uint8_t)13)
#define SD_CMD_HS_BUSTEST_READ                     ((uint8_t)14)
#define SD_CMD_GO_INACTIVE_STATE                   ((uint8_t)15)
#define SD_CMD_SET_BLOCKLEN                        ((uint8_t)16)
#define SD_CMD_READ_SINGLE_BLOCK                   ((uint8_t)17)
#define SD_CMD_READ_MULT_BLOCK                     ((uint8_t)18)
#define SD_CMD_HS_BUSTEST_WRITE                    ((uint8_t)19)
#define SD_CMD_WRITE_DAT_UNTIL_STOP                ((uint8_t)20) /*!< SD Card doesn't support it */
#define SD_CMD_SET_BLOCK_COUNT                     ((uint8_t)23) /*!< SD Card doesn't support it */
#define SD_CMD_WRITE_SINGLE_BLOCK                  ((uint8_t)24)
#define SD_CMD_WRITE_MULT_BLOCK                    ((uint8_t)25)
#define SD_CMD_PROG_CID                            ((uint8_t)26) /*!< reserved for manufacturers */
#define SD_CMD_PROG_CSD                            ((uint8_t)27)
#define SD_CMD_SET_WRITE_PROT                      ((uint8_t)28)
#define SD_CMD_CLR_WRITE_PROT                      ((uint8_t)29)
#define SD_CMD_SEND_WRITE_PROT                     ((uint8_t)30)
#define SD_CMD_SD_ERASE_GRP_START                  ((uint8_t)32) /*!< To set the address of the first write
                                                                  block to be erased. (For SD card only) */
#define SD_CMD_SD_ERASE_GRP_END                    ((uint8_t)33) /*!< To set the address of the last write block of the
                                                                  continuous range to be erased. (For SD card only) */
#define SD_CMD_ERASE_GRP_START                     ((uint8_t)35) /*!< To set the address of the first write block to be erased.
                                                                  (For MMC card only spec 3.31) */

#define SD_CMD_ERASE_GRP_END                       ((uint8_t)36) /*!< To set the address of the last write block of the
                                                                  continuous range to be erased. (For MMC card only spec 3.31) */

#define SD_CMD_ERASE                               ((uint8_t)38)
#define SD_CMD_FAST_IO                             ((uint8_t)39) /*!< SD Card doesn't support it */
#define SD_CMD_GO_IRQ_STATE                        ((uint8_t)40) /*!< SD Card doesn't support it */
#define SD_CMD_LOCK_UNLOCK                         ((uint8_t)42)
#define SD_CMD_APP_CMD                             ((uint8_t)55)
#define SD_CMD_GEN_CMD                             ((uint8_t)56)
#define SD_CMD_NO_CMD                              ((uint8_t)64)

/** 
  * @brief Following commands are SD Card Specific commands.
  *        SDIO_APP_CMD :CMD55 should be sent before sending these commands. 
  */
#define SD_CMD_APP_SD_SET_BUSWIDTH                 ((uint8_t)6)  /*!< For SD Card only */
#define SD_CMD_SD_APP_STAUS                        ((uint8_t)13) /*!< For SD Card only */
#define SD_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS        ((uint8_t)22) /*!< For SD Card only */
#define SD_CMD_SD_APP_OP_COND                      ((uint8_t)41) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CLR_CARD_DETECT          ((uint8_t)42) /*!< For SD Card only */
#define SD_CMD_SD_APP_SEND_SCR                     ((uint8_t)51) /*!< For SD Card only */
#define SD_CMD_SDIO_RW_DIRECT                      ((uint8_t)52) /*!< For SD I/O Card only */
#define SD_CMD_SDIO_RW_EXTENDED                    ((uint8_t)53) /*!< For SD I/O Card only */

/** 
  * @brief Following commands are SD Card Specific security commands.
  *        SDIO_APP_CMD should be sent before sending these commands. 
  */
#define SD_CMD_SD_APP_GET_MKB                      ((uint8_t)43) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_MID                      ((uint8_t)44) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CER_RN1                  ((uint8_t)45) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_CER_RN2                  ((uint8_t)46) /*!< For SD Card only */
#define SD_CMD_SD_APP_SET_CER_RES2                 ((uint8_t)47) /*!< For SD Card only */
#define SD_CMD_SD_APP_GET_CER_RES1                 ((uint8_t)48) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_READ_MULTIPLE_BLOCK   ((uint8_t)18) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK  ((uint8_t)25) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_ERASE                 ((uint8_t)38) /*!< For SD Card only */
#define SD_CMD_SD_APP_CHANGE_SECURE_AREA           ((uint8_t)49) /*!< For SD Card only */
#define SD_CMD_SD_APP_SECURE_WRITE_MKB             ((uint8_t)48) /*!< For SD Card only */


/** 
  * @brief  Mask for errors Card Status R1 (CSR Register) 
  */
#define SD_CSR_ADDR_OUT_OF_RANGE        ((uint32_t)0x80000000)
#define SD_CSR_ADDR_MISALIGNED          ((uint32_t)0x40000000)
#define SD_CSR_BLOCK_LEN_ERR            ((uint32_t)0x20000000)
#define SD_CSR_ERASE_SEQ_ERR            ((uint32_t)0x10000000)
#define SD_CSR_BAD_ERASE_PARAM          ((uint32_t)0x08000000)
#define SD_CSR_WRITE_PROT_VIOLATION     ((uint32_t)0x04000000)
#define SD_CSR_LOCK_UNLOCK_FAILED       ((uint32_t)0x01000000)
#define SD_CSR_COM_CRC_FAILED           ((uint32_t)0x00800000)
#define SD_CSR_ILLEGAL_CMD              ((uint32_t)0x00400000)
#define SD_CSR_CARD_ECC_FAILED          ((uint32_t)0x00200000)
#define SD_CSR_CC_ERROR                 ((uint32_t)0x00100000)
#define SD_CSR_GENERAL_UNKNOWN_ERROR    ((uint32_t)0x00080000)
#define SD_CSR_STREAM_READ_UNDERRUN     ((uint32_t)0x00040000)
#define SD_CSR_STREAM_WRITE_OVERRUN     ((uint32_t)0x00020000)
#define SD_CSR_CID_CSD_OVERWRIETE       ((uint32_t)0x00010000)
#define SD_CSR_WP_ERASE_SKIP            ((uint32_t)0x00008000)
#define SD_CSR_CARD_ECC_DISABLED        ((uint32_t)0x00004000)
#define SD_CSR_ERASE_RESET              ((uint32_t)0x00002000)
#define SD_CSR_AKE_SEQ_ERROR            ((uint32_t)0x00000008)
#define SD_CSR_ERRORBITS                ((uint32_t)0xFDFFE008)


#define SD_MAX_VOLT_TRIAL               ((uint32_t)0x0000FFFF)
#define SD_ALLZERO                      ((uint32_t)0x00000000)

#define SD_WIDE_BUS_SUPPORT             ((uint32_t)0x00040000)
#define SD_SINGLE_BUS_SUPPORT           ((uint32_t)0x00010000)
#define SD_CARD_LOCKED                  ((uint32_t)0x02000000)

#define SD_0TO7BITS                     ((uint32_t)0x000000FF)
#define SD_8TO15BITS                    ((uint32_t)0x0000FF00)
#define SD_16TO23BITS                   ((uint32_t)0x00FF0000)
#define SD_24TO31BITS                   ((uint32_t)0xFF000000)
#define SD_MAX_DATA_LENGTH              ((uint32_t)0x01FFFFFF)
/** 
  * @brief  Masks for R7 Response 
  */
#define SD_VOLTAGE_WINDOW_SD            ((uint32_t)0x00100000)
#define SD_HIGH_CAPACITY                ((uint32_t)0x40000000)
#define SD_STD_CAPACITY                 ((uint32_t)0x00000000)
#define SD_CHECK_PATTERN                ((uint32_t)0x000001AA)


/** 
  * @brief Supported SD Memory Cards 
  */
#define SDIO_STD_CAPACITY_SD_CARD_V1_1             ((uint32_t)0x00000000)
#define SDIO_STD_CAPACITY_SD_CARD_V2_0             ((uint32_t)0x00000001)
#define SDIO_HIGH_CAPACITY_SD_CARD                 ((uint32_t)0x00000002)
#define SDIO_MULTIMEDIA_CARD                       ((uint32_t)0x00000003)
#define SDIO_SECURE_DIGITAL_IO_CARD                ((uint32_t)0x00000004)
#define SDIO_HIGH_SPEED_MULTIMEDIA_CARD            ((uint32_t)0x00000005)
#define SDIO_SECURE_DIGITAL_IO_COMBO_CARD          ((uint32_t)0x00000006)
#define SDIO_HIGH_CAPACITY_MMC_CARD                ((uint32_t)0x00000007)


/*! @brief SD group number */
typedef enum _sd_group_num
{
    SDH_GroupTimingMode = 0U,     /*!< acess mode group*/
    SDH_GroupCommandSystem = 1U,  /*!< command system group*/
    SDH_GroupDriverStrength = 2U, /*!< driver strength group*/
    SDH_GroupCurrentLimit = 3U,   /*!< current limit group*/
} sd_group_num;

/*! @brief SD card timing mode flags */
typedef enum _sd_timing_mode
{
    SDH_TimingSDR12DefaultMode = 0U,   /*!< Identification mode & SDR12 */
    SDH_TimingSDR25HighSpeedMode = 1U, /*!< High speed mode & SDR25 */
    SDH_TimingSDR50Mode = 2U,          /*!< SDR50 mode*/
    SDH_TimingSDR104Mode = 3U,         /*!< SDR104 mode */
    SDH_TimingDDR50Mode = 4U,          /*!< DDR50 mode */
} sd_timing_mode_t;

/*! @brief SD card switch mode */
typedef enum _sd_switch_mode
{
    SDH_SwitchCheck = 0U, /*!< SD switch mode 0: check function */
    SDH_SwitchSet = 1U,   /*!< SD switch mode 1: set function */
} sd_switch_mode_t;

#define SDH_MSG(a,...)              bflb_platform_printf(a,##__VA_ARGS__)

/*
bus_wide shoud be SDH_DATA_BUS_WIDTH_1BIT/SDH_DATA_BUS_WIDTH_4BITS/SDH_DATA_BUS_WIDTH_8BITS
*/
SD_Error SDH_Init(uint32_t bus_wide,sd_card_t *pOutCardInfo);
SD_Error SD_Erase(uint32_t startaddr, uint32_t endaddr);
SD_Error SDH_BlockReadMultiBlocks(uint8_t *readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
SD_Error SDH_BlockWriteMultiBlocks(uint8_t *writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
SD_Error SDH_ReadMultiBlocks(uint8_t *readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
SD_Error SDH_WriteMultiBlocks(uint8_t *writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks);
#endif /* __SDCARD_H */

