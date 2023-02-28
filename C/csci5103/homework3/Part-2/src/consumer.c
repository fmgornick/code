/* CSCI 5103 Spring 2023
 * Assignment 3
 * name: Flercher Gornick
 * student id: 5579904
 * x500 id: gorni025
 * CSELABS machine: csel-cuda-04 */

#include "part2.h"

int main(int argc, char *argv[]) {
  int id;
  shared_vars_t *s;

  /* get id of shared memory segment using key passed as arg from part2.c */
  if ((id = shmget(atoi(argv[1]), 0, 0)) < 0) {
    printf("consumer: error getting shared memory\n");
    return 1;
  }

  /* attach our shared vars struct to the segment corresponding to ID */
  s = (shared_vars_t *)shmat(id, NULL, 0);
  if (s == (void *)-1) {
    printf("consumer: error attaching shared memory\n");
    return 2;
  }

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
    pthread_mutex_lock(&s->lock);
    while (s->count == 0)
      while (pthread_cond_wait(&s->itemAvailable, &s->lock) != 0)
        ;

    /* grab item from buffer (remove newline for logging),
     * increment tail, and decrement count */
    item_t new_item = s->buffer[s->tail];
    new_item.info[strcspn(new_item.info, "\n")] = 0;
    s->tail = (s->tail + 1) % s->N;
    s->count--;

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
    pthread_mutex_unlock(&s->lock);
    pthread_cond_signal(&s->spaceAvailable);
  }

  /* wait for producer processes to finish executing
   * (they should all probably be done before we reach this anyways) */
  for (int i = 0; i < 3; i++)
    /* consumer process takes in pids of all producers for waiting */
    waitpid(atoi(argv[i + 2]), NULL, 0);

  /* detach mem segment, close our file descriptor, and exit */
  shmdt(s);
  close(fd);
  return 0;
}
