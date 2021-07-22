#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void foo() {
    printf("hello %d\n", getpid());
    exit(0);
}

int main(int argc, char *argv[])
{

    int i;
    for(i = 0; i < 5; i++) {
        pid_t pid;

        pid = fork();

        if(pid < 0) {
            perror("fork");
            return -1;
        } else if(pid == 0){
            foo();
        } else {
        }
    }
    return 0;
}
