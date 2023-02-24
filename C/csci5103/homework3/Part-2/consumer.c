#include "part2.h"

void *consume() {
  char buf[INFOSIZE];
  int size;
  struct timeval time;
  /* set logfile name open for appending with rw-r--r-- permissions */
  int fd = open("consumer.log", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);

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
      size = snprintf(buf, INFOSIZE, "%s\t%ld-%ld\n", new_item.info,
                      time.tv_sec, time.tv_usec);
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
      fprintf(stderr, "pthread_create :%s\n", strerror(errno));
      exit(1);
    }
  }

  /* close our file descriptor and finish thread execution */
  close(fd);
  pthread_exit(NULL);
}
