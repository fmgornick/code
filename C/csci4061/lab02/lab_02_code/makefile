CC = gcc
CFLAGS = -g -Wall
LDFLAGS =  
PROGS = main foo_static strings malloc

all: ${PROGS}

main: main.o apple.o
main.o: main.c apple.h
apple.o: apple.c apple.h

foo: foo_static.o
foo.o: foo_static.c

strings: strings.o
strings.o: strings.c

malloc: malloc.o
malloc.o: malloc.c

clean:
	rm -f *.o ${PROGS}

