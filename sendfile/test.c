#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int fd1, fd2;

	fd1 = open("/home/huanglei/Temp/1.c", O_RDWR);
	fd2 = open("b.txt", O_RDWR | O_CREAT, 0664);

	fd1 = sendfile(fd2, fd1, NULL, 5);
	if (fd1 == -1)
		perror("sendfile");
	else
		printf("send %d bytes\n", fd1);

	close(fd1);
	close(fd2);

	return 0;
}
