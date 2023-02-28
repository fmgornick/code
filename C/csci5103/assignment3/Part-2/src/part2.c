/* CSCI 5103 Spring 2023
 * Assignment 3
 * name: Flercher Gornick
 * student id: 5579904
 * x500 id: gorni025
 * CSELABS machine: csel-cuda-04 */

#include "part2.h"

int main(int argc, char *argv[]) {
  shared_vars_t *s;
  int id, errno;

  /* array for calling exec on the consumer process 
   * [0]:     execuatable path 
   * [1]:     shared memory key 
   * [2,3,4]: producer pids for consumer to wait for 
   * [5]:     NULL */
  char *consumer_args[6];
  char *colors[3] = {"red", "white", "blue"};

  /* keep track of all our child pids */
  int ppids[3];
  int cpid;

  /* create our memory segment with KEY defined in part2.h 
   * (should be size of our struct, given rw-rw-rw- permissions) */
  if ((id = shmget(KEY, sizeof(shared_vars_t), IPC_CREAT | 0666)) < 0) {
    printf("main: error getting shared memory\n");
    return 1;
  }

  /* attach our struct pointer to our shared mem segment */
  s = (shared_vars_t *)shmat(id, NULL, 0);
  if (s == (void *)-1) {
    printf("main: error attaching shared memory\n");
    return 2;
  }

  /* initialize our struct (DEFINED IN part2.h) */
  initialize_shared(s);
  if (argc == 2 && (s->max_count = atoi(argv[1])) == 0) {
    printf("invalid argument... assigning 100\n");
    s->max_count = DEFAULT;
  }

  char key[KEYSIZE];
  sprintf(key, "%d", KEY);

  /* fork our 3 producer processes 
   * - pass in a key and color each time 
   * - add pid to our consumer args array */
  for (int i = 0; i < 3; i++) {
    if (!(ppids[i] = fork())) {
      if ((errno = execl("./bin/producer", "./bin/producer", key, colors[i], NULL)) < 0)
        printf("error executing producer process %d: %s\n", i, strerror(errno));
      break;
    } else if (ppids[i] < 0) {
      printf("error forking producer process %d\n", i);
      return 3;
    } else {
      char ppid[IDSIZE];
      sprintf(ppid, "%d", ppids[i]);
      consumer_args[i + 2] = ppid;
    }
  }

  /* fork consumer process with array mentioned above */
  if (!(cpid = fork())) {
    consumer_args[0] = "./bin/consumer";
    consumer_args[1] = key;
    consumer_args[5] = NULL;
    if ((errno = execv(consumer_args[0], consumer_args)) < 0)
      printf("error executing consumer process: %s\n", strerror(errno));
  } else if (cpid < 0) {
    printf("error forking consumer process\n");
    return 4;
  }

  /* wait for consumer 
   * (consumer already waits for 3 producers) */
  waitpid(cpid, NULL, 0);

  /* deallocate shared resources, detatch, and remove before exiting
   * (free_shared DEFINED IN part2.h) */
  free_shared(s);
  shmdt(s);
  shmctl(id, IPC_RMID, NULL);
  return 0;
}
