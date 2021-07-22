#include "common.h"

static int semaphore_init(int sem_id, int value);
static int semaphore_p(int sem_id);
static int semaphore_v(int sem_id);
static int semaphore_destory(int sem_id);

static int sem_id = 0;

static int run(int time)
{
	if(semaphore_p(sem_id) == EXIT_FAILURE)
		return perror("semaphore_p"), EXIT_FAILURE;

	printf("process %d start\n", getpid());
	sleep(time);
	printf("process %d end\n", getpid());

	if(semaphore_v(sem_id) == EXIT_FAILURE)
		return perror("semaphore_v"), EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int xsi_sem(int time)
{
	int cnt = 10;

	sem_id = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	if (sem_id == -1)
		return perror("semget"), EXIT_FAILURE;

	if(semaphore_init(sem_id, 1) == EXIT_FAILURE) {

		printf("failed to initialize semaphore\n");

		if (semaphore_destory(sem_id) == EXIT_FAILURE)
			perror("remove semaphore");

		return EXIT_FAILURE;
	}

	cnt = forkn(cnt, run, time);
	printf("%d child process created\n", cnt);

	if (waitall() == EXIT_SUCCESS)
		printf("all child process finish\n");
	else
		printf("waitall error\n");

	if (semaphore_destory(sem_id) == EXIT_FAILURE)
		perror("semaphore_destory");

	return EXIT_SUCCESS;
}

static int semaphore_init(int sem_id, int value)
{
	union semun sem_union;

	sem_union.val = value;

	if(semctl(sem_id, 0, SETVAL, sem_union) == -1)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

static int semaphore_p(int sem_id)
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	//sem_b.sem_flg = SEM_UNDO;

	if(semop(sem_id, &sem_b, 1) == -1)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

static int semaphore_v(int sem_id)
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	//sem_b.sem_flg = SEM_UNDO;

	if(semop(sem_id, &sem_b, 1) == -1)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

static int semaphore_destory(int sem_id)
{
	if (semctl(sem_id, 0, IPC_RMID) == -1)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
