#include<stdio.h>
#include<stdlib.h>
#include <dirent.h>

int 
main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <file_name>\n", argv[0]);
		exit(1);
	}
	DIR            *dip;	/* points of the directory named filename */
	dip = opendir(argv[1]);
	if (dip != NULL) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
}
