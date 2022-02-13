
dup2: 
	gcc -g -Wall dup2.c -o dup2
	./dup2

copy:
	gcc -g -Wall copy_low_io.c -o runner

test:
	make clean
	make copy
	chmod +x grade.sh
	./grade.sh

clean:
	rm -f dup2 dup2_output runner output

