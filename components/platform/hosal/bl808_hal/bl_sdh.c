/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#include <bl808_glb.h>
#include "bl_sdh.h"


#define SDH_CLK_PIN                     GLB_GPIO_PIN_40
#define SDH_CMD_PIN                     GLB_GPIO_PIN_41
#define SDH_DAT0_PIN                    GLB_GPIO_PIN_42
#define SDH_DAT1_PIN                    GLB_GPIO_PIN_43
#define SDH_DAT2_PIN                    GLB_GPIO_PIN_44
#define SDH_DAT3_PIN                    GLB_GPIO_PIN_45

#define SDH_CLK_PIN_FUN                 GPIO40_FUN_SDH_CLK
#define SDH_CMD_PIN_FUN                 GPIO41_FUN_SDH_CMD
#define SDH_DAT0_PIN_FUN                GPIO42_FUN_SDH_DAT0
#define SDH_DAT1_PIN_FUN                GPIO43_FUN_SDH_DAT1
#define SDH_DAT2_PIN_FUN                GPIO44_FUN_SDH_DAT2
#define SDH_DAT3_PIN_FUN                GPIO45_FUN_SDH_DAT3

#define SDH_SDCARD_IRQn                 SDH_MMC1_IRQn
#define SDH_SDCARD_IRQ_PRIORITY_PRE     (4)
#define SDH_SDCARD_IRQ_PRIORITY_SUB     (0)

#define SDH_CLK_SRC                     (50000000ul)
#define SDH_CLK_INIT                    (400000ul)
#define SDH_CLK_TRANSFER                (50000000ul) 

/* Private variables ---------------------------------------------------------*/
static uint32_t CardType =  SDIO_STD_CAPACITY_SD_CARD_V2_0;


//static uint32_t CSD_Tab[4], CID_Tab[4], RCA = 0;


static sd_card_t *pSDCardInfo = NULL;



static SD_Error SDH_WaitStatus   =  SD_WAITING;
static SDH_Cfg_Type                 SDH_Cfg_Type_Instance;
static SDH_CMD_Cfg_Type             SDH_CMD_Cfg_TypeInstance;
static SDH_Data_Cfg_Type            SDH_Data_Cfg_TypeInstance;
static SDH_Trans_Cfg_Type           SDH_Trans_Cfg_TypeInstance={&SDH_Data_Cfg_TypeInstance,&SDH_CMD_Cfg_TypeInstance};
static SDH_Trans_Callback_Cfg_Type  SDH_Trans_Callback_Cfg_TypeInstance;



static SDH_Handle_Cfg_Type SDH_Handle_Cfg_TypeInstance = {
    .dataCfg =  &SDH_Data_Cfg_TypeInstance,
	  .cmdCfg  =  &SDH_CMD_Cfg_TypeInstance,
};

static SDH_DMA_Cfg_Type   SDH_DMA_Cfg_TypeInstance;
/*causion: ADMA related variables must on OCRAM or shared ram*/
static SDH_ADMA2_Desc_Type adma2Entries[16] __attribute__ ((section (".system_ram")));


/* Private function prototypes -----------------------------------------------*/
static void SDH_GPIO_Init(uint32_t bus_wide);
static void SDH_INT_Init(void);
static SD_Error SDEnWideBus(BL_Fun_Type NewState);
static SD_Error FindSCR(uint16_t rca, uint32_t *pscr);
static SD_Error GetSSR(uint16_t rca, uint32_t *pssr);
static SD_Error IsCardProgramming(uint8_t *pstatus);
static SD_Error WaitInProgramming(void);


static void SD_DecodeCid(sd_card_t *card, uint32_t *rawCid)
{
    sd_cid_t *cid;

    cid = &(card->cid);
    cid->manufacturerID = (uint8_t)((rawCid[3U] & 0xFF0000U) >> 16U);
    cid->applicationID = (uint16_t)((rawCid[3U] & 0xFFFFU) >> 0U);

    cid->productName[0U] = (uint8_t)((rawCid[1U] & 0xFF000000U) >> 24);
    cid->productName[1U] = (uint8_t)((rawCid[2U] & 0xFF) >> 0U);
    cid->productName[2U] = (uint8_t)((rawCid[2U] & 0xFF00U) >> 8U);
    cid->productName[3U] = (uint8_t)((rawCid[2U] & 0xFF0000U) >> 16U);
    cid->productName[4U] = (uint8_t)((rawCid[2U] & 0xFF000000U) >> 24U);

    cid->productVersion = (uint8_t)((rawCid[1U] & 0xFF0000U) >> 16U);

    cid->productSerialNumber = (uint32_t)((rawCid[1U] & 0xFFFFU) << 16U);
    cid->productSerialNumber |= (uint32_t)((rawCid[0U] & 0xFFFF0000U) >> 16U);

    cid->manufacturerData = (uint16_t)((rawCid[0U] & 0xFFFU) >> 0U);
}
static void SD_DecodeCsd(sd_card_t *card, uint32_t *rawCsd)
{
    sd_csd_t *csd;

    csd = &(card->csd);
    csd->csdStructure = (uint8_t)((rawCsd[3U] & 0xC00000U) >> 22U);
    csd->dataReadAccessTime1 = (uint8_t)((rawCsd[3U] & 0xFF00U) >> 8U);
    csd->dataReadAccessTime2 = (uint8_t)((rawCsd[3U] & 0xFFU) >> 0U);
	
    csd->transferSpeed = (uint8_t)((rawCsd[2U] & 0xFF000000U) >> 24);
	  csd->cardCommandClass = (uint16_t)((rawCsd[2U] & 0xFFF000U) >> 12U);
    csd->readBlockLength = (uint8_t)((rawCsd[2U] & 0xF00U) >> 8U);

		csd->deviceSize = (uint32_t)((rawCsd[1U] & 0x3FFFFF00U) >> 8U);
		card->blockSize = 512;
		card->blockCount = ((csd->deviceSize + 1U) * 1024U);
}
static void SD_DecodeScr(sd_card_t *card, uint32_t *rawScr)
{
    sd_scr_t *scr;

    scr = &(card->scr);
    scr->scrStructure = (uint8_t)((rawScr[1U] & 0xF0000000U) >> 28U);
    scr->sdSpecification = (uint8_t)((rawScr[1U] & 0xF000000U) >> 24U);
	
		/*
    if ((uint8_t)((rawScr[1U] & 0x800000U) >> 23U))
    {
				//1 after erase
    }
	  */
		
    scr->sdSecurity = (uint8_t)((rawScr[1U] & 0x700000U) >> 20U);
    scr->sdBusWidths = (uint8_t)((rawScr[1U] & 0xF0000U) >> 16U);

    scr->extendedSecurity = (uint8_t)((rawScr[1U] & 0x7800U) >> 10U);
    scr->commandSupport = (uint8_t)(rawScr[1U] & 0x3U);
    scr->reservedForManufacturer = rawScr[0U];
    /* Get specification version. */  
}


/*!< SDH transfer complete callback */
void SDH_TransferFinished_CallBack(SDH_Handle_Cfg_Type *handle,SDH_Stat_Type status,void *userData)
{

	  //bflb_platform_printf("Interrupt occurs! intFlag=0x%02x,\r\n",handle->intFlag);
	  if(status != SDH_STAT_SUCCESS)
		{
			SDH_WaitStatus = SD_DataCfg_ERROR;
		}
		else
		{
			SDH_WaitStatus = SD_OK;
		}
}
/****************************************************************************//**
 * @brief  SDH GPIO init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void SDH_GPIO_Init(uint32_t bus_wide)
{
	GLB_GPIO_Cfg_Type cfg;
	uint8_t gpiopins[6];
	uint8_t gpiofuns[6];
	uint8_t i=0;

	cfg.gpioMode=GPIO_MODE_AF;
	cfg.pullType=GPIO_PULL_UP;
	cfg.drive=1;
	cfg.smtCtrl=1;

  gpiopins[0]=SDH_CLK_PIN;
  gpiopins[1]=SDH_CMD_PIN;
	gpiopins[2]=SDH_DAT0_PIN;
	gpiopins[3]=SDH_DAT1_PIN;
	gpiopins[4]=SDH_DAT2_PIN;
	gpiopins[5]=SDH_DAT3_PIN;
	
  gpiofuns[0]=SDH_CLK_PIN_FUN;
	gpiofuns[1]=SDH_CMD_PIN_FUN;
	gpiofuns[2]=SDH_DAT0_PIN_FUN;
	gpiofuns[3]=SDH_DAT1_PIN_FUN;
	gpiofuns[4]=SDH_DAT2_PIN_FUN;
	gpiofuns[5]=SDH_DAT3_PIN_FUN;
	switch (bus_wide)
	{
		case SDH_DATA_BUS_WIDTH_1BIT:
			for(i=1;i<sizeof(gpiopins)-3;i++){
				cfg.gpioPin=gpiopins[i];
				cfg.gpioFun=gpiofuns[i];
				GLB_GPIO_Init(&cfg);
			}
			break;
		
		case SDH_DATA_BUS_WIDTH_4BITS:
			for(i=1;i<sizeof(gpiopins);i++){
				cfg.gpioPin=gpiopins[i];
				cfg.gpioFun=gpiofuns[i];
				GLB_GPIO_Init(&cfg);
			}
			break;
		
		/*set 1bit as default*/
		default:
			for(i=1;i<sizeof(gpiopins)-3;i++){
				cfg.gpioPin=gpiopins[i];
				cfg.gpioFun=gpiofuns[i];
				GLB_GPIO_Init(&cfg);
			}
			break;
		
	}
	
	cfg.gpioPin=gpiopins[0];
	cfg.gpioFun=gpiofuns[0];
	cfg.pullType=GPIO_PULL_NONE;	
	GLB_GPIO_Init(&cfg);
}

/****************************************************************************//**
 * @brief  SDH INT init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void SDH_INT_Init(void)
{
    Interrupt_Handler_Register(SDH_SDCARD_IRQn, SDH_MMC1_IRQHandler);
    System_NVIC_SetPriority(SDH_SDCARD_IRQn, 7, 1);
    CPU_Interrupt_Enable(SDH_SDCARD_IRQn);
                           
	SDH_DisableIntSource(SDH_INT_ALL);
	SDH_Trans_Callback_Cfg_TypeInstance.SDH_CallBack_TransferFinished = SDH_TransferFinished_CallBack;
    SDH_InstallHandleCallback(&SDH_Handle_Cfg_TypeInstance, &SDH_Trans_Callback_Cfg_TypeInstance, NULL);
}
SD_Error SDH_PowerON(void)
{
	SD_Error errorstatus = SD_OK;
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
	uint32_t SDType = SD_HIGH_CAPACITY;
	uint32_t response = 0, count = 0, validvoltage = 0;
	
	/* initialise SDH controller*/
	SDH_Cfg_Type_Instance.vlot18Enable = DISABLE;
	SDH_Cfg_Type_Instance.highSpeed = ENABLE;
	SDH_Cfg_Type_Instance.dataWidth = SDH_DATA_BUS_WIDTH_1BIT;
	SDH_Cfg_Type_Instance.volt = SDH_VOLTAGE_3P3V;
	SDH_Cfg_Type_Instance.srcClock = SDH_CLK_SRC;
	SDH_Cfg_Type_Instance.busClock = SDH_CLK_INIT;
	SDH_Ctrl_Init(&SDH_Cfg_Type_Instance);
	
	SDH_Powon();	
	
	/*CMD0: GO_IDLE_STATE, send card to reset state*/
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_GO_IDLE_STATE;
	SDH_CMD_Cfg_TypeInstance.argument = 0;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_NONE;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS)
	{
		return SD_CMD_ERROR;
	}

	/* CMD8: SEND_IF_COND */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_HS_SEND_EXT_CSD;
	SDH_CMD_Cfg_TypeInstance.argument = SD_CHECK_PATTERN;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R7;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS)
	{
		return SD_CMD_ERROR;
	}
	
	//SDH_MSG("R7 is: 0x%02x.\r\n",SDH_CMD_Cfg_TypeInstance.response[0]);
	
	/* SD Card 2.0 */
  CardType = SDIO_STD_CAPACITY_SD_CARD_V2_0;	
	/* parameter for ACMD41, to query card is sdsc or sdhc? */
  SDType = SD_HIGH_CAPACITY;		
	
	/* CMD55: SEND_IF_COND */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_APP_CMD;
	SDH_CMD_Cfg_TypeInstance.argument = 0;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_RESP1_ERROR;
	}
	do{
		/*loop send ACMD41*/
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_APP_CMD;
		SDH_CMD_Cfg_TypeInstance.argument = 0;
		SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
		SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
		SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
		
		SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
		stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
		if(stat != SDH_STAT_SUCCESS){
			return SD_CMD_ERROR;
		}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
			return SD_CMD_RESP1_ERROR;
		}
		/*ACMD41*/
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_APP_OP_COND;
		SDH_CMD_Cfg_TypeInstance.argument = SD_VOLTAGE_WINDOW_SD | SDType;
		SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
		SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R3;
		SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;	
		SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
		stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
		if(stat != SDH_STAT_SUCCESS){
			return SD_CMD_ERROR;
		}
		response = SDH_CMD_Cfg_TypeInstance.response[0];
		validvoltage = (((response >> 31) == 1) ? 1 : 0);	
		count++;	
	}while(  (!validvoltage) && (count < SD_MAX_VOLT_TRIAL)  );

	pSDCardInfo->ocr = response;
	if (response &= SD_HIGH_CAPACITY) {      
		CardType = SDIO_HIGH_CAPACITY_SD_CARD; /* change from sdsc to sdhc */
	}	
	
	
	
	return errorstatus;
}
SD_Error SDH_InitializeCards(void)
{
  SD_Error errorstatus = SD_OK;
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
 	
	/* CMD2: SD_CMD_ALL_SEND_CID */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_ALL_SEND_CID;
	SDH_CMD_Cfg_TypeInstance.argument = 0;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R2;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}
//	CID_Tab[0] = SDH_CMD_Cfg_TypeInstance.response[0];
//	CID_Tab[1] = SDH_CMD_Cfg_TypeInstance.response[1];
//	CID_Tab[2] = SDH_CMD_Cfg_TypeInstance.response[2];
//	CID_Tab[3] = SDH_CMD_Cfg_TypeInstance.response[3];

//	SDH_MSG("CID is: 0x%02x-0x%02x-0x%02x-0x%02x.\r\n",
//				SDH_CMD_Cfg_TypeInstance.response[0],SDH_CMD_Cfg_TypeInstance.response[1],SDH_CMD_Cfg_TypeInstance.response[2],SDH_CMD_Cfg_TypeInstance.response[3]);

	pSDCardInfo->rawCid[0] = SDH_CMD_Cfg_TypeInstance.response[0];
	pSDCardInfo->rawCid[1] = SDH_CMD_Cfg_TypeInstance.response[1];
	pSDCardInfo->rawCid[2] = SDH_CMD_Cfg_TypeInstance.response[2];
	pSDCardInfo->rawCid[3] = SDH_CMD_Cfg_TypeInstance.response[3];
	
	SD_DecodeCid(pSDCardInfo,pSDCardInfo->rawCid);
	
	/*CMD3: send relative card address*/
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_REL_ADDR;
	SDH_CMD_Cfg_TypeInstance.argument = 0;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R6;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}
	//SDH_MSG("RCA is: 0x%02x. status is 0x%02x. \r\n",SDH_CMD_Cfg_TypeInstance.response[0]>>16, SDH_CMD_Cfg_TypeInstance.response[0]&0xffff);

//	RCA = SDH_CMD_Cfg_TypeInstance.response[0]>>16;   /*global variable to save rca*/
	pSDCardInfo->relativeAddress = SDH_CMD_Cfg_TypeInstance.response[0]>>16;
	
	/*CMD9: send card-specific data(CSD)*/
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SEND_CSD;
	SDH_CMD_Cfg_TypeInstance.argument = (uint32_t)( (pSDCardInfo->relativeAddress) << 16);
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R2;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}	
//	CSD_Tab[0] = SDH_CMD_Cfg_TypeInstance.response[0];
//	CSD_Tab[1] = SDH_CMD_Cfg_TypeInstance.response[1];
//	CSD_Tab[2] = SDH_CMD_Cfg_TypeInstance.response[2];
//	CSD_Tab[3] = SDH_CMD_Cfg_TypeInstance.response[3];
//	SDH_MSG("CSD is: 0x%02x-0x%02x-0x%02x-0x%02x.\r\n",
//						SDH_CMD_Cfg_TypeInstance.response[0],SDH_CMD_Cfg_TypeInstance.response[1],SDH_CMD_Cfg_TypeInstance.response[2],SDH_CMD_Cfg_TypeInstance.response[3]);

	pSDCardInfo->rawCsd[0] = SDH_CMD_Cfg_TypeInstance.response[0];
	pSDCardInfo->rawCsd[1] = SDH_CMD_Cfg_TypeInstance.response[1];
	pSDCardInfo->rawCsd[2] = SDH_CMD_Cfg_TypeInstance.response[2];
	pSDCardInfo->rawCsd[3] = SDH_CMD_Cfg_TypeInstance.response[3];	
	
	SD_DecodeCsd(pSDCardInfo,pSDCardInfo->rawCsd);
	return 	errorstatus;
}

#if 0
SD_Error SD_GetCardInfo(SD_CardInfo *cardinfo)
{
  SD_Error errorstatus = SD_OK;
  uint32_t tmp = 0;
	
	cardinfo->CardType = (uint8_t)CardType;
  cardinfo->RCA = (uint16_t)RCA;
	
	/*deal with CSD*/

  /*!< Byte 14 */
  tmp = (uint8_t)((CSD_Tab[3] & 0xFF0000) >> 16);
  cardinfo->SD_csd.CSDStruct = (tmp & 0xC0) >> 6;
  cardinfo->SD_csd.SysSpecVersion = (tmp & 0x3C) >> 2;
  cardinfo->SD_csd.Reserved1 = tmp & 0x03;
  /*!< Byte 13 */
  tmp = (uint8_t)((CSD_Tab[3] & 0x00FF00) >> 8);
  cardinfo->SD_csd.TAAC = tmp;
  /*!< Byte 12 */
  tmp = (uint8_t)((CSD_Tab[3] & 0x0000FF) >> 0);
  cardinfo->SD_csd.NSAC = tmp;	
  /*!< Byte 11 */
  tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000)>>24);
  cardinfo->SD_csd.MaxBusClkFrec = tmp;
  /*!< Byte 10 */
  tmp = (uint16_t)((CSD_Tab[2] & 0x00FFF000) >> 12);
  cardinfo->SD_csd.CardComdClasses = tmp;
  /*!< Byte 9 */
  tmp = (uint8_t)((CSD_Tab[2] & 0x00000F00) >> 8);
  cardinfo->SD_csd.RdBlockLen = tmp;
  /*!< Byte 8 */
  tmp = (uint8_t)(CSD_Tab[2] & 0x000000FF);
  cardinfo->SD_csd.PartBlockRead = (tmp & 0x80) >> 7;
  cardinfo->SD_csd.WrBlockMisalign = (tmp & 0x40) >> 6;
  cardinfo->SD_csd.RdBlockMisalign = (tmp & 0x20) >> 5;
  cardinfo->SD_csd.DSRImpl = (tmp & 0x10) >> 4;
  cardinfo->SD_csd.Reserved2 = 0; /*!< Reserved */	
	
  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)	
	{
    /*!< Byte 7 6 5 */
    tmp = (uint32_t)((CSD_Tab[1] & 0x3FFFFF00)>>8);
    cardinfo->SD_csd.DeviceSize = tmp;
    
    cardinfo->CardCapacity = (cardinfo->SD_csd.DeviceSize + 1) * 512;
    cardinfo->CardBlockSize = 512;    		
	}
	/*deal with CID*/
	/*!< Byte 14 */
  tmp = (uint8_t)((CID_Tab[3] & 0xFF0000) >> 16);
  cardinfo->SD_cid.ManufacturerID = tmp;
	/*!< Byte 13,12 */
  tmp = (CID_Tab[3] & 0x00FFFF);
	cardinfo->SD_cid.OEM_AppliID[0] = (tmp&0xff00)>>8;
  cardinfo->SD_cid.OEM_AppliID[1] = tmp&0xff;
	cardinfo->SD_cid.OEM_AppliID[2] = 0;
	/*!< Byte 11,10,9,8 */
	tmp = CID_Tab[2];
	cardinfo->SD_cid.ProdName[5] = 0;
	cardinfo->SD_cid.ProdName[3] = (tmp & 0xff);
	cardinfo->SD_cid.ProdName[2] = (tmp & 0xff00)>>8;
	cardinfo->SD_cid.ProdName[1] = (tmp & 0xff0000)>>16;
	cardinfo->SD_cid.ProdName[0] = (tmp & 0xff000000)>>24;
	/*!< Byte 7*/
	tmp = CID_Tab[1];
	cardinfo->SD_cid.ProdName[4] = (tmp & 0xff000000) >>24;
	/*!< Byte 6*/
	cardinfo->SD_cid.ProdRev = (tmp & 0xff0000)>>16;
	/*!< Byte 5,4*/
	cardinfo->SD_cid.ProdSN = (tmp&0xffff)<<16;
	
	/*!< Byte 3*/
	tmp=CID_Tab[0];
	cardinfo->SD_cid.ProdSN |= ((tmp&0xffff0000)>>16);
	
	cardinfo->SD_cid.month = (tmp&0x0000000F) ;
	cardinfo->SD_cid.year = ((tmp&0x00000FF0)>>4) +2000;
	
	return 	errorstatus;
}
#endif

SD_Error SD_SelectDeselect(uint32_t addr)
{
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
	SD_Error errorstatus = SD_OK;
	/* CMD7: select/deselect specified card */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SEL_DESEL_CARD;
	SDH_CMD_Cfg_TypeInstance.argument = addr;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1B;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	

	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_RESP1_ERROR;
	}	
	return errorstatus;
	
}
static SD_Error SDEnWideBus(BL_Fun_Type NewState)
{
  SD_Error errorstatus = SD_OK;
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
	uint32_t widthArgs=0; /*'0b00' = 1bit or '0b10'=4bit*/
  uint32_t scr[2] = {0, 0};
	
  /*!< Get SCR Register */
  errorstatus = FindSCR(pSDCardInfo->relativeAddress, scr);
  if (errorstatus != SD_OK)		
  {
    return(errorstatus);
  }
  /*!< If wide bus operation to be enabled */
  if (NewState == ENABLE)
		widthArgs = 0x02;
	
	if( (scr[1] & (SD_WIDE_BUS_SUPPORT|SD_SINGLE_BUS_SUPPORT) ) != SD_ALLZERO){
		
		/*!< Send CMD55 APP_CMD with argument as card's RCA */
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_APP_CMD;
		SDH_CMD_Cfg_TypeInstance.argument = (((uint32_t) pSDCardInfo->relativeAddress )<< 16);
		SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
		SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
		SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
		
		SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
		stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
		if(stat != SDH_STAT_SUCCESS){
			return SD_CMD_ERROR;
		}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
			return SD_CMD_RESP1_ERROR;
		}			
		/*!< Send ACMD6 APP_CMD with argument as 2 for wide bus mode */
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_APP_SD_SET_BUSWIDTH;
		SDH_CMD_Cfg_TypeInstance.argument = widthArgs;
		SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
		SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
		SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
		
		SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
		stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
		if(stat != SDH_STAT_SUCCESS){
			return SD_CMD_ERROR;
		}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
			return SD_CMD_RESP1_ERROR;
		}
		
	}else{
			errorstatus = SD_REQUEST_NOT_APPLICABLE;
			return(errorstatus);
	}
	return errorstatus;
}
static SD_Error FindSCR(uint16_t rca, uint32_t *pscr)
{
  SD_Error errorstatus = SD_OK;
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
	uint32_t tempscr[2] = {0, 0};	
	
	if(pscr == NULL)
		return SD_INVALID_PARAMETER;
	SDH_DisableDMA();
	
	/*!< Send CMD55 APP_CMD with argument as card's RCA */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_APP_CMD;
	SDH_CMD_Cfg_TypeInstance.argument = (((uint32_t) rca )<< 16);
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_RESP1_ERROR;
	}
	
	/*!< Set Block Size To 8 Bytes */ 
	SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
	SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
	SDH_Data_Cfg_TypeInstance.blockSize = 8;
	SDH_Data_Cfg_TypeInstance.blockCount = 1;
	SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
	SDH_Data_Cfg_TypeInstance.rxData = tempscr;
	SDH_Data_Cfg_TypeInstance.txDataLen = 0;
	SDH_Data_Cfg_TypeInstance.txData = NULL;	
	/* Config the data transfer parameter */
	stat = SDH_ConfigDataTranfer(&SDH_Data_Cfg_TypeInstance);
	if (SDH_STAT_SUCCESS != stat){
			return SD_DataCfg_ERROR;
	}
	
	/*!< Send ACMD51 SD_APP_SEND_SCR with argument as 0 */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_APP_SEND_SCR;
	SDH_CMD_Cfg_TypeInstance.argument = 0;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_RESP1_ERROR;
	}	
	
	/*polling data*/
	stat = SDH_TransferDataBlocking(&SDH_Data_Cfg_TypeInstance, 0);
	if (SDH_STAT_SUCCESS != stat){
			return SD_DATA_ERROR;
	}	

	*(pscr + 1) = ((tempscr[0] & SD_0TO7BITS) << 24) | ((tempscr[0] & SD_8TO15BITS) << 8) | ((tempscr[0] & SD_16TO23BITS) >> 8) | ((tempscr[0] & SD_24TO31BITS) >> 24);
  *(pscr) = ((tempscr[1] & SD_0TO7BITS) << 24) | ((tempscr[1] & SD_8TO15BITS) << 8) | ((tempscr[1] & SD_16TO23BITS) >> 8) | ((tempscr[1] & SD_24TO31BITS) >> 24);
//	SDH_MSG("scr[0]=0x%x,scr[1]=0x%x.\r\n",pscr[0],pscr[1]);
	
	pSDCardInfo->rawScr[0] = pscr[0];
	pSDCardInfo->rawScr[1] = pscr[1];
	SD_DecodeScr(pSDCardInfo,pSDCardInfo->rawScr);
	
	return errorstatus;	
}
/*
* Get SD status register
* pssr points 64bytes array
*/
static SD_Error GetSSR(uint16_t rca, uint32_t *pssr)
{
  SD_Error errorstatus = SD_OK;
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;

	
	if(pssr == NULL)
		return SD_INVALID_PARAMETER;
	SDH_DisableDMA();
	
	/*!< Send CMD55 APP_CMD with argument as card's RCA */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_APP_CMD;
	SDH_CMD_Cfg_TypeInstance.argument = (((uint32_t) rca )<< 16);
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_RESP1_ERROR;
	}
	
	/*!< Set Block Size To 512 Bytes */ 
	SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
	SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
	SDH_Data_Cfg_TypeInstance.blockSize = 64;
	SDH_Data_Cfg_TypeInstance.blockCount = 1;
	SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
	SDH_Data_Cfg_TypeInstance.rxData = pssr;
	SDH_Data_Cfg_TypeInstance.txDataLen = 0;
	SDH_Data_Cfg_TypeInstance.txData = NULL;	
	/* Config the data transfer parameter */
	stat = SDH_ConfigDataTranfer(&SDH_Data_Cfg_TypeInstance);
	if (SDH_STAT_SUCCESS != stat){
			return SD_DataCfg_ERROR;
	}
	
	/*!< Send ACMD13 SD_APP_SEND_SCR with argument as 0 */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_APP_STAUS;
	SDH_CMD_Cfg_TypeInstance.argument = 0;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_RESP1_ERROR;
	}	
	
	/*polling data*/
	stat = SDH_TransferDataBlocking(&SDH_Data_Cfg_TypeInstance, 0);
	if (SDH_STAT_SUCCESS != stat){
			return SD_DATA_ERROR;
	}	
	
	return errorstatus;	
}
/*
 *         @arg SDIO_BusWide_8b: 8-bit data transfer
 *         @arg SDIO_BusWide_4b: 4-bit data transfer
 *         @arg SDIO_BusWide_1b: 1-bit data transfer (default)
 */
SD_Error SD_EnableWideBusOperation(SDH_Data_Bus_Width_Type WideMode)
{
  SD_Error errorstatus = SD_OK;
	
	if ((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
	{
    if (SDH_DATA_BUS_WIDTH_8BITS == WideMode)   //2.0 sdh do not support 8-bit mode
    {
      errorstatus = SD_UNSUPPORTED_FEATURE;
      return(errorstatus);
    }		
    else if (SDH_DATA_BUS_WIDTH_4BITS == WideMode)
    {
			errorstatus = SDEnWideBus(ENABLE);
			if (SD_OK == errorstatus)
      {
				/* reinitialise SDH controller*/
				SDH_Cfg_Type_Instance.vlot18Enable = DISABLE;
				SDH_Cfg_Type_Instance.highSpeed = ENABLE;
				SDH_Cfg_Type_Instance.dataWidth = SDH_DATA_BUS_WIDTH_4BITS;
				SDH_Cfg_Type_Instance.volt = SDH_VOLTAGE_3P3V;
				SDH_Cfg_Type_Instance.srcClock = SDH_CLK_SRC;
				SDH_Cfg_Type_Instance.busClock = SDH_CLK_TRANSFER;
				SDH_Ctrl_Init(&SDH_Cfg_Type_Instance);				
			}
		}
		else
		{
      errorstatus = SDEnWideBus(DISABLE);
			if (SD_OK == errorstatus)
      {
				/* reinitialise SDH controller*/
				SDH_Cfg_Type_Instance.vlot18Enable = DISABLE;
				SDH_Cfg_Type_Instance.highSpeed = ENABLE;
				SDH_Cfg_Type_Instance.dataWidth = SDH_DATA_BUS_WIDTH_1BIT;
				SDH_Cfg_Type_Instance.volt = SDH_VOLTAGE_3P3V;
				SDH_Cfg_Type_Instance.srcClock = SDH_CLK_SRC;
				SDH_Cfg_Type_Instance.busClock = SDH_CLK_TRANSFER;
				SDH_Ctrl_Init(&SDH_Cfg_Type_Instance);				
			}			
		}
		
	}
	return errorstatus;	
}
SD_Error SD_SwitchFunction(uint32_t mode, uint32_t group, uint32_t number, uint32_t *status)
{
	
  SD_Error errorstatus = SD_OK;
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;

		
	/*!< Set Block Size To 512 Bytes */ 
	SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
	SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
	SDH_Data_Cfg_TypeInstance.blockSize = 64;
	SDH_Data_Cfg_TypeInstance.blockCount = 1;
	SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
	SDH_Data_Cfg_TypeInstance.rxData = status;
	SDH_Data_Cfg_TypeInstance.txDataLen = 0;
	SDH_Data_Cfg_TypeInstance.txData = NULL;	
	/* Config the data transfer parameter */
	stat = SDH_ConfigDataTranfer(&SDH_Data_Cfg_TypeInstance);
	if (SDH_STAT_SUCCESS != stat){
			return SD_DataCfg_ERROR;
	}
	
	/*!< Send CMD6 SD_CMD_HS_SWITCH with argument as 0 */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_HS_SWITCH;
	SDH_CMD_Cfg_TypeInstance.argument = (mode << 31U | 0x00FFFFFFU);
	SDH_CMD_Cfg_TypeInstance.argument &= ~((uint32_t)(0xFU) << (group * 4U));
	SDH_CMD_Cfg_TypeInstance.argument |= (number << (group * 4U));
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_RESP1_ERROR;
	}	
	

	/*polling data*/
	stat = SDH_TransferDataBlocking(&SDH_Data_Cfg_TypeInstance, 0);
	if (SDH_STAT_SUCCESS != stat){
			return SD_DATA_ERROR;
	}	
    return errorstatus;
}
SD_Error SD_SelectFunction(uint32_t group, uint32_t function)
{
  SD_Error errorstatus = SD_OK;
	uint32_t cmd6Status[16] = {0};
	uint16_t functionGroupInfo[6U] = {0};
  uint32_t currentFunctionStatus = 0U;

	uint32_t i;
	
	/* Check if card support high speed mode. */
	if (SD_OK != SD_SwitchFunction(SDH_SwitchCheck, group, function, cmd6Status))
	{
			return SD_SWITCH_ERROR;
	}	
	
	for(i=0;i<16;i++)
	{
		//bflb_platform_printf("cmd6Status[%d]=0x%x.\r\n",i,cmd6Status[i]);
	}
	/* In little endian mode, SD bus byte transferred first is the byte stored in lowest byte position in
	a word which will cause 4 byte's sequence in a word is not consistent with their original sequence from
	card. So the sequence of 4 bytes received in a word should be converted. */
	cmd6Status[0U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[0U]);
	cmd6Status[1U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[1U]);
	cmd6Status[2U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[2U]);
	cmd6Status[3U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[3U]);
	cmd6Status[4U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[4U]);	
	
	functionGroupInfo[5U] = (uint16_t)cmd6Status[0U];
  functionGroupInfo[4U] = (uint16_t)(cmd6Status[1U] >> 16U);
  functionGroupInfo[3U] = (uint16_t)(cmd6Status[1U]);
  functionGroupInfo[2U] = (uint16_t)(cmd6Status[2U] >> 16U);
  functionGroupInfo[1U] = (uint16_t)(cmd6Status[2U]);
  functionGroupInfo[0U] = (uint16_t)(cmd6Status[3U] >> 16U);
	currentFunctionStatus = ((cmd6Status[3U] & 0xFFFFU) << 8U) | (cmd6Status[4U] >> 24U);
	
	for(i=0;i<6;i++)
	{
		//bflb_platform_printf("functionGroupInfo[%d]=0x%x.\r\n",i,functionGroupInfo[i]);
	}	
	
	//bflb_platform_printf("currentFunctionStatus = 0x%x.\r\n",currentFunctionStatus);
	
	/* check if function is support */
	if (((functionGroupInfo[group] & (1 << function)) == 0U) ||
			((currentFunctionStatus >> (group * 4U)) & 0xFU) != function)
	{
			return SD_SWITCH_ERROR;
	}		


	/* Check if card support high speed mode. */
	if (SD_OK != SD_SwitchFunction(SDH_SwitchSet, group, function, cmd6Status))
	{
			return SD_SWITCH_ERROR;
	}	
	/* In little endian mode is little endian, SD bus byte transferred first is the byte stored in lowest byte
	position in a word which will cause 4 byte's sequence in a word is not consistent with their original
	sequence from card. So the sequence of 4 bytes received in a word should be converted. */
	cmd6Status[3U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[3U]);
	cmd6Status[4U] = SWAP_WORD_BYTE_SEQUENCE(cmd6Status[4U]);

	/* According to the "switch function status[bits 511~0]" return by switch command in mode "set function":
		 -check if group 1 is successfully changed to function 1 by checking if bits 379~376 equal value 1;
	 */
	currentFunctionStatus = ((cmd6Status[3U] & 0xFFFFU) << 8U) | (cmd6Status[4U] >> 24U);
	//bflb_platform_printf("currentFunctionStatus = 0x%x.\r\n",currentFunctionStatus);
	

	if (((currentFunctionStatus >> (group * 4U)) & 0xFU) != function)
	{
			return SD_SWITCH_ERROR;
	}	
	
	
  return errorstatus;	
}
/**
  * @brief  Initializes the SD card device.
  * @retval SD status
  */
SD_Error SDH_Init(uint32_t bus_wide,sd_card_t *pOutCardInfo)
{
  SD_Error errorstatus = SD_OK;

//	uint32_t i;
	
	if(pOutCardInfo==NULL)
		return SD_INVALID_PARAMETER;
	
	pSDCardInfo = pOutCardInfo;
	/* config SDH gpio */
	SDH_GPIO_Init(bus_wide);
	
	SDH_INT_Init();	
	
  /* Config SDH clk ,use 50M */
  GLB_Set_SDH_CLK(ENABLE,GLB_SDH_CLK_50M);
	
	/* reset SDH controller*/
	SDH_Reset();
	SDH_Set_Timeout(0x0e);
	
	errorstatus = SDH_PowerON();
  if (errorstatus != SD_OK)
  { /*fails at powerup stage*/
    return(errorstatus);	
  }

	errorstatus = SDH_InitializeCards(); 
  if (errorstatus != SD_OK)
  { /*fails at InitializeCards stage*/
    return(errorstatus);	
  }
	
	/*
  errorstatus = SD_GetCardInfo(&SDCardInfo);	
  if (errorstatus != SD_OK)
  { 
    return(errorstatus);	
  }
	*/
	
	errorstatus = SD_SelectDeselect((uint32_t) ( (pSDCardInfo->relativeAddress) << 16));	  
  if (errorstatus != SD_OK)
  { /*fails at select stage*/
    return(errorstatus);	
  }	

	/* setup 4-bit mode and uplift SDH_CLK to 50MHz*/
	errorstatus = SD_EnableWideBusOperation(bus_wide);
	if (errorstatus != SD_OK)
  { /*fails at EnableWideBusOperation stage*/
    return(errorstatus);	
  }	

	errorstatus = GetSSR(pSDCardInfo->relativeAddress,pSDCardInfo->rawSsr);
	if (errorstatus != SD_OK)
  { 
    return(errorstatus);	
  }	
		
	//SD_SelectFunction(SDH_GroupTimingMode,SDH_TimingSDR25HighSpeedMode);
  return  errorstatus;
}

/**
  * @brief  Allows to erase memory area specified for the given card.
  * @param  startaddr: the start address.
  * @param  endaddr: the end address.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_Erase(uint32_t startaddr, uint32_t endaddr)
{
	SD_Error errorstatus = SD_OK;
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
	uint32_t maxdelay = 0;
	uint8_t cardstate = 0;
	
	maxdelay = 120000/(SDH_CLK_SRC/SDH_CLK_TRANSFER);
	
  /*!< According to sd-card spec 1.0 ERASE_GROUP_START (CMD32) and erase_group_end(CMD33) */
  if ((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
  {
		/*!< Send CMD32 SD_ERASE_GRP_START with argument as addr  */
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_ERASE_GRP_START;
		SDH_CMD_Cfg_TypeInstance.argument = startaddr;
		SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
		SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
		SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
		
		SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
		stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
		if(stat != SDH_STAT_SUCCESS){
			return SD_CMD_ERROR;
		}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
			return SD_CMD_ERASE_ERROR;
		}	

    /*!< Send CMD33 SD_ERASE_GRP_END with argument as addr  */
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SD_ERASE_GRP_END;
		SDH_CMD_Cfg_TypeInstance.argument = endaddr;
		SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
		SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
		SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
		
		SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
		stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
		if(stat != SDH_STAT_SUCCESS){
			return SD_CMD_ERROR;
		}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
			return SD_CMD_ERASE_ERROR;
		}		
  }	
  /*!< Send CMD38 ERASE */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_ERASE;
	SDH_CMD_Cfg_TypeInstance.argument = 0;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1B;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_ERASE_ERROR;
	}	

  if (errorstatus != SD_OK)
  {
    return(errorstatus);
  }

  while(maxdelay--){}
	
  /*!< Wait till the card is in programming state */
  errorstatus = IsCardProgramming(&cardstate);
  while ((errorstatus == SD_OK) && ((SD_CARD_PROGRAMMING == cardstate) || (SD_CARD_RECEIVING == cardstate)))
  {
    errorstatus = IsCardProgramming(&cardstate);
  }	
	
  return(errorstatus);	
}
static SD_Error WaitInProgramming(void)
{
	uint8_t cardstate = 0;	
	SD_Error errorstatus = SD_OK;
	uint32_t maxdelay = 0;
	maxdelay = 120000/(SDH_CLK_SRC/SDH_CLK_TRANSFER);	
	
	while(maxdelay--){}
  /*!< Wait till the card is in programming state */
  errorstatus = IsCardProgramming(&cardstate);
  while ((errorstatus == SD_OK) && ((SD_CARD_PROGRAMMING == cardstate) || (SD_CARD_RECEIVING == cardstate)))
  {
    errorstatus = IsCardProgramming(&cardstate);
  }	
	
	return errorstatus;
}
/*check sd card state*/
static SD_Error IsCardProgramming(uint8_t *pstatus)
{
  SD_Error errorstatus = SD_OK;
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;

  /*cmd13 addressed card send its status*/
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SEND_STATUS;
	SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) (pSDCardInfo->relativeAddress) << 16;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_PROGRAM_ERROR;
	}	
	  /*!< Find out card status */
  *pstatus = (uint8_t) ((SDH_CMD_Cfg_TypeInstance.response[0] >> 9) & 0x0000000F);   //status[12:9] :cardstate
	
  return(errorstatus);		
}
/**
  * @brief  Allows to read blocks from a specified address  in a card.  The Data
  *         transfer can be managed by DMA mode or Polling mode. //?????
  * @note   This operation should be followed by two functions to check if the 
  *         DMA Controller and SD Card status.	   //dma????????????
  *          - SD_ReadWaitOperation(): this function insure that the DMA
  *            controller has finished all data transfer. 
  *          - SD_GetStatus(): to check that the SD Card has finished the 
  *            data transfer and it is ready for data.   
  * @param  readbuff: pointer to the buffer that will contain the received data.
  * @param  ReadAddr: Address from where data are to be read.
  * @param  BlockSize: the SD card Data block size. The Block size should be 512.
  * @param  NumberOfBlocks: number of blocks to be read.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SDH_BlockReadMultiBlocks(uint8_t *readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  SD_Error errorstatus = SD_OK;	
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)//for sdhc block size is fixed to 512bytes 
  {
    BlockSize = 512;
  }	
	/*!< Set Block Size for SDSC Card,cmd16,no impact on SDHC card */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_BLOCKLEN;
	SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) BlockSize;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_ERROR;
	}	
	
	/*set cmd parameter for READ_MULTIPLE_BLOCK*/
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_READ_MULT_BLOCK;
	//SDH_CMD_Cfg_TypeInstance.index = SD_CMD_READ_SINGLE_BLOCK;
	SDH_CMD_Cfg_TypeInstance.argument =  (uint32_t)ReadAddr;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;	
	/*set data parameter for READ_MULTIPLE_BLOCK*/
	SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = ENABLE;
	SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
	SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
	SDH_Data_Cfg_TypeInstance.blockSize = BlockSize;
	SDH_Data_Cfg_TypeInstance.blockCount = NumberOfBlocks;
	SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
	SDH_Data_Cfg_TypeInstance.rxData = (uint32_t *)readbuff;
	SDH_Data_Cfg_TypeInstance.txDataLen = 0;
	SDH_Data_Cfg_TypeInstance.txData = NULL;	
	/*set parameters for SDH_DMA_Cfg_TypeInstance*/
	SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
	SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_128_BYTES;
	SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;
	SDH_DMA_Cfg_TypeInstance.admaEntries = (uint32_t *)adma2Entries;
	SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries)/sizeof(adma2Entries[0]);
	
	stat = SDH_TransferBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);
	
	if(stat != SDH_STAT_SUCCESS){
		return SD_DATA_ERROR;
	}
	return(errorstatus);		
}
SD_Error SDH_ReadMultiBlocks(uint8_t *readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  SD_Error errorstatus = SD_OK;	
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)//for sdhc block size is fixed to 512bytes 
  {
    BlockSize = 512;
  }	
	
	//SDH_MSG("Read-->IN, read %d blocks from %d with buffer 0x%p. \r\n",NumberOfBlocks,ReadAddr,readbuff);
	
	/*!< Set Block Size for SDSC Card,cmd16,no impact on SDHC card */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_BLOCKLEN;
	SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) BlockSize;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_ERROR;
	}	
	
	/*set cmd parameter for READ_MULTIPLE_BLOCK*/
	if(NumberOfBlocks<=1)
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_READ_SINGLE_BLOCK;
	else
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_READ_MULT_BLOCK;

	SDH_CMD_Cfg_TypeInstance.argument =  (uint32_t)ReadAddr;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;	
	/*set data parameter for READ_MULTIPLE_BLOCK*/
	if(NumberOfBlocks<=1)
		SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
	else
		SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = ENABLE;
	
	SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
	SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
	SDH_Data_Cfg_TypeInstance.blockSize = BlockSize;
	SDH_Data_Cfg_TypeInstance.blockCount = NumberOfBlocks;
	SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
	SDH_Data_Cfg_TypeInstance.rxData = (uint32_t *)readbuff;
	SDH_Data_Cfg_TypeInstance.txDataLen = 0;
	SDH_Data_Cfg_TypeInstance.txData = NULL;	
	/*set parameters for SDH_DMA_Cfg_TypeInstance*/
	SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
	SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_128_BYTES;
	SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;
	SDH_DMA_Cfg_TypeInstance.admaEntries = (uint32_t *)adma2Entries;
	SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries)/sizeof(adma2Entries[0]);
	
	stat = SDH_TransferNonBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);
	
	if(stat != SDH_STAT_SUCCESS){
		if(stat == SDH_STAT_DMA_ADDR_NOT_ALIGN)
			return SD_ADMA_ALIGN_ERROR;
		else
			return SD_DATA_ERROR;
	}
	
	SDH_ITConfig(SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,ENABLE);
	
	/*wait for Xfer status. might pending here in multi-task OS*/
	while(SDH_WaitStatus == SD_WAITING){}
	
	SDH_ITConfig(SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,DISABLE);
		
	errorstatus = SDH_WaitStatus;
	SDH_WaitStatus = SD_WAITING;
	
		
	//SDH_MSG("Read-->OUT, read %d blocks from %d with buffer 0x%p. \r\n",NumberOfBlocks,ReadAddr,readbuff);

	return(errorstatus);		
}

SD_Error SDH_BlockWriteMultiBlocks(uint8_t *writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  SD_Error errorstatus = SD_OK;	
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)//for sdhc block size is fixed to 512bytes 
  {
    BlockSize = 512;
  }	
	/*!< Set Block Size for SDSC Card,cmd16,no impact on SDHC card */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_BLOCKLEN;
	SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) BlockSize;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_ERROR;
	}	
	
	/*set cmd parameter for SD_CMD_WRITE_MULT_BLOCK*/
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_WRITE_MULT_BLOCK;
	SDH_CMD_Cfg_TypeInstance.argument =  (uint32_t)WriteAddr;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;	
	/*set data parameter for WRITE_MULTIPLE_BLOCK*/
	SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = ENABLE;
	SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
	SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
	SDH_Data_Cfg_TypeInstance.blockSize = BlockSize;
	SDH_Data_Cfg_TypeInstance.blockCount = NumberOfBlocks;
	SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
	SDH_Data_Cfg_TypeInstance.rxData = NULL;
	SDH_Data_Cfg_TypeInstance.txDataLen = 0;
	SDH_Data_Cfg_TypeInstance.txData = (uint32_t *)writebuff;
	/*set parameters for SDH_DMA_Cfg_TypeInstance*/
	SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
	SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_128_BYTES;
	SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;
	SDH_DMA_Cfg_TypeInstance.admaEntries = (uint32_t *)adma2Entries;
	SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries)/sizeof(adma2Entries[0]);
	
	stat = SDH_TransferBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_DATA_ERROR;
	}
	
	errorstatus = WaitInProgramming();
	
	return(errorstatus);		
}
SD_Error SDH_WriteMultiBlocks(uint8_t *writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  SD_Error errorstatus = SD_OK;	
	SDH_Stat_Type stat = SDH_STAT_SUCCESS;
  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)//for sdhc block size is fixed to 512bytes 
  {
    BlockSize = 512;
  }	
	//SDH_MSG("Write-->IN, write %d blocks to %d with buffer 0x%p. \r\n",NumberOfBlocks,WriteAddr,writebuff);
	
	/*!< Set Block Size for SDSC Card,cmd16,no impact on SDHC card */
	SDH_CMD_Cfg_TypeInstance.index = SD_CMD_SET_BLOCKLEN;
	SDH_CMD_Cfg_TypeInstance.argument = (uint32_t) BlockSize;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_NONE;
	
	SDH_SendCommand(&SDH_CMD_Cfg_TypeInstance);	
	stat = SDH_WaitCommandDone(&SDH_CMD_Cfg_TypeInstance);
	if(stat != SDH_STAT_SUCCESS){
		return SD_CMD_ERROR;
	}else if(SDH_CMD_Cfg_TypeInstance.response[0] & SD_CSR_ERRORBITS){
		return SD_CMD_ERROR;
	}	
	
	/*set cmd parameter for SD_CMD_WRITE_MULT_BLOCK*/
	if(NumberOfBlocks<=1)
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_WRITE_SINGLE_BLOCK;
	else
		SDH_CMD_Cfg_TypeInstance.index = SD_CMD_WRITE_MULT_BLOCK;
	
	SDH_CMD_Cfg_TypeInstance.argument =  (uint32_t)WriteAddr;
	SDH_CMD_Cfg_TypeInstance.type = SDH_CMD_NORMAL;
	SDH_CMD_Cfg_TypeInstance.respType = SDH_RESP_R1;
	SDH_CMD_Cfg_TypeInstance.flag = SDH_TRANS_FLAG_DATA_PRESENT;	
	/*set data parameter for WRITE_MULTIPLE_BLOCK*/
	if(NumberOfBlocks<=1)
		SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = DISABLE;
	else
		SDH_Data_Cfg_TypeInstance.enableAutoCommand12 = ENABLE;
	
	SDH_Data_Cfg_TypeInstance.enableAutoCommand23 = DISABLE;
	SDH_Data_Cfg_TypeInstance.enableIgnoreError = DISABLE;
	SDH_Data_Cfg_TypeInstance.dataType = SDH_TRANS_DATA_NORMAL;
	SDH_Data_Cfg_TypeInstance.blockSize = BlockSize;
	SDH_Data_Cfg_TypeInstance.blockCount = NumberOfBlocks;
	SDH_Data_Cfg_TypeInstance.rxDataLen = 0;
	SDH_Data_Cfg_TypeInstance.rxData = NULL;
	SDH_Data_Cfg_TypeInstance.txDataLen = 0;
	SDH_Data_Cfg_TypeInstance.txData = (uint32_t *)writebuff;
	/*set parameters for SDH_DMA_Cfg_TypeInstance*/
	SDH_DMA_Cfg_TypeInstance.dmaMode = SDH_DMA_MODE_ADMA2;
	SDH_DMA_Cfg_TypeInstance.burstSize = SDH_BURST_SIZE_128_BYTES;
	SDH_DMA_Cfg_TypeInstance.fifoThreshold = SDH_FIFO_THRESHOLD_256_BYTES;
	SDH_DMA_Cfg_TypeInstance.admaEntries = (uint32_t *)adma2Entries;
	SDH_DMA_Cfg_TypeInstance.maxEntries = sizeof(adma2Entries)/sizeof(adma2Entries[0]);
	
	stat = SDH_TransferNonBlocking(&SDH_DMA_Cfg_TypeInstance, &SDH_Trans_Cfg_TypeInstance);
	
	if(stat != SDH_STAT_SUCCESS){
		if(stat == SDH_STAT_DMA_ADDR_NOT_ALIGN)
			return SD_ADMA_ALIGN_ERROR;
		else
			return SD_DATA_ERROR;
	}

	
	SDH_ITConfig(SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,ENABLE);
	
	/*wait for Xfer status. might pending here in multi-task OS*/
	while(SDH_WaitStatus == SD_WAITING){}
	
		
	SDH_ITConfig(SDH_INT_DATA_COMPLETED|SDH_INT_DATA_ERRORS|SDH_INT_DMA_ERROR|SDH_INT_AUTO_CMD12_ERROR,DISABLE);
		
	if(SDH_WaitStatus != SD_OK)
	{
		SDH_WaitStatus = SD_WAITING;
		return SD_DATA_ERROR;
	}
	
	SDH_WaitStatus = SD_WAITING;	
	errorstatus = WaitInProgramming();
	
	//SDH_MSG("Write-->OUT, write %d blocks to %d with buffer 0x%p. \r\n",NumberOfBlocks,WriteAddr,writebuff);
	return(errorstatus);		
}
