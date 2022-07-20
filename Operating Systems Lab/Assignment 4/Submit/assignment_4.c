/*
OSL:Assignment 04

Instructions
A. Thread synchronization using counting semaphores. 
Application to demonstrate: producer-consumer problem
 with counting semaphores and mutex. 

B. Thread synchronization and mutual exclusion using mutex.
 Application to demonstrate: Reader-Writer problem
  with reader priority.
*/

// COMPILE: gcc assignment_4.c -o assign4out -lpthread
// RUN: ./assign4out

#include <pthread.h>
#include <semaphore.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

// Mutex Lock
pthread_mutex_t lock;

//Counting semaphores (not binary)
sem_t empty,full;

// Global variable for counting shared by producer and consumer
int count=0;

// Buffer array
int* buffer;
// Constant size of the buffer
int BUF_SIZE;

// Current Indices
int pidx,cidx;

// Functions for producer and consumer
void *producer_fn(void *arg) {
	int *my_number = (int*) arg;

	// for(;;) is same as saying while(1)
	for(;;){
		int i;

		printf("\n*********************************************");
		printf("\nProcess [%lu] went inside producer\n", pthread_self());
		sem_wait(&empty);
		// Locking the mutex
		pthread_mutex_lock(&lock);
		
		// Critical section 
		printf("\nProducer [%d] entered critical section || ID: %lu\n",*my_number,pthread_self());
		
		// Save in buffer
		buffer[pidx] = *my_number;

		// Displaying buffer
		printf("\n");
		printf("Current Buffer: ");
		for(int i=0;i<BUF_SIZE;i++)
			printf(" %d ",buffer[i]);
		printf("\n");
	
		// Updating current index
		pidx=(pidx+1)%BUF_SIZE;

		printf("Producer [%d] has exited the critical section || ID: %lu \n",*my_number,pthread_self());
		
		// Unlocking the mutex and releasing the locks
		pthread_mutex_unlock(&lock);

		// Increments value and locks the semaphore
		sem_post(&full);

		printf("Process [%lu] out of Producer\n", pthread_self());
		printf("*********************************************\n");
	}
}

void *consumer_fn(void *arg) {
	int *my_number = (int*) arg;
	for(;;) { // Same as while(1)

		int i;
		printf("\n*********************************************");
		printf("\nProcess [%lu] went inside consumer\n", pthread_self());
		
		sem_wait(&full);
		// Locking the mutex

		pthread_mutex_lock(&lock);
	
		
		// Critical section 
		printf("\nConsumer [%d] entered critical section || ID: %lu  \n",*my_number,pthread_self());
		
		// Consuming from buffer
		buffer[cidx]=0;

		// Displaying buffer
		printf("\n");
		printf("Current Buffer: ");
		for(int i=0;i<BUF_SIZE;i++)
			printf(" %d ",buffer[i]);
		printf("\n");
		
		// Updating index
		cidx=(cidx+1)%BUF_SIZE;

		printf("Consumer [%d] has exited the critical section || ID: %lu\n",*my_number,pthread_self());
		
		// Unlocking the mutex and releasing the locks
		pthread_mutex_unlock(&lock);
		//sem_post(&S);
		
		// Increments value
		sem_post(&empty);

		printf("Process [%lu] out of Consumer", pthread_self());
		printf("\n*********************************************\n");
	}
}

// Main method
int main() {
	int *loc;
	int res,prod_count,cons_count,i;
	printf("\n----------------------------------------------");
	printf("\nPlease enter the size of buffer: \n");
	scanf("%d",&BUF_SIZE);

	// Dynamically allocating the memory to the buffer
	buffer = (int*)malloc(BUF_SIZE* sizeof(int));
	
	printf("\n----------------------------------------------");
	printf("\nNumber of producers: \n");
	scanf("%d",&prod_count);	
	printf("\nNumber of consumers: \n");
	scanf("%d",&cons_count);
	printf("\n----------------------------------------------\n");
	
	// Creatng new threads according to input from the user
	pthread_t producers[prod_count], consumers[cons_count];
	
	// Initializing semaphores
	res=sem_init(&empty,0,BUF_SIZE);

	if(res!=0)
	{
		printf("Caught error in semaphore initialisation! \n");
		exit(EXIT_FAILURE);
	}

	res=sem_init(&full,0,0);

	if(res!=0)
	{
		printf("Caught eror in semaphore initialisation! \n");
		exit(EXIT_FAILURE);
	}
		
	// Initializing mutex lock
	res=pthread_mutex_init(&lock,NULL);
	if(res!=0)
	{
		printf("Caught error in mutex initialisation! \n");
		exit(EXIT_FAILURE);
	}
	
	// Setting inddices to 0
	pidx=0;
	cidx=0;
	
	printf("Creating producer threads...\n");
	for(i = 1; i <= prod_count; i++) {
		printf("Producer number: %d \n", i);
		
		// Allocating memory
		loc=(int *) malloc(sizeof(int));

		// Associating value at memory
		*loc=i;

		// Creating new thread
		res = pthread_create(&producers[i], NULL, producer_fn,
		loc);

		if (res != 0) {
			perror("Caught error in thread creation!");
			exit(EXIT_FAILURE);
		}
		
	}
	
	printf("Creating Consumer threads...\n");
	for(i = 1; i <= cons_count; i++) {
		printf("Consumer number: %d \n",i);

		// Allocating memory
		loc=(int *) malloc(sizeof(int));

		// Associating value at memory
		*loc=i;

		// Creating thread
		res = pthread_create(&consumers[i], NULL, consumer_fn,
		loc);
		if (res != 0) {
			perror("Caughtt error in thread creation!");
			exit(EXIT_FAILURE);
		}		
	}
	
	
	for(int i=0;i<prod_count;i++){
		res = pthread_join(producers[i],NULL);
		if(res!=0){
		    printf("Caught error in thread join: \n");
		    exit(EXIT_FAILURE);
		}
    	}


    	for(int i=0;i<cons_count;i++){
		res = pthread_join(consumers[i],NULL);
		if(res!=0){
		    printf("Cught error in thread join: \n");
		    exit(EXIT_FAILURE);
		}
    	}	

	// Killing everything
	pthread_mutex_destroy(&lock);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;
	
}

