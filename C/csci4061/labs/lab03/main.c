/*
 *  Fletcher Gornick (gorni025@umn.edu)
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {

  // take 'n' from the input and convert to integer
  // You can use strtol()
  if (argc != 2) {
    printf("ERROR: incorrect # of args, please try again\n");
    return -1;
  }

  int n = atoi(argv[1]);
  pid_t pid;
  int status;

  // for i in n
  //		create child process
  //			print pid
  //			call execl to print 'hello there' using 'echo'
  for (int i = 0; i < n; i++) {
    pid = fork();
    if (pid == -1) {
      printf("ERROR: fork() failed\n");
      return -1;
    } else if (pid > 0) {
      printf("%d\n", pid);
    } else {
      execl("/bin/echo", "echo", "hello there", NULL);
      printf("ERROR: execl() failed\n");
      return -1;
    }
  }

  // parent waits for all child processes to terminate
  while (wait(&status) > 0)
    ;

  // parent create child process
  //		call execv on 'ptime' executable
  pid = fork();
  if (pid == -1) {
    printf("ERROR: fork() failed\n");
    return -1;
  } else if (pid == 0) {
    char *args[] = {"ptime", "ptime"};
    execv(*args, args);
    printf("ERROR: execv() failed\n");
    return -1;
  }

  // parent waits for child to complete
  wait(&status);
  return 0;
}
