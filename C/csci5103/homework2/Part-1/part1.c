/* CSCI 5103 Spring 2023
 * Assignment 3
 * name: Flercher Gornick
 * student id: 5579904
 * x500 id: gorni025
 * CSELABS machine: csel-cuda-04 */

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

struct item buffer[BUFSIZE];

int max_count = 100;
int N = BUFSIZE;
int head = 0, tail = 0, count = 0;
int current_producer = 0;

pthread_t producers[3], consumer;
pthread_mutex_t lock;
pthread_cond_t spaceAvailable, itemAvailable;

void *produce(void *arg) {
  char *color = arg;
  int size;
  char file[20];
  struct timeval time;

  sprintf(file, "producer_%s.log", color);
  int fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);

  pthread_mutex_lock(&lock);
  int producer_num = current_producer;
  current_producer = (current_producer + 1) % 3;
  pthread_mutex_unlock(&lock);

  for (int i = 0; i <= max_count; i++) {
    pthread_mutex_lock(&lock);
    while (count == N || producer_num != current_producer) {
      pthread_cond_signal(&spaceAvailable);
      while (pthread_cond_wait(&spaceAvailable, &lock) != 0)
        ;
    }

    struct item new_item;
    if (i < max_count)
      new_item.num = i;
    else
      new_item.num = -1;

    gettimeofday(&time, NULL);
    size = snprintf(new_item.info, INFOSIZE, "%-7s%-6d%ld-%d\n", color,
                    new_item.num, time.tv_sec, time.tv_usec);

    buffer[head] = new_item;
    head = (head + 1) % N;
    count++;
    current_producer = (current_producer + 1) % 3;

    if (new_item.num != -1)
      write(fd, &new_item.info, size);

    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&itemAvailable);
  }

  close(fd);
  pthread_exit(NULL);
}

void *consume() {
  char buf[INFOSIZE];
  int size;
  struct timeval time;
  int fd = open("consumer.log", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);

  int num_producers_exited = 0;
  while (num_producers_exited < 3) {
    memset(buf, 0, INFOSIZE);

    pthread_mutex_lock(&lock);
    while (count == 0)
      while (pthread_cond_wait(&itemAvailable, &lock) != 0)
        ;

    struct item new_item = buffer[tail];
    new_item.info[strcspn(new_item.info, "\n")] = 0;
    tail = (tail + 1) % N;
    count--;

    if (new_item.num == -1) {
      num_producers_exited++;
    } else {
      gettimeofday(&time, NULL);
      size = snprintf(buf, INFOSIZE, "%s\t%ld-%d\n", new_item.info, time.tv_sec,
                      time.tv_usec);
      write(fd, &buf, size);
    }

    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&spaceAvailable);
  }

  int errno;
  for (int i = 0; i < 3; i++) {
    if ((errno = pthread_join(producers[i], NULL))) {
      fprintf(stderr, "pthread_create :%s\n", strerror(errno));
      exit(1);
    }
  }

  close(fd);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc == 2 && (max_count = atoi(argv[1])) < 0)
    printf("invalid argument... assigning 100\n");

  char *colors[3] = {"red", "white", "blue"};
  int errno;

  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&spaceAvailable, NULL);
  pthread_cond_init(&itemAvailable, NULL);

  for (int i = 0; i < 3; i++) {
    if ((errno = pthread_create(&producers[i], NULL, produce, colors[i]))) {
      fprintf(stderr, "pthread_create :%s\n", strerror(errno));
      exit(1);
    }
  }

  if ((errno = pthread_create(&consumer, NULL, consume, NULL))) {
    fprintf(stderr, "pthread_create :%s\n", strerror(errno));
    exit(1);
  }

  if ((errno = pthread_join(consumer, NULL))) {
    fprintf(stderr, "pthread_join:%s\n", strerror(errno));
    exit(1);
  }

  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&spaceAvailable);
  pthread_cond_destroy(&itemAvailable);

  return 0;
}
