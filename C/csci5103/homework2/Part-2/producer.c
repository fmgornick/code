#include "part2.h"

void *produce(void *arg) {
  char *color = arg;
  int size;
  char file[20];
  struct timeval time;

  /* set logfile name based on color and open for appending with
   * rw-r--r-- permissions */
  sprintf(file, "producer_%s.log", color);
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
    size = snprintf(new_item.info, INFOSIZE, "%-7s%-6d%ld-%ld\n", color,
                    new_item.num, time.tv_sec, time.tv_usec);

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
