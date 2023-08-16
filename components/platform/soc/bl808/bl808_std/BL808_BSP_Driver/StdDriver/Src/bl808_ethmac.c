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
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"

#include "bl808_ethmac.h"

#include "mii.h"
#include "mdio.h"


#define BIT(nr)			(1UL << (nr))
#define NUM_TX_BD       1

#define ETH_RXBUFNB     7
#define ETH_TXBUFNB     (NUM_TX_BD)

#define PHY_AUTONEGOTIATE_TIMEOUT 5000

#define MII_MARVELL_PHY_PAGE		22

/* 88E1011 PHY Status Register */
#define MIIM_88E1xxx_PHY_STATUS		0x11
#define MIIM_88E1xxx_PHYSTAT_SPEED	0xc000
#define MIIM_88E1xxx_PHYSTAT_GBIT	0x8000
#define MIIM_88E1xxx_PHYSTAT_100	0x4000
#define MIIM_88E1xxx_PHYSTAT_DUPLEX	0x2000
#define MIIM_88E1xxx_PHYSTAT_SPDDONE	0x0800
#define MIIM_88E1xxx_PHYSTAT_LINK	0x0400

#define MIIM_88E1xxx_PHY_SCR		0x10
#define MIIM_88E1xxx_PHY_MDI_X_AUTO	0x0060

/* 88E1111 PHY LED Control Register */
#define MIIM_88E1111_PHY_LED_CONTROL	24
#define MIIM_88E1111_PHY_LED_DIRECT	0x4100
#define MIIM_88E1111_PHY_LED_COMBINE	0x411C

/* 88E1111 Extended PHY Specific Control Register */
#define MIIM_88E1111_PHY_EXT_CR		0x14
#define MIIM_88E1111_RX_DELAY		0x80
#define MIIM_88E1111_TX_DELAY		0x2

/* 88E1111 Extended PHY Specific Status Register */
#define MIIM_88E1111_PHY_EXT_SR		0x1b
#define MIIM_88E1111_HWCFG_MODE_MASK		0xf
#define MIIM_88E1111_HWCFG_MODE_COPPER_RGMII	0xb
#define MIIM_88E1111_HWCFG_MODE_FIBER_RGMII	0x3
#define MIIM_88E1111_HWCFG_MODE_SGMII_NO_CLK	0x4
#define MIIM_88E1111_HWCFG_MODE_COPPER_RTBI	0x9
#define MIIM_88E1111_HWCFG_FIBER_COPPER_AUTO	0x8000
#define MIIM_88E1111_HWCFG_FIBER_COPPER_RES	0x2000

#define MIIM_88E1111_COPPER		0
#define MIIM_88E1111_FIBER		1

/* 88E1118 PHY defines */
#define MIIM_88E1118_PHY_PAGE		22
#define MIIM_88E1118_PHY_LED_PAGE	3

/* 88E1121 PHY LED Control Register */
#define MIIM_88E1121_PHY_LED_CTRL	16
#define MIIM_88E1121_PHY_LED_PAGE	3
#define MIIM_88E1121_PHY_LED_DEF	0x0030

/* 88E1121 PHY IRQ Enable/Status Register */
#define MIIM_88E1121_PHY_IRQ_EN		18
#define MIIM_88E1121_PHY_IRQ_STATUS	19

#define MIIM_88E1121_PHY_PAGE		22

/* 88E1145 Extended PHY Specific Control Register */
#define MIIM_88E1145_PHY_EXT_CR 20
#define MIIM_M88E1145_RGMII_RX_DELAY	0x0080
#define MIIM_M88E1145_RGMII_TX_DELAY	0x0002

#define MIIM_88E1145_PHY_LED_CONTROL	24
#define MIIM_88E1145_PHY_LED_DIRECT	0x4100

#define MIIM_88E1145_PHY_PAGE	29
#define MIIM_88E1145_PHY_CAL_OV 30

#define MIIM_88E1149_PHY_PAGE	29

/* 88E1310 PHY defines */
#define MIIM_88E1310_PHY_LED_CTRL	16
#define MIIM_88E1310_PHY_IRQ_EN		18
#define MIIM_88E1310_PHY_RGMII_CTRL	21
#define MIIM_88E1310_PHY_PAGE		22

/* 88E151x PHY defines */
/* Page 2 registers */
#define MIIM_88E151x_PHY_MSCR		21
#define MIIM_88E151x_RGMII_RX_DELAY	BIT(5)
#define MIIM_88E151x_RGMII_TX_DELAY	BIT(4)
#define MIIM_88E151x_RGMII_RXTX_DELAY	(BIT(5) | BIT(4))
/* Page 3 registers */
#define MIIM_88E151x_LED_FUNC_CTRL	16
#define MIIM_88E151x_LED_FLD_SZ		4
#define MIIM_88E151x_LED0_OFFS		(0 * MIIM_88E151x_LED_FLD_SZ)
#define MIIM_88E151x_LED1_OFFS		(1 * MIIM_88E151x_LED_FLD_SZ)
#define MIIM_88E151x_LED0_ACT		3
#define MIIM_88E151x_LED1_100_1000_LINK	6
#define MIIM_88E151x_LED_TIMER_CTRL	18
#define MIIM_88E151x_INT_EN_OFFS	7
/* Page 18 registers */
#define MIIM_88E151x_GENERAL_CTRL	20
#define MIIM_88E151x_MODE_SGMII		1
#define MIIM_88E151x_RESET_OFFS		15


/* Common PHY Registers */
#define PHY_BCR                                         ((uint16_t)0x00U)    /*!< Transceiver Basic Control Register   */
#define PHY_BSR                                         ((uint16_t)0x01U)    /*!< Transceiver Basic Status Register    */
#    define PHY_BSR_100BASETXFULL                       (1 << 14)
#    define PHY_BSR_100BASETXHALF                       (1 << 13)
#    define PHY_BSR_10BASETXFULL                        (1 << 12)
#    define PHY_BSR_10BASETXHALF                        (1 << 11)
#define PHY_RESET                                       ((uint16_t)0x8000U)  /*!< PHY Reset */
#define PHY_LOOPBACK                                    ((uint16_t)0x4000U)  /*!< Select loop-back mode */
#define PHY_FULLDUPLEX_100M                             ((uint16_t)0x2100U)  /*!< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M                             ((uint16_t)0x2000U)  /*!< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M                              ((uint16_t)0x0100U)  /*!< Set the full-duplex mode at 10 Mb/s  */
#define PHY_HALFDUPLEX_10M                              ((uint16_t)0x0000U)  /*!< Set the half-duplex mode at 10 Mb/s  */
#define PHY_AUTONEGOTIATION                             ((uint16_t)0x1000U)  /*!< Enable auto-negotiation function     */
#define PHY_RESTART_AUTONEGOTIATION                     ((uint16_t)0x0200U)  /*!< Restart auto-negotiation function    */
#define PHY_POWERDOWN                                   ((uint16_t)0x0800U)  /*!< Select the power down mode           */
#define PHY_ISOLATE                                     ((uint16_t)0x0400U)  /*!< Isolate PHY from MII                 */
#define PHY_AUTONEGO_COMPLETE                           ((uint16_t)0x0020U)  /*!< Auto-Negotiation process completed   */
#define PHY_LINKED_STATUS                               ((uint16_t)0x0004U)  /*!< Valid link established               */
#define PHY_JABBER_DETECTION                            ((uint16_t)0x0002U)  /*!< Jabber condition detected            */

#define PHY_PHYID1                                      ((uint16_t)0x02U)    /*!< PHY ID 1    */
#define PHY_PHYID2                                      ((uint16_t)0x03U)    /*!< PHY ID 2    */
#define PHY_ADVERTISE                                   ((uint16_t)0x04U)    /*!< Auto-negotiation advertisement       */
#    define PHY_ADVERTISE_100BASETXFULL                 (1 << 8)
#    define PHY_ADVERTISE_100BASETXHALF                 (1 << 7)
#    define PHY_ADVERTISE_10BASETXFULL                  (1 << 6)
#    define PHY_ADVERTISE_10BASETXHALF                  (1 << 5)
#    define PHY_ADVERTISE_8023                          (1 << 0)
#define PHY_LPA                                         ((uint16_t)0x05U)    /*!< Auto-negotiation link partner base page ability    */
#define PHY_EXPANSION                                   ((uint16_t)0x06U)    /*!< Auto-negotiation expansion           */
/* Section 4: Extended PHY Registers */
#define PHY_SR                                          ((uint16_t)0x1FU)    /*!< PHY special control/ status register Offset     */
#    define PHY_SR_SPEED_OFFSET                         (2)
#    define PHY_SR_SPEED_MASK                           (0x7 << PHY_SR_SPEED_OFFSET)
#    define PHY_SR_SPEED_10BASETXHALF                   (0x1 << PHY_SR_SPEED_OFFSET)
#    define PHY_SR_SPEED_10BASETXFULL                   (0x5 << PHY_SR_SPEED_OFFSET)
#    define PHY_SR_SPEED_100BASETXHALF                  (0x2 << PHY_SR_SPEED_OFFSET)
#    define PHY_SR_SPEED_100BASETXFULL                  (0x6 << PHY_SR_SPEED_OFFSET)
#    define PHY_SR_SPEED_MODE_COMPARE(status, mode)     (!!(mode == (status & PHY_SR_SPEED_MASK)))
#define PHY_SPEED_STATUS                                ((uint16_t)0x0004U)  /*!< PHY Speed mask                                  */
#define PHY_DUPLEX_STATUS                               ((uint16_t)0x0010U)  /*!< PHY Duplex mask                                 */
#define PHY_ISFR                                        ((uint16_t)0x1DU)    /*!< PHY Interrupt Source Flag register Offset       */
#define PHY_ISFR_INT4                                   ((uint16_t)0x0010U)  /*!< PHY Link down inturrupt                         */

#define PHY_MAX_RETRY                                   (0x3FFF)
#define ETH_MAX_PACKET_SIZE                             (1536 + 16)

/* TODO: formalize MMU mapping later */
#define EMAC_DMA_MAPPING_OFFSET   0//(0xCF000000 - 0x3F000000) /*FIXME :if MMU enable should add memory map*/

ETHMAC_Handle_Type ethHandle;
static ETHMAC_Handle_Type *thiz = NULL;

/* TODO: ethRxBuff and ethTxBuff MUST in VRAM */
/* TODO: malloc */
/* Ethernet Receive Buffers */
static volatile uint8_t ethRxBuff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE] __attribute__ ((aligned(16), section(".fgpa_ddr")));
/* Ethernet Transmit Buffers */
static volatile uint8_t ethTxBuff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE] __attribute__ ((aligned(16), section(".fgpa_ddr")));

static int phy_read(phy_device *phydev, uint8_t regnum)
{
    int val;
    ethmac_reg_t *ethmac_reg = (ethmac_reg_t*)ETHMAC_BASE;

    ethmac_reg->MIIADDRESS.BF.FIAD = phydev->addr;
    ethmac_reg->MIIADDRESS.BF.RGAD = regnum;

    /* kick off the read operation */
    ethmac_reg->MIICOMMAND.BF.RSTAT = 1;

    vTaskDelay(10); // delay 10 ms
    /* poll until MII is not busy */
    while (ethmac_reg->MIISTATUS.BF.MIIM_BUSY == 1);

    val = ethmac_reg->MIIRX_DATA.BF.PRSD;
        
    printf("phy_read[%d], val 0x%04x\r\n", regnum, val);

    return val;
}

static int phy_write(phy_device *phydev, uint8_t regnum, uint16_t val)
{
    ethmac_reg_t *ethmac_reg = (ethmac_reg_t*)ETHMAC_BASE;

    ethmac_reg->MIIADDRESS.BF.FIAD = phydev->addr;
    ethmac_reg->MIIADDRESS.BF.RGAD = regnum;

    ethmac_reg->MIITX_DATA.BF.CTRLDATA = val;

    /* kick off the write operation */
    ethmac_reg->MIICOMMAND.BF.WCTRLDATA = 1;

    vTaskDelay(10); // delay 10 ms
    /* poll until MII is not busy */
    while (ethmac_reg->MIISTATUS.BF.MIIM_BUSY == 1);
    
    printf("phy_write[%d], val 0x%04x\r\n", regnum, val);

    return 0;
}


int phy_reset(phy_device *phydev)
{
	int reg;
	int timeout = 500;

	if (phy_write(phydev, MII_BMCR, BMCR_RESET) < 0) {
		puts("PHY reset failed\r\n");
		return -1;
	}

	/*
	 * Poll the control register for the reset bit to go to 0 (it is
	 * auto-clearing).  This should happen within 0.5 seconds per the
	 * IEEE spec.
	 */
	reg = phy_read(phydev, MII_BMCR);
	while ((reg & BMCR_RESET) && timeout--) {
		reg = phy_read(phydev, MII_BMCR);

		if (reg < 0) {
			printf("PHY status read failed\r\n");
			return -1;
		}
		vTaskDelay(1);
	}

	if (reg & BMCR_RESET) {
		puts("PHY reset timed out\r\n");
		return -1;
	}

    puts("PHY reset succeed!\r\n");
	return 0;
}

/* Generic PHY support and helper functions */

/**
 * genphy_config_advert - sanitize and advertise auto-negotiation parameters
 * @phydev: target phy_device struct
 *
 * Description: Writes MII_ADVERTISE with the appropriate values,
 *   after sanitizing the values to make sure we only advertise
 *   what is supported.  Returns < 0 on error, 0 if the PHY's advertisement
 *   hasn't changed, and > 0 if it has changed.
 */
static int genphy_config_advert(phy_device *phydev)
{
	uint32_t advertise;
	int oldadv, adv, bmsr;
	int err, changed = 0;

	/* Only allow advertising what this PHY supports */
	phydev->advertising &= phydev->supported;
	advertise = phydev->advertising;

	/* Setup standard advertisement */
	adv = phy_read(phydev, MII_ADVERTISE);
	oldadv = adv;

	if (adv < 0)
		return adv;

	adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4 | ADVERTISE_PAUSE_CAP |
		 ADVERTISE_PAUSE_ASYM);
	if (advertise & ADVERTISED_10baseT_Half)
		adv |= ADVERTISE_10HALF;
	if (advertise & ADVERTISED_10baseT_Full)
		adv |= ADVERTISE_10FULL;
	if (advertise & ADVERTISED_100baseT_Half)
		adv |= ADVERTISE_100HALF;
	if (advertise & ADVERTISED_100baseT_Full)
		adv |= ADVERTISE_100FULL;
	if (advertise & ADVERTISED_Pause)
		adv |= ADVERTISE_PAUSE_CAP;
	if (advertise & ADVERTISED_Asym_Pause)
		adv |= ADVERTISE_PAUSE_ASYM;
	if (advertise & ADVERTISED_1000baseX_Half)
		adv |= ADVERTISE_1000XHALF;
	if (advertise & ADVERTISED_1000baseX_Full)
		adv |= ADVERTISE_1000XFULL;

	if (adv != oldadv) {
		err = phy_write(phydev, MII_ADVERTISE, adv);

		if (err < 0)
			return err;
		changed = 1;
	}

	bmsr = phy_read(phydev, MII_BMSR);
	if (bmsr < 0)
		return bmsr;

	/* Per 802.3-2008, Section 22.2.4.2.16 Extended status all
	 * 1000Mbits/sec capable PHYs shall have the BMSR_ESTATEN bit set to a
	 * logical 1.
	 */
	if (!(bmsr & BMSR_ESTATEN))
		return changed;

	/* Configure gigabit if it's supported */
	adv = phy_read(phydev, MII_CTRL1000);
	oldadv = adv;

	if (adv < 0)
		return adv;

	adv &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);

	if (phydev->supported & (SUPPORTED_1000baseT_Half |
				SUPPORTED_1000baseT_Full)) {
		if (advertise & SUPPORTED_1000baseT_Half)
			adv |= ADVERTISE_1000HALF;
		if (advertise & SUPPORTED_1000baseT_Full)
			adv |= ADVERTISE_1000FULL;
	}

	if (adv != oldadv)
		changed = 1;

	err = phy_write(phydev, MII_CTRL1000, adv);
	if (err < 0)
		return err;

	return changed;
}

/**
 * genphy_setup_forced - configures/forces speed/duplex from @phydev
 * @phydev: target phy_device struct
 *
 * Description: Configures MII_BMCR to force speed/duplex
 *   to the values in phydev. Assumes that the values are valid.
 */
static int genphy_setup_forced(phy_device *phydev)
{
	int err;
	int ctl = BMCR_ANRESTART;

	phydev->pause = 0;
	phydev->asym_pause = 0;

	if (phydev->speed == SPEED_1000)
		ctl |= BMCR_SPEED1000;
	else if (phydev->speed == SPEED_100)
		ctl |= BMCR_SPEED100;

	if (phydev->duplex == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;

	err = phy_write(phydev, MII_BMCR, ctl);

	return err;
}

/**
 * genphy_restart_aneg - Enable and Restart Autonegotiation
 * @phydev: target phy_device struct
 */
int genphy_restart_aneg(phy_device *phydev)
{
	int ctl;

	ctl = phy_read(phydev, MII_BMCR);

	if (ctl < 0)
		return ctl;

	ctl |= (BMCR_ANENABLE | BMCR_ANRESTART);

	/* Don't isolate the PHY if we're negotiating */
	ctl &= ~(BMCR_ISOLATE);

	ctl = phy_write(phydev, MII_BMCR, ctl);

	return ctl;
}

/**
 * genphy_config_aneg - restart auto-negotiation or write BMCR
 * @phydev: target phy_device struct
 *
 * Description: If auto-negotiation is enabled, we configure the
 *   advertising, and then restart auto-negotiation.  If it is not
 *   enabled, then we write the BMCR.
 */
int genphy_config_aneg(phy_device *phydev)
{
	int result;

	if (phydev->autoneg != AUTONEG_ENABLE)
		return genphy_setup_forced(phydev);

	result = genphy_config_advert(phydev);

	if (result < 0) /* error */
		return result;

	if (result == 0) {
		/*
		 * Advertisment hasn't changed, but maybe aneg was never on to
		 * begin with?  Or maybe phy was isolated?
		 */
		int ctl = phy_read(phydev, MII_BMCR);

		if (ctl < 0)
			return ctl;

		if (!(ctl & BMCR_ANENABLE) || (ctl & BMCR_ISOLATE))
			result = 1; /* do restart aneg */
	}

	/*
	 * Only restart aneg if we are advertising something different
	 * than we were before.
	 */
	if (result > 0)
		result = genphy_restart_aneg(phydev);

	return result;
}

/**
 * genphy_update_link - update link status in @phydev
 * @phydev: target phy_device struct
 *
 * Description: Update the value in phydev->link to reflect the
 *   current link value.  In order to do this, we need to read
 *   the status register twice, keeping the second value.
 */
int genphy_update_link(phy_device *phydev)
{
	unsigned int mii_reg;

	/*
	 * Wait if the link is up, and autonegotiation is in progress
	 * (ie - we're capable and it's not done)
	 */
	mii_reg = phy_read(phydev, MII_BMSR);

	/*
	 * If we already saw the link up, and it hasn't gone down, then
	 * we don't need to wait for autoneg again
	 */
	if (phydev->link && mii_reg & BMSR_LSTATUS)
		return 0;

	if ((phydev->autoneg == AUTONEG_ENABLE) &&
	    !(mii_reg & BMSR_ANEGCOMPLETE)) {
		int i = 0;

		printf("Waiting for PHY auto negotiation to complete\r\n");
		while (!(mii_reg & BMSR_ANEGCOMPLETE)) {
			/*
			 * Timeout reached ?
			 */
			if (i > PHY_ANEG_TIMEOUT) {
				printf(" TIMEOUT !\r\n");
				phydev->link = 0;
				return -1;
			}

			if ((i++ % 500) == 0)
				puts(".");

			vTaskDelay(1);	/* 1 ms */
			mii_reg = phy_read(phydev, MII_BMSR);
		}
		printf(" done\r\n");
		phydev->link = 1;
	} else {
		/* Read the link a second time to clear the latched state */
		mii_reg = phy_read(phydev, MII_BMSR);

		if (mii_reg & BMSR_LSTATUS)
			phydev->link = 1;
		else
			phydev->link = 0;
	}

	return 0;
}


/* Parse the 88E1011's status register for speed and duplex
 * information
 */
static int m88e1xxx_parse_status(phy_device *phydev)
{
	unsigned int speed;
	unsigned int mii_reg;

	mii_reg = phy_read(phydev, MIIM_88E1xxx_PHY_STATUS);

	if ((mii_reg & MIIM_88E1xxx_PHYSTAT_LINK) &&
	    !(mii_reg & MIIM_88E1xxx_PHYSTAT_SPDDONE)) {
		int i = 0;

		printf("Waiting for PHY realtime link");
		while (!(mii_reg & MIIM_88E1xxx_PHYSTAT_SPDDONE)) {
			/* Timeout reached ? */
			if (i > PHY_AUTONEGOTIATE_TIMEOUT) {
				printf(" TIMEOUT !\r\n");
				phydev->link = 0;
				return -1;
			}

			if ((i++ % 1000) == 0)
				puts(".");
			vTaskDelay(1);
			mii_reg = phy_read(phydev, MIIM_88E1xxx_PHY_STATUS);
		}
		printf(" done\r\n");
		vTaskDelay(500);	/* another 500 ms (results in faster booting) */
	} else {
		if (mii_reg & MIIM_88E1xxx_PHYSTAT_LINK)
			phydev->link = 1;
		else
			phydev->link = 0;
	}

    printf("PHY link is %d\r\n", phydev->link);

	if (mii_reg & MIIM_88E1xxx_PHYSTAT_DUPLEX)
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

    printf("PHY duplex is %d\r\n", phydev->duplex);

	speed = mii_reg & MIIM_88E1xxx_PHYSTAT_SPEED;

	switch (speed) {
	case MIIM_88E1xxx_PHYSTAT_GBIT:
		phydev->speed = SPEED_1000;
        printf("PHY speed 1000\r\n");
		break;
	case MIIM_88E1xxx_PHYSTAT_100:
		phydev->speed = SPEED_100;
        printf("PHY speed 100\r\n");
		break;
	default:
		phydev->speed = SPEED_10;
        printf("PHY speed 10\r\n");
		break;
	}

	return 0;
}


int M88e1111s_startup(phy_device *phydev)
{
	int ret;

	ret = genphy_update_link(phydev);
	if (ret)
		return ret;

	return m88e1xxx_parse_status(phydev);
}

/* Marvell 88E1111S */
int M88e1111s_config(phy_device *phydev)
{
	/* soft reset */
	phy_reset(phydev);

	genphy_config_aneg(phydev);
	//genphy_restart_aneg(phydev);

    phy_write(phydev, 18, 0xffff);

	return 0;
}

static int ETHMAC_Phy_AutoNegotiate(phy_device *phydev)
{
	uint16_t id1, id2;
    volatile uint16_t regval = 0;
    uint16_t advertise = 0;
    uint16_t lpa = 0;
    uint32_t timeout = PHY_MAX_RETRY;

    id1 = phy_read(phydev, PHY_PHYID1);
    id2 = phy_read(phydev, PHY_PHYID2);
	  printf("PHY %x:%x\r\n", id1, id2);

    regval = phy_read(phydev, PHY_BCR);

    regval &= ~PHY_AUTONEGOTIATION;
    regval &= ~(PHY_LOOPBACK | PHY_POWERDOWN);
    regval |= PHY_ISOLATE;
    if(phy_write(phydev, PHY_BCR, regval) != 0){
        return -1;
    }

    /* set advertisement mode */
    advertise = PHY_ADVERTISE_100BASETXFULL | PHY_ADVERTISE_100BASETXHALF |
             PHY_ADVERTISE_10BASETXFULL | PHY_ADVERTISE_10BASETXHALF |
             PHY_ADVERTISE_8023;
    if(phy_write(phydev, PHY_ADVERTISE, advertise) != 0){
        return -1;
    }

    vTaskDelay(16);
    regval = phy_read(phydev, PHY_BCR);

    vTaskDelay(16);
    regval |= (PHY_FULLDUPLEX_100M | PHY_AUTONEGOTIATION);
    if(phy_write(phydev, PHY_BCR, regval) != 0){
        return -1;
    }

    regval |= PHY_RESTART_AUTONEGOTIATION;
    regval &= ~PHY_ISOLATE;
    if(phy_write(phydev, PHY_BCR, regval) != 0){
        return -1;
    }

    vTaskDelay(16);
    while(1) {
        regval = phy_read(phydev, PHY_BSR);

        if (regval & PHY_AUTONEGO_COMPLETE) {
            /* complete */
            break;
        }

        if (!(--timeout)) {
            return -2;
        }
    }

    vTaskDelay(16);
    lpa = phy_read(phydev, PHY_LPA);

    if (((advertise & lpa) & PHY_ADVERTISE_100BASETXFULL) != 0)
    {
        /* 100BaseTX and Full Duplex */
        phydev->duplex = DUPLEX_FULL;
        phydev->speed = SPEED_100;
    }
    else if (((advertise & lpa) & PHY_ADVERTISE_10BASETXFULL) != 0)
    {
        /* 10BaseT and Full Duplex */
        phydev->duplex = DUPLEX_FULL;
        phydev->speed = SPEED_10;
    }
    else if (((advertise & lpa) & PHY_ADVERTISE_100BASETXHALF) != 0)
    {
        /* 100BaseTX and half Duplex */
        phydev->duplex = DUPLEX_HALF;
        phydev->speed = SPEED_100;
    }
    else if (((advertise & lpa) & PHY_ADVERTISE_10BASETXHALF) != 0)
    {
        /* 10BaseT and half Duplex */
        phydev->duplex = DUPLEX_HALF;
        phydev->speed = SPEED_10;
    }

    return 0;
}

static int ETHMAC_Phy_Linkup(phy_device *phydev)
{
    uint16_t phy_bsr = 0;
    uint16_t phy_sr = 0;

    vTaskDelay(16);
    phy_bsr = phy_read(phydev, PHY_BSR);

    vTaskDelay(16);
    if (!(PHY_LINKED_STATUS & phy_bsr)) {
        return -1;
    }

    vTaskDelay(16);
    phy_sr = phy_read(phydev, PHY_SR);

    if ((phy_bsr & PHY_BSR_100BASETXFULL) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_100BASETXFULL)) {
        /* 100BaseTX and Full Duplex */
        phydev->duplex = DUPLEX_FULL;
        phydev->speed = SPEED_100;
    } else if ((phy_bsr & PHY_BSR_10BASETXFULL) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_10BASETXFULL)) {
        /* 10BaseT and Full Duplex */
        phydev->duplex = DUPLEX_FULL;
        phydev->speed = SPEED_10;
    } else if ((phy_bsr & PHY_BSR_100BASETXHALF) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_100BASETXHALF)) {
        /* 100BaseTX and half Duplex */
        phydev->duplex = DUPLEX_HALF;
        phydev->speed = SPEED_100;
    } else if ((phy_bsr & PHY_BSR_10BASETXHALF) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_10BASETXHALF)) {
        /* 10BaseT and half Duplex */
        phydev->duplex = DUPLEX_HALF;
        phydev->speed = SPEED_10;
    }

#if 0
    if (SUCCESS != EMAC_Phy_Read(PHY_BCR, &phy_bsr)) {
        return ERROR;
    }

    /* enter test mode: near-end loopback */
    BL702_Delay_MS(16);
    phy_bsr |= PHY_LOOPBACK;
    if(EMAC_Phy_Write(PHY_BCR, phy_bsr) != SUCCESS){
        return ERROR;
    }

    if (SUCCESS != EMAC_Phy_Read(PHY_BCR, &phy_bsr)) {
        return ERROR;
    }
#endif

#if 0
    if (SUCCESS != EMAC_Phy_Read(17, &phy_bsr)) {
        return ERROR;
    }

    /* enter test mode: far loopback */
    BL702_Delay_MS(16);
    phy_bsr |= (1 << 9); /* mode control/status register, FARLOOPBACK bit */
    if(EMAC_Phy_Write(17, phy_bsr) != SUCCESS){
        return ERROR;
    }
#endif

    return 0;
}

int ETHMAC_PhyInit(phy_device *phydev)
{
    if (AUTONEG_ENABLE == phydev->autoneg) {
        ETHMAC_Phy_AutoNegotiate(phydev);
    } else {
        printf("%s:%d:not implemented\n\r", __func__, __LINE__);
        return -1;
    }

    /*
     *TODO: set ETHMAC control reg accroding to negotiation results,
     * such as the duplex.
     */

    ETHMAC_Phy_Linkup(phydev);

    return 0;
}

int ETHMAC_Cfg(phy_device *phydev)
{
    ethmac_reg_t *ethmac_reg = (ethmac_reg_t*)ETHMAC_BASE;

    ethmac_reg->TX_BD_NUM.BF.TXBDNUM = NUM_TX_BD;

    ethmac_reg->INT_MASK.WORD   = 0xFFFFFFFF;   /* mask  all interrupts */
    ethmac_reg->INT_SOURCE.WORD = 0xFFFFFFFF;   /* clear all interrupts */
    
    ethmac_reg->MODE.BF.RMIIEN = (true == phydev->is_rmii) ? 1 : 0;
    ethmac_reg->MODE.BF.RECSMALL = 0;
    ethmac_reg->MODE.BF.PAD = 1;
    ethmac_reg->MODE.BF.HUGEN = 1;
    ethmac_reg->MODE.BF.CRCEN = 1;
    ethmac_reg->MODE.BF.FULLD = (DUPLEX_FULL == phydev->duplex) ? 1 : 0;
    ethmac_reg->MODE.BF.IFG = 0;
    ethmac_reg->MODE.BF.PRO = 0;
    ethmac_reg->MODE.BF.BRO = 1;
    ethmac_reg->MODE.BF.NOPRE = 0;
    ethmac_reg->MODE.BF.TXEN = 0;
    ethmac_reg->MODE.BF.RXEN = 0;

    ethmac_reg->MAC_ADDR0.BF.MAC_B5 = phydev->mac_addr[5];
    ethmac_reg->MAC_ADDR0.BF.MAC_B4 = phydev->mac_addr[4];
    ethmac_reg->MAC_ADDR0.BF.MAC_B3 = phydev->mac_addr[3];
    ethmac_reg->MAC_ADDR0.BF.MAC_B2 = phydev->mac_addr[2];
    ethmac_reg->MAC_ADDR1.BF.MAC_B1 = phydev->mac_addr[1];
    ethmac_reg->MAC_ADDR1.BF.MAC_B0 = phydev->mac_addr[0];

//    ethmac_reg->MAC_ADDR0.WORD = 0x33332211;
//    ethmac_reg->MAC_ADDR1.WORD = 0x1122;

    //bflb_IRQ_Enable(ETHMAC_IRQn);
    //bflb_IRQ_Cfg(ETHMAC_IRQn, 7, ETHMAC_IRQHandler);
    Interrupt_Handler_Register(ETHMAC_IRQn, ETHMAC_IRQHandler);
    System_NVIC_SetPriority(ETHMAC_IRQn,7,1);
    CPU_Interrupt_Enable(ETHMAC_IRQn);

    return 0;
}

int ETHMAC_Cfg_BD(void)
{
    int err = 0;

    thiz = &ethHandle;

    /* init the BDs in ethmac with buffer address */
    /*
     * TODO: hard code for debugging on FPGA ONLY!!!
     * MUST check why !!!
     */
#if 1
    err = ETHMAC_DMADescListInit(thiz, (uint8_t *)ethTxBuff, ETH_TXBUFNB, (uint8_t *)ethRxBuff, ETH_RXBUFNB);
#else
    err = ETHMAC_DMADescListInit(thiz, (uint8_t *)0xb0000000, ETH_TXBUFNB, (uint8_t *)0xb0100000, ETH_RXBUFNB);
#endif

    return err;
}

int ETHMAC_Transmit_Enable(void)
{
    ethmac_reg_t *ethmac_reg = (ethmac_reg_t*)ETHMAC_BASE;

    ethmac_reg->MODE.BF.TXEN = 1;

    return 0;
}

int ETHMAC_Receive_Enable(void)
{
    ethmac_reg_t *ethmac_reg = (ethmac_reg_t*)ETHMAC_BASE;

    ethmac_reg->MODE.BF.RXEN = 1;

    return 0;
}

void ETHMAC_IntMask(ETHMAC_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    //CHECK_PARAM(IS_ETHMAC_INT_TYPE(intType));
    //CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    switch(intType)
    {
        case ETHMAC_INT_TX:
            tmpVal = BL_RD_REG(ETHMAC_BASE, ETHMAC_INT_MASK);
            if(intMask == MASK){
                /* Disable this interrupt */
                BL_WR_REG(ETHMAC_BASE, ETHMAC_INT_MASK, BL_SET_REG_BIT(tmpVal, ETHMAC_TXB_M));
            }else{
                /* Enable this interrupt */
                BL_WR_REG(ETHMAC_BASE, ETHMAC_INT_MASK, BL_CLR_REG_BIT(tmpVal, ETHMAC_TXB_M));
            }
            break;

        case ETHMAC_INT_RX:
            tmpVal = BL_RD_REG(ETHMAC_BASE, ETHMAC_INT_MASK);
            if(intMask == MASK){
                /* Disable this interrupt */
                BL_WR_REG(ETHMAC_BASE, ETHMAC_INT_MASK, BL_SET_REG_BIT(tmpVal, ETHMAC_RXB_M));
            }else{
                /* Enable this interrupt */
                BL_WR_REG(ETHMAC_BASE, ETHMAC_INT_MASK, BL_CLR_REG_BIT(tmpVal, ETHMAC_RXB_M));
            }
            break;

        case ETHMAC_INT_ALL:
            tmpVal = BL_RD_REG(ETHMAC_BASE, ETHMAC_INT_MASK);
            if(intMask == MASK){
                /* mask all interrupts */
                tmpVal = BL_SET_REG_BIT(tmpVal, ETHMAC_TXB_M);
                tmpVal = BL_SET_REG_BIT(tmpVal, ETHMAC_RXB_M);
                tmpVal = BL_SET_REG_BIT(tmpVal, ETHMAC_TXE_M);
                tmpVal = BL_SET_REG_BIT(tmpVal, ETHMAC_RXE_M);
                tmpVal = BL_SET_REG_BIT(tmpVal, ETHMAC_BUSY_M);
                tmpVal = BL_SET_REG_BIT(tmpVal, ETHMAC_TXC_M);
                tmpVal = BL_SET_REG_BIT(tmpVal, ETHMAC_RXC_M);
                BL_WR_REG(ETHMAC_BASE, ETHMAC_INT_MASK, tmpVal);
            }else{
                /* unmask all interrupts */
                tmpVal = BL_CLR_REG_BIT(tmpVal, ETHMAC_TXB_M);
                tmpVal = BL_CLR_REG_BIT(tmpVal, ETHMAC_RXB_M);
                tmpVal = BL_CLR_REG_BIT(tmpVal, ETHMAC_TXE_M);
                tmpVal = BL_CLR_REG_BIT(tmpVal, ETHMAC_RXE_M);
                tmpVal = BL_CLR_REG_BIT(tmpVal, ETHMAC_BUSY_M);
                tmpVal = BL_CLR_REG_BIT(tmpVal, ETHMAC_TXC_M);
                tmpVal = BL_CLR_REG_BIT(tmpVal, ETHMAC_RXC_M);
                BL_WR_REG(ETHMAC_BASE, ETHMAC_INT_MASK, tmpVal);
            }
            break;

        default:
            break;
    }
}

/****************************************************************************//**
 * @brief  Initialize EMAC TX RX MDA buffer
 *
 * @param  handle: EMAC handle pointer
 * @param  txBuff: TX buffer
 * @param  txBuffCount: TX buffer count
 * @param  rxBuff: RX buffer
 * @param  rxBuffCount: RX buffer count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
int ETHMAC_DMADescListInit(ETHMAC_Handle_Type *handle,uint8_t *txBuff, uint32_t txBuffCount,uint8_t *rxBuff, uint32_t rxBuffCount)
{
    uint32_t i = 0;
    ethmac_reg_t *ethmac_reg = (ethmac_reg_t*)ETHMAC_BASE;

    /* Set the Ethernet handler env */
    handle->bd = (ETHMAC_BD_Desc_Type *)(ETHMAC_BASE + BD_DESC_OFFSET);
    handle->txIndexEMAC = 0;
    handle->txIndexCPU  = 0;
    handle->txBuffLimit = txBuffCount - 1;
    /* The receive descriptors' address starts right after the last transmit BD. */
    handle->rxIndexEMAC = txBuffCount;
    handle->rxIndexCPU  = txBuffCount;
    handle->rxBuffLimit = txBuffCount + rxBuffCount - 1;

    /* Fill each DMARxDesc descriptor with the right values */
    for(i=0; i < txBuffCount; i++){
        /* Get the pointer on the ith member of the Tx Desc list */
        handle->bd[i].Buffer= (NULL == txBuff) ? NULL : (uint32_t)(txBuff+(ETH_MAX_PACKET_SIZE*i));
        handle->bd[i].C_S_L = 0;
    }
    /* For the last TX DMA Descriptor, it should be wrap back */
    handle->bd[handle->txBuffLimit].C_S_L |= ETHMAC_BD_FIELD_MSK(TX_WR);

    for(i = txBuffCount; i < (txBuffCount + rxBuffCount); i++){
        /* Get the pointer on the ith member of the Rx Desc list */
        handle->bd[i].Buffer= ( NULL == rxBuff) ? NULL : (uint32_t)(rxBuff+(ETH_MAX_PACKET_SIZE*(i - txBuffCount)));
        handle->bd[i].C_S_L = (ETH_MAX_PACKET_SIZE << 16)  |
                               ETHMAC_BD_FIELD_MSK(RX_IRQ) |
                               ETHMAC_BD_FIELD_MSK(RX_E);
    }
    /* For the last RX DMA Descriptor, it should be wrap back */
    handle->bd[handle->rxBuffLimit].C_S_L |= ETHMAC_BD_FIELD_MSK(RX_WR);

    /* For the TX DMA Descriptor, it will wrap to 0 according to EMAC_TX_BD_NUM*/
    ethmac_reg->TX_BD_NUM.BF.TXBDNUM = txBuffCount;

    return 0;
}

int ETHMAC_BD_TX_enqueue(uint32_t flags, uint32_t len, const uint8_t *data_in, bool no_copy)
{
    int err = 0;
    ETHMAC_BD_Desc_Type *DMADesc;

    DMADesc = &thiz->bd[thiz->txIndexCPU];

    if ((uint32_t)(-1) == flags) {
        flags = ETHMAC_TX_COMMON_FLAGS;
    }

    if(DMADesc->C_S_L & ETHMAC_BD_FIELD_MSK(TX_RD)){
        /* no free BD, lost sync with DMA TX? */
        err = -16; /* -EBUSY */
    }else{
        if (true == no_copy) {
            DMADesc->Buffer = (uint32_t)data_in;
        } else {
            memcpy((void *)(DMADesc->Buffer + EMAC_DMA_MAPPING_OFFSET), data_in, len);
            //memcpy((void *)(DMADesc->Buffer), data_in, len);
        }
#if CPU_CA5
        //asm volatile ("dsb"::);
#endif
        __DSB();
        /* move to next TX BD */
        if ((++thiz->txIndexCPU) > thiz->txBuffLimit) {
            /* wrap back */
            thiz->txIndexCPU = 0;
            /* the last BD */
            flags |= ETHMAC_BD_FIELD_MSK(TX_WR);
        }

        __DSB();
        //asm volatile ("DSB");
        DMADesc->C_S_L = flags | (len << BD_TX_LEN_POS);
    }

    return err;
}

/* this func will be called in ISR */
int ETHMAC_BD_TX_dequeue(uint32_t index)
{
    int err = 0;
    ETHMAC_BD_Desc_Type *DMADesc;

    thiz->txIndexEMAC = index;
    DMADesc = &thiz->bd[thiz->txIndexEMAC];
    /* release this tx BD to SW (HW will do this) */
    //DMADesc->C_S_L &= ETHMAC_BD_FIELD_UMSK(TX_RD);

    return err;
}

void ETHMAC_BD_TX_onErr(uint32_t index)
{
    /* handle error */
    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(TX_UR)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(TX_RTRY)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(TX_RL)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(TX_LC)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(TX_DF)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(TX_CS)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    thiz->bd[index].C_S_L &= ~0xff;
}

int ETHMAC_BD_RX_enqueue(uint32_t index)
{
    int err = 0;

    thiz->rxIndexEMAC = index;

    return err;
}

int ETHMAC_BD_RX_dequeue(uint32_t flags, uint32_t *len, uint8_t *data_out)
{
    int err = 0;
    ETHMAC_BD_Desc_Type *DMADesc;

    DMADesc = &thiz->bd[thiz->rxIndexCPU];

    if(DMADesc->C_S_L & ETHMAC_BD_FIELD_MSK(RX_E)){
        /* current RX BD is empty */
        err = -16;
        *len = 0;

        /* move to next RX BD */
        if ((++thiz->rxIndexCPU) > thiz->rxBuffLimit) {
            /* wrap back */
            thiz->rxIndexCPU = thiz->txBuffLimit + 1;
        }
    }else{
        *len = (thiz->bd[thiz->rxIndexCPU].C_S_L & ETHMAC_BD_FIELD_MSK(RX_LEN)) >> BD_RX_LEN_POS;
        if (data_out) {
#if __riscv_xlen == 64
            csi_dcache_invalid_range((uint64_t *)(DMADesc->Buffer + EMAC_DMA_MAPPING_OFFSET), (int64_t)*len);
#endif
#if __riscv_xlen == 32
            csi_dcache_invalid_range((uint32_t *)(DMADesc->Buffer + EMAC_DMA_MAPPING_OFFSET), (int32_t)*len);
#endif
            memcpy(data_out, (const void *)(DMADesc->Buffer + EMAC_DMA_MAPPING_OFFSET), *len);
            //memcpy(data_out, (const void *)(DMADesc->Buffer), *len);
        }

        /* move to next RX BD */
        if ((++thiz->rxIndexCPU) > thiz->rxBuffLimit) {
            /* the last BD */
            DMADesc->C_S_L |= ETHMAC_BD_FIELD_MSK(RX_WR);
            /* wrap back */
            thiz->rxIndexCPU = thiz->txBuffLimit + 1;
        }

        /* RX BD can be used for another receive now */
        DMADesc->C_S_L |= ETHMAC_BD_FIELD_MSK(RX_E);
    }

    return err;
}

uint32_t ETHMAC_BD_Get_CurActive(ETHMAC_BD_TYPE_e bdt)
{
    uint32_t bd = 0;
    ethmac_reg_t *ethmac_reg = (ethmac_reg_t*)ETHMAC_BASE;

    bd = ethmac_reg->TX_BD_NUM.WORD;

    if (bdt == EMAC_BD_TYPE_TX) {
        bd &= ETHMAC_TXBDPTR_MSK;
        bd >>= ETHMAC_TXBDPTR_POS;
    }

    if (bdt == EMAC_BD_TYPE_RX) {
        bd &= ETHMAC_RXBDPTR_MSK;
        bd >>= ETHMAC_RXBDPTR_POS;
    }

    return bd;
}

void ETHMAC_BD_RX_onErr(uint32_t index)
{
    /* handle error */
    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(RX_OR)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(RX_RE)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(RX_DN)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(RX_TL)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(RX_CRC)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    if (thiz->bd[index].C_S_L & ETHMAC_BD_FIELD_MSK(RX_LC)) {
        printf("%s:%d\r\n", __func__, __LINE__);
    }

    thiz->bd[index].C_S_L &= ~0xff;
    /* RX BD is ready for RX */
    thiz->bd[index].C_S_L |= ETHMAC_BD_FIELD_MSK(RX_E);
}

static int ETHMAC_Handle_RX_Buffer(void)
{
    static int buf_cnt = 0;
    int rx_buf_len;
    bd_reg_t *bd_reg;
    uint32_t dest_addr;

    /* RX BD */
    bd_reg = (bd_reg_t*)(ETHMAC_BASE + BD_DESC_OFFSET) + NUM_TX_BD + buf_cnt;
    rx_buf_len = bd_reg->BD_Config.BD_RX.LEN - 4;   /* exclude 4 byte FCS */

    printf("receive buffer[%d], len %d\r\n", buf_cnt, rx_buf_len);

    bd_reg->BD_Config.BD_RX.E = 1;  /* re-enable this RX BD */


    /* hack dest addr to linux host */
    dest_addr = 0x70030000 + buf_cnt * 0x1000;

    memcpy((void*)dest_addr, (void*)0x70034000, 12);
#if 0
    *dest_addr = 0x80002766;
    dest_addr++;
    *dest_addr = (*dest_addr && 0x0000FFFF) | (0x3653 << 16);
#endif

    /* TX BD */
    bd_reg = (bd_reg_t*)(ETHMAC_BASE + BD_DESC_OFFSET) + buf_cnt;
    bd_reg->BD_Config.BD_TX.LEN = rx_buf_len;
    bd_reg->BD_Config.BD_TX.RD = 1;

    

    buf_cnt = (buf_cnt + 1) & 0x3;
    
    return 0;
}

static void ETHMAC_TX_Done_Callback(void)
{
    uint32_t index = 0;

    index = ETHMAC_BD_Get_CurActive(EMAC_BD_TYPE_TX);

#if (EMAC_TEST_ROLE & TEST_ROLE_TX)
    tx_pkg_cnt ++;
#endif

    ETHMAC_BD_TX_dequeue(index);
}

static void ETHMAC_TX_Error_Callback(void)
{
    uint32_t index = 0;

#if (EMAC_TEST_ROLE & TEST_ROLE_TX)
    tx_err_cnt ++;
#endif

    index = ETHMAC_BD_Get_CurActive(EMAC_BD_TYPE_TX);

    ETHMAC_BD_TX_onErr(index);
}

static void ETHMAC_RX_Done_Callback(void)
{
    uint32_t index = 0;

    index = ETHMAC_BD_Get_CurActive(EMAC_BD_TYPE_RX);

    ETHMAC_BD_RX_enqueue(index);
}

static void ETHMAC_RX_Error_Callback(void)
{
    uint32_t index;

    index = ETHMAC_BD_Get_CurActive(EMAC_BD_TYPE_RX);

#if (EMAC_TEST_ROLE & TEST_ROLE_RX)
    rx_err_cnt ++;
#endif

    ETHMAC_BD_RX_onErr(index);
}

static void ETHMAC_RX_Busy_Callback(void)
{
   printf("%s:%d\r\n", __func__, __LINE__);
}

void ETHMAC_IRQHandler(void)
{
    uint32_t ethmac_int;

    ethmac_int = BL_RD_REG(ETHMAC_BASE, ETHMAC_INT_SOURCE);

    /* clear interrupts */
    BL_WR_REG(ETHMAC_BASE, ETHMAC_INT_SOURCE, ethmac_int);

	if (BL_IS_REG_BIT_SET(ethmac_int, ETHMAC_TXB)) {
		ETHMAC_TX_Done_Callback();
    }
	if (BL_IS_REG_BIT_SET(ethmac_int, ETHMAC_TXE)) {
		ETHMAC_TX_Error_Callback();
    }
	if (BL_IS_REG_BIT_SET(ethmac_int, ETHMAC_RXB)) {
		ETHMAC_RX_Done_Callback();
    }
	if (BL_IS_REG_BIT_SET(ethmac_int, ETHMAC_RXE)) {
		ETHMAC_RX_Error_Callback();
    }
	if (BL_IS_REG_BIT_SET(ethmac_int, ETHMAC_BUSY)) {
		ETHMAC_RX_Busy_Callback();
    }
	if (BL_IS_REG_BIT_SET(ethmac_int, ETHMAC_TXC)) {
        /* TODO */
    }
	if (BL_IS_REG_BIT_SET(ethmac_int, ETHMAC_RXC)) {
        /* TODO */
    }
}

