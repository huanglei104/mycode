#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    printf("test printf in fork");

    pid = fork();
    if(pid < 0) return perror("fork"), -1;

    return 0;
}
