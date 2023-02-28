/* CSCI 5103 Spring 2023
 * Assignment 3
 * name: Flercher Gornick
 * student id: 5579904
 * x500 id: gorni025
 * CSELABS machine: csel-cuda-04 */

#ifndef PART_2
#define PART_2

/* includes used in our src files */
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <wait.h>

/* macros to make code more readable*/
#define BUFSIZE  50
#define COLORSZE 6
#define DEFAULT  100
#define IDSIZE   20
#define INFOSIZE 100
#define KEY      69420
#define KEYSIZE  10

/* item object: contains sequence num and item info */
typedef struct item {
  int num;
  char info[INFOSIZE];
} item_t;

/* ----------- SHARED VARIABLES ---------- */
/* used by producer and consumer processes */
typedef struct shared_vars {
  item_t buffer[BUFSIZE]; // bounded buffer
  int head;               // for tracking bounds of our buffer
  int tail;               // for tracking bounds of our buffer

  int max_count;          // stopping point (could be changed by user input)
  int N;                  // variable for tracking size of our buffer
  int count;              // number of items currently in our buffer

  int current_producer;   // used to synchronize producer threads

  pthread_mutex_t lock;          // for accessing shared variables
  pthread_cond_t spaceAvailable; // buffer condition variable
  pthread_cond_t itemAvailable;  // buffer condition variable
} shared_vars_t;

/* function to initialize our shared memory struct 
 * (called at the start of part2.c) */
extern inline void initialize_shared(shared_vars_t *s) {
  /* initialize shared variables */
  s->head = 0;
  s->tail = 0;
  s->count = 0;

  s->max_count = DEFAULT;
  s->N = BUFSIZE;

  /* create mutex and cond attribute variables 
   * to allow sharing between processes */
  pthread_mutexattr_t mutexattr;
  pthread_mutexattr_init(&mutexattr);

  pthread_condattr_t condattr;
  pthread_condattr_init(&condattr);

  pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
  pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED);

  /* initialize our mutex and conds with our attribute */
  pthread_mutex_init(&s->lock, &mutexattr);
  pthread_cond_init(&s->spaceAvailable, &condattr);
  pthread_cond_init(&s->itemAvailable, &condattr);
}

/* function to deallocate our shared memory struct 
 * (called at the end of part2.c) */
extern inline void free_shared(shared_vars_t *s) {
  /* no memory to actually deallocate really, just making 
   * sure to destroy our mutual exclustion variables*/
  pthread_mutex_destroy(&s->lock);
  pthread_cond_destroy(&s->spaceAvailable);
  pthread_cond_destroy(&s->itemAvailable);
}

#endif // !PART_2
