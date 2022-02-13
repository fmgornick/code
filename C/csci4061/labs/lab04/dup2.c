#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> 

int main(int argc, char **argv)
{
	int in, out;
	char *grep_args[] = {"grep", "find", NULL};

	// open input and output files

	if((in = open("input", O_RDONLY)) == -1)
	{
		perror("Failed to open input.");
		return -1;
	}

	if((out = open("dup2_output", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
	{
		perror("Failed to open dup2_output.");
		return -1;
	}

	if (dup2(in, 0) == -1) 
	{
		perror("Failed to redirect stdin.");
	    return -1;
	}

	if (dup2(out, 1) == -1) 
	{
		perror("Failed to redirect stdout.");
		return -1;
	}

	// close unused file descriptors
	close(in);
	close(out);

	// execute grep
	execvp("grep", grep_args);
}