#include "../include/mapreduce.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_DIGITS 10

int main(int argc, char *argv[]) {
  // takes in (executable, number of mappers, number of reducers, name of file)
  // exit if too few arguments
  if (argc < 4) {
    printf("Less number of arguments.\n");
    printf("./mapreduce #mappers #reducers inputFile\n");
    exit(0);
  }

  // ###### DO NOT REMOVE ######
  // set variables to arguments
  int nMappers = strtol(argv[1], NULL, 10);
  int nReducers = strtol(argv[2], NULL, 10);
  char *inputFile = argv[3];

  // status variable for pids
  int status;
  // string that represents the id arg for mapper and reducer, allocates 10
  // bytes which means we can have max 9 digits for our id, which I assume
  // is more than enough
  char arg[NUM_DIGITS];

  // ###### DO NOT REMOVE ######
  // directory creation/ removal
  bookeepingCode();

  // ###### DO NOT REMOVE ######
  pid_t pid = fork();
  if (pid == 0) {
    // divide input file into 1024B segments and
    // send chunks of data to the mappers in RR fashion
    sendChunkData(inputFile, nMappers);
    exit(0);
  }
  sleep(1);

  // spawnMapper(nMappers)
  for (int i = 0; i < nMappers; i++) {
    pid = fork();
    // exit if forking fails
    if (pid == -1) {
      printf("error forking\n");
      return -1;
    }
    // spawn mappers processes and run 'mapper' executable using exec
    if (pid == 0) {
      sprintf(arg, "%d", i + 1);
      execl("mapper", "mapper", arg, NULL);
    }
  }

  // waitForAll()
  // wait for all children to complete execution
  // to avoid zombies!
  while (wait(&status) > 0)
    ;

  // ###### DO NOT REMOVE ######
  // shuffle sends the word.txt files generated by mapper
  // to reducer based on a hash function
  pid = fork();
  if (pid == 0) {
    shuffle(nMappers, nReducers);
    exit(0);
  }
  sleep(1);

  // spawnReducers(nReducers)
  for (int i = 0; i < nReducers; i++) {
    pid = fork();
    // exit if forking fails
    if (pid == -1) {
      printf("error forking\n");
      return -1;
    }
    // spawn reducer processes and run 'reducer' executable using exec
    if (pid == 0) {
      sprintf(arg, "%d", i + 1);
      execl("reducer", "reducer", arg, NULL);
    }
  }

  // waitForAll()
  // wait for all children to complete execution
  // to avoid zombies!
  while (wait(&status) > 0)
    ;

  return 0;
}
