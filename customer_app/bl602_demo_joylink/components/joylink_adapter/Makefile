TOP_DIR = .

include ${TOP_DIR}/scripts/config.mk

DEPS := pal example

all:  clean_lib ${DEPS} jt

clean: clean_lib ${DEPS} 

distclean: ${DEPS}
	${RM} ${TARGET_LIB}/*

${DEPS}: 
	make -C $@ $(MAKECMDGOALS) 

jt:
	make jt -C example

clean_lib:
	rm -rf ${TARGET_LIB}
	mkdir -p ${TARGET_LIB}
	rm -rf ${TARGET_BIN}
	mkdir -p ${TARGET_BIN}

.PHONY:all clean distclean ${DEPS} jt
