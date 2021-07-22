#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 100

int count = 1;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* subthread_run(void* args) {
	sleep(2);
	printf("thread %ld finish\n", pthread_self());
	pthread_mutex_lock(&mutex);
	count++;
	pthread_mutex_unlock(&mutex);
	if(count == THREAD_COUNT)
		pthread_cond_signal(&cond);
	return NULL;
}

int main(int argc, char *argv[]) {

	pthread_t threads[THREAD_COUNT];

	int i = 0;
	for(; i < THREAD_COUNT; i++){
		pthread_create(&threads[i], NULL, subthread_run, NULL);
	}
	pthread_cond_wait(&cond, &mutex);
	return 0;
}
