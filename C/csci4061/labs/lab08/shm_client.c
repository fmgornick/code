#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMSZ 100

main() {
  int shmid;
  key_t key;
  char *shm, *s;

  // shared memory key
  key = 5678;

  // Locate the segment.
  if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
    perror("shmget");
  }
  // Attach the segment to our data space.

  if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
    perror("shmat");
  }

  // Read what the server put in the memory and print it out
  for (s = shm; *s != NULL; s++)
    putchar(*s);
  putchar("\n");

  // change the first character to tell server to finish
  *shm = '*';

  return 0;
}
