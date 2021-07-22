#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int fd;

	if (mkfifo("./fifo1", 0666) == -1) {
		if(errno != EEXIST) return perror("mkfifo"), -1;
	}

	if ((fd = open("./fifo1", O_WRONLY)) == -1) return perror("open"), -1;

	if (write(fd, "hello", 5) == -1) return perror("write"), -1;

	if (close(fd) == -1) return perror("close"), -1;

	return 0;
}
