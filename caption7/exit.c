#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void exit1()
{
    printf("%s\n", __func__);
}

void exit2()
{
    printf("%s\n", __func__);
}

void exit3()
{
    printf("%s\n", __func__);
}

int main(int argc, char *argv[])
{
    pid_t pid;

    if(atexit(exit1)) return perror("atexit"), -1;
    if(atexit(exit1)) return perror("atexit"), -1;
    if(atexit(exit2)) return perror("atexit"), -1;
    if(atexit(exit3)) return perror("atexit"), -1;

    pid = fork();
    if(pid < 0) return perror("fork"), -1;
    printf("PID %d\n", getpid());
    //sleep(4);
    if(pid == 0) {
        //execl("/usr/bin/pwd", "pwd", NULL);
    }
    //exit(0);
    //_exit(0);
    //_Exit(0);
}
