#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 10

int cur_queue_len = 0; // shared variable

pthread_t add_thread[NTHREADS];
pthread_t delete_thread[NTHREADS];

// TODO: [Task3] Initialize lock
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// increase cur_queue_len by 1
// TODO: [Task3] Synchronize queue so that 1 thread can access critical section
void *addQueue() {
  pthread_mutex_lock(&lock);
  cur_queue_len++;
  pthread_mutex_unlock(&lock);
  printf("Added 1 item. Current queue len: %d\n", cur_queue_len);
  return NULL;
}

// decrease cur_queue_len by 1
// TODO: [Task3] Synchronize queue so that 1 thread can access critical section
void *deleteQueue() {
  if (cur_queue_len == 0) {
    printf("No item in the queue.\n");
    return NULL;
  }
  pthread_mutex_lock(&lock);
  cur_queue_len--;
  pthread_mutex_unlock(&lock);
  printf("Deleted 1 item. Current queue len: %d\n", cur_queue_len);
  return NULL;
}

int main() {
  int i;

  // TODO: [Task1] Create 20 threads. 10 threads execute “addQueue”. Other 10 thr
  // ads execute “deleteQueue”.
  for (i = 0; i < NTHREADS; i++) {
    // Create threads
    if (pthread_create(&(add_thread[i]), NULL, addQueue, NULL) != 0) {
      printf("add thread %d failed to create\n", i);
    }
    printf("add thread created successfully: %d\n", i);

    if (pthread_create(&(delete_thread[i]), NULL, deleteQueue, NULL) != 0) {
      printf("delete thread %d failed to create\n", i);
    }
    printf("delete thread created successfully: %d\n", i);
  }

  // TODO: [Task2] Join 20 threads before main returns
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(add_thread[i], NULL);
    pthread_join(delete_thread[i], NULL);
  }

  printf("Final queue len: %d\n", cur_queue_len);
  return EXIT_SUCCESS;
}
