#define _GNU_SOURCE

#include <sched.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>

#define STACK_SIZE 8192

int a;

int foo(void *args)
{
    printf("sub pid %d\n", getpid());
    printf("sub ppid %d\n", getppid());
    pause();

    return 0;
}

int main(int argc, char *argv[])
{
    int pid;
    int flags;
    void *stack;

    printf("main pid %d\n", getpid());
    printf("main ppid %d\n", getppid());

    stack = calloc(1, STACK_SIZE);
    if(stack == NULL) return perror("calloc"), -1;

    flags = CLONE_THREAD | CLONE_VM;

    pid = clone(foo, stack + STACK_SIZE, flags, NULL);
    if(pid == -1) return perror("clone"), pid;

    pause();

    return 0;
}
