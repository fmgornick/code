CFLAGS = -Wall -g
CC = gcc
LIBS = -lpthread -D_REENTRANT

part1: part1.o log
	$(CC) $< -o $@ $(LIBS)

part1.o: part1.c
	$(CC) $(CFLAGS) -c $<

log:
	mkdir log

clean:
	-rm -rf part1.o part1 log
