.PHONY: run

run:
	chmod +x mapreduce
	chmod +x mapper
	chmod +x reducer
	./mapreduce 5 2 test/T1/F1.txt

t1:
	./mapreduce 5 2 test/T1/F1.txt
v1:
	valgrind ./mapreduce 5 2 test/T1/F1.txt

t2:
	./mapreduce 5 2 test/T2/F2.txt
v2:
	valgrind ./mapreduce 5 2 test/T2/F2.txt

t3:
	./mapreduce 1 1 test/T3/F3.txt
v3:
	valgrind ./mapreduce 1 1 test/T3/F3.txt

t4:
	./mapreduce 32 32 test/T4/F4.txt
v4:
	valgrind ./mapreduce 32 32 test/T4/F4.txt

clean:
	rm -rf output
