#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

CPPFLAGS += -DBFLB_CRYPT_HARDWARE -DBFLB_PKA_HARDWARE -DBLSP_BOOT2_ROLLBACK

LINKER_SCRIPTS := blsp_boot2_flash.ld




COMPONENT_ADD_LDFLAGS += -L $(BL60X_SDK_PATH)/customer_app/bl602_boot2/bl602_boot2 \
                         $(addprefix -T ,$(LINKER_SCRIPTS))
##
COMPONENT_ADD_LINKER_DEPS := $(addprefix ,$(LINKER_SCRIPTS))
