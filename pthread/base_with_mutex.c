#include <pthread.h>
#include <stdio.h>

int const times = 10000;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* p1_run(void* args) {

	int i = 0;
	pthread_mutex_lock(&mutex);
	for(i; i < times; i++) {
		printf("thread-1:%d\n", i);
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}
void* p2_run(void* args) {

	int i = 0;
	pthread_mutex_lock(&mutex);
	for(i; i < times; i++) {
		printf("thread-2:%d\n", i);
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char *argv[]) {


	pthread_t p1, p2;
	pthread_create(&p1, NULL, p1_run, NULL);
	pthread_create(&p2, NULL, p2_run, NULL);
	pthread_exit(NULL);
}



