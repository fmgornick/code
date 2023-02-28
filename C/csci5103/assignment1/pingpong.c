/* CSCI 5103 Spring 2023
 * Assignment# 1
 * name: Flercher Gornick
 * student id: 5579904
 * x500 id: gorni025
 * CSELABS machine: csel-cuda-04 */

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 64

int fd, limit, terminated;

/* parent and child signal handler, doesn't actually do anything */
void sigusr_handler(int signum) {}

/* signal handler for when process terminates unexpectedly */
void unexpected_handler(int signum) { terminated = 1; }

/* parent process (takes in child pid as an argument)*/
void parent(int pid) {
  printf("PARENT::parent process executing with LIMIT = %d\n", limit);
  printf("PARENT::parent process id = %d\n", getpid());

  int count = 0;
  char buf[BUFSIZE] = {'\0'};
  struct sigaction usr2 = {0};
  struct sigaction childterm = {0};

  /* set up sigaction for when parent recieves SIGUSR1 from child */
  sigemptyset(&usr2.sa_mask);
  usr2.sa_handler = sigusr_handler;
  sigaction(SIGUSR2, &usr2, NULL);

  /* set up sigaction for when child terminates unexpectedly */
  sigemptyset(&childterm.sa_mask);
  childterm.sa_handler = unexpected_handler;
  sigaction(SIGCHLD, &childterm, NULL);

  /* this mask (used by sigsuspend) temporarily unblocks the SIGUSR2, SIGCHLD
   * and SIGINT making it so the parent process is suspended until one of these
   * three specific signals are sent */
  sigset_t pmask;
  sigfillset(&pmask);
  sigdelset(&pmask, SIGUSR2);
  sigdelset(&pmask, SIGCHLD);
  sigdelset(&pmask, SIGINT);

  /* loop until we've finished ping-ponging or exit if child terminated */
  while (count < limit && !terminated) {
    /* write counter value to Logger file */
    sprintf(buf, "Parent %d\n", count++);
    write(fd, &buf, BUFSIZE);

    /* send SIGUSR1 signal to child and suspend parent process until SIGUSR2
     * signal sent back (NOTE: sigsuspend restores the previous set of masked
     * signals when it returns) */
    kill(pid, SIGUSR1);
    if (!terminated)
      sigsuspend(&pmask);
  }

  /* send message if unexpected termination occurs */
  if (terminated)
    printf("child process terminated unexpectedly\nyou may not see a prompt, "
           "but the process terminated gracefully!!\n\n");

  /* wait for child process to terminate and delete reference to file */
  close(fd);
  wait(NULL);
}

void child() {
  printf("CHILD::child process executing with LIMIT = %d\n", limit);
  printf("CHILD::child process id = %d\n", getpid());

  int count = 0;
  char buf[BUFSIZE] = {'\0'};
  struct sigaction usr1 = {0};
  struct sigaction parentterm = {0};

  /* set up sigaction for when parent recieves SIGUSR2 from parent */
  sigemptyset(&usr1.sa_mask);
  usr1.sa_handler = sigusr_handler;
  sigaction(SIGUSR1, &usr1, NULL);

  /* set up sigaction for when parent terminates unexpectedly */
  sigemptyset(&parentterm.sa_mask);
  parentterm.sa_handler = unexpected_handler;
  sigaction(SIGUSR2, &parentterm, NULL);

  /* send SIGUSR2 signal to child if parent terminates */
  prctl(PR_SET_PDEATHSIG, SIGUSR2);

  /* this mask (used by sigsuspend) temporarily unblocks the SIGUSR1, SIGUSR2,
   * and SIGINT making it so the parent process is suspended until one of these
   * three specific signals are sent */
  sigset_t cmask;
  sigfillset(&cmask);
  sigdelset(&cmask, SIGUSR1);
  sigdelset(&cmask, SIGUSR2);
  sigdelset(&cmask, SIGINT);

  /* loop until we've finished ping-ponging or exit if parent terminated */
  while (count < limit && !terminated) {
    /* suspend parent process until SIGUSR1 signal sent back (NOTE: sigsuspend
     * restores the previous set of masked signals when it returns) */
    if (!terminated)
      sigsuspend(&cmask);

    /* write counter value to Logger file */
    sprintf(buf, "Child %d\n", count++);
    write(fd, &buf, BUFSIZE);

    /* send SIGUSR2 signal to parent */
    kill(getppid(), SIGUSR2);
  }

  /* send message if unexpected termination occurs */
  if (terminated)
    printf("parent process terminated unexpectedly\nyou may not see a prompt, "
           "but the process terminated gracefully!!\n\n");

  /* delete reference to file */
  close(fd);
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
  fd = open("Logger", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC);

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

  return 0;
}
