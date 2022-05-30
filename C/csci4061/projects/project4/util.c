#ifndef _REENTRANT
#define _REENTRANT
#endif

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"

// Global variables
static int master_fd = -1; // Global var used to store socket

/**********************************************
 * makeargv
 * @param s is the buffer that needs to be parsed.
 * @param delimeters is used to split the buffer. Will be used by strtok_r
 * @param argvp is adress to string array (so charr*** type) -> Try to reason
 *why this needs to be char** type
 *
 * Returns number of tokens on sucess and sets argvp -1 otherwise
 * Usage example:
 *    char* buf = "This is the string I want to parse \n";
 *    char **result;
 *    makeargv(buf," \n",&result)
 *    result contains => ["This","is","the","string","I","want","to","parse"]
 ************************************************/
int makeargv(const char *s, const char *delimiters, char ***argvp) {
  int error;
  int i;
  int numtokens;
  const char *snew;
  char *t;
  char *context;

  if ((s == NULL) || (delimiters == NULL) || (argvp == NULL)) {
    errno = EINVAL;
    return -1;
  }

  *argvp = NULL;
  snew = s + strspn(s, delimiters);

  if ((t = malloc(strlen(snew) + 1)) == NULL)
    return -1;
  strcpy(t, snew);

  numtokens = 0;
  if (strtok_r(t, delimiters, &context) != NULL)
    for (numtokens = 1; strtok_r(NULL, delimiters, &context) != NULL;
         numtokens++)
      ;

  if ((*argvp = malloc((numtokens + 1) * sizeof(char *))) == NULL) {
    error = errno;
    free(t);
    errno = error;
    return -1;
  }

  if (numtokens == 0)
    free(t);
  else {
    strcpy(t, snew);
    **argvp = strtok_r(t, delimiters, &context);
    for (i = 1; i < numtokens; i++) {
      *((*argvp) + i) = strtok_r(NULL, delimiters, &context);
    }
  }
  *((*argvp) + numtokens) = NULL;

  return numtokens;
}

void freemakeargv(char **argv) {
  if (argv == NULL)
    return;
  if (*argv != NULL)
    free(*argv);
  free(argv);
}

/**********************************************
 * init
   - port is the number of the port you want the server to be
     started on
   - initializes the connection acception/handling system
   - YOU MUST CALL THIS EXACTLY ONCE (not once per thread,
     but exactly one time, in the main thread of your program)
     BEFORE USING ANY OF THE FUNCTIONS BELOW
   - if init encounters any errors, it will call exit().
************************************************/
void init(int port) {
  // set up sockets using bind, listen
  // also do setsockopt(SO_REUSEADDR)
  // exit if the port number is already in use

  // Create socket, store return value in master_fd
  master_fd = -1;
  if ((master_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    perror("cannot create socket");
    exit(1);
  }

  // Use setsockopt with SO_REUSEADDR
  int enable = 1;
  if (setsockopt(master_fd, SOL_SOCKET, SO_REUSEADDR, &enable, 4) == -1) {
    perror("cannot set socket option");
    exit(1);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(port);

  // Bind socket
  if (bind(master_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("cannot bind socket");
    exit(1);
  }

  // Listen
  if (listen(master_fd, BACKLOG) == -1) {
    perror("could not listen");
    exit(1);
  }

  // If successful should print
  printf("UTILS.O: Server Started on Port %d\n", port);
}

/**********************************************
 * accept_connection - takes no parameters
   - returns a file descriptor for further request processing.
     DO NOT use the file descriptor of your own -- use
     get_request() instead.
   - if the return value is negative, the thread calling
     accept_connection must should ignore request.
***********************************************/
int accept_connection(void) {

  // create socket 
  struct sockaddr_in addr;
  socklen_t size = sizeof(addr);
  int fd = -1;

  // accept the connection and set master_fd
  if ((fd = accept(master_fd, (struct sockaddr *)&addr, &size)) == -1) {
    perror("failed to accept connection");
    return -1;
  }
  return fd;
}

/**********************************************
 * get_request
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        from where you wish to get a request
      - filename is the location of a character buffer in which
        this function should store the requested filename. (Buffer
        should be of size 1024 bytes.)
   - returns 0 on success, nonzero on failure. You must account
     for failures because some connections might send faulty
     requests. This is a recoverable error - you must not exit
     inside the thread that called get_request. After an error, you
     must NOT use a return_request or return_error function for that
     specific 'connection'.
************************************************/
int get_request(int fd, char *filename) {
  /*
     Read from the socketfd and parse the first line for the GET info
     Error checks:
        - if it isn't a GET request
        - if the file starts with .. or // -> Security breach (Accessing file
     outside server roor dir)
        - if the file path length is greater than 1024 (Possible buffer
     overflow) In all the cases just dump it and return -1.

     otherwise, store the path/filename into 'filename'.
  */

  // Read first line from fd (The rest does not matter to us)
  // Look at fgets
  char request[MAX_HTTP_REQUEST_SIZE];
  FILE *fd2 = fdopen(fd, "r");
  if (fd2 == NULL) {
    perror("cannot open file");
    return -1;
  }

  // check if request is empty
  if (fgets(request, MAX_HTTP_REQUEST_SIZE, fd2) == NULL) {
    perror("empty request");
    fclose(fd2);
    return -1;
  }

  // Pass the first line read into makeargv
  // Look at makeargv comments for usage
  char **words;
  int num_tokens = makeargv(request, " ", &words);
  if (num_tokens == -1) {
    perror("error parsing request");
    freemakeargv(words);
    close(fd);
    return -1;
  }

  // Error checks

  // make sure request type and file path provided
  if (num_tokens < 2) {
    perror("missing request type or file name");
    freemakeargv(words);
    close(fd);
    return -1;
  }

  // make sure it's a get request
  if (strcmp(words[0], "GET") != 0) {
    perror("not a get request");
    freemakeargv(words);
    close(fd);
    return -1;
  }

  // make sure their not trying to access outside of the root folder
  if (strstr(words[1], "..")) {
    printf("attempted security breach: \'..\' not allowed in request file\n");
    freemakeargv(words);
    close(fd);
    return -1;
  }

  // check for other possible security breach
  if (strstr(words[1], "//")) {
    printf("attempted security breach: \'//\' not allowed in request file\n");
    freemakeargv(words);
    close(fd);
    return -1;
  }

  // make sure the file path isn't bigger than the buffer
  if (strlen(words[1]) >= MAX_FILEPATH_LENGTH) {
    perror("file path too big");
    freemakeargv(words);
    close(fd);
    return -1;
  }

  // Passed error checks copy the path into filename
  strcpy(filename, words[1]);

  // Call freemakeargv to free memory
  freemakeargv(words);

  // Return success
  return 0;
}

/**********************************************
 * return_result
   - returns the contents of a file to the requesting client
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        to where you wish to return the result of a request
      - content_type is a pointer to a string that indicates the
        type of content being returned. possible types include
        "text/html", "text/plain", "image/gif", "image/jpeg" cor-
        responding to .html, .txt, .gif, .jpg files.
      - buf is a pointer to a memory location where the requested
        file has been read into memory (the heap). return_result
        will use this memory location to return the result to the
        user. (remember to use -D_REENTRANT for CFLAGS.) you may
        safely deallocate the memory after the call to
        return_result (if it will not be cached).
      - numbytes is the number of bytes the file takes up in buf
   - returns 0 on success, nonzero on failure.
************************************************/
int return_result(int fd, char *content_type, char *buf, int numbytes) {
  /*
     send headers back to the socketfd, connection: close, content-type,
     content-length, etc then finally send back the resulting file then close
     the connection.

     It is IMPORTANT that you follow the format as described in the writeup
     while writing to the socket.

  */
  // response header
  char result[] = "HTTP/1.1 200 OK\n";
  if (write(fd, result, strlen(result)) < strlen(result)) {
    printf("couldn't write result header into file descriptor\n");
    return -1;
  }

  // content type header
  char ctype[MAX_HEADER_LENGTH];
  if (snprintf(ctype, MAX_HEADER_LENGTH, "Content-Type: %s\n", content_type) >= MAX_HEADER_LENGTH) {
    perror("content-type string too large");
    return -1;
  }
  if (write(fd, ctype, strlen(ctype)) < strlen(ctype)) {
    printf("couldn't write content-type header into file descriptor\n");
    return -1;
  }

  // content length header
  char clen[MAX_HEADER_LENGTH];
  if (snprintf(clen, MAX_HEADER_LENGTH, "Content-Length: %d\n", numbytes) >= MAX_HEADER_LENGTH) {
    perror("content-length string too large");
    return -1;
  }
  if (write(fd, clen, strlen(clen)) < strlen(clen)) {
    printf("couldn't write content-length header into file descriptor\n");
    return -1;
  }

  // connection close header
  char connection[] = "Connection: Close\n\n";
  if (write(fd, connection, strlen(connection)) < strlen(connection)) {
    printf("couldn't write connection header into file descriptor\n");
    return -1;
  }

  // finally send requested data
  if (write(fd, buf, numbytes) < numbytes) {
    printf("couldn't write data into file descriptor\n");
    return -1;
  }

  close(fd);
  return 0;
}

/**********************************************
 * return_error
   - returns an error message in response to a bad request
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        to where you wish to return the error
      - buf is a pointer to the location of the error text
   - returns 0 on success, nonzero on failure.
************************************************/
int return_error(int fd, char *buf) {
  // length of error result
  int numbytes = strlen(buf);

  // result header
  char result[] = "HTTP/1.1 404 Not Found\n";
  if (write(fd, result, strlen(result)) < strlen(result)) {
    printf("couldn't write result header into file descriptor\n");
    return -1;
  }

  // content type header
  char ctype[] = "Content-Type: text/html\n";
  if (write(fd, ctype, strlen(ctype)) < strlen(ctype)) {
    printf("couldn't write content-type header into file descriptor\n");
    return -1;
  }

  // content length header
  char clen[MAX_HEADER_LENGTH];
  if (snprintf(clen, MAX_HEADER_LENGTH, "Content-Length: %d\n", numbytes) >= MAX_HEADER_LENGTH) {
    perror("content-length string too large");
    return -1;
  }
  if (write(fd, clen, strlen(clen)) < strlen(clen)) {
    printf("couldn't write content-length header into file descriptor\n");
    return -1;
  }

  // connection close header
  char connection[] = "Connection: Close\n\n";
  if (write(fd, connection, strlen(connection)) < strlen(connection)) {
    printf("couldn't write connection header into file descriptor\n");
    return -1;
  }

  // finally send requested data
  if (write(fd, buf, numbytes) < numbytes) {
    printf("couldn't write data into file descriptor\n");
    return -1;
  }

  close(fd);
  return 0;
}
