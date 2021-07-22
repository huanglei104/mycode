#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

void read_child()
{
}

void write_child()
{
}

int main(int argc, char *argv[])
{
	int fd, ret, pid;

	if (mkfifo("./fifo_test", 0666) == -1) {
		if (errno != EEXIST) {
			perror("mkfifo");
			return 0;
		}
	}

	pid = fork();
	if (pid < 0) {
		perror("fork");
		return 0;

	} else if (pid == 0){
		read_child();
		return 0;

	} else {
		pid = fork();
		if (pid < 0) {
			perror("fork");
			return 0;

		} else if (pid == 0){
			read_child();
			return 0;

		} else {
			pid = fork();
		}
	}

	return 0;
}
