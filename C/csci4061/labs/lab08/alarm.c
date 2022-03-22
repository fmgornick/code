#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ALARMcount;

void AlarmSignalHandler(int sig) {

  // if another alarm occurs while in signal handler, ignore it
  signal(SIGALRM, SIG_IGN);

  // increment alarm counter
  ALARMcount += 1;

  // print "Woke up for the # time"
  printf("Woke up for the %d time\n", ALARMcount);

  // if count < 3 call alarm again
  if (ALARMcount < 3) {
    alarm(5);
  } else {
    exit(0);
  }

  // reinstall the signal handler
  signal(SIGALRM, AlarmSignalHandler);
}

int main(int argc, char *argv[]) {

  // initialize counter
  ALARMcount = 0;

  // install signal handler for SIGALRM
  signal(SIGALRM, AlarmSignalHandler);

  // call alarm(5)
  alarm(5);

  while (1)
    ;
  return 0;
}
