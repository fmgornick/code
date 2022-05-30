#include "server.h"
#include "util.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

// global variables (set in main)
int queue_len           = INVALID;                                  // global integer to indicate the length of the queue
int cache_len           = INVALID;                                  // global integer to indicate the length or # of entries in the cache
int num_worker          = INVALID;                                  // global integer to indicate the number of worker threads
int num_dispatcher      = INVALID;                                  // global integer to indicate the number of dispatcher threads
uint dynamic_flag       = INVALID_FLAG;                             // global flag to indicate if the dynamic poool is being used or not
uint cache_flag         = INVALID_FLAG;                             // global flag to indicate if the cache is being used or not
struct sigaction action;                                            // global signal handling structure for gracefully terminating from SIGINT
FILE *logfile;                                                      // global file pointer for writing to log file in worker


int cache_idx   = 0;                                                // keeps track of where to insert new memory into cache
int request_idx = 0;                                                // track where to put next request in the queue
int remaining   = 0;                                                // track reuests left in the queue
int request_num = 0;                                                // track total number of requests made


pthread_t workers[MAX_THREADS];                                     // array of worker threads
pthread_t dispatchers[MAX_THREADS];                                 // array of dispatcher threads
int       threadIDs[MAX_THREADS];                                   // array of IDs for the workers and dispatchers (they can share the same ID)
pthread_t pool_manager;                                             // thread pool worker thread ID
int       pmID = DYNAM_POOL_TID;


pthread_mutex_t queueLock = PTHREAD_MUTEX_INITIALIZER;              // lock the queue for when dispatchers are adding to, or workers are removing from
pthread_mutex_t cacheLock = PTHREAD_MUTEX_INITIALIZER;              // lock the cache for when workers are adding new content to it
pthread_mutex_t globLock  = PTHREAD_MUTEX_INITIALIZER;              // lock for accessing and changing the remaining variable and num_worker variable
pthread_mutex_t logLock   = PTHREAD_MUTEX_INITIALIZER;              // lock the webserver log, so only one worker can add to it at a time
pthread_cond_t freeSlot   = PTHREAD_COND_INITIALIZER;               // condition variable that the dispatcher waits for so it can add another request to the queue
pthread_cond_t newRequest = PTHREAD_COND_INITIALIZER;               // condition variable that the worker waits for so it can pull a request off the queue


request_t requests[MAX_QUEUE_LEN];                                  // used to track the requests globally between threads


cache_entry_t* cache_array;                                         // cache array for storing requests


/* ************************ Signal Handler Code **********************************/
void gracefulTerminationHandler(int sig_caught) {
  /*
  * mask SIGINT signal, so the signal handler does not get interrupted
  */
  signal(SIGINT, SIG_IGN);

  /*
  * accessing global variables that might be changed so we should lock it
  */
  pthread_mutex_lock(&globLock);
  int num_remn_req = remaining;  
  int nworker = num_worker;
  pthread_mutex_unlock(&globLock);

  /*
  * print to stdout the number of pending requests in the request queue
  */
  printf("\nGraceful Termination: There are [%d] requests left in the request queue\n", num_remn_req);

  /*
  * terminate server by closing threads (including dynamic thread if the flag is set)
  */
  for (int i = 0; i < nworker; i++) {
    if (pthread_cancel(workers[i]) != 0)
      fprintf(stderr, "failed to cancel worker thread %d: %s\n", i, strerror(errno));
  }
  printf("SUCCESS: all worker threads killed\n");

  for (int i = 0; i < num_dispatcher; i++) {
    if (pthread_cancel(dispatchers[i]) != 0)
      fprintf(stderr, "failed to cancel dispatcher thread %d: %s\n", i, strerror(errno));
  }
  printf("SUCCESS: all dispatcher threads killed\n");

  if (dynamic_flag) {
    if (pthread_cancel(pool_manager) != 0)
      perror("failed to cancel pool manager thread");
    else
      printf("SUCCESS: dynamic ppol thread killed\n");
  }

  /*
  * close the log file
  */
  fclose(logfile);
  printf("SUCCESS: closed logfile\n");

  /*
  * remove the cache by calling deleteCache IF using cache [Extra Credit B]
  */
  if (cache_flag)
    deleteCache();
}
/**********************************************************************************/

/* ************************* Dynamic Pool Code ************************************/
void * dynamic_pool_size_update(void *arg) {
  /*
  * allow thread to be asynchronously cancelled
  */
  EnableThreadCancel();

  /*
  * setup cleanup handler to release queue lock if interrupt signal is called
  */
  pthread_cleanup_push(pthread_lock_release, &queueLock);

  /*
  * get the id as an input argument from arg, set it to ID
  */
  int id = *(int *)arg;
  printf("%-30s [%3d] Started\n", "Dynamic Thread Pool Manager", id);

  /*
  * every iteration, check to see if the number of workers matches the number of requests
  * resize the pool if this isn't the case
  * we also use a lock because we're altering the num_worker global variable
  */
  while(1) {
    /*
    * accessing global variables that might be changed so we should lock it
    * also add a lock for when we alter the value of num_worker
    */
    pthread_mutex_lock(&globLock);
    int rem = remaining;  
    int nworker = num_worker;
    pthread_mutex_unlock(&globLock);

    // count number of threads added or removed in this iteration
    if (nworker < rem) {
      // calculate percent change of server load and print how many workers we're creating
      int num_change = rem - nworker;
      double server_load_change = 100 * ((double)rem / nworker - 1);
      printf("created %d worker thread(s) because server load increased by %.2f%%\n", num_change, server_load_change);

      // create the worker threads
      for (int i = nworker; i < rem; i++) {
        if (pthread_create(&workers[i], NULL, worker, &threadIDs[i]) != 0)
          fprintf(stderr, "failed to create worker thread %d: %s\n", i, strerror(errno));
      }

      // update value of num_worker to new number of threads
      pthread_mutex_lock(&globLock);
      num_worker = rem;
      pthread_mutex_unlock(&globLock);
    }

    // delete some threads if there are too many
    else if (nworker > rem && nworker > 1) {
      // calculate percent change of server load
      int num_change = (rem == 0) ? nworker - 1 : nworker - rem;
      double server_load_change = 100 * (1 - (double)rem / nworker);

      // cancel and join threads
      for (int i = rem; i < nworker; i++) {
        // delete thread (assuming there's at least one left to delete)
        if (i > 0) {
          if (pthread_cancel(workers[i]) != 0)
            fprintf(stderr, "failed to cancel worker thread %d: %s\n", i, strerror(errno));
          if (pthread_join(workers[i], NULL) != 0)
            fprintf(stderr, "failed to join worker thread %d: %s\n", i, strerror(errno));
        }
      }

      // print number of threads deleted and update num_worker
      printf("deleted %d worker thread(s) because server load decreased by %.2f%%\n", num_change, server_load_change);
      pthread_mutex_lock(&globLock);
      num_worker = (rem == 0) ? 1 : rem;
      pthread_mutex_unlock(&globLock);
    }
    // sleep for 1 ms
    usleep(1000);
  }

  /*
  * pop queue lock cleanup handler that was pushed onto the queue because we already released the lock
  */
  pthread_cleanup_pop(0);
}
/**********************************************************************************/

/* ************************ Cache Code [Extra Credit B] **************************/

// Function to check whether the given request is present in cache
int getCacheIndex(char *request) {
  /*
  * check if request matches cache array's index request
  * if so return the index, otherwise return invalid
  * also if len = 0, then cache array ran out of values so break
  */
  for (int i = 0; i < cache_len; i++) {
    if (cache_array[i].len == 0)
      break;
    if (strcmp(cache_array[i].request, request) == 0)
      return i;
  }
  return INVALID;    
}

// Function to add the request and its file content into the cache
void addIntoCache(char *mybuf, char *memory , int memory_size){
  /*
  * free memory if it's already been used, update the cache elements
  * and change cache_idx, go back to 0 if index is greater than cache length
  */
  if (cache_array[cache_idx].len > 0)
    free(cache_array[cache_idx].content);

  cache_array[cache_idx].len = memory_size;

  strcpy(cache_array[cache_idx].request, mybuf);

  cache_array[cache_idx].content = memory;

  cache_idx++;
  if (cache_idx >= cache_len)
    cache_idx = 0;
}

// Function to clear the memory allocated to the cache
void deleteCache(){
  /*
  * free memory of content elements if their set, then free the array
  * if len = 0, then memory hasn't been allocated from that index onwards
  * so break from the loop
  */
  for (int i = 0; i < cache_len; i++) {
    if (cache_array[i].len > 0) {
      free(cache_array[i].content);
      cache_array[i].content = NULL;
    }
    else break;
  }
  free(cache_array);
}

// Function to initialize the cache
void initCache(){
  /*
  * initialize dynamic cache array and set the content fields to null pointers
  */
  cache_array = malloc(cache_len * sizeof(cache_entry_t));
  for (int i = 0; i < cache_len; i++) {
    cache_array[i].len = 0;
    cache_array[i].content = NULL;
  }
}

/**********************************************************************************/

/* ******************************** Utilities *************************************/

/*
* function to get the content type from the request
*/
char* getContentType(char *mybuf) {
  /*
  * return the content type based on the file type in the request
  * only checks for .html, .jpg, and .gif files
  */
  char *ext = strrchr(mybuf, '.');
  if (strcmp(ext, ".html") == 0) return "text/html";
  if (strcmp(ext, ".jpg") == 0) return "image/jpeg";
  if (strcmp(ext, ".gif") == 0) return "image/gif";
  else return "text/plain";
}

/*
* function to open and read the file from the disk into the memory
*/
int readFromDisk(char *filename, void **memory) {

  int fd;
  struct stat st;
  void *contents;

  /*
  * open requested file, return INVALID if there's an error
  */
  if ((fd = open(filename + 1, O_RDONLY)) == -1) {
    *memory = (void *)"404: FILE NOT FOUND";
    return INVALID;
  }
  
  /*
  * find the size of the file, read all of the contents into memory argument and return the file size
  * dynamically allocate file size for memory, free up later
  */
  fstat(fd, &st);
  int size = st.st_size;

  contents = malloc(size);
  read(fd, contents, size);
  *memory = contents;

  /*
  * close file descriptors
  */
  close(fd);
  return size;
}

/**********************************************************************************/

/*
* function to receive the request from the client and add to the queue
*/
void * dispatch(void *arg) {
  /*
  * allow thread to be asynchronously cancelled
  */
  EnableThreadCancel();                                         

  /*
  * setup cleanup handler to release queue lock if interrupt signal is called
  */
  pthread_cleanup_push(pthread_lock_release, &queueLock);

  /*
  * get the id as an input argument from arg, set it to ID
  */
  int id = *(int *)arg;
  printf("%-30s [%3d] Started\n", "Dispatcher", id);

  while (1) {

    /*
    * accept client connection, loop back if no connection made
    */
    int fd = accept_connection();
    if (fd < 0) {
      printf("invalid file descriptor\n");
      continue;
    }

    /*
    * Get request from the client
    */
    char req[BUFF_SIZE];
    if (get_request(fd, req)) {
      printf("faulty request, ignored\n");
      continue;
    }

    /*
    * add request to the queue using request_queue struct and increment globals
    * since we're dealing with globals, we need a lock for the queue
    * also need a condition variable to make sure queue isn't already full
    */
    pthread_mutex_lock(&queueLock);
    while (remaining == MAX_QUEUE_LEN)
      pthread_cond_wait(&freeSlot, &queueLock);

    struct request_queue request = { .fd = fd, .request = req };
    requests[request_idx] = request;
    request_idx++;
    pthread_mutex_lock(&globLock);
    remaining++;
    pthread_mutex_unlock(&globLock);

    pthread_cond_signal(&newRequest);
    pthread_mutex_unlock(&queueLock);
  }

  /*
  * pop queue lock cleanup handler that was pushed onto the queue because we already released the lock
  */
  pthread_cleanup_pop(0);

  return NULL;
}

/**********************************************************************************/

/*
* function to retrieve the request from the queue, process it and then return a result to the client
*/
void * worker(void *arg) {
  /*
  * allow thread to be asynchronously cancelled
  */
  EnableThreadCancel();

  bool cache_hit  = false;                                // boolean flag for tracking cache hits or misses if doing
  int filesize    = 0;                                    // integer for holding the file size returned from readFromDisk or the cache
  void *memory    = NULL;                                 // memory pointer where contents being requested are read and stored
  int fd          = INVALID;                              // integer to hold the file descriptor of incoming request
  char path[BUFF_SIZE];                                   // string to hold the file path from the request

  /*
  * setup cleanup handler to release queue lock if interrupt signal is called
  * also add function to release memory for file contents if interrupt is called
  */
  pthread_cleanup_push(pthread_lock_release, &queueLock);
  pthread_cleanup_push(pthread_mem_release, memory);

  /*
  * get the id as an input argument from arg, set it to ID
  */
  int id = *(int *)arg;
  printf("%-30s [%3d] Started\n", "Worker", id);

  while (1) {
    /*
    * pull request from the request queue and decrement globals
    * since we're dealing with globals, we need a lock for the queue
    * also need a condition variable to make sure queue isn't already full
    * we block cancel signal if a request is recieced, so if interrupt is sent we process the whole request first
    */
    pthread_mutex_lock(&queueLock);
    while (remaining == 0)
      pthread_cond_wait(&newRequest, &queueLock);

    BlockCancelSignal();

    fd = requests[0].fd;
    strcpy(path, requests[0].request);

    for (int i = 0; i < remaining - 1; i++)
      requests[i] = requests[i+1];

    request_idx--;
    request_num++;
    pthread_mutex_lock(&globLock);
    remaining--;
    pthread_mutex_unlock(&globLock);

    pthread_cond_signal(&freeSlot);
    pthread_mutex_unlock(&queueLock);

    /*
    * if cache flag is set, try to get data from cache
    * if it returns invalid, then it's a cache miss, so
    * set cache_hit to false, otherwise it's true
    */
    pthread_mutex_lock(&cacheLock);
    int idx = INVALID;
    if (cache_flag) {
      idx = getCacheIndex(path);
      if (idx != INVALID) {
        filesize = cache_array[idx].len;
        memory = cache_array[idx].content;
      }
    }

    cache_hit = idx != INVALID ? true : false;

    /*
    * read from disk if no cache hit or cache flag not set
    * if cache flag set and it's a cache miss, then add the 
    * data to the cache
    */
    if (!cache_hit) {
      filesize = readFromDisk(path, &memory);
      if (cache_flag)
        addIntoCache(path, memory, filesize);
    }
    pthread_mutex_unlock(&cacheLock);


    /*
    * log the request into the file and terminal
    * logfile is global, so we need a lock
    */
    pthread_mutex_lock(&logLock);
    LogPrettyPrint(logfile, id, request_num, fd, path, filesize, cache_hit);
    LogPrettyPrint(stdout, id, request_num, fd, path, filesize, cache_hit);
    pthread_mutex_unlock(&logLock);

    /*
    * get the content type and return the result or error
    * free memory and set it to NULL so the cancel hanlder does not double free
    * re-enable thread cancellation so we can exit our program
    */
    char *content_type = getContentType(path);
    if (filesize != INVALID) {
      if (return_result(fd, content_type, memory, filesize) != 0)
        perror("failed to service request");

      if (!cache_flag) {
        free(memory);
        memory = NULL;
      }
    } else {
      if (return_error(fd, memory) != 0)
        perror("failed to service error");

      if (!cache_flag)
        memory = NULL;
    }

    EnableThreadCancel();
  }

  /*
  * pop queue lock and memory cleanup handler that was pushed onto the queue because we already released the lock
  */
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);

  return NULL;
}

/**********************************************************************************/

int main(int argc, char **argv) {

  /*
  * Error check number of arguments
  */
  if(argc != 9){
    printf("usage: %s port path num_dispatcher num_workers dynamic_flag cache_flag queue_length cache_size\n", argv[0]);
    return -1;
  }

  int port            = -1;
  char path[PATH_MAX] = "no path set\0";
  num_dispatcher      = -1;                               // global variable
  num_worker          = -1;                               // global variable
  dynamic_flag        = 99999;                            // global variable
  cache_flag          = 99999;                            // global variable
  queue_len           = -1;                               // global variable
  cache_len           = -1;                               // global variable

  /*
  * get input args --> (1) port (2) path (3) num_dispatcher (4) num_workers (5) dynamic_flag (6) cache_flag (7) queue_length (8) cache_size
  */
  strcpy(path, argv[PATH_INDEX]);
  port            = strtol(argv[PORT_INDEX], NULL, 10);
  num_dispatcher  = strtol(argv[NUM_DSP_INDEX], NULL, 10);
  num_worker      = strtol(argv[NUM_WRK_INDEX], NULL, 10);
  dynamic_flag    = strtol(argv[DYNM_FLAG_INDEX], NULL, 10);
  cache_flag      = strtol(argv[CACHE_FLAG_INDEX], NULL, 10);
  queue_len       = strtol(argv[QUEUE_LEN_INDEX], NULL, 10);
  cache_len       = strtol(argv[CACHE_LEN_INDEX], NULL, 10);

  /*
  * error check input arguments
  */
  if (port < MIN_PORT || port > MAX_PORT) {
    printf("ERROR: port = %d, should be between 1024 and 65535\n", port);
    exit(1);
  }

  DIR *dir = opendir(path);
  if (!dir) {
    printf("ERROR: path to directory %s doesn't exist", path);
    closedir(dir);
    exit(1);
  } else {
    closedir(dir);
  }

  if (num_dispatcher < 1 || num_dispatcher > MAX_THREADS) {
    printf("ERROR: number of dispatchers is %d, should be between 1 and %d\n", num_dispatcher, MAX_THREADS);
    exit(1);
  }

  if (num_worker < 1 || num_worker > MAX_THREADS) {
    printf("ERROR: number of workers is %d, should be between 1 and %d\n", num_worker, MAX_THREADS);
    exit(1);
  }

  if (dynamic_flag != 0 && dynamic_flag != 1) {
    printf("ERROR: dynamic flag should be set to either 0 or 1\n");
    exit(1);
  }

  if (cache_flag != 0 && cache_flag != 1) {
    printf("ERROR: cache flag should be set to either 0 or 1\n");
    exit(1);
  }

  if (queue_len < 1 || queue_len > MAX_QUEUE_LEN) {
    printf("ERROR: queue length is %d, should be between 1 and %d\n", queue_len, MAX_QUEUE_LEN);
    exit(1);
  }

  if (cache_len < 1 || cache_len > MAX_CE) {
    printf("ERROR: cache size is %d, should be between 1 and %d\n", cache_len, MAX_CE);
    exit(1);
  }


  /*
  * verify arguments print statement
  */
  printf("Arguments Verified:\n\
    Port:           [%d]\n\
    Path:           [%s]\n\
    num_dispatcher: [%d]\n\
    num_workers:    [%d]\n\
    dynamic_flag:   [%s]\n\
    cache_flag:     [%s]\n\
    queue_length:   [%d]\n\
    cache_size:     [%d]\n\n", 
    port, 
    path, 
    num_dispatcher, 
    num_worker, 
    dynamic_flag ? "TRUE" : "FALSE", 
    cache_flag ? "TRUE" : "FALSE", 
    queue_len, 
    cache_len);

  /*
  * change SIGINT action for graceful termination
  */
  action.sa_handler = gracefulTerminationHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  if (sigaction(SIGINT, &action, NULL) < 0)
    perror("failed to handle SIGINT\n");

  /*
  * open log file
  */
  if ((logfile = fopen(LOG_FILE_NAME, "a")) == NULL)
    perror("failed to open log file");

  /*
  * change the current working directory to server root directory
  */
  if (chdir(path) != 0)
    fprintf(stderr, "chdir() to %s failed: %s\n", path, strerror(errno));


  /*
  * initialize cache (if cache flag set)
  */
  if (cache_flag)
    initCache();


  /*
  * start the server
  */
  printf("STARTING SERVER: PORT %d\n", port);
  init(port);

  /*
  * create dispatcher and worker threads
  * assign them IDs indexed in thread IDs array
  * if dynamic flag set, then create it as well
  */
  for (int i = 0; i < MAX_THREADS; i++) {
    threadIDs[i] = i;
  }

  for (int i = 0; i < num_worker; i++) {
    if (pthread_create(&workers[i], NULL, worker, &threadIDs[i]) != 0)
      fprintf(stderr, "failed to create worker thread %d: %s\n", i, strerror(errno));
  }

  for (int i = 0; i < num_dispatcher; i++) {
    if (pthread_create(&dispatchers[i], NULL, dispatch, &threadIDs[i]) != 0)
      fprintf(stderr, "failed to create dispatcher thread %d: %s\n", i, strerror(errno));
  }

  if (dynamic_flag) {
    if (pthread_create(&pool_manager, NULL, dynamic_pool_size_update, &pmID) != 0)
      perror("failed to create pool manager thread");
  }

  /*
  * wait for each of the threads to complete their work, join finished when interrupt is sent
  * remember interrupt is sent to gracefulTerminationHandler
  */
  for (int i = 0; i < MAX_THREADS; i++) {
    if (i < num_worker) {
      if (pthread_join(workers[i], NULL) != 0)
        fprintf(stderr, "failed to join worker thread %d: %s\n", i, strerror(errno));
    }
    if (i < num_dispatcher) {
      if (pthread_join(dispatchers[i], NULL) != 0)
        fprintf(stderr, "failed to join dispatcher thread %d: %s\n", i, strerror(errno));
    }
  }
  if (dynamic_flag) {
    if (pthread_join(pool_manager, NULL) != 0) {
      perror("failed to join pool manager");
    }
  }


  /* SHOULD NOT HIT THIS CODE UNLESS RECEIVED SIGINT AND THREADS CLOSED */
  printf("web_server closing, exiting main\n");
  fflush(stdout);
  return 0;
}
