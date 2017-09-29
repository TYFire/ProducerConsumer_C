#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "CircularBuffer.c"

#define PRODUCER_NUM 3
#define CONSUMER_NUM 1
#define TASK_TIME_LIMIT 4
#define SLEEP_TIME_LIMIT 3

CircularBuffer cb;
pthread_mutex_t cbLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cbProCond = PTHREAD_COND_INITIALIZER; // full -> not full
pthread_cond_t cbCsmCond = PTHREAD_COND_INITIALIZER; // empty -> not empty

void *ProducerThread(void *args);
void *ConsumerThread(void *args);
int TaskTime();
int SleepTime();

int main(void){
	InitQueue(&cb);
	srand((unsigned)time(NULL));
	pthread_t threads[PRODUCER_NUM + CONSUMER_NUM];
	int i = 0;
	for(i = 0; i < CONSUMER_NUM; i++){
		pthread_create(&threads[i], NULL, ConsumerThread, (void *)i);
	}
	sleep(2);
	for(i = 0; i < PRODUCER_NUM; i++){
		pthread_create(&threads[i], NULL, ProducerThread, (void *)i);
	}

	while(1);
	return 0;


}


void *ProducerThread(void *args){
	pthread_detach(pthread_self());
	int num = (int) args;//dont use for now, could be used to tell the type86 of producer, like usb, wifi..
	while(1){
		pthread_mutex_lock(&cbLock);
		while(IsFull(&cb)){
			pthread_cond_wait(&cbProCond, &cbLock);
		}
		int task = TaskTime();
		EnterQueue(&cb, task);
		if(QueueNum(&cb) == 1){
			pthread_cond_broadcast(&cbCsmCond);
		}
		int size = QueueNum(&cb);
		printf("Producer %p products a task, which required %d sec, size: %d\n", &cb, task, size);
		pthread_mutex_unlock(&cbLock);
		
		sleep(SleepTime());
	}
	


}


void *ConsumerThread(void *args){
	pthread_detach(pthread_self());
	int num = (int) args;
	while(1){
		pthread_mutex_lock(&cbLock);
		while(IsEmpty(&cb)){
			pthread_cond_wait(&cbCsmCond, &cbLock);
		}
		int task = LeaveQueue(&cb);
		if(QueueNum(&cb) == QueueSize(&cb) - 1){
			//printf("broadcast to cbProCond\n");
			pthread_cond_broadcast(&cbProCond);
		}
		int size = QueueNum(&cb);
		printf("Consumer %p consumes a task, which required %d sec, size: %d\n", &cb, task, size);
		pthread_mutex_unlock(&cbLock);

		sleep(task);
	}
}


int TaskTime(){
	return (rand() % TASK_TIME_LIMIT) + 1;
}

int SleepTime(){
	return (rand() % SLEEP_TIME_LIMIT) + 1;
}