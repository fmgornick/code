#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 64

int fd, limit;

/* parent and child signal handler, doesn't actually do anything */
void handler(int signum) {}

/* parent process (takes in child pid as an argument)*/
void parent(int pid) {
  printf("PARENT::parent process executing with LIMIT = %d\n", limit);
  printf("PARENT::parent process id = %d\n", getpid());

  int count = 0;
  char buf[BUFSIZE] = {'\0'};
  struct sigaction parent_sa;

  /* set up sigaction for when parent recieves SIGUSR1 from child */
  sigemptyset(&parent_sa.sa_mask);
  parent_sa.sa_handler = handler;
  sigaction(SIGUSR2, &parent_sa, NULL);

  /* this mask (used by sigsuspend) temporarily unblocks the SIGUSR2 signal as
   * well as SIGINT making it so the parent process is suspended until these two
   * specific signals are sent */
  sigset_t pmask;
  sigfillset(&pmask);
  sigdelset(&pmask, SIGUSR2);
  sigdelset(&pmask, SIGINT);

  /* loop until we've finished ping-ponging */
  while (count < limit) {
    /* write buffer to Logger file */
    sprintf(buf, "Parent %d\n", count++);
    write(fd, &buf, BUFSIZE);

    /* send SIGUSR1 signal to child and suspend parent process until SIGUSR2
     * signal sent back (NOTE: sigsuspend restores the previous set of masked
     * signals when it returns) */
    kill(pid, SIGUSR1);
    sigsuspend(&pmask);
  }
}

void child() {
  printf("CHILD::child process executing with LIMIT = %d\n", limit);
  printf("CHILD::child process id = %d\n", getpid());

  int count = 0;
  char buf[BUFSIZE] = {'\0'};
  struct sigaction child_sa;

  /* set up sigaction for when parent recieves SIGUSR2 from parent */
  sigemptyset(&child_sa.sa_mask);
  child_sa.sa_handler = handler;
  sigaction(SIGUSR1, &child_sa, NULL);

  /* this mask (used by sigsuspend) temporarily unblocks the SIGUSR1 signal as
   * well as SIGINT making it so the child process is suspended until these two
   * specific signals are sent */
  sigset_t cmask;
  sigfillset(&cmask);
  sigdelset(&cmask, SIGUSR1);
  sigdelset(&cmask, SIGINT);

  while (count < limit) {
    /* suspend parent process until SIGUSR1 signal sent back (NOTE: sigsuspend
     * restores the previous set of masked signals when it returns) */
    sigsuspend(&cmask);

    /* write buffer to Logger file */
    sprintf(buf, "Child %d\n", count++);
    write(fd, &buf, BUFSIZE);

    /* send SIGUSR2 signal to parent */
    kill(getppid(), SIGUSR2);
  }
}

int main(int argc, char *argv[]) {
  /* argument checking and string parsing */
  if (argc != 2) {
    printf("pass the limit as an argument to the program\n");
    return 1;
  } else {
    if ((limit = atoi(argv[1])) < 0) {
      printf("invalid argument (should be a positive integer)\n");
      return 2;
    }
  }

  /* create logger file (file descriptor is a global variable, so both child
   * processes can access it) */
  fd = open("Logger", O_WRONLY | O_CREAT | O_APPEND);

  /* block both SIGUSR1 and SIGUSR2 signals from both processes to start off,
   * this way the processes can unblock to synchronize */
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);
  sigaddset(&mask, SIGUSR2);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  /* fork and run the parent and child processes */
  int pid = fork();
  if (pid == 0)
    child();
  else
    parent(pid);

  /* wait for child process to terminate and close file descriptor */
  wait(NULL);
  close(fd);
  return 0;
}
