#include "part2.h"

int main(int argc, char *argv[]) {
  shared_vars_t *s;
  int id, errno;

  char *colors[3] = {"red", "white", "blue"};
  char *consumer_args[6];

  int ppids[3];
  int cpid;

  if ((id = shmget(KEY, sizeof(shared_vars_t), IPC_CREAT | 0666)) < 0) {
    printf("main: error getting shared memory\n");
    return 1;
  }

  s = (shared_vars_t *)shmat(id, NULL, 0);
  if (s == (void *)-1) {
    printf("main: error attaching shared memory\n");
    return 2;
  }

  initialize_shared(s);
  if (argc == 2 && (s->max_count = atoi(argv[1])) == 0) {
    printf("invalid argument... assigning 100\n");
    s->max_count = DEFAULT;
  }

  char key[KEYSIZE];
  sprintf(key, "%d", KEY);

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

  waitpid(cpid, NULL, 0);

  free_shared(s);
  shmdt(s);
  shmctl(id, IPC_RMID, NULL);
  return 0;
}
