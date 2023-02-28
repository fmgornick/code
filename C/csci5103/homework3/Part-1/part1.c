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

/* item object: contains sequence num and item info */
struct item {
  int num;
  char info[INFOSIZE];
};

/* ------------ SHARED VARIABLES: (locked with our mutex lock) ------------ */
struct item buffer[BUFSIZE]; // bounded buffer
int head = 0, tail = 0;      // for tracking bounds of our buffer

int max_count = 100;         // stopping point (could be changed by user input)
int N         = BUFSIZE;     // variable for tracking size of our buffer
int count     = 0;           // number of items currently in our buffer

int current_producer = 0;    // used to synchronize producer threads
/* ------------------------------------------------------------------------ */

pthread_t producers[3], consumer; // threads used for program
pthread_mutex_t lock;             // for accessing shared variables
pthread_cond_t spaceAvailable, itemAvailable; // buffer condition variables

/* parent thread process; takes string input for color */
void *produce(void *arg) {
  char *color = arg;
  int size;
  char file[20];
  struct timeval time;

  /* set logfile name based on color and open for appending with 
   * rw-r--r-- permissions */
  sprintf(file, "log/producer_%s.log", color);
  int fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);

  /* grapb the current producer value and this will be used for ordering 
   * our producers in a FCFS fashion */
  pthread_mutex_lock(&lock);
  int producer_num = current_producer;
  current_producer = (current_producer + 1) % 3;
  pthread_mutex_unlock(&lock);

  /* loop max_count times to add that many itmes 
   * NOTE: we actually iterate one extra time to send -1 to consumer */
  for (int i = 0; i <= max_count; i++) {
    /* 1) grab lock 
     * 2) if there's no space left in our buffer, or we're not the 
     *    correct producer process, then: 
     *    a) signal a different producer to try the condition 
     *    b) give up the lock and wait to be signaled again
     * 3) otherwise, proceed with the lock */
    pthread_mutex_lock(&lock);
    while (count == N || producer_num != current_producer) {
      pthread_cond_signal(&spaceAvailable);
      while (pthread_cond_wait(&spaceAvailable, &lock) != 0)
        ;
    }

    struct item new_item;
    /* check if we're at our finishing condition */
    if (i < max_count)
      new_item.num = i;
    else
      new_item.num = -1;

    /* format time and num into new_item.info to add to buffer */
    gettimeofday(&time, NULL);
    size = snprintf(new_item.info, INFOSIZE, "%-7s%-6d%ld-%ld\n", 
                    color, new_item.num, time.tv_sec, time.tv_usec);

    /* add item to buffer, increment head and count 
     * also change current_producer to the next one for a different 
     * producer to jump into the critical section */
    buffer[head] = new_item;
    head = (head + 1) % N;
    count++;
    current_producer = (current_producer + 1) % 3;

    /* throw the data into our logfile for all but the last case */
    if (new_item.num != -1)
      write(fd, &new_item.info, size);

    /* release the lock, and signal that there's a new item available 
     * for the consumer to grab off our buffer */
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&itemAvailable);
  }

  /* close our file descriptor and finish thread execution */
  close(fd);
  pthread_exit(NULL);
}

void *consume() {
  char buf[INFOSIZE];
  int size;
  struct timeval time;
  /* set logfile name and open for appending with rw-r--r-- permissions */
  int fd = open("log/consumer.log", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);

  /* track the number of -1's recieved from producer threads 
   * loop until all the producers signal that they're done */
  int num_producers_exited = 0;
  while (num_producers_exited < 3) {
    /* 1) grab lock 
     * 2) if the buffer is empty, give up the lock and wait to 
     *    be signaled again
     * 3) otherwise, proceed with the lock */
    pthread_mutex_lock(&lock);
    while (count == 0)
      while (pthread_cond_wait(&itemAvailable, &lock) != 0)
        ;

    /* grab item from buffer (remove newline for logging),
     * increment tail, and decrement count */
    struct item new_item = buffer[tail];
    new_item.info[strcspn(new_item.info, "\n")] = 0;
    tail = (tail + 1) % N;
    count--;

    /* if producer sent a -1, then just increment num_producers_exited, 
     * otherwise we want to add the data to our logfile */
    if (new_item.num == -1) {
      num_producers_exited++;
    } else {
      gettimeofday(&time, NULL);
      size = snprintf(buf, INFOSIZE, "%s\t%ld-%ld\n", 
                      new_item.info, time.tv_sec, time.tv_usec);
      write(fd, &buf, size);
    }

    /* release the lock, and signal that there's more space available 
     * for the producers to add item(s) to our buffer */
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&spaceAvailable);
  }

  /* wait for producer threads to finish executing 
   * (they should all probably be done before we reach this anyways) */
  int errno;
  for (int i = 0; i < 3; i++) {
    if ((errno = pthread_join(producers[i], NULL))) {
      fprintf(stderr, "pthread_join :%s\n", strerror(errno));
      exit(1);
    }
  }

  /* close our file descriptor and finish thread execution */
  close(fd);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  /* default max_count to 100 if no user input, or the user 
   * doesn't input an argument properly */
  if (argc == 2 && (max_count = atoi(argv[1])) == 0) {
    printf("invalid argument... assigning 100\n");
    max_count = 100;
  }

  char *colors[3] = {"red", "white", "blue"};
  int errno;

  /* initialize our mutexes and condition variables */
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&spaceAvailable, NULL);
  pthread_cond_init(&itemAvailable, NULL);

  /* create each thread with a corresponding color as an argument */
  for (int i = 0; i < 3; i++) {
    if ((errno = pthread_create(&producers[i], NULL, produce, colors[i]))) {
      fprintf(stderr, "pthread_create :%s\n", strerror(errno));
      exit(1);
    }
  }

  /* create consumer thread */
  if ((errno = pthread_create(&consumer, NULL, consume, NULL))) {
    fprintf(stderr, "pthread_create :%s\n", strerror(errno));
    exit(1);
  }

  /* wait for consumer thread to finish 
   * (consumer thread waits for all the producer threads, 
   *  so this consequently waits for ALL threads) */
  if ((errno = pthread_join(consumer, NULL))) {
    fprintf(stderr, "pthread_join:%s\n", strerror(errno));
    exit(1);
  }

  /* delete our mutexes and condition variables */
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&spaceAvailable);
  pthread_cond_destroy(&itemAvailable);

  return 0;
}
