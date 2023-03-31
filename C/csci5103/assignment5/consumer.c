#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "timedbuffer.h"

#define DEBUG 1

int main(int argc, char **argv) {

	int fd_tb, fd_log, noofitems = 0, res;
	int item_size = ITEM_SIZE;
	char buffer[item_size];
	char item[item_size];
	char filename[255];
	
	//Process arguments
	if (argc < 2) {
		printf("Too few arguments to consumer --  Usage:\n   consumer  <num_items> [consumer_name]\n");
		return 0;
	}
	noofitems = atoi(argv[1]);
	if (argc == 3)
		sprintf(filename, "Cons_%s.log", argv[2]);
	else
		sprintf(filename, "Cons.log");

	//Open the timedbuffer device in write mode
	fd_tb = open("/dev/timedbuffer", O_RDONLY);
	if (fd_tb == -1) {
		#ifdef DEBUG
		printf("Failed to open the device %d\n", errno);
		#endif
		goto cleanup;
	}

	//Sleep for a moment to give each process time to open timedbuffer
	sleep(1);

	//Clear and open the logfile
	unlink(filename);
	fd_log = open(filename, O_WRONLY|O_CREAT, 0664);
	if (fd_log == -1) {
		printf("Failed to open the consumer log file: %s\n", filename);
		goto cleanup;
	}
	else
		printf("Name of the Consumer logfile is: %s\n", filename);


	printf("Consumer starting to remove items...\n");
	//Read the required number of items from the timedbuffer device
	for (int i = 0; i < noofitems; i++) {
	
		//Read an item from timedbuffer into consumer buffer and log the result
		memset(buffer, '\0', item_size);
		res = read(fd_tb, buffer, item_size);
		if (res == item_size) {
			snprintf(item, strlen(buffer) + 1, "%s", buffer);
			sprintf(item, "%s\n", item);
			write(fd_log, item, strlen(item));
		}

		#ifdef DEBUG
		printf("Consumer: removed item %s\n", buffer);
		#endif

		if (res == 0)
	           printf("Consumer timed out after 20 seconds: buffer is empty but no active producer.\n");

		//read returns 0 if there are no producers and timeout of 20 seconds when no items left to read
		//read returns -1 if an unrecoverable error occurred.
		if (res <= 0)
			goto cleanup;
	}

cleanup:
	printf("Consumer completed removing items from the buffer\n");
	close(fd_tb);
	close(fd_log);

	return 0;
}
