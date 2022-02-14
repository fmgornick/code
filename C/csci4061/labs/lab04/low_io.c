#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUF_SIZE 1024

#define STDIN 0
#define STDOUT 1
#define STDERR 2

char *get_line_low_level(int FD_TO_READ, int *num_char_read) {
  // Allocate space for a string that we will later return (initial size is 1
  // char)
  char *line_in = malloc(sizeof(char) * 1);

  // Pre-Loop Declarations
  char *temp;
  char single_char[1];
  *num_char_read = 0;

  // Read 1 char at a time from FD_TO_READ into single_char

  while (read(FD_TO_READ, single_char, 1) > 0) {
    // Increment the number of charachters we have read
    (*num_char_read)++;

    // If not a newline char, allocate more space for the new char and append it
    // to the string
    if ((temp = realloc(line_in, *num_char_read + 1)) != NULL) {
      line_in = temp;
      line_in[*num_char_read - 1] = *single_char;
      line_in[*num_char_read] = '\0';

      // If the char read was a newline char, break and return the string
      if (*single_char == '\n') {
        break;
      }
    } else {
      printf("Realloc Failed\n");
    }
  }

  return line_in;
}

int main(int argc, char *argv[]) {
  int inputFd = 0;
  int outputFd = 0;
  int openFlags = 0;

  mode_t filePerms;

  openFlags = O_CREAT | O_RDWR | O_TRUNC; // Write-output
  filePerms =
      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */

  if (argc != 3) {
    printf("Usage: %s <source> <destination>\n", argv[0]);
    exit(1);
  }

  // 1. open source file -> argv[1] : open()
  if ((inputFd = open(argv[1], O_RDONLY)) == -1) {
    perror("Failed to open source file.");
    return -1;
  }
  /*TODO - Open Source File*/

  // 2. open destination file -> argv[2] : open()
  if ((outputFd = open(argv[2], openFlags, filePerms)) == -1) {
    perror("Failed to open destination file.");
    return -1;
  }
  /*TODO - Open Destination File*/

  // 3. Read the first 3 lines from source and write it to destination AND print
  // to stdout
  for (int i = 0; i < 3; i++) {
    int num_char_read = 0;
    char *line_read = get_line_low_level(inputFd, &num_char_read);

    write(1, line_read, num_char_read);

    write(outputFd, line_read, num_char_read);

    free(line_read);
  }

  // 4. Read a single line from stdin and write it to destination
  printf("Please type something and hit enter:\n");

  int num_char_read = 0;
  char *line_from_stdin = get_line_low_level(0, &num_char_read);

  write(outputFd, line_from_stdin, num_char_read);

  free(line_from_stdin);

  // 5. close source file : close()
  if (close(inputFd) == -1) {
    perror("Failed to close source file");
    return -1;
  }

  // 6. close destination file : close()
  if (close(outputFd) == -1) {
    perror("Failed to close destination file");
    return -1;
  }
}
