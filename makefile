SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
MOTH_CFLAGS=-std=gnu99 -Iinclude -Wall -Werror -Wextra
NAME=moth
LIB=${NAME}.so
OUT_DIR=lib
CLEAN=${OBJECTS} ${OUT_DIR}/${LIB}
OUT_OBJ=

HAS_CCACHE := $(shell command -v ccache 2> /dev/null)
ifdef HAS_CCACHE
	CC := ccache $(CC)
else
	CC := $(CC)
endif

${OUT_DIR}:
	mkdir $@

all: ${LIB} ${OUT_DIR}
	mv ${LIB} ${OUT_DIR}/

clean:
	rm ${CLEAN}

install: ${LIB}
	# TODO correct
	sudo cp ${LIB} /usr/local/lib/${NAME}
	mandb

src/%.o : src/%.c
	${CC} -fpic -c $< -o $@ ${MOTH_CFLAGS}

${OBJECTS}: ${SOURCES}

${LIB} : ${OBJECTS}
	${CC} -fpic -shared -o $@ ${OBJECTS} ${MOTH_CFLAGS}
