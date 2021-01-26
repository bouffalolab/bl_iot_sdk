################################################################################
# this is used for compile the crc modules
################################################################################


CRC_MODULE_SRC  = ${wildcard $(iot_link_root)/crc/*.c} 
C_SOURCES += $(CRC_MODULE_SRC)	
		
CRC_MODULE_INC = -I $(iot_link_root)/crc
C_INCLUDES += $(CRC_MODULE_INC)



