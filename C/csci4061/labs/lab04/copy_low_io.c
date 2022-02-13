#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
  int inputFd = 0;
  int outputFd = 0;
  int openFlags = 0;

  mode_t filePerms;
  ssize_t numRead;
  char buf[BUF_SIZE];

  openFlags = O_CREAT | O_WRONLY | O_TRUNC; // Write-output
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

  // 2. open destination file -> argv[2] : open()
  if ((outputFd = open(argv[2], openFlags, filePerms)) == -1) {
    perror("Failed to open destination file.");
    return -1;
  }

  // 3. Read from source and write it to destination : read(), write()
  /*while (Soruce is available)
  {
  }*/
  while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
    if (write(outputFd, buf, numRead) == -1) {
      perror("Failed to write to output file.");
      return -1;
    }
  }
  if (numRead == -1) {
    perror("Failed to read from input file.");
    return -1;
  }

  // 4. close source file : close()
  if (close(inputFd) == -1) {
    perror("failed to close input file.");
    return -1;
  }

  // 5. close destination file : close()
  if (close(outputFd) == -1) {
    perror("failed to close output file.");
    return -1;
  }

  return 0;
}
