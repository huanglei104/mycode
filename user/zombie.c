#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();

    if(pid < 0) return perror("fork"), -1;

    if(pid == 0) {
	sleep(5);
	exit(0);
    }

    return 0;
}
