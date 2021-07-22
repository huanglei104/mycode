#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd = open("./txt.txt", O_WRONLY);
	if (fd == -1) return perror("open"), -1;

	lseek(fd, 0, SEEK_CUR);

	write(fd, "hello", 5);

	return 0;
}
