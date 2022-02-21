#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <file_name>\n", argv[0]);
		exit(1);
	}
	struct stat     st;
	if (!stat(argv[1], &st)) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
}
