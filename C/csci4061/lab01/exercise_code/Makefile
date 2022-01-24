CC=gcc
CFLAGS=-I./include
DEPS=main.h name.h address.h major.h
OBJ=main.o name.o address.o major.o
EXE=w2.out

.PHONY: all clean run

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm *.o $(EXE)

run:
	./$(EXE)
