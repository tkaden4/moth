SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
ETTY_CFLAGS=-std=gnu99 -Iinclude -lutil
NAME=ryte
LIB=${NAME}.so
OUT_DIR=lib
CLEAN=${OBJECTS} ${OUT_DIR}/${LIB}
OUT_OBJ=

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
	gcc -fpic -c $< -o $@ ${ETTY_CFLAGS}

${OBJECTS}: ${SOURCES}

${LIB} : ${OBJECTS}
	gcc -fpic -shared -o $@ ${OBJECTS}
