CC = gcc
CFLAGS = -D_REENTRANT -g -Wall -Wno-unknown-pragmas
LDFLAGS = -lpthread -pthread

web_server: server.o util.o
	${CC} $(CFLAGS) -o web_server server.o util.o ${LDFLAGS}

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c -o util.o	${LDFLAGS}

test_full:
	@# Port: passed_in | Path: ./testing | num_dispatcher: 5 | num_workers: 5
	@# dynamic_flag: 1 | cache_flag: 1 | queue_length: 50 | cache_size: 50

	@read -p "Enter a random port between 1024 & 65536: " sock_in; \
	./web_server $$sock_in ./testing 100 100 1 1 50 50

test:
	@# Port: passed_in | Path: ./testing | num_dispatcher: 5 | num_workers: 5
	@# dynamic_flag: 1 | cache_flag: 1 | queue_length: 50 | cache_size: 50

	@read -p "Enter a random port between 1024 & 65536: " sock_in; \
	./web_server $$sock_in ./testing 4 4 0 0 50 50

solution:
	@# Port: passed_in | Path: ./testing | num_dispatcher: 5 | num_workers: 5
	@# dynamic_flag: 1 | cache_flag: 1 | queue_length: 50 | cache_size: 50
	@chmod +x web_server_sol
	@read -p "Enter a random port between 1024 & 65536: " sock_in; \
	./web_server_sol $$sock_in ./testing 100 100 1 1 50 50

force_kill:
	@echo -n "Force Killing web_server proc PID: "; ps -C "web_server" -o pid=
	@ps -C "web_server" -o pid= | xargs kill -9
	@echo -n "Force Killing parent proc PID: "; ps -C "make" -o pid=
	@ps -C "make" -o pid= | xargs kill -9

submission: clean
	@echo "Creating Tar Submission..."
	@read -p "Please enter your group number: " grou_num; \
	tar_name="group_"$$grou_num"_p4_submission.tar.gz";\
	rm -f $$tar_name;tar -czvf $$tar_name util.c README.md util.h Makefile;\
	echo "Submission Created: " $$tar_name

clean:
	rm -f web_server webserver_log util.o *.tar.gz
	@clear
	@echo "Succesful Clean"
