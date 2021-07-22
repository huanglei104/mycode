#pragma GCC diagnostic warning "-Wformat"
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct shmid_ds sds;
	int *sh_var = NULL;
	int shm_id = shmget((key_t)0x1234, sizeof(int), IPC_CREAT | 0666);

	if(shm_id < 0) return perror("shmget"), -1;

	sh_var = shmat(shm_id, NULL, 0);
	if(sh_var == NULL) return perror("shmat"), -1;

	*sh_var = 8888;

	shmctl(shm_id, IPC_STAT, &sds);

	return printf("shm %d value is %d\n", shm_id, 8888), 0;
}
