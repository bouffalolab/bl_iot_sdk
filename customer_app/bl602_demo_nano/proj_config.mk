#
#compiler flag config domain
#
#CONFIG_TOOLPREFIX :=
#CONFIG_OPTIMIZATION_LEVEL_RELEASE := 1
#CONFIG_M4_SOFTFP := 1

#
#board config domain
#
CONFIG_BOARD_FLASH_SIZE := 2

#firmware config domain
#

#set CONFIG_ENABLE_ACP to 1 to enable ACP, set to 0 or comment this line to disable
CONFIG_BL_IOT_FW_AP:=1
CONFIG_BL_IOT_FW_AMPDU:=0
CONFIG_BL_IOT_FW_AMSDU:=0
CONFIG_BL_IOT_FW_P2P:=0

# set easyflash env psm size, only support 4K、8K、16K options

CONFIG_FREERTOS_TICKLESS_MODE:=0

CONFIG_BT:=1

CONFIG_DTS_INAPP:=1

#LOG_ENABLED_COMPONENTS:=bl602_demo_nano bl602_wifi bl602_wifidrv cli
LOG_ENABLED_COMPONENTS:=bl602_demo_nano

