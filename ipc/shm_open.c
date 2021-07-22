#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int *ptr;

    int fd = shm_open("/test_shm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if(fd == -1) return perror("shm_open"), -1;

    //if(write(fd, "aa", 2) < 0) return perror("write"), -1;

    //if(ftruncate(fd, sizeof(int)) == -1) return perror("ftruncate"), -1;

    ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(ptr == MAP_FAILED) return perror("mmap"), -1;

    *ptr = 'A';

    return 0;
}
