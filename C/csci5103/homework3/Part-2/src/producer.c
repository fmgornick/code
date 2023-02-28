#include "../include/part2.h"

int main(int argc, char *argv[]) {
  int id;
  shared_vars_t *s;

  if ((id = shmget(atoi(argv[1]), 0, 0)) < 0) {
    printf("consumer: error getting shared memory\n");
    return 1;
  }

  s = (shared_vars_t *)shmat(id, NULL, 0);
  if (s == (void *)-1) {
    printf("consumer: error attaching shared memory\n");
    return 2;
  }

  char *color = argv[2];
  int size;
  char file[20];
  struct timeval time;

  /* set logfile name based on color and open for appending with
   * rw-r--r-- permissions */
  sprintf(file, "producer_%s.log", color);
  int fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);

  /* grapb the current producer value and this will be used for ordering
   * our producers in a FCFS fashion */
  pthread_mutex_lock(&s->lock);
  int producer_num = s->current_producer;
  s->current_producer = (s->current_producer + 1) % 3;
  pthread_mutex_unlock(&s->lock);

  /* loop max_count times to add that many itmes
   * NOTE: we actually iterate one extra time to send -1 to consumer */
  for (int i = 0; i <= s->max_count; i++) {
    /* 1) grab lock
     * 2) if there's no space left in our buffer, or we're not the
     *    correct producer process, then:
     *    a) signal a different producer to try the condition
     *    b) give up the lock and wait to be signaled again
     * 3) otherwise, proceed with the lock */
    pthread_mutex_lock(&s->lock);
    while (s->count == s->N || producer_num != s->current_producer) {
      pthread_cond_signal(&s->spaceAvailable);
      while (pthread_cond_wait(&s->spaceAvailable, &s->lock) != 0)
        ;
    }

    struct item new_item;
    /* check if we're at our finishing condition */
    if (i < s->max_count)
      new_item.num = i;
    else
      new_item.num = -1;

    /* format time and num into new_item.info to add to buffer */
    gettimeofday(&time, NULL);
    size = snprintf(new_item.info, INFOSIZE, "%-7s%-6d%ld-%ld\n", color,
                    new_item.num, time.tv_sec, time.tv_usec);

    /* add item to buffer, increment head and count
     * also change current_producer to the next one for a different
     * producer to jump into the critical section */
    s->buffer[s->head] = new_item;
    s->head = (s->head + 1) % s->N;
    s->count++;
    s->current_producer = (s->current_producer + 1) % 3;

    /* throw the data into our logfile for all but the last case */
    if (new_item.num != -1)
      write(fd, &new_item.info, size);

    /* release the lock, and signal that there's a new item available
     * for the consumer to grab off our buffer */
    pthread_mutex_unlock(&s->lock);
    pthread_cond_signal(&s->itemAvailable);
  }

  /* close our file descriptor and finish thread execution */
  shmdt(s);
  close(fd);
  return 0;
}
