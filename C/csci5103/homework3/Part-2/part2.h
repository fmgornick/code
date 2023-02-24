#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define INFOSIZE 100
#define BUFSIZE 50

struct item {
  int num;
  char info[INFOSIZE];
};

typedef struct s {
  struct item buffer[BUFSIZE];
  int head = 0;
  int tail = 0;

  int max_count = 100;
  int N = BUFSIZE;
  int count = 0;

  int current_producer = 0;

  pthread_t producers[3], consumer;
  pthread_mutex_t lock;
  pthread_cond_t spaceAvailable;
  pthread_cond_t itemAvailable;
} shared_vars;

void *produce(void *arg);
void *consume();
