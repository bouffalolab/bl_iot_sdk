/**
  ******************************************************************************
  * @file    bl702_sflash.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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
  *
  ******************************************************************************
  */

#include "string.h"
#include "bl702_sflash.h"
#include "bl702_sf_ctrl.h"
#include "bl702_nf_cfg.h"
#include "bl702_nflash.h"
#include "bl702_l1c.h"

#define SFCTRL_BUSY_STATE_TIMEOUT               (5 * 160 * 1000)
Nand_Flash_Cfg_Type flashCfg;

/*
ECCS provides ECC status as follows:[2:5]
0000b = No bit errors were detected during the previous read algorithm.
0001b = 1 bit error was detected and corrected.
0010b = 2 bit error was detected and corrected.
0011b = 3 bit error was detected and corrected.
0100b = 4 bit error was detected and corrected.
0101b = 5 bit error was detected and corrected.
0110b = 6 bit error was detected and corrected.
0111b = 7 bit error was detected and corrected.
1000b = bit error was detected and not corrected.
1100b = 8bit errors were detected and corrected,
*/
/*
BL_Nand_Flash_Program_Bit_Err_Type ATTR_TCM_SECTION NFlash_Pass(uint8_t errorCode, BL_Nand_Flash_OP_Type opType)
{
	if (opType == ERASE){
		if ((errorCode & 0x04) == 4)
			return E_FAIL;
	}
	else if (opType == READ){
		if ((errorCode & 0x04) == 4)
			return P_FAIL;
	}
	else if (opType == PROGRAM){
		if ((errorCode & 0x3C) == 0x0)
			return NO_BIT;
		else if ((errorCode & 0x3C) == 0x04)
			return ONE_BIT;
		else if ((errorCode & 0x3C) == 0x08)
			return TWO_BIT;
		else if ((errorCode & 0x3C) == 0x0C)
			return THREE_BIT;
		else if ((errorCode & 0x3C) == 0x10)
			return FOUR_BIT;
		else if ((errorCode & 0x3C) == 0x14)
			return FIVE_BIT;
		else if ((errorCode & 0x3C) == 0x18)
			return SIX_BIT;
		else if ((errorCode & 0x3C) == 0x1C)
			return SEVEN_BIT;
		else if ((errorCode & 0x3C) == 0x20)
			return BIT;
		else if ((errorCode & 0x3C) == 0x30)
			return EIGHT_BIT;
	}

	return PROGRAM_OK;
}
*/
DSTATUS ff_disk_initialize (BYTE pdrv)
{
	NF_Cfg_Flash_Identify(0, 1, 0, 0, &flashCfg);
	return RES_OK;
}
DRESULT ff_disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
	//512 bytes in a sector
	uint32_t startaddr = sector * DISK_SECTOR_SIZE;
	uint32_t len = count * DISK_SECTOR_SIZE;
	uint32_t i = 0, curLen = 0;
	Nand_Flash_Cfg_Type flashCfg;
	for(i = 0; i < len;){
		curLen = len - i;
		if(curLen >= FLASH_CTRL_BUF_SIZE){
			curLen = FLASH_CTRL_BUF_SIZE;
		}
		if(NFlash_Read(&flashCfg, startaddr, buff,  curLen) != SUCCESS){
			return RES_ERROR;
		}
		i += curLen;
		buff += curLen;
	}
	return RES_OK;
}
DRESULT ff_disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
	//512 bytes in a sector
	uint32_t startaddr = sector * DISK_SECTOR_SIZE;
	uint32_t len = count * DISK_SECTOR_SIZE;
	uint32_t i = 0, curLen = 0;
	Nand_Flash_Cfg_Type flashCfg;
	for (i = 0; i < len;){
		curLen = len - i;
		if(curLen >= FLASH_CTRL_BUF_SIZE){
			curLen = FLASH_CTRL_BUF_SIZE;
		}
		if (NFlash_Program(&flashCfg, startaddr, buff, curLen) != SUCCESS){
			return RES_ERROR;
		}
		i += curLen;
		buff += curLen;
	}
	return RES_OK;
}
/****************************************************************************//**
 * @brief  Get flash jedec ID
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  data: data pointer to store read data
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_GetJedecId(Nand_Flash_Cfg_Type *flashCfg, uint8_t *data)
{
    uint8_t * const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint8_t cmd = 0x9F, dummyClks = 1;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t timeOut = 0;

    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    flashCmd.cmdBuf[0] = (cmd << 24);
    flashCmd.rwFlag = SF_CTRL_READ;
    /* make dummy bytes zero*/
    flashCmd.addrSize = dummyClks;
    flashCmd.nbData = 2;

    SF_Ctrl_SendCmd(&flashCmd);
    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
	while(SET == SF_Ctrl_GetBusyState()){
		timeOut--;
		if(timeOut == 0){
			return TIMEOUT;
		}
	}

    BL702_MemCpy(data, flashCtrlBuf, flashCmd.nbData);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Erase flash
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  startaddr: start address to erase
 * @param  endaddr: end address(include this address) to erase
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Erase(Nand_Flash_Cfg_Type *flashCfg, uint32_t startAddr, uint32_t endAddr)
{
	uint32_t blockNum = 0;
    uint32_t startBlockNum = 0, endBlockNum = 0;
    uint8_t getFeatureData = 0;

    startBlockNum = startAddr / BFLB_NAND_FLASH_BLK_DATA_SIZE;
    endBlockNum = endAddr / BFLB_NAND_FLASH_BLK_DATA_SIZE;

    if (startAddr <= endAddr){
    	for (blockNum = startBlockNum; blockNum <= endBlockNum; blockNum++){
    		//NFlash_Set_Feature(flashCfg);
    		if (flashCfg->blk128EraseCmd != BFLB_NAND_FLASH_CMD_INVALID){
				NFlash_Write_Enable(flashCfg);
				NFlash_Blk128_Erase(flashCfg, blockNum);
				NFlash_Get_Feature(flashCfg, &getFeatureData, 0xC0);
				// bit[0]:operation in process
				while ((getFeatureData & 1) == 1){
					NFlash_Get_Feature(flashCfg, &getFeatureData, 0xC0);
				}
				// bit[2]:erase fail
				if ((getFeatureData & 4) == 4){
					return ERROR;
				}
			}else{
				return ERROR;
			}
    	}
    }else{
    	return ERROR;
    }

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Erase block
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  blockNum: The number of block(first block is zero)
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Blk128_Erase(Nand_Flash_Cfg_Type *flashCfg, uint32_t blockNum)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t timeOut = 0;

    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

	//RA[6:15]=block
    flashCmd.cmdBuf[0] = (flashCfg->blk128EraseCmd << 24) | (blockNum << 6);
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 3;

    SF_Ctrl_SendCmd(&flashCmd);
    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
	while(SET == SF_Ctrl_GetBusyState()){
		timeOut--;
		if(timeOut == 0){
			return TIMEOUT;
		}
	}

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Write enable
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Write_Enable(Nand_Flash_Cfg_Type *flashCfg)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t timeOut = 0;
    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    /* Write enable*/
    flashCmd.cmdBuf[0] = (flashCfg->writeEnableCmd) << 24;
    /* rwFlag don't care */
    flashCmd.rwFlag = SF_CTRL_READ;
    SF_Ctrl_SendCmd(&flashCmd);
    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
	while(SET == SF_Ctrl_GetBusyState()){
		timeOut--;
		if(timeOut == 0){
			return TIMEOUT;
		}
	}

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Write enable
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  absolutePageNum: The number of pages(each block has 64 pages,
 * block[0]:page[0]~page[63],block[1]:page[64]~page[127]......)
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Page_Read_To_Cache(Nand_Flash_Cfg_Type *flashCfg, uint32_t absolutePageNum)
{
    uint32_t blockNum = 0, pageNum = 0, address = 0;
    uint8_t cmd;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t timeOut = 0;

    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    blockNum = absolutePageNum / BFLB_NAND_FLASH_PAGES_PER_BLOCK;
    //each block has 64 pages
    pageNum = absolutePageNum % BFLB_NAND_FLASH_PAGES_PER_BLOCK;
    address |= pageNum;
    address |= (blockNum << 6);
    /*page read to cache*/
    cmd = flashCfg->pageReadToCacheCmd;
    flashCmd.cmdBuf[0] = (cmd << 24) | (address);
    flashCmd.addrSize = 3;
    flashCmd.rwFlag = SF_CTRL_READ;

    SF_Ctrl_SendCmd(&flashCmd);
    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
	while(SET == SF_Ctrl_GetBusyState()){
		timeOut--;
		if(timeOut == 0){
			return TIMEOUT;
		}
	}

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Set feature
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Set_Feature(Nand_Flash_Cfg_Type *flashCfg)
{
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint8_t cmd;
    uint32_t timeOut = 0;

    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    cmd = flashCfg->setFeaturesCmd;
    flashCmd.cmdBuf[0] = (cmd << 24) | (0xA0 << 16) | (0x0 << 8);
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.addrSize = 2;
    SF_Ctrl_SendCmd(&flashCmd);
    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
	while(SET == SF_Ctrl_GetBusyState()){
		timeOut--;
		if(timeOut == 0){
			return TIMEOUT;
		}
	}

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Get feature
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Get_Feature(Nand_Flash_Cfg_Type *flashCfg, uint8_t *data, uint8_t cmdType)
{
    uint8_t * const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint8_t cmd;
    uint32_t timeOut = 0;

    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    cmd = flashCfg->getFeaturesCmd;
    flashCmd.cmdBuf[0] = (cmd << 24) | (cmdType << 16);
    flashCmd.rwFlag = SF_CTRL_READ;
    flashCmd.nbData = 1;
    flashCmd.addrSize = 1;
    SF_Ctrl_SendCmd(&flashCmd);
    timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
	while(SET == SF_Ctrl_GetBusyState()){
		timeOut--;
		if(timeOut == 0){
			return TIMEOUT;
		}
	}

    BL702_MemCpy(data, flashCtrlBuf, flashCmd.nbData);
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Read from cache
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  addr: start address to read
 * @param  data: data pointer to store read data
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Read_From_Cache(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr, uint8_t *data, uint32_t len, uint8_t readType)
{
    uint8_t * const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint32_t curLen, i, columnAddr = 0, timeOut = 0 ;
    uint8_t cmd, dummyClks;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    if(SF_CTRL_NIO_MODE == flashCfg->ioMode){
		cmd = flashCfg->fastReadCmd;
		dummyClks = flashCfg->frDmyClk;
	}else if(SF_CTRL_DO_MODE == flashCfg->ioMode){
		flashCmd.dataMode = SF_CTRL_DATA_2_LINES;
		cmd = flashCfg->fastReadDoCmd;
		dummyClks = flashCfg->frDoDmyClk;
	}else if(SF_CTRL_DIO_MODE == flashCfg->ioMode){
		flashCmd.addrMode = SF_CTRL_ADDR_2_LINES;
		flashCmd.dataMode = SF_CTRL_DATA_2_LINES;
		cmd = flashCfg->fastReadDioCmd;
		dummyClks = flashCfg->frDioDmyClk;
	}else if(SF_CTRL_QO_MODE == flashCfg->ioMode){
		flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
		cmd = flashCfg->fastReadQoCmd;
		dummyClks=flashCfg->frQoDmyClk;
	}else if(SF_CTRL_QIO_MODE == flashCfg->ioMode){
		flashCmd.addrMode = SF_CTRL_ADDR_4_LINES;
		flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
		cmd = flashCfg->fastReadQioCmd;
		dummyClks=flashCfg->frQioDmyClk;
	}else{
		return ERROR;
	}

    if(readType == READ_DATA_FROM_CACHE){
    columnAddr = addr % BFLB_NAND_FLASH_PAGE_SIZE;
    }else if(readType == READ_SPARE_DATA_FROM_CACHE){
    	columnAddr = addr % BFLB_NAND_FLASH_PAGE_TOTAL_SIZE;
    }else{
    	return ERROR;
    }
    flashCmd.dummyClks = dummyClks;
    flashCmd.addrSize = 2;

    for(i = 0; i < len;){
        /* Prepare command */
        flashCmd.cmdBuf[0] = (cmd << 24) | (columnAddr << 8);
        curLen = len - i;
        if(curLen >= FLASH_CTRL_BUF_SIZE){
            curLen = FLASH_CTRL_BUF_SIZE;
            flashCmd.nbData = curLen;
        }else{
            /* Make sf_ctrl word read */
            flashCmd.nbData = ((curLen + 3) >> 2) << 2;
        }

        SF_Ctrl_SendCmd(&flashCmd);
        timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
		while(SET == SF_Ctrl_GetBusyState()){
			timeOut--;
			if(timeOut == 0){
				return TIMEOUT;
			}
		}

        BL702_MemCpy_Fast(data, flashCtrlBuf, curLen);

        i += curLen;
        data += curLen;
    }

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Program execute
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  addr: start address to program execute
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Program_Execute(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr)
{
	SF_Ctrl_Cmd_Cfg_Type flashCmd;
	uint32_t blockNum = 0, pageNum = 0, address = 0;
	uint32_t timeOut = 0;

	if(((uint32_t)&flashCmd) % 4 == 0){
		BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
	}else{
		BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
	}

	blockNum = addr / BFLB_NAND_FLASH_BLK_DATA_SIZE;
	//each block has 64 pages
	pageNum = (addr / BFLB_NAND_FLASH_PAGE_SIZE) - (blockNum * 64);
	address |= pageNum;
	address |= (blockNum << 6);

	flashCmd.cmdBuf[0] = (flashCfg->pageProgramCmd << 24) | (address);
	/* rwFlag don't care */
	flashCmd.rwFlag = SF_CTRL_WRITE;
	flashCmd.addrSize = 3;

	SF_Ctrl_SendCmd(&flashCmd);
	timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
	while(SET == SF_Ctrl_GetBusyState()){
		timeOut--;
		if(timeOut == 0){
			return TIMEOUT;
		}
	}

	return SUCCESS;
}

BL_Err_Type ATTR_TCM_SECTION NFlash_Check_Bad_Block(Nand_Flash_Cfg_Type *flashCfg, uint32_t blockNum, uint8_t *data, uint32_t len)
{
	uint8_t getFeatureData = 0;
	uint32_t pageNum = 0, readAddr = 0;
	uint32_t stat = 0;
	pageNum = blockNum * BFLB_NAND_FLASH_PAGES_PER_BLOCK;
	readAddr = pageNum * BFLB_NAND_FLASH_PAGE_TOTAL_SIZE + 2048;
	stat = NFlash_Page_Read_To_Cache(flashCfg, pageNum);
	stat = NFlash_Get_Feature(flashCfg, &getFeatureData, 0xC0);
	while ((getFeatureData & 1) == 1){
		stat = NFlash_Get_Feature(flashCfg, &getFeatureData, 0xC0);
	}
	stat = NFlash_Read_From_Cache(flashCfg, readAddr, data, len, 1);
	return stat;
}
/****************************************************************************//**
 * @brief  Read flash
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  startaddr: start address to read
 * @param  data: data pointer to store read data
 * @param  len: the length of read data
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Read(Nand_Flash_Cfg_Type *flashCfg, uint32_t startaddr, uint8_t *data, uint32_t len)
{
    uint8_t getFeatureData = 0;
    uint32_t startPageNum = 0, endPageNum = 0, absolutePageNum = 0;
    uint32_t readLen = 0,  readAddr = 0, beginAddr = startaddr;

    startPageNum = startaddr / BFLB_NAND_FLASH_PAGE_SIZE;
    endPageNum = (startaddr + len - 1) / BFLB_NAND_FLASH_PAGE_SIZE;
    /* Read data */
    if (len > 0){
    	for (absolutePageNum = startPageNum; absolutePageNum <= endPageNum; absolutePageNum++){
    		readAddr = startaddr;
    		if (absolutePageNum == startPageNum){
    			if (beginAddr + len >= BFLB_NAND_FLASH_PAGE_SIZE){
    				readLen = (startPageNum + 1) * BFLB_NAND_FLASH_PAGE_SIZE - beginAddr;
    			}else{
    				readLen = len;
    			}
    		}else if ((startPageNum < absolutePageNum) && (absolutePageNum < endPageNum)){
    			readLen = BFLB_NAND_FLASH_PAGE_SIZE;
    		}else if (absolutePageNum == endPageNum){
    			readLen = (beginAddr + len) - (endPageNum * BFLB_NAND_FLASH_PAGE_SIZE);
    		}

    		NFlash_Page_Read_To_Cache(flashCfg, absolutePageNum);
			NFlash_Get_Feature(flashCfg, &getFeatureData, 0xC0);
			while ((getFeatureData & 1) == 1){
				NFlash_Get_Feature(flashCfg, &getFeatureData, 0xC0);
			}

			NFlash_Read_From_Cache(flashCfg, readAddr, data, readLen, 0);
			startaddr = (absolutePageNum + 1) * BFLB_NAND_FLASH_PAGE_SIZE;
			data += readLen;
    	}
    }else{
    	return ERROR;
    }

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Program load
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  addr: start address to program execute
 * @param  data: data pointer to program load data
 * @param  len: the length of program load data
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Program_Load(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr, const uint8_t *data, uint32_t len)
{
    uint8_t * const flashCtrlBuf = (uint8_t *)SF_CTRL_BUF_BASE;
    uint8_t cmd;
    uint32_t timeOut = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;

    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd) / 4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    if(SF_CTRL_NIO_MODE == flashCfg->ioMode || SF_CTRL_DO_MODE == flashCfg->ioMode || SF_CTRL_DIO_MODE == flashCfg->ioMode)
	{
		cmd = flashCfg->programLoadCmd;
	}else if(SF_CTRL_QIO_MODE == flashCfg->ioMode||SF_CTRL_QO_MODE==flashCfg->ioMode){
		flashCmd.addrMode = (SF_Ctrl_Addr_Mode_Type)flashCfg->qppAddrMode;
		flashCmd.dataMode = SF_CTRL_DATA_4_LINES;
		cmd = flashCfg->qprogramLoadCmd;
	}else{
		return ERROR;
	}

    //program load
    flashCmd.addrSize = 2;
    flashCmd.rwFlag = SF_CTRL_WRITE;
	flashCmd.cmdBuf[0] = (cmd << 24) | (addr << 8);
	flashCmd.nbData = len;
	BL702_MemCpy_Fast(flashCtrlBuf, data, len);
	SF_Ctrl_SendCmd(&flashCmd);
	timeOut = SFCTRL_BUSY_STATE_TIMEOUT;
	while(SET == SF_Ctrl_GetBusyState()){
		timeOut--;
		if(timeOut == 0){
			return TIMEOUT;
		}
	}

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Program load
 *
 * @param  flashCfg: Serial flash parameter configuration pointer
 * @param  addr: start address to program
 * @param  data: data pointer to program load data
 * @param  len: the length of program data
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION NFlash_Program(Nand_Flash_Cfg_Type *flashCfg, uint32_t addr, const uint8_t *data, uint32_t len)
{
    uint8_t getFeatureData = 0;
    SF_Ctrl_Cmd_Cfg_Type flashCmd;
    uint32_t startPageNum = 0, endPageNum = 0, absolutePageNum = 0;
	uint32_t writeLen = 0, programLoadAddr = 0, programExecuteAddr = 0;
	uint32_t i = 0, curLen = 0, offsite = 0, begin_addr =  addr;

	startPageNum = addr / BFLB_NAND_FLASH_PAGE_SIZE;
	endPageNum = (addr + len - 1) / BFLB_NAND_FLASH_PAGE_SIZE;

    if(((uint32_t)&flashCmd) % 4 == 0){
        BL702_MemSet4((uint32_t *)&flashCmd, 0, sizeof(flashCmd)/4);
    }else{
        BL702_MemSet(&flashCmd, 0, sizeof(flashCmd));
    }

    if (len > 0){
		for (absolutePageNum = startPageNum; absolutePageNum <= endPageNum; absolutePageNum++){
			programExecuteAddr = addr;
			offsite = 0;
			curLen = 0;
			if (absolutePageNum == startPageNum){
				if (begin_addr + len >= BFLB_NAND_FLASH_PAGE_SIZE){
					writeLen = (startPageNum + 1) * BFLB_NAND_FLASH_PAGE_SIZE - begin_addr;
				}else{
					writeLen = len;
				}
				programLoadAddr = begin_addr % BFLB_NAND_FLASH_PAGE_SIZE;
			}else if ((startPageNum < absolutePageNum) && (absolutePageNum < endPageNum)){
				writeLen = BFLB_NAND_FLASH_PAGE_SIZE;
				programLoadAddr = 0;
			}else if (absolutePageNum == endPageNum){
				writeLen = (begin_addr + len) - (endPageNum * BFLB_NAND_FLASH_PAGE_SIZE);
				programLoadAddr = 0;
			}
			for(i = 0; i < writeLen;){
				curLen = writeLen - i;
				if(curLen >= FLASH_CTRL_BUF_SIZE){
					curLen = FLASH_CTRL_BUF_SIZE;
				}
				NFlash_Program_Load(flashCfg, programLoadAddr + offsite, data, curLen);
				NFlash_Write_Enable(flashCfg);
				NFlash_Program_Execute(flashCfg, programExecuteAddr + offsite);
				NFlash_Get_Feature(flashCfg, &getFeatureData, 0xC0);
				// bit[0]:operation in process
				while ((getFeatureData & 1) == 1){
					NFlash_Get_Feature(flashCfg, &getFeatureData, 0xC0);
				}
				// bit[3]:program fail
				if ((getFeatureData & 8) == 8){
					return ERROR;
				}
				i += curLen;
				data += curLen;
				offsite += curLen;
			}
			addr = (absolutePageNum + 1) * BFLB_NAND_FLASH_PAGE_SIZE;
		}
    }else{
		return ERROR;
	}

    return SUCCESS;
}
