#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int fd;
	char buf[6] = {[5] = 0};

	if ((fd = open("./fifo1", O_RDONLY)) == -1) return perror("open"), -1;

	if (read(fd, buf, 5) == -1) return perror("read"), -1;

	if (close(fd) == -1) return perror("close"), -1;

	printf("%s\n", buf);

	return 0;
}
