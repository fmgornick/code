#ifndef _SERVER_H
#define _SERVER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include "util.h"
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>

/********************* [ Helpful Macro Definitions ] **********************/
#define MIN_PORT 1024                               //Minimum port number, < 1024 is protected
#define MAX_PORT 65535                              //Maximum port number supported by OS
#define MAX_THREADS 100                             //Maximum number of threads
#define MAX_QUEUE_LEN 100                           //Maximum queue length
#define MAX_CE 100                                  //Maximum cache size
#define INVALID -1                                  //Reusable int for marking things as invalid or incorrect
#define INVALID_FLAG 99999                          //Reusable flag to marking a flag as invalid
#define BUFF_SIZE 1024                              //Maximum file path length to make things easier
#define LOG_FILE_NAME "webserver_log"            //Standardized log file name
#define DYNAM_POOL_TID MAX_THREADS + 1              //Standard and save thread ID to pass into working thread pool

/********************* [ Helpful Typedefs        ] ************************/
typedef enum{
  PORT_INDEX        = 1,
  PATH_INDEX        = 2,
  NUM_DSP_INDEX     = 3,
  NUM_WRK_INDEX     = 4,
  DYNM_FLAG_INDEX   = 5,
  CACHE_FLAG_INDEX  = 6,
  QUEUE_LEN_INDEX   = 7,
  CACHE_LEN_INDEX   = 8
} argument_index;

typedef struct request_queue {
   int fd;
   char *request;
} request_t;

typedef struct cache_entry {
    int len;
    char request[BUFF_SIZE];
    char *content;
} cache_entry_t;

/********************* [ Function Prototypes       ] **********************/
void    gracefulTerminationHandler(int sig_caught);
void *  dynamic_pool_size_update(void *arg);
int     getCacheIndex(char *request);
void    addIntoCache(char *mybuf, char *memory , int memory_size);
void    deleteCache();
void    initCache();
char*   getContentType(char * mybuf);
int     readFromDisk(char *filename, void **memory);
void *  dispatch(void *arg);
void *  worker(void *arg);

/********************* [ Static Helper Functions    ] **********************/

/**********************************************
 * EnableThreadCancel
   - description:
      - helpful method called by each of the threads such that they can be signalled
        with the pthread_cancel call and they will terminate immediatly
   - parameters:
      - None
   - returns:
      - None
************************************************/
void EnableThreadCancel(void){
    if(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) < 0){
        perror("Thread could not enable cancel state\n");
        pthread_exit(NULL);
    }
    if(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) < 0){
        perror("Thread could not set cancel type to ASYNC\n");
        pthread_exit(NULL);
    }
}

/**********************************************
 * BlockCancelSignal
   - description:
      - helpful method called by each of the threads such that they can safely service
        certain critcal regions and cannot be cancelled
   - parameters:
      - None
   - returns:
      - None
************************************************/
void BlockCancelSignal(void){
    if(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) < 0){
        perror("Thread could not disable cancel state\n");
        pthread_exit(NULL);
    }
}

/**********************************************
 * pthread_lock_release AND pthread_mem_release
   - description:
      - helpful methods that can be used by pthread_cleanup_push to free thread resources before cancelling
        You will want to call both of these to unlock any mutexs and to free any memory
   - parameters:
      - void *lock_to_rel   --> Address of the lock to unlock
      - void *mem_to_rel    --> Address of memory to free IF NOT NULL
   - returns:
      - None
************************************************/
void pthread_lock_release(void *lock_to_rel) {
    pthread_mutex_unlock(lock_to_rel);
}
void pthread_mem_release(void *mem_to_rel) {
  if(mem_to_rel != NULL){
    free(mem_to_rel);
  }
}

/**********************************************
 * LogPrettyPrint
   - parameters:
      - to_write is expected to be an open file pointer, or it 
        can be NULL which means that the output is printed to the terminal
      - All other inputs are self explanatory or specified in the writeup
   - returns:
       - no return value
************************************************/
void LogPrettyPrint(FILE* to_write, int threadId, int requestNumber, int file_descriptor, char* request_str, int num_bytes_or_error, bool cache_hit){
    if(to_write == NULL){
        printf("[%3d] [%3d] [%3d] [%-30s] [%7d] [%5s]\n", threadId, requestNumber, file_descriptor, request_str, num_bytes_or_error, cache_hit? "TRUE" : "FALSE");
        fflush(stdout);
    }else{
        fprintf(to_write, "[%3d] [%3d] [%3d] [%-30s] [%7d] [%5s]\n", threadId, requestNumber, file_descriptor, request_str, num_bytes_or_error, cache_hit? "TRUE" : "FALSE");
        fflush(to_write);
    }    
}
#endif /* _SERVER_H */
