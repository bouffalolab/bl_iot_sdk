
COMPRESSION_ALGO_SRC = $(iot_link_root)/link_ota/compress/lzma/C/Lzma2Dec.c \
			           $(iot_link_root)/link_ota/compress/lzma/C/LzmaDec.c
C_SOURCES += $(COMPRESSION_ALGO_SRC)

COMPRESSION_ALGO_INC = -I $(iot_link_root)/link_ota/compress/lzma/C/
C_INCLUDES += $(COMPRESSION_ALGO_INC)
