#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
};

int forkn(int n, int (*run)(int time), int time);
int waitall();
