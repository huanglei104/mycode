/*
 * @file: t_mmap.c
 */
#include <stdio.h>
#include <ctype.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    char *buf;
    off_t len;
    struct stat sb;
    char *fname = "test.bin";

    fd = open(fname, O_RDWR, S_IRUSR | S_IWUSR);

    if(fd == -1) return perror("open"), 1;

    if(fstat(fd, &sb) == -1) return perror("fstat"), 1;

    if(ftruncate(fd, sb.st_size) == -1) return perror("ftruncate"), 1;

    buf = mmap(NULL, sb.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED) return perror("mmap"), 1;

    if (close(fd) == -1) return perror("close"), 1;

    for (len = 0; len < sb.st_size; ++len) {
        buf[len] = toupper(buf[len]);
        /*putchar(buf[len]);*/
    }

    if (munmap(buf, sb.st_size) == -1) return perror("munmap"), 1;

    return 0;
}
