CC = gcc
CFLAGS = -Wall -g

ROOT_DIR:=$(shell pwd)
INC = -I$(ROOT_DIR)/include
LIBS = -lpthread -D_REENTRANT

part2: build/part2.o bin/producer bin/consumer log
	$(CC) $< -o $@ $(LIBS)

bin/producer: build/producer.o bin
	$(CC) $< -o $@ $(LIBS)

bin/consumer: build/consumer.o bin
	$(CC) $< -o $@ $(LIBS)

build/%.o: src/%.c build
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

build:
	mkdir build

bin:
	mkdir bin

log:
	mkdir log

clean:
	-rm -rf part2 bin build log 
