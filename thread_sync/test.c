#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS 5

int threadn = 0;
int count = 0;
pthread_cond_t cond;
pthread_mutex_t mutex, mutex2;

void* thread_run(void *arg)
{
	while (1) {
		pthread_mutex_lock(&mutex2);
		if (count <= 0) {
			printf("thread %ld wait...\n", pthread_self());
			pthread_mutex_unlock(&mutex2);
			pthread_cond_wait(&cond, &mutex);

		} else {
			count--;
			printf("thread %ld consume one, remain %d\n", pthread_self(), count);
		}
		pthread_mutex_unlock(&mutex2);

		sleep(3);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[THREADS];

	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex2, NULL);


	for (int i = 0; i < THREADS; i++) {
		pthread_create(&threads[i], NULL, thread_run, NULL);
	}

	pthread_mutex_lock(&mutex);

	while (1) {
		pthread_mutex_lock(&mutex2);
		count++;
		printf("add one, remain %d\n", count);
		pthread_mutex_unlock(&mutex2);

		pthread_cond_broadcast(&cond);

		sleep(1);
	}

	pthread_mutex_unlock(&mutex);

	printf("main finish\n");

	return 0;
}
