#include <stdlib.h>
#include <stdio.h>

/*
 * Allocate and forget about n_bytes bytes of memory.
 */
static size_t leak(size_t n_bytes) {
  void *forgotten = malloc(n_bytes);

  /* Even here we check the return value from malloc.
   * ALWAYS check the return value from malloc!  */
  return forgotten ? n_bytes : 0;
}

/*
 * Leak some memory!  To catch these leaks in valgrind, compile and run using:
 *
 *   gcc -Wall -o leak leak.c
 *   valgrind --leak-check=full ./leak 10 10
 *
 * This leaks 10 bytes at a time, 10 times, or 100 bytes total (assuming every
 * malloc call succeeded).  Valgrind will show you which function allocated the
 * memory.  If you want to see exactly _where_ the allocation was performed,
 * compile with debugging info using:
 *
 *   gcc -Wall -g -o leak leak.c
 *
 * Now valgrind will display exactly which _line_ contains the offending
 * allocation.
 */
int main(int argc, char **argv) {

  int i, n_times, n_bytes;
  size_t n_leaked;

  /* Parse args */
  if (argc != 3) {
    printf("usage: %s n_bytes n_times\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  n_bytes = atoi(argv[1]);
  n_times = atoi(argv[2]);
  if (n_bytes <= 0 || n_times <= 0) {
    printf("Both n_bytes and n_times must be positive integers.\n");
    exit(EXIT_FAILURE);
  }

  /* Leak n_bytes a total of n_times */
  n_leaked = 0;
  for (i = 0; i < n_times; i++) {
    n_leaked += leak((size_t) n_bytes);
  }
  printf("Leaked %ld total bytes.\n", (long) n_leaked);

  return EXIT_SUCCESS;
}
