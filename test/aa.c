#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int s = atoi(argv[1]);
    sleep(s);

    printf("pthread %d finish\n", getpid());
    return 0;
}
