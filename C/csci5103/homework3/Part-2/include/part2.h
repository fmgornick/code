#ifndef PART_2
#define PART_2

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <wait.h>

#define IDSIZE   20
#define BUFSIZE  50
#define COLORSZE 6
#define DEFAULT  100
#define INFOSIZE 100
#define KEY      69420
#define KEYSIZE  10

typedef struct item {
  int num;
  char info[INFOSIZE];
} item_t;

typedef struct shared_vars {
  struct item buffer[BUFSIZE];
  int head;
  int tail;

  int max_count;
  int N;
  int count;

  int current_producer;

  pthread_mutex_t lock;
  pthread_cond_t spaceAvailable;
  pthread_cond_t itemAvailable;
} shared_vars_t;

extern inline void initialize_shared(shared_vars_t *s) {
  s->head = 0;
  s->tail = 0;
  s->count = 0;

  s->max_count = DEFAULT;
  s->N = BUFSIZE;

  pthread_mutexattr_t mutexattr;
  pthread_mutexattr_init(&mutexattr);

  pthread_condattr_t condattr;
  pthread_condattr_init(&condattr);

  pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
  pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED);

  pthread_mutex_init(&s->lock, &mutexattr);
  pthread_cond_init(&s->spaceAvailable, &condattr);
  pthread_cond_init(&s->itemAvailable, &condattr);
}

extern inline void free_shared(shared_vars_t *s) {
  pthread_mutex_destroy(&s->lock);
  pthread_cond_destroy(&s->spaceAvailable);
  pthread_cond_destroy(&s->itemAvailable);
}

#endif // !PART_2
