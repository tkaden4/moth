all:
	gcc -o test test.c \
	    -I../include -L../lib -l:moth.so

run:
	env LD_LIBRARY_PATH=../lib ./test


clean:
	rm test
