EXTRA_CPPFLAGS  ?=
ifeq ("$(CONFIG_CHIP_NAME)", "BL602")
EXTRA_CPPFLAGS  += -D BL_SDK_VER=\"release_bl_iot_sdk_1.6.38-63-gae97ed42f\"
EXTRA_CPPFLAGS  += -D BL_SDK_PHY_VER=\"a0_final-74-g478a1d5\"
EXTRA_CPPFLAGS  += -D BL_SDK_RF_VER=\"0a5bc1d\"
EXTRA_CPPFLAGS  += -D BL_SDK_STDDRV_VER=\"a67b266\"
endif
ifeq ("$(CONFIG_CHIP_NAME)", "BL702")
EXTRA_CPPFLAGS  += -D BL_SDK_VER=\"release_bl_iot_sdk_1.6.38-63-gae97ed42f\"
EXTRA_CPPFLAGS  += -D BL_SDK_STDDRV_VER=\"dff9318\"
EXTRA_CPPFLAGS  += -D BL_SDK_STDCOM_VER=\"9fe1995\"
EXTRA_CPPFLAGS  += -D BL_SDK_RF_VER=\"b5662bc\"
endif
