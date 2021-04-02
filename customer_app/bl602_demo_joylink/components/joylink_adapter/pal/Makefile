TOP_DIR = ..

include ${TOP_DIR}/scripts/config.mk

TARGET_DIR = ${TOP_DIR}/target
TARGET_LIB = ${TARGET_DIR}/lib
TARGET_BIN = ${TARGET_DIR}/bin

INCLUDE_DIRS = $(shell ls -l ../joylink/inc | grep ^d | awk '{print $$9}')
ORG_SOURCES = $(wildcard src/*.c)
OUT_SRC = src/joylink_ota.c src/joylink_wifi.c

SOURCES=$(filter-out ${OUT_SRC}, ${ORG_SOURCES})
OBJS = $(patsubst %.c, %.o, $(SOURCES))

LIBNAME = lib$(strip ${shell pwd |xargs basename})

CFLAGS += -I../example
CFLAGS += -I./inc
CFLAGS += $(addprefix -I../joylink/inc/,${INCLUDE_DIRS})

ifeq (${ARCH}, x86)  
all:${OBJS} liba libso 
else
all:${OBJS} liba 
endif


.SUFFIXES: .c .o

liba:${OBJS}
	@echo ------------------
	@echo ${SOURCES}
	@echo ------------------
	@echo ${OUT_SRC}
	@echo ------------------
	${AR} -crs ${LIBNAME}.a ${OBJS}
	@echo ------------------
	${MV} ${LIBNAME}.a ${TARGET_LIB}

libso:${OBJS}
	${CC} ${OBJS} -shared -fPIC -o ${LIBNAME}.so
	${MV} ${LIBNAME}.so ${TARGET_LIB} 

clean:
	${RM} ${OBJS} *.i *.s $(wildcard src/*.d) $(wildcard src/*/*.d) $(wildcard src/*.su) $(wildcard src/*/*.su)

$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

distclean:clean
	${RM} ${TARGET_LIB}/*

.PHONY:all clean test jt
