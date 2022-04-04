#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 10

int counter;   //shared variable
pthread_t tid[NTHREADS];

// initialize lock
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//updates value of a shared variable counter
void* addCount(void *arg) {
    int value = *(int *) arg;
    pthread_mutex_lock(&lock);
    printf("counter value: %d + %d = ", counter, value);
    counter += value;
    printf("%d\n", counter);
    fflush(stdout);
    pthread_mutex_unlock(&lock);
    return NULL;
}


int main(int argc,  char *argv[]) {
    counter = 0;

    int i;
    int arg_arr[NTHREADS];

    for (i = 0; i < NTHREADS; i++) {
        arg_arr[i] = i;
    }

    for(i = 0; i < NTHREADS; i++) {
        // Create threads
        if(pthread_create(&(tid[i]), NULL, addCount, (void *) &arg_arr[i]) != 0) {
            printf("Thread %d failed to create\n", i);
        }
        printf("Thread created successfully: %d\n", i);
    }

    // join threads
    for(i = 0; i < NTHREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}