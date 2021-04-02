TOP_DIR = ..
include ${TOP_DIR}/scripts/config.mk

TARGET_DIR = ${TOP_DIR}/target
TARGET_LIB = ${TARGET_DIR}/lib
TARGET_BIN = ${TARGET_DIR}/bin

INCLUDE_DIRS = $(shell ls -l ../joylink/inc | grep ^d | awk '{print $$9}')
ORG_SOURCES = $(wildcard *.c)
#OUT_SRC = test.c
OUT_SRC = 

SOURCES=$(filter-out ${OUT_SRC}, ${ORG_SOURCES})
OBJS = $(patsubst %.c, %.o, $(SOURCES))

LIBNAME = lib$(strip ${shell pwd |xargs basename})

CFLAGS += -I../joylink/inc
CFLAGS += -I../pal/inc
CFLAGS += $(addprefix -I../joylink/inc/,${INCLUDE_DIRS})

LIBS += ../joylink/lib/libjoylink.a
LIBS += -lpal

ifeq (${ARCH}, x86)  
LIBS += -lpthread -lm
all:${OBJS} liba libso 
else
all:${OBJS} liba 
endif


jt:${OBJS}
	${CC} ${OBJS} -o $@ -L${TARGET_LIB} ${LIBS} ${LDFLAGS}
	$(STRIP) $@
	${MV} $@ ${TARGET_BIN}

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
