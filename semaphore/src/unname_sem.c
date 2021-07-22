#include "common.h"

void* thread_run(void *args)
{
	sem_t *sem = args;
	if(sem_wait(sem) == -1)
		perror("sem_wait");

	printf("thread %ld start\n", pthread_self());
	sleep(2);
	printf("thread %ld end\n", pthread_self());

	if(sem_post(sem)== -1)
		perror("sem_post");

	return NULL;
}

int unname_sem(int time)
{
	pthread_t threads[10];
	sem_t sem;

	if (sem_init(&sem, 0, 1) == -1)
		return perror("sem_init"), -1;

	for (int i = 0; i < 10; i++) {
		if (pthread_create(&threads[i], NULL, thread_run, &sem)) {
			printf("failed to create subthread\n");
		} else
			printf("create %ld thread\n", threads[i]);
	}

	for (int i = 0; i < 10; ++i) {
		pthread_join(threads[i], NULL);
	}

	printf("all thread finish\n");

	return 0;
}

