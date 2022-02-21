#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <file_name>\n", argv[0]);
		exit(1);
	}
	mode_t          perm;

	struct stat     st;
	stat(argv[1], &st);
	perm = st.st_mode;
	printf("%o\n", 0777 & perm);
}
