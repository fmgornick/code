CC=gcc
CFLAGS=-g

SRCDIR=src
INCLDIR=include
LIBDIR=lib

EXE=mapper reducer mapreduce

mapreduce: $(SRCDIR)/mapreduce.c $(LIBDIR)/utils.o mapper reducer
	$(CC) $(CFLAGS) -I$(INCLDIR) $(LIBDIR)/utils.o $(SRCDIR)/mapreduce.c -o mapreduce

mapper: $(SRCDIR)/mapper.c $(LIBDIR)/utils.o
	$(CC) $(CFLAGS) -I$(INCLDIR) $(LIBDIR)/utils.o $(SRCDIR)/mapper.c -o mapper

reducer: $(SRCDIR)/reducer.c $(LIBDIR)/utils.o
	$(CC) $(CFLAGS) -I$(INCLDIR)  $(LIBDIR)/utils.o $(SRCDIR)/reducer.c -o reducer

.PHONY: clean t1

#500KB
t1: $(EXE)
	./mapreduce 5 2 test/T1/F1.txt
v1: $(EXE)
	valgrind ./mapreduce 5 2 test/T1/F1.txt

t2: $(EXE)
	./mapreduce 5 2 test/T2/F2.txt
v2: $(EXE)
	valgrind ./mapreduce 5 2 test/T2/F2.txt

t3: $(EXE)
	./mapreduce 1 1 test/T3/F3.txt
v3: $(EXE)
	valgrind ./mapreduce 1 1 test/T3/F3.txt

t4: $(EXE)
	./mapreduce 32 32 test/T4/F4.txt
v4: $(EXE)
	valgrind ./mapreduce 32 32 test/T4/F4.txt

t5: $(EXE)
	./mapreduce 5 2 test/T5/F5.txt
v5: $(EXE)
	valgrind ./mapreduce 5 2 test/T5/F5.txt

t6: $(EXE)
	./mapreduce 5 2 test/T6/F6.txt
v6: $(EXE)
	valgrind ./mapreduce 5 2 test/T6/F6.txt

clean:
	rm mapreduce mapper reducer
	rm -rf output
