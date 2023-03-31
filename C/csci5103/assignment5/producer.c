#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "timedbuffer.h"

#define DEBUG 1

/*The program takes the No of items to be produced and the item string as the parameter*/
int main(int argc, char **argv)
{
	int fd_tb, fd_log, noofitems = 0, res;
	int item_size = ITEM_SIZE;
	char buffer[item_size];
	char item[item_size];
	char filename[255];

	//Process arguments
	if (argc != 3) {
		printf("Too few arguments to producer. Usage:\n   producer <num_items> <item_name-string>\n");
		return 0;
	}
	noofitems = atoi(argv[1]);
	sprintf(filename, "Prod_%s.log", argv[2]);

	//Open the timedbuffer device in write mode
	fd_tb = open("/dev/timedbuffer", O_WRONLY);
	if (fd_tb == -1) {
		printf("Failed to open the scullbuffer device\n");
		return 0;
	}

	//Sleep for a moment to give other processes time to open timedbuffer
	sleep(10);

	//Clear and open the logfile
	unlink(filename);
	fd_log = open(filename, O_WRONLY|O_CREAT, 0664);
	if (fd_log == -1) {
		printf("Failed to open the producer log file: %s\n", filename);
		goto cleanup;
	} else {
		#ifdef DEBUG
		printf("The name of the new producer log file is %s\n", filename);
		#endif
	}

	printf("Producer starting to deposit items...\n");
	//Write the required number of items into the timedbuffer device
	for (int i = 0; i < noofitems; i++) {
		
		//Write the item content to the producer temporary buffer
		memset(buffer, '\0', item_size);
		sprintf(buffer, "%s%d", argv[2], i);
		#ifdef DEBUG
		printf("Produer: deposited item %s\n", buffer);
		#endif

		//Write to scullbuffer and Log the result
		res = write(fd_tb, buffer, item_size);
		if (res == item_size) {
			snprintf(item, strlen(buffer) + 1, "%s", buffer);
			sprintf(item, "%s\n", item);
			write(fd_log, item, strlen(item));
		}

		//write returns 0 if there is no space left to write and no readers.
		if (res==0) {
		   printf("Producer timed out after 20 seconds: buffer is full but there is no active consumer.\n");
                }

		//write returns -1 if an unrecoverable error occurred.
		if (res <= 0)
			goto cleanup;
	}

cleanup:
        printf("Producer finished deposting items in the buffer.\n");
	close(fd_tb);
	close(fd_log);
	return res;
}
