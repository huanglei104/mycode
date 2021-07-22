#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char buf[100];

	int dir = open("/tmp", O_RDONLY | O_DIRECTORY);
	if (dir == -1) {
		perror("open dir");
		return -1;
	}

	if (read(dir, buf, 100) == -1) {
		perror("read dir");
		return -1;
	}

	printf("data: %s\n", buf);

	return 0;
}
