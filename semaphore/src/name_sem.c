#include "common.h"

sem_t *sem;

static int sem_remove(sem_t *sem)
{
	if (sem_close(sem) == -1)
		return perror("sem_close"), EXIT_FAILURE;
	else
		if (sem_unlink("name_sem_test") == -1)
			return perror("sem_unlink"), EXIT_FAILURE;

	return EXIT_SUCCESS;
}

static int run(int time)
{
	if(sem_wait(sem) == -1)
		exit(EXIT_FAILURE);

	printf("process %d start\n", getpid());
	sleep(time);
	printf("process %d end\n", getpid());

	if(sem_post(sem) == -1)
		exit(EXIT_FAILURE);

	return EXIT_SUCCESS;
}

int name_sem(int time)
{
	int cnt = 10;

	sem = sem_open("name_sem_test", O_CREAT, 0666, 1);
	if (sem == SEM_FAILED)
		return perror("sem_open"), EXIT_FAILURE;

	cnt = forkn(cnt, run, time);
	printf("%d child process created\n", cnt);

	if (waitall() == EXIT_SUCCESS)
		printf("all child process finish\n");
	else
		printf("waitall error\n");

	if (sem_remove(sem) == EXIT_FAILURE)
		perror("sem_remove");

	return 0;
}
