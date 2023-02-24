#include "part2.h"

int main(int argc, char *argv[]) {
  /* default max_count to 100 if no user input, or the user
   * doesn't input an argument properly */
  if (argc == 2 && (s.max_count = atoi(argv[1])) < 0)
    printf("invalid argument... assigning 100\n");

  char *colors[3] = {"red", "white", "blue"};
  int errno;

  /* initialize our mutexes and condition variables */
  pthread_mutex_init(&s.lock, NULL);
  pthread_cond_init(&s.spaceAvailable, NULL);
  pthread_cond_init(&s.itemAvailable, NULL);

  /* create each thread with a corresponding color as an argument */
  for (int i = 0; i < 3; i++) {
    if ((errno = pthread_create(&s.producers[i], NULL, produce, colors[i]))) {
      fprintf(stderr, "pthread_create :%s\n", strerror(errno));
      exit(1);
    }
  }

  /* create consumer thread */
  if ((errno = pthread_create(&s.consumer, NULL, consume, NULL))) {
    fprintf(stderr, "pthread_create :%s\n", strerror(errno));
    exit(1);
  }

  /* wait for consumer thread to finish
   * (consumer thread waits for all the producer threads,
   *  so this consequently waits for ALL threads) */
  if ((errno = pthread_join(s.consumer, NULL))) {
    fprintf(stderr, "pthread_join:%s\n", strerror(errno));
    exit(1);
  }

  /* delete our mutexes and condition variables */
  pthread_mutex_destroy(&s.lock);
  pthread_cond_destroy(&s.spaceAvailable);
  pthread_cond_destroy(&s.itemAvailable);

  return 0;
}
