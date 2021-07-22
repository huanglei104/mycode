#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int offset;
	int fd = open("./txt.txt", O_RDWR | O_APPEND);
	if (fd == -1) return perror("open"), -1;
	
	offset = lseek(fd, 0, SEEK_CUR);
	printf("1 %d\n", offset);
	

	int flag = fcntl(fd, F_GETFL);
	flag &= ~O_APPEND;

	fcntl(fd, F_SETFL, flag);

	offset = lseek(fd, 0, SEEK_END);
	printf("2 %d\n", offset);
	

	lseek(fd, 0, SEEK_SET);

	write(fd, "hello", 5);
	write(fd, "world", 5);

	return 0;
}
