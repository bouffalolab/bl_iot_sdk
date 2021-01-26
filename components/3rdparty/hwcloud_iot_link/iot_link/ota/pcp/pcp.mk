################################################################################
# this is used for compile the pcp modules
################################################################################
PCP_MODULE_SRC  = ${wildcard $(iot_link_root)/ota/pcp/*.c} 
C_SOURCES += $(PCP_MODULE_SRC)	
		
PCP_MODULE_INC = -I $(iot_link_root)/ota/pcp
C_INCLUDES += $(PCP_MODULE_INC)

C_DEFS += -D CONFIG_PCP_ENABLE=1