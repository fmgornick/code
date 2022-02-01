#include <errno.h>
#include <unistd.h>
#define BLKSIZE 1024

// fd = file descriptor (0 = stdin, 1 = stdout, 2 = stderr)
// *buf = string of file's readline
// nbytes = max # of bytes read into buf
// return = actual # of bytes if successful
int readline(int fd, char *buf, int nbytes) {
  int numread = 0;
  int returnval;

  while (numread < nbytes - 1) {
    // read a character into buf
    returnval = read(fd, buf + numread, 1);
    // EINTR: read terminated from signal and no data transferred
    if ((returnval == -1) && (errno == EINTR))
      continue;
    // end of file reached, so nothing added to buf
    if ((returnval == 0) && (numread == 0))
      return 0;
    if (returnval == 0)
      break;
    // if read returns normal error, return same errno
    if (returnval == -1)
      return -1;
    // in the case where read returns 1 and appended a character to buf
    numread++;
    // if newline reached, end string with null terminator and return
    if (buf[numread - 1] == '\n') {
      buf[numread] = '\0';
      return numread;
    }
    // if nothing else, then argument was passed in wrong so returns EINVAL
    // EINVAL: invalid argument
    errno = EINVAL;
    return -1;
  }
  return numread;
}

// copy file from "fromfd" to "tofd"
int copyfile(int fromfd, int tofd) {
  char *bp;
  char buf[BLKSIZE];
  int bytesread, byteswritten;
  int totalbytes = 0;

  while (1) {
    // if no stop signal sent, this just terminates immediately, but if there's
    // a stop signal, then it continuously loops until errno != EINTR
    while (((bytesread = read(fromfd, buf, BLKSIZE)) == -1) && (errno == EINTR))
      ;
    // In the case that -1 is returned, but errno != EINTR, then there's an
    // actual error, so we exit
    if (bytesread <= 0)
      break;
    // if we reach here, then everything is going smooth
    bp = buf;
    while (bytesread > 0) {
      // same as above, making sure no interrupt signal sent
      while (((byteswritten = write(tofd, bp, bytesread)) == -1) &&
             (errno == EINTR))
        ;
      // real error or EOF reached
      if (byteswritten <= 0)
        break;
      totalbytes += byteswritten;
      bytesread -= byteswritten;
      bp += byteswritten;
    }
    if (byteswritten == -1)
      break;
  }
  return totalbytes;
}
