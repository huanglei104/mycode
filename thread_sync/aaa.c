#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_run(void *arg)
{
	while (1) {
		sleep(1);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[10];

	for (int i = 0; i < 10; i++) {
		pthread_create(&threads[i], NULL, thread_run, NULL);
	}

	for (int i = 0; i < 10; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("main finish\n");

	return 0;
}
