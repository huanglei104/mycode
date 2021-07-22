#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>

void* p1_run(void* args)
{
	sleep(3);
	printf("p1 finish\n");
    return NULL;
}

int main(int argc, char *argv[])
{

	pthread_t t1;

	pthread_create(&t1, NULL, p1_run, NULL);

	pthread_exit(NULL);

    return 0;
}
