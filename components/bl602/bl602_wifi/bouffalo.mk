COMPONENT_LIB_ONLY := 1
COMPONENT_ADD_INCLUDEDIRS += include plf/refip/src/driver/phy/bl602_phy_rf
LIBS ?= bl602_wifi
COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/lib $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/lib/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)
