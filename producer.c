#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/unistd.h>
#include<wait.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0,out = 0;
sem_t empty,full;

void* producer(void *arg){
	int item;
	while(1){
		item = rand() % 100;
		sem_wait(&empty);
		
		buffer[in] = item;
		printf("Producer produced: %d\n",item);
		in = (in + 1)%BUFFER_SIZE;
		
		sem_post(&full);
		sleep(1);
	}
}
void* consumer(void *arg){
	int item;
	while(1){
		sem_wait(&full);
		
		item = buffer[out];
		printf("Consumer consumed: %d\n",item);
		out = (out + 1)%BUFFER_SIZE;
		
		sem_post(&empty);
		sleep(2);
	}
}

int main(){
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	
	pthread_t producer_thread, consumer_thread;
	
	pthread_create(&producer_thread, NULL, *producer, NULL);
	pthread_create(&consumer_thread, NULL, *consumer, NULL);
	
	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);
	
	sem_destroy(&empty);
	sem_destroy(&full);
	
	return 0;
}
