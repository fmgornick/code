#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

#define BUFSIZE 10
#define NUMITEMS 100

static pthread_mutex_t buffer_access = PTHREAD_MUTEX_INITIALIZER;

static int buffer[BUFSIZE];
static int in 				= 0;
static int out 				= 0;
static int count 			= 0;

/*
 * Inserts a number into the buffer
*/
void * producer(void *arg)
{
	int item, i;
	//produce items randomly
	for(i = 0; i < NUMITEMS; i++) {
		//Get the lock to start working on the buffer
		pthread_mutex_lock(&buffer_access);

		printf("Producer: Buffer Full Check, busy wait?\n");
		while (count == BUFSIZE) {
			//Buffer full, release the lock, print then get the lock and check again
			pthread_mutex_unlock(&buffer_access);
			printf("Producer: Wasting CPU\n");
			sleep(0.1);
			pthread_mutex_lock(&buffer_access);
		};

		//We have the lock and we know the buffer is not full
		printf("Producer: Buffer NOT Full\n");

		//Add an item into the buffer and release lock
		item 		= rand();
		buffer[in] 	= item;
		in = (in + 1) % BUFSIZE;
		count++;
		printf("Produced item: %10d\tBuffer count: %d\n", item, count);
		pthread_mutex_unlock(&buffer_access);
	}

	return NULL;
}

/*
 * Extracts a number from the buffer
*/
void * consumer(void *arg)
{
	int item, i;
	for(i = 0; i < NUMITEMS; i++) {
		//Get the lock to start working on the buffer
		pthread_mutex_lock(&buffer_access);

		printf("Consumer: Buffer Empty Check, busy wait?\n");
		while (count == 0) {
			//Buffer empty, release the lock, print then get the lock and check again
			pthread_mutex_unlock(&buffer_access);
			printf("Consumer: Wasting CPU\n");
			sleep(0.1);
			pthread_mutex_lock(&buffer_access);
		}

		//We have the lock and we know the buffer is not empty
		printf("Consumer: Buffer NOT Empty\n");

		//Remove item from buffer and unlock the lock
		item = buffer[out];
		out = (out + 1) % BUFSIZE;
		count--;
		printf("Consumed item: %10d\tBuffer count: %d\n", item, count);
		pthread_mutex_unlock(&buffer_access);
	}

	return NULL;
}

int main(int argc, char **argv){
	
	pthread_t prod;
	pthread_t cons;

	//Create consumer threads
	if(pthread_create(&cons, NULL, consumer, NULL)!=0){
		fprintf(stderr,"Error creating consumer thread\n");
		exit(1);
	}
	
	//Let consumer run for a second to demo the wasted CPU of busy wait
	sleep(1);

	//Create producer threads
	if(pthread_create(&prod, NULL, producer, NULL)!=0){
		fprintf(stderr,"Error creating producer thread\n");
		pthread_join(cons,NULL);
		exit(1);
	}

	//Join threads
	if(pthread_join(cons,NULL)!=0)
		fprintf(stderr,"Error joining consumer thread\n");
	if(pthread_join(prod,NULL)!=0)
		fprintf(stderr,"Error joining producer thread\n");

	return 0;
}
