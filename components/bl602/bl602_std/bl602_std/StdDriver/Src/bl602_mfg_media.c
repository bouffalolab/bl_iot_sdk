#include "bl602_mfg_media.h"

static uint8_t rf_para_on_flash=0;

int8_t mfg_media_init( SPI_Flash_Cfg_Type *flashCfg)
{
    if(0==mfg_flash_init(flashCfg)){
        rf_para_on_flash=1;
    }else{
        rf_para_on_flash=0;
    }
    return 0;
}

uint8_t mfg_media_is_xtal_capcode_slot_empty(uint8_t reload)
{
    if(rf_para_on_flash){
        return 1;
    }else{
        return mfg_efuse_is_xtal_capcode_slot_empty(reload);
    }
}

int8_t mfg_media_write_xtal_capcode_pre(uint8_t capcode,uint8_t program)
{
    if(rf_para_on_flash){
        return mfg_flash_write_xtal_capcode_pre(capcode,program);
    }else{
        return mfg_efuse_write_xtal_capcode_pre(capcode,program);
    }
}

void mfg_media_write_xtal_capcode(void)
{
    if(rf_para_on_flash){
       return mfg_flash_write_xtal_capcode();
    }else{
       return mfg_efuse_write_xtal_capcode();
    }
}

int8_t mfg_media_read_xtal_capcode(uint8_t *capcode,uint8_t reload)
{
    if(rf_para_on_flash){
       return mfg_flash_read_xtal_capcode(capcode,reload);
    }else{
       return mfg_efuse_read_xtal_capcode(capcode,reload);
    }
}

uint8_t mfg_media_is_poweroffset_slot_empty(uint8_t reload)
{
    if(rf_para_on_flash){
        return 1;
    }else{
        return mfg_efuse_is_poweroffset_slot_empty(reload);
    }
}

int8_t mfg_media_write_poweroffset_pre(int8_t pwrOffset[14],uint8_t program)
{
    if(rf_para_on_flash){
        return mfg_flash_write_poweroffset_pre(pwrOffset,program);
    }else{
        return mfg_efuse_write_poweroffset_pre(pwrOffset,program);
    }
}

void mfg_media_write_poweroffset(void)
{
    if(rf_para_on_flash){
        return mfg_flash_write_poweroffset();
    }else{
        return mfg_efuse_write_poweroffset();
    }
}

int8_t mfg_media_read_poweroffset(int8_t pwrOffset[14],uint8_t reload)
{
    if(rf_para_on_flash){
        return mfg_flash_read_poweroffset(pwrOffset,reload);
    }else{
        return mfg_efuse_read_poweroffset(pwrOffset,reload);
    }
}

uint8_t mfg_media_is_macaddr_slot_empty(uint8_t reload)
{
    if(rf_para_on_flash){
        return 1;
    }else{
        return mfg_efuse_is_macaddr_slot_empty(reload);
    }
}

int8_t mfg_media_write_macaddr_pre(uint8_t mac[6],uint8_t program)
{
    if(rf_para_on_flash){
        return mfg_flash_write_macaddr_pre(mac,program);
    }else{
        return mfg_efuse_write_macaddr_pre(mac,program);
    }
}

void mfg_media_write_macaddr(void)
{
    if(rf_para_on_flash){
        return mfg_flash_write_macaddr();
    }else{
        return mfg_efuse_write_macaddr();
    }
}

int8_t mfg_media_read_macaddr(uint8_t mac[6],uint8_t reload)
{
    if(rf_para_on_flash){
        return mfg_flash_read_macaddr(mac,reload);
    }else{
        return mfg_efuse_read_macaddr(mac,reload);
    }
}

