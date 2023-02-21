CFLAGS = -Wall -g
CC		 = gcc
LIBS   = -lpthread -D_REENTRANT

part1: part1.o
	$(CC) $(LIBS) $^ -o $@

part1.o: part1.c
	$(CC) $(CFLAGS) -c $<

clean:
	-rm *.log part1.o part1
