#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd, newfd;

    fd = open("./output", O_RDWR | O_CREAT, 0666);
    if(fd == -1) return perror("open output"), -1;

    newfd = dup(STDOUT_FILENO);
    if(newfd == -1) return perror("dup"), -1;

    close(STDOUT_FILENO);
    return 0;
}
